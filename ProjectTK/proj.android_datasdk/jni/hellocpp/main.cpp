#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include "JavaCppHelper.h"
#include "MB_YJMgr.h"
#include <jni.h>
#include <android/log.h>

#include "../../../Classes/Game/MB_DataExchange.h"
#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern bool InitUiTestSupport(); //TestBird UI

extern "C" {

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JniHelper::setJavaVM(vm);

	return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv* env,
		jobject thiz, jint w, jint h) {
	CCUserDefault::sharedUserDefault()->setStringForKey("PACKEAGE",
			"com/zdbpkq/bt/");
	JavaCppHelper::getInstance()->setEnv(env);
	if (!CCDirector::sharedDirector()->getOpenGLView()) {
		CCEGLView *view = CCEGLView::sharedOpenGLView();
		view->setFrameSize(w, h);

		AppDelegate *pAppDelegate = new AppDelegate();

//        InitUiTestSupport();

		CCApplication::sharedApplication()->run();

	}
	//else {
//		ccDrawInit();
//		ccGLInvalidateStateCache();
//
//		CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
//		CCTextureCache::reloadAllTextures();
//		CCNotificationCenter::sharedNotificationCenter()->postNotification(
//				EVNET_COME_TO_FOREGROUND, NULL);
//		CCDirector::sharedDirector()->setGLDefaultValues();
//	}
}
//void Java_com_yueyou_common_ProjectMB_weiXinSuccess(JNIEnv* env, jobject thiz) {
//
//	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
//	scene->runAction(
//			CCCallFunc::create(TK_WeChatManager::getInstance(),
//					callfunc_selector(TK_WeChatManager::onSendSuccess)));
//}

//void Java_com_yueyou_common_ZZSDKManager_login(JNIEnv* env, jobject thiz,
//		jstring str) {
//
//	char *strid = JavaCppHelper::getInstance()->jstringTostring(env, str);
//	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
//	CCAction *action = CCCallFuncO::create(TK_ZZManager::getInstance(),
//			callfuncO_selector(TK_ZZManager::login), CCString::create(strid));
//	scene->runAction(action);
//	CC_SAFE_DELETE_ARRAY(strid);
//}
//void Java_com_yueyou_common_ZZSDKManager_payFail(JNIEnv* env, jobject thiz) {
//
//	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
//	CCAction *action = CCCallFunc::create(TK_ZZManager::getInstance(),
//			callfunc_selector(TK_ZZManager::onBuyFail));
//	scene->runAction(action);
//}
//void Java_com_yueyou_common_ZZSDKManager_payCancel(JNIEnv* env, jobject thiz) {
//
//	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
//	CCAction *action = CCCallFunc::create(TK_ZZManager::getInstance(),
//			callfunc_selector(TK_ZZManager::onBuyCancle));
//	scene->runAction(action);
//}


void Java_com_yueyou_common_YJSDKManager_login(JNIEnv* env, jobject thiz,
		jstring id,jstring key,jstring type, jstring token) {

	LOGI("YYBSDK Java_com_yueyou_common_YJSDKManager_login");

	LOGI("MB_YJMgr -> login a ");

	CCArray *array = CCArray::create();

	char *struid = JavaCppHelper::getInstance()->jstringTostring(env, id);

	LOGI("MB_YJMgr -> login b ");

	CCString *cstruid = CCString::create(struid);
	array->addObject(cstruid);
	char *strkey = JavaCppHelper::getInstance()->jstringTostring(env, key);
	LOGI("MB_YJMgr -> login c ");
	CCString *cstrkey = CCString::create(strkey);
	array->addObject(cstrkey);
	char *strtype = JavaCppHelper::getInstance()->jstringTostring(env, type);
	LOGI("MB_YJMgr -> login d ");
	CCString *cstrtype = CCString::create(strtype);
	array->addObject(cstrtype);
	char *strtoken = JavaCppHelper::getInstance()->jstringTostring(env, token);

	if(strtoken == NULL) {

		CCString *cstrtoken = CCString::create("");
		LOGI("MB_YJMgr -> login e 1");
		array->addObject(cstrtoken);

	}
	else {
			//LOGI("MB_YJMgr -> login e %s",strtoken);
		CCString *cstrtoken = CCString::create(strtoken);
		LOGI("MB_YJMgr -> login e 1");
		array->addObject(cstrtoken);
		LOGI("MB_YJMgr -> login e 2");
		LOGI("MB_YJMgr -> login f ");
	}




	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	LOGI("MB_YJMgr -> login f 1");
	CCAction *action = CCCallFuncO::create(MB_YJMgr::getInstance(),
			callfuncO_selector(MB_YJMgr::login),array);

	LOGI("MB_YJMgr -> login f 2");

	scene->runAction(action);
	LOGI("MB_YJMgr -> login f 3");
	CC_SAFE_DELETE_ARRAY(struid);
	CC_SAFE_DELETE_ARRAY(strkey);
	CC_SAFE_DELETE_ARRAY(strtype);
	if(strtoken != NULL )
		CC_SAFE_DELETE_ARRAY(strtoken);

	LOGI("MB_YJMgr -> login f4 ");
}
void Java_com_yueyou_common_YJSDKManager_payFail(JNIEnv* env, jobject thiz) {

	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	CCAction *action = CCCallFunc::create(MB_YJMgr::getInstance(),
			callfunc_selector(MB_YJMgr::onBuyFail));
	scene->runAction(action);
}
void Java_com_yueyou_common_YJSDKManager_payCancel(JNIEnv* env, jobject thiz) {

	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	CCAction *action = CCCallFunc::create(MB_YJMgr::getInstance(),
			callfunc_selector(MB_YJMgr::onBuyCancle));
	scene->runAction(action);
}
void Java_com_yueyou_common_YJSDKManager_goLogout(JNIEnv* env, jobject thiz)
{
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	CCAction *action = CCCallFunc::create(MB_YJMgr::getInstance(),
			callfunc_selector(MB_YJMgr::goLogout));
	scene->runAction(action);
}
void Java_com_yueyou_common_YJSDKManager_removeLoading(JNIEnv* env, jobject thiz){

     CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
     CCAction *action = CCCallFunc::create(MB_YJMgr::getInstance(),callfunc_selector(MB_YJMgr::removeLoading));
     scene->runAction(action);
 }
char* jstringTostring(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

void Java_com_yueyou_common_YJSDKManager_playVideo(JNIEnv* env,jobject thiz)
{
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	scene->runAction(CCCallFunc::create(MB_VideoMgr::getInstance(),callfunc_selector(MB_VideoMgr::playVideo)));
}

//设置城市名字
void Java_com_yueyou_common_LocationHelper_SetCityName(JNIEnv* env,
		jobject thiz, jstring cityName) {
	char *strid = JavaCppHelper::getInstance()->jstringTostring(env, cityName);
	NSDataExchange::g_LocationName = strid;
	CC_SAFE_DELETE_ARRAY(strid);
}

//视频播放完毕
void Java_com_yueyou_common_VideoMgr_onFinishVideo(JNIEnv* env,jobject thiz)
{
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	scene->runAction(CCCallFunc::create(MB_VideoMgr::getInstance(),callfunc_selector(MB_VideoMgr::onFinishVideo)));
}


}

