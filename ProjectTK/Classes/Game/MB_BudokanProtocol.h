//
//  MB_BudokanProtocol.h
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#ifndef __ProjectMB__MB_BudokanProtocol__
#define __ProjectMB__MB_BudokanProtocol__

#include "MB_ServerData.h"
#include "MB_ClientData.h"

//請求信息
#define CS_BUDUOKAN_INFO        11301
#define SC_BUDUOKAN_INFO        11302

// 請求購買加成
#define CS_BUDUOKAN_BUY         11303
#define SC_BUDUOKAN_BUY         11304

// 請求戰鬥
#define CS_BUDUOKAN_FIGHT       11305
#define SC_BUDUOKAN_FIGHT       11306

//一键扫塔
#define CS_BUDUOKAN_RAIDS       11307
#define SC_BUDUOKAN_RAIDS       11308


class MB_BudokanData :  public MB_ServerData
{
public:
    MB_BudokanData();
    virtual bool read(MB_MsgBuffer* pRecv);
    
    CC_SYNTHESIZE(uint16_t,m_nCurDungeonNum, CurDungeonNum);//當前是挑戰第几關
    CC_SYNTHESIZE(uint16_t,m_nAddAttack,AddAttack);//當前攻擊增加百分比
    CC_SYNTHESIZE(uint16_t,m_nAddHp,AddHp);//當前血量增加百分比
    CC_SYNTHESIZE(uint16_t,m_nDungeonID,DungeonID);//關卡ID
    CC_SYNTHESIZE(uint8_t,m_nChallengeTimes,ChallengeTimes);//生命值
    CC_SYNTHESIZE(uint8_t,m_bIsOpen,IsOpen);
    CC_SYNTHESIZE(uint32_t,m_bLastTime,LastTime);
    CC_SYNTHESIZE(uint8_t,m_nCoinBuyTimes, CoinBuyTimes);
    CC_SYNTHESIZE(uint8_t,m_nMoneyBuyTimes, MoneyBuyTimes);
    CC_SYNTHESIZE(uint16_t,m_nMaxDungeonNum, MaxDungeonNum);

};

class MB_BudokanChapterData : public MB_ClientData
{
public:    
    bool init(MB_XmlNode *pNode);
    CC_SYNTHESIZE(uint16_t,m_nChapterID,ChapterID);
    CC_SYNTHESIZE(uint16_t,m_nBoosID,BoosID);
    
    CC_SYNTHESIZE(uint16_t,m_nRewardID1,RewordID1);
    CC_SYNTHESIZE(uint16_t,m_nRewardNum1,Num1);
    CC_SYNTHESIZE(uint16_t,m_nRewardID2,RewordID2);
    CC_SYNTHESIZE(uint16_t,m_nRewardNum2,Num2);
    CC_SYNTHESIZE(uint16_t,m_nRewardID3,RewordID3);
    CC_SYNTHESIZE(uint16_t,m_nRewardNum3,Num3);
    CC_SYNTHESIZE(uint16_t,m_nRewardID4,RewordID4);
    CC_SYNTHESIZE(uint16_t,m_nRewardNum4,Num4);
};

class MB_BudokanConfig : public CCObject
{
public:
    MB_BudokanConfig();
    ~MB_BudokanConfig();
    virtual bool init(const char* pFile);
    
    CCArray* getBudokanArray(){return m_pBudokanConfig;};
    MB_BudokanChapterData* getChapterDataByID(uint16_t id);
private:
    CCArray* m_pBudokanConfig;
};
#endif /* defined(__ProjectMB__MB_BudokanProtocol__) */
