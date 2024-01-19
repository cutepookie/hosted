//
//  MB_RefreshShopEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-5.
//
//

#include "MB_RefreshShopEntry.h"
#include "MB_RefreshShopInterface.h"

bool MB_RefreshShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_RefreshShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}