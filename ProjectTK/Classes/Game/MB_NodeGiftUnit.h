//
//  MB_NodeGiftUnit.h
//  ProjectMB
//
//  Create by wenyong on 17/12/2014.
//
//
#ifndef __ProjectMB__MB_NodeGiftUnit__
#define __ProjectMB__MB_NodeGiftUnit__

#include "MB_ResWindow.h"
#include "MB_GiftsProtocol.h"
class MB_NodeGiftUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver,public MB_NodeItemDelegate
{
    MB_NodeGiftUnit();
public:
	virtual ~MB_NodeGiftUnit();
    
    static MB_NodeGiftUnit* create(MB_DailyRewrd*);
    static CCSize getUnitSize();
    
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void onCommitClicked(CCObject* pSender);
    void addItem(CCArray* pReward);
    void onClicked(MB_NodeItem* pItem);
private:
    CCNode*	size;
    CCLabelTTF*	m_pLabelNeedValue;
    CCControlButton*	m_pBtGive;
    CCNode* m_pNodePos;
    MB_DailyRewrd* m_pData;
    CCNode* m_pState;
};
#endif /* defined(__ProjectMB__MB_NodeGiftUnit__) */
