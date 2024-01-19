//
//  MB_NodePerfectRacePlayer.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_NodePerfectRacePlayer.h"
#include "MB_PerfectRaceProtocol.h"
#include "Game.h"

MB_NodePerfectRacePlayer::MB_NodePerfectRacePlayer()
{
    m_pPlayer = NULL;
//    m_pNodeLevel = NULL;
    m_pNodeEmemy = NULL;
    m_pNodeFriend = NULL;
    m_pRoleLevel = NULL;
    m_pRolePower = NULL;
    m_pIcon = NULL;
    m_pFrame = NULL;
    m_pRoleName = NULL;
}

MB_NodePerfectRacePlayer::~MB_NodePerfectRacePlayer()
{
    m_pPlayer = NULL;
    CC_SAFE_RELEASE_NULL(m_pNodeFriend);
    CC_SAFE_RELEASE_NULL(m_pNodeEmemy);
    CC_SAFE_RELEASE_NULL(m_pRoleLevel);
    CC_SAFE_RELEASE_NULL(m_pRolePower);
    CC_SAFE_RELEASE_NULL(m_pIcon);
    CC_SAFE_RELEASE_NULL(m_pFrame);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
}

bool MB_NodePerfectRacePlayer::init(MB_RaceFighter* pPlayer)
{
    if (pPlayer == NULL)
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/monsterrace_node_detail.ccbi");
    if (pNode)
    {
        addChild(pNode);
        m_pPlayer = pPlayer;
        
        
        onResetWnd();
        return true;
    }
    return false;
}

void MB_NodePerfectRacePlayer::onResetWnd()
{
    if (m_pPlayer)
    {
        //头像
        uint32_t HeadID = m_pPlayer->getHead();
        if(m_pPlayer->getRoleId() == MB_RoleData::getInstance()->getUID())
        {
            HeadID = MB_RoleData::getInstance()->getHead();
        }
        CCSpriteFrame *frame = NULL;
        if (HeadID == 0)
        {
            MB_TitleTemplete* titleTemplete = MB_TitleMgr::getInstance()->getTitleByID(m_pPlayer->getTitle());
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
            if (m_pPlayer->getIsMale())
            {
                frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(titleTemplete->getMFaceFrame());
            }
            else
            {
                frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(titleTemplete->getFFaceFrame());
            }
        }
        else
        {
            uint16_t tID = HeadID%SHAPE_BASE;
            uint16_t shape = HeadID/SHAPE_BASE;
            MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(tID);
            CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTemplete->getPetFace(shape));
            if(textrue !=NULL)
            {
                frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            }
        }
        if (frame != NULL)
        {
            m_pIcon->setDisplayFrame(frame);
            NSGameHelper::creatMaskSprite(m_pIcon);
        }
        
        //m_pFrame->setVisible(false);
        
        //战斗力
        char str[32] = {0};
        sprintf(str, "%llu", m_pPlayer->getFightPower());
        m_pRolePower->setString(str);
        //等级
        sprintf(str,"Lv.%d", m_pPlayer->getRoleLevel());
        m_pRoleLevel->setString(str);
        
        //名字
        m_pRoleName->setString(m_pPlayer->getRoleName().c_str());
        
        //是否好友
        CCArray* tempArray = MB_FriendMgr::getInstance()->getFriendArray();
        uint32_t roleID = m_pPlayer->getRoleId();
        m_pNodeEmemy->setVisible(false);
        m_pNodeFriend->setVisible(false);
        for (int i = 0; i < tempArray->count(); i++)
        {
            MB_DataFriend* dataFriend = (MB_DataFriend*)tempArray->objectAtIndex(i);
            if (dataFriend->getRoleID() == roleID)
            {
                m_pNodeFriend->setVisible(true);
            }
        }
        //是否仇人
        if (m_pNodeFriend->isVisible() == false)
        {
            tempArray = MB_FriendMgr::getInstance()->getEnemyArray();
            for (int i = 0; i < tempArray->count(); i++)
            {
                MB_DataFriend* dataFriend = (MB_DataFriend*)tempArray->objectAtIndex(i);
                if (dataFriend->getRoleID() == roleID)
                {
                    m_pNodeEmemy->setVisible(true);
                    break;
                }
            }
        }
    }
}

bool MB_NodePerfectRacePlayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_enemy", CCNode*, m_pNodeEmemy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_friend", CCNode*, m_pNodeFriend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleLevel", CCLabelTTF*, m_pRoleLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_power", CCLabelTTF*, m_pRolePower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_roleicon", CCSprite*, m_pIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_frame", CCSprite*, m_pFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_rolename", CCLabelTTF*, m_pRoleName);
    return false;
}

SEL_MenuHandler MB_NodePerfectRacePlayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCheckClicked", MB_NodePerfectRacePlayer::onCheckClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClick", MB_NodePerfectRacePlayer::onIconClick);
    return NULL;
}

SEL_CCControlHandler MB_NodePerfectRacePlayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

MB_NodePerfectRacePlayer* MB_NodePerfectRacePlayer::create(MB_RaceFighter* pPlayer)
{
    MB_NodePerfectRacePlayer* pInstance =  new MB_NodePerfectRacePlayer;
    if (pInstance && pInstance->init(pPlayer))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodePerfectRacePlayer::onCheckClicked(CCObject* pSender)
{
    if(m_pPlayer->getRoleId() == MB_RoleData::getInstance()->getUID()){
        
        MB_Message::sharedMB_Message()->showMessage("不能对比自己");
        return ;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_TeamData::getInstance()->sendpet_view_other(m_pPlayer->getRoleId(),0);
}

void MB_NodePerfectRacePlayer::onIconClick(CCObject* pSender)
{
    onCheckClicked(pSender);
}
