

#include "MB_NodePetDuiWuFang.h"
#include "MB_LayerGuard.h"
#include "MB_TeamData.h"
#include "MB_LayerPetEquipment.h"
MB_NodePetDuiWuFang::MB_NodePetDuiWuFang(uint64_t petId){
    m_nPetId = petId;
    m_pSprite_face = NULL;
    m_pSize = NULL;
    m_pBg = NULL;
    m_pToVis = NULL;
}
MB_NodePetDuiWuFang::~MB_NodePetDuiWuFang(){
    
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE_NULL(m_pSize);
    CC_SAFE_RELEASE_NULL(m_pBg);
    CC_SAFE_RELEASE_NULL(m_pToVis);
}

MB_NodePetDuiWuFang * MB_NodePetDuiWuFang::create(uint64_t petId){
    
    MB_NodePetDuiWuFang *node = new MB_NodePetDuiWuFang(petId);
    
    if( node && node->init() ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool  MB_NodePetDuiWuFang::init(){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_iconDuiWuFang.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    
    m_nWidth = m_pSize->getContentSize().width;
    m_nHeight= m_pSize->getContentSize().height;
    if (m_nPetId==-1) {
        m_pToVis->setVisible(false);
        return true;
    }
    
    setPetID(m_nPetId);
    
    return true;
}

bool MB_NodePetDuiWuFang::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSize", CCNode *, m_pSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCSprite *, m_pBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVis", CCNode *, m_pToVis);
    return  false;
}
SEL_MenuHandler MB_NodePetDuiWuFang::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
SEL_CCControlHandler MB_NodePetDuiWuFang::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickDetail",MB_NodePetDuiWuFang::onClickDetail);
    return NULL;
}

void MB_NodePetDuiWuFang::onClickDetail(CCObject * pSender)
{
    m_pLg->setSelectPetID(m_nIndex);
}

void MB_NodePetDuiWuFang::setPetID(uint64_t petId)
{
    if (m_nPetId==-1) {
        m_nPetId = petId;
        m_pToVis->setVisible(true);
    }
    if(petId == -1)
    {
        m_nPetId = petId;
        m_pToVis->setVisible(false);
    }

    MB_PetData  *petData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    if (petData==NULL)
    {
        return;
    }
    MB_PetTemplate *petTempelete = petData->getTemplete();
    if (petTempelete==NULL)
    {
        return;
    }
    NSGameHelper::setSpriteFrame(m_pSprite_face, petTempelete->getPetFace(NSGameHelper::getShapeTypeByRank(petData->getPetQuallity())));
    m_pBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTempelete->getPetKingdom())->getCString()));
}

void MB_NodePetDuiWuFang::setParent(MB_LayerGuard* lg,int index)
{
    m_pLg = lg;
    m_nIndex = index;
}
