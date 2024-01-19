

#include "MB_ShopIngots.h"
#include "MB_ShopData.h"
#include "MB_LayerVipInfo.h"
#include "MB_ShopPay.h"
#include "MB_NodeVipDailyReward.h"
#include "MB_IngotsShopInterface.h"
#include "MB_GiftsProtocol.h"
#include "MB_LayerRewardMore.h"
#include "MB_FunctionMgr.h"
MB_ShopIngots::MB_ShopIngots()
{
	SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_ShopIngots);
	SOCKET_MSG_REGIST(RECV_DAILY_VIP_DRAW, MB_ShopIngots);
	SOCKET_MSG_REGIST(RECV_DAILY_VIP_INFO, MB_ShopIngots);
	m_pInterface = NULL;
	m_pNodeVipDes = NULL;
	m_pNodeDailyVipReward = NULL;
	m_pNodeReward = NULL;
	m_bShowRoleInfoPanel = false;
}

bool MB_ShopIngots::init()
{
	MB_ShopPageBase::init();

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode*  node = pCCBReader->readNodeGraphFromFile("res/gui_shop1_2.ccbi", this);

	node->setVisible(true);
	this->addChild(node);
	CC_SAFE_RELEASE_NULL(pCCBReader);
	sDesCommon* pdc;
	pdc = DesTable.getDesCommon("shop_ID.xml", 4);
	m_uShopID = pdc->queryValue("shopid").toInt();
	MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionIngotsShop, (CCFunctionInterface**)&m_pInterface);
	m_pNodeReward = MB_NodeVipDailyReward::create();
	if (m_pNodeReward)
	{
		m_pNodeDailyVipReward->removeAllChildren();
		m_pNodeDailyVipReward->addChild(m_pNodeReward);
		if (m_pInterface)
		{
			m_pNodeReward->setMailReward(m_pInterface->getReward());
			m_pNodeReward->setReceiveEnable(!m_pInterface->getReceived());
		}
	}

#ifdef OPEN_PAY
	m_pNodeVipDes->setVisible(true);
#else
	m_pNodeVipDes->setVisible(false);
#endif
	return true;
}

MB_ShopIngots* MB_ShopIngots::create()
{
	MB_ShopIngots* layer = new MB_ShopIngots();
	if (layer)
	{
		layer->init();
		layer->autorelease();
		layer->onResetWnd();
		return layer;
	}
	CC_SAFE_RELEASE_NULL(layer);
	return NULL;
}

MB_ShopIngots::~MB_ShopIngots()
{
	SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
	SOCKET_MSG_UNREGIST(RECV_DAILY_VIP_DRAW);
	SOCKET_MSG_UNREGIST(RECV_DAILY_VIP_INFO);
	CC_SAFE_RELEASE_NULL(m_pNodeVipDes);
	CC_SAFE_RELEASE_NULL(m_pNodeDailyVipReward);
	CC_SAFE_RELEASE_NULL(m_pPageNode);
	CC_SAFE_RELEASE_NULL(m_pPanel);
}

bool MB_ShopIngots::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget,
	const char *pMemberVariableName,
	cocos2d::CCNode *pNode)
{

	if (MB_ShopPageBase::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
	{
		return true;
	}

	if (0 == strcmp("shopPage4", pMemberVariableName))
	{
		m_Pos = pNode->getPosition();
	}

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopIngotsPanel", CCNode *, m_pPanel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopPage4", CCNode *, m_pPageNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeVipDes", CCNode*, m_pNodeVipDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeDailyVipReward", CCNode*, m_pNodeDailyVipReward);

	return false;
}

SEL_MenuHandler MB_ShopIngots::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

//礼包商店，数据来自配置，需要根据购买次数等信息筛选显示
void MB_ShopIngots::onResetWnd()
{
	MB_ShopPageBase::onResetWnd();

	m_nListLength = 0;
	CCObject *objet;
	int index = 1;
	m_pArray->removeAllObjects();
	CCARRAY_FOREACH(m_pShopInfo->getShopGoodsArray(), objet)
	{
		MB_ShopGoodsItem *data = (MB_ShopGoodsItem *)objet;

		//可以购买，vip等级相差3级的显示
		if (data->getRealBuyNum() < data->getBuyNum() && MB_RoleData::getInstance()->getVipLevel() >= (data->getVipLimit() - 3))
		{
			m_nListLength++;
			m_pArray->addObject(objet);
		}
		index++;
	}

	m_pTableView->reloadData();//重新更新界面
}
CCSize MB_ShopIngots::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}
CCTableViewCell* MB_ShopIngots::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

	MB_ShopGoodsItem *node = (MB_ShopGoodsItem*)m_pArray->objectAtIndex(idx);
	MB_VIPShopSubItem* pSubItem = MB_VIPShopSubItem::create(m_uShopID, node);
	pSubItem->showBuy10(false);
	pSubItem->setPosition(CCPointMake(m_cellSize.width / 2, m_cellSize.height / 2));
	cell->addChild(pSubItem);
	return cell;
}

unsigned int MB_ShopIngots::numberOfCellsInTableView(CCTableView *table)
{
	return m_pArray->count();
}


void  MB_ShopIngots::onMsgRecv(CCNode*    node, SocketResponse* response){

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
	case SC_SHOP_BUY:
	{
						uint8_t result;
						recvPacket->readU8(&result);
						if (result == kmShopBuy_Result_Success)
						{
							this->onResetWnd();
						}
	}
		break;
	case RECV_DAILY_VIP_INFO:
		if (m_pInterface)
		{
			m_pNodeReward->setMailReward(m_pInterface->getReward());
			m_pNodeReward->setReceiveEnable(!m_pInterface->getReceived());
		}
		break;
	case RECV_DAILY_VIP_DRAW:
		if (m_pInterface)
		{
			MB_Message::sharedMB_Message()->removeALLMessage();
			if (m_pInterface->getReceived())
			{
				m_pNodeReward->setReceiveEnable(false);
				MB_LayerRewardMore* p = MB_LayerRewardMore::create(m_pInterface->getReward()->converIDNUM2RewardTempleteValue());
				if (p)
				{
					p->setShowRoleInfoPanel(false);
					pushWindow(p);
				}
			}
		}
		break;
	}
}
