//
//  MB_CommandHome.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_CommandHome.h"
#include "MB_LayerHome.h"
#include "MB_NodeHomeEntry.h"
#include "MB_FunctionModule.h"
#include "MB_LayerCommand.h"
MB_ResWindow* MB_CommandHome::createEntryDialog()
{
    MB_NodeHomeEntry* pInstance = new MB_NodeHomeEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_CommandHome::createFunctionDialog()
{
    MB_LayerHome* ptr = new MB_LayerHome();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        MB_LayerCommand* LayerCommand = dynamic_cast<MB_LayerCommand*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND));
        if(LayerCommand)LayerCommand->setSelectedSprPos(0);
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}

void MB_CommandHome::onLoadingScene()
{

}

void MB_CommandHome::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_CommandHome::allowShow()
{
    return true;
}

uint16_t MB_CommandHome::getFunctionType()
{
    return kFunctionHome;
}

void MB_CommandHome::onEntryClicked(CCObject* pSender)
{
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("MB_LayerHome",false)) {
        goFunctionHome();
    }
}
