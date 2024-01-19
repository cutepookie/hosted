//
//  MB_NodeItemBuchong.h
//  ProjectPM
//
//  Create by WenYong on 9/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeItemBuchong__
#define __ProjectMB__MB_NodeItemBuchong__

#include "MB_ResWindow.h"

class MB_NodeItemBuchong : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeItemBuchong();
    static MB_NodeItemBuchong* create(uint64_t nItemUid);
	virtual ~MB_NodeItemBuchong();
	virtual void onResetWnd();
	virtual bool init(uint64_t nItemUid);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static CCSize getNodeSize();
protected:
    void onUseItemClicked(CCObject* pSender);
private:
    uint64_t    m_nItemUID;
    CCNode*     m_pItemIcon;
    CCLabelTTF*	    m_pItemName;
    CCLabelTTF*     m_pItemDescription;
    CCLabelTTF*     m_pItemCanUseTimes;
    CCNode*     m_pNodeSize;
};
#endif /* defined(__ProjectMB__MB_NodeItemBuchong__) */
