//
//  MB_LayerComposeRule.h
//  ProjectPM
//
//  Created by cri-mac on 14-4-16.
//
//

#ifndef __ProjectMB__MB_LayerComposeRule__
#define __ProjectMB__MB_LayerComposeRule__

#include "MB_ResWindow.h"



class MB_LayerComposeRule:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    enum
    {
        eFormulaRule,
        eRandomRule,
    };
public:
    MB_LayerComposeRule();
    virtual ~MB_LayerComposeRule();
    static MB_LayerComposeRule* create(int nType = eFormulaRule);
    virtual bool init(int nType);
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onClosedClicked(CCObject*);
};

#endif /* defined(__ProjectMB__MB_LayerComposeRule__) */
