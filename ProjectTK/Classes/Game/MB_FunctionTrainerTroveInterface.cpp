//
//  MB_FunctionTrainerTroveInterface.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#include "MB_FunctionTrainerTroveInterface.h"
#include "MB_NodeTrainerTroveEnter.h"
#include "MB_LayerTrainerTrove.h"
#include "MB_TrainerTroveProtocol.h"
#include "MB_Message.h"
#include "MB_FightData.h"
#include "MB_SceneGame.h"
MB_FunctionTrainerTroveInterface::MB_FunctionTrainerTroveInterface()
{
    m_pData = new MB_BattleCoinData();
    SOCKET_MSG_REGIST(SC_BATTLE_COIN_INFO,MB_FunctionTrainerTroveInterface);
    SOCKET_MSG_REGIST(SC_BATTLE_COIN_FIGHT,MB_FunctionTrainerTroveInterface);
}
MB_FunctionTrainerTroveInterface::~MB_FunctionTrainerTroveInterface()
{
    CC_SAFE_RELEASE_NULL(m_pData);
    SOCKET_MSG_UNREGIST(SC_BATTLE_COIN_INFO);
    SOCKET_MSG_UNREGIST(SC_BATTLE_COIN_FIGHT);
}
MB_ResWindow* MB_FunctionTrainerTroveInterface::createEntryDialog()
{
    MB_NodeTrainerTroveEnter* pInstance = new MB_NodeTrainerTroveEnter;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        pInstance->setType(getFunctionType());
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
MB_ResWindow* MB_FunctionTrainerTroveInterface::createFunctionDialog()
{
    MB_LayerTrainerTrove* pInstance = new MB_LayerTrainerTrove;
    if (pInstance && pInstance->init() && pInstance->setDataSource(this) )
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
void MB_FunctionTrainerTroveInterface::onLoadingScene()
{
    sendBattleCoinInfo();
}
void MB_FunctionTrainerTroveInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg) {
        case SC_BATTLE_COIN_INFO:
            recvBattleCoinInfo(pRecv);
            break;
        case SC_BATTLE_COIN_FIGHT:
            MB_Message::sharedMB_Message()->removeALLMessage();
            recvBattleCoinFight(pRecv);
            break;
        default:
            break;
    }
}
bool MB_FunctionTrainerTroveInterface::allowShow()
{
    return true;
}
uint16_t MB_FunctionTrainerTroveInterface::getFunctionType()
{
    return kFunctionTrainerTrove;
}


void MB_FunctionTrainerTroveInterface::sendBattleCoinInfo()
{
    SOCKET_REQUEST_START(CS_BATTLE_COIN_INFO);
    SOCKET_REQUEST_END(CS_BATTLE_COIN_INFO, NULL);
}
/*
 message sc_battle_coin_info[id=10218]{
 required    int16               times               =1;//已挑戰次數
 required    int32               coolDown            =2;//冷卻時間
 }
 */
void MB_FunctionTrainerTroveInterface::recvBattleCoinInfo(MB_MsgBuffer* pRecv)
{
    m_pData->read(pRecv);
}

//难度類型，1简單，2普通，3困难
void MB_FunctionTrainerTroveInterface::sendBattleCoinFight(uint8_t type)
{
    SOCKET_REQUEST_START(CS_BATTLE_COIN_FIGHT);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_BATTLE_COIN_FIGHT, NULL);
}

/*
 message sc_battle_coin_fight[id=10220]{
 required    int8                result              =1;//0 ok，1次數不足，2冷卻時間中，3等級不足
 required    int32                type                =2;//冷卻時間
 required    bool                isWin               =3;//是否勝利
 required    int32               coin                =4;//獲得金幣
 repeated    sc_fight_request    fightInfo           =5;//戰鬥的回放
 }
 */
void MB_FunctionTrainerTroveInterface::recvBattleCoinFight(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    pRecv->readU8(&result);
    if (result == 0)
    {
        uint8_t data8;
        uint32_t data32;
        pRecv->readU32(&data32);
        m_pData->setTimes(m_pData->getTimes()+1);
        m_pData->setCoolDown(data32);
        pRecv->readU8(&data8);
        pRecv->readU32(&data32);

        //戰鬥具体信息
        MB_NetStructFight fight;
        short data16 ;
        pRecv->readU16(&data16);
        recvfight * fightresult = fight.recvfight_request(pRecv);
        fightresult->type = kFightResultTypeTrainerTrove;
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,data32,0));
        
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("次数不足");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("冷却时间中");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("等级不足");
    }
}

int MB_FunctionTrainerTroveInterface::getFightCount()
{
    return m_pData->getTimes();
}
int MB_FunctionTrainerTroveInterface::getCoolDown()
{
    return m_pData->getCoolDown();
}
