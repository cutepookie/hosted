//
//  MB_LayerRechargeItemList.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-6.
//
//

#include "MB_LayerRechargeItemList.h"
#include "MB_ItemData.h"
#include "MB_NodeItemBuchong.h"

MB_LayerRechargeItemList::MB_LayerRechargeItemList()
{
    SOCKET_MSG_REGIST(SC_ITEM_USE, MB_LayerRechargeItemList);
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = true;
}

MB_LayerRechargeItemList::~MB_LayerRechargeItemList()
{
    SOCKET_MSG_UNREGIST(SC_ITEM_USE);
}

void MB_LayerRechargeItemList::onResetWnd()
{
    if (m_pTableView)
    {
        m_pTableView->reloadData();
    }
}

bool MB_LayerRechargeItemList::init()
{
    if(!MB_LayerItemList::init())
    {
        return false;
    }
    
    CC_SAFE_RELEASE_NULL(m_pTableView);
    m_pNodeContainer->removeAllChildren();
    NSGameHelper::adjustScrollNode(m_pNodeContainer);
    m_pTableView = CCTableView::create(this, m_pNodeContainer->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pNodeContainer->addChild(m_pTableView);
    m_CellSize = MB_NodeItemBuchong::getNodeSize();
    return true;
}



void MB_LayerRechargeItemList::onMsgRecv(CCNode* node, SocketResponse* response)
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
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (Msg)
    {
        case SC_ITEM_USE:
            onResetWnd();
            break;
        default:
            break;
    }

}

CCSize MB_LayerRechargeItemList::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerRechargeItemList::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_vContainer[idx]);
    if (itemData != NULL)
    {
        CCNode* pNode = MB_NodeItemBuchong::create(itemData->getItemUID());
        pNode->setPosition( CCPointMake(m_CellSize.width/2, m_CellSize.height/2));
        cell->addChild(pNode);
    }

    return cell;
}

unsigned int MB_LayerRechargeItemList::numberOfCellsInTableView(CCTableView *table)
{
    return m_vContainer.size();
}
