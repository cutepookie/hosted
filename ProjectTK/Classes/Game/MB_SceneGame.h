

#ifndef __ProjectMB__GameScene__
#define __ProjectMB__GameScene__

#include "Game.h"
#include "MB_DataPVP.h"
#include "MB_CommonType.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
//using namespace std;
#define REEL_NODE 10
#define ANGERY_NODE 11
#define FIGHTSCENE 199
#include<queue>
class MB_NodeShow;
class SResultData;
class MB_SceneGame:public CCLayer
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCBMemberVariableAssigner
{
protected:
    float m_pSpeed;
    CCNode*m_pNodeTop;
    CCNode *m_pLayerShow;//显示层
    uint64_t m_nPreHp;
    recvfight *m_pSc_fightdata;
    p_action *m_pActionmove;
    float m_nTimeCount;
    float m_nLastTimeStart;
    float m_nCenterOur;
    float m_nCenterEnenmy;
    bool m_bIsover;
    CCBAnimationManager *m_pAnimationMgr;
    CCNode *m_pTempode[12];

    float timePos[20][20];
    //result不同需要重载的内容
    p_reward *m_pReward;
    p_result_ranking* m_pResultPVPRanking;
    sTreasureRobResult m_TreasureRobData;
    //    CCArray* m_pRewardArray;
    
    SResultData* m_pResultdata;          //
    
    int m_pRewardCoin;
    int m_pRewardReputation;
    int m_pAddRewardCoin;
    CCNode *m_pNodeJump;
    CCNode *m_pNodeOtherRole;
    CCNode *m_pNodeRole;
    CCLabelTTF *m_pOtherRoleName;
    CCLabelTTF *m_pOtherRoleLevel;
    CCLabelTTF *m_pRoleName;
    CCLabelTTF *m_pRoleLevel;
    CCLabelTTF *m_pPassName;
    
    int indexEnterOur;
    CCMenu *m_pMenu;
    bool isShowJump;
    
    CCCallBackDelegate*   m_pReplayCallBackTarget;
    CallBack1st m_pReplayCallBack;
    CCNode* m_pEnemyNode;
    CCSprite* m_pBattleBg;
    CCSprite* m_pDiZuo;
    CC_SYNTHESIZE(bool, m_bFirstFailed, FirstFailed);
    std::vector<p_action *> m_actionVector;
    CCMenuItemImage* m_pMenuSpeedUp;
    void onPlotPlayComplate(CCObject* pSender);
public:
    MB_NodeShow *m_pOur[CARD_IN_GAME];//我方卡牌数组
    MB_NodeShow *m_pEnemy[CARD_IN_GAME];//地方卡牌数组
    void setBattleBackground(const char* pFile);
    
    const char* getOtherLv(){return m_pOtherRoleLevel->getString();};
    const char* getSelfLv(){return m_pRoleLevel->getString();};
    
    void setBlood(int petPos,int addHp);
    void palyDaZhao(bool b);
    void delayPalyDaZhao();
    void initEnd();
    void initEndWorldBoss();
    uint8_t tempZhongZu;
    int m_pTeamPos;
    CC_SYNTHESIZE(uint64_t, m_nReplayID, ReplayID);
    CC_SYNTHESIZE(uint8_t, m_nTable, Table);
    CC_SYNTHESIZE(uint8_t, m_nReplayType, ReplayType);//0pvp，1皇权,2emperor
    
    
    MB_SceneGame ();
    ~MB_SceneGame();
    void actionAddDelayTime(float delay);
    //执行一个攻击
    void LoadOneFight(p_action * );
    void LoadOneFight2();
    void LoadOneFight2(p_action * oneFight);
    bool init(recvfight *recvfightdata,bool isScaleBoss = false);
    
    virtual void onEnter();
    virtual void onExit();
    
    //result不同需要重载的内容
    static CCScene *scene(recvfight *recvfightdata,int rewardcoin,int rewardreputation,bool isScaleBoss);
    static CCScene *scene(recvfight *recvfightdata,int rewardCoin,int rewardreputation);
    static CCScene *scene(recvfight *recvfightdata,p_reward *reward,uint16_t doungeonLevel,const char* pBg=NULL,bool bFirstFailed=false);
    static CCScene *scene(recvfight* fightData, p_result_ranking* resultData,const char* pBg=NULL);
    static CCScene *scene(recvfight* fightdata, sTreasureRobResult* resultData);
    static CCScene *scene(recvfight* fightdata);
    static CCScene *scene(recvfight* fightdata,const char *attackName, const char *defenseName,const char* pBg = NULL);
    static CCScene *sceneChangeCoin(recvfight* fightdata,int rewardcoin,int addrewardcoin,const char* pBg = NULL);
    static CCScene *scene(recvfight* fightdata,const char *attackName, const char *defenseName,uint64_t replayId,uint8_t table,uint8_t type);
    static CCScene *sceneWithReward(recvfight* fightdata,SResultData* pResultData);
    void showStart();
    void setReward(p_reward *reward);
    void setResult(p_result_ranking* resultData);
    void setResult(sTreasureRobResult* resultData);
    void setResult(const char *attackName, const char *defenceName);
    void releaseFightData(recvfight* pData);
    const char * getAttackName();
    const char * getDefenceName();
    void setReward(int rewardcoin,int rewardreputation);
    static MB_SceneGame * create(recvfight *recvfightdata,bool isScaleBoss = false);
    
    //初始化卡牌
    void loadArmy();
    void tickAniamtion(float dt);
    void startAnimation();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    MB_NodeShow * getActorByindexAndType(int index,int type);
    virtual void onMainMenuClick(CCObject *);
    void onSpeedUpClick(CCObject *);
    void onMainOver(CCObject *);
    bool  isnextSameType(int actionId1, int actionId2);
    void removeNodeAndCleanUp(CCNode *node);
    CCPoint  getCenterByType(int type);
    void loadTimeXml();
    void onAllover();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    virtual void delayOver();
    void tickInEnter(float dt);
    void setTouch(bool touch);
    CC_SYNTHESIZE(bool, m_nIsDelayOver, IsDelayOver);
    void whenDelayOver();
    void rePlay();
    CCProgressTimer*  setProgressBar(CCSprite* spr,CCPoint midp,int o = 255);
    void updateProgress(float dt);
    void updateProgressWorldBoss(float dt);
    void finishProgress();
    void finishStartBg();
    void finish2();
    void finish3();
    void loadDaZhaoRes(float dt);
    void loadDaZhaoResDemo(float dt);
private:
    int m_nOurAllHpNum;
    int m_nOurNowHpNum;
    int m_nEnemyAllHpNum;
    int m_nEnemyNowHpNum;
    int m_nWorldBossBarNum;
    map<int,uint64_t> ourPosNowHp;
    map<int,uint64_t> enemyPosNowHp;
    map<int,uint64_t> ourPosAllHp;
    map<int,uint64_t> enemyPosAllHp;
    
    CCSprite* m_ourBar1;
    CCSprite* m_ourBar2;
    CCSprite* m_enemyBar1;
    CCSprite* m_enemyBar2;
    CCLabelBMFont* m_pAllOurHP;
    CCLabelBMFont* m_pAllEnemyHP;
    CCProgressTimer* ourProgress1;
    CCProgressTimer* ourProgress2;
    CCProgressTimer* m_enemyProgress1;
    CCProgressTimer* m_enemyProgress2;
    CCProgressTimer* ourProgress1_o;
    CCProgressTimer* ourProgress2_o;
    CCProgressTimer* m_enemyProgress1_o;
    CCProgressTimer* m_enemyProgress2_o;
    CCLabelBMFont* m_pBossLevel;
    CCLabelTTF* m_pTitleName1;
    CCLabelTTF* m_pTitleName2;
    bool m_bIsScaleBoss;
    float nowOurPer;
    float nowEnemyPer;
    float nowTrueEnemyPer;
    int deayPerFrame_our;
    int deayPerFrame_enemy;
    float progressSpeedJian_our;
    float progressSpeedJian_enemy;
    float progressSpeedJian_our_o;
    float progressSpeedJian_enemy_o;
    float PROGRESSSPEED_our;
    float PROGRESSSPEED_enemy;
    CCLayerColor* m_pStartBg;
    int lastPetPos;
    bool isRunScaleMoveNode;
    
    
    int toAddIndex;
    CCPoint dizuoLittleP;
    float dizuoLittleSX;
    float dizuoLittleSY;
    CCPoint dizuoBigP;
    float dizuoBigSX;
    float dizuoBigSY;
    
    CCPoint EnemyNodeLittleP;
    float EnemyNodeLittleSX;
    float EnemyNodeLittleSY;
    CCPoint EnemyNodeBigP;
    float EnemyNodeBigSX;
    float EnemyNodeBigSY;
    
    int worldBossBarIndex;
    CCLabelBMFont* m_pNowEnemyHP;
};



#endif /* defined(__ProjectMB__GameScene__) */
