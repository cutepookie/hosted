
#include "MB_LayerRewardOne.h"
#include "MB_LayerPicDeploy.h"
#include "MB_DataExchange.h"
USING_NS_CC;
USING_NS_CC_EXT;
CCPoint starPt_lro[MAX_GER_STAR];
MB_LayerRewardOne::MB_LayerRewardOne()
{
	index = 0;
	isSet = false;
    m_pBtn = NULL;
	m_pNext = NULL;
	m_pLayerBg = NULL;
	m_pTTFName = NULL;
	m_pBg2 = NULL;
	m_pBg = NULL;
	m_pNodeCard = NULL;
	m_pCommit = NULL;
	m_pOnceMore = NULL;
	m_pTenthMore = NULL;
	m_pPass = NULL;
	m_pVisibleNode2 = NULL;
	m_pNodeTutorial = NULL;
	m_pTarget = NULL;
	m_pMenuCall = NULL;
	m_pMenuCallOnceMore = NULL;
	m_pAnimation = NULL;
	isReward = false;
	for (int i = 0; i < REWARD_TEN_COUNT; i++) {
		m_pNodeIcon[i] = NULL;
	}
	for (int i = 0; i < MAX_GER_STAR; i++) {
		m_pStar[i] = NULL;
	}
	m_ValueArray = new CCArray();
	isOnlyShow = false;
	MB_LayerRoleInfoHeader::setMenuEnable(false, "MB_LayerRewardOne");
}

MB_LayerRewardOne::~MB_LayerRewardOne()
{
	for (int i = 0; i < REWARD_TEN_COUNT; i++) {
		CC_SAFE_RELEASE(m_pNodeIcon[i]);
	}
	
	CC_SAFE_RELEASE_NULL(m_pNext);
	CC_SAFE_RELEASE_NULL(m_pLayerBg);
	CC_SAFE_RELEASE_NULL(m_pBg2);
	CC_SAFE_RELEASE_NULL(m_pBg);
	CC_SAFE_RELEASE_NULL(m_pNodeCard);
	CC_SAFE_RELEASE_NULL(m_pCommit);
	CC_SAFE_RELEASE_NULL(m_pOnceMore);
	CC_SAFE_RELEASE_NULL(m_pTenthMore);
	CC_SAFE_RELEASE_NULL(m_pPass);
	CC_SAFE_RELEASE_NULL(m_pVisibleNode2);
	CC_SAFE_RELEASE_NULL(m_pAnimation);
	CC_SAFE_RELEASE_NULL(m_pNodeTutorial);
	CC_SAFE_RELEASE(m_ValueArray);
	CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pBtn);

	for (int i = 0; i < MAX_GER_STAR; i++) {
		CC_SAFE_RELEASE_NULL(m_pStar[i]);
	}
	m_pMenuCallOnceMore = NULL;
	MB_LayerRoleInfoHeader::setMenuEnable(true, "MB_LayerRewardOne");
}


MB_LayerRewardOne* MB_LayerRewardOne::createPet(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank){

	MB_LayerRewardOne* pNode = new MB_LayerRewardOne();
	if (pNode != NULL && pNode->initPet(type, typeID, num, rank)) {
		pNode->autorelease();
		return pNode;
	}
	delete pNode;
	return NULL;

}


void MB_LayerRewardOne::openedCallBack(){
	if (m_ValueArray->count() == 0)
	{
		m_pNodeTutorial->setTag(tutorialTag);
	}
    if (m_nStar > 4) {
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_4Star).c_str());
    }
    else{
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_3Star).c_str());
    }
}
void MB_LayerRewardOne::onExit(){
	if (m_pAnimation) {
		m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
	}
	MB_ResWindow::onExit();
}
MB_LayerRewardOne* MB_LayerRewardOne::createTen(CCArray* valueArray, uint8_t type)
{
	MB_LayerRewardOne* pNode = new MB_LayerRewardOne();
	if (pNode != NULL && pNode->initTen(valueArray, type))
	{
		pNode->autorelease();
		return pNode;
	}
	delete pNode;
	return NULL;
}
MB_LayerRewardOne* MB_LayerRewardOne::createItem(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{

	MB_LayerRewardOne* pNode = new MB_LayerRewardOne();
	if (pNode != NULL && pNode->initItem(type, typeID, num, rank)) {
		pNode->autorelease();
		return pNode;
	}
	delete pNode;
	return NULL;
}

bool MB_LayerRewardOne::initItem(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{

	addChild(NSGameHelper::createDisableTouchLayer());
	setType(type);
	setTypeID(typeID);
	setNum(num);
	setRank(rank);

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/reward_layer_one_eff1.ccbi", this);
	addChild(pNode);
	m_pAnimation = pCCBReader->getAnimationManager();
	CC_SAFE_RETAIN(m_pAnimation);
	CC_SAFE_RELEASE_NULL(pCCBReader);
	onResetWnd();
	return true;
}

void MB_LayerRewardOne::onEnterTransitionDidFinish()
{
	MB_ResWindow::onEnterTransitionDidFinish();
}

MB_LayerRewardOne* MB_LayerRewardOne::create(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{
	MB_LayerRewardOne* pNode = new MB_LayerRewardOne();
	if (pNode != NULL && pNode->init(type, typeID, num, rank)) {
		pNode->autorelease();
		return pNode;
	}
	delete pNode;
	return NULL;
}

bool MB_LayerRewardOne::init(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{
	addChild(NSGameHelper::createDisableTouchLayer());
	setType(type);
	setTypeID(typeID);
	setNum(num);
	setRank(rank);
	isReward = true;
	CCNode *pNode = loadResource("res/reward_layer_one.ccbi");
	addChild(pNode);

	onResetWnd();

	return true;
}


bool MB_LayerRewardOne::initTen(CCArray* valueArray, uint8_t type)
{
	addChild(NSGameHelper::createDisableTouchLayer());
	setType(type);
	//这里会retain,外面的array自行管理不影响
	m_ValueArray->addObjectsFromArray(valueArray);

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/reward_layer_one_eff1.ccbi", this);
	addChild(pNode);
	m_pAnimation = pCCBReader->getAnimationManager();
	CC_SAFE_RETAIN(m_pAnimation);
	for (int i = 0; i < MAX_GER_STAR; ++i)
	{
		starPt_lro[i] = m_pStar[i]->getPosition();
	}
	m_pBg2->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(.8f, .9f), CCScaleTo::create(.8f, 1), NULL)));
	RewardTempleteValue* rewardTemplete = (RewardTempleteValue*)m_ValueArray->objectAtIndex(index);
	setTypeID(rewardTemplete->getValueID());
	isSet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MB_VideoMgr::getInstance()->playVideo(this, -1);
#else
	toPlayAnimation();
#endif
	runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(MB_LayerRewardOne::setProp)), NULL));

	m_pOnceMore->removeFromParent();
	m_pCommit->setScale(0);
	m_pTenthMore->setScale(0);

	CC_SAFE_RELEASE_NULL(pCCBReader);
	return true;
}
bool MB_LayerRewardOne::initTenAgain(CCArray* valueArray, uint8_t type)
{
	index = 0;
	m_pNodeCard->setVisible(true);
	m_pCommit->setVisible(false);
	m_pTenthMore->setVisible(false);
	m_pVisibleNode2->setVisible(false);
	m_pTTFName->setVisible(true);
	m_pCommit->setScale(0);
	m_pTenthMore->setScale(0);
    m_pNext->setScale(1);
    m_pPass->setScale(1);
	isOnlyShow = true;
	setType(type);
	//这里会retain,外面的array自行管理不影响
	m_ValueArray->addObjectsFromArray(valueArray);
	RewardTempleteValue* rewardTemplete = (RewardTempleteValue*)m_ValueArray->objectAtIndex(index);
	setTypeID(rewardTemplete->getValueID());
	isSet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MB_VideoMgr::getInstance()->playVideo(this, -1);
#else
	toPlayAnimation();
#endif
	runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(MB_LayerRewardOne::setProp)), NULL));
	return true;
}
bool MB_LayerRewardOne::initPet(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{
	addChild(NSGameHelper::createDisableTouchLayer());
	setType(type);
	setTypeID(typeID);
	setNum(num);
	setRank(rank);
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/reward_layer_one_eff1.ccbi", this);
	addChild(pNode);
	m_pAnimation = pCCBReader->getAnimationManager();
	CC_SAFE_RETAIN(m_pAnimation);
	CC_SAFE_RELEASE_NULL(pCCBReader);
	m_pPass->removeFromParent();
	m_pVisibleNode2->removeFromParent();
	m_pTenthMore->removeFromParent();
	m_pNext->removeFromParent();
	m_pPass->removeFromParent();

	m_pBg2->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(.8f, .9f), CCScaleTo::create(.8f, 1), NULL)));
	for (int i = 0; i < MAX_GER_STAR; ++i)
	{
		starPt_lro[i] = m_pStar[i]->getPosition();
	}
	isSet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MB_VideoMgr::getInstance()->playVideo(this, -1);
#else
	toPlayAnimation();
#endif
	runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(MB_LayerRewardOne::setProp)), NULL));

	return true;
}

void MB_LayerRewardOne::initPetAgain(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank)
{
	m_pCommit->setVisible(false);
	m_pOnceMore->setVisible(false);
	setType(type);
	setTypeID(typeID);
	setNum(num);
	setRank(rank);
	isOnlyShow = true;
	isSet = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MB_VideoMgr::getInstance()->playVideo(this, -1);
#else
	toPlayAnimation();
#endif
	runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(MB_LayerRewardOne::setProp)), NULL));
}
void MB_LayerRewardOne::toPlayAnimation()
{
	setProp();//如果已经set过则会跳过
	m_pAnimation->runAnimationsForSequenceNamed("show");
	m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerRewardOne::openedCallBack));
}

bool MB_LayerRewardOne::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	if (isReward) {
		TutorialAssignLayerWindow
	}
	else{
		if (pTarget == this && 0 == strcmp(pMemberVariableName, ("tutorial"))) {
			CCNode* pOldVar = m_pNodeTutorial;
			m_pNodeTutorial = dynamic_cast<CCNode*>(pNode);
			CC_ASSERT(m_pNodeTutorial);
			if (pOldVar != m_pNodeTutorial) {
				CC_SAFE_RELEASE(pOldVar);
				m_pNodeTutorial->retain();
			}

			m_pNodeTutorial->setZOrder(100);
			m_pTutorialNodeArray->addObject(m_pNodeTutorial);
			//TODODO 直接跳过引导
            m_bTutorial = true;
			tutorialTag = m_pNodeTutorial->getTag();
			m_pNodeTutorial->setTag(-1);
			return true;
		}
	}

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "card", CCNode*, m_pNodeCard);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCommit", CCNode*, m_pCommit);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pOnceMore", CCNode*, m_pOnceMore);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTenthMore", CCNode*, m_pTenthMore);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPass", CCNode*, m_pPass);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVisibleNode2", CCNode*, m_pVisibleNode2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCSprite*, m_pBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg2", CCSprite*, m_pBg2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", CCLabelTTF*, m_pTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayerColor*, m_pLayerBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNext", CCNode*, m_pNext);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtn", CCControlButton*, m_pBtn);
	
	char tempName[32];
	sprintf(tempName, "icon0");
	for (int i = 0; i < REWARD_TEN_COUNT; i++)
	{
		CCB_MEMBERVARIABLEASSIGNER_GLUE(this, tempName, CCNode*, m_pNodeIcon[i]);
		tempName[4] += 1;
	}
	char strStar[] = "m_pStar1";
	for (int i = 0; i < MAX_GER_STAR; i++) {
		strStar[7] = '1' + i;
		CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strStar, CCSprite*, m_pStar[i]);
	}
	return true;
}

SEL_MenuHandler MB_LayerRewardOne::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MB_LayerRewardOne::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerRewardOne::onCommitClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOnceMoreClicked", MB_LayerRewardOne::onOnceMoreClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTenthMoreClicked", MB_LayerRewardOne::onTenthMoreClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNextClicked", MB_LayerRewardOne::onNextClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPassClicked", MB_LayerRewardOne::onPassClicked);

	return NULL;
}

void MB_LayerRewardOne::onOnceMoreClicked(CCObject* pSender)
{
	if (m_pTarget && m_pMenuCallOnceMore)
	{
		(m_pTarget->*m_pMenuCallOnceMore)(this);
	}
	//    removeFromParent();
}
void MB_LayerRewardOne::onTenthMoreClicked(CCObject* pSender)
{
	if (m_pTarget && m_pMenuCallOnceMore)
	{
		(m_pTarget->*m_pMenuCallOnceMore)(this);
	}
	//    popWindow();
}

void MB_LayerRewardOne::onResetWnd()
{
	if (m_uType == kRewardValueTypeItem)
	{
		MB_NodeItem* pNode = MB_NodeItem::create(m_uTypeID);
		m_pNodeCard->addChild(pNode);
	}
	else if (isReward){
        MB_NodePet* pNode = MB_NodePet::create(m_uTypeID);
        m_pNodeCard->addChild(pNode);
	}
	else
	{
		MB_LOG("unkown type: %d, typeId: %d", m_uType, m_uTypeID);
	}

}

void MB_LayerRewardOne::setProp()
{
	if (isSet)
	{
		return;
	}
	isSet = true;
	m_pLayerBg->setOpacity(255);
	m_pNodeCard->removeAllChildren();
	MB_NodePetCard* pNode = MB_NodePetCard::create(m_uTypeID, 0);
	m_pNodeCard->addChild(pNode);

	char* name = new char[64];
	MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(m_uTypeID);
	m_nStar = petTemplete->getPetStar();
	CCTexture2D *textrue;
	CCSpriteFrame* frame;
	if (m_nStar > 4) {
		textrue = CCTextureCache::sharedTextureCache()->addImage("bg/bg_chouka_violet.png");
		frame = CCSpriteFrame::createWithTexture(textrue, CCRect(0, 0, textrue->getContentSize().width, textrue->getContentSize().height));
		m_pBg->setDisplayFrame(frame);
		textrue = CCTextureCache::sharedTextureCache()->addImage("bg/efx_light_violet.png");
		frame = CCSpriteFrame::createWithTexture(textrue, CCRect(0, 0, textrue->getContentSize().width, textrue->getContentSize().height));
		m_pBg2->setDisplayFrame(frame);
	}
	else{
		textrue = CCTextureCache::sharedTextureCache()->addImage("bg/bg_chouka_yellow.png");
		frame = CCSpriteFrame::createWithTexture(textrue, CCRect(0, 0, textrue->getContentSize().width, textrue->getContentSize().height));
		m_pBg->setDisplayFrame(frame);
		textrue = CCTextureCache::sharedTextureCache()->addImage("bg/efx_light_yellow.png");
		frame = CCSpriteFrame::createWithTexture(textrue, CCRect(0, 0, textrue->getContentSize().width, textrue->getContentSize().height));
		m_pBg2->setDisplayFrame(frame);
	}
	sprintf(name, "%s", petTemplete->getPetName(NSGameHelper::getShapeTypeByRank(getRank())));
	m_pTTFName->setString(name);
	for (int i = 0; i < MAX_GER_STAR; ++i)
	{
		m_pStar[i]->setPosition(starPt_lro[i]);
	}
	NSGameHelper::centerStars(m_pStar, MAX_GER_STAR, m_nStar);
}
void  MB_LayerRewardOne::setTarget(CCObject *target, SEL_MenuHandler callback, SEL_MenuHandler onceMore){

	m_pTarget = target;
	m_pMenuCall = callback;
	m_pMenuCallOnceMore = onceMore;
}

void MB_LayerRewardOne::onCommitClicked(cocos2d::CCObject *pSender)
{
    TutorialTriggerComplete
	if (MB_TutorialMgr::getInstance()->getHasTutorialDilog())
	{
		MB_TutorialMgr::getInstance()->trigpetComplete();
	}
	if (m_pTarget && m_pMenuCall){

		(m_pTarget->*m_pMenuCall)(m_pTarget);
	}
	removeFromParent();
}
void MB_LayerRewardOne::onPassClicked(cocos2d::CCObject *pSender)
{
    m_pPass->setScale(0);
	m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
	for (int i = 0; i < m_ValueArray->count() && i < REWARD_TEN_COUNT; i++)
	{
        m_pNodeIcon[i]->removeAllChildren();
		RewardTempleteValue* rewardTemplete = (RewardTempleteValue*)m_ValueArray->objectAtIndex(i);
		if (rewardTemplete->getType() == kRewardValueTypePet)
		{
			MB_NodePet* pNode = MB_NodePet::create(rewardTemplete->getValueID());
			if (pNode != NULL)
			{
				m_pNodeIcon[i]->addChild(pNode);
                pNode->setNameColorBlack();
				pNode->showName(true);
			}
		}
		else
		{
			MB_LOG("unkown type:%d, valueID:%d", rewardTemplete->getType(), rewardTemplete->getValueID());
		}
	}

	m_pNext->setScale(0);
    m_pNext->setVisible(false);
	m_pNodeCard->setVisible(false);
	m_ValueArray->removeAllObjects();
	m_pCommit->setScale(1);
	m_pTenthMore->setScale(1);
	m_pVisibleNode2->setVisible(true);
	m_pTTFName->setVisible(false);
	for (int i = 0; i < MAX_GER_STAR; i++) {
		m_pStar[i]->setVisible(false);
	}
}



void MB_LayerRewardOne::onNextClicked(CCObject* pSender)
{
	if (++index == 10) {
		onPassClicked(NULL);
	}
	else
	{
		RewardTempleteValue* rewardTemplete = (RewardTempleteValue*)m_ValueArray->objectAtIndex(index);
		setTypeID(rewardTemplete->getValueID());
		MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(m_uTypeID);
		m_nStar = petTemplete->getPetStar();
		isSet = false;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//		runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(MB_LayerRewardOne::setProp)), NULL));
//		MB_VideoMgr::getInstance()->playVideo(this, m_nStar);
//#else
		toPlayAnimation();
//#endif
	}
}
void MB_LayerRewardOne::restTouch()
{
    addChild(NSGameHelper::createDisableTouchLayer());
    m_pBtn->setTouchEnabled(false);
    m_pBtn->setTouchEnabled(true);
}
