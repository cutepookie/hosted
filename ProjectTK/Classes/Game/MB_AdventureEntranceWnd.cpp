//
//  MB_AdventureEntranceWnd.cpp
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#include "MB_AdventureEntranceWnd.h"
#include "MB_AdventureEntry.h"
#include "MB_RoleData.h"
#include "MB_LayerRuningCool.h"
MB_AdventureEntranceWnd::MB_AdventureEntranceWnd()
{
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL,MB_AdventureEntranceWnd);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_DISCOVERYTIMES,MB_AdventureEntranceWnd);
    SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_AdventureEntranceWnd);
}
MB_AdventureEntranceWnd::~MB_AdventureEntranceWnd()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_DISCOVERYTIMES);
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
}
bool MB_AdventureEntranceWnd::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_AdventureEntry*>(pDataSource);
    if (m_pDataSource)
    {
        return true;
    }
    return false;
}

void MB_AdventureEntranceWnd::onResetWnd()
{
    MB_NodeCommandEntrance::onResetWnd();
    //pve 入口信息 探险
    uint32_t kType = ((NSGameFunction::CCFunctionInterface*)m_pDataSource)->getFunctionType();
    MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kType);
    if (pItem)
    {
        if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
        {
            uint16_t iTimes = MB_RoleData::getInstance()->getDiscoveryTimes();
            if (iTimes > 0)
            {
                m_pFlagNode2->setVisible(true);
                if (iTimes>99) {
                    m_pFlag2->setString("!");
                }else
                {
                    char databuf[20];
                    sprintf(databuf,"%d",iTimes);
                    m_pFlag2->setString(databuf);
                }
            }
            else
            {
                m_pFlagNode2->setVisible(false);
            }
        }
        else
        {
            m_pFlagNode2->setVisible(false);
        }
    }

}
void MB_AdventureEntranceWnd::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_ROLE_BUY_ENERGY:
        case SC_ROLE_UPDATE_DISCOVERYTIMES:
            this->onResetWnd();
            break;
        default:
            break;
    }
}

void MB_AdventureEntranceWnd::onEntranceClicked(CCObject* pSender)
{
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("MB_LayerRuningCool"))
    {
    }
    else
    {
        MB_NodeCommandEntrance::onEntranceClicked(this);
    }
}





