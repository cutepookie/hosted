
#include "MB_NodePetAid.h"
#include "MB_LayerEqCompare.h"
#include "MB_LayerPetCommand.h"
#include "MB_LayerGuard.h"
#include "MB_LayerPetEquipment.h"
MB_NodePetAid::MB_NodePetAid(){
    
    m_nPetId = 0;
    m_pSprite_face = NULL;
    m_pSprite_quality = NULL;
    m_pMenu = NULL;
    m_pNodActive = NULL;
    m_pInfo = NULL;
    m_pNodeSelect = NULL;
    m_bShowTutorial = false;
    
}
MB_NodePetAid::~MB_NodePetAid(){
    
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pSprite_quality);
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE(m_pNodActive);
    CC_SAFE_RELEASE(m_pInfo);
    CC_SAFE_RELEASE(m_pNodeSelect);
    SOCKET_MSG_UNREGIST(SC_GER_LIEU_UNTIE);

}

MB_NodePetAid::MB_NodePetAid(uint64_t petId){
    
    m_nPetId = petId;
    m_pSprite_face = NULL;
    m_pSprite_quality = NULL;
    m_pMenu = NULL;
    m_pNodActive = NULL;
    m_pInfo = NULL;
    m_pNodeSelect = NULL;
    
}

bool MB_NodePetAid::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    if(m_bShowTutorial)
    {
       TutorialAssignLayerWindow
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_quality", CCSprite *, m_pSprite_quality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pmenu", CCMenu *, m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodActive", CCNode *, m_pNodActive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInfo", CCLabelTTF *, m_pInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelect", CCNode *, m_pNodeSelect);
    return  false;
}
SEL_MenuHandler MB_NodePetAid::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClick", MB_NodePetAid::onIconClick);
    
    return NULL;
}
SEL_CCControlHandler MB_NodePetAid::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
void MB_NodePetAid::onIconClick(CCObject *){
    
    TutorialTriggerComplete
    MB_LOG("on click ");
    MB_TARGET_PARENT(MB_LayerPetEquipment, ptr)
}
bool MB_NodePetAid::init(){
    
    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    
    if(m_nType == kNodePetTypeMain || m_nType == kNodePetTypeAid || m_nType == kNodePetTypeGuard){
    
        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_skipper.ccbi", this);
        this->addChild(node);
        pCCBReader->release();
        m_pMenu->setSwallowsTouches(false);
        if(m_pNodeSelect){
        
            m_pNodeSelect->setVisible(false);
        }
    
    }else if(m_nType == kNodePetTypeLock){
    
        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_locked2.ccbi", this);
        this->addChild(node);
        pCCBReader->release();
        char databuf[80];
        sprintf(databuf, "Lv.%llu\n开启",m_nPetId);
        m_pInfo->setString(databuf);
        return true;
        
    }else if(m_nType == kNodePetTypeAidNoneLock){
        
        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petassistant_untieprestige.ccbi", this);
        this->addChild(node);
        pCCBReader->release();
        char databuf[80];
        sprintf(databuf, "  解锁  \n%llu补天石",m_nPetId);
        m_pInfo->setString(databuf);
        
        return true;
    }
    else if(m_nType == kNodePetTypeAidNone || m_nType == kNodePetTypeMainNone){
        
        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_add.ccbi", this);
        this->addChild(node);
        pCCBReader->release();
        m_pMenu->setSwallowsTouches(false);
        return true;
    }
//    else  if(m_nType == kNodePetTypeTeamAid) {
//        
////        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petportrait_activation.ccbi", this);
////        this->addChild(node);
////        pCCBReader->release();
//        
//    }else if(m_nType == kNodePetTypeTeamLock){
//        
//        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petassistant_locked.ccbi", this);
//        this->addChild(node);
//        pCCBReader->release();
//        char databuf[80];
//        sprintf(databuf, "Lv.%llu\n开启",m_nPetId);
//        m_pInfo->setString(databuf);
//        return true;
//        
//    }else if(m_nType == kNodePetTypeTeamAidNone){
//        
//        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petassistant_add2.ccbi", this);
//        this->addChild(node);
//        pCCBReader->release();
//        return true;
//        
//    }else if(m_nType == kNodePetTypeTeamAidNoneLock){
//        
//        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petassistant_untieprestige2.ccbi", this);
//        this->addChild(node);
//        pCCBReader->release();
//        char databuf[80];
//        sprintf(databuf, "%llu徽章",m_nPetId);
//        m_pInfo->setString(databuf);
//        return true;
//    
//    }
    if (m_nType == kNodePetTypeMain) {
    
//        m_pNodeMainPet->setVisible(true);
//        m_pNodeLiPet->setVisible(false);
    
    }else if(m_nType == kNodePetTypeAid) {
    
//        m_pNodeMainPet->setVisible(false);
//        m_pNodeLiPet->setVisible(true);
    }
    if(m_nPetId == 0){
    
        return true;
    }
    MB_PetData  *petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    MB_PetTemplate *petTempelete = petData->getTemplete();
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetFace(NSGameHelper::getShapeTypeByRank(petData->getPetQuallity())));
    if(textrue !=NULL){
        CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pSprite_face->setDisplayFrame(frame);
    }
    NSGameHelper::setHeadFrame(m_pSprite_quality, petTempelete->getPetStar(), MONSTER_HEADFRAME , petData->getPetQuallity());
    NSGameHelper::creatMaskSprite(m_pSprite_face);
    if(m_nType == kNodePetTypeTeamAid){
        
        if(m_pNodActive){
        
            m_pNodActive->setVisible(false);
        }
    }
    return true;
}
int64_t  MB_NodePetAid::getData(){
    
    return m_nPetId;
}
MB_NodePetAid * MB_NodePetAid::createType(uint16_t petType){

    
    MB_NodePetAid *node = new MB_NodePetAid();
    if( node && node->init(petType) ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;

}
bool MB_NodePetAid::init(uint16_t petType){

    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_equipmenticon.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    
    MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(petType);
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetFace());
    if(textrue !=NULL){
        
        CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pSprite_face->setDisplayFrame(frame);
    }

    
    NSGameHelper::setHeadFrame(m_pSprite_quality, petTempelete->getPetStar(), MONSTER_HEADFRAME);
    m_pMenu->setEnabled(false);
    if(m_pNodActive){
        
        m_pNodActive->setVisible(false);
    }
//    if(m_pElite != NULL){
//    
//        m_pElite->setVisible(false);
//    }
    return  true;

}
MB_NodePetAid * MB_NodePetAid::create(uint64_t petId,uint8_t type,bool bShowTutorial){
    
    MB_NodePetAid *node = new MB_NodePetAid(petId);
    node->setType(type);
    node->m_bShowTutorial = bShowTutorial;
    if( node && node->init() ){
        
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
MB_NodePetAid * MB_NodePetAid::createType(MB_PetData* petData,uint8_t type){

    MB_NodePetAid *node = new MB_NodePetAid();
    if( node && node->init(petData, type)){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;
}
bool MB_NodePetAid::init(MB_PetData* petData,uint8_t type){

    MB_ResWindow::init();
    
    m_nType = type;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_skipper.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    m_pMenu->setSwallowsTouches(false);
    if(m_pNodeSelect){
        
        m_pNodeSelect->setVisible(false);
    }    
    if (m_nType == kNodePetTypeMain) {
        
    }else if(m_nType == kNodePetTypeAid) {
    }
    
    MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(petData->getPetTypeID());
    NSGameHelper::setMonsterIconDetailByTid(petTempelete->getPetTypeID(),petData->getPetQuallity(),m_pSprite_face,NULL,m_pSprite_quality,true);

    return  true;
}
void MB_NodePetAid::setMenuTouch(bool iscanTouch){
    
    m_pMenu->setTouchEnabled(iscanTouch);
}
void MB_NodePetAid::setActive(bool isActive){

    m_pNodActive->setVisible(isActive);
}
CCSize MB_NodePetAid::getNodeSize(){

    return    m_pSprite_quality->getContentSize();
}
void MB_NodePetAid::setIsSelect(bool isSelect){
    
    if(m_pNodeSelect){
    
        m_pNodeSelect->setVisible(isSelect);
    
    }
}
void  MB_NodePetAid::onMsgRecv(CCNode* node, SocketResponse* response){

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
                
            case SC_GER_LIEU_UNTIE:{
             
                uint8_t result ;
                recvPacket->readU8(&result);
                if(result == 1){
                
                    this->removeAllChildrenWithCleanup(true);
                    CC_SAFE_RELEASE(m_pSprite_face);
                    CC_SAFE_RELEASE(m_pSprite_quality);
                    CC_SAFE_RELEASE(m_pMenu);
//                    CC_SAFE_RELEASE(m_pElite);
                    CC_SAFE_RELEASE(m_pNodActive);
//                    CC_SAFE_RELEASE(m_pNodeMainPet);
//                    CC_SAFE_RELEASE(m_pNodeLiPet);
                    CC_SAFE_RELEASE(m_pInfo);
                    CC_SAFE_RELEASE(m_pNodeSelect);
                    SOCKET_MSG_UNREGIST(SC_GER_LIEU_UNTIE);
                
                    
                    m_pSprite_face = NULL;
                    m_pSprite_quality = NULL;
                    m_pMenu = NULL;
//                    m_pElite = NULL;
                    m_pNodActive = NULL;
//                    m_pNodeLiPet = NULL;
//                    m_pNodeMainPet = NULL;
//                    m_pNodeLiPet = NULL;
                    m_pInfo = NULL;
                    m_pNodeSelect = NULL;
                    
                    if(m_nType == kNodePetTypeTeamAidNoneLock){
                    
                        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
                        CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
                        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/obj_petassistant_add2.ccbi", this);
                        this->addChild(node);
                        pCCBReader->release();
                        m_pMenu->setSwallowsTouches(false);
                        m_nType = kNodePetTypeTeamAidNone;
              
                    }else {
                    
                        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
                        CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
                        CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_add.ccbi", this);
                        this->addChild(node);
                        pCCBReader->release();
                        m_pMenu->setSwallowsTouches(false);
                        m_nType = kNodePetTypeAidNone;
                    }
                }
                
            }
        
                break;
            default:
                break;
            
        }
}
