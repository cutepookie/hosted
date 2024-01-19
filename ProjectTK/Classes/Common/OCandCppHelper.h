

#ifndef ProjectMB_OCandCppHelper_h
#define ProjectMB_OCandCppHelper_h
#include "Game.h"

class OCandCppHelper {
    
private:
    static  std::string m_strProductName;
    static  std::string m_strProjectID;
    static  std::string m_strVersion;
    static  std::string m_strUniString;
    static  std::string m_strDeviceTocken;
    public :
    
    OCandCppHelper();
    ~OCandCppHelper();
    static bool createFileWithPath(const char *path);
    static bool isconnectWIFI();
    static bool isconnect3G();
    static bool setLocalTips(const char *message,float time,const char *messageName,unsigned int repeatInterval = 0);
    static void cancelLocalTips(const char *);
    static void setLockSceen(bool isLockSceen);
    static void removeAllMessage();
    static void convertScollerViewSuitable(CCNode *node);
    static void convertScollerViewSuitable(CCScrollView *node);
    static const char *getVervion();
    static void EnterBackGroud();
    static void EnterFront();
    static const char *getUniString();
    static const char *getProjectID();
    static const char *getProjectName();
    static void goUpdate(const char *url);
    static void setDeviceTocken(const char *tocken);
    static const char *getDeviceTocken();
    static void setQualityColor(CCNodeRGBA* pDest,int star);
    static void setSpriteFrame(CCSprite* pSprite,const char* pFile);
    static CCLayer* createDisableTouchLayer(const CCSize& sz);
    static const char*  formatTimeStringDHM(int iLeftTime );
    static const char*  formatTimeStringDHMS(int iLeftTime );
    static const char*  formatTimeStringHMS(int iLeftTime );
    static void RequestCityName();
    static const char* getPhoneModel();
    static const char* getPhoneVersion();
    static const std::string getChannelAndVer();
};













#endif












