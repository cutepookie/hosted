//
//  MB_NodeKingEntry.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#include "MB_NodeKingEntry.h"
#include "MB_FunctionKingInterface.h"
#include "MB_KingProtocol.h"
#include "MB_DefineProto.h"

MB_NodeKingEntry::MB_NodeKingEntry()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MB_NodeKingEntry::refresh), open_status_notify.c_str(), this);
}
MB_NodeKingEntry::~MB_NodeKingEntry()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, open_status_notify.c_str());
}
bool MB_NodeKingEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_FunctionKingInterface*>(pDataSource);
    return m_pDataSource != NULL;

}
void MB_NodeKingEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
}

void MB_NodeKingEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    dirty();
}

void MB_NodeKingEntry::refresh(CCObject*)
{
    dirty();
}


