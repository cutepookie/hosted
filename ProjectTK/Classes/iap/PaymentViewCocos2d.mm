
#include  "PayMentViewCocos2d.h"
#include "PaymentViewController.h"
#include "MyStoreObserver.h"

#define kMyFeatureIdentifier inAppPurchase

PayMentViewCocos2d::PayMentViewCocos2d(){

    PaymentViewController *  pview= [[PaymentViewController alloc] init];
    MyStoreObserver *observer = [MyStoreObserver instance];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:observer];
    objobject=observer;
    payViewController=pview;

}

PayMentViewCocos2d::~PayMentViewCocos2d(){

    if(s_PayMent != NULL){
        
        s_PayMent = NULL;
    }
    [(PaymentViewController *)payViewController release];
    [(MyStoreObserver *)objobject release];
//    CC_SAFE_DELETE(m_pArray);
}



PayMentViewCocos2d* PayMentViewCocos2d::s_PayMent = NULL;

PayMentViewCocos2d* PayMentViewCocos2d::sharedPayMentView(){

    if (s_PayMent == NULL) {
        
        s_PayMent =new PayMentViewCocos2d();
    }
    return  s_PayMent;
}


void PayMentViewCocos2d::setPayment(const char *productid){

    [(PaymentViewController *)payViewController setPayment: [NSString stringWithUTF8String:productid]]; //您的产品编号

}


void PayMentViewCocos2d::loadFile(){
    
//    xmlDocPtr g_sharedDoc =  TK_XmlReader::readXml(filename);
//    if (!g_sharedDoc)
//    {
//        return ;
//    }
//    xmlNodePtr root;
//    root=xmlDocGetRootElement(g_sharedDoc);
//    xmlNodePtr curNode = root->xmlChildrenNode;
//    char* value;
//    while(curNode != NULL) {
//        
//        if (xmlStrcmp(curNode->name,BAD_CAST "buylist")) {
//            
//            curNode = curNode->next;
//            continue;
//        }
//        struct _xmlAttr * attr = curNode->properties;
//        if (!xmlStrcmp(attr->name,BAD_CAST "cooOrderSerial")){
//            
//            value = (char*)xmlNodeGetContent(attr->children);
//           // m_pArray->addObject(CCString::create(value));
//            CC_SAFE_FREE(value);
//        }
//        curNode = curNode->next;
//    }
//    xmlFreeDoc(g_sharedDoc);
    
}
void PayMentViewCocos2d::saveFile(){
//    
//    return;
//    xmlDocPtr  g_sharedDoc = xmlNewDoc(BAD_CAST "1.0");
//    xmlNodePtr root = xmlNewNode(NULL, BAD_CAST"buylists");
//    xmlDocSetRootElement(g_sharedDoc, root);
//
//    CCObject *obj;
//    CCARRAY_FOREACH(m_pArray, obj){
//        xmlNodePtr preReport = xmlNewNode(NULL,BAD_CAST "buylist");
//        xmlAddChild(root,preReport);
//        xmlNewProp(preReport,BAD_CAST "cooOrderSerial",BAD_CAST ((CCString *)obj)->getCString());
//    }
//    int nRel = xmlSaveFormatFileEnc(filename, g_sharedDoc, "UTF-8", 1);
//    if (nRel != -1)
//    {
//        printf("%s被创建，写入%d个字节\n",filename, nRel);
//    }
//    //释放文档内节点动态申请的内存
//    xmlFreeDoc(g_sharedDoc);
//    char filename2[200];
//    sprintf(filename2, "%s%dappstore.xb",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(),TK_RoleData::getInstance()->getUID());
//    TK_Aescypt::encrypt_stream(filename, filename2);
//    remove(filename);
}

void PayMentViewCocos2d::checkList(){
    
//    CCObject *obj;
//    CCARRAY_FOREACH(m_pArray, obj){
//        
//        TK_RoleData::getInstance()->cs_role_pay_ios(((CCString *)obj)->getCString(), "unkown");
//    }
}

void PayMentViewCocos2d::removeCoord(const char *str){
   
    [[MyStoreObserver instance] finishTransactionByRec: str];
}



