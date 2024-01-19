

#include "OCandCppHelper.h"
#include "cocos2d.h"
#include "MB_ClientSocket.h"

#include "MB_RoleData.h"
#include "CCGameHelper.h"
#import <AdSupport/AdSupport.h>
#import <AdSupport/ASIdentifierManager.h>

#import "LoctionHelper.h"
#include "IOSPlayVideo.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_FunctionConfig.h"
#import <sys/types.h>
#import <sys/sysctl.h>
#import <sys/utsname.h>
#import <dlfcn.h>


using namespace cocos2d;

OCandCppHelper::OCandCppHelper(){
    
}

OCandCppHelper::~OCandCppHelper(){
    
}
//移植android 的時候需要改 創建文件夹
bool OCandCppHelper::createFileWithPath(const char * pathstr){
    
    
    int length = strlen(pathstr);
    
    char dirpath[300];
    
    
    for (; pathstr[length]!='/'; length--) ;
    
    int j=0;
    
    for ( ;j<length; j++) {
        
        dirpath[j]=pathstr[j];
    }
    
    dirpath[j]='\0';
    
    
    
    NSString* path = [NSString stringWithFormat:@"%s",dirpath];
    BOOL isDir= NO;
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    BOOL existed = [fileMgr fileExistsAtPath:path isDirectory:&isDir];    if(!( isDir == YES && existed == YES)){
        
        [fileMgr createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:nil];
        
        return  true;
    }
    
    return  false ;
}

bool OCandCppHelper::isconnectWIFI()
{
    return true;
}

bool OCandCppHelper::isconnect3G()
{
    return true;
}

bool OCandCppHelper::setLocalTips(const char *message,float times,const char *messageName,unsigned int repeatInterval){
    
    if(times <= 0)return false;
    if( MB_RoleData::getInstance()->getisPushNightMute() ){
        
        time_t t;
        struct tm * a;
        time(&t);
        t = t+times;
        a = localtime(&t);
        if(a->tm_hour >= 23 ||a->tm_hour <= 7){
            
            return false;
        }
    }
    UILocalNotification *notification = [[[UILocalNotification alloc] init] autorelease];
    //設置10秒之后
    NSDate *pushDate = [NSDate dateWithTimeIntervalSinceNow:times];
    if (notification != nil) {
        
        // 設置推送時間
        notification.fireDate = pushDate;
        // 設置時區
        notification.timeZone = [NSTimeZone defaultTimeZone];
        // 設置重復間隔
        notification.repeatInterval = 0;
        // 推送声音
        notification.soundName = UILocalNotificationDefaultSoundName;
        // 推送内容
        notification.alertBody = [NSString stringWithUTF8String:message];
        //显示在icon上的红色圈中的數子
        notification.applicationIconBadgeNumber += 1;
        //設置userinfo 方便在之后需要撤销的時候使用
        NSDictionary *info = [NSDictionary dictionaryWithObject:[NSString stringWithUTF8String:messageName]forKey:@"key"];
        notification.userInfo = info;
        //添加推送到UIApplication
        UIApplication *app = [UIApplication sharedApplication];
        [app scheduleLocalNotification:notification];
        
    }
    return true;
}
void OCandCppHelper::cancelLocalTips(const char * messageName){
    
    
    // 獲得 UIApplication
    UIApplication *app = [UIApplication sharedApplication];
    //獲取本地推送數組
    NSArray *localArray = [app scheduledLocalNotifications];
    //声明本地通知對象
    
    if (localArray) {
        for (UILocalNotification *noti in localArray) {
            NSDictionary *dict = noti.userInfo;
            if (dict) {
                NSString *inKey = [dict objectForKey:@"key"];
                if ([inKey isEqualToString:[NSString stringWithUTF8String:messageName]]) {
                    
                    [app cancelLocalNotification:noti];
                    
                    break;
                }
            }
        }
        
    }
    
}
void OCandCppHelper::removeAllMessage(){
    UIApplication *app = [UIApplication sharedApplication];
    [app cancelAllLocalNotifications];
}
void OCandCppHelper::setLockSceen(bool islock){
    
    [[UIApplication sharedApplication] setIdleTimerDisabled: islock];
}
void  OCandCppHelper::convertScollerViewSuitable(CCNode *node){
    
    //     CCSize size = CCDirector::sharedDirector()->getWinSize();
    //     CCPoint posheight = ccp(0,size.height- 480);
    //     posheight = node->getParent()->convertToNodeSpace(posheight);
    //     node->setContentSize(CCSize(node->getContentSize().width,node->getContentSize().height + 2*posheight.y/node->getScaleY()));
    //     node->setPosition(ccp(node->getPosition().x, node->getPosition().y  + (2*node->getAnchorPoint().y -1)*posheight.y/node->getScaleY()));
    
}
void  OCandCppHelper::convertScollerViewSuitable(CCScrollView *m_pScollerView){
    //
    //     CCSize size = CCDirector::sharedDirector()->getWinSize();
    //     CCPoint posheight = ccp(0,size.height- 480);
    //     posheight = m_pScollerView->getParent()->convertToNodeSpace(posheight);
    //     m_pScollerView->setViewSize(CCSize(CCSize(m_pScollerView->getViewSize().width,m_pScollerView->getViewSize().height+posheight.y*2*m_pScollerView->getScaleY())));
    //     m_pScollerView->setPosition(ccp(m_pScollerView->getPosition().x, m_pScollerView->getPosition().y - posheight.y));
}
const char * OCandCppHelper::getVervion(){
    
    NSString* strVersion =  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    return [strVersion UTF8String];
}

static int nServerZone = 8;         //伺服器部署地時區，这个最好又伺服器發

//返回伺服器今天指定int hour,int min,int sec 的時間戳
static time_t gettime_tWithServerZone(int hour,int min,int sec)
{
    time_t tNow = MB_ClientSocket::getInstance()->getServerTime();
    struct tm *pTemp = gmtime(&tNow);
    
    int n = hour - nServerZone;     //hour是相對伺服器時區的值，这里是用UTC計算，故减去伺服器時區
    if(n<0)n+=24;
    
    pTemp->tm_hour = n;
    pTemp->tm_min = min;
    pTemp->tm_sec = sec;
    return timegm(pTemp);
}

//返回伺服器今天指定int hour,int min,int sec 是星期几
int getwadWithServerZone()
{
    time_t tNow = MB_ClientSocket::getInstance()->getServerTime();
    struct tm *pTemp = gmtime(&tNow);
    int nwad = pTemp->tm_wday;
    
    int n = pTemp->tm_hour + nServerZone;
    if(n>23)
    {
        nwad++;
    }
    return nwad%=7;
}

int getseflzone()
{
    time_t time_utc;
    struct tm tm_local;
    
    // Get the UTC time
    time(&time_utc);
    
    // Get the local time
    // Use localtime_r for threads safe
    localtime_r(&time_utc, &tm_local);
    
    time_t time_local;
    struct tm tm_gmt;
    
    // Change tm to time_t
    time_local = mktime(&tm_local);
    
    // Change it to GMT tm
    gmtime_r(&time_utc, &tm_gmt);
    
    int time_zone = tm_local.tm_hour - tm_gmt.tm_hour;
    if (time_zone < -12) {
        time_zone += 24;
    } else if (time_zone > 12) {
        time_zone -= 24;
    }
    return time_zone;
}

void OCandCppHelper::EnterBackGroud(){
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("isGameInitOver"))
    {
        if(MB_RoleData::getInstance()->getLevel() >= 20)
        {
            if (MB_RoleData::getInstance()->getEnergy() < MB_RoleData::getInstance()->getEnergyMax())
            {
                int times = MB_RoleData::getInstance()->getEnergyMax()-MB_RoleData::getInstance()->getEnergy()-1;
                int endtime = times *30*60+ (MB_RoleData::getInstance()->getNextEnergyTime() -MB_ClientSocket::getInstance()->getServerTime());    //体力恢復满時間
                
                if(endtime >= 10)
                {
                    OCandCppHelper::setLocalTips("尊敬的玩家，您的体力已经恢复，请继续远征吧！", endtime, "role_energy_full");
                }
            }
            else
            {
                OCandCppHelper::cancelLocalTips("role_energy_full");
            }
            
            if (MB_RoleData::getInstance()->getDiscoveryTimes() <  MB_RoleData::getInstance()->getDiscoveryTimesMax())
            {
                int times = MB_RoleData::getInstance()->getDiscoveryTimesMax() -MB_RoleData::getInstance()->getDiscoveryTimes()-1;
                int endtime = times *6*60+(MB_RoleData::getInstance()->getNextDscvTime() - MB_ClientSocket::getInstance()->getServerTime());
                if(endtime >= 10)
                {
                    MB_NotificationMgr::getInstence()->setLocalTips("尊敬的玩家，您的冒险次数已经恢复，让我们冒险吧！", endtime, "role_discovry_full",  kNotificationTypeAdventrue);
                }
            }
            else
            {
                MB_NotificationMgr::getInstence()->removeTipsByName("role_discovry_full");
            }
        }
        
        
        //領取体力
        {
            int seconds = 0;
            time_t tNow=MB_ClientSocket::getInstance()->getServerTime();
            
            MB_MoneyEventEnergy*  pEvnet =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
            if(pEvnet)
            {
                time_t starttime = pEvnet->getStartTime();
                if(tNow  < starttime)
                {
                    seconds = starttime - tNow;
                }
                else
                {
                    seconds = starttime + 24 * 60 * 60 - tNow;
                }
                
                OCandCppHelper::setLocalTips("尊敬的玩家，午饭已经为您准备好了！", seconds , "role_get_energy_noon");
            }
            
            
            pEvnet =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
            if(pEvnet)
            {
                time_t starttime = pEvnet->getStartTime();
                if(tNow  < starttime)
                {
                    seconds = starttime - tNow;
                }
                else
                {
                    seconds = starttime + 24 * 60 * 60 - tNow;
                }
                OCandCppHelper::setLocalTips("尊敬的玩家，晚饭已经为您准备好了！", seconds , "role_get_energy_evening");
            }
        }
        
        
        //get pika
        //        DailyRewardValue* tempValue = NULL;
        //
        //        time_t tNow=MB_ClientSocket::getInstance()->getServerTime();
        //
        //        time_t tTemp13 = gettime_tWithServerZone(13,0,0);
        //        time_t tTemp19 = gettime_tWithServerZone(19,0,0);
        //
        //        for (int i = 0; i < MB_ItemMgr::getInstance()->getDailyRewardArray()->count(); i++)
        //        {
        //            tempValue = (DailyRewardValue*)MB_ItemMgr::getInstance()->getDailyRewardArray()->objectAtIndex(i);
        //            if (tempValue->getType() == kRewardTypeDaily)
        //            {
        //                uint8_t  m_uValue =     tempValue->getValue();
        //                uint8_t  m_uIsGet =   tempValue->getIsGet();
        //
        //                if (m_uValue == 1)
        //                {
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"皮卡丘\"喔~", tTemp13 - tNow + 24 * 60 * 60, "get_pika");
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"皮卡丘\"喔~", tTemp19 - tNow + 24 * 60 * 60, "get_pika");
        //
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp13 - tNow + 2 * 24 * 60 * 60 , "get_xds");
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp19 - tNow + 2 * 24 * 60 * 60 , "get_xds");
        //                }
        //                else if(m_uValue == 2)//連续登入1天
        //                {
        //                    if(m_uIsGet == 1)
        //                    {
        //                        OCandCppHelper::cancelLocalTips("get_pika");
        //                    }
        //                    else
        //                    {
        //                        if(tTemp13 - tNow > 0)
        //                        {
        //                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"皮卡丘\"喔~", tTemp13 - tNow, "get_pika");
        //                        }
        //                        if (tTemp19 - tNow > 0)
        //                        {
        //                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"皮卡丘\"喔~", tTemp19 - tNow, "get_pika");
        //                        }
        //                    }
        //
        //                    OCandCppHelper::cancelLocalTips("get_xds");
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp13 - tNow + 24 * 60 * 60 , "get_xds");
        //                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp19 - tNow + 24 * 60 * 60 , "get_xds");
        //
        //                }
        //                else if(m_uValue == 3)//連续登入2天
        //                {
        //                    if(m_uIsGet == 1)
        //                    {
        //                        OCandCppHelper::cancelLocalTips("get_xds");
        //                    }
        //                    else
        //                    {
        //                        if(tTemp13 - tNow > 0)
        //                        {
        //                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp13 - tNow, "get_xds");
        //                        }
        //                        if (tTemp19 - tNow > 0)
        //                        {
        //                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电狮\"喔~", tTemp19 - tNow, "get_xds");
        //                        }
        //                    }
        //                }
        //                break;
        //            }
        //        }
        //get xiaodiaosi
        
        //4	激戰超梦		玩家等級大於等於10級	AM 12:25:00
        if(MB_RoleData::getInstance()->getLevel() >= 10)
        {
            int seconds = 0;
            time_t tNow=MB_ClientSocket::getInstance()->getServerTime();
            
            time_t tTemp = gettime_tWithServerZone(19,55,0);
            if(tNow < tTemp)
            {
                seconds = tTemp - tNow;
            }
            else
            {
                seconds = tTemp + 24 * 60 * 60 - tNow;
            }
            
            
            unsigned int repeatInterval = 24 * 60 * 60;
            OCandCppHelper::setLocalTips("尊敬的玩家，火箭队又来捣乱，快和我们一起制裁他们吧！", seconds , "fight_cm",repeatInterval);
        }
        
        //5	激戰鳳王		玩家等級大於等於35級	PM 19:55:00	主人，众多訓練師正赶往玲玲塔挑戰鳳王，我們快去吧～～
        //        if(MB_RoleData::getInstance()->getLevel() >= 35)
        //        {
        //            int seconds = 0;
        //            time_t tNow=MB_ClientSocket::getInstance()->getServerTime();
        //
        //            time_t tTemp = gettime_tWithServerZone(19,55,0);
        //            if(tNow < tTemp)
        //            {
        //                seconds = tTemp - tNow;
        //            }
        //            else
        //            {
        //                seconds = tTemp + 24 * 60 * 60 - tNow;
        //            }
        //            unsigned int repeatInterval = 24 * 60 * 60;
        //            OCandCppHelper::setLocalTips("主人，BOSS鳳王即將刷新，我們快去挑戰它吧～～", seconds , "fight_fw",repeatInterval);
        //        }
        MB_NotificationMgr::getInstence()->loadTips();
        
    }
    
}
void OCandCppHelper::EnterFront(){
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("isGameInitOver")){
        
        OCandCppHelper::removeAllMessage();
    }
    
}

std::string& trim(std::string &s)
{
    std::string::size_type loc = 0;
    loc = s.find(' ');
    while (loc != std::string::npos)
    {
        s.erase(loc,1);
        loc = s.find(' ',loc);
    }
    return s;
}

unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            //strTemp += '%';
            //strTemp += ToHex((unsigned char)str[i] >> 4);
            //strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

const char * OCandCppHelper::getUniString(){
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0) {
        
        NSString *adId = nil;
        if([[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled])
        {
            adId = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        }
        else
        {
            adId = @"0";
        }
        char* outstring = new char[adId.length];
        sprintf(outstring, "%s",[adId UTF8String]);
        m_strUniString =outstring;
        CC_SAFE_DELETE_ARRAY(outstring);
        m_strUniString = trim(m_strUniString);
        return m_strUniString.c_str();
        
    }else {
        
        const char *str  = MB_ClientSocket::getMacAddress();
        m_strUniString = str;
        CC_SAFE_DELETE_ARRAY(str);
        m_strUniString = trim(m_strUniString);
        return m_strUniString.c_str();
        
    }
}
std::string OCandCppHelper::m_strProductName = "";
std::string OCandCppHelper::m_strProjectID = "";
std::string OCandCppHelper::m_strUniString = "";
std::string OCandCppHelper::m_strDeviceTocken = "";
void OCandCppHelper::setDeviceTocken(const char *tocken){
    
    m_strDeviceTocken = tocken;
}
const char * OCandCppHelper::getDeviceTocken(){
    
    return m_strDeviceTocken.c_str();
}
const char * OCandCppHelper::getProjectID(){
    
    m_strProjectID = "0";
    return  m_strProjectID.c_str();
}
const char *OCandCppHelper::getProjectName(){
    
    NSString* bundleid =  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"];
    return  [bundleid UTF8String];
    
}

const std::string OCandCppHelper::getChannelAndVer() {
    
    unsigned long sizeOfFile = 0;
    unsigned char * data = CCFileUtils::sharedFileUtils()->getFileData("channel.flag", "r", &sizeOfFile);
    if(data != NULL){
        
        
        Json::Reader reader;
        Json::Value root;
        if(reader.parse((char*)data, root)){
            return root["CM"].asString() + " " + root["MKN"].asString();
        }
        
        return "";
//
//
//        std::string info = (char*)data;
//        delete data;
//        size_t i = info.find_first_of('\n');
//        if(i > 0 && i < info.length())
//            return info.substr(0,i);
//
//        i = info.find_first_of('\r');
//        if(i > 0 && i < info.length())
//            return info.substr(0,i);
//
//        return info;
    }
    
    
    return "";
    
}

void OCandCppHelper::goUpdate(const char *url){
    
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
}

void OCandCppHelper::setQualityColor(CCNodeRGBA* pDest,int star)
{
    if (pDest == NULL)
    {
        return;
    }
}

void OCandCppHelper::setSpriteFrame(CCSprite* pSprite,const char* pFile)
{
    if (pSprite == NULL)
    {
        return;
    }
    
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(pFile);
    if(textrue !=NULL)
    {
        CCSpriteFrame * frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        pSprite->setDisplayFrame(frame);
    }
}

CCLayer* OCandCppHelper::createDisableTouchLayer(const CCSize& sz)
{
    MB_MessageBox3 *message= MB_MessageBox3::create();
    message->setTouchPriority(0);
    message->removeAllChildrenWithCleanup(true);
    message->setTouchEnabled(true);
    message->setAnchorPoint(ccp(0.5, 0.5));
    message->setContentSize(sz);
    return message;
}

const char* OCandCppHelper::formatTimeStringDHM(int iLeftTime )
{
    static char buff[128] = {};
    sprintf(buff,"%d天%02d时%02d分",iLeftTime/(3600*24),iLeftTime%(3600*24)/3600,iLeftTime%3600/60);
    return buff;
}

const char* OCandCppHelper::formatTimeStringDHMS(int iLeftTime )
{
    static char buff[128] = {};
    sprintf(buff,"%d天%02d时%02d分%02d秒",iLeftTime/(3600*24),iLeftTime%(3600*24)/3600,iLeftTime%3600/60,iLeftTime%3600%60);
    return buff;
}

const char* OCandCppHelper::formatTimeStringHMS(int iLeftTime )
{
    static char buff[128] = {};
    sprintf(buff,"%02d:%02d:%02d",iLeftTime%(3600*24)/3600,iLeftTime%3600/60,iLeftTime%3600%60);
    return buff;
}




void OCandCppHelper::RequestCityName()
{
    LocationHelper* g_pLocationHelper = [[LocationHelper alloc]init];
    [g_pLocationHelper startLocation];
}

const char*  OCandCppHelper::getPhoneModel(){
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *machine = (char*)malloc(size);
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    NSString *platform = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    //NSString *platform = [NSStringstringWithUTF8String:machine];二者等效
    free(machine);
    
    if ([platform isEqualToString:@"iPhone1,1"]) return [@"iPhone 2G (A1203)" UTF8String];
    if ([platform isEqualToString:@"iPhone1,2"]) return [@"iPhone 3G (A1241/A1324)" UTF8String];
    if ([platform isEqualToString:@"iPhone2,1"]) return [@"iPhone 3GS (A1303/A1325)" UTF8String];
    if ([platform isEqualToString:@"iPhone3,1"]) return [@"iPhone 4 (A1332)" UTF8String];
    if ([platform isEqualToString:@"iPhone3,2"]) return [@"iPhone 4 (A1332)" UTF8String];
    if ([platform isEqualToString:@"iPhone3,3"]) return [@"iPhone 4 (A1349)" UTF8String];
    if ([platform isEqualToString:@"iPhone4,1"]) return [@"iPhone 4S (A1387/A1431)" UTF8String];
    if ([platform isEqualToString:@"iPhone5,1"]) return [@"iPhone 5 (A1428)" UTF8String];
    if ([platform isEqualToString:@"iPhone5,2"]) return [@"iPhone 5 (A1429/A1442)" UTF8String];
    if ([platform isEqualToString:@"iPhone5,3"]) return [@"iPhone 5c (A1456/A1532)" UTF8String];
    if ([platform isEqualToString:@"iPhone5,4"]) return [@"iPhone 5c (A1507/A1516/A1526/A1529)" UTF8String];
    if ([platform isEqualToString:@"iPhone6,1"]) return [@"iPhone 5s (A1453/A1533)" UTF8String];
    if ([platform isEqualToString:@"iPhone6,2"]) return [@"iPhone 5s (A1457/A1518/A1528/A1530)" UTF8String];
    if ([platform isEqualToString:@"iPhone7,1"]) return [@"iPhone 6 Plus (A1522/A1524)" UTF8String];
    if ([platform isEqualToString:@"iPhone7,2"]) return [@"iPhone 6 (A1549/A1586)" UTF8String];
    
    if ([platform isEqualToString:@"iPod1,1"])   return [@"iPod Touch 1G (A1213)" UTF8String];
    if ([platform isEqualToString:@"iPod2,1"])   return [@"iPod Touch 2G (A1288)" UTF8String];
    if ([platform isEqualToString:@"iPod3,1"])   return [@"iPod Touch 3G (A1318)" UTF8String];
    if ([platform isEqualToString:@"iPod4,1"])   return [@"iPod Touch 4G (A1367)" UTF8String];
    if ([platform isEqualToString:@"iPod5,1"])   return [@"iPod Touch 5G (A1421/A1509)" UTF8String];
    
    if ([platform isEqualToString:@"iPad1,1"])   return [@"iPad 1G (A1219/A1337)" UTF8String];
    
    if ([platform isEqualToString:@"iPad2,1"])   return [@"iPad 2 (A1395)" UTF8String];
    if ([platform isEqualToString:@"iPad2,2"])   return [@"iPad 2 (A1396)" UTF8String];
    if ([platform isEqualToString:@"iPad2,3"])   return [@"iPad 2 (A1397)" UTF8String];
    if ([platform isEqualToString:@"iPad2,4"])   return [@"iPad 2 (A1395+New Chip)" UTF8String];
    if ([platform isEqualToString:@"iPad2,5"])   return [@"iPad Mini 1G (A1432)" UTF8String];
    if ([platform isEqualToString:@"iPad2,6"])   return [@"iPad Mini 1G (A1454)" UTF8String];
    if ([platform isEqualToString:@"iPad2,7"])   return [@"iPad Mini 1G (A1455)" UTF8String];
    
    if ([platform isEqualToString:@"iPad3,1"])   return [@"iPad 3 (A1416)" UTF8String];
    if ([platform isEqualToString:@"iPad3,2"])   return [@"iPad 3 (A1403)" UTF8String];
    if ([platform isEqualToString:@"iPad3,3"])   return [@"iPad 3 (A1430)" UTF8String];
    if ([platform isEqualToString:@"iPad3,4"])   return [@"iPad 4 (A1458)" UTF8String];
    if ([platform isEqualToString:@"iPad3,5"])   return [@"iPad 4 (A1459)" UTF8String];
    if ([platform isEqualToString:@"iPad3,6"])   return [@"iPad 4 (A1460)" UTF8String];
    
    if ([platform isEqualToString:@"iPad4,1"])   return [@"iPad Air (A1474)" UTF8String];
    if ([platform isEqualToString:@"iPad4,2"])   return [@"iPad Air (A1475)" UTF8String];
    if ([platform isEqualToString:@"iPad4,3"])   return [@"iPad Air (A1476)" UTF8String];
    if ([platform isEqualToString:@"iPad4,4"])   return [@"iPad Mini 2G (A1489)" UTF8String];
    if ([platform isEqualToString:@"iPad4,5"])   return [@"iPad Mini 2G (A1490)" UTF8String];
    if ([platform isEqualToString:@"iPad4,6"])   return [@"iPad Mini 2G (A1491)" UTF8String];
    
    if ([platform isEqualToString:@"i386"])      return [@"iPhone Simulator" UTF8String];
    if ([platform isEqualToString:@"x86_64"])    return [@"iPhone Simulator" UTF8String];
    return [platform UTF8String];
}
const char*  OCandCppHelper::getPhoneVersion(){
    NSString* phoneVersion = [[UIDevice currentDevice] systemVersion];
    return [phoneVersion UTF8String];
    
}









