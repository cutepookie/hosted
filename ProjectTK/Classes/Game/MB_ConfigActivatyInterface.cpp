//
//  MB_ConfigActivatyInterface.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-12.
//
//


#include "MB_ConfigActivatyInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_NodeConfigActivatyEntry.h"
#include "MB_LayerEventDetail.h"


MB_ResWindow* MB_ConfigActivatyInterface::createEntryDialog(int eventID)
{
    MB_NodeConfigActivatyEntry* pInstance = new MB_NodeConfigActivatyEntry(eventID);
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}


MB_ResWindow* MB_ConfigActivatyInterface::createFunctionDialog(int eventID)
{
    return MB_LayerEventDetail::create(eventID);
}

void MB_ConfigActivatyInterface::onLoadingScene()
{
    //公告里面發了
//    MB_MoneyEevntMgr::getInstance()->sendactivity_get_list();
}

void MB_ConfigActivatyInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_ConfigActivatyInterface::allowShow()
{
    return true;
}

uint16_t MB_ConfigActivatyInterface::getFunctionType()
{
    return kActivatyConfig;
}
