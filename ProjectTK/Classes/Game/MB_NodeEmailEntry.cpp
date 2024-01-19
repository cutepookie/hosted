//
//  MB_NodeEmailEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#include "MB_NodeEmailEntry.h"
#include "MB_EmailInterface.h"
#include "Game.h"
#include "MB_MailData.h"
MB_NodeEmailEntry::MB_NodeEmailEntry()
{
    SOCKET_MSG_REGIST(SC_MAIL_UNREAD_NUM, MB_NodeEmailEntry);
}
MB_NodeEmailEntry::~MB_NodeEmailEntry()
{
    SOCKET_MSG_UNREGIST(SC_MAIL_UNREAD_NUM);
}

void MB_NodeEmailEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);

    if (Msg == SC_MAIL_UNREAD_NUM)
    {
        dirty();
    }
}


void MB_NodeEmailEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
    bool bShow = false;
    if(MailMgr->queryMailUnRead(kmMailsTable_Preson)>0
       || MailMgr->queryMailUnRead(kmMailsTable_System) >0)
    {
        bShow = true;
        m_pFlagNode2->setVisible(true);
        int nCount = MailMgr->queryMailUnRead(kmMailsTable_System) + MailMgr->queryMailUnRead(kmMailsTable_Preson);
        if (nCount>99) {
            m_pFlag2->setString("!");
        }else
        {
            char buff[25] = {};
            sprintf(buff, "%d",nCount);
            m_pFlag2->setString(buff);
        }
    }
}
