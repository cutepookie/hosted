
//传輸動画中的數据项

#ifndef ProjectMB_MB_FightData_h
#define ProjectMB_MB_FightData_h

class MB_DataPVPRank;
//
enum FightResultType {
    kFightResultTypePVE = 1,
    kFightResultTypePVPRanking,
    kFightResultTypeTreasureRob,
    kFightResultTypeRocketTeam,
    kFightResultTypeNanm,
    kFightResultTypeHuRong,
    kFightResultTypeReplay,
//    kFightResultTypeWorldkingRanking,
//    kFightResultTypeWorldkingRecord,
//    kFightResultTypeWorldkingSelfRecord,
    kFightResultType3v3,
    kFightResultTypeChangeCoin,
    kFightResultTypeDemoFight,
    kFightResultTypeRuleFight,  //秩序戰场
    kFightResultTypeRoad,   //訓練師之路
    kFightResultTypeNoRule,   //大乱鬥
    kFightResultTypeKing,  //精靈王
    kFightResultTypeTrainerTrove,    //訓練師寶库
    kFightResultTypeFriendFight     //好友挑戰
};

typedef struct p_fighter
{
    uint64_t        petId;
    uint16_t        petTypeID;
    signed  char    petPos;
    uint64_t        petHp;
    uint64_t        petHpMax;
    int             petSp;
    uint8_t         petQuality;
    uint16_t        petLevel;
    p_fighter*      next;
}p_fighter;

typedef struct MB_ActionEffect{
    
    char effectName[100];
    float effectTime ;
    float effectStartTime;
    int effectType;    //特俗動画里面表示概率
    char sound[80];
    int flipType;
    int turnMove;
    MB_ActionEffect *next;
    
}MB_ActionEffect;

typedef struct MB_Action{
    
    char actionName[80];
    char actionFlipName[80];
    float actionTime;
    char sound[50];
    int  actionType;
    uint8_t actionID;
    float   moveTime;
    uint8_t moveType;
    MB_ActionEffect *effect;
    MB_ActionEffect *speffect;
} MB_Action;


typedef struct p_action{

    signed char petPos;
    MB_Action *action;
    signed char targetPos[7];
    signed  char addSp;
    int  addHp;
    signed char state ;
    p_action * next ;
    
    
} p_action;

typedef struct p_item_view{
    
    int16_t itemTypeId;
    int16_t  itemLevel;
    int16_t  itemRank;
    short itemNum;
    p_item_view * next ;
    
}p_item_view;

typedef struct p_petExp{

    int8_t petPos ;
    int addExp;
    int8_t isUpgraded ;
    p_petExp *next ;

}p_petExp;

typedef struct   p_reward{
    
    int coin ;
    int roleExp ;
    int reputation; //声望
    p_petExp *petExp ;
    int gold ;
    p_item_view *item;
    
    int8_t score ;
    int16_t preLevel;
    int64_t preExp ;
    int preEnergy;
    int preDiscovery;
    int preStar;

}p_reward;

typedef struct recvfight{
    
    recvfight()
    {
        m_pReplayCallBackTarget = NULL;
        m_pReplayCallBack = NULL;
        memset(isBoss, 0, 7);
        type = (FightResultType)0;
    }
    bool hasBoss()
    {
        for(int i=0;i<7;++i)
        {
            if(isBoss[i]=='1')
            {
                return true;
            }
        }
        return false;
    }
    p_fighter *fighterList;
    p_action *actionList;
    char isBoss[7] ;
    signed  char  issuccess ;
    FightResultType type;
    
    CCCallBackDelegate*   m_pReplayCallBackTarget;
    CallBack1st            m_pReplayCallBack;
}recvfight ;

typedef struct p_result_ranking{
    uint8_t _isSuccess;
    MB_DataPVPRank* _dataPVPRank;
    uint16_t _myRank;
    uint16_t _myOldRank;
    
    int32_t _addCoin;       //v1.0.5 chk
}p_result_ranking;

#endif
