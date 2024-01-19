//
//  MB_LayerFunctionRule.cpp
//  ProjectPM
//
//  Create by WenYong on 26/7/2014.
//
//
#include "MB_LayerFunctionRule.h"
#include "MB_FunctionRule.h"
#include "MB_FunctionModule.h"

MB_LayerFunctionRule* MB_LayerFunctionRule::create(int nType)
{
    MB_LayerFunctionRule* pInstance = new MB_LayerFunctionRule;
    if (pInstance && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setRuleType(nType);
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_LayerFunctionRule::MB_LayerFunctionRule()
{
    scale9sprite	 = NULL;
    m_pNodeRule	 = NULL;
}
MB_LayerFunctionRule::~MB_LayerFunctionRule()
{
    CC_SAFE_RELEASE_NULL(scale9sprite);
    CC_SAFE_RELEASE_NULL(m_pNodeRule);
}
bool MB_LayerFunctionRule::init()
{
    CCNode* pNode = loadResource("res/functiong_layer_rule.ccbi");
    if(pNode)
	{
        NSGameHelper::adjustScrollNode(m_pNodeRule);
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
		return true;
	}
	return false;
}
void MB_LayerFunctionRule::onResetWnd()
{

}
bool MB_LayerFunctionRule::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"scale9sprite",CCScale9Sprite*,scale9sprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRule",CCNode*,m_pNodeRule);
	return false;
}
SEL_MenuHandler MB_LayerFunctionRule::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerFunctionRule::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerFunctionRule::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerFunctionRule::onCloseClick(CCObject* pSender)
{
    popWindow();
}
void MB_LayerFunctionRule::setRuleType(int nType)
{
    CCSize sz = m_pNodeRule->getContentSize();
    sz.height = 0;
    CCNode* pNode = MB_FunctionRule::getInstance()->craeteRuleNodeByType(nType,sz);
    if (pNode)
    {
        m_pNodeRule->removeAllChildren();
        m_pNodeRule->addChild(pNode);
        pNode->setAnchorPoint(CCPointZero);
        pNode->setPosition(0, m_pNodeRule->getContentSize().height - pNode->getContentSize().height);
    }
}
