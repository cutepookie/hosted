//
//  MB_DataExchange.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-5-4.
//
//

#include "MB_DataExchange.h"
#include "Game.h"
#include "AppDelegate.h"
#include "MB_LayerRewardOne.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "JavaCppHelper.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IOSPlayVideo.h"
#endif

std::string NSDataExchange::g_LocationName = "";
bool NSDataExchange::g_bInCharge = false;


MB_VideoMgr::MB_VideoMgr()
{

}

MB_VideoMgr::~MB_VideoMgr()
{

}

void MB_VideoMgr::onFinishVideo()
{
	m_pLro->toPlayAnimation();
}

MB_VideoMgr* MB_VideoMgr::m_pShareVideoMgr = NULL;
MB_VideoMgr* MB_VideoMgr::getInstance()
{
	if (m_pShareVideoMgr == NULL){

		m_pShareVideoMgr = new MB_VideoMgr();
	}
	return m_pShareVideoMgr;
}
void MB_VideoMgr::playVideo(MB_LayerRewardOne* lro, int nStar)
{
	m_pLro = lro;
	const char* szVideoName;
	if (nStar == -1)//抽卡开场视频
	{
		szVideoName = "choukaBegain.mp4";
	}
	else if (nStar < 5)
		//小于5星抽卡视频
	{
		szVideoName = "chouka1.mp4";
	}
	else//大于等于5星抽卡视频
	{
		szVideoName = "chouka2.mp4";
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();

	char buff_class[256] = {0};
	char buff_methid_instance[256] = {0};

	sprintf(buff_class,"%s%s",JAVA_PACKAGE,"VideoMgr");
	jclass _jclass = (m_pEnv)->FindClass(buff_class);

	sprintf(buff_methid_instance,"()L%s;",buff_class);

	//查找方法ID
	jmethodID _jmethod_instacnce = (m_pEnv)->GetStaticMethodID(_jclass, "instance",buff_methid_instance);
	jmethodID _jmethod = (m_pEnv)->GetMethodID(_jclass, "playVideo", "(Ljava/lang/String;)V");

	//调用静态方法
	jobject _jobject_method_instacnce = (jobject) (m_pEnv)->CallStaticObjectMethod(_jclass, _jmethod_instacnce );

	//C->JAVA參數轉換
	jstring jVideoName = JavaCppHelper::getInstance()->stoJstring(m_pEnv,szVideoName);
	//调用成员方法
	m_pEnv->CallVoidMethod(_jobject_method_instacnce,_jmethod,jVideoName);

	//释放資源
	m_pEnv->DeleteLocalRef(_jclass);

	m_pEnv->DeleteLocalRef(jVideoName);
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	IOSPlayVideo::playVideoForIOS(szVideoName);
#endif
}
