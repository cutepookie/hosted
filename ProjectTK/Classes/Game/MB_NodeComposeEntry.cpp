//
//  MB_NodeComposeEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#include "MB_NodeComposeEntry.h"
#include "MB_ComposeInterface.h"
bool MB_NodeComposeEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ComposeInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}