//
//  LoctionHelper.h
//  LoctionDemo
//
//  Created by cri-mac on 14-4-24.
//
//

#ifndef LoctionDemo_LoctionHelper_h
#define LoctionDemo_LoctionHelper_h


#import <CoreLocation/CoreLocation.h>
@interface LocationHelper :UIViewController<CLLocationManagerDelegate>
{
    CLLocationManager* locationMgr;
}

@property (strong, nonatomic) CLLocationManager* locationMgr;

-(void)locationMgr:(CLLocationManager *)manapet didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation;
-(void)startLocation;
-(void)dealloc;
@end

#endif
