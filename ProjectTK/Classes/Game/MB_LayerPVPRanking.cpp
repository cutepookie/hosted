//
//  MB_LayerPVPRanking.cpp
//  ProjectTK
//
//
//

#include "MB_LayerPVPRanking.h"
#include "MB_NodePVPInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;

//pvp排行逻辑功能类
MB_LayerPVPRanking::MB_LayerPVPRanking()
{
    m_pTableView = NULL;
    SOCKET_MSG_REGIST(SC_PVP_FIGHT, MB_LayerPVPRanking);
    SOCKET_MSG_REGIST(SC_PVP_GET_LIST, MB_LayerPVPRanking);

}

MB_LayerPVPRanking::~MB_LayerPVPRanking()
{
    m_pTableView->removeFromParent();
    SOCKET_MSG_UNREGIST(SC_PVP_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_PVP_FIGHT);

}

MB_LayerPVPRanking* MB_LayerPVPRanking::create(const CCSize& sz)
{
    MB_LayerPVPRanking* pLayerPVPRanking = new MB_LayerPVPRanking();
    if (pLayerPVPRanking != NULL && pLayerPVPRanking->init(sz)) {
        pLayerPVPRanking->autorelease();
        return pLayerPVPRanking;
    }
    CC_SAFE_DELETE(pLayerPVPRanking);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerPVPRanking::init(const CCSize& sz)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->readNodeGraphFromFile("res/arena_node_pvpunit.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);

    
    CCTableView* tableView = CCTableView::create(this, sz);
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setDelegate(this);
    this->addChild(tableView);
    m_pTableView = tableView;
    
    //offset 跳转
    MB_DataPVPRank* dataPVPRank = NULL;
    for (int i = 0; i < MB_DataPVPMgr::getInstance()->getPVPRankArray()->count(); i++)
    {
        dataPVPRank = (MB_DataPVPRank*)MB_DataPVPMgr::getInstance()->getPVPRankArray()->objectAtIndex(i);
        if (dataPVPRank->getCanFight()) {
            CCPoint offset = m_pTableView->getContentOffset();
            offset.y += i * m_cellSize.height;
            m_pTableView->setContentOffset(offset);
            break;
        }
    }
    MB_DataPVPMgr::getInstance()->sendpvp_get_list();
	return true;
}
void MB_LayerPVPRanking::setScrollSize(const CCSize& sz)
{
    m_pTableView->setViewSize(sz);
}
void MB_LayerPVPRanking::onResetWnd()
{
    m_pTableView->reloadData();
    
    //offset 跳转
    MB_DataPVPRank* dataPVPRank = NULL;
    for (int i = 0; i < MB_DataPVPMgr::getInstance()->getPVPRankArray()->count(); i++)
    {
        dataPVPRank = (MB_DataPVPRank*)MB_DataPVPMgr::getInstance()->getPVPRankArray()->objectAtIndex(i);
        if (dataPVPRank->getCanFight()) {
            CCPoint offset = m_pTableView->getContentOffset();
            offset.y += i * m_cellSize.height;
            m_pTableView->setContentOffset(offset);
            break;
        }
    }
}

bool MB_LayerPVPRanking::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
        return true;
    }
    
    
    return true;
}

SEL_MenuHandler MB_LayerPVPRanking::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_LayerPVPRanking::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
void MB_LayerPVPRanking::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    MB_LOG("onNodeLoaded succeed!");
}

void MB_LayerPVPRanking::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}

CCSize MB_LayerPVPRanking::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_LayerPVPRanking::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_DataPVPRank* dataPVPRank = (MB_DataPVPRank*)MB_DataPVPMgr::getInstance()->getPVPRankArray()->objectAtIndex(idx);
    bool bShowTutorial = false;
    if( dataPVPRank->getCanFight())
    {
        bShowTutorial = true;
    }
    MB_NodePVPInfo* nodeInfo = MB_NodePVPInfo::create(dataPVPRank,bShowTutorial);
    nodeInfo->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
    cell->addChild(nodeInfo);
    
    
    return cell;
}

unsigned int MB_LayerPVPRanking::numberOfCellsInTableView(CCTableView *table)
{
    return MB_DataPVPMgr::getInstance()->getPVPRankArray()->count();
}

void MB_LayerPVPRanking::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_PVP_FIGHT:
            dirty();
            break;
        case SC_PVP_GET_LIST:
            dirty();
            break;
        default:
            break;
    }
}

void MB_LayerPVPRanking::refreshRestCount()
{
    
}
