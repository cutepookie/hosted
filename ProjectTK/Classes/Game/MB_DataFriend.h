

#ifndef __ProjectMB__MB_DataFriend__
#define __ProjectMB__MB_DataFriend__

#include "Game.h"

USING_NS_CC;

class MB_DataFriend: public CCObject
{
public:
    CC_SYNTHESIZE(uint32_t, m_uRoleID, RoleID);
    CC_SYNTHESIZE(bool, m_bIsMale, IsMale);
    CC_SYNTHESIZE(uint8_t, m_uLevel, Level);
    CC_SYNTHESIZE(uint8_t, m_uTitle, Title);
    CC_SYNTHESIZE(uint64_t, m_uFightPower, FightPower);
    CC_SYNTHESIZE(uint32_t, m_uLogoutTime, LogoutTime);
    CC_SYNTHESIZE(std::string, m_Location, Location);
    CC_SYNTHESIZE(uint32_t, m_uHead, Head);//头像ID
    CC_SYNTHESIZE(uint32_t, m_uMatingCoolSecond, MatingCoolSecond);//守護武將交配冷卻時間
//    CC_SYNTHESIZE(bool, m_bCanGold, CanGold);//能否充能金幣
//    CC_SYNTHESIZE(bool, m_bCanBadge, CanBadge);//能否充能徽章
    bool getCanGold();
    bool getCanBadge();
    CC_SYNTHESIZE(uint16_t, m_uMonsterTID, MonsterTID);//守護武將TID
    CC_SYNTHESIZE(uint16_t, m_uRank, Rank);//守護武將品階
    CC_SYNTHESIZE(uint8_t, m_uCanAdd, CanAdd);//是否已邀請 0不可添加  1可以添加  2已經添加
    CC_SYNTHESIZE(bool, m_bGiveEnergy,CanGiveEnergy);//是否可以領取体力
    CC_SYNTHESIZE(uint8_t, m_bSendEnergy,CanSendEnergy);//是否可以贈送体力 0不可贈送 1可贈送 2已經贈送
    CC_SYNTHESIZE(uint32_t, m_nSendTime, SendTime);// 贈送体力時間
    
    /*
     required		int32				beginGold				=16[default=0];//充能(金幣)開始時間
     required		int32				endGold					=17[default=0];//充能(金幣)結束時間
     required		int32				beginBadge              =18[default=0];//充能(徽章)開始時間
     required		int32				endBadge				=19[default=0];//充能(徽章)結束時間
     */
    CC_SYNTHESIZE(uint32_t, m_nBeginGold, BeginGold);
    CC_SYNTHESIZE(uint32_t, m_nEndGold, EndGold);
    CC_SYNTHESIZE(uint32_t, m_nBeginBadge, BeginBadge);
    CC_SYNTHESIZE(uint32_t, m_nEndBadge, EndBadge);
    void setRoleName(const char* name) { m_strRoleName = name;}
    const char* getRoleName() { return m_strRoleName.c_str();}
    CC_SYNTHESIZE(bool, m_bCanFight,CanFight);//是否可以挑戰
private:
    std::string m_strRoleName;
};


class MB_DataMsgFriend: public MB_DataFriend
{
public:
    virtual bool read(MB_MsgBuffer* pRecv);
};


class MB_FriendMgr: public CCObject
{
public:
    
    ~MB_FriendMgr();
    
    /** Return the shared instance **/
    static MB_FriendMgr *getInstance();
    /** Relase the shared instance **/
    static void destroyInstance();
    
    CCArray* getFriendArray() { return m_pArrayFriend;}
    CCArray* getEnemyArray() { return m_pArrayEnemy;}
    CCArray* getExploreArray() { return m_pArrayExplore;}
    CCArray* getFriendMsgArray(){return m_pArrayMsg;};
    
    bool parseFriend(CCArray* pArray, MB_MsgBuffer* recvPacket, bool bClear);
    bool parseExploreFriend(CCArray* pArray, MB_MsgBuffer* recvPacket, bool bClear);
    int getFriendLevel(uint32_t roleId);
    bool queryFriendDataByRoleID(uint32_t roleId,MB_DataFriend** pData);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    static int sortArray(CCObject* p1,CCObject* p2);
    
    bool sendfriend_get_list(uint8_t type);
    bool recvfriend_get_list(MB_MsgBuffer* recvPacket);
    bool sendfriend_get_add_list();
    bool recvfriend_get_add_list(MB_MsgBuffer* recvPacket);
    bool sendfriend_add(int nCount,uint32_t* list);
    bool recvfriend_add(MB_MsgBuffer* recvPacket);
    bool sendfriend_explore(std::string roleName);
    bool recvfriend_explore(MB_MsgBuffer* recvPacket);
    bool sendfriend_delete(uint8_t type, uint32_t roleID);
    bool recvfriend_delete(MB_MsgBuffer* recvPacket);
    bool recvfriend_notify_delete(MB_MsgBuffer *recvPacket);
    //被動添加好友或仇人
    bool recvfriend_new(MB_MsgBuffer* recvPacket);
    
    //好友挑戰
    void sendfriend_fight(uint32_t roleid);
    void recvfriend_fight(MB_MsgBuffer* recvPacket);
    
    //贈送体力部分
    bool sendfriend_send_energy(int nCount,uint32_t* list);
    bool recvfriend_send_energy(MB_MsgBuffer* recvPacket);
    bool recvfriend_give_energy_me(MB_MsgBuffer* recvPacket);
    bool recvfriend_send_energy_me(MB_MsgBuffer* recvPacket);
    bool sendfriend_give_energy(int nCount,uint32_t* list);
    bool recvfriend_give_energy(MB_MsgBuffer* recvPacket);
    bool sendfriend_give_all_enargy();
    //剩余体力領取次數
    CC_SYNTHESIZE(uint8_t, m_uGetEnergyLastTimes, GetEnergyLastTimes);
    //体力領取次數限制
    CC_SYNTHESIZE(uint8_t, m_uLimitGetEnergyTimes, LimitGetEnergyTimes);
    
    //体力領取次數限制
    CC_SYNTHESIZE(uint8_t, m_uFightTimes, FightTimes);
    CC_SYNTHESIZE(uint32_t, m_uFightRoleID, FightRoleID);
    
    void recvhomestead_sync_mating_cool_second(MB_MsgBuffer* pRecv);
    void recvhomestead_sync_pet(MB_MsgBuffer* pRecv);
    void recvhomestead_sync_add_enagy(MB_MsgBuffer* pRecv);
    
    //好友請求
    void sendfriend_add_list(); //好友請求消息列表
    void recvfriend_add_list(MB_MsgBuffer* pRecv);
    void recvfriend_new_add(MB_MsgBuffer* pRecv); //新增好友請求消息請求
    void sendfriend_agree(int nCount,uint32_t* list); //同意加好友
    void recvfriend_agree(MB_MsgBuffer* pRecv);
    void sendfriend_refuse(int nCount,uint32_t* list); //拒絕加好友
    void recvfriend_refuse(MB_MsgBuffer* pRecv);
    // 自動更新
private:
    MB_FriendMgr();
    CCArray* m_pArrayFriend;
    CCArray* m_pArrayEnemy;
    CCArray* m_pArrayExplore;
    CCArray* m_pArrayMsg;
    uint32_t m_uLastGetFriendListTime;
    
};

#endif /* defined(__ProjectMB__MB_DataFriend__) */
