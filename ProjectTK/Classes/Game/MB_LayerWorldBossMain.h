

#ifndef __ProjectMB__MB_LayerWorldBossMain__
#define __ProjectMB__MB_LayerWorldBossMain__

#include "Game.h"
#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
class MB_EventData;
class MB_ResearchInstituteInterface;
class MB_LayerWorldBossMain:public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    friend class MB_ResearchInstituteInterface;
public:
    bool setDataSource(CCFunctionDataSource* pDataSource);
    
private:
    bool    m_bFirstEnter;
    MB_LayerWorldBossMain();
    CCLabelTTF *m_pTimeStart;
    CCLabelBMFont *m_pAutoRellifeTime;
    
    CCNode *m_pNodeBoss;
    CCNode *m_pNotActive;
    CCNode *m_pNodeActive;
    CCNode *m_pVipvisible;
    CCNode *m_pNodeLife;
    CCNode *m_pNodeDie;
    CCNode *m_pNodeAddBuff;
    
    CCNode *m_pNodeNowReport;
    
    CCSprite *m_pBloodBar;
    CCProgressTimer *m_pBloodTimer;
    CCLabelBMFont *m_pBossLevel;
    CCLabelBMFont *m_pBossBlood;
    CCLabelBMFont *m_pBossBlood2;
    CCLabelTTF *m_pReward;
    CCLabelTTF *m_pOfflineCost;
    CCLabelBMFont *m_pNowTotalDamage;
    CCLabelBMFont *m_pNowRank;
    CCNode *m_pDamageZone;
    MB_EventData* m_pData;
    CCSpriteFrame *m_pPreframe;
    CCSpriteFrame *m_pAutoPreFrame;
    CCMenuItemImage * m_pAutoOffLineBt;
    CCMenuItemImage * m_pAutoFight;
    CCNode *m_pWillDo;
    CCNode *m_pDone;
    CCLabelBMFont *m_pBuffNum;
    CCSprite*   m_pBloodBar3;
    CCSprite*   m_pBloodBar2;
    CCSprite*   m_pBloodBar1;

    bool isAutoPlay;
    CCNode *m_pBuffer;
    CCNode* m_pToAddGuWu;
    CCScrollView* m_pScrollView;
    void onAnimationCompleted();
    bool m_bAnimationComplete;
    CCBAnimationManager *m_pAniamtion;
    CCBAnimationManager *m_pBuffAniamtion;
    CCControlButton* m_pAddBuff;
    bool isInGame ;
    MB_ResWindow *m_pNodeFight;
    uint8_t lastBossResult;
    bool isToShowClose;
    uint64_t harm;
    uint32_t coin;
    uint32_t repu;
    static int ms_nLayerID;
    int m_nLayerID;
    
    public :
    bool isToHome;
    
    ~MB_LayerWorldBossMain();
    virtual bool init();
    //        static  MB_LayerWorldBossMain* create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onCloseClick(CCObject *object);
    void onReportClick(CCObject *object);
    void onAddBuffClick(CCObject *object);
    void onSoSAddBuffClick(CCObject *object);
    void onPreReportClick(CCObject *object);
//    void onOfflineClick(CCObject *object);
    void onAutoBattleClick(CCObject *object);
    void onBattleClick(CCObject *object);
    void onRelifeClick(CCObject *object);
    void onRuleClicked(CCObject* pSender);
    void tickCountToStart(float dt);
    void tickReborn(float dt);
    bool sendworldboss_fight();
    bool sendworldboss_last_info();
    bool sendworldboss_cur_info();
    bool sendworldboss_open(CCObject *);
    bool recvworldboss_cur_info_ignore(MB_MsgBuffer* recvPacket);
    bool recvworldboss_cur_info(MB_MsgBuffer* recvPacket);
    bool recvworldboss_offline_play(MB_MsgBuffer* recvPacket);
    bool recvworldboss_last_info_fail(MB_MsgBuffer* recvPacket);
    bool recvworldboss_last_info_win(MB_MsgBuffer *recvPacket);
    bool recvworldboss_last_info_ignore(MB_MsgBuffer *recvPacket);
    bool recvworldboss_reborn(MB_MsgBuffer *recvPacket);
    bool recvworldboss_fight(MB_MsgBuffer *recvPacket);
    bool recvworldboss_hp_sync(MB_MsgBuffer *recvPaccket);
    bool recvworldboss_rank_sync(MB_MsgBuffer *recvPaccket);
    bool recvworldboss_buff_sync(MB_MsgBuffer *recvPaccket);
    bool recvworldboss_buff(MB_MsgBuffer *recvPaccket);
    bool recvworldboss_stop(MB_MsgBuffer *recvPaccket);
    bool recvworldboss_harm_broadcast(MB_MsgBuffer *recvPaccket);
    void tickBossBeKillShowMessage(float dt);
    void onBufferOneClick(CCObject *);
    void onBufferTwoClick(CCObject *);
    void onBufferThreeClick(CCObject *);
    void onDetailCloseClick(CCObject *);
    void onSoSDetailCloseClick(CCObject *);
    virtual void onEnter();
    virtual void onExit();
    virtual void onResetWnd (void);
    void setBloodCorlorByProgress(float persent);
    void onEnterTransitionDidFinish();
    int m_nSelectBuffType;
};


#endif /* defined(__ProjectMB__MB_Nodeworldbosso__) */
