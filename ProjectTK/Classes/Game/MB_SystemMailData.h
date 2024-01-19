//
//  MB_SystemMailData.h
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#ifndef __ProjectMB__MB_SystemMailData__
#define __ProjectMB__MB_SystemMailData__

#include "MB_ClientData.h"

class MB_SystemMailData : public MB_ClientData
{
public:
    virtual bool init(MB_XmlNode* pNode);
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nMailTemplateID, MailTemplateID);
    CC_SYNTHESIZE_READONLY(std::string, m_szTitle, Title);
    CC_SYNTHESIZE_READONLY(std::string, m_szContent, Content);
};

class MB_SystemDataMgr:public CCObject
{
public:
    ~MB_SystemDataMgr();
    static MB_SystemDataMgr* getInstance();
    static void destroyInstance();
    const MB_SystemMailData* queryMailDataByMailTid(uint16_t id);
protected:
    virtual bool init();
private:
    static MB_SystemDataMgr* m_pThisInstance;
    MB_SystemDataMgr();
    CCArray* m_pSystemMailData;
};

#endif /* defined(__ProjectMB__MB_SystemMailData__) */
