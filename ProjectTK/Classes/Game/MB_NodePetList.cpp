
#include "MB_NodePetList.h"
#include "MB_LayerShowPic.h"
#include "MB_FunctionMainWnd.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerChatMain.h"
#include "MB_GuardInterface.h"
MB_NodePetList::MB_NodePetList()
:m_pNow_show_node(NULL)
{
    m_pScrollsize = NULL;
    m_nCanTouch = true;
    m_pArray = new CCArray();
    m_uPetTypeID = 0;
    m_uPetID = 0;
    m_pNodePiece = NULL;
    m_pNodePet = NULL;
    m_pPetNumber = NULL;
    m_bShowRoleInfoPanel = true;
    m_pTTFTitleName1 = NULL;
    
    SOCKET_MSG_REGIST(SC_GER_STANDUP, MB_NodePetList);
    SOCKET_MSG_REGIST(SC_GER_LIEU_STANDUP, MB_NodePetList);
    MB_LayerChatMain::SetChatMainVisible(false, "MB_NodePetList");
}

MB_NodePetList::~MB_NodePetList()
{
    SOCKET_MSG_UNREGIST(SC_GER_STANDUP);
    SOCKET_MSG_UNREGIST(SC_GER_LIEU_STANDUP);
    
    CC_SAFE_RELEASE(m_pArray);
//    CC_SAFE_RELEASE(m_pNow_show_page);
    CC_SAFE_RELEASE(m_pNow_show_node);
    CC_SAFE_RELEASE(m_pNodePiece);
    CC_SAFE_RELEASE(m_pNodePet);
    CC_SAFE_RELEASE(m_pPetNumber);
//    CC_SAFE_RELEASE(m_pSpriteLeft);
//    CC_SAFE_RELEASE(m_pSpriteRight);
    CC_SAFE_RELEASE(m_pScrollsize);
    CC_SAFE_RELEASE(m_pTTFTitleName1);
//MB_LayerChatMain::SetChatMainVisible(true, "MB_NodePetList");
}

MB_NodePetList * MB_NodePetList::create(int layerType){
    
    MB_NodePetList * node = new MB_NodePetList();    
    if( node && node->init(layerType, 0, kListTypeStand, 0, 0)){
        
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;

}

MB_NodePetList* MB_NodePetList::create(int layerType, uint16_t petTypeID, uint64_t petID)
{
    MB_NodePetList * node = new MB_NodePetList();
    if( node && node->init(layerType, 0, kListTypeStand, petTypeID, petID)){
        
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;
}

MB_NodePetList * MB_NodePetList::create(int layertype, int pos,int type){
    
    MB_NodePetList * node = new MB_NodePetList();    
    if( node && node->init(layertype,pos,type,0,0)){
        
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;
}
bool MB_NodePetList::init(int layerType, int pos,int type,uint16_t petTypeID,uint64_t petID){
    
    if( CCLayer::init() == false){
    
        return false;
    }
    
    m_pLayerType = layerType;
    m_nPos = pos;
    m_nPerPage = 7;
    m_nType = type;
    m_uPetTypeID = petTypeID;
    m_uPetID = petID;

    m_bscrollerWidth = CCDirector::sharedDirector()->getWinSize().width/3.0f;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* node = NULL;
    if (m_pLayerType == kPetTeamTypeEnhance
        || m_pLayerType == kPetTeamTypeEnhanceCost
        || m_pLayerType == kPetTeamTypeUpdate
        || m_pLayerType == kPetGuardTypeSelect
        || ((m_pLayerType == kPetTeamTypeMove || m_pLayerType == kPetTeamTypeEquipment) && (m_nType == kListTypeStand || m_nType == kListTypeAidStand)))
    {
        node = pCCBReader->readNodeGraphFromFile("res/card_layer_changelist.ccbi", this);
    }
    else
    {
        node = pCCBReader->readNodeGraphFromFile("res/card_layer_list.ccbi", this);
        m_pNodePiece->setVisible(false);
        
        int count = MB_ItemMgr::getInstance()->getCanComposPetNum();
        if(count == 0){
            
            m_pNodePet->setVisible(false);
            
        }else {
            char databuf[50];
            m_pNodePet->setVisible(true);
            sprintf(databuf,"%d", count);
            m_pPetNumber->setString(databuf);
        }
    }
    addChild(NSGameHelper::createDisableTouchLayer12());
    this->addChild(node);
    
    pCCBReader->release();
    //初始化数据
    reloadArray();

    m_objUnitSize = MB_NodePetUnit::create(-1, 0)->getCellSize();
    NSGameHelper::adjustScrollNode(m_pScrollsize);
    m_pTableView = CCTableView::create(this, m_pScrollsize->getContentSize());

    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pScrollsize->addChild( m_pTableView);
    m_pTableView->reloadData();

//    m_soldButton->setVisible( m_nType == kListTypeList);
    if (m_pLayerType == kPetTeamTypeEnhance
        || m_pLayerType == kPetTeamTypeEnhanceCost
        || m_pLayerType == kPetTeamTypeUpdate
        || m_pLayerType == kPetGuardTypeSelect
        || ((m_pLayerType == kPetTeamTypeMove || m_pLayerType == kPetTeamTypeEquipment) && (m_nType == kListTypeStand || m_nType == kListTypeAidStand)))
    {
        //不显示数量
    }
    else
    {
        char databuf[10];
        //    m_pNow_show_page->setString("1");
        sprintf(databuf, "%d",m_nListSize);
        m_pNow_show_node->setString(databuf);
    }
    
    if (m_pLayerType == kPetGuardTypeSelect)
    {
        m_pTTFTitleName1->setString("选择守护");
    }
    return  true;
}


void MB_NodePetList::onResetWnd()
{
    
    MB_ResWindow::onResetWnd();
    reloadArray();    
    m_pTableView->reloadData();
 
    
    if (m_pLayerType == kPetTeamTypeEnhance
        || m_pLayerType == kPetTeamTypeEnhanceCost
        || m_pLayerType == kPetTeamTypeUpdate
        || m_pLayerType == kPetGuardTypeSelect
        || ((m_pLayerType == kPetTeamTypeMove || kPetTeamTypeEquipment) && (m_nType == kListTypeStand || m_nType == kListTypeAidStand)))
    {
        //不显示数量
    }
    else
    {
        char databuf[10];
        //    m_pNow_show_page->setString("1");
        sprintf(databuf, "数量%d",m_nListSize);
        m_pNow_show_node->setString(databuf);
    }
    
    


}

void MB_NodePetList::reloadArray(){

    m_pArray->removeAllObjects();
//    CCArray *tempList  =CCArray::create();
    CCObject *petData;
    
    MB_PetTemplate* petTemp = NULL;
    uint8_t uPetStar = 0;
    if (m_pLayerType == kPetTeamTypeEnhanceCost)
    {
        petTemp = MB_PetMgr::getInstance()->getPetTemplateByID(m_uPetTypeID);
        uPetStar = petTemp->getPetStar();

    }
    CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();
    CCARRAY_FOREACH(pArray, petData){
        
        if (m_pLayerType == kPetTeamTypeEnhanceCost)
        {
            //查找同星级 不是同张卡牌 没上阵的卡牌 不是经验卡牌 作为材料
            MB_PetTemplate* petCost = ((MB_PetData*)petData)->getTemplete();
            if(!petCost)
            {
                continue;
            }
            uint8_t uPetCostStar = petCost->getPetStar();
            if (uPetStar != uPetCostStar      
                || ((MB_PetData*)petData)->getPetID() == m_uPetID
                || MB_TeamData::getInstance()->checkInTeam((MB_PetData *)petData)
                || NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID()))
            {
                continue;
            }
            if (((MB_PetData*)petData)->getIsHomelandPet())
            {
                continue;
            }
        }
        
        //上阵列表和升级选择 屏蔽经验卡牌
        if(m_pLayerType == kPetTeamTypeEquipment
           || m_pLayerType == kPetTeamTypeUpdate
           || m_pLayerType == kPetTeamTypeMove
           || m_pLayerType == kPetGuardTypeSelect )
        {
            if (NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID())) {
                continue;
            }
        }
        
        if (m_pLayerType == kPetGuardTypeSelect) //上阵守护 不显示队形里的精灵
        {
            if (MB_TeamData::getInstance()->checkInTeam((MB_PetData*)petData))
            {
                continue;
            }
        }
        m_pArray->addObject(petData);
    }
 
    m_nListSize = m_pArray->count();
    //排序
    if (m_pLayerType == kPetTeamTypeEnhanceCost && m_nListSize > 1 && m_uPetTypeID != 0) {
        sortArray();

    }
}
cocos2d::SEL_MenuHandler MB_NodePetList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLevelUpClicked",     MB_NodePetList::onLevelUpClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onQualityUpClicked",     MB_NodePetList::onQualityUpClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_NodePetList::onListCloseClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodePetList::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    
    return NULL;
}

bool MB_NodePetList::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "now_show_node", CCLabelTTF*, m_pNow_show_node);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *, m_pScrollsize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece", CCNode*, m_pNodePiece);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet", CCNode*, m_pNodePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetNumber", CCLabelTTF*, m_pPetNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFTitleName1",CCLabelBMFont*,m_pTTFTitleName1);
    
    return false;
}


void MB_NodePetList::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){

    
}
bool MB_NodePetList::sendpet_standup( uint64_t petID)
{
     MB_Message::sharedMB_Message()->showMessage("等待", 15, NULL);
    if(m_nType == kListTypeStand)
    {
        MB_TeamData::getInstance()->sendpet_standup(m_nPos + 1 , petID);
    }
//   else {
//        
//        MB_TeamData::getInstance()->sendpet_lieu_standup(m_nPos + 1 , petID);
//    }
    return  true;
}
void MB_NodePetList::onMsgRecv(CCNode* node, SocketResponse* response)
{
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

        case SC_GER_STANDUP:
        {
            uint8_t result = 0;
            recvPacket->readU8(&result);
            if(result == 1){
            
                unscheduleAllSelectors();
                popWindow(true);
            }
           
            break;
        }
        case SC_GER_LIEU_STANDUP:{
        
            uint8_t result = 0;
            recvPacket->readU8(&result);
            if(result == 1){
           
                unscheduleAllSelectors();
                popWindow(true);
            }
            break;
        }
        default:
            break;
    }

}
cocos2d::CCSize MB_NodePetList::cellSizeForTable(cocos2d::extension::CCTableView *table){

    return  m_objUnitSize;
    
}
cocos2d::extension::CCTableViewCell* MB_NodePetList::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    
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
    
    
    if (m_pLayerType == kPetTeamTypeEnhance
        || m_pLayerType == kPetTeamTypeEnhanceCost
        || m_pLayerType == kPetTeamTypeUpdate
        || ((m_pLayerType == kPetTeamTypeMove ||  m_pLayerType == kPetTeamTypeEquipment) && (m_nType == kListTypeStand || m_nType == kListTypeAidStand)))
    {
        reloadCellData(cell,idx);
        
    }else {
        
        
        
        reloadCellData(cell,idx);
    }
    return cell ;
}
void MB_NodePetList::reloadCellData(CCTableViewCell *cell,int idx){

    MB_LOG("table index %d",idx);
    MB_PetData *data = (MB_PetData *)m_pArray->objectAtIndex(idx);
    bool issel = MB_TeamData::getInstance()->checkInTeam(data);
    MB_NodePetUnit *node = MB_NodePetUnit::create(data->getPetID(), issel);
    node->setPosition(ccp(m_pScrollsize->getContentSize().width/2.0f,m_objUnitSize.height/2.0f));
    cell->addChild(node);
    node->setTag(1);
    node->setUnitType(m_pLayerType);
   
}
unsigned int MB_NodePetList::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    
    if (m_pLayerType == kPetTeamTypeEnhance
        || m_pLayerType == kPetTeamTypeEnhanceCost
        || m_pLayerType == kPetTeamTypeUpdate
        || ((m_pLayerType == kPetTeamTypeMove  || m_pLayerType == kPetTeamTypeEquipment)&& (m_nType == kListTypeStand || m_nType == kListTypeAidStand)))
    {
        //不显示数量
      
            return m_nListSize  ;
        
    }else {
        
        return m_nListSize;
    }
}
void MB_NodePetList::scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {
    
}

void MB_NodePetList::scrollViewDidZoom(cocos2d::extension::CCScrollView* view){
    
}

void MB_NodePetList::onSoldClick(CCObject *){
    
    MB_LayerPetSell* layer = MB_LayerPetSell::create();
    pushWindow(layer,true);
}

void MB_NodePetList::onLevelUpClicked(cocos2d::CCObject *)
{
    
}

void MB_NodePetList::onQualityUpClicked(cocos2d::CCObject *)
{
    
}

void MB_NodePetList::onListCloseClick(CCObject* )
{
    //popWindow();
    
    if (m_pLayerType != kPetTeamTypeMain)
    {
        popWindow();
    }
    else
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }
//
}

void MB_NodePetList::reloadPet(){
    
    reloadArray();
    m_pTableView->reloadData();
}

void MB_NodePetList::setTableTouch(bool istouch){

    m_pTableView ->setTouchEnabled(istouch);
    m_nCanTouch = istouch;
    this->setTouchEnabled(istouch);
    for(int i = 0; i < m_nListSize ; i++){
        
        CCTableViewCell *cell = m_pTableView->cellAtIndex(i);
        if (cell != NULL ) {
            
            MB_NodePetUnit *node = (MB_NodePetUnit *)cell->getChildByTag(1);
            if (node != NULL) {
                
                node->setIsHeadCanClick(istouch);
            }
        }
    }
}

//材料排序，Id相同优先 其次品阶升序  等级升序 ID升序
void MB_NodePetList::sortArray()
{   
    MB_PetData *petData1,*petData2;
    int nSameIDCount = 0;
     //优先同ID
    for(int i = 0;i < m_nListSize;++i)
    {
        for (int j = i+1; j < m_nListSize; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetTypeID() == m_uPetTypeID)
            {
                nSameIDCount++;
                break;
            }
            
            if (petData2->getPetTypeID() == m_uPetTypeID)
            {
                nSameIDCount++;
                m_pArray->exchangeObjectAtIndex(i,j);
                break;
            }
        }
    }
    petData1 = (MB_PetData*)m_pArray->objectAtIndex(m_nListSize-1);
    if (petData1->getPetTypeID() == m_uPetTypeID)
    {
        nSameIDCount++;
    }
    //同ID 品阶升序
    for(int i = 0;i < nSameIDCount;++i)
    {
        for (int j = i+1; j < nSameIDCount; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() > petData2->getPetQuallity())
            {
                m_pArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //同ID品阶  等级升序
    for(int i = 0;i < nSameIDCount;++i)
    {
        for (int j = i+1; j < nSameIDCount; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity())
            {
                break;
            }
            if (petData1->getPetLevel() > petData2->getPetLevel())
            {
                m_pArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //不同ID   品阶升序
    for(int i = nSameIDCount;i < m_nListSize;++i)
    {
        for (int j = i+1; j < m_nListSize; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() > petData2->getPetQuallity())
            {
                m_pArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }

    //不同ID 同品阶  等级升序
    for(int i = nSameIDCount;i < m_nListSize;++i)
    {
        for (int j = i+1; j < m_nListSize; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity())
            {
                break;
            }
            if (petData1->getPetLevel() > petData2->getPetLevel())
            {
                m_pArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //不同ID 同品阶  同等级  ID升序
    for(int i = nSameIDCount;i < m_nListSize;++i)
    {
        for (int j = i+1; j < m_nListSize; ++j)
        {
            petData1 = (MB_PetData*)m_pArray->objectAtIndex(i);
            petData2 = (MB_PetData*)m_pArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity()
                || petData1->getPetLevel() != petData2->getPetLevel())
            {
                break;
            }
            if (petData1->getPetTypeID() > petData2->getPetTypeID())
            {
                m_pArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
}

