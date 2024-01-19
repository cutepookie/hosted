//
//  MB_NodeCallcardUnit.h
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#ifndef __ProjectMB__MB_NodeCallcardUnit__
#define __ProjectMB__MB_NodeCallcardUnit__

#include "MB_ResWindow.h"
class MB_LayerToyShopMain;
class MB_NodeCallcardUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeCallcardUnit();
	virtual ~MB_NodeCallcardUnit();
    
    static MB_NodeCallcardUnit* create();
    
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){};
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    CCLabelBMFont* m_pNeedCallTimesLabel;
    CCLabelBMFont* m_pCostLabels[3];
    CCLabelBMFont* m_pslfCallBallCountLabel;//召唤球数量文本
    MB_LayerToyShopMain* layerToyShopMain;
protected:
    void onCallElfClicked(CCObject* pSender);

        CCNode* m_pShielding;
};


#endif /* defined(__ProjectMB__MB_NodeCallcardUnit__) */
