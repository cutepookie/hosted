//
//  MB_FunctionTrainerRoad.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#include "MB_FunctionTrainerRoad.h"
#include "MB_TrainerRoadNodeEntry.h"
#include "MB_TrainerRoadLayerMain.h"
#include "MB_TrainerRoadConfigure.h"
#include "MB_LayerResultPVPRanking.h"
#include "MB_GiftsProtocol.h"
#include "MB_SceneGame.h"
MB_FunctionTrainerRoad::MB_FunctionTrainerRoad()
{
    SOCKET_MSG_REGIST(SC_ROAD_INFO,MB_FunctionTrainerRoad);
    SOCKET_MSG_REGIST(SC_ROAD_RESET,MB_FunctionTrainerRoad);
    SOCKET_MSG_REGIST(SC_ROAD_FIGHT,MB_FunctionTrainerRoad);
    SOCKET_MSG_REGIST(SC_ROAD_FIGHT_EXT,MB_FunctionTrainerRoad);
    SOCKET_MSG_REGIST(SC_ROAD_BOX,MB_FunctionTrainerRoad);
}

MB_FunctionTrainerRoad::~MB_FunctionTrainerRoad()
{
    SOCKET_MSG_UNREGIST(SC_ROAD_INFO);
    SOCKET_MSG_UNREGIST(SC_ROAD_RESET);
    SOCKET_MSG_UNREGIST(SC_ROAD_FIGHT);
    SOCKET_MSG_UNREGIST(SC_ROAD_FIGHT_EXT);
    SOCKET_MSG_UNREGIST(SC_ROAD_BOX);
}

MB_ResWindow* MB_FunctionTrainerRoad::createEntryDialog()
{
    MB_TrainerRoadNodeEntry* p = new MB_TrainerRoadNodeEntry;
    if (p && p->init())
    {
        p->setType(getFunctionType());
        p->autorelease();
        return p;
    }
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}

MB_ResWindow* MB_FunctionTrainerRoad::createFunctionDialog()
{
    MB_TrainerRoadLayerMain* p = new MB_TrainerRoadLayerMain;
    if (p && p->setDataSource(this) && p->init())
    {
        send_road_info();
        p->autorelease();
        return p;
    }
    
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}

bool MB_FunctionTrainerRoad::allowShow()
{
    return true;
}

void MB_FunctionTrainerRoad::onLoadingScene()
{
    send_road_info();
}

uint16_t MB_FunctionTrainerRoad::getFunctionType()
{
    return kFunctionTrainerRoad;
}

void MB_FunctionTrainerRoad::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_ROAD_INFO:
            recv_road_info(pRecv);
            break;
        case SC_ROAD_RESET:
            recv_road_reset(pRecv);
            break;
        case SC_ROAD_FIGHT:
            recv_road_fight(pRecv);
            break;
        case SC_ROAD_FIGHT_EXT:
            recv_road_fight_ext(pRecv);
            break;
        case SC_ROAD_BOX:
            recv_road_box(pRecv);
            break;
        default:
            break;
    }
}

//=====================================================

void MB_FunctionTrainerRoad::send_road_info()
{
    SOCKET_REQUEST_START(CS_ROAD_INFO);
    SOCKET_REQUEST_END(SC_ROAD_INFO, MB_FunctionTrainerRoad::onMsgDeliver);
}
void MB_FunctionTrainerRoad::recv_road_info(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nResetTimes);
    pRecv->readU8(&m_nCurID);
    int n = 0;
    pRecv->readU8(&n);
    m_nStatus = (ERoadDungeonStatus)n;
    pRecv->readU8(&m_nExtID);
}


void MB_FunctionTrainerRoad::send_road_reset()
{
    SOCKET_REQUEST_START(CS_ROAD_RESET);
    SOCKET_REQUEST_END(SC_ROAD_RESET, MB_FunctionTrainerRoad::onMsgDeliver);
}
void MB_FunctionTrainerRoad::recv_road_reset(MB_MsgBuffer* pRecv)
{
    //    required        int8            result          =1;//0成功，客户端自己重置界面及扣除次數, 1次數不足
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 0:
        {
            m_nCurID = ROLE_BEGIN_ID;
            m_nStatus = DUNGEON_NOT_PASS;
            m_nResetTimes--;
            m_nExtID = 0;
            MB_Message::sharedMB_Message()->showMessage("成功");
            break;
        }
        case 1:
            MB_Message::sharedMB_Message()->showMessage("次数不足");
            break;
        default:
            break;
    }
}

void MB_FunctionTrainerRoad::send_road_fight(std::string str)
{
    m_strGateName = str;
    SOCKET_REQUEST_START(CS_ROAD_FIGHT);
    SOCKET_REQUEST_END(SC_ROAD_FIGHT, MB_FunctionTrainerRoad::onMsgDeliver);
}

void MB_FunctionTrainerRoad::recv_road_fight(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 0:
        {
            bool isWin = false;
            pRecv->readU8(&isWin);
            pRecv->readU8(&m_nExtID);
            if(isWin)
            {
                m_nStatus = DUNGEON_PASSED;
            }
            recv_fight_reward(pRecv);
            MB_Message::sharedMB_Message()->removeALLMessage();
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("未激活");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("已经通关");
            break;
            
        default:
            break;
    }
}

void MB_FunctionTrainerRoad::recv_fight_reward(MB_MsgBuffer* pRecv)
{
    uint16_t len = 0;
    pRecv->readU16(&len);
    
    SResultData* pResultData = new SResultData();
    MB_NetStructFight structFight;

    recvfight* fight = NULL;
    if(len)
    {
        fight = structFight.recvfight_request(pRecv);
        fight->type = kFightResultTypeRoad;

        pResultData->defenseName = MB_RoleData::getInstance()->getName();
        pResultData->attackName = m_strGateName;
        pResultData->bWin = fight->issuccess;
        pResultData->type = kFightResultTypeRoad;
    }
    pRecv->readU16(&len);
    if(len)
    {
        MB_MailReward* pMailReward = new MB_MailReward();
        pMailReward->read(pRecv);
        CCArray* pRewards = pMailReward->converIDNUM2RewardTempleteValue();
        pResultData->setRewards(pRewards);
        CC_SAFE_DELETE(pMailReward);
    }
    CCDirector::sharedDirector()->pushScene(MB_SceneGame::sceneWithReward(fight,pResultData));
    CC_SAFE_RELEASE(pResultData);
}

void MB_FunctionTrainerRoad::send_road_fight_ext(std::string str)
{
    m_strGateName = str;
    SOCKET_REQUEST_START(CS_ROAD_FIGHT_EXT);
    SOCKET_REQUEST_END(SC_ROAD_FIGHT_EXT, MB_FunctionTrainerRoad::onMsgDeliver);
}
void MB_FunctionTrainerRoad::recv_road_fight_ext(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 0:
        {
            bool isWin = false;
            pRecv->readU8(&isWin);
            recv_fight_reward(pRecv);
            if(isWin)m_nExtID = 0;
            MB_Message::sharedMB_Message()->removeALLMessage();
            break;
        }
        case 1:
            MB_Message::sharedMB_Message()->showMessage("未激活");
            break;
        default:
            break;
    }
}


void MB_FunctionTrainerRoad::send_road_box()
{
    SOCKET_REQUEST_START(CS_ROAD_BOX);
    SOCKET_REQUEST_END(SC_ROAD_BOX, MB_FunctionTrainerRoad::onMsgDeliver);
}
void MB_FunctionTrainerRoad::recv_road_box(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 0:
        {
            m_nCurID++;
            m_nStatus = DUNGEON_NOT_PASS;
            MB_Message::sharedMB_Message()->removeALLMessage();
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("未激活");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("已领取");
            break;
        default:
            break;
    }
}


