
#ifndef __ProjectMB__MB_LayerEventRecoveryEnergy__
#define __ProjectMB__MB_LayerEventRecoveryEnergy__

#include "Game.h"
//补体力
class MB_NodeRolePKQ;
class MB_LayerEventRecoveryEnergy :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
private:
    
    CCControlButton *m_pGetBtn;
    CCSprite *m_pInfoSpr1;
    CCSprite *m_pInfoSpr2;
    CCSprite *m_pInfoSpr3;
    CCNode* m_pTowel1;
    CCNode* m_pTowel2;
    CCNode* m_pTowel3;
//    CCNode* m_pNodeCloudLand;
public :
    
    MB_LayerEventRecoveryEnergy();
    ~MB_LayerEventRecoveryEnergy();
    virtual bool init();
    static MB_LayerEventRecoveryEnergy * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onResetWnd(void);
    void timeTick(float dt);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onClosedClicked(CCObject*);
    void onGetClick(CCObject*);
    void onExit();
    void onEnterTransitionDidFinish();
//    void update(float dt);
};

#endif /* defined(__ProjectMB__MB_LayerEventRecoveryEnergy__) */
