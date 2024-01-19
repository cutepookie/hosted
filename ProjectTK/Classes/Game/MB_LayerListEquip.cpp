

#include "MB_LayerListEquip.h"
#include "MB_LayerListItemSale.h"
#include "MB_LayerShowPic.h"
#include "MB_FunctionMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerListEquip::MB_LayerListEquip()
{
    m_pTableContainer = NULL;
    m_pTableContainer2 = NULL;
    m_pTableView = NULL;
    m_pNodeSale = NULL;
    m_pLabelItemCount = NULL;
    m_pComonItemPiece3Num = NULL;
    m_pComonItemPiece4Num = NULL;
    m_pComonItemPiece5Num = NULL;
    m_pNodeItem = NULL;
    m_pItemNumber = NULL;
    m_pNodePiece = NULL;
    //m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_ITEM_COMPOUND, MB_LayerListEquip);

}
MB_LayerListEquip::~MB_LayerListEquip()
{

    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pTableContainer2);
    CC_SAFE_RELEASE_NULL(m_pNodeSale);
    CC_SAFE_RELEASE_NULL(m_pLabelItemCount);
    
    CC_SAFE_RELEASE(m_pComonItemPiece3Num);
    CC_SAFE_RELEASE(m_pComonItemPiece4Num);
    CC_SAFE_RELEASE(m_pComonItemPiece5Num);
    CC_SAFE_RELEASE(m_pNodeItem);
    CC_SAFE_RELEASE(m_pItemNumber);
    CC_SAFE_RELEASE(m_pNodePiece);
    SOCKET_MSG_UNREGIST(SC_ITEM_COMPOUND);
  }

MB_LayerListEquip* MB_LayerListEquip::create(int type)
{
    MB_LayerListEquip* layer = new MB_LayerListEquip();
    if (layer != NULL && layer->init(type)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListEquip::init(int type)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    setSubType(type);
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //解析cell的大小
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->readNodeGraphFromFile("res/item_node_unitopen.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    //读取界面
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_layer_list1.ccbi", this);
    
    this->addChild(pNode);

    CC_SAFE_RELEASE_NULL(pCCBReader);
    m_nLength = 0;
    //OCandCppHelper::convertScollerViewSuitable(m_pTableContainer);
    //OCandCppHelper::convertScollerViewSuitable(m_pTableContainer2);
    NSGameHelper::adjustScrollNode(m_pTableContainer);
    NSGameHelper::adjustScrollNode(m_pTableContainer2);
    m_nLength = 0;
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer2->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setDelegate(this);
    m_pTableContainer2->addChild(tableView);
    
    //    tableView->reloadData();
    m_pTableView = tableView;

    onResetWnd();
    
	return true;
}

void MB_LayerListEquip::onResetWnd()
{

    
    if(m_kSubType == kListItemTypeEquip){

        m_nLength = MB_ItemMgr::getInstance()->getEquipArray()->count();
        
        m_pNodePiece->setVisible(false);
    
    }else {
    
        getListUnion();
        m_pNodePiece->setVisible(true);
    }
    
    m_pTableView->reloadData();
    
    refreshCount();
    
    //button显示判断
//    if (m_kSubType == kListItemTypeEquipUp) {
//        m_pBtPiece->setVisible(false);
//        m_pNodeSale->setVisible(false);
//    }
//    //button高亮更新
    char databuf[50];
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM3_ID));
    m_pComonItemPiece3Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM4_ID));
    m_pComonItemPiece4Num->setString(databuf);
    sprintf(databuf,"%d", MB_ItemMgr::getInstance()->getItemEntityCount(COMPOS_ITEM5_ID));
    m_pComonItemPiece5Num->setString(databuf);
    int count = MB_ItemMgr::getInstance()->getCanComposItemNum();
    if(count == 0){
        
        m_pNodeItem->setVisible(false);
        
    }else {
        
        m_pNodeItem->setVisible(true);
        sprintf(databuf,"%d", count);
        m_pItemNumber->setString(databuf);
    }

   updateButton();
}
void  MB_LayerListEquip::getListUnion(){

  
    CCArray *list = MB_ItemMgr::getInstance()->getEquipUnionArray();
    int length = list->count();
    for (int i = 0 ; i < length; i++) {
        
        MB_ItemData * nowCheckdata = (MB_ItemData *)list->objectAtIndex(i);
        MB_ItemTemplate *nowTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(nowCheckdata->getItemID());
        MB_ItemTemplate *nowItem =  MB_ItemMgr::getInstance()->getItemTemplateByID(nowTemplete->getComposeItemID());
        bool  isNowEnghou =  MB_ItemMgr::getInstance()->getCanComposItemNumByType(nowCheckdata) > 0;
        
        
        for (int j = i ; j<length ; j++) {
            
            MB_ItemData * data =  (MB_ItemData *)list->objectAtIndex(j);
            MB_ItemTemplate *templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
            bool isEnghou = MB_ItemMgr::getInstance()->getCanComposItemNumByType(data) > 0;
            
            if( isNowEnghou ){
                
                if(isEnghou){
                    
                    if(templete->getComposeItemID() < nowTemplete->getComposeItemID()){
                        
                        nowCheckdata =data;
                    }
                    
                }else {
                    
                    continue;
                }
                
                
            }else{
                
                if(isEnghou){
                    
                    nowCheckdata =data;
                    isNowEnghou = isEnghou;
                    
                }else {
                    
                    if(data->getItemNumber() > nowCheckdata->getItemNumber()){
                        
                        nowCheckdata = data;
                        
                    }else if(data->getItemNumber() == nowCheckdata->getItemNumber()){
                        
                        MB_ItemTemplate *checkPet =  MB_ItemMgr::getInstance()->getItemTemplateByID(templete->getComposeItemID());
                        
                        if(checkPet->getItemStar() > nowItem->getItemStar()){
                            
                            nowCheckdata = data;
                            
                        }else   if(checkPet->getItemStar() == nowItem->getItemStar()){
                            
                            if(checkPet->getItemID() < nowItem->getItemID()){
                                
                                nowCheckdata = data;
                            }
                        }
                    }
                }
                
            }
            
        }
        int k = list->indexOfObject(nowCheckdata);
        list->exchangeObjectAtIndex(i,k);
    }
    m_nLength = MB_ItemMgr::getInstance()->getEquipUnionArray()->count();
}

bool MB_LayerListEquip::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
        return true;
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btSale", CCNode*, m_pNodeSale);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ItemCount", CCLabelTTF*, m_pLabelItemCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize2", CCNode *, m_pTableContainer2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece3", CCLabelTTF *, m_pComonItemPiece3Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece4", CCLabelTTF *, m_pComonItemPiece4Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece5", CCLabelTTF *, m_pComonItemPiece5Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeItem", CCNode *, m_pNodeItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemNumber", CCLabelTTF *, m_pItemNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePiece", CCNode *, m_pNodePiece);
    return true;
}

SEL_MenuHandler MB_LayerListEquip::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerListEquip::onBackClicked);
    return NULL;
}

void MB_LayerListEquip::onBackClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}
SEL_CCControlHandler MB_LayerListEquip::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

void MB_LayerListEquip::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
//    int cellIndex = cell->getIdx();
//    MB_LOG("cell touched at index: %d", cellIndex);
}

CCSize MB_LayerListEquip::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerListEquip::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

        
        if(m_kSubType ==  kListItemTypeEquip)
        {
            MB_ItemData* itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getEquipArray()->objectAtIndex(idx);
            CCNode* pNode = MB_NodeItemUnit::create(m_kSubType, itemData->getItemUID());
            pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
            cell->addChild(pNode);
            
        }
        else
        {
            MB_LayerItemUnionUnit * node = MB_LayerItemUnionUnit::create();
            cell->addChild(node);
            node->setData((MB_ItemData *)MB_ItemMgr::getInstance()->getEquipUnionArray()->objectAtIndex(idx));
            node->setPosition(CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
        }

    
    return cell;
}

unsigned int MB_LayerListEquip::numberOfCellsInTableView(CCTableView *table)
{
    return m_nLength;
}

//void MB_LayerListEquip::onMsgRecv(CCNode* node, SocketResponse* response)
//{
//    assert(response != NULL);
//    
//    //将socket数据读取到序列化结构
//    MB_MsgBuffer* recvPacket = response->getResponseData();
//    
//    //协议号
//    uint16_t Msg = 0;
//    recvPacket->Reset();
//    recvPacket->skipU16();
//    recvPacket->skipU8();
//    recvPacket->readU16(&Msg);
//    
//    switch (Msg) {
//        case SC_PVP_FIGHT:
//            dirty();
//            break;
//            
//        default:
//            break;
//    }
//}


void MB_LayerListEquip::onSaleClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onSaleClicked");
    
    MB_LayerListItemSale* layer = MB_LayerListItemSale::create(kListItemTypeEquipSale);
    pushWindow(layer, true);
}

void MB_LayerListEquip::updateButton()
{
}
void MB_LayerListEquip::refreshCount()
{
    if (m_pLabelItemCount != NULL)
    {
        char* strCount = new char[8];
            sprintf(strCount, "数量%d", m_nLength);
        m_pLabelItemCount->setString(strCount);
        CC_SAFE_DELETE_ARRAY(strCount);
    }
}
void MB_LayerListEquip::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
        case SC_ITEM_COMPOUND:{
        
            uint8_t data8;
            recvPacket->readU8(&data8);
            if(data8 == 1){
                
                uint16_t data16;
                recvPacket->readU16(&data16);
                this->dirty();
                MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data16);
                MB_LayerRewardOne* layer = MB_LayerRewardOne::createPet(kRewardValueTypeItem,templete->getComposeItemID(),1);
                CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
            }

        }
            break;
        default:
            break;
    }
    
}

