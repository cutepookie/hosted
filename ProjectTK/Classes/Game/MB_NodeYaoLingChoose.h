

#ifndef __ProjectMB__MB_NodeYaoLingChoose__
#define __ProjectMB__MB_NodeYaoLingChoose__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerGuard;
class MB_NodeYaoLingChoose : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_NodeYaoLingChoose();
    ~MB_NodeYaoLingChoose();
    
    static MB_NodeYaoLingChoose* create(uint64_t petUID);
    
    virtual bool init();
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onChooseClicked(CCObject* pSender);
    CCSize getCellSize();
    MB_LayerGuard* m_pLg;
private:
    
    CCLabelBMFont* m_pAttack;
    CCLabelBMFont* m_pHp;
    CCLabelTTF*  m_pRoleName;
    CCNode* m_pNodeSize;
    CCLabelTTF* m_pRoleReputation;
    CCNode*  m_pRoleIcon;
    CCLabelBMFont* m_pLabelLevel;
    uint64_t m_nPetUID;
    CCLabelTTF* m_pTTFGuard;
    CCMenu* m_pScrollmenu;
};

#endif /* defined(__ProjectMB__MB_NodeYaoLingChoose__) */
