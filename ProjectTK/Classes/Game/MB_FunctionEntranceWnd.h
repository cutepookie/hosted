//
//  MB_FunctionEntranceWnd.h
//  ProjectPM
//
//  Created by wenyong on 14-3-21.
//
//

#ifndef __ProjectMB__MB_FunctionEntranceWnd__
#define __ProjectMB__MB_FunctionEntranceWnd__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_FunctionEntranceWnd:public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_FunctionEntranceWnd();
    virtual ~MB_FunctionEntranceWnd();
    
    virtual bool init();
    virtual void onResetWnd();
    virtual void onInitializedWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void setEnable();
    virtual void setDisable();
    void setType(int nType){m_nType=nType;onResetWnd();}
    CCMenu*     m_pScroller;
protected:
    
    virtual void onEntranceClicked(CCObject* pSender);
protected:
    int         m_nType;
    CCNode*     m_pFlagNode2;
    CCLabelBMFont* m_pFlag2;
    CCSprite*   m_pSpriteName;
    CCMenuItemImage* m_pItemImage;
    bool        m_bEnable;

};

#endif /* defined(__ProjectMB__MB_FunctionEntranceWnd__) */
