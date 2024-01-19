

#include "MB_NodePetUnit.h"
#include "MB_LayerPetEnhance.h"
#include "MB_LayerGuard.h"
#include "MB_GuardInterface.h"
#include "MB_LayerPetUpdate.h"
MB_NodePetUnit::MB_NodePetUnit():m_pNode_icon(NULL),m_pSprite_back(NULL),m_pLabel_name(NULL),m_pText_hp(NULL),m_pSprite_country(NULL),m_pSprite_inbattle(NULL){
    
    for (int i=0 ; i<MAX_GER_STAR ; i++) {
        
        m_pStar[i] = NULL;
    }
    
    m_pOnSoldSelect = NULL;
    m_pNodeSize = NULL;
    m_pNodeNomal = NULL;
    m_pNodeChange = NULL;
    m_pNodeSale = NULL;
 //   m_pMoneyLabel = NULL;
    m_pNodeChoose = NULL;
    m_pNodeChooseNone = NULL;
    m_pOnSoldSelect2 = NULL;
    m_pNodeGuard = NULL;
    m_pTTFGuard = NULL;
    m_bShowTutoral = false;
}

MB_NodePetUnit::~MB_NodePetUnit(){
    
    for (int i=0 ; i<MAX_GER_STAR ; i++) {
        
        CC_SAFE_RELEASE(m_pStar[i]);
    }
    CC_SAFE_RELEASE(m_pNode_icon);
    CC_SAFE_RELEASE(m_pSprite_back);
    CC_SAFE_RELEASE(m_pLabel_name);
    CC_SAFE_RELEASE(m_pText_hp);
    CC_SAFE_RELEASE(m_pSprite_country);
    CC_SAFE_RELEASE(m_pSprite_inbattle);
    CC_SAFE_RELEASE(m_pOnSoldSelect);
    CC_SAFE_RELEASE(m_pNodeSize);
    CC_SAFE_RELEASE(m_pNodeNomal);
    CC_SAFE_RELEASE(m_pNodeChange);
    CC_SAFE_RELEASE(m_pNodeSale);
   // CC_SAFE_RELEASE(m_pMoneyLabel);
    CC_SAFE_RELEASE(m_pNodeChooseNone);
    CC_SAFE_RELEASE(m_pNodeChoose);
    CC_SAFE_RELEASE(m_pOnSoldSelect2);
    CC_SAFE_RELEASE(m_pNodeGuard);
    CC_SAFE_RELEASE(m_pTTFGuard);
    
}

bool MB_NodePetUnit::init(uint64_t petId,bool isSelected){
    
    m_nPetId = petId;
    m_bIsSelect = isSelected;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_node_unit.ccbi", this);
    this->addChild(node);
    CC_SAFE_RELEASE(pCCBReader);
    if(petId == -1){
        
        return true;
    }
    
    m_pHeadCanClick = true;
    m_pNodeer = MB_NodePet::create(m_nPetId);
//    m_pNodeer->setPosition(m_pNode_icon->getPosition());
//    m_pNodeer->setScale(0.8f);
    m_pNodeer->setMenuTouch(true);
//    m_pNode_icon->getParent()->addChild(m_pNodeer,m_pNode_icon->getZOrder());
    m_pNode_icon->addChild(m_pNodeer);
    m_pSprite_inbattle->setVisible(isSelected);
    MB_PetData *t_gData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    MB_PetTemplate *t_gTData = t_gData->getTemplete();
    
    char realname[100];
    m_pLabel_name->setString(MB_PetMgr::getInstance()->getPetRealName(realname,m_nPetId));
//    CCNodeRGBA pDest;
//    NSGameHelper::setQualityColor(&pDest,t_gTData->getPetStar());
//    m_pLabel_name->setColor(pDest.getColor());
    char databuf[10];
    sprintf(databuf, "%d",t_gData->getPetHpMax());
    m_pText_hp->setString(databuf);
    
    for ( int i= 0; i<MAX_GER_STAR; i++) {
        
        if( i >= t_gTData->getPetStar()){
            
            m_pStar[i]->setVisible(false);
        }
        else
        {
            m_pStar[i]->setVisible(true);
        }
    }
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pic_1.plist");
//    char country[]="ico_camp_0.png";
//    country[9]='0'+ t_gTData->getPetKingdom()-1;
//    
//    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(country);
//    if ( frame != NULL) {
//        
//        m_pSprite_country->setDisplayFrame(frame);
//        
//    }else{
//        
//        MB_LOG("%s",country);
//    }
    
    m_pOnSoldSelect->setVisible(false);
    m_pNodeSale->setVisible(false);
    m_pNodeChange->setVisible(false);
    m_pNodeNomal->setVisible(false);
    m_pNodeChoose->setVisible(false);
    m_pNodeChooseNone->setVisible(false);
    
    m_pNodeer->setMenuTouch(false);
    m_pOnSoldSelect->setVisible(false);
    m_pOnSoldSelect2->setVisible(false);
    return true;
}

void MB_NodePetUnit::onChangeClick(){
    
    TutorialTriggerComplete
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    ((MB_NodePetList *)node)->sendpet_standup(m_nPetId);
}
void MB_NodePetUnit::onSoldClick(){
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_LayerPetSell *>(node) == NULL; node = node->getParent()) {
        
    }
    if ( m_pOnSoldSelect->isVisible() ){
        
        ((MB_LayerPetSell *)node)->removeFromSell(m_nPetId);
        
    }else {
        
        ((MB_LayerPetSell *)node)->addToSell(m_nPetId);
    }
    changeSel();
}
void MB_NodePetUnit::onEnhanceClick(){
    
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    MB_LayerPetEnhance* layer = MB_LayerPetEnhance::create(kPetEnhanceEntrDetail, m_nPetId);
    ((MB_ResWindow *)(node))->pushWindow(layer);
    
}
void MB_NodePetUnit::onUpdateClick(){
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    MB_LayerPetUpdate* layer = MB_LayerPetUpdate::create(m_nPetId);
    ((MB_ResWindow *)(node))->pushWindow(layer);
}
void MB_NodePetUnit::onChooseNoneClick(){
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    
    if(m_pUnitType == kPetTeamTypeUpdate ){
        
        ((MB_LayerPetUpdate *) ((MB_ResWindow *)(node))->getLogicParent())->readLoadPet(m_nPetId);
        
    }else  if(m_pUnitType == kPetTeamTypeEnhance ){
        
        ((MB_LayerPetEnhance*) ((MB_ResWindow *)(node))->getLogicParent())->resetPetID(m_nPetId);
        
    }else  if(m_pUnitType == kPetTeamTypeEnhanceCost ){
        
        ((MB_LayerPetEnhance*) ((MB_ResWindow *)(node))->getLogicParent())->resetCostPetID(m_nPetId);
        
    }
    else  if(m_pUnitType == kPetGuardTypeSelect ){
        
        ((MB_LayerGuard*) ((MB_ResWindow *)(node))->getLogicParent())->setPetGuard(m_nPetId);
        
    }
    this->runAction(CCCallFunc::create(this, callfunc_selector(MB_NodePetUnit::onNodeCallBack)));
}
void MB_NodePetUnit::onNodeCallBack(){
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    ((MB_ResWindow *)node)->popWindow();
}
void MB_NodePetUnit::onChooseClick(){
    
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodeUpdatePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    MB_PetData *t_gData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
    if ( m_pOnSoldSelect2->isVisible() ){
        
        
        ((MB_NodeUpdatePetList *)node)->getSoldList()->removeObject(t_gData);
        
        
    }else {
        
        if (((MB_NodeUpdatePetList *)node)->getSoldList()->count() >=8 ) {
            
            MB_Message::sharedMB_Message()->showMessage("只能选择8个材料");
            return;
        }
        
        ((MB_NodeUpdatePetList *)node)->getSoldList()->addObject(t_gData);
    }
    changeSel();
}
void MB_NodePetUnit::onPetClick(){
    
    if(  m_pHeadCanClick == false){
        
        return ;
    }

    MB_ResWindow * layer = MB_LayerPetDetail::createWithPetID(m_nPetId);
    if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
    
}
cocos2d::extension::SEL_CCControlHandler MB_NodePetUnit::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
    
}
cocos2d::SEL_MenuHandler MB_NodePetUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetClick", MB_NodePetUnit::onPetClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSoldClick", MB_NodePetUnit::onSoldClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChangeClick", MB_NodePetUnit::onChangeClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEnhanceClick", MB_NodePetUnit::onEnhanceClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUpdateClick", MB_NodePetUnit::onUpdateClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseClick", MB_NodePetUnit::onChooseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseNoneClick", MB_NodePetUnit::onChooseNoneClick);
    
    return NULL;
}
bool MB_NodePetUnit::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    //上阵的不会有按钮
    if ( !m_bIsSelect && MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
        return true;
    }
    
    if(m_bShowTutoral)
    {
        if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
            return true;
        }
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGuard",CCNode*,m_pNodeGuard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFGuard",CCLabelTTF*, m_pTTFGuard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_back",   CCScale9Sprite *, m_pSprite_back);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "level_name", CCLabelTTF *, m_pLabel_name);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_icon", CCNode *, m_pNode_icon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_hp", CCLabelTTF *,m_pText_hp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_country", CCSprite *,m_pSprite_country);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_inbattle", CCSprite *,m_pSprite_inbattle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "onSoldSelect", CCSprite *,   m_pOnSoldSelect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "onSoldSelect2", CCSprite *,   m_pOnSoldSelect2)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNomal", CCNode *, m_pNodeNomal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSale", CCNode *, m_pNodeSale);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChange", CCNode *, m_pNodeChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChoose", CCNode *, m_pNodeChoose );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChooseNone", CCNode *, m_pNodeChooseNone);
//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoneyLabel", CCLabelTTF *,m_pMoneyLabel);
    for (int i=0 ; i<MAX_GER_STAR; i++) {
        
        char starstr[]="star0";
        
        starstr[4] = i+'1';
        
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCSprite *, m_pStar[i]);
    }
    
    return false;
    
}
CCSize MB_NodePetUnit::getCellSize(){
    
    return  m_pNodeSize->getContentSize();
}
int64_t MB_NodePetUnit::getData(){
    
    return m_nPetId;
}
bool MB_NodePetUnit::isCanClick(){
    
    return  m_pSprite_inbattle->isVisible() == false;
}
MB_NodePetUnit * MB_NodePetUnit::create( uint64_t data,bool isSelected,bool showTurtorial){
    
    MB_NodePetUnit * node =new MB_NodePetUnit();
    
    if( node && node->init(data,isSelected) ){
        
        node->autorelease();
        node->m_bShowTutoral = showTurtorial;
        
        return  node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}
bool MB_NodePetUnit::changeSel(){
    
    
    if(m_pUnitType == kPetTeamTypeCost){
        
        if ( m_pOnSoldSelect->isVisible() ){
            
            m_pOnSoldSelect->setVisible(false);            
            return false;
            
        }else {
            
            m_pOnSoldSelect->setVisible(true);            
            return true;
        }        
        
    }else {
        
        
        if ( m_pOnSoldSelect2->isVisible() ){
            
            m_pOnSoldSelect2->setVisible(false);
            return false;
            
        }else {
            
            m_pOnSoldSelect2->setVisible(true);
            return true;
        }        
    }
}
bool MB_NodePetUnit::setIsHeadCanClick(bool isHeadCanClick){
    
    m_pHeadCanClick = isHeadCanClick;
    
    return true;
    
}

void MB_NodePetUnit::setUnitType(int UnitType){
    
    m_pUnitType = UnitType;
//    if (m_pUnitType == kPetTeamTypeUpdate
//        
//        || m_pUnitType == kPetTeamTypeEnhance
//        || m_pUnitType == kPetTeamTypeEnhanceCost
//        )
//    {
//        setIsHeadCanClick(false);
//    }
    if(m_pUnitType == kPetTeamTypeMain){
        
        m_pNodeNomal->setVisible(true);
        
    }else if(m_pUnitType == kPetTeamTypeMove || m_pUnitType == kPetTeamTypeEquipment){
        m_pNodeChange->setVisible(!m_bIsSelect);
        MB_PetTemplate* petTempalte = MB_PetMgr::getInstance()->getPetTemplateByUID(m_nPetId);
        if (petTempalte)
        {
            if(NSGameHelper::checkIsGuardPetType(petTempalte->getPetTypeID()))
            {
                m_pNodeChange->setVisible(false);
            }
        }
    }else if(m_pUnitType == kPetTeamTypeCost){
        
        m_pNodeSale->setVisible(true);
        //char databuf[50];
      // MB_PetData *t_gData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetId);
        //MB_PetTemplate *t_gTData = MB_PetMgr::getInstance()->getPetTemplateByID(t_gData->getPetTypeID());
       // sprintf(databuf, "%d",t_gTData->getPetCost());
       // m_pMoneyLabel->setString(databuf);
        
    }else if(m_pUnitType == kPetTeamTypeUpdate || m_pUnitType == kPetTeamTypeEnhance || m_pUnitType == kPetTeamTypeEnhanceCost){
        
        m_pNodeChooseNone->setVisible(true);
        
    }else if(m_pUnitType == kPetTeamTypeUpdateCost){
        
        m_pNodeChoose->setVisible(true);
    }
    else if(m_pUnitType == kPetGuardTypeSelect)//选择守护
    {
        m_pNodeChooseNone->setVisible(true);
        MB_PetTemplate* petTempalte = MB_PetMgr::getInstance()->getPetTemplateByUID(m_nPetId);
        if (petTempalte)
        {
            if(NSGameHelper::checkIsGuardPetType(petTempalte->getPetTypeID()))
            {
                m_pNodeChooseNone->setVisible(false); //守护中同类型的不显示按钮
            }
        }
    }
    
    
    //经验卡牌  不显示升级进化按钮
    if(NSGameHelper::checkIsExperienceCard(m_nPetId))
    {
        m_pNodeNomal->setVisible(false);
    }
    m_pNodeGuard->setVisible(false);
    
    //守护
    if(NSGameHelper::checkIsGuardPet(m_nPetId))
    {
        m_pNodeChange->setVisible(false);
        if (m_pUnitType == kPetTeamTypeEnhanceCost)//精灵进化材料不可选择守护
        {
            m_pNodeChooseNone->setVisible(false);
        }
        if (m_pUnitType == kPetGuardTypeSelect)//选择守护 不可替换已上阵的守护
        {
            m_pNodeChooseNone->setVisible(false);
        }
        
        MB_PetGuardData* data = MB_GuardInterface::getInstance()->getPetGuardDataByUid(m_nPetId);
        if(data != NULL)
        {
            m_pNodeGuard->setVisible(true);
            char str[128];
            TeamDataStruct* teamData = MB_TeamData::getInstance()->getTeamMemberByIndex(data->getPetPos()-1);
            if (teamData != NULL && teamData->m_pPet != NULL)
            {
                MB_PetTemplate* petTemplate =  MB_PetMgr::getInstance()->getPetTemplateByUID(teamData->m_pPet->getPetID());
                if (petTemplate != NULL)
                {
                    char str[128];
                    sprintf(str,"%s的守护",petTemplate->getPetName(NSGameHelper::getShapeTypeByRank(teamData->m_pPet->getPetQuallity())));
                    m_pTTFGuard->setString(str);
                }
                
            }
            
        }
    }

        
}
