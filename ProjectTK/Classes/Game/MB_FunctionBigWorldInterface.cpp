//
//  MB_FunctionBigWorldInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-13.
//
//

#include "MB_FunctionBigWorldInterface.h"
//#include "MB_LayerBigWorld.h"
#include "MB_NodeBigWorldEntry.h"
#include "MB_LayerWorld.h"

MB_ResWindow* MB_FunctionBigWorldInterface::createEntryDialog()
{
    return MB_NodeBigWorldEntry::create();
}

MB_ResWindow* MB_FunctionBigWorldInterface::createFunctionDialog()
{
    return MB_LayerWorld::create();
}

void MB_FunctionBigWorldInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_FunctionBigWorldInterface::allowShow()
{
    return true;
}

uint16_t MB_FunctionBigWorldInterface::getFunctionType()
{
    return kFunctionBigWorld;
}

void MB_FunctionBigWorldInterface::onEntryClicked(CCObject* pSender)
{
    MB_ResWindow* pWnd = createFunctionDialog();
    if (pWnd)
    {
        replaceMainSceneLayer(pWnd);
    }
}

void MB_FunctionBigWorldInterface::onLoadingScene()
{
}