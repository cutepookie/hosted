//
//  MB_RecoveryEnergyInterface.cpp
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//

#include "MB_RecoveryEnergyInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerEventRecoveryEnergy.h"
#include "MB_NodeRecoveryEnergyEntry.h"


MB_ResWindow* MB_RecoveryEnergyInterface::createEntryDialog()
{
    MB_NodeRecoveryEnergyEntry* pInstance = new MB_NodeRecoveryEnergyEntry();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        
        pInstance->setType(kActivatyRecoverEnergy);
        pInstance->schedule(schedule_selector(MB_ResWindow::tick));
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_RecoveryEnergyInterface::createFunctionDialog()
{
    return MB_LayerEventRecoveryEnergy::create();
}

void MB_RecoveryEnergyInterface::onLoadingScene()
{
    
}

void MB_RecoveryEnergyInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_RecoveryEnergyInterface::allowShow()
{
    return true;
}

uint16_t MB_RecoveryEnergyInterface::getFunctionType()
{
    return kActivatyRecoverEnergy;
}

