//
//  MB_ChampionshipEntryDialog.cpp
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#include "MB_ChampionshipEntryDialog.h"
#include "MB_Championship.h"
#include "MB_RoleData.h"
#include "MB_FunctionModule.h"
MB_ChampionshipEntryDialog* MB_ChampionshipEntryDialog::create()
{
    MB_ChampionshipEntryDialog* pNode = new MB_ChampionshipEntryDialog;
    if (pNode && pNode->init())
    {
        pNode->setType(kFunctionArena);
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}
MB_ChampionshipEntryDialog::MB_ChampionshipEntryDialog()
{
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_ChampionshipEntryDialog);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PLUNDERTIMES, MB_ChampionshipEntryDialog);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PVPTIMES, MB_ChampionshipEntryDialog);
}

MB_ChampionshipEntryDialog::~MB_ChampionshipEntryDialog()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PLUNDERTIMES);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PVPTIMES);
}



void MB_ChampionshipEntryDialog::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_ROLE_UPDATE_LEVEL:
        case SC_ROLE_UPDATE_PLUNDERTIMES:
        case SC_ROLE_UPDATE_PVPTIMES:
            this->onResetWnd();
            break;
        default:
            break;
    }
}

void MB_ChampionshipEntryDialog::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    
    if(m_bEnable)
    {
        showActivities(MB_RoleData::getInstance()->getPVPTimes() > 0);
    }
}
