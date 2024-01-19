//
//  MB_NodeMailSystem.h
//  ProjectPM
//
//  Create by WenYong on 9/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeMailSystem__
#define __ProjectMB__MB_NodeMailSystem__

#include "MB_ResWindow.h"

class MB_NodeMailSystem : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeMailSystem();
    static MB_NodeMailSystem* create(uint64_t nMailUid);
	virtual ~MB_NodeMailSystem();
	virtual void onResetWnd();
	virtual bool init(uint64_t nMailUid);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static CCSize getNodeSize();
protected:
    void onViewEmailClicked(CCObject* pSender);
    bool check(uint64_t uid);
private:
    uint64_t    m_nMailUID;
    CCNode*     m_pMailTitle;
    CCLabelTTF*	m_pTimeText;
    CCNode*     m_pNodeSize;
};
#endif /* defined(__ProjectMB__MB_NodeMailSystem__) */
