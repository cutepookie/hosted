

#ifndef __ProjectMB__MB_NodeYaoLingDuiWu__
#define __ProjectMB__MB_NodeYaoLingDuiWu__

#include "Game.h"
class MB_LayerGuard;
class MB_NodeYaoLingDuiWu: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeYaoLingDuiWu(int index);
    ~MB_NodeYaoLingDuiWu();
    
    static MB_NodeYaoLingDuiWu *create(int index);

    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool init();
    void onClickYaoLing(CCObject * pSender);
    void setPetID();
    MB_LayerGuard* m_pLg;
    CCNode* m_pSelectSpr;
    CCNode* m_pRoleIcon;
private:
    int m_nIndex;
};
#endif /* defined(__ProjectMB__MB_NodeYaoLingDuiWu__) */
