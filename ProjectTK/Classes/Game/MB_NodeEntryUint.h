//
//  MB_NodeEntryUint.h
//  ProjectPM
//
//  Created by CRIMOON0073 on 14-7-17.
//
//

#ifndef __ProjectMB__MB_NodeEntryUint__
#define __ProjectMB__MB_NodeEntryUint__

#include "MB_FunctionEntranceWnd.h"

class MB_NodeEntryUint:public  MB_FunctionEntranceWnd
{
public:
    MB_NodeEntryUint();
    void setFunctionType(int type);
    virtual void onResetWnd();
    virtual void setEnable();
    virtual void setDisable();
protected:
    virtual void onEntranceClicked(CCObject* pSender);
    virtual void goFunction()=0;
protected:
    int m_nType;
};

#endif /* defined(__ProjectMB__MB_NodeEntryUint__) */
