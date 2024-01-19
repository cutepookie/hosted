//
//  MB_NodeEmailEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#ifndef __ProjectMB__MB_NodeEmailEntry__
#define __ProjectMB__MB_NodeEmailEntry__

#include "MB_NodeHoverEntry.h"

class MB_NodeEmailEntry:public MB_NodeHoverEntry
{
public:
    MB_NodeEmailEntry();
    ~MB_NodeEmailEntry();
    //virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
};

#endif /* defined(__ProjectMB__MB_NodeEmailEntry__) */
