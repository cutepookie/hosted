//
//  MB_FunctionRankingProtocol.h
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#ifndef __ProjectMB__MB_FunctionRankingProtocol__
#define __ProjectMB__MB_FunctionRankingProtocol__

/*
 message cs_pvp_rank[id=10811]{
 
 }
 
 message sc_pvp_rank[10812]{
 repeated    p_pvp_rank          list            =1;//排名信息
 }

 message cs_fight_rank[id=20005]{
 
 }
 
 message sc_fight_rank[id=20006]{
 repeated    p_pvp_rank          list            =1;//排名信息
 }
 
 message p_fight_rank[id=20007]{
 required        int8            rank            = 1;
 required        int32           roleID          = 2;
 required        int16           level           = 3;
 required        string          name            = 4;
 required        int32           head            = 5;
 required        int8            title           = 6;
 required        bool            isMale          = 7;
 required        int64           fightPower      = 8;
 }

 message cs_rank_info[id=13701]{
 required    int8                    rankType            = 1;// 1:等級榜, 2:戰鬥力榜, 3:pvp榜, 4:關卡榜
 required    int8                    type                = 2;// 1:普通關卡 2:困难關卡 3:最困难關卡
 required    int8                    start               = 3;// 从第几名開始請求
 required    int8                    num                 = 4;// 請求多少个
 }
 
 message sc_rank_info[id=13702]{
 required    int8                    rankType            = 1;// 1:等級榜, 2:戰鬥力榜, 3:pvp榜, 4:關卡榜
 required    int8                    type                = 2;// 1:普通關卡   2:困难關卡  3:最困难關卡
 repeated    p_rank_info             list                = 3;// 排行榜數据
 }

 message p_rank_info[id=13703]{
 required        int8            rank            = 1;
 required        int32           roleID          = 2;
 required        int16           level           = 3;
 required        string          name            = 4;
 required        int32           head            = 5;
 required        int8            title           = 6;
 required        bool            isMale          = 7;
 required        int64           fightPower      = 8;
 required        string          dungeonName     = 9;
 }
 */
#include "MB_ServerData.h"
#define SEND_RANK_INFO 13701
#define RECV_RANK_INFO 13702
/*
 message p_pvp_rank[10813]{
 required        int8            rank            = 1;
 required        int32           roleID          = 2;
 required        int16           level           = 3;
 required        string          name            = 4;
 required        int32           head            = 5;
 required        int8            title           = 6;
 required        bool            isMale          = 7;
 required        int64           fightPower      = 8;
 required        string          dungeonName     = 9;
 required        string          chapterName     = 10;
 }
 */
class MB_MsgBuffer;
class MB_RankData : public MB_ServerData
{
public:
    MB_RankData()
    {
        m_nRank = 0;
        m_nRoleID = 0;
        m_nLevel = 0;
        m_nHead = 0;
        m_nTitle = 0;
        m_bMale = false;
        m_nPower = 0;
    }
    virtual bool read(MB_MsgBuffer* pRecv);
protected:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nRank, Rank);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nRoleID, RoleID);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLevel, Level);
    CC_SYNTHESIZE_READONLY(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nHead, Head);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nTitle, Title);
    CC_SYNTHESIZE_READONLY(bool, m_bMale, IsMale);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nPower, Power);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nChapter, Chapter);
    CC_SYNTHESIZE_READONLY(std::string, m_szDungeonName, DungeonName);
};
#endif /* defined(__ProjectMB__MB_FunctionRankingProtocol__) */
