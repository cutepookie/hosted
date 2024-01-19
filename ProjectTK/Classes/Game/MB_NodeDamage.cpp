

#include "MB_NodeDamage.h"

MB_NodeDamage::MB_NodeDamage(){
    
    m_pNumber = NULL;
    m_pAnimation = NULL;
    
}
MB_NodeDamage::~MB_NodeDamage(){
    
    CC_SAFE_RELEASE(m_pNumber);
    CC_SAFE_RELEASE(m_pAnimation);
}
MB_NodeDamage * MB_NodeDamage::create(int damage,bool iscrit){
    
    MB_NodeDamage * ptr = new MB_NodeDamage();
    if (ptr && ptr->init( damage ,iscrit) ) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
bool   MB_NodeDamage::init(int damage,bool iscrit){

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/eff_node_damage.ccbi", this);
    
    if (node == NULL) {
        
        return true;
    }
    m_pAnimation = pCCBReader->getAnimationManager();
    m_pAnimation ->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeDamage::whenShowOver));
    this->addChild(node);
    if (iscrit) {
       m_pAnimation->runAnimationsForSequenceNamed("crit");
    }
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_DELETE(pCCBReader);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("number.plist");
    char str[20];
    char name[16] = {};
    if (damage>0)
    {
        strcpy(name, "pm.png");
        sprintf(str,"%d",damage);
    }
    else
    {
        if (iscrit)
        {
            strcpy(name, "cm.png");
        }
        else
        {
            strcpy(name, "mm.png");
        }
        sprintf(str,"%d",-damage);
    }
   
    CCObject *object = NULL;
    float width = 0;
    CCNode* pContainer = CCNode::create();
    for (int i= 0 ; str[i] != '\0' ; i++)
    {
        name[1]=str[i];
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(name);
        sprite->setAnchorPoint(ccp(.5f,0));
        if (i==0) {
            sprite->setScaleY(1.1f);
        }
        pContainer->addChild(sprite);
        width = width +sprite->getContentSize().width;
    }
    m_pNumber->addChild(pContainer);
    float shift = 0;
    
    CCARRAY_FOREACH(pContainer->getChildren(), object)
    {
        CCSprite* characterSprite = (CCSprite*) object;
        characterSprite->setPosition(ccp(shift, 0));
        shift += characterSprite->getContentSize().width*0.7;
    }
    shift = shift * 0.5;
    pContainer->setPositionX(pContainer->getPositionX()-shift);
    
    return true;
}
void MB_NodeDamage::whenShowOver(){
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    this->removeFromParentAndCleanup(true);
}

void MB_NodeDamage::onExit(){
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    CCNode::onExit();
}
void MB_NodeDamage::removeNode(){

   
}
cocos2d::SEL_MenuHandler MB_NodeDamage::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeDamage::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
bool MB_NodeDamage::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "number",CCNode * , m_pNumber);
    
    return false;
}
