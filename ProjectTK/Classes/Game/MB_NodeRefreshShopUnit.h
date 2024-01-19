//
//  MB_NodeRefreshShopUnit.h
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#ifndef __ProjectMB__MB_NodeRefreshShopUnit__
#define __ProjectMB__MB_NodeRefreshShopUnit__

#include "MB_ResWindow.h"

class MB_Treasure;
class MB_NodeRefreshShopUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeRefreshShopUnit();
	virtual ~MB_NodeRefreshShopUnit();
    
    static CCSize getUnitSize();
    static MB_NodeRefreshShopUnit* create(MB_Treasure*);
    
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    virtual void onBuyClicked(CCObject* pSender);
protected:
    CCLabelTTF*	m_pNameTtf;
    CCControlButton*	m_pButBtn;
    CCNode* m_pBuyedBtn;
    CCLabelBMFont*	m_pCostTtf;
    CCNode*	m_pItemIcon;
    CCNode* m_pCellSize;
    CCSprite* m_pMask;
    bool m_bTutorial;
private:
    MB_Treasure* m_pTreasure;
};


#endif /* defined(__ProjectMB__MB_NodeRefreshShopUnit__) */
