

#include "MB_NodePetResult.h"
#include "MB_LayerHome.h"
#include "MB_TeamData.h"
#include "MB_LayerPetEquipment.h"
MB_NodePetResult::MB_NodePetResult(uint64_t petId){
    roleName = NULL;
    m_pQiangHua = NULL;
    m_pBg = NULL;
    m_nPetId = petId;
    m_pSprite_face = NULL;
    m_pText_level = NULL;
    m_pNodeStar = NULL;
    m_pSize = NULL;
    m_pMoveNode = NULL;
    m_pInteam = NULL;
    m_pDetailBtn = NULL;
    m_pToVis = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    
}
MB_NodePetResult::~MB_NodePetResult(){
    
    CC_SAFE_RELEASE(m_pToVis);
    CC_SAFE_RELEASE(roleName);
    CC_SAFE_RELEASE(m_pQiangHua);
    CC_SAFE_RELEASE(m_pBg);
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pText_level);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    CC_SAFE_RELEASE_NULL(m_pSize);
    CC_SAFE_RELEASE_NULL(m_pMoveNode);
    CC_SAFE_RELEASE_NULL(m_pInteam);
    CC_SAFE_RELEASE_NULL(m_pDetailBtn);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
}

MB_NodePetResult * MB_NodePetResult::create(uint64_t petId){
    
    MB_NodePetResult *node = new MB_NodePetResult(petId);
    
    if( node && node->init() ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool  MB_NodePetResult::init(){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_iconResult.ccbi", this);
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

void MB_NodePetResult::setSelectedState(bool isSelected)
{
    m_pDetailBtn->setTouchEnabled(isSelected);
}
bool MB_NodePetResult::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleName", CCLabelTTF *, roleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQiangHua", CCLabelBMFont *, m_pQiangHua);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCSprite *, m_pBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleLevel", CCLabelBMFont *, m_pText_level);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode *, m_pNodeStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSize", CCNode *, m_pSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoveNode", CCNode *, m_pMoveNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInteam", CCNode *, m_pInteam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDetailBtn", CCControlButton *, m_pDetailBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVis", CCNode *, m_pToVis);
    
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    return  false;
}
SEL_MenuHandler MB_NodePetResult::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
SEL_CCControlHandler MB_NodePetResult::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickDetail",MB_NodePetResult::onClickDetail);
    return NULL;
}

void MB_NodePetResult::setPetID(uint64_t petId)
{
    if (m_nPetId==-1) {
        m_nPetId = petId;
    }
    if(petId == -1)
    {
        m_nPetId = petId;
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
    char databuf[30];
    sprintf(databuf, "Lv.%d" ,petData->getPetLevel());
    m_pText_level->setString(databuf);
    sprintf(databuf, "%s" ,petTempelete->getPetName());
    roleName->setString(databuf);
    NSGameHelper::setSpriteFrame(m_pSprite_face, petTempelete->getPetFace(NSGameHelper::getShapeTypeByRank(petData->getPetQuallity())));
    m_pBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTempelete->getPetKingdom())->getCString()));
    NSGameHelper::setStar(m_pStar, petTempelete->getPetStar());

    int tempInt = petData->getPetQuallity()%10;
    if (tempInt>0) {
        m_pQiangHua->setVisible(true);
        sprintf(databuf,"+%d",petData->getPetQuallity()%10);
        m_pQiangHua->setString(databuf);
    }else
    {
        m_pQiangHua->setVisible(false);
    }
}

void MB_NodePetResult::setShangZhen(bool b)
{
    m_pInteam->setVisible(b);
}

void MB_NodePetResult::setAllAnchpoint(CCNode* node,CCPoint ap)
{
    CCObject* pObj = NULL;
    CCArray* pChildren = node->getChildren();
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        pChild->setAnchorPoint(ap);
        setAllAnchpoint(pChild,ap);
    }
}

void MB_NodePetResult::onClickDetail(CCObject * pSender)
{
    MB_ResWindow* layerDetail = MB_LayerPetDetail::createWithPetID(m_nPetId);
    if (global_layerPetEquipment!=NULL) {
        global_layerPetEquipment->addChild(layerDetail,999);
        global_layerPetEquipment->setMyTouchEnable(false);
    }else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail,Z_ORDER_OUTSHOW);
    }
}

