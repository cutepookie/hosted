//
//  MB_ResourcesPackageUpdate.cpp
//  ProjectMB
//
//  Created by wenyong on 14-11-24.
//
//

#include "MB_ResourcesPackageUpdate.h"
#include <fstream>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif
#include <stdio.h>
#include "../Common/GameLib/UnityXml/MB_XmlItems.h"
#include <unistd.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <ftw.h>
#endif
//static const char package_url[] = "http://101.251.223.115/package_v1.1.0.zip";
//static const char version_url[] = "http://101.251.223.115/test.php";
MB_ResourcesPackageUpdate::MB_ResourcesPackageUpdate()
{
    getStoragePath(m_szRootPath);
    setStoragePath(m_szRootPath.c_str());
    // Create the folder if it doesn't exist
        #if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
            DIR *pDir = NULL;
    
            pDir = opendir(m_szRootPath.c_str());
            if (!pDir)
            {
                mkdir(m_szRootPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            }
        #else
            if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
            {
                CreateDirectoryA(pathToSave.c_str(), 0);
            }
        #endif
}

void MB_ResourcesPackageUpdate::getStoragePath(std::string& path)
{
    path = CCFileUtils::sharedFileUtils()->getWritablePath() + "external_path/";
}

MB_ResourcesPackageUpdate::~MB_ResourcesPackageUpdate()
{
}

bool MB_ResourcesPackageUpdate::init()
{
//    std::string command = "rm -r ";
//    // Path may include space.
//    command += "\"" + m_szRootPath + "\"";
//    system(command.c_str());
    
    DIR *pDir = NULL;
    
    pDir = opendir (m_szRootPath.c_str());
    if (! pDir)
    {
        mkdir(m_szRootPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        return true;
    }
    
    
    return true;
}

void MB_ResourcesPackageUpdate::reset()
{
    std::string root;
    getStoragePath(root);
    if (access(root.c_str(), 0)==0)
    {
        //rmdir(root.c_str());
        removeSearchPath(root);
        removeSearchPath(root+"texture/");
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        std::string command = "rm -rf ";
        // Path may include space.
        command += "\"" + root + "\"";
        system(command.c_str());
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        std::string command = "rm -rf ";
        // Path may include space.
        command += "\"" + root + "\"";
        nftw(command.c_str(),nullptr, 64, FTW_DEPTH | FTW_PHYS);
#endif
    }
    else
    {
        CCLOG("已删除补丁目录");
    }
}

bool MB_ResourcesPackageUpdate::update()
{
    if (_tid) return false;
    
    // 1. Urls of package and version should be valid;
    // 2. Package should be a zip file.
    if (_packageUrl.size() == 0 ||
        std::string::npos == _packageUrl.find(".zip"))
    {
        CCLOG("no version file url, or no package url, or the package is not a zip file");
        return false;
    }
    
    // Is package already downloaded?
//    _downloadedVersion = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_OF_DOWNLOADED_VERSION);
//
    _curl = curl_easy_init();
    _downloadedVersion = m_szVersion;
    _tid = new pthread_t();
    pthread_create(&(*_tid), NULL, cocos2d::extension::assetsManagerDownloadAndUncompress, this);
    return true;
}


void MB_ResourcesPackageUpdate::setSearchPath()
{
    AssetsManager::setSearchPath();
    // wenyong add
    if (access((_storagePath+"texture/").c_str(),0)==0)
    {
        insertSearchPath((_storagePath+"texture/").c_str());
    }
}

void MB_ResourcesPackageUpdate::storeVersionFile()
{
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_OF_VERSION, m_szVersion);
}


bool MB_ResourcesPackageUpdate::goUpdate()
{
    return update();
}


