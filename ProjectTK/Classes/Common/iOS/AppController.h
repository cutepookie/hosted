

#import "CCVideoPlayer.h"
@class RootViewController;


@interface AppController : NSObject<

UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate,
CCVideoPlayerDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
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
