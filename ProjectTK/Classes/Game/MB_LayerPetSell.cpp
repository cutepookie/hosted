
#include "MB_LayerPetSell.h"

MB_LayerPetSell::MB_LayerPetSell(){
   
    m_pText_pet = NULL;
   // m_pText_Money = NULL;
    m_pScrollSize = NULL;
   // m_nMoney = 0;
    m_pPetArray = CCArray::create();
    m_pPetArray->retain();
    m_nCout = 0;
    MB_PetMgr::getInstance()->clearPetForSell();
    SOCKET_MSG_REGIST(SC_GER_SELL, MB_LayerPetSell);
}

MB_LayerPetSell::~MB_LayerPetSell(){
    
    SOCKET_MSG_UNREGIST(SC_GER_SELL);
    CC_SAFE_RELEASE(m_pPetArray);
   // CC_SAFE_RELEASE(m_pText_Money);
    CC_SAFE_RELEASE(m_pText_pet);    
    CC_SAFE_RELEASE(m_pScrollSize);
}

MB_LayerPetSell*  MB_LayerPetSell::create(){
    
    MB_LayerPetSell *ptr = new MB_LayerPetSell();
    
    if( ptr && ptr->init() ){
        
        ptr->autorelease();
        return  ptr;
        
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
    
}

bool MB_LayerPetSell::init(){
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/gui_main_generalsale.ccbi", this);
    this->addChild(node);
    CC_SAFE_DELETE(pCCBReader);
    
    //解析cell的大小
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->readNodeGraphFromFile("res/card_node_unit.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    m_cellSize = MB_NodePetUnit::create(-1, 0)->getCellSize();
    m_pText_pet->setString("0");
   // m_pText_Money->setString("0");
    //初始化可售数据
    reloadArray();
    OCandCppHelper::convertScollerViewSuitable(m_pScrollSize);
    m_pTableView = CCTableView::create(this, m_pScrollSize->getContentSize());
    
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pScrollSize->addChild( m_pTableView);
    m_pTableView->reloadData();
    
    
    return true;
}

cocos2d::SEL_MenuHandler MB_LayerPetSell::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", MB_LayerPetSell::onBackClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCommitClicked", MB_LayerPetSell::onCommitClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAutoClicked", MB_LayerPetSell::onAutoClicked);
    return  NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerPetSell::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return  NULL;

}

bool  MB_LayerPetSell::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pText_pet", CCLabelTTF *, m_pText_pet);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pText_Money", CCLabelFX *, m_pText_Money);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *, m_pScrollSize);
    return  false;
}
void MB_LayerPetSell::onAutoClicked(CCObject *){
    CCObject *obj;
    CCARRAY_FOREACH(m_pPetArray, obj){
    
        MB_PetData *data = (MB_PetData *)obj;
        MB_PetTemplate * templete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getPetTypeID());
        if (templete->getPetStar() == 3 && data->getReadyForSold() == false)
        {    
            data->setReadyForSold(true);
            m_nCout ++;
          //  MB_PetTemplate * temptete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getPetTypeID());
          //            m_nMoney = m_nMoney  + temptete->getPetCost()*(1 +data->getPetLevel()/10+ data->getPetQuallity()/2 );
//            sprintf(databuf, "%d",m_nMoney);
//            m_pText_Money->setString(databuf);
  
        }
    }
    char databuf[50];
    sprintf(databuf, "%d", m_nCout);
    m_pText_pet->setString(databuf);
    int num =  numberOfCellsInTableView(m_pTableView);
    for (int i = 0; i < num; i++) {
        
        m_pTableView->updateCellAtIndex(i);
    }
}
void MB_LayerPetSell::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}

CCSize MB_LayerPetSell::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerPetSell::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
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
    reloadCellData(cell,idx);
    return cell ;
}

unsigned int MB_LayerPetSell::numberOfCellsInTableView(CCTableView *table)
{
    return m_pPetArray->count();
}

void  MB_LayerPetSell::addToSell(int64_t petid){

 
    MB_PetData *data = MB_PetMgr::getInstance()->getPetDataByUID(petid);
    if(data && data->getReadyForSold() == false){
        
        data->setReadyForSold(true);
        m_nCout ++;
        char databuf[50];
        sprintf(databuf, "%d", m_nCout);
        m_pText_pet->setString(databuf);
       // m_nMoney = m_nMoney  + temptete->getPetCost();
        //*(1 +data->getPetLevel()/10+ data->getPetQuallity()/2 );
       // sprintf(databuf, "%d",m_nMoney);
        //m_pText_Money->setString(databuf);
    }
    
}
void  MB_LayerPetSell::removeFromSell(int64_t petid){
    
    MB_PetData *data = MB_PetMgr::getInstance()->getPetDataByUID(petid);
    if(data && data->getReadyForSold()){
        
        data->setReadyForSold(false);
        m_nCout --;
       // MB_PetTemplate * temptete = MB_PetMgr::getInstance()->getPetTemplateByID(data->getPetTypeID());
        char databuf[50];
        sprintf(databuf, "%d", m_nCout);
        m_pText_pet->setString(databuf);
      //  m_nMoney = m_nMoney  - temptete->getPetCost()*(1 + data->getPetLevel()/10 + data->getPetQuallity()/2 );

        //sprintf(databuf, "%d",m_nMoney);
        //m_pText_Money->setString(databuf);
    }
}

void  MB_LayerPetSell::onCommitClicked(CCObject *)
{
    if(m_nCout >0){
    
        sendpet_sell();
    
    }else {
    
        MB_Message::sharedMB_Message()->showMessage("未选择任何精灵出售");
    }
}

void MB_LayerPetSell::onBackClicked(cocos2d::CCObject *)
{
    popWindow(true);
}

bool MB_LayerPetSell::sendpet_sell(){
    
    MB_Message::sharedMB_Message()->showMessage("出售中", 600, NULL);
    SOCKET_REQUEST_START(CS_GER_SELL);
    CCObject *obj;
    uint16_t count =0;
    CCARRAY_FOREACH(m_pPetArray,obj){
        
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            count++;
        }
        
    }
    packet->writeU16(count);
    CCARRAY_FOREACH(m_pPetArray,obj){
        
        if( ((MB_PetData *)obj)->getReadyForSold()){
            
            packet->WriteUINT64(((MB_PetData *)obj)->getPetID());
        }
        
    }
    SOCKET_REQUEST_END(SC_GER_SELL, MB_PetMgr::onMsgRecv);
    return true;
}

bool  MB_LayerPetSell::recvpet_sell(MB_MsgBuffer *recvPacket){
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1) {
//    
        MB_Message::removeALLMessage();
        

        CCArray *array =  CCArray::create();
        uint16_t length;
        recvPacket->readU16(&length);
        uint8_t data8;
        uint16_t data16;
        uint32_t data32;
        
        for (int i = 0; i < length ; i++) {
          
            RewardTempleteValue *data = new RewardTempleteValue();
            array->addObject(data);
            data->release();
            recvPacket->readU8(&data8);
            data->setType(data8);
            recvPacket->readU16(&data16);
            data->setValueID(data16);
            recvPacket->readU32(&data32);
            data->setNumber(data32);
        }
        m_nCout = 0;
        MB_LayerRewardMore *layer =  MB_LayerRewardMore::create(array);
        this->pushWindow(layer);
        reloadArray();
        m_pTableView->reloadData();
        m_pText_pet->setString("0");
        
    }else{
    
        if (result == 2)
        MB_Message::sharedMB_Message()->showMessage("失败","精灵不存在","确定");

        if (result == 3)
        MB_Message::sharedMB_Message()->showMessage("失败","某个精灵不能卖","确定");

        if (result == 4)
        MB_Message::sharedMB_Message()->showMessage("失败","未知原因","确定");

    }
    return true;
}

void MB_LayerPetSell::onMsgRecv(CCNode* node, SocketResponse* response){
    
    
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
            
        case SC_GER_SELL:
            recvpet_sell(recvPacket);
            break;
        default:
            break;
    }
    
}

void MB_LayerPetSell::reloadArray(){
    
    m_pPetArray->removeAllObjects();
    CCObject *petData;
    //需要显示的列表
    CCARRAY_FOREACH_REVERSE(MB_PetMgr::getInstance()->getPetDataArray(), petData){
        
        if(MB_TeamData::getInstance()->checkInTeam((MB_PetData *)petData) == true){
            
            continue;
        }                
        m_pPetArray->addObject(petData);
    }
}

void MB_LayerPetSell::reloadCellData(CCTableViewCell *cell,int idx){
    
    MB_LOG("table index %d",idx);
    MB_PetData *data = (MB_PetData *)m_pPetArray->objectAtIndex(idx);
    MB_NodePetUnit *node = MB_NodePetUnit::create(data->getPetID(), false);
    
    node->setPosition(ccp(m_pScrollSize->getContentSize().width/2.0f, m_cellSize.height/2.0f));
    node->setUnitType(kPetTeamTypeCost);
    cell->addChild(node);
    node->setTag(1);    
    if (data->getReadyForSold()){
   
        node->changeSel();
    }
}
