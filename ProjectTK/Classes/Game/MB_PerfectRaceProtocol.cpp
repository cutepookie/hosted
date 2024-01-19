//
//  MB_PerfectRaceProtocol.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-22.
//
//

#include "MB_PerfectRaceProtocol.h"
#include "MB_PerfectRaceInterface.h"
#include "Game.h"
#include "MB_SceneGame.h"
const char* getStatusString(int status)
{
    static const char* pStatus[] = {"下次报名倒计时:","火热报名中...",
        "等待预选赛第一场:","预选赛第一场直播中:",
        "等待预选赛第二场:","预选赛第二场直播中:",
        "等待预选赛第三场:","预选赛第三场直播中:",
        "等待预选赛第四场:","预选赛第四场直播中:",
        "等待预选赛第五场:","预选赛第五场直播中:",
        "等待预选赛第六场:","预选赛第六场直播中:",
        "等待预选赛第七场:","预选赛第七场直播中:",
        "等待预选赛第八场:","预选赛第八场直播中:",
        "四强赛准备:","四强赛直播中:",
        "半决赛准备:","半决赛直播中:",
        "决赛准备:","决赛场直播中:"};
    
    if (status <0 || status > STATUS_FINAL_FIGHT)
    {
        return "未知状态";
    }
    
    return pStatus[status];
}

const char* getMatchRound(int status)
{
    if (status == STATUS_FOUR_FIGHT)
    {
        return "四强赛";
    }
    else if (status == STATUS_TWO_FIGHT)
    {
        return "半决赛";
    }
    else if (status == STATUS_FINAL_FIGHT)
    {
        return "决赛";
    }
    
    return "";
}

MB_RaceRecord::~MB_RaceRecord()
{
    m_vRecordList.clear();
    m_vResultList.clear();
}

bool MB_RaceRecord::read(MB_MsgBuffer *recvPacket)
{
    char* pString = recvPacket->ReadString();
    if (pString)
    {
        m_szAtkName = pString;
        CC_SAFE_FREE(pString);
    }
    
    pString = recvPacket->ReadString();
    if (pString)
    {
        m_szDefName = pString;
        CC_SAFE_FREE(pString);
    }
    
    uint16_t count = 0;
    uint64_t value = 0;
    recvPacket->readU16(&count);

    m_vRecordList.clear();
    for (uint16_t i=0; i<count; ++i)
    {
        recvPacket->readU64(&value);
        m_vRecordList.push_back(value);
    }
    
    recvPacket->readU32(&m_nAtkRoleId);
    recvPacket->readU32(&m_nDefRoleId);
    recvPacket->readU64(&m_nAtkFightPower);
    recvPacket->readU64(&m_nDefFightPower);
    recvPacket->readU8(&m_nStep);
    recvPacket->readU8(&m_nGroupId);
    recvPacket->readU8(&m_bAtkIsMale);
    recvPacket->readU8(&m_bDefIsMale);
    recvPacket->readU8(&m_nAtkTitle);
    recvPacket->readU8(&m_nDefTitle);
    recvPacket->readU32(&m_nAtkHead);
    recvPacket->readU32(&m_nDefHead);
    
    recvPacket->readU16(&count);
    m_vResultList.clear();
    bool value_boolen = false;
    for (uint16_t i=0; i<count; ++i)
    {
        recvPacket->readU8(&value_boolen);
        m_vResultList.push_back(value_boolen);
    }
    return true;
}

bool MB_RaceRecord::resolvRaceRecord(CCArray** pRoundRecordList)
{
    if (*pRoundRecordList == NULL)
    {
        return false;
    }
    
    size_t count = m_vRecordList.size();
    
    MB_RaceRoundRecord*  pRoundRecord = NULL;
    int index = 0;
    int atkscore = 0;
    int defscore = 0;
    for (size_t sz=0; sz<count; ++sz)
    {
        pRoundRecord = new MB_RaceRoundRecord;
        index = sz % 2;
        if (index == 0)
        {
            pRoundRecord->m_szAtkName = m_szAtkName;
            pRoundRecord->m_szDefName = m_szDefName;
            pRoundRecord->m_nAtkRoleId = m_nAtkRoleId;
            pRoundRecord->m_nDefRoleId = m_nDefRoleId;
            pRoundRecord->m_bAtkIsMale = m_bAtkIsMale;
            pRoundRecord->m_bDefIsMale = m_bDefIsMale;
            pRoundRecord->m_nAtkHead = m_nAtkHead;
            pRoundRecord->m_nDefHead = m_nDefHead;
            if (m_vResultList[sz])
            {
                atkscore++;
            }
            else
            {
                defscore++;
            }
            pRoundRecord->m_nAtkScore = atkscore;
            pRoundRecord->m_nDefScore = defscore;
        }
        else
        {
            pRoundRecord->m_szAtkName = m_szDefName;
            pRoundRecord->m_szDefName = m_szAtkName;
            pRoundRecord->m_nAtkRoleId = m_nDefRoleId;
            pRoundRecord->m_nDefRoleId = m_nAtkRoleId;
            pRoundRecord->m_bAtkIsMale = m_bDefIsMale;
            pRoundRecord->m_bDefIsMale = m_bAtkIsMale;
            pRoundRecord->m_nAtkHead = m_nDefHead;
            pRoundRecord->m_nDefHead = m_nAtkHead;
            if (m_vResultList[sz])
            {
                defscore++;
            }
            else
            {
                atkscore++;
            }
            pRoundRecord->m_nAtkScore = defscore;
            pRoundRecord->m_nDefScore = atkscore;
        }
        
        
        pRoundRecord->m_bAtkWin = m_vResultList[sz];
        pRoundRecord->m_nGroupId = m_nGroupId;
        pRoundRecord->m_nStep = m_nStep;
        pRoundRecord->m_nRecordUID = m_vRecordList[sz];

        
        (*pRoundRecordList)->addObject(pRoundRecord);
        CC_SAFE_RELEASE_NULL(pRoundRecord);
    }
    return (*pRoundRecordList)->count();
};

int MB_RaceRecord::getPowerAtkScoreByRound(int round)
{
    if (round >= m_vResultList.size())
    {
        return 0;
    }
    
    int score = 0;
    for (int i=0; i<=round; i++)
    {
        if (i % 2 == 0 && m_vResultList[i])
        {
            score++;
            continue;
        }
        if (i%2 == 1 && !m_vResultList[i])
        {
            score++;
        }
    }
    return score;
}
void MB_RaceRecord::getName(std::string& winner,std::string& loser)
{
    int winner_score,loser_score;
    getScore(winner_score, loser_score);
    if (winner_score > loser_score)
    {
        winner = m_szAtkName;
        loser = m_szDefName;
    }
    else
    {
        winner = m_szDefName;
        loser = m_szAtkName;
    }
}

void MB_RaceRecord::getScore(int& winner,int& loser)
{
    winner = 0;
    loser = 0;
    int score1 = 0;
    int score2 = 0;
    for (int i=0; i<m_vResultList.size(); i++)
    {
        if (i % 2 == 0 && m_vResultList[i])
        {
            score1++;
            continue;
        }
        if (i%2 == 1 && !m_vResultList[i])
        {
            score1++;
        }
    }
    score2 = m_vResultList.size() - score1;
    winner = score2 > score1 ? score2 : score1;
    loser = m_vResultList.size() - winner;
}

void MB_RaceRecord::getResult(int& winner,int& loser,std::string& szwinner,std::string& szloser)
{
    winner = 0;
    loser = 0;
    int score1 = 0;
    int score2 = 0;
    for (int i=0; i<m_vResultList.size(); i++)
    {
        if (i % 2 == 0 && m_vResultList[i])
        {
            score1++;
            continue;
        }
        if (i%2 == 1 && !m_vResultList[i])
        {
            score1++;
        }
    }
    
    score2 = m_vResultList.size() - score1;
    
    if (score2 > score1)
    {
        winner = score2;
        loser = score1;
        szwinner = m_szDefName;
        szloser = m_szAtkName;
    }
    else
    {
        winner = score1;
        loser = score2;
        szwinner = m_szAtkName;
        szloser = m_szDefName;
    }
}

bool MB_RaceFighter::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU32(&m_nRoleId);
    char* pName = recvPacket->ReadString();
    if (pName)
    {
        m_szRoleName = pName;
        CC_SAFE_FREE(pName);
    }
    
    recvPacket->readU64(&m_nFightPower);
    recvPacket->readU16(&m_nRoleLevel);
    recvPacket->readU8(&m_bIsMale);
    recvPacket->readU8(&m_nTitle);
    recvPacket->readU32(&m_nHead);
    return true;
}

/*
 // 对阵图每个位置的信息
 message p_race_pos[id=13416]{
 required        int32           role_id             =1;//role_id
 required        string          role_name           =2;//名字
 required        bool            is_male             =3;//性别
 required        int8            title               =4;//称号
 required        int32           head                =5;//自定义头像
 required        int8            pos                 =6;//位置编号
 }
 */
bool MB_RacePos::read(MB_MsgBuffer *pRecv)
{
    pRecv->readU32(&m_nRoleId);
    char* pName = pRecv->ReadString();
    if (pName)
    {
        m_szRoleName = pName;
        CC_SAFE_FREE(pName);
    }
    pRecv->readU8(&m_bIsMale);
    pRecv->readU8(&m_nTitle);
    pRecv->readU32(&m_nHead);
    pRecv->readU8(&m_nPos);
    return true;
}

MB_RaceRecordDelegate::MB_RaceRecordDelegate():m_nLastRecordUID(0)
{
    
}
void MB_RaceRecordDelegate::onReplayCallBack()
{
    if (m_nLastRecordUID != 0)
    {
        onRecrodRequest(m_nLastRecordUID,m_szAtkName,m_szDefName);
    }
}
void MB_RaceRecordDelegate::onRecrodRequest(uint64_t uid,const std::string& atkName,const std::string& defName)
{
    NSGameFunction::CCFunctionInterface* pFunction = NULL;
    MB_PerfectRaceInterface* pInterface = NULL;
    if (MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPerfectRace, &pFunction))
    {
        pInterface = dynamic_cast<MB_PerfectRaceInterface*>(pFunction);
    }
    
    if (pInterface)
    {
        m_nLastRecordUID = uid;
        m_szAtkName = atkName;
        m_szDefName = defName;
        MB_Message::sharedMB_Message()->showMessage("",15);
        pInterface->sendrace_replay(uid);
    }
}
/*
 message recvrace_replay[id=13407]{
 required    int8                result          =1;//请求结果
 // 1=> 成功查询到战报
 // 2=> 查询的战报不存在，比如过期已经被删除
 required    recvfight_request    fight_info       =2;//战斗内容
 }
 */
void MB_RaceRecordDelegate::recvrace_replay(MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t value = 0;
    pRecv->readU8(&value);
    if (value == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("战报已过期");
        return;
    }
    
    MB_NetStructFight structFight;
    recvfight* fight = structFight.recvfight_request(pRecv);
    fight->type =  kFightResultTypeReplay;
    fight->m_pReplayCallBackTarget = this;
    fight->m_pReplayCallBack = callback_selector1st(MB_RaceRecordDelegate::onReplayCallBack);
    CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fight,m_szDefName.c_str(),m_szAtkName.c_str()));
}
