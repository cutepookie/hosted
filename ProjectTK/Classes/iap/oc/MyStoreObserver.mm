
#import "MyStoreObserver.h"
#import<UIKit/UIKit.h>
#import<UIKit/UIAlert.h>
//#import "NSString+SBJSON.h"
//#import "JSON.h"
#import "cocos2d.h"
#import "MB_RoleData.h"
#import "PayMentViewCocos2d.h"



/**
 IAP编号：
 com.happyinfinity.001.001
 
 测试账号:
 rollin_z@164.com
 Ilikethis1
 */

@implementation MyStoreObserver

MyStoreObserver * m_pShareData = nil;
-(id)init{

    self = [super init];
    m_pArray = [[NSMutableArray alloc] init];
    return self;
}
-(void)dealloc{

    [m_pArray removeAllObjects];
    [m_pArray release];
    [super dealloc];
}
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    NSLog(@"updatedTransactions");
    for (SKPaymentTransaction *transaction in transactions)
    {      
        switch (transaction.transactionState)
        {				
            case SKPaymentTransactionStatePurchased://支付
				NSLog(@"-----交易成功 --------");
                [self completeTransaction:transaction];			
                break;
                
            case SKPaymentTransactionStateFailed://失败
               	NSLog(@"-----交易失败 --------");
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored://付款交易状态恢复
              	NSLog(@"-----已经购买过该商品 --------");  
                [self restoreTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表   
                NSLog(@"-----商品添加进列表 --------");   
                break;   
				
            default:
				
                break;
        }
        
    }    
}
+(id) instance{

    if(m_pShareData == nil){
    
        m_pShareData =  [[MyStoreObserver alloc] init];
    }
    return m_pShareData;
}
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction
{
	NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
	[self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
	[transactions release];
}

- (void) completeTransaction: (SKPaymentTransaction *)transaction
{	//纪录补单
    //nsdata=transaction.transactionReceipt;
    //nspductid=  NSString *product 
    //nsshijian;
    //jilu
    //[[UserData instence] addToBuyList:transaction.payment.productIdentifier andTransRepeint:transaction.transactionReceipt];
    [m_pArray addObject:transaction];
	// Your application should implement these two methods.
//    NSLog(@"username:%@",transaction.payment.applicationUsername);
    if ([MyStoreObserver putStringToItunes:transaction.transactionReceipt]||[MyStoreObserver putStringToItunes2:transaction.transactionReceipt])
    {
       
        //[[UserData instence] popOutBuy];
        
        NSString *product = transaction.payment.productIdentifier;
        NSLog(@"订单发送成功.product:%@",product);
      
    }else {
        
        UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle: @"网络错误"
                                                             message: @"网络链接失败！"
                                                            delegate:self  cancelButtonTitle: @"Close（关闭）" otherButtonTitles:nil];
        [alerView2 setTag:100];
        [alerView2 show];   
        [alerView2 release];  
        
        //纪录补单
        //nsdata=transaction.transactionReceipt;
        //nspductid=  NSString *product 
        //nsshijian;
        //jilu
        }
}
-(void) finishTransactionByRec:(const char * )iapData{

    NSString* strIapData = [NSString stringWithFormat:@"%s",iapData];
    for (SKPaymentTransaction * transaction in m_pArray) {
        
        NSString *transbye = [NSString stringWithFormat:@"%s",(char*)transaction.transactionReceipt.bytes];
        if([strIapData isEqualToString:transbye]){
        
            [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
            [m_pArray removeObject:transaction];
            break;
        }

    }
    
}
//记录交易
-(void)recordTransaction:(NSString *)product
{
	
    
}

//处理交易完成
+(void)provideContent:(NSString *)product
{	
    NSLog(@"buy %@",product);
    MB_PayTemplete* payTemplete = NULL;
    CCArray* payArray = MB_RoleData::getInstance()->getPayArray();
    for (int i=0; i < payArray->count(); i++) {
        payTemplete = (MB_PayTemplete*)payArray->objectAtIndex(i);
        NSString *str=[[NSString alloc] initWithFormat:@"%d",payTemplete->getID()];
        if ([product isEqualToString: str]) {
            //购买成功
            NSLog(@"buy scceed.");
            [str release];
            return;
        }
        [str release];
    }
     //购买失败
    UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                             message:@"You can‘t purchase in app store（购买失败，请重新尝试购买～）"
                                                            delegate:self cancelButtonTitle: @"Close（关闭）" otherButtonTitles:nil];
    [alerView2 setTag:100];
    [alerView2 show];
    [alerView2 release];  
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction

{
    NSLog(@"err %d",transaction.error.code);	

    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        
        [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
        
        UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                             message:@"You can‘t purchase in app store（购买失败，请重新尝试购买～）"
                                                            delegate:self cancelButtonTitle: @"Close（关闭）" otherButtonTitles:nil];
        [alerView2 setTag:100];
        [alerView2 show];
        [alerView2 release];
  
        return;
    }else {
        
        [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
        [self alertView:nil willDismissWithButtonIndex:0];
    }
}


- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    [MyStoreObserver provideContent:transaction.originalTransaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
	NSLog(@"paymentQueue");
}

+(BOOL)putStringToItunes:(NSData*)iapData
{
    NSLog(@"iapData: %s",(char*)iapData.bytes);
    return MB_RoleData::getInstance()->sendrole_pay_ios((char*)iapData.bytes, "unkown");
}


+(BOOL)putStringToItunes2:(NSData*)iapData
{
  /*  //用户购成功的transactionReceipt
    NSString*encodingStr = [iapData base64EncodedString];
    NSString *URL=[MobClick getConfigParams:@"IAPURLTEST"];
    if(URL==nil||URL.length==0){
        
        URL=@"https://sandbox.itunes.apple.com/verifyReceipt";
    }else {
        
    
        char str[5]="http";
        for(int i=0;i<5;i++){
            if([URL characterAtIndex:i]!=str[i]){
             
                URL=@"https://sandbox.itunes.apple.com/verifyReceipt";
                break;
            }
        }
        
    }
    
    //@"https://sandbox.itunes.apple.com/verifyReceipt"; //测试沙盒地址
    // NSString *URL=@"http://apple.happyinfinity.com/iap/buyVerifyReceipt";//@"https://buy.itunes.apple.com/verifyReceipt";   //正式上线后地址
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];// autorelease];
    [request setURL:[NSURL URLWithString:URL]];
    [request setHTTPMethod:@"POST"];
    //设置contentType
    [request addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    //设置Content-Length
    [request setValue:[NSString stringWithFormat:@"%d", [encodingStr length]] forHTTPHeaderField:@"Content-Length"];
    
    NSDictionary* body = [NSDictionary dictionaryWithObjectsAndKeys:encodingStr, @"receipt-data", nil];
    SBJsonWriter *writer = [SBJsonWriter new];
    [request setHTTPBody:[[writer stringWithObject:body] dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES]];
    NSHTTPURLResponse *urlResponse=nil;
    NSError *errorr=nil;
    NSData *receivedData = [NSURLConnection sendSynchronousRequest:request
                                                 returningResponse:&urlResponse
                                                             error:&errorr];
    
    //解析
    NSString *results=[[NSString alloc]initWithBytes:[receivedData bytes] length:[receivedData length] encoding:NSUTF8StringEncoding];
    NSDictionary*dic = [results JSONValue];
    
    if ([dic objectForKey:@"status"]==nil) {
        [results release];
        [request release];
        [writer release];
        return NO;
    }
    
    if([[dic objectForKey:@"status"] intValue]==0){//注意，status=@"0" 是验证收据成功
        [results release];
        [request release];
        [writer release];
        return true;
    }
    [results release];
    [request release];
    [writer release];*/
    return false;
}


#pragma mark connection delegate
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"connection didReceiveData");
	NSLog(@"%@",  [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);

	//[self.receivedData appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection{
	NSLog(@"connection DidFinishLoading");
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    NSLog(@"connection didReceiveResponse");
	switch([(NSHTTPURLResponse *)response statusCode]) {
		case 200:
		case 206:
			break;
		case 304:			
			break;
		case 400:			
			break;		
		case 404:
			break;
		case 416:
			break;
		case 403:
			break;
		case 401:
		case 500:
			break;
		default:
			break;
	}	
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	NSLog(@"test");
	
}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0 && alertView.tag == 100) {
        MB_Message::sharedMB_Message()->removeALLMessage();
    }
}
- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex
{
    MB_Message::sharedMB_Message()->removeALLMessage();
}

@end
