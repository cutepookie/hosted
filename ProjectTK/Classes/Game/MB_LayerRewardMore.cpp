
#include "MB_LayerRewardMore.h"
#include "MB_NodeItemBook.h"
#include "MB_LayerChatMain.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LayerRewardMore::MB_LayerRewardMore()
{
//    for (int i = 0; i < REWARD_MORE_COUNT; i++) {
//        m_pNodeIcon[i] = NULL;
//        m_pNode[i] = NULL;
//        m_pTTFName[i] = NULL;
//    }
    m_ValueArray = new CCArray();
    m_pTarget = NULL;
    m_pScrollView = NULL;
    m_pNodeScroll = NULL;
    m_pBtn = NULL;
    m_bShowRoleInfoPanel = true;
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerRewardMore");
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerRewardMore");
}

MB_LayerRewardMore::~MB_LayerRewardMore()
{
//    for (int i = 0; i < REWARD_MORE_COUNT; i++) {
//        CC_SAFE_RELEASE(m_pNode[i]);
//        CC_SAFE_RELEASE(m_pNodeIcon[i]);
//        CC_SAFE_RELEASE(m_pTTFName[i]);
//    }
    CC_SAFE_RELEASE_NULL(m_pNodeScroll);
    CC_SAFE_RELEASE(m_ValueArray);
    CC_SAFE_RELEASE_NULL(m_pBtn);
    
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerRewardMore");
//    MB_LayerChatMain::SetChatMainVisible(true, "MB_LayerRewardMore");
}

MB_LayerRewardMore* MB_LayerRewardMore::create(CCArray* valueArray)
{
    MB_LayerRewardMore* pNode = new MB_LayerRewardMore();
    if (pNode != NULL && pNode->init(valueArray)) {
        pNode->autorelease();
        return pNode;
    }
    delete pNode;
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerRewardMore::init(CCArray* valueArray)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    //这里会retain,外面的array自行管理不影响
    m_ValueArray->addObjectsFromArray(valueArray);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/reward_layer_more.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    onResetWnd();
    
	return true;
}
void MB_LayerRewardMore::setCallBack(CCObject *target,SEL_MenuHandler callback){

    m_pTarget = target;
    m_pCallBack = callback;
}

bool MB_LayerRewardMore::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroll", CCNode*, m_pNodeScroll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtn", CCControlButton*, m_pBtn);
    
    return true;
}

SEL_MenuHandler MB_LayerRewardMore::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_LayerRewardMore::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerRewardMore::onCommitClicked);
    
    return NULL;
}

void MB_LayerRewardMore::onResetWnd()
{
    if (m_ValueArray->count() < 1)
    {
        return;
    }
    if(m_pScrollView != NULL)
    {
        m_pScrollView->removeFromParent();
    }


    m_pScrollView = CCScrollView::create(m_pNodeScroll->getContentSize());
    m_pScrollView->setSwaller(false);
    m_pNodeScroll->addChild(m_pScrollView);
    m_pScrollView->setAnchorPoint(CCPoint(0.5,0.5));
    MB_LayerRewardContainer* ItemContainer = MB_LayerRewardContainer::create(m_ValueArray);
    CCSize sz = m_pNodeScroll->getContentSize();
    if (sz.width<ItemContainer->getContentSize().width)
    {
        sz.width = ItemContainer->getContentSize().width;
    }
    ItemContainer->setContentSize(sz);
    m_pScrollView->setContainer(ItemContainer);
    m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
}

void MB_LayerRewardMore::onCommitClicked(cocos2d::CCObject *pSender)
{
    TutorialTriggerComplete
    
    MB_LOG("onCommitClicked");
    if (m_pTarget) {
        
        (m_pTarget->*m_pCallBack)(pSender);
    }
    popWindow();
}

MB_LayerRewardMore* MB_LayerRewardMore::createWithRewardLayer(MB_LayerRewardContainer* pLayer)
{
    MB_LayerRewardMore* pInstance = new MB_LayerRewardMore;
    
    if (pInstance && pInstance->initWithRewardLayer(pLayer))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

bool MB_LayerRewardMore::initWithRewardLayer(MB_LayerRewardContainer* pLayer)
{
    if (pLayer == NULL)
    {
        return false;
    }
    this->addChild(NSGameHelper::createDisableTouchLayer());
    CCNode* node = loadResource("res/reward_layer_more.ccbi");
    if (node)
    {
        addChild(node);
        CC_SAFE_RELEASE_NULL(m_pScrollView);
        m_pScrollView = CCScrollView::create(m_pNodeScroll->getContentSize());
        m_pScrollView->setSwaller(false);
        m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pNodeScroll->removeAllChildren();
        m_pNodeScroll->addChild(m_pScrollView);
        pLayer->setContentSize(m_pNodeScroll->getContentSize());
        m_pScrollView->setContainer(pLayer);
        return true;
    }
    return false;
}

void MB_LayerRewardMore::onEnterTransitionDidFinish()
{
    MB_ResWindow::onEnterTransitionDidFinish();
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Reward).c_str());
}


MB_LayerRewardMore2::MB_LayerRewardMore2()
{
    
}
MB_LayerRewardMore2::~MB_LayerRewardMore2()
{
    
}
MB_LayerRewardMore2* MB_LayerRewardMore2::create(CCArray* valueArray)
{
    MB_LayerRewardMore2* pNode = new MB_LayerRewardMore2();
    if (pNode != NULL && pNode->init(valueArray)) {
        pNode->autorelease();
        return pNode;
    }
    delete pNode;
    return NULL;
}

bool MB_LayerRewardMore2::init(CCArray* valueArray)
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
    //这里会retain,外面的array自行管理不影响
    m_ValueArray->addObjectsFromArray(valueArray);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/reward_layer_more2.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    onResetWnd();
    
	return true;
}

void MB_LayerRewardMore2::onResetWnd()
{
    if (m_ValueArray->count() < 1)
    {
        return;
    }

    CC_SAFE_RELEASE_NULL(m_pScrollView);
    m_pScrollView = CCScrollView::create(m_pNodeScroll->getContentSize());
    m_pScrollView->setSwaller(false);
    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    m_pScrollView->setAnchorPoint(ccp(0.5,0.5));
    m_pNodeScroll->addChild(m_pScrollView);
    MB_LayerRewardContainerEx* layer = MB_LayerRewardContainerEx::create(m_ValueArray);
    m_pScrollView->setContainer(layer);
    layer->setCenter(m_pNodeScroll->getContentSize());
    m_pScrollView->setContentOffset(ccp(0,m_pNodeScroll->getContentSize().height - layer->getContentSize().height));
}
	
bool MB_LayerRewardMore2::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return MB_LayerRewardMore::onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
}
SEL_MenuHandler MB_LayerRewardMore2::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return MB_LayerRewardMore::onResolveCCBCCMenuItemSelector(pTarget,pSelectorName);
}
SEL_CCControlHandler MB_LayerRewardMore2::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return MB_LayerRewardMore::onResolveCCBCCControlSelector(pTarget,pSelectorName);
}
void MB_LayerRewardMore2::restTouch()
{
    addChild(NSGameHelper::createDisableTouchLayer());
    m_pBtn->setTouchEnabled(false);
    m_pBtn->setTouchEnabled(true);
}
