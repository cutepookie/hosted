

#include "MB_LayerPetUnion.h"
#include "MB_FunctionMgr.h"
MB_LayerPetUnion::MB_LayerPetUnion(){
  
    m_pPreson = NULL;
    m_pUnion = NULL;
    m_pScrollsize = NULL;
    m_pNow_show_node = NULL;
    m_pComonPetPiece3Num = NULL;
    m_pComonPetPiece4Num = NULL;
    m_pComonPetPiece5Num = NULL;
    m_pNodePet = NULL;
    m_pPetNumber = NULL;
    m_pNodePiece = NULL;
    m_pArray = new CCArray();
    SOCKET_MSG_REGIST(SC_ITEM_COMPOUND,MB_LayerPetUnion);
}
MB_LayerPetUnion::~MB_LayerPetUnion(){
    
    CC_SAFE_RELEASE(m_pPreson);
    CC_SAFE_RELEASE(m_pUnion);
    CC_SAFE_RELEASE(m_pScrollsize);
    CC_SAFE_RELEASE(m_pNow_show_node);
    CC_SAFE_RELEASE(m_pComonPetPiece3Num);
    CC_SAFE_RELEASE(m_pComonPetPiece4Num);
    CC_SAFE_RELEASE(m_pComonPetPiece5Num);
    CC_SAFE_RELEASE(m_pNodePet);
    CC_SAFE_RELEASE(m_pPetNumber);
    CC_SAFE_RELEASE(m_pNodePiece);
    m_pArray->removeAllObjects();
    CC_SAFE_DELETE(m_pArray);
    SOCKET_MSG_UNREGIST(SC_ITEM_COMPOUND);
}
bool MB_LayerPetUnion::init(){
    
    if( MB_ResWindow::init() == false){
        
        return false;
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * node = pCCBReader->readNodeGraphFromFile("res/card_layer_list.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    m_pUnion->setEnabled(false);
    m_pUnion->getDisabledImage()->setVisible(false);
    m_pUnion->getNormalImage()->setVisible(false );
    m_pUnion->getSelectedImage()->setVisible(true);
    getListAndSort();

    m_objUnitSize = MB_LayerItemUnionUnit::create()->getContentSize();
    //OCandCppHelper::convertScollerViewSuitable(m_pScrollsize);
    NSGameHelper::adjustScrollNode(m_pScrollsize);
    m_pTableView = CCTableView::create(this,m_pScrollsize->getContentSize());    
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pScrollsize->addChild( m_pTableView);
    char databuf[50];
    sprintf(databuf, "%d",m_nListSize);
    m_pNow_show_node->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER3_ID));
    m_pComonPetPiece3Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER4_ID));
    m_pComonPetPiece4Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER5_ID));
    m_pComonPetPiece5Num->setString(databuf);
    int count = MB_ItemMgr::getInstance()->getCanComposPetNum();
    if(count == 0){
    
        m_pNodePet->setVisible(false);
   
    }else {
        
        m_pNodePet->setVisible(true);
        sprintf(databuf,"%d", count);
        m_pPetNumber->setString(databuf);
    }
    
    return  true;
}
void MB_LayerPetUnion::onResetWnd(void){
  
    getListAndSort();
    m_pTableView->reloadData();
    char databuf[50];
    sprintf(databuf, "%d",m_nListSize);
    m_pNow_show_node->setString(databuf);
    
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER3_ID));
    m_pComonPetPiece3Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER4_ID));
    m_pComonPetPiece4Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_GER5_ID));
    m_pComonPetPiece5Num->setString(databuf);
    int count = MB_ItemMgr::getInstance()->getCanComposPetNum();
    if(count == 0){
        
        m_pNodePet->setVisible(false);
        
    }else {
        
        m_pNodePet->setVisible(true);
        sprintf(databuf,"%d", count);
        m_pPetNumber->setString(databuf);
    }
}
void MB_LayerPetUnion::getListAndSort(){

    m_pArray->removeAllObjects();
    CCArray *list = CCArray::create();
    CCObject *obj;
    CCArray *array = MB_ItemMgr::getInstance()->getPetUnionArray();
    CCARRAY_FOREACH(array, obj){
        
        MB_ItemData * data = (MB_ItemData *)obj;
        if (data->getItemNumber() >0 ) {
            
            list->addObject(data);
        }
    }
    
    int length = list->count();
    for (int i = 0 ; i < length; i++) {
        
        MB_ItemData * nowCheckdata = (MB_ItemData *)list->objectAtIndex(0);
        MB_ItemTemplate *nowTemplete =  MB_ItemMgr::getInstance()->getItemTemplateByID(nowCheckdata->getItemID());
        MB_PetTemplate *nowPet =  MB_PetMgr::getInstance()->getPetTemplateByID(nowTemplete->getComposeItemID());
        bool  isNowEnghou =  MB_ItemMgr::getInstance()->getCanComposPetNumByType(nowCheckdata) > 0;
        CCARRAY_FOREACH(list, obj){
            
            MB_ItemData * data = (MB_ItemData *)obj;
            MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
            bool isEnghou =  MB_ItemMgr::getInstance()->getCanComposPetNumByType(data) > 0;
            if( isNowEnghou ){
                
                if(isEnghou){
                    
                    if(templete->getComposeItemID() < nowTemplete->getComposeItemID()){
                    
                        nowCheckdata = data;
                    }
                    
                }else {
                
                    continue;
                }
                
           
            }else{
            
                if(isEnghou){
                   
                    nowCheckdata =data;
                    isNowEnghou = true;
                
                }else {
                
                    if(data->getItemNumber() > nowCheckdata->getItemNumber()){
                    
                        nowCheckdata = data;
                    
                    }else if(data->getItemNumber() == nowCheckdata->getItemNumber()){
                    
                        MB_PetTemplate *checkPet =  MB_PetMgr::getInstance()->getPetTemplateByID(templete->getComposeItemID());
                        
                        if(checkPet->getPetStar() > nowPet->getPetStar()){
                        
                             nowCheckdata = data;
                            
                        }else   if(checkPet->getPetStar() == nowPet->getPetStar()){
                        
                            if(checkPet->getPetTypeID() < nowPet->getPetTypeID()){
                            
                                 nowCheckdata = data;
                            }
                        }
                        
                            
                    }
                }
            
            }
            
        }
        list->removeObject(nowCheckdata);
        m_pArray->addObject(nowCheckdata);
    }
    m_nListSize = m_pArray->count();   
}
cocos2d::SEL_MenuHandler MB_LayerPetUnion::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPetUnion::onCloseClicked);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerPetUnion::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

void MB_LayerPetUnion::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}
bool MB_LayerPetUnion::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Preson", CCMenuItemImage *, m_pPreson);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Union", CCMenuItemImage *, m_pUnion);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize2", CCNode *, m_pScrollsize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "now_show_node", CCLabelTTF*, m_pNow_show_node);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pComonPetPiece3Num", CCLabelTTF*, m_pComonPetPiece3Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pComonPetPiece4Num", CCLabelTTF*, m_pComonPetPiece4Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pComonPetPiece5Num", CCLabelTTF*, m_pComonPetPiece5Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet", CCNode *, m_pNodePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetNumber", CCLabelTTF*, m_pPetNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece", CCNode*, m_pNodePiece);
    
    return false;
}
MB_LayerPetUnion* MB_LayerPetUnion::create(){
    
MB_LayerPetUnion *ptr = new MB_LayerPetUnion();
    if(ptr && ptr->init()){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
void MB_LayerPetUnion::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){

}
cocos2d::CCSize MB_LayerPetUnion::cellSizeForTable(cocos2d::extension::CCTableView *table){

    return m_objUnitSize;
}
cocos2d::extension::CCTableViewCell* MB_LayerPetUnion::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    MB_LayerItemUnionUnit * node = MB_LayerItemUnionUnit::create();
    cell->addChild(node);
    node->setData((MB_ItemData *)m_pArray->objectAtIndex(idx));
    node->setPosition(m_objUnitSize.width/2.0f,m_objUnitSize.height/2.0f);
    
    return cell;
}
unsigned int MB_LayerPetUnion::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){

    return m_nListSize;
}
void MB_LayerPetUnion::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_ITEM_COMPOUND:
            MB_Message::removeALLMessage();
            recvitem_compound(recvPacket);
            break;
        default:
            break;
    }
    
}
bool  MB_LayerPetUnion::recvitem_compound(MB_MsgBuffer* recvPacket){    
 
    uint8_t data8;
    recvPacket->readU8(&data8);
    if(data8 == 1){
        
        uint16_t data16;
        recvPacket->readU16(&data16);
        this->dirty();
        MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data16);
        MB_LayerRewardOne* layer = MB_LayerRewardOne::createPet(kRewardValueTypePet,templete->getComposeItemID(),1);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
    }
        return true;
}
