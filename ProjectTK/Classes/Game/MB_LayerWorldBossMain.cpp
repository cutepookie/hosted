
#include "MB_LayerWorldBossMain.h"
#include "MB_ResearchInstituteInterface.h"
#include "MB_FunctionModule.h"
#include "MB_LayerFunctionRule.h"
#include "MB_NodeRocketTeamDamage.h"
#include "MB_NodeRocketTeamPreReport.h"
#include "MB_NodeRocketTeamReport.h"
#include "MB_SceneGame.h"
int MB_LayerWorldBossMain::ms_nLayerID = 0;
#define BUFF_DISABLE_TOUCH_LAYER 1010
MB_LayerWorldBossMain::MB_LayerWorldBossMain(){
    isToHome = false;
    m_pToAddGuWu = NULL;
    m_pTimeStart = NULL;
    m_pAutoRellifeTime = NULL;
    m_pAddBuff = NULL;
    m_pNodeBoss = NULL;
    m_pNotActive = NULL;
    m_pVipvisible = NULL;
    m_pNodeLife = NULL;
    m_pNodeDie = NULL;
    m_pNodeAddBuff = NULL;
    m_pBossBlood2 = NULL;
    m_pBloodBar = NULL;
    m_pBloodBar1 = NULL;
    m_pBloodBar2 = NULL;
    m_pBloodBar3 = NULL;
    
    m_pBloodTimer = NULL;
    m_pBossLevel = NULL;
    m_pBossBlood = NULL;
    m_pReward = NULL;
    m_pOfflineCost = NULL;
    m_pNowTotalDamage = NULL;
    m_pNowRank = NULL;
    
    m_pDamageZone = NULL;
    m_pAniamtion = NULL;
    m_pNodeActive = NULL;
    m_pPreframe = NULL;
    m_pAutoOffLineBt = NULL;
    m_pAutoPreFrame = NULL;
    m_pAutoFight = NULL;
    m_pWillDo = NULL;
    m_pDone = NULL;
    m_pBuffNum = NULL;
    m_pBuffer= NULL;
    m_bFirstEnter = true;
    m_pBuffAniamtion = NULL;
    isInGame =true;
    m_pNodeFight = NULL;
    isToShowClose = false;
    m_pNodeNowReport = NULL;
    m_nLayerID = ms_nLayerID;
    ms_nLayerID ++;
//    m_bShowRoleInfoPanel = true;
//    m_bShowEXP = true;
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_FAIL,MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_WIN,MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_LAST_INFO_IGNORE,MB_LayerWorldBossMain);
    //    SOCKET_MSG_REGIST(SC_NANM_OFFLINE_PLAY, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_BUFF, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_REBORN, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_HP_SYNC, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_RANK_SYNC, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_BUFF_SYNC, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_HARM_BROADCAST ,MB_LayerWorldBossMain );
    SOCKET_MSG_REGIST(SC_NANM_CUR_INFO_IGNORE, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_CUR_INFO, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_STOP, MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_OPEN, MB_LayerWorldBossMain);
    m_bAnimationComplete = true;
    m_nSelectBuffType = -1;
}
MB_LayerWorldBossMain::~MB_LayerWorldBossMain(){

    if (!m_bFirstEnter)
    {
        m_bFirstEnter = true;
        MB_EventMgr::getInstence()->sendworldboss_close();
    }
    MB_EventMgr::getInstence()->sendworldboss_close();
    
    
    CC_SAFE_RELEASE(m_pToAddGuWu);
    CC_SAFE_RELEASE(m_pAddBuff);
    CC_SAFE_RELEASE(m_pTimeStart);
    CC_SAFE_RELEASE(m_pAutoRellifeTime);
    CC_SAFE_RELEASE(m_pNodeActive);
    CC_SAFE_RELEASE(m_pNodeBoss);
    CC_SAFE_RELEASE(m_pNotActive);
    //CC_SAFE_RELEASE( m_pVipvisible );
    CC_SAFE_RELEASE(m_pNodeLife);
    CC_SAFE_RELEASE(m_pNodeDie );
    CC_SAFE_RELEASE( m_pNodeAddBuff);
    CC_SAFE_RELEASE( m_pBloodBar);
    CC_SAFE_RELEASE(m_pBloodBar1);
    CC_SAFE_RELEASE(m_pBloodBar2);
    CC_SAFE_RELEASE(m_pBloodBar3);
    CC_SAFE_RELEASE( m_pBossLevel );
    CC_SAFE_RELEASE(m_pBossBlood );
    CC_SAFE_RELEASE( m_pReward );
    CC_SAFE_RELEASE(m_pOfflineCost);
    CC_SAFE_RELEASE(m_pNowTotalDamage);
    CC_SAFE_RELEASE( m_pNowRank);
    CC_SAFE_RELEASE(m_pDamageZone);
    CC_SAFE_RELEASE(m_pAniamtion);
    CC_SAFE_RELEASE(m_pPreframe);
    CC_SAFE_RELEASE(m_pAutoOffLineBt);
    CC_SAFE_RELEASE(m_pAutoPreFrame);
    CC_SAFE_RELEASE(m_pAutoFight);
    CC_SAFE_RELEASE(m_pNodeNowReport);
    
    CC_SAFE_RELEASE(m_pWillDo);
    CC_SAFE_RELEASE(m_pDone);
    CC_SAFE_RELEASE(m_pBuffNum);
    CC_SAFE_RELEASE(m_pBuffAniamtion);
    CC_SAFE_RELEASE(m_pBossBlood2);
    
    m_nLayerID ++;
    if(m_nLayerID == ms_nLayerID){
        
        MB_EventMgr::getInstence()->sendworldboss_close();
    }
    
    SOCKET_MSG_UNREGIST(SC_NANM_FIGHT);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_FAIL);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_WIN);
    SOCKET_MSG_UNREGIST(SC_NANM_LAST_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_NANM_REBORN);
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
    SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_NANM_HP_SYNC);
    SOCKET_MSG_UNREGIST(SC_NANM_RANK_SYNC);
    SOCKET_MSG_UNREGIST(SC_NANM_BUFF_SYNC);
    SOCKET_MSG_UNREGIST(SC_NANM_BUFF);
    SOCKET_MSG_UNREGIST(SC_NANM_HARM_BROADCAST );
    SOCKET_MSG_UNREGIST(SC_NANM_CUR_INFO);
    SOCKET_MSG_UNREGIST(SC_NANM_CUR_INFO_IGNORE);
    SOCKET_MSG_UNREGIST(SC_NANM_STOP);
    
}

bool MB_LayerWorldBossMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    MB_ResearchInstituteInterface* pTarget = dynamic_cast<MB_ResearchInstituteInterface*>(pDataSource);
    if (pTarget)
    {
        m_pDataSource = pTarget;
        return true;
    }
    
    return false;
}

void MB_LayerWorldBossMain::onAnimationCompleted()
{
    m_bAnimationComplete = true;
}

bool MB_LayerWorldBossMain::init(){
    
    if( CCLayer::init() == false){
        
        return false;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/station_layer_rocket.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    node= pCCBReader->readNodeGraphFromFile("res/station_node_rocket_unit.ccbi", this);
    m_pNodeBoss->addChild(node);
    m_pAniamtion = pCCBReader->getAnimationManager();
    m_pAniamtion->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerWorldBossMain::onAnimationCompleted));
    CC_SAFE_RETAIN(m_pAniamtion);
    pCCBReader->release();
    
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    node= pCCBReader->readNodeGraphFromFile("res/station_node_rocket_buff.ccbi", this);
    m_pNodeAddBuff->addChild(node);
    m_pBuffAniamtion= pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pBuffAniamtion);
    pCCBReader->release();
    
    
    
    m_pData= (MB_EventData* )MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(0);
    m_pBloodBar1->setVisible(false);
    m_pBloodBar2->setVisible(false);
    m_pBloodBar3->setVisible(false);
    CCNode *barpa =m_pBloodBar->getParent();
    CCPoint pos = m_pBloodBar->getPosition();
    float scalex =   m_pBloodBar->getScaleX();
    float scaley =   m_pBloodBar->getScaleY();
    m_pBloodBar->removeFromParentAndCleanup(true);
    m_pBloodBar->setPosition(ccp(0,0));
    m_pBloodTimer  = CCProgressTimer::create(m_pBloodBar);
    m_pBloodTimer ->setType(kCCProgressTimerTypeBar);
    m_pBloodTimer->setScaleX(scalex);
    m_pBloodTimer->setScaleY(scaley);
    
    m_pBloodTimer->setMidpoint(ccp(0,1));
    m_pBloodTimer->setBarChangeRate(ccp(1, 0));
    m_pBloodTimer->setPosition(pos);
    m_pBloodTimer->setCascadeColorEnabled(true);
    barpa->addChild( m_pBloodTimer);
    isAutoPlay =  false;
    CCUserDefault::sharedUserDefault()->getBoolForKey("autoworldboss");
    m_propertyDirty = false;
    onResetWnd();

    NSGameHelper::changeParent(m_pAddBuff, m_pToAddGuWu);
    m_pToAddGuWu->setPosition(ccp(-18,-96));
    return  true;
}

void MB_LayerWorldBossMain::setBloodCorlorByProgress(float persent)
{
    CCSprite* sp = m_pBloodTimer->getSprite();
    
    if (persent > 75.0f)
    {
        if (sp != m_pBloodBar)
        {
            m_pBloodBar->removeFromParent();
            m_pBloodTimer->setSprite(m_pBloodBar);
            m_pBloodBar->setVisible(true);
            m_pBloodBar1->setVisible(false);
            m_pBloodBar2->setVisible(false);
            m_pBloodBar3->setVisible(false);
        }
        m_pBloodTimer->setPercentage(persent);
        return;
    }
    if (persent > 50.0f)
    {
        if (sp != m_pBloodBar1)
        {
            m_pBloodBar1->removeFromParent();
            m_pBloodTimer->setSprite(m_pBloodBar1);
            m_pBloodBar->setVisible(false);
            m_pBloodBar1->setVisible(true);
            m_pBloodBar2->setVisible(false);
            m_pBloodBar3->setVisible(false);
        }
        m_pBloodTimer->setPercentage(persent);
        return;
    }
    if (persent > 25)
    {
        if (sp != m_pBloodBar2)
        {
            m_pBloodBar2->removeFromParent();
            m_pBloodTimer->setSprite(m_pBloodBar2);
            m_pBloodBar->setVisible(false);
            m_pBloodBar1->setVisible(false);
            m_pBloodBar2->setVisible(true);
            m_pBloodBar3->setVisible(false);
        }
        m_pBloodTimer->setPercentage(persent);
    }
    else
    {
        if (sp != m_pBloodBar3)
        {
            m_pBloodBar3->removeFromParent();
            m_pBloodBar->setVisible(false);
            m_pBloodBar1->setVisible(false);
            m_pBloodBar2->setVisible(false);
            m_pBloodBar3->setVisible(true);
            m_pBloodTimer->setSprite(m_pBloodBar3);
        }
        m_pBloodTimer->setPercentage(persent);
    }
}
void MB_LayerWorldBossMain::onResetWnd (void){
    
    char databuf[256];
    sprintf(databuf, "Lv.%d",m_pData->getbossLevel());
    m_pBossLevel->setString(databuf);
    
    if(m_pData->getIsOpen())
    {
        m_pNodeNowReport->setVisible(true);
        m_pNotActive->setVisible(false);
        m_pNodeActive->setVisible(true);
        
        char databuf[60];
        sprintf(databuf, "%lld (%0.2f%%)",m_pData->getCurHarm(),m_pData->getCurHarm()*100.0f/m_pData->getMaxHp());
        m_pNowTotalDamage->setString(databuf);
        sprintf(databuf, "当前排名:%d",m_pData->getCurRank());
        if(m_pNowRank)m_pNowRank->setString(databuf);
        
        if( isAutoPlay == true )
        {
            if(m_pAutoPreFrame == NULL)
            {
                m_pAutoPreFrame = ((CCSprite *)m_pAutoFight->getNormalImage())->displayFrame();
                m_pAutoPreFrame->retain();
                ((CCSprite *)m_pAutoFight->getNormalImage())->setDisplayFrame(((CCSprite *)m_pAutoFight->getSelectedImage())->displayFrame());
            }
        }
        else
        {
            if(m_pAutoPreFrame != NULL)
            {
                ((CCSprite *)m_pAutoFight->getNormalImage())->setDisplayFrame(m_pAutoPreFrame);
                m_pAutoPreFrame->release();
                m_pAutoPreFrame = NULL;
            }
        }
        if (m_pData->getRebornTime() <= 0) {
            
            m_pNodeLife->setVisible(true);
            m_pNodeDie->setVisible(false);
            m_pNodeAddBuff->setVisible(true);
            
        }else {
            
            m_pNodeLife->setVisible(false);
            m_pNodeDie->setVisible(true);
            m_pNodeAddBuff->setVisible(false);
            schedule(schedule_selector(MB_LayerWorldBossMain::tickReborn),1.0f);
            tickReborn(0);
        }
        
        sprintf(databuf,"%lld", m_pData->getCurHp());
        m_pBossBlood->setString(databuf);
        sprintf(databuf,"%lld", m_pData->getMaxHp());
        m_pBossBlood2->setString(databuf);
        float persent = m_pData->getCurHp()*100.0f/m_pData->getMaxHp();
        //m_pBloodTimer->setPercentage(persent);
        setBloodCorlorByProgress(persent);
        
        
    }else {
        
        m_pNotActive->setVisible(true);
        m_pNodeActive->setVisible(false);
        m_pNodeNowReport->setVisible(false);
        
        sprintf(databuf,"%lld",m_pData->getMaxHp());
        m_pBossBlood->setString(databuf);
        sprintf(databuf,"%lld",m_pData->getMaxHp());
        m_pBossBlood2->setString(databuf);
        //m_pBloodTimer->setPercentage(100.0f);
        setBloodCorlorByProgress(100.0f);
        
        schedule(schedule_selector(MB_LayerWorldBossMain::tickCountToStart),1);
        tickCountToStart(0);
    }
    
    if( m_pData->getIsBuffed()){
        
        m_pDone->setVisible(true);
        m_pWillDo->setVisible(false);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
        CCSpriteFrame *pSprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_guwu_2.png");
        if (pSprFrame)
        {
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateNormal);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateHighlighted);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateSelected);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateDisabled);
        }
    }else {
        
        m_pDone->setVisible(false);
        m_pWillDo->setVisible(true);
        
    }
    sprintf(databuf, "+%d%%",   m_pData->getBuffNum());
    m_pBuffNum->setString(databuf);
    //    sprintf(databuf, "+%d%%",   m_pData->getBuffNumYuanJun());
    //    m_pBuffNumYuanJun->setString(databuf);
    
}
//MB_LayerWorldBossMain* MB_LayerWorldBossMain::create(){
//
//    MB_LayerWorldBossMain *ptr = new MB_LayerWorldBossMain();
//    if(ptr && ptr->init()){
//
//        ptr->autorelease();
//        return ptr;
//    }
//    CC_SAFE_DELETE(ptr);
//    return NULL;
//}
void MB_LayerWorldBossMain::onBufferOneClick(CCObject *){
    
    MB_Message::sharedMB_Message()->showMessage("鼓舞",600);
    SOCKET_REQUEST_START(CS_NANM_BUFF);
    packet->writeU8(1);
    m_nSelectBuffType = 1;
    SOCKET_REQUEST_END(SC_NANM_BUFF, MB_LayerWorldBossMain::onMsgRecv);
}
void MB_LayerWorldBossMain::onBufferTwoClick(CCObject *){
    
    MB_Message::sharedMB_Message()->showMessage("鼓舞",600);
    SOCKET_REQUEST_START(CS_NANM_BUFF);
    packet->writeU8(2);
    m_nSelectBuffType = 2;
    SOCKET_REQUEST_END(SC_NANM_BUFF, MB_LayerWorldBossMain::onMsgRecv);
}

void MB_LayerWorldBossMain::onBufferThreeClick(CCObject *){
    
    MB_Message::sharedMB_Message()->showMessage("鼓舞",600);
    SOCKET_REQUEST_START(CS_NANM_BUFF);
    packet->writeU8(3);
    m_nSelectBuffType = 3;
    SOCKET_REQUEST_END(SC_NANM_BUFF, MB_LayerWorldBossMain::onMsgRecv);
}
cocos2d::SEL_MenuHandler MB_LayerWorldBossMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOfflineClick", MB_LayerWorldBossMain::onOfflineClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAutoBattleClick", MB_LayerWorldBossMain::onAutoBattleClick);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDetailCloseClick", MB_LayerWorldBossMain::onDetailCloseClick);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onYuanJunAddBuffClick", MB_LayerWorldBossMain::onSoSAddBuffClick);
    
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "downinfoClose", MB_LayerWorldBossMain::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onReportClick", MB_LayerWorldBossMain::onReportClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPreReportClick", MB_LayerWorldBossMain::onPreReportClick);
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOfflineClick", MB_LayerWorldBossMain::onOfflineClick);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onYuanJunDetailCloseClick", MB_LayerWorldBossMain::onSoSDetailCloseClick);
    //    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAutoBattleClick", MB_LayerWorldBossMain::onAutoBattleClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattleClick", MB_LayerWorldBossMain::onBattleClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRelifeClick", MB_LayerWorldBossMain::onRelifeClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBufferOneClick", MB_LayerWorldBossMain::onBufferOneClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBufferTowClick", MB_LayerWorldBossMain::onBufferTwoClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBufferThreeClick", MB_LayerWorldBossMain::onBufferThreeClick);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerWorldBossMain::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRuleClicked", MB_LayerWorldBossMain::onRuleClicked);
    
    return  NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerWorldBossMain::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBufferOneClick", MB_LayerWorldBossMain::onBufferOneClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBufferTowClick", MB_LayerWorldBossMain::onBufferTwoClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBufferThreeClick", MB_LayerWorldBossMain::onBufferThreeClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAddBuffClick", MB_LayerWorldBossMain::onAddBuffClick);

    return  NULL;
}
bool MB_LayerWorldBossMain::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTimeStart", CCLabelTTF *,m_pTimeStart);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoRellifeTime", CCLabelBMFont *,m_pAutoRellifeTime);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBoss", CCNode *,m_pNodeBoss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNotAcive", CCNode *,m_pNotActive);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipvisible", CCNode *, m_pVipvisible );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeLife", CCNode *,m_pNodeLife);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeDie", CCNode *,m_pNodeDie );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeAddBuff", CCNode *, m_pNodeAddBuff);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBloodBar", CCSprite *,m_pBloodBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBossLevel", CCLabelBMFont *,m_pBossLevel );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBossBlood", CCLabelBMFont *,m_pBossBlood );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBossBlood2", CCLabelBMFont *,m_pBossBlood2 );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pReward", CCLabelTTF *,m_pReward );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pOfflineCost", CCLabelTTF *,m_pOfflineCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNowTotalDamage", CCLabelBMFont *,m_pNowTotalDamage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNowRank", CCLabelBMFont *,m_pNowRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "damagezone", CCNode*, m_pDamageZone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeActive", CCNode *,m_pNodeActive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoOffLineBt", CCMenuItemImage *, m_pAutoOffLineBt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoFight",CCMenuItemImage *, m_pAutoFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pWillDo",CCNode *,m_pWillDo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDone",CCNode *,m_pDone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBuffNum",CCLabelBMFont *,m_pBuffNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNowReport", CCNode *, m_pNodeNowReport);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBloodBar1", CCSprite*, m_pBloodBar1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBloodBar2", CCSprite*, m_pBloodBar2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBloodBar3", CCSprite*, m_pBloodBar3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAddBuff", CCControlButton*, m_pAddBuff);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToAddGuWu", CCNode *, m_pToAddGuWu);
    
    return false;
}
void MB_LayerWorldBossMain::onMsgRecv(CCNode* node, SocketResponse* response){
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
            
            //        case SC_NANM_OFFLINE_PLAY:
            //            recvworldboss_offline_play(recvPacket);
            //            break;
        case SC_NANM_LAST_INFO_IGNORE:
            recvworldboss_last_info_ignore(recvPacket);
            break;
        case SC_NANM_LAST_INFO_WIN:
            recvworldboss_last_info_win(recvPacket);
            break;
        case SC_NANM_LAST_INFO_FAIL:
            recvworldboss_last_info_fail(recvPacket);
            break;
        case SC_NANM_BUFF:
            recvworldboss_buff(recvPacket);
            break;
        case SC_NANM_REBORN:
            recvworldboss_reborn(recvPacket);
            break;
        case SC_NANM_FIGHT:
            SOCKET_MSG_UNREGIST(SC_NANM_FIGHT);
            recvworldboss_fight(recvPacket);
            break;
        case  SC_NANM_HARM_BROADCAST:
            recvworldboss_harm_broadcast(recvPacket);
            break;
        case SC_NANM_OPEN:{
            
            SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
            if(m_pData->getIsOpen() == false){
                
                MB_Message::removeALLMessage();
                dirty();
            }
        }
            break;
        case SC_NANM_INIT_STATE:{
            
            SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);
            MB_Message::removeALLMessage();
            dirty();
        }
            break;
        case SC_NANM_HP_SYNC:
            recvworldboss_hp_sync(recvPacket);
            break;
        case SC_NANM_BUFF_SYNC:
            recvworldboss_buff_sync(recvPacket);
            break;
        case SC_NANM_STOP:
            recvworldboss_stop(recvPacket);
            break;
        case SC_NANM_RANK_SYNC:
            recvworldboss_rank_sync(recvPacket);
            break;
        case SC_NANM_CUR_INFO:
            recvworldboss_cur_info(recvPacket);
            break;
        case SC_NANM_CUR_INFO_IGNORE:
            recvworldboss_cur_info_ignore(recvPacket);
            break;
        default:
            break;
    }
    
}
bool  MB_LayerWorldBossMain::recvworldboss_cur_info_ignore(MB_MsgBuffer* recvPacket){
    
    MB_Message::removeALLMessage();
    if(m_pNodeFight!=NULL){
        
        m_pNodeFight->removeFromParentAndCleanup(true);
    }
//    m_pNodeFight = MB_NodeRocketTeamReport::create(2);
//    addChild(m_pNodeFight);
    return true;
}
bool  MB_LayerWorldBossMain::recvworldboss_cur_info(MB_MsgBuffer* recvPacket){
    
    MB_Message::removeALLMessage();
    //    if(m_pNodeFight!=NULL){
    //
    //        m_pNodeFight->removeFromParentAndCleanup(true);
    //    }
    m_pNodeFight = MB_NodeRocketTeamReport::create(0);
    //    addChild(m_pNodeFight);
    pushWindow(m_pNodeFight);
    return true;
}
bool  MB_LayerWorldBossMain::recvworldboss_harm_broadcast(MB_MsgBuffer *recvPaccket){
    
    if( isInGame == false){
        
        return  true;
    }
    uint16_t data16;
    int data64;
    recvPaccket->readU16(&data16);
    for(int i = 0 ; i < data16 ; i++){
        
        char *str =recvPaccket->ReadString();
        recvPaccket->readU64(&data64);
        MB_NodeRocketTeamDamage *ptr = MB_NodeRocketTeamDamage::create(data64,str);
        int rangeX = m_pDamageZone->getContentSize().width;
        int rangeY = m_pDamageZone->getContentSize().height;
        ptr->setPosition(ccp(rand()%rangeX,rand()%rangeY));
        m_pDamageZone->addChild(ptr);
        CC_SAFE_FREE(str);
    }
    m_bAnimationComplete = false;
    m_pAniamtion->runAnimationsForSequenceNamed("beattack");
    
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_buff(MB_MsgBuffer *recvPaccket){
    
    uint8_t data8;
    uint8_t type;
    recvPaccket->readU8(&type);
    recvPaccket->readU8(&data8);
    int result = data8;
    MB_Message::removeALLMessage();
    if(m_pBuffer != NULL && result == 1 ){
        
        this->removeChildByTag(BUFF_DISABLE_TOUCH_LAYER);
        m_pBuffer->removeFromParentAndCleanup(true);
        m_pBuffer = NULL;
        if(m_pData->getIsOpen() == false){
            
            int num = m_pData->getBuffNum()+ (type == 1 ? 1 :(type == 2? 5 : 30));
            char databuf[100];
            sprintf(databuf, "+%d%%",  num);
            m_pBuffNum->setString(databuf);
            m_pBuffAniamtion->runAnimationsForSequenceNamed("add");
            
        }
    }
    if(result == 2){
        char type[32] = {};
        if (m_nSelectBuffType == 1) {
            sprintf(type, "%s","金币");
        }
        if (m_nSelectBuffType == 2) {
            sprintf(type, "%s","宝石");
        }
        if (m_nSelectBuffType == 3) {
            sprintf(type, "%s","宝石");
        }
        char buff[128] = {};
        char title[32] = {};
        sprintf(title,"%s不足",type);
        sprintf(buff,"您的%s不足, 充值可以增加资源, 进行勇气鼓舞。",type);
        MB_Message::sharedMB_Message()->showMessage(title,buff,"充值","取消",this,menu_selector(MB_RoleData::goCharge),NULL);
        //MB_Message::sharedMB_Message()->showMessage("失败","资源不足","确定");
    }
    if(result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("失败","已经擂过鼓","确定");
    }
    if( m_pData->getIsBuffed()){
        
        m_pDone->setVisible(true);
        m_pWillDo->setVisible(false);
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
        CCSpriteFrame *pSprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_guwu_2.png");
        if (pSprFrame)
        {
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateNormal);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateHighlighted);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateSelected);
            m_pAddBuff->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateDisabled);
        }
        
    }else {
        
        m_pDone->setVisible(false);
        m_pWillDo->setVisible(true);
        
    }
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_rank_sync(MB_MsgBuffer *recvPaccket){
    
    char databuf[100];
    sprintf(databuf, "%d",m_pData->getCurRank());
    m_pNowRank->setString(databuf);
    
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_buff_sync(MB_MsgBuffer *recvPaccket){
    
    char databuf[100];
    sprintf(databuf, "+%d%%",   m_pData->getBuffNum());
    m_pBuffNum->setString(databuf);
    m_pBuffAniamtion->runAnimationsForSequenceNamed("add");
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_stop(MB_MsgBuffer *recvPaccket){
    
    recvPaccket->readU8(&lastBossResult);
    if(lastBossResult == 1){
        
        recvPaccket->readU64(&harm);
        recvPaccket->readU32(&coin);
        recvPaccket->readU32(&repu);
    }
    unschedule(schedule_selector(MB_LayerWorldBossMain::tickReborn));
    schedule(schedule_selector(MB_LayerWorldBossMain::tickBossBeKillShowMessage));
    isToShowClose = true;
    sendworldboss_open(NULL);
    return true;
}
void MB_LayerWorldBossMain::tickBossBeKillShowMessage(float dt){
    
    char databuf[400];
    if (lastBossResult == 1) {
        
        sprintf(databuf, "火箭队已经被击败。您：\n累计输出伤害：%llu\n累计获得补天石：%d\n累计获得金币：%d",harm,repu,coin);
        
    }else {
        
        sprintf(databuf, "火箭队坚不可摧，们都纷纷离开");
    }
    MB_Message::sharedMB_Message()->showMessage("攻打结束",databuf,"确定");
    unschedule(schedule_selector(MB_LayerWorldBossMain::tickBossBeKillShowMessage));
    
}
bool MB_LayerWorldBossMain::recvworldboss_hp_sync(MB_MsgBuffer *recvPaccket){
    
    char databuf[100];
    sprintf(databuf,"%lld", m_pData->getCurHp());
    m_pBossBlood->setString(databuf);
    sprintf(databuf,"%lld", m_pData->getMaxHp());
    m_pBossBlood2->setString(databuf);
    float persent = m_pData->getCurHp()*100.0f/m_pData->getMaxHp();
    //m_pBloodTimer->setPercentage(persent);
    setBloodCorlorByProgress(persent);
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_fight(MB_MsgBuffer *recvPacket){
    
    uint8_t data8;
    recvPacket->readU8(&data8);
    if (data8 ==1 ) {
        
        short data16;
        recvPacket->readU16(&data16);
        MB_NetStructFight fight;
        MB_Message::removeALLMessage();
        recvfight *  fightresult =fight.recvfight_request(recvPacket);
        strcpy(fightresult->isBoss,"111111");
        fightresult->type = kFightResultTypeNanm;
        isInGame = false;
        int data32;
        recvPacket->readU32(&data32);
        m_pData->setRebornTime(data32);
        int rewardcoin;
        recvPacket->readU32(&rewardcoin);
        int rewardrep;
        recvPacket->readU32(&rewardrep);
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,rewardcoin,rewardrep,true));
        sendworldboss_open(NULL);

    }else if(data8 ==2 ){
        
        MB_Message::sharedMB_Message()->showMessage("失败","等待复活中","确定");
        
    }else if(data8 == 3){
        
        MB_Message::sharedMB_Message()->showMessage("决斗失败","疯狂的火箭队已经被击败了。","确定");
        
    }else if(data8 == 4){
        
        MB_Message::sharedMB_Message()->showMessage("决斗失败","攻打火箭队的战斗已经结束了。","确定");
        
    }else if(data8 == 5){
        
//        MB_Message::sharedMB_Message()->showMessage("失败","您当前处于离线参与中","确定");

    }else if(data8 == 6){
        
        MB_Message::sharedMB_Message()->showMessage("失败","未知错误","确定");
    }
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_reborn(MB_MsgBuffer *recvPacket){
    
    uint8_t data8;
    recvPacket->readU8(&data8);
    if (data8 == 1) {
        
        m_pNodeLife->setVisible(true);
        m_pNodeDie->setVisible(false);
        m_pNodeAddBuff->setVisible(true);
        m_pData->setRebornTime(0);
        unschedule(schedule_selector(MB_LayerWorldBossMain::tickReborn));
        
    }else if(data8 == 2) {
        
        MB_Message::sharedMB_Message()->removeALLMessage();
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
        
    }else if(data8 == 3) {
        
        MB_Message::sharedMB_Message()->removeALLMessage();
        MB_Message::sharedMB_Message()->showMessage("疯狂的火箭队已经被击败了");
        dirty();
    }
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_offline_play(MB_MsgBuffer* recvPacket){
    
    //
    //    int8_t data8;
    //    recvPacket->readU8(&data8);
    //    if (data8 == 1 )
    //    {
    //        if (m_pYuanJunBuffer)
    //        {
    //            m_pYuanJunBuffer->removeFromParentAndCleanup(true);
    //            m_pYuanJunBuffer = NULL;
    //        }
    //        if( m_pData->getIsOfflinePlay() == true)
    //        {
    //            m_pDoneYuanJun->setVisible(true);
    //            m_pWillDoYuanJun->setVisible(false);
    //        }
    //        else
    //        {
    //            m_pDoneYuanJun->setVisible(false);
    //            m_pWillDoYuanJun->setVisible(true);
    //        }
    //        // 攻击力增加
    //        char databuf[100];
    //        sprintf(databuf, "+%d%%",   m_pData->getBuffNumYuanJun());
    //        m_pBuffNumYuanJun->setString(databuf);
    //        m_pBuffAniamtionYuanJun->runAnimationsForSequenceNamed("add");
    //    }
    return  true;
}

void  MB_LayerWorldBossMain::onAddBuffClick(CCObject *object){
    
    if(m_pBuffer == NULL){
        
        if(m_pData->getIsBuffed() == true){
            
            MB_Message::sharedMB_Message()->showMessage("每次活动结束前, 只能鼓舞1次.");
            return;
        }
        
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        m_pBuffer= pCCBReader->readNodeGraphFromFile("res/worldboss_layer_addbuff.ccbi", this);
        
        this->addChild(NSGameHelper::createDisableTouchLayer(),0,BUFF_DISABLE_TOUCH_LAYER);
        this->addChild(m_pBuffer);
        pCCBReader->release();
        
    }else {
        
        this->removeChildByTag(BUFF_DISABLE_TOUCH_LAYER);
        m_pBuffer->removeFromParentAndCleanup(true);
        m_pBuffer = NULL;
        
    }
}

//////////援军助阵//////////
void MB_LayerWorldBossMain::onSoSAddBuffClick(CCObject *object)
{
}

void MB_LayerWorldBossMain::onDetailCloseClick(CCObject *){
    
    if(m_pBuffer != NULL)
    {
        this->removeChildByTag(BUFF_DISABLE_TOUCH_LAYER);
        m_pBuffer->removeFromParentAndCleanup(true);
        m_pBuffer = NULL;
    }
}
void MB_LayerWorldBossMain::onSoSDetailCloseClick(CCObject *)
{
}
void MB_LayerWorldBossMain::onCloseClick(CCObject *object){
    if (isToHome) {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }else
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
    }
}
void MB_LayerWorldBossMain::onReportClick(CCObject *object)
{
    MB_Message::sharedMB_Message()->showMessage("获取战报",30);
    sendworldboss_cur_info();
}
bool MB_LayerWorldBossMain::sendworldboss_cur_info(){
    
    SOCKET_REQUEST_START(CS_NANM_CUR_INFO);
    SOCKET_REQUEST_END(SC_NANM_CUR_INFO, MB_LayerWorldBossMain::onMsgRecv);
    return true;
}
void MB_LayerWorldBossMain::onPreReportClick(CCObject *object){
    
    MB_LOG("PreReportClick");
    MB_Message::sharedMB_Message()->showMessage("获取前回战报",30);
    sendworldboss_last_info();
    
}
bool MB_LayerWorldBossMain::sendworldboss_last_info(){
    
    SOCKET_REQUEST_START(CS_NANM_LAST_INFO);
    packet->writeU32(m_pData->getCurSaveInfoID());
    SOCKET_REQUEST_END(SC_NANM_LAST_INFO_FAIL, MB_LayerWorldBossMain:onMsgRecv);
    
    return true;
}
bool MB_LayerWorldBossMain::recvworldboss_last_info_fail(MB_MsgBuffer* recvPacket){
    
    MB_Message::removeALLMessage();
    MB_NodeRocketTeamPreReport *preReport =  MB_NodeRocketTeamPreReport::create(0);
    this->pushWindow(preReport);
    return  true;
}
bool MB_LayerWorldBossMain::recvworldboss_last_info_win(MB_MsgBuffer *recvPacket){
    
    MB_Message::removeALLMessage();
    MB_NodeRocketTeamPreReport *preReport =  MB_NodeRocketTeamPreReport::create(0);
    this->pushWindow(preReport);
    
    return  true;
}
bool MB_LayerWorldBossMain::recvworldboss_last_info_ignore(MB_MsgBuffer *recvPacket){
    
    MB_Message::removeALLMessage();
    MB_NodeRocketTeamPreReport *preReport =  MB_NodeRocketTeamPreReport::create(0);
    this->pushWindow(preReport);
    
    return  true;
}
//void MB_LayerWorldBossMain::onOfflineClick(CCObject *object){
//
//    /*
//     if( m_pData->getIsOfflinePlay() == true)
//     {
//     m_pDoneYuanJun->setVisible(true);
//     m_pWillDoYuanJun->setVisible(false);
//     }
//     else
//     {
//     m_pDoneYuanJun->setVisible(false);
//     m_pWillDoYuanJun->setVisible(true);
//     }*/
//    MB_Message::sharedMB_Message()->showMessage("等待相应",30);
//    SOCKET_REQUEST_START(CS_NANM_OFFLINE_PLAY);
//    packet->writeU8( m_pData->getIsOfflinePlay() == false );
//    SOCKET_REQUEST_END(SC_NANM_OFFLINE_PLAY,MB_LayerWorldBossMain::onMsgRecv);
//}
void MB_LayerWorldBossMain::onAutoBattleClick(CCObject *object)
{
    if( isAutoPlay == false )
    {
        m_pAutoPreFrame = ((CCSprite *)m_pAutoFight->getNormalImage())->displayFrame();
        m_pAutoPreFrame->retain();
        ((CCSprite *)m_pAutoFight->getNormalImage())->setDisplayFrame(((CCSprite *)m_pAutoFight->getSelectedImage())->displayFrame());
        isAutoPlay = true;
//        if(m_pData->getRebornTime() - MB_ClientSocket::getInstance()->getServerTime() <= 0)
//        {
//            MB_Message::sharedMB_Message()->showMessage(15);
//            this->sendworldboss_fight();
//        }
        tickReborn(0);
    }
    else
    {
        ((CCSprite *)m_pAutoFight->getNormalImage())->setDisplayFrame(m_pAutoPreFrame);
        m_pAutoPreFrame->release();
        m_pAutoPreFrame = NULL;
        isAutoPlay = false;
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("autoworldboss",isAutoPlay);
    
}
void MB_LayerWorldBossMain::onBattleClick(CCObject *object)
{
    sendworldboss_fight();
}
bool MB_LayerWorldBossMain::sendworldboss_fight()
{
    SOCKET_MSG_REGIST(SC_NANM_FIGHT, MB_LayerWorldBossMain);
    
    MB_Message::sharedMB_Message()->showMessage(15);
    SOCKET_REQUEST_START(CS_NANM_FIGHT);
    SOCKET_REQUEST_END(SC_NANM_FIGHT,MB_EventMgr::onMsgRecv);
    
    return true;
}
void MB_LayerWorldBossMain::onRelifeClick(CCObject *object){
    
    MB_Message::sharedMB_Message()->showMessage("",30);
    SOCKET_MSG_REGIST(SC_NANM_FIGHT, MB_LayerWorldBossMain);
    SOCKET_REQUEST_START(CS_NANM_REBORN);
    SOCKET_REQUEST_END(SC_NANM_REBORN,MB_LayerWorldBossMain::onMsgRecv);
    
}
void MB_LayerWorldBossMain::tickCountToStart(float dt){
    
    int timetick = m_pData->getBeginTime() - MB_ClientSocket::getInstance()->getServerTime();
    
    if (timetick < 0) {
        
        timetick = 0;
    }
    char databuf[40];
    sprintf(databuf, "%02d:%02d:%02d",timetick/3600,timetick%3600/60,timetick%3600%60);
    m_pTimeStart->setString(databuf);
    if (timetick <= 0) {
        
        MB_Message::sharedMB_Message()->showMessage("准备开启火箭队",30);
        sendworldboss_open(NULL);
        unschedule(schedule_selector(MB_LayerWorldBossMain::tickCountToStart));
        
    }
    
}
void MB_LayerWorldBossMain::tickReborn(float dt){
    
    int timetick = m_pData->getRebornTime() - MB_ClientSocket::getInstance()->getServerTime();
    if (timetick < 0) {
        
        timetick = 0;
    }
    char databuf[40];
    sprintf(databuf, "%02d:%02d:%02d",timetick/3600,timetick%3600/60,timetick%3600%60);
    m_pAutoRellifeTime->setString(databuf);
    if (timetick <= 0) {
        
        m_pNodeLife->setVisible(true);
        m_pNodeDie->setVisible(false);
        m_pNodeAddBuff->setVisible(true);
        m_pData->setRebornTime(0);
        if(isAutoPlay){
            
            MB_Message::sharedMB_Message()->showMessage("决斗",30);
            this->sendworldboss_fight();
        }
        unschedule(schedule_selector(MB_LayerWorldBossMain::tickReborn));
    }
}
bool  MB_LayerWorldBossMain::sendworldboss_open(CCObject *){
    
    SOCKET_MSG_REGIST(SC_NANM_OPEN,MB_LayerWorldBossMain);
    SOCKET_MSG_REGIST(SC_NANM_INIT_STATE, MB_LayerWorldBossMain);
    MB_EventMgr::getInstence()->sendworldboss_open();
    return true;
}
void MB_LayerWorldBossMain::onEnter(){
    
    MB_ResWindow::onEnter();
    isInGame = true;
    if (m_pDamageZone)
    {
        m_pDamageZone->removeAllChildren();
    }
    if (m_bFirstEnter)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        sendworldboss_open(NULL);
        m_bFirstEnter = false;
    }
}

void MB_LayerWorldBossMain::onExit()
{
    m_pAniamtion->setAnimationCompletedCallback(NULL, NULL);
    CCFunctionWnd::onExit();
}

void MB_LayerWorldBossMain::onEnterTransitionDidFinish()
{
    CCFunctionWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerWorldBossMain::onRuleClicked(CCObject* pSender)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionResearchInstitute);
    if (pWnd)
    {
        pushWindow(pWnd);
    }
}
