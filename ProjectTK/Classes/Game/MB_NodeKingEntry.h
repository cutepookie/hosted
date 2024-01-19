//
//  MB_NodeKingEntry.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#ifndef __ProjectMB__MB_NodeKingEntry__
#define __ProjectMB__MB_NodeKingEntry__


#include "MB_NodeHoverEntry.h"

class MB_NodeKingEntry:public MB_NodeHoverEntry
{
public:
    MB_NodeKingEntry();
    ~MB_NodeKingEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void refresh(CCObject*);
private:
};


#endif /* defined(__ProjectMB__MB_NodeKingEntry__) */
