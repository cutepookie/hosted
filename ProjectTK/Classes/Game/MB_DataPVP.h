

#ifndef __ProjectMB__MB_DataPVP__
#define __ProjectMB__MB_DataPVP__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MB_DataPVPRank: public CCObject
{
public:
    
    CC_SYNTHESIZE(uint32_t, m_uRoleID, RoleID)
    CC_SYNTHESIZE(uint8_t, m_uIsMale, IsMale)
    CC_SYNTHESIZE(uint8_t, m_uRoleLevel, RoleLevel)
    CC_SYNTHESIZE(uint8_t, m_uRoleTitle, RoleTitle)
    CC_SYNTHESIZE(uint64_t, m_uRoleFightPower, RoleFightPower)
    CC_SYNTHESIZE(uint16_t, m_uRoleRank, RoleRank)
    //玩家头像
    CC_SYNTHESIZE(uint32_t, m_uHead, Head)
    //local
    CC_SYNTHESIZE(bool, m_bCanFight, CanFight);
    
    void setRoleName(const char* name) { m_sRoleName = name;}
    const char* getRoleName() { return m_sRoleName.c_str();}
    
private:
    
    std::string m_sRoleName;
};


class MB_DataPVPMgr: public CCObject
{
public:
    
    static MB_DataPVPMgr* getInstance();
    static void destroyInstance();
    
    MB_DataPVPMgr();
    ~MB_DataPVPMgr();
    
    CCArray* getPVPRankArray() { return m_PVPRankArray;}
    
    void setTarget(MB_DataPVPRank* dataPVPRank);
    
    //从伺服器收到消息的回调函數
    void onMsgRecv(CCNode* node, SocketResponse* response);
    //獲取可對戰排名列表
    bool sendpvp_get_list();
    bool recvpvp_get_list(MB_MsgBuffer* recvPacket);
    //触發戰鬥
    bool sendpvp_fight(uint32_t roleID, uint16_t rank);
    bool recvpvp_fight(MB_MsgBuffer* recvPacket);
    
    CC_SYNTHESIZE(uint16_t, m_uRoleRank, RoleRank);
    
    bool canFight(uint16_t myRank, uint16_t tagRank);
    bool checkTimes();
private:
    CCArray* m_PVPRankArray;
    MB_DataPVPRank* m_pTargetRole;
    CC_SYNTHESIZE(bool,m_bGoFight,GoFight);
    CC_SYNTHESIZE(uint32_t,m_uFightRoleID,FightRoleID);
    CC_SYNTHESIZE(uint16_t,m_uFightRank,FightRank);
};



#endif /* defined(__ProjectMB__MB_DataPVP__) */
