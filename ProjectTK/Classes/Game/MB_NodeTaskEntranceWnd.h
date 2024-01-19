//
//  MB_NodeTaskEntranceWnd.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_NodeTaskEntranceWnd__
#define __ProjectMB__MB_NodeTaskEntranceWnd__

//#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_FunctionEntranceWnd.h"
class MB_NodeTaskEntranceWnd:public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeTaskEntranceWnd();
    ~MB_NodeTaskEntranceWnd();
    virtual void onResetWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool init();
    CREATE_FUNC(MB_NodeTaskEntranceWnd);
protected:
    void onTaskEntranceClicked(CCObject* pSender);
protected:
    CCLabelTTF*     m_pEntryName;
    CCNode*         m_pNodeFlag;
    CCLabelTTF*         m_pNodeShowNumber;
    CCParticleSystemQuad*   m_pParticlesEffect;
};

class MB_NodeTaskEntranceWndEx:public MB_FunctionEntranceWnd
{
public:
    bool setDataSource(CCFunctionDataSource* pDataSource);
    
};

#include "MB_NodeHoverEntry.h"
class MB_NodeTaskEntry:public MB_NodeHoverEntry
{
public:
    MB_NodeTaskEntry();
    ~MB_NodeTaskEntry();
    virtual void onResetWnd();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
};

#endif /* defined(__ProjectMB__MB_NodeTaskEntranceWnd__) */
