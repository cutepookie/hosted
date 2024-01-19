//
//  MB_AdventureEntranceWnd.h
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#ifndef __ProjectMB__MB_AdventureEntranceWnd__
#define __ProjectMB__MB_AdventureEntranceWnd__

#include "MB_NodeCommandEntrance.h"

class MB_AdventureEntry;
class MB_AdventureEntranceWnd : public MB_NodeCommandEntrance
{
    friend class MB_AdventureEntry;
public:
    MB_AdventureEntranceWnd();
    ~MB_AdventureEntranceWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual void onEntranceClicked(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_AdventureEntranceWnd__) */
