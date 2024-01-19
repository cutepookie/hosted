
#include "MB_Message.h"
#include "Game.h"
void MB_Message::removeALLMessage(){

    CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG,true);
}
void MB_Message::removeAllZuZhiMessage(){
    
    CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(ZUZHIMESSAGE_TAG,true);
}
MB_Message* MB_Message::m_sharedMB_Message=NULL ;

MB_Message::MB_Message(){

}

MB_Message::~MB_Message(){

    if (m_sharedMB_Message != NULL) {
        
        m_sharedMB_Message = NULL;
    }

}
MB_Message* MB_Message::sharedMB_Message(){

    if(m_sharedMB_Message == NULL){
    
        m_sharedMB_Message = new MB_Message();
    }
    
    return m_sharedMB_Message;
}
void MB_Message::purge(){
    
    if (m_sharedMB_Message!=NULL) {
        
        delete m_sharedMB_Message;        
        m_sharedMB_Message=NULL;
    }

}
void MB_Message::showMessage(const char *str,float time , CCObject *target ,SEL_CallFunc actionCall,CCPoint *point){
   
    removeALLMessage();
    MB_MessageBox3*m_pLayerMessage3  = MB_MessageBox3::create();   
    CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage3,Z_ORDER_MESSAGE);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    if(point == NULL){
        
      m_pLayerMessage3->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
        
    }else{
    
       m_pLayerMessage3->setPosition(*point);
    }
    m_pLayerMessage3->setTag(MESSAGE_TAG);    
    m_pLayerMessage3->runAction(CCSequence::create(CCDelayTime::create(time),CCFadeOut::create(0.2f),
                                          
                                                                                    CCCallFunc::create(target,actionCall),CCCallFunc::create(m_pLayerMessage3 , callfunc_selector(MB_MessageBox3::MessageOver)),NULL));

}
void MB_Message::showMessage(float time = 5){
    
    removeALLMessage();
    MB_MessageBox3 *message= MB_MessageBox3::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(message,Z_ORDER_MESSAGE);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    message->removeAllChildrenWithCleanup(true);
    message->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
    message->setTag(MESSAGE_TAG);    
    message->runAction(CCSequence::create(CCDelayTime::create(time),                                       
                                       CCCallFunc::create(message, callfunc_selector(MB_MessageBox3::MessageOver)),NULL));
    
}
void MB_Message::showMessage(const char *str,float time,CCPoint *point){
    
    removeALLMessage();
    MB_MessageBox3* m_pLayerMessage3  = MB_MessageBox3::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage3,Z_ORDER_MESSAGE);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    m_pLayerMessage3->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
    m_pLayerMessage3->setTag(MESSAGE_TAG);
    m_pLayerMessage3->runAction(CCSequence::create(CCDelayTime::create(time),CCFadeOut::create(0.2f),
                                                   CCCallFunc::create(m_pLayerMessage3, callfunc_selector(MB_MessageBox3::MessageOver)),NULL));
}
void MB_Message::showZuZhiMessage(const char *message, float time)
{
    removeAllZuZhiMessage();
    MB_MessageBoxZuZhi* messageBoxZuZhi  = MB_MessageBoxZuZhi::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(messageBoxZuZhi,Z_ORDER_MESSAGE);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    messageBoxZuZhi->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
    messageBoxZuZhi->setTag(ZUZHIMESSAGE_TAG);
    messageBoxZuZhi->runAction(CCSequence::create(CCDelayTime::create(time),CCFadeOut::create(0.2f),CCRemoveSelf::create(),NULL));
}
MB_ResWindow* MB_Message::createMessageBox2(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall)
{
    removeALLMessage();
    
    MB_MessageBox2* m_pLayerMessage2  = MB_MessageBox2::create();
    //CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage2,Z_ORDER_MESSAGE);
    m_pLayerMessage2->setTag(MESSAGE_TAG);
    m_pLayerMessage2->set(title,message,buttonone,buttontwo,target,buttonOneCall,buttonTwoCall);
    return m_pLayerMessage2;
}
MB_ResWindow* MB_Message::createMessageBox1(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall)
{
    removeALLMessage();
    
    MB_MessageBox2* layer  = MB_MessageBox2::create();
    layer->setTag(MESSAGE_TAG);
    layer->set(title,message,buttonone,NULL,target,buttonOneCall,NULL);
    
    return layer;
}
MB_ResWindow* MB_Message::showMessage(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall){
  
    removeALLMessage();
    
    MB_MessageBox2* m_pLayerMessage2  = MB_MessageBox2::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage2,Z_ORDER_MESSAGE);
    m_pLayerMessage2->setTag(MESSAGE_TAG);
    m_pLayerMessage2->set(title,message,buttonone,buttontwo,target,buttonOneCall,buttonTwoCall);
  
    return m_pLayerMessage2;
}
void MB_Message::showMessage(const char * title,const char *str,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall,CCPoint *point){
    
    removeALLMessage();
    MB_MessageBox2*  m_pLayerMessage2  = MB_MessageBox2::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage2,Z_ORDER_MESSAGE);
    m_pLayerMessage2->setTag(MESSAGE_TAG);    
    m_pLayerMessage2->set(title,str,buttonone,buttontwo,target,buttonOneCall,buttonTwoCall);
    if(point!=NULL){
        
       m_pLayerMessage2->setPosition(ccp(0,point->y-CCDirector::sharedDirector()->getWinSize().height/2.0f));
    }
}
void MB_Message::showMessage(const char *message, float time){
    
    this->showMessage(message,time,NULL);
}

void MB_Message::showMessage(const char *message){
    
    removeALLMessage();
    while ( CCDirector::sharedDirector()->getRunningScene()->getChildByTag(MESSAGE_LITE_TAG)) {
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_LITE_TAG,true);
    }
    MB_MessageBox4*  m_pLayerMessage4 = MB_MessageBox4::create();
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    if (scene == NULL) {
        return;
        
    }
    
    CCDirector::sharedDirector()->getRunningScene()->addChild(m_pLayerMessage4,Z_ORDER_MESSAGE);
    m_pLayerMessage4->set(message);
    m_pLayerMessage4->setTag(MESSAGE_LITE_TAG);  

}
void MB_Message::showEditBox(const char * title, const char *message,const char *buttonone, MB_MessageEditDeleate *target ){

    MB_MessageBox5 *mesg = MB_MessageBox5::create();
    CCDirector::sharedDirector()->getRunningScene()->addChild(mesg,Z_ORDER_MESSAGE);
    mesg->set(title,message,buttonone,target);

}
void MB_Message::showMessage(const char *message, CCPoint *point){
    
        this->showMessage(message, 3, point);
}
void MB_Message::showMessage(const char * title, const char *message,const char *buttonone){
    
    this->showMessage(title,message,buttonone,NULL,NULL,NULL,NULL,NULL);

}
void MB_Message::showMessage(const char * title, const char *message,const char *buttonone, CCPoint *point){
    
    this->showMessage(title,message,buttonone,NULL,NULL,NULL,NULL,point);
}
void MB_Message::showMessage(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall){

    this->showMessage(title,message,buttonone,NULL,target,buttonOneCall,NULL);

}
void MB_Message::showMessage(const char * title, const char *message,const char *buttonone, CCObject *target ,SEL_MenuHandler buttonOneCall,CCPoint *point){

      this->showMessage(title,message,buttonone,NULL,target,buttonOneCall,NULL,point);
}
void MB_Message::showMessage(const char * title, const char *message,const char *buttonone,const char *buttontwo){

    this->showMessage(title,message,buttonone,buttontwo,NULL,NULL,NULL,NULL);

}


MB_MessageBox2::MB_MessageBox2(){
    
    m_text_message = NULL;
    m_onOk = NULL;
    m_onOk2 = NULL;
    m_onCancel = NULL;
    target = NULL;        //按钮回调消息处理
    buttonOneCall  = NULL; //回调函数
    buttonTwoCall = NULL; //回调函数
    m_pAniamtion = NULL;
    m_nGoDistroy = false;
}

MB_MessageBox2::~MB_MessageBox2(){

   CC_SAFE_RELEASE(m_text_message );
   CC_SAFE_RELEASE( m_onOk );
   CC_SAFE_RELEASE(m_onOk2 );\
   CC_SAFE_RELEASE(m_onCancel);


}

bool MB_MessageBox2::init(){
    
    if(CCLayer::init() == false){
    
    
        return false;
    }
    setTouchPriority(TOUCHPROPERTY);
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("res/message_layer_popupmessage.ccbi",this);
    this->addChild(node,0);

    ccbReader->release();
    return true;
}

void MB_MessageBox2::registerWithTouchDispatcher(){

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);

}

bool MB_MessageBox2::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_message", CCLabelTTF * , m_text_message);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_onOk", CCControlButton  * , m_onOk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_onOk2", CCControlButton  * , m_onOk2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_onCancel", CCControlButton  * , m_onCancel);
    
    return false;
}
SEL_MenuHandler MB_MessageBox2::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){


    return NULL;
}

SEL_CCControlHandler MB_MessageBox2::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onConfirmClicked", MB_MessageBox2::onConfirmClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onConfirmClicked2", MB_MessageBox2::onConfirmClicked2);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBackClicked", MB_MessageBox2::onBackClicked);
    
    return NULL;

}


void MB_MessageBox2::onConfirmClicked(CCObject *){

//    TutorialTriggerComplete  千万不能加  这个在任何时候都可以弹出来，点击会让引导完成
    
    m_nGoDistroy = true;
    if( target != NULL){
        
        (target->*buttonOneCall)(target);
        
    }
    if (m_nGoDistroy){
        
        this->removeFromParentAndCleanup(true);
    }


}
void MB_MessageBox2::onConfirmClicked2(CCObject *){

//    TutorialTriggerComplete  千万不能加
    m_nGoDistroy = true;
    if( target != NULL && buttonOneCall!= NULL){
        
        (target->*buttonOneCall)(target);
        
    }
    if (m_nGoDistroy){
    
        this->removeFromParentAndCleanup(true);
    }

}
void MB_MessageBox2::onBackClicked(CCObject *){
   
//    TutorialTriggerComplete  千万不能加
    
    m_nGoDistroy = true;
    if( target != NULL && buttonTwoCall!= NULL){
        
        (target->*buttonTwoCall)(target);
        
    }
    if (m_nGoDistroy){
        
        this->removeFromParentAndCleanup(true);
    }

}

void  MB_MessageBox2::set(const char * title, const char *message,const char *buttonone,const char *buttontwo, CCObject *target ,SEL_MenuHandler buttonOneCall,SEL_MenuHandler buttonTwoCall){
   
    this->target = target;
    this->buttonOneCall = buttonOneCall;
    this->buttonTwoCall = buttonTwoCall;
    m_text_message->setString(message);
    m_onOk->setVisible(true);
    m_onCancel->setVisible(true);
    m_onOk2->setVisible(true);
    buttonIsGo[0] = false;
    buttonIsGo[1] = false;
    buttonIsGo[2] = false;
    m_nGoDistroy = false;
    m_onOk->sendActionsForControlEvents(CCControlEventTouchUpOutside);
    m_onOk2->sendActionsForControlEvents(CCControlEventTouchUpOutside);
    m_onCancel->sendActionsForControlEvents(CCControlEventTouchUpOutside);
    if ( buttontwo == NULL ) {
        
        m_onOk->setVisible(false);        
        m_onCancel->setVisible(false);        
//        m_onOk2->setTitleForState(CCString::create(buttonone), CCControlStateNormal);
//        m_onOk2->setTitleForState(CCString::create(buttonone), CCControlStateSelected);
//        m_onOk2->setTitleForState(CCString::create(buttonone),CCControlStateHighlighted);
    }else  {
        
        m_onOk2->setVisible(false);
        
//        m_onOk->setTitleForState(CCString::create(buttonone), CCControlStateNormal);
//        m_onOk->setTitleForState(CCString::create(buttonone), CCControlStateSelected);
//        m_onOk->setTitleForState(CCString::create(buttonone),CCControlStateHighlighted);
//
//        m_onCancel->setTitleForState(CCString::create(buttontwo), CCControlStateNormal);
//        m_onCancel->setTitleForState(CCString::create(buttontwo), CCControlStateSelected);
//        m_onCancel->setTitleForState(CCString::create(buttontwo),CCControlStateHighlighted);

    }
 
}
bool MB_MessageBox2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    
    if (m_onOk ->isVisible()) {
        
          buttonIsGo[0] =  m_onOk->ccTouchBegan(pTouch, pEvent);
    }
    if (m_onOk2 ->isVisible()) {
        
           buttonIsGo[1] = m_onOk2->ccTouchBegan(pTouch, pEvent);
    }
    if ( m_onCancel ->isVisible()) {
        
           buttonIsGo[2] = m_onCancel->ccTouchBegan(pTouch, pEvent);
    }
    
    return true;
}
void MB_MessageBox2::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){

    if (  m_onOk ->isVisible() &&  buttonIsGo[0] ) {
        
        m_onOk->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_onOk2 ->isVisible()  &&  buttonIsGo[1]) {
        
        m_onOk2->ccTouchMoved(pTouch, pEvent);
    }
    if ( m_onCancel ->isVisible()  &&  buttonIsGo[2]) {
        
        m_onCancel->ccTouchMoved(pTouch, pEvent);
    }
    
}

void MB_MessageBox2::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

    if (  m_onOk ->isVisible()  &&  buttonIsGo[0]) {
        
        m_onOk->ccTouchEnded(pTouch, pEvent);
    }
    
    if (m_onOk2 ->isVisible()  &&  buttonIsGo[1]) {
        
        m_onOk2->ccTouchEnded(pTouch, pEvent);
    }
    if ( m_onCancel ->isVisible()  &&  buttonIsGo[2]) {
        
        m_onCancel->ccTouchEnded(pTouch, pEvent);
    }
    
}

MB_MessageBox3::MB_MessageBox3(){
    m_pAniamtion = NULL;
}
MB_MessageBox3::~MB_MessageBox3(){
    this->stopAllActions();
    m_pAniamtion->setAnimationCompletedCallback(NULL,NULL);
    
    CC_SAFE_RELEASE(m_pAniamtion);

}
bool MB_MessageBox3::init(){

    if(CCLayer::init() == false){        
        
        return false;
    }
    setTouchPriority(TOUCHPROPERTY);
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("res/message_layer_responsetime.ccbi",this);
    this->addChild(node,0);
    m_pAniamtion  = ccbReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAniamtion);
    ccbReader->release();
    return  true;
}
void MB_MessageBox3::registerWithTouchDispatcher(){

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);

}
bool MB_MessageBox3::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

    
    return false;
}
SEL_MenuHandler MB_MessageBox3::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    return NULL;
}
SEL_CCControlHandler MB_MessageBox3::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}

bool MB_MessageBox3::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);
    return true;
}
void MB_MessageBox3::setPosition(CCPoint pos){
    CCLayer::setPosition(pos);
}
void MB_MessageBox3::MessageOver(){
    m_pAniamtion->setAnimationCompletedCallback(NULL, NULL);
    this->removeFromParentAndCleanup(true);
}
void MB_MessageBox3::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    CC_UNUSED_PARAM(pEvent);
}
void MB_MessageBox3::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    
}

MB_MessageBox4::MB_MessageBox4(){
    m_pAnimation = NULL;
    m_text_message = NULL;
}
MB_MessageBox4::~MB_MessageBox4(){

    CC_SAFE_RELEASE(m_pAnimation);
    CC_SAFE_RELEASE(m_text_message);
    
}
bool MB_MessageBox4::init(){
    
    if(CCLayer::init() == false){
        
        return false;
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("res/message_layer_title.ccbi",this);
    this->addChild(node,0);
    m_pAnimation = ccbReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    ccbReader->release();    
    return  true;
}


void MB_MessageBox4::onExit()
{
    m_pAnimation->setAnimationCompletedCallback(NULL,NULL);
    CCLayer::onExit();
};
void MB_MessageBox4::set(const char *message){
    
        m_text_message->setString(message);
        m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector( MB_MessageBox4::MessageOver));
        m_pAnimation->runAnimationsForSequenceNamed("Default Timeline");
}
bool MB_MessageBox4::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_message", CCLabelTTF* , m_text_message);
    
    return false;
}
SEL_MenuHandler MB_MessageBox4::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    

    return NULL;
}
SEL_CCControlHandler MB_MessageBox4::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
void MB_MessageBox4::MessageOver(){
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    this->removeFromParentAndCleanup(true);
}

MB_MessageBox5::MB_MessageBox5(){
    m_title = NULL;
    m_onOk2 = NULL;
    target = NULL;        //按钮回调消息处理
    m_pEditCode = NULL;
}

MB_MessageBox5::~MB_MessageBox5(){
    
    
    CC_SAFE_RELEASE(m_title);
    CC_SAFE_RELEASE(m_onOk2 );
 
}

bool MB_MessageBox5::init(){
    
    if(CCLayer::init() == false){
        
        
        return false;
    }
    
    CCNode *pNode1 = CCNode::create();
    pNode1->setContentSize(CCDirector::sharedDirector()->getWinSize());
    CCNode *pNode2 = CCNode::create();
    pNode2->setContentSize(CCDirector::sharedDirector()->getWinSize());
    CCMenuItem * menuitem = CCMenuItemSprite::create(pNode1, pNode2);
    CCMenu *menu = CCMenu::create(menuitem,NULL);
    this->addChild(menu);

//    setTouchPriority(TOUCHPROPERTY);
//    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(false);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("res/message_layer_exitbox.ccbi",this);
    this->addChild(node,0);
    ccbReader->release();
    
 
    return true;
}

void MB_MessageBox5::registerWithTouchDispatcher(){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
    
}

bool MB_MessageBox5::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_title", CCLabelTTF * , m_title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_onOk2", CCControlButton  * , m_onOk2);
    if ( 0 == strcmp(pMemberVariableName, "Account")) {
        
        initEditBox((CCEditBox*)pNode);
        
    }
    
    return false;
}
SEL_MenuHandler MB_MessageBox5::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    
    return NULL;
}

SEL_CCControlHandler MB_MessageBox5::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onConfirmClicked2", MB_MessageBox5::onConfirmClicked);
    
    return NULL;
    
}
void MB_MessageBox5::onConfirmClicked(CCObject *){
    
    if( target != NULL){
        
        if( dynamic_cast<MB_MessageEditDeleate *>(target) != NULL){
        
            ((MB_MessageEditDeleate *)target)->setString(m_pEditCode->getText());
        }
        
    }
    this->removeFromParentAndCleanup(true);
    
}


void  MB_MessageBox5::set(const char * title, const char *message,const char *buttonone,  MB_MessageEditDeleate *target){
    
    this->target = target;
    m_title->setString(title);
    buttonIsGo[0] = false;
//    m_onOk2->setTitleForState(CCString::create(buttonone), CCControlStateNormal);
//    m_onOk2->setTitleForState(CCString::create(buttonone), CCControlStateSelected);
//    m_onOk2->setTitleForState(CCString::create(buttonone),CCControlStateHighlighted);
    m_pEditCode->setPlaceHolder(message);
  
}
bool MB_MessageBox5::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

    buttonIsGo[0] =  m_onOk2->ccTouchBegan(pTouch, pEvent);
    
    return true;
}
void MB_MessageBox5::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
   
    if(buttonIsGo[0]){
   
        m_onOk2->ccTouchMoved(pTouch, pEvent);
    }
}

void MB_MessageBox5::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

    
    if(buttonIsGo[0]){
    
        m_onOk2->ccTouchEnded(pTouch, pEvent);
    }
    
}
void MB_MessageBox5::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{

    std::string str = editBox->getText();
    int pos;
    do {
        pos = str.find("\xe2\x80\x86");
        if (pos != std::string::npos) {
            str.replace(pos, 3, "");
        }
        else
        {
            break;
        }
    } while (1);
    
    editBox->setText(str.c_str());
    
}
void MB_MessageBox5::editBoxReturn(CCEditBox* editBox) {
    
}
void MB_MessageBox5::initEditBox(CCEditBox* editBox){
    editBox->setMaxLength(24);
    editBox->setFontColor(ccWHITE);
    m_pEditCode = editBox;
}
MB_MessageBoxZuZhi::MB_MessageBoxZuZhi()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->setDispatchEvents(false);
}
MB_MessageBoxZuZhi::~MB_MessageBoxZuZhi()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->setDispatchEvents(true);
}
bool MB_MessageBoxZuZhi::init(){
    
    if(CCLayer::init() == false){
        
        return false;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("res/message_layer_responsetime.ccbi",this);
    this->addChild(node);
    ccbReader->release();
    return  true;
}
