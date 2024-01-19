

#include "MB_NodePetHome.h"
#include "MB_LayerHome.h"
#include "MB_TeamData.h"
MB_NodePetHome::MB_NodePetHome(MB_LayerHome* layerHome,uint64_t petId){
    m_pLayerHome = layerHome;
    m_nPetId = petId;
    m_pSprite_face = NULL;
    m_pText_level = NULL;
    m_pNodeStar = NULL;
    m_pSprite_kuang = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodePetHome::~MB_NodePetHome(){
    
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pText_level);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    CC_SAFE_RELEASE_NULL(m_pSprite_kuang);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i] );
    }
}

MB_NodePetHome * MB_NodePetHome::create(MB_LayerHome* layerHome,uint64_t petId){
    
    MB_NodePetHome *node = new MB_NodePetHome(layerHome,petId);
    
    if( node && node->init() ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool  MB_NodePetHome::init(){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_iconHome.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    if (m_nPetId==-1) {
        showAll(false);
        return true;
    }
    MB_PetData  *petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    if (petData==NULL)
    {
        return false;
    }
    MB_PetTemplate *petTempelete = petData->getTemplete();
    if (petTempelete==NULL)
    {
        return false;
    }
    char databuf[10];
    sprintf(databuf, "Lv.%d" ,petData->getPetLevel());
    m_pText_level->setString(databuf);
    NSGameHelper::setMonsterIconDetailWithStarByTid(petTempelete->getPetTypeID(),petData->getPetQuallity(),NULL,NULL,NULL,m_pNodeStar);
    
    
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetFace(NSGameHelper::getShapeTypeByRank(petData->getPetQuallity())));
    if(textrue !=NULL){
        CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pSprite_face->setDisplayFrame(frame);
    }
    m_pSprite_kuang->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTempelete->getPetKingdom())->getCString()));
    NSGameHelper::setStar(m_pStar, petData->getTemplateStar());
    
    return true;
}


bool MB_NodePetHome::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritekuang", CCSprite *, m_pSprite_kuang);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleLevel", CCLabelBMFont *, m_pText_level);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode *, m_pNodeStar);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    
    return  false;
}
SEL_MenuHandler MB_NodePetHome::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClick", MB_NodePetHome::onIconClick);
    
    return NULL;
}
SEL_CCControlHandler MB_NodePetHome::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
void MB_NodePetHome::onIconClick(CCObject *)
{
    if (m_nPetId==-1) {
        return;
    }
    if (!MB_TutorialMgr::getInstance()->getSkipTutorial()) {
        return;
    }
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    nowHomeShowPetTypeID = petData->getPetTypeID();
    m_pLayerHome->setCardIcon(petData);
}

void MB_NodePetHome::showAll(bool b)
{
    m_pSprite_face->setVisible(b);
    m_pNodeStar->setVisible(b);
    m_pText_level->setVisible(b);
}

