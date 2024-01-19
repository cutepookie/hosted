
#include "MB_LayerTutorial.h"

USING_NS_CC;
USING_NS_CC_EXT;
MB_LayerTutorial::MB_LayerTutorial()
{
    m_pMenu = NULL;
    m_pButtonSkip = NULL;
    m_pSkipLayer = NULL;
    pTargetNode = NULL;
}

MB_LayerTutorial::~MB_LayerTutorial()
{
    unscheduleAllSelectors();
    CC_SAFE_RELEASE_NULL(m_pMenu);
    CC_SAFE_RELEASE(m_pButtonSkip);
    CC_SAFE_RELEASE_NULL(pTargetNode);
}

MB_LayerTutorial* MB_LayerTutorial::create(cocos2d::CCNode *pNode)
{
    MB_LayerTutorial* layer = new MB_LayerTutorial();
    if (layer != NULL && layer->init(pNode)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}



bool MB_LayerTutorial::init(CCNode* pNode)
{
	if ( !CCLayer::init() )return false;
    CC_SAFE_RELEASE_NULL(pTargetNode);
    pTargetNode = pNode;
    CC_SAFE_RETAIN(pTargetNode);
    CCNode* obj = loadResource("res/tutorial_node_position.ccbi");
    this->addChild(obj);
    
    CCPoint ptarget = pNode->getParent()->convertToWorldSpace(pNode->getPosition());
    obj->setPosition(obj->getParent()->convertToNodeSpace(ptarget));
    
    m_pMenu->setTouchPriority(kCCMenuHandlerPriorityTutorial);
    m_pSkipLayer = loadResource("res/tutorial_node_skip.ccbi");
    m_pSkipLayer->setPosition(ccp(0,CCDirector::sharedDirector()->getVisibleSize().height + CCDirector::sharedDirector()->getVisibleOrigin().y));
    this->addChild(m_pSkipLayer);
    
    m_pButtonSkip->setTouchPriority(kCCMenuHandlerPriorityTutorial);
    
    this->setContentSize(CCDirector::sharedDirector()->getVisibleSize());
    this->setPosition(CCDirector::sharedDirector()->getVisibleOrigin());
    return true;
    
}

bool MB_LayerTutorial::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu", CCMenu*, m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "skipbutton", CCControlButton*, m_pButtonSkip);
    return true;
}

SEL_MenuHandler MB_LayerTutorial::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_LayerTutorial::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(pTarget, "onSkipClicked", MB_LayerTutorial::onSkipClicked);
    return NULL;
}

void MB_LayerTutorial::onSkipClicked(cocos2d::CCObject *pSender)
{
    MB_TutorialMgr::getInstance()->skipTutorial();
}

