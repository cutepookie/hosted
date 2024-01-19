//
//  MB_NodeResearchInstituteEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-14.
//
//

#include "MB_NodeResearchInstituteEntry.h"
#include "MB_ResearchInstituteInterface.h"
#include "MB_RoleData.h"
#include "MB_FunctionModule.h"

MB_NodeResearchInstituteEntry* MB_NodeResearchInstituteEntry::create()
{
    MB_NodeResearchInstituteEntry* pNode = new MB_NodeResearchInstituteEntry;
    if (pNode && pNode->init())
    {
        pNode->setType(kFunctionResearchInstitute);
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    
    return NULL;
}

MB_NodeResearchInstituteEntry::MB_NodeResearchInstituteEntry()
{
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL,MB_NodeResearchInstituteEntry);
    SOCKET_MSG_REGIST(SC_NANM_OPEN_TIME,MB_NodeResearchInstituteEntry);
    SOCKET_MSG_REGIST(SC_NANM_STOP,MB_NodeResearchInstituteEntry);
    SOCKET_MSG_REGIST(SC_PUSH_HIGHLIGHT_INFO,MB_NodeResearchInstituteEntry);
    schedule(schedule_selector(MB_NodeResearchInstituteEntry::UpDataState), 1.0f);
}

MB_NodeResearchInstituteEntry::~MB_NodeResearchInstituteEntry()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_NANM_STOP);
    SOCKET_MSG_UNREGIST(SC_PUSH_HIGHLIGHT_INFO);
}

void MB_NodeResearchInstituteEntry::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    
    if (m_bEnable)
    {
        showActivities(MB_EventMgr::getInstence()->getIsNanMOnLine());
    }
    
}

void MB_NodeResearchInstituteEntry::onMsgRecv(CCNode* node, SocketResponse* response){
    
    
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
        case SC_ROLE_UPDATE_LEVEL:
        case SC_NANM_OPEN_TIME:
        case SC_PUSH_HIGHLIGHT_INFO:
        {
            onResetWnd();
        }
            break;
        case SC_NANM_STOP:
        {
            this->unschedule(schedule_selector(MB_NodeResearchInstituteEntry::UpDataState));
        }
            break;
            
        default:
            break;
    }
    
}


void MB_NodeResearchInstituteEntry::UpDataState(float dt)
{
    time_t timestart = ((MB_EventData *)MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(0))->getBeginTime();
    time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
    
    //活动不是今天开启
    if(timestart/(3600*24) != nowtime/(3600*24))
    {
        this->unschedule(schedule_selector(MB_NodeResearchInstituteEntry::UpDataState));
    }
    if (m_bEnable)
    {
        showActivities(MB_EventMgr::getInstence()->getIsNanMOnLine());
    }
}