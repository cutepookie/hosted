//
//  MB_KingProtocol.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-16.
//
//

#ifndef __ProjectMB__MB_KingProtocol__
#define __ProjectMB__MB_KingProtocol__

#define CS_KING_OPEN  14001
#define SC_KING_OPEN  14002
#define SC_KING_INIT_STATE   14004
#define CS_KING_CLOSE 14006
#define SC_KING_STOP 14013
#define CS_KING_FIGHT 14016
#define SC_KING_FIGHT 14017
#define CS_KING_OPEN_TIME 14020
#define SC_KING_OPEN_TIME 14021
#define SC_KING_HP_SYNC 14010
#define SC_KING_HARM_BROADCAST 14011
#define CS_KING_REBORN 14018
#include "MB_ServerData.h"
const std::string open_status_notify = "king_open_status_changed";
class KingBossInfo : MB_ServerData
{
public:
    KingBossInfo();
    ~KingBossInfo();
    
    virtual bool read(MB_MsgBuffer* recvPacket);
protected:
    CC_SYNTHESIZE_READONLY(uint8_t, m_uBoosID,BoosID);
    CC_SYNTHESIZE_READONLY(uint64_t, m_uMaxHP,MaxHP);
    CC_SYNTHESIZE_READONLY(uint16_t, m_uBossRank,BossRank);
    CC_SYNTHESIZE_READONLY(std::string, m_szRoleName,RoleName);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale,IsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_uTitle,Title);
    CC_SYNTHESIZE_READONLY(uint32_t,m_uHead,Head);
};

class KingBossState : MB_ServerData
{
public:
    KingBossState();
    ~KingBossState();
    virtual bool read(MB_MsgBuffer* recvPacket);
protected:
    CC_SYNTHESIZE_READONLY(uint8_t, m_uBoosID,BoosID);
    CC_SYNTHESIZE(uint64_t, m_uCurHP,CurHP);
    CC_SYNTHESIZE_READONLY(uint64_t, m_uMaxHP,MaxHP);
    CC_SYNTHESIZE_READONLY(std::string, m_szRoleName,RoleName);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale,IsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_uTitle,Title);
    CC_SYNTHESIZE_READONLY(uint32_t,m_uHead,Head);
};


class KingResult : MB_ServerData
{
public:
    KingResult();
    ~KingResult();
    virtual bool read(MB_MsgBuffer* recvPacket);
protected:
    CC_SYNTHESIZE_READONLY(uint64_t, m_uHarm,Harm);
    CC_SYNTHESIZE_READONLY(uint32_t, m_uCoin,Coin);
    CC_SYNTHESIZE_READONLY(uint32_t, m_uRepu,Repu);
};

class KingInfo : public CCObject
{
public:
    KingInfo();
    ~KingInfo();
    void setBossInfo(MB_MsgBuffer* recvPacket);
    void setBossState(MB_MsgBuffer* recvPacket);
    void setResult(MB_MsgBuffer* recvPacket);

    KingResult* getResult(){return &m_Result;};
    KingBossInfo* getBossInfoByID(int uid);
    KingBossState* getBossStateByID(int uid);
    
    void setBossHP(int bossid,uint64_t hp);
protected:
    CC_SYNTHESIZE(bool,m_bIsOpen,IsOpen);
    CC_SYNTHESIZE(uint32_t, m_uOpenTime,OpenTime);
    CC_SYNTHESIZE(uint32_t, m_uEndTime,EndTime);
    CC_SYNTHESIZE(uint32_t, m_uRebornTime,RebornTime);
    
    KingBossInfo m_BossInfo[4];
    KingBossState m_bossState[4];
    KingResult   m_Result;
};




#endif /* defined(__ProjectMB__MB_KingProtocol__) */
