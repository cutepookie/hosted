//
//  MB_LayerAprCard.cpp
//  ProjectMB
//
//  Create by wenyong on 10/3/2015.
//
//
#include "MB_LayerAprCard.h"
#include "MB_FunctionAprCardInterface.h"
#include "MB_AprCardProtocol.h"

MB_LayerAprCard::MB_LayerAprCard()
{
    m_pTTFLastDay	 = NULL;
    m_pBtReceive	 = NULL;
    m_pBtGoBuy = NULL;
    SOCKET_MSG_REGIST(SC_ACTIVITY_MONTH, MB_LayerAprCard);
    SOCKET_MSG_REGIST(SC_ACTIVITY_MONTH_BUY, MB_LayerAprCard);
    SOCKET_MSG_REGIST(SC_ACTIVITT_MONTH_DRAW, MB_LayerAprCard);
}
MB_LayerAprCard::~MB_LayerAprCard()
{
    CC_SAFE_RELEASE_NULL(m_pTTFLastDay);
    CC_SAFE_RELEASE_NULL(m_pBtReceive);
    CC_SAFE_RELEASE_NULL(m_pBtGoBuy);
    
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_MONTH);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_MONTH_BUY);
    SOCKET_MSG_UNREGIST(SC_ACTIVITT_MONTH_DRAW);
}
bool MB_LayerAprCard::init()
{
    CCNode* pNode = loadResource("res/functiong_layer_yueka.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();
		return true;
	}
	return false;
}

void MB_LayerAprCard::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    
    dirty();
}
bool MB_LayerAprCard::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_FunctionAprCardInterface*>(pDataSource);
    return m_pInterface != NULL;
}
void MB_LayerAprCard::onResetWnd()
{
    MB_AprCardData* data = NULL;
    if (m_pInterface == NULL)
    {
        return;
    }
    data = m_pInterface->getAprCardData();
    if (data == NULL)
    {
        return;
    }

    
    char str[64] = "";
    sprintf(str,"%d",data->getLeftDay());
    m_pTTFLastDay->setString(str); //剩余天数
    
    //按钮
    m_pBtReceive->setEnabled(!data->getIsDraw());
    m_pBtGoBuy->setEnabled(data->getLeftDay() == 0);
    
}
bool MB_LayerAprCard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLastDay",CCLabelBMFont*,m_pTTFLastDay);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtReceive",CCControlButton*,m_pBtReceive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGoBuy",CCControlButton*,m_pBtGoBuy);
	return false;
}
SEL_MenuHandler MB_LayerAprCard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_LayerAprCard::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onGoChargeClicked",MB_LayerAprCard::onGoChargeClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBuyClicked",MB_LayerAprCard::onBuyClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onReceiveClicked",MB_LayerAprCard::onReceiveClicked);
	return NULL;
}
void MB_LayerAprCard::onGoChargeClicked(CCObject* pSender)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop ,&pInterface))
    {
        pInterface->onEntryClicked(this);
    }
}
void MB_LayerAprCard::onBuyClicked(CCObject* pSender)
{
    if (m_pInterface->getAprCardData()->getLeftDay() != 0) {
        MB_Message::sharedMB_Message()->showMessage("您的月卡还未过期，暂不能购买");
        return;
    }
//    if(m_pInterface->getAprCardData()->getNeedPayGold() > m_pInterface->getAprCardData()->getPayGold())
//    {
//        MB_Message::sharedMB_Message()->showMessage("未达到条件，不能购买");
//        return;
//    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pInterface->sendActivity_Month_Buy();
}
void MB_LayerAprCard::onReceiveClicked(CCObject* pSender)
{
    if (m_pInterface->getAprCardData()->getIsDraw()) {
        MB_Message::sharedMB_Message()->showMessage("今天已经领取过了");
        return;
    }
    if (m_pInterface->getAprCardData()->getLeftDay() == 0) {
        MB_Message::sharedMB_Message()->showMessage("您还未购买月卡或月卡已过期");
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pInterface->sendActivity_Month_Draw();
}
