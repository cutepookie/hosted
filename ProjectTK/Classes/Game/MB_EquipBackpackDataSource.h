//
//  MB_EquipBackpackDataSource.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#ifndef __ProjectMB__MB_EquipBackpackDataSource__
#define __ProjectMB__MB_EquipBackpackDataSource__
using namespace std;
#include "Game.h"
class MB_EquipBackpackDataSource:public CCTableViewDataSource
{
public:
    MB_EquipBackpackDataSource();
    ~MB_EquipBackpackDataSource();
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx) ;
    vector<int> isRunedIdx;
    bool isAllRun;
private:
    CCArray* m_pItemArray;
    CCSize m_szCell;
    int allCellCount;
};

#endif /* defined(__ProjectMB__MB_EquipBackpackDataSource__) */
