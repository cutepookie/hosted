//
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#ifndef __ProjectMB__MB_LayerChapterWnd__
#define __ProjectMB__MB_LayerChapterWnd__

#include "MB_FunctionMainWnd.h"
class MB_XmlNode;
class MB_DungeonInfo;
class MB_MsgBuffer;
class MB_DungeonData;
class p_reward;
class MB_LayerStoryPlayer;
class MB_LayerChapterWnd:public MB_FunctionMainWnd
{
public:
    MB_LayerChapterWnd();
    ~MB_LayerChapterWnd();
    virtual bool init();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onCloseClicked(CCObject* pSender);
    void onPerfectBoxClicked(CCObject* pSender);
    void onCloseClick(CCObject* pSender);
    bool initConfigure();
    bool initDungeonData(MB_DungeonData* pDungeoData,MB_XmlNode* pNode);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    MB_DungeonInfo* getDungeonInfoById(uint16_t nDungeonId);
    
    void updateDungeonData(MB_DungeonData* pDungeoData);
    void onGetRewardClicked(CCObject* pSender);
    void onSweepClicked(CCObject* pSender);
    void onBattleClicked(CCObject* pSender);
    void goMessageShow();
    void swithXuanGuanOrReady(bool isXuanGuan,int index = 1,const char * levelName = "");
    void resetSweep();
    void onExit();
    void onEnterTransitionDidFinish();

protected:
    void sendbattle_perfect_reward();
    void recvbattlt_perfect_reward(MB_MsgBuffer* pRecv);
    void recvbattle_dungeon_raids(MB_MsgBuffer* pRecv);
    void showReward();
    void recvbattle_challenge(MB_MsgBuffer* pRecv);
    void sendbattle_challenge(uint8_t type,uint16_t id);
    void onNextClick(CCObject*);
    void onSetReward(p_reward *reward,MB_MsgBuffer* recvPacket);
    MB_DungeonData* queryDungeonDataById(uint16_t id);
    bool hasPassed();
    
    void checkLevelUp();
    void requestBattle(CCObject* pSender);
    bool playPlot(int dungeonId,int condition);
    MB_LayerStoryPlayer* tryCreateStoryPlayer(int dungeonId,int condition);
    void setReadyUI();
    virtual void onEnter();
    void onClickTZDW(CCObject* pSender);
    void updateToRetry(float dt);
private:
    bool isToXuanGuan;
    CCLabelTTF* m_pChapterName2;
    CCNode*     m_pNodeContainer;
    CCScrollView* m_pScrollView;
    CCArray*    m_pDungeonList;
    std::string m_szBackground;
    CCNode* m_pNodeScroller;
    CCNode* m_pXuanGuan;
    CCNode* m_pReady;
    CCNode *m_pStar[3];
    CCNode* m_pPassP[10];
    CCLabelBMFont* m_pMoney;
    CCLabelBMFont* m_pExp;
    CCLabelBMFont* m_pLefttimes;
    CCControlButton* m_pBtnSweep;
    CCNode* m_pWuXianLabel;
    CCNode *m_pItem0;
    CCNode *m_pItem1;
    CCNode* m_pItemMoveNode;
    CCNode* m_pRootLine;
    CCNode* m_pBg;
    int m_nLevel;
    int m_nPreExp;
    int m_nPreEnery;
    int m_nPreDicovery;
    int m_nPreStar;
    int m_nDungeonLevel;
    bool m_bPerfect;
    bool m_bComplate;
    uint16_t    m_nDungeonId;
    int selectIndex;
    MB_DungeonData* m_pNowdata;
    CCNode* pRootNode2;
    bool m_bShowTutorial;
    
    int m_nPreValue[3];       //扫荡前 等级、冒险次数、体力次数
    float lastItemMoveNodeX;
    CCSprite* m_pTitle;
};

#endif /* defined(__ProjectMB__MB_LayerChapterWnd__) */
