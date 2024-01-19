//
//  MB_RefreshShopInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-5.
//
//

#include "MB_RefreshShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_RefreshShopEntry.h"
#include "MB_LayerRefreshShop.h"
#include "MB_NodeRefreshShopUnit.h"
#include "MB_RefreshShopProtocol.h"
#include "MB_LayerShopMain.h"
MB_ResWindow* MB_RefreshShopInterface::createEntryDialog()
{
    MB_RefreshShopEntry* pInstance = new MB_RefreshShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}
MB_RefreshShopInterface::MB_RefreshShopInterface()
{
    m_pDataSource = new MB_RefreshShopDataSource(this);
    m_pTreasureInfo = new MB_TreasureInfo;
    
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_INFO, MB_RefreshShopInterface);
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_NEW_ACTIVITY, MB_RefreshShopInterface);
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_NEW_SHOP, MB_RefreshShopInterface);
    SOCKET_MSG_REGIST(SC_SHOP_REFRESH2, MB_RefreshShopInterface);
}
MB_RefreshShopInterface::~MB_RefreshShopInterface()
{
    CC_SAFE_DELETE(m_pDataSource);
    CC_SAFE_RELEASE_NULL(m_pTreasureInfo);
    
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_INFO);
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_NEW_ACTIVITY);
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_NEW_SHOP);
    SOCKET_MSG_UNREGIST(SC_SHOP_REFRESH2);
}

MB_ResWindow* MB_RefreshShopInterface::createFunctionDialog()
{
    return MB_LayerShopMain::createRefreshShop();
    MB_LayerRefreshShop* layer = MB_LayerRefreshShop::create();
    layer->setDataSource(this);
    return layer;
}

void MB_RefreshShopInterface::onLoadingScene()
{
    
}


void MB_RefreshShopInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_SHOP_TREASURE_INFO:
            recvshop_treasure_info(pRecv);
            break;
        case SC_SHOP_TREASURE_NEW_ACTIVITY:
            recvshop_treasure_new_activity(pRecv);
            break;
        case SC_SHOP_TREASURE_NEW_SHOP:
            recvshop_treasure_new_shop(pRecv);
            break;
        case SC_SHOP_REFRESH2:
            recvshop_refresh2(pRecv);
            break;
        default:
            break;
    }
};

bool MB_RefreshShopInterface::allowShow()
{
    return true;
}

uint16_t MB_RefreshShopInterface::getFunctionType()
{
    return kFunctionRefreshShop;
}
void MB_RefreshShopInterface::sendshop_treasure_info()
{
    SOCKET_REQUEST_START(CS_SHOP_TREASURE_INFO);
    SOCKET_REQUEST_END(CS_SHOP_TREASURE_INFO, NULL);
}

void MB_RefreshShopInterface::sendshop_refresh2()
{
    SOCKET_REQUEST_START(CS_SHOP_REFRESH2);
    SOCKET_REQUEST_END(SC_SHOP_REFRESH2, NULL);
}

void MB_RefreshShopInterface::recvshop_refresh2(MB_MsgBuffer* recvPacket)
{
    char result;
    recvPacket->readU8(&result);
    if(result == 0)
    {
        m_pTreasureInfo->read_refresh_goods2(recvPacket);
    }
}

void MB_RefreshShopInterface::sendshop_treasure_buy(int16_t index)
{
    SOCKET_REQUEST_START(CS_SHOP_TREASURE_BUY);
    packet->writeU8(index);
    SOCKET_REQUEST_END(CS_SHOP_TREASURE_BUY, NULL);
}

void MB_RefreshShopInterface::recvshop_treasure_info(MB_MsgBuffer* recvPacket)
{
    if(m_pTreasureInfo->read(recvPacket)){}
}

void MB_RefreshShopInterface::recvshop_treasure_new_shop(MB_MsgBuffer* recvPacket)
{
    m_pTreasureInfo->read_refresh_goods(recvPacket);
}

void MB_RefreshShopInterface::recvshop_treasure_new_activity(MB_MsgBuffer* recvPacket)
{
    m_pTreasureInfo->read_new_activity(recvPacket);
}






///////////

MB_RefreshShopDataSource::MB_RefreshShopDataSource(MB_RefreshShopInterface* pInterface)
{
//    m_pArray = new CCArray;
    m_pInterface = pInterface;
}

MB_RefreshShopDataSource::~MB_RefreshShopDataSource()
{
//    CC_SAFE_RELEASE_NULL(m_pArray);
}

CCSize MB_RefreshShopDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeRefreshShopUnit::getUnitSize();
}

CCTableViewCell* MB_RefreshShopDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_Treasure* itemData = (MB_Treasure*)m_pInterface->getTreasureInfo()->getTreasures()->objectAtIndex(idx);
    if (itemData != NULL)
    {
        CCNode* pNode = MB_NodeRefreshShopUnit::create(itemData);
        pNode->setPosition( CCPointMake(MB_NodeRefreshShopUnit::getUnitSize().width/2, MB_NodeRefreshShopUnit::getUnitSize().height/2));
        cell->addChild(pNode);
    }
    
    return cell;
}

unsigned int MB_RefreshShopDataSource::numberOfCellsInTableView(CCTableView *table)
{
    if(m_pInterface)
    {
        return m_pInterface->getTreasureInfo()->getTreasures()->count();
    }
    return 0;
}
