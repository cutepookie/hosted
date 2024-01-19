//
//  MB_NodeBackpackEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-2.
//
//

#include "MB_NodeBackpackEntry.h"
#include "MB_BackpackInterface.h"
#include "Game.h"

MB_NodeBackpackEntry::MB_NodeBackpackEntry()
{
    SOCKET_MSG_REGIST(SC_ITEM_UPDATE, MB_NodeBackpackEntry);
    SOCKET_MSG_REGIST(SC_ITEM_DELETE_NOTIFY, MB_NodeBackpackEntry);
    SOCKET_MSG_REGIST(SC_ITEM_NEW,MB_NodeBackpackEntry);
    
}

MB_NodeBackpackEntry::~MB_NodeBackpackEntry()
{
    SOCKET_MSG_UNREGIST(SC_ITEM_UPDATE);
    SOCKET_MSG_UNREGIST(SC_ITEM_DELETE_NOTIFY);
    SOCKET_MSG_UNREGIST(SC_ITEM_NEW);
}

void MB_NodeBackpackEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);

    onResetWnd();
//    this->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFunc::create(this,callfunc_selector(MB_NodeBackpackEntry::onResetWnd))));
}


bool MB_NodeBackpackEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_BackpackInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}

void MB_NodeBackpackEntry::onResetWnd()
{
    MB_NodeCommandEntrance::onResetWnd();
    
    
    
    CCArray* pArray = MB_ItemMgr::getInstance()->getOtherArray();
    MB_ItemData* pTemp = NULL;
    int count = 0;
    
    CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pTemp)
    {
        if (pTemp->getItemType() == kOTHER_BOX)
        {
            count += pTemp->getItemNumber();
        }
    }
    
    pArray = MB_ItemMgr::getInstance()->getItemDebrisArray();
    pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(pArray, MB_ItemData*, pTemp)
    {
        MB_ItemTemplate* templete = MB_ItemMgr::getInstance()->getItemTemplateByID(pTemp->getItemID());
        int n = pTemp->getItemNumber()/templete->getComposeNum();
        if(n > 0)
        {
            count += n;
        }
    }
    
    if (count !=0 )
    {
        setEff(true);
        if (count>99) {
            m_pFlag2->setString("!");
        }else
        {
            char buff[12] = {};
            sprintf(buff, "%d",count);
            m_pFlag2->setString(buff);
        }
    }
    else
    {
        setEff(false);
    }
    
}
