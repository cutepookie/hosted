//
//  MB_NodeSubActivatyEntry.h
//  ProjectPM
//
//  Created by chk on 14-4-30.
//
//

#ifndef __ProjectMB__MB_NodeSubActivatyEntry__
#define __ProjectMB__MB_NodeSubActivatyEntry__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"



//子活动入口图标
class MB_ActivatyMainLayer;
class MB_NodeSubActivatyEntry:public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    friend class MB_ActivatyMgr;
public:
    MB_NodeSubActivatyEntry();
    virtual ~MB_NodeSubActivatyEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    virtual void onResetWnd();
    virtual void onInitializedWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setSelect(bool select);
    virtual void onLoadingScene(){};
    bool init();
    
    
    virtual void onEntranceClicked(CCObject* pSender);
    void setMainWnd(MB_ActivatyMainLayer* wnd);
protected:
    void onMsgRecv(CCNode* node, SocketResponse* response);
protected:
    CCLabelBMFont *m_pName;
    CCSprite *m_pIcon;
    CCMenuItemImage *m_pMenuItem;
    CCNode *m_pNodeTre;
    CCLabelTTF *m_pTreNumber;
    CCNode *m_pNodeEffect;
    CCNode* m_pChoose;
    MB_ActivatyMainLayer* m_pMainWnd;
};


#endif /* defined(__ProjectMB__MB_NodeSubActivatyEntry__) */
