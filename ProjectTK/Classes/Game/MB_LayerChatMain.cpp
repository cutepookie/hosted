
#include "MB_LayerChatMain.h"
#include "MB_LayerChatList.h"
MB_LayerChatMain::MB_LayerChatMain(){

    m_pSprite = NULL;
    m_pAnimation = NULL;
    m_nNewmessage = 0;
    SOCKET_MSG_REGIST(SC_TALK_WORLD_MESSAGE, MB_LayerChatMain);
}
MB_LayerChatMain::~MB_LayerChatMain(){

    CC_SAFE_RELEASE(m_pSprite);
    CC_SAFE_RELEASE(m_pAnimation);
    SOCKET_MSG_UNREGIST(SC_TALK_WORLD_MESSAGE);
}


bool static enableMenu(std::map<std::string, bool>& m)
{
    std::map<std::string,bool>::iterator it = m.begin();
    for (; it!=m.end(); ++it)
    {
        if(!it->second)
        {
            return false;
        }
    }
    return true;
}


static std::map<std::string,bool> m_MapChatMainVisible;

void MB_LayerChatMain::SetChatMainVisible(bool b,const char* key)
{
    m_MapChatMainVisible[key] = b;
    CCNode* pNode = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_CHAT_TAG) ;
    if(pNode)pNode->setVisible(b);//(enableMenu(m_MapChatMainVisible));
}

bool MB_LayerChatMain::init(){
    
    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    m_pNode = pCCBReader->readNodeGraphFromFile("res/chat_node_btn.ccbi", this);
    m_pAnimation =pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    pCCBReader->release();
    this->addChild(m_pNode);
    this->setTouchEnabled(true);
    
    m_pSize = CCDirector::sharedDirector()->getWinSize();
    CCSize sz = CCDirector::sharedDirector()->getWinSize();
    m_pNode->setPosition(ccp(sz.width*0.065f, sz.height*0.302f));
    onResetWnd();
    return true;
}
void MB_LayerChatMain::onResetWnd(){

    MB_ResWindow::onResetWnd();
    if(m_nNewmessage == 0){
    
        m_pAnimation->runAnimationsForSequenceNamed("noactive");
        m_pAnimation->setAnimationCompletedCallback(NULL, NULL);

    }else{
    
        m_pAnimation->runAnimationsForSequenceNamed("active");
        m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerChatMain::dirty));

    }
}

MB_LayerChatMain * MB_LayerChatMain::create(){

    MB_LayerChatMain *ptr = new MB_LayerChatMain();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    ptr = NULL;
    return ptr;
}
void MB_LayerChatMain::onRecieveMessage(){

    m_pAnimation->runAnimationsForSequenceNamed("active");
}
void MB_LayerChatMain::onNoMessage(){

    m_pAnimation->runAnimationsForSequenceNamed("noactive");
}
void MB_LayerChatMain::onExit(){

    MB_ResWindow::onExit();
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
}
bool MB_LayerChatMain::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

    if(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_CHAT_LIST_TAG) != NULL){

        return false;
    }

    if(isVisible() == false)return false;

    CCObject * obj;
    CCARRAY_FOREACH(this->getParent()->getChildren(), obj){

        if(((CCNode *)obj)->getZOrder() > this->getZOrder() && ((CCNode *)obj)->getZOrder() != Z_ORDER_MESSAGE){

            return false;
        }
    }

    CCPoint point = pTouch->getLocation();
    CCPoint  des = m_pSprite->convertToNodeSpace(point);
    if(des.x > 0 && des.x < m_pSprite->getContentSize().width && des.y > 0 && des.y < m_pSprite->getContentSize().height){

//        isMove = false;
        return  true;
    }
    return false;
}
//void MB_LayerChatMain::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
//
//    CCPoint point = pTouch->getDelta();
//    m_pNode->setPosition(ccp( m_pNode->getPosition().x + point.x, m_pNode->getPosition().y + point.y));
//    if(point.x >3 || point.x < -3 || point.y > 3 || point.y < - 3){
//
//        isMove  = true;
//    }
//
//}
void MB_LayerChatMain::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

//    if(isMove == false){
    
        onChatClick(NULL);
//    }
    /*
    CCPoint point = pTouch->getDelta();
    point = ccp(point.x+ m_pNode->getPosition().x ,point.y + m_pNode->getPosition().y);
    float left = point.x;
    float right = m_pSize.width- point.x;
    float height = point.y;
    float top = m_pSize.height-point.y;
    if(left <= right && left <= height && left <= top){
    
        if(height < m_pSprite->getContentSize().height/2.0f ){
        
            height = m_pSprite->getContentSize().height/2.0f;
            
        }else if(top  < m_pSprite->getContentSize().height/2.0f){
        
            height  = m_pSize.height - m_pSprite->getContentSize().height/2.0f;
        }
        m_pNode->runAction(CCMoveTo::create(0.1f, ccp(m_pSprite->getContentSize().width/2.0f, height)));

        
    }else  if(right <= left && right <= height && right <= top){
        
        
        if(height < m_pSprite->getContentSize().height/2.0f ){
            
            height = m_pSprite->getContentSize().height/2.0f;
            
        }else if(top  < m_pSprite->getContentSize().height/2.0f){
            
            height  = m_pSize.height - m_pSprite->getContentSize().height/2.0f;
        }
        m_pNode->runAction(CCMoveTo::create(0.1f, ccp(m_pSize.width - m_pSprite->getContentSize().width/2.0f, height)));

        
    }else  if(height <= left && height <= right  && height <= top){
        
        
        if( left  < m_pSprite->getContentSize().width/2.0f ){
            
           left = m_pSprite->getContentSize().width/2.0f;
            
        }else if(right  < m_pSprite->getContentSize().width/2.0f){
            
            left  = m_pSize.width - m_pSprite->getContentSize().width/2.0f;
        }
        m_pNode->runAction(CCMoveTo::create(0.1f, ccp(left, m_pSprite->getContentSize().height/2.0f)));
        
    }else{
    
        
        if( left  < m_pSprite->getContentSize().width/2.0f ){
            
            left = m_pSprite->getContentSize().width/2.0f;
            
        }else if(right  < m_pSprite->getContentSize().width/2.0f){
            
            left  = m_pSize.width - m_pSprite->getContentSize().width/2.0f;
        }
        m_pNode->runAction(CCMoveTo::create(0.1f, ccp(left, m_pSize.height- m_pSprite->getContentSize().height/2.0f)));

    }

    */
}
void MB_LayerChatMain::registerWithTouchDispatcher(void){

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, TOUCHPROPERTY , true);

}
cocos2d::SEL_MenuHandler  MB_LayerChatMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChatClick", MB_LayerChatMain::onChatClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler  MB_LayerChatMain::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
bool  MB_LayerChatMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    if(strcmp("scroller", pMemberVariableName) == 0){
    
        ((CCMenu *)pNode)->setSwallowsTouches(false);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite", CCSprite *, m_pSprite);
    return false;
}


void  MB_LayerChatMain::onChatClick(CCObject *){

//    if(MB_TutorialMgr::getInstance()->getHasTutorialDilog())return;
    CCUserDefault::sharedUserDefault()->setBoolForKey("autoGoDiscovery",false);
    m_nNewmessage = 0;
    dirty();
    CCLayer *layer = MB_LayerChatList::create();
    layer->setTag(LAYER_CHAT_LIST_TAG);
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_CHATLIST);
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(kmBackGround_Default_Effect_Sound).c_str());
}
void  MB_LayerChatMain::onMsgRecv(CCNode* node, SocketResponse* response){

    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_TALK_WORLD_MESSAGE:
            if(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_CHAT_LIST_TAG) == NULL){
                
                m_nNewmessage = 1;
                dirty();
            }
            break;
        default:
            break;
    }
}
