//
//  MB_LayerFunctionRule.h
//  ProjectPM
//
//  Create by WenYong on 26/7/2014.
//
//
#ifndef __ProjectMB__MB_LayerFunctionRule__
#define __ProjectMB__MB_LayerFunctionRule__

#include "MB_ResWindow.h"

class MB_LayerFunctionRule : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerFunctionRule* create(int nType);
	MB_LayerFunctionRule();
	virtual ~MB_LayerFunctionRule();
	virtual void onResetWnd();
	virtual bool init();
    virtual void setRuleType(int nType);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void onCloseClick(CCObject* pSender);
private:
    CCScale9Sprite*	scale9sprite;
    CCNode*	m_pNodeRule;
};
#endif /* defined(__ProjectMB__MB_LayerFunctionRule__) */
