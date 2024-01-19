//
//  MB_NodeMonsterSelect.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#ifndef __ProjectMB__MB_NodeMonsterSelect__
#define __ProjectMB__MB_NodeMonsterSelect__

#include "MB_NodeSelect.h"

class MB_NodeMonsterSelect:public MB_NodeSelect
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:

    MB_NodeMonsterSelect();

    ~MB_NodeMonsterSelect();

    static MB_NodeMonsterSelect* create(uint64_t nUid,uint16_t nType,bool showTutoril = false);
    
    virtual bool init(uint64_t nUid,uint16_t nType);
    
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

protected:
    void onButton1Clicked(CCObject* pSender);
private:
    CCLabelTTF* m_pAttack;
    CCLabelTTF* m_pHp;
    bool m_bShowTutoril;
};

#endif /* defined(__ProjectMB__MB_NodeMonsterSelect__) */
