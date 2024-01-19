//
//  MB_FunctionPveRoot.h
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#ifndef __ProjectMB__MB_FunctionPveRoot__
#define __ProjectMB__MB_FunctionPveRoot__

#include "MB_ResWindow.h"

class MB_FunctionPveMain:public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    MB_FunctionPveMain();
    virtual ~MB_FunctionPveMain();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    CREATE_FUNC(MB_FunctionPveMain);
    void onOpen();
    void onClose();
    void onCloseComplete();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
protected:
    virtual bool initFunctions();
protected:
    CCNode*     m_pNodes[8];
    CCBAnimationManager *m_pAnimation;
    CCNode *m_pCommandList;
    CCNode *m_pScrollsize;
};
#endif /* defined(__ProjectMB__MB_FunctionPveRoot__) */
