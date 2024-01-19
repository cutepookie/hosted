//
//  MB_LayerTaskMain.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_LayerTaskMain__
#define __ProjectMB__MB_LayerTaskMain__

#include "MB_FunctionMainWnd.h"
class MB_MsgBuffer;
class MB_LayerTaskMain:public MB_FunctionMainWnd,
public CCTableViewDataSource
{
public:
    
    MB_LayerTaskMain();
    ~MB_LayerTaskMain();
    virtual void onResetWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool init();
    CREATE_FUNC(MB_LayerTaskMain);

    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onStatusClicked(uint8_t nOperatType,uint32_t nTaskId);
protected:
    virtual void onCloseClicked(CCObject* pSender);
    
    void recvtask_operate(MB_MsgBuffer* recvPacket);
    void recvtask_error(MB_MsgBuffer* recvPacket);
    
    
    void updateCell(uint32_t nTaskId);
private:
    CCNode*     m_pNodeTaskContainer;
    CCTableView*m_pTableView;
    uint32_t    m_nSelectType;
    CCSize      m_szUnitSize;
};
#endif /* defined(__ProjectMB__MB_LayerTaskMain__) */
