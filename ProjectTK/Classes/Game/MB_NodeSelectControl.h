//
//  MB_NodeSelectControl.h
//  ProjectPM
//
//  Create by WenYong on 22/6/2014.
//
//
#ifndef __ProjectMB__MB_NodeSelectControl__
#define __ProjectMB__MB_NodeSelectControl__

#include "MB_ResWindow.h"

class MB_ControlEventDelegate
{
public:
    virtual void onControlClicked(CCObject* pControl)=0;
};

class MB_NodeSelectControl : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeSelectControl();
	virtual ~MB_NodeSelectControl();
    CREATE_FUNC(MB_NodeSelectControl);
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    bool    getSelected()const;
    bool    select();
    bool    unselect();
    void    setText(const char* pText);
protected:
    void onButtonClicked(CCObject* pSender);
    CCMenuItemImage*	m_pSelectFlag;
protected:
    CCSprite* m_pRoleIcon;
    CCLabelTTF*         m_pText;
    CCLabelBMFont*         m_pTextBMF;
    bool                m_bSelected;
    CCSprite* m_pIconFrame;
};

class MB_NodeSelectCoin:public MB_NodeSelectControl
{
public:
    CREATE_FUNC(MB_NodeSelectCoin);
    virtual bool init();
};

class MB_NodeSelectPlayer:public MB_NodeSelectControl
{
public:
    CREATE_FUNC(MB_NodeSelectPlayer);
    void    setHeadID(bool isMale,int roleID, int nTitle);
};

typedef MB_NodeSelectControl MB_NodeSelectButton;
#endif /* defined(__ProjectMB__MB_NodeSelectControl__) */
