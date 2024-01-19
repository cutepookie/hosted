

#include "MB_LayerListItemSale.h"

USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerListItemSale::MB_LayerListItemSale()
{
    m_pTableContainer = NULL;
    m_pTableView = NULL;
    m_pFXCount = NULL;
   // m_pFXCoin = NULL;
    
    m_pArrayCanSale = new CCArray();
    
    SOCKET_MSG_REGIST(SC_ITEM_SELL, MB_LayerListItemSale);
}

MB_LayerListItemSale::~MB_LayerListItemSale()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pFXCount);
  //  CC_SAFE_RELEASE_NULL(m_pFXCoin);
    CC_SAFE_RELEASE_NULL(m_pArrayCanSale);
    
    SOCKET_MSG_UNREGIST(SC_ITEM_SELL);
}

MB_LayerListItemSale* MB_LayerListItemSale::create(int type)
{
    MB_LayerListItemSale* layer = new MB_LayerListItemSale();
    if (layer != NULL && layer->init(type)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListItemSale::init(int type)
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
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/gui_main_itemsale.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    OCandCppHelper::convertScollerViewSuitable(m_pTableContainer); 
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setDelegate(this);
    m_pTableContainer->addChild(tableView);
    tableView->reloadData();
    m_pTableView = tableView;
    
    onResetWnd();
    
	return true;
}

void MB_LayerListItemSale::onResetWnd()
{
    m_pArrayCanSale->removeAllObjects();
    MB_ItemData* itemData = NULL;
    if (m_kSubType == kListItemTypeEquipSale)
    {
        for (int i = 0; i < MB_ItemMgr::getInstance()->getEquipArray()->count(); i++)
        {
            itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getEquipArray()->objectAtIndex(i);
            if (itemData->getItemPetID() != 0)
            {
                continue;
            }
            m_pArrayCanSale->addObject(itemData);
        }
    }
    else if (m_kSubType == kListItemTypeTreasureSale)
    {
        MB_ItemData* itemData = NULL;
        for (int i = 0; i < MB_ItemMgr::getInstance()->getTreasureArray()->count(); i++)
        {
            itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getTreasureArray()->objectAtIndex(i);
            if (itemData->getItemPetID() != 0)
            {
                continue;
            }
            m_pArrayCanSale->addObject(itemData);
        }
    }
    
    refreshCount();
    
    m_pTableView->reloadData();
//    int num = numberOfCellsInTableView(m_pTableView);
//    for (int i = 0; i < num; ++i) {
//        m_pTableView->updateCellAtIndex(i);
//    }
}

bool MB_LayerListItemSale::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
        return true;
    }

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "SelectCount", CCLabelTTF *, m_pFXCount);
   // CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "SliverCost", CCLabelFX *, m_pFXCoin);
    
    return true;
}

SEL_MenuHandler MB_LayerListItemSale::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerListItemSale::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAutoClicked", MB_LayerListItemSale::onAutoClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCommitClicked", MB_LayerListItemSale::onSaleClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerListItemSale::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerListItemSale::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int cellIndex = cell->getIdx();
    MB_LOG("cell touched at index: %d", cellIndex);
}

CCSize MB_LayerListItemSale::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerListItemSale::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

        MB_ItemData* itemData = (MB_ItemData*)m_pArrayCanSale->objectAtIndex(idx);
        CCNode* pNode = MB_NodeItemUnit::create(m_kSubType, itemData->getItemUID());
        pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
        cell->addChild(pNode);

    
    return cell;
}

unsigned int MB_LayerListItemSale::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrayCanSale->count();
}

void MB_LayerListItemSale::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_ITEM_SELL:
            recvitem_sell(recvPacket);
            break;
            
        default:
            break;
    }
}

bool MB_LayerListItemSale::recvitem_sell(MB_MsgBuffer* recvPacket)
{
    uint8_t result;
    if (recvPacket->readU8(&result))
    {
        if (result == 1)
        {
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
            
            MB_LayerRewardMore *layer =  MB_LayerRewardMore::create(array);
            this->pushWindow(layer);

            dirty();
        }
    }
    
    return true;
}

void MB_LayerListItemSale::onCloseClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onCloseClicked");
    MB_ItemData* itemData = NULL;
    for (int i = 0; i < m_pArrayCanSale->count(); i++) {
        itemData = (MB_ItemData*)m_pArrayCanSale->objectAtIndex(i);
        itemData->setReadyForSell(false);

    }
    popWindow(true);
}

void MB_LayerListItemSale::onAutoClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onAutoClicked");
    MB_ItemData* itemData = NULL;
    MB_ItemTemplate* itemTemplete = NULL;
    for (int i = 0; i < m_pArrayCanSale->count(); i++) {
        itemData = (MB_ItemData*)m_pArrayCanSale->objectAtIndex(i);
        itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
        if (itemTemplete->getItemStar() < 3) {
            itemData->setReadyForSell(true);
        }
    }
    
    dirty();
}

void MB_LayerListItemSale::onSaleClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onSaleClicked");
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_ItemMgr::getInstance()->senditem_sell();
}

void MB_LayerListItemSale::refreshCount()
{
    m_nSellCount = 0;
    m_nSellCoin = 0;
    MB_ItemData* itemData = NULL;
    for (int i = 0; i < m_pArrayCanSale->count(); i++) {
        itemData = (MB_ItemData*)m_pArrayCanSale->objectAtIndex(i);
        if (itemData->getReadyForSell()) {
            m_nSellCount++;
            m_nSellCoin += MB_ItemMgr::getInstance()->getItemCostByUID(itemData->getItemUID());
        }
    }
    char* temp = new char[32];
   // sprintf(temp, "%d", m_nSellCoin);
 //   m_pFXCoin->setString(temp);
    sprintf(temp, "%d", m_nSellCount);
    m_pFXCount->setString(temp);
    CC_SAFE_DELETE_ARRAY(temp);
}
