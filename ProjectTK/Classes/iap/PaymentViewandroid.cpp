//
//  PaymentViewCocos2d.cpp
// 
//  Created by YanJiyong on 13-2-22.
//

#include  "PayMentViewCocos2d.h"


#define kMyFeatureIdentifier inAppPurchase

PayMentViewCocos2d::PayMentViewCocos2d(){

  
}

PayMentViewCocos2d::~PayMentViewCocos2d(){

    if(s_PayMent != NULL){
        
        s_PayMent = NULL;
    }

}



PayMentViewCocos2d* PayMentViewCocos2d::s_PayMent = NULL;

PayMentViewCocos2d* PayMentViewCocos2d::sharedPayMentView(){

    if (s_PayMent == NULL) {
        
        s_PayMent =new PayMentViewCocos2d();
    }
    return  s_PayMent;
}


void PayMentViewCocos2d::setPayment(const char *productid){

    // [(PaymentViewController *)payViewController setPayment: [NSString stringWithUTF8String:productid]]; //你的产品编号

}


void PayMentViewCocos2d::loadFile(){
    
    
}
void PayMentViewCocos2d::saveFile(){
    
  
}

void PayMentViewCocos2d::checkList(){
    
  
}
void PayMentViewCocos2d::removeCoord(const char *str){
   
 
    
}


