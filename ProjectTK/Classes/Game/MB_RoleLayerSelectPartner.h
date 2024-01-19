//
//  MB_RoleLayerSelectPartner.h
//  ProjectMB
//
//  Create by wenyong on 22/1/2015.
//
//
#ifndef __ProjectMB__MB_RoleLayerSelectPartner__
#define __ProjectMB__MB_RoleLayerSelectPartner__

#include "MB_ResWindow.h"

class MB_RoleLayerSelectPartner : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_RoleLayerSelectPartner);
	MB_RoleLayerSelectPartner();
	virtual ~MB_RoleLayerSelectPartner();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual CCNode* loadResource(const char* pName);
protected:
    void onCloseClick(CCObject* pSender);
    void onLeftClicked(CCObject* pSender);
    void onRightClicked(CCObject* pSender);
    void onEnterClicked(CCObject* pSender);
    void selectPartner1();
    void selectPartner2();
    void selectPartner3();
    void reset();
    bool loadConfig();
    void runAnimation();
    void animationCallBack(CCNode* pNode);
private:
    CCNode*	m_pNodePartner1;
    CCNode*	m_pNodePartner2;
    CCNode*	m_pNodePartner3;
    CCMenuItemImage*	m_pMenuItemImageLeft;
    CCMenuItemImage*	m_pMenuItemImageRight;
    CCBAnimationManager*m_pAnimation;
    int     m_nSelectType;
    int     m_pInitMonster[3];
};
#endif /* defined(__ProjectMB__MB_RoleLayerSelectPartner__) */
