//
//  MB_MysteryShopEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#include "MB_PayShopEntry.h"
#include "MB_PayShopInterface.h"

bool MB_PayShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_PayShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}

void MB_PayShopEntry::onEntranceClicked(CCObject* pSender)
{
    ((MB_PayShopInterface*)m_pDataSource)->cs_activity_day_pay_mul();
    MB_NodeHoverEntry::onEntranceClicked(pSender);
}