//
//  MB_NodeBigWorldEntry.cpp
//  ProjectPM
//
//  Created by CRIMOON0073 on 14-7-17.
//
//

#include "MB_NodeBigWorldEntry.h"
#include "MB_FunctionModule.h"


MB_NodeBigWorldEntry::MB_NodeBigWorldEntry()
{
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_NodeBigWorldEntry);
}

MB_NodeBigWorldEntry::~MB_NodeBigWorldEntry()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
}
MB_NodeBigWorldEntry* MB_NodeBigWorldEntry::create()
{
    MB_NodeBigWorldEntry* pNode = new MB_NodeBigWorldEntry;
    pNode->setFunctionType(kFunctionBigWorld);
    if (pNode->init())
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_RELEASE(pNode);
    return NULL;
}

void MB_NodeBigWorldEntry::goFunction()
{
    if (m_bEnable)
    {
        MB_FunctionMgr::getInstance()->goFunction(m_nType, this);
    }
    else
    {
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(m_nType);
        if (pItem)
        {
            char buff[64] = {};
            sprintf(buff,"%s将在%d级开放",pItem->getFunctionName().c_str(),pItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(buff);
        }
    }
}

void MB_NodeBigWorldEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == SC_ROLE_UPDATE_LEVEL)
    {
        onResetWnd();
    }
}