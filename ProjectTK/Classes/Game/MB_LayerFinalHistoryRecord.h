//
//  MB_LayerFinalHistoryRecord.h
//  ProjectPM
//
//  Created by WenYong on 14-4-25.
//
//

#ifndef __ProjectMB__MB_LayerFinalHistoryRecord__
#define __ProjectMB__MB_LayerFinalHistoryRecord__
#include "MB_PerfectRaceProtocol.h"
#include "MB_FunctionMainWnd.h"
class MB_PerfectRaceInterface;
class MB_RaceRecord;
class MB_LayerFinalHistoryRecord:public MB_FunctionMainWnd
,public CCTableViewDataSource
,public MB_RaceRecordDelegate
{
public:
    MB_LayerFinalHistoryRecord();
    ~MB_LayerFinalHistoryRecord();
    virtual bool init(MB_RaceRecord* pRaceRecord);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
protected:
    void recvrace_new_fight(MB_MsgBuffer* pRecv);
private:
    void onCloseClicked(CCObject* pSender);
private:
    MB_RaceRecord*      m_pRaceRecord;
    MB_PerfectRaceInterface* m_pPerfectRaceInterface;
    CCLabelTTF*     m_pAtkName;
    CCLabelTTF*     m_pDefName;
    CCLabelTTF*     m_pAtkScore;
    CCLabelTTF*     m_pDefScore;
    CCTableView*    m_pTableView;
    CCNode*         m_pContainer;
    CCSize          m_CellSize;
    int             m_nPos;
    CCArray*        m_pLivingData;
};

#endif /* defined(__ProjectMB__MB_LayerFinalHistoryRecord__) */
