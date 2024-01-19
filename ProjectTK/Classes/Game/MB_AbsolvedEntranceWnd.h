//
//  MB_AbsolvedEntranceWnd.h
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#ifndef __ProjectMB__MB_AbsolvedEntranceWnd__
#define __ProjectMB__MB_AbsolvedEntranceWnd__

#include "MB_NodeCommandEntrance.h"

class MB_AbsolvedEntry;

class MB_AbsolvedEntranceWnd : public MB_NodeCommandEntrance
{
    friend class MB_Championship;   
public:
    MB_AbsolvedEntranceWnd();
    ~MB_AbsolvedEntranceWnd();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void onEntranceClicked(CCObject* pSender);
    void finish2();
    CCNode* sceneNode;
};




#endif /* defined(__ProjectMB__MB_AbsolvedEntranceWnd__) */
