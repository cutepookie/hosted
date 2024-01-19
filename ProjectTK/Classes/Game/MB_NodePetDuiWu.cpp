

#include "MB_NodePetDuiWu.h"
#include "MB_LayerHome.h"
#include "MB_TeamData.h"
#include "MB_LayerPetEquipment.h"
MB_NodePetDuiWu::MB_NodePetDuiWu(uint64_t petId,bool isH){
    m_nPetId = petId;
    m_bIsH = isH;
    m_pSprite_face = NULL;
    m_pText_level = NULL;
    m_pNodeStar = NULL;
    m_pSize = NULL;
    m_pBgHighlight = NULL;
    m_pToVis = NULL;
    m_pMoveNode = NULL;
    m_pInteam = NULL;
    m_pDetailBtn = NULL;
    m_pInguard = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    
}
MB_NodePetDuiWu::~MB_NodePetDuiWu(){
    CC_SAFE_RELEASE(m_pInguard);
    CC_SAFE_RELEASE(m_pSprite_face);
    CC_SAFE_RELEASE(m_pText_level);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    CC_SAFE_RELEASE_NULL(m_pSize);
    CC_SAFE_RELEASE_NULL(m_pBgHighlight);
    CC_SAFE_RELEASE_NULL(m_pToVis);
    CC_SAFE_RELEASE_NULL(m_pMoveNode);
    CC_SAFE_RELEASE_NULL(m_pInteam);
    CC_SAFE_RELEASE_NULL(m_pDetailBtn);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
}

MB_NodePetDuiWu * MB_NodePetDuiWu::create(uint64_t petId,bool isH,bool isSetBtn){
    
    MB_NodePetDuiWu *node = new MB_NodePetDuiWu(petId,isH);
    
    if( node && node->init(isSetBtn) ){
        
        node->autorelease();
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool  MB_NodePetDuiWu::init(bool isSetBtn){
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node;
    if (m_bIsH) {
        node = pCCBReader->readNodeGraphFromFile("res/card_node_iconDuiWu.ccbi", this);
    }else
    {
        node = pCCBReader->readNodeGraphFromFile("res/card_node_iconDuiWu2.ccbi", this);
    }
    this->addChild(node);
    pCCBReader->release();
    
    if (isSetBtn) {
        m_pDetailBtn->setTouchPriority(-99);
        m_pDetailBtn->setSwallowsTouches(false);
    }
    
    m_nWidth = m_pSize->getContentSize().width;
    m_nHeight= m_pSize->getContentSize().height;
    if (m_nPetId==-1) {
        m_pToVis->setVisible(false);
        return true;
    }
    
    setPetID(m_nPetId);
    
    if (!m_bIsH) {
        setAllAnchpoint(this,ccp(.5f,0.1f));
    }
    
    return true;
}

void MB_NodePetDuiWu::setSelectedState(bool isSelected)
{
    m_pBgHighlight->setVisible(isSelected);
    m_pDetailBtn->setTouchEnabled(isSelected);
}
bool MB_NodePetDuiWu::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInguard", CCNode *, m_pInguard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_face", CCSprite *, m_pSprite_face);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleLevel", CCLabelBMFont *, m_pText_level);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode *, m_pNodeStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSize", CCNode *, m_pSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBgHighlight", CCNode *, m_pBgHighlight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToVis", CCNode *, m_pToVis);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoveNode", CCNode *, m_pMoveNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pInteam", CCNode *, m_pInteam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDetailBtn", CCControlButton *, m_pDetailBtn);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        char starstr[] = "star0";
        starstr[4] = i + '0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    return  false;
}
SEL_MenuHandler MB_NodePetDuiWu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
SEL_CCControlHandler MB_NodePetDuiWu::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickDetail",MB_NodePetDuiWu::onClickDetail);
    return NULL;
}

void MB_NodePetDuiWu::setPetID(uint64_t petId)
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
    char databuf[10];
    sprintf(databuf, "%d" ,petData->getPetLevel());
    m_pText_level->setString(databuf);
    NSGameHelper::setMonsterIconDetailWithStarByTid(petTempelete->getPetTypeID(),petData->getPetQuallity(),NULL,NULL,NULL,m_pNodeStar);
    
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("army_card/army_card_%d.png",petTempelete->getPetTypeID()+NSGameHelper::getShapeTypeByRank(petData->getPetQuallity()))->getCString());
    if(textrue !=NULL){
        CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pSprite_face->setDisplayFrame(frame);
    }
    
    NSGameHelper::setStar(m_pStar, petData->getTemplateStar());
}

void MB_NodePetDuiWu::setShangZhen(bool b)
{
    m_pInteam->setVisible(b);
}

void MB_NodePetDuiWu::setShouHu(bool b)
{
    m_pInguard->setVisible(b);
}

void MB_NodePetDuiWu::setAllAnchpoint(CCNode* node,CCPoint ap)
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
bool checkInTeamNPDW(uint64_t petID){
    
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        if (teamV[i] != -1 && teamV[i] == petID) {
            return true;
        }
    }
    return false;
}
void MB_NodePetDuiWu::onClickDetail(CCObject * pSender)
{
    if (global_layerPetEquipment!=NULL&&checkInTeamNPDW(m_nPetId)) {
        bool isSendZhenxing = false;
        for (int i =0; i<MEMBER_NUM; i++) {
            if ((MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet==NULL&&teamV[i]!=-1) || (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL&&teamV[i] != MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID())) {
                isSendZhenxing = true;
                break;
            }
        }
        if (isSendZhenxing) {
            global_layerPetEquipment->toShowDetailPetUID = m_nPetId;
            global_layerPetEquipment->sendZhenXing();
            return;
        }
    }
    
    MB_ResWindow* layerDetail = MB_LayerPetDetail::createWithPetID(m_nPetId);
    if (global_layerPetEquipment!=NULL) {
        global_layerPetEquipment->setMyTouchEnable(false);
        global_layerPetEquipment->pushWindow(layerDetail,true);
    }else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail,Z_ORDER_OUTSHOW);
    }
}

