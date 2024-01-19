//
//  MB_LayerResultPve.h
//  ProjectMB
//
//  Create by chk on 29/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerResultPve__
#define __ProjectMB__MB_LayerResultPve__

#include "MB_ResWindow.h"
#include "Game.h"
class SResultData;
class MB_LayerResultPve : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    
    static MB_LayerResultPve * create(recvfight *fightResult,p_reward *result ,bool bFirstFailed=false);
    bool   init(recvfight *fightResult,p_reward *result,bool bFirstFailed);
    
	MB_LayerResultPve();
	virtual ~MB_LayerResultPve();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void onEnter();
    void onExit();
protected:
    void onBackClick(CCObject* pSender);
    void onHomeClick(CCObject* pSender);
    void onRetryClick(CCObject* pSender);
    void update(float dt);
    void updateBack(float dt);
    void updateStarSound(float dt);
    void onBack();
    int lastLevel;
    float lastExp;
    int nowLevel;
    float nowExp;
    float addExpSpeed;
    int preDiscovery;
    int preEnergy;
    int starSoundIndex;
    int starSoundIndex2;
protected:
    CCLabelBMFont*	m_pExpLabel;
    CCLabelBMFont*	m_pCoinLabel;
    CCNode*	m_pNodeReward;
    CCSprite* m_pStars[3];
    bool m_bClickedBack;
    CCSprite* m_pSpr1;
    CCSprite* m_pSpr2;
    CCSprite* m_pSpr3;
    CCBAnimationManager* m_pAnimation;
    
    CCNode* m_pNode1;
    CCNode* m_pNode2;
    CCNode* m_pNodeScroller;
    CCLabelBMFont* m_pRoleExp;
    CCSprite* m_pSpriteExp;
    CCSprite* m_pSpriteExp2;
    CCLabelBMFont* m_pRoleLevel;
    CCLabelTTF* ttf_chaptername2;
    CCNode* m_pLevelUp;
    CCProgressTimer* m_pExpTimer;
    CCProgressTimer* m_pExpTimer2;
    
    CCNode* m_pItemSpr1;
    CCNode* m_pItemSpr2;
    int64_t m_preExp;
    int64_t m_nextExp;
    
};


class MB_LayerResultChungGuan:public MB_LayerResultPve
{
public:
    static MB_LayerResultChungGuan * create(recvfight *fightResult,p_reward *result);
    bool   init(recvfight *fightResult,p_reward *result);
};

class MB_LayerResultRoad:public MB_LayerResultPve
{
public:
    static MB_LayerResultRoad * create(recvfight *fightResult,SResultData *result);
    bool   init(recvfight *fightResult,SResultData *result);
private:
    SResultData* m_pResultData;
};

#endif /* defined(__ProjectMB__MB_LayerResultPve__) */
