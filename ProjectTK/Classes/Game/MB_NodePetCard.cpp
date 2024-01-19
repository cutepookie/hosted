

#include "MB_NodePetCard.h"
MB_NodePetCard::MB_NodePetCard(){
    
    m_pCardFace = NULL;
    m_pCountry = NULL;
    m_pQuallity = NULL;
    m_pElite = NULL;
    m_pAnimMgr = NULL;
    m_pPetName = NULL;
    m_pRank = NULL;
    m_pNodeSize = NULL;
    for (int i= 0; i < MAX_GER_STAR; i++) {
    
        m_pStar[i] = NULL;
    }    
}

MB_NodePetCard::~MB_NodePetCard(){
    
    CC_SAFE_RELEASE(m_pCountry);
    CC_SAFE_RELEASE(m_pCardFace);    
    CC_SAFE_RELEASE(m_pQuallity);
    CC_SAFE_RELEASE(m_pElite);
    CC_SAFE_RELEASE(m_pAnimMgr);
    CC_SAFE_RELEASE(m_pPetName);
    CC_SAFE_RELEASE(m_pRank);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    for (int i= 0; i < MAX_GER_STAR; i++) {
        
        CC_SAFE_RELEASE( m_pStar[i]);
    }
}

bool MB_NodePetCard::init(int64_t petId){

    m_nPetId = petId;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_image.ccbi", this);
    this->addChild(node);
    m_pAnimMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimMgr);
    CC_SAFE_DELETE(pCCBReader);    
    MB_PetData *data = MB_PetMgr::getInstance()->getPetDataByUID(petId);
    
    if (data != NULL) {
        m_nPetTypeId = data->getPetTypeID();
        MB_PetTemplate *petTempelete = data->getTemplete();
        CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetCard(data->getPetQuallity()/10+1));
        if(textrue !=NULL){
            
            CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            m_pCardFace->setDisplayFrame(frame);
        }

        NSGameHelper::setQualityFrameByStar(m_pQuallity,petTempelete->getPetStar());
        NSGameHelper::setRankFrame(m_pRank,petTempelete->getPetStar(),data->getPetQuallity());
        if (data->getPetQuallity() >= 2) {
            m_pElite->setVisible(false);
        }else {
            m_pElite->setVisible(false);
        }
    }
    this->setContentSize(m_pNodeSize->getContentSize());
    return true;
}
MB_NodePetCard* MB_NodePetCard::create(int16_t petId,int rank){
    
    MB_NodePetCard* ptr = new MB_NodePetCard();
    if(ptr && ptr->initWithType(petId,rank)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;    
}
 bool MB_NodePetCard::initWithType(uint16_t petTypeId,int rank){
     
     CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
     CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
     CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_image.ccbi", this);
     m_pAnimMgr = pCCBReader->getAnimationManager();
     CC_SAFE_RETAIN(m_pAnimMgr);
     this->addChild(node);
     CC_SAFE_DELETE(pCCBReader);
     m_nPetTypeId = petTypeId;
     
     
     
     MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(petTypeId);
     if( petTempelete != NULL){
         
         CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetCard(NSGameHelper::getShapeTypeByRank(rank)));
         if(textrue !=NULL){
             
             CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
             m_pCardFace->setDisplayFrame(frame);
         }
         
         NSGameHelper::setQualityFrameByStar(m_pQuallity,petTempelete->getPetStar());
         
         NSGameHelper::setRankFrame(m_pRank,petTempelete->getPetStar(),rank);
         
         
         if (rank >= 2) {
             
             m_pElite->setVisible(false);
             int index = 0;
             
             if (rank >= 10){
                 
                 index = 1;
                 
             }else   if (rank >= 5){
                 
                 index = 2;
             }
             else   if (rank >= 2){
                 
                 index = 3;
             }
             char databuf[60];
             sprintf(databuf, "pic_card_elite_%d.png",index);
             CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(databuf);
             if(frame != NULL){
                 
                 m_pElite->setDisplayFrame(frame);
             }
             
         }else {
             m_pElite->setVisible(false);
             
         }
         
     }
     this->setContentSize(m_pNodeSize->getContentSize());
     return true;
}
bool MB_NodePetCard::initWithType(uint16_t petTypeId){

    return initWithType(petTypeId,0);
}
MB_NodePetCard* MB_NodePetCard::createWithType(uint16_t petTypeID){

    MB_NodePetCard* ptr = new MB_NodePetCard();
    if(ptr && ptr->initWithType(petTypeID) ){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
MB_NodePetCard* MB_NodePetCard::createWithFirstType(uint16_t petTypeID){
    
    
    MB_NodePetCard* ptr = new MB_NodePetCard();
    if(ptr && ptr->initWithFirstType(petTypeID,0) ){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
 bool MB_NodePetCard::initWithFirstType(uint16_t petTypeId,int rank){
     
     CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
     CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
     CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_general_card3.ccbi", this);
     m_pAnimMgr = pCCBReader->getAnimationManager();
     CC_SAFE_RETAIN(m_pAnimMgr);
     this->addChild(node);
     CC_SAFE_DELETE(pCCBReader);
     m_nPetTypeId = petTypeId;
     MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(petTypeId);
     if( petTempelete != NULL){
         
         const char *nameStr = MB_PetMgr::getInstance()->getPetRealName(petTypeId, rank/10+1);
         m_pPetName->setString(nameStr);
         CC_SAFE_DELETE_ARRAY(nameStr);
          CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetCard(rank/10+1));
         if(textrue !=NULL){
             
             CCSpriteFrame* frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
             m_pCardFace->setDisplayFrame(frame);
         }

         NSGameHelper::setQualityFrameByStar(m_pQuallity, petTempelete->getPetStar());
         NSGameHelper::setRankFrame(m_pRank,petTempelete->getPetStar(),rank);
         
         if (rank >= 2) {
             
             m_pElite->setVisible(false);
             int index = 0;
             
             if (rank >= 10){
                 
                 index = 1;
                 
             }else   if (rank >= 5){
                 
                 index = 2;
             }
             else   if (rank >= 2){
                 
                 index = 3;
             }
             char databuf[60];
             sprintf(databuf, "pic_icon_elite_%d.png",index);
             CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(databuf);
             if(frame != NULL){
                 
                 m_pElite->setDisplayFrame(frame);
             }
             
         }else {
             
             m_pElite->setVisible(false);
             
         }
         for (int i = 0 ; i < MAX_GER_STAR; i++) {
             
             if (i >= petTempelete->getPetStar()) {
                 
                 m_pStar[i]->setVisible(false);
             }
             else
             {
                 m_pStar[i]->setVisible(true);
             }
         }
     }
     this->setContentSize(m_pNodeSize->getContentSize());
     return true;

}
CCSprite * MB_NodePetCard::getRectSprite(){
    
    return m_pQuallity;

}
cocos2d::SEL_MenuHandler MB_NodePetCard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return  NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodePetCard::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return  NULL;
}
bool MB_NodePetCard::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCardFace" ,CCSprite *, m_pCardFace);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCountry" ,CCSprite *,  m_pCountry);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pElite" ,CCSprite *,  m_pElite);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQuallity" ,CCSprite *,  m_pQuallity);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetName", CCLabelTTF *, m_pPetName);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "SpriteRank", CCSprite *, m_pRank);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSize", CCNode *, m_pNodeSize);
    
     char star[]= "star1";
     for (int i = 0 ; i < MAX_GER_STAR; i++) {
     
         star[4] = '1' +i;
         CCB_MEMBERVARIABLEASSIGNER_GLUE(this,star,CCSprite *,m_pStar[i]);
     }
    
    return false;
}
uint16_t MB_NodePetCard::getPetTypeId(){

    return m_nPetTypeId;
}
MB_NodePetCard* MB_NodePetCard::create(int64_t petId){
    
    MB_NodePetCard* ptr = new MB_NodePetCard();    
    if(ptr && ptr->init(petId) ){
        
        ptr->autorelease();        
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

//void MB_NodePetCard::runAnimation()
//{
//    m_pAnimMgr->runAnimationsForSequenceNamed("Default Timeline");
//};
