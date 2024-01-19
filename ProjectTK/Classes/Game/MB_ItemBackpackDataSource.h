//
//  MB_ItemBackpackDataSource.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#ifndef __ProjectMB__MB_ItemBackpackDataSource__
#define __ProjectMB__MB_ItemBackpackDataSource__

#include "Game.h"
using namespace std;
class MB_ItemBackpackDataSource:public CCTableViewDataSource
{
public:
    MB_ItemBackpackDataSource();
    ~MB_ItemBackpackDataSource();
    
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

#endif /* defined(__ProjectMB__MB_ItemBackpackDataSource__) */
