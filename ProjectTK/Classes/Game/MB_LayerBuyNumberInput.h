//
//  MB_LayerBuyNumberInput.h
//  ProjectMB
//
//  Create by chenhongkun on 1/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerBuyNumberInput__
#define __ProjectMB__MB_LayerBuyNumberInput__

#include "MB_ResWindow.h"

class BuyNumberInputDelegate
{
public:
    virtual void onNumberInputed(int num) = 0;
};

class MB_LayerBuyNumberInput : public MB_ResWindow,public CCBSelectorResolver,public CCBMemberVariableAssigner
{
public:
	MB_LayerBuyNumberInput();
	virtual ~MB_LayerBuyNumberInput();
    static MB_LayerBuyNumberInput* create(BuyNumberInputDelegate* pDelegate = NULL);
	virtual void onResetWnd();
	virtual bool init();
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
protected:
    void onCloseClick(CCObject* pSender);
    void onClickedAdd(CCObject* pSender);
    void onClickedSubtract(CCObject* pSender);
    void onClickedSure(CCObject* pSender);
private:
    CCLabelBMFont* m_pLabelCount;
    CC_SYNTHESIZE(BuyNumberInputDelegate*, m_pDelegate, Delegate);
    int m_nNum;
};
#endif /* defined(__ProjectMB__MB_LayerBuyNumberInput__) */
