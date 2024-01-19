//
//  MB_EmailInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#ifndef __ProjectMB__MB_EmailInterface__
#define __ProjectMB__MB_EmailInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_EmailInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
};

#endif /* defined(__ProjectMB__MB_EmailInterface__) */
