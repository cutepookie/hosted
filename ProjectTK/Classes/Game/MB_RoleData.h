

#ifndef __ProjectMB__MB_RoleData__
#define __ProjectMB__MB_RoleData__

#include "Game.h"
#include "MB_CommonType.h"

USING_NS_CC;

class MB_RoleData :public CCObject
{
private:
    std::string m_sName ;
    std::string m_sDescription;
    CCArray *m_pVipConig;
    CCArray* m_pPayArray;
    CCArray* m_pFirstPayArray;
    std::string m_sFirstPayDesc;
    std::string m_sWhoInviteYou;
    uint8_t  m_nSetting[9];
    uint16_t m_nSttingLength;
    bool initPayTemplete();
    bool initFirstPayTemplete();

public:
    
    MB_RoleData();
    ~MB_RoleData();
    //use in android
    static bool IsCheckSetRoleData ;
    
    /** Return the shared instance **/
    static MB_RoleData *getInstance();
    
    /** Relase the shared instance **/
    static void destroyInstance();
    
    //冒險家协议
    bool sendrole_info();
    bool sendrole_buy_energy(uint8_t type);
//    bool sendexplore_free();
    bool sendrole_push_setting(uint8_t type, uint16_t data);
    bool recvrole_push_setting(MB_MsgBuffer *recvPacket);
    bool recvexplore_free(MB_MsgBuffer *recvPacket);
    bool sendrole_token(const char *token);
    bool recvrole_token(MB_MsgBuffer *recvPacket);
    bool recvrole_info(MB_MsgBuffer *recvPacket);
    bool recvrole_buy_energy(MB_MsgBuffer *recvPacket);
    bool recvrole_update_list(MB_MsgBuffer *recvPacket);
    bool recvrole_update_level(MB_MsgBuffer *recvPacket);
    bool recvrole_update_exp(MB_MsgBuffer *recvPacket);
    bool recvrole_update_coin(MB_MsgBuffer *recvPacket);
    bool recvrole_update_reputation(MB_MsgBuffer *recvPacket);
    bool recvrole_update_gold(MB_MsgBuffer *recvPacket);
    bool recvrole_update_goldbonus(MB_MsgBuffer *recvPacket);
    bool recvrole_update_viplevel(MB_MsgBuffer *recvPacket);
    bool recvrole_update_energy(MB_MsgBuffer *recvPacket);
    bool recvrole_update_discoverytimes(MB_MsgBuffer *recvPacket);
    bool recvrole_update_pvptimes(MB_MsgBuffer *recvPacket);
    bool recvrole_update_plundertimes(MB_MsgBuffer *recvPacket);
    bool recvrole_update_randompvptimes(MB_MsgBuffer *recvPacket);
    bool recvrole_update_singlepvptimes(MB_MsgBuffer *recvPacket);
    bool recvrole_update_title(MB_MsgBuffer *recvPacket);
    bool recvrole_base_config(MB_MsgBuffer *recvPacket);
    bool recvrole_update_encounterFreeNum(MB_MsgBuffer *recvPacket);
    bool recvrole_update_weibocount(MB_MsgBuffer *recvPacket);
    bool sendrole_setting();
    bool recvrole_setting(MB_MsgBuffer *recvPacket);
    bool sendrole_challengegod_info();
    bool recvrole_update_challengegodtimes(MB_MsgBuffer *recePacket);
    //付费协议
    bool sendrole_pay_91(const char *receipt,int payID,const char *deviceID);
    bool recvrole_pay_91(MB_MsgBuffer *recvPacket);
    bool sendrole_pay_ios(const char* receipt, const char* deviceID);  
    bool recvrole_pay_ios(MB_MsgBuffer* recvPacket);
    bool recvrole_pay_uc(MB_MsgBuffer* recvPacket);
    bool recvrole_pay_dl(MB_MsgBuffer* recvPacket);
    bool recvrole_pay_ZZ(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_360(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_wdj(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_dk(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_mi(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_az(MB_MsgBuffer *recvPacket);
    bool recvrole_pay_yyb(MB_MsgBuffer *recvPacket);
    bool sendinvite_info();
    bool recvinvite_info(MB_MsgBuffer* recvPacket);
    bool sendrole_buy_coin_value();
    bool recvrole_buy_coin_value(MB_MsgBuffer* recvPacket);
    bool sendrole_change_location();
    void send_role_change_name(const char* pName);
   
    void goreSendPayOrder(CCObject *);
    void buyEenergy();
    void initVipConfig();
    int  getNowBuyLimit(kBuyTimesType type);
    int  getMoneyDungeonLimit();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    //冒險家描述
    void setDescription(const char * description);
    const char * getDescription();
    //冒險家名字
    void setName(const char * name);
    const char * getName();
    //首儲禮包描述
    void setFirstPayDesc(const char* desc) { m_sFirstPayDesc = desc;}
    const char* getFirstPayDesc() { return m_sFirstPayDesc.c_str();}
    //邀請者
    void setWhoInviteYou(const char* whoInviteYou) { m_sWhoInviteYou = whoInviteYou;}
    const char* getWhoInviteYou() { return m_sWhoInviteYou.c_str();}
    
    void loadLevelLimit();
    void checkIsNewUser();
    int  getCurrency(kmCurrency_Type type);
    
    int64_t getExpByExp(int64_t exp);
    int32_t getLevelByExp(int64_t exp);
    int64_t getExpByLevel(int level);    
    int  getNeedGold();
    int  getNeedGoldByTime(int type);
//    int  getExplorFreeNeedMonney();
    void goBuyEnergy(CCObject *);
    void goCharge(int index);
    void goBuyDiscoveryTimes(CCObject *);
    void goBuyPvpTimes(CCObject *);
    void goBuyRuleFight(CCObject * obj);
//    void goBuyPlunderTimes(CCObject *);
    void goBuyCoin(CCObject *);
    CCArray* getPayArray() { return m_pPayArray;}
    CCArray* getFirstPayArray() { return m_pFirstPayArray;}
    CCArray* getVipConfigArray() { return m_pVipConig;}
    int getVipLevelUpPay();
    
    //冒險家唯一ID
    CC_SYNTHESIZE(int , m_iUid, UID)
    //冒險家性别
    CC_SYNTHESIZE(uint8_t , m_iSex, Sex)
    //工会ID
    CC_SYNTHESIZE(int , m_iClan, Clan)
    //等級
    CC_SYNTHESIZE_READONLY(uint16_t, m_iLevel, Level)
    //經驗
    CC_SYNTHESIZE(uint64_t, m_iExp, EXP)
    //银两
    CC_SYNTHESIZE_READONLY(int, m_iCoin, Coin)
    //备用
    //CC_SYNTHESIZE(int, m_iCoin2, Coin2)
    //备用
    //CC_SYNTHESIZE(int, m_iCoin3, Coin3)
    //徽章
    CC_SYNTHESIZE_READONLY(int, m_iReputation, Reputation)
    //儲值元寶
    CC_SYNTHESIZE_READONLY(int, m_iGold, Gold)
    //儲值贈送元寶
    CC_SYNTHESIZE_READONLY(int, m_iGoldBoune, GoldBoune)
    //消费积分
    CC_SYNTHESIZE(int ,m_iGoldUsed, GoldUsed)
    //vip等級
    CC_SYNTHESIZE(uint8_t, m_iVipLevel, VipLevel)
    //实际儲值货幣总量
    CC_SYNTHESIZE(int, m_iGoldPay, GoldPay)
    //剩余体力
    CC_SYNTHESIZE_READONLY(uint16_t, m_iEnergy, Energy)
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nPreEnergy, PreEnergy);
    void setEnergy(uint16_t nEnergy)
    {
        m_nPreEnergy = m_iEnergy;
        m_iEnergy = nEnergy;
    }
    //今日体力已購買次數
    CC_SYNTHESIZE(uint16_t, m_iEnergyBuyTimes, EnergyBuyTimes)
    CC_SYNTHESIZE(uint16_t, m_iDiscoveryBuyTimes, DiscoveryBuyTimes)
    CC_SYNTHESIZE(uint16_t, m_iPvpBuyTimes,PvpBuyTimes)
//    CC_SYNTHESIZE(uint16_t, m_iPlunderBuyTimes,PlunderBuyTimes)
    CC_SYNTHESIZE(uint16_t, m_iCoinBuyTimes,CoinBuyTimes)
    //每次購買恢複次數
    CC_SYNTHESIZE(uint16_t, m_iEnergyRecoveryTimes, EnergyRecoveryTimes)
    CC_SYNTHESIZE(uint16_t, m_iDiscoveryRecoveryTimes, DiscoveryRecoveryTimes)
    CC_SYNTHESIZE(uint16_t, m_iPvpRecoveryTimes,PvpRecoveryTimes)
    CC_SYNTHESIZE(uint16_t, m_iRuleFightRecoveryimes,RuleFightRecoveryTimes)
    CC_SYNTHESIZE(int, m_iCoinRecoveryimes,CoinRecoveryimes)
    //下次回復体力時間
    CC_SYNTHESIZE(uint32_t, m_iNextEnergyTime, NextEnergyTime)
    //探险的次數
    CC_SYNTHESIZE_READONLY(uint8_t, m_iDiscoveryTimes, DiscoveryTimes)
private:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nPreDisTimes, PreDisTimes);
    void setDiscoveryTimes(uint8_t nTiems)
    {
        m_nPreDisTimes = m_iDiscoveryTimes;
        m_iDiscoveryTimes = nTiems;
    }
    //下次探险回復的時間
    CC_SYNTHESIZE(uint32_t, m_iNextDscvTime, NextDscvTime)
    CC_SYNTHESIZE(uint32_t, m_iNextPvpcvTime, NextPvpcvTime)
//    CC_SYNTHESIZE(uint32_t, m_iNextPlundercvTime, NextPlundercvTime)
    //排位pvp的次數
    CC_SYNTHESIZE(uint8_t, m_iPVPTimes, PVPTimes )
    //夺寶的次數
//    CC_SYNTHESIZE(uint8_t, m_iPlunderTimes, PlunderTimes)
    //随机讨伐次數
    CC_SYNTHESIZE(uint8_t, m_iRandomPVPTime, RandomPVPTime)
    //精靈單挑的次數(預留)
    CC_SYNTHESIZE(uint8_t, m_iSinglePVPTime, SinglePVPTime)
    //神將录决鬥总次數 old
    //CC_SYNTHESIZE(uint8_t, m_iPetTimes,PetTimes);
    //神將录决鬥总次數 new
    CC_SYNTHESIZE(uint16_t, m_iChallengeGodTimes,ChallengeGodTimes);
    // 神將录可購買的次數
    CC_SYNTHESIZE(uint16_t, m_iChallengePayTimes, ChallengePayTimes);
    // 神將录免费次數
    CC_SYNTHESIZE(uint16_t, m_iChallengeFreeTimes, ChallengeFreeTimes);
    // 神將录精靈位置
    CC_SYNTHESIZE(uint8_t, m_iChallengePetPos, ChallengePetPos);
    // 神將录單次購買的价格
    CC_SYNTHESIZE(uint16_t, m_iChallengeEachPayPrice, ChallengeEachPayPrice)
    //体力上限
    CC_SYNTHESIZE(uint16_t, m_iEnergyMax, EnergyMax)
    //探险次數上限
    CC_SYNTHESIZE(uint8_t, m_iDiscoveryTimesMax, DiscoveryTimesMax)
    //
    CC_SYNTHESIZE(uint8_t, m_iPVPTimesMax, PVPTimesMax )
    //夺寶的次數上限
    CC_SYNTHESIZE(uint8_t, m_iPlunderMax, PlunderTimesMax)
    //随机讨伐次數上限
    CC_SYNTHESIZE(uint8_t, m_iRandomPVPTimeMax, RandomPVPTimeMax)
    //精靈單挑的次數上限(預留)
    CC_SYNTHESIZE(uint8_t, m_iSinglePVPTimeMax, SinglePVPTimeMax)
    //角色官爵
    CC_SYNTHESIZE(uint8_t, m_iTitle, Title)
    //當前付费id
    CC_SYNTHESIZE(uint32_t, m_uCurPayID, CurPayID);    
    //奇遇解鎖
    CC_SYNTHESIZE(uint8_t, m_iEnCounterFreeNum , EnCounterFreeNum)
    
    //是否绑定過微博
    CC_SYNTHESIZE(bool, m_nisBindWeibo, isBindWeibo);
    //是否輸入過邀請碼
    CC_SYNTHESIZE(bool, m_nisInputInviteCode, isInputInviteCode);
    //已經完成邀請好友數量
    CC_SYNTHESIZE(uint16_t, m_nInviteNum, InvireNum);
    //已獲得的邀請好友儲值力保的次數
    CC_SYNTHESIZE(uint16_t,m_nGetFirstPayRewardNum, GetFirstPayRewardNum);
    CC_SYNTHESIZE(bool, m_pisPvpPushOpen, isPvpPushopen);
    CC_SYNTHESIZE(bool, m_pisPushNightMute, isPushNightMute);
    
    
    //奇遇功能限制
    CC_SYNTHESIZE(uint16_t, m_pRoleAdventureLimit, RoleAdventureLimit);
    //戰役功能限制
    CC_SYNTHESIZE(uint16_t, m_pRoleNormalLimit, RoleNormalLimit);
    //副本功能限制
    CC_SYNTHESIZE(uint16_t, m_pRoleCarbonLimit, CarbonLimit);
    //虎老關功能限制
    CC_SYNTHESIZE(uint16_t, m_pRoleRocketTeamLimit, RoleRocketTeamLimit);
    //华容功能限制
    CC_SYNTHESIZE(uint16_t, m_pRoleHuaRongLimit, RoleHuaRongLimit);
    //夺寶限制
    CC_SYNTHESIZE(uint16_t, m_pRolePlunderLimit, RolePlunderLimit);
    //爭霸限制
    CC_SYNTHESIZE(uint16_t, m_pRolePvpLimit, RolePvpLimit);
    //皇权限制
    CC_SYNTHESIZE(uint16_t, m_pRoleKingLimit, RoleKingLimit);
    //南蛮等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleNanMLimit, RoleNanMLimit);
    //長版坡等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleChangbanLimit, RoleChangbanLimit);
    //神將录等級限制 old
    //CC_SYNTHESIZE(uint16_t, m_pRolePetLimit, RolePetLimit);
    //神將录等級限制 new
    CC_SYNTHESIZE(uint16_t, m_pRoleChallengeGodLimit, RoleChallengeGodLimit);
    //援军等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleAidLimit, RoleAidLimit);
    //联盟大賽等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleOnesLimit, RoleOnesLimit);
    //联盟大賽報名等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleOnesSignLimit, RoleOnesSignLimit);
    //無双限制
    CC_SYNTHESIZE(uint16_t, m_pRoleWushuangLimit, RoleWushuangLimit);
    //煉狱限制
    CC_SYNTHESIZE(uint16_t, m_pRoleAdvanceLimit, RoleAdvanceLimit);
    //聊天等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleChatLimit,  RoleChatLimit);
    //掃蕩等級限制
    CC_SYNTHESIZE(uint16_t, m_pRoleSweepLimit, RoleSweepLimit);
    //掃蕩vip等級限制
    CC_SYNTHESIZE(uint8_t, m_pRoleSweepVip, RoleSweepVip);
    //帝王限制
    CC_SYNTHESIZE(uint8_t, m_pRoleEmperorLimit, RoleEmperorLimit);
    
    CC_SYNTHESIZE(uint32_t, m_pLastWeiXinShareSec, LastWeiXinShareSec);

    CC_SYNTHESIZE(kSceneTipLayerType, m_nWillShowLayer,WillShowLayer);
    CC_SYNTHESIZE(uint8_t,m_nWeiboCount,WeiboCount);
    CC_SYNTHESIZE(uint32_t, m_nBuyCoinValue, BuyConinValue);
    
    //玩家头像
    CC_SYNTHESIZE(uint32_t, m_nHead, Head);
    uint16_t getSettinglength();
    uint8_t  * getSettings();
    CC_SYNTHESIZE(bool, m_bPveHasFailed, PveHasFailed);

    //检查双倍儲值
    CC_SYNTHESIZE(uint32_t , m_nPayInfoId , PayInfoId );
    
	//抽卡次数
	CC_SYNTHESIZE(uint32_t, m_nChouKaTimes, ChouKaTimes);
    std::string     m_pChangedName;
};
class MB_VipConfig:public CCObject{
    
    public :
    
        MB_VipConfig();
        ~MB_VipConfig();
        CC_SYNTHESIZE(short, m_nLevel, level);
        CC_SYNTHESIZE(int, m_nEnergyBuyLimit, EnergyBuyLimit);
        CC_SYNTHESIZE(int, m_nDiscoveryBuyLimit, DiscoveryLimit);
        CC_SYNTHESIZE(int, m_nPvpBuyLimit, PvpLimit);
//        CC_SYNTHESIZE(int, m_nPlunderBuyLimit, PlunderLimit);
        CC_SYNTHESIZE(int, m_nCoinBuyLimit,CoinBuyLimit);
    CC_SYNTHESIZE(int64_t, m_nLvuppay, Lvuppay);
    CC_SYNTHESIZE(int, m_nMaxFriendNum,MaxFriendNum);
    CC_SYNTHESIZE(int, m_nRuleFightBuyLimit,RuleFightBuyLimit);
    CC_SYNTHESIZE(int, m_nMoneyDungeon,MoneyDungeon);
};
class MB_TitleTemplete :public CCObject{
  
    private:
    
        std::string m_strTitleName;
        std::string m_strMfaceFrame;
        std::string m_strFfaceFrame;
        std::string m_strMcardFrame;
        std::string m_strFcardFrame;
    
    public:
    
        MB_TitleTemplete(){
    
        }
        ~MB_TitleTemplete(){
    
        }
      
        const char * getTitleName();
        const char * getMFaceFrame();
        const char * getMCardFrame();
        const char * getFFaceFrame();
        const char * getFCardFrame();
    
        void setTitleName(const char * titleName);
        void setMFaceFrame(const char * mfaceFrame);
        void setMCardFrame(const char * mcardFrame);
        void setFFaceFrame(const char * ffaceFrame);
        void setFCardFrame(const char * fcardFrame);
            
        CC_SYNTHESIZE(int, m_nLevelNeed, LeveLNeed);
        CC_SYNTHESIZE(int, m_nRankNeed, RankNeed);
        CC_SYNTHESIZE(uint8_t, m_nTitleID, TitleID);
};
typedef std::map<uint8_t , MB_TitleTemplete*> TitleMap;
typedef std::pair<uint8_t , MB_TitleTemplete *> TitleEntry;


class MB_TitleMgr{
    
private:
    
    TitleMap m_mapTitle;
    static  MB_TitleMgr * m_pSharedTitleMgr;
    void initTitleData();
    
public:
    
    MB_TitleMgr();
    ~MB_TitleMgr();
    
    MB_TitleTemplete *getTitleByID(uint8_t titleID);
    static MB_TitleMgr *getInstance();
    void purgeData();
    
};

class MB_FirstPayTemplete:public CCObject
{
    CC_SYNTHESIZE(uint32_t, m_uID, ID);
    CC_SYNTHESIZE(int, m_nNum, Num);
    CC_SYNTHESIZE(int, m_nType, Type);
};

class MB_PayTemplete: public CCObject
{
public:
    CC_SYNTHESIZE(uint32_t, m_uID, ID);
    CC_SYNTHESIZE(uint32_t, m_uIapID, IapID);
    CC_SYNTHESIZE(int, m_nGold, Gold);
    CC_SYNTHESIZE(int, m_nBonus, Bonus);
    CC_SYNTHESIZE(float, m_nPrice, Price);
    CC_SYNTHESIZE(int, m_nExtreward, Extreward);
    
    const char* getIconName() { return m_sIconName.c_str();}
    void setIconName (const char* iconName) { m_sIconName = iconName;}
    
private:
    std::string m_sIconName;
};

#endif /* defined(__ProjectMB__MB_RoleData__) */
