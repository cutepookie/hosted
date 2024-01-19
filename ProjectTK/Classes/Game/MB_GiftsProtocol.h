//
//  MB_GiftsProtocol.h
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#ifndef __ProjectMB__MB_GiftsProtocol__
#define __ProjectMB__MB_GiftsProtocol__

#include "MB_ServerData.h"
#include "MB_ClientData.h"
#include "MB_LocalProto.h"
#include "MB_ItemData.h"
#define CS_DAILY_REWARD_LIST 11007
#define SC_DAILY_REWARD_LIST 11008
#define CS_DAILY_REWARD_GET 11011
#define SC_DAILY_REWARD_GET 11012


enum EGiftType
{
    //1在线時長禮包，2等級禮包，3連续登入禮包
    eGiftNone = 0,
    eGiftTime = 1,
    eGiftLevel = 2,
    eGiftMLogin = 3,
};

//message	p_id_num[id=11403]{
//    required		int16		typeID			=1;//類型ID
//    required		int32		num				=2;//數量
//}
class MB_ID_NUM:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* pRecv);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTypeID, TypeID);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nNum, Num);
};

//message	p_mail_reward[id=11404]{
//    repeated		p_id_num	itemList		=1;//道具列表
//    repeated		p_id_num	gerList			=2;//武將列表
//}
class MB_MailReward:public MB_ServerData
{
public:
    MB_MailReward();
    ~MB_MailReward();
    virtual bool read(MB_MsgBuffer* pRecv);
    CCArray* converIDNUM2RewardTempleteValue();
private:
    CC_SYNTHESIZE_READONLY(CCArray* ,m_pItemList,ItemList);//MB_ID_NUM
    CC_SYNTHESIZE_READONLY(CCArray* ,m_pPetList,PetList);//MB_ID_NUM
};

//message p_daily_reward[id=11010]{
//    required        int32           needValue       =1;//需要条件，type=1，在线累計分钟數，type=2，當前等級，type=3，累計連续登入天數
//    required        bool            isGet           =2;//是否領取
//    required        p_mail_reward   reward          =3;//獎勵展示
//}
class MB_DailyRewrd:public MB_ServerData
{
    friend class MB_DailyRewrdInfo;
public:
    MB_DailyRewrd();
    ~MB_DailyRewrd();
    virtual bool read(MB_MsgBuffer* pRecv);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nNeedValue, NeedValue);
    CC_SYNTHESIZE(bool, m_bIsGet, IsGet);
    CC_SYNTHESIZE_READONLY(MB_MailReward*, m_pMailRewards, MailRewards);
    
    CC_SYNTHESIZE_READONLY(uint8_t, m_nType, Type);
    CC_SYNTHESIZE(uint32_t, m_nNowValue, NowValue);
public:
    uint32_t getEnable();
};

//message p_daily_reward_info[id=11009]{
//    required        int8            type            =1;//1在线時長禮包，2等級禮包，3連续登入禮包
//    required        int32           nowValue        =2;//當前所在數值，type=1，在线累計分钟數，type=2，當前等級，type=3，累計連续登入天數
//    repeated        p_daily_reward  list            =3;//獎勵列表
//}
class MB_DailyRewrdInfo:public MB_ServerData
{
public:
    MB_DailyRewrdInfo();
    ~MB_DailyRewrdInfo();
    virtual bool read(MB_MsgBuffer* pRecv);
    CC_SYNTHESIZE(uint8_t, m_nType, Type);
    CC_SYNTHESIZE(uint32_t, m_nNowValue, NowValue);
    CC_SYNTHESIZE(CCArray*, m_pDailyRewards, Info);
    
    MB_DailyRewrd* getRewardByNeedValue(int needValue);
    int getEnableCount();
    int getUnGetCount();
};





#endif