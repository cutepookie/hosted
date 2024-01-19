

#include "MB_SceneGame.h"
//#include "MB_SceneLogin.h"
#include "MB_LayerResultPVPRanking.h"
#include "MB_LayerResultBoss.h"
#include "MB_LayerResultRepLay.h"
#include "MB_Championship.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionMgr.h"
#include "MB_RuleFightInterface.h"
#include "MB_LayerResultPve.h"
#include "MB_MailData.h"
#include "MB_LayerResultChangeCoin.h"
#include "MB_LayerTrainerTroveResult.h"
#include "MB_LayerFriendFightResult.h"
#include "MB_NodeShow.h"
#define STATE_DEAD   0x10
#define ENTER_DT 0.2f
#define ACTION_REBORN 9
#define BLOODBARSTART (16.2f)
#define BLOODBAREND (33.8f)
//#define PROGRESSSPEED (0.2f)
#define PROGRESS_JIAN_SPEED (0.02f)
#define ALLDEAYPERFRAME 15
#define TESHUROTATION 25
#define PERSPEED 5
#define TOADDSTRSIZE 22
#define TOADDSTR2SIZE 6
#define WORLDBOSSTRUEBARNUM 4
#define WORLDBOSSBARNUM 4
#define WORLDBOSSPERSPEED .5f
MB_SceneGame::MB_SceneGame():m_pSc_fightdata(NULL),m_pReward(NULL){
    m_pBossLevel = NULL;
    isRunScaleMoveNode = false;
    PROGRESSSPEED_enemy = 0;
    m_nOurAllHpNum = 0;
    m_nOurNowHpNum= 0;
    m_nEnemyAllHpNum= 0;
    m_nEnemyNowHpNum= 0;
    deayPerFrame_our = -999;
    deayPerFrame_enemy = -999;
    lastPetPos = 999;
    m_nWorldBossBarNum = 100/WORLDBOSSBARNUM;
    for (int i = 0; i< CARD_IN_GAME ; i++) {
        
        m_pOur[i] = NULL;
        m_pEnemy[i] = NULL;
        m_pTempode[i]=NULL;
        m_pTempode[i+6]=NULL;
    }
    m_pSpeed = 1.0;
    m_pPassName = NULL;
    m_pTitleName1 = NULL;
    m_pTitleName2 = NULL;
    m_pNowEnemyHP = NULL;
    tempZhongZu = 1;
    m_pStartBg = NULL;
    m_bFirstFailed = false;
    m_pNodeJump = NULL;
    m_pNodeOtherRole = NULL;
    m_pNodeRole = NULL;
    m_pOtherRoleName = NULL;
    m_pOtherRoleLevel = NULL;
    m_pRoleName = NULL;
    m_pRoleLevel = NULL;
    indexEnterOur = 0;
    loadTimeXml();
    m_pMenu = NULL;
    m_pAnimationMgr = NULL;
    m_nIsDelayOver = false;
    m_pResultPVPRanking = NULL;
    m_nPreHp = 0;
    m_pReplayCallBack = NULL;
    m_pReplayCallBackTarget = NULL;
    m_nReplayType = -1;
    m_pBattleBg = NULL;
    m_pMenuSpeedUp = NULL;
    m_pAddRewardCoin = 0;
    m_pNodeTop = NULL;
    m_pResultdata = NULL;
    m_pEnemyNode = NULL;
    
    m_ourBar1 = NULL;
    m_ourBar2 = NULL;
    m_enemyBar1 = NULL;
    m_enemyBar2 = NULL;
    m_pAllOurHP = NULL;
    m_pAllEnemyHP = NULL;
    m_pDiZuo = NULL;
}

void MB_SceneGame::releaseFightData(recvfight* pData)
{
    for (p_action *action = pData->actionList; action != NULL;  ) {
        
        p_action *nowaction=action;
        action=action->next;
        free(nowaction);
    }
    
    for (p_fighter *fighter =  pData->fighterList; fighter != NULL;  ) {
        
        p_fighter *nowfighter = fighter;
        fighter = fighter->next;
        free(nowfighter );
        
    }
    pData->fighterList = NULL;
    pData->actionList = NULL;
    
    free( pData);
    pData = NULL;
}
MB_SceneGame::~MB_SceneGame(){
    global_sceneGame = NULL;
    if (m_pSc_fightdata)
    {
        releaseFightData(m_pSc_fightdata);
        m_pSc_fightdata = NULL;
    }
    
    if ( m_pReward != NULL ) {
        
        for (p_petExp* exp = m_pReward->petExp ; exp!=NULL;) {
            
            p_petExp *temp = exp;
            exp = exp->next;
            free (temp);
        }
        m_pReward->petExp = NULL;
        for (p_item_view *item=  m_pReward->item; item != NULL;  ) {
            
            p_item_view *nowitem = item;
            item = item->next;
            free(nowitem);
            
        }
        m_pReward->item = NULL;
        free( m_pReward);
    }
    
    for (int i = 0; i < CARD_IN_GAME ; i++) {
        
        if( m_pOur[i] != NULL){
            
            m_pOur[i] = NULL;
        }
        if(m_pEnemy[i]!=NULL){
            
            m_pEnemy[i] = NULL;
        }
        CC_SAFE_RELEASE(m_pTempode[i]);
        CC_SAFE_RELEASE(m_pTempode[i+6]);
    }
    
    CC_SAFE_RELEASE(m_pBossLevel);
    CC_SAFE_RELEASE(m_pPassName);
    CC_SAFE_RELEASE(m_pTitleName1);
    CC_SAFE_RELEASE(m_pTitleName2);
    CC_SAFE_RELEASE(m_pAnimationMgr);
    CC_SAFE_RELEASE(m_pNodeJump);
    CC_SAFE_RELEASE(m_pNodeOtherRole);
    CC_SAFE_RELEASE(m_pNodeRole);
    CC_SAFE_RELEASE(m_pOtherRoleName);
    CC_SAFE_RELEASE(m_pOtherRoleLevel);
    CC_SAFE_RELEASE(m_pRoleName);
    CC_SAFE_RELEASE(m_pRoleLevel);
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE_NULL(m_pBattleBg);
    CC_SAFE_RELEASE_NULL(m_pMenuSpeedUp);
    CC_SAFE_RELEASE_NULL(m_pNodeTop);
    CC_SAFE_RELEASE_NULL(m_pEnemyNode);
    CC_SAFE_RELEASE_NULL(m_pDiZuo);
    CC_SAFE_RELEASE_NULL(m_pStartBg);
    CC_SAFE_RELEASE_NULL(m_pNowEnemyHP);
    
    if(m_pResultPVPRanking != NULL){
        
        CC_SAFE_DELETE(m_pResultPVPRanking);
    }
    CC_SAFE_RELEASE(m_pResultdata);
    m_pReplayCallBack = NULL;
    m_pReplayCallBackTarget = NULL;
    
    
        CC_SAFE_RELEASE_NULL(m_ourBar1);
        CC_SAFE_RELEASE_NULL(m_ourBar2);
        CC_SAFE_RELEASE_NULL(m_enemyBar1);
        CC_SAFE_RELEASE_NULL(m_enemyBar2);
        CC_SAFE_RELEASE_NULL(m_pAllOurHP);
        CC_SAFE_RELEASE_NULL(m_pAllEnemyHP);
}

const char* toAddStr[TOADDSTRSIZE] = {"battle2.plist","rage_skill_1_0.plist" ,"rage_skill_1_1.plist","rage_skill_1_2.plist","rage_skill_2_0.plist","rage_skill_2_1.plist","rage_skill_2_2.plist","rage_skill_3_0.plist","rage_skill_3_1.plist","rage_skill_4_0.plist","rage_skill_4_1.plist","rage_skill_5_0.plist","rage_skill_5_1.plist","rage_skill_5_2.plist","absorb.plist" , "beattack_e1.plist", "damageback.plist" ,"dead_e1.plist" ,"miss.plist" , "reel.plist", "revive_e1_0.plist","revive_e1_1.plist",};
const char* toAddStr2[TOADDSTR2SIZE] = {"battle2.plist","rage_skill_5_0.plist","rage_skill_5_1.plist","rage_skill_5_2.plist","beattack_e1.plist","dead_e1.plist" };
void MB_SceneGame::loadDaZhaoRes(float dt)
{
    for (int i = 0; i< TOADDSTRSIZE; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(toAddStr[toAddIndex++]);
    }
    if (m_bIsScaleBoss) {
        initEndWorldBoss();
    }else
    {
        initEnd();
    }
}
void MB_SceneGame::loadDaZhaoResDemo(float dt)
{
    for (int i = 0; i< TOADDSTR2SIZE; i++) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(toAddStr2[toAddIndex++]);
    }
    if (m_bIsScaleBoss) {
        initEndWorldBoss();
    }else
    {
        initEnd();
    }
}
bool MB_SceneGame::init(recvfight *recvfightdata,bool isScaleBoss){
    if(!CCLayer::init()){
        return false;
    }
    m_bIsScaleBoss = isScaleBoss;
    toAddIndex = 0;
    m_pSc_fightdata = recvfightdata;
    //预加载大招
    if (m_bIsDemoFight) {
        m_bIsDemoFight = false;
        scheduleOnce(schedule_selector(MB_SceneGame::loadDaZhaoResDemo),.2f);
    }else
    {
        scheduleOnce(schedule_selector(MB_SceneGame::loadDaZhaoRes),.2f);
    }
    
    global_sceneGame = this;
    isShowJump = false;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    if (m_bIsScaleBoss) {
        m_pLayerShow = ccbReader->readNodeGraphFromFile("res/battle_layer_mainWorldBoss.ccbi",this);
    }else
    {
        m_pLayerShow = ccbReader->readNodeGraphFromFile("res/battle_layer_main.ccbi",this);
    }
    
    this->addChild(m_pLayerShow);
    this->setTag(FIGHTSCENE);
    m_pStartBg->setVisible(true);
    m_pAnimationMgr = ccbReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimationMgr);
    ccbReader->release();
    m_pNodeJump->setVisible(false);
    m_pNodeRole->setVisible(false);
    m_pNodeOtherRole->setVisible(false);
    
    m_pReplayCallBackTarget = m_pSc_fightdata->m_pReplayCallBackTarget;
    m_pReplayCallBack = m_pSc_fightdata->m_pReplayCallBack;
    
    m_bIsover=false;
    m_pActionmove = m_pSc_fightdata->actionList;
    this->loadArmy();
    m_nTimeCount = 0;
    m_nLastTimeStart = 0;
    this->setTouchEnabled(false);
    
    m_pNodeJump->setVisible(false);
    
    
    if (m_pSc_fightdata->hasBoss())
    {
        PlayBackGround(kmBackGround_Battle_Boss);
    }
    else
    {
        PlayBackGround(kmBackGround_Combat);
    }
    return  true;
}

void MB_SceneGame::initEnd()
{
    char strKey[50];
    sprintf(strKey,"speedup%d",MB_RoleData::getInstance()->getUID());
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(strKey) && (MB_RoleData::getInstance()->getVipLevel() >= 2))
    {
        m_pMenuSpeedUp->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
        m_pMenuSpeedUp->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
    }
    
    
    ourProgress1_o = setProgressBar(m_ourBar1,ccp(0.01f,0.5f) ,100);
    ourProgress2_o =setProgressBar(m_ourBar2,ccp(0.01f,0.5f),100);
    m_enemyProgress1_o =setProgressBar(m_enemyBar1,ccp(0.5f,0.99f),100);
    m_enemyProgress2_o =setProgressBar(m_enemyBar2,ccp(0.5f,0.99f),100);
    
    
    ourProgress1 = setProgressBar(m_ourBar1,ccp(0.01f,0.5f));
    ourProgress2 =setProgressBar(m_ourBar2,ccp(0.01f,0.5f));
    m_enemyProgress1 =setProgressBar(m_enemyBar1,ccp(0.5f,0.99f));
    m_enemyProgress2 =setProgressBar(m_enemyBar2,ccp(0.5f,0.99f));
    
    nowOurPer =BLOODBAREND;
    nowEnemyPer =TESHUROTATION+BLOODBAREND;
    
    
    ourProgress1->setPercentage(BLOODBARSTART);
    ourProgress2->setPercentage(BLOODBARSTART);
    m_enemyProgress1->setPercentage(TESHUROTATION+BLOODBARSTART);
    m_enemyProgress2->setPercentage(TESHUROTATION+BLOODBARSTART);
    ourProgress1_o->setPercentage(BLOODBARSTART);
    ourProgress2_o->setPercentage(BLOODBARSTART);
    m_enemyProgress1_o->setPercentage(TESHUROTATION+BLOODBARSTART);
    m_enemyProgress2_o->setPercentage(TESHUROTATION+BLOODBARSTART);
    
    m_pAnimationMgr->runAnimationsForSequenceNamed("ready");
    runAction(CCSequence::create(CCDelayTime::create(.1f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finish3)),NULL));
    for (int i = 0;  i < CARD_IN_GAME; i++) {
        if(m_pEnemy[i] != NULL){
            m_pEnemy[i]->getParent()->setVisible(true);
        }
    }
    runAction(CCSequence::create(CCDelayTime::create(.5f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finish2)),CCDelayTime::create(.7f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finishStartBg)),NULL));
    
    if (m_SceneGameIsSetLevelUI) {
        m_SceneGameIsSetLevelUI = false;
        char strKey[50];
        sprintf(strKey,"%d-%d",m_SceneGameBigLevel,m_SceneGameLittleLevel);
        m_pTitleName1->setString(strKey);
        m_pTitleName2->setString(m_SceneGameLevelName);
        sprintf(strKey,"%d-%d %s",m_SceneGameBigLevel,m_SceneGameLittleLevel,m_SceneGameLevelName);
        m_pPassName->setString(strKey);
    }else
    {
        m_pTitleName1->setVisible(false);
        m_pTitleName2->setVisible(false);
        m_pPassName->getParent()->setVisible(false);
    }
}

void MB_SceneGame::initEndWorldBoss()
{
    m_pNowEnemyHP->setString(CCString::createWithFormat("%d",m_nEnemyNowHpNum )->getCString() );
    m_pAllEnemyHP->setString(CCString::createWithFormat("%d",m_nEnemyAllHpNum )->getCString() );
    
    nowOurPer =BLOODBAREND;
    nowEnemyPer = 100.0f*m_nEnemyNowHpNum/m_nEnemyAllHpNum;
    nowTrueEnemyPer = nowEnemyPer;
    worldBossBarIndex = (int)nowEnemyPer/m_nWorldBossBarNum;
    int tempInt = worldBossBarIndex%WORLDBOSSTRUEBARNUM+1;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
    m_enemyBar1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bg_blood_0%d.png",tempInt)->getCString()));
    if(worldBossBarIndex==0)
    {
        m_enemyBar2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_blood_00.png"));
    }else
    {
        tempInt--;
        tempInt = tempInt==0?WORLDBOSSTRUEBARNUM:tempInt;
        m_enemyBar2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bg_blood_0%d.png",tempInt)->getCString()));
    }
    
    char strKey[50];
    sprintf(strKey,"speedup%d",MB_RoleData::getInstance()->getUID());
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(strKey) && (MB_RoleData::getInstance()->getVipLevel() >= 2))
    {
        m_pMenuSpeedUp->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
        m_pMenuSpeedUp->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
    }
    
    ourProgress1_o = setProgressBar(m_ourBar1,ccp(0.01f,0.5f) ,100);
    ourProgress2_o =setProgressBar(m_ourBar2,ccp(0.01f,0.5f),100);
    
    ourProgress1 = setProgressBar(m_ourBar1,ccp(0.01f,0.5f));
    ourProgress2 =setProgressBar(m_ourBar2,ccp(0.01f,0.5f));

    
    m_enemyProgress1 =setProgressBar(m_enemyBar1,ccp(0,0));
    m_enemyProgress1->setType(kCCProgressTimerTypeBar);
    m_enemyProgress1->setBarChangeRate(ccp(1,0));
    m_enemyProgress1->setPercentage((nowEnemyPer-worldBossBarIndex*m_nWorldBossBarNum)*WORLDBOSSBARNUM);
    
    
    ourProgress1->setPercentage(BLOODBARSTART);
    ourProgress2->setPercentage(BLOODBARSTART);
    ourProgress1_o->setPercentage(BLOODBARSTART);
    ourProgress2_o->setPercentage(BLOODBARSTART);
    
    m_pAnimationMgr->runAnimationsForSequenceNamed("ready");
    runAction(CCSequence::create(CCDelayTime::create(.1f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finish3)),NULL));
    for (int i = 0;  i < CARD_IN_GAME; i++) {
        if(m_pEnemy[i] != NULL){
            m_pEnemy[i]->getParent()->setVisible(true);
        }
    }
    runAction(CCSequence::create(CCDelayTime::create(.5f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finish2)),CCDelayTime::create(.7f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finishStartBg)),NULL));
    
    if (m_SceneGameIsSetLevelUI) {
        m_SceneGameIsSetLevelUI = false;
        char strKey[50];
        sprintf(strKey,"%d-%d",m_SceneGameBigLevel,m_SceneGameLittleLevel);
        m_pTitleName1->setString(strKey);
        m_pTitleName2->setString(m_SceneGameLevelName);
        sprintf(strKey,"%d-%d %s",m_SceneGameBigLevel,m_SceneGameLittleLevel,m_SceneGameLevelName);
        m_pPassName->setString(strKey);
    }else
    {
        m_pTitleName1->setVisible(false);
        m_pTitleName2->setVisible(false);
        m_pPassName->getParent()->setVisible(false);
    }
    sprintf(strKey,"Lv.%d",((MB_EventData* )MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(0))->getbossLevel());
    m_pBossLevel->setString(strKey);
}

void MB_SceneGame::finish3()
{
    dizuoLittleP = m_pDiZuo->getPosition();
    dizuoLittleSX = m_pDiZuo->getScaleX();
    dizuoLittleSY = m_pDiZuo->getScaleY();
    
    EnemyNodeLittleP = m_pEnemyNode->getPosition();
    EnemyNodeLittleSX = m_pEnemyNode->getScaleX();
    EnemyNodeLittleSY = m_pEnemyNode->getScaleY();
}

void  MB_SceneGame::finishProgress()
{
    m_pStartBg->removeFromParent();
    if (m_bIsScaleBoss) {
        schedule(schedule_selector(MB_SceneGame::updateProgressWorldBoss));
    }else
    {
        schedule(schedule_selector(MB_SceneGame::updateProgress));
    }
    showStart();
}
void MB_SceneGame::tickInEnter(float dt){
    for (int i = indexEnterOur;  i < CARD_IN_GAME; i++) {
        
        if(m_pOur[i] != NULL){
            m_pOur[i]->getParent()->setVisible(true);
            m_pOur[i]->callAnimationByName("enter");
            indexEnterOur ++;
            break;
        }
        indexEnterOur ++;
        
    }

    if(indexEnterOur >= CARD_IN_GAME){
        unschedule(schedule_selector(MB_SceneGame::tickInEnter));
    }
    
}
void MB_SceneGame::finish2()
{
    schedule(schedule_selector(MB_SceneGame::tickInEnter),ENTER_DT);
}
void MB_SceneGame::finishStartBg()
{
    float tempTime = .5f;
    ourProgress1->runAction(CCSequence::create(CCProgressTo::create(tempTime, nowOurPer),CCDelayTime::create(.5f+5/30.0f), CCCallFunc::create(this, callfunc_selector(MB_SceneGame::finishProgress)),NULL));
    ourProgress2->runAction( CCProgressTo::create(tempTime, nowOurPer));
    ourProgress1_o->runAction(CCProgressTo::create(tempTime, nowOurPer));
    ourProgress2_o->runAction(CCProgressTo::create(tempTime, nowOurPer));
    if (!m_bIsScaleBoss) {
        m_enemyProgress1->runAction(CCProgressTo::create(tempTime, nowEnemyPer));
        m_enemyProgress2->runAction(CCProgressTo::create(tempTime, nowEnemyPer));
        m_enemyProgress1_o->runAction(CCProgressTo::create(tempTime, nowEnemyPer));
        m_enemyProgress2_o->runAction(CCProgressTo::create(tempTime, nowEnemyPer));
    }
}
void MB_SceneGame::showStart(){
    m_bIsover=false;
    if( isShowJump == false ){
        
        isShowJump = true;
        
        if(m_pSc_fightdata->type == kFightResultTypePVE){
            
            if(m_pReward->preStar >= 0){
                
                m_pNodeJump->setVisible(true);
            }
            
        }else{
            
            m_pNodeJump->setVisible(true);
            
        }
    }
    if (m_pActionmove && (m_pActionmove->action->actionID >100
                          ||  m_pActionmove->action->actionID == 0) ) {
        
        this->LoadOneFight(m_pActionmove);
        this->runAction(CCSequence::create(
                                           CCDelayTime::create(m_nLastTimeStart),
                                           CCCallFunc::create(this, callfunc_selector(MB_SceneGame::showStart)),
                                           NULL));
        this->schedule(schedule_selector(MB_SceneGame::tickAniamtion));
    }else {
        
        
        if(m_pActionmove == NULL){
            
            unschedule(schedule_selector(MB_SceneGame::tickAniamtion));
            this->onMainOver(NULL);
            return;
        }
        
        m_nLastTimeStart = 0;
        
        
        
        dizuoBigP = m_pDiZuo->getPosition();
        dizuoBigSX = m_pDiZuo->getScaleX();
        dizuoBigSY = m_pDiZuo->getScaleY();
        
        EnemyNodeBigP = m_pEnemyNode->getPosition();
        EnemyNodeBigSX = m_pEnemyNode->getScaleX();
        EnemyNodeBigSY = m_pEnemyNode->getScaleY();
        m_pAnimationMgr->runAnimationsForSequenceNamed("start");
        m_pAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_SceneGame::startAnimation));
        
    }
    
}
void MB_SceneGame ::startAnimation(){
    
    m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    
    
    for (int i = 0;  i < CARD_IN_GAME; i++) {
        
        if(m_pOur[i] != NULL){
            
            m_pOur[i]->setDetailShow(false);
        }
        
        
    }
    for (int i = 0;  i < CARD_IN_GAME; i++) {
        
        if(m_pEnemy[i] != NULL){
            
            m_pEnemy[i]->setDetailShow(false);
        }
        
    }
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(MB_SceneGame::tickAniamtion));
    
}
cocos2d::SEL_MenuHandler MB_SceneGame ::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "goMainMenu", MB_SceneGame::onMainMenuClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSpeedUpClick", MB_SceneGame::onSpeedUpClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_SceneGame ::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
    
}
bool MB_SceneGame :: onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    for ( int i = 0; i < 6 ; i++) {
        
        char str[3] = "a1";
        str[1] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str ,CCNode *, m_pTempode[i]);
        str[0] = 'b';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, str ,CCNode *, m_pTempode[i+6]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEnemyNode", CCNode *, m_pEnemyNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeJump",CCNode *,m_pNodeJump);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeOtherRole",CCNode *,m_pNodeOtherRole);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRole",CCNode *,m_pNodeRole);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pOtherRoleName",CCLabelTTF *,m_pOtherRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pOtherRoleLevel",CCLabelTTF *,m_pOtherRoleLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleName",CCLabelTTF *,m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleLevel",CCLabelTTF *,m_pRoleLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenu", CCMenu *, m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "battle_bg", CCSprite *,m_pBattleBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuSpeedUp", CCMenuItemImage *,m_pMenuSpeedUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDiZuo", CCSprite *,m_pDiZuo);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPassName", CCLabelTTF *,m_pPassName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_ourBar1", CCSprite *,m_ourBar1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_ourBar2", CCSprite *,m_ourBar2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_enemyBar1", CCSprite *,m_enemyBar1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_enemyBar2", CCSprite *,m_enemyBar2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAllOurHP", CCLabelBMFont *,m_pAllOurHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAllEnemyHP", CCLabelBMFont *,m_pAllEnemyHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pStartBg", CCLayerColor *,m_pStartBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTitleName1", CCLabelTTF *,m_pTitleName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTitleName2", CCLabelTTF *,m_pTitleName2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTop", CCNode*, m_pNodeTop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNowEnemyHP", CCLabelBMFont *,m_pNowEnemyHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBossLevel", CCLabelBMFont *,m_pBossLevel);
    
    return false;
}

void MB_SceneGame::setBattleBackground(const char* pFile)
{
    NSGameHelper::setSpriteFrame(m_pBattleBg, pFile);
}
//初始化卡牌
void MB_SceneGame ::loadArmy(){
    
    for (int i=0; i < CARD_IN_GAME ; i++) {
        m_pOur[i] = NULL;
        m_pEnemy[i] = NULL;
    }
    
    m_nCenterOur = (m_pTempode[1]->getPositionY()+m_pTempode[4]->getPositionY())/2.0f;
    CCPoint pos = ccp(0,m_nCenterOur);
    pos = m_pTempode[1]->getParent()->convertToWorldSpace(pos);
    this->convertToNodeSpace(pos);
    m_nCenterOur = pos.y;
    
    m_nCenterEnenmy = (m_pTempode[7]->getPositionY()+m_pTempode[10]->getPositionY())/2.0f;
    
    pos = ccp(0,  m_nCenterEnenmy);
    pos = m_pTempode[7]->getParent()->convertToWorldSpace(pos);
    this->convertToNodeSpace(pos);
    m_nCenterEnenmy = pos.y;
    
    if(m_bIsScaleBoss)
    {
        for (p_fighter *fighter = m_pSc_fightdata->fighterList ; fighter != NULL ; fighter=fighter->next ) {
            
            if ( fighter->petPos >0 ) {//添加友方卡牌
                int pos= abs(fighter->petPos)-1;
                m_pOur[pos] = MB_NodeShow::createMB_NodeShow(fighter,0,this);
                m_pTempode[pos]->addChild(m_pOur[pos],2);
                m_pTempode[pos]->setVisible(false);
                m_pOur[pos]->setDetailShow(true);
                m_pOur[pos]->setWorldPlace(m_pOur[pos]->getCard()->getParent()->convertToWorldSpace(m_pOur[pos]->getCard()->getPosition()));
                
                m_nOurAllHpNum+=fighter->petHp;
                ourPosNowHp.insert(pair<int, uint64_t>(pos, fighter->petHp));
                ourPosAllHp.insert(pair<int, uint64_t>(pos, fighter->petHpMax));
            }else {//添加敌方卡牌
                
                int pos= abs(fighter->petPos)-1;
                m_pEnemy[pos] = MB_NodeShow::createMB_NodeShow(fighter,1 ,this,m_bIsScaleBoss);
                m_pTempode[pos+6]->addChild( m_pEnemy[pos],2);
                m_pTempode[pos+6]->setVisible(false);
                m_pEnemy[pos]->setWorldPlace(m_pEnemy[pos]->getCard()->getParent()->convertToWorldSpace(m_pEnemy[pos]->getCard()->getPosition()));
                if(m_pSc_fightdata->type == kFightResultTypeRocketTeam || m_pSc_fightdata->type == kFightResultTypeNanm || m_pSc_fightdata->type == kFightResultTypeKing){
                    m_nPreHp = m_nPreHp + fighter->petHp;
                }
                m_pEnemy[pos]->setDetailShow(true);
                m_nEnemyNowHpNum+=fighter->petHp;
                m_nEnemyAllHpNum+=fighter->petHpMax;
                enemyPosNowHp.insert(pair<int, uint64_t>(pos, fighter->petHp));
                enemyPosAllHp.insert(pair<int, uint64_t>(pos, fighter->petHpMax));
            }
            
        }
        m_nOurNowHpNum = m_nOurAllHpNum;
    }else
    {
        for (p_fighter *fighter = m_pSc_fightdata->fighterList ; fighter != NULL ; fighter=fighter->next ) {
            
            if ( fighter->petPos >0 ) {//添加友方卡牌
                int pos= abs(fighter->petPos)-1;
                m_pOur[pos] = MB_NodeShow::createMB_NodeShow(fighter,0,this);
                m_pTempode[pos]->addChild(m_pOur[pos],2);
                m_pTempode[pos]->setVisible(false);
                m_pOur[pos]->setDetailShow(true);
                m_pOur[pos]->setWorldPlace(m_pOur[pos]->getCard()->getParent()->convertToWorldSpace(m_pOur[pos]->getCard()->getPosition()));
                
                m_nOurAllHpNum+=fighter->petHp;
                ourPosNowHp.insert(pair<int, uint64_t>(pos, fighter->petHp));
                ourPosAllHp.insert(pair<int, uint64_t>(pos, fighter->petHpMax));
            }else {//添加敌方卡牌
                
                int pos= abs(fighter->petPos)-1;
                m_pEnemy[pos] = MB_NodeShow::createMB_NodeShow(fighter,1 ,this);
                m_pTempode[pos+6]->addChild( m_pEnemy[pos],2);
                m_pTempode[pos+6]->setVisible(false);
                m_pEnemy[pos]->setWorldPlace(m_pEnemy[pos]->getCard()->getParent()->convertToWorldSpace(m_pEnemy[pos]->getCard()->getPosition()));
                if(m_pSc_fightdata->type == kFightResultTypeRocketTeam || m_pSc_fightdata->type == kFightResultTypeNanm || m_pSc_fightdata->type == kFightResultTypeKing){
                    m_nPreHp = m_nPreHp + fighter->petHp;
                }
                m_pEnemy[pos]->setDetailShow(true);
                m_nEnemyAllHpNum+=fighter->petHp;
                enemyPosNowHp.insert(pair<int, uint64_t>(pos, fighter->petHp));
                enemyPosAllHp.insert(pair<int, uint64_t>(pos, fighter->petHpMax));
            }
            
        }
        m_nOurNowHpNum = m_nOurAllHpNum;
        m_nEnemyNowHpNum = m_nEnemyAllHpNum;
    }
}
CCPoint  MB_SceneGame ::getCenterByType(int type){
    
    CCPoint poss = ccp(CCDirector::sharedDirector()->getWinSize().width/2.0f,type == 0 ?m_nCenterOur :m_nCenterEnenmy);
    return poss;
}


//读取攻擊動画
MB_SceneGame * MB_SceneGame::create(recvfight  *recvfightdata,bool isScaleBoss){
    
    MB_SceneGame *node =new MB_SceneGame();
    
    if( node && node->init(recvfightdata,isScaleBoss) ){
        
        node ->autorelease();
        return  node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;
    
}

void MB_SceneGame::onEnter()
{
    CCLayer::onEnter();
}
void MB_SceneGame::onExit()
{    
    m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
    m_pScheduler->setTimeScale(1.0);
    CCLayer::onExit();
}



CCScene *MB_SceneGame::scene(recvfight *recvfightdata,int rewardcoin,int rewardreputation,bool isScaleBoss)
{
    CCScene *scene = CCScene::create();
    MB_SceneGame  *node = MB_SceneGame::create(recvfightdata,isScaleBoss);
    scene->addChild(node);
    node->setReward(rewardcoin, rewardreputation);
    return  scene;
}
//执行攻擊動画
CCScene *  MB_SceneGame::scene(recvfight *recvfightdata,int rewardcoin,int rewardreputation){
    
    CCScene *scene = CCScene::create();
    MB_SceneGame  *node = MB_SceneGame::create(recvfightdata);
    scene->addChild(node);
    node->setReward(rewardcoin, rewardreputation);
    return  scene;
}
void MB_SceneGame::setReward(int rewardcoin,int rewardreputation){
    
    m_pRewardCoin = rewardcoin;
    m_pRewardReputation = rewardreputation;
}
CCScene *  MB_SceneGame::scene(recvfight *recvfightdata,p_reward *reward,uint16_t doungeonLevel,const char* pBg,bool bFirstFailed){
    
    CCScene *scene = CCScene::create();
    MB_SceneGame  *node = MB_SceneGame::create(recvfightdata);
    node->setReward(reward);
    if (pBg)
    {
        node->setBattleBackground(pBg);
    }
    node->setFirstFailed(bFirstFailed);
    scene->addChild(node);
    
    return  scene;
}
CCScene* MB_SceneGame::scene(recvfight* fightData,const char *attackName, const char *defenseName,uint64_t replayId,uint8_t table,uint8_t type){
    
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightData);
    node->setResult(attackName,defenseName);
    node->setReplayID(replayId);
    node->setTable(table);
    node->setReplayType(type);
    scene->addChild(node);
    return scene;
}

CCScene* MB_SceneGame::sceneChangeCoin(recvfight* fightdata,int rewardcoin,int addrewardcoin,const char* pBg)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightdata);
    node->m_pRewardCoin = rewardcoin;
    node->m_pAddRewardCoin = addrewardcoin;
    scene->addChild(node);
    if (pBg)
    {
        node->setBattleBackground(pBg);
    }
    return scene;
}

CCScene *MB_SceneGame::sceneWithReward(recvfight* fightdata,SResultData* pResultData)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightdata);
    node->m_pResultdata = pResultData;
    CC_SAFE_RETAIN(node->m_pResultdata);
    scene->addChild(node);
    node->setResult(pResultData->attackName.c_str(),pResultData->defenseName.c_str());
    if (!pResultData->pBg.empty())
    {
        node->setBattleBackground(pResultData->pBg.c_str());
    }
    return scene;
}

CCScene* MB_SceneGame::scene(recvfight* fightData,const char *attackName, const char *defenseName,const char* pBg)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightData);
    node->setResult(attackName,defenseName);
    scene->addChild(node);
    if (pBg)node->setBattleBackground(pBg);
    return scene;
}
CCScene* MB_SceneGame::scene(recvfight *fightData, sTreasureRobResult *resultData)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightData);
    node->setResult(resultData);
    scene->addChild(node);
    return scene;
}
CCScene* MB_SceneGame::scene(recvfight *recvfightdata)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(recvfightdata);
    scene->addChild(node);
    return scene;
}
CCScene* MB_SceneGame::scene(recvfight *fightData, p_result_ranking *resultData,const char* pBg)
{
    CCScene* scene = CCScene::create();
    MB_SceneGame* node = MB_SceneGame::create(fightData);
    node->setResult(resultData);
    scene->addChild(node);
    if (pBg)
    {
        node->setBattleBackground(pBg);
    }
    return scene;
}

void MB_SceneGame::setResult(p_result_ranking* resultData)
{
    m_pResultPVPRanking = resultData;
    m_pNodeOtherRole->setVisible(true);
    m_pNodeRole->setVisible(true);
    
    if(resultData->_dataPVPRank)
    {
        m_pOtherRoleName->setString(resultData->_dataPVPRank->getRoleName());
        m_pRoleName->setString(MB_RoleData::getInstance()->getName());
        char databuf[50];
        sprintf(databuf, "%d",MB_RoleData::getInstance()->getLevel());
        m_pRoleLevel->setString(databuf);
        
        sprintf(databuf, "%d",m_pResultPVPRanking->_dataPVPRank->getRoleLevel());
        m_pOtherRoleLevel->setString(databuf);
        if(m_pResultPVPRanking->_dataPVPRank->getRoleLevel() == 0){
            
            m_pOtherRoleLevel->setVisible(false);
        }
    }
}
void MB_SceneGame::setResult(const char *attackName, const char *defenceName){
    
    m_pNodeOtherRole->setVisible(true);
    m_pNodeRole->setVisible(true);
    m_pOtherRoleName->setString(attackName);
    m_pRoleName->setString(defenceName);
    m_pRoleLevel->setVisible(false);
    m_pOtherRoleLevel->setVisible(false);
}
const char * MB_SceneGame::getAttackName(){
    
    return  m_pOtherRoleName->getString();
}
const char * MB_SceneGame::getDefenceName(){
    
    return  m_pRoleName->getString();
    
}
void MB_SceneGame::setResult(sTreasureRobResult* resultData)
{
    m_TreasureRobData.isSuccess  = resultData->isSuccess;
    m_TreasureRobData.roleName   = resultData->roleName;
    m_TreasureRobData.itemID     = resultData->itemID;
    m_TreasureRobData.needItemID = resultData->needItemID;
}

void MB_SceneGame::setReward(p_reward *reward){
    
    this->m_pReward = reward;
}
MB_NodeShow * MB_SceneGame::getActorByindexAndType(int index,int type){
    
    if(type > 0){
        
        return m_pOur[index];
        
    }else {
        
        return m_pEnemy[index];
    }
    
}
void MB_SceneGame::actionAddDelayTime(float delay)
{
    m_nLastTimeStart += delay;
}
void MB_SceneGame::tickAniamtion(float dt){
    
    if (m_actionVector.size()>0) {
        return;
    }
    if (m_nTimeCount > m_nLastTimeStart)
    {
        
        if(m_pActionmove == NULL){
            
            unschedule(schedule_selector(MB_SceneGame::tickAniamtion));
            this->onMainOver(NULL);
            
            return;
        }
        
        this->LoadOneFight(m_pActionmove);
        m_nTimeCount = 0;
        
    }else {
        
        m_nTimeCount += dt;
    }
    
}
#include "MB_SynopsisConfig.h"
#include "MB_LayerStory.h"

void MB_SceneGame::onPlotPlayComplate(CCObject* pSender)
{
    //    if (m_pActionmove==NULL)
    //    {
    //        unscheduleAllSelectors();
    //        CCScene* pScene = MB_SceneLoading::scene();
    //        CCDirector::sharedDirector()->replaceScene(pScene);
    //        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    //        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    //        return ;
    //    }
    m_nLastTimeStart = 0;
}
//播放一次攻擊
void MB_SceneGame::LoadOneFight(p_action * oneFight){
    //吓一条動作類型一样就同時播。
    if(m_pActionmove->next ){
        if (m_pActionmove->next->action->actionID<100)
        {
            if(isRunScaleMoveNode)
            {
                isRunScaleMoveNode = false;
                m_pEnemyNode->runAction(CCEaseExponentialOut::create(CCScaleTo::create(15.0f/30, EnemyNodeBigSX,EnemyNodeBigSY)));
                m_pDiZuo->runAction(CCEaseExponentialOut::create(CCScaleTo::create(15.0f/30, dizuoBigSX,dizuoBigSY)));
            }
           
            m_nLastTimeStart = timePos[m_pActionmove->action->actionType ][m_pActionmove->next->action->actionType];
            
          
            if(m_pEnemyNode->getScaleX()<1)
            {
                if ((m_pActionmove->action->actionType==5||m_pActionmove->action->actionType==8||m_pActionmove->action->actionType==14)&& (m_pActionmove->next->action->actionType!=5&&m_pActionmove->next->action->actionType!=8&&m_pActionmove->next->action->actionType!=14)) {
                    m_nLastTimeStart+=1;
                    runAction(CCSequence::create(CCDelayTime::create(.5f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::delayPalyDaZhao)),NULL ));
                }
            }
            
//            CCLog("m_nLastTimeStart==================%f",m_nLastTimeStart);
//            CCLog("m_pActionmove->petPos=====%d",m_pActionmove->petPos);
//            CCLog("m_pActionmove->action->actionType=====%d",m_pActionmove->action->actionType);
//            CCLog("m_pActionmove->action->actionID=====%d",m_pActionmove->action->actionID);
//            CCLog("m_pActionmove->action->actionName=====%s",m_pActionmove->action->actionName);
//
//            CCLog("m_pActionmove->next->petPos=====%d",m_pActionmove->next->petPos);
//            CCLog("m_pActionmove->next->action->actionType=========%d",m_pActionmove->next->action->actionType);
//            CCLog("m_pActionmove->next->action->actionID=====%d",m_pActionmove->next->action->actionID);
//            CCLog("m_pActionmove->next->action->actionName=====%s",m_pActionmove->next->action->actionName);
//            CCLog("m_nLastTimeStart=========%f",m_nLastTimeStart);
        }
    }
    int pos = -999;
    if(oneFight->petPos>0&&oneFight->targetPos[0]!='\0' ){
        pos = abs(oneFight->targetPos[0])-1;
    }else if(oneFight->petPos<0&&oneFight->targetPos[0]!='\0' ){
        pos =abs(oneFight->petPos)-1;
    }
    if (pos!=-999) {
        float px  = m_pEnemyNode->convertToWorldSpace(m_pTempode[pos+6]->getPosition()).x;
        float tempSpan =CCDirector::sharedDirector()->getWinSize().width/2-px;
        if (fabsf(tempSpan)>10) {
            float timeSpan =.4f;
            float timeSpan2 =oneFight->action->effect->effectStartTime+oneFight->action->effect->effectTime;
            if (timeSpan2<timeSpan) {
                timeSpan = timeSpan2;
            }

            m_actionVector.push_back(oneFight);
            m_pEnemyNode->runAction(CCSequence::create(CCEaseExponentialOut::create(CCMoveBy::create(timeSpan, ccp(tempSpan,0))),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::LoadOneFight2)),NULL));
            m_pDiZuo->runAction(CCEaseExponentialOut::create(CCMoveBy::create(timeSpan, ccp(tempSpan/2,0))));
            m_pTeamPos = pos;
            return;
        }
    }
    
    LoadOneFight2(oneFight);
}
void MB_SceneGame::LoadOneFight2(){
    LoadOneFight2(m_actionVector.back());
    m_actionVector.pop_back();
}
void MB_SceneGame::LoadOneFight2(p_action * oneFight){
    if (oneFight->action->actionID>100)
    {
        MB_LayerStoryPlayer* pLayer = MB_SynopsisConfig::getInstance()->createBattlePlotByID(oneFight->action->actionID);
        if (pLayer)
        {
            m_nLastTimeStart = 99999999;
            pLayer->setTarget(this,menu_selector(MB_SceneGame::onPlotPlayComplate));
            m_pNodeTop->addChild(pLayer,100);
        }
        m_pActionmove = m_pActionmove->next;
        return;
    }
    MB_NodeShow *actCharactor;//攻擊發起者
    actCharactor= getActorByindexAndType(abs(oneFight->petPos)-1, oneFight->petPos );
    if (actCharactor == NULL) {
        
        return;
    }

    if (m_pActionmove == NULL) {
        
        m_nLastTimeStart = 0;
        
    }else{
        m_pActionmove = m_pActionmove->next;
    }
    actCharactor->startAction(oneFight);
}
void MB_SceneGame::onMainOver(CCObject *){
    
    if( m_bIsover ){
        
        return;
    }
    for (; m_pActionmove != NULL; m_pActionmove = m_pActionmove->next ) {
        
        MB_NodeShow *actCharactor;//攻擊發起者
        actCharactor= getActorByindexAndType(abs(m_pActionmove->petPos)-1, m_pActionmove->petPos );
        
        if (actCharactor != NULL) {
            
            actCharactor->changeSp(m_pActionmove->addSp);
            actCharactor->changeBoold(m_pActionmove->addHp);
            uint8_t state = m_pActionmove->state;
            if(( state & STATE_DEAD ) == STATE_DEAD ){
                
                actCharactor->getActionMgr()->setList(m_pActionmove);
                actCharactor->getActionMgr()->goPlay();
                
            }else if(m_pActionmove->action->actionID == 4){
                
                actCharactor->getActionMgr()->setList(m_pActionmove);
                actCharactor->getActionMgr()->goPlay();
                
            }else if(m_pActionmove->action->actionID == ACTION_REBORN){
                
                actCharactor->getActionMgr()->setList(m_pActionmove);
                actCharactor->getActionMgr()->goPlay();
            }
            
        }
    }
    for (int i = 0 ; i < 12; i++) {
        
        MB_NodeShow *actCharactor;//攻擊發起者
        actCharactor= getActorByindexAndType(i%6, i < 6 );
        if (actCharactor == NULL) {
            
            continue;
        }
        if(  i>= 6 && (m_pSc_fightdata->type == kFightResultTypeRocketTeam || m_pSc_fightdata->type == kFightResultTypeNanm || m_pSc_fightdata->type == kFightResultTypeKing)){
            
            m_nPreHp = m_nPreHp - actCharactor->getFighter()->petHp;
        }
        for (CCNode *node =   actCharactor->getParent()->getChildByTag(ANGERY_NODE); node != NULL; node = actCharactor->getParent()->getChildByTag(ANGERY_NODE) ) {
            
            node->removeFromParentAndCleanup(true);
        }
        for (CCNode *node =  actCharactor->getParent()->getChildByTag(REEL_NODE); node != NULL; node = actCharactor->getParent()->getChildByTag(REEL_NODE) ) {
            
            node->removeFromParentAndCleanup(true);
        }
    }
    
    this->stopAllActions();
    this->unscheduleAllSelectors();
    m_pAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
    m_bIsover = true;
    this->setTouchEnabled(false);
    this->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::delayOver)),NULL));
}
void MB_SceneGame::onMainMenuClick(CCObject *object){
    
    if( m_bIsover ){
        
        return;
    }
    
#ifndef DEBUG
    
    int roleLevel =  MB_RoleData::getInstance()->getLevel();
    int vipLevel = MB_RoleData::getInstance()->getVipLevel();
    if(m_pSc_fightdata->type == kFightResultTypePVE){
        
        if(m_pReward->preStar  <= 0 && vipLevel < 2){
            
            MB_Message::sharedMB_Message()->showMessage("当前战况不明, 不能跳过战斗.");
            return;
            
        }
    }
    else if(m_pSc_fightdata->type == kFightResultTypeDemoFight)
    {
        MB_Message::sharedMB_Message()->showMessage("无法跳过该战斗");
        return;
    }
    //int roleLevel =  MB_RoleData::getInstance()->getLevel();
    //int vipLevel = MB_RoleData::getInstance()->getVipLevel();
    if(roleLevel < 15 && vipLevel <2){
        
        MB_Message::sharedMB_Message()->showMessage("玩家15级或VIP2级以上才可以跳过战斗！");
        return;
    }
#endif
    onMainOver(object);
    
}
void MB_SceneGame::delayOver()
{
    m_pScheduler->setTimeScale(1.0);
    if (kFightResultTypeDemoFight != m_pSc_fightdata->type)
    {
        PlayBackGround2(m_pSc_fightdata->issuccess == 1?
                        kmBackGround_CombatWin :
                        kmBackGround_CombatLose);
    }
    else
    {
        MB_Audio::getInstance()->stopBackGround();
    }
    
    if(m_pSc_fightdata->type == kFightResultTypePVE){
        
        MB_LayerResultPve * layer = MB_LayerResultPve::create(m_pSc_fightdata, m_pReward,m_bFirstFailed);
        this->addChild(layer,20);
        this->setTouchEnabled(false);
    }
    else if (m_pSc_fightdata->type == kFightResultTypePVPRanking)
    {
        MB_LayerResultPVPRanking* layer = MB_LayerResultPVPRanking::create(m_pResultPVPRanking);
        this->addChild(layer,20);
    }
    else if(m_pSc_fightdata->type == kFightResultTypeRocketTeam)
    {
        this->setTouchEnabled(false);
        MB_LayerResultBoss * layer = MB_LayerResultBoss::create(m_pRewardCoin, m_pRewardReputation,m_pSc_fightdata->issuccess,m_nPreHp,kFightResultTypeRocketTeam);
        this->addChild( layer,20);
    }
    else if(m_pSc_fightdata->type == kFightResultTypeNanm)
    {
        this->setTouchEnabled(false);
        MB_LayerResultBoss * layer = MB_LayerResultBoss::create(m_pRewardCoin, m_pRewardReputation,m_pSc_fightdata->issuccess,m_nPreHp,kFightResultTypeNanm);
        this->addChild( layer,20);
    }
    else  if(m_pSc_fightdata->type == kFightResultTypeHuRong){
        
        this->setTouchEnabled(false);
        this->addChild(MB_LayerResultChungGuan::create(m_pSc_fightdata, m_pReward),20);
        
    }else if(kFightResultTypeReplay == m_pSc_fightdata->type)
    {
        this->setTouchEnabled(false);
        this->addChild(MB_LayerResultRepLay::create(this),20);
    }
    else if(kFightResultTypeRuleFight == m_pSc_fightdata->type)
    {
        this->setTouchEnabled(false);
        QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface);
        m_pResultdata->roleID = pInterface->getReplayRoleID();
        QUERY_FUNCTION_END;
        this->addChild(MB_LayerResultCommonFight::create(m_pResultdata),20);
    }
    else if (kFightResultTypeNoRule == m_pSc_fightdata->type)
    {
        m_pResultdata->type = kFightResultTypeNoRule;
        this->addChild(MB_LayerResultCommonFight::create(m_pResultdata),20);
    }
    else if(kFightResultTypeRoad == m_pSc_fightdata->type)
    {
        this->setTouchEnabled(false);
        this->addChild(MB_LayerResultRoad::create(m_pSc_fightdata, m_pResultdata),20);
        //        this->addChild(MB_LayerResultCommonFight::create(m_pResultdata),20);
    }
    else if (m_pSc_fightdata->type == kFightResultTypeChangeCoin)//招財猫戰鬥
    {
        this->setTouchEnabled(false);
        this->addChild(MB_LayerResultChangeCoin::create(m_pRewardCoin,m_pAddRewardCoin),20);
    }
    else if(kFightResultTypeDemoFight == m_pSc_fightdata->type)
    {
        CCDirector::sharedDirector()->popToRootScene();
        CCScene* pScene = MB_SceneRoleCreate::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    else if(kFightResultTypeKing == m_pSc_fightdata->type)
    {
        this->setTouchEnabled(false);
        MB_LayerResultBoss * layer = MB_LayerResultBoss::create(m_pRewardCoin, m_pRewardReputation,m_pSc_fightdata->issuccess,m_nPreHp,kFightResultTypeKing);
        this->addChild( layer,20);
    }
    else if(kFightResultTypeTrainerTrove == m_pSc_fightdata->type)
    {
        this->setTouchEnabled(false);
        MB_LayerTrainerTroveResult* layer = MB_LayerTrainerTroveResult::create(m_pSc_fightdata->issuccess,m_pRewardCoin);
        this->addChild(layer,20);
    }
    else if (m_pSc_fightdata->type == kFightResultTypeFriendFight)
    {
        this->setTouchEnabled(false);
        MB_LayerFriendFightResult* layer = MB_LayerFriendFightResult::create(m_pSc_fightdata->issuccess,m_pRewardCoin,m_pRewardReputation);
        this->addChild(layer,20);
    }
    else
    {
        onAllover();
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    this->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCCallFunc::create(this, callfunc_selector(MB_SceneGame::whenDelayOver)),NULL));
}
bool  MB_SceneGame::isnextSameType(int actionId1, int actionId2){
    
    if (actionId1 == actionId2) {
        
        return  true;
    }
    
    return  false;
}

void MB_SceneGame::removeNodeAndCleanUp(CCNode *node){
    
    node->removeFromParentAndCleanup(true);
}
void MB_SceneGame::loadTimeXml(){
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/actiontime.xml");
    
    if (!g_sharedDoc)
    {
        return ;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "actiontime")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        int first,second;
        float time;
        
        for ( ;attr != NULL;attr = attr->next){
            
            if (!xmlStrcmp(attr->name,BAD_CAST "actionType1"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                first = atoi(value);
                CC_SAFE_FREE(value);
                
            }
            else if (!xmlStrcmp(attr->name,BAD_CAST "actionType2"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                second = atoi(value);
                CC_SAFE_FREE(value);
                
            }
            else if (!xmlStrcmp(attr->name,BAD_CAST "time"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                time = atof(value);
                CC_SAFE_FREE(value);
                
            }
            
        }
        
        //time *= 0.5; // 控制戰鬥節奏
        
        timePos[first][second] = time;
        
        char strKey[50];
        sprintf(strKey,"speedup%d",MB_RoleData::getInstance()->getUID());
        if(CCUserDefault::sharedUserDefault()->getBoolForKey(strKey) && (MB_RoleData::getInstance()->getVipLevel() >= 2))
        {
            m_pScheduler->setTimeScale(2.0);
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
}
bool MB_SceneGame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    if ( m_bIsover  == true ) {
        
        
        return true;
    }
    
    for ( int i = 0 ; i < CARD_IN_GAME ; i++) {
        
        if(m_pOur[i] != NULL ){
            
            m_pOur[i]->setDetailShow(m_pOur[i]->isDetailShow() == false);
            
        }
        if(m_pEnemy[i] != NULL ){
            
            m_pEnemy[i]->setDetailShow(m_pEnemy[i]->isDetailShow() == false);
            
        }
    }
    return false;
    
}
void MB_SceneGame::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
    
    if(m_pSc_fightdata->type == kFightResultTypeRocketTeam || m_pSc_fightdata->type == kFightResultTypeNanm || m_pSc_fightdata->type == kFightResultTypeHuRong){
        
        if(m_nIsDelayOver == false){
            
            m_bIsover = true;
            return;
        }
    }
    
    if ( m_bIsover  == true ) {
        
        m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
        this->removeAllChildrenWithCleanup(true);
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        m_bIsover  = false;
    }
}

void MB_SceneGame::onAllover(){
    
    if (m_pAnimationMgr!=NULL) {
        
        m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
        m_pAnimationMgr = NULL;
    }
    this->removeAllChildrenWithCleanup(true);
}
void MB_SceneGame::registerWithTouchDispatcher(void){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MB_SceneGame::setTouch(bool touch){
    
    this->setTouchEnabled(touch);
    m_pMenu->setSwallowsTouches(true);
    m_pMenu->setTouchEnabled(touch);
    
    
}
void MB_SceneGame::whenDelayOver(){
    
    m_nIsDelayOver = true;
}
void MB_SceneGame::rePlay(){
    
    uint64_t replayId = m_nReplayID;
    uint8_t  table = m_nTable;
    uint8_t type = m_nReplayType;
    CCDirector::sharedDirector()->popScene();
    if(type == kReplayTypePvp){
        
        MB_MailData::getInstance()->sendhist_replay((kmMailsTable)table, replayId);
        
    }else if(type == kReplayTypeKing)
    {
    }
    else if(type == kReplayTypeEight) // PVP Top8 Report
    {
        MB_FunctionMgr* pFunctionMgr = MB_FunctionMgr::getInstance();
        NSGameFunction::CCFunctionInterface *pInterface = NULL;
        pFunctionMgr->queryFunctionByType(kFunctionArena,&pInterface);
        
        MB_Championship* pChampionship = dynamic_cast<MB_Championship*>(pInterface);
        if(pChampionship)
        {
            pChampionship->sendpvp_eight_replay(pChampionship->getFightReplayUID());
        }
    }
    else if(type == kReplayTypeRuleFight)
    {
        QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface);
        pInterface->cs_hist_replay(pInterface->getFightReplayUID());
        QUERY_FUNCTION_END;
    }
    else
    {
        if (m_pReplayCallBackTarget && m_pReplayCallBack)
        {
            (m_pReplayCallBackTarget->*m_pReplayCallBack)();
        }
    }
}




void MB_SceneGame::onSpeedUpClick(CCObject *)
{
    if(MB_RoleData::getInstance()->getVipLevel() < 2){
        
        MB_Message::sharedMB_Message()->showMessage("主人, 充值成为VIP2就可以加速战斗哦~~~");
        return;
    }
    
    char strKey[50];
    sprintf(strKey,"speedup%d",MB_RoleData::getInstance()->getUID());
    CCUserDefault::sharedUserDefault()->setBoolForKey(strKey,   CCUserDefault::sharedUserDefault()->getBoolForKey(strKey) ==false);
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(strKey))
    {
        m_pMenuSpeedUp->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
        m_pMenuSpeedUp->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_2.png"));
        m_pScheduler->setTimeScale(2);
    }else
    {
        m_pMenuSpeedUp->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_1.png"));
        m_pMenuSpeedUp->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_speed_1.png"));
        m_pScheduler->setTimeScale(1);
    }
}


CCProgressTimer* MB_SceneGame::setProgressBar(CCSprite* spr,CCPoint midp,int o)
{
    CCNode *node=spr->getParent();
    CCPoint pos=spr->getPosition();
    int z= spr->getZOrder();
    float scalex = spr->getScaleX();
    float scaley = spr->getScaleY();
    float rotaition = spr->getRotation();
    spr->setVisible(false);
    
    CCSprite* sprite1 =CCSprite::createWithSpriteFrame(spr->displayFrame());
    CCProgressTimer* pr = CCProgressTimer::create(sprite1);
    pr->setType(kCCProgressTimerTypeRadial);
    pr->setMidpoint(midp);
    if (midp.x>0.2f) {
        pr->setReverseDirection(true);
        pr->setPercentage(TESHUROTATION+BLOODBAREND);
    }else
    {
        pr->setPercentage(BLOODBAREND);
    }

    pr->setPosition(pos);
    pr->setScaleX(scalex);
    pr->setScaleY(scaley);
    pr->setRotation(rotaition);
    node->addChild(pr,z );

    pr->setOpacity(o);
    return pr;
}
void MB_SceneGame::setBlood(int petPos,int addHp)
{
    float tempFloat = BLOODBAREND - BLOODBARSTART;
    int p = -1;
    if (petPos>0) {
        petPos = petPos-1;
        float lastPer = nowOurPer;
        if (addHp<0) {
            addHp = ourPosNowHp[petPos]>(-addHp)?addHp:-ourPosNowHp[petPos];
        }else
        {
            addHp = (ourPosNowHp[petPos]+addHp)<ourPosAllHp[petPos]?addHp:ourPosAllHp[petPos]-ourPosNowHp[petPos];
        }
        ourPosNowHp[abs(petPos)]+= addHp;
        
        m_nOurNowHpNum = m_nOurNowHpNum+addHp;
        if(m_nOurNowHpNum<0){m_nOurNowHpNum = 0;p=0;nowOurPer=BLOODBARSTART;}
        if(m_nOurNowHpNum>m_nOurAllHpNum){m_nOurNowHpNum = m_nOurAllHpNum;p=100;nowOurPer=BLOODBAREND;}
        if(p==-1){p = m_nOurNowHpNum*100.0f/m_nOurAllHpNum;nowOurPer =BLOODBARSTART+ m_nOurNowHpNum*tempFloat/m_nOurAllHpNum;}
        m_pAllOurHP->setString(CCString::createWithFormat("%d",p )->getCString() );
        PROGRESSSPEED_our =(ourProgress1->getPercentage()-nowOurPer)/PERSPEED;
        progressSpeedJian_our =PROGRESSSPEED_our*.6f;
        if (deayPerFrame_our = -999) {
            progressSpeedJian_our_o =PROGRESSSPEED_our*.6f;
            deayPerFrame_our = ALLDEAYPERFRAME;
        }else
        {
            ourProgress1_o->setPercentage(ourProgress1_o->getPercentage()-(lastPer-nowOurPer));
            ourProgress2_o->setPercentage(ourProgress2_o->getPercentage());
        }
    }
    else
    {
        float lastPer = nowEnemyPer;
        petPos =abs(petPos)-1;
        if (addHp<0) {
            addHp = enemyPosNowHp[petPos]>(-addHp)?addHp:-enemyPosNowHp[petPos];
        }else
        {
            addHp = (enemyPosNowHp[petPos]+addHp)<enemyPosAllHp[petPos]?addHp:enemyPosAllHp[petPos]-enemyPosNowHp[petPos];
        }
        enemyPosNowHp[abs(petPos)]+= addHp;
        
        m_nEnemyNowHpNum = m_nEnemyNowHpNum+addHp;
        if (m_bIsScaleBoss) {
            if(m_nEnemyNowHpNum<0){m_nEnemyNowHpNum = 0;p=0;}
            if(m_nEnemyNowHpNum>m_nEnemyAllHpNum){m_nEnemyNowHpNum = m_nEnemyAllHpNum;p=100;}
            if(p==-1){p =m_nEnemyNowHpNum*100.0f/m_nEnemyAllHpNum;}
            nowTrueEnemyPer = p;
            m_pNowEnemyHP->setString(CCString::createWithFormat("%d",m_nEnemyNowHpNum )->getCString() );
        }else
        {
            if(m_nEnemyNowHpNum<0){m_nEnemyNowHpNum = 0;p=0;nowEnemyPer = TESHUROTATION+BLOODBARSTART;}
            if(m_nEnemyNowHpNum>m_nEnemyAllHpNum){m_nEnemyNowHpNum = m_nEnemyAllHpNum;p=100;nowEnemyPer = TESHUROTATION+BLOODBAREND;}
            if(p==-1){p =m_nEnemyNowHpNum*100.0f/m_nEnemyAllHpNum;nowEnemyPer =TESHUROTATION+BLOODBARSTART+ m_nEnemyNowHpNum*tempFloat/m_nEnemyAllHpNum;}
            PROGRESSSPEED_enemy =(m_enemyProgress1->getPercentage()-nowEnemyPer)/PERSPEED;
            progressSpeedJian_enemy =PROGRESSSPEED_enemy*.6f;
            if (deayPerFrame_enemy = -999) {
                progressSpeedJian_enemy_o =PROGRESSSPEED_enemy*.6f;
                deayPerFrame_enemy = ALLDEAYPERFRAME;
            }else
            {
                m_enemyProgress1_o->setPercentage(m_enemyProgress1_o->getPercentage()-(lastPer-nowEnemyPer));
                m_enemyProgress2_o->setPercentage(m_enemyProgress1_o->getPercentage());
            }
            m_pAllEnemyHP->setString(CCString::createWithFormat("%d",p )->getCString() );
        }
    }
}


void MB_SceneGame::updateProgress(float dt)
{
    float tempFloat =ourProgress1->getPercentage() - nowOurPer;
    if(tempFloat>0&&PROGRESSSPEED_our>0||tempFloat<0&&PROGRESSSPEED_our<0)
    {
        if (tempFloat<PROGRESSSPEED_our*1.5f) {

            ourProgress1->setPercentage(ourProgress1->getPercentage()-progressSpeedJian_our);
            progressSpeedJian_our/=3;
            if(progressSpeedJian_our>0&&progressSpeedJian_our<0.01f)progressSpeedJian_our = 0.01f;
            else if(progressSpeedJian_our<0&&progressSpeedJian_our>-0.01f)progressSpeedJian_our = -0.01f;
        }else
        {
            ourProgress1->setPercentage(ourProgress1->getPercentage()-PROGRESSSPEED_our);
        }

        ourProgress2->setPercentage(ourProgress1->getPercentage());
    }

    tempFloat =m_enemyProgress1->getPercentage()-nowEnemyPer;
    if(tempFloat>0&&PROGRESSSPEED_enemy>0||tempFloat<0&&PROGRESSSPEED_enemy<0)
    {
        if (tempFloat<PROGRESSSPEED_enemy*1.5f) {
            m_enemyProgress1->setPercentage(m_enemyProgress1->getPercentage()-progressSpeedJian_enemy);
            progressSpeedJian_enemy/=3;
            if(progressSpeedJian_enemy>0&&progressSpeedJian_enemy<0.01f)progressSpeedJian_enemy = 0.01f;
            else if(progressSpeedJian_enemy<0&&progressSpeedJian_enemy>-0.01f)progressSpeedJian_enemy = -0.01f;
        }else
        {
            m_enemyProgress1->setPercentage(m_enemyProgress1->getPercentage()-PROGRESSSPEED_enemy);
        }
        m_enemyProgress2->setPercentage(m_enemyProgress1->getPercentage());
    }


    if (deayPerFrame_our!=0) {
        deayPerFrame_our--;
    }else if(ourProgress1_o->getPercentage()>nowOurPer&&PROGRESSSPEED_our>0)
    {
        tempFloat =ourProgress1_o->getPercentage()-nowOurPer;
        if (tempFloat<PROGRESSSPEED_our*1.5f) {
            ourProgress1_o->setPercentage(ourProgress1_o->getPercentage()-progressSpeedJian_our_o);
            progressSpeedJian_our_o/=3;
            if(progressSpeedJian_our_o>0&&progressSpeedJian_our_o<0.01f)progressSpeedJian_our_o = 0.01f;
            else if(progressSpeedJian_our_o<0&&progressSpeedJian_our_o>-0.01f)progressSpeedJian_our_o = -0.01f;
        }else
        {
            ourProgress1_o->setPercentage(ourProgress1_o->getPercentage()-PROGRESSSPEED_our);
        }

        ourProgress2_o->setPercentage(ourProgress1_o->getPercentage());
    }else
    {
        deayPerFrame_our = -999;
        ourProgress1_o->setPercentage(ourProgress1->getPercentage());
        ourProgress2_o->setPercentage(ourProgress1_o->getPercentage());
    }

    if (deayPerFrame_enemy!=0) {
        deayPerFrame_enemy--;
    }else if(m_enemyProgress1_o->getPercentage()>nowEnemyPer&&PROGRESSSPEED_enemy>0)
    {
        tempFloat =m_enemyProgress1_o->getPercentage()-nowEnemyPer;
        if (tempFloat<PROGRESSSPEED_enemy*1.5f) {
            m_enemyProgress1_o->setPercentage(m_enemyProgress1_o->getPercentage()-progressSpeedJian_enemy_o);
            progressSpeedJian_enemy_o/=3;
            if(progressSpeedJian_enemy_o>0&&progressSpeedJian_enemy_o<0.01f)progressSpeedJian_enemy_o = 0.01f;
            else if(progressSpeedJian_enemy_o<0&&progressSpeedJian_enemy_o>-0.01f)progressSpeedJian_enemy_o = -0.01f;
        }else
        {
            m_enemyProgress1_o->setPercentage(m_enemyProgress1_o->getPercentage()-PROGRESSSPEED_enemy);
        }

        m_enemyProgress2_o->setPercentage(m_enemyProgress1_o->getPercentage());
    }else
    {
        deayPerFrame_enemy = -999;
        m_enemyProgress1_o->setPercentage(m_enemyProgress1->getPercentage());
        m_enemyProgress2_o->setPercentage(m_enemyProgress1_o->getPercentage());
    }
    
    
    for (int i = 0;  i < CARD_IN_GAME; i++) {
        if(m_pEnemy[i] != NULL){
            tempFloat = fabs(m_pTempode[i+6]->getPositionX()+m_pEnemyNode->getPositionX()-320)/250;
            tempFloat = tempFloat>1?1:tempFloat;
            m_pEnemy[i]->m_pToScaleNode->setScale(1+.35f*(1-tempFloat));
            
        }
    }
}
void MB_SceneGame::updateProgressWorldBoss(float dt)
{
    float tempFloat =ourProgress1->getPercentage() - nowOurPer;
    if(tempFloat>0&&PROGRESSSPEED_our>0||tempFloat<0&&PROGRESSSPEED_our<0)
    {
        if (tempFloat<PROGRESSSPEED_our*1.5f) {
            
            ourProgress1->setPercentage(ourProgress1->getPercentage()-progressSpeedJian_our);
            progressSpeedJian_our/=3;
            if(progressSpeedJian_our>0&&progressSpeedJian_our<0.01f)progressSpeedJian_our = 0.01f;
            else if(progressSpeedJian_our<0&&progressSpeedJian_our>-0.01f)progressSpeedJian_our = -0.01f;
        }else
        {
            ourProgress1->setPercentage(ourProgress1->getPercentage()-PROGRESSSPEED_our);
        }
        
        ourProgress2->setPercentage(ourProgress1->getPercentage());
    }
    
    if (deayPerFrame_our!=0) {
        deayPerFrame_our--;
    }else if(ourProgress1_o->getPercentage()>nowOurPer&&PROGRESSSPEED_our>0)
    {
        tempFloat =ourProgress1_o->getPercentage()-nowOurPer;
        if (tempFloat<PROGRESSSPEED_our*1.5f) {
            ourProgress1_o->setPercentage(ourProgress1_o->getPercentage()-progressSpeedJian_our_o);
            progressSpeedJian_our_o/=3;
            if(progressSpeedJian_our_o>0&&progressSpeedJian_our_o<0.01f)progressSpeedJian_our_o = 0.01f;
            else if(progressSpeedJian_our_o<0&&progressSpeedJian_our_o>-0.01f)progressSpeedJian_our_o = -0.01f;
        }else
        {
            ourProgress1_o->setPercentage(ourProgress1_o->getPercentage()-PROGRESSSPEED_our);
        }
        
        ourProgress2_o->setPercentage(ourProgress1_o->getPercentage());
    }else
    {
        deayPerFrame_our = -999;
        ourProgress1_o->setPercentage(ourProgress1->getPercentage());
        ourProgress2_o->setPercentage(ourProgress1_o->getPercentage());
    }
    
    
    if (nowTrueEnemyPer!=nowEnemyPer) {
        if(nowEnemyPer<nowTrueEnemyPer)PROGRESSSPEED_enemy = WORLDBOSSPERSPEED;
        else PROGRESSSPEED_enemy = -WORLDBOSSPERSPEED;
        nowEnemyPer+=PROGRESSSPEED_enemy;
        
        if (PROGRESSSPEED_enemy>0) {
            if (nowEnemyPer>nowTrueEnemyPer) {
                nowEnemyPer = nowTrueEnemyPer;
            }
        }else if (nowEnemyPer<nowTrueEnemyPer) {
            nowEnemyPer = nowTrueEnemyPer;
        }
    }
    
    tempFloat = m_enemyProgress1->getPercentage()+PROGRESSSPEED_enemy*m_nWorldBossBarNum;
    if (worldBossBarIndex==(int)nowEnemyPer/m_nWorldBossBarNum) {
        float tempFloat2 = (nowEnemyPer-worldBossBarIndex*m_nWorldBossBarNum)*WORLDBOSSBARNUM;
        if(PROGRESSSPEED_enemy<0)
        {
            if(tempFloat<tempFloat2)
            {
                tempFloat = tempFloat2;
            }
        }else if(tempFloat>tempFloat2)
        {
            tempFloat = tempFloat2;
        }
    }
    
    if (tempFloat<0 || tempFloat>100) {
        if (tempFloat<0) {
            tempFloat+=100;
            worldBossBarIndex--;
        }else if (tempFloat>100)
        {
            tempFloat-=100;
            worldBossBarIndex++;
        }
        
        int tempInt = worldBossBarIndex%WORLDBOSSTRUEBARNUM+1;
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist"); m_enemyProgress1->getSprite()->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bg_blood_0%d.png",tempInt)->getCString()));
        if(worldBossBarIndex==0)
        {
            m_enemyBar2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_blood_00.png"));
        }else
        {
            tempInt--;
            tempInt = tempInt==0?WORLDBOSSTRUEBARNUM:tempInt;
            m_enemyBar2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bg_blood_0%d.png",tempInt)->getCString()));
        }
    }
    m_enemyProgress1->setPercentage(tempFloat);
}

void MB_SceneGame::palyDaZhao(bool b)
{
    if (b) {
        m_pDiZuo->runAction(CCMoveTo::create(.5f, dizuoLittleP));
        m_pDiZuo->runAction(CCScaleTo::create(.5f, dizuoLittleSX,dizuoLittleSY));
        m_pEnemyNode->runAction(CCMoveTo::create(.5f, EnemyNodeLittleP));
        m_pEnemyNode->runAction(CCScaleTo::create(.5f, EnemyNodeLittleSX,EnemyNodeLittleSY));
    }else
    {
        m_pDiZuo->runAction(CCMoveTo::create(.7f, dizuoBigP));
        m_pDiZuo->runAction(CCScaleTo::create(.7f, dizuoBigSX,dizuoBigSY));
        m_pEnemyNode->runAction(CCMoveTo::create(.7f, EnemyNodeBigP));
        m_pEnemyNode->runAction(CCScaleTo::create(.7f,EnemyNodeBigSX, EnemyNodeBigSY));
    }
}
void MB_SceneGame::delayPalyDaZhao()
{
    palyDaZhao(false);
}
