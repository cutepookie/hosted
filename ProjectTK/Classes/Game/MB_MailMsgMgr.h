//
//  MB_MailMsgMgr.h
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#ifndef __ProjectMB__MB_MailMsgMgr__
#define __ProjectMB__MB_MailMsgMgr__

#include "MB_MailMsgData.h"
#include "MB_MailMsgFile.h"

class MB_MailMsgMgr:public CCObject
{
public:
    MB_MailMsgMgr();
    ~MB_MailMsgMgr();
    static MB_MailMsgMgr* getInstance();
    static void destroyInstance();
    bool   readMsgDataByTargetID(uint32_t uID);
    MB_SaveMsgFile<MB_MailMsgData>*  querlyMsgDataByTargetID(uint32_t uID);
    bool   deleteMsgDataByTargetID(uint32_t uID);
private:
    static MB_MailMsgMgr* m_pThisInstance;
    std::map<uint64_t, uint16_t>  m_vNewMsgMap;
};
#endif /* defined(__ProjectMB__MB_MailMsgMgr__) */
