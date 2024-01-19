//
//  MB_MailMsgData.h
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#ifndef __ProjectMB__MB_MailMsgData__
#define __ProjectMB__MB_MailMsgData__


#include "MB_ClientData.h"

#include <libxml/tree.h>

class MB_SaveMsgData : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode) = 0;
    virtual bool saveEmail(xmlNodePtr ptr) = 0;
protected:
};

class MB_MailMsgData:public MB_SaveMsgData
{
public:
    virtual bool init(MB_XmlNode* pNode);
    virtual bool saveEmail(xmlNodePtr ptr);
protected:
    CC_SYNTHESIZE(std::string, m_strTitle, Title);
    CC_SYNTHESIZE(std::string, m_strMsgData, MsgData);
    CC_SYNTHESIZE(uint32_t, m_uTime, Time);                    //发送时间(Unix时间戳)
};

#endif /* defined(__ProjectMB__MB_MailMsgData__) */
