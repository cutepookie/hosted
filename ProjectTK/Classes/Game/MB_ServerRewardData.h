//
//  MB_ServerRewardData.h
//  ProjectPM
//
//  Created by WenYong on 14-4-3.
//
//

#ifndef __ProjectMB__MB_ServerRewardData__
#define __ProjectMB__MB_ServerRewardData__

#include "MB_ServerData.h"

class MB_ResWindow;
class RewardTempleteValue;
class MB_RewardView:public MB_ServerData
{
public:
    static void readRewardTemplateValue(RewardTempleteValue* pDest,MB_MsgBuffer* pBuff);
    static void showRewardMoreWithSerbuffer(MB_MsgBuffer* pRecv,MB_ResWindow* pParent);
    static void skipRepeatedSerbuffer(MB_MsgBuffer* pRecv);
};

/*
 message p_battle_progress[id=10216]{
 required	int8				type				=1;// 1:普通关卡   2:困难关卡  3:最困难关卡
 required	int16			dungeonID	=2;//关卡
 required	int16			chapterID	=3;//章节
 required	int16			dungeonCount	=4;//章节总关卡
 }
 */
class MB_ChapterProgress:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket);
private:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nType, Type);
    CC_SYNTHESIZE(uint16_t, m_nDungeonId, DungeonId);
    CC_SYNTHESIZE(uint16_t, m_nChapterId, ChapterId);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nDungeonCount, DungeonCount);
};

/*
 // 当个关卡信息的数据结构
 message	p_dungeon[id=10205]{
 required	int16		dungeonID		=1;//关卡唯一ID
 required	int16		restTimes		=2;//剩余挑战次数
 required	int8		bestScore		=3;//历史最佳通关评级：0=未通关，1..N=通关评级
 }
 */
class MB_DungeonInfo:public MB_ServerData
{
public:
    MB_DungeonInfo()
    {
        m_nDungeonID = 0;
        m_nRestTimes = 0;
        m_nBestScore = 0;
    }
    virtual bool read(MB_MsgBuffer* recvPacket);
private:
    CC_SYNTHESIZE(uint16_t, m_nDungeonID, DungeonID);
    CC_SYNTHESIZE(uint16_t, m_nRestTimes, RestTimes);
    CC_SYNTHESIZE(uint8_t, m_nBestScore, BestScore);
};

/*
 message recvbattle_info[id=10204]{
 required	int8		type			// 1:普通关卡   2:困难关卡  3:最困难关卡
 required	int16		chapterID		=1;//章节ID
 required	bool		perfectRewarded	=2;//是否领取过完美通关奖励
 repeated	p_dungeon	dungeonInfo		=3;//每个关卡的信息
 required	int16			dungeonCount	=4;//章节总关卡

 }
 */
class MB_BattleInfo:public MB_ServerData
{
public:
    MB_BattleInfo();
    ~MB_BattleInfo();
    virtual bool read(MB_MsgBuffer* recvPacket);
    CCArray* getDungeonInfoList();
    MB_DungeonInfo* queryDungeonInfoByDungeonId(uint16_t nDungeonId);
    void updateInfo(MB_MsgBuffer* recvPacket);
    int getBattleStar();
    void addDungeonInfo(MB_DungeonInfo* pInfo);
private:
    CC_SYNTHESIZE(uint8_t, m_nType, Type);
    CC_SYNTHESIZE(uint16_t, m_nChapterId, ChapterId);
    CC_SYNTHESIZE(uint8_t, m_bPerfect, Perfect);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTotalDungeon, TotalDungeon);
    CCArray*            m_pDungeonInfoList;
};

class MB_PetView : public MB_ServerData
{
public:
    MB_PetView();
    virtual bool read(MB_MsgBuffer* recvPacket);
private:
    CC_SYNTHESIZE_READONLY(uint16_t,m_nRank,Rank);     //精灵品阶
    CC_SYNTHESIZE_READONLY(uint16_t,m_nLevel,Level);   //精灵等级
    CC_SYNTHESIZE_READONLY(uint16_t,m_nTypeID,TypeID);  //精灵模版ID
};
#endif /* defined(__ProjectMB__MB_ServerRewardData__) */
