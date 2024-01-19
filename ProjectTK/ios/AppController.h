
#ifdef PLATFORM_UC
#import <UCGameSdk/UCGameSdk.h>
#endif
#ifdef PLATFORM_PP
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#endif
#ifdef PLATFORM_KY
#import "KYSDK.h"
#endif
#ifdef PLATFORM_I4
#import <AsSdkFMWK/AsPlatformSDK.h>
#endif
#ifdef PLATFORM_XY
#import <XYPlatform/XYPlatform.h>
#include "MB_XYMgr.h"
#endif
#ifdef PLATFORM_HM
#import "HmcpUpdate.h"
#import <AiBeiFramework/IPAYKIT.h>
#endif
#ifdef PLATFORM_IPG
#import "IIApple.h"
#endif
#ifdef PLATFORM_HJR
#include "MB_LYMgr.h"
#import <GameWorksSDK/GameWorksSDK.h>
#endif
#ifdef PLATFORM_APPSTORE
#include "MB_AppStoreMgr.h"
#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>
#import "ErrorWebView.h"
#endif

#import "CCVideoPlayer.h"
@class RootViewController;

@class Reachability;

@interface AppController : NSObject<
#ifdef PLATFORM_UC
UCGameSdkProtocol,
#endif
#ifdef PLATFORM_PP
PPAppPlatformKitDelegate,
#endif
#ifdef PLATFORM_KY
KYSDKDelegate,
#endif
#ifdef PLATFORM_I4
AsPlatformSDKDelegate,
#endif
#ifdef PLATFORM_XY
XYPayDelegate,
#endif
#ifdef PLATFORM_HJR
GameKitObserverProtocol,
#endif
#ifdef PLATFORM_HM
HmcpUpdateDelegate,IPAYKitLoginDelegate, IPAYKitPaymentDelegate,
#endif
#ifdef PLATFORM_APPSTORE
SKPaymentTransactionObserver,SKProductsRequestDelegate,ErrorWebViewDelegate,
#endif
UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate,
CCVideoPlayerDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    Reachability* hostReach;
    Reachability* internetReach;
    Reachability* wifiReach;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;
-(void)playVideo: (NSString *) file;
- (void) moviePlaybackFinished;
- (void) movieStartsPlaying;
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
- (void) updateOrientationWithOrientation: (UIDeviceOrientation) newOrientation;
#endif
@end

