//
//  AdventureEntry.cpp
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//探险進入接口

#include "MB_AdventureEntry.h"
#include "MB_AdventureEntranceWnd.h"
#include "MB_LayerRuningCool.h"

MB_AdventureEntry::MB_AdventureEntry()
{
    SOCKET_MSG_REGIST(SC_EXPLORE_AUTO_EXPLORE_CHECK,MB_AdventureEntry);
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRuningCool",false);
}
MB_AdventureEntry::~MB_AdventureEntry()
{
    SOCKET_MSG_UNREGIST(SC_EXPLORE_AUTO_EXPLORE_CHECK);
}
uint16_t MB_AdventureEntry::getFunctionType()
{
    return kFunctionMaoXian;
}
MB_ResWindow* MB_AdventureEntry::createEntryDialog()
{
    MB_AdventureEntranceWnd* ptr = new MB_AdventureEntranceWnd();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
MB_ResWindow* MB_AdventureEntry::createFunctionDialog()
{
    MB_LayerRuningCool* ptr = new MB_LayerRuningCool();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_AdventureEntry::allowShow()
{
    return true;
}

void MB_AdventureEntry::onLoadingScene()
{
    sendexplore_auto_explore_check();
}

void MB_AdventureEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_EXPLORE_AUTO_EXPLORE_CHECK:
            recvexplore_auto_explore_check(recvPacket);
            break;
        default:
            break;
    }

}
bool MB_AdventureEntry::sendexplore_auto_explore_check(){
    
    SOCKET_REQUEST_START(CS_EXPLORE_AUTO_EXPLORE_CHECK);
    SOCKET_REQUEST_END(SC_EXPLORE_AUTO_EXPLORE_CHECK, MB_ExplorerMgr::onMsgRecv);
    return true;
}
bool MB_AdventureEntry::recvexplore_auto_explore_check(MB_MsgBuffer *recvPacket){
    
    recvPacket->readU8(&m_pAutoVipLimit);
    return true;
}

void MB_AdventureEntry::sendexplor_one()
{
    SOCKET_REQUEST_START(CS_EXPLORE_ONE);
    SOCKET_REQUEST_END(SC_EXPLORE_ONE, NULL);
}
