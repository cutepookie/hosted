//
//  MB_NodeTrainerTroveEnter.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#include "MB_NodeTrainerTroveEnter.h"
#include "MB_FunctionTrainerTroveInterface.h"
#include "MB_RoleData.h"

MB_NodeTrainerTroveEnter::MB_NodeTrainerTroveEnter()
{
    SOCKET_MSG_REGIST(SC_BATTLE_COIN_INFO,MB_NodeTrainerTroveEnter);
}

MB_NodeTrainerTroveEnter::~MB_NodeTrainerTroveEnter()
{
    SOCKET_MSG_UNREGIST(SC_BATTLE_COIN_INFO);
}

MB_NodeTrainerTroveEnter* MB_NodeTrainerTroveEnter::create()
{
    MB_NodeTrainerTroveEnter* pNode = new MB_NodeTrainerTroveEnter;
    if (pNode && pNode->init())
    {
        pNode->autorelease();
        pNode->setType(kFunctionTrainerTrove);
        return pNode;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}

void MB_NodeTrainerTroveEnter::onResetWnd()
{
    MB_NodeBannerEntry::onResetWnd();
    MB_FunctionTrainerTroveInterface* interface = dynamic_cast<MB_FunctionTrainerTroveInterface*>(m_pDataSource);
    if (m_bEnable && interface)
    {
        showActivities(interface->getFightCount() < MB_RoleData::getInstance()->getMoneyDungeonLimit());
    }
    
}

void MB_NodeTrainerTroveEnter::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    dirty();
}