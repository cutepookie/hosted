//
//  MB_NodeHomeEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_NodeHomeEntry.h"
#include "MB_CommandHome.h"

using namespace NSGameFunction;

bool MB_NodeHomeEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_CommandHome*>(pDataSource);
    
    if (m_pDataSource)
    {
        return true;
    }
    
    return false;
}