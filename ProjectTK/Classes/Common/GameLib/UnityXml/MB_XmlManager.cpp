//
//  MB_XmlManager.cpp
//  XmlManager
//
//  Created by WenYong on 14-1-24.
//
//

#include "MB_XmlManager.h"

MB_XmlManager* MB_XmlManager::m_pSignelInstance = NULL;
MB_XmlManager::~MB_XmlManager()
{
    std::map<std::string, MB_XmlFile*>::iterator it = m_pFileMapping.begin();
    for (; it!=m_pFileMapping.end(); ++it)
    {
        it->second->release();
    }
    m_pFileMapping.clear();
}

MB_XmlManager::MB_XmlManager()
{

}

MB_XmlManager* MB_XmlManager::getInstance()
{
    if (m_pSignelInstance == NULL)
    {
        m_pSignelInstance = new MB_XmlManager;
    }
    return m_pSignelInstance;
}

void MB_XmlManager::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSignelInstance);
}

MB_XmlFile* MB_XmlManager::queryXmlFile(const char* szPath)
{
    if (m_pFileMapping[szPath]!=NULL)
    {
        return m_pFileMapping[szPath];
    }
    return NULL;
}

MB_XmlFile* MB_XmlManager::loadXml(const char* szPath,bool bCache)
{
    MB_XmlFile* pInstance = queryXmlFile(szPath);
    if (pInstance)
    {
        return pInstance;
    }
    else
    {
        pInstance = new MB_XmlFile;
        if (pInstance && pInstance->readXmlData(szPath))
        {
            if (bCache)
            {
                addXmlFile(szPath,pInstance);
            }
            return pInstance;
        }
    }

    return NULL;
}

void MB_XmlManager::addXmlFile(const char* szPath,MB_XmlFile* pFile)
{
    assert(szPath && pFile);
    std::string path = szPath;
    m_pFileMapping[szPath] = pFile;
}
void MB_XmlManager::removeXml(const char* szPath)
{
    assert(szPath);
    std::string path = szPath;
    MB_XmlFile* pFile = m_pFileMapping[path];
    if (pFile!=NULL)
    {
        pFile->release();
        pFile = NULL;
        m_pFileMapping.erase(path);
    }
}