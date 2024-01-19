//
//  MB_NodeGiftEntry.h
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#ifndef __ProjectMB__MB_NodeGiftEntry__
#define __ProjectMB__MB_NodeGiftEntry__
#include "MB_NodeHoverEntry.h"

class MB_NodeGiftEntry:public MB_NodeHoverEntry
{
public:
    MB_NodeGiftEntry();
    ~MB_NodeGiftEntry();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onEntranceClicked(CCObject* pSender);
    void onResetWnd();
    bool init();
    void tick(float dt);
};

#endif /* defined(__ProjectMB__MB_NodeGiftEntry__) */
