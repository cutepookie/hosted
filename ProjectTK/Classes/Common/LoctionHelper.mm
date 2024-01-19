//
//  LoctionHelper.cpp
//  LoctionDemo
//
//  Created by cri-mac on 14-4-24.
//
//

#import "LoctionHelper.h"
#include "cocos2d.h"
using namespace cocos2d;
#include "Game.h"
#include "../Game/MB_DataExchange.h"

@implementation LocationHelper

//開始定位
-(void)startLocation
{
    self.locationMgr = [[CLLocationManager alloc] init];
    self.locationMgr.delegate = self;
    self.locationMgr.desiredAccuracy = kCLLocationAccuracyBest;
    self.locationMgr.distanceFilter = 10.0f;
    [self.locationMgr startUpdatingLocation];
}

-(void)dealloc
{
    [super dealloc];
}

//定位代理經緯度回调
-(void)locationMgr:(CLLocationManager *)manapet didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    
    [locationMgr stopUpdatingLocation]; //收到數据停止更新

    NSLog(@"%@",[NSString stringWithFormat:@"经度:%3.5f\n纬度:%3.5f",newLocation.coordinate.latitude,newLocation.coordinate.longitude]);
    
    CLGeocoder * geoCoder = [[CLGeocoder alloc] init];
    [geoCoder reverseGeocodeLocation:newLocation completionHandler:^(NSArray *placemarks, NSError *error)
     {
         if (placemarks.count > 0)
         {
             CLPlacemark *placemark = [placemarks objectAtIndex:0];
             
//             NSString* country = placemark.country;
             NSString* administrativeArea = placemark.administrativeArea;
             NSString* locality = placemark.locality;

             NSString* strLocation=[[NSString alloc] initWithString:@""];
//             if(country != nil)
//             {
//                 strLocation = [strLocation stringByAppendingString:country];
//             }
             if(administrativeArea != nil)
             {
                 strLocation = [strLocation stringByAppendingString:administrativeArea];
             }
             if(locality != nil)
             {
                 strLocation = [strLocation stringByAppendingString:locality];
             }
             
//             NSString* strLocation = [NSString stringWithFormat:@"%@%@%@",country,administrativeArea,locality];
             if(strLocation != nil)
             {
                 const char* pLocation = [strLocation UTF8String];
                 CCLog(pLocation);
                 
                 NSDataExchange::g_LocationName = pLocation;
             }
     

//             NSLog(@"%@",[NSString stringWithFormat:@"1%@ 2%@ 3%@ 4%@ 5%@ 6%@ 7%@ 8%@ 9%@ 10%@ 11%@ 12%@ 13%@",
//                          placemark.name,               //中国四川省成都市武侯區
//                          placemark.thoroughfare,
//                          placemark.subThoroughfare,
//                          placemark.locality,           //成都市
//                          placemark.subLocality,        //武侯區
//                          placemark.administrativeArea, //四川省
//                          placemark.subAdministrativeArea,
//                          placemark.postalCode,
//                          placemark.ISOcountryCode,
//                          placemark.country,            //中国
//                          placemark.inlandWater,
//                          placemark.ocean,
//                          placemark.areasOfInterest
//                          ]);

         }
         else if (error == nil && [placemarks count] == 0)
         {
             NSLog(@"No results were returned.");
         }
         else if (error != nil)
         {
             NSLog(@"An error occurred = %@", error);
         }
     }];
    
    [geoCoder release];
}




@end

