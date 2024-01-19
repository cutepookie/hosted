//
//  MB_LayerGroupRecordLive.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//
// 小组直播界面
#ifndef __ProjectMB__MB_LayerGroupRecordLive__
#define __ProjectMB__MB_LayerGroupRecordLive__

#include "MB_FunctionMainWnd.h"
#include "MB_PerfectRaceProtocol.h"
class MB_PerfectRaceInterface;
class MB_LayerGroupRecordLive:public MB_FunctionMainWnd
,public CCTableViewDataSource
,public MB_RaceRecordDelegate
{
public:
    MB_LayerGroupRecordLive();
    ~MB_LayerGroupRecordLive();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
private:
    virtual void recvrace_new_fight(MB_MsgBuffer* pRecv);
    void onCloseClicked(CCObject* pSender);
protected:
    CCArray*        m_pLiveList;
    MB_PerfectRaceInterface* m_pPerfectRaceInterface;
    CCNode*         m_pContainer;
    CCSize          m_CellSize;
private:
    CCSprite*     m_pGroupLabel;
    CCTableView*    m_pTableView;
    CCLabelTTF*     m_pResultLabel;
    
    int m_nGroupID;
};
#endif /* defined(__ProjectMB__MB_LayerGroupRecordLive__) */
