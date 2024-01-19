//
//  MB_ItemDebrisDataSource.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-23.
//
//

#ifndef __ProjectMB__MB_ItemDebrisDataSource__
#define __ProjectMB__MB_ItemDebrisDataSource__

#include "Game.h"
using namespace std;
class MB_ItemDebrisDataSource :public CCTableViewDataSource
{
public:
	MB_ItemDebrisDataSource();
	~MB_ItemDebrisDataSource();

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
#endif /* defined(__ProjectMB__MB_ItemDebrisDataSource__) */
