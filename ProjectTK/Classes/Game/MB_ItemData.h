
#ifndef __ProjectMB__MB_MB_ItemData__
#define __ProjectMB__MB_MB_ItemData__

#include "cocos2d.h"
#include "Game.h"
#include "MB_DescriptionCommonTable.h"
#include "MB_DateMgr.h"
#include "MB_ClientData.h"
USING_NS_CC;

#define PACKET_ITEM_MAX     100
#define EQUIP_ID_MAX        14000
#define TREASURE_ID_MAX     16000
#define MATERIAL_ID_MAX     22000
#define BOX_ID_MAX          28000
#define PERLINEITEM     6
#define LASTCELLADDHEIGHT     100
//道具類型
typedef enum 
{
    kWEAPON = 1,                                    //兵器
    kARMOR = 2,										//戰甲
    kHORSE = 3,										//坐骑
    kTREASURE_PHYSICAL_DAMAGE_ADDTION = 4,			//破甲寶物
    kTREASURE_PHYSICAL_DAMAGE_REDUCTION = 5,        //護甲寶物
    kTREASURE_MAGIC_DAMAGE_ADDTION = 6,             //法穿寶物
    kTREASURE_MAGIC_DAMAGE_REDUCTION = 7,			//法抗寶物
    kTREASURE_CRITIC = 8,							//暴擊寶物
    kTREASURE_CRITIC_REDUCE = 9,					//韧性寶物
    kTREASURE_DOOM = 10,							//命中寶物
    
    kDEBRIS_WEAPON = 11,							//武器碎片
    kDEBRIS_HEADWEAR= 12,							//头盔碎片
    kDEBRIS_ARMOR= 13,                              //護甲碎片
    kDEBRIS_WINGS = 14,                             //幸运物碎片
    kDEBRIS_TOTEM = 15,                             //项链碎片
    kDEBRIS_RUNESTONE = 16,							//戒指碎片
    
    kTREASURE_REEL_REDUCE = 17,						//抗擊晕寶物
    kMATERRIAL = 18,								//材料
    kOTHER = 19,                                    //其他
    KMATERRIAL_PATCH_GENERAL = 20,                  //將魂（精靈碎片）
    KMATERRIAL_PATCH_WEAPON = 21,                   //武器碎片
    KMATERRIAL_PATCH_ARMOR  = 22,                   //防具碎片
    KMATERRIAL_PATCH_HORSE  = 23,                   //坐骑碎片
    kOTHER_BOX = 24,                                //寶箱
    kTREASURE_TIANQIAN = 25,                       //天谴
    kTREASURE_DIKUN = 26,                           //地锟
    kTREASURE_LEIZHEN = 27,                         //雷震
    kTREASURE_FENGXUN = 28,                         //风讯
    kTREASURE_SHUIKAN = 29,                         //水堪
    kTREASURE_HUOLI = 30,                           //huoli
    kTREASURE_SHANGENG = 31,                        //shangeng
    kTREASURE_ZEDUI = 32,                           //zedui
    kITEM_WING = 33,                                //翅膀
    kITEM_HEADWEAR = 34,                            //头饰
    kITEM_TOTEM = 35,                               //图腾
    kITEM_RUNESTONE = 36,                           //符石
    kITEM_FORMULA = 37,                              //配方
    ENERGY_RECOVERY = 38,                            //体力恢複道具
    kEXPCARD = 39,                                  //經驗卡牌
    kNONE,
} ItemType;

typedef enum
{
    Energy_ADD = 1,                 //体力道具
    Discovery_ADD = 2,              //探索次數道具
    PVP_ADD = 3,                    //爭霸次數道具
    
} ItemUseType;

enum eItem_Attribute_Type
{
    eItem_Attribute_Type_Attack = 1,//攻擊
    eItem_Attribute_Type_HP,        //生命
    eItem_Attribute_Type_PDAdd,     //破甲
    eItem_Attribute_Type_PDRed,     //護甲
    eItem_Attribute_Type_MDAdd,     //法穿
    eItem_Attribute_Type_MDRed,     //法抗
    eItem_Attribute_Type_Critic,    //暴擊
    eItem_Attribute_Type_CriticRed, //韧性
    eItem_Attribute_Type_Doom,      //命中
    eItem_Attribute_Type_Miss,      //閃避
    eItem_Attribute_Type_SPInit,    //能量
    eItem_Attribute_Type_SPLeft,    //固元
    eItem_Attribute_Type_Absorb,    //吸血
    eItem_Attribute_Type_DamageBack,//反弹
    eItem_Attribute_Type_Reel,      //擊晕
    eItem_Attribute_Type_ReelRed,   //抗晕
    eItem_Attribute_Type_Count,     //數量
};

typedef std::map<eItem_Attribute_Type,int32_t>  attributeMap;
typedef attributeMap::iterator                  attributeMap_It;

class MB_ItemData;

//道具模板類
class MB_ItemTemplate: public CCObject
{
public:
    
    MB_ItemTemplate();
    ~MB_ItemTemplate();
    
    //名称
    void setItemName(const char* itemName) { m_sItemName = itemName;}
    const char* getItemName() { return m_sItemName.c_str();}
    //描述
    void setItemDesc(const char* itemDesc) { m_sItemDesc = itemDesc;}
    const char* getItemDesc() { return m_sItemDesc.c_str();}
    //道具图标
    void setItemIcon(const char* itemIcon) { m_sItemIcon = itemIcon;}
    const char* getItemIcon() { return m_sItemIcon.c_str();}
    //道具整体形象图
    void setItemCard(const char* itemCard) { m_sItemCard = itemCard;}
    const char* getItemCard() { return m_sItemCard.c_str();}
    
    CC_SYNTHESIZE(uint16_t, m_iItemID, ItemID)
    CC_SYNTHESIZE(uint8_t,  m_iItemType, ItemType)
    //是否堆叠
    CC_SYNTHESIZE(bool,     m_bItemStack, ItemStack)
    CC_SYNTHESIZE(uint16_t,  m_iItemCost, ItemCost)
    //星級
    CC_SYNTHESIZE(uint8_t,  m_iItemStar, ItemStar)
    //品階上限
    CC_SYNTHESIZE(uint8_t, m_iItemRankMax, ItemRankMax)

    //要合成道具的ID，沒有就是0
    CC_SYNTHESIZE(uint16_t, m_iComposeItemID, ComposeItemID)
    //合成新道具所需要本道具的數量
    CC_SYNTHESIZE(uint16_t, m_iComposeNum, ComposeNum)
    
    CC_SYNTHESIZE(uint16_t, m_nComposeCommonMaxNum, ComposeCommonMaxNum);

    CC_SYNTHESIZE(uint16_t, m_nSuitID,SuitID);//套装ID，属於套装则為套装ID，不属於套装则為0
public:
    void                    setAttribute        (eItem_Attribute_Type type,int32_t value);
    float                   getAtrribute        (eItem_Attribute_Type type,MB_ItemData* entity = NULL);
    float                   getAtrribute        (eItem_Attribute_Type type, uint8_t itemLevel, uint8_t itemRank);
    bool                    containsAtrribute   (eItem_Attribute_Type type);
    attributeMap&           getAtrributeMap     (void);
    bool getIsDebris();
    bool getIsEquip();
protected:
    float                   calculateAttribute  (eItem_Attribute_Type type,MB_ItemData* entity ,float templateValue);
    float                   calculateAttribute  (eItem_Attribute_Type type, uint8_t itemLevel, uint8_t itemRank,float templateValue);

private:
    attributeMap            m_attributeMap;
    std::string             m_sItemName;
    std::string             m_sItemDesc;
    std::string             m_sItemIcon;
    std::string             m_sItemCard;
    
};


//实例化道具類
class MB_ItemData: public CCObject
{
public:
    MB_ItemData();
    ~MB_ItemData();
    
    CC_SYNTHESIZE(uint64_t, m_uItemUID, ItemUID)
    CC_SYNTHESIZE(uint16_t, m_uItemID, ItemID)
    //等級
    CC_SYNTHESIZE(uint8_t, m_uItemLevel, ItemLevel)
    //品階
    CC_SYNTHESIZE(uint8_t, m_uItemRank, ItemRank)
    //數量
    CC_SYNTHESIZE(uint16_t, m_uItemNumber, ItemNumber)
    //所属精靈,默认0
    CC_SYNTHESIZE(uint64_t, m_uItemPetID, ItemPetID)
    //裝備位置,默认0
    CC_SYNTHESIZE(uint8_t, m_uItemPos, ItemPos)
    //品階衰减倒計時
    CC_SYNTHESIZE(uint32_t, m_uRankOverTime, ItemRankOverTim)
    //不同步的属性
    //是否准备出售
    CC_SYNTHESIZE(bool, m_bReadyForSell, ReadyForSell);
    //从模板獲取的itemtype,方便遍历
    CC_SYNTHESIZE(uint8_t, m_uItemType, ItemType);    
    CC_SYNTHESIZE(uint16_t, m_uExp, Exp);
    bool getUsed();
    int getTemplateStar();
    bool isSuitPart(int nSuitId);
};


//每日獎勵數据
class DailyRewardValue: public CCObject
{
public:
    // 獎勵類型:
    // 1=> 官爵俸禄
	// 2=> 連续登录獎勵
	// 3=> 升級禮包
    CC_SYNTHESIZE(uint8_t, m_uType, Type);
    //type=1，當前官爵，
    //type=2，當前連续登录天數,
    //type=3,上次領取的登录獎勵等級
    CC_SYNTHESIZE(uint8_t, m_uValue, Value);
    //是否領取
    CC_SYNTHESIZE(uint8_t, m_uIsGet, IsGet);
};

class DailyReward: public CCObject
{
public:
    DailyReward();
    ~DailyReward();
    CCArray* getValueArray() { return m_pValueArray;}
private:
    CCArray* m_pValueArray;
};

class RewardTempleteValue: public CCObject
{
public:
    RewardTempleteValue():m_uNumber(1),m_uValueID(0),m_uType(0){}
    CC_SYNTHESIZE(uint8_t, m_uType, Type);
    CC_SYNTHESIZE(uint16_t, m_uValueID, ValueID);
    CC_SYNTHESIZE(uint32_t, m_uNumber, Number);
};

class RewardTemplete: public CCObject
{
public:
    RewardTemplete();
    ~RewardTemplete();
    
    CC_SYNTHESIZE(uint8_t, m_uID, ID);
    
    CCArray* getValueArray() { return m_pValueArray;}
    
private:
    CCArray* m_pValueArray;
};


//品階提升价格显示模板
class MB_ItemQualityCostTemplete: public CCObject
{
public:
    MB_ItemQualityCostTemplete();
    
    CC_SYNTHESIZE(uint8_t, m_nStar, Star);
    CC_SYNTHESIZE(uint16_t, m_nQuality, Quality);
    CC_SYNTHESIZE(int64_t, m_nCoin, Coin);
};


class MB_ExpCardData : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
    CC_SYNTHESIZE(uint32_t, m_nExp, Exp);
    CC_SYNTHESIZE(uint16_t, m_nTid, Tid);
};




typedef std::map<uint16_t, MB_ItemTemplate*> MB_ItemTemplateMap;
typedef std::pair<uint16_t, MB_ItemTemplate*> MB_ItemTemplateMapEntry;
typedef std::map<uint8_t, int> ItemRankValueMap;
typedef std::pair<uint8_t, int> ItemRankValueMapEntry;

//使用道具限制
class MB_UseItemRule:public CCObject
{
public:
    MB_UseItemRule();
    static MB_UseItemRule* create(uint16_t id,uint8_t times,uint8_t type = 0);
    MB_UseItemRule(uint16_t id,uint8_t times,uint8_t type = 0);
    CC_SYNTHESIZE(uint16_t, m_utID,ItemTID);        //道具類型
    CC_SYNTHESIZE(uint8_t, m_uLastTime, LastTime); //道具剩余使用次數
    CC_SYNTHESIZE(uint8_t, m_uType, Type); //道具類型
};
//道具管理類
class MB_ItemMgr: public MB_DataMgr
{
    
public:
    
    MB_ItemMgr();
    ~MB_ItemMgr();

    static MB_ItemMgr* getInstance();
    static void         destroyInstance();

    //template
    bool                initItemTemplate();
//    bool                initItemRank();
    MB_ItemTemplateMap*    getItemTemplateMap();
    MB_ItemTemplate*       getItemTemplateByID(uint16_t itemID);
    int                 getItemQualityByUid(uint64_t uid);
    int                 getItemQualityByTid(uint32_t tid);
    
    unsigned int        getItemEntityCount(uint32_t itemID);
    uint64_t            getItemEntityUID  (uint32_t itemID,uint32_t itemNum);
    
    uint32_t            getItemCostByUID         (uint64_t uid);
    uint32_t            getEnhanceItemCostByUID  (uint64_t uid);

    float               getAtrributeByUID (uint64_t uid,eItem_Attribute_Type type);
//    int                 getTresureOtherAttributeValue(uint16_t type, uint8_t rank);
    std::string         getItemNameByUid           (uint64_t uid);
    std::string         getItemNameByTid           (uint32_t tid);
    
    bool                canBeEnhancedByItemUid     (uint64_t uid);
    bool                canBeEnhancedByItemTid     (uint32_t tid);
    
    void                setItemLevel               (uint64_t uid,uint16_t level);
    void                plusItemLevel              (uint64_t uid,uint16_t plusNum);
    // all entity
    CCArray*            getItemDataArray() { return m_pItemDataArray;}
    MB_ItemData*           getItemDataByUID(uint64_t itemUID);
    int                 getCanComposPetNum();
    int                 getCanComposItemNum();
    int                 getCanComposPetNumByType(MB_ItemData * data);
    int                 getCanComposItemNumByType(MB_ItemData * data);
    //get type arr
    CCArray*            getItemFormulaArray(){return m_pItemFormulaArray;}
    CCArray*            getHeadwareArray(){ return m_pHeadwareArray;}
    CCArray*            getWingArray(){return m_pWingArray;}
    CCArray*            getRuneStoreArray(){return m_pRuneStoreArray;}
    CCArray*            getTotermArray(){return m_pTotermArray;}
    CCArray*            getEquipArray() { return m_pEquipArray;}
    CCArray*            getWeaponArray() { return m_pWeaponArray;}
    CCArray*            getDefenceArray() { return m_pDefenceArray;}
    CCArray*            getHorseArray() { return m_pHorseArray;}
    CCArray*            getTreasureArray() { return m_pTreasureArray;}
    CCArray*            getMaterialArray() { return m_pMaterialArray;}
    CCArray*            getBoxArray() { return m_pBoxArray;}
    CCArray*            getOtherArray() { return m_pOtherArray;}
    CCArray*            getEquipUnionArray() { return m_pEquipUnionArray;}
    CCArray*            getPetUnionArray() { return m_pPetUnionArray;}
    CCArray*            getCanEquipTreaArray(uint64_t petUID, uint8_t itemPos);
    
    CCArray*            getItemDebrisArray(){return m_pItemDebrisArray;};//碎片
    CCArray*            getExpCardArray(); //經驗卡
    void                sortDebrisArray();
    static bool         sortDebris(CCObject* p1,CCObject* p2);
    //使用次數限制道具數組（体力道具）
    CCArray*            getUseItemRuleArray(){return m_pUseItemRuleArray;};
    //領取相關隊列
    CCArray*            getDailyRewardArray() { return m_pDailyRewardArray;}
    CCArray*            getTitleRewardTempleteArray() { return m_pTitleRewardTemplete;}
    CCArray*            getDailyRewardTempleteArray() { return m_pDailyRewardTemplete;}
//    CCArray*            getLevelRewardTempleteArray() { return m_pLevelRewardTemplete;}
    
    //get entity
    MB_ItemData*           getEquipByUID(uint64_t uID);
    MB_ItemData*           getTreasureByUID(uint64_t uID);
    MB_ItemData*           getMaterialByUID(uint64_t uID);
    MB_ItemData*           getBoxByUID(uint64_t uID);
    bool                getItemInPackage(uint16_t tid);
    void                sortOtherArray();
    static bool          sortOther(CCObject* p1,CCObject* p2);
    static bool          sortExpCard(CCObject* p1,CCObject* p2);
    void                setSpriteFrame(CCSprite* icon,std::string frameName);
    
    //convert
    std::string         attrConvertToDes    (eItem_Attribute_Type type,float value);
    std::string         attrConvertToTitle    (eItem_Attribute_Type type);
    std::string         attrConvertToDesValue    (eItem_Attribute_Type type,float value);
    bool                isAttrValueDecimal  (eItem_Attribute_Type type);
    
    void                sortMB_ItemDataArray();
    void                updateSubArray();
    int                 getItemPrice(MB_ItemData* itemData, MB_ItemTemplate* itemTemplete);
    int                 getItemNumForExchangeByType(uint16_t type);
    unsigned int        getItemCountInPacket();
    //添加到待售列表
    bool                addItemForSell(uint64_t itemUID, ItemType itemType);
    //从待售列表中取消
    bool                removeItemForSell(uint64_t petID);
    //清空待售列表
    void                clearItemForSell();
    
    void                setSellTotalPrice(uint32_t price);
    
    ///c2s s2c
    //MB_ItemData 协议
    //獲取背包道具
    bool                senditem_bag();
    bool                recvitem_bag(MB_MsgBuffer* recvPacket);
    
    //獲取裝備道具
    bool                senditem_equip();
    bool                recvitem_equip(MB_MsgBuffer* recvPacket);
    
    //使用道具
    bool                senditem_use(uint64_t itemuid,uint8_t itemnum);
    bool                recvitem_use(MB_MsgBuffer* recvPacket);
    //剩余次數
    bool                senditem_use_info();
    bool                recvitem_use_info(MB_MsgBuffer* recvPacket);
    //出售道具
    bool                senditem_sell();
    bool                recvitem_sell(MB_MsgBuffer* recvPacket);
    
    int                 getRenameCardCount();
    
    //卸下裝備
    bool                senditem_down_equip(uint64_t petUID, uint8_t itemPos);
    bool                recvitem_down_equip(MB_MsgBuffer* recvPacket);
    //穿裝備,有其他裝備自動卸下
    bool                senditem_up_equip(uint64_t petUID, uint8_t itemPos, uint64_t itemUID, uint64_t oldPetUID = 0);
    bool                recvitem_up_equip(MB_MsgBuffer* recvPacket);
    //伺服器push消息
    bool                recvitem_new(MB_MsgBuffer* recvPacket);
    bool                recvitem_update(MB_MsgBuffer* recvPacket);
    //每日獎勵
    bool                senddaily_get_list();
    bool                recvdaily_get_list(MB_MsgBuffer* recvPacket);
    bool                senddaily_draw(uint8_t type);
    bool                recvdaily_draw(MB_MsgBuffer* recvPacket);
    
    void                recvitem_delete_notify(MB_MsgBuffer* recvPacket);
    
    void                send_role_login_reward();
    void                recv_role_login_reward(MB_MsgBuffer* pRecv);
    
    void                senditem_reinforce(uint64_t itemUid,uint64_t petID);
    void                recvitem_reinforce(MB_MsgBuffer* recvPacket);
    void                senditem_max_reinforce(uint64_t itemUid,uint64_t petID);
    void                recvitem_max_reinforce(MB_MsgBuffer* recvPacket);
    //裝備升品
    bool                recvitem_update_rank(MB_MsgBuffer* recvPacket);
    bool                senditem_up_rank(uint64_t srcUID, uint64_t foodUID, uint64_t srcPetID, uint64_t foodPetID);
    bool                recvitem_up_rank(MB_MsgBuffer* recvPacket);
    bool                senditem_compound(uint16_t typeID);
    bool                recvitem_compound(MB_MsgBuffer* recvPacket);
    
    //寶物吃寶物
    bool                senditem_eat(uint64_t itemid,CCArray *itemList);
    bool                recvitem_eat(MB_MsgBuffer* recvPacket);
    void                onMsgRecv(CCNode* node, SocketResponse* response);
    
    const char *        realName(char *buf, uint64_t UID);
    const char*         realNameByTypeID(char* buf, uint16_t typeID);
    
    sDesCommon*         getItemAttributeCommon(uint16_t/*eItem_Attribute_Type*/ type);
    sDesCommon*         getItemTypeCommon     (uint16_t/*ItemType*/ type);
    void                removeItemByUID  (uint64_t itemuid);
    void                removeItem  (uint64_t itemuid,uint8_t removenum = 1);
    void                removeItemByTypeID(uint16_t itemTypeID, uint8_t num = 1);
    uint16_t            getExpByRank(uint8_t rank, uint8_t star = 4);
    uint8_t             getRankByExp(uint16_t  exp, uint8_t star = 4);
//    bool                initExp();
    
    //通過TID獲取剩余次數（体力道具）返回-1表示沒找到
    int                 getUseItemLastTimesByTID(uint16_t tID);
    //通過TID獲取道具類型
//    Energy_ADD = 1,                 //体力道具
//    Discovery_ADD = 2,              //探索次數道具
//    PVP_ADD = 3,                    //爭霸次數道具
    uint8_t             getUseItemType(uint16_t tID);
    void                getUseItemTidByType(int type,std::vector<uint16_t>& vContainer);
    bool                setUseItemLastTimes(MB_UseItemRule* data);
    void                initUseItemLastTimes();
    
    std::vector<uint16_t>&  getEnhanceLevelList(void);
    uint64_t                getEnhanceItemUid  (void);
    //道具升品的相關函數
    CCArray*                getItemQualityCostArray() { return m_pItemQualityUpCost;}
    
    const std::vector<int>& getLoginRecordList()const;
    
    
    bool                CheckIsDebris(uint16_t type);//检查是否碎片
    
    void                initExpCardData();
    uint32_t            getExpByTid(uint16_t tid);
    
    void sc_item_more(MB_MsgBuffer* recvPacket);
private:
    void                    removeItemAfterSell();
    bool                    initQualityCost();

private:

    MB_ItemTemplateMap             m_mapItemTemplate;
//    ItemRankValueMap m_mapItemRankValueMap[14];
    CCArray*                    m_pItemDataArray;

    CCArray*                    m_pEquipArray;
    CCArray*                    m_pWeaponArray;
    CCArray*                    m_pDefenceArray;
    CCArray*                    m_pHorseArray;
    CCArray*                    m_pTreasureArray;
    CCArray*                    m_pMaterialArray;
    CCArray*                    m_pBoxArray;
    CCArray*                    m_pOtherArray;
    CCArray*                    m_pEquipUnionArray;
    CCArray*                    m_pPetUnionArray;
    CCArray*                    m_pCanEquipTreaArray;
    CCArray*                    m_pEatArray;
    CCArray*                    m_pWingArray;
    CCArray*                    m_pHeadwareArray;
    CCArray*                    m_pRuneStoreArray;
    CCArray*                    m_pTotermArray;
    CCArray*                    m_pItemFormulaArray;
    
    CCArray*                    m_pUseItemRuleArray;
    CCArray*                    m_pExpCardDataArray;
    CCArray*                    m_pItemDebrisArray;
    CCArray*                    m_pExpCardArray;
    std::vector<uint64_t>*      m_vecItemForSell;
    CCArray*                    m_pDailyRewardArray;
    std::vector<uint16_t>       m_enhanceItemList;
    uint64_t                    m_enhanceItemUID;
    CCArray*                    m_pItemQualityUpCost;
//    uint16_t                    m_ExpList[MAX_TREASURE_QUALITY];
//    uint16_t                    m_ExpList5s[MAX_TREASURE_QUALITY];
    uint32_t                    m_sellTotalPrice;
    
    bool                        initDailyRewardTemplete();
//    bool                        initLevelRewardTemplete();
    bool                        initTitleRewardTemplete();
 
    CCArray*                    m_pDailyRewardTemplete;
//    CCArray*                    m_pLevelRewardTemplete;
    CCArray*                    m_pTitleRewardTemplete;

    std::vector<int>            m_vLoginRecord;
    
};

#define  ItemMgr MB_ItemMgr::getInstance()
#endif /* defined(__ProjectMB__MB_MB_ItemData__) */
