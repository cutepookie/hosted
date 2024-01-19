

#include "MB_LayerListTreasure.h"
#include "MB_LayerListItemSale.h"

USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerListTreasure::MB_LayerListTreasure()
{
    m_pTableContainer = NULL;
    m_pTableView = NULL;
  // m_pNodeSale = NULL;
    m_pLabelItemCount = NULL;
    m_pButtonTreasure = NULL;
    m_pButtonPiece = NULL;
    m_pNodePiece = NULL;
}

MB_LayerListTreasure::~MB_LayerListTreasure()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
  //  CC_SAFE_RELEASE_NULL(m_pNodeSale);
    CC_SAFE_RELEASE_NULL(m_pLabelItemCount);
    CC_SAFE_RELEASE_NULL(m_pButtonTreasure);
    CC_SAFE_RELEASE_NULL(m_pButtonPiece);
    CC_SAFE_RELEASE_NULL(m_pNodePiece);
}

MB_LayerListTreasure* MB_LayerListTreasure::create(int type)
{
    MB_LayerListTreasure* layer = new MB_LayerListTreasure();
    if (layer != NULL && layer->init(type)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListTreasure::init(int type)
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
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_layer_list2.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    //OCandCppHelper::convertScollerViewSuitable(m_pTableContainer);
    
    NSGameHelper::adjustScrollNode(m_pTableContainer);
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setDelegate(this);
    m_pTableContainer->addChild(tableView);
    //    tableView->reloadData();
    m_pTableView = tableView;
    
    m_pButtonTreasure->setIsScale(false);
    m_pButtonPiece->setIsScale(false);
    onResetWnd();
    
    onTreasureClicked(NULL);
    
	return true;
}

void MB_LayerListTreasure::onResetWnd()
{
    m_pTableView->reloadData();
    
    refreshCount();
    
    //button显示判断
    //    if (m_kSubType == kListItemTypeEquipUp) {
    //        m_pBtPiece->setVisible(false);
    //        m_pNodeSale->setVisible(false);
    //    }
    //    //button高亮更新
    //    updateButton();
}

bool MB_LayerListTreasure::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
        return true;
    }
    
   // CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sale", CCNode*, m_pNodeSale);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ItemCount", CCLabelTTF*, m_pLabelItemCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "SubItemPositionSign", CCNode *, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btTreasure", CCMenuItemImage *, m_pButtonTreasure);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btPiece", CCMenuItemImage *, m_pButtonPiece);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodePiece", CCNode *, m_pNodePiece);
    
    return true;
}

SEL_MenuHandler MB_LayerListTreasure::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSaleClicked", MB_LayerListTreasure::onSaleClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTreasureClicked", MB_LayerListTreasure::onTreasureClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPieceClicked", MB_LayerListTreasure::onPieceClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPVPTreasureClicked", MB_LayerListTreasure::onPVPTreasureClicked);
    
    return NULL;
}
SEL_CCControlHandler MB_LayerListTreasure::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerListTreasure::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int cellIndex = cell->getIdx();
    MB_LOG("cell touched at index: %d", cellIndex);
}

CCSize MB_LayerListTreasure::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerListTreasure::tableCellAtIndex(CCTableView *table, unsigned int idx)
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


        MB_ItemData* itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getTreasureArray()->objectAtIndex(idx);
        CCNode* pNode = MB_NodeItemUnit::create(m_kSubType, itemData->getItemUID());
        pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
        cell->addChild(pNode);
    
    
    return cell;
}

unsigned int MB_LayerListTreasure::numberOfCellsInTableView(CCTableView *table)
{
    return MB_ItemMgr::getInstance()->getTreasureArray()->count();
}

//void MB_LayerListTreasure::onMsgRecv(CCNode* node, SocketResponse* response)
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

void MB_LayerListTreasure::onSaleClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onSaleClicked");
    MB_LayerListItemSale* layer = MB_LayerListItemSale::create(kListItemTypeTreasureSale);
    pushWindow(layer, true);
}

void MB_LayerListTreasure::onTreasureClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onTreasureClicked");
    
    m_pButtonPiece->unselected();
    m_pButtonTreasure->selected();
    m_pNodePiece->setVisible(false);
    m_pTableView->setVisible(true);
    //m_pNodeSale->setVisible(true);
    
}

void MB_LayerListTreasure::onPVPTreasureClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onPVPTreasureClicked");
    if(MB_RoleData::getInstance()->getLevel() < MB_RoleData::getInstance()->getRolePlunderLimit()){
        
        char databuf[40];
        sprintf(databuf, "此功能%d级开放",MB_RoleData::getInstance()->getRolePlunderLimit());
        MB_Message::sharedMB_Message()->showMessage(databuf);
        return;
    }
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    
    if (pScene != NULL) {
        pScene->enterLayer(kSceneMainLayerTypePVP, kSubLayerTypeTreasure);
    }
}

void MB_LayerListTreasure::onPieceClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onPieceClicked");
    
    m_pButtonPiece->selected();
    m_pButtonTreasure->unselected();
    m_pNodePiece->setVisible(true);
    //m_pNodeSale->setVisible(false);
    m_pTableView->setVisible(false);
}

void MB_LayerListTreasure::refreshCount()
{
    if (m_pLabelItemCount != NULL)
    {
        char* strCount = new char[8];
        sprintf(strCount, "%d/100", MB_ItemMgr::getInstance()->getTreasureArray()->count());
        m_pLabelItemCount->setString(strCount);
        CC_SAFE_DELETE_ARRAY(strCount);
    }
}
