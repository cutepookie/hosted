
//
//  OCandCppHelper.cpp
//  ProjectTK
//
//  Created by YanJiYong on 13-1-31.
//
//

#include "OCandCppHelper.h"
#include "cocos2d.h"
#include "MB_ClientSocket.h"
#include "MB_RoleData.h"
#include "JavaCppHelper.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#include "MB_PerfectRaceInterface.h"
#include "MB_FunctionConfig.h"
#include "MB_DataExchange.h"
#include <time.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

 time_t timegm( struct tm *tm ) {
	time_t t = mktime( tm );
	return t + localtime( &t )->tm_gmtoff;
}
#endif
using namespace cocos2d;
//static time_t timegm(struct tm *tm)
//
//{
//    time_t ret;
//
//    char *tz;
//
//    /** save current timezone and set UTC */
//
//    tz = getenv("TZ");
//
//    putenv("TZ=UTC");   /** use Coordinated Universal Time (i.e. zero offset) */
//
//    tzset();
//
//    ret = mktime(tm);
//
//    if(tz)
//    {
//        char buf[256];
//        snprintf(buf, sizeof(buf), "TZ=%s", tz);
//        putenv(buf);
//    } else
//        putenv("TZ=");
//    putenv(tz);
//        tzset();
//    
//        return ret;
//}

OCandCppHelper::OCandCppHelper(){


}

OCandCppHelper::~OCandCppHelper(){


}
//移植android 的時候需要改 創建文件夹
bool OCandCppHelper::createFileWithPath(const char * pathstr){

	int length = strlen(pathstr);
	char dirpath[300];
	for (; pathstr[length] != '/'; length--);
	int j = 0;
	for (; j < length; j++) {

		dirpath[j] = pathstr[j];
	}
	dirpath[j] = '\0';
	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID jcreateFileWithPath = (m_pEnv)->GetStaticMethodID(javaHelper, "createfile", "(Ljava/lang/String;)Z");
	jstring jmessage = JavaCppHelper::getInstance()->stoJstring(m_pEnv, dirpath);
	jboolean	issuccess = (m_pEnv)->CallStaticBooleanMethod(javaHelper, jcreateFileWithPath, jmessage);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jmessage);
	return issuccess == 1;
}

bool OCandCppHelper::isconnectWIFI(){

	return JavaCppHelper::getInstance()->isconnectWIFI();

}

bool OCandCppHelper::isconnect3G(){

	return JavaCppHelper::getInstance()->isconnect3G();
}

bool OCandCppHelper::setLocalTips(const char *message, float times, const char *messageName, unsigned int repeatInterval){

	//if (times <= 0)return false;

	//if (MB_RoleData::getInstance()->getisPushNightMute()){

	//	time_t t;
	//	struct tm * a;
	//	time(&t);
	//	t = t + times;
	//	a = localtime(&t);
	//	if (a->tm_hour >= 23 || a->tm_hour <= 7){

	//		return false;
	//	}
	//}

	//JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	//std::string package = "com/zdbpkq/bt/";
	//package += "PushMessageManager";
	//jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	//std::string stringback = "()L";
	//stringback += package;
	//stringback += ";";

	//jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());

	//jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	//jmethodID post = (m_pEnv)->GetMethodID(javaHelper, "pushMessage", "(Ljava/lang/String;ILjava/lang/String;)V");
	//jstring jmessage = JavaCppHelper::getInstance()->stoJstring(m_pEnv, message);
	//jstring jmessageName = JavaCppHelper::getInstance()->stoJstring(m_pEnv, messageName);
	//(m_pEnv)->CallVoidMethod(myObject, post, jmessage, (int)times, jmessageName);
	//m_pEnv->DeleteLocalRef(javaHelper);
	//m_pEnv->DeleteLocalRef(jmessage);
	//m_pEnv->DeleteLocalRef(jmessageName);
	return true;
}
void OCandCppHelper::cancelLocalTips(const char * messageName){

	//JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	//std::string package = "com/zdbpkq/bt/";
	//package += "PushMessageManager";
	//jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	//std::string stringback = "()L";
	//stringback += package;
	//stringback += ";";
	//jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	//jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	//jmethodID post = (m_pEnv)->GetMethodID(javaHelper, "cancelMessage", "(Ljava/lang/String;)V");
	//jstring jmessageName = JavaCppHelper::getInstance()->stoJstring(m_pEnv, messageName);
	//(m_pEnv)->CallVoidMethod(myObject, post, jmessageName);
	//m_pEnv->DeleteLocalRef(javaHelper);
	//m_pEnv->DeleteLocalRef(jmessageName);
}
void OCandCppHelper::removeAllMessage(){

	//JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	//std::string package = "com/zdbpkq/bt/";
	//package += "PushMessageManager";
	//jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	//std::string stringback = "()L";
	//stringback += package;
	//stringback += ";";
	//jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	//jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	//jmethodID post = (m_pEnv)->GetMethodID(javaHelper, "removeAllMessage", "()V");
	//(m_pEnv)->CallVoidMethod(myObject, post);
	//m_pEnv->DeleteLocalRef(javaHelper);

}
void OCandCppHelper::setLockSceen(bool islock){

	//    JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	//    std::string package = "com/zdbpkq/bt/";
	//    package += "WeiboMgr";
	//    jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	//    std::string stringback = "()L";
	//    stringback += package;
	//    stringback += ";";
	//    
	//    jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance",stringback.c_str());
	//    jobject myObject = (jobject) (m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence );
	//    jmethodID post = (m_pEnv)->GetMethodID(javaHelper, "lockSceen", "(I)V");
	//    (m_pEnv)->CallVoidMethod(myObject,post,(int)islock);
	//    m_pEnv->DeleteLocalRef (javaHelper);


}
void  OCandCppHelper::convertScollerViewSuitable(CCNode *node){

	//     CCSize size = CCDirector::sharedDirector()->getWinSize();
	//     CCPoint posheight = ccp(0,size.height- 480);
	//     posheight = node->getParent()->convertToNodeSpace(posheight);
	//     node->setContentSize(CCSize(node->getContentSize().width,node->getContentSize().height + 2*posheight.y/node->getScaleY()));
	//     node->setPosition(ccp(node->getPosition().x, node->getPosition().y  + (2*node->getAnchorPoint().y -1)*posheight.y/node->getScaleY()));

}
void  OCandCppHelper::convertScollerViewSuitable(CCScrollView *m_pScollerView){

	//     CCSize size = CCDirector::sharedDirector()->getWinSize();
	//     CCPoint posheight = ccp(0,size.height- 480);
	//     posheight = m_pScollerView->getParent()->convertToNodeSpace(posheight);
	//     m_pScollerView->setViewSize(CCSize(CCSize(m_pScollerView->getViewSize().width,m_pScollerView->getViewSize().height+posheight.y*2*m_pScollerView->getScaleY())));
	//     m_pScollerView->setPosition(ccp(m_pScollerView->getPosition().x, m_pScollerView->getPosition().y - posheight.y));
}
const char * OCandCppHelper::getVervion(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID jgetversion = (m_pEnv)->GetStaticMethodID(javaHelper, "getVersion", "()Ljava/lang/String;");
	jstring jversion = (jstring)(m_pEnv)->CallStaticObjectMethod(javaHelper, jgetversion);
	const char * version = JavaCppHelper::getInstance()->jstringTostring(m_pEnv, jversion);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jversion);
	m_strVersion = version;
	delete[] version;
	return  m_strVersion.c_str();
}

int nServerZone = 8;

//返回伺服器今天指定int hour,int min,int sec 的時間戳
time_t gettime_tWithServerZone(int hour, int min, int sec)
{
	time_t tNow = MB_ClientSocket::getInstance()->getServerTime();
	struct tm *pTemp = gmtime(&tNow);

	int n = hour - nServerZone;     //hour是相對伺服器時區的值，这里是用UTC計算，故减去伺服器時區
	if (n < 0)n += 24;

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
	if (n > 23)
	{
		nwad++;
	}
	return nwad %= 7;
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
	}
	else if (time_zone > 12) {
		time_zone -= 24;
	}
	return time_zone;
}


void OCandCppHelper::EnterBackGroud()
{
	if (NSDataExchange::g_bInCharge)return;

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isGameInitOver"))
	{
		if (MB_RoleData::getInstance()->getLevel() >= 20)
		{
			if (MB_RoleData::getInstance()->getEnergy() < MB_RoleData::getInstance()->getEnergyMax())
			{
				int times = MB_RoleData::getInstance()->getEnergyMax() - MB_RoleData::getInstance()->getEnergy() - 1;
				int endtime = times * 30 * 60 + (MB_RoleData::getInstance()->getNextEnergyTime() - MB_ClientSocket::getInstance()->getServerTime());    //体力恢複满時間

				if (endtime >= 10)
				{
                    OCandCppHelper::setLocalTips("尊敬的训练师，您的精力已经恢复，请继续远征吧！", endtime, "role_energy_full");
				}
			}
			else
			{
				OCandCppHelper::cancelLocalTips("role_energy_full");
			}

			if (MB_RoleData::getInstance()->getDiscoveryTimes() < MB_RoleData::getInstance()->getDiscoveryTimesMax())
			{
				int times = MB_RoleData::getInstance()->getDiscoveryTimesMax() - MB_RoleData::getInstance()->getDiscoveryTimes() - 1;
				int endtime = times * 6 * 60 + (MB_RoleData::getInstance()->getNextDscvTime() - MB_ClientSocket::getInstance()->getServerTime());
				if (endtime >= 10)
				{
                    MB_NotificationMgr::getInstence()->setLocalTips("尊敬的训练师，您的冒险次数已经恢复，让我们冒险吧！", endtime, "role_discovry_full",  kNotificationTypeAdventrue);
				}
			}
			else
			{
				MB_NotificationMgr::getInstence()->removeTipsByName("role_discovry_full");
			}
		}

		//9	華麗大賽開賽	華麗大賽開始		開服第二周的周一AM 11:00:00	主人，華麗大賽開始報名啦！～～
		//        if(MB_RoleData::getInstance()->getLevel() >= MB_FunctionConfigure::getInstance()->getFunctionLimitLevel(kFunctionPerfectRace))
		//        {
		//            NSGameFunction::CCFunctionInterface* pInterface = NULL;
		//            if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPerfectRace,&pInterface))
		//            {
		//                MB_PerfectRaceInterface* pPerfectRace = dynamic_cast<MB_PerfectRaceInterface*>(pInterface);
		//                if(pPerfectRace)
		//                {
		//                    time_t tNow;
		//                    tNow = MB_ClientSocket::getInstance()->getServerTime();
		//                    time_t t11 = gettime_tWithServerZone(11,0,0);   //伺服器今天11点時間戳
		//                    int wday = getwadWithServerZone();              //伺服器今天星期几
		//                    
		//                    int n1 = 0;
		//                    if(wday == 1 && tNow>t11)
		//                    {
		//                        n1 = 8 - wday;
		//                    }
		//                    else
		//                    {
		//                        if(wday <= 1)
		//                        {
		//                            if(!pPerfectRace->getIsSign())
		//                            {
		//                                n1 = 1 - wday;
		//                            }
		//                            else
		//                            {
		//                                n1 = 8 - wday;
		//                            }
		//                        }
		//                        else
		//                        {
		//                            n1 = 8 - wday;
		//                        }
		//                    }
		//                    time_t tdis = n1 * 24 * 3600 + t11 - tNow;
		//                    unsigned int repeatInterval = 7 * 24 * 60 * 60;
		//                    OCandCppHelper::setLocalTips("主人，華麗大賽開始報名啦！～～", tdis , "perfect_race_sign",repeatInterval);
		//                }
		//            }
		//        }



		//領取体力
		{
			int seconds = 0;
			time_t tNow = MB_ClientSocket::getInstance()->getServerTime();

			MB_MoneyEventEnergy*  pEvnet = MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
			if (pEvnet)
			{
				time_t starttime = pEvnet->getStartTime();
				if (tNow < starttime)
				{
					seconds = starttime - tNow;
				}
				else
				{
					seconds = starttime + 24 * 60 * 60 - tNow;
				}

                OCandCppHelper::setLocalTips("尊敬的训练师，午饭已经为您准备好了！", seconds , "role_get_energy_noon");
			}


			pEvnet = MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
			if (pEvnet)
			{
				time_t starttime = pEvnet->getStartTime();
				if (tNow < starttime)
				{
					seconds = starttime - tNow;
				}
				else
				{
					seconds = starttime + 24 * 60 * 60 - tNow;
				}
                OCandCppHelper::setLocalTips("尊敬的训练师，晚饭已经为您准备好了！", seconds , "role_get_energy_evening");
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
		//                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp13 - tNow + 2 * 24 * 60 * 60 , "get_xds");
		//                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp19 - tNow + 2 * 24 * 60 * 60 , "get_xds");
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
		//                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp13 - tNow + 24 * 60 * 60 , "get_xds");
		//                    OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp19 - tNow + 24 * 60 * 60 , "get_xds");
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
		//                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp13 - tNow, "get_xds");
		//                        }
		//                        if (tTemp19 - tNow > 0)
		//                        {
		//                            OCandCppHelper::setLocalTips("皮卡皮卡～～快來領取登入獎勵吧，今天送五星\"小电獅\"喔~", tTemp19 - tNow, "get_xds");
		//                        }
		//                    }
		//                }
		//                break;
		//            }
		//        }
		//get xiaodiaosi

		//4	激戰超梦		玩家等級大於等於10級	AM 12:25:00
		if (MB_RoleData::getInstance()->getLevel() >= 10)
		{
			int seconds = 0;
			time_t tNow = MB_ClientSocket::getInstance()->getServerTime();

			time_t tTemp = gettime_tWithServerZone(19, 55, 0);
			if (tNow < tTemp)
			{
				seconds = tTemp - tNow;
			}
			else
			{
				seconds = tTemp + 24 * 60 * 60 - tNow;
			}


			unsigned int repeatInterval = 24 * 60 * 60;
            OCandCppHelper::setLocalTips("尊敬的训练师，火箭队又来捣乱，快和我们一起制裁他们吧！", seconds , "fight_cm",repeatInterval);
		}

		//5	激戰鳳王		玩家等級大於等於35級	PM 19:55:00	主人，眾多訓練師正趕往玲玲塔挑戰鳳王，我們快去吧～～
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

	NSDataExchange::g_bInCharge = false;

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isGameInitOver")){

		OCandCppHelper::removeAllMessage();
	}

}
std::string OCandCppHelper::m_strProductName = "";
std::string OCandCppHelper::m_strProjectID = "";
std::string OCandCppHelper::m_strVersion = "";
std::string OCandCppHelper::m_strUniString = "";
const char * OCandCppHelper::getProjectID(){


	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID jgetversion = (m_pEnv)->GetStaticMethodID(javaHelper, "getProjectID", "()Ljava/lang/String;");
	jstring jprojectid = (jstring)(m_pEnv)->CallStaticObjectMethod(javaHelper, jgetversion);
	const char * projectid = JavaCppHelper::getInstance()->jstringTostring(m_pEnv, jprojectid);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jprojectid);
	m_strProjectID = projectid;
	delete[] projectid;
	return m_strProjectID.c_str();
}
const char *OCandCppHelper::getProjectName(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID jgetversion = (m_pEnv)->GetStaticMethodID(javaHelper, "getProductName", "()Ljava/lang/String;");
	jstring jproduct = (jstring)(m_pEnv)->CallStaticObjectMethod(javaHelper, jgetversion);
	const char * product = JavaCppHelper::getInstance()->jstringTostring(m_pEnv, jproduct);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jproduct);
	m_strProductName = product;
	delete[] product;
	return  m_strProductName.c_str();

}
void OCandCppHelper::goUpdate(const char *url){


	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID post = (m_pEnv)->GetStaticMethodID(javaHelper, "update", "(Ljava/lang/String;)V");
	jstring jmessageName = JavaCppHelper::getInstance()->stoJstring(m_pEnv, url);
	(m_pEnv)->CallStaticVoidMethod(javaHelper, post, jmessageName);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jmessageName);
}
const char * OCandCppHelper::getUniString(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = "com/zdbpkq/bt/";
	package += "JavaToCppHelper";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	jmethodID jgetversion = (m_pEnv)->GetStaticMethodID(javaHelper, "getDevID", "()Ljava/lang/String;");
	jstring jproduct = (jstring)(m_pEnv)->CallStaticObjectMethod(javaHelper, jgetversion);
	const char * product = JavaCppHelper::getInstance()->jstringTostring(m_pEnv, jproduct);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jproduct);
	m_strUniString = product;
	CCLOG("GetUniString:%s", product);
	delete[] product;
	return m_strUniString.c_str();
}

const std::string OCandCppHelper::getChannelAndVer() {

	// unsigned long sizeOfFile = 0;
	// unsigned char * data = CCFileUtils::sharedFileUtils()->getFileData("channel.flag", "r", &sizeOfFile);
	// if(data != NULL){
	//     std::string info = (char*)data;
	//     delete data;
	//     size_t i = info.find_first_of('\n');
	//     if(i > 0 && i < info.length())
	//         return info.substr(0,i);

	//     i = info.find_first_of('\r');
	//     if(i > 0 && i < info.length())
	//         return info.substr(0,i);

	//     return info;
	// }


	return "";

}

