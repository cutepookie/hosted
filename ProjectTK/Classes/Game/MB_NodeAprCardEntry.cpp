//
//  MB_NodeAprCardEntry.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#include "MB_NodeAprCardEntry.h"
#include "MB_FunctionAprCardInterface.h"
#include "MB_AprCardProtocol.h"

MB_NodeAprCardEntry::MB_NodeAprCardEntry()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MB_NodeAprCardEntry::refresh), aprcard_status_notify.c_str(), this);
}
MB_NodeAprCardEntry::~MB_NodeAprCardEntry()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, aprcard_status_notify.c_str());
}
bool MB_NodeAprCardEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_FunctionAprCardInterface*>(pDataSource);
    return m_pDataSource != NULL;
}
void MB_NodeAprCardEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
}
void MB_NodeAprCardEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    dirty();
}

void MB_NodeAprCardEntry::refresh(CCObject*)
{
    dirty();
}
