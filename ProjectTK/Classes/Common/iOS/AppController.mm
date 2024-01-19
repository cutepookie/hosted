#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "Game.h"

#ifdef YJ_IOS
#import <SMPCQuickSDK/SMPCQuickSDK.h>
#include "MB_YJMgr_IOS.h"
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


#define PRODUCT_CODE    @"02377503891500152578630765016637"
#define PRODUCT_KEY     @"96461490"

@implementation AppController

@synthesize window;
@synthesize viewController;


static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
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
    cocos2d::CCApplication::sharedApplication()->run();

#ifdef YJ_IOS
    //初始化
    SMPCQuickSDKInitConfigure *cfg = [[SMPCQuickSDKInitConfigure alloc] init];
    cfg.productKey = PRODUCT_KEY;
    cfg.productCode = PRODUCT_CODE;
    [[SMPCQuickSDK defaultInstance] initWithConfig:cfg application:application didFinishLaunchingWithOptions:launchOptions];
    
    
    
    //添加对QuickSDK通知的监听
    //登录
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(smpcQpLoginResult:) name:kSmpcQuickSDKNotiLogin object:nil];
    //注销
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(smpcQpLogoutResult:) name:kSmpcQuickSDKNotiLogout object:nil];
    //充值结果
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(smpcQpRechargeResult:) name:kSmpcQuickSDKNotiRecharge object:nil];
    //暂停结束 这个回调可以不用添加
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(smpcQpPauseOver:) name:kSmpcQuickSDKNotiPauseOver object:nil];
#endif

    return YES;
}
#ifdef YJ_IOS
//MARK:-
- (void)smpcQpLoginResult:(NSNotification *)notify {
    NSLog(@"登录成功通知%@",notify);
    int error = [[[notify userInfo] objectForKey:kSmpcQuickSDKKeyError] intValue];
    NSDictionary *userInfo = [notify userInfo];
    if (error == 0) {
        NSString *uid = [[SMPCQuickSDK defaultInstance] userId];
        NSString *user_name = [[SMPCQuickSDK defaultInstance] userNick];
        //获取user_token，用于从服务器去验证用户信息
        NSString *user_token = userInfo[kSmpcQuickSDKKeyUserToken];
        NSString * channelID =  [[SMPCQuickSDK defaultInstance] getConfigValue:@"channel"];
        if (channelID == nil || channelID == NULL||[channelID isKindOfClass:[NSNull class]]||[[channelID stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]] length]==0) {
            char buff[10];
            sprintf(buff, "%d", [[SMPCQuickSDK defaultInstance] channelType]);
            MB_YJMgr_IOS::getInstance()->login([PRODUCT_CODE UTF8String],buff,[uid UTF8String],[user_token UTF8String]);
        }else
        {
            MB_YJMgr_IOS::getInstance()->login([PRODUCT_CODE UTF8String],[channelID UTF8String],[uid UTF8String],[user_token UTF8String]);
        }
    }else
    {
        MB_YJMgr_IOS::getInstance()->logout();
    }
}

- (void)smpcQpLogoutResult:(NSNotification *)notify {
    NSLog(@"%s",__func__);
    NSDictionary *userInfo = notify.userInfo;
    int errorCode = [userInfo[kSmpcQuickSDKKeyError] intValue];
    switch (errorCode) {
        case SMPC_QUICK_SDK_ERROR_NONE:
        {
            NSLog(@"注销成功");
            //注销成功
           MB_YJMgr_IOS::getInstance()->logout();
        }
            break;
        case SMPC_QUICK_SDK_ERROR_LOGOUT_FAIL:
        default:
        {
            //注销失败
            NSLog(@"注销失败");
        }
            break;
    }
    if (errorCode == SMPC_QUICK_SDK_ERROR_NONE) {
        
    }
    
}
- (void)smpcQpRechargeResult:(NSNotification *)notify{
    NSLog(@"充值结果%@",notify);
    NSDictionary *userInfo = notify.userInfo;
    int error = [[userInfo objectForKey:kSmpcQuickSDKKeyError] intValue];
    switch (error) {
        case SMPC_QUICK_SDK_ERROR_NONE:
        {
            //充值成功
            //QuickSDK订单号,cp下单时传入的订单号，渠道sdk的订单号，cp下单时传入的扩展参数
            NSString *orderID = userInfo[kSmpcQuickSDKKeyOrderId];
            NSString *cpOrderID = userInfo[kSmpcQuickSDKKeyCpOrderId];
            NSLog(@"充值成功数据：%@,%@",orderID,cpOrderID);
        }
            break;
        case SMPC_QUICK_SDK_ERROR_RECHARGE_CANCELLED:
        case SMPC_QUICK_SDK_ERROR_RECHARGE_FAILED:
        {
            //充值失败
            NSString *orderID = userInfo[kSmpcQuickSDKKeyOrderId];
            NSString *cpOrderID = userInfo[kSmpcQuickSDKKeyCpOrderId];
            NSLog(@"充值失败数据%@,%@",orderID,cpOrderID);
        }
            break;
        default:
            break;
    }
}
- (void)smpcQpPauseOver:(NSNotification *)notify{
    NSLog(@"收到QuickSDK暂停结束通知");
}
#endif

//- (IBAction)payBtnDidClicked:(id)sender
//{
//    //拉起内购支付，扩展字段Extral对应支付接口ext
//    [[YRApplePayMgr sharedManager] requestProductWithId:@"com.yourui.YRSuspend010" andDelegte:self andExtral:@"123456"];
//}

//支付成功的回调
- (void)successedWithReceipt:(NSData *)transactionReceipt
{
    NSLog(@"购买成功");
    
//    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"失败" message:@"" delegate:self cancelButtonTitle:@"关闭" otherButtonTitles:nil, nil];
//    [alert show];
    
    
}

//MARK:- 支付代理



-(void)playVideo: (NSString *) file
{
    [CCVideoPlayer cancelPlaying];
    [CCVideoPlayer setNoSkip: NO];//视频是否可以跳過
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
    
    
#ifdef YJ_IOS
    [[SMPCQuickSDK defaultInstance] application:app didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
#endif
}

- (void)applicationWillResignActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->pause();
}
- (void)applicationDidBecomeActive:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->resume();
}
- (void)applicationDidEnterBackground:(UIApplication *)application {
    
#ifdef YJ_IOS
    [[SMPCQuickSDK defaultInstance] applicationDidEnterBackground:application];
#endif
    
    [CCVideoPlayer pause];
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
    //OCandCppHelper::EnterBackGroud();
}
- (void)applicationWillEnterForeground:(UIApplication *)application {
#ifdef YJ_IOS
    [[SMPCQuickSDK defaultInstance] applicationWillEnterForeground:application];
#endif
    
    [CCVideoPlayer resume];
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    //OCandCppHelper::EnterFront();
}
- (void)applicationWillTerminate:(UIApplication *)application {
    
}
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
#ifdef YJ_IOS
    [[SMPCQuickSDK defaultInstance] openURL:url application:application];
#endif
    
    return  YES;
}



- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString*, id> *)options{
#ifdef YJ_IOS
       [[SMPCQuickSDK defaultInstance] openURL:url application:app options:options];
#endif
    return YES;
}
- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray * restorableObjects))restorationHandler{
#ifdef YJ_IOS
   [[SMPCQuickSDK defaultInstance] application:application continueUserActivity:userActivity restorationHandler:restorationHandler];
#endif
    return YES;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
#ifdef YJ_IOS
    [[SMPCQuickSDK defaultInstance] openURL:url sourceApplication:sourceApplication application:application annotation:annotation];
#endif

    
    return  YES;
}
#ifdef YJ_IOS
- (NSUInteger)application:(UIApplication *)app supportedInterfaceOrientationsForWindow:(UIWindow *)win {
    [[SMPCQuickSDK defaultInstance] application:app supportedInterfaceOrientationsForWindow:win];
    return UIInterfaceOrientationMaskAll;
}
#endif

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
        if(buttonIndex != 0)
        {
            abort();
        }
    }if (alertView.tag == LAYER_TAG_FOR_UPDATE) {
    }else if (alertView.tag == LAYER_TAG_UPDATE) {
    }else if(alertView.tag == LAYER_TAG_KY_UPDATE_1)
    {
    }
}



@end
