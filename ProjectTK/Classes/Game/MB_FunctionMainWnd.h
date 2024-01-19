//
//  MB_FunctionMainWnd.h
//  ProjectPM
//
//  Created by WenYong on 14-3-24.
//
//

#ifndef __ProjectMB__MB_FunctionMainWnd__
#define __ProjectMB__MB_FunctionMainWnd__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
class MB_FunctionMainWnd:public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    // must be implement the interface by create a new function;
    // the temp implement is used to make it easy to reconstruction function
    // by inherit this class 
    MB_FunctionMainWnd();
    ~MB_FunctionMainWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource){return true;}
    static void setRoleInfoPanelVisable(bool bVisable);
    static bool getRoleInfoPanelVisable();
protected:
};
#endif /* defined(__ProjectMB__MB_FunctionMainWnd__) */
