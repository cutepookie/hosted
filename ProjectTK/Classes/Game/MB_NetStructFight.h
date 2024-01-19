
#ifndef __ProjectMB__NetStructFight__
#define __ProjectMB__NetStructFight__
#include "Game.h"
//
//读取网路数据loading
//
class MB_NetStructFight{
    
    private:
    
        int m_nLevel;
        int64_t m_nPreExp;
        char *m_pBossList;
        int m_nPreEnpety;
        int m_nPreDistime;
        int m_nPrestar;
        uint16_t m_nDoungeLevel;
    
    public:
    
        MB_NetStructFight();
        MB_NetStructFight(int m_nLevel,int64_t preExp,char *bossList,
                          int perenpety, int predistime,int prestar,
                          uint16_t doungeLevel);
        ~MB_NetStructFight();
        recvfight * recvfight_request(MB_MsgBuffer* recvPacket);
        void structDatas(MB_MsgBuffer* recvPacket,recvfight *fightResult);
        p_reward * recvfight_reward(MB_MsgBuffer* recvPacket);
        p_reward * recvfight_sore(MB_MsgBuffer* recvPacket, p_reward *reward);
        p_reward * recvexplore_challenge_encounter(MB_MsgBuffer* recvPacket);
        p_reward * recvbattle_challenge(MB_MsgBuffer* recvPacket,const char* pBackground=NULL,uint8_t *bSuccess = NULL);
        uint8_t  recvexplore_challenge_state(MB_MsgBuffer* recvPacket);
};
#endif /* defined(__ProjectMB__NetStructFight__) */

