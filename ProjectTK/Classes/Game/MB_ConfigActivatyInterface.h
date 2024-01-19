//
//  MB_ConfigActivatyInterface.h
//  ProjectPM
//
//  Created by cri-mac on 14-6-12.
//
//

#ifndef __ProjectMB__MB_ConfigActivatyInterface__
#define __ProjectMB__MB_ConfigActivatyInterface__

#include "MB_CommandActivaty.h"

class MB_ConfigActivatyInterface:public MB_CommandActivaty
{
    virtual MB_ResWindow* createEntryDialog(){return NULL;}
    virtual MB_ResWindow* createFunctionDialog(){return NULL;}
public:
    virtual MB_ResWindow* createEntryDialog(int eventID);
    virtual MB_ResWindow* createFunctionDialog(int eventID);
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
};

#endif /* defined(__ProjectMB__MB_ConfigActivatyInterface__) */
