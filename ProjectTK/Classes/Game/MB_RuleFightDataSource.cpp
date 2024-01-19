//
//  MB_RuleFightDataSource.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#include "MB_RuleFightDataSource.h"
#include "MB_RuleFightInterface.h"
#include <algorithm>
#include "MB_NodeRuleRankUnit.h"
#include "MB_RuleFightProtocol.h"
#include "MB_NodeRuleReportUnit.h"
MB_RuleFightDataSource::MB_RuleFightDataSource(MB_RuleFightInterface* pInterface)
{
    m_pDatas = pInterface->getRuleInfo()->getList();
}

CCSize MB_RuleFightDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeRuleReportUnit::getUnitSize();
}

CCTableViewCell* MB_RuleFightDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_NodeRuleReportUnit* node = MB_NodeRuleReportUnit::create((Hist*)m_pDatas->objectAtIndex(idx));
    if (node)
    {
        cell->addChild(node);
        node->setPosition(ccp(MB_NodeRuleReportUnit::getUnitSize().width/2,MB_NodeRuleReportUnit::getUnitSize().height/2));
    }
    return cell;
}

unsigned int MB_RuleFightDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDatas->count();
}


////////////////
MB_RuleRankDataSource::MB_RuleRankDataSource(MB_RuleFightInterface* pInterface)
{
    m_pDatas = pInterface->getRankList();
}

CCSize MB_RuleRankDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeRuleRankUnit::getUnitSize();
}

CCTableViewCell* MB_RuleRankDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_NodeRuleRankUnit* pNode = MB_NodeRuleRankUnit::create((RuleFighter*)m_pDatas->objectAtIndex(idx));
    if(pNode)
    {
        cell->addChild(pNode);
        pNode->setPosition(MB_NodeRuleRankUnit::getUnitSize().width/2, MB_NodeRuleRankUnit::getUnitSize().height/2);
    }
    return cell;
}

unsigned int MB_RuleRankDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDatas->count();
}

////////////////
MB_LastWeekRankDataSource::MB_LastWeekRankDataSource(MB_RuleFightInterface* pInterface)
{
    m_pDatas = pInterface->getLastWeekRank();
}

CCSize MB_LastWeekRankDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeRuleRankUnit::getUnitSize();
}

CCTableViewCell* MB_LastWeekRankDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_NodeRuleRankUnit* pNode = MB_NodeRuleRankUnit::create((RuleFighter*)m_pDatas->objectAtIndex(idx));
    if(pNode)
    {
        cell->addChild(pNode);
        pNode->setPosition(MB_NodeRuleRankUnit::getUnitSize().width/2, MB_NodeRuleRankUnit::getUnitSize().height/2);
    }
    return cell;
}

unsigned int MB_LastWeekRankDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDatas->count();
}
