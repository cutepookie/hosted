//
//  MB_RoomEntry.h
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//探险進入接口

#ifndef __ProjectMB__MB_RoomEntry__
#define __ProjectMB__MB_RoomEntry__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_FunctionModule.h"
class MB_RoomEntry : public NSGameFunction::CCFunctionInterface
{   
public:
    MB_RoomEntry();
    ~MB_RoomEntry();
    
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};

#endif /* defined(__ProjectMB__MB_RoomEntry__) */
