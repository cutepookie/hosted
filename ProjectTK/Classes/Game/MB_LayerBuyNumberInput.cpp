//
//  MB_LayerBuyNumberInput.cpp
//  ProjectMB
//
//  Create by chenhongkun on 1/12/2014.
//
//
#include "MB_LayerBuyNumberInput.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
MB_LayerBuyNumberInput* MB_LayerBuyNumberInput::create(BuyNumberInputDelegate* pDelegate)
{
    MB_LayerBuyNumberInput* pLayer = new MB_LayerBuyNumberInput();
    if (pLayer && pLayer->init()) {
        pLayer->autorelease();
        pLayer->setDelegate(pDelegate);
        return pLayer;
    }
    else
    {
        CC_SAFE_RELEASE_NULL(pLayer);
        return NULL;
    }
}

//int MB_LayerBuyNumberInput::m_nNum = 10;

MB_LayerBuyNumberInput::MB_LayerBuyNumberInput()
{
    m_pDelegate = NULL;
    m_pLabelCount = NULL;
    m_nNum = 10;
    m_bShowRoleInfoPanel = true;
}
MB_LayerBuyNumberInput::~MB_LayerBuyNumberInput()
{
    CC_SAFE_RELEASE_NULL(m_pLabelCount);
}
bool MB_LayerBuyNumberInput::init()
{
    CCNode* pNode = loadResource("res/shop_layer_money.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_LayerBuyNumberInput::onResetWnd()
{
    char buff[100];
    sprintf(buff, "%d",m_nNum);
    m_pLabelCount->setString(buff);
}


bool MB_LayerBuyNumberInput::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelCount", CCLabelBMFont*, m_pLabelCount);
    return false;
}
SEL_MenuHandler MB_LayerBuyNumberInput::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerBuyNumberInput::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onClickedAdd",MB_LayerBuyNumberInput::onClickedAdd);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onClickedSubtract",MB_LayerBuyNumberInput::onClickedSubtract);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onClickedSure",MB_LayerBuyNumberInput::onClickedSure);
	return NULL;
}
SEL_CCControlHandler MB_LayerBuyNumberInput::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerBuyNumberInput::onCloseClick(CCObject* pSender)
{
    popWindow();
}
void MB_LayerBuyNumberInput::onClickedAdd(CCObject* pSender)
{
    if(m_nNum<100)
    {
        m_nNum+=10;
        onResetWnd();
    }
}
void MB_LayerBuyNumberInput::onClickedSubtract(CCObject* pSender)
{
    if(m_nNum>10)
    {
        m_nNum-=10;
        onResetWnd();
    }
}
void MB_LayerBuyNumberInput::onClickedSure(CCObject* pSender)
{
    if(m_pDelegate)m_pDelegate->onNumberInputed(m_nNum);
    popWindow();
}
