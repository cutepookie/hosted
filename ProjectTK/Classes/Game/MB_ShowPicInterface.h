//
//  MB_ShowPicInterface.h
//  ProjectPM
//
//  Created by chk on 14-4-2.
//
//

#ifndef __ProjectMB__MB_ShowPicInterface__
#define __ProjectMB__MB_ShowPicInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"


class MB_ShowPicInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_ShowPicInterface();
    ~MB_ShowPicInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onLoadingScene();
    virtual void onEntryClicked(CCObject* pSender);
};

#include "MB_FunctionEntranceWnd.h"
class MB_NodeShowPicEntry:public MB_FunctionEntranceWnd
{
public:
    MB_NodeShowPicEntry();
    ~MB_NodeShowPicEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
private:
};

#endif /* defined(__ProjectMB__MB_ShowPicInterface__) */
