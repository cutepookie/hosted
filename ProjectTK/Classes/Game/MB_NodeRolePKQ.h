//
//  MB_NodeRolePKQ.h
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#ifndef __ProjectMB__MB_NodeRolePKQ__
#define __ProjectMB__MB_NodeRolePKQ__

#include "MB_ResWindow.h"

class MB_NodeRolePKQ : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    static MB_NodeRolePKQ* create(int index);
    MB_NodeRolePKQ();
    virtual ~MB_NodeRolePKQ();
    virtual void onResetWnd();
    bool init(int index);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void run();
    virtual void jump();
    virtual CCNode* loadResource(const char* pName);
    bool canJump(){return m_bCanJump;}
    void setSprFilpX(bool b);
        bool isSprFlipX();
    virtual void onExit();
protected:
    void onAnimationFinished();
    void recoveryJump();
    
private:
    bool m_bCanJump;
    CCSprite* m_pSpr;
    CCNode*	m_pNodeSize;
    CCBAnimationManager*    m_pAnimationMgr;
};
#endif /* defined(__ProjectMB__MB_NodeRolePKQ__) */
