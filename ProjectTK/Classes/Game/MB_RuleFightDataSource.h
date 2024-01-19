//
//  MB_RuleFightDataSource.h
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#ifndef __ProjectMB__MB_RuleFightDataSource__
#define __ProjectMB__MB_RuleFightDataSource__

#include "CCTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_RuleFightInterface;

class MB_RuleFightDataSource:public CCTableViewDataSource
{
public:
    MB_RuleFightDataSource(MB_RuleFightInterface* pInterface);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
protected:
    CCArray*    m_pDatas;
};


class MB_RuleRankDataSource:public CCTableViewDataSource
{
public:
    MB_RuleRankDataSource(MB_RuleFightInterface* pInterface);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
protected:
    CCArray*    m_pDatas;
};


class MB_LastWeekRankDataSource:public CCTableViewDataSource
{
public:
    MB_LastWeekRankDataSource(MB_RuleFightInterface* pInterface);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
protected:
    CCArray*    m_pDatas;
};


#endif /* defined(__ProjectMB__MB_RuleFightDataSource__) */
