//
//  MB_LayerRewardMoreCard.h
//  ProjectPM
//
//  Create by WenYong on 24/7/2014.
//
//
#ifndef __ProjectMB__MB_LayerRewardMoreCard__
#define __ProjectMB__MB_LayerRewardMoreCard__

#include "MB_NodeItemBook.h"

// this layer should be add to parent with addChild();
class MB_LayerRewardMoreCard : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerRewardMoreCard* create(CCArray* pArray);
	MB_LayerRewardMoreCard();
	virtual ~MB_LayerRewardMoreCard();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setRewardData(CCArray* pArray);
protected:
    void onCommitClicked(CCObject* pSender);
private:
    CCNode*	m_pRewardContainer;
    CCScrollView*   m_pScrollView;
};

class MB_LayerRewardCardContainer : public MB_LayerRewardContainer
{
public:
    static MB_LayerRewardCardContainer* create(CCArray* pArray);
    virtual bool init(CCArray* valueArray);
};
#endif /* defined(__ProjectMB__MB_LayerRewardMoreCard__) */
