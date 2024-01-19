//
//  MB_LayerListOther.cpp
//  ProjectTK
//
//

#include "MB_LayerListOther.h"
#include "MB_LayerShowPic.h"
//#include "MB_LayerSale.h"
#include "MB_FunctionModule.h"
#include "MB_ParsingReward.h"
#include <algorithm>
#include "Game.h"
USING_NS_CC;
USING_NS_CC_EXT;


MB_LayerListOther::MB_LayerListOther()
{
    m_pTableContainer = NULL;
    m_pTableView = NULL;
    m_pFXCount = NULL;
    SOCKET_MSG_REGIST(SC_BOX_ITEM, MB_LayerListOther);
    SOCKET_MSG_REGIST(SC_ITEM_USE, MB_LayerListOther);
    SOCKET_MSG_REGIST(SC_COMBINE_GER, MB_LayerListOther);
    SOCKET_MSG_REGIST(SC_COMBINE_EQUIP, MB_LayerListOther);
    SOCKET_MSG_REGIST(SC_ITEM_UPDATE, MB_LayerListOther);
    m_bShowRoleInfoPanel = true;
}

MB_LayerListOther::~MB_LayerListOther()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pFXCount);
    
    SOCKET_MSG_UNREGIST(SC_BOX_ITEM);
    SOCKET_MSG_UNREGIST(SC_ITEM_USE);
    SOCKET_MSG_UNREGIST(SC_COMBINE_GER);
    SOCKET_MSG_UNREGIST(SC_COMBINE_EQUIP);
    SOCKET_MSG_UNREGIST(SC_ITEM_UPDATE);
}

MB_LayerListOther* MB_LayerListOther::create()
{
    MB_LayerListOther* layer = new MB_LayerListOther();
    if (layer != NULL && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListOther::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //解析cell的大小
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->readNodeGraphFromFile("res/item_node_unitopen.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
//    m_cellSizeFormula = MB_NodeSaleUnit::getCellSize();
    //读取界面
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_layer_list3.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    //OCandCppHelper::convertScollerViewSuitable(m_pTableContainer);
    NSGameHelper::adjustScrollNode(m_pTableContainer);
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setDelegate(this);
    m_pTableContainer->addChild(tableView);
    //tableView->reloadData();
    m_pTableView = tableView;
    
    onResetWnd();
    onItemPageClicked(NULL);
	return true;
}

void MB_LayerListOther::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}

/*星级升序>品阶升序>ID升序*/
bool MB_LayerListOther::sortFunction(MB_ItemData* first,MB_ItemData* second)
{
    //星级降序
    if(first->getTemplateStar() > second->getTemplateStar())
    {
        return true;
    }
    else if(first->getTemplateStar() < second->getTemplateStar())
    {
        return false;
    }
    
    //等级降序
    if (first->getItemLevel() > second->getItemLevel())
    {
        return true;
    }
    else if(first->getItemLevel() < second->getItemLevel())
    {
        return false;
    }
    
    //品阶降序
    if (first->getItemRank() > second->getItemRank())
    {
        return true;
    }
    else if(first->getItemRank() < second->getItemRank())
    {
        return false;
    }
    
    if (first->getItemUID() > second->getItemUID())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool MB_LayerListOther::sortFormulaArray(const CCArray* pArray,std::vector<MB_ItemData*>& result)
{
    CCArray* pTemp = const_cast<CCArray*>(pArray);
    
    if (pTemp == NULL)
    {
        return true;
    }
    
    int count = pTemp->count();
    MB_ItemData* pItem = NULL;
    for (int i=0; i<count; ++i)
    {
        pItem = dynamic_cast<MB_ItemData*>(pTemp->objectAtIndex(i));
        result.push_back(pItem);
    }
    
    std::sort(result.begin(), result.end(),sortFunction);
    
    return true;
}


void MB_LayerListOther::onResetWnd()
{
    refreshCount();

    
    if(m_nCurPage == kPageFormula)
    {
        m_pSortFormulas.clear();
        sortFormulaArray(MB_ItemMgr::getInstance()->getItemFormulaArray(), m_pSortFormulas);
    }
//    CCPoint pos = m_pTableView->getContentOffset();
    MB_ItemMgr::getInstance()->sortOtherArray();
    m_pTableView->reloadData();
    
//    //整个框显示不完的情况才保留offset
//    if (MB_ItemMgr::getInstance()->getOtherArray()->count() * m_cellSize.height > m_pTableContainer->getContentSize().height) {
//        
//        m_pTableView->setContentOffset(pos);
//    }
}

bool MB_LayerListOther::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }

    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSizeItem = pNode->getContentSize();
        return true;
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ItemCount", CCLabelTTF *, m_pFXCount);
    

    return true;
}

void MB_LayerListOther::onItemPageClicked(CCObject*)
{
    m_nCurPage = kPageItem;
    onResetWnd();
}


SEL_MenuHandler MB_LayerListOther::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerListOther::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerListOther::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}


void MB_LayerListOther::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int cellIndex = cell->getIdx();
    MB_LOG("cell touched at index: %d", cellIndex);
}

CCSize MB_LayerListOther::cellSizeForTable(CCTableView *table)
{
    if(m_nCurPage == kPageItem)
    {
        return m_cellSizeItem;
    }
    else
    {
        return m_cellSizeFormula;
    }
}

CCTableViewCell* MB_LayerListOther::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    
        if(m_nCurPage == kPageItem)
        {
            MB_ItemData* itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getOtherArray()->objectAtIndex(idx);
            if (itemData != NULL)
            {
                CCNode* pNode = MB_NodeItemUnit::create(kListItemTypeOther, itemData->getItemUID());
                pNode->setPosition( CCPointMake(m_cellSizeItem.width/2, m_cellSizeItem.height/2));
                cell->addChild(pNode);
            }
        }
    return cell;
}

unsigned int MB_LayerListOther::numberOfCellsInTableView(CCTableView *table)
{
    if(m_nCurPage == kPageItem)
    {
        return MB_ItemMgr::getInstance()->getOtherArray()->count();
    }
    else
    {
        return MB_ItemMgr::getInstance()->getItemFormulaArray()->count();
    }
}

void MB_LayerListOther::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_BOX_ITEM:
        {
            int result = 0;
            if (recvPacket->readU8(&result))
            {
                if (result == 1)//成功
                {
                    MB_ParsingReward* pRward = MB_ParsingReward::create(recvPacket);
                    CCArray* pArray = pRward->getRewardArray();
                    if(pArray->count() == 1)
                    {
                        RewardTempleteValue* rewardValue = dynamic_cast<RewardTempleteValue*>(pArray->objectAtIndex(0));
                        if (rewardValue != NULL)
                        {
                            MB_LayerRewardOne* rewardOne = MB_LayerRewardOne::create(rewardValue->getType(), rewardValue->getValueID(), rewardValue->getNumber());
                            rewardOne->setShareType(kShareTypeListBox);
                            CCDirector::sharedDirector()->getRunningScene()->addChild(rewardOne,Z_ORDER_OUTSHOW);
                        }
                    }
                    else if(pArray->count() > 1)
                    {
                        MB_LayerRewardMore2* rewardMore = MB_LayerRewardMore2::create(pArray);
                        if(rewardMore != NULL)
                        {
                            CCDirector::sharedDirector()->getRunningScene()->addChild(rewardMore,Z_ORDER_OUTSHOW);
//                            pushWindow(rewardMore);
                        }
                    }
                    this->onResetWnd();
                }
                else if (result == 2) {
                    MB_Message::sharedMB_Message()->showMessage("开启失败, 道具不足.");
                }
                else //失败,未知原因
                {
                    MB_Message::sharedMB_Message()->showMessage("开启失败!");
                }
            }
            onResetWnd();
        }
            break;
        case SC_ITEM_USE:
        case SC_COMBINE_GER:
        case SC_COMBINE_EQUIP:
        case SC_ITEM_UPDATE:
        {
            onResetWnd();
        }
            break;
        default:
            break;
    }
}

void MB_LayerListOther::refreshCount()
{

    char* temp = new char[32];
    sprintf(temp, "%d", MB_ItemMgr::getInstance()->getOtherArray()->count());
    m_pFXCount->setString(temp);
    CC_SAFE_DELETE_ARRAY(temp);
}


void MB_LayerListOther::onComposeSuccessed(MB_ResWindow* pRewardWnd,MB_ResWindow* pSender)
{
    pSender->popWindow();
    addChild(pRewardWnd);
    onResetWnd();
}
