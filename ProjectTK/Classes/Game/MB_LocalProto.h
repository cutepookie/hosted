
#ifndef ProjectMB_MB_LocalProto_h
#define ProjectMB_MB_LocalProto_h


//是否開啟下載更新
#ifdef DEBUG
#define USE_FILE_CHECK 0
#else
#define USE_FILE_CHECK 1
#endif

#define CC_UPDATE_BAG_DATA      1
#define CC_CALLGENERAL_SHOW_ALL_CARD    1   //显示召喚卡牌


//窗口引导tag标志
#define TUTORIAL_DIALOG_TAG 2000
#define ROLED_ETAIL_TAG 789
//layer tag
#define LAYER_SCENE_MAIN 101      
#define LAYER_MAIN_CAMPAIGN_TAG 102
#define MB_NODEDUNGEONUNIT_TAG 103
#define LAYER_TAG_BIND_GUEST 105
#define LAYER_EVENTBTN_TAG 106
#define LAYER_MAIN_COMMAND 107
#define LAYER_EVENT_POPWND_TAG 10086
#define LAYER_MAIN_CAMPAIGN_ADVENTURE_TAG 108
#define LAYER_MAIN_CAMPAIGN_ADVENTURE_QUICKSEARCH_TAG 109
#define DEAD_EFFECT_TAG 1000
#define LAYER_CHAT_TAG 110
#define LAYER_CHAT_LIST_TAG 111
#define LAYER_ROLE_DETAIL 112
#define LAYER_ACHIVE 113
#define LAYER_ITEM_DETAIL 114
//layer z order
#define Z_ORDER_SCENEMAIN 0
#define Z_ORDER_CHAT 2
#define Z_ORDER_MAINCOMMAND 1
#define Z_ORDER_ROLEDETAIL 3
#define Z_ORDER_OUTSHOW 4
#define Z_ORDER_CHANGEANI 7
#define Z_ORDER_SWEEP 5
#define Z_ORDER_CHATLIST 6
#define Z_ORDER_ACHIVE  8 //成就
#define Z_ORDER_STORY 7 //剧情


#define Z_ORDER_WarningHeader 13 //跑馬灯
#define Z_ORDER_Detail 12
#define Z_ORDER_RoleInfoHeader 11

#define Z_ORDER_MESSAGE 20
#define Z_ORDER_PVECOMMAND 20


#define CARD_IN_GAME 6  //隊伍上限

#define COIN_ID 30007//21100//钱幣图标
#define FRESH_ID 30003//21111 //黑石货幣图表
#define COLLECT_ID 21108 //感恩书图标
#define SPEED_ID 21109    //神速令图标
#define GOLD_ID 30008//21101 //元寶
#define REPUTATION_ID 30006//21102//徽章
#define ROLE_EXP_ID 30005 //角色經驗
#define GER_EXP_ID 21104
#define COMPOS_ITEM3_ID 21144
#define COMPOS_ITEM4_ID 21145
#define COMPOS_ITEM5_ID 21146
#define COMPOS_GER3_ID 21141
#define COMPOS_GER4_ID 21142
#define COMPOS_GER5_ID 21143

#define GER_SHOP_CHAPTER_ID 6666
#define ITEM_SHOP_CHAPTER_ID 8888

#define MAX_LEVEL 241   //等級上限+1
#define MAX_GER_QUALITY 20  //精靈升品上限
#define MAX_EQUIP_QUALITY 10    //武器升品上限
#define MAX_TREASURE_QUALITY 10     //法寶升品上限+1

#define MAX_PVP_RANKING 15  //PVP RANKING 上限
#define MAX_PVP_TREASURE 15 //夺寶 上限

#define PIC_SHOW_TYPE_GER 1
#define PIC_SHOW_TYPE_TREASURE  2
#define PIC_SHOW_TYPE_EQUIP 3

#define MAX_VIP_LEVEL 15
#define EQUIP_MAX 6//裝備最大值
#define TREASURE_MAX 3 //寶物最大值
#define DESTINY_MAX 4 //伙伴最大值
#define MAX_ITEM_ATTR 4     //裝備属性數量
#define MAX_GER_STAR 7      //精靈的最高星級
#define MAX_ITEM_STAR 7     //裝備的最高星級
#define MAX_TUTORIAL_ID 200        //新手引导id最大限制


#define JAVA_PACKAGE "com/zdbpkq/bt/"

#define GETBYKEY(x) CCUserDefault::sharedUserDefault()->getBoolForKey(x)
#define SETBYKEY(x,y) CCUserDefault::sharedUserDefault()->setBoolForKey(x,y)
#define  IS_CHECKED_UPDATE CCUserDefault::sharedUserDefault()->getBoolForKey("ischeckedupdate")
#define  SET_CHECKED_UPDATE(x) CCUserDefault::sharedUserDefault()->setBoolForKey("ischeckedupdate",x);
enum chapterType{
    
    kChapterTypeNormal = 0,
    kChapterTypeAdventure,
    kChapterTypeAdventureShop,
    kChapterTypeAdventurePetShop,
    kChapterTypeAdventureCollect,
    kChapterTypeAdventureTreasure,
    kChapterTypeRocketTeam,
    kChapterTypeHuaRong,
    kChapterTypeLock,
    kChapterTypeNone,
    kChapterTypeLockEvent,
    kChapterTypeNanM,
    kChapterTypeAdvance,
};


class CCCallBackDelegate
{
public:
};
typedef void (CCCallBackDelegate::*CallBack1st)();
#define callback_selector1st(_SELECTOR) (CallBack1st)(&_SELECTOR)

enum kSceneMainLayerType
{
    kSceneMainLayerTypeNone = 0,
    kSceneMainLayerTypeMain,
    kSceneMainLayerTypePVE,
    kSceneMainLayerTypePVP,             //爭霸(PVP)
    kSceneMainLayerTypePet,
    kSceneMainLayerTypeShop,
    kSceneMainLayerTypeActivity,
    kSceneMainLayerTypeOther,
};
enum kSceneTipLayerType
{
    kSceneTipLayerTypeNone = 0,
    kSceneTipLayerTypePet,
    kSceneTipLayerTypeItem,
    kSceneTipLayerTypePetEntrance,
    kSceneTipLayerTypePetUp,
    kSceneTipLayerTypeAdventure,
    kSceneTipLayerTypeItemEntrance,
    kSceneTipLayerTypeHome,
    kSceneTipLayerTypeShopToy,
    kSceneTipLayerTypeBackpack,
};
enum KReplayType{

    kReplayTypePvp = 0,
    kReplayTypeKing ,
    kReplayTypeEmper,
    kReplayTypeEight,
    kReplayTypeOnes,
    kReplayTypeRuleFight
};
enum kSubLayerType
{
    kSubLayerTypeNone = 0,
    //main
    kSubLayerTypeMainPetUpdate, //換精靈
    kSubLayerTypeMainPetList,   //精靈列表
    kSubLayerTypeMainEquipList, //裝備列表
    kSubLayerTypeMainTreaList,  //寶物列表
    kSubLayerTypeMainOtherList, //道具列表
    kSubLayerTypeMainShowPic,   //图鉴
    kSubLayerTypeMainFriend,    //好友
    //pve
    kSubLayerTypeNormal,
    kSubLayerTypeAdventure,
    kSubLayerTypeCity,
    kSubLayerTypeRocketTeam,
    kSubLayerTypeHuaRong,
    kSubLayerTypeWorldBoss,
    kSubLayerTypeAdvance,
    kSubLayerTypeShenJiangLu,
    //pvp
    kSubLayerTypeRanking,       //爭霸
    kSubLayerTypeTreasure,      //夺寶
    kSubLayerTypePvpKing,
    kSubLayerTypePvpEmperor,
    kSubLayerTypePvpOnes,
    //petneral
    kSubLayerTypeTeam,
    kSubLayerTypePet,
    //shop
    kSubLayerTypeGeneral,
    kSubLayerTypeIngots,
    kSubLayerTypePoints,
    kSubLayerTypePay,
    kSubLayerTypeBox,
    //other
    kSubLayerChangeCoin
};

enum kListItemType {
    kListItemTypeChange,
    kListItemTypeEquip,
    kListItemTypeTreasure,
    kListItemTypeOther,
    kListItemTypeUnion,
    
    kListItemTypeWeaponUp,
    kListItemTypeDefenceUp,
    kListItemTypeHorseUp,
    kListItemTypeTreasureUp,
    
    kListItemTypeEquipSale,
    kListItemTypeTreasureSale,
    kListItemTypeItemEnhance,
    kListItemTypeTreasureCost,
    
    kListItemTypeLevelUp,
    };

//獎勵類型,标识作用
enum kRewardType {
    kRewardTypeTitle = 1,
    kRewardTypeDaily,
    kRewardTypeLevel,
};

enum kRewardGetType {
    
    kRewardGetTypeReady = 0,
    kRewardGetTypeAlready = 1,
    kRewardGetTypeDisable,
};

enum kRewardValueType {
    kRewardValueTypeItem = 1,
    kRewardValueTypePet,
};
enum  kBuyTimesType{

    kBuyTimesTypeEnergy = 1,
    kBuyTimesTypeDiscovery,
    kBuyTimesTypePvp,
    kBuyTimesTypeRuleFight,//秩序戰场次數
    kBuyTimesTypeCoin
};
enum kShareType{

    kShareTypeNone =0,
    kShareTypeCallPet = 10001,
    kShareTypeChange,
    kShareTypeMail,
    kShareTypeCollect,
    kShareTypeTreasure,
    kShareTypeShopBox,
    kShareTypeListBox,
    kShareTypeTreasureRob
};
enum kNodePetType{
    
    kNodePetTypeMain = 0,
    kNodePetTypeMainNone,
    
    kNodePetTypeAid,
    kNodePetTypeLock,
    kNodePetTypeAidNone,
    kNodePetTypeAidNoneLock,
    
    kNodePetTypeGuard,
    
    kNodePetTypeTeamAid,
    kNodePetTypeTeamLock,
    kNodePetTypeTeamAidNone,
    kNodePetTypeTeamAidNoneLock,
    
    kNodePetTypeOtherMain ,
    kNodePetTypeOtherAid ,
};
enum PetListType{
    kListTypeStand =0,
    kListTypeList = 1,
    kListTypeAidStand = 2,
};

#define UTF8_LENGTH(Char)            \
((Char) < 0x80 ? 1 :                \
((Char) < 0x800 ? 2 :            \
((Char) < 0x10000 ? 3 :            \
((Char) < 0x200000 ? 4 :            \
((Char) < 0x4000000 ? 5 : 6)))))

#define MB_TARGET_PARENT(T, ptr) \
            T * ptr = NULL; \
            CCNode* nptr = NULL; \
            for (nptr = this; nptr->getParent() != NULL; nptr = nptr->getParent()) { \
                ptr = dynamic_cast< T *>(nptr); \
                if (ptr != NULL) \
                { \
                    break; \
                } \
            }

#define MB_TARGET_PARENT2(T, ptr) \
            T * ptr = NULL; \
            nptr = NULL; \
            for (nptr = this; nptr->getParent() != NULL; nptr = nptr->getParent()) { \
                ptr = dynamic_cast< T *>(nptr); \
                if (ptr != NULL) \
                { \
                    break; \
                } \
            }
#endif


#define CCARRAY_FOREACH_4TYPE(__array__,__type__, __object__)                                                                         \
if ((__array__) && (__array__)->data->num > 0)                                                                     \
for(CCObject** __arr__ = (__array__)->data->arr, **__end__ = (__array__)->data->arr + (__array__)->data->num-1;    \
__arr__ <= __end__ && (((__object__) = dynamic_cast<__type__>(*__arr__)) != NULL/* || true*/);                                             \
__arr__++)
