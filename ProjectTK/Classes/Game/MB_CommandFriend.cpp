//
//  MB_CommandFriend.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_CommandFriend.h"
#include "MB_NodeFriendEntry.h"
//#include "MB_LayerFriend.h"
#include "MB_FunctionModule.h"
#include "MB_LayerFriend.h"
#include "MB_LayerCommand.h"

MB_ResWindow* MB_CommandFriend::createEntryDialog()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerFriend",false);
    MB_NodeFriendEntry* pInstance = new MB_NodeFriendEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_CommandFriend::createFunctionDialog()
{
    MB_LayerCommand* LayerCommand = dynamic_cast<MB_LayerCommand*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND));
    if(LayerCommand)LayerCommand->setSelectedSprPos(5);
    return MB_LayerFriend::create();
}
void MB_CommandFriend::onEntryClicked(CCObject* pSender)
{
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("MB_LayerFriend",false)) {
        NSGameFunction::CCFunctionInterface::onEntryClicked(pSender);
    }
}
void MB_CommandFriend::onLoadingScene()
{

}

void MB_CommandFriend::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
}

bool MB_CommandFriend::allowShow()
{
    return true;
}

uint16_t MB_CommandFriend::getFunctionType()
{
    return kFunctionFriend;
}
