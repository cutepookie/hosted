//
//  MB_LayerPerfectRaceRule.h
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#ifndef __ProjectMB__MB_LayerPerfectRaceRule__
#define __ProjectMB__MB_LayerPerfectRaceRule__

#include "MB_ResWindow.h"
class RichText;
class MB_LayerPerfectRaceRule:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    MB_LayerPerfectRaceRule();
    ~MB_LayerPerfectRaceRule();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setRuleString(const char* pString);
    const std::string& getRuleString();
    CREATE_FUNC(MB_LayerPerfectRaceRule);
protected:
    void onBackClicked(CCObject* pSender);
    
private:
    RichText*    m_pRichBox;
    CCNode*     m_pNodeRule;
    static std::string m_szRule;
    CCScrollView* pScrollView;
};

#endif /* defined(__ProjectMB__MB_LayerPerfectRaceRule__) */
