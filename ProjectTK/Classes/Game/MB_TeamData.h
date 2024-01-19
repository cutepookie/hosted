
#ifndef __ProjectMB__MB_TeamData__
#define __ProjectMB__MB_TeamData__

#include "cocos2d.h"
#include "MB_TeamData.h"
USING_NS_CC;
#define MEMBER_NUM 6
class MB_PetData ;
class MB_ItemData;
class MB_DestinyData;

enum ItemPosType {
    
    kItemPosEquip1 = 1,
    kItemPosEquip2,
    kItemPosEquip3,
    kItemPosTreasure1,
    kItemPosTreasure2,
    kItemPosTreasure3,
    kItemPosTreasure4,
    kItemPosTreasure5,
    kItemPosTreasure6,
    kItemPosTreasure7,
    kItemPosTreasure8,
    };

typedef struct
{
    MB_PetData*     m_pPet ;
    MB_ItemData*       m_pEquip1;
    MB_ItemData*       m_pEquip2;
    MB_ItemData*       m_pEquip3;
    MB_ItemData*       m_pTreasure1;
    MB_ItemData*       m_pTreasure2;
    MB_ItemData*       m_pTreasure3;
    MB_ItemData*       m_pTreasure4;
    MB_ItemData*       m_pTreasure5;
    MB_ItemData*       m_pTreasure6;
    MB_ItemData*       m_pTreasure7;
    MB_ItemData*       m_pTreasure8;
    
} TeamDataStruct;

//class LieutenantData:public CCObject{
//
//    private:
//    
//        MB_PetData *m_pPet;
//        MB_ItemData *m_pEquip1;
//        MB_ItemData *m_pEquip2;
//        MB_ItemData *m_pEquip3;
//
//    public:
//    
//    LieutenantData();
//    ~LieutenantData();
//    void setPet(MB_PetData *data);
//    void setEquip1(MB_ItemData *data);
//    void setEquip2(MB_ItemData *data);
//    void setEquip3(MB_ItemData *data);
//    MB_PetData *getPet();
//    MB_ItemData * getEquip1();
//    MB_ItemData * getEquip2();
//    MB_ItemData * getEquip3();
//    CC_SYNTHESIZE(uint16_t, m_nSpecialID, SpecialID);
//    CC_SYNTHESIZE(uint16_t, m_nAtkID, AtkID);
//    CC_SYNTHESIZE(uint16_t, m_nHP, HP);
//    CC_SYNTHESIZE(uint8_t,m_nLock1,Lock1);
//    CC_SYNTHESIZE(uint8_t,m_nLock2,Lock2);
//    CC_SYNTHESIZE(uint8_t,m_nLock3,Lock3);
//    CC_SYNTHESIZE(uint8_t, m_nIsUlock, IsUlock);
//    CC_SYNTHESIZE(int, m_nReputation,Reputation);
//    CC_SYNTHESIZE(uint8_t, m_nLockLevel,LockLevel);
//    bool isActive();
//    uint32_t getFighterChange();
//};
//class Lieu_ViewData :public CCObject{
//
//    public :
//    
//        Lieu_ViewData(){
//            
//        }
//        ~Lieu_ViewData(){
//    
//        }
//        CC_SYNTHESIZE(uint16_t, m_nPetType, PetType);
//};
//class LiBoxTemlete:public CCObject{
//
//    private :
//    
//    std::string m_strName;
//    std::string m_strIcon;
//    
//    public :
//    
//    LiBoxTemlete(){
//    
//        m_nLiBoxID = 0;
//        m_nValue = 0;
//    }
//    ~LiBoxTemlete(){
//    
//    }
//    CC_SYNTHESIZE(uint16_t, m_nLiBoxID, ID)
//    CC_SYNTHESIZE(uint8_t, m_nType, Type)//专属1//攻击2//加血3//
//    CC_SYNTHESIZE(uint16_t, m_nStar, Star)
//    CC_SYNTHESIZE(uint16_t, m_nValue, Value)
//
//    const char * getName(){
//    
//        return m_strName.c_str();
//    }
//    void setName(const char * name){
//    
//        m_strName = name;
//    }
//    const char * getIcon(){
//        
//        return m_strIcon.c_str();
//    }
//    void setIcon(const char * name){
//        
//       m_strIcon = name;
//    }
//
//};

typedef struct boxFreshCost{
    
    uint8_t m_nLockCost;
    uint16_t m_nLockCostType;
    int m_nLockGold;
    
}boxFreshCost;
class MB_FightDataCover:public CCObject{

    public :
    
        MB_FightDataCover(){
        
        }
        ~MB_FightDataCover(){
    
        }
        CC_SYNTHESIZE(int, m_nFightPower, FightPower);
        CC_SYNTHESIZE(int, m_nAddPower, AddPower);
};
class MB_TeamData :public CCObject
{
private:
    
    CCArray * m_mapLiBox;
    TeamDataStruct* m_pTeamData[MEMBER_NUM];
    //CCArray* m_pLiData;
    CCArray * m_mapFightPower;
    
//    void initLiboxTemplete();
//    void initBoxes();
//    void initBoxes2();
    boxFreshCost m_nCost[3];
    uint8_t m_pNowLockOpPos;
    uint8_t m_pNowLockOpNum;
    void initFightPowerToAddMap();
    
public:
    
    MB_TeamData();
    ~MB_TeamData();
    

    static MB_TeamData *getInstance();
    
    static void destroyInstance();
    CC_SYNTHESIZE(int, m_nCurIndex, CurIndex);
    CC_SYNTHESIZE(uint64_t,m_nNowPet, NowPet);
    TeamDataStruct** getTeamData() {
    
        return m_pTeamData;
    }
    TeamDataStruct* getTeamMemberByIndex(int index)
    {
        return m_pTeamData[index];
    }
    
    TeamDataStruct* getTeamMemberByUID(uint64_t uid);
    
//    LieutenantData * getLiMemberByIndex(int index)
//    {
//        return (LieutenantData *)m_pLiData->objectAtIndex(index);
//    }

    // 获取是否有4星及以上的属性没有锁定
    //bool getIsLockedByValue(uint8_t index,uint16_t value);
    //bool getUp4StarIsLocked(uint8_t index);
    
    //换精灵
    bool petUpByPetID(uint8_t petPos, uint64_t petID);
    //换装备
    bool equipUpByItemUID(uint8_t petPos, uint64_t itemUID);
    //卸装备
    bool equipDownByItemUID(uint8_t petPos, uint64_t itemUID);
    //精灵换位
    bool exchangePetPos(uint8_t petPos, uint8_t targetPos);
    
    //副将
    //换精灵
//    bool petUpLiByPetID(uint8_t petPos, uint64_t petID);
//    //换装备
//    bool equipUpLiByItemUID(uint8_t petPos, uint64_t itemUID);
//    //卸装备
//    bool equipDownLiByItemUID(uint8_t petPos, MB_ItemData* itemData);
//    //精灵换位
//    bool exchangeLiPetPos(uint8_t petPos, uint8_t targetPos);
    

    
    //获取精灵位置
    uint8_t getPetPosByPetID(uint64_t petID);
    
    //检查treasure装备合法性
    bool canEquipTreasure(uint8_t petPos, uint8_t itemPos, uint64_t itemUID);
    //获取队伍的总战斗力
    uint64_t getFightPower();
    
    //精灵上场
    bool sendpet_standup(uint8_t petPos, uint64_t petID);
    bool recvpet_standup(MB_MsgBuffer* recvPacket);
    //精灵下阵
    bool sendpet_zhenxing(uint64_t petId1,uint64_t petId2,uint64_t petId3,uint64_t petId4,uint64_t petId5,uint64_t petId6,uint64_t equipId1,uint64_t equipId2,uint64_t equipId3,uint64_t equipId4,uint64_t equipId5,uint64_t equipId6);
    //精灵移动
    bool sendpet_move_pos(uint8_t petPos, uint8_t targetPos);
    bool recvpet_move_pos(MB_MsgBuffer* recvPacket);
    //精灵位置信息
    bool sendpet_pos_list();
    bool recvpet_pos_list(MB_MsgBuffer* recvPacket);
//    bool sendpet_lieu_pos_list();
//    bool recvpet_lieu_pos_list(MB_MsgBuffer* recvPacket);
//    bool sendpet_lieu_info_list();
//    bool recvpet_lieu_info_list(MB_MsgBuffer* recvPacket);
//    bool sendpet_lieu_standup(uint8_t petPos, uint64_t petID);
//    bool recvpet_lieu_standup(MB_MsgBuffer* recvPacket);
//    bool sendpet_lieu_untie(uint8_t petPos);
//    bool recvpet_lieu_untie(MB_MsgBuffer * recvPacket);
//    bool sendpet_lieu_move_pos(uint8_t petPos, uint8_t targetPos);
//    bool recvpet_lieu_move_pos(MB_MsgBuffer *recvPacket);
//    bool sendpet_lieu_lock_clo(uint8_t petPos, uint8_t num);
//    bool recvpet_lieu_lock_clo(MB_MsgBuffer *recvPacket);
//    bool sendpet_lieu_unlock_clo(uint8_t petPos, uint8_t num);
//    bool recvpet_lieu_unlock_clo(MB_MsgBuffer *recvPacket);
//    bool sendpet_lieu_refresh_clo(uint8_t petPos);
//    bool recvpet_lieu_refresh_clo(MB_MsgBuffer *recvPacket);
//    bool sendpet_lieu_tie_info();
//    bool recvpet_lieu_tie_info(MB_MsgBuffer *recvPacket);
//    bool sendpet_lieu_refresh_freetimes();
//    bool recvpet_lieu_refresh_freetimes(MB_MsgBuffer *recvPacket);
    CC_SYNTHESIZE(uint16_t, m_nFreeTimes, FreeTimes);
    
    //一键换装
    void senditem_up_all_equip(uint64_t uid);
    //    void recvitem_up_all_equip(MB_MsgBuffer * recvPacket);
    //阵容对比
    bool sendpet_view_other(uint32_t roleID,uint16_t serverid);
    CC_SYNTHESIZE(uint16_t,m_nLastServerID,LastServerID);
    bool recvpet_view_other(MB_MsgBuffer* recvPacket);
    bool recvpet_refresh_power(MB_MsgBuffer* recvPacket);
    bool sendpet_view_other_dtl(uint32_t roleID,uint16_t serverid);
    bool recvpet_view_other_dtl(MB_MsgBuffer* recvPacket);
    //bool sendteam_view_other_dtl(uint32_t roleID);
    bool recvteam_view_other_dtl(MB_MsgBuffer* recvPacket);
    bool sendteam_view_other(uint32_t roleID);
    bool recvteam_view_other(MB_MsgBuffer *recvPacket);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    int getLimitPet();
    int getLimitPetByLevel(int level);
    int getEmptyCount();
    int getLimitLevelByIndex(int index);
    bool checkInTeam(MB_PetData *data);
    bool checkInTeam(uint64_t petID);
    TeamDataStruct* checkInTeamData(MB_PetData *data);
    bool isTeamNone();
    uint64_t getSelectPetID();
    
//    LiBoxTemlete *getLiBoxTemleteByID(uint16_t liboxid);
    int IsUnLockDestiny(MB_DestinyData *data,TeamDataStruct *tdata);
    bool IsFindInItem(int ItemType,TeamDataStruct* tdata);
    bool IsFindInTeam(int petType);
    bool IsFindInLiTeam(int petType,bool isLiTeam);
//    int IsUnLockDestiny(MB_DestinyData *data,LieutenantData *tdata);
//    bool IsFindInItem(int ItemType,LieutenantData * tdata);

    boxFreshCost* getCostByLockNum(int lockNum);
    uint32_t getFightPowerToAddByFightPower(uint32_t fightpower);
    
    bool checkSuitActivate(MB_ItemData* pItem,TeamDataStruct* pTs);
};

#endif /* defined(__ProjectMB__MB_TeamData__) */
