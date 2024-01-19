//
//  MB_TaskConfigure.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_TaskConfigure.h"

MB_TaskConfigure* MB_TaskConfigure::m_pSingletonInstance = NULL;

MB_TaskConfigure::MB_TaskConfigure()
{
    m_pArray = new CCArray;
}

MB_TaskConfigure::~MB_TaskConfigure()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}

MB_TaskConfigure* MB_TaskConfigure::getInstance()
{
    if (m_pSingletonInstance==NULL)
    {
        m_pSingletonInstance = new MB_TaskConfigure;
        if(!m_pSingletonInstance->init("config/daily_task.xml"))
        {
            CCLog("[Error]:load config/daily_task.xml failed");
        }
    }
    return m_pSingletonInstance;
}

void MB_TaskConfigure::destoryInstance()
{
    CC_SAFE_DELETE(m_pSingletonInstance);
}

MB_TaskData* MB_TaskConfigure::getTaskDataById(uint32_t nTid)
{
    MB_TaskData* pData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pArray, MB_TaskData*, pData)
    {
        if (nTid == pData->getTypeId())
        {
            return pData;
        }
    }
    
    return NULL;
}

int MB_TaskConfigure::getTaskByType(CCArray* pOut,uint16_t nType)
{
    pOut->removeAllObjects();
    int index = 0;
    
    MB_TaskData* pData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pArray, MB_TaskData*, pData)
    {
        if (pData->getType() == nType)
        {
            pOut->addObject(pData);
            ++index;
        }
    }
    return index;
}

bool MB_TaskConfigure::init(const char* pFile)
{
    MB_XmlFile* pXml = MB_XmlFile::create(pFile);
    
    if (pXml == NULL)
    {
        return false;
    }
    
    CCArray* pArray = CCArray::create();
    MB_XmlNode* pNode = NULL;
    MB_TaskData* pData = NULL;
    
    if (pXml->queryNodesByName("task|task", pArray))
    {
        m_pArray->removeAllObjects();
        
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
        {
            pData = MB_TaskData::create(pNode);
            if (pData)
            {
                m_pArray->addObject(pData);
            }
        }
        
        return true;
    }
    
    return true;
}
