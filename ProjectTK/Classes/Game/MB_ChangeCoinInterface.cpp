//
//  MB_ChangeCoinInterface.cpp
//  ProjectPM
//
//  Created chk on 14-4-29.
//
//

#include "MB_ChangeCoinInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerEventChangeCoin.h"
#include "MB_NodeChangeCoinEntry.h"

MB_ResWindow* MB_ChangeCoinInterface::createEntryDialog()
{
    MB_NodeChangeCoinEntry* pInstance = new MB_NodeChangeCoinEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(kActivatyChangeCoin);
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_ChangeCoinInterface::createFunctionDialog()
{
    return MB_LayerEventChangeCoin::create();
}

void MB_ChangeCoinInterface::onLoadingScene()
{
}

void MB_ChangeCoinInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

bool MB_ChangeCoinInterface::allowShow()
{
    return true;
}

uint16_t MB_ChangeCoinInterface::getFunctionType()
{
    return kActivatyChangeCoin;
}

void MB_ChangeCoinInterface::onDayPassed()
{
}
