//
//  MB_DailyInterface.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-6.
//
//

#include "MB_DailyInterface.h"
#include "MB_DailyEntry.h"
#include "MB_FunctionMgr.h"
//#include "MB_LayerDailyReward.h"
#include "MB_LayerRegistration.h"
#include "MB_LayerCommand.h"

MB_ResWindow* MB_DailyInterface::createEntryDialog()
{
    MB_DailyEntry* pInstance = new MB_DailyEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(getFunctionType());
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_DailyInterface::createFunctionDialog()
{
    return MB_LayerRegistration::create();
}
void MB_DailyInterface::onLoadingScene()
{
    
}
void MB_DailyInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}
bool MB_DailyInterface::allowShow()
{
    return true;
}
uint16_t MB_DailyInterface::getFunctionType()
{
    return kFunctionDaily;
}
void MB_DailyInterface::onEntryClicked(CCObject* pSender)
{
    TutorialTriggerComplete;
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionDaily ,&pInterface))
    {
        MB_ResWindow* pResWindow = createFunctionDialog();
        if (pResWindow)
        {
            CCDirector::sharedDirector()->getRunningScene()->addChild(pResWindow,Z_ORDER_CHAT);
        }
    }
}
