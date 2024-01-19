
#import "PaymentViewController.h"



@implementation PaymentViewController


#pragma mark -
#pragma mark SotoreKit method




- (void) requestProductData:(NSString *)kMyFeatureIdentifier;
{
	NSLog(@"kMyFeatureIdentifier %@",kMyFeatureIdentifier);
	
	SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers: [NSSet setWithObject: kMyFeatureIdentifier]];
	request.delegate = self;
	[request start];
    [request release];
}


#pragma mark request delegate
//!收到产品的消息
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
//    NSLog(@"-----------收到产品反馈信息--------------");   
    NSArray *myProduct = response.products;   
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);   
    NSLog(@"产品付费数量: %d", [myProduct count]);
    CCLog("%s",OCandCppHelper::getProjectName());
    if ([myProduct count] > 0)
    {
        // populate UI  
        for(SKProduct *product in myProduct){   
            NSLog(@"product info");   
            NSLog(@"SKProduct 描述信息%@", [product description]);      
            NSLog(@"产品标题 %@" , product.localizedTitle);   
            NSLog(@"产品描述信息: %@" , product.localizedDescription);   
            NSLog(@"价格: %@" , product.price);   
            NSLog(@"Product id: %@" , product.productIdentifier); 
            SKPayment *payment =  [SKPayment paymentWithProduct:product];            
            [[SKPaymentQueue defaultQueue] addPayment: payment];
//            SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
//            payment.quantity = 1;
//            NSString *strRoleID = [NSString stringWithFormat:@"%d",MB_RoleData::getInstance()->getUID()];
//            payment.applicationUsername = strRoleID;
//            [[SKPaymentQueue defaultQueue] addPayment: payment];
        }
    }
    else
    {
        
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"错误" message:@"无法获取产品信息，购买失败。" delegate:self   cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
        [alerView setTag:100];
        [alerView show];
        [alerView release];
        
    }
    
     NSLog(@"end");
  }

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
	NSLog(@"error %@",error);
	NSLog(@"[error localizedDescription] %@",[error localizedDescription]);
	UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert" message:[error localizedDescription] delegate:self  cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
	
	[alerView show];
	[alerView release];
 }


-(void)setPayment:(NSString *)productId {
	
	NSLog(@"productId %@",productId);
	if([SKPaymentQueue canMakePayments])
	{
		
		[self requestProductData:productId];
        
	}else {
        NSLog(@"不允许程序内付费购买");    
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"    
                                                            message:@"You can‘t purchase in app store（您没允许应用程序内购买）"                                                           
                                                           delegate:self cancelButtonTitle:@"Close（关闭）" otherButtonTitles:nil];
        
        [alerView setTag:100];
        [alerView show];   
        [alerView release];  


	}
}
//alter close
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{

}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;
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
