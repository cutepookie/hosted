//
//  MB_LayerRegistration.h
//  ProjectMB
//
//  Create by WenYong on 28/8/2014.
//
//
#ifndef __ProjectMB__MB_LayerRegistration__
#define __ProjectMB__MB_LayerRegistration__

#include "MB_FunctionMainWnd.h"

class MB_LayerRegistration :public MB_FunctionMainWnd,public CCTableViewDataSource
{
public:
    CREATE_FUNC(MB_LayerRegistration);
	MB_LayerRegistration();
	virtual ~MB_LayerRegistration();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    void updateClose(float dt);
protected:
    void onRequestReward(CCObject* pSender);
    void finish();
protected:
    void onCloseClick(CCObject* pSender);
private:
    CCNode*	tutorial;
    CCNode*	m_pCalendarContainer;
    CCNode*	m_pRewardContainer;
    CCControlButton*    m_pBtnRequest;
    uint8_t m_uIsGet;
//    CCScrollView*   m_pRewardView;
    CCTableView* m_pTableView;
    int m_uValue;
};
#endif /* defined(__ProjectMB__MB_LayerRegistration__) */
