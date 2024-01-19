
#include "MB_LayerEventRecoveryEnergy.h"
#include "MB_LayerChatMain.h"
#include "MB_NodeRolePKQ.h"
#include "MB_FunctionMgr.h"
MB_LayerEventRecoveryEnergy::MB_LayerEventRecoveryEnergy(){
    m_pGetBtn = NULL;
    m_pInfoSpr1= NULL;
    m_pInfoSpr2= NULL;
    m_pInfoSpr3= NULL;
    m_pTowel1 = NULL;
    m_pTowel2 = NULL;
    m_pTowel3 = NULL;
//    m_pNodeCloudLand = NULL;
    m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_ACTIVITY_ENERGY, MB_LayerEventRecoveryEnergy);
    SOCKET_MSG_REGIST(SC_ROLE_GET_ENERGY , MB_LayerEventRecoveryEnergy);
    SOCKET_MSG_REGIST(SC_ACTIVITY_GET_LIST,MB_LayerEventRecoveryEnergy);
//    MB_LayerChatMain::SetChatMainVisible(false,"MB_LayerEventRecoveryEnergy");
}
MB_LayerEventRecoveryEnergy::~MB_LayerEventRecoveryEnergy(){
    
//    CC_SAFE_RELEASE(m_pNodeCloudLand);
    CC_SAFE_RELEASE(m_pGetBtn);
    CC_SAFE_RELEASE(m_pInfoSpr1);
    CC_SAFE_RELEASE(m_pInfoSpr2);
    CC_SAFE_RELEASE(m_pInfoSpr3);
    CC_SAFE_RELEASE(m_pTowel1);
    CC_SAFE_RELEASE(m_pTowel2);
    CC_SAFE_RELEASE(m_pTowel3);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_ENERGY);
    SOCKET_MSG_UNREGIST(SC_ROLE_GET_ENERGY);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_GET_LIST);
//    MB_LayerChatMain::SetChatMainVisible(true,"MB_LayerEventRecoveryEnergy");
}
bool MB_LayerEventRecoveryEnergy::init(){
    
    if(MB_ResWindow::init() == false){
        
        return false;
    }
    m_bShowRoleInfoPanel = true;
    char filename[100];
    sprintf(filename, "res/dinner_layer.ccbi");
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile(filename, this);
    pCCBReader->release();
    this->addChild(NSGameHelper::createDisableTouchLayer12());
    this->addChild(node);
    
    
    schedule(schedule_selector(MB_LayerEventRecoveryEnergy::timeTick),1);
    onResetWnd();
    
    
//    float width = 0;
//    CCSize sz = CCDirector::sharedDirector()->getWinSize();
//    CCNode* pElement;
//    while (width < sz.width * 1.5f)
//    {
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("wenquan.plist");
//        pElement = CCSprite::createWithSpriteFrameName("tmzz_img_spa_smoke.png");
//        pElement->setAnchorPoint(ccp(0,.5f));
//        m_pNodeCloudLand->addChild(pElement);
//        pElement->setPositionX(width);
//        pElement->setTag(-100);
//        width += pElement->getContentSize().width;
//    }
//    pElement->setTag(0);
//    scheduleUpdate();
    return true;
}

//void MB_LayerEventRecoveryEnergy::update(float dt)
//{
//    m_pNodeCloudLand->setPositionX(m_pNodeCloudLand->getPositionX()-1);
//    CCNode* node = (CCNode*)m_pNodeCloudLand->getChildren()->objectAtIndex(m_pNodeCloudLand->getChildrenCount()-1 );
//    if (node->getTag()!=-100) {
//        if (m_pNodeCloudLand->convertToWorldSpace(node->getPosition()).x<670) {
//            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("wenquan.plist");
//            CCSprite* pElement = CCSprite::createWithSpriteFrameName("tmzz_img_spa_smoke.png");
//            pElement->setAnchorPoint(ccp(0,.5f));
//            m_pNodeCloudLand->addChild(pElement);
//            pElement->setPositionX(node->getPositionX()+node->getContentSize().width);
//        }
//    }
//}

MB_LayerEventRecoveryEnergy * MB_LayerEventRecoveryEnergy::create(){
    
    MB_LayerEventRecoveryEnergy *ptr = new MB_LayerEventRecoveryEnergy();
    if(ptr && ptr->init()){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
    
}
cocos2d::SEL_MenuHandler MB_LayerEventRecoveryEnergy::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClosedClicked",  MB_LayerEventRecoveryEnergy::onClosedClicked);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerEventRecoveryEnergy::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGetClick",  MB_LayerEventRecoveryEnergy::onGetClick);
    
    return NULL;
}

void MB_LayerEventRecoveryEnergy::onClosedClicked(CCObject*)
{
    removeFromParent();
//    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}
bool MB_LayerEventRecoveryEnergy::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pGetBtn", CCControlButton *,m_pGetBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInfoSpr1", CCSprite *,m_pInfoSpr1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInfoSpr2", CCSprite *,m_pInfoSpr2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInfoSpr3", CCSprite *,m_pInfoSpr3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTowel1", CCNode *,m_pTowel1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTowel2", CCNode *,m_pTowel2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTowel3", CCNode *,m_pTowel3);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCloudLand", CCNode *,m_pNodeCloudLand);
    
    return false;
}
void MB_LayerEventRecoveryEnergy::onExit()
{
    PlayBackGround(ksSound_YeShiJie);
    MB_ResWindow::onExit();
}

void MB_LayerEventRecoveryEnergy::onEnterTransitionDidFinish()
{
    MB_ResWindow::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_WenQuan);
}
void MB_LayerEventRecoveryEnergy::onResetWnd(void){
    MB_ResWindow::onResetWnd();
    time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
    MB_MoneyEventEnergy*  pEvnet1 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
    MB_MoneyEventEnergy*  pEvnet2 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
    MB_MoneyEventEnergy*  pEvnet3 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(2);
    time_t  temp = pEvnet1->getStartTime();
    time_t  temp2 = pEvnet1->getEnTime();
    time_t  temp3 = pEvnet2->getStartTime();
    time_t  temp4 = pEvnet2->getEnTime();
    time_t  temp5 = pEvnet3->getStartTime();
    time_t  temp6 = pEvnet3->getEnTime();
    
    struct tm *timestruct = localtime(&nowtime);
    int day = timestruct->tm_mday;
    timestruct = localtime(&temp);
    int hour1 = timestruct->tm_hour;
    timestruct = localtime(&temp2);
    int hour2 = timestruct->tm_hour;
    timestruct = localtime(&temp3);
    int hour3 = timestruct->tm_hour;
    timestruct = localtime(&temp4);
    int hour4 = timestruct->tm_hour;
    timestruct = localtime(&temp5);
    int hour5 = timestruct->tm_hour;
    timestruct = localtime(&temp6);
    int hour6 = timestruct->tm_hour;
    int day2 = timestruct->tm_mday;
    if(day != day2){
        m_pGetBtn->setEnabled(false);
        MB_MoneyEevntMgr::getInstance()->sendactivity_energy();
        return;
    }
    timeTick(0);
    
}
void MB_LayerEventRecoveryEnergy::timeTick(float dt){
    
    time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
    MB_MoneyEventEnergy*  pEvnet1 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
    MB_MoneyEventEnergy*  pEvnet2 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
    MB_MoneyEventEnergy*  pEvnet3 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(2);
    
    bool isIn1 = false;
    bool isIn2 = false;
    bool isIn3 = false;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("wenquan.plist");
    if(nowtime <  pEvnet1->getStartTime()){
        //=======================上午未开始=======================
    }
    else if (nowtime  >= pEvnet1->getStartTime() && nowtime  < pEvnet1->getEnTime()) {
        isIn1 = true;
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已开始=======================
            m_pTowel1->setVisible(true);
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
    }else if(nowtime  <  pEvnet2->getStartTime()){
        //=======================中午未开始=======================
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已结束=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
    }else if(nowtime  >=  pEvnet2->getStartTime() && nowtime  <  pEvnet2->getEnTime()){
        isIn2 = true;
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已结束=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet2->getIsGet() == 1){
            //=======================中午已开始=======================
            m_pTowel2->setVisible(true);
        }else  {
            //=======================中午已享用=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
    }
    else if(nowtime  <  pEvnet3->getStartTime()){
        //=======================晚上未开始=======================
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已结束=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet2->getIsGet() == 1){
            //=======================中午已结束=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else  {
            //=======================中午已享用=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
    }else if(nowtime  >=  pEvnet3->getStartTime() && nowtime  <  pEvnet3->getEnTime()){
        isIn3 = true;
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已结束=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet2->getIsGet() == 1){
            //=======================中午已结束=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else  {
            //=======================中午已享用=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet3->getIsGet() == 1){
            //=======================晚上已开始=======================
            m_pTowel3->setVisible(true);
        }else  {
            //=======================晚上已享用=======================
            m_pInfoSpr3->setVisible(true);
            m_pInfoSpr3->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
    }
    else {
        //=======================超过晚上享用时间=======================
        if(pEvnet1->getIsGet() == 1){
            //=======================上午已结束=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else{
            //=======================上午已享用=======================
            m_pInfoSpr1->setVisible(true);
            m_pInfoSpr1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet2->getIsGet() == 1){
            //=======================中午已结束=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }else  {
            //=======================中午已享用=======================
            m_pInfoSpr2->setVisible(true);
            m_pInfoSpr2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_get.png"));
        }
        if(pEvnet3->getIsGet() == 1){
            //=======================晚上已结束=======================
            m_pTowel3->setVisible(true);
        }else  {
            //=======================晚上已享用=======================
            m_pInfoSpr3->setVisible(true);
            m_pInfoSpr3->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_spa_over.png"));
        }
    }
    
    if(isIn1 == false){
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy1_2", false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy1_1", false);
        
    }else {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy1_1", true);
    }
    if (isIn2 == false) {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy2_2", false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy2_1", false);
        
    }else {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy2_1", true);
    }
    if (isIn3 == false) {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy3_2", false);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy3_1", false);
        
    }else {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy3_1", true);
    }
    
}
void MB_LayerEventRecoveryEnergy::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_ROLE_GET_ENERGY:{
            
            MB_Message::sharedMB_Message()->removeALLMessage();
            uint8_t result;
            recvPacket->readU8(&result);
            if(result == 1)
            {
                MB_MoneyEventEnergy* pEvent = MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
                int energy = pEvent->getEnergyMin();
                char databuf[100];
                sprintf(databuf, "成功领取，体力恢复%d点。", energy);
                MB_Message::sharedMB_Message()->showMessage(databuf);
                
            }else if(result == 2){
                
                MB_Message::sharedMB_Message()->showMessage("不在领取体力的时间段");
                
            }else if(result == 3){
                
                MB_Message::sharedMB_Message()->showMessage("已经领取过体力了");
            }
            
        }
            dirty();
            break;
        case SC_ACTIVITY_ENERGY:
            dirty();
            break;
        case SC_ACTIVITY_GET_LIST:
            dirty();
            break;
        default:
            break;
    }
}

void MB_LayerEventRecoveryEnergy::onGetClick(CCObject*)
{
    MB_MoneyEevntMgr::getInstance()->sendrole_get_energy(0);
}
