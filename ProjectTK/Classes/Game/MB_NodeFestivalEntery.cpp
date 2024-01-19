//
//  MB_NodeFestivalEntery.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#include "MB_NodeFestivalEntery.h"
#include "MB_FunctionFestival.h"
#include "MB_Message.h"
#include "MB_FestivalProtocol.h"
#include "MB_ClientSocket.h"

void MB_NodeFestivalEntery::onEntranceClicked(CCObject* pSender)
{
    MB_FunctionFestival* pFunction = dynamic_cast<MB_FunctionFestival*>(m_pInterface);
    if (pFunction)
    {
        enter();
    }
}

void MB_NodeFestivalEntery::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{

}

MB_NodeFestivalEntery::MB_NodeFestivalEntery()
{
}

MB_NodeFestivalEntery::~MB_NodeFestivalEntery()
{
}