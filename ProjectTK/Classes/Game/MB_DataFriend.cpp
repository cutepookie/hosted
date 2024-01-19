

#include "MB_DataFriend.h"
#include "MB_FriendDataSyncUpdate.h"
#include "MB_MsgBuffer.h"
#include <algorithm>
#include "MB_SceneGame.h"
static MB_FriendMgr* s_pFriendMgr = NULL;

bool MB_DataFriend::getCanGold()
{
    if (m_nEndGold <= m_nBeginGold)
    {
        return false;
    }
    int now = MB_ClientSocket::getInstance()->getServerTime();
    return now < m_nEndGold && now > m_nBeginGold;
}
bool MB_DataFriend::getCanBadge()
{
    if (m_nEndBadge <= m_nBeginBadge)
    {
        return false;
    }
    int now = MB_ClientSocket::getInstance()->getServerTime();
    return now < m_nEndBadge && now > m_nBeginBadge;
}
MB_FriendMgr::MB_FriendMgr()
{
    m_pArrayFriend = new CCArray();
    m_pArrayEnemy = new CCArray();
    m_pArrayExplore = new CCArray();
    m_pArrayMsg = new CCArray();
    
    m_uLastGetFriendListTime = 0;
    SOCKET_MSG_REGIST(SC_FRIEND_GET_LIST, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_GET_ADD_LIST, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_EXPLORE, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_ADD, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_DELETE, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_NOTIFY_DELETE, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_NEW, MB_FriendMgr);
    
    SOCKET_MSG_REGIST(SC_FRIEND_SEND_ENERGY, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY_ME, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_SEND_ENERGY_ME, MB_FriendMgr);
    
    /*
     #define SC_HOMESTEAD_SYNC_MATING_COOL_SECOND    20230
     #define SC_HOMESTEAD_SYNC_GER                   20231
     #define SC_HOMESTEAD_SYNC_ADD_ENGRY             20232
     */
    SOCKET_MSG_REGIST(SC_HOMESTEAD_SYNC_MATING_COOL_SECOND, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_HOMESTEAD_SYNC_GER, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_HOMESTEAD_SYNC_ADD_ENGRY, MB_FriendMgr);
    
    SOCKET_MSG_REGIST(SC_FRIEND_ADD_LIST, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_NEW_ADD, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_AGREE, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_REFUSE, MB_FriendMgr);
    SOCKET_MSG_REGIST(SC_FRIEND_FIGHT, MB_FriendMgr);
}

MB_FriendMgr::~MB_FriendMgr()
{
    CC_SAFE_RELEASE_NULL(m_pArrayFriend);
    CC_SAFE_RELEASE_NULL(m_pArrayEnemy);
    CC_SAFE_RELEASE_NULL(m_pArrayExplore);
    CC_SAFE_RELEASE_NULL(m_pArrayMsg);
    
    SOCKET_MSG_UNREGIST(SC_FRIEND_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GET_ADD_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_EXPLORE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_ADD);
    SOCKET_MSG_UNREGIST(SC_FRIEND_DELETE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NOTIFY_DELETE)
    SOCKET_MSG_UNREGIST(SC_FRIEND_NEW);
    
    SOCKET_MSG_UNREGIST(SC_FRIEND_SEND_ENERGY);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY_ME);
    SOCKET_MSG_UNREGIST(SC_FRIEND_SEND_ENERGY_ME);
    
    SOCKET_MSG_UNREGIST(SC_HOMESTEAD_SYNC_MATING_COOL_SECOND);
    SOCKET_MSG_UNREGIST(SC_HOMESTEAD_SYNC_GER);
    SOCKET_MSG_UNREGIST(SC_HOMESTEAD_SYNC_ADD_ENGRY);
    
    SOCKET_MSG_UNREGIST(SC_FRIEND_ADD_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NEW_ADD);
    SOCKET_MSG_UNREGIST(SC_FRIEND_AGREE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_REFUSE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_FIGHT);
}

MB_FriendMgr* MB_FriendMgr::getInstance()
{
    if (s_pFriendMgr == NULL)
    {
        s_pFriendMgr = new MB_FriendMgr();
    }
    
    return s_pFriendMgr;
}

void MB_FriendMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pFriendMgr);
    s_pFriendMgr = NULL;
}

void MB_FriendMgr::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_FRIEND_GET_LIST:
            recvfriend_get_list(recvPacket);
            break;
        case SC_FRIEND_GET_ADD_LIST:
            recvfriend_get_add_list(recvPacket);
            break;
        case SC_FRIEND_ADD:
            recvfriend_add(recvPacket);
            break;
        case SC_FRIEND_DELETE:
            recvfriend_delete(recvPacket);
        case SC_FRIEND_NOTIFY_DELETE:
            recvfriend_notify_delete(recvPacket);
            break;
        case SC_FRIEND_EXPLORE:
            recvfriend_explore(recvPacket);
            break;
        case SC_FRIEND_NEW:
            recvfriend_new(recvPacket);
            break;
        case SC_FRIEND_SEND_ENERGY:
            recvfriend_send_energy(recvPacket);
            break;
        case SC_FRIEND_GIVE_ENERGY:
            recvfriend_give_energy(recvPacket);
            break;
        case SC_FRIEND_GIVE_ENERGY_ME:
            recvfriend_give_energy_me(recvPacket);
        case SC_FRIEND_SEND_ENERGY_ME:
            recvfriend_send_energy_me(recvPacket);
            break;
        case SC_HOMESTEAD_SYNC_ADD_ENGRY:
            recvhomestead_sync_add_enagy(recvPacket);
            break;
        case SC_HOMESTEAD_SYNC_GER:
            recvhomestead_sync_pet(recvPacket);
            break;
        case SC_HOMESTEAD_SYNC_MATING_COOL_SECOND:
            recvhomestead_sync_mating_cool_second(recvPacket);
            break;
        case SC_FRIEND_ADD_LIST:
            recvfriend_add_list(recvPacket);
            break;
        case SC_FRIEND_NEW_ADD:
            recvfriend_new_add(recvPacket);
            break;
        case SC_FRIEND_AGREE:
            recvfriend_agree(recvPacket);
            break;
        case SC_FRIEND_REFUSE:
            recvfriend_refuse(recvPacket);
            break;
        case SC_FRIEND_FIGHT:
            recvfriend_fight(recvPacket);
            break;
        default:
            break;
    }
    
}

int MB_FriendMgr::getFriendLevel(uint32_t roleId)
{
    MB_DataFriend* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pArrayFriend, MB_DataFriend*, pTemp)
    {
        if (roleId == pTemp->getRoleID())
        {
            return pTemp->getLevel();
        }
    }
    
    return 1;
}

bool MB_FriendMgr::parseFriend(CCArray* pArray, MB_MsgBuffer* recvPacket, bool bClear)
{
    if (bClear) {
        pArray->removeAllObjects();
    }
    
    uint16_t count = 0;
    uint8_t data8;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    if (recvPacket->readU16(&count)) {
        for (int i = 0; i < count; i++)
        {
            MB_DataFriend* dataFriend = new MB_DataFriend();
            if (recvPacket->readU32(&data32)) {
                dataFriend->setRoleID(data32);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setIsMale(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setLevel(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setTitle(data8);
            }
            
            char* strData = recvPacket->ReadString();
            if (strData != NULL) {
                dataFriend->setRoleName(strData);
            }
            CC_SAFE_FREE(strData);
            
            if (recvPacket->readU64(&data64)) {
                dataFriend->setFightPower(data64);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setLogoutTime(data32);
            }
            
            char* location = recvPacket->ReadString();
            if (location != NULL) {
                dataFriend->setLocation(location);
            }
            CC_SAFE_FREE(location);
            
            if (recvPacket->readU32(&data32)) {
                dataFriend->setHead(data32);
            }
            
            if (recvPacket->readU32(&data32)) {
                dataFriend->setMatingCoolSecond(data32);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setMonsterTID(data32);
            }
            if (recvPacket->readU16(&data16)) {
                dataFriend->setRank(data16);
            }
//            if (recvPacket->readU8(&data8)) {
//                dataFriend->setCanGold(data8);
//            }
//            if (recvPacket->readU8(&data8)) {
//                dataFriend->setCanBadge(data8);
//            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setCanGiveEnergy(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setCanSendEnergy(data8);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setSendTime(data32);
            }
            /*
             required		int32				beginGold				=16[default=0];//充能(金幣)開始時間
             required		int32				endGold					=17[default=0];//充能(金幣)結束時間
             required		int32				beginBadge              =18[default=0];//充能(徽章)開始時間
             required		int32				endBadge				=19[default=0];//充能(徽章)結束時間
             */
            recvPacket->readU32(&data32);
            dataFriend->setBeginGold(data32);
            recvPacket->readU32(&data32);
            dataFriend->setEndGold(data32);
            recvPacket->readU32(&data32);
            dataFriend->setBeginBadge(data32);
            recvPacket->readU32(&data32);
            dataFriend->setEndBadge(data32);
            
            //是否可挑戰
            recvPacket->readU8(&data8);
            dataFriend->setCanFight(data8 == 0);
            
            pArray->addObject(dataFriend);
            dataFriend->release();
        }
        //std::sort(pArray->data->arr,pArray->data->arr + pArray->data->num,sortArray);
    }
    else
    {
        return false;
    }
    
    return true;
}

bool MB_FriendMgr::parseExploreFriend(CCArray* pArray, MB_MsgBuffer* recvPacket, bool bClear)
{
    if (bClear) {
        pArray->removeAllObjects();
    }
    
    uint16_t count = 0;
    uint8_t data8;
    //uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    if (recvPacket->readU16(&count)) {
        for (int i = 0; i < count; i++)
        {
            MB_DataFriend* dataFriend = new MB_DataFriend();
            if (recvPacket->readU32(&data32)) {
                dataFriend->setRoleID(data32);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setIsMale(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setLevel(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setTitle(data8);
            }
            
            char* strData = recvPacket->ReadString();
            if (strData != NULL) {
                dataFriend->setRoleName(strData);
            }
            CC_SAFE_FREE(strData);
            
            if (recvPacket->readU64(&data64)) {
                dataFriend->setFightPower(data64);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setLogoutTime(data32);
            }
            
            char* location = recvPacket->ReadString();
            if (location != NULL) {
                dataFriend->setLocation(location);
            }
            CC_SAFE_FREE(location);
            
            if (recvPacket->readU32(&data32)) {
                dataFriend->setHead(data32);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setCanAdd(data8);
            }

            pArray->addObject(dataFriend);
            dataFriend->release();
        }
        std::sort(pArray->data->arr,pArray->data->arr + pArray->data->num,sortArray);

    }
    else
    {
        return false;
    }
    
    return true;
}
bool MB_FriendMgr::sendfriend_get_list(uint8_t type)
{
    if ( MB_ClientSocket::getInstance()->getServerTime() - m_uLastGetFriendListTime < 120)
    {
        return false;
    }
    m_uLastGetFriendListTime = MB_ClientSocket::getInstance()->getServerTime();
    SOCKET_REQUEST_START(CS_FRIEND_GET_LIST);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_FRIEND_GET_LIST, MB_FriendMgr::onMsgRecv);
    return true;
}

bool MB_FriendMgr::recvfriend_get_list(MB_MsgBuffer *recvPacket)
{
    uint8_t type = 0;
    uint8_t data8;
    if (recvPacket->readU8(&type)) {
        if (type == 1) {    //好友
            parseFriend(m_pArrayFriend, recvPacket, true);
        }
        else if (type == 2)
        {
            parseFriend(m_pArrayEnemy, recvPacket, true);
        }
    }
    recvPacket->readU8(&data8);
    setGetEnergyLastTimes(data8);
    recvPacket->readU8(&data8);
    setLimitGetEnergyTimes(data8);
    recvPacket->readU8(&m_uFightTimes);
    
    return true;
}

bool MB_FriendMgr::sendfriend_get_add_list()
{
    SOCKET_REQUEST_START(CS_FRIEND_GET_ADD_LIST);
    SOCKET_REQUEST_END(SC_FRIEND_GET_ADD_LIST, MB_FriendMgr::onMsgRecv);
    return true;
}

bool MB_FriendMgr::recvfriend_get_add_list(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    return parseExploreFriend(m_pArrayExplore, recvPacket, true);
}

bool MB_FriendMgr::sendfriend_explore(std::string roleName)
{
    SOCKET_REQUEST_START(CS_FRIEND_EXPLORE);
    packet->Write(roleName.c_str(), roleName.length());
    SOCKET_REQUEST_END(SC_FRIEND_EXPLORE, MB_FriendMgr::onMsgRecv);
    return true;
}

bool MB_FriendMgr::recvfriend_explore(MB_MsgBuffer *recvPacket)
{
    return parseExploreFriend(m_pArrayExplore, recvPacket, true);
}

bool MB_FriendMgr::sendfriend_add(int nCount,uint32_t* list)
{
    SOCKET_REQUEST_START(CS_FRIEND_ADD);
    packet->writeU16(nCount);
    for (int i = 0; i < nCount; i++) {
        packet->writeU32(list[i]);
    }
    SOCKET_REQUEST_END(SC_FRIEND_ADD, MB_FriendMgr::onMsgRecv);
    return true;
}

bool MB_FriendMgr::recvfriend_add(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint8_t result = 0;
    if (recvPacket->readU8(&result))
    {
        if (result == 1) {
            MB_Message::sharedMB_Message()->showMessage("成功发送邀请.");
        }
        else
        {
            if (result == 2) {
                MB_Message::sharedMB_Message()->showMessage("已经是您的好友.");
            }
            else if (result == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("邀请失败, 未知原因.");
            }
            else if (result == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("您的好友已满.");
            }
            else if (result == 5)
            {
                MB_Message::sharedMB_Message()->showMessage("已经发送过邀请了.");
            }
            else if (result == 6)
            {
                MB_Message::sharedMB_Message()->showMessage("已达到申请加好友上限.");
            }
            else if (result == 7)
            {
                MB_Message::sharedMB_Message()->showMessage("对方已达到被申请加好友上限.");
            }
            else
            {
                MB_Message::sharedMB_Message()->removeALLMessage();
            }
        }
    }
    return true;
}

bool MB_FriendMgr::sendfriend_delete(uint8_t type, uint32_t roleID)
{
    SOCKET_REQUEST_START(CS_FRIEND_DELETE);
    packet->writeU8(type);
    packet->writeU32(roleID);
    SOCKET_REQUEST_END(SC_FRIEND_DELETE, MB_FriendMgr::onMsgRecv);
    return true;
}

bool MB_FriendMgr::recvfriend_delete(MB_MsgBuffer *recvPacket)
{
    uint8_t result = 0, type;
    uint32_t data32;
    if (recvPacket->readU8(&result)) {
        if (result == 1) {
            MB_Message::sharedMB_Message()->showMessage("删除成功.");
            if (recvPacket->readU8(&type) && recvPacket->readU32(&data32)) {
                CCArray* unitArray = NULL;
                if (type == 1)
                {
                    unitArray = m_pArrayFriend;
                }
                else
                {
                    unitArray = m_pArrayEnemy;
                }
                MB_DataFriend* dataFriend = NULL;
                for (int i = 0; i < unitArray->count(); i++) {
                    dataFriend = (MB_DataFriend*)unitArray->objectAtIndex(i);
                    if (dataFriend->getRoleID() == data32) {
                        unitArray->removeObjectAtIndex(i);
                        break;
                    }
                }
            }
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("删除失败, 未知原因.");
        }
    }
    return true;
}

bool MB_FriendMgr::recvfriend_notify_delete(MB_MsgBuffer *recvPacket)
{
    uint8_t type;
    uint32_t data32;
    if (recvPacket->readU8(&type))
    {
        if (type == 1)
        {
            if (recvPacket->readU32(&data32))
            {
                MB_DataFriend* dataFriend = NULL;
                for (int i = 0; i < m_pArrayFriend->count(); i++)
                {
                    dataFriend = (MB_DataFriend*)m_pArrayFriend->objectAtIndex(i);
                    if (dataFriend->getRoleID() == data32)
                    {
                        m_pArrayFriend->removeObjectAtIndex(i);
                        break;
                    }
                }
            }
        }
    }
    return true;
}

bool MB_FriendMgr::recvfriend_new(MB_MsgBuffer *recvPacket)
{
    uint8_t type = 0, data8;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    if (recvPacket->readU8(&type)) {
        if (type == 1)
        {
            MB_DataFriend* dataFriend = new MB_DataFriend();
            if (recvPacket->readU32(&data32)) {
                dataFriend->setRoleID(data32);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setIsMale(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setLevel(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setTitle(data8);
            }

            char* strData = recvPacket->ReadString();
            if (strData != NULL) {
                dataFriend->setRoleName(strData);
            }
            CC_SAFE_FREE(strData);
            
            if (recvPacket->readU64(&data64)) {
                dataFriend->setFightPower(data64);
            }
      
            if (recvPacket->readU32(&data32)) {
                dataFriend->setLogoutTime(data32);
            }
        
            char* strData2 = recvPacket->ReadString();
            if (strData2 != NULL) {
                dataFriend->setLocation(strData2);
            }
            CC_SAFE_FREE(strData2);
            if (recvPacket->readU32(&data32)) {
                dataFriend->setHead(data32);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setMatingCoolSecond(data32);
            }
            if (recvPacket->readU32(&data32)) {
                
                dataFriend->setMonsterTID(data32);
            }
            if (recvPacket->readU16(&data16)) {
                dataFriend->setRank(data16);
            }
//            if (recvPacket->readU8(&data8)) {
//                dataFriend->setCanGold(data8);
//            }
//            if (recvPacket->readU8(&data8)) {
//                dataFriend->setCanBadge(data8);
//            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setCanGiveEnergy(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setCanSendEnergy(data8);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setSendTime(data32);
            }
            /*
             required		int32				beginGold				=16[default=0];//充能(金幣)開始時間
             required		int32				endGold					=17[default=0];//充能(金幣)結束時間
             required		int32				beginBadge              =18[default=0];//充能(徽章)開始時間
             required		int32				endBadge				=19[default=0];//充能(徽章)結束時間
             */
            recvPacket->readU32(&data32);
            dataFriend->setBeginGold(data32);
            recvPacket->readU32(&data32);
            dataFriend->setEndGold(data32);
            recvPacket->readU32(&data32);
            dataFriend->setBeginBadge(data32);
            recvPacket->readU32(&data32);
            dataFriend->setEndBadge(data32);
            
            //是否可挑戰
            recvPacket->readU8(&data8);
            dataFriend->setCanFight(data8 == 0);
            m_pArrayFriend->addObject(dataFriend);
        }
        else if (type == 2)
        {
            MB_DataFriend* dataFriend = new MB_DataFriend();
            if (recvPacket->readU32(&data32)) {
                dataFriend->setRoleID(data32);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setIsMale(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setLevel(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dataFriend->setTitle(data8);
            }
            
            char* strData = recvPacket->ReadString();
            if (strData != NULL) {
                dataFriend->setRoleName(strData);
            }
            CC_SAFE_FREE(strData);
            
            if (recvPacket->readU64(&data64)) {
                dataFriend->setFightPower(data64);
            }
            if (recvPacket->readU32(&data32)) {
                dataFriend->setLogoutTime(data32);
            }
            
            m_pArrayEnemy->addObject(dataFriend);
        }
    }
    std::sort(m_pArrayFriend->data->arr,m_pArrayFriend->data->arr + m_pArrayFriend->data->num,sortArray);
    return true;
}


void MB_FriendMgr::sendfriend_fight(uint32_t roleid)
{
    m_uFightRoleID = roleid;
    SOCKET_REQUEST_START(CS_FRIEND_FIGHT);
    packet->writeU32(roleid);
    SOCKET_REQUEST_END(SC_FRIEND_FIGHT, MB_FriendMgr::onMsgRecv);
}

/*
 message sc_friend_fight[id=11705]{
 required    int8                result          =1;//請求結果
 // 0=> 成功發起挑戰
 // 1=> 發起挑戰失敗，無此好友
 // 2=> 發起挑戰失敗，已經挑戰
 // 3=> 發起挑戰失敗，挑戰次數不足
 required    int32               addCoin         =2;//獎勵金幣
 required    int32               addRepu         =3;//獎勵漿果
 repeated    sc_fight_request    fightInfo       =4;//戰鬥結果
 }
 */
void MB_FriendMgr::recvfriend_fight(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    MB_DataFriend* data = NULL;
    if(queryFriendDataByRoleID(m_uFightRoleID,&data))
    {
        data->setCanFight(false);
        if (m_uFightTimes > 0) {
            --m_uFightTimes;
        }
    }
    else
    {
        return;
    }
    recvPacket->readU8(&result);
    if (result == 0) {
        uint32_t coin,repu;
        recvPacket->readU32(&coin);
        recvPacket->readU32(&repu);

        //戰鬥具体信息
        MB_NetStructFight fight;
        short data16 ;
        recvPacket->readU16(&data16);
        recvfight * fightresult = fight.recvfight_request(recvPacket);
        fightresult->type = kFightResultTypeFriendFight;
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,coin,repu));

    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("挑战失败，无此好友");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("挑战失败，已经挑战");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("挑战失败，挑战次数不足");
    }
    
}
//赠送体力部分
bool MB_FriendMgr::sendfriend_send_energy(int nCount,uint32_t* list)
{
    SOCKET_REQUEST_START(CS_FRIEND_SEND_ENERGY);
    packet->writeU16(nCount);
    for (int i = 0; i < nCount; i++) {
        packet->writeU32(list[i]);
    }
    SOCKET_REQUEST_END(SC_FRIEND_SEND_ENERGY, MB_FriendMgr::onMsgRecv);
    return true;
}
bool MB_FriendMgr::recvfriend_send_energy(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t data8;
    uint32_t data32;
    if (recvPacket->readU8(&data8))
    {
        if (data8 == 1)//贈送成功
        {
            if (recvPacket->readU32(&data32))
            {
                int nCount = m_pArrayFriend->count();
                for(int i = 0;i < nCount;i++)
                {
                    MB_DataFriend* data = (MB_DataFriend*)m_pArrayFriend->objectAtIndex(i);
                    if (data->getRoleID() == data32) {
                        data->setCanSendEnergy(2);
                        MB_Message::sharedMB_Message()->showMessage("赠送体力成功");
                        break;
                    }
                }
            }
        }
        else if(data8 == 2)//表示不是好友
        {
            MB_Message::sharedMB_Message()->showMessage("对方已经不是您的好友");
        }
        else if(data8 == 3)//不可赠送
        {
            MB_Message::sharedMB_Message()->showMessage("不可赠送");
        }
    }
    return true;
}
bool MB_FriendMgr::recvfriend_give_energy_me(MB_MsgBuffer* recvPacket)
{
    uint32_t data32;
    uint8_t data8;
    if (recvPacket->readU32(&data32))//我送了体力的玩家
    {
        if (!recvPacket->readU8(&data8))
        {
            return true;
        }
        int nCount = m_pArrayFriend->count();
        for(int i = 0;i < nCount;i++)
        {
            MB_DataFriend* data = (MB_DataFriend*)m_pArrayFriend->objectAtIndex(i);
            if (data->getRoleID() == data32) {
                data->setCanSendEnergy(data8);
                break;
            }
        }        
    }
    return true;
}
bool MB_FriendMgr::recvfriend_send_energy_me(MB_MsgBuffer* recvPacket)
{
    uint32_t data32;
    if (recvPacket->readU32(&data32))//送我体力的玩家
    {
        int nCount = m_pArrayFriend->count();
        for(int i = 0;i < nCount;i++)
        {
            MB_DataFriend* data = (MB_DataFriend*)m_pArrayFriend->objectAtIndex(i);
            if (data->getRoleID() == data32) {
                data->setCanGiveEnergy(true);
                break;
            }
        }
    }
    return true;
}
bool MB_FriendMgr::sendfriend_give_energy(int nCount,uint32_t* list)
{
    SOCKET_REQUEST_START(CS_FRIEND_GIVE_ENERGY);
    packet->writeU16(nCount);
    for (int i = 0; i < nCount; i++) {
         packet->writeU32(list[i]);
    }
    SOCKET_REQUEST_END(SC_FRIEND_GIVE_ENERGY, MB_FriendMgr::onMsgRecv);
    return true;

}
bool MB_FriendMgr::recvfriend_give_energy(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t data8;
    uint32_t data32;
    uint16_t count = 0;
    if(recvPacket->readU8(&data8))
    {
        if (data8 == 0)
        {
            
        }
        else if(data8 == 1)
        {
            MB_Message::sharedMB_Message()->showMessage("体力值已满");
            return true;
        }
        else if(data8 == 2)
        {
            MB_Message::sharedMB_Message()->showMessage("领取对象错误");
            return true;
        }
        else if(data8 == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("没有可领取的体力");
            return true;
        }
        else if(data8 == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("领取体力次数达到上限");
            return true;
        }
        
    }
    if (recvPacket->readU16(&count))
    {
        for(int i = 0;i < count; i++)
        {
            if (recvPacket->readU32(&data32))//領取該玩家送的体力
            {
                int nCount = m_pArrayFriend->count();
                for(int j = 0;j < nCount;j++)
                {
                    MB_DataFriend* data = (MB_DataFriend*)m_pArrayFriend->objectAtIndex(j);
                    if (data->getRoleID() == data32) {
                        data->setCanGiveEnergy(false);
                        data->setCanSendEnergy(2);
                        break;
                    }
                }
            }
        }
    }
    if (recvPacket->readU8(&data8))//剩餘領取次數
    {
        setGetEnergyLastTimes(data8);
    }
    
    if (count == 1) {
        MB_Message::sharedMB_Message()->showMessage("获得1点体力并回赠好友1点体力");
    }
    else
    {
        char str[128] = {};
        sprintf(str, "总共领取了%d点体力,今天剩余领取次数%d",count,getGetEnergyLastTimes());
        MB_Message::sharedMB_Message()->showMessage("领取成功", str, "确定");
    }
    return true;
}

bool MB_FriendMgr::sendfriend_give_all_enargy()
{
    SOCKET_REQUEST_START(CS_FRIEND_GIVE_ALL_ENERGY);
    SOCKET_REQUEST_END(SC_FRIEND_GIVE_ENERGY, MB_FriendMgr::onMsgRecv);
    return true;
}

int MB_FriendMgr::sortArray(CCObject* p1,CCObject* p2)
{
    if (p1 == NULL || p2 == NULL) {
        return false;
    }
    MB_DataFriend* data1 = dynamic_cast<MB_DataFriend*>(p1);
    MB_DataFriend* data2 = dynamic_cast<MB_DataFriend*>(p2);
    
    if (data1 == NULL || data2 == NULL) {
        return false;
    }
    //优先在线
    if (data1->getLogoutTime() != 0 && data2->getLogoutTime() == 0)
    {
        return true;
    }
    if (data1->getLogoutTime() == 0 && data2->getLogoutTime() != 0)
    {
        return false;
    }
    
    //戰鬥力排序降序
    if(data1->getFightPower() < data2->getFightPower())
    {
        return true;
    }
    if(data1->getFightPower() > data2->getFightPower())
    {
        return false;
    }
    
    //等級排序降序
    if (data1->getLevel() < data2->getLevel())
    {
        return true;
    }
    if (data1->getLevel() > data2->getLevel())
    {
        return false;
    }
    
    //id升序
    if (data1->getRoleID() > data2->getRoleID())
    {
        return true;
    }
    return false;
    
}
bool MB_FriendMgr::queryFriendDataByRoleID(uint32_t roleId,MB_DataFriend** pData)
{
    MB_DataFriend* pTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pArrayFriend, MB_DataFriend*, pTemp)
    {
        if (pTemp->getRoleID() == roleId)
        {
            *pData = pTemp;
            return true;
        }
    }
    
    return false;
}
/*
 message recvhomestead_sync_mating_cool_second[id=20230]{
 required		int32			roleID							=1;
 required		int32			matingCoolSecond	=2;//交配冷卻結束時間
 }
 */
void MB_FriendMgr::recvhomestead_sync_mating_cool_second(MB_MsgBuffer* pRecv)
{
    MB_DataFriend* pData = NULL;
    uint32_t id = 0;
    
    pRecv->readU32(&id);
    if (queryFriendDataByRoleID(id,&pData))
    {
        pRecv->readU32(&id);
        pData->setMatingCoolSecond(id);
    }
}

/*
 message recvhomestead_sync_pet[id=20231]{
 required		int32			roleID							=1;
 required		int32			petTypeID					=2;//守護武將類型
 required		int16			petQuality					=3;//守護武將品质
 }
 */
void MB_FriendMgr::recvhomestead_sync_pet(MB_MsgBuffer* pRecv)
{
    MB_DataFriend* pData = NULL;
    uint32_t id = 0;
    
    pRecv->readU32(&id);
    if (queryFriendDataByRoleID(id,&pData))
    {
        uint16_t u16 = 0;
        pRecv->readU32(&id);
        pData->setMonsterTID(id);
        pRecv->readU16(&u16);
        pData->setRank(u16);
    }
}

/*
 message recvhomestead_sync_add_enagy[id=20232]{
 required		int32				roleID						=1;
 required		int32				beginGold				=2[default=0];//充能(金幣)開始時間
 required		int32               endGold					=3[default=0];//充能(金幣)結束時間
 required		int32				beginBadge              =4[default=0];//充能(徽章)開始時間
 required		int32				endBadge				=5[default=0];//充能(徽章)結束時間
 }
 */
void MB_FriendMgr::recvhomestead_sync_add_enagy(MB_MsgBuffer* pRecv)
{
    MB_DataFriend* pData = NULL;
    uint32_t id = 0;
    
    pRecv->readU32(&id);
    if (queryFriendDataByRoleID(id,&pData))
    {
        pRecv->readU32(&id);
        pData->setBeginGold(id);
        pRecv->readU32(&id);
        pData->setEndGold(id);
        pRecv->readU32(&id);
        pData->setBeginBadge(id);
        pRecv->readU32(&id);
        pData->setEndBadge(id);
    }
}


/*
 message p_friend_add[id=11710]{
 required       int32           roleID           = 1;//請求者ID
 required       int32           timestamp        = 2;//申請時間
 required       bool            isMale           = 3;//性别
 required       int8            level            = 4;//等級
 required       int8            title            = 5;//官爵
 required       string          roleName         = 6;//玩家名称
 required       int64           fightPower       = 7;//总戰鬥力
 required       int32           head             = 8[default=0];//头像
 
 }
 */
bool MB_DataMsgFriend::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU32(&m_uRoleID);
    pRecv->readU32(&m_uLogoutTime);
    pRecv->readU8(&m_bIsMale);
    pRecv->readU8(&m_uLevel);
    pRecv->readU8(&m_uTitle);
    
    char* strData = pRecv->ReadString();
    if (strData != NULL) {
        setRoleName(strData);
    }
    CC_SAFE_FREE(strData);
    
    pRecv->readU64(&m_uFightPower);
    pRecv->readU32(&m_uHead);
    
    return true;
}

//好友請求
void MB_FriendMgr::sendfriend_add_list() //好友請求消息列表
{
    SOCKET_REQUEST_START(CS_FRIEND_ADD_LIST);
    SOCKET_REQUEST_END(SC_FRIEND_ADD_LIST, MB_FriendMgr::onMsgRecv);
}
void MB_FriendMgr::recvfriend_add_list(MB_MsgBuffer* pRecv)
{
    uint16_t count = 0;
    m_pArrayMsg->removeAllObjects();
    pRecv->readU16(&count);
    for (int i = 0;i < count;i++)
    {
        MB_DataMsgFriend* data = new MB_DataMsgFriend;
        data->read(pRecv);
        m_pArrayMsg->addObject(data);
        data->release();
    }
    
    
}
void MB_FriendMgr::recvfriend_new_add(MB_MsgBuffer* pRecv) //新增好友請求消息請求
{
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    for (int i = 0;i < count;i++)
    {
        MB_DataMsgFriend* data = new MB_DataMsgFriend;
        data->read(pRecv);
        m_pArrayMsg->addObject(data);
        data->release();
    }
}
void MB_FriendMgr::sendfriend_agree(int nCount,uint32_t* list) //同意加好友
{
    SOCKET_REQUEST_START(CS_FRIEND_AGREE);
    packet->writeU16(nCount);
    for (int i = 0; i < nCount; i++) {
        packet->writeU32(list[i]);
    }
    SOCKET_REQUEST_END(SC_FRIEND_AGREE, MB_FriendMgr::onMsgRecv);
}
void MB_FriendMgr::recvfriend_agree(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    if (pRecv->readU8(&result))
    {
        if (result == 0)
        {
            
        }
        else if(result == 1)
        {
            MB_Message::sharedMB_Message()->showMessage("对方好友超过上限");
        }
        else if(result == 2)
        {
            MB_Message::sharedMB_Message()->showMessage("您的好友超过上限");
        }
        else if(result == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("对方已经是好友了");
        }
        else if(result == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("获取同意方信息失败");
        }
        else if(result == 5)
        {
            MB_Message::sharedMB_Message()->showMessage("获取请求方信息失败");
        }
        
    }
}
void MB_FriendMgr::sendfriend_refuse(int nCount,uint32_t* list) //拒绝加好友
{
    SOCKET_REQUEST_START(CS_FRIEND_REFUSE);
    packet->writeU16(nCount);
    for (int i = 0; i < nCount; i++) {
        packet->writeU32(list[i]);
    }
    SOCKET_REQUEST_END(SC_FRIEND_REFUSE, MB_FriendMgr::onMsgRecv);
}
;

void MB_FriendMgr::recvfriend_refuse(MB_MsgBuffer* pRecv)
{

}

