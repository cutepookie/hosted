

#include "MB_LayerListItemEnhance.h"


USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerListItemEnhance::MB_LayerListItemEnhance()
{
    m_pTableContainer = NULL;
    m_pTableView = NULL;

    m_pArrayCanChoose = new CCArray();
    m_bShowRoleInfoPanel = true;
}

MB_LayerListItemEnhance::~MB_LayerListItemEnhance()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pArrayCanChoose);
    
}

MB_LayerListItemEnhance* MB_LayerListItemEnhance::create(uint64_t itemUID)
{
    MB_LayerListItemEnhance* layer = new MB_LayerListItemEnhance();
    if (layer != NULL && layer->init(itemUID)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListItemEnhance::init(uint64_t itemUID)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    setItemUID(itemUID);
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //解析cell的大小
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->readNodeGraphFromFile("res/item_node_unitopen.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    //读取界面
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_layer_list.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    //OCandCppHelper::convertScollerViewSuitable(m_pTableContainer);
    NSGameHelper::adjustScrollNode(m_pTableContainer);
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

void MB_LayerListItemEnhance::onResetWnd()
{
    m_pArrayCanChoose->removeAllObjects();
    MB_ItemData* itemData = NULL;
    MB_ItemData* itemData2 = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    int nStar = (MB_ItemMgr::getInstance()->getItemTemplateByID(itemData2->getItemID()))->getItemStar();
    uint8_t type = itemData2->getItemType();
    for (int i = 0; i < MB_ItemMgr::getInstance()->getItemDataArray()->count(); i++)
    {
        itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getItemDataArray()->objectAtIndex(i);
        int nStar2 = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID())->getItemStar();
        //不是同类道具||是主道具 || 已经装备了 || 星级不同
        if (type != itemData->getItemType() || itemData->getItemUID() == getItemUID() || itemData->getItemPetID() != 0 || nStar != nStar2)
        {
            continue;
        }
        m_pArrayCanChoose->addObject(itemData);
    }
    //排序
    if(m_pArrayCanChoose->count() > 1)
    {
        sortData();
    }
    m_pTableView->reloadData();
}

void MB_LayerListItemEnhance::sortData()
{    
    MB_ItemData *MB_ItemData1,*MB_ItemData2;
    int nDataCount = m_pArrayCanChoose->count();
    //品阶升序
    for(int i = 0;i < nDataCount;++i)
    {
        for (int j = i+1; j < nDataCount; ++j)
        {
            MB_ItemData1 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
            MB_ItemData2 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(j);
            
            if (MB_ItemData1->getItemRank() > MB_ItemData2->getItemRank())
            {
                m_pArrayCanChoose->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //同品阶  等级升序
    for(int i = 0;i < nDataCount;++i)
    {
        for (int j = i+1; j < nDataCount; ++j)
        {
            MB_ItemData1 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
            MB_ItemData2 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(j);
            
            if (MB_ItemData1->getItemRank() != MB_ItemData2->getItemRank())
            {
                break;
            }
            if (MB_ItemData1->getItemLevel() > MB_ItemData2->getItemLevel())
            {
                m_pArrayCanChoose->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
}

bool MB_LayerListItemEnhance::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
        return true;
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_list", CCNode *, m_pTableContainer);
    
    return true;
}

SEL_MenuHandler MB_LayerListItemEnhance::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerListItemEnhance::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerListItemEnhance::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

void MB_LayerListItemEnhance::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int cellIndex = cell->getIdx();
    MB_LOG("cell touched at index: %d", cellIndex);
}

CCSize MB_LayerListItemEnhance::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerListItemEnhance::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    

        MB_ItemData* itemData = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(idx);
        CCNode* pNode = MB_NodeItemUnit::create(kListItemTypeItemEnhance, itemData->getItemUID());
        pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
        cell->addChild(pNode);
    
    
    return cell;
}

unsigned int MB_LayerListItemEnhance::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrayCanChoose->count();
}

void MB_LayerListItemEnhance::onCloseClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onCloseClicked");
    
    popWindow(true);
}
