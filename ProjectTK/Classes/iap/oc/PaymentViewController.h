

#import <UIKit/UIKit.h>
#import<StoreKit/StoreKit.h>
#import "MyStoreObserver.h"

@interface PaymentViewController : UIViewController<SKProductsRequestDelegate,UIAlertViewDelegate> {


}
-(void)setPayment:(NSString *)productId;
@end
