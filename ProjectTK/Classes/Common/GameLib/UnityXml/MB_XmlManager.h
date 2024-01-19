//
//  MB_XmlManager.h
//  XmlManager
//
//  Created by WenYong on 14-1-24.
//
//

#ifndef __XmlManager__MB_XmlManager__
#define __XmlManager__MB_XmlManager__

#include "MB_XmlItems.h"
class MB_XmlFile;
class MB_XmlManager:public CCObject
{
public:
    ~MB_XmlManager();
    static MB_XmlManager* getInstance();
    static void destroyInstance();
    MB_XmlFile* queryXmlFile(const char* szPath);
    MB_XmlFile* loadXml(const char* szPath,bool bCache);
    void removeXml(const char* szPath);
private:
    void addXmlFile(const char* szPath,MB_XmlFile* pFile);
    MB_XmlManager();
private:
    std::map<std::string,MB_XmlFile*>       m_pFileMapping;
    static MB_XmlManager*  m_pSignelInstance;
};

#endif /* defined(__XmlManager__MB_XmlManager__) */
