
#ifndef ProjectMB_MB_CommonType_h
#define ProjectMB_MB_CommonType_h
#include "cocos2d.h"
#include "MB_LocalProto.h"
#include "ParamListParser.h"
//道具品階
enum kmItemQuality
{
    kmItemQuality_Default = 0,
    kmItemQuality_Level1,
    kmItemQuality_Level2,
    kmItemQuality_Level3,
};

//背景音乐
enum  kmBackGround
{
    kmBackGround_Normal = 0,                //"正常背景音mp3"
    kmBackGround_Combat,                    //"戰鬥背景音mp3"
    kmBackGround_CombatWin,                 //"勝利背景音mp3"
    kmBackGround_CombatLose,                //"失敗背景音mp3"
    kmBackGround_Default_Effect_Sound,      //"按钮默认特效音wav"
    kmBackGround_GetOnePet,                 //"点將音效mp3"
    kmBackGround_GetTenPet,                 //"十連抽音效mp3"
    kmBackGround_Login,                     //"登入画面mp3"
    kmBackGround_Battle_Boss,               //"BOSS戰鬥背景音乐MP3（戰役最后一關）"
    ksSound_Card_Level_Up,                  //"精靈升級時的音乐"
    ksSound_Card_Rank_Up,                   //"精靈進化時的音乐"
    ksSound_Equip_Level_Up,                 //"裝備强化時的音乐"
    ksSound_Equip_Rank_Up,                  //"裝備精煉時的音乐"
    ksSound_Star_Up,                        //"合成時的音乐"
    ksSound_AchievementComplate,            //"完成成就的音乐"
    ksSound_ZhuanSheng,                     //精靈轉生音效：15
    ksSound_RunningCool,                    //跑酷背景音效：16
    ksSound_Reward = 17,    //獲得物品音效
    ksSound_GetCard = 18,   //抽卡獲得精靈音效
    ksSound_Star = 19,   //结算星星音效
    ksSound_MyRoom = 20,   //我的房间Bgm
    ksSound_Shop = 21,   //商城Bgm
    ksSound_CallCard = 22,   //召唤Bgm
    ksSound_YeShiJie = 23,   //夜世界Bgm
    ksSound_Xuanguan = 24,   //选关Bgm
    ksSound_PvpAndPaiHang = 25,   //PVP和排行榜Bgm
    ksSound_ShiLian = 26,   //试炼Bgm
    ksSound_WenQuan = 27,   //温泉Bgm
    ksSound_ShiLianInner = 28,   //试炼内Bgm
    ksSound_JieSuan = 29,   //结算Bgm
    ksSound_3Star = 30,   //抽卡3星以下音效
    ksSound_4Star = 31,   //抽卡4星以上音效
};

//物品裝備信息
struct sBeEquip
{
    uint8_t     goodsPos;
    uint64_t    petId;
    int         itemType;
};

//货幣類型
enum kmCurrency_Type
{
    kmCurrency_Type_Ingots = 1, //钻石
    kmCurrency_Type_silver,     //金幣
    kmCurrency_Type_prestige,   //徽章
    kmCurrency_Type_points,     //积分
    kmCurrency_Type_reserve1,   
    kmCurrency_Type_reserved2,
    kmCurrency_Type_num
};


//商品獎勵類型
enum kmRewardType
{
    kmRewardType_General = 0,//精靈
    kmRewardType_Item,      //道具
    kmRewardType_Gold,      //金幣
    kmRewardType_Silver,    //金幣
    kmRewardType_Exp        //經驗
};

//商店購買結果
enum kmShopBuy_Result
{
    kmShopBuy_Result_Success = 1,       //成功
    kmShopBuy_Result_NoIngots,          // 2=> 钻石不足
    kmShopBuy_Result_NoSilver,          // 3=> 银两不足
    kmShopBuy_Result_NoPrestige,        //徽章不足
    kmShopBuy_Result_NoPoints,          //积分不足
    kmShopBuy_Result_NoCurrency,        //其他货幣不足
    kmShopBuy_Result_NoVip,             //vip等級不足
    kmShopBuy_Result_BeyondMaxBuyying,  //購買次數超過上限
    kmShopBuy_Result_NoSpecialShop      //您不拥有此奇遇商店
};

//商品獎勵
struct sShopGoodsReward
{
    kmRewardType rewardtype;
    uint32_t     rewardvalue;
    int          buyNumOnce;
    int          level;
    int          ranking;
};

typedef std::vector<sShopGoodsReward>   shopGoodsRewardVec;
typedef shopGoodsRewardVec::iterator    shopGoodsRewardVec_It;

//商店商品项
struct sShopGoodsItem
{
    uint32_t            goodsID;        //商品ID
    std::string         icon;           //图标
    std::string         description;    //描述
    std::string         name;           //名字
    int                 buyNum;         //可以購買的次數
    int                 reallyBuyNum;   //已買的次數
    int                 Price;          //商品的价格
    int                 Star;           //星階
    kmCurrency_Type     currencyType;   //货幣類型
    shopGoodsRewardVec  vecShopGoodsReward;//獎勵表
};

typedef std::map<uint32_t,sShopGoodsItem>   GoodsInfoMap;
typedef GoodsInfoMap::iterator              GoodsInfoMap_It;

struct sShopInformation
{
    int                     shopID;         //商店ID
    std::string             shopName;       //商店名字
    GoodsInfoMap            mapShopGoods;   //商店商品列表
};

//锁定的商品
struct sLockedShopGoods
{
    void clear(){shopId = 0;goodsId = 0;}
    void operator()(int sid,int iid){shopId = sid;goodsId = iid;}
    int         shopId;     //商店id
    int         goodsId;    //商品id
};

//商店主頁面分頁
enum kmShopPage
{
    kmShopPage_CallGeneral = 0,//召喚
    kmShopPage_Ingots,         //钻石
    kmShopPage_Points,         //积分
    kmShopPage_Pay,            //儲值付费
    kmShopPage_Box,             //寶箱
    kmShopPage_Num
};

//合成需要的材料种類數量
const int ComposeMaterialNumber = 5;

//合成狀態
enum kmComposeState
{
    kmComposeState_UnCompose = 0,   //未合成
    kmComposeState_Composing,       //合成中
    kmComposeState_Composed,        //合成完成可以領取
    kmComposeState_breakOff,        //合成中断
    kmComposeState_Ready ,          //材料足够，可以合成
    kmComposeState_None,            //無效。
};

//合成單元信息
struct sComposeUnit
{
    int             materialNum;        //材料數量
    unsigned int    materialItemId;     //材料id（道具）
};

//合成信息
struct sComposeInformation
{
    void clear()
    {
        memset(this,0,sizeof(sComposeInformation));
        composeState = kmComposeState_UnCompose;
    }
    sComposeInformation ()
    {
        clear();
    }
    kmComposeState  composeState;                      //當前合成狀態
    //unsigned int    composeTime;                       //合成時間
    unsigned int    composeEndTime;                    //合成結束時間
    unsigned int    composeID;                         //合成ID
    sComposeUnit    composeUnit[ComposeMaterialNumber];//合成單元
    unsigned int    generateItemID;                    //生成道具ID
};

typedef std::map<unsigned int, sComposeInformation> ComposeMap;
typedef ComposeMap::iterator                        ComposeMap_It;

//玩家信息
struct sRoleInformation
{
    uint32_t		roleID;//玩家ID
	bool			isMale;//是否是男性
	uint16_t		level;//等級
    std::string		roleName;//玩家名字
	uint8_t			title;//官爵
	uint64_t		fightPower;//总戰鬥力
    uint32_t        cannotFightEndTime;//是否免戰
};

typedef std::vector<sRoleInformation>  RoleGather;


///
/// 1.2.1 修正玩家信息,此处做兼容代碼处理
/* 夺寶目标信息
message		p_plunder_target[id=10922]{
	required	int32			roleID				=1;//玩家ID
	required	bool			isMale				=2;//是否是男性
	required	int16			level				=3;//等級
	required	string			roleName			=4;//玩家名字
	required	int8			title				=5;//官爵
	required	int64			fightPower			=6;//总戰鬥力
	required	int32			freeEndTime			=7;//免戰結束時間，0=非免戰狀態
	required	int16			itemTypeID			=8;//玩家拥有的碎片ID
}*/
struct sRoleInformation121
{
    uint32_t			roleID;//玩家ID
	bool                isMale;//是否是男性
	uint16_t			level;//等級
    std::string			roleName;//玩家名字
	uint8_t             title;//官爵
	uint64_t			fightPower;//总戰鬥力
	uint32_t			freeEndTime;//免戰結束時間，0=非免戰狀態
	uint16_t			itemTypeID;//玩家拥有的碎片ID
};
typedef std::vector<sRoleInformation121> RoleGather121;
///
//寶物爭夺結果
struct sTreasureRobResult
{
    sTreasureRobResult()
    {
        isSuccess = false;
        roleName  = "";
        itemID    = 0;
        needItemID= 0;
    }
    bool        isSuccess;  //是否成功
    std::string roleName;   //對方角色名字
    uint32_t    itemID;     //实际獲得的道具ID
    uint32_t    needItemID; //需要的道具id
};

//召喚卡牌信息
enum kmCardType
{
    kmCardType_General = 1, //精靈
    kmCardType_Item ,    //道具
    kmCardType_Gold, //钻石
    kmCardType_Silver, //银两
    kmCardType_Repute, //徽章
    
};

class sCallGeneralCard :public cocos2d::CCObject
{
public:
    
    sCallGeneralCard(){
    
        m_nIsTaked = false;
        m_nID = 0;
        m_nPos = 0;
        m_nNum = 0;
    }
    ~sCallGeneralCard(){
    
    }
  	CC_SYNTHESIZE(kmCardType,m_nType,Type);   //卡牌類型
    CC_SYNTHESIZE(uint32_t ,  m_nID,ID)     //模板ID
    CC_SYNTHESIZE(uint32_t ,  m_nNum,Num);    //數量
    CC_SYNTHESIZE(uint8_t  ,  m_nPos,Pos);    //记录上次被翻出来時，卡片所在的位置,位置定义由客户端自行决定
    CC_SYNTHESIZE(bool     ,  m_nIsTaked,IsTaked);//是否被獲取
};

struct sCallGeneralCost
{
    uint32_t   itemID;
    uint32_t   itemCost;
    uint32_t   backItemID;
    uint32_t   backItemRatio;
};

//召喚狀態
enum kmCallGeneral_State
{
    kmCallGeneral_State_FirstReady = 0,         //第一次准备
    kmCallGeneral_State_FirstCallGeneral,   //第一次召喚
    kmCallGeneral_State_Ready,              //准备
    kmCallGeneral_State_CallGeneral,        //召喚
    kmCallGeneral_State_CallGeneralOver     //召喚結束
    
};

const int Max_CallGeneralCard_Count = 6;


//公告
struct sNoticeInfo
{
    uint32_t    identity;
    std::string notice;
};

typedef std::map<uint32_t,sNoticeInfo> NoticeMap;
typedef NoticeMap::iterator            NoticeMap_It;


//信件
//獎勵
enum kmMailType
{
    kmMailType_None = 0,
    kmMailType_SystemHint,          //系統提示消息信件
    kmMailType_SystemReward,        //系統獎勵信件
    kmMailType_SystemAppendFriend,  //系統好友添加提示
    kmMailType_SystemJoinUnion,     //系統加盟提示
    kmMailType_PresonMail,          //个人信件
    kmMailType_UnionMail,           //联盟信件
    kmMailType_Pvp,                 //精靈榜戰報
    kmMailType_TreasureRob,         //夺寶戰報
};

enum kmMailsTable
{
    kmMailsTable_System = 1,                    //系統
    kmMailsTable_Preson,                        //个人
    kmMailsTable_Union,                         //联盟列表
    kmMailsTable_Pvp,                           //pvp
    kmMailsTable_RuleFight,                   //秩序戰场戰報
    kmMailsTable_Num = kmMailsTable_RuleFight //个數
};

typedef std::map<uint32_t/*ItemID or PetID*/, uint32_t/*ItemNum or PetNum*/> KeyValue_Map;
typedef KeyValue_Map::iterator KeyValue_It;

struct sMailReward
{
    KeyValue_Map    ItemRewards;
    KeyValue_Map    PetRewards;
};

//信件單元
#define hisType_IsSbAttack(v)       ((bool)((v>>7)&0x01))
#define hisType_IsWin(v)            ((bool)((v>>6)&0x01))
#define hisType_IsRobSuccess(v)     ((bool)((v>>5)&0x01))

struct sMailCell
{
    uint64_t            mailUID;        //信件唯一ID
    kmMailType          mailType;       //信件類型
	uint32_t            senderID;       //信件發送者的UID，0=系統發送的
    std::string         senderName;     //發送者名字,如果本信件是系統信件，则此字段為空
    std::string         content;        //内容
	uint32_t            time;           //發送時間(Unix時間戳)
	uint16_t            mailTemplateID; //信件模版ID
    ParamListParser     paramList;      //動态類型參數列表
	sMailReward         mailReward;     //可領取獎勵
    uint8_t             hisType;        //戰報類型
    uint16_t            arg;            //戰報附带參數
    uint32_t            addRepu;        //得到声望
    void clear()
    {
        mailUID         = 0;
        mailType        = kmMailType_None;
        senderID        = 0;
        senderName      = "";
        content         = "";
        time            = 0;
        mailTemplateID  = 0;
        hisType         = 0;
        arg             = 0;
        addRepu         = 0;
        mailReward.ItemRewards.clear();
        mailReward.PetRewards.clear();
    }
};

//新信件結构
struct sNewMail
{
    std::string content;
    int32_t     targetID;
    std::string targetName;
};

#endif
