//
//  MB_FunctionValentineDay.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-22.
//
//

#include "MB_FunctionValentineDay.h"
#include "MB_ValentineDayProtocol.h"
#include "MB_FunctionModule.h"
#include "MB_ValentineDayNodeEntry.h"
#include "MB_ValentineDayLayerRank.h"
#include "MB_ValentineDayLayerMain.h"

uint16_t MB_FunctionValentineDay::getFunctionType()
{
    return kFunctionValentineDay;
}

MB_ResWindow* MB_FunctionValentineDay::createEntryDialog()
{
    MB_ValentineDayNodeEntry* pEntry = new MB_ValentineDayNodeEntry;
    if (pEntry && pEntry->setDataSource(this) && pEntry->init())
    {
        pEntry->autorelease();
        return pEntry;
    }
    
    CC_SAFE_RELEASE_NULL(pEntry);
    return NULL;
}

MB_ResWindow* MB_FunctionValentineDay::createFunctionDialog()
{
    MB_ValentineDayLayerMain* p = new MB_ValentineDayLayerMain;
    if (p && p->setDataSource(this) && p->init())
    {
        p->autorelease();
        return p;
    }
    return NULL;
}

MB_ResWindow* MB_FunctionValentineDay::createRankDialog()
{
    MB_ValentineDayLayerRank* p = new MB_ValentineDayLayerRank;
    if (p && p->setDataSource(this) && p->init())
    {
        p->autorelease();
        return p;
    }
    
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}