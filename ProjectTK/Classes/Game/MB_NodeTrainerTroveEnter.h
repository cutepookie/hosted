//
//  MB_NodeTrainerTroveEnter.h
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#ifndef __ProjectMB__MB_NodeTrainerTroveEnter__
#define __ProjectMB__MB_NodeTrainerTroveEnter__

#include "MB_NodeBannerEntry.h"

class MB_NodeTrainerTroveEnter:public MB_NodeBannerEntry
{
public:
    MB_NodeTrainerTroveEnter();
    ~MB_NodeTrainerTroveEnter();
    static MB_NodeTrainerTroveEnter* create();
    void onResetWnd();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
};

#endif /* defined(__ProjectMB__MB_NodeTrainerTroveEnter__) */
