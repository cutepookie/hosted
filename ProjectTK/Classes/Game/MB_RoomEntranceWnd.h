//
//  MB_RoomEntranceWnd.h
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#ifndef __ProjectMB__MB_RoomEntranceWnd__
#define __ProjectMB__MB_RoomEntranceWnd__

#include "MB_NodeCommandEntrance.h"

class MB_AdventureEntry;
class MB_RoomEntranceWnd : public MB_NodeCommandEntrance
{
    friend class MB_AdventureEntry;
public:
    MB_RoomEntranceWnd();
    ~MB_RoomEntranceWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void tick(float dt);
    virtual void onEntranceClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_RoomEntranceWnd__) */
