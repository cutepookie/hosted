//
//  MB_LayerAprCard.h
//  ProjectMB
//
//  Create by wenyong on 10/3/2015.
//
//
#ifndef __ProjectMB__MB_LayerAprCard__
#define __ProjectMB__MB_LayerAprCard__


#include "MB_FunctionModule.h"

class MB_FunctionAprCardInterface;
class MB_LayerAprCard : public MB_FunctionMainWnd
{
public:
	MB_LayerAprCard();
	virtual ~MB_LayerAprCard();
	virtual void onResetWnd();
	virtual bool init();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    bool setDataSource(CCFunctionDataSource* pDataSource);
    void onBuyClicked(CCObject* pSender);
protected:
    void onGoChargeClicked(CCObject* pSender);

    void onReceiveClicked(CCObject* pSender);
private:
    CCLabelBMFont*	m_pTTFLastDay;
    CCControlButton*	m_pBtReceive;
    CCControlButton*    m_pBtGoBuy;
    MB_FunctionAprCardInterface* m_pInterface;
};
#endif /* defined(__ProjectMB__MB_LayerAprCard__) */
