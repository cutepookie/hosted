//
//  MB_FunctionKingInterface.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#include "MB_FunctionKingInterface.h"
#include "MB_NodeKingEntry.h"
#include "MB_LayerKing.h"
#include "MB_KingProtocol.h"
#include "MB_DefineProto.h"
#include "MB_SceneGame.h"
MB_FunctionKingInterface::MB_FunctionKingInterface()
{
    m_pKingInfo = new KingInfo();
    SOCKET_MSG_REGIST(SC_KING_OPEN, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_KING_INIT_STATE, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_KING_STOP, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_KING_FIGHT, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_KING_OPEN_TIME, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_KING_HP_SYNC, MB_FunctionKingInterface);
    SOCKET_MSG_REGIST(SC_PUSH_HIGHLIGHT_INFO, MB_FunctionKingInterface);
}
MB_FunctionKingInterface::~MB_FunctionKingInterface()
{
    CC_SAFE_RELEASE_NULL(m_pKingInfo);
    SOCKET_MSG_UNREGIST(SC_KING_OPEN);
    SOCKET_MSG_UNREGIST(SC_KING_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_KING_STOP);
    SOCKET_MSG_UNREGIST(SC_KING_FIGHT);
    SOCKET_MSG_UNREGIST(SC_KING_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_KING_HP_SYNC);
    SOCKET_MSG_UNREGIST(SC_PUSH_HIGHLIGHT_INFO);
}
MB_ResWindow* MB_FunctionKingInterface::createEntryDialog()
{
    MB_NodeKingEntry* pInstance = new MB_NodeKingEntry;
    if (pInstance && pInstance->init() && pInstance->setDataSource(this) )
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
MB_ResWindow* MB_FunctionKingInterface::createFunctionDialog()
{
    MB_LayerKing* pInstance = new MB_LayerKing;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
void MB_FunctionKingInterface::onLoadingScene()
{
    cs_king_open_time();
}

void MB_FunctionKingInterface::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_KING_OPEN:
            sc_king_open(recvPacket);
            break;
        case SC_KING_INIT_STATE:
            sc_king_init_state(recvPacket);
            break;
        case SC_KING_STOP:
            sc_king_stop(recvPacket);
            break;
        case SC_KING_FIGHT:
            MB_Message::sharedMB_Message()->removeALLMessage();
            sc_king_fight(recvPacket);
            break;
        case SC_KING_OPEN_TIME:
            sc_king_open_time(recvPacket);
            break;
        case SC_KING_HP_SYNC:
            sc_king_hp_sync(recvPacket);
            break;
        case SC_PUSH_HIGHLIGHT_INFO:
            uint8_t data8;
            recvPacket->readU8(&data8);
            if(data8 == 1)
            {
                recvPacket->readU8(&data8);
                setOpenStatus(data8 == 1);
            }
            break;
            
            
        default:
            break;
    }
}

void MB_FunctionKingInterface::setOpenStatus(bool bOpen)
{
    m_pKingInfo->setIsOpen(bOpen);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(open_status_notify.c_str());
}
bool MB_FunctionKingInterface::allowShow()
{
    return true;
}
uint16_t MB_FunctionKingInterface::getFunctionType()
{
    return kFunctionKing;
}

void MB_FunctionKingInterface::cs_king_open()
{
    SOCKET_REQUEST_START(CS_KING_OPEN);
    SOCKET_REQUEST_END(SC_KING_OPEN, NULL);
}

/*
 message sc_hula_open[id=14002]{
 required	bool		isOpen			=1;//活動是否開始
 repeated    p_hula_boss_open    list    =2;//boss信息
 required	int32		beginTime		=7;//活動開始時間
 }
 */
void MB_FunctionKingInterface::sc_king_open(MB_MsgBuffer* pRecv)
{
    uint8_t data8;
    uint32_t data32;
    pRecv->readU8(&data8);
    setOpenStatus(data8);
    m_pKingInfo->setBossInfo(pRecv);
    pRecv->readU32(&data32);
    m_pKingInfo->setOpenTime(data32);
    if (data32 == 0)
    {
        setOpenStatus(false);
    }
}

/*
 // 請求cs_hula_open后，如果當前活動正在進行，则返回下面一条协议
 message	sc_hula_init_state[id=14004]{
 repeated    p_hula_boss_state  list     =1;//當前boss信息
 required    int64       curHarm         =2;//當前累积傷害
 required	int32		curRank			=3;//當前排名
 required	int32		rebornTime		=4;//複活時間，當前非倒計時狀態，则此值為0
 required    int32       endTime         =5;//
 }
 */
void MB_FunctionKingInterface::sc_king_init_state(MB_MsgBuffer* pRecv)
{
    uint64_t data64;
    uint32_t data32;
    m_pKingInfo->setBossState(pRecv);
    pRecv->readU64(&data64);
    pRecv->readU32(&data32);
    pRecv->readU32(&data32);
    m_pKingInfo->setRebornTime(data32);
    pRecv->readU32(&data32);
    m_pKingInfo->setEndTime(data32);
}

void MB_FunctionKingInterface::cs_king_close()
{
    SOCKET_REQUEST_START(CS_KING_CLOSE);
    SOCKET_REQUEST_END(CS_KING_CLOSE, NULL);
}

/*
 // 通知玩家活動結束
 message	sc_hula_stop[id=14013]{
 required	int8		type				=1;//活動結束類型
 required    int32       nextTime            =2;//
 // 1=> 吕布被活活打死了
 // 2=> 吕布苟幸活下来了
 required	p_role_stastic	roleSta			=3;
 }
 */
void MB_FunctionKingInterface::sc_king_stop(MB_MsgBuffer* pRecv)
{
    uint8_t data8;
    uint32_t data32;
    pRecv->readU8(&data8);
    pRecv->readU32(&data32);
    m_pKingInfo->setOpenTime(data32);
    m_pKingInfo->setResult(pRecv);
    setOpenStatus(false);
}

void MB_FunctionKingInterface::cs_king_fight()
{
    SOCKET_REQUEST_START(CS_KING_FIGHT);
    SOCKET_REQUEST_END(SC_KING_FIGHT, NULL);
}

void MB_FunctionKingInterface::cs_king_reborn()
{
    SOCKET_REQUEST_START(CS_KING_REBORN);
    SOCKET_REQUEST_END(SC_KING_FIGHT, NULL);
}
/*
 message	sc_hula_fight[id=14017]{
 required	int8		result			=1;//請求結果
 // 1=> 請求成功
 // 2=> 請求失敗， 等待複活中
 // 3=> 請求失敗，boss已死亡
 // 4=> 請求失敗，活動已經結束
 // 5=> 請求失敗，您當前处於離線參與中
 // 6=> 請求失敗，未知錯誤
 repeated	sc_fight_request	fightInfo	=2;//戰鬥播放信息
 required	int32				rebornTime 	=3;//複活時間，unixTime
 required	int32				rewardCoin	=4;//獲得的银两
 required	int32				rewardReputation=5;//獲得的声望
 
 }
 */
void MB_FunctionKingInterface::sc_king_fight(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    uint32_t data32;
    pRecv->readU8(&result);
    

    if (result == 1)
    {
        //戰鬥具体信息
        MB_NetStructFight fight;
        short data16 ;
        pRecv->readU16(&data16);
        recvfight * fightresult = fight.recvfight_request(pRecv);
        fightresult->type = kFightResultTypeKing;
        //獎勵信息
        pRecv->readU32(&data32);
        m_pKingInfo->setRebornTime(data32);
        pRecv->readU32(&data32);
        int rewardcoin = data32;
        pRecv->readU32(&data32);
        int rewardrep = data32;

        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,rewardcoin,rewardrep));
        
        
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败,等待复活中");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败,boss已死亡");
    }
    else if(result == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败,活动已经结束");
    }
    else if(result == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败,您当前处于离线参与中");
    }
    else if(result == 6)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败,未知错误");
    }
    
    
    

}

/*
 // 同步怪物血量
 message	sc_hula_hp_sync[id=14010]{
 required    int8        bossID          =1;//
 required	int64		bossHp			=2;//BOSS當前HP
 }
 */
void MB_FunctionKingInterface::sc_king_hp_sync(MB_MsgBuffer* pRecv)
{
    uint8_t boosid;
    uint64_t hp;
    pRecv->readU8(&boosid);
    pRecv->readU64(&hp);
    
    m_pKingInfo->setBossHP(boosid,hp);
}


void MB_FunctionKingInterface::cs_king_open_time()
{
    SOCKET_REQUEST_START(CS_KING_OPEN_TIME);
    SOCKET_REQUEST_END(SC_KING_OPEN_TIME, NULL);
}
void MB_FunctionKingInterface::sc_king_open_time(MB_MsgBuffer* pRecv)
{
    uint32_t data32;
    pRecv->readU32(&data32);
    m_pKingInfo->setOpenTime(data32);
    if(data32 == 0)
    {
        setOpenStatus(false);
    }
    else
    {
        int time = MB_ClientSocket::getInstance()->getServerTime()-m_pKingInfo->getOpenTime();
        if (time >= 0)
        {
            setOpenStatus(true);
        }
    }


//    else
//    {
//        setOpenStatus(false);
//    }
}

bool MB_FunctionKingInterface::getIsOpen()
{
    if (m_pKingInfo->getIsOpen())
    {
        return true;
    }
    
//    if(m_pKingInfo->getOpenTime() == 0)
//    {
//        return false;
//    }
//    int time = MB_ClientSocket::getInstance()->getServerTime()-m_pKingInfo->getOpenTime();
//    if (time > 0)
//    {
////        cs_king_open();
//        return true;
//    }
    return false;
}


bool MB_FunctionKingInterface::getHasBoss()
{
    for (int i = 0;i < 4;i++)
    {
        KingBossInfo* boosInfo = m_pKingInfo->getBossInfoByID(i+1);
        if (boosInfo != NULL)
        {
            return true;
        }
    }
    return false;
}
