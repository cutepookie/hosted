//
//  MB_NodeFriendEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_NodeFriendEntry__
#define __ProjectMB__MB_NodeFriendEntry__

#include "MB_NodeCommandEntrance.h"

class MB_NodeFriendEntry:public MB_NodeCommandEntrance
{
public:
    MB_NodeFriendEntry();
    virtual ~MB_NodeFriendEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onResetWnd();
};

#endif /* defined(__ProjectMB__MB_NodeFriendEntry__) */
