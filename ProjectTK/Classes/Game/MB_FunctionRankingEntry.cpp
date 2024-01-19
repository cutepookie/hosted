//
//  MB_FunctionRankingEntry.cpp
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#include "MB_FunctionRankingEntry.h"
#include "MB_FunctionRanking.h"

bool MB_FunctionRankingEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_FunctionRanking*>(pDataSource);
    
    return m_pDataSource != NULL;
}

void MB_FunctionRankingEntry::onEntranceClicked(CCObject* pSender)
{
    MB_FunctionEntranceWnd::onEntranceClicked(pSender);
}