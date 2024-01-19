//
//  MB_KingProtocol.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-16.
//
//

#include "MB_KingProtocol.h"
#include "MB_MsgBuffer.h"

KingBossInfo::KingBossInfo()
{
    m_uBoosID = 0;
    m_uMaxHP = 0;
    m_uBossRank = 0;
    m_szRoleName = "";
    m_bIsMale = false;
    m_uTitle = 0;
    m_uHead = 0;
}

KingBossInfo::~KingBossInfo()
{
    
}

/*
 message p_hula_boss_open[id=14003]{
 required    int8        bossID          =1;//
 required    int64       maxHp           =2;//BOSS最大血量
 required    int16       bossQuality     =3;//BOSS品阶
 required    string      roleName        =4;//
 required    bool        isMale          =5;//
 required    int8        title           =6;//
 required    int32       head            =7;//
 }
 */
bool KingBossInfo::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_uBoosID);
    recvPacket->readU64(&m_uMaxHP);
    recvPacket->readU16(&m_uBossRank);
    
    char *str = recvPacket->ReadString();
    if(str)m_szRoleName = str;
    CC_SAFE_FREE(str);
    
    recvPacket->readU8(&m_bIsMale);
    recvPacket->readU8(&m_uTitle);
    recvPacket->readU32(&m_uHead);

    return true;
}

KingBossState::KingBossState()
{
    m_uBoosID = 0;
    m_uMaxHP = 0;
    m_uCurHP = 0;
    m_szRoleName = "";
    m_bIsMale = false;
    m_uTitle = 0;
    m_uHead = 0;
}
KingBossState::~KingBossState()
{
    
}
/*
 message p_hula_boss_state[id=14005]{
 required    int8        bossID          =1;//
 required    int64       curHp           =2;//BOSS当前血量
 required    int64       maxHP           =3;//
 required    string      roleName        =4;//
 required    bool        isMale          =5;//
 required    int8        title           =6;//
 required    int32       head            =7;//
 }
 */
bool KingBossState::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_uBoosID);
    recvPacket->readU64(&m_uCurHP);
    recvPacket->readU64(&m_uMaxHP);
    
    char *str = recvPacket->ReadString();
    if(str)m_szRoleName = str;
    CC_SAFE_FREE(str);
    
    recvPacket->readU8(&m_bIsMale);
    recvPacket->readU8(&m_uTitle);
    recvPacket->readU32(&m_uHead);

    return true;
}

KingResult::KingResult()
{
    m_uHarm = 0;
    m_uCoin = 0;
    m_uRepu = 0;
}
KingResult::~KingResult()
{
}
/*
 // 玩家造成的伤害总和和玩家获得的银两，声望 总和
 message p_role_stastic[id=14022]{
 required	int64		harm			=1;
 required	int32		coin			=2;
 required	int32		repu			=3;
 }
 */
bool KingResult::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU64(&m_uHarm);
    recvPacket->readU32(&m_uCoin);
    recvPacket->readU32(&m_uRepu);

    return true;
}




KingInfo::KingInfo()
{
    m_bIsOpen = false;
    m_uOpenTime = 0;
    m_uEndTime = 0;
    m_uRebornTime = 0;
}

KingInfo::~KingInfo()
{
    
}

void KingInfo::setBossInfo(MB_MsgBuffer* recvPacket)
{
    uint16_t len;
    recvPacket->readU16(&len);
    for (int i = 0;i < len && i<4;i++)
    {
        m_BossInfo[i].read(recvPacket);
    }
}

void KingInfo::setBossState(MB_MsgBuffer* recvPacket)
{
    uint16_t len;
    recvPacket->readU16(&len);
    for (int i = 0;i < len && i<4;i++)
    {
        m_bossState[i].read(recvPacket);
    }
}
void KingInfo::setResult(MB_MsgBuffer* recvPacket)
{
    m_Result.read(recvPacket);
}

KingBossInfo* KingInfo::getBossInfoByID(int uid)
{
    if (uid < 1 || uid > 4)
    {
        return NULL;
    }
    for (int i = 0;i < 4;i++)
    {
        if (m_BossInfo[i].getBoosID() == uid)
        {
            return &m_BossInfo[i];
        }
        
    }
    return NULL;
}
KingBossState* KingInfo::getBossStateByID(int uid)
{
    if (uid < 1 || uid > 4)
    {
        return NULL;
    }
    for (int i = 0;i < 4;i++)
    {
        if (m_bossState[i].getBoosID() == uid)
        {
            return &m_bossState[i];
        }
        
    }
    return NULL;
}

void KingInfo::setBossHP(int bossid,uint64_t hp)
{
    if (bossid < 1 || bossid > 4)
    {
        return;
    }
    for (int i = 0;i < 4;i++)
    {
        if (m_bossState[i].getBoosID() == bossid)
        {
            m_bossState[i].setCurHP(hp);
            break;
        }
    }
}