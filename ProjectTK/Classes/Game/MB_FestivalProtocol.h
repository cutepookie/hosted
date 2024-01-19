//
//  MB_FestivalProtocol.h
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#ifndef __ProjectMB__MB_FestivalProtocol__
#define __ProjectMB__MB_FestivalProtocol__

#define SEND_FESTIVAL_INFO 13901
#define RECV_FESTIVAL_INFO 13902
#define SEND_FESTIVAL_CLICK 13903
#define RECV_FESTIVAL_CLICK 13904
#define SEND_FESTIVAL_RANK 13905
#define RECV_FESTIVAL_RANK 13906
/*
 message p_festival_rank[id=13907]{
 required        int32           roleID                = 1;//角色ID
 required        bool            isMale                = 3;//性别
 required        int8            title                 = 4;//称號
 required        int32           head                  = 5;//头像
 required        int16           level                 = 6;//等級
 required        string          roleName              = 7;//名字
 required        int32           totalCount            = 8;//參与总次數
 required        int16           rank                  = 9;//排名
 }
 
 message p_festival_rank_reward[id=13908]{
 required        int16           rankStart             = 1;//排名區間起始位置
 required        int16           rankEnd               = 2;//排名區間結束位置
 required        p_mail_reward   reward                = 3;//排名在該區間内的獎勵
 }
 */
#include "MB_ServerData.h"

class MB_FestivalRankData : public MB_ServerData
{
public:
    MB_FestivalRankData();
    virtual ~MB_FestivalRankData();
    virtual bool read(MB_MsgBuffer* pRecv);
private:
    CC_SYNTHESIZE_READONLY(uint32_t, m_nRoleID, RoleID);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale, IsMale);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nTitle, Title);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nHead, Head);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLevel, Level);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::string, m_szRoleName, RoleName);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nTotalCount, TotalCount);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nRank, Rank);
};

class MB_MailReward;
class MB_FestivalRankReward : public MB_ServerData
{
public:
    MB_FestivalRankReward();
    virtual ~MB_FestivalRankReward();
    virtual bool read(MB_MsgBuffer* pRecv);
    MB_MailReward* getReward()const{return m_pMainReward;}
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nRankStart, RankStart);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nRankEnd, RankEnd);
    MB_MailReward*    m_pMainReward;
};

class MB_RankReward : public CCObject
{
public:
    MB_RankReward()
    {
        m_nRank = 0;
        m_pReward = NULL;
    }
private:
    CC_SYNTHESIZE(uint16_t, m_nRank, Rank);
    CC_SYNTHESIZE(MB_MailReward*,m_pReward,Reward);
};

#endif /* defined(__ProjectMB__MB_FestivalProtocol__) */
