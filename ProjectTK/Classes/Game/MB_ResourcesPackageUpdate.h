//
//  MB_ResourcesPackageUpdate.h
//  ProjectMB
//
//  Created by wenyong on 14-11-24.
//
//

#ifndef __ProjectMB__MB_ResourcesPackageUpdate__
#define __ProjectMB__MB_ResourcesPackageUpdate__

#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC;

class MB_ResourcesPackageUpdate : public extension::AssetsManager
{
public:
    MB_ResourcesPackageUpdate();
    virtual ~MB_ResourcesPackageUpdate();
    bool init();
    bool goUpdate();
    void storeVersionFile();
    virtual bool update();
    void setTargetVersion(const std::string& version){m_szVersion=version;}
    static void getStoragePath(std::string& path);
    virtual void setSearchPath();
    static void reset();
private:
    std::string                         m_szVersion;
    std::string                         m_szRootPath;
    
};

#endif /* defined(__ProjectMB__MB_ResourcesPackageUpdate__) */
