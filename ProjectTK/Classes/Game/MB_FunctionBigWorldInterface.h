//
//  MB_FunctionBigWorldInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-5-13.
//
//

#ifndef __ProjectMB__MB_FunctionBigWorldInterface__
#define __ProjectMB__MB_FunctionBigWorldInterface__

#include "MB_FunctionModule.h"

class MB_FunctionBigWorldInterface:public NSGameFunction::CCFunctionInterface
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onEntryClicked(CCObject* pSender);
    virtual void onLoadingScene();
};
#endif /* defined(__ProjectMB__MB_FunctionBigWorldInterface__) */
