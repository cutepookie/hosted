//
//  MB_NodeBudokanEntry.h
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#ifndef __ProjectMB__MB_NodeBudokanEntry__
#define __ProjectMB__MB_NodeBudokanEntry__
#include "MB_NodeBannerEntry.h"

class MB_NodeBudokanEntry:public MB_NodeBannerEntry
{
public:
    static MB_NodeBudokanEntry* create();
    MB_NodeBudokanEntry();
    ~MB_NodeBudokanEntry();
    
    virtual void onResetWnd();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void UpDataState(float dt);
};

#endif /* defined(__ProjectMB__MB_NodeBudokanEntry__) */
