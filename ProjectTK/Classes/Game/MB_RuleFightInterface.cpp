//
//  MB_RuleFightInterface.cpp
//  ProjectPM
//
//  Created by chk
//
//

#include "MB_RuleFightInterface.h"
#include "MB_RuleFightProtocol.h"
#include "MB_MailData.h"
#include "MB_LayerRuleFight.h"
#include "MB_NodeRuleFightEntry.h"
#include "MB_GiftsProtocol.h"
#include "MB_SceneGame.h"
MB_RuleFightInterface::MB_RuleFightInterface()
{
    m_pRankList = new CCArray;
    m_pRuleInfo = new RuleFightInfo;
    m_pLastWeekRank = new CCArray;
    m_pMainLayer = NULL;
    SOCKET_MSG_REGIST(SC_HIST_NEW, MB_RuleFightInterface);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_RULETIMES, MB_RuleFightInterface);
    SOCKET_MSG_REGIST(SC_RULE_LAST_RANK, MB_RuleFightInterface);
    SOCKET_MSG_REGIST(SC_RULE_INFO, MB_RuleFightInterface);
    SOCKET_MSG_REGIST(SC_RULE_RANK, MB_RuleFightInterface);
    SOCKET_MSG_REGIST(SC_RULE_FIGHT, MB_RuleFightInterface);
    m_nFightReplayUID = 0;
    m_bUpMainLayer = false;
//    for (int i = 0; i< 50 ; ++i)
//    {
//        RuleFighter* pFighter = new RuleFighter;
//        pFighter->setFightPower(i * 100);
//        pFighter->setLevel(i);
//        pFighter->setRoleName(CCString::createWithFormat("name%d",i)->getCString());
//        pFighter->setWinConMaxTimes(2);
//        pFighter->setWinConTimes(3);
//        pFighter->setWinTimes(5);
//        m_pRankList->addObject(pFighter);
//        CC_SAFE_RELEASE_NULL(pFighter);
//        
//        pFighter = new RuleFighter;
//        pFighter->setFightPower(i * 100);
//        pFighter->setLevel(i);
//        pFighter->setRoleName(CCString::createWithFormat("name%d",i)->getCString());
//        pFighter->setWinConMaxTimes(2);
//        pFighter->setWinConTimes(3);
//        pFighter->setWinTimes(5);
//        pFighter->setScore(i*10);
//        m_pLastWeekRank->addObject(pFighter);
//        CC_SAFE_RELEASE_NULL(pFighter);
//        
//        Hist* pHist = new Hist;
//        pHist->setName(CCString::createWithFormat("Name%d",i)->getCString());
//        m_pRuleInfo->getList()->addObject(pHist);
//        m_pRuleInfo->setScore(5);
//        CC_SAFE_RELEASE_NULL(pHist);
//    }
    
    m_pMyRecordDataSource = new MB_RuleFightDataSource(this);
    m_pRankDataSource = new MB_RuleRankDataSource(this);
    LastWeekRankDataSource = new MB_LastWeekRankDataSource(this);
}

MB_RuleFightInterface::~MB_RuleFightInterface()
{
    CC_SAFE_DELETE(m_pMyRecordDataSource);
    CC_SAFE_DELETE(m_pRankDataSource);
    CC_SAFE_DELETE(LastWeekRankDataSource);
    CC_SAFE_DELETE(m_pRuleInfo);
    CC_SAFE_RELEASE_NULL(m_pRankList);
    SOCKET_MSG_UNREGIST(SC_HIST_NEW);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_RULETIMES);
    SOCKET_MSG_UNREGIST(SC_RULE_LAST_RANK);
    SOCKET_MSG_UNREGIST(SC_RULE_INFO);
    SOCKET_MSG_UNREGIST(SC_RULE_RANK);
    SOCKET_MSG_UNREGIST(SC_RULE_FIGHT);
}

MB_ResWindow* MB_RuleFightInterface::createEntryDialog()
{
    return MB_NodeRuleFightEntry::create();
}

MB_ResWindow* MB_RuleFightInterface::createFunctionDialog()
{
    m_pMainLayer = MB_LayerRuleFight::create();
    return m_pMainLayer;
}

void MB_RuleFightInterface::cs_rule_info()
{
    m_bUpMainLayer = true;
    SOCKET_REQUEST_START(CS_RULE_INFO);
    SOCKET_REQUEST_END(SC_RULE_INFO, MB_RuleFightInterface::onMsgDeliver);
}

void MB_RuleFightInterface::cs_rule_rank()
{
    SOCKET_REQUEST_START(CS_RULE_RANK);
    SOCKET_REQUEST_END(SC_RULE_RANK, MB_RuleFightInterface::onMsgDeliver);
}

void MB_RuleFightInterface::cs_rule_fight()
{
    m_nReplayRoleID = m_pRuleInfo->getTarFighter()->getRoleID();
    SOCKET_REQUEST_START(CS_RULE_FIGHT);
    SOCKET_REQUEST_END(SC_RULE_FIGHT, MB_RuleFightInterface::onMsgDeliver);
}

void MB_RuleFightInterface::cs_rule_leave()
{
    SOCKET_REQUEST_START(CS_RULE_LEAVE);
    SOCKET_REQUEST_END(CS_RULE_LEAVE, MB_RuleFightInterface::onMsgDeliver);
}

void MB_RuleFightInterface::cs_rule_last_rank()
{
    SOCKET_REQUEST_START(CS_RULE_LAST_RANK);
    SOCKET_REQUEST_END(SC_RULE_LAST_RANK, MB_RuleFightInterface::onMsgDeliver);
}

void MB_RuleFightInterface::cs_hist_replay(uint64_t id)
{
    m_nFightReplayUID = id;
    SOCKET_REQUEST_START(CS_HIST_REPLAY);
    packet->WriteUINT64(id);
    packet->writeU8(5);
    SOCKET_REQUEST_END(SC_HIST_REPLAY, MB_RuleFightInterface::onMsgDeliver);
}
#include "MB_LayerResultPVPRanking.h"
void MB_RuleFightInterface::sc_hist_replay(MB_MsgBuffer* pRecv,SResultData* pResultData)
{
    int len = 0;
    pRecv->readU16(&len);
    if (len)
    {
        MB_NetStructFight structFight;
        recvfight* fight = structFight.recvfight_request(pRecv);
        fight->type = kFightResultTypeRuleFight;
        
        pResultData->bWin = fight->issuccess;
        pResultData->type = kFightResultTypeRuleFight;
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::sceneWithReward(fight,pResultData));
    }
}

void MB_RuleFightInterface::p_rule_fighter(MB_MsgBuffer* pRecv,CCArray* pArray)
{
    int len = 0;
    pRecv->readU16(&len);
    for (int i  = 0; i<len; ++i)
    {
        RuleFighter* pFighter = new RuleFighter;
        if (pFighter)
        {
            pFighter->read(pRecv);
            pArray->addObject(pFighter);
        }
        CC_SAFE_RELEASE_NULL(pFighter);
    }
}

void MB_RuleFightInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_HIST_NEW:
        {
            if(m_pRuleInfo)m_pRuleInfo->sc_hist_new(pRecv,m_nFightReplayUID);
            break;
        }
        case SC_ROLE_UPDATE_RULETIMES:
        {
            pRecv->readU8(&m_nRuleTimes);
            pRecv->readU32(&m_nNextRuleTime);
            break;
        }
        case SC_RULE_INFO:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            if(m_pRuleInfo)m_pRuleInfo->read(pRecv);
            if(m_bUpMainLayer)
            {
                m_pMainLayer->showPage(MB_LayerRuleFight::eMainPage,true);
                m_bUpMainLayer = false;
            }
            break;
        }
        case SC_RULE_RANK:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            m_pRankList->removeAllObjects();
            p_rule_fighter(pRecv,m_pRankList);
            break;
        }
        case SC_RULE_FIGHT:
        {
            uint8_t result = 0;
            pRecv->readU8(&result);
            
            switch (result)
            {
                case 0:
                {
                    bool isWin = 0;
                    pRecv->readU8(&isWin);
                    
                    std::string targetName = "";
                    char* pName = NULL;
                    pName = pRecv->ReadString();
                    targetName = pName;
                    CC_SAFE_FREE(pName);
                    
                    int32_t newScore = 0;
                    pRecv->readU32(&newScore);
                    m_pRuleInfo->setScore(newScore);
                    
                    int nOldRank = m_pRuleInfo->getRank();
                    
                    int32_t rank = 0;
                    pRecv->readU32(&rank);
                    m_pRuleInfo->setRank(rank);
                    
                    int16_t winTimes = 0;
                    pRecv->readU16(&winTimes);
                    m_pRuleInfo->setWinTimes(winTimes);
                    
                    int16_t fightTimes = 0;
                    pRecv->readU16(&fightTimes);
                    m_pRuleInfo->setFightTimes(fightTimes);
                    
                    int16_t winConTimes = 0;
                    pRecv->readU16(&winConTimes);
                    m_pRuleInfo->setWinConTimes(winConTimes);
                    
                    int16_t winConMaxTimes = 0;
                    pRecv->readU16(&winConMaxTimes);
                    m_pRuleInfo->setWinConMaxTimes(winConMaxTimes);
                    
                    MB_MailReward* pMailReward = new MB_MailReward();
                    pMailReward->read(pRecv);
                    CCArray* pRewards = pMailReward->converIDNUM2RewardTempleteValue();
                    CC_SAFE_DELETE(pMailReward);
                    
                    m_pRuleInfo->getTarFighter()->read(pRecv);
                    
                    SResultData* pResultData = new SResultData();
                    pResultData->setRewards(pRewards);
                    pResultData->nOldRank = nOldRank;
                    pResultData->nNowRank = m_pRuleInfo->getRank();
                    pResultData->attackName = targetName;
                    
                    sc_hist_replay(pRecv,pResultData);
                    CC_SAFE_RELEASE(pResultData);
                    MB_Message::sharedMB_Message()->removeALLMessage();
                }
                    break;
                case 1:
                    MB_Message::sharedMB_Message()->showMessage("等级不够");
                    break;
                case 2:
                    MB_Message::sharedMB_Message()->showMessage("次数不足");
                    break;
                case 3:
                    MB_Message::sharedMB_Message()->showMessage("功能未开放");
                    break;
                case 4:
                    MB_Message::sharedMB_Message()->showMessage("获取自己信息失败");
                    break;
                case 5:
                    MB_Message::sharedMB_Message()->showMessage("获取对手战斗信息失败");
                    break;
                case 6:
                    MB_Message::sharedMB_Message()->showMessage("战斗结果异常");
                default:
                    break;
            }
            break;
        }
        case SC_RULE_LAST_RANK:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            m_pLastWeekRank->removeAllObjects();
            p_rule_fighter(pRecv,m_pLastWeekRank);
        }
            break;
        default:
            break;
    }
}

bool MB_RuleFightInterface::allowShow()
{
    return true;
}

uint16_t MB_RuleFightInterface::getFunctionType()
{
    return kFunctionRuleFight;
}


void MB_RuleFightInterface::onLoadingScene()
{
}

