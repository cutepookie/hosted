

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h> 
#import <StoreKit/SKPaymentTransaction.h> 
#import "MB_Message.h"
#import "Game.h"

@interface MyStoreObserver : NSObject<SKPaymentTransactionObserver,UIAlertViewDelegate> {
	
    NSString *productId;
    NSMutableArray *m_pArray;
}

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;
-(void) completeTransaction: (SKPaymentTransaction *)transaction;
-(void) failedTransaction: (SKPaymentTransaction *)transaction;
+(BOOL) putStringToItunes:(NSData*)iapData;
+(BOOL) putStringToItunes2:(NSData*)iapData;
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;
+(id) instance;
-(void) restoreTransaction: (SKPaymentTransaction *)transaction;
+(void) provideContent:(NSString *)product;
-(void) recordTransaction:(NSString *)product;
-(void) finishTransactionByRec:(const char *)iapData;
@end
