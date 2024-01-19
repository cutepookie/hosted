//
//  MB_MysteryShopEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#include "MB_MysteryShopEntry.h"
#include "MB_MysteryShopInterface.h"

bool MB_MysteryShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_MysteryShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}