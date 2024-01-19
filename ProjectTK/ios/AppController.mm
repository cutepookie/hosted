#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "Game.h"
#ifdef PLATFORM_91
#import "MB_91Mgr.h"
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NDComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#include "MB_LayerFirstLogin.h"
#endif
#ifdef PLATFORM_UC
#include "TK_UCManager.h"
#endif
#ifdef PLATFORM_DL
#include "TK_DLManager.h"
#include <DownjoySDK_framework/DJPlatform.h>
#include <DownjoySDK_framework/DJPlatformMemberInfo.h>
#include <DownjoySDK_framework/DJPlatformNotify.h>
#endif
#ifdef PLATFORM_ZZ
#include "TK_ZZManager.h"
#import <Cmge/Cmge.h>
#import <Cmge/CmgePlatformNotification.h>
#endif
#ifdef PLATFORM_PP
#include "MB_PPMgr.h"
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#endif
#ifdef PLATFORM_KY
#include "MB_KYMgr.h"
#define KY_UNKNOWN 0
#define KY_INSTALLED 1
#define KY_INST_REPORTED 2
#define KY_REPORT_FAIL 0
#define KY_REPORT_SUCC 1
extern int ky_installed();
#endif
#ifdef PLATFORM_IT
#import "HXAppPlatformKitPro.h"
#include "MB_ITMgr.h"
#endif
#ifdef PLATFORM_TBT
#import <TBPlatform/TBPlatform.h>
#include "MB_TBTMgr.h"
#endif
#ifdef PLATFORM_DJX
#import <DJGame/DJGame.h>
#include "TK_DJXManager.h"
#endif
#ifdef PLATFORM_I4
#import <AsSdkFMWK/AsInfoKit.h>
#import <AsSdkFMWK/AsPlatformSDK.h>
#include "MB_I4Mgr.h"
#endif
#ifdef PLATFORM_SM
#include "TK_SMManager.h"
#include "JorgSDK.h"
#endif

#ifdef PLATFORM_HM
#import <AiBeiFramework/IPAYKit.h>
#include "MB_HMMgr.h"
#endif
#ifdef PLATFORM_IPG
#import "IIApple.h"
#include "MB_IPGMgr.h"
#endif

#ifdef PLATFORM_APPSTORE
#import <StoreKit/StoreKit.h>
#import <GameKit/GameKit.h>
#include "MB_AppStoreMgr.h"
#import "ErrorWebView.h"
#endif

#ifdef PLATFORM_QD
#import <HoyoFramework/DJPlatform.h>
#import <HoyoFramework/DJPlatformNotify.h>
#import <HoyoFramework/DJPlatformMemberInfo.h>
#include "TK_QDManager.h"
#endif
#include "MB_DataExchange.h"
#import <AdSupport/AdSupport.h>
#import <AdSupport/ASIdentifierManager.h>
//#import "DCAgent.h"
//#define URL_POST_ADDRESS @"http://triggertk.crimoon.net:11000/active?mac=%s&idfa=%@"
#define LAYER_TAG_FOR_UPDATE 3
#define LAYER_TAG_UPDATE 2
#define LAYER_TAG_WIFI 1
#define LAYER_TAG_KY_UPDATE_1 11
@implementation AppController

@synthesize window;
@synthesize viewController;


static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{
    
#ifdef PLATFORM_XY
    [XYPlatform defaultPlatform];
#endif
    
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
#ifdef PLATFORM_ZZ
    CmgeProject *project = [[[CmgeProject alloc] init] autorelease];
    project.projectId = ZZ_PROJECTID;
    project.gameId = ZZ_GAMEID;
    project.serverId = ZZ_SERVERID;
    project.gameKey = ZZ_GAMEKEY;
    project.clientId = ZZ_GAMEKEY;
    project.redirectUri = @"1";
    project.isOnlineGame = YES;
    project.openAntiAddiction = NO;
    project.openPublicVersion= NO;
    [[CmgePlatform defaultPlatform] setProject:project];
    [[CmgePlatform defaultPlatform] setViewOrientation:UIInterfaceOrientationMaskPortrait];
#endif
    
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    
    [__glView setMultipleTouchEnabled:NO];

    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        [window addSubview: viewController.view];
         window.rootViewController = viewController;
    }
    else
    {
        [window setRootViewController:viewController];
    }

    [window makeKeyAndVisible];
    [[UIApplication sharedApplication]setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    
    [CCVideoPlayer setDelegate :self];
    
//    [DCAgent setReportMode:DC_AFTER_LOGIN];
//    [DCAgent setDebugMode:NO];
//    [DCAgent onStart:@"EA16A8CA3373B3B0ACC80ADF53A4320A" withChannelId:@"DataEye"];
    
    #ifdef PLATFORM_91
    [self checkWiFi];
    #elif defined(PLATFORM_UC)
    [self checkWiFiUC];
    #elif defined(PLATFORM_DL)
    [self checkWiFiDL];
    #elif defined(PLATFORM_ZZ)
    [self checkWiFiZZ];
    #elif defined(PLATFORM_PP)
    [self checkWiFiPP];
    #elif defined(PLATFORM_KY)
    [self checkWiFiKY];
    #elif defined(PLATFORM_IT)
    [self checkWiFiIT];
    #elif defined(PLATFORM_TBT)
    [self checkWiFiTBT];
    #elif defined(PLATFORM_DJX)
    [self checkWiFiDJX];
    #elif defined(PLATFORM_I4)
    [self checkWiFiI4];
    #elif defined(PLATFORM_SM)
    [self checkWiFiSM];
    #elif defined(PLATFORM_XY)
    [self checkWiFiXY];
    #elif defined(PLATFORM_QD)
    [self checkWiFiQD];
    #elif defined(PLATFORM_HM)
    [self checkWiFiHM];
    #elif defined(PLATFORM_IPG)
    [self checkWiFiIPG];
    #elif defined(PLATFORM_HJR)
    [self checkWiFiHJR];
    #elif defined(PLATFORM_APPSTORE)
    [self checkWiFiAppStore];
    #else
    /** 注册推送通知功能, */
    cocos2d::CCApplication::sharedApplication()->run();
	[[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound)];
    #endif

    return YES;
}




-(void)playVideo: (NSString *) file
{
    [CCVideoPlayer cancelPlaying];
    [CCVideoPlayer setNoSkip: NO];//视频是否可以跳过
    [CCVideoPlayer playMovieWithFile: file];//播放视频
//    [CCVideoPlayer updateOrientationWithOrientation:UIDeviceOrientationLandscapeRight];
}
- (void) moviePlaybackFinished
{
    MB_VideoMgr::getInstance()->onFinishVideo();
}
- (void) movieStartsPlaying
{
}
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
- (void) updateOrientationWithOrientation: (UIDeviceOrientation) newOrientation
{
    [CCVideoPlayer updateOrientationWithOrientation:newOrientation ];
}
#endif


- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    UIAlertView *alert=[[UIAlertView alloc]initWithTitle:@"通知" message: [userInfo objectForKey:@"alert"] delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil, nil];
    [alert show];
    [alert release];
   
    NSLog(@"%@", userInfo);
}
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(@"Regist fail%@",error);    
}
-(void) application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    NSLog(@"message %@",notification.alertBody);
    application.applicationIconBadgeNumber -= 1;
}
-(void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    NSString* token = [NSString stringWithFormat:@"%@",deviceToken];
    token =[[token stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]] stringByReplacingOccurrencesOfString:@" " withString:@""];
    token =[token  stringByReplacingOccurrencesOfString:@"<" withString:@""];
    token =[token  stringByReplacingOccurrencesOfString:@">" withString:@""];
	NSLog(@"apns -> 生成的devToken:%@", token);
    const char *str =[token UTF8String];
    OCandCppHelper::setDeviceTocken(str);
}

- (void)applicationWillResignActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->pause();
}
- (void)applicationDidBecomeActive:(UIApplication *)application {
    
#ifdef PLATFORM_HJR
    //游戏继续 渠道接口检测
    if ([[GameKitSDK defaultSdk] hasProvide_response_continueEvent_service]) {
        [[GameKitSDK defaultSdk] gameContinueEvent];
    }
#endif
    
    cocos2d::CCDirector::sharedDirector()->resume();
}
- (void)applicationDidEnterBackground:(UIApplication *)application {
    
#ifdef PLATFORM_HJR
    //暂停游戏 渠道接口检测
    if ([[GameKitSDK defaultSdk] hasProvide_response_suspendEvent_service]) {
        [[GameKitSDK defaultSdk] gameSuspendEvent];
    }
#endif
    
    [CCVideoPlayer pause];
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
    //OCandCppHelper::EnterBackGroud();
}
- (void)applicationWillEnterForeground:(UIApplication *)application {
    #ifdef PLATFORM_91
    [[NdComPlatform defaultPlatform] NdPause];
    #endif
    [CCVideoPlayer resume];
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    //OCandCppHelper::EnterFront();
}
- (void)applicationWillTerminate:(UIApplication *)application {
    
#ifdef PLATFORM_HJR
    //游戏停止 渠道接口检测
    if ([[GameKitSDK defaultSdk] hasProvide_response_stopEvent_service]) {
        [[GameKitSDK defaultSdk] gameStopEvent];
    }
#endif
    
}
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
#ifdef PLATFORM_XY
    [[XYPlatform defaultPlatform] XYHandleOpenURL:url];
#endif
#ifdef PLATFORM_KY
    [[NSNotificationCenter defaultCenter] postNotificationName:@"KY_NOTIFICATION" object:url];
#endif
    
#ifdef PLATFORM_HJR
    // 检测接口可用
    if ([[GameKitSDK defaultSdk] hasProvide_response_openurl_service]) {
        [[GameKitSDK defaultSdk] application:application openURL:url sourceApplication:nil annotation:nil];
    }
#endif
    
#ifdef PLATFORM_PP
    [[PPAppPlatformKit sharedInstance] alixPayResult:url];
#endif
    
#ifdef PLATFORM_HM
//    [[IPAYiAppPay sharediAppPay] handleOpenurl: url];
    [[IPAYKit sharedInstance] handleOpenurl:url];
#endif
    return  YES;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
#ifdef PLATFORM_XY
    [[XYPlatform defaultPlatform] XYHandleOpenURL:url];
#endif
#ifdef PLATFORM_HM
//    [[IPAYiAppPay sharediAppPay] handleOpenurl: url];
    [[IPAYKit sharedInstance] handleOpenurl:url];
#endif
#ifdef PLATFORM_IPG
    [IIApple application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
#endif

    
#ifdef PLATFORM_I4
    [[AsInfoKit sharedInstance] payResult:url sourceApplication:sourceApplication];
#endif
    
#ifdef PLATFORM_HJR
    //检测接口可用
    if ([[GameKitSDK defaultSdk] hasProvide_response_openurl_service]) {
        [[GameKitSDK defaultSdk] application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    }
#endif
    
    return  true;
}
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    NSLog(@"warning memerory.........");
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}
- (void)dealloc
{
    [super dealloc];
}
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(alertView.tag == LAYER_TAG_WIFI)
    {
        if(buttonIndex == 0){
            
#ifdef PLATFORM_91
            [self checkWiFi];
#endif
#ifdef PLATFORM_UC
           [self checkWiFiUC];
#endif  
#ifdef PLATFORM_DL
            [self checkWiFiDL];
#endif
#ifdef PLATFORM_ZZ
            [self checkWiFiZZ];
#endif
#ifdef PLATFORM_PP
            [self checkWiFiPP];
#endif
#ifdef PLATFORM_KY
            [self checkWiFiKY];
#endif
#ifdef PLATFORM_IT
            [self checkWiFiIT];
#endif
#ifdef PLATFORM_TBT
            [self checkWiFiTBT];
#endif
#ifdef PLATFORM_DJX
            [self checkWiFiDJX];
#endif
#ifdef PLATFORM_I4
            [self checkWiFiI4];
#endif
#ifdef PLATFORM_SM
            [self checkWiFiSM];
#endif
#ifdef PLATFORM_XY
            [self checkWiFiXY];
#endif
#ifdef PLATFORM_QD
            [self checkWiFiQD];
#endif
        }else
        {
            abort();
        }
    }if (alertView.tag == LAYER_TAG_FOR_UPDATE) {
    }else if (alertView.tag == LAYER_TAG_UPDATE) {
    }else if(alertView.tag == LAYER_TAG_KY_UPDATE_1)
    {
    }
}


#ifdef PLATFORM_HM
-(void)checkWiFiHM
{
    if(OCandCppHelper::isconnect3G())
    {
        BOOL b = NO;
        if (![[IPAYKit sharedInstance]checkSetOK])
        {
            b = [[IPAYKit sharedInstance]setAppId:@"3001738887"
                                      channel:nil
                                        urls:[NSDictionary dictionaryWithObjectsAndKeys:@"ipayalipay-com.moongame.pkq.hm",@"kKEY_CALLBACK_URL_ALIPAY",nil]
                                privateKey:@"MIICXAIBAAKBgQCH09Ih29XaRtjGqxZKeuTQ0ovrkI3YOWAL1wAx5OWgFHjhCAC6eda+OimJIKdrFCPnCScOsCfFtaDNvGaLUPH84EFhX5A9vrtZH4bmW2U5Ed2guzyo4/9iDW5ctVUMtoKcJ+ihxZA7XCvnFZtjkHC6h9a5Ryw9YImF08PUtYAmOwIDAQABAoGAfLGcVpMgB2xE9FX6d9PMnly8MT0ayycZIqV1u1hc6hIBSu1y5b6WwzpYCVid+fKaZy6C2bwkNyBgCJ/uL/XWwK6MwTfN+xyLnCapdVphKH3wIBU8qYeyHzINdyR2RhU7i1xBjFjqR924dKn9IjYFeoGLD+bkIz1OIkHsHD2htLECQQC/ZmOzAaYcThJ0yZ9J5wCWAen3d6pai1KYXTgDS9CcoV819mc1rBO7XOGra3JjAjfmNDDBmcjHXBYjUrO94siTAkEAtavGSOelFQowDPeHLKEJCmFEyRFqGdatnRYbqZeq3CVomhX3yF1d7yzd9fsT2tKmDcswBd80urwchGWupnJ8uQJBAJFkvielAQJPbEW7Q31oNVG+cnTCOm49l6iWZ45ZcUcKbsEXRJ/I79RMYkFNhb8gWEZPLxpiL9sBYO/ESzXbqHECQFLWN3you1pjodNXzrgn2ZJ1FcNFAIc1n0ZgfU6QTKVDHXYdDDW9dQaJA9CUotIFeRgTDRuwUj/PZIVuQ/u7emkCQCgECzrrkBJjHoD16ROe8BsrU3ZDrWhpFTkiXS1AikLYbp9d7HRtEt3BnUyf8TMthB4J8Dm9tUaNef34DFX6M/I="
                                  payDelegate:self
                                loginDelegate:self];
        }
        
        [[HmcpUpdate sharedUpdate]setLogEnable:NO];
        [[HmcpUpdate sharedUpdate]checkUpdateForTest:NO delegate:self];
        
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

- (void)loginDidFail
{
}
- (void)loginDidCancel
{
}

- (void)loginDidSuccessWithUserName:(NSString *)userName andTempToken:(NSString *)tempToken
{
    MB_HMMgr::getInstance()->login([userName UTF8String],[tempToken UTF8String]);
}


- (void)checkUpdateFinish:(BOOL)isSuccess shouldUpdate:(BOOL)update isForceUpdate:(BOOL)force
{
    NSLog(@"检查是否请求成功：%d 是否有新版本：%d 是否需要强更：%d",isSuccess,update,force);
}

-(void)paymentStatusCode:(IPAYKITPaymentStatusCodeType)statusCode signature:(NSString *)signature resultInfo:(NSString *)resultInfo
{
}

#endif

#ifdef PLATFORM_IPG
-(void)checkWiFiIPG{
    if(OCandCppHelper::isconnect3G()){
        //获取info配置的版本号
        NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
        NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
        NSString* version = [data objectForKey:@"CFBundleVersion"];
        NSLog(@"%@", version);//直接打印数据。

        NSDictionary* dic=[NSDictionary dictionaryWithObjectsAndKeys:
                           @"8d49be89e102ed7c7abe2442eece3553",@"gameKey",
                           @"1001000101",@"channelId",
                           @"1",@"isVer", //"0":横版游戏, "1":竖版游戏
                           @"1",@"isShowATView",
                           @"com.moongame.pkq.ipg",@"alipayScheme",//”支付宝URL Scheme”,游戏方自行添加，与info.plist内URL Types设置相同。
                           @"67aa32f6004924cc8b79f7bcc90839eb",@"cuKey",
                           version,@"gameVersion",
                           @"0",@"isRepeatPay",
                           @"1",@"isLastXcode6", //Xcode版本是否大于等于6
                           nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginSucceed:) name:IALOGINSUCCEED object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(logout:) name:IALOGOUTSUCCEED object:nil];
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginInFail:) name:IALOGINFAIL object:nil];
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(closeLoginView:) name:IACLOSELOGINVIEW object:nil];
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(closeUserenterView:) name:IACLOSEUSERCENTERVIEW object:nil];
        
        [IIApple initIiappleWithDic:dic];//sdk初始化
        
        [IIApple checkUpdate];//检查版本更新

        cocos2d::CCApplication::sharedApplication()->run();
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

-(void)loginSucceed:(NSNotification *)noti
{
    NSDictionary* dic=noti.object;

    NSString* session=[dic objectForKey:@"session"];

    NSString* userid=[dic objectForKey:@"userid"];

    //使用参数按照服务器验证文档，去服务器验证账号是否为iiapple账号
    
     MB_IPGMgr::getInstance()->login([userid UTF8String],[session UTF8String]);
}
-(void)logout:(NSNotification*)noti
{
    MB_IPGMgr::getInstance()->logout();
}
#endif

#ifdef PLATFORM_DJX
-(void)checkWiFiDJX{
    
    if(OCandCppHelper::isconnect3G()){
        
        [[DPayPlatform defaultPlatform] setAppId:DJXAPPID andAppKey:DJXAPPKEY];
        [[DPayPlatform defaultPlatform] setViewOrientation: UIInterfaceOrientationPortrait];
        [[DPayPlatform defaultPlatform] setViewAutoRotate:NO];
        [[DPayPlatform defaultPlatform] setNavigationItemVisible:YES];
        [[DPayPlatform defaultPlatform] setGuestAccountEnable:NO];
        cocos2d::CCApplication::sharedApplication()->run();
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onLoginSuccess) name:DPay_kNotificationUserLoginSuccess
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onLoginSuccess) name: DPay_kNotificationSwitchAccount 
                                                   object:nil];
        
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
-(void)onLoginSuccess {

    if([[DPayPlatform defaultPlatform] isUserLoggedIn]){
    
        CCArray* array =   CCArray::create();
        array->addObject(CCString::createWithFormat("%d",DJXAPPID));
        array->addObject(CCString::createWithFormat("%d",[[DPayPlatform defaultPlatform] getUserId]));
        array->addObject(CCString::create([[[DPayPlatform defaultPlatform] getSessionId] UTF8String]));
        TK_DJXManager::getInstance()->login(array);
    }else{
        TK_DJXManager::getInstance()->logout();
    }
}
#endif


#ifdef PLATFORM_TBT
-(void)checkWiFiTBT{
    
    if(OCandCppHelper::isconnect3G())
    {
        [[TBPlatform defaultPlatform] TBSetAutoRotation:NO];
     
#ifdef DEBUG
//        [[TBPlatform defaultPlatform] TBSetUpdateDebugMode:0];
#endif
        /*初始化结束通知，登录等操作务必在收到该通知后调用！！*/
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sdkInitFinished) name:kTBInitDidFinishNotification object:nil];
        
        /*登录成功通知*/
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginFinished) name:(NSString *)kTBLoginNotification object:nil];

        
        /*注销通知（个人中心页面的注销也会触发该通知，注意处理*/
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didLogout) name:(NSString *)kTBUserLogoutNotification object:nil];
        
        /*离开平台通知（包括登录页面、个人中心页面、web充值页等*/
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(leavedSDKPlatform:) name:kTBLeavePlatformNotification object:nil];
        
        //SDK初始化，务必放在其他SDK接口的调用之前
        
        [[TBPlatform defaultPlatform] TBInitPlatformWithAppID:150141 screenOrientation:UIInterfaceOrientationPortrait isContinueWhenCheckUpdateFailed:NO];
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

- (void)sdkInitFinished
{
    [[TBPlatform defaultPlatform] TBSetAutoRotation:NO];
    cocos2d::CCApplication::sharedApplication()->run();
}

- (void)didLogout
{
    MB_TBTMgr::getInstance()->logout();
}

- (void)loginFinished
{
	if([[TBPlatform defaultPlatform] TBIsLogined])
    {
        MB_TBTMgr::getInstance()->login([[[TBPlatform defaultPlatform] sessionID] UTF8String]);
        //显示浮动工具条
        [[TBPlatform defaultPlatform] TBShowToolBar:TBToolBarAtMiddleLeft isUseOldPlace:YES];
	}
	else
    {
	}
}

- (void)leavedSDKPlatform:(NSNotification *)notification
{
    NSDictionary *notifyUserInfo = notification.userInfo;
    TBPlatformLeavedType leavedFromType = (TBPlatformLeavedType)[[notifyUserInfo objectForKey:TBLeavedPlatformTypeKey] intValue];
    switch (leavedFromType)
    {
            //从登录页离开
        case TBPlatformLeavedFromLogin:
        {
        }
            break;
            //从个人中心离开
        case TBPlatformLeavedFromUserCenter:
        {
        }
            break;
            //从充值页面离开
        case TBPlatformLeavedFromUserPay:
        {
//            NSString *orderString = [notifyUserInfo objectForKey:TBLeavedPlatformOrderKey];
//            [[TBPlatform defaultPlatform] TBCheckPaySuccess:orderString delegate:self];
        }
            break;
        default:
            break;
    }
}

#endif




#ifdef PLATFORM_IT
-(void)checkWiFiIT{
    
    if(OCandCppHelper::isconnect3G()){
    
        //设置充值平台分配的appid和appkey
        [HXAppPlatformKitPro setAppId:772 appKey:@"53A865B7090C5AEAC5BDFC99EFDC0194"];
        //设置支持的旋转方向
        [HXAppPlatformKitPro setSupportOrientationPortrait:YES portraitUpsideDown:NO landscapeLeft:NO landscapeRight:NO];
        
        //设置是否开启自动更新,默认为 NO,不开启
//        [HXAppPlatformKitPro setAutoCheckAppUpdateEnabled:YES];
        
        //监听登录通知
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginNotification:) name:HX_NOTIFICATION_LOGIN object:nil];
        //视图关闭通知
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(closeViewNotification:) name:HX_NOTIFICATION_CLOSEVIEW object:nil];
        //注销通知
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(logoutNotification:) name:HX_NOTIFICATION_LOGOUT object:nil];

        cocos2d::CCApplication::sharedApplication()->run();
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)loginNotification:(NSNotification *)notification
{
    NSLog(@"userId: %@", [notification.object objectForKey:@"userId"]);
    NSLog(@"userName: %@", [notification.object objectForKey:@"userName"]);
    NSLog(@"sessionId: %@", [notification.object objectForKey:@"sessionId"]);
    MB_ITMgr::getInstance()->login( [[notification.object objectForKey:@"sessionId"] UTF8String]);
}
- (void)closeViewNotification:(NSNotification *)notification
{
    NSLog(@"SDK View Closed");
    static bool bFirst = true;
    
    if(bFirst)
    {
        //IT 闪屏和视频播放有冲突，  这里做特殊处理，第一次视图关闭播放视频。   如果有问题，在训其他方式解决
//            MB_VideoMgr::getInstance()->playVideo();
        AppDelegate::goLogin();
        bFirst = false;
    }
    
}
- (void)logoutNotification:(NSNotificationCenter *)notification
{
    MB_ITMgr::getInstance()->logout();
}
#endif



#ifdef PLATFORM_KY
-(void)checkWiFiKY
{
    if(OCandCppHelper::isconnect3G())
    {
        [[KYSDK instance]setSdkdelegate:self];
        // [[KYSDK instance] setOnlySupportIPhone:YES];
        // [[KYSDK instance] setISShowForgetGamePwd:YES];
        [[KYSDK instance] changeLogOption:KYLOG_OFFGAMENAME];
        
        // 在游戏初始化时检测更新，可以打开此注释
        // [[KYSDK instance] checkUpdate];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(payResult:) name:@"KY_NOTIFICATION" object:nil];
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

//result:NO当前不是最新,yes当前为最新. serVer是服务器版本号
- (void) updataCheckResult:(BOOL)result serVer:(NSString *)serVer{
    if(!result){
        
        UIAlertView * alert = [[UIAlertView alloc]initWithTitle:@"是否升级" message:@"最新版本上线\n是否升级" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"升级", nil];
        
        alert.tag = LAYER_TAG_KY_UPDATE_1;
        [alert show];
        [alert release];
        
    }else{
      
    }
}

-(void)loginCallBack:(NSString *)tokenKey
{
    MB_KYMgr::getInstance()->login([tokenKey UTF8String]);
}

-(void)quickLogCallBack:(NSString *)tokenKey{
    MB_KYMgr::getInstance()->login([tokenKey UTF8String]);
}

-(void)gameLogBack:(NSString *)username passWord:(NSString *)password {
    
}

-(void)logOutCallBack:(NSString *)guid {
    [[KYSDK instance] changeLogOption:KYLOG_OFFGAMENAME];
    MB_KYMgr::getInstance()->logout();
}

#endif

#ifdef PLATFORM_DL
-(void)checkWiFiDL{
    
    if(OCandCppHelper::isconnect3G()){
     
        [[DJPlatform defaultDJPlatform] setAppId:DLAPPID];
        [[DJPlatform defaultDJPlatform] setAppKey:DLAPPKEY];
        [[DJPlatform defaultDJPlatform] setMerchantId:DLMERCHANT_ID];
        [[DJPlatform defaultDJPlatform] setServerId:@"1"];
        [[DJPlatform defaultDJPlatform] setTapBackgroundHideView:NO];
        [[DJPlatform defaultDJPlatform] setAppScheme:@"sdk"];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformLoginResultNotify:) name:kDJPlatformLoginResultNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformLoginOut:) name:kDJPlatformLogotResultNotification  object:nil];
        cocos2d::CCApplication::sharedApplication()->run(); 
     
}else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
    
}
-(void)dealDJPlatformLoginResultNotify:(NSNotification *)notify{

    DJPlatformMemberInfo* memberInfo = [notify object];
    switch ([memberInfo.errorCode intValue]){
            
        case 100:
            //用户取消登陆
            break;
        case 101:
            //系统错误:
            break;
        case 201:
            //app_id 错误
            break;
        case 210:
            //sig 为空
            break;
        case 211 :
            //app_key 错误
            break;
        case 220 :
            //token 为空
            break;
        case 221 :
            //token 错误
            break;
        case 222:
            //tocken 超时
            break;
        case 300:
            //没有接口访问权限
            break;            
        default:
            NSLog(@"error code %d",[memberInfo.errorCode intValue]);
            TK_DLManager::getInstance()->goLogin([memberInfo.userName UTF8String] ,[[memberInfo.memberId stringValue] UTF8String] , [memberInfo.token UTF8String]);
            break;
    }
}
-(void) dealDJPlatformLoginOut:(NSNotification *)notify{

    if(TK_DLManager::getInstance()->hasLogin()){
        
        TK_DLManager::getInstance()->logout();
    }
}
-(BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url{
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kDJPlatfromAlixQuickPayEnd   object:url];
    [WXApi handleOpenURL:url delegate:self];
    return  YES;
}
#endif


#ifdef PLATFORM_PP
-(void)checkWiFiPP
{
    if(OCandCppHelper::isconnect3G())
    {
        [[PPAppPlatformKit sharedInstance] setAppId:5005 AppKey:@"1e09ff50da9f9c4d2322f8b9528c9493"];
        [[PPAppPlatformKit sharedInstance] setIsNSlogData:NO];
        [[PPAppPlatformKit sharedInstance] setRechargeAmount:10];
        [[PPAppPlatformKit sharedInstance] setIsLongComet:YES];
        [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:NO];
        [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
        [[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"关闭充值提示语"];
        
        [[PPUIKit sharedInstance] checkGameUpdate];
        [PPUIKit sharedInstance];
        [PPUIKit setIsDeviceOrientationLandscapeLeft:NO];
        [PPUIKit setIsDeviceOrientationLandscapeRight:NO];
        [PPUIKit setIsDeviceOrientationPortrait:YES];
        [PPUIKit setIsDeviceOrientationPortraitUpsideDown:YES];
        [[PPAppPlatformKit sharedInstance] setDelegate:self];
        
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode{

}
- (void)ppVerifyingUpdatePassCallBack{

}
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey
{
    NSString * messsage = [NSString stringWithFormat:@"%@",paramStrToKenKey];

    NSLog(@"%@",messsage);
    [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
    MB_PPMgr::getInstance()->login([paramStrToKenKey UTF8String]);
}
//- (void)ppLoginHexCallBack:(char *)paramHexToKen{
//
//}
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode{

}
- (void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode{

}
- (void)ppLogOffCallBack{

    MB_PPMgr::getInstance()->logout();
}

#endif


#ifdef PLATFORM_ZZ
-(void)checkWiFiZZ{
    
    if(OCandCppHelper::isconnect3G()){
        
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onZZLogin:)
                                                     name:Cmge_kNotificationUserLoginSuccess
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onZZPayBack:)
                                                     name:Cmge_kNotificationUserPayOver
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onZZEXit:)
                                                     name:Cmge_kNotificationLoginOutPlatform
                                                   object:nil];
        

        cocos2d::CCApplication::sharedApplication()->run();
        
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)onZZLogin:(NSNotification *)notification
{
    NSDictionary *dicInfo = notification.object;
    NSString *code = [dicInfo objectForKey:Cmge_Access_Code];
    if(code != nil){
        
        TK_ZZManager::getInstance()->login(CCString::create([code UTF8String]));
    }
    
}
- (void)onZZEXit:(NSNotification *)notification
{

    TK_Message::sharedTK_Message()->removeALLMessage();
}
- (void)onZZPayBack:(NSNotification *)notification
{
    
}
#endif

#ifdef PLATFORM_HJR
- (void)parse:(NSURL *)url application:(UIApplication *)application {
    //结果处理
    //检测接口可用
    if ([[GameKitSDK defaultSdk] hasProvide_response_openurl_service]) {
        [[GameKitSDK defaultSdk] application:application openURL:url sourceApplication:nil annotation:nil];
    }
}
#endif

#ifdef PLATFORM_UC
-(BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url{
    
    [[UCGameSdk defaultSDK] parseAliPayResultWithURL:url application:application];
    return  YES;
}
-(void)checkWiFiUC{

    if(OCandCppHelper::isconnect3G()){
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onSdkInitFin:)
                                                     name:UCG_SDK_MSG_SDK_INIT_FIN
                                                   object:nil];
        
        UCGameSdk *sdk = [UCGameSdk defaultSDK];        
        sdk.cpId = UCCPID;          // 将 UC 分配的 Cp ID 赋值给 sdk.cpId 属性
        sdk.gameId = UCGAMEID;       // 将 UC 分配的 Game ID 赋值给 sdk.gameId 属性
        sdk.serverId = UCSERVERID;     // 将 UC 分配的 Server ID 赋值给 sdk.serverId 属性
        
#ifdef DEBUG
        sdk.isDebug = true;
#else 
        sdk.isDebug = false;
#endif
        // 是否启用调试模式，如果启用调试模式，SDK访问的服务器将SDK的测试服务器
        sdk.logLevel = UCLOG_LEVEL_DEBUG;   // 日志级别，控制sdk自身日志的输出
        sdk.gameName = @"口袋妖怪移动版";

        sdk.allowGameUserLogin = false;  // 是否允许官方账号登录，如果允许，请传 YES
        sdk.allowChangeAccount = true;   // 是否允许切换帐号，如果允许，请处理用户注销的情况
        //sdk.gameUserName
        // 设置登录界面横竖屏情况
        sdk.orientation = UC_PORTRAIT;
        
        //设置悬浮按钮是否显示,默认不显示
        sdk.isShowFloatButton = YES;
        //设置悬浮按钮的初始位置，x只能是0或100，0代表左边，100代表右边；y为0~100，0表示最上面，100表示最下面
        //默认是在屏幕右边的中间，如(100,50)
        sdk.floatButtonPosition = CGPointMake(100, 12);
        [sdk initSDK];
                     
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }

}
- (IBAction)onGetFriends:(id)sender
{
    [[UCGameSdk defaultSDK] getUCZoneFriendList:1 pageSize:10 type:1 delegate:self];
}
- (void)onSdkInitFin:(NSNotification *) notification
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UCG_SDK_MSG_SDK_INIT_FIN
                                                  object:nil];
    
    UCResult *result = (UCResult *)notification.object;
//    [NSString stringWithFormat:@"SDK init res: \ncode=%d, msg=%@",
//                          result.statusCode, result.message];
    // 初始化成功时的处理
    if (result.isSuccess)
    {
        
        cocos2d::CCApplication::sharedApplication()->run();
        //初始化完成后，开始监听SDK页面的进入 及 退出
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onEnterSDK:)
                                                     name:UCG_SDK_MSG_SDK_ENTER
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onExitSDK:)
                                                     name:UCG_SDK_MSG_SDK_EXIT
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UCG_SDK_MSG_LOGIN_FIN
                                                      object:nil];
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:UCG_SDK_MSG_EXIT_WITHOUT_LOGIN
                                                      object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onLogOutSDK:)
                                                     name:UCG_SDK_MSG_LOGOUT
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onLoginFin:)
                                                     name:UCG_SDK_MSG_LOGIN_FIN
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onUnloginExit:)
                                                     name:UCG_SDK_MSG_EXIT_WITHOUT_LOGIN
                                                   object:nil];
    }
    // 初始化失败时的处理
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)onLogOutSDK:(NSNotification *)notification
{
    if(TK_UCManager::getInstance()->hasLogin()){
        
        TK_UCManager::getInstance()->logout();
    }
}
- (void)onLoginFin:(NSNotification *)notification
{
    UCResult *result = notification.object;
    // 登录成功的处理
    if (result.isSuccess)
    {
        TK_UCManager::getInstance()->goLogin([[[UCGameSdk defaultSDK] sid] UTF8String]);
    }
    // 登录失败时的处理
    else
    {
        //self.labelTip.text = [NSString stringWithFormat:@"登录失败，错误信息: %@", result.message];
    }
}
- (void)onLogout
{
    [self onEnterGame:nil]; // 此处帐号注销的处理：重新调用登录接口
}
- (IBAction)onEnterGame:(id)sender
{
    {
        [[UCGameSdk defaultSDK] login];
    }
}
- (void)onUnloginExit:(NSNotification *)notification
{
  }
- (void)onEnterSDK:(NSNotification *)notification
{
   
}
- (void)onExitSDK:(NSNotification *)notification
{
     NSNotification *notifaction = [NSNotification notificationWithName:UIKeyboardDidHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] postNotification:notifaction];
    //[[UIApplication sharedApplication] resignFirstResponder];
}
#endif



#ifdef PLATFORM_91
-(void) checkWiFi{
    
//    MB_91Mgr::getInstance()->setIsShowFloatButton(false);
    
    if(OCandCppHelper::isconnect3G()){
        
        /******91平台初始化****/
        NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
        cfg.appid = 116508;
        cfg.appKey = @"7fa47abbd9086e7613bcbec5c2405b9024933be1a7c768fc";
        cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
        cfg.orientation = UIInterfaceOrientationPortrait;
        
        [[NdComPlatform defaultPlatform] NdInit:cfg];
        
        //设定为调试模式
        //设定为调试模式的支付功能和升级功能,参数为预留,默认为零。
       // #ifdef DEBUG
       //[[NdComPlatform defaultPlatform] NdSetDebugMode:0];
       // #endif
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(SNSInitResult:)
                                                     name:(NSString *)kNdCPInitDidFinishNotification
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(SNSLeaveComplatformUI:)
                                                     name:(NSString *)kNdCPLeavePlatformNotification
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(SNSSessionInvalid:)
                                                     name:(NSString *)kNdCPSessionInvalidNotification
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(SNSLoginResult:)
                                                     name:(NSString *)kNdCPLoginNotification
                                                   object:nil];
        
        [[NdComPlatform defaultPlatform]
         NdSetScreenOrientation:UIInterfaceOrientationPortrait];
        [[NdComPlatform defaultPlatform] NdSetAutoRotation:YES];
        cocos2d::CCApplication::sharedApplication()->run();
        
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)SNSInitResult:(NSNotification *)notify
{
//    MB_VideoMgr::getInstance()->playVideo();
    AppDelegate::goLogin();
}
- (void)SNSLoginResult:(NSNotification *)notify
{
    NSDictionary *dict = [notify userInfo];
    BOOL success = [[dict objectForKey:@"result"] boolValue];
    NdGuestAccountStatus* guestStatus =
    (NdGuestAccountStatus*)[dict objectForKey:@"NdGuestAccountStatus"]; //登录成功后处理
    if([[NdComPlatform defaultPlatform] isLogined] && success) {
        //也可以通过[[NdComPlatform defaultPlatform] getCurrentLoginState]判断是否游客登录状态
        if (guestStatus) {
            
            if ([guestStatus isGuestLogined]) {
                //游客账号登录成功;
                NSLog(@"guest success %@ %@",[[NdComPlatform defaultPlatform] loginUin], [[NdComPlatform defaultPlatform]nickName]);
                MB_91Mgr::getInstance()->goLogin("NULL",[[[NdComPlatform defaultPlatform] loginUin] UTF8String],[[[NdComPlatform defaultPlatform] sessionId] UTF8String]);
                
            }else if([guestStatus isGuestRegistered]) {
                //游客成功注册为普通账号        
                NSLog(@"guest to normal success %@", [[NdComPlatform defaultPlatform] loginUin] );
                MB_91Mgr::getInstance()->onGuestToNormal();
            }

        }else {
      
            MB_91Mgr::getInstance()->goLogin([[[NdComPlatform defaultPlatform] nickName] UTF8String],[[[NdComPlatform defaultPlatform] loginUin] UTF8String],[[[NdComPlatform defaultPlatform] sessionId] UTF8String]);
            
        }
    }   //登录失败处理和相应提示
    else {
        
        int error = [[dict objectForKey:@"error"] intValue];
        NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d",
                            error];
        switch (error) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
                if (([[NdComPlatform defaultPlatform] getCurrentLoginState] ==
                     ND_LOGIN_STATE_GUEST_LOGIN)) {
                    strTip = @"当前仍处于游客登录状态";
                    
                } else {
                    MB_LayerFirstLogin::m_bSkipLogin = true;
                    strTip = @"用户未登录";
                }
                if(MB_91Mgr::getInstance()->hasLogin()){
                
                    MB_91Mgr::getInstance()->logout();
                }
                break;
            case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
                break;
                strTip = @"登录失败, 请检查appId/appKey";
            case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
                strTip = @"登录失败, 无效的应用ID"; break;
            case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91: strTip = @"有关联的91账号,不能以游客方式登录";
                break;
            default:
                break;
        }
    }
}

-(void)SNSLeaveComplatformUI:(NSNotification *)notify{

}
-(void)SNSSessionInvalid:(NSNotification *)notify{
    
    if(MB_91Mgr::getInstance()->hasLogin()){
        MB_91Mgr::getInstance()->logout();
    }
}
#endif


#ifdef PLATFORM_I4
-(void)checkWiFiI4
{
    if(OCandCppHelper::isconnect3G())
    {
        [[AsInfoKit sharedInstance] setAppId:502];
        [[AsInfoKit sharedInstance] setAppKey:@"1c51a606d1264f86b0ede3260973071c"];
        [[AsInfoKit sharedInstance] setLogData:NO];
        [[AsInfoKit sharedInstance] setCloseRecharge:NO];
        [[AsInfoKit sharedInstance] setCloseRechargeAlertMessage:@"充值功能暂时不开放"];
        [[AsInfoKit sharedInstance] setLongComet:YES];
        
        [[AsInfoKit sharedInstance] setRootViewController:self.viewController];
//        [[AsInfoKit sharedInstance] updateSDKOperatingEnvironment:YES andOrientationOfGame:UIInterfaceOrientationMaskPortrait];
        [[AsPlatformSDK sharedInstance] checkGameUpdate];

        [[AsPlatformSDK sharedInstance] setDelegate:self];
        
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
- (void)asClosedCenterViewCallBack
{
    
}
- (void)asAlixPayResultCallBack:(int)statusCode
{
    
}
- (void)asPayResultCallBack:(AsPayResultCode)paramPPPayResultCode{

}
- (void)asVerifyingUpdatePassCallBack{

}
- (void)asLoginCallBack:(NSString *)paramToken{

    [[AsPlatformSDK sharedInstance] showFloatIcon];
    MB_I4Mgr::getInstance()->login([paramToken UTF8String]);
}
- (void)asCloseWebViewCallBack:(AsWebViewCode)paramWebViewCode{

}
- (void)asClosePageViewCallBack:(AsPageCode)paramPPPageCode{

}
- (void)asLogOffCallBack{

    MB_I4Mgr::getInstance()->logout();
}
#endif



#ifdef PLATFORM_SM
-(void)checkWiFiSM
{
    if(OCandCppHelper::isconnect3G())
    {
        [[JorgPlatform defaultPlatform] setViewOrientation:UIInterfaceOrientationMaskPortrait];
   
        JorgProject *project = [[[JorgProject alloc] init] autorelease];
		project.projectId = SM_PROJECTID;      //必填 项目ID
		project.productId = SM_PRODUCTID;    //必填 产品ID
		project.serverId = SM_SERVERID;        // 必填 服务器ID
		project.isOnlineGame = YES;        //必填 在线游戏 YES，单机 NO
//		[[JorgPlatform defaultPlatform] setProject:project];
        
        [[NSNotificationCenter defaultCenter]addObserver:self		selector:@selector(loginSuccess) 	name:Jorg_kNotificationUserLoginSuccess object:nil];
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}
-(void) loginSuccess
{
    
    NSString *username =  [[JorgPlatform defaultPlatform] getUserName];
    if(username != nil){
        
        TK_SMManager::getInstance()->login([username UTF8String]);
    
    }
}
#endif


#ifdef PLATFORM_XY
-(void)checkWiFiXY
{
    if(OCandCppHelper::isconnect3G())
    {
        [[XYPlatform defaultPlatform] initializeWithAppId:@"100005057" appKey:@"YPfgti0EXXDsg2OhoOjA4RnBKX9ZUjzM" isContinueWhenCheckUpdateFailed:YES];
        //[[XYPlatform defaultPlatform] setDebugModel:NO];
        MB_XYMgr::getInstance()->setControllerPtr(self);
        [[XYPlatform defaultPlatform] setAppScheme:@"com.moongame.pkq.xy.alipay"];
        
        //添加XYPlatform 各类通知的观察者
        
        /*初始化结束通知, 登录等操作务必在收到该通知后调用*/
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyplatformInitFinished:)
                                                     name:kXYPlatformInitDidFinishedNotification
                                                   object:nil];
        
        /*登录通知*/
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyplatformLoginNoti:)
                                                     name:kXYPlatformLoginNotification
                                                   object:nil];
        
        /*注册通知*/
        /*[[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyplatformRegisterNoti:)
                                                     name:kXYPlatformRegisterNotification
                                                   object:nil];*/
        /* 注销登录通知 */
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyplatformLogoutFinished:)
                                                     name:kXYPlatformLogoutNotification
                                                   object:nil];
        
        /*离开平台通知*/
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyplatformLeavedPlatform:)
                                                     name:kXYPlatformLeavedNotification
                                                   object:nil];
        
        
        /*登录状态验证 通知 */
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(xyPlatformVertifyLogin:)
                                                     name:kXYPlatformSetLoginNotification
                                                   object:nil];

        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }

}

- (void)xyplatformInitFinished:(NSNotification*)notification
{
//        MB_VideoMgr::getInstance()->playVideo();
    AppDelegate::goLogin();
}

- (void)xyplatformLoginNoti:(NSNotification*)notification
{
    // 登录完成, 提供token 以及 openuid 给游戏校验
    
    NSDictionary *userInfo = notification.userInfo;
    if ([userInfo[kXYPlatformErrorKey] intValue] == XY_PLATFORM_NO_ERROR) {
        
        NSString* token = [[XYPlatform defaultPlatform] XYToken];
        
        NSString* openuid = [[XYPlatform defaultPlatform] XYOpenUID];
        
        MB_XYMgr::getInstance()->login([openuid UTF8String],[token UTF8String]);
    }
    
    [[XYPlatform defaultPlatform] XYShowToolBar:XYToolBarAtTopLeft isUseOldPlace:YES];
}

- (void)xyplatformRegisterNoti:(NSNotification*)notification
{
    NSDictionary *userInfo = notification.userInfo;
    if ([userInfo[kXYPlatformErrorKey] intValue] == XY_PLATFORM_NO_ERROR) {
        
        NSString* token = [[XYPlatform defaultPlatform] XYToken];
        
        NSString* openuid = [[XYPlatform defaultPlatform] XYOpenUID];
        
        MB_XYMgr::getInstance()->login([openuid UTF8String],[token UTF8String]);
    }
}

- (void)xyplatformLeavedPlatform:(NSNotification*)notification
{
    NSNumber* leavedType = (NSNumber*)notification.object;
    
    switch ([leavedType integerValue]) {
        case XYPlatformLeavedDefault: {
            break;
        }
        case XYPlatformLeavedFromLogin: {
            break;
        }
        case XYPlatformLeavedFromRegister: {
            break;
        }
        case XYPlatformLeavedFromPayment: {
            break;
        }
        case XYPlatformLeavedFromSNSCenter:{
            break;
        }
            
        default:
            break;
    }
    
    [[XYPlatform defaultPlatform] XYShowToolBar:XYToolBarAtTopLeft isUseOldPlace:YES];
}
- (void) xyPlatformVertifyLogin:(NSNotification *) noti
{
    NSDictionary *dic = noti.userInfo;
    int ret = [dic[kXYPlatformErrorKey] intValue];
    if (ret == XY_PLATFORM_NO_ERROR) {
        NSString* token = [[XYPlatform defaultPlatform] XYToken];
        
        NSString* openuid = [[XYPlatform defaultPlatform] XYOpenUID];
        
        MB_XYMgr::getInstance()->login([openuid UTF8String],[token UTF8String]);
    }else{
    }
}

- (void)xyplatformLogoutFinished:(NSNotification*)notification
{
    MB_XYMgr::getInstance()->logout();
}

-(void) XYPaySuccessWithOrder:(NSString *)orderId payAmount:(NSString *)amount
{
    MB_Message::sharedMB_Message()->showMessage("支付成功");
}
-(void) XYPayFailedWithOrder:(NSString *)orderId payAmount:(NSString *)amount
{
    MB_Message::sharedMB_Message()->showMessage("支付失败");
}

#endif



#ifdef PLATFORM_QD
-(void)checkWiFiQD
{
    if(OCandCppHelper::isconnect3G())
    {
        /*
         口袋妖怪移动版1：1770
         口袋妖怪移动版2：1771
         口袋妖怪移动版3：1772
         口袋妖怪移动版4：1773
         口袋妖怪移动版5：1774
         苦逼打包员一个一个换着打包吧 - -
         */
        [[DJPlatform defaultDJPlatform] setAppId:@"2036"];
        [[DJPlatform defaultDJPlatform] setAppKey:@"af31c25c"];
        [[DJPlatform defaultDJPlatform] setMerchantId:@"1770"];
        [[DJPlatform defaultDJPlatform] setServerId:@"1"];
        [[DJPlatform defaultDJPlatform] setTapBackgroundHideView:NO];
        [[DJPlatform defaultDJPlatform] saveCurrentGameInfo];	//保存设置信息
        
        // register notification for response to 44755 ios sdk
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformLoginResultNotify:) name:kDJPlatformLoginResultNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformLoginGiveupNotify:) name:kDJPlatformLoginGiveupNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformReadMemberInfoResultNotify:) name:kDJPlatformReadMemberInfoResultNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformLogoutResultNotify:) name:kDJPlatformLogotResultNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformPaymentResultNotify:) name:kDJPlatformPaymentResultNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformPaymentGiveupNotify:) name:kdjPlatformPaymentGiveupNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dealDJPlatformGlobalErrorNotify:) name:kDJPlatformErrorNotification object:nil];
        
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

-(void) dealDJPlatformGlobalErrorNotify : (NSNotification *) notify
{
    NSError *error = notify.object;
    NSString * msg = [error localizedDescription];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示信息" message:msg delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    [alert show];
    
}
-(void) dealDJPlatformLoginResultNotify:(NSNotification *) notify
{
    DJPlatformMemberInfo *memberInfo = [notify object];
    TK_QDManager::getInstance()->login([memberInfo.memberId intValue],[memberInfo.token UTF8String]);
}
-(void) dealDJPlatformLoginGiveupNotify:(NSNotification *) notify
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示信息" message:@"用户取消登陆" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    [alert show];
}
-(void) dealDJPlatformLogoutResultNotify : (NSNotification *) notify
{
    
}
-(void) dealDJPlatformReadMemberInfoResultNotify:(NSNotification *) notify
{
}
-(void) dealDJPlatformPaymentResultNotify : (NSNotification *) notify
{
    NSDictionary *dict = notify.userInfo;
    NSString *orderNo = [dict objectForKey:@"orderNo"];
    NSNumber *code = [dict objectForKey:@"code"];
    NSString *msg = [dict objectForKey:@"msg"];
    NSString *content=[NSString stringWithFormat:@"orderNo:%@,code:%@,msg:%@", orderNo, code, msg];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示信息" message:content delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    [alert show];
    [alert release];
    
}
-(void) dealDJPlatformPaymentGiveupNotify:(NSNotification *) notify
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示信息" message:@"用户取消支付" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    [alert show];
    
}
#endif

#ifdef PLATFORM_HJR

#pragma mark - 注册回调函数
-(void)checkWiFiHJR
{
    if(OCandCppHelper::isconnect3G())
    {
        GameKitInitParam *param = [[GameKitInitParam alloc] init];
        // param.zoneID = @"1";
        [[GameKitSDK defaultSdk] initWithObserver:self params:param];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(payResult:) name:@"KY_NOTIFICATION" object:nil];
        cocos2d::CCApplication::sharedApplication()->run();
    }
    else
    {
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

#pragma mark - GameKitObserverProtocol

/**平台初始化回调函数*/
-(void)gameKitInitCompletedISSucceedStatus:(BOOL) isSucceed error:(GWError *)error
{
    // [self alertMsg:isSucceed?@"初始化成功":@"初始化失败"];
    if (isSucceed) {
        if ([[GameKitSDK defaultSdk] hasProvide_checkupdate_service]) {
            [[GameKitSDK defaultSdk] checkUpdate];
        }
        MB_LYMgr::getInstance()->setInitSDKOK();
        if (MB_LYMgr::getInstance()->canLogin())
        {
            MB_LYMgr::getInstance()->goLogin();
        }
        
    } else {
        CCLog("好接入 GameKitSDK Init Error, errorCode = %d, errorDesc = %s", [error errorCode], [[error errorDesc] UTF8String]);
    }
}

/**注册成功回调函数*/
-(void)rigisterCompletedWithResponseData:(GWUserInfo *)obj
{
    NSLog(@"%@",obj);
}

/**登录回调接口*/
-(void)loginCompletedWithLoginStatus:(LoginStatus)loginStatus responseObj:(GWUserInfo *)obj error:(GWError *)error
{
    if (loginStatus == LOGIN_SUCCEED) {
        // [self alertMsg:@"登录成功!"];
        CCArray *pArray = CCArray::create();
        pArray->addObject(CCString::create([obj.userID UTF8String]));
        pArray->addObject(CCString::create([obj.userName UTF8String]));
        pArray->addObject(CCString::create([obj.nickName UTF8String]));
        pArray->addObject(CCString::create([obj.userLoginToken UTF8String]));
        pArray->addObject(CCString::create([obj.uuid UTF8String]));
        pArray->addObject(CCString::create([obj.CPName UTF8String]));
        pArray->addObject(CCString::create([obj.cpToken UTF8String]));
        
        MB_LYMgr::getInstance()->showFloatWindowOrBar(TRUE);
        MB_LYMgr::getInstance()->login(pArray);
        
    } else if (loginStatus == LOGIN_CANCLE) {
        // [self alertMsg:@"登录被取消"];
    } else {
        // [self alertMsg:[@"" stringByAppendingFormat:@"登录失败:%@",error.errorDesc]];
    }
}

/**支付回调接口*/
-(void)payCompletedWithPayStatus:(PayStatus)payStatus responseObj:(GWPayBackInfo *)obj error:(GWError *)error
{
    if (payStatus == PAY_SUCCEED) {
        // [self alertMsg:[@"" stringByAppendingFormat:@"支付成功:%@",obj.orderId]];
        MB_LYMgr::getInstance()->doStatisticsPay([obj.orderId UTF8String]);
    }else if (payStatus == PAY_CANCLE)
    {
        // [self alertMsg:[@"" stringByAppendingFormat:@"支付被取消:%@",obj.orderId]];
    }else if(payStatus == PAY_PROCESSING)
    {
        // [self alertMsg:[@"" stringByAppendingFormat:@"正在处理中:%@",obj.orderId]];
    }else if (payStatus == PAY_FAILED)
    {
        // [self alertMsg:[@"" stringByAppendingFormat:@"支付失败:%@,%@",obj.orderId,error.errorDesc]];
    }
}

/**登录注销完成回调*/
-(void)LoginOutCompletedISSucceedStatus:(BOOL) isSucceed error:(GWError *)error
{
    if (isSucceed) {
        // [self alertMsg:@"登录已经注销"];
        MB_LYMgr::getInstance()->logout();
    }else
    {
        // [self alertMsg:[@"" stringByAppendingFormat:@"注销失败:%@",error.errorDesc]];
    }
}

/**订单查询*/
-(void)checkOrderCompletedWithData:(GWCheckOrderInfo *)obj error:(GWError *)error
{
    if (error) {
        // [self alertMsg:[@"" stringByAppendingFormat:@"订单查询失败:%@",[error errorDesc]]];
    }else
    {
        if (obj.status == TRADE_SUCCEED) {
            // [self alertMsg:@"交易成功"];
        }else if(obj.status == TRADE_FAILED)
        {
            // [self alertMsg:[@"" stringByAppendingFormat:@"交易失败:%@,",obj.statusDesc]];
        }
    }
}

/**检查更新获取回调数据*/
-(void)checkUpdateCompletedWithData:(GWUpdateInfo *)obj error:(GWError *)error
{
    if (error) {
        // [self alertMsg:[@"" stringByAppendingFormat:@"检查更新失败:%@",[error errorDesc]]];
    }else
    {
        if (obj.status == CHECK_SUCCEED) {
            NSLog(@"检查更新成功:");
        }else
        {
            NSLog(@"检查更新失败");
        }
    }
}

#endif
#ifdef PLATFORM_APPSTORE
-(void)checkWiFiAppStore{
    if(OCandCppHelper::isconnect3G()){
        //获取info配置的版本号
        NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
        NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
        NSString* version = [data objectForKey:@"CFBundleVersion"];
        NSLog(@"%@", version);//直接打印数据。
        
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc addObserver: self selector:@selector(authenticationChanged) name:GKPlayerAuthenticationDidChangeNotificationName object:nil];

        cocos2d::CCApplication::sharedApplication()->run();
    }else {
        
        UIAlertView *alter = [[UIAlertView alloc] initWithTitle:nil message:@"请检测网络是否正确" delegate:self cancelButtonTitle:@"重试" otherButtonTitles:@"取消", nil];
        [alter show];
        [alter release];
        alter.tag  = 1;
    }
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    
    NSLog(@"-----------收到产品反馈信息--------------");
    
    if (response.invalidProductIdentifiers.count > 0) {
        MB_Message::sharedMB_Message()->showMessage("支付失败，ProductID无效");
        CCLOG("ProductID为无效ID");
    }else{
            SKProduct *product = response.products.firstObject;
        
        NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
        
        NSLog(@"产品付费数量: %d", (int)[response.products count]);
        
        NSLog(@"product info");
        NSLog(@"SKProduct描述信息%@", [product description]);
        NSLog(@"产品标题%@", product.localizedTitle);
        NSLog(@"产品描述信息: %@", product.localizedDescription);
        NSLog(@"价格: %@", product.price);
        NSLog(@"Product id: %@", product.productIdentifier);
        
        //取到内购产品进行购买
        SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
};

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
    
    NSLog(@"------------------错误-----------------:%@", error);
    
}

- (void)requestDidFinish:(SKRequest *)request{
    
    NSLog(@"------------反馈信息结束-----------------");
    
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://购买成功
            {
                NSString *productIdentifier = transaction.payment.productIdentifier;
                NSData *receiptData = [NSData dataWithContentsOfURL:[[NSBundle mainBundle] appStoreReceiptURL]];
                NSString *receipt = [receiptData base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
                if ([receipt length] > 0 && [productIdentifier length] > 0) {
                    /**
                     可以将receipt发给服务器进行购买验证
                     */
                    MB_RoleData::getInstance()->sendrole_pay_ios([receipt UTF8String], "unkown");
                }
                MB_Message::sharedMB_Message()->showMessage("支付成功");
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
            }
                break;
            case SKPaymentTransactionStateFailed://购买失败
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                MB_Message::sharedMB_Message()->showMessage("支付失败");
                break;
            case SKPaymentTransactionStateRestored://恢复购买
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                break;
            case SKPaymentTransactionStatePurchasing://正在处理
                break;
            default:
                break;
        }
    }
    
}

// 这玩意会比authenticationHandler早回调
-(void) authenticationChanged
{
    NSLog(@"authenticationChanged");
    

    MB_AppStoreMgr::getInstance()->goLogout();
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    //在此处截取链接获取支付结果
    NSString *absoluteString = request.URL.absoluteString;
    if ([absoluteString hasPrefix:@"支付成功后跳转的链接"]) {
        //在此处提示支付成功的支付结果
        
        return NO;
    } else if ([absoluteString hasPrefix:@"支付失败后跳转的链接"]) {
        //在此处提示支付失败的支付结果
        
        return NO;
    } else if ([absoluteString hasPrefix:@"支付取消后跳转的链接"]) {
        //在此处提示支付取消的支付结果
        
        return NO;
    }
    return YES;
}

- (void)closeAppStoreView
{
    MB_Message::sharedMB_Message()->showMessage("");
}
#endif
@end
