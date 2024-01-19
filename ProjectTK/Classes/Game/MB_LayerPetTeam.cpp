

#include "MB_LayerPetTeam.h"
#include "MB_NodePetAid.h"
#include "MB_LayerPetCommand.h"
#include "MB_LayerPetEquipment.h"
#include "MB_LayerPetEnhance.h"
#include "MB_LayerPetUpdate.h"
MB_LayerPetTeam::MB_LayerPetTeam(){

    m_pText_attackCount = NULL;
    m_pTrigpetMenu = NULL;
    m_pPetAnimMgr = NULL;
    m_pMenu = NULL;
    m_nTagItem = -1;
    m_nSelItem = -1;
    
    m_pAddAttck = NULL;
    m_pAddHp = NULL;
    m_bShowRoleInfoPanel = false;

    //m_pLibox = NULL;

    for (int i=0 ; i< CARD_IN_GAME ; i++) {
        
        m_pNode[i] = NULL;
        m_pShowNode[i] = NULL;        
//        m_pText_name[i] = NULL;
        m_pItem[i] = NULL;
//        m_pItemLevel[i] = NULL;
        m_pNodeAid[i] = NULL;
        m_pLock[i] = NULL;
//        m_pLevelBgNode[i] = NULL;
//        m_pNodeShardow[i] = NULL;
    }
    
    SOCKET_MSG_REGIST(SC_GER_MOVE_POS, MB_LayerPetTeam);
    SOCKET_MSG_REGIST(SC_GER_REFRESH_POWER, MB_LayerPetTeam);
    SOCKET_MSG_REGIST(SC_GER_UPDATE, MB_LayerPetTeam);
    //SOCKET_MSG_REGIST(SC_GER_LIEU_MOVE_POS, MB_LayerPetTeam);
}

MB_LayerPetTeam::~MB_LayerPetTeam(){
    
    SOCKET_MSG_UNREGIST(SC_GER_MOVE_POS);
    SOCKET_MSG_UNREGIST(SC_GER_REFRESH_POWER);
    SOCKET_MSG_UNREGIST(SC_GER_UPDATE);
    //SOCKET_MSG_UNREGIST(SC_GER_LIEU_MOVE_POS);
    CC_SAFE_RELEASE(m_pText_attackCount);
    CC_SAFE_RELEASE(m_pPetAnimMgr);
    
    CC_SAFE_RELEASE(m_pAddAttck);
    CC_SAFE_RELEASE(m_pAddHp);

    //CC_SAFE_RELEASE(m_pLibox);
    for (int i=0 ; i< 6 ; i++) {
        
        CC_SAFE_RELEASE(m_pNode[i]);
//        CC_SAFE_RELEASE(m_pText_name[i]);
        CC_SAFE_RELEASE(m_pItem[i]);
//        CC_SAFE_RELEASE(m_pItemLevel[i]);
        CC_SAFE_RELEASE(m_pNodeAid[i]);
        CC_SAFE_RELEASE(m_pLock[i]);
//        CC_SAFE_RELEASE(m_pLevelBgNode[i]);
//        CC_SAFE_RELEASE_NULL(m_pNodeShardow[i]);
    }
    CC_SAFE_RELEASE(m_pMenu);
    
}

MB_LayerPetTeam * MB_LayerPetTeam::create(int type){
    
    MB_LayerPetTeam *prt = new MB_LayerPetTeam();
    if( prt && prt->init(type)){
        
        prt->autorelease();
        return prt;
        
    }
    delete prt;
    return NULL;
}

bool MB_LayerPetTeam::init(int type){
    
    if( CCLayer::init() == false ){
        
        return  false;
    }
    
    m_nType = type;
    
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *node = pCCBReader->readNodeGraphFromFile("res/formation_layer_setting.ccbi", this);
    this->addChild(node);
    pCCBReader->getAnimationManager()->runAnimationsForSequenceNamed("open");
    pCCBReader->release();
    isShowLock = true;
    

    onResetWnd();
    int level  = MB_RoleData::getInstance()->getLevel();
    char databuf[40];
    if(level >= kTeamLimit30_6 ){
        
        sprintf(databuf, " ");
        
    }else if(level >= kTeamLimit20_5){
        
        sprintf(databuf, "25级解锁");
        
        
    } else if(level >= kTeamLimit10_4 ){
        
        sprintf(databuf,"20级解锁");
        
    }else {
        
        sprintf(databuf,"10级解锁");
    }
    for (int i = 0; i < CARD_IN_GAME; i++) {
        
        m_pLock[i]->setString(databuf);
    }
    return true;
}
void MB_LayerPetTeam::onRestShow(){

 
    
}
void MB_LayerPetTeam::onResetWnd()
{
    MB_ResWindow::onResetWnd();
    //刷新数据
    m_nCount = 0;
    m_nAttackCount =0 ;
    
    
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pMenu->getChildren(), pObject)
    {
        CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
        
        if (pChild  && pChild->isEnabled())
        {
            pChild->setPositionX(pChild->getPositionX()+(130-46)/2);
            pChild->setContentSize(CCSize(130,130));
        }
    }
    
//    for(int i = 0 ;i < CARD_IN_GAME && m_nType == 1; i++){
//        
//        m_pText_name[i]->setString("");
//        m_pItemLevel[i]->setString("");
//    }
    
    for (int i=0 ; i< CARD_IN_GAME; i++) {
        
        m_pLock[i]->setVisible(true);
        MB_PetData * data =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet;
        
        if(  data  !=  NULL){
            
            CCPoint pos = m_pNode[i]->getPosition();
            CCNode *per = m_pNode[i]->getParent();
           
            m_nAttackCount = m_nAttackCount+((MB_PetData *)data)->getPetFightPower();
            m_nCount++;
            if (m_pShowNode[i] != NULL) {
                m_pShowNode[i]->removeFromParent();
                m_pShowNode[i] = NULL;
            }
            m_pShowNode[i] = MB_NodePetTeam::create(((MB_PetData *)data)->getPetID());
            m_pShowNode[i]->m_pSpriteBG2->setVisible(false);
            m_pShowNode[i]->setPosition(pos);
//            m_pShowNode[i]->setScale(0.5);
            m_pShowNode[i]->setAnchorPoint(ccp(0,0));
            per->addChild(m_pShowNode[i],0);
//            if (m_nType == 1) {
//                
//                char realname[100];
//                m_pText_name[i]->setString(MB_PetMgr::getInstance()->getPetRealNameNoSpace(realname,((MB_PetData *)data)->getPetID()));
//                sprintf(realname, "%d",data->getPetLevel());
//                
//                CCNodeRGBA Dest;
//                m_pItemLevel[i]->setString(realname);
//                
//            }
            m_pLock[i]->setVisible(false);
            m_pItem[i]->setVisible(false);
//            m_pLevelBgNode[i]->setVisible(true);
//            
//            m_pNodeShardow[i]->setVisible(false);
        }
        else
        {
             m_pItem[i]->setVisible(true);
//            m_pLevelBgNode[i]->setVisible(false);
//            m_pNodeShardow[i]->setVisible(true);
        }
    }
    
    char databuf[64];
    m_nAttackCount =  MB_TeamData::getInstance()->getFightPower();
    sprintf(databuf, "%llu",m_nAttackCount);
    m_pText_attackCount->setString(databuf);
    this->setTouchEnabled(true);
    m_pMenu->setTouchEnabled(false);
//    m_nIschange = false ;
    
    if(m_nCount >= MB_TeamData::getInstance()->getLimitPet()){
        
        isShowLock = true;
        for (int i =0 ; i < CARD_IN_GAME ; i++) {
            
            m_pItem[i]->setVisible(false);
        }
    }
    if(m_nCount < MB_TeamData::getInstance()->getLimitPet()){
    
        isShowLock = false;
        for (int i =0 ; i < CARD_IN_GAME ; i++) {
        
            m_pLock[i]->setVisible(false);
        }

    }
    

    onRestShow();
}


cocos2d::SEL_MenuHandler MB_LayerPetTeam::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet1Change",MB_LayerPetTeam::onPet1ChangeClick );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet2Change",MB_LayerPetTeam::onPet2ChangeClick );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet3Change",MB_LayerPetTeam::onPet3ChangeClick );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet4Change",MB_LayerPetTeam::onPet4ChangeClick );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet5Change",MB_LayerPetTeam::onPet5ChangeClick );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pet6Change",MB_LayerPetTeam::onPet6ChangeClick );
    //trigpet menu
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDetailClicked",MB_LayerPetTeam::onDetailClicked );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEquipClicked2",MB_LayerPetTeam::onEquipClicked2 );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLevelClicked",MB_LayerPetTeam::onLevelClicked );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onQualityClicked",MB_LayerPetTeam::onQualityClicked );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetClicked",MB_LayerPetTeam::onPetClicked );
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetClicked",MB_LayerPetTeam::onPetClicked );
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick",MB_LayerPetTeam::onCloseClicked );
    
    return NULL;
}
void MB_LayerPetTeam::onCloseClicked(CCObject *){

    MB_TARGET_PARENT(MB_LayerPetCommand, ptr);
    if(ptr){
    
        ptr->enterPetEquip();
    }
}
cocos2d::extension::SEL_CCControlHandler MB_LayerPetTeam::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool MB_LayerPetTeam::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
        return true;
    }
    

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "text_attackCount", CCLabelBMFont *,m_pText_attackCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menu_SelectPet", CCMenu *, m_pMenu);
    
    for(int i=0 ; i< CARD_IN_GAME; i++){
        
        char item[] = "ger1";
        item[3] = '1'+i;
        
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, item, CCNode *, m_pNode[i]);        
        
        char itemstr[]="m_pItem1";
        itemstr[7]= '1' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  itemstr, CCMenuItemImage *, m_pItem[i]);
        
        char petNode[] = "m_pLock0";
        petNode[7] = '0' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,    petNode, CCLabelTTF *, m_pLock[i]);
        
        char aidNode[] = "m_pNodeAid0";
        aidNode[10] = '0' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,    aidNode, CCNode *, m_pNodeAid[i]);
        
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAddAttck", CCLabelTTF *,m_pAddAttck);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pAddHp", CCLabelTTF *, m_pAddHp);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLibox", CCNode *, m_pLibox);
    return true;
}

void MB_LayerPetTeam::check_posAndChangeCand(int index){
    
    if(m_nCount >= MB_TeamData::getInstance()->getLimitPet()
       && MB_TeamData::getInstance()->getTeamMemberByIndex(index)->m_pPet == NULL )
    {
        return;
    }
    else if (MB_TeamData::getInstance()->getTeamMemberByIndex(index)->m_pPet == NULL)
    {
       onEnterNodePetList(m_nType, index, kListTypeStand);
    }
    else
    {
        MB_TeamData::getInstance()->setNowPet(MB_TeamData::getInstance()->getTeamMemberByIndex(index)->m_pPet->getPetID());
        this->onEquipClicked2(NULL);
    }
    
    
}
void MB_LayerPetTeam::onPet1ChangeClick(CCObject *){

    this->check_posAndChangeCand(0);
}

void MB_LayerPetTeam::onPet2ChangeClick(CCObject *){
    
     this->check_posAndChangeCand(1);
    
}

void MB_LayerPetTeam::onPet3ChangeClick(CCObject *){
    
     this->check_posAndChangeCand(2);

}

void MB_LayerPetTeam::onPet4ChangeClick(CCObject *){
    
     this->check_posAndChangeCand(3);

}

void MB_LayerPetTeam::onPet5ChangeClick(CCObject *){
    
     this->check_posAndChangeCand(4);

}

void MB_LayerPetTeam::onPet6ChangeClick(CCObject *){
    
     this->check_posAndChangeCand(5);
}

void MB_LayerPetTeam::onEquipClicked2(cocos2d::CCObject *)
{
    MB_LayerPetCommand* layer = dynamic_cast<MB_LayerPetCommand*>(getLogicParent());
    if (layer != NULL) {
        TutorialTriggerComplete
        layer->enterPetEquip();
    }
}

void MB_LayerPetTeam::onDetailClicked(cocos2d::CCObject *)
{
    MB_PetData * petData =MB_TeamData::getInstance()->getTeamMemberByIndex(MB_TeamData::getInstance()->getCurIndex())->m_pPet;
    MB_ResWindow* layer = MB_LayerPetDetail::createWithPetID(petData->getPetID());
    if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
}

void MB_LayerPetTeam::onLevelClicked(cocos2d::CCObject *)
{
    MB_PetData * petData =MB_TeamData::getInstance()->getTeamMemberByIndex(MB_TeamData::getInstance()->getCurIndex())->m_pPet;
    
    MB_LayerPetUpdate* layer = MB_LayerPetUpdate::create(petData->getPetID());
    if (layer != NULL) {
        TutorialTriggerComplete
        pushWindow(layer, true);
    }
}

void MB_LayerPetTeam::onQualityClicked(cocos2d::CCObject *)
{
    MB_PetData * petData =MB_TeamData::getInstance()->getTeamMemberByIndex(MB_TeamData::getInstance()->getCurIndex())->m_pPet;
    MB_LayerPetEnhance* layer = MB_LayerPetEnhance::create(kPetEnhanceEntrDetail, petData->getPetID());
    if (layer != NULL) {
        pushWindow(layer, true);
    }
}

void MB_LayerPetTeam::onPetClicked(cocos2d::CCObject *)
{
    TutorialTriggerComplete
    onEnterNodePetList(m_nType, MB_TeamData::getInstance()->getCurIndex(), kListTypeStand);
}

CCNode *MB_LayerPetTeam::itemForTouch(CCTouch *touch){

    
        CCPoint touchLocation = touch->getLocation();
        CCObject* pObject = NULL;
        int  count = 0;
        CCARRAY_FOREACH(m_pMenu->getChildren(), pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            
            if (pChild  && pChild->isEnabled())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = pChild->rect();
                r.origin = CCPointZero;
                
                if (r.containsPoint(local))
                {
                    
                    pChild->setTag(count);
                    
                    return pChild;
                }
            }
            
            count ++;
        }
    return NULL;
}
CCNode *MB_LayerPetTeam::itemForTouchAid(CCTouch *touch) {
    
    
    CCPoint touchLocation = touch->getLocation();
    for(int i = 0; i < 6 ; i++) {
        
        if(i != m_nLiSelItem ){
        
            MB_NodePetAid *node = (MB_NodePetAid *) m_pNodeAid[i]->getChildren()->objectAtIndex(0);
            CCPoint local = node->convertToNodeSpace(touchLocation);
            if ((node->getType() == kNodePetTypeTeamAid || node->getType() == kNodePetTypeTeamAidNone) && isInRect(local) && node->getPosition().x == 0  && node->getPosition().y == 0  )
            {
                return node;
            }
        }
    }
    
    return NULL;
}
bool MB_LayerPetTeam::isInRect(CCPoint & pos){
    if( pos.x < (m_nSize.width/2) &&  pos.x > ((-m_nSize.width)/2)  && pos.y < (m_nSize.height/2.0f) && pos.y > (-(m_nSize.height/2.0f))){
        
        return true;
    }
    return false;
}
bool MB_LayerPetTeam::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
   m_nSelItem = -1;
   m_nLiSelItem = -1;
   CCNode* m_pSelectedItem = itemForTouch(pTouch);    
    if(m_pSelectedItem!=NULL){
        
        m_nSelItem =m_pSelectedItem->getTag();
        if( m_pShowNode[m_nSelItem] != NULL){
       
            m_pShowNode[m_nSelItem]->getParent()->reorderChild(m_pShowNode[m_nSelItem], 2);
            m_pShowNode[m_nSelItem]->getParent()->sortAllChildren();
            m_pShowNode[m_nSelItem]->setShowInfo(false);
           
        }
        return true;
    }

    return false;
}
void MB_LayerPetTeam::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
    if(m_nType == kPetTeamTypeMain){
    
        return;
    }
    
    if (m_nSelItem != -1) {
        
        if(m_pShowNode[m_nSelItem] != NULL){
        
           CCPoint pos =  m_pShowNode[m_nSelItem]->getParent()->convertTouchToNodeSpace(pTouch);
           m_pShowNode[m_nSelItem]->setPosition(pos);
        }
    }
    if(m_nLiSelItem != -1){
    
        if(m_pNodeAid[m_nLiSelItem] != NULL){
        
            CCPoint pos = m_pNodeAid[m_nLiSelItem]->convertTouchToNodeSpace(pTouch);
            ((CCNode*)m_pNodeAid[m_nLiSelItem]->getChildren()->objectAtIndex(0))->setPosition(pos);
        }
    }
}

void MB_LayerPetTeam::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

    if (m_nSelItem != -1) {
        
        if( m_pShowNode[m_nSelItem] != NULL){
            
            m_pShowNode[m_nSelItem]->getParent()->reorderChild(m_pShowNode[m_nSelItem], 0);
            m_pShowNode[m_nSelItem]->getParent()->sortAllChildren();
            m_pShowNode[m_nSelItem]->setShowInfo(true);
        }
        
        m_nTagItem = -1 ;
        CCNode* pSelectedItem = itemForTouch(pTouch);
        if(pSelectedItem!=NULL){
            
            m_nTagItem =pSelectedItem->getTag();
        }
        if(m_nTagItem == m_nSelItem ){
            
            if (m_pShowNode[m_nSelItem] != NULL) {
                m_pShowNode[m_nSelItem]->runAction(CCMoveTo::create(0.1f, m_pNode[m_nSelItem]->getPosition()));
            }
            
            this->check_posAndChangeCand( m_nSelItem );
            
        }
        else  if(m_pShowNode[m_nSelItem] != NULL)
        {
            
            if(m_nType == kPetTeamTypeMain){
                
                return;
            }
            
            if( m_nTagItem != -1 ){
                
                m_pShowNode[m_nSelItem]->runAction(CCMoveTo::create(0.1f, m_pNode[m_nTagItem]->getPosition()));
                sendpet_move_pos(m_nSelItem+1, m_nTagItem+1);
                MB_Message::sharedMB_Message()->showMessage("读取网络数据", 15, NULL);
                
            }
            else {
                
                m_pShowNode[m_nSelItem]->runAction(CCMoveTo::create(0.1f, m_pNode[m_nSelItem]->getPosition()));
            }
        }
    }
 }

bool MB_LayerPetTeam::sendpet_move_pos(uint8_t petPos, uint8_t targetPos){

    return MB_TeamData::getInstance()->sendpet_move_pos(petPos, targetPos);
}

bool MB_LayerPetTeam::recvpet_move_pos(MB_MsgBuffer *recvPacket)
{
    //崩溃保护
    if (m_nTagItem < 0 || m_nTagItem >= CARD_IN_GAME || m_nSelItem < 0 || m_nSelItem >= CARD_IN_GAME)
    {
        MB_LOG("m_nTagItem = %d, m_SelItem = %d\n",m_nTagItem, m_nSelItem);
        return false;
    }
    
    if( m_pShowNode[m_nTagItem] == NULL){
        
        m_pShowNode[m_nTagItem]  =  m_pShowNode[m_nSelItem];
//        m_pText_name[m_nTagItem]->setString(m_pText_name[m_nSelItem]->getString());
//        m_pItemLevel[m_nTagItem]->setString(m_pItemLevel[m_nSelItem]->getString());
//        m_pText_name[m_nTagItem]->setColor(m_pText_name[m_nSelItem]->getColor());
        
        m_pShowNode[m_nSelItem] = NULL;
//        m_pText_name[m_nSelItem]->setString("");
//        m_pItemLevel[m_nSelItem]->setString("");
        m_pLock[m_nTagItem]->setVisible(false);
        m_pLock[m_nSelItem]->setVisible(isShowLock);
    }
    else {
        
        MB_NodePetTeam *temp  = m_pShowNode[m_nTagItem];
        m_pShowNode[m_nTagItem] = m_pShowNode[m_nSelItem];
//        std::string  tempName, tempLevel;
//        tempName = m_pText_name[m_nTagItem]->getString();
//        tempLevel = m_pItemLevel[m_nTagItem]->getString();
//        ccColor3B c3 = m_pText_name[m_nTagItem]->getColor();
//        m_pText_name[m_nTagItem]->setString(m_pText_name[m_nSelItem]->getString());
//        m_pItemLevel[m_nTagItem]->setString(m_pItemLevel[m_nSelItem]->getString());
//        m_pText_name[m_nTagItem]->setColor(m_pText_name[m_nSelItem]->getColor());
        m_pShowNode[m_nSelItem] = temp;
//        m_pText_name[m_nSelItem]->setString(tempName.c_str());
//        m_pItemLevel[m_nSelItem]->setString(tempLevel.c_str());
//        m_pText_name[m_nSelItem]->setColor(c3);
        temp->runAction(CCMoveTo::create(0.1f, m_pNode[m_nSelItem]->getPosition()));
        temp->setShowInfo(true);
        
    }
    if (MB_TeamData::getInstance()->getCurIndex() == m_nSelItem)
    {
        MB_TeamData::getInstance()->setCurIndex(m_nTagItem);
    }
    m_nSelItem = -1;
    m_nTagItem = -1;
    
    for (int i=0 ; i< CARD_IN_GAME; i++) {
        MB_PetData * data =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet;
        
        if(  data  !=  NULL){
            m_pItem[i]->setVisible(false);
//            m_pLevelBgNode[i]->setVisible(true);
//            m_pNodeShardow[i]->setVisible(false);
        }
        else
        {
//            m_pLevelBgNode[i]->setVisible(false);
//           
//            m_pNodeShardow[i]->setVisible(true);
            
            if(m_nCount < MB_TeamData::getInstance()->getLimitPet())
            {
                 m_pItem[i]->setVisible(true);
            }
        }
    }
    return true;
}

void MB_LayerPetTeam::onMsgRecv(CCNode* node, SocketResponse* response){
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
        case SC_GER_MOVE_POS:
            MB_Message::removeALLMessage();
            recvpet_move_pos(recvPacket);
            break;
        case SC_GER_REFRESH_POWER:{
            
                m_nAttackCount = MB_TeamData::getInstance()->getFightPower();
                char databuf[64];
                sprintf(databuf, "%llu",m_nAttackCount);
                m_pText_attackCount->setString(databuf);
            break;
        }
        case SC_GER_UPDATE:{
            
                m_nAttackCount = MB_TeamData::getInstance()->getFightPower();
                char databuf[64];
                sprintf(databuf, "%llu",m_nAttackCount);
                m_pText_attackCount->setString(databuf);
            
            }
            break;
        case   SC_GER_LIEU_MOVE_POS:
            onRestShow();
            break;
        default:
            break;
    }

}
void MB_LayerPetTeam::registerWithTouchDispatcher(void){
    
     CCDirector* pDirector = CCDirector::sharedDirector();
     pDirector->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}

void MB_LayerPetTeam::onEnterNodePetList(int layertype,int pos,int type)
{
    MB_NodePetList* pNodePetList = MB_NodePetList::create(layertype, pos, type);
    if(pNodePetList != NULL)
    {
        pushWindow(pNodePetList, true);
    }
}

void MB_LayerPetTeam::onEnterLayerGeneralEquipment(int64_t petid)
{    
    MB_LayerPetEquipment* pLayerPetEquipment = MB_LayerPetEquipment::create();
    
    if(pLayerPetEquipment != NULL)
    {
        pushWindow(pLayerPetEquipment, true);
    }
}

void MB_LayerPetTeam::trigpetPet(int index)
{
    if (MB_TeamData::getInstance()->getCurIndex() == index)
    {
        return;
    }
    
    TutorialTriggerComplete
    
    if (m_pTrigpetMenu == NULL) {
        
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
        m_pTrigpetMenu = pCCBReader->readNodeGraphFromFile("res/gui_embattle_cmd.ccbi", this);
        this->addChild(m_pTrigpetMenu);
        m_pPetAnimMgr = pCCBReader->getAnimationManager();
        CC_SAFE_RETAIN(m_pPetAnimMgr);
        m_pPetAnimMgr->runAnimationsForSequenceNamed("open");
        pCCBReader->release();
    }
    else
    {
        m_pPetAnimMgr->runAnimationsForSequenceNamed("open");
    }
    MB_TeamData::getInstance()->setCurIndex(index);
}


