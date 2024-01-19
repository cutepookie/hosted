//
//  MB_NodeFormulaUnit.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_NodeFormulaUnit__
#define __ProjectMB__MB_NodeFormulaUnit__

#include "Game.h"

class MB_NodeFormulaUnit:public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver
{
public:
    static MB_NodeFormulaUnit* create(uint16_t nComposeID);
    MB_NodeFormulaUnit();
    virtual ~MB_NodeFormulaUnit();
    virtual bool init(uint16_t nComposeID);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void onFormulaClicked(CCObject* pObject);
    void setComplateStatus(bool bStatus);
private:
    CCNode*             m_pComplateNode;
    CCLabelTTF*         m_pItemName;
    CCSprite*           m_pItemIcon;
    CCSprite*           m_pBgFrame;
    uint16_t            m_nType;
    CC_SYNTHESIZE_READONLY(uint16_t, m_nComposeID, ComposeID);
    CCNode* m_pSpriteDebris;
};
#endif /* defined(__ProjectMB__MB_NodeFormulaUnit__) */
