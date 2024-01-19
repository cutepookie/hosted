//
//  MB_TrainerTroveProtocol.h
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#ifndef __ProjectMB__MB_TrainerTroveProtocol__
#define __ProjectMB__MB_TrainerTroveProtocol__

#include "MB_ServerData.h"
#include "MB_ClientData.h"


#define CS_BATTLE_COIN_INFO     10217
#define SC_BATTLE_COIN_INFO     10218

#define CS_BATTLE_COIN_FIGHT    10219
#define SC_BATTLE_COIN_FIGHT    10220


class MB_BattleCoinData : public MB_ServerData
{
public:
    MB_BattleCoinData();
    virtual bool read(MB_MsgBuffer* pRecv);
    CC_SYNTHESIZE(uint16_t,m_uTimes,Times);
    CC_SYNTHESIZE(uint32_t,m_uCoolDown,CoolDown);
};


#endif /* defined(__ProjectMB__MB_TrainerTroveProtocol__) */
