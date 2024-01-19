//
//  MB_ItemShopInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//
#include "MB_ItemShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_ItemShopEntry.h"
#include "MB_ShopPoints.h"
#include "MB_LayerShopMain.h"

MB_ResWindow* MB_ItemShopInterface::createEntryDialog()
{
    MB_ItemShopEntry* pInstance = new MB_ItemShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_ItemShopInterface::createFunctionDialog()
{
    return MB_LayerShopMain::createItemShop();
    return MB_ShopPoints::create();
}

void MB_ItemShopInterface::onLoadingScene()
{
    
}

void MB_ItemShopInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

bool MB_ItemShopInterface::allowShow()
{
    return true;
}

uint16_t MB_ItemShopInterface::getFunctionType()
{
    return kFunctionItemShop;
}

void MB_ItemShopInterface::onDayPassed()
{
}