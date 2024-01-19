//
//  MB_ValentineDayNodeEntry.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_ValentineDayNodeEntry.h"
#include "MB_FunctionValentineDay.h"

void MB_ValentineDayNodeEntry::onEntranceClicked(CCObject* pSender)
{
    MB_FunctionValentineDay* pFunction = dynamic_cast<MB_FunctionValentineDay*>(m_pInterface);
    if (pFunction)
    {
        enter();
    }
}