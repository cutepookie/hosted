//
//  MB_RefreshShopProtocol.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-5.
//
//

#ifndef __ProjectMB__MB_RefreshShopProtocol__
#define __ProjectMB__MB_RefreshShopProtocol__

#include "MB_ServerData.h"
#include "MB_ClientSocket.h"
#include <string>

#define CS_SHOP_TREASURE_INFO 10731
#define SC_SHOP_TREASURE_INFO 10732
#define CS_SHOP_TREASURE_BUY 10734
#define SC_SHOP_TREASURE_BUY 10735
#define SC_SHOP_TREASURE_NEW_ACTIVITY 10736
#define SC_SHOP_TREASURE_NEW_SHOP 10737
#define CS_SHOP_REFRESH2 10738
#define SC_SHOP_REFRESH2 10739
/**
 required        int8                type                    = 1;//类型 1：物品 2：卡牌
 required        int16               typeID                  = 2;//模板ID
 required        int32               num                     = 3;//数量
 required        int8                costType                = 4;//单价消耗类型 1：金币 2：钻石 3：声望
 required        int32               costVal                 = 5;//单价消耗数量
 required        bool                isBuy                   = 6;//是否购买过
 **/

class MB_Treasure:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket);
private:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nType, Type);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTID, TID);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nNum, Num);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nCostType, CostType);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nCostVal, CostVal);
    CC_SYNTHESIZE(bool, m_isBuy, IsBuy);
    CC_SYNTHESIZE_READONLY(int16_t, m_nIndex, Index);
};

class MB_TreasureInfo:public MB_ServerData
{
public:
    MB_TreasureInfo();
    ~MB_TreasureInfo();
    virtual bool read(MB_MsgBuffer* recvPacket);
    virtual bool read_refresh_goods(MB_MsgBuffer* recvPacket);
    virtual bool read_refresh_goods2(MB_MsgBuffer* recvPacket);
    virtual bool read_new_activity(MB_MsgBuffer* recvPacket);
    
    MB_Treasure* queryFunctionByIndex(uint16_t);
private:
    CC_SYNTHESIZE_READONLY(std::string, m_activityName, ActivityName);
    CC_SYNTHESIZE_READONLY(uint32_t, m_ActivityEndTime, ActivityEndTime);
    CC_SYNTHESIZE_READONLY(uint8_t, m_Mul, Mul);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nDiscounts, Discounts);
    CC_SYNTHESIZE_READONLY(uint32_t, m_NextRefreshTime, NextRefreshTime);
    CC_SYNTHESIZE_READONLY(CCArray*,m_Treasures,Treasures);
};

#endif /* defined(__ProjectMB__MB_RefreshShopProtocol__) */
