//
//  MB_CommandActivaty.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_CommandActivaty.h"
#include "MB_NodeActivatyEntry.h"
#include "MB_FunctionModule.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_ActivatyMgr.h"

MB_CommandActivaty::~MB_CommandActivaty()
{
    MB_ActivatyMgr::destroyInstance();
}
MB_CommandActivaty::MB_CommandActivaty()
{
    MB_ActivatyMgr::getInstance();
}
MB_ResWindow* MB_CommandActivaty::createEntryDialog()
{
    return MB_NodeActivatyEntry::create();
}

MB_ResWindow* MB_CommandActivaty::createFunctionDialog()
{
    MB_ActivatyMainLayer* pLayer = MB_ActivatyMainLayer::create();
    pLayer->setDataSource(this);
    pLayer->setShowActivatyID(0);
    return pLayer;//MB_LayerAllEvent::create((kSubLayerType)kSubLayerTypeNone);
}

void MB_CommandActivaty::onLoadingScene()
{

}

void MB_CommandActivaty::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

bool MB_CommandActivaty::allowShow()
{
    return true;
}

uint16_t MB_CommandActivaty::getFunctionType()
{
    return kFunctionActivaty;
}
void MB_CommandActivaty::onEntryClicked(CCObject* pSender)
{
    MB_ResWindow* pResWindow = createFunctionDialog();
    if (pResWindow)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(pResWindow,Z_ORDER_CHAT+1);
    }
}
