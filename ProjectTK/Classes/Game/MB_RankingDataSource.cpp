//
//  MB_RankingDataSource.cpp
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#include "MB_RankingDataSource.h"
#include "MB_NodeRankUnit.h"
#include "MB_FunctionRankingProtocol.h"

MB_RankDataSource::MB_RankDataSource()
{
    m_ItemSize = MB_NodeRankUnit::getNodeSize();
    m_pArray = NULL;
}

MB_RankDataSource::~MB_RankDataSource()
{
    
}

void MB_RankDataSource::setDataArray(CCArray* pArray)
{
    m_pArray = pArray;
}

CCSize MB_RankDataSource::cellSizeForTable(CCTableView *table)
{
    return m_ItemSize;
}

CCTableViewCell* MB_RankDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_RankData* pData = dynamic_cast<MB_RankData*>(m_pArray->objectAtIndex(m_pArray->count()-idx-1));
    CCNode* pNode = createUnitByData(pData);
    if (pNode)
    {
        cell->addChild(pNode);
        pNode->setPosition(m_ItemSize.width/2.0, m_ItemSize.height/2.0);
    }
    return cell;
}

unsigned int MB_RankDataSource::numberOfCellsInTableView(CCTableView *table)
{
    if (m_pArray!=NULL)
    {
        return m_pArray->count();
    }
    return 0;
}

CCNode* MB_RankDataSourceLevel::createUnitByData(MB_RankData* pData)
{
    MB_NodeRankLevel* pLevel = MB_NodeRankLevel::create();
    if (pLevel)
    {
        pLevel->setData(pData);
        return pLevel;
    }
    return NULL;
}

CCNode* MB_RankDataSourcePower::createUnitByData(MB_RankData* pData)
{
    MB_NodeRankPower* pPower = MB_NodeRankPower::create();
    if (pPower)
    {
        pPower->setData(pData);
        return pPower;
    }
    return NULL;
}

CCNode* MB_RankDataSourceAbsolved::createUnitByData(MB_RankData* pData)
{
    MB_NodeRankAbsolved* pNode = MB_NodeRankAbsolved::create();
    if (pNode)
    {
        pNode->setData(pData);
        return pNode;
    }
    return NULL;
}

CCNode* MB_RankDataSourceArena::createUnitByData(MB_RankData* pData)
{
    MB_NodeRankArena* pNode = MB_NodeRankArena::create();
    if (pNode)
    {
        pNode->setData(pData);
        return pNode;
    }
    return NULL;
}