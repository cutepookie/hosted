//
//  MB_YeShiJieInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-17.
//
//

#include "MB_YeShiJieInterface.h"
#include "MB_YeShiJieEntrance.h"
#include "MB_LayerYeShiJieMain.h"

MB_YeShiJieInterface::MB_YeShiJieInterface()
{
}

MB_YeShiJieInterface::~MB_YeShiJieInterface()
{
}

MB_ResWindow* MB_YeShiJieInterface::createEntryDialog()
{
    MB_YeShiJieEntrance* pWnd = new MB_YeShiJieEntrance;
    if (pWnd&& pWnd->init())
    {
        pWnd->autorelease();
        pWnd->setType(getFunctionType());
        return pWnd;
    }
    
    CC_SAFE_RELEASE_NULL(pWnd);
    
    return pWnd;
}

MB_ResWindow* MB_YeShiJieInterface::createFunctionDialog()
{
    MB_LayerYeShiJieMain* pWnd = new MB_LayerYeShiJieMain;
    if (pWnd && pWnd->setDataSource(this) && pWnd->init())
    {
        pWnd->autorelease();
        return pWnd;
    }
    
    CC_SAFE_RELEASE_NULL(pWnd);
    return NULL;
}


uint16_t MB_YeShiJieInterface::getFunctionType()
{
    return kFunctionYeShiJie;
}
void MB_YeShiJieInterface::onLoadingScene()
{
}

void MB_YeShiJieInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
}
