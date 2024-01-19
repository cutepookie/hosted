//
//  MB_PerfectRaceProtocol.h
//  ProjectPM
//
//  Created by WenYong on 14-4-22.
//
//

#ifndef __ProjectMB__MB_PerfectRaceProtocol__
#define __ProjectMB__MB_PerfectRaceProtocol__

#include "MB_ServerData.h"
#include "MB_LocalProto.h"

#define SC_RACE_NEW_FIGHT   13401
#define CS_RACE_HISTORY     13404
#define SC_RACE_HISTORY     13405
#define CS_RACE_REPLAY      13406
#define SC_RACE_REPLAY      13407
#define CS_RACE_FIGHT_LIST  13408
#define SC_RACE_FIGHT_LIST  13409
#define CS_RACE_SIGN        13410
#define SC_RACE_SIGN        13411
#define CS_RACE_INFO        13412
#define SC_RACE_INFO        13413
#define CS_RACE_ENTER       13414
#define CS_RACE_LEAVE       13415
#define CS_RACE_POS_HISTORY 13417
#define SC_RACE_POS_HISTORY 13418
#define SC_RACE_NEW_FIRST   13419
#define SC_RACE_NEW_STATUS  13420
#define SC_RACE_IS_OPEN     13422
#define CS_RACE_IS_OPEN     13421
#define CS_RACE_AUTO_SIGN   13423
#define SC_RACE_AUTO_SIGN   13424
#define CS_RACE_AUTO_UNSIGN 13425
#define SC_RACE_AUTO_UNSIGN 13426
#define CS_RACE_SELF_RECORD 13427
#define SC_RACE_SELF_RECORD 13428
#define CS_RACE_GUESS_INFO  13429
#define SC_RACE_GUESS_INFO  13430
#define CS_RACE_GUESS       13431
#define SC_RACE_GUESS       13432

#define STATUS_NOT_OPEN            0
#define STATUS_SIGN                1
#define STATUS_WAIT_PRE_FIHGT1     2
#define STATUS_PRE_FIGHT1          3
#define STATUS_WAIT_PRE_FIHGT2     4
#define STATUS_PRE_FIGHT2          5
#define STATUS_WAIT_PRE_FIHGT3     6
#define STATUS_PRE_FIGHT3          7
#define STATUS_WAIT_PRE_FIHGT4     8
#define STATUS_PRE_FIGHT4          9
#define STATUS_WAIT_PRE_FIHGT5     10
#define STATUS_PRE_FIGHT5          11
#define STATUS_WAIT_PRE_FIHGT6     12
#define STATUS_PRE_FIGHT6          13
#define STATUS_WAIT_PRE_FIHGT7     14
#define STATUS_PRE_FIGHT7          15
#define STATUS_WAIT_PRE_FIHGT8     16
#define STATUS_PRE_FIGHT8          17
#define STATUS_WAIT_FOUR_FIGHT     18
#define STATUS_FOUR_FIGHT          19
#define STATUS_WAIT_TWO_FIGHT      20
#define STATUS_TWO_FIGHT           21
#define STATUS_WAIT_FINAL_FIGHT    22
#define STATUS_FINAL_FIGHT         23

extern const char* getStatusString(int status);
extern const char* getMatchRound(int status);
class MB_RaceRecord;
class MB_RaceRoundRecord:public CCObject
{
public:
    friend class MB_RaceRecord;
    CC_SYNTHESIZE_READONLY(std::string, m_szAtkName, AtkName);
    CC_SYNTHESIZE_READONLY(std::string, m_szDefName, DefName);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nAtkRoleId, AtkRoleId);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nDefRoleId, DefRoleId);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nStep, Step);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nGroupId, GroupId);
    CC_SYNTHESIZE_READONLY(bool, m_bAtkIsMale, AtkIsMale);
    CC_SYNTHESIZE_READONLY(bool, m_bDefIsMale, DefIsMale);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nAtkHead, AtkHead);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nDefHead, DefHead);
    CC_SYNTHESIZE_READONLY(bool, m_bAtkWin, IsAtkWin);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nRecordUID, RecordUID);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nAtkScore, AtkScore);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nDefScore, DefScore);
};

class MB_RaceRecord:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket);
    bool resolvRaceRecord(CCArray** pRoundRecordList);
    void getName(std::string& winner,std::string& loser);
    void getScore(int& winner,int& loser);
    void getResult(int& winner,int& loser,std::string& szwinner,std::string& szloser);
    int getPowerAtkScoreByRound(int round);
    virtual ~MB_RaceRecord();
private:
    CC_SYNTHESIZE_READONLY(std::string, m_szAtkName, AtkName);
    CC_SYNTHESIZE_READONLY(std::string, m_szDefName, DefName);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nAtkRoleId, AtkRoleId);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nDefRoleId, DefRoleId);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nAtkFightPower, AtkFightPower);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nDefFightPower, DefFightPower);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nStep, Step);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nGroupId, GroupId);
    CC_SYNTHESIZE_READONLY(bool, m_bAtkIsMale, AtkIsMale);
    CC_SYNTHESIZE_READONLY(bool, m_bDefIsMale, DefIsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nAtkTitle, AtkTitle);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nDefTitle, DefTitle);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nAtkHead, AtkHead);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nDefHead, DefHead);
public:
    std::vector<uint64_t>   m_vRecordList;
    std::vector<bool>       m_vResultList;
};

class MB_RaceRecordWithPos:public MB_RaceRecord
{
public:
    MB_RaceRecordWithPos(int nPos):m_nPos(nPos){}
    CC_SYNTHESIZE_READONLY(int,m_nPos,Pos);
};

class MB_RaceFighter:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket);
    
private:
    CC_SYNTHESIZE_READONLY(uint32_t, m_nRoleId, RoleId);
    CC_SYNTHESIZE_READONLY(std::string, m_szRoleName, RoleName);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nFightPower, FightPower);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nRoleLevel, RoleLevel);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale, IsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nTitle, Title);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nHead, Head);
};

class MB_RacePos:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* pRecv);
private:
    CC_SYNTHESIZE_READONLY(uint32_t, m_nRoleId, RoleId);
    CC_SYNTHESIZE_READONLY(std::string, m_szRoleName, RoleName);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale, IsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nTitle, Title);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nHead, Head);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nPos, Pos);
};

class MB_RaceRecordDelegate:public CCCallBackDelegate
{
public:
    MB_RaceRecordDelegate();
    virtual void onReplayCallBack();
    virtual void onRecrodRequest(uint64_t uid,const std::string& atkName,const std::string& defName);
    virtual void recvrace_replay(MB_MsgBuffer* pRecv);
protected:
    uint64_t        m_nLastRecordUID;
    std::string     m_szAtkName;
    std::string     m_szDefName;
};

#endif /* defined(__ProjectMB__MB_PerfectRaceProtocol__) */
