//
//  MB_LayerResultBoss.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#ifndef __ProjectMB__MB_LayerResultBoss__
#define __ProjectMB__MB_LayerResultBoss__

#include "MB_ResWindow.h"
#include "Game.h"
class MB_LayerResultBoss : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerResultBoss * create(int rewardCoin,int rewardreputation,char issuccess,int attack,int resulttype);
    bool init(int rewardCoin,int rewardreputation,char issuccess,int attack);
    
	MB_LayerResultBoss();
	virtual ~MB_LayerResultBoss();
	virtual void onResetWnd();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nResultType, ResultType);
protected:
    void onBackClick(CCObject* pSender);
    void animationOver();
    void goOver();
protected:
    CCLabelBMFont*	m_pExpLabel;
    CCLabelBMFont*	m_pCoinLabel;
    CCLabelBMFont* m_pAttack;
    CCNode*	m_pNodeReward;
    CCBAnimationManager* m_pAnimationMgr;
    bool m_nIsSuccess;
    bool m_bClickedBack;
    CCNode* m_pSpr1;
    CCNode* m_pSpr2;
};


#endif /* defined(__ProjectMB__MB_LayerResultBoss__) */
