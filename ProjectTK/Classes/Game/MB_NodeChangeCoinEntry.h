//
//  MB_NodeChangeCoinEntry.h
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//

#ifndef __ProjectMB__MB_NodeChangeCoinEntry__
#define __ProjectMB__MB_NodeChangeCoinEntry__

#include "MB_NodeHoverEntry.h"

class MB_ChangeCoinInterface;
class MB_NodeChangeCoinEntry:public MB_NodeHoverEntry
{
    friend class MB_ChangeCoinInterface;
    MB_NodeChangeCoinEntry();
public:
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual bool init();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void onEntranceClicked(CCObject* pSender);
    ~MB_NodeChangeCoinEntry();
};

#endif /* defined(__ProjectMB__MB_NodeChangeCoinEntry__) */
