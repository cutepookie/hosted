
#include "MB_NodeTanChuangUnit.h"

MB_NodeTanChuangUnit::MB_NodeTanChuangUnit(){
    m_pDetailBtn = NULL;
    m_pSprite_face = NULL;
    m_pBg = NULL;
    m_pLevel = NULL;
    m_pQiangHua = NULL;
    m_pName = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
}
MB_NodeTanChuangUnit::~MB_NodeTanChuangUnit(){
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pBg);
    CC_SAFE_RELEASE(m_pLevel);
    CC_SAFE_RELEASE(m_pQiangHua);
    CC_SAFE_RELEASE(m_pDetailBtn);
    CC_SAFE_RELEASE(m_pName);
    
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE(m_pStar[i]);
    }
}
MB_NodeTanChuangUnit* MB_NodeTanChuangUnit::create(uint16_t type,uint16_t rank,uint16_t level,bool isItem ){

    MB_NodeTanChuangUnit *ptr = new MB_NodeTanChuangUnit();
    if(ptr && ptr->init(type, rank, level, isItem)){
    
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_NodeTanChuangUnit::init(uint16_t type,uint16_t rank,uint16_t level,bool isItem){
    
    MB_ResWindow::init();
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    m_bIsItem = isItem;
    if (isItem) {
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/tanchuang_node_item.ccbi", this);
        this->addChild(pNode);
        CC_SAFE_RELEASE_NULL(pCCBReader);
        MB_ItemTemplate* pItem = MB_ItemMgr::getInstance()->getItemTemplateByID(type);
        char str[5];
        sprintf(str,"+%d",rank%10);
        m_pQiangHua->setString(str);
        sprintf(str,"Lv.%d",level);
        m_pLevel->setString(str);
        sprintf(str,"%s",pItem->getItemName());
        m_pName->setString(str);
        
        CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(pItem->getItemIcon());
        if(textrue !=NULL)
        {
            CCSpriteFrame * frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
            m_pSprite_face->setDisplayFrame(frame);
        }
        NSGameHelper::setStar(m_pStar, pItem->getItemStar());
    }else
    {
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/tanchuang_node_card.ccbi", this);
        this->addChild(pNode);
        CC_SAFE_RELEASE_NULL(pCCBReader);
        MB_PetTemplate *petTempelete = MB_PetMgr::getInstance()->getPetTemplateByID(type);
        char str[5];
        sprintf(str,"+%d",rank%10);
        m_pQiangHua->setString(str);
        sprintf(str,"Lv.%d",level);
        m_pLevel->setString(str);
        sprintf(str,"%s",petTempelete->getPetName());
        m_pName->setString(str);
        NSGameHelper::setSpriteFrame(m_pSprite_face, petTempelete->getPetFace(rank));
        m_pBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTempelete->getPetKingdom())->getCString()));
        NSGameHelper::setStar(m_pStar, petTempelete->getPetStar());
    }
    
    m_pDetailBtn->setSwallowsTouches(false);
    return true;
}
bool MB_NodeTanChuangUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCSprite *, m_pBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLevel", CCLabelBMFont *, m_pLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pName", CCLabelTTF *, m_pName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQiangHua", CCLabelBMFont *, m_pQiangHua);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDetailBtn", CCControlButton *, m_pDetailBtn);
    
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    return false;
}
SEL_MenuHandler MB_NodeTanChuangUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
SEL_CCControlHandler MB_NodeTanChuangUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickDetail", MB_NodeTanChuangUnit::onClickDetail);
    return  NULL;
}
void MB_NodeTanChuangUnit::onClickDetail(CCObject* pSender)
{
    
}
