//
//  MB_ServerData.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef ProjectMB_MB_ServerData_h
#define ProjectMB_MB_ServerData_h
#include "cocos2d.h"
USING_NS_CC;

class MB_MsgBuffer;
class MB_ServerData:public CCObject
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket) = 0;
};

#endif
