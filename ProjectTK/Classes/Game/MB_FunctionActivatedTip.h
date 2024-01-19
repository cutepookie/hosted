//
//  MB_FunctionActivatedTip.h
//  ProjectPM
//
//  Created by WenYong on 14-3-31.
//
//

#ifndef __ProjectMB__MB_FunctionActivatedTip__
#define __ProjectMB__MB_FunctionActivatedTip__

#include "MB_ResWindow.h"

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_TutorialMgr.h"
class MB_FunctionActivatedTip:public MB_ResWindow
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
{
public:
    MB_FunctionActivatedTip();
    ~MB_FunctionActivatedTip();
    virtual bool init(const char* pFile);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onGoFunctionClicked(CCObject *);
    void onCloseClicked(CCObject *);
    void setFunctionInterface(NSGameFunction::CCFunctionInterface* pInterface);
    static MB_FunctionActivatedTip* create(const char* pFile);
    
    void onEnter()
    {
        MB_ResWindow::onEnter();
        MB_TutorialMgr::getInstance()->SetModelDilogState("MB_FunctionActivatedTip",true);
    }
    void onExit()
    {
        MB_ResWindow::onExit();
        MB_TutorialMgr::getInstance()->SetModelDilogState("MB_FunctionActivatedTip",false);
    }
private:
    NSGameFunction::CCFunctionInterface* m_pInterface;
};
#endif /* defined(__ProjectMB__MB_FunctionActivatedTip__) */
