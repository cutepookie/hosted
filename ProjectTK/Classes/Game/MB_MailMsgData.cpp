//
//  MB_MailMsgData.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#include "MB_MailMsgData.h"
#include "Game.h"


bool MB_MailMsgData::init(MB_XmlNode *pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    m_strTitle = pNode->queryAttributeByName("title")->getCString();
    m_strMsgData = pNode->queryAttributeByName("chat")->getCString();
    m_uTime = pNode->queryAttributeByName("time")->intValue();
    return true;
}

bool MB_MailMsgData::saveEmail(xmlNodePtr ptr)
{
    xmlNewProp(ptr,BAD_CAST"title",BAD_CAST getTitle().c_str());
    xmlNewProp(ptr,BAD_CAST"chat",BAD_CAST getMsgData().c_str());
    xmlNewProp(ptr,BAD_CAST"time",BAD_CAST getTime());
    return true;
}


