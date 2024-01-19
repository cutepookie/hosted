//
//  MB_LayerResultChangeCoin.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#ifndef __ProjectMB__MB_LayerResultChangeCoin__
#define __ProjectMB__MB_LayerResultChangeCoin__

#include "MB_ResWindow.h"
#include "Game.h"
class MB_LayerResultChangeCoin : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerResultChangeCoin * create(int rewardCoin,int addCoin);
    bool init(int rewardCoin,int addCoin);
    
    MB_LayerResultChangeCoin();
    virtual ~MB_LayerResultChangeCoin();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void onBackClick(CCObject* pSender);
    void animationOver();
protected:
    CCLabelBMFont*	m_pAddCoinLabel;
    CCLabelBMFont*	m_pCoinLabel;
    bool m_bClickedBack;
};


#endif /* defined(__ProjectMB__MB_LayerResultChangeCoin__) */
