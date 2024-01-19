//
//  MB_GuardInterface.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-3.
//
//

#include "MB_GuardInterface.h"
#include "MB_GuardProtocol.h"
#include "MB_ClientSocket.h"
#include "MB_Message.h"


MB_GuardInterface* MB_GuardInterface::m_pInstance = NULL;

MB_GuardInterface::MB_GuardInterface()
{
    m_pRule = new MB_PetGuardRule();
    if (!m_pRule->init())
    {
        CCLOG("ERROR: MB_GuardInterface load error");
    }
    for (int i = 0;i < MEMBER_NUM; i++)
    {
        m_pData[i] = NULL;
    }
    m_uCurPos = 0;
    SOCKET_MSG_REGIST(SC_PET_GUARD_INFO,MB_GuardInterface);
    SOCKET_MSG_REGIST(SC_PET_GUARD_SET,MB_GuardInterface);
    SOCKET_MSG_REGIST(SC_PET_GUARD_REFRESH,MB_GuardInterface);
}

MB_GuardInterface::~MB_GuardInterface()
{
    for (int i = 0;i < MEMBER_NUM; i++)
    {
        CC_SAFE_RELEASE_NULL(m_pData[i]);
    }
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_INFO);
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_SET);
    SOCKET_MSG_UNREGIST(SC_PET_GUARD_REFRESH);
}
MB_GuardInterface* MB_GuardInterface::getInstance()
{
    if(m_pInstance == NULL){
        
        m_pInstance = new MB_GuardInterface();
        
    }
    return m_pInstance;
}
void MB_GuardInterface::destroyInstance()
{
    if (m_pInstance != NULL) {
        
        delete  m_pInstance;
        m_pInstance = NULL;
    }
}

void MB_GuardInterface::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_PET_GUARD_INFO:
            recv_PetGuardInfo(recvPacket);
            break;
        case SC_PET_GUARD_SET:
            recv_PetGuardSet(recvPacket);
            break;
        case SC_PET_GUARD_REFRESH:
            recv_PetGuardRefresh(recvPacket);
            break;
        default:
            break;
    }
}
void MB_GuardInterface::send_PetGuardInfo()
{
    SOCKET_REQUEST_START(CS_PET_GUARD_INFO);
    SOCKET_REQUEST_END(SC_PET_GUARD_INFO,NULL);
}
/*
 message     sc_ger_guard_info[id=10445]{
 repeated    p_ger_guard         list            =1;//守護精靈信息及屬性加成信息
 }
 */
void MB_GuardInterface::recv_PetGuardInfo(MB_MsgBuffer* pRecv)
{
    uint16_t len;
    pRecv->readU16(&len);
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL)
        {
            CC_SAFE_RELEASE_NULL(m_pData[i]);
        }
    }
    for (int i = 0;i < len;i++)
    {
        m_pData[i] = new MB_PetGuardData();
        m_pData[i]->read(pRecv);
    }
}
/*
 message     cs_ger_guard_set[id=10446]{
 required    int64               gerID           =1;//放入的守護精靈ID
 required    int8                gerPos          =2;//放入的位置,1-6
 }
 */
void MB_GuardInterface::send_PetGuardSet(uint64_t uid,uint8_t pos)
{
    SOCKET_REQUEST_START(CS_PET_GUARD_SET);
    packet->WriteUINT64(uid);
    packet->writeU8(pos);
    SOCKET_REQUEST_END(SC_PET_GUARD_SET,NULL);
}
/*
 message     sc_ger_guard_set[id=10447]{
 required        int8                result          =1;//0成功,1背包中無此卡牌，2經驗卡片，3位置參數錯誤，4出戰卡牌中有同類卡牌，5守護精靈中有同類卡牌 ,6對應位置無上陣卡牌
 required        int64               gerID           =2;//放入的守護精靈ID
 required        int8                gerPos          =3;//放入的位置,1-6
 repeated        p_ger_guard_attr    baseList        =4;//新的基础屬性
 }
 */
void MB_GuardInterface::recv_PetGuardSet(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    pRecv->readU8(&result);
    if (result == 0)
    {
        uint64_t uid;
        pRecv->readU64(&uid);
        uint8_t pos;
        pRecv->readU8(&pos);        
        bool bHasPet = false;//是否替換
        for (int i = 0;i < MEMBER_NUM;i++) {
            if (m_pData[i] != NULL)
            {
                if(m_pData[i]->getPetPos() == pos)
                {
                    bHasPet = true;
                    m_pData[i]->setPetUid(uid);
                    m_pData[i]->setBaseAttr(pRecv);
                    return;
                }
            }
        }
        
        if (!bHasPet)
        {
            
            for (int i = 0;i < MEMBER_NUM;i++) {
                if (m_pData[i] == NULL)
                {
                    m_pData[i] = new MB_PetGuardData();
                    m_pData[i]->setPetUid(uid);
                    m_pData[i]->setPetPos(pos);
                    m_pData[i]->setBaseAttr(pRecv);\
                    return;
                }
            }
            
        }

    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("背包中无此卡牌");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("经验卡片不能作为守护");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("位置参数错误");
    }
    else if(result == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("出战卡牌中有同类卡牌");
    }
    else if(result == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("守护中有同类卡牌");
    }
    else if(result == 6)
    {
        MB_Message::sharedMB_Message()->showMessage("对应位置无上阵卡牌");
    }

}
/*
 message     cs_ger_guard_refresh[id=10448]{
 required    int8                gerPos          =1;//刷新的位置，1-6
 repeated    bool                lockList        =2;//鎖定信息，false表示沒鎖定，true表示鎖定，六个高級屬性的鎖定狀態按顺序填到这个數組里面
 */
void MB_GuardInterface::send_PetGuardRefresh(uint8_t pos,bool* list)
{
    m_uCurPos = pos;
    SOCKET_REQUEST_START(CS_PET_GUARD_REFRESH);
    packet->writeU8(pos);
    packet->writeU16(GUARD_ATTR_MAX);
    for (int i = 0;i < GUARD_ATTR_MAX; i++)
    {
        packet->writeU8(list[i]);
    }
    SOCKET_REQUEST_END(SC_PET_GUARD_REFRESH,NULL);
}
/*
 message     sc_ger_guard_refresh[id=10449]{
 required    int8                result          =1;//0成功,1未放入守護精靈，2鎖定參數錯誤，3高級屬性低於2条，不能鎖定，4鎖定了未激活屬性，5不能鎖住全部屬性，6寶石不足
 repeated    p_ger_guard_attr    highList        =2;//新的高級屬性信息
 }
 */
void MB_GuardInterface::recv_PetGuardRefresh(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    pRecv->readU8(&result);
    if (result == 0)
    {
        MB_PetGuardData* data =  getPetGuardDataByPos(m_uCurPos);
        if (data != NULL)
        {
            data->setHightAttr(pRecv);
        }
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("未放入守护");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("锁定参数错误");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("高级属性低于2条，不能锁定");
    }
    else if(result == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("锁定了未激活属性");
    }
    else if(result == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("不能锁住全部属性");
    }
    else if(result == 6)
    {
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
    }

    
}

MB_PetGuardData* MB_GuardInterface::getPetGuardDataByPos(uint8_t pos)
{
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL && m_pData[i]->getPetPos() == pos)
        {
            return m_pData[i];
        }
    }
    return NULL;
}
MB_PetGuardData* MB_GuardInterface::getPetGuardDataByUid(uint64_t uid)
{
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL && m_pData[i]->getPetUid() == uid)
        {
            return m_pData[i];
        }
    }
    CCLOG("ERROR:MB_GuardInterface not find uid=%d",uid);
    return NULL;
}
bool MB_GuardInterface::checkIsGuardPos(uint8_t pos)
{
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL && m_pData[i]->getPetPos() == pos)
        {
            return true;
        }
    }
    return false;
}
//检查是否守護精靈
bool MB_GuardInterface::checkIsGuardPet(uint64_t uid)
{
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL && m_pData[i]->getPetUid() == uid)
        {
            return true;
        }
    }
    CCLOG("ERROR:MB_GuardInterface not find uid=%d",uid);
    return false;
}

bool MB_GuardInterface::checkIsGuardPetType(uint16_t tid)
{
    for (int i = 0;i < MEMBER_NUM;i++)
    {
        if (m_pData[i] != NULL)
        {
            MB_PetTemplate* petTemplate = MB_PetMgr::getInstance()->getPetTemplateByUID(m_pData[i]->getPetUid());
            if (petTemplate != NULL && petTemplate->getPetTypeID() == tid)
            {
                return true;
            }
        }
    }
    CCLOG("ERROR:MB_GuardInterface not find tid=%d",tid);
    return false;
}

uint8_t MB_GuardInterface::getRankByValAndType(uint32_t val,uint8_t type)
{
    return m_pRule->getRankByValAndType(val,type);
}

uint32_t MB_GuardInterface::getCostByLockNum(int num)
{
    return m_pRule->getCostByLockNum(num);
}
