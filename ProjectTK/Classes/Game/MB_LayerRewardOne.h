
#ifndef __ProjectMB__MB_LayerRewardOne__
#define __ProjectMB__MB_LayerRewardOne__

#include "Game.h"
#define REWARD_TEN_COUNT 10

class MB_LayerRewardOne : public MB_ResWindow
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
{
public:
	MB_LayerRewardOne();
	~MB_LayerRewardOne();
	static MB_LayerRewardOne* createTen(CCArray* valueArray, uint8_t type = kRewardValueTypePet);
	static MB_LayerRewardOne* create(uint8_t type, uint16_t typeID, uint32_t num = 1, uint8_t rank = 0);             //奖励一个道具或精灵的界面   没有动画  type(1:pet 2:item)

	static MB_LayerRewardOne* createPet(uint8_t type, uint16_t typeID, uint32_t num = 1, uint8_t rank = 0);          //奖励一个精灵的界面   有闪电动画
	static MB_LayerRewardOne* createItem(uint8_t type, uint16_t typeID, uint32_t num = 1, uint8_t rank = 0);         //奖励一个道具的界面   有闪电动画

	virtual bool initTen(CCArray* valueArray, uint8_t type);
    virtual bool initTenAgain(CCArray* valueArray, uint8_t type);
	virtual bool initPet(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank = 0);
    void initPetAgain(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank = 0);
	virtual bool initItem(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank = 0);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(uint8_t type, uint16_t typeID, uint32_t num, uint8_t rank = 0);
	virtual void onResetWnd();

	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

	CC_SYNTHESIZE(uint8_t, m_uType, Type);
	CC_SYNTHESIZE(uint16_t, m_uTypeID, TypeID);
	CC_SYNTHESIZE(uint32_t, m_uNum, Num);
	CC_SYNTHESIZE(uint16_t, m_nShareType, ShareType);
	CC_SYNTHESIZE(uint8_t, m_uRank, Rank);
	void onCommitClicked(CCObject* pSender);
	void setTarget(CCObject *target, SEL_MenuHandler callback, SEL_MenuHandler onceMore = NULL);
	void onEnterTransitionDidFinish();
	void onOnceMoreClicked(CCObject* pSender);
	void onTenthMoreClicked(CCObject* pSender);
	void onPassClicked(CCObject* pSender);
	void onNextClicked(CCObject* pSender);
	virtual void onExit();
	void openedCallBack(void);
	void setProp();
    void toPlayAnimation();
    void restTouch();
private:
	bool isSet;
	CCBAnimationManager *m_pAnimation;
	CCObject *m_pTarget;        //按钮回调消息处理
	SEL_MenuHandler m_pMenuCall; //回调函数
	SEL_MenuHandler m_pMenuCallOnceMore;
	CCNode*             m_pNodeCard;
	CCNode*             m_pNodeIcon[REWARD_TEN_COUNT];
	CCArray*            m_ValueArray;
	CCNode*             m_pCommit;
	CCNode*             m_pOnceMore;
	CCNode*             m_pTenthMore;
	CCNode*             m_pNext;
	CCNode*             m_pPass;
	CCNode*             m_pVisibleNode2;
    CCNode*             m_pNodeTutorial;
    CCLabelTTF* m_pTTFName;
    CCSprite*           m_pBg;
    CCSprite*           m_pBg2;
    CCSprite* m_pStar[MAX_GER_STAR];
    CCLayerColor* m_pLayerBg;
    CCControlButton* m_pBtn;
	int index;
    int tutorialTag;
    bool isReward;
    bool isOnlyShow;
	int m_nStar;
};

#endif /* defined(__ProjectMB__MB_LayerRewardOne__) */
