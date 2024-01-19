//
//  MB_DailyEntry.h
//  ProjectPM
//
//  Created by cri-mac on 14-6-6.
//
//

#ifndef __ProjectMB__MB_DailyEntry__
#define __ProjectMB__MB_DailyEntry__


#include "MB_NodeHoverEntry.h"

class MB_DailyEntry:public MB_NodeHoverEntry
{
public:
    MB_DailyEntry();
    ~MB_DailyEntry();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};

#endif /* defined(__ProjectMB__MB_DailyEntry__) */
