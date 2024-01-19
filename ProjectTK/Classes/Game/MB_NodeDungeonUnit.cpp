//
//  File.cpp
//  ProjectTK
//
//

#include "MB_NodeDungeonUnit.h"
#include "MB_LayerChapterWnd.h"
#include "MB_RechargeSystem.h"
#include "MB_LayerSweep.h"
#include "MB_LayerChapterWnd.h"
MB_NodeDungeonUnit::MB_NodeDungeonUnit():m_pLevel_name(NULL){
    
}
MB_NodeDungeonUnit::MB_NodeDungeonUnit(MB_DungeonData *data):m_pLevel_name(NULL),m_pSprite_back(NULL){
    
    this->m_data = data;
    
    m_pNodeBattleWarn2 = NULL;
    m_pBtnReady = NULL;
    m_pStar[0]=NULL;
    m_pStar[1]=NULL;
    m_pStar[2]=NULL;
    //    m_pPass = NULL;
    m_pSpriteBack = NULL;
    m_pNodeBattleWarn = NULL;
    m_bShowTutorial = false;
    m_pSpr = NULL;
}

MB_NodeDungeonUnit::~MB_NodeDungeonUnit(){
    
    CC_SAFE_RELEASE(m_pNodeBattleWarn2);
    CC_SAFE_RELEASE(m_pLevel_name);
    CC_SAFE_RELEASE(m_pSprite_back);
    CC_SAFE_RELEASE(m_pStar[0]);
    CC_SAFE_RELEASE(m_pStar[1]);
    CC_SAFE_RELEASE(m_pStar[2]);
    //    CC_SAFE_RELEASE(m_pPass);
    CC_SAFE_RELEASE(m_pSpriteBack);
    CC_SAFE_RELEASE(m_pNodeBattleWarn);
    CC_SAFE_RELEASE(m_pSpr);
    CC_SAFE_RELEASE(m_pBtnReady);
    
    
}

bool MB_NodeDungeonUnit::init(){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    if(m_nType  == kChapterTypeAdvance){
        
        return false;//没有这个功能了
        
    }else{
        CCNode*  node= pCCBReader->readNodeGraphFromFile("res/pve_node_dungeon_unit.ccbi", this);
        this->addChild(node);
    }
    pCCBReader->release();
    if (m_data == NULL) {
        
        return true;
    }
    
    onResetWnd();
    
    m_pBtnReady->setSwallowsTouches(false);
    return true ;
}
void MB_NodeDungeonUnit::setPass(){
    m_pStar[0]->setVisible(false);
}

cocos2d::SEL_MenuHandler MB_NodeDungeonUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeDungeonUnit::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
     CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickReady",MB_NodeDungeonUnit::onClickReady);
    return NULL;
}

bool MB_NodeDungeonUnit::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    if ( m_data != NULL && m_data->getIsCanTouch() && m_data->getBestScore() <= 0 && MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    
    if(m_bShowTutorial)
    {
        if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))return true;
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBattleWarn2", CCNode *, m_pNodeBattleWarn2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "level_name", CCLabelTTF *, m_pLevel_name);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star1", CCSprite *,  m_pStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star2", CCSprite *,  m_pStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star3", CCSprite *,  m_pStar[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_back", CCNode *,  m_pSprite_back);
    //    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPass", CCSprite *,m_pPass);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBattleWarn", CCNode *, m_pNodeBattleWarn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpr", CCSprite *,  m_pSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnReady", CCControlButton *,  m_pBtnReady);
    
    
    return true;
}
MB_NodeDungeonUnit *MB_NodeDungeonUnit::create(MB_DungeonData *data,uint8_t type,bool bShowTutorial){
    
    MB_NodeDungeonUnit * node = new MB_NodeDungeonUnit(data);
    node->settype(type);
    node->m_bShowTutorial = bShowTutorial;
    
    if( node && node->init()){
        
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
void MB_NodeDungeonUnit::onResetWnd(){
    int tempInt = m_data->getID()%10000;tempInt = (tempInt-1)/10+1;
    m_pLevel_name->setString(CCString::createWithFormat("%d-%d %s",tempInt,m_data->getNumber(), m_data->getName())->getCString() );
}
void MB_NodeDungeonUnit::setNow(bool b,int bestScore)
{
    for (int i = 0; i < 3; i++) {
        if(bestScore <= i){
            m_pStar[i]->setVisible(false);
        }else
        {
            m_pStar[i]->setVisible(true);
        }
    }
    
    
    if (b) {
        m_pNodeBattleWarn->setVisible(true);
        m_pNodeBattleWarn2->setVisible(true);
        if (m_pNodeBattleWarn->getChildrenCount()==0) {
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
            CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
            CCNode*  node = pCCBReader->readNodeGraphFromFile("res/pve_node_dungeon_highlight.ccbi", this);
            m_pNodeBattleWarn->addChild(node);
            
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");
            CCSprite* guangSpr = CCSprite::createWithSpriteFrameName("efx_horizon_01.png");
            guangSpr->setPosition(ccp(-80.0,-54));
            guangSpr->setScale(.7f);
            m_pNodeBattleWarn2->addChild(guangSpr);
            ccBlendFunc blend = {GL_SRC_ALPHA, GL_DST_ALPHA};
            guangSpr->setBlendFunc(blend);
            CC_SAFE_DELETE(pCCBReader);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_mission_1.png");
            m_pSpr->setDisplayFrame(frame);
            m_pSpr->setPositionY(-25.2f);
        }
    }else
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_mission_2.png");
        m_pSpr->setDisplayFrame(frame);
        m_pNodeBattleWarn->removeAllChildren();
        m_pNodeBattleWarn2->removeAllChildren();
        m_pNodeBattleWarn->setVisible(false);
        m_pNodeBattleWarn2->setVisible(false);
    }
    

}
void MB_NodeDungeonUnit::onSweepClick(CCObject *){
    
    MB_LayerSweep::strCurDungeonName = m_pLevel_name->getString();
    if(MB_RoleData::getInstance()->getVipLevel() < MB_RoleData::getInstance()->getRoleSweepVip())
    {
        char databuf[200];
        //扫荡功能需要VIP级且玩家等级大于15级才可以使用
        sprintf(databuf, "扫荡功能需要VIP%d级才可以使用, VIP等级不足可以进行充值",MB_RoleData::getInstance()->getRoleSweepVip());
        MB_Message::sharedMB_Message()->showMessage("VIP等级不足", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
        return ;
    }
    else if(MB_RoleData::getInstance()->getLevel() < 15)
    {
        MB_Message::sharedMB_Message()->showMessage("15级才可以扫荡");
        return;
    }
    if(MB_RoleData::getInstance()->getEnergy() <= 0 )
    {
        if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(Energy_ADD, NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
        {
            int needMoney = MB_RoleData::getInstance()->getNeedGold();
            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeEnergy)-MB_RoleData::getInstance()->getEnergyBuyTimes();
            if(limit > 0)
            {
                char databuf[200];
                sprintf(databuf, "您的体力不足了, 您可以消耗%d宝石, 来补充20点体力, 您今天还可以购买 %d次。",needMoney,limit);
                MB_Message::sharedMB_Message()->showMessage("购买体力", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyEnergy),NULL);
            }
            else
            {
                if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL)
                {
                    
                    char databuf[200];
                    sprintf(databuf, "您的体力不足了, 并且今日的体力回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数");
                    MB_Message::sharedMB_Message()->showMessage("购买体力", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                    
                }
                else
                {
                    MB_Message::sharedMB_Message()->showMessage("您的体力不足了, 今日体力购买次数已达上限");
                }
            }
        }
        return;
    }
    else if(MB_RoleData::getInstance()->getEnergy() < m_data->getCostEnergy())
    {
        MB_Message::sharedMB_Message()->showMessage("您的体力不足了");
        return;
    }
    
    
    
    if(m_data->getLeftTime() > 0)
    {
        char databuf[200];
        sprintf(databuf, "是否要对当前关卡进行扫荡");
        MB_Message::sharedMB_Message()->showMessage("扫荡", databuf,"确定","取消",this ,menu_selector( MB_NodeDungeonUnit::onGoSweepClick),NULL);
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("此关卡已到达今日远征上限");
    }
    
}
void MB_NodeDungeonUnit::onGoSweepClick(CCObject *){
    
    MB_TARGET_PARENT(MB_LayerChapterWnd, ptr);
    if (ptr)
    {
        ptr->onSweepClicked(m_data);
    }
}


void MB_NodeDungeonUnit::onClickReady(CCObject *)
{
    m_pChapterLayer->swithXuanGuanOrReady(false,getTag()-999,m_pLevel_name->getString());
}
void MB_NodeDungeonUnit::onEnter()
{
    MB_ResWindow::onEnter();
    if (global_tutorialNode!=NULL&&m_bTutorial) {
        m_bTutorial = false;
        int tempInt = m_data->getID()%10000;tempInt = (tempInt-1)/10+1;
        if (tempInt==1) {
            if (m_data->getNumber()==6) {
                global_tutorialNode->setPositionY(global_tutorialNode->getPositionY()+505);
            }else if (m_data->getNumber()==7) {
                global_tutorialNode->setPositionY(global_tutorialNode->getPositionY()+572);
            }else if (m_data->getNumber()>7) {
                global_tutorialNode->setPositionY(global_tutorialNode->getPositionY()+869);
            }
        }
    }
}
