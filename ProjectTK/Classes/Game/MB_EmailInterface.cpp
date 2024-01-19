//
//  MB_EmailInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#include "MB_EmailInterface.h"
#include "MB_FunctionModule.h"
#include "MB_NodeEmailEntry.h"
#include "MB_LayerMailView.h"

MB_ResWindow* MB_EmailInterface::createEntryDialog()
{
    MB_NodeEmailEntry* pInstance = new MB_NodeEmailEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_EmailInterface::createFunctionDialog()
{
    return MB_LayerMailView::create();//MB_MailMainView::create();//
}

void MB_EmailInterface::onLoadingScene()
{
    
}

void MB_EmailInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_EmailInterface::allowShow()
{
    return true;
}

uint16_t MB_EmailInterface::getFunctionType()
{
    return kFunctionEmail;
}