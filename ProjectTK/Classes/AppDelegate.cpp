
#include "AppDelegate.h"

#include "Game.h"
#include "MB_SceneLoginBackground.h"
#include "MB_CommonType.h"

#include "MB_DataExchange.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "JavaCppHelper.h"
#endif
USING_NS_CC;
using namespace CocosDenshion; 
//static struct timeval startTime;

#include "Common/GameLib/CCDebugCodePage.h"
#include "MB_SystemMailData.h"

#ifdef YJ_IOS 
#include "MB_YJMgr_IOS.h"
#endif



AppDelegate::AppDelegate()
{
    global_tutorialNode = NULL;
    global_layerBackpack = NULL;
    global_layerItemDetail = NULL;
    global_sceneGame = NULL;
    global_layerPetEquipment = NULL;
    global_layerPetDetail = NULL;
    m_IsCanRetryGame = true;
    m_SceneGameIsSetLevelUI = false;
    nowHomeShowPetTypeID = CCUserDefault::sharedUserDefault()->getIntegerForKey("HomeShowPetTypeID", 0);;
    m_bIsCanToChapter = true;
	global_isYeShiJieToShop = false;
	global_isRePlay = false;
	m_bIsChangeRole = 0;
	isAutoTanChuSign = true;
	m_bIsToHome = false;
    m_bIsDemoFight = false;
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{

	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

#ifdef DISPLAY_FPS
	// turn on display FPS
	pDirector->setDisplayStats(false);
#else
	pDirector->setDisplayStats(false);
#endif


	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 30);

	srand(time(NULL));
	//NSGameHelper::RequestCityName();
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	CCSize designSize = CCSizeMake(640, 1136);
	CCFileUtils::sharedFileUtils()->addSearchPath("texture");
//    int ram  = JavaCppHelper::getInstance()->getMem();
//    if (screenSize.width >= 480 && ram >= 512)
//    {
//
//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
//        float  hwbit = screenSize.width / screenSize.height;
//        //iphone5
//        if (hwbit <=  0.5625) {
//
//            designSize= CCSizeMake(640,1136 );
//            CCSize resourceSize = CCSizeMake(640, 1136);
//
//            pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
//
//        }
//        //iphone-hd
//        else
//        {
//            CCSize resourceSize = CCSizeMake(640, 960);
//            pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
//        }
//    }
//    //iphone3gs
//    else
//    {
//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
//        float  hwbit = screenSize.width / screenSize.height;
//        //iphone5
//        if (hwbit <= 0.5625) {
//
//            designSize= CCSizeMake(640,1136 );
//            CCSize resourceSize = CCSizeMake(640,1136);
//            pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
//        }
//        else
//        {
//            CCSize resourceSize = CCSizeMake(640, 960);
//            pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
//        }
//    }
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
#else
	//******************添加分辨率和高清适配*******************************/
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize designSize = CCSizeMake(640, 960);
	CCFileUtils::sharedFileUtils()->addSearchPath("texture");


	//    float  hwbit = screenSize.width / screenSize.height;
	//   // CCLog("%f=====%f",screenSize.width,screenSize.height);
	//    if (hwbit < 0.666){
	//        designSize = CCSizeMake(640, 1136);
	//        CCSize resourceSize = CCSizeMake(640, 1136);
	//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
	//        pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
	//    }
	//    //ipad-hd & ipad
	//    else if (screenSize.width > 640)
	//    {
	//        CCSize resourceSize = CCSizeMake(750, 1334);
	//        designSize = CCSizeMake(750, 1334);
	//        //CCFileUtils::sharedFileUtils()->addSearchPath("resources-ipadhd");
	//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
	//        //        CCFileUtils::sharedFileUtils()->addSearchPath("resources-iphone");
	//
	//        pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
	//    }
	//    else if (screenSize.width > 320)
	//    {
	//
	//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
	//        float  hwbit = screenSize.width / screenSize.height;
	//        //iphone5
	//        if (screenSize.height >= 1136 && hwbit <= 0.5625) {
	//
	//            designSize = CCSizeMake(640, 1136);
	//            CCSize resourceSize = CCSizeMake(640, 1136);
	//            pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
	//
	//        }
	//        //iphone-hd
	//        else
	//        {
	//            CCSize resourceSize = CCSizeMake(640, 960);
	//            pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
	//        }
	//    }
	//    //iphone3gs
	//    else
	//    {
	//        CCFileUtils::sharedFileUtils()->addSearchPath("texture");
	//        CCSize resourceSize = CCSizeMake(640, 960);
	//        pDirector->setContentScaleFactor(resourceSize.height / designSize.height);
	//    }
	if (screenSize.height == 2436) {
		designSize = CCSizeMake(1242, 2208) / 2;
	}
	else if (screenSize.height == 1624 || screenSize.height == 1792) {
		designSize = CCSizeMake(640, 1136);
	}
	else if (screenSize.height > 1334) {
		designSize = CCSizeMake(screenSize.width, screenSize.height) / 2;
	}
	else{
		designSize = CCSizeMake(640, 1136);
	}

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
#endif
	CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
	//TODODO 回退资源版本
	//    CCUserDefault::sharedUserDefault()->setStringForKey("locationVersion", "1.2.1");
	SET_CHECKED_UPDATE(false);
	srand(time(NULL));
	//    MB_ActionData::getInstance()->testActionCcbFiles();
	NSDebugSpace::beginDebugCode();
	NSDebugSpace::endDebugCode();

	CCDirector::sharedDirector()->runWithScene(CCScene::create()); //不能删，安卓播放视频完毕，回调需要用到getRunningScene();

	goLogin();
	return true;
}


void AppDelegate::goLogin()
{
	CCLOG("goLogin");
	PlayBackGround(kmBackGround_Login);
	CCDirector* pDirector = CCDirector::sharedDirector();

	CCScene* pScene = MB_SceneLoginBackground::scene();
	if (pDirector->getRunningScene())
		pDirector->replaceScene(pScene);
	else
		pDirector->runWithScene(pScene);
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isGameInitOver")){

		MB_EventMgr::getInstence()->saveEvent();
	}
	//time_t curTime = time(NULL);
	//setTimeStamp(curTime);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
	if (MB_Audio::getInstance()->getBackGroundOpen()){

		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	if (MB_Audio::getInstance()->getEffectsoundOpen()){

		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
	// time_t curTime = time(NULL);
	// time_t timeDiv = curTime - getTimeStamp();
	// if (timeDiv > 300) {
	//     if (MB_ClientSocket::getInstance()->getCanAutoConnect() > 1)
	//     {
	//         MB_ClientSocket::getInstance()->getSocketHeartBit()->setHeartBitCount(4);
	//         MB_ClientSocket::getInstance()->getSocketHeartBit()->sendautoconnect();
	//     }
	// }
}
