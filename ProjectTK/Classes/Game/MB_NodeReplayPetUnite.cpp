
#include "MB_NodeReplayPetUnite.h"

MB_NodeReplayPetUnite::MB_NodeReplayPetUnite(){
    m_pSprite_face = NULL;
    m_pBg = NULL;
    m_pSize = NULL;
    m_pLevel = NULL;
    m_pQiangHua = NULL;
    m_pNodeIsDead = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodeReplayPetUnite::~MB_NodeReplayPetUnite(){
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pBg);
    CC_SAFE_RELEASE(m_pSize);
    CC_SAFE_RELEASE(m_pLevel);
    CC_SAFE_RELEASE(m_pQiangHua);
    CC_SAFE_RELEASE(m_pNodeIsDead);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE(m_pStar[i]);
    }
}
MB_NodeReplayPetUnite* MB_NodeReplayPetUnite::create(uint16_t type,uint16_t rank,uint16_t level ,bool isDead){

    MB_NodeReplayPetUnite *ptr = new MB_NodeReplayPetUnite();
    if(ptr && ptr->init(type, rank, level, isDead)){
    
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_NodeReplayPetUnite::init(uint16_t type,uint16_t rank,uint16_t level ,bool isDead){
    
    MB_ResWindow::init();
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/formation_node_compare_unit.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    m_pNodeIsDead->setVisible(isDead);
    
    char str[5];
    sprintf(str,"+%d",rank%10);
    m_pQiangHua->setString(str);
    sprintf(str,"Lv.%d",level);
    m_pLevel->setString(str);
    setContentSize(m_pSize->getContentSize());
    return true;
}
bool MB_NodeReplayPetUnite::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCSprite *, m_pBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSize", CCNode *, m_pSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLevel", CCLabelBMFont *, m_pLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQiangHua", CCLabelBMFont *, m_pQiangHua);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeIsDead", CCNode *, m_pNodeIsDead);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    return false;
}
SEL_MenuHandler MB_NodeReplayPetUnite::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
SEL_CCControlHandler MB_NodeReplayPetUnite::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    return  NULL;
}
void MB_NodeReplayPetUnite::setPet(uint16_t type,int petRank)
{
    MB_PetTemplate *petTempelete  = MB_PetMgr::getInstance()->getPetTemplateByID(type);
    if (petTempelete==NULL)
    {
        return;
    }
    NSGameHelper::setSpriteFrame(m_pSprite_face, petTempelete->getPetFace(petRank));
    m_pBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTempelete->getPetKingdom())->getCString()));
    NSGameHelper::setStar(m_pStar, petTempelete->getPetStar());
}
