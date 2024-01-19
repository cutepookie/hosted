//
//  MB_ParsingReward.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#ifndef __ProjectMB__MB_ParsingReward__
#define __ProjectMB__MB_ParsingReward__
#include "MB_MsgBuffer.h"
#include "MB_ServerData.h"
#include "MB_ItemData.h"

class MB_ParsingReward:public MB_ServerData
{
    MB_ParsingReward();
public:
    
    ~MB_ParsingReward();
    static MB_ParsingReward* create(MB_MsgBuffer *recv);
    virtual bool read(MB_MsgBuffer* recvPacket);
    CCArray* getRewardArray();
private:
    bool init(MB_MsgBuffer *recv);    
    CCArray* m_pArray;
};

#endif /* defined(__ProjectMB__MB_ParsingReward__) */
