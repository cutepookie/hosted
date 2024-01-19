//
//  MB_LayerGroupPlayerList.h
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#ifndef __ProjectMB__MB_LayerGroupPlayerList__
#define __ProjectMB__MB_LayerGroupPlayerList__

#include "MB_FunctionMainWnd.h"
class MB_PerfectRaceInterface;
class MB_LayerGroupPlayerList:public MB_FunctionMainWnd
,public CCTableViewDataSource
{
public:
    MB_LayerGroupPlayerList();
    ~MB_LayerGroupPlayerList();
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual bool init(int nGroup);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);

protected:
    void onPreRecordClicked(CCObject* pSender);
    void onRuleClicked(CCObject* pSender);
    void onGroupRecordClicked(CCObject* pSender);
    virtual void requestPlayerList(int nGroup);
    virtual void recvrace_fight_list(MB_MsgBuffer* pRecv);
    void onCloseClicked(CCObject* pSender);
    void onViewRaceRecord(CCObject* pSender);
private:
    MB_PerfectRaceInterface*        m_pPerfectRaceInterface;
    CCTableView*                    m_pTableView;
    int m_nGroupId;
    CCArray*        m_pDataList;
    CCSize          m_CellSize;
    CCControlButton*    m_pBtnVeiwRecord;
    CCNode*         m_pContainer;
    CCLabelTTF*     m_pGroupTitle;
};

#endif /* defined(__ProjectMB__MB_LayerGroupPlayerList__) */
