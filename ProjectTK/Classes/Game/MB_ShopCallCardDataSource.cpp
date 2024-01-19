//
//  MB_ShopCallCardDataSource.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#include "MB_NodeCallcardUnit.h"
#include "MB_ShopCallCardDataSource.h"
MB_ShopCallCardDataSource::MB_ShopCallCardDataSource()
{
}

MB_ShopCallCardDataSource::~MB_ShopCallCardDataSource()
{
    
}

CCSize MB_ShopCallCardDataSource::cellSizeForTable(CCTableView *table)
{
    return CCSize(640,330);
}

CCTableViewCell* MB_ShopCallCardDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }

    CCNode* pNode = MB_NodeCallcardUnit::create();
    cell->addChild(pNode);
    
    return cell;
}

unsigned int MB_ShopCallCardDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return 1;
}
