//
//  MB_BackpackInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#include "MB_FunctionModule.h"
#include "MB_BackpackInterface.h"
#include "MB_NodeBackpackEntry.h"
#include "MB_LayerBackpack.h"
#include "MB_ItemBackpackDataSource.h"

MB_ResWindow* MB_BackpackInterface::createEntryDialog()
{
    MB_NodeBackpackEntry* pInstance = new MB_NodeBackpackEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(getFunctionType());
        
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_BackpackInterface::MB_BackpackInterface()
{
    m_pMB_ItemDataSource = new MB_ItemBackpackDataSource;
    m_pEquipDataSource = new MB_EquipBackpackDataSource;
    m_pDebrisDataSource = new MB_ItemDebrisDataSource;
}

MB_BackpackInterface::~MB_BackpackInterface()
{
    CC_SAFE_DELETE(m_pMB_ItemDataSource);
    CC_SAFE_DELETE(m_pEquipDataSource);
    CC_SAFE_DELETE(m_pDebrisDataSource);
}

MB_ResWindow* MB_BackpackInterface::createFunctionDialog()
{
    MB_LayerBackpack* layer = MB_LayerBackpack::create();
    layer->setDataSource(this);
    return layer;
}

void MB_BackpackInterface::onLoadingScene()
{
    
}

void MB_BackpackInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_BackpackInterface::allowShow()
{
    return true;
}

uint16_t MB_BackpackInterface::getFunctionType()
{
    return kFunctionBackpack;
}
