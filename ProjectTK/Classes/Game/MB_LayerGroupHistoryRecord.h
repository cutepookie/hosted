//
//  MB_LayerGroupHistoryRecord.h
//  ProjectPM
//
//  Created by WenYong on 14-4-25.
//
//

#ifndef __ProjectMB__MB_LayerGroupHistoryRecord__
#define __ProjectMB__MB_LayerGroupHistoryRecord__

#include "MB_FunctionMainWnd.h"
#include "MB_PerfectRaceProtocol.h"

class MB_PerfectRaceInterface;
class MB_LayerGroupHistoryRecord:public MB_FunctionMainWnd
,public CCTableViewDataSource
,public CCTableViewDelegate
,public MB_RaceRecordDelegate
{
public:
    MB_LayerGroupHistoryRecord();
    ~MB_LayerGroupHistoryRecord();
    virtual bool init(int nGroup);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view){};
private:
    void onCloseClicked(CCObject* pSender);
    void selectGroup(int nGroupId);
    void recvrace_history(MB_MsgBuffer* pRecv);
private:
    MB_PerfectRaceInterface* m_pPerfectRaceInterface;
    CCNode*         m_pContainer;
    CCTableView*    m_pTableView;
    CCSize          m_CellSize;
    int             m_bRequest;
    int             m_nLastTouched;
    int             m_nShowCount;
    int             m_nGroupId;
    int             m_nStartRecord;
    int             m_nEndRecord;
    int             m_nCurrentRound;
    CCArray*        m_pGroupRecord;
    CCLabelTTF*     m_pGrouptitle;
    CCLabelTTF*     m_pResultLabel;
};
#endif /* defined(__ProjectMB__MB_LayerGroupHistoryRecord__) */
