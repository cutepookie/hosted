//
//  MB_LayerFestivalRank.h
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#ifndef __ProjectMB__MB_LayerFestivalRank__
#define __ProjectMB__MB_LayerFestivalRank__

#include "MB_FunctionMainWnd.h"
class MB_NodeFestivalRank;
class MB_FunctionFestival;
class MB_LayerFestivalRank : public MB_FunctionMainWnd,public CCTableViewDataSource
{
public:
	MB_LayerFestivalRank();
	virtual ~MB_LayerFestivalRank();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
protected:
    void onInitialized();
    void onCloseClicked(CCObject* pSender);
    CCNode* createCellByIndex(int idx);
    virtual void updateCellNode(int idx,MB_NodeFestivalRank* pNode);
private:
    CCTableView*    m_pTableView;
    float m_fContainerHeight;
    CCNode*	m_pNodePower;
    CCLabelTTF*	m_pLabelJoinTimes;
    CCLabelTTF*	m_pLabelRank;
    CCNode*	m_pContainer;
    CCLabelTTF* m_pLabelUpRankTimes;
    CCSize  m_CellSize;
    CCArray*    m_pRankArray;
    MB_FunctionFestival* m_pFunction;
    bool   m_bRequestData;
};
#endif /* defined(__ProjectMB__MB_LayerFestivalRank__) */