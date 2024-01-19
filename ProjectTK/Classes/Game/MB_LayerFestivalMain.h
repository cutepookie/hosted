//
//  MB_LayerFestivalMain.h
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#ifndef __ProjectMB__MB_LayerFestivalMain__
#define __ProjectMB__MB_LayerFestivalMain__

#include "MB_FunctionMainWnd.h"
class MB_FunctionFestival;
class MB_LayerFestivalMain : public MB_FunctionMainWnd
{
public:
	MB_LayerFestivalMain();
	virtual ~MB_LayerFestivalMain();
	virtual void onResetWnd();
	virtual bool init();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
protected:
    void onBoxClicked(CCObject* pSender);
    void onJoinOneTimeClicked(CCObject* pSender);
    void onJoinTenTimesClicked(CCObject* pSender);
    void onRuleClicked(CCObject* pSender);
    void onRankClicked(CCObject* pSender);
    void onChargeClicked(CCObject* pSender);
    void onInitialized();
    void recv_festival_click(MB_MsgBuffer* pRecv);
    void goCharge(CCObject* pSender);
    void onCloseClick(CCObject* pSender);
private:
    MB_FunctionFestival*    m_pFunction;
    CCNode*     m_pNodeDes;
    CCLabelTTF*	m_pJoinTimes;
    CCNode*	m_pNodeUnActiviteAll;
    CCLabelTTF*	m_pLeftJoinTimes;
    CCNode*	m_pNodeShouldReceiveAll;
    CCNode*	m_pNodeReceivedAll;
    CCNode*	m_pNodeFreeTimes;
    CCLabelTTF*	m_pLabelFreeTimes;
    CCNode*	m_pNodeUnFreeTimes;
    CCLabelTTF*	m_pLabelPriceByOnce;
    CCLabelTTF*	m_pLabelPriceByTenTimes;
    CCLabelTTF* m_pEventName;
    CCLabelTTF* m_pEventName1;
    CCMenuItemImage* m_pMenuImageBox;
};
#endif /* defined(__ProjectMB__MB_LayerFestivalMain__) */
