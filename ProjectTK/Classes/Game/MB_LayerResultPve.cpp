//
//  MB_LayerResultPve.cpp
//  ProjectMB
//
//  Create by chk on 29/9/2014.
//
//
#include "MB_LayerResultPve.h"
#include "MB_NodeItemBook.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerResultPVPRanking.h"
#include "MB_NodePetResult.h"
#include "MB_ScrollBg.h"
MB_LayerResultPve::MB_LayerResultPve()
{
    m_pSpriteExp2 = NULL;
    m_pNode1 = NULL;
    m_pNode2 = NULL;
    m_pNodeScroller = NULL;
    m_pRoleExp = NULL;
    m_pSpriteExp = NULL;
    m_pRoleLevel = NULL;
    ttf_chaptername2 = NULL;
    m_pLevelUp = NULL;
    m_pCoinLabel = NULL;
    m_pExpLabel = NULL;
    m_pNodeReward	 = NULL;
    m_pStars[0] = NULL;
    m_pStars[1] = NULL;
    m_pStars[2] = NULL;
    m_bClickedBack = false;
    m_pSpr1= NULL;
    m_pSpr2= NULL;
    m_pSpr3= NULL;
  m_pItemSpr1= NULL;
 m_pItemSpr2= NULL;
}
MB_LayerResultPve::~MB_LayerResultPve()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteExp2);
    CC_SAFE_RELEASE_NULL(m_pNode1);
    CC_SAFE_RELEASE_NULL(m_pNode2);
    CC_SAFE_RELEASE_NULL(m_pNodeScroller);
    CC_SAFE_RELEASE_NULL(m_pRoleExp);
    CC_SAFE_RELEASE_NULL(m_pSpriteExp);
    CC_SAFE_RELEASE_NULL(m_pRoleLevel);
    CC_SAFE_RELEASE_NULL(ttf_chaptername2);
    CC_SAFE_RELEASE_NULL(m_pLevelUp);
    
    CC_SAFE_RELEASE_NULL(m_pExpLabel);
    CC_SAFE_RELEASE_NULL(m_pCoinLabel);
    CC_SAFE_RELEASE_NULL(m_pNodeReward);
    
    CC_SAFE_RELEASE_NULL(m_pStars[0]);
    CC_SAFE_RELEASE_NULL(m_pStars[1]);
    CC_SAFE_RELEASE_NULL(m_pStars[2]);
    CC_SAFE_RELEASE_NULL(m_pSpr1);
    CC_SAFE_RELEASE_NULL(m_pSpr2);
    CC_SAFE_RELEASE_NULL(m_pSpr3);
    CC_SAFE_RELEASE_NULL(m_pItemSpr1);
    CC_SAFE_RELEASE_NULL(m_pItemSpr2);
}
void MB_LayerResultPve::onEnter()
{
    MB_ResWindow::onEnter();
    if (global_tutorialNode!=NULL) {
        global_tutorialNode->setVisible(false);
    }
}


bool MB_LayerResultPve::init(recvfight *fightResult,p_reward *result,bool bFirstFailed)
{
    MB_ResWindow::init();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(fightResult->issuccess == 1?"res/pve_layer_win.ccbi":"res/pve_layer_lose.ccbi", this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RELEASE(pCCBReader);
    this->addChild(pNode);
    if(fightResult->issuccess == 1)
    {
        setTouchEnabled(true);
        lastLevel =result->preLevel;
        lastExp =result->preExp;
        nowLevel = MB_RoleData::getInstance()->getLevel();
        nowExp = MB_RoleData::getInstance()->getEXP();
        addExpSpeed = (nowExp-lastExp)/60;
        
        preDiscovery = result->preDiscovery;
        preEnergy = result->preEnergy;
        if ( result->score > 0)
        {
            for(int i = 0;i<3;++i)
            {
                m_pStars[i]->setVisible(result->score>i);
            }
        }
        starSoundIndex = 0;
        starSoundIndex2 = result->score;
        schedule(schedule_selector(MB_LayerResultPve::updateStarSound));
        
        char databuf[50];
        sprintf(databuf, "+%d",result->roleExp);
        if(m_pExpLabel)m_pExpLabel->setString(databuf);
        
        sprintf(databuf, "+%d",result->coin);
        if(m_pCoinLabel)m_pCoinLabel->setString(databuf);
        sprintf(databuf, "%d",lastLevel);
        m_pRoleLevel->setString(databuf);
        
        //奖励
        CCArray* pArray = CCArray::create();
        
        p_item_view *item = result->item;
        while ( item!=NULL)
        {
            if(item->itemNum>0)
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(1);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                
                pArray->addObject(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            else
            {
                RewardTempleteValue* pValue = new RewardTempleteValue;
                
                pValue->setType(2);
                pValue->setValueID(item->itemTypeId);
                pValue->setNumber(item->itemNum);
                
                pArray->addObject(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            item = item->next;
        }
        if(pArray->count())
        {
            MB_LayerRewardContainer* ItemContainer = MB_LayerRewardContainer::create(pArray);
            CCScrollView* pScrollView = CCScrollView::create(m_pNodeReward->getContentSize());
            m_pNodeReward->addChild(pScrollView);
//            pScrollView->setAnchorPoint(CCPoint(0.5,0.5));
            ItemContainer->setPosLeft();
            pScrollView->setContainer(ItemContainer);
            pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        }
        
        
        m_pExpTimer2 = CCProgressTimer::create(m_pSpriteExp2);
        m_pExpTimer2->setType(kCCProgressTimerTypeBar);
        m_pExpTimer2->setMidpoint(ccp(0, 1));
        m_pExpTimer2->setBarChangeRate(ccp(1, 0));
        m_pSpriteExp2->getParent()->addChild(m_pExpTimer2, m_pSpriteExp2->getZOrder(), m_pSpriteExp2->getTag());
        m_pExpTimer2->setPosition(m_pSpriteExp2->getPosition());
        m_pExpTimer2->setAnchorPoint(m_pSpriteExp2->getAnchorPoint());
        
        m_pExpTimer = CCProgressTimer::create(m_pSpriteExp);
        m_pExpTimer->setType(kCCProgressTimerTypeBar);
        m_pExpTimer->setMidpoint(ccp(0, 1));
        m_pExpTimer->setBarChangeRate(ccp(1, 0));
        m_pSpriteExp->getParent()->addChild(m_pExpTimer, m_pSpriteExp2->getZOrder()+1, m_pSpriteExp->getTag());
        m_pExpTimer->setPosition(m_pSpriteExp->getPosition());
        m_pExpTimer->setAnchorPoint(m_pSpriteExp->getAnchorPoint());
        
        m_pSpriteExp2->removeFromParent();
        m_pSpriteExp->removeFromParent();
        
        m_preExp = MB_RoleData::getInstance()->getExpByLevel(lastLevel- 1);
        m_nextExp = MB_RoleData::getInstance()->getExpByLevel(lastLevel);
        float m_tPerccent = 100.0f*(lastExp - m_preExp) / (m_nextExp - m_preExp);
        sprintf(databuf, "%lld/%lld", (int64_t)lastExp - m_preExp, m_nextExp - m_preExp);
        m_pRoleExp->setString(databuf);
        m_pExpTimer->setPercentage(m_tPerccent);
        m_pExpTimer2->setPercentage(m_tPerccent);
        
        sprintf(databuf,"%d-%d %s",m_SceneGameBigLevel,m_SceneGameLittleLevel,m_SceneGameLevelName);
        ttf_chaptername2->setString(databuf);
    }
    else
    {
        //失败
        m_pSpr1->setOpacity(0);
        m_pSpr2->setOpacity(0);
        m_pSpr3->setOpacity(0);
        
        m_pSpr1->runAction(CCSequence::create(CCDelayTime::create(.2f),CCFadeIn::create(1),NULL ));
        m_pSpr2->runAction(CCSequence::create(CCDelayTime::create(.6f),CCFadeIn::create(1),NULL ));
        m_pSpr3->runAction(CCSequence::create(CCDelayTime::create(1),CCFadeIn::create(1),NULL ));
    }
    return true;
}
void MB_LayerResultPve::update(float dt)
{
    lastExp+=addExpSpeed;
    if (lastExp>=nowExp) {
        unscheduleUpdate();
        lastExp = nowExp;
    }
    
    char databuf[50];
    float m_tPerccent = 100.0f*(lastExp - m_preExp) / (m_nextExp - m_preExp);
    if (m_tPerccent>=100) {
        lastLevel++;
        sprintf(databuf, "%d",lastLevel);
        m_pRoleLevel->setString(databuf);
        int64_t tempNextExp = m_nextExp;
        m_pExpTimer->removeFromParent();
        m_preExp = MB_RoleData::getInstance()->getExpByLevel(lastLevel- 1);
        m_nextExp = MB_RoleData::getInstance()->getExpByLevel(lastLevel);
        m_tPerccent -= 100;
        sprintf(databuf, "%lld/%lld", (int64_t)lastExp - tempNextExp, m_nextExp - m_preExp);
        
        m_pLevelUp->setVisible(true);
        MB_LayerRoleLevelUp *pLayer = MB_LayerRoleLevelUp::create(lastLevel-1, preDiscovery, preEnergy);
        if (global_tutorialNode!=NULL) {
            CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer,global_tutorialNode->getZOrder()+1,999);
        }else
        {
            addChild(pLayer,Z_ORDER_OUTSHOW,999);
        }
    }else
    {
        sprintf(databuf, "%lld/%lld", (int64_t)lastExp - m_preExp, m_nextExp - m_preExp);
    }
    m_pRoleExp->setString(databuf);
    m_pExpTimer2->setPercentage(m_tPerccent);
}
void MB_LayerResultPve::onExit()
{
    MB_Audio::getInstance()->playNormalBgm();
    MB_ResWindow::onExit();
}
bool MB_LayerResultPve::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr1",CCSprite*,m_pSpr1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr2",CCSprite*,m_pSpr2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpr3",CCSprite*,m_pSpr3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pExpLabel",CCLabelBMFont*,m_pExpLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCoinLabel",CCLabelBMFont*,m_pCoinLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward",CCNode*,m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar1",CCSprite*,m_pStars[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar2",CCSprite*,m_pStars[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar3",CCSprite*,m_pStars[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteExp2",CCSprite*,m_pSpriteExp2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode1",CCNode*,m_pNode1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode2",CCNode*,m_pNode2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeScroller",CCNode*,m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleExp",CCLabelBMFont*,m_pRoleExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteExp",CCSprite*,m_pSpriteExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleLevel",CCLabelBMFont*,m_pRoleLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ttf_chaptername2",CCLabelTTF*,ttf_chaptername2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLevelUp",CCNode*,m_pLevelUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemSpr1",CCNode*,m_pItemSpr1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemSpr2",CCNode*,m_pItemSpr2);
    return false;
}
SEL_MenuHandler MB_LayerResultPve::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBackClick",MB_LayerResultPve::onBackClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerResultPve::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBackClick",MB_LayerResultPve::onBackClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHomeClick", MB_LayerResultPve::onHomeClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRetryClick", MB_LayerResultPve::onRetryClick);
    return NULL;
}
void MB_LayerResultPve::registerWithTouchDispatcher(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}
bool MB_LayerResultPve::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void MB_LayerResultPve::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    PlayBackGround(ksSound_JieSuan);
    setTouchEnabled(false);
    addChild(MB_ScrollBg::create(left_top,.5f,2),-1);
    m_pNode1->removeFromParent();
    m_pNode2->setVisible(true);
    m_pAnimation->runAnimationsForSequenceNamed("play");
    MB_NodePetResult* npdw;
    for (int i = 0; i < CARD_IN_GAME; i++) {
        if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)!=NULL&&MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL){
            npdw = MB_NodePetResult::create(MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID());
        }
        else {
            npdw = MB_NodePetResult::create(-1);
        }
        npdw->setTag(i+100);
        npdw->opx2 = npdw->m_nWidth*(.5f + i);
        npdw->opy2 = npdw->getPositionY();
        npdw->setPositionX(npdw->opx2);
        m_pNodeScroller->addChild(npdw);
    }
    
    scheduleUpdate();
    if (global_tutorialNode!=NULL) {
        global_tutorialNode->setVisible(true);
    }
}

void MB_LayerResultPve::onHomeClick(CCObject* pSender)
{
    m_bIsToHome = true;
    onBackClick(pSender);
}

void MB_LayerResultPve::onRetryClick(CCObject* pSender)
{
    global_isRePlay = true;
    onBackClick(NULL);
}

void MB_LayerResultPve::onBackClick(CCObject* pSender)
{
    if(m_bClickedBack)return;
    m_bClickedBack = true;
    TutorialTriggerComplete
    if (lastExp<nowExp) {
        lastExp = nowExp;
        update(0);
    }
    if (!getChildByTag(999) && !CCDirector::sharedDirector()->getRunningScene()->getChildByTag(999)) {
        onBack();
    }else
    {
        schedule(schedule_selector(MB_LayerResultPve::updateBack));
    }
}
void MB_LayerResultPve::onBack()
{
    PlayBackGround(kmBackGround_Normal);
    CCDirector::sharedDirector()->popScene();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    if(MB_TutorialMgr::getInstance()->getCompletePveGoHome())
    {
        MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypeHome);
    }
}
void MB_LayerResultPve::updateBack(float dt)
{
    if (!getChildByTag(999) && !CCDirector::sharedDirector()->getRunningScene()->getChildByTag(999)) {
        unschedule(schedule_selector(MB_LayerResultPve::updateBack));
        onBack();
    }
}
MB_LayerResultPve * MB_LayerResultPve::create(recvfight *fightResult,p_reward *result, bool bFirstFailed){
    
    MB_LayerResultPve * ptr = new MB_LayerResultPve();
    if (ptr && ptr->init(fightResult,result,bFirstFailed))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

void MB_LayerResultPve::updateStarSound(float dt)
{
    if (m_pStars[starSoundIndex]->getScale()>0.2f) {
        if (++starSoundIndex==starSoundIndex2) {
            unschedule(schedule_selector(MB_LayerResultPve::updateStarSound));
        }
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Star).c_str());
    }
}
/////

MB_LayerResultChungGuan * MB_LayerResultChungGuan::create(recvfight *fightResult,p_reward *result){
    
    MB_LayerResultChungGuan * ptr = new MB_LayerResultChungGuan();
    if (ptr && ptr->init(fightResult,result))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_LayerResultChungGuan::init(recvfight *fight,p_reward *result)
{
    MB_ResWindow::init();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCNode* pNode = loadResource(fight->issuccess == 1?"res/pve_layer_towerwin.ccbi":"res/pve_layer_towerfail.ccbi");
    this->addChild(pNode);
    

    
    if(fight->issuccess == 1)
    {
        char databuf[50];
        sprintf(databuf, "%d",result->coin);
        if(m_pCoinLabel)m_pCoinLabel ->setString(databuf);
        sprintf(databuf, "%d",result->reputation);
        if(m_pExpLabel)m_pExpLabel ->setString(databuf);
        m_pItemSpr1->setPositionX(384+((m_pCoinLabel->getContentSize().width-48)*.4f));
        m_pItemSpr2->setPositionX(404+((m_pExpLabel->getContentSize().width-93)*.4f));
    }
    
    //奖励
    CCArray* pArray = CCArray::create();
    p_item_view *item = result->item;
    while ( item!=NULL)
    {
        if(item->itemNum>0)
        {
            RewardTempleteValue* pValue = new RewardTempleteValue;
            
            pValue->setType(1);
            pValue->setValueID(item->itemTypeId);
            pValue->setNumber(item->itemNum);
            
            pArray->addObject(pValue);
            CC_SAFE_RELEASE_NULL(pValue);
        }
        else
        {
            RewardTempleteValue* pValue = new RewardTempleteValue;
            
            pValue->setType(2);
            pValue->setValueID(item->itemTypeId);
            pValue->setNumber(item->itemNum);
            
            pArray->addObject(pValue);
            CC_SAFE_RELEASE_NULL(pValue);
        }
        item = item->next;
    }
    if(pArray->count())
    {
        MB_LayerRewardContainer* ItemContainer = MB_LayerRewardContainer::create(pArray);
        CCScrollView* pScrollView = CCScrollView::create(m_pNodeReward->getContentSize());
        m_pNodeReward->addChild(pScrollView);
        CCSize sz = ItemContainer->getContentSize();
        if (sz.width<m_pNodeReward->getContentSize().width)
        {
            sz.width = m_pNodeReward->getContentSize().width;
            ItemContainer->setContentSize(sz);
        }
        pScrollView->setContainer(ItemContainer);
        pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
    }
    
    
    return true;
}


/////

MB_LayerResultRoad * MB_LayerResultRoad::create(recvfight *fightResult,SResultData *result)
{    
    MB_LayerResultRoad * ptr = new MB_LayerResultRoad();
    if (ptr && ptr->init(fightResult,result))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

bool MB_LayerResultRoad::init(recvfight *fight,SResultData *result)
{
    MB_ResWindow::init();
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCNode* pNode = loadResource(fight->issuccess == 1?"res/pve_layer_towerwin.ccbi":"res/pve_layer_towerfail.ccbi");
    this->addChild(pNode);
    
    CCArray* pArray = result->getRewards();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH_REVERSE(pArray,pObj)
    {
        RewardTempleteValue* pTemp = dynamic_cast<RewardTempleteValue*>(pObj);
        if(pTemp->getValueID() == COIN_ID)
        {
            if(m_pCoinLabel)m_pCoinLabel->setString(CCString::createWithFormat("%d",pTemp->getNumber())->getCString());
            pArray->removeObject(pObj);
            
        }
        else if(pTemp->getValueID() == REPUTATION_ID)
        {
            if(m_pExpLabel)m_pExpLabel->setString(CCString::createWithFormat("%d",pTemp->getNumber())->getCString());
            pArray->removeObject(pObj);
        }
    }
   
    if(fight->issuccess == 1)
    {
        m_pItemSpr1->setPositionX(384+((m_pCoinLabel->getContentSize().width-48)*.4f));
        m_pItemSpr2->setPositionX(404+((m_pExpLabel->getContentSize().width-93)*.4f));
    }
    

    if(pArray && pArray->count())
    {
        MB_LayerRewardContainer* ItemContainer = MB_LayerRewardContainer::create(pArray);
        CCScrollView* pScrollView = CCScrollView::create(m_pNodeReward->getContentSize());
        m_pNodeReward->addChild(pScrollView);
        CCSize sz = ItemContainer->getContentSize();
        if (sz.width<m_pNodeReward->getContentSize().width)
        {
            sz.width = m_pNodeReward->getContentSize().width;
            ItemContainer->setContentSize(sz);
        }
        pScrollView->setContainer(ItemContainer);
        pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
    }
    
    return true;
}

