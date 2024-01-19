//
//  MB_ShopCallCardDataSource.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#ifndef __ProjectMB__MB_ShopCallCardDataSource__
#define __ProjectMB__MB_ShopCallCardDataSource__

#include "Game.h"
class MB_ShopCallCardDataSource:public CCTableViewDataSource
{
public:
    MB_ShopCallCardDataSource();
    ~MB_ShopCallCardDataSource();
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

#endif /* defined(__ProjectMB__MB_ShopCallCardDataSource__) */
