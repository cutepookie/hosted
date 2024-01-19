//
//  MB_TrainerTroveProtocol.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#include "MB_TrainerTroveProtocol.h"
#include "MB_MsgBuffer.h"


MB_BattleCoinData::MB_BattleCoinData()
{
    m_uTimes = 0;
    m_uCoolDown = 0;
}

bool MB_BattleCoinData::read(MB_MsgBuffer *pRecv)
{
    pRecv->readU16(&m_uTimes);
    pRecv->readU32(&m_uCoolDown);
    return true;
}