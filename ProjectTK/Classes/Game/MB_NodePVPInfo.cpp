
#include "MB_NodePVPInfo.h"
#include "Game.h"
#include "MB_RechargeSystem.h"

#include "MB_ItemData.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_NodePVPInfo::MB_NodePVPInfo()
{
    m_pRoleName = NULL;
    m_pRoleRank = NULL;
    m_pRoleFightPower = NULL;
    m_pRoleIcon = NULL;
    m_pNodeBattle = NULL;
    m_pDataPVPRank = NULL;
    m_bShowTutorial = false;
    m_pLabelLevel = NULL;
}

MB_NodePVPInfo::~MB_NodePVPInfo()
{
    CC_SAFE_RELEASE_NULL(m_pRoleIcon);
    CC_SAFE_RELEASE_NULL(m_pRoleRank);
    CC_SAFE_RELEASE_NULL(m_pLabelLevel);
    CC_SAFE_RELEASE_NULL(m_pRoleFightPower);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pNodeBattle);
    CC_SAFE_RELEASE_NULL(m_pDataPVPRank);
}

MB_NodePVPInfo* MB_NodePVPInfo::create(MB_DataPVPRank* dataPVPRank,bool bShowTutorial)
{
    MB_NodePVPInfo* pNode = new MB_NodePVPInfo();
    
    pNode->m_bShowTutorial = bShowTutorial;
    if (pNode != NULL && pNode->init(dataPVPRank)) {
        pNode->autorelease();
        return pNode;
    }
    delete pNode;
    return NULL;
}

bool MB_NodePVPInfo::init(MB_DataPVPRank* dataPVPRank)
{
    MB_ResWindow::init();
    
    CCAssert(dataPVPRank != NULL, "");
    
    m_pDataPVPRank = dataPVPRank;
    m_pDataPVPRank->retain();
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
 
    char databuf[100];
    sprintf( databuf, "res/arena_node_pvpunit.ccbi");
    CCNode *pNode = pCCBReader->readNodeGraphFromFile(databuf, this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    
    onResetWnd();
    
    return true;
}

void MB_NodePVPInfo::onResetWnd()
{
    refreshData();
}

bool MB_NodePVPInfo::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if(m_bShowTutorial)
    {
        TutorialAssignLayerWindow
    }
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleIcon", CCSprite *, m_pRoleIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleRank", CCLabelBMFont *, m_pRoleRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelLevel", CCLabelBMFont *, m_pLabelLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"fightPower", CCLabelBMFont *, m_pRoleFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"roleName", CCLabelTTF *, m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"nodeBattle", CCNode *, m_pNodeBattle);
    
    

    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0) {
        ((CCMenu*)pNode)->setSwallowsTouches(false);
        return true;
    }

    return true;
}

SEL_MenuHandler MB_NodePVPInfo::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFightClicked",MB_NodePVPInfo::onFightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCompareClick",MB_NodePVPInfo::onCompareClick);
    return NULL;
}
SEL_CCControlHandler MB_NodePVPInfo::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodePVPInfo::onFightClicked(cocos2d::CCObject *pSender)
{
    TutorialTriggerComplete
    
    //发送战斗申请
    MB_DataPVPMgr::getInstance()->sendpvp_fight(m_pDataPVPRank->getRoleID(), m_pDataPVPRank->getRoleRank());
    MB_DataPVPMgr::getInstance()->setTarget(m_pDataPVPRank);
}

void MB_NodePVPInfo::onCompareClick(cocos2d::CCObject *pSender)
{
    if(m_pDataPVPRank->getRoleID() == MB_RoleData::getInstance()->getUID()){
        
    
        return;
    }
    MB_LOG("onCompareClicked.");
    MB_TeamData::getInstance()->sendpet_view_other(m_pDataPVPRank->getRoleID(),0);
}


void MB_NodePVPInfo::refreshData(MB_DataPVPRank *dataPVPRank)
{
    if (dataPVPRank != NULL) {
        m_pDataPVPRank->release();
        m_pDataPVPRank = dataPVPRank;
        m_pDataPVPRank->retain();
    }
    
    m_pNodeBattle->setVisible(false);
    
    //头像
    uint32_t HeadID = m_pDataPVPRank->getHead();
    if(m_pDataPVPRank->getRoleID() == MB_RoleData::getInstance()->getUID())
    {
        HeadID = MB_RoleData::getInstance()->getHead();
    }
    CCSpriteFrame *frame = NULL;
    MB_TitleTemplete* titleTemplete = MB_TitleMgr::getInstance()->getTitleByID(m_pDataPVPRank->getRoleTitle());
    if (HeadID == 0)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
        if (m_pDataPVPRank->getIsMale()) {
            
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
    }
    if (frame != NULL) {
        m_pRoleIcon->setDisplayFrame(frame);
        NSGameHelper::creatMaskSprite(m_pRoleIcon);
    }
    else
    {
        MB_LOG("ERROR PvpHead"); 
    }
    
    
    
    //战斗力
    char str[32] = {0};
    sprintf(str, "%llu", m_pDataPVPRank->getRoleFightPower());
    m_pRoleFightPower->setString(str);
    //等级
    sprintf(str,"Lv.%d", m_pDataPVPRank->getRoleLevel());
    m_pLabelLevel->setString(str);
    //排名
    sprintf(str, "%d", m_pDataPVPRank->getRoleRank());
    m_pRoleRank->setString(str);
    //名字
    m_pRoleName->setString(m_pDataPVPRank->getRoleName());
    //查看 or 决斗
    if (m_pDataPVPRank->getCanFight())
    {
        m_pNodeBattle->setVisible(true);
    }
    
    
}
