//
//  MB_NodePerfectRacePlayerHead.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_NodePerfectRacePlayerHead.h"
#include "MB_PerfectRaceProtocol.h"
#include "Game.h"
#include "MB_NodePet.h"
MB_NodePerfectRacePlayerHead::MB_NodePerfectRacePlayerHead()
{
    m_pRacePlayer = NULL;
    m_pRoleIcon = NULL;
    m_pRoleName = NULL;
    m_pMenu = NULL;
    m_pIconFrame = NULL;
}

MB_NodePerfectRacePlayerHead::~MB_NodePerfectRacePlayerHead()
{
//    CC_SAFE_RELEASE_NULL(m_pRacePlayer);
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pMenu);
    CC_SAFE_RELEASE_NULL(m_pIconFrame);
    
}

bool MB_NodePerfectRacePlayerHead::init(MB_RacePos* pPos)
{
    if (pPos == NULL)
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/role_node_icon.ccbi");
    if (pNode)
    {
        addChild(pNode);
        m_pRacePlayer = pPos;
        onResetWnd();
        return true;
    }
    return false;
}

void MB_NodePerfectRacePlayerHead::onResetWnd()
{
    //头像
    uint32_t HeadID = m_pRacePlayer->getHead();
    if(m_pRacePlayer->getRoleId() == MB_RoleData::getInstance()->getUID())
    {
        HeadID = MB_RoleData::getInstance()->getHead();
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
    CCSpriteFrame *frame = NULL;
    MB_TitleTemplete* titleTemplete = MB_TitleMgr::getInstance()->getTitleByID(m_pRacePlayer->getTitle());
    if (HeadID == 0)
    {
        if (m_pRacePlayer->getIsMale()) {
            
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
        if(textrue !=NULL){
            frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        }
        m_pIconFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTemplete->getPetKingdom())->getCString()));
    }
    if (frame != NULL) {
        m_pRoleIcon->setDisplayFrame(frame);
        NSGameHelper::creatMaskSprite(m_pRoleIcon);
        
        
    }
    else
    {
        MB_LOG("ERROR PvpHead");
    }

    m_pRoleName->setString(m_pRacePlayer->getRoleName().c_str());
}

CCLabelTTF* MB_NodePerfectRacePlayerHead::getRoleName()
{
    return m_pRoleName;
}
bool MB_NodePerfectRacePlayerHead::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sp_roleicon", CCSprite*, m_pRoleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_rolename", CCLabelTTF*, m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenu", CCMenu*, m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIconFrame", CCSprite*, m_pIconFrame);
    return false;
}

SEL_MenuHandler MB_NodePerfectRacePlayerHead::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClicked", MB_NodePerfectRacePlayerHead::onIconClicked);
    return NULL;
}

SEL_CCControlHandler MB_NodePerfectRacePlayerHead::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

MB_NodePerfectRacePlayerHead* MB_NodePerfectRacePlayerHead::create(MB_RacePos* pPos)
{
    MB_NodePerfectRacePlayerHead* pInstance = new MB_NodePerfectRacePlayerHead;
    if (pInstance && pInstance->init(pPos))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_NodePerfectRacePlayerHead::onIconClicked(CCObject* pSender)
{
    if(m_pRacePlayer->getRoleId() == MB_RoleData::getInstance()->getUID()){
        
        MB_Message::sharedMB_Message()->showMessage("不能对比自己");
        return ;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_TeamData::getInstance()->sendpet_view_other(m_pRacePlayer->getRoleId(),0);
}
