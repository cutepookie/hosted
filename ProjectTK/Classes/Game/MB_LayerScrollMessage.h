//
//  MB_LayerScrollMessage.h
//  ProjectMB
//
//  Create by wenyong on 10/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerScrollMessage__
#define __ProjectMB__MB_LayerScrollMessage__

#include "MB_ResWindow.h"

class MB_LayerScrollMessage : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_LayerScrollMessage);
	MB_LayerScrollMessage();
	virtual ~MB_LayerScrollMessage();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onInitialized();
    virtual void setMessage(const char* p);
    virtual void setCallBack(CCObject* pTarget,SEL_MenuHandler hander);
protected:
    void onConfirmClicked(CCObject* pSender);
    void onBackClicked(CCObject* pSender);
    void onConfirmClicked2(CCObject* pSender);
private:
    CCLabelTTF*	text_message;
    CCControlButton*	m_onOk;
    CCControlButton*	m_onCancel;
    CCControlButton*	m_onOk2;
    CCNode*	m_pScrollNotice;
    CCLabelTTF*         m_pLabel;
    CCLabelTTF*         m_pScrollTTF;
    CCObject*           m_pTarget;
    SEL_MenuHandler    m_pHandler;
    CCScrollView*       m_pView;
};
#endif /* defined(__ProjectMB__MB_LayerScrollMessage__) */
