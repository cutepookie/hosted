//
//  MB_PerfectRaceEntrance.cpp
//  ProjectPM
//
//  Created by crimoon on 14-4-14.
//
//

#include "MB_PerfectRaceEntrance.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_FunctionModule.h"


MB_PerfectRaceEntrance::MB_PerfectRaceEntrance()
{
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL,MB_PerfectRaceEntrance);
    SOCKET_MSG_REGIST(SC_RACE_INFO, MB_PerfectRaceEntrance);
    m_pPerfectRaceInterface = NULL;
}
MB_PerfectRaceEntrance::~MB_PerfectRaceEntrance()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    SOCKET_MSG_UNREGIST(SC_RACE_INFO);
    m_pPerfectRaceInterface = NULL;
}

void MB_PerfectRaceEntrance::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    if(m_bEnable)
    {
        showActivities(m_pPerfectRaceInterface->getStep()!=STATUS_NOT_OPEN);
    }
}
bool MB_PerfectRaceEntrance::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    return m_pPerfectRaceInterface != NULL;
}
void MB_PerfectRaceEntrance::onMsgRecv(CCNode* node, SocketResponse* response)
{
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
            onResetWnd();
            break;
            
        case SC_RACE_INFO:
            onResetWnd();
            break;
        default:
            break;
    }
}