//
//  MB_LayerFriendFightResult.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-17.
//
//

#ifndef __ProjectMB__MB_LayerFriendFightResult__
#define __ProjectMB__MB_LayerFriendFightResult__


#include "MB_ResWindow.h"

class MB_LayerFriendFightResult : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    MB_LayerFriendFightResult();
    virtual ~MB_LayerFriendFightResult();
    virtual void onResetWnd();
    static MB_LayerFriendFightResult* create(bool isWin,int coin,int reputation);
    virtual bool init(bool isWin,int coin,int reputation);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

protected:
    void onCompareClicked(CCObject* pSender);
    void onBackClicked(CCObject* pSender);
private:
    CCLabelBMFont*	m_pTTFReputation;
    CCLabelBMFont*	m_pTTFCoin;
    int m_nCoin;
    int m_nReputation;
    CCNode* m_pSpr1;
    CCNode* m_pSpr2;
};

#endif /* defined(__ProjectMB__MB_LayerFriendFightResult__) */
