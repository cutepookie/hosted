//
//  MB_LayerHome.h
//  ProjectPM
//
//  Created by WenYong on 14-4-9.
//
//

#ifndef __ProjectMB__MB_LayerHome__
#define __ProjectMB__MB_LayerHome__
#include "MB_ResWindow.h"
#include "MB_LayerHomeFlipDelegate.h"

#define MOVESCENESPEED 2500
class MB_PetData;
class MB_LayerHome:public MB_FunctionMainWnd
{
public:
    MB_LayerHome();
    virtual ~MB_LayerHome();
    
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    CREATE_FUNC(MB_LayerHome);
    void setCardIcon(MB_PetData *  data);
    void setYDSJ();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onCardInfoClicked(CCObject* pSender);
    void onCloseJSClicked(CCObject* pSender);
    void onAndOffBtn();
    void onMXClicked(CCObject* pSender);
    void onYLJKClicked(CCObject* pSender);
    void onSCClicked(CCObject* pSender);
    void onCallCardClick(CCObject* pSender);
    void onWorldBossClicked(CCObject* pSender);
    void tickCountToStart(float dt);
    void tickCountToStart2(float dt);
    void onEnterTransitionDidFinish();
    void tick(float dt);
protected:
    bool initFunctions();
protected:
    
    void updateNode(CCNode* pNode);
    void finish();
    void finish2();
private:
    bool isYueKa;
    CCControlButton* m_pSCBtn;
    CCLabelBMFont* m_pworldBossTime;
    CCNode* sceneNode;
    CCNode* m_pNodeReward;
    CCNode* m_pNodeEmail;
    CCNode* m_pNodeActivaty;
    CCPoint m_TouchBegain;
    CCLabelBMFont* m_pFightPower;
    CCNode* m_pNodeVipPack;
    CCNode* m_pNodeCharge;
    CCNode* m_pNodeDaily;
    CCNode* m_pNodeYeShiJie;
    CCNode* m_pNodePic;
    CCNode* m_pNodeGift;
    CCNode* m_pNodeKing;
    CCNode* m_pNodeAprCard;
    CCNode* m_iconHomeNode[6];
    CCSprite* m_pCardIcon;
    CCLabelTTF* m_pCardName;
    MB_PetData * m_pPetData;
    CCNode* m_pLeft;
    CCNode* m_pRight;
    CCNode* m_pLeftLong;
    CCNode* m_pCloseJS;
    CCNode* m_pXiangxi;
    CCPoint leftP,rightP,leftLongP,closeJSP,xiangxiP,upP,downP;
    bool isOn;
    CCRect leftMoveRect;
    bool isTouchLeftMove;
    CCSprite* m_pVipLevelSpr;
    CCNode* moveDown;
    CCNode* moveUp;
    CCNode* m_pWorldBossBtn;
    CCNode* node_worldBoss;
    CCNode* m_pToAddNode;
    CCNode* m_pworldBossStar;
    int m_nWorldBossBeginTime;
    CCNode* node_flag_main;
    CCLabelBMFont* flag_main;
    CCNode* node_flag_yljk;
    CCNode* node_flag_mx;
    CCLabelBMFont* flag_yljk;
    CCLabelBMFont* flag_mx;
    uint16_t iTimes;
};

#endif /* defined(__ProjectMB__MB_LayerHome__) */
