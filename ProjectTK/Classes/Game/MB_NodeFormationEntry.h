//
//  MB_NodeFormationEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#ifndef __ProjectMB__MB_NodeFormationEntry__
#define __ProjectMB__MB_NodeFormationEntry__

#include "MB_NodeCommandEntrance.h"

class MB_NodeFormationEntry:public MB_NodeCommandEntrance
{
public:
    MB_NodeFormationEntry();
    ~MB_NodeFormationEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual bool init();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
};

#endif /* defined(__ProjectMB__MB_NodeFormationEntry__) */
