//
//  MB_RankingDataSource.h
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#ifndef __ProjectMB__MB_RankingDataSource__
#define __ProjectMB__MB_RankingDataSource__

#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_RankData;
class MB_RankDataSource : public CCTableViewDataSource
{
public:
    MB_RankDataSource();
    virtual ~MB_RankDataSource();
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void setDataArray(CCArray* pArray);
    virtual CCNode* createUnitByData(MB_RankData* pData)=0;
protected:
    CCSize  m_ItemSize;
    CCArray* m_pArray;
};

class MB_RankDataSourceLevel :  public MB_RankDataSource
{
public:
    virtual CCNode* createUnitByData(MB_RankData* pData);
};
class MB_RankDataSourcePower :  public MB_RankDataSource
{
public:
    virtual CCNode* createUnitByData(MB_RankData* pData);
};
class MB_RankDataSourceAbsolved :  public MB_RankDataSource
{
public:
    virtual CCNode* createUnitByData(MB_RankData* pData);
};
class MB_RankDataSourceArena :  public MB_RankDataSource
{
public:
    virtual CCNode* createUnitByData(MB_RankData* pData);
};
#endif /* defined(__ProjectMB__MB_RankingDataSource__) */
