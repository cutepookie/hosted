//
//  MB_YJMgr.cpp
//  ProjectTK
//
//  Created by WORKER on 13-8-21.
//
//

#include "MB_YJMgr.h"
#include "MB_DataExchange.h"
#include "JavaCppHelper.h"
#include "platform/android/jni/JniHelper.h"
#include  "OCandCppHelper.h"
#include <jni.h>
#include <android/log.h>
#include "MB_LayerFirstLogin.h"
#include <fcntl.h>
#ifdef __cplusplus
extern "C" {
#endif

	void __attribute__((visibility("default"))) ijiami(){

		char* cpuinfo = NULL;
		int cpuinfo_len;

		int fd, ret, result = 0;
		char buffer[256];

		fd = open("/proc/cpuinfo", 0x00);
		if (fd > 0) {

			for (;;) {
				int ret = read(fd, buffer, sizeof buffer);
				if (ret < 0) {
					break;
				}
				if (ret == 0)
					break;

				result += ret;
			}
			cpuinfo_len = result;
		}

		if (cpuinfo_len > 0) {

			cpuinfo = (char*)malloc(cpuinfo_len);
			if (cpuinfo != NULL) {

				int count = 0;
				while (count < cpuinfo_len) {
					int ret = read(fd, cpuinfo + count, cpuinfo_len - count);
					if (ret < 0) {

						if (count == 0)
							count = -1;
						break;
					}
					if (ret == 0)
						break;
					count += ret;
				}
			}
			free(cpuinfo);
			close(fd);
		}
	}

#ifdef __cplusplus
}
#endif


extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JNIEXPORT void JNICALL Java_com_zdbpkq_bt_YJSDKManager_login(JNIEnv *env, jobject thiz,jstring appId,jstring channelId,jstring userId,jstring token )
	{
		MB_YJMgr::getInstance()->login(JavaCppHelper::getInstance()->jstringTostring(env, appId),JavaCppHelper::getInstance()->jstringTostring(env, channelId),JavaCppHelper::getInstance()->jstringTostring(env, userId),JavaCppHelper::getInstance()->jstringTostring(env, token));
	}
	JNIEXPORT void JNICALL Java_com_zdbpkq_bt_YJSDKManager_goLogout(JNIEnv *env, jobject thiz)
	{
		MB_YJMgr::getInstance()->logout();
	}
	JNIEXPORT void JNICALL Java_com_zdbpkq_bt_YJSDKManager_goChangeRole(JNIEnv *env, jobject thiz,jstring appId,jstring channelId,jstring userId,jstring token)
	{
		m_bIsChangeRole = 1;
		change_appid = JavaCppHelper::getInstance()->jstringTostring(env, appId);
		change_channelid = JavaCppHelper::getInstance()->jstringTostring(env, channelId);
		change_userid = JavaCppHelper::getInstance()->jstringTostring(env, userId);
		change_token = JavaCppHelper::getInstance()->jstringTostring(env, token);
		MB_YJMgr::getInstance()->logout();
	}
	JNIEXPORT void JNICALL Java_com_zdbpkq_bt_VideoMgr_onFinishVideo(JNIEnv *env, jobject thiz)
	{
		MB_VideoMgr::getInstance()->onFinishVideo();
	}
#endif
}
MB_YJMgr::MB_YJMgr(){

	m_pDelegate = NULL;
	strcpy(sid, "");
	sid[0] = '\0';

}
MB_YJMgr::~MB_YJMgr(){

	m_pDelegate = NULL;
}
void MB_YJMgr::login(char* appid, char* channelid, char* userid, char* token){
	strcpy(sid, userid);
	if (m_pDelegate) {


		MB_LayerFirstLogin *layer;
		layer = dynamic_cast<MB_LayerFirstLogin *>(m_pDelegate);
		if (layer) {
			layer->onLoginStart(appid, channelid,
				userid, token);
		}
		return;

	}
	if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN) == NULL){

		CCDirector::sharedDirector()->popToRootScene();
	}
	MB_RoleData::destroyInstance();
	MB_ServerList::destroyInstance();
	MB_ClientSocket::destroyInstance();
	CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
	CCScene *pScene = MB_SceneLoginBackground::scene();
	CCDirector::sharedDirector()->popToRootScene();
	CCDirector::sharedDirector()->replaceScene(pScene);

	MB_LayerFirstLogin *layer;
	layer = dynamic_cast<MB_LayerFirstLogin *>(m_pDelegate);
	if (layer) {
		layer->onLoginStart(sid);
	}

}
bool MB_YJMgr::hasLogin(){

	int len = strlen(sid);
	return len > 0;
}
void MB_YJMgr::logout(){
	if (strlen(sid) > 1){

		distroy();


		sid[0] = '\0';

		MB_RoleData::destroyInstance();
		MB_ServerList::destroyInstance();
		MB_ClientSocket::destroyInstance();
		CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
		CCScene *pScene = MB_SceneLoginBackground::scene();
		CCDirector::sharedDirector()->popToRootScene();
		CCDirector::sharedDirector()->replaceScene(pScene);
		PlayBackGround(kmBackGround_Normal);
	}
}
void  MB_YJMgr::onGuestToNormal(){

	CCDirector::sharedDirector()->getRunningScene()->onEnter();
}
void MB_YJMgr::registDelegate(CCObject *delegate){

	m_pDelegate = delegate;
}
void MB_YJMgr::unregistDelegate(CCObject *delegate){

	if (m_pDelegate == delegate){

		m_pDelegate = NULL;
	}
}
MB_YJMgr* MB_YJMgr::getInstance(){

	if (m_pShareUCManager == NULL){

		m_pShareUCManager = new MB_YJMgr();
	}
	return m_pShareUCManager;
}
void MB_YJMgr::distroy(){

	if (m_pShareUCManager != NULL) {

		delete  m_pShareUCManager;
		m_pShareUCManager = NULL;
	}

}
int  MB_YJMgr::getCurrentLoginState(){

	return  false;
}

void MB_YJMgr::openurl()
{
	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";
	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID login = (m_pEnv)->GetMethodID(javaHelper, "openurl", "()V");
	(m_pEnv)->CallVoidMethod(myObject, login);
	m_pEnv->DeleteLocalRef(javaHelper);
}

void MB_YJMgr::goLogin(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";
	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID login = (m_pEnv)->GetMethodID(javaHelper, "gologin", "()V");
	(m_pEnv)->CallVoidMethod(myObject, login);
	m_pEnv->DeleteLocalRef(javaHelper);

}
bool  MB_YJMgr::isAutoLogin(){

	return     false;
}
void MB_YJMgr::goLogout(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";
	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID login = (m_pEnv)->GetMethodID(javaHelper, "logout", "()V");
	(m_pEnv)->CallVoidMethod(myObject, login);
	m_pEnv->DeleteLocalRef(javaHelper);
	logout();
}
void MB_YJMgr::goBuylist(){


}
void MB_YJMgr::goRegist(){

}
void MB_YJMgr::goLogin(const char *sid){

}
void MB_YJMgr::onBuyCancle(){
}
void MB_YJMgr::setPay(const char * payid){

	MB_Message::sharedMB_Message()->removeALLMessage();
	int amount = 0;
	char payinfo[100];
	char roleid[100];
	CCArray* payArray = MB_RoleData::getInstance()->getPayArray();
	CCObject * obj;
	int tag = atoi(payid);
	CCARRAY_FOREACH(payArray, obj){

		MB_PayTemplete *templete = (MB_PayTemplete *)obj;
		if (templete->getID() == tag) {

			amount = templete->getPrice();
			sprintf(payinfo, "%d", templete->getID());
			break;
		}
	}




	sprintf(roleid, "%d", MB_RoleData::getInstance()->getUID());

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";

	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID pay = (m_pEnv)->GetMethodID(javaHelper, "pay", "(IILjava/lang/String;Ljava/lang/String;)V");

	jstring jroleid = JavaCppHelper::getInstance()->stoJstring(m_pEnv, roleid);
	jstring jpayinfo = JavaCppHelper::getInstance()->stoJstring(m_pEnv, payinfo);
	(m_pEnv)->CallVoidMethod(myObject, pay, amount, MB_ServerList::getInstance()->getNowServerID(), jroleid, jpayinfo);
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jroleid);
	m_pEnv->DeleteLocalRef(jpayinfo);
}
void  MB_YJMgr::creatRole(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";

	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID pay = (m_pEnv)->GetMethodID(javaHelper, "createRole", "(Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;I)V");

	char databuf[100];
	sprintf(databuf, "%d", MB_RoleData::getInstance()->getUID());
	jstring jroleid = JavaCppHelper::getInstance()->stoJstring(m_pEnv, databuf);
	jstring jrolename = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_RoleData::getInstance()->getName());
	jstring jservername = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_ServerList::getInstance()->getNowServerName());
	(m_pEnv)->CallVoidMethod(myObject, pay, jroleid, jrolename, MB_RoleData::getInstance()->getLevel(), MB_ServerList::getInstance()->getNowServerID(), jservername, MB_RoleData::getInstance()->getVipLevel());
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jroleid);
	m_pEnv->DeleteLocalRef(jrolename);
	m_pEnv->DeleteLocalRef(jservername);
}
void  MB_YJMgr::enterGame(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";

	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID pay = (m_pEnv)->GetMethodID(javaHelper, "enterGame", "(Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;I)V");

	char databuf[100];
	sprintf(databuf, "%d", MB_RoleData::getInstance()->getUID());
	jstring jroleid = JavaCppHelper::getInstance()->stoJstring(m_pEnv, databuf);
	jstring jrolename = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_RoleData::getInstance()->getName());
	jstring jservername = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_ServerList::getInstance()->getNowServerName());
	(m_pEnv)->CallVoidMethod(myObject, pay, jroleid, jrolename, MB_RoleData::getInstance()->getLevel(), MB_ServerList::getInstance()->getNowServerID(), jservername, MB_RoleData::getInstance()->getVipLevel());
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jroleid);
	m_pEnv->DeleteLocalRef(jrolename);
	m_pEnv->DeleteLocalRef(jservername);
}
void  MB_YJMgr::roleLevelUp(){

	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";

	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID pay = (m_pEnv)->GetMethodID(javaHelper, "roleLevelUp", "(Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;I)V");

	char databuf[100];
	sprintf(databuf, "%d", MB_RoleData::getInstance()->getUID());
	jstring jroleid = JavaCppHelper::getInstance()->stoJstring(m_pEnv, databuf);
	jstring jrolename = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_RoleData::getInstance()->getName());
	jstring jservername = JavaCppHelper::getInstance()->stoJstring(m_pEnv, MB_ServerList::getInstance()->getNowServerName());
	(m_pEnv)->CallVoidMethod(myObject, pay, jroleid, jrolename, MB_RoleData::getInstance()->getLevel(), MB_ServerList::getInstance()->getNowServerID(), jservername, MB_RoleData::getInstance()->getVipLevel());
	m_pEnv->DeleteLocalRef(javaHelper);
	m_pEnv->DeleteLocalRef(jroleid);
	m_pEnv->DeleteLocalRef(jrolename);
	m_pEnv->DeleteLocalRef(jservername);
}

void MB_YJMgr::quitGame()
{
	JNIEnv*  m_pEnv = JavaCppHelper::getInstance()->getEnv();
	std::string package = CCUserDefault::sharedUserDefault()->getStringForKey("PACKEAGE");
	package += "YJSDKManager";
	jclass javaHelper = (m_pEnv)->FindClass(package.c_str());
	std::string stringback = "()L";
	stringback += package;
	stringback += ";";
	jmethodID getInstence = (m_pEnv)->GetStaticMethodID(javaHelper, "instance", stringback.c_str());
	jobject myObject = (jobject)(m_pEnv)->CallStaticObjectMethod(javaHelper, getInstence);
	jmethodID _quitGame = (m_pEnv)->GetMethodID(javaHelper, "quitGame", "()V");
	(m_pEnv)->CallVoidMethod(myObject, _quitGame);
	m_pEnv->DeleteLocalRef(javaHelper);
}

void MB_YJMgr::onBuySuccess(const char *receipt, int payid, const char *deviceid){

	//MB_RoleData::getInstance()->cs_role_pay_91(receipt,payid, deviceid);
}
void MB_YJMgr::onBuyFail(){

	if (m_pDelegate) {

		MB_Message::sharedMB_Message()->removeALLMessage();
		MB_Message::sharedMB_Message()->showMessage("网络错误，下次验证。");

	}
}
void MB_YJMgr::openUC(){



}
void MB_YJMgr::openBBS(){

}
void MB_YJMgr::openFAQ(){


}
void MB_YJMgr::checkSuccess(const char *receipt){

	// [[MB_91IAP instance] removeRecord: [NSString stringWithUTF8String:receipt]];
}
void MB_YJMgr::setIsShowFloatButton(bool isshow){

	//[UCGameSdk defaultSDK].isShowFloatButton = isshow;
}
void MB_YJMgr::setIsShowFloatButton(CCPoint &pos){

	//[UCGameSdk defaultSDK].floatButtonPosition = CGPointMake(pos.x, pos.y);

}
void MB_YJMgr::EnterBackGroud(){

	OCandCppHelper::EnterBackGroud();
}
void MB_YJMgr::EnterFront(){

	OCandCppHelper::EnterFront();
}

void MB_YJMgr::removeLoading()
{
	MB_Message::sharedMB_Message()->removeALLMessage();
}
MB_YJMgr * MB_YJMgr::m_pShareUCManager = NULL;
