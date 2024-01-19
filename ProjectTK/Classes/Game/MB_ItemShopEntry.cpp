//
//  MB_MysteryShopEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#include "MB_ItemShopEntry.h"
#include "MB_ItemShopInterface.h"

bool MB_ItemShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ItemShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}