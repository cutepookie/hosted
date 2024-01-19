//
//  MB_LayerRechargeItemList.h
//  ProjectPM
//
//  Created by WenYong on 14-6-6.
//
//

#ifndef __ProjectMB__MB_LayerRechargeItemList__
#define __ProjectMB__MB_LayerRechargeItemList__

#include "MB_LayerItemList.h"

class MB_LayerRechargeItemList : public MB_LayerItemList,public CCTableViewDataSource
{
public:
    CREATE_FUNC(MB_LayerRechargeItemList);
    MB_LayerRechargeItemList();
    ~MB_LayerRechargeItemList();
    virtual void onResetWnd();
    virtual bool init();
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
    CCTableView* m_pTableView;
    CCSize       m_CellSize;
};

#endif /* defined(__ProjectMB__MB_LayerRechargeItemList__) */
