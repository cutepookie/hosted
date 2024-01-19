//
//  MB_NodeBigWorldEntry.h
//  ProjectPM
//
//  Created by CRIMOON0073 on 14-7-17.
//
//

#ifndef __ProjectMB__MB_NodeBigWorldEntry__
#define __ProjectMB__MB_NodeBigWorldEntry__

#include "MB_NodeEntryUint.h"

class MB_NodeBigWorldEntry:public MB_NodeEntryUint
{
public:
    MB_NodeBigWorldEntry();
    ~MB_NodeBigWorldEntry();
    static MB_NodeBigWorldEntry* create();
    virtual void goFunction();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource){return true;}
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
};

#endif /* defined(__ProjectMB__MB_NodeBigWorldEntry__) */
