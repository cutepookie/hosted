//
//  MB_NodeFriendEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_NodeFriendEntry.h"
#include "MB_CommandFriend.h"
#include "MB_DataFriend.h"
bool MB_NodeFriendEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_CommandFriend*>(pDataSource);
    
    return m_pDataSource != NULL;
}


void MB_NodeFriendEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    onResetWnd();
}

MB_NodeFriendEntry::MB_NodeFriendEntry()
{
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY_ME, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_SEND_ENERGY_ME, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_ADD_LIST, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_NEW_ADD, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_AGREE, MB_NodeFriendEntry);
    SOCKET_MSG_REGIST(SC_FRIEND_REFUSE, MB_NodeFriendEntry);
}

MB_NodeFriendEntry::~MB_NodeFriendEntry()
{
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY_ME);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY);
    SOCKET_MSG_UNREGIST(SC_FRIEND_SEND_ENERGY_ME);
    SOCKET_MSG_UNREGIST(SC_FRIEND_ADD_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NEW_ADD);
    SOCKET_MSG_UNREGIST(SC_FRIEND_AGREE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_REFUSE);
}

void MB_NodeFriendEntry::onResetWnd()
{
    MB_NodeCommandEntrance::onResetWnd();
    
    
    int msgCount = 0;
    msgCount = MB_FriendMgr::getInstance()->getFriendMsgArray()->count();
    if (msgCount > 0)
    {
        setEff(true);
    }
    else
    {
        setEff(false);
    }
    
    CCArray* pArray = MB_FriendMgr::getInstance()->getFriendArray();
        CCArray* pArray2 = MB_FriendMgr::getInstance()->getFriendMsgArray();
    MB_DataFriend* pData = NULL;
    
    int count = pArray2->count();
    CCARRAY_FOREACH_4TYPE(pArray, MB_DataFriend*, pData)
    {
        if (pData && pData->getCanGiveEnergy())
        {
            ++count;
        }
    }
    
    if (count !=0 )
    {
        m_pFlagNode2->setVisible(true);
        if (count>99) {
            m_pFlag2->setString("!");
        }else
        {
            char buff[12] = {};
            sprintf(buff, "%d",count);
            m_pFlag2->setString(buff);
        }
    }
    else
    {
        m_pFlagNode2->setVisible(false);
    }
    

}
