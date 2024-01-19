//
//  AdventureEntry.cpp
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//探险進入接口

#include "MB_RoomEntry.h"
#include "MB_RoomEntranceWnd.h"
#include "MB_LayerRoom.h"
#include "MB_LayerCommand.h"
MB_RoomEntry::MB_RoomEntry()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRoom",false);
}
MB_RoomEntry::~MB_RoomEntry()
{
}
uint16_t MB_RoomEntry::getFunctionType()
{
    return kFunctionRoom;
}
MB_ResWindow* MB_RoomEntry::createEntryDialog()
{
    MB_RoomEntranceWnd* ptr = new MB_RoomEntranceWnd();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
MB_ResWindow* MB_RoomEntry::createFunctionDialog()
{
    MB_LayerRoom* ptr = new MB_LayerRoom();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        MB_LayerCommand* LayerCommand = dynamic_cast<MB_LayerCommand*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND));
        if(LayerCommand)LayerCommand->setSelectedSprPos(3);
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_RoomEntry::allowShow()
{
    return true;
}

void MB_RoomEntry::onLoadingScene()
{
}

void MB_RoomEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{

}
