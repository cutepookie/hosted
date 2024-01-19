//
//  MB_CallShopEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-11.
//
//

#include "MB_CallShopEntry.h"
#include "MB_ToyShopInterface.h"
bool MB_NodeCallShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ToyShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}