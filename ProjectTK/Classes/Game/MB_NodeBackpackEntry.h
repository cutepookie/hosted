//
//  MB_NodeBackpackEntry.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#ifndef __ProjectMB__MB_NodeBackpackEntry__
#define __ProjectMB__MB_NodeBackpackEntry__

#include "MB_NodeCommandEntrance.h"

class MB_NodeBackpackEntry:public MB_NodeCommandEntrance
{
public:
    MB_NodeBackpackEntry();
	virtual ~MB_NodeBackpackEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};


#endif /* defined(__ProjectMB__MB_NodeBackpackEntry__) */
