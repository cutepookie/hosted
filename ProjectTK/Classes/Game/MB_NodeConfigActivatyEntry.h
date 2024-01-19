//
//  MB_NodeConfigActivatyEntry.h
//  ProjectPM
//
//  Created by cri-mac on 14-6-12.
//
//

#ifndef __ProjectMB__MB_NodeConfigActivatyEntry__
#define __ProjectMB__MB_NodeConfigActivatyEntry__
#include "MB_NodeSubActivatyEntry.h"

class MB_NodeConfigActivatyEntry:public MB_NodeSubActivatyEntry
{
public:
    MB_NodeConfigActivatyEntry(int eventID);
    ~MB_NodeConfigActivatyEntry();
    bool init();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    void onEntranceClicked(CCObject* pSender);
protected:
    int m_nEventID;
};

#endif /* defined(__ProjectMB__MB_NodeConfigActivatyEntry__) */
