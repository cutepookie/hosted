
#ifndef ProjectMB_MB_LayerRoleLevelUp_h
#define ProjectMB_MB_LayerRoleLevelUp_h

#include "Game.h"
class MB_LayerRoleLevelUp: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_LayerRoleLevelUp();
    ~MB_LayerRoleLevelUp();    
    static MB_LayerRoleLevelUp *create(int preLevel,int predis,int preenergy);
    virtual bool init(int preLevel,int predis,int preenergy);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onConfirmClicked(CCObject *);
    void goReguest(CCObject *);
    void goCancel(CCObject *);    
    virtual void onEnter();
    void goClose(CCObject *);
    void goCheck();
    void onExit();

private:
    bool m_pHasCheckLevel;
    CCLabelBMFont *m_pPreLevel;
    CCLabelBMFont *m_pNowLevel;
    CCLabelBMFont *m_pPreEnpety;
    CCLabelBMFont *m_pNextEnpety;
    CCLabelBMFont *m_pPreDistime;
    CCLabelBMFont *m_pNowDistime;
    CCControlButton * m_onOk;
    
    bool buttonIsGo[2];
    CCLayer *m_pRegest;
    CCNode *m_pNode;
    CCControlButton* m_pConfirmBtn;
};


#endif
