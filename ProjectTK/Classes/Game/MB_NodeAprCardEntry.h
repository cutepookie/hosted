//
//  MB_NodeAprCardEntry.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#ifndef __ProjectMB__MB_NodeAprCardEntry__
#define __ProjectMB__MB_NodeAprCardEntry__

#include "MB_NodeHoverEntry.h"

class MB_NodeAprCardEntry:public MB_NodeHoverEntry
{
public:
    MB_NodeAprCardEntry();
    ~MB_NodeAprCardEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void refresh(CCObject*);
private:
};

#endif /* defined(__ProjectMB__MB_NodeAprCardEntry__) */
