//
//  MB_MailMsgMgr.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#include "MB_MailMsgMgr.h"
#include "MB_LocalProto.h"
#include "MB_RoleData.h"
#include "platform/CCFileUtils.h"

MB_MailMsgMgr::MB_MailMsgMgr()
{
    m_vNewMsgMap.clear();
}

MB_MailMsgMgr::~MB_MailMsgMgr()
{
    m_vNewMsgMap.clear();
}

MB_SaveMsgFile<MB_MailMsgData>* MB_MailMsgMgr::querlyMsgDataByTargetID(uint32_t uID)
{
    MB_SaveMsgFile<MB_MailMsgData>* pData = MB_SaveMsgFile<MB_MailMsgData>::create(MB_RoleData::getInstance()->getUID(),uID);
    
    return pData;
}

bool MB_MailMsgMgr::deleteMsgDataByTargetID(uint32_t uID)
{
    char path[400];
    sprintf(path,"%sMsgCache/%d/%d.cb",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),MB_RoleData::getInstance()->getUID(),uID);
    return !remove(path);
    
}

MB_MailMsgMgr* MB_MailMsgMgr::m_pThisInstance = NULL;

MB_MailMsgMgr* MB_MailMsgMgr::getInstance()
{
    if (m_pThisInstance == NULL)
    {
        m_pThisInstance = new MB_MailMsgMgr;
    }
    
    return m_pThisInstance;
}

void MB_MailMsgMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pThisInstance);
}