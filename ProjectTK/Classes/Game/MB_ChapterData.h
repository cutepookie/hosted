
//  章節会一開始初始化好,章節中的關卡需要每一次读取章節具体内容的時候才会触發初始化(由协议自動初始化)

#ifndef __ProjectMB__MB_ChapterData__
#define __ProjectMB__MB_ChapterData__

//#include "Game.h"
#include "MB_ClientData.h"
#include "MB_ServerData.h"
#include "MB_ResWindow.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
class MB_MsgBuffer;
//class MB_ChapterData: public CCObject
//{
//    
//private:
//    
//    std::string m_strName;
//    std::string m_strDescription;
//    std::string m_strIcon;
//    
//public:
//    MB_ChapterData();
//    virtual ~MB_ChapterData();
//    //base Info
//    CC_SYNTHESIZE( uint16_t, m_iID, ID)
//    CC_SYNTHESIZE( short, m_iNumber, Number)
//    CC_SYNTHESIZE( short, m_iDialog, Dialog)
//    CC_SYNTHESIZE( uint8_t,m_iType, Type)
//    const char * getName() { return m_strName.c_str();}
//    const char * getDescription() { return m_strDescription.c_str();}
//    const char * getIcon() { return m_strIcon.c_str();}
//    void  setIcon(const char *icon) { m_strIcon = icon;}
//    void  setName(const char *name) { m_strName = name;}
//    void  setDescription(const char *description) { m_strDescription = description;}
//    
//    //condition of active
//    CC_SYNTHESIZE( short,m_iNeedLevel ,NeedLevel)
//    CC_SYNTHESIZE( short, m_iNeedPass, NeedPass)
//    //levelData
//    CC_SYNTHESIZE( short,m_levels_length ,LevelLength)
//    //pass reword
//    CC_SYNTHESIZE(int, m_iCoin, Coin)
//    CC_SYNTHESIZE(int, m_iGoldBonus, GoldBonus)
//    CC_SYNTHESIZE(short, m_iReputation, Reputation)
//    CC_SYNTHESIZE(bool, m_bPerfectRewarded,PerfectRewarded)
//    CC_SYNTHESIZE(bool, m_bIsPerfectPass, IsPerfectPass)
//    CC_SYNTHESIZE(bool, m_bIsNicePass, IsNicePass);
//    //章節通關情况 0:未通關 1:已通關 2:正在通關中
//    CC_SYNTHESIZE(uint8_t, m_uIsPassed, IsPassed)
//    CC_SYNTHESIZE(int , m_iPos, Pos);    
//};
//class MB_ExplorerData: public MB_ChapterData
//{
//private:
//    
//    std::string m_strChapterCard;
//    
//public:
//    
//    MB_ExplorerData();
//    virtual  ~MB_ExplorerData();
//    CC_SYNTHESIZE(int ,  m_iCloseTime, CloseTime);
//    CC_SYNTHESIZE(int ,  m_iCollectEndTime, CollectEndTime);
//    CC_SYNTHESIZE(int , m_bChapterisgiveup, Chapterisgiveup);
//    CC_SYNTHESIZE(int , m_nChapterrate, Chapterrate);
//    CC_SYNTHESIZE(int , m_nCostType1, CostType1);
//    CC_SYNTHESIZE(int , m_nCostType2, CostType2);
//    CC_SYNTHESIZE(int , m_nCostType3, CostType3);
//    CC_SYNTHESIZE(uint8_t, m_nCollectType,CollectType);
//    CC_SYNTHESIZE(uint16_t, m_nCollectValue,CollectValue);
//    CC_SYNTHESIZE(int, m_nCollectNum,CollectNum);
//    CC_SYNTHESIZE(int , m_nShop, Shop);
//    CC_SYNTHESIZE(uint16_t , m_nItemID, ItemID);
//    CC_SYNTHESIZE(bool,m_bIsCollected, IsCollected);
//    void setChapterCard(const char *);
//    const char *getChapterCard();
//    const char *getUitKey(char *databuf);
//};
//
//class MB_ExplorerShopMB_ItemData:public CCObject{
//
//    public :
//    
//    MB_ExplorerShopMB_ItemData(){
//        
//        m_nBuyTimes = 0;
//    }
//    ~MB_ExplorerShopMB_ItemData(){
//    }
//    CC_SYNTHESIZE(uint16_t, m_nSellId, SellID);
//    CC_SYNTHESIZE(uint16_t, m_nBuyTimes, BuyTimes);
//  
//};
//class MB_ExplorerShop: public MB_ExplorerData
//{
//    private:
//    
//        CCArray *m_pShopItemList;
//    
//    public:
//    
//        CC_SYNTHESIZE(bool,m_nIsInit, IsInit);
//        MB_ExplorerShop(){
//            
//            m_nIsInit = false;
//            m_pShopItemList = NULL;
//        }
//        ~MB_ExplorerShop(){
//            
//            CC_SAFE_RELEASE(m_pShopItemList);
//        }
//        CCArray *getShopItems(){
//
//            return m_pShopItemList;
//        }
//        void setShopItems(CCArray *array){
//            
//            CC_SAFE_RELEASE(m_pShopItemList);
//            m_pShopItemList = array;
//            CC_SAFE_RETAIN(m_pShopItemList);
//        }
//    MB_ExplorerShopMB_ItemData * getItemByID(uint16_t itemId){
//        
//        CCObject * obj;
//        CCARRAY_FOREACH(m_pShopItemList, obj){
//        
//            if(((MB_ExplorerShopMB_ItemData *)obj)->getSellID() == itemId){
//            
//                return ((MB_ExplorerShopMB_ItemData *)obj);
//            }
//        }
//        return NULL;
//    }
//};
class MB_DungeonData :public CCObject{
    
private:
    
    std::string m_strName;
    std::string m_strBossList;
   
    
    public :
    
    MB_DungeonData();
    virtual ~MB_DungeonData();
    const char * getName() const{ return m_strName.c_str();}
    void setName(const char  *name) { m_strName = name;}
    const char * getBossList() const{ return m_strBossList.c_str();}
    void setBossList(const char  *BossList) { m_strBossList = BossList;}
    
    //base
    CC_SYNTHESIZE( uint16_t, m_iID, ID)
    CC_SYNTHESIZE( uint16_t, m_iNumber, Number)
    //0:未通關 1:险胜 2:大胜 3:完美
    CC_SYNTHESIZE( uint8_t,  m_iBestScore, BestScore)
    //active
    CC_SYNTHESIZE( uint16_t, m_iActiveNeedPass, ActiveNeedPass)
    //fightcost
    CC_SYNTHESIZE( uint16_t, m_iCostEnergy, CostEnergy)
    CC_SYNTHESIZE( uint16_t, m_iLeftTime, LeftTime)
    CC_SYNTHESIZE( uint16_t, m_iMaxTimes, MaxTimes);
    //monster position
    CC_SYNTHESIZE( uint16_t, m_iGeneral1, General1);
    CC_SYNTHESIZE( uint16_t, m_iGeneral2, General2);
    CC_SYNTHESIZE( uint16_t, m_iGeneral3, General3);
    CC_SYNTHESIZE( uint16_t, m_iGeneral4, General4);
    CC_SYNTHESIZE( uint16_t, m_iGeneral5, General5);
    CC_SYNTHESIZE( uint16_t, m_iGeneral6, General6);
    //reword
    CC_SYNTHESIZE( int, m_iCoin, Coin);
    CC_SYNTHESIZE( int, m_iExpRole, ExpRole);
    CC_SYNTHESIZE( int, m_iExpGeneral, ExpGeneral);
    CC_SYNTHESIZE( uint16_t, m_iDrop1, DropItem1);
    CC_SYNTHESIZE( uint16_t, m_iDrop2, DropItem2);
    CC_SYNTHESIZE( int, m_iAddMorale, AddMorale);
    CC_SYNTHESIZE( bool, m_bIsCanTouch, IsCanTouch);
    CC_SYNTHESIZE( int, m_iDungeon_icon,Dungeon_icon);
    CC_SYNTHESIZE(uint16_t,m_iDungeonLevel,DungeonLevel);
    
    
};
class MB_ExpDungeonData :public MB_DungeonData
{

    public :
    MB_ExpDungeonData();
    virtual ~MB_ExpDungeonData();
    CC_SYNTHESIZE(int8_t, m_nState, State);
};
//
//typedef std::map<uint16_t, CCArray*> DungeonMap;
//typedef std::pair<uint16_t, CCArray*> DungeonMapEntry;
//
//class MB_ChapterMgr:public CCObject
//{
//public:
//    
//    MB_ChapterMgr();
//    ~MB_ChapterMgr();
//    
//    /** Return the shared instance **/
//    static MB_ChapterMgr* getInstance();
//    /** Relase the shared instance **/
//    static void destroyInstance();
//    static void purgeData();
//    
//    CCArray *getChaperArray();
//    MB_ChapterData* getChapterDataByID(uint16_t chapterID);
//    uint16_t getNowDungeon();
//    uint16_t getNowChaper();
//    void setNowDungeon(uint16_t dungeon);
//    void setNowChaper(uint16_t Chaper);
//    CCArray* getDungeonArrayByChapterID(uint16_t chapterID);
//    
//    CCArray *getChaperArray2();
//    MB_ChapterData* getChapterDataByID2(uint16_t chapterID);
//    uint16_t getNowDungeon2();
//    uint16_t getNowChaper2();
//    void setNowDungeon2(uint16_t dungeon);
//    void setNowChaper2(uint16_t Chaper);
//    CCArray* getDungeonArrayByChapterID2(uint16_t chapterID);
//    
//    
//    bool sendbattle_progress();
//    bool recvbattle_progress(MB_MsgBuffer* recvPacket);
//    bool sendbattle_info(uint16_t chapterID,uint8_t type);
//    bool recvbattle_info(MB_MsgBuffer* recvPacket);
//    //    bool sendbattle_challenge(uint16_t dungeonID);
//    //    bool recvbattle_challenge(MB_MsgBuffer* recvPacket);
//    bool sendbattle_perfect_reward(uint16_t chapterID);
//    bool recvbattle_perfect_reward(MB_MsgBuffer* recvPacket);
//
//    void onMsgRecv(CCNode* node, SocketResponse* response);
//    
//private:
//    
//    CCArray *m_pChapterArray;
//    CCArray *m_pChapterArray2;
//    uint16_t m_nNowDungeon;
//    uint16_t m_nNowChapter;
//    uint16_t m_nNowDungeon2;
//    uint16_t m_nNowChapter2;
//    DungeonMap m_mapDungeonInfo;
//    DungeonMap m_mapDungeonInfo2;
//    CC_SYNTHESIZE( bool, m_bIssuccess, Issuccess);
//    uint8_t m_nNowBattleType;
//    bool initChapterTemplete();
//    bool initDungeonsByChapterID(uint16_t chapterID);
//    void initChapterPassStatus();
//
//    bool initChapterTemplete2();
//    bool initDungeonsByChapterID2(uint16_t chapterID);
//    void initChapterPassStatus2();
//};


class MB_EventHarm:public CCObject{
    
private:
    
    std::string m_strName;
    
    public :
    
    CC_SYNTHESIZE(uint64_t, m_pHarm,Harm);
    MB_EventHarm();
    ~MB_EventHarm();
    const char *getName();
    void setName(const char *name);
    
};
class MB_EventLastReport{
    
private:
    
    CCArray *m_pHuLaInfoList;
    CCArray *m_pLuckyRoleList;
    
public:
    
    MB_EventLastReport();
    ~MB_EventLastReport();
    CCArray *getHuaInfoList();
    CCArray *getLuckyRoleList();
    CC_SYNTHESIZE(short,m_nBossLevel,BossLevel);
    CC_SYNTHESIZE(int, m_nInterValSec, InterValSec);
    CC_SYNTHESIZE(uint64_t, m_nBossMaxHp, BossMaxHp);
    
};
class  MB_EventData :public CCObject{
    
private:
    
    std::string m_strEventName;
    CCArray *m_pHarmList;
    MB_EventLastReport *m_pEventLastReport;
    
    public :
    
    MB_EventData(){
        
        m_pHarmList = new CCArray();
        m_nCurSavedInfoId = 0;
        m_nBeginTime = 0;
        m_nBuffNumYuanJun = 0;
        m_pEventLastReport = new MB_EventLastReport();
    }
    ~MB_EventData(){
        
        m_pHarmList->removeAllObjects();
        CC_SAFE_DELETE(m_pHarmList);
        delete  m_pEventLastReport;
    }
    bool getIsOfflinePlay()const{return m_nIsOfflinePlay;}
    void setIsOfflinePlay(bool bOfflinePlay)
    {
        if (bOfflinePlay)
        {
            setBuffNumYuanJun(100);
        }
        else
        {
            setBuffNumYuanJun(0);
        }
        m_nIsOfflinePlay = bOfflinePlay;
    }
    const char *getEventName();
    void setEventName(const char *eventName);
    CCArray *getHarmList();
    MB_EventLastReport *getEventLastReport();
    void loadRank();
    void saveRank();
    CC_SYNTHESIZE(uint8_t, m_nEventId,EventID);
    CC_SYNTHESIZE(bool, m_nIsOpen, IsOpen);
    bool        m_nIsOfflinePlay;
    CC_SYNTHESIZE(uint64_t, m_nMaxHp, MaxHp);
    CC_SYNTHESIZE(uint16_t, m_nBossLevel, bossLevel);
    CC_SYNTHESIZE(bool, m_nIsBuffed, IsBuffed);
    CC_SYNTHESIZE(uint16_t, m_nBuffNum, BuffNum);
    CC_SYNTHESIZE(uint16_t, m_nBuffNumYuanJun, BuffNumYuanJun);
    CC_SYNTHESIZE(uint64_t, m_nCurHp, CurHp);
    CC_SYNTHESIZE(uint64_t, m_mCurHarm, CurHarm);
    CC_SYNTHESIZE(uint16_t, m_nCurRank,CurRank);
    CC_SYNTHESIZE(int, m_nRebornTime,RebornTime);
    CC_SYNTHESIZE(int, m_nCurSavedInfoId, CurSaveInfoID);
    CC_SYNTHESIZE(int , m_nBeginTime,BeginTime );
    void loadLastReport(xmlNodePtr curNode);
    
};
class MB_EventRole :public CCObject{
 
private:
    
    std::string m_strUserName;
    
public:
    
    MB_EventRole(){
    }
    ~MB_EventRole(){
    }
    void setUserName(const char *username){
        
        m_strUserName = username;
    }
    const char * getUserName(){
        
        return m_strUserName.c_str();
    }
    CC_SYNTHESIZE(uint16_t, m_nSore,Sore);
    CC_SYNTHESIZE(int, m_nRoleID, RoleID);
    
};
class MB_EventMgr :public CCObject{
    
    private :
    
    static MB_EventMgr* m_pSharedEventMgr;
    CCArray *m_pEvenList;
    
    public :
    
    MB_EventMgr();
    ~MB_EventMgr();
    static MB_EventMgr *getInstence();
    static void destroyInstance();
    CC_SYNTHESIZE(bool,m_pIsRocketTeamOnline,IsRocketTeamOnLine);
    CC_SYNTHESIZE(bool,m_pIsNanMOnline,IsNanMOnLine);
    CC_SYNTHESIZE(uint8_t, m_nHRClickIndex, HRClickIndex);
    CCArray *getEvenlist();
    
    bool sendworldboss_open();
    bool recvworldboss_open(MB_MsgBuffer* recvPacket);
    bool recvworldboss_init_state(MB_MsgBuffer* recvPacket);
    bool sendworldboss_close();
    bool sendworldboss_buff(int times);
    bool recvworldboss_buff(MB_MsgBuffer* recvPacket);
    bool sendworldboss_last_info();
    bool recvworldboss_last_info_ignore(MB_MsgBuffer* recvPacket);
    bool recvworldboss_last_info_win(MB_MsgBuffer* recvPacket);
    bool recvworldboss_last_info_fail(MB_MsgBuffer* recvPacket);
    bool sendworldboss_cur_info();
    bool recvworldboss_cur_info_ignore(MB_MsgBuffer* recvPacket);
    bool recvworldboss_cur_info(MB_MsgBuffer* recvPacket);
    bool recvworldboss_hp_sync(MB_MsgBuffer* recvPacket);
    bool recvworldboss_harm_broadcast(MB_MsgBuffer* recvPacket);
    bool recvworldboss_rank_sync(MB_MsgBuffer* recvPacket);
    bool recvworldboss_buff_sync(MB_MsgBuffer* recvPacket);
    bool sendworldboss_fight();
    bool recvworldboss_fight(MB_MsgBuffer* recvPacket);
    bool sendworldboss_reborn();
    bool recvworldboss_reborn(MB_MsgBuffer *recvPacket);
    bool sendworldboss_offline_play();
    bool recvworldboss_offline_play(MB_MsgBuffer *recvPacket);
    bool sendworldboss_open_time();
    bool recvworldboss_open_time(MB_MsgBuffer *recvPacket);
    
    
//    bool recvhron_open_m_pDungeonList *recvPacket);
    void saveEvent();
    
    
    
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
};



class MB_RewardData:public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTypeId, TypeId);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType, Type);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nValue, Value);
};

class MB_ChapterData:public MB_ClientData
{
public:
    MB_ChapterData();
    ~MB_ChapterData();
    virtual bool init(MB_XmlNode* pNode);
    CCArray* getRewardArray()const;
private:
    CC_SYNTHESIZE_READONLY(int, m_nChapterId, ChapterId);
    CC_SYNTHESIZE_READONLY(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY(std::string, m_szDescription, Description);
    CC_SYNTHESIZE_READONLY(std::string, m_szActovateIcon, ActovateIcon);
    CC_SYNTHESIZE_READONLY(std::string, m_szDisableIcon, DisableIcon);
    
    CC_SYNTHESIZE_READONLY(uint32_t, m_nNeedLevel, NeedLevel);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nNeedPass, NeedPass);
    CC_SYNTHESIZE_READONLY(CCPoint, m_location, Location);
    CCArray*        m_pRewardArray;
};


class MB_ChapterPage:public MB_ClientData
{
public:
    void loadResource2SpriteCache();
    void removeResourceFromSpriteCache();
    MB_ChapterPage();
    ~MB_ChapterPage();
    virtual bool init(MB_XmlNode* pNode);
    bool queryChapterById(int nChapterId,MB_ChapterData** pData);
    const char* getChapterName(uint16_t nChapterID);
    CCArray* getChapterArray()const{return m_pChapterArray;}
    bool hasChapter(int nChapterId);
private:
    CC_SYNTHESIZE_READONLY(int, m_nId, PageId);
    CC_SYNTHESIZE_READONLY(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY(std::string, m_szDescription, Description);
    CC_SYNTHESIZE_READONLY(std::string, m_szBackground, Background);
    CC_SYNTHESIZE_READONLY(std::string, m_szBattleBg, BattleBg);
    CC_SYNTHESIZE_READONLY(std::string, m_szResource, Resource);
    CCArray*        m_pChapterArray;
};

class MB_ChapterPageList:public MB_ClientData
{
public:
    MB_ChapterPageList();
    ~MB_ChapterPageList();
    virtual bool init(MB_XmlNode* pNode);
    bool queryPageById(int nPageId,MB_ChapterPage** pPage);
    bool queryPageByChapterId(int nChapterId,MB_ChapterPage** pPage);
    bool queryChapterByID(int nChapterId,MB_ChapterData** pData);
private:
    CCArray*    m_pPageList;
};



class MB_ChapterRankData:public MB_ServerData
{
public:
    MB_ChapterRankData();
    virtual bool read(MB_MsgBuffer* recvPacket);
private:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nRank,Rank);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nRoleID, RoleID);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLv, Lv);
    CC_SYNTHESIZE_READONLY(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nHead, Head);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nTitle, Title);
    CC_SYNTHESIZE_READONLY(bool, m_bIsMale, IsMale);
    CC_SYNTHESIZE_READONLY(std::string, m_szDungeonName, DungeonName);
    
};

#endif /* defined(__ProjectMB__MB_ChapterData__) */
