//
//  MB_SystemMailData.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#include "MB_SystemMailData.h"
#include "../Common/GameLib/UnityXml/MB_XmlItems.h"

bool MB_SystemMailData::init(MB_XmlNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    m_nMailTemplateID = pNode->queryAttributeByName("tid")->intValue();
    m_szTitle = pNode->queryAttributeByName("title")->getCString();
    m_szContent = pNode->queryAttributeByName("content")->getCString();
    CCLOG("%s",m_szTitle.c_str());
    
    return true;
}


MB_SystemDataMgr::~MB_SystemDataMgr()
{
    CC_SAFE_RELEASE_NULL(m_pSystemMailData);
}

MB_SystemDataMgr* MB_SystemDataMgr::getInstance()
{
    if (m_pThisInstance == NULL)
    {
        m_pThisInstance = new MB_SystemDataMgr;
        if(!m_pThisInstance->init())
        {
            CCLOG("[Error]:System data init failed");
        }
    }
    return m_pThisInstance;
}

void MB_SystemDataMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pThisInstance);
}

bool MB_SystemDataMgr::init()
{
    MB_XmlFile* pFile = MB_XmlFile::create("config/email_system.xml");
    if (pFile)
    {
        CCArray* pArray = CCArray::create();
        if(pFile->queryNodesByName("email|content", pArray))
        {
            MB_XmlNode* pNode = NULL;
            MB_SystemMailData* pData = NULL;
            CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
            {
                pData = new MB_SystemMailData;
                if (pData->init(pNode))
                {
                    m_pSystemMailData->addObject(pData);
                }
                CC_SAFE_RELEASE_NULL(pData);
            }
        }
    }
    return true;
}

MB_SystemDataMgr* MB_SystemDataMgr::m_pThisInstance = NULL;

MB_SystemDataMgr::MB_SystemDataMgr()
{
    m_pSystemMailData = new CCArray;
}

const MB_SystemMailData* MB_SystemDataMgr::queryMailDataByMailTid(uint16_t id)
{
    MB_SystemMailData* pData = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pSystemMailData, MB_SystemMailData*, pData)
    {
        if (pData && pData->getMailTemplateID()==id)
        {
            return pData;
        }
    }
    return NULL;
}