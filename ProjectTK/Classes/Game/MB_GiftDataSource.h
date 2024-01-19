//
//  MB_GiftDataSource.h
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#ifndef __ProjectMB__MB_GiftDataSource__
#define __ProjectMB__MB_GiftDataSource__

#include "CCTableView.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_GiftsInterface;

//等級
class MB_GiftLevelDataSource:public CCTableViewDataSource
{
public:
    MB_GiftLevelDataSource(MB_GiftsInterface* pInterface);
    virtual ~MB_GiftLevelDataSource();
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    void sortData();
protected:
    MB_GiftLevelDataSource(){};
    CCArray*    m_pDatas;
};

//在线時間
class MB_GiftTimeDataSource:public MB_GiftLevelDataSource
{
public:
    MB_GiftTimeDataSource(MB_GiftsInterface*);
    void sortData();
//    static bool less(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1);
};

//連续登入
class MB_GiftMLoginDataSource:public MB_GiftLevelDataSource
{
public:
    MB_GiftMLoginDataSource(MB_GiftsInterface*);
};

#endif /* defined(__ProjectMB__MB_GiftDataSource__) */
