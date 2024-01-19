//
//  MB_NodeBudokanEntry.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#include "MB_NodeBudokanEntry.h"
#include "MB_FunctionBudokanInterface.h"


MB_NodeBudokanEntry* MB_NodeBudokanEntry::create()
{
    MB_NodeBudokanEntry* pNode = new MB_NodeBudokanEntry;
    if (pNode && pNode->init())
    {
        pNode->autorelease();
        pNode->setType(kFunctionBudokan);
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}
MB_NodeBudokanEntry::MB_NodeBudokanEntry()
{
    SOCKET_MSG_REGIST(SC_BUDUOKAN_INFO,MB_NodeBudokanEntry);
    //schedule(schedule_selector(MB_NodeBudokanEntry::UpDataState), 1.0f); // 以后请不要这么做 wenyong
}

MB_NodeBudokanEntry::~MB_NodeBudokanEntry()
{
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_INFO);
    //this->unschedule(schedule_selector(MB_NodeBudokanEntry::UpDataState));
}

void MB_NodeBudokanEntry::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionBudokan ,&pInterface))
    {
        MB_FunctionBudokanInterface* pInterfaceTemp = dynamic_cast<MB_FunctionBudokanInterface*>(pInterface);
        if (pInterfaceTemp)
        {
            if (pInterfaceTemp->getIsOpen()  && pInterfaceTemp->getBudokanData()->getChallengeTimes() > 0 )
            {
                //开启活动特效
                showActivities(true);
            }
            else
            {
                showActivities(false);
            }
        }
    }
}


void MB_NodeBudokanEntry::onMsgRecv(CCNode* node, SocketResponse* response){
    
    
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg){
        case SC_BUDUOKAN_INFO:
        {
            onResetWnd();
        }
        break;
        default:
            break;
    }
    
}

void MB_NodeBudokanEntry::UpDataState(float dt)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionBudokan ,&pInterface))
    {
        MB_FunctionBudokanInterface* pInterfaceTemp = dynamic_cast<MB_FunctionBudokanInterface*>(pInterface);
        if(pInterfaceTemp->getBudokanData()->getChallengeTimes() == 0)
        {
            this->unschedule(schedule_selector(MB_NodeBudokanEntry::UpDataState));
        }
        if (pInterfaceTemp)
        {
            showActivities(pInterfaceTemp->getIsOpen() && pInterfaceTemp->getBudokanData()->getChallengeTimes() > 0);
        }
    }


}
