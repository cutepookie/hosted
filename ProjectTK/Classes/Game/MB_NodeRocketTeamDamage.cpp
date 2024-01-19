

#include "MB_NodeRocketTeamDamage.h"

MB_NodeRocketTeamDamage::MB_NodeRocketTeamDamage(){

    m_pAttackName = NULL;
    m_pNumber = NULL;
    m_pAnimation = NULL;
}
MB_NodeRocketTeamDamage::~MB_NodeRocketTeamDamage(){

    CC_SAFE_RELEASE_NULL(m_pNumber);
    CC_SAFE_RELEASE_NULL(m_pAttackName);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
}
MB_NodeRocketTeamDamage  * MB_NodeRocketTeamDamage::create(uint64_t damage , const char *username){

    MB_NodeRocketTeamDamage *ptr =new MB_NodeRocketTeamDamage();
    if (ptr && ptr->init(damage, username)) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_NodeRocketTeamDamage::init(uint64_t damage,const char * username){
 
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_worldboss_damage.ccbi", this);
    m_pAnimation = pCCBReader->getAnimationManager();
    m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_NodeRocketTeamDamage::whenShowOver));
    CC_SAFE_RETAIN(m_pAnimation);
    this->addChild(node);
    CC_SAFE_DELETE(pCCBReader);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("number.plist");
    char str[20];
    char name[16] = {};

        strcpy(name, "mm.png");
        
        sprintf(str,"-%lld",damage);
    
    CCObject *object = NULL;
    float width = 0;
    CCNode* pContainer = CCNode::create();
    for (int i= 0 ; str[i] != '\0' ; i++)
    {
        if(str[i] == '-')
        {
            name[1] = 'm';
            CCSprite *sprite = CCSprite::createWithSpriteFrameName(name);
            pContainer->addChild(sprite);
            width = width +sprite->getContentSize().width;
        }
        else
        {
            name[1]=str[i];
            CCSprite *sprite = CCSprite::createWithSpriteFrameName(name);
            pContainer->addChild(sprite);
            width = width +sprite->getContentSize().width;
        }
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
    if(username){
    
        m_pAttackName->setString(username);
    
    }else {
    
        m_pAttackName->setString(" ");

    }
    return true;
}
void MB_NodeRocketTeamDamage::whenShowOver(){
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    removeFromParentAndCleanup(true);
}

void MB_NodeRocketTeamDamage::onExit()
{
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    CCNode::onExit();
}

cocos2d::SEL_MenuHandler MB_NodeRocketTeamDamage::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeRocketTeamDamage::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;

}
bool MB_NodeRocketTeamDamage::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAttackName", CCLabelTTF *, m_pAttackName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNumber", CCNode *, m_pNumber);
    return false;
}