//
//  MB_NodeRewardUnit.h
//  ProjectMB
//
//  Created by yuanwugang on 14-8-29.
//
//

#ifndef __ProjectMB__MB_NodeRewardUnit__
#define __ProjectMB__MB_NodeRewardUnit__

#include "Game.h"

class MB_NodeRewardUnit:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    static MB_NodeRewardUnit* create(uint16_t nTID,uint16_t num = 1);
    MB_NodeRewardUnit();
    virtual ~MB_NodeRewardUnit();
    virtual bool init(uint16_t nTID,uint16_t num = 1);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    

private:
    CCLabelTTF*         m_pItemName;
    CCSprite*           m_pItemIcon;
    CCSprite*           m_pItemFrame;
    uint16_t            m_nTid;
    uint16_t            m_nNum;
};

#endif /* defined(__ProjectMB__MB_NodeRewardUnit__) */
