//
//  MB_LayerRewardMoreCard.cpp
//  ProjectPM
//
//  Create by WenYong on 24/7/2014.
//
//
#include "MB_LayerRewardMoreCard.h"
#include "MB_NodeRewardCard.h"
#include "MB_LocalProto.h"
#include "MB_FunctionModule.h"

MB_LayerRewardMoreCard* MB_LayerRewardMoreCard::create(CCArray* pArray)
{
    MB_LayerRewardMoreCard* pNode = new MB_LayerRewardMoreCard;
    if (pNode && pNode->init())
    {
        pNode->autorelease();
        pNode->setRewardData(pArray);
        return pNode;
    }
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}
MB_LayerRewardMoreCard::MB_LayerRewardMoreCard()
{
    m_pRewardContainer	 = NULL;
    m_pScrollView = NULL;
}
MB_LayerRewardMoreCard::~MB_LayerRewardMoreCard()
{
    CC_SAFE_RELEASE_NULL(m_pRewardContainer);
    CC_SAFE_RELEASE_NULL(m_pScrollView);
}
bool MB_LayerRewardMoreCard::init()
{
    CCNode* pNode = loadResource("res/reward_layer_crit.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
        m_pScrollView = CCScrollView::create(m_pRewardContainer->getContentSize());
        m_pScrollView->retain();
        m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pRewardContainer->removeAllChildren();
        m_pRewardContainer->addChild(m_pScrollView);
		return true;
	}
	return false;
}
void MB_LayerRewardMoreCard::onResetWnd()
{

}
bool MB_LayerRewardMoreCard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRewardContainer",CCNode*,m_pRewardContainer);
	return false;
}
SEL_MenuHandler MB_LayerRewardMoreCard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_LayerRewardMoreCard::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCommitClicked",MB_LayerRewardMoreCard::onCommitClicked);
	return NULL;
}
void MB_LayerRewardMoreCard::onCommitClicked(CCObject* pSender)
{
    removeFromParent();
    TutorialTriggerComplete
}


void MB_LayerRewardMoreCard::setRewardData(CCArray* pArray)
{
    MB_LayerRewardCardContainer* pContainer = MB_LayerRewardCardContainer::create(pArray);
    if (pContainer)
    {
        pContainer->setContentSize(m_pRewardContainer->getContentSize());
        m_pScrollView->setContainer(pContainer);
    }
}

MB_LayerRewardCardContainer* MB_LayerRewardCardContainer::create(CCArray* pArray)
{
    MB_LayerRewardCardContainer* pInstance = new MB_LayerRewardCardContainer;
    if (pInstance && pInstance->init(pArray))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}
bool MB_LayerRewardCardContainer::init(CCArray* pArray)
{
    CCLayer::init();
    if(pArray==NULL || pArray->count() < 1)
    {
        return false;
    }
    
    setAnchorPoint(ccp(0.5,0.5));
    
    m_ItemSize = MB_NodeRewardCard::getNodeSize();
    
    MB_RewardDataDetail* pTemp = NULL;
    MB_NodeRewardCard* pItem = NULL;
    removeAllChildren();
    
    CCARRAY_FOREACH_4TYPE(pArray,MB_RewardDataDetail*,pTemp)
    {
        pItem = MB_NodeRewardCard::create(pTemp);
        if (pItem)
        {
            addChild(pItem);
        }
    }
    return true;
}
