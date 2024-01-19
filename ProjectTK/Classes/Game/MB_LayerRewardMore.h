

#ifndef __ProjectMB__MB_LayerRewardMore__
#define __ProjectMB__MB_LayerRewardMore__

#include "Game.h"

#define REWARD_MORE_COUNT 14

class MB_LayerRewardContainer;

class MB_LayerRewardMore : public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
{
public:
    MB_LayerRewardMore();
    ~MB_LayerRewardMore();
    
    static MB_LayerRewardMore* create(CCArray* valueArray);
    static MB_LayerRewardMore* createWithRewardLayer(MB_LayerRewardContainer* pLayer);
    
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(CCArray* valueArray);
    virtual void onResetWnd();
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onCommitClicked(CCObject* pSender);
    void setCallBack(CCObject *target,SEL_MenuHandler callback);
    
    void onEnterTransitionDidFinish();
protected:
    virtual bool initWithRewardLayer(MB_LayerRewardContainer* pLayer);
    CCControlButton* m_pBtn;

    
//    CCNode*             m_pNode[REWARD_MORE_COUNT];
//    CCLabelTTF*         m_pTTFName[REWARD_MORE_COUNT];
//    CCNode*             m_pNodeIcon[REWARD_MORE_COUNT];
    CCObject *          m_pTarget;
    SEL_MenuHandler     m_pCallBack;
    CCArray*            m_ValueArray;
    
    CCNode*             m_pNodeScroll;
    CCScrollView*       m_pScrollView;
};

class MB_LayerRewardMore2 : public MB_LayerRewardMore
{
public:
    MB_LayerRewardMore2();
    virtual ~MB_LayerRewardMore2();
    static MB_LayerRewardMore2* create(CCArray* valueArray); 
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(CCArray* valueArray);
    virtual void onResetWnd();
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void restTouch();

};
#endif /* defined(__ProjectMB__MB_LayerRewardMore__) */
