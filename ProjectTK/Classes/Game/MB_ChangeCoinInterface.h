//
//  MB_ChangeCoinInterface.h
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//

#ifndef __ProjectMB__MB_ChangeCoinInterface__
#define __ProjectMB__MB_ChangeCoinInterface__


#include "MB_CommandActivaty.h"
#include "MB_LayerEventChangeCoin.h"
//招財
class MB_ChangeCoinInterface:public MB_CommandActivaty
{
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onDayPassed();
};

#endif /* defined(__ProjectMB__MB_ChangeCoinInterface__) */
