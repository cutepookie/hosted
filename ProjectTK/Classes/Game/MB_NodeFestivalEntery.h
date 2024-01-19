//
//  MB_NodeFestivalEntery.h
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#ifndef __ProjectMB__MB_NodeFestivalEntery__
#define __ProjectMB__MB_NodeFestivalEntery__

#include "MB_FunctionEntery2ActivatyEntery.h"

class MB_NodeFestivalEntery : public MB_FunctionEntery2ActivatyEntery
{
public:
    MB_NodeFestivalEntery();
    virtual ~MB_NodeFestivalEntery();
private:
    virtual void onEntranceClicked(CCObject* pSender);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
};

#endif /* defined(__ProjectMB__MB_NodeFestivalEntery__) */
