
#ifndef ProjectMB_MB_ShopData_h
#define ProjectMB_MB_ShopData_h
#include "Game.h"
#include "MB_DateMgr.h"
#include "MB_CommonType.h"


class RewardTempleteValue;
enum kShopRewardType
{
    kShopRewardTypeCoin = 1,    // 1=> 银两
	kShopRewardTypeGold = 2,   // 2=> 元宝
	kShopRewardTypeReputation = 3, // 3=> 徽章
	kShopRewardTypeRoleExp = 4, // 4=> 冒险家经验
	kShopRewardTypePetExp = 5,  // 5=> 宠物经验
	kShopRewardTypeItem = 6,    // 6=> 道具
	kShopRewardTypePet = 7,     // 7=> 精灵
};


//商品奖励
class MB_ShopGoodsReward: public CCObject
{
    CC_SYNTHESIZE(uint8_t, m_uRewardType, RewardType);
    CC_SYNTHESIZE(uint32_t, m_uRewardValue, RewardValue);
    CC_SYNTHESIZE(int, m_nBuyNumOnce, BuyNumOnce);
    CC_SYNTHESIZE(int, m_nLevel, Level);
    CC_SYNTHESIZE(int, m_nRanking, Ranking);
};

class MB_ShopGoodsItem: public CCObject
{
public:
    
    MB_ShopGoodsItem();
    ~MB_ShopGoodsItem();
    
    CC_SYNTHESIZE(uint16_t, m_uGoodsID, GoodsID);   //商品ID
    CC_SYNTHESIZE(int, m_nBuyNum, BuyNum);          //可以购买的次数
    CC_SYNTHESIZE(int, m_nRealBuyNum, RealBuyNum);  //已买的次数
    CC_SYNTHESIZE(int, m_nPrice, Price);            //商品的价格
    CC_SYNTHESIZE(int, m_nStar, Star);              //星阶
    CC_SYNTHESIZE(uint8_t, m_uCoinType, CoinType);  //货币类型
    CC_SYNTHESIZE(int8_t, m_nVipLimit, VipLimit);
    
    void setIcon(const char* str) { m_strIcon = str;}
    void setDesc(const char* str) { m_strDesc = str;}
    void setName(const char* str) { m_strName = str;}
    const char* getIcon() { return m_strIcon.c_str();}
    const char* getDesc() { return m_strDesc.c_str();}
    const char* getName() { return m_strName.c_str();}
    CCArray* getRewardArray() { return m_pRewardArray;}

private:
    
    std::string         m_strIcon;          //图标
    std::string         m_strDesc;          //描述
    std::string         m_strName;          //名字
    CCArray*            m_pRewardArray;     //奖励表
    
};

class MB_ShopInfo: public CCObject
{
public:
    
    MB_ShopInfo();
    ~MB_ShopInfo();
    
    CC_SYNTHESIZE(int, m_nShopID, ShopID);//商店ID
    
    void setShopName(const char* name) { m_strShopName = name;}
    const char* getShopName() { return m_strShopName.c_str();}
    
    CCArray* getShopGoodsArray() { return m_pShopGoodsArray;}
    
private:

    std::string             m_strShopName;       //商店名字
    CCArray*                m_pShopGoodsArray;   //商店商品列表
};

//补天石商店 神秘商店（原）
#define MYSTERY_SHOP_ID (6666)  //神秘商店ID  服务器说写死

class MB_MysterShopInfo:public MB_ShopInfo
{
public:
    CC_SYNTHESIZE(uint32_t, m_nRefreshsec, Refreshsec);//商店刷新时间
};


class MB_ShopMgr: public CCObject
{
public:
    MB_ShopMgr();
    ~MB_ShopMgr();
    static MB_ShopMgr* getInstance();
    static void destroyInstance();
    
    void initShowCard();
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    //宝箱协议
    bool sendbox_item(uint16_t itemTypeID,uint8_t itemNum = 1);
    
    bool sendbox_shop(int32_t shopid, int8_t type);
    
    bool sendbox_shop_info();
    bool recvbox_shop_info(MB_MsgBuffer* recvPacket);
    
    bool sendbox_get_spirit_equip_count();
    bool recvbox_get_spirit_equip_count(MB_MsgBuffer* recvPacket);
    
    bool sendshop_buy_num();
    bool recvshop_buy_num(MB_MsgBuffer* recvPacket);
    
    bool sendshop_buy (uint16_t shopid,uint16_t sellID,uint8_t num,uint8_t cointype,int cost);
    bool recvshop_buy (MB_MsgBuffer* recvPacket);
    
    //神秘商店协议
    bool sendshop_encounter();                       //请求神秘商店信息
    bool recvshop_encounter(MB_MsgBuffer *recvPacket);
    
    bool sendshop_refresh();                         //刷新神秘商店
    bool recvshop_refresh(MB_MsgBuffer *recvPacket);
    bool recvshop_auto_refresh(MB_MsgBuffer *recvPacket);
    
    MB_ShopGoodsItem* getShopGoodsItemByID(uint16_t goodsID);
    MB_ShopGoodsItem* getShopGoodsItemInShop(uint16_t shopID, uint16_t goodsID);
    MB_ShopInfo* getShopInfoByID(uint16_t shopID);
    
    void updateShopGoodsRealNum(uint16_t shopID, uint16_t goodsID, int realNum = 1);
    bool shopGoodsCanBuy(uint16_t shopID, uint16_t goodsID);
    bool shopGoodsCanBuy(MB_ShopGoodsItem* pGoods);
    void autoAddShopGoodsRealNum(uint16_t shopID, uint16_t goodsID);
    
    
    CCArray* getShopBoxTemplete() { return m_pShopBoxTempleteArray;};
    CCArray* getShopGoodsTemplete() { return m_pShopGoodsTempleteArray;}
    CCArray* getShopDataTemplete() { return m_pShopDataTempleteArray;}
    int getShopCanBuyCount(int type);
    bool hasBall();
    bool hasStone();
    
    std::vector<uint16_t>& getShowCard(){return m_vShowCard;};
private:
    
    int m_uCurShopID;
    int m_uCurGoodsID;
    int m_uCurGoodsCount;
    int m_uCurCoinType;
    int m_uCurCost;
    
    CCArray* m_pShopBoxTempleteArray;           //召唤精灵、祈求装备
    CCArray* m_pShopGoodsTempleteArray;
    CCArray* m_pShopDataTempleteArray;
    
    CC_SYNTHESIZE(uint32_t,m_uPetCriticTime, PetCriticTime);
    std::vector<uint16_t> m_vShowCard;  //预览卡牌数据
    bool initShopGoods();
    bool initShopData();
};


class MB_ShopBoxTemplete: public CCObject
{
public:
    
    CC_SYNTHESIZE(uint16_t, m_uID, ID);
    CC_SYNTHESIZE(int, m_nCost1, Cost1);
    CC_SYNTHESIZE(int, m_nCost10, Cost10);
    
    CC_SYNTHESIZE(bool, m_OpenActivity,isOpenActivity);     //是否开启活动
    CC_SYNTHESIZE(int32_t, m_nDiscount, Discount);          //打折信息(1到100之间)
    CC_SYNTHESIZE(int32_t, m_nEndtime, Endtime);            //活动结束时间戳
    
    CC_SYNTHESIZE(int32_t, m_nNeedCallTimes, NeedCallTimes);//需要再抽m_nNeedCallTimes次
    CC_SYNTHESIZE(int32_t,m_nItemID,ItemID);                //道具召唤道具ID
    CC_SYNTHESIZE(int32_t,m_nItemCount,ItemCount);          //道具召唤道具数量
};


class MB_ShowCardConfig :  public  CCObject
{
    
};
#endif
