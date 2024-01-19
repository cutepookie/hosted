//
//  MB_FunctionArenaTip.h
//  ProjectPM
//
//  Created by cri-mac on 14-4-29.
//
//

#ifndef __ProjectMB__MB_FunctionArenaTip__
#define __ProjectMB__MB_FunctionArenaTip__

#include "MB_ResWindow.h"

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"


//沒有用
class MB_FunctionArenaTip:public MB_ResWindow
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
{
public:
    MB_FunctionArenaTip();
    ~MB_FunctionArenaTip();
    virtual bool init(const char* pFile);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onGoFunctionClicked(CCObject *);
    void onCloseClicked(CCObject *);
    void setFunctionInterface(NSGameFunction::CCFunctionInterface* pInterface);
    static MB_FunctionArenaTip* create(const char* pFile);
private:
    NSGameFunction::CCFunctionInterface* m_pInterface;
};

#endif /* defined(__ProjectMB__MB_FunctionArenaTip__) */
