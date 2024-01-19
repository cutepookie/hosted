

#include "MB_NodePet.h"
MB_NodePet::MB_NodePet(){
    isTopZorder = false;
    m_nPetId = 0;
    m_pSprite_face = NULL;
    m_pSprite_quality = NULL;
    m_pSprite_elite = NULL;
    m_pText_level = NULL;
    m_pMenu = NULL;
    m_pLabelName = NULL;
    m_pMask = NULL;
    m_nPetRank = 0;
    m_nPetLevel = 1;
    for (int i = 0; i<MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodePet::MB_NodePet(uint64_t petId){
    
    m_nPetId = petId;
    m_pSprite_face = NULL;
    m_pSprite_quality = NULL;
    m_pSprite_elite = NULL;
    m_pText_level = NULL;
    m_pMenu = NULL;
    m_pMask = NULL;
    m_pLabelName = NULL;
    for (int i = 0; i<MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodePet::~MB_NodePet(){
    
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pSprite_quality);
    CC_SAFE_RELEASE(m_pSprite_elite);
    CC_SAFE_RELEASE(m_pText_level);
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE_NULL(m_pLabelName);
    CC_SAFE_RELEASE_NULL(m_pMask);
    for (int i = 0; i<MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
}


MB_NodePet * MB_NodePet::create(uint64_t petId,bool bCircle){
    
    MB_NodePet *node = new MB_NodePet(petId);
    
    if( node && node->init(bCircle) ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
MB_NodePet * MB_NodePet::create(uint16_t petTypeID, short petLevel, short petQuality,bool bCircle){

    MB_NodePet *node = new MB_NodePet();
    
    if( node && node->init(petTypeID,petLevel,petQuality,bCircle) ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;

}
bool  MB_NodePet::init(uint16_t petTypeID, short petLevel, short petQuality,bool bCircle){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_icon.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    m_pMenu->setSwallowsTouches(false);
    m_nPetTypeID = petTypeID;
    m_nPetRank = petQuality;
    m_nPetLevel = petLevel;
    MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(petTypeID);
    char databuf[50];
    if (petLevel == 0)
    {
        m_pText_level->setString("");
    }else
    {
        sprintf(databuf, "Lv.%d" ,petLevel);
        m_pText_level->setString(databuf);
    }
    
    if(petTempelete)NSGameHelper::setMonsterIconDetailByTid(petTempelete->getPetTypeID(),petQuality,m_pSprite_face,m_pLabelName,m_pSprite_quality,bCircle);
    
    
    //星级
    int normalStar = petTempelete->getPetStar();
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < normalStar) {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
    
    return true;
}

bool  MB_NodePet::init(bool bCircle){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_icon.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    m_pMenu->setSwallowsTouches(false);
    setPetUID(m_nPetId);
    return true;
}
void MB_NodePet::setPetUID(uint64_t petId)
{
    MB_PetData  *petData = MB_PetMgr::getInstance()->getPetDataByUID(petId);
    MB_PetTemplate *petTempelete = petData->getTemplete();
    if (petTempelete==NULL)
    {
        return;
    }
    char databuf[50];
    sprintf(databuf, "Lv.%d" ,petData->getPetLevel());
    m_pText_level->setString(databuf);
    m_pMenu->setTouchEnabled(false);
    
    NSGameHelper::setMonsterIconDetailByTid(petTempelete->getPetTypeID(),petData->getPetQuallity(),m_pSprite_face,m_pLabelName,m_pSprite_quality);
    
    //星级
    int normalStar = petTempelete->getPetStar();
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < normalStar) {
            m_pStar[i]->setVisible(true);
        }
        else
        {
            m_pStar[i]->setVisible(false);
        }
    }
}
bool MB_NodePet::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_quality", CCSprite *, m_pSprite_quality);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_elite", CCSprite *, m_pSprite_elite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleLevel", CCLabelBMFont *, m_pText_level);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pmenu", CCMenu *, m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMask", CCSprite *, m_pMask);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelName", CCLabelTTF*, m_pLabelName);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pStar[i]);
    }
    return  false;
}
SEL_MenuHandler MB_NodePet::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIconClick", MB_NodePet::onIconClick);
    
    return NULL;
}
SEL_CCControlHandler MB_NodePet::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
void MB_NodePet::onIconClick(CCObject *)
{
    MB_PetTemplate *pTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(m_nPetTypeID);
    if (pTemplate == NULL)
    {
        return;
    }
    MB_LayerPetDetail* layerDetail = MB_LayerPetDetail::create(MB_PetMgr::getInstance()->createInstance(pTemplate,m_nPetRank,m_nPetLevel));
    if (m_nPetId==0) {
        layerDetail->setAllBtnShowFalse();
    }
    if(layerDetail)
    {
        if(isTopZorder)
        {
            CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail,Z_ORDER_OUTSHOW+999);
        }else
        {
            CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail,Z_ORDER_OUTSHOW);
        }
    }
}

void MB_NodePet::showName(bool b)
{
    m_pLabelName->setVisible(b);
}

void MB_NodePet::showLevel(bool b)
{
    m_pText_level->setVisible(b);
}

void MB_NodePet::setNameColorBlack()
{
    m_pLabelName->setColor(ccBLACK);
}
int64_t  MB_NodePet::getData(){

    return m_nPetId;
}


void MB_NodePet::setMenuTouch(bool iscanTouch){
    
    m_pMenu->setTouchEnabled(iscanTouch);
    m_pMenu->setEnabled(false);
}
