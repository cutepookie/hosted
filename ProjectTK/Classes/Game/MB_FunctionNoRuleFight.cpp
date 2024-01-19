//
//  MB_FunctionNoRuleFight.cpp
//  ProjectMB
//
//  Created by chk on 15-1-15.
//
//

#include "MB_FunctionNoRuleFight.h"
#include "MB_NoRuleFightNodeEntry.h"
#include "MB_NoRuleFightLayerMain.h"
#include "MB_RoleSoundProtocol.h"
#include "MB_GiftsProtocol.h"
#include "MB_LayerResultPVPRanking.h"
#include "MB_SceneGame.h"
MB_FunctionNoRuleFight::MB_FunctionNoRuleFight()
{
    m_pNoRuleInfo = new MB_NoRuleInfo;
    SOCKET_MSG_REGIST(SC_MELEE_INFO,MB_FunctionNoRuleFight);
    SOCKET_MSG_REGIST(SC_MELEE_SIGN,MB_FunctionNoRuleFight);
    SOCKET_MSG_REGIST(SC_MELEE_FIGHT,MB_FunctionNoRuleFight);
}

MB_FunctionNoRuleFight::~MB_FunctionNoRuleFight()
{
    CC_SAFE_RELEASE_NULL(m_pNoRuleInfo);
    SOCKET_MSG_UNREGIST(SC_MELEE_INFO);
    SOCKET_MSG_UNREGIST(SC_MELEE_SIGN);
    SOCKET_MSG_UNREGIST(SC_MELEE_FIGHT);
}

MB_ResWindow* MB_FunctionNoRuleFight::createEntryDialog()
{
    MB_NoRuleFightNodeEntry* p = new MB_NoRuleFightNodeEntry;
    if (p && p->init())
    {
        p->setType(getFunctionType());
        p->autorelease();
        return p;
    }
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}

MB_ResWindow* MB_FunctionNoRuleFight::createFunctionDialog()
{
    MB_NoRuleFightLayerMain* p = new MB_NoRuleFightLayerMain;
    if (p && p->setDataSource(this) && p->init())
    {
        cs_melee_info();
        p->autorelease();
        return p;
    }
    
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}

bool MB_FunctionNoRuleFight::allowShow()
{
    return true;
}

void MB_FunctionNoRuleFight::onLoadingScene()
{
}

uint16_t MB_FunctionNoRuleFight::getFunctionType()
{
    return kFunctionNoRuleFight;
}

void MB_FunctionNoRuleFight::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_MELEE_INFO:
            sc_melee_info(pRecv);
            break;
        case SC_MELEE_SIGN:
            sc_melee_sign(pRecv);
            break;
        case SC_MELEE_FIGHT:
            sc_melee_fight(pRecv);
            break;
        default:
            break;
    }
}

/////////////
void MB_FunctionNoRuleFight::cs_melee_info()
{
    MB_Message::sharedMB_Message()->showMessage(5);
    SOCKET_REQUEST_START(CS_MELEE_INFO);
    SOCKET_REQUEST_END(SC_MELEE_INFO, MB_FunctionNoRuleFight::onMsgDeliver);
}

void MB_FunctionNoRuleFight::sc_melee_info(MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    m_pNoRuleInfo->read(pRecv);
}

void MB_FunctionNoRuleFight::cs_melee_sign()
{
    SOCKET_REQUEST_START(CS_MELEE_SIGN);
    SOCKET_REQUEST_END(SC_MELEE_SIGN, MB_FunctionNoRuleFight::onMsgDeliver);
}

void MB_FunctionNoRuleFight::sc_melee_sign(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result) {
        case 0:
            MB_Message::sharedMB_Message()->showMessage("报名成功");
            m_pNoRuleInfo->setState(NORULE_SIGNED);
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("等级不足");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("暂未开始报名");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("参加次数不足,明天再来吧");
            break;
        default:
            MB_Message::sharedMB_Message()->showMessage("未知错误");
            break;
    }
}

void MB_FunctionNoRuleFight::cs_melee_fight()
{
    SOCKET_REQUEST_START(CS_MELEE_FIGHT);
    SOCKET_REQUEST_END(SC_MELEE_FIGHT, MB_FunctionNoRuleFight::onMsgDeliver);
}

void MB_FunctionNoRuleFight::sc_melee_fight(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);//0成功,1等級不够，2功能未開放,3等待復活中 4 未報名,5 沒有找到對手,6 戰鬥結果異常
    
    switch (result)
    {
        case 0:
            MB_Message::sharedMB_Message()->removeALLMessage();
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("等级不足");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("功能未开放");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("等待复活中");
            break;
        case 4:
            MB_Message::sharedMB_Message()->showMessage("未报名");
            break;
        case 5:
            MB_Message::sharedMB_Message()->showMessage("没有找到对手");
            break;
        case 6:
            MB_Message::sharedMB_Message()->showMessage("战斗结果异常");
            break;
        default:
            MB_Message::sharedMB_Message()->showMessage("未知异常");
            break;
    }
    if(result != 0)return;
    
    uint64_t tar_role_id = 0;
    std::string tar_role_name = "";
    pRecv->readU64(&tar_role_id);
    char *str = pRecv->ReadString();
    if(str)tar_role_name = str;
    CC_SAFE_FREE(str);
    
    uint16_t add_score = 0;
    pRecv->readU16(&add_score);
    
    uint32_t team0scroe = 0;
    pRecv->readU32(&team0scroe);
    
    uint32_t team1scroe = 0;
    pRecv->readU32(&team1scroe);
    getNoRuleInfo()->setTeam0Score(team0scroe);
    getNoRuleInfo()->setTeam1Score(team1scroe);
    getNoRuleInfo()->setSelfScore(add_score + getNoRuleInfo()->getSelfScore());
    
    SResultData* pResultData = new SResultData();
    pResultData->defenseName = MB_RoleData::getInstance()->getName();
    pResultData->attackName = tar_role_name;
    pResultData->nNowRank = add_score;
    pResultData->roleID = tar_role_id;
    MB_MailReward* pMailReward = new MB_MailReward();
    pMailReward->read(pRecv);
    CCArray* pRewards = pMailReward->converIDNUM2RewardTempleteValue();
    pResultData->setRewards(pRewards);
    CC_SAFE_DELETE(pMailReward);
    

    uint16_t len = 0;
    pRecv->readU16(&len);
    if(len)
    {
        MB_NetStructFight structFight;
        recvfight* fight = NULL;
        
        fight = structFight.recvfight_request(pRecv);
        fight->type = kFightResultTypeNoRule;

        pResultData->bWin = fight->issuccess;
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::sceneWithReward(fight,pResultData));
    }
    
    uint8_t nWinCount = 0;
    pRecv->readU8(&nWinCount);
    m_pNoRuleInfo->setWinCount(nWinCount);
    
}


