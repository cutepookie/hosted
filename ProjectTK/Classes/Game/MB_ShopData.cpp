
#include "MB_ShopData.h"
#include "MB_CommonType.h"


MB_ShopGoodsItem::MB_ShopGoodsItem()
{
    m_nVipLimit = 0;
    m_nRealBuyNum = 0;
    m_pRewardArray = new CCArray();
}

MB_ShopGoodsItem::~MB_ShopGoodsItem()
{
    CC_SAFE_RELEASE(m_pRewardArray);
}



MB_ShopInfo::MB_ShopInfo()
{
    m_pShopGoodsArray = new CCArray();
}

MB_ShopInfo::~MB_ShopInfo()
{
    CC_SAFE_RELEASE(m_pShopGoodsArray);
}



//新的商店数据管理,逐渐会替换老的

static MB_ShopMgr* s_pShopMgr = NULL;

MB_ShopMgr::MB_ShopMgr()
{
    m_pShopBoxTempleteArray = new CCArray();
//    m_pRewardArrayDisplay = new CCArray();
    m_pShopGoodsTempleteArray = new CCArray();
    m_pShopDataTempleteArray = new CCArray();
    
    SOCKET_MSG_REGIST(SC_BOX_ITEM, MB_ShopMgr);
    SOCKET_MSG_REGIST(SC_BOX_SHOP, MB_ShopMgr);
    SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_ShopMgr);
    SOCKET_MSG_REGIST(SC_SHOP_BUY_NUM, MB_ShopMgr);
    SOCKET_MSG_REGIST(SC_BOX_SHOP_INFO, MB_ShopMgr);

    SOCKET_MSG_REGIST(SC_SHOP_REFRESH,MB_ShopMgr);//神秘商店
    SOCKET_MSG_REGIST(SC_SHOP_ENCOUNTER,MB_ShopMgr);
    SOCKET_MSG_REGIST(SC_SHOP_AUTO_REFRESH,MB_ShopMgr);
    
    SOCKET_MSG_REGIST(SC_BOX_GET_SPRIT_EQUIP_COUNT,MB_ShopMgr);
    
    if (!initShopGoods()) {
        MB_LOG("initShopGoods failed.");
    }
    
    if (!initShopData()) {
        MB_LOG("initShopData failed.");
    }
    initShowCard();
}

MB_ShopMgr::~MB_ShopMgr()
{
    CC_SAFE_RELEASE_NULL(m_pShopBoxTempleteArray);
//    CC_SAFE_RELEASE_NULL(m_pRewardArrayDisplay);
    CC_SAFE_RELEASE(m_pShopGoodsTempleteArray);
    CC_SAFE_RELEASE(m_pShopDataTempleteArray);

    
   // CC_SAFE_RELEASE(m_pMysteryShop);//神秘商店
    
    SOCKET_MSG_UNREGIST(SC_BOX_ITEM);
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP);
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY_NUM);
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP_INFO);
    
    SOCKET_MSG_UNREGIST(SC_SHOP_REFRESH);//神秘商店
    SOCKET_MSG_UNREGIST(SC_SHOP_ENCOUNTER);
    SOCKET_MSG_UNREGIST(SC_SHOP_AUTO_REFRESH);
    SOCKET_MSG_UNREGIST(SC_BOX_GET_SPRIT_EQUIP_COUNT);
    
    m_vShowCard.clear();
}

void MB_ShopMgr::initShowCard()
{
    MB_XmlFile* pXml = MB_XmlFile::create("config/ShowCard.xml");
    if (pXml == NULL)
    {
        return;
    }
    m_vShowCard.clear();
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("ShowCard", pArray))
    {
        return;
    }
    MB_XmlNode* pRoot = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
    MB_XmlNode* pTemp = NULL;
    
    pArray->removeAllObjects();
    pRoot->queryNodesByName("CardIDs|CardID", pArray);
    
    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
    {
        int id = pTemp->queryAttributeByName("ID")->intValue();
        m_vShowCard.push_back(id);
    }
    

}
MB_ShopMgr* MB_ShopMgr::getInstance()
{
    if (s_pShopMgr == NULL) {
        s_pShopMgr = new MB_ShopMgr();
    }
    return s_pShopMgr;
}

void MB_ShopMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pShopMgr);
    s_pShopMgr = NULL;
}


bool MB_ShopMgr::initShopGoods()
{
    //清空
    m_pShopGoodsTempleteArray->removeAllObjects();
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/shop/goods.xml");
    
    if (g_sharedDoc == NULL) {
        return false;
    }
    
    
    
    xmlNodePtr root;
    
    root = xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char*               value;
    while(curNode)
    {
        if (xmlStrcmp(curNode->name,BAD_CAST "GoodsItem"))
        {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL)
        {
            MB_ShopGoodsItem* pShopGoodsItem = new MB_ShopGoodsItem();
            pShopGoodsItem->setRealBuyNum(0);
            
            if (!xmlStrcmp(attr->name,BAD_CAST "GoodsID"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setGoodsID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "GoodsName"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "GoodsDescription"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
//                printf(value);
                pShopGoodsItem->setDesc(value);
                CC_SAFE_FREE(value);
                attr = attr->next;

            }
            if (!xmlStrcmp(attr->name,BAD_CAST "GoodsIcon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setIcon(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "Star"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setStar(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "BuyNum"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setBuyNum(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "MoneyType"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setCoinType(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "Price"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setPrice(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (!xmlStrcmp(attr->name,BAD_CAST "needVipLevel"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopGoodsItem->setVipLimit(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            //解析reward部分
            xmlNodePtr children = curNode->xmlChildrenNode;
            
            while (children)
            {
                attr = children->properties;
                
                if(attr)
                {
                    MB_ShopGoodsReward* pShopGoodsReward = new MB_ShopGoodsReward();
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "RewardType"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        pShopGoodsReward->setRewardType(atoi(value));
                        CC_SAFE_FREE(value);
                        attr = attr->next;
                    }
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "RewardValue"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        pShopGoodsReward->setRewardValue(atoi(value));
                        CC_SAFE_FREE(value);
                        attr = attr->next;
                    }
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "BuyNumOnce"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        pShopGoodsReward->setBuyNumOnce(atoi(value));
                        CC_SAFE_FREE(value);
                        attr = attr->next;
                    }
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "level"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        pShopGoodsReward->setLevel(atoi(value));
                        CC_SAFE_FREE(value);
                        attr = attr->next;
                    }
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "Ranking"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        pShopGoodsReward->setRanking(atoi(value));
                        CC_SAFE_FREE(value);
                    }
                    pShopGoodsItem->getRewardArray()->addObject(pShopGoodsReward);
                    pShopGoodsReward->release();
                }
                children = children->next;
            }
            
            m_pShopGoodsTempleteArray->addObject(pShopGoodsItem);
            pShopGoodsItem->release();
        }
        
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

bool MB_ShopMgr::initShopData()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/shop/shop.xml");
    
    if (g_sharedDoc == NULL) {
        return false;
    }
    
    xmlNodePtr root;
    
    root = xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char*               value;
    while(curNode)
    {
        if (xmlStrcmp(curNode->name,BAD_CAST "ShopItem"))
        {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL)
        {
            MB_ShopInfo* pShopInfo = new MB_ShopInfo();

            if (!xmlStrcmp(attr->name,BAD_CAST "ShopId"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopInfo->setShopID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (!xmlStrcmp(attr->name,BAD_CAST "ShopName"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                pShopInfo->setShopName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            xmlNodePtr children = curNode->xmlChildrenNode;
            
            while (children)
            {
                if (xmlStrcmp(children->name,BAD_CAST "GoodsID"))
                {
                    children = children->next;
                    continue;
                }
                
                value = (char*)xmlNodeGetContent(children->children);
                MB_ShopGoodsItem* pShopGoodsItem = getShopGoodsItemByID(atoi(value));
                pShopInfo->getShopGoodsArray()->addObject(pShopGoodsItem);
                CC_SAFE_FREE(value);
                children = children->next;
            }
            
            m_pShopDataTempleteArray->addObject(pShopInfo);
            pShopInfo->release();
        }
        
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
    
    //创建神秘商店
    MB_MysterShopInfo* pMysteryShopinfo = new MB_MysterShopInfo();
    pMysteryShopinfo->setShopID(MYSTERY_SHOP_ID);
    pMysteryShopinfo->setShopName("宝石商店");
    m_pShopDataTempleteArray->addObject(pMysteryShopinfo);
    pMysteryShopinfo->release();
    
    return true;
}

MB_ShopInfo* MB_ShopMgr::getShopInfoByID(uint16_t shopID)
{
    for (int i = 0; i < m_pShopDataTempleteArray->count(); ++i)
    {
        MB_ShopInfo* pShopInfo = (MB_ShopInfo*)m_pShopDataTempleteArray->objectAtIndex(i);
        if (pShopInfo->getShopID() == shopID) {
            return pShopInfo;
        }
    }
    return NULL;
}

MB_ShopGoodsItem* MB_ShopMgr::getShopGoodsItemByID(uint16_t goodsID)
{
    for (int i = 0; i < m_pShopGoodsTempleteArray->count(); ++i)
    {
        MB_ShopGoodsItem* obj = (MB_ShopGoodsItem*)m_pShopGoodsTempleteArray->objectAtIndex(i);
        if (obj->getGoodsID() == goodsID) {
            return obj;
        }
    }
    MB_LOG("can't find goods id: %u", goodsID);
    return NULL;
}

MB_ShopGoodsItem* MB_ShopMgr::getShopGoodsItemInShop(uint16_t shopID, uint16_t goodsID)
{
    MB_ShopInfo* pShopInfo = NULL;
    CCArray* pGoodsArray = NULL;
    MB_ShopGoodsItem* pShopGoodsItem = NULL;
    for (int i = 0; i < m_pShopDataTempleteArray->count(); ++i)
    {
        pShopInfo = (MB_ShopInfo*)m_pShopDataTempleteArray->objectAtIndex(i);
        if (pShopInfo->getShopID() == shopID)
        {
            pGoodsArray = pShopInfo->getShopGoodsArray();
            break;
        }
    }
    
    if (pGoodsArray != NULL)
    {
        for (int j = 0; j < pGoodsArray->count(); ++j)
        {
            pShopGoodsItem = (MB_ShopGoodsItem*)pGoodsArray->objectAtIndex(j);
            if (pShopGoodsItem->getGoodsID() == goodsID)
            {
                return pShopGoodsItem;
            }
        }
    }
    
    MB_LOG("can't find Goods:%d in Shop:%d\n",goodsID, shopID);
    return NULL;
}

void MB_ShopMgr::updateShopGoodsRealNum(uint16_t shopID, uint16_t goodsID, int realNum)
{
    MB_ShopGoodsItem* pGoods = getShopGoodsItemInShop(shopID, goodsID);
    if (pGoods != NULL)
    {
        pGoods->setRealBuyNum(realNum);
    }
}

void MB_ShopMgr::autoAddShopGoodsRealNum(uint16_t shopID, uint16_t goodsID)
{
    MB_ShopGoodsItem* pGoods = getShopGoodsItemInShop(shopID, goodsID);
    if (pGoods != NULL)
    {
        pGoods->setRealBuyNum(pGoods->getRealBuyNum() + 1);
    }
}

bool MB_ShopMgr::shopGoodsCanBuy(uint16_t shopID, uint16_t goodsID)
{
    MB_ShopGoodsItem* pGoods = getShopGoodsItemInShop(shopID, goodsID);
    if (pGoods) {
        if (pGoods->getBuyNum() == -1 || pGoods->getRealBuyNum() < pGoods->getBuyNum()) {
            return true;
        }
    }

    return false;
}

int MB_ShopMgr::getShopCanBuyCount(int type)
{
    int count = 0;
    sDesCommon* pdc;
    pdc = DesTable.getDesCommon("shop_ID.xml",type);
    int shopID = pdc->queryValue("shopid").toInt();
    MB_ShopInfo* shopInfo = MB_ShopMgr::getInstance()->getShopInfoByID(shopID);
    MB_ShopGoodsItem *node = NULL;
    CCARRAY_FOREACH_4TYPE(shopInfo->getShopGoodsArray(), MB_ShopGoodsItem *, node)
    {
        if (MB_ShopMgr::getInstance()->shopGoodsCanBuy(node))
        {
            count++;
        }
    }
    return count;
}

bool MB_ShopMgr::shopGoodsCanBuy(MB_ShopGoodsItem* pGoods)
{
    if (pGoods)
    {
        if(pGoods->getVipLimit() <= MB_RoleData::getInstance()->getVipLevel()){
            
            if (pGoods->getBuyNum() == -1 || pGoods->getRealBuyNum() < pGoods->getBuyNum())
            {
                return true;
            }
        }
    }
    return false;
}


void MB_ShopMgr::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_SHOP_BUY_NUM:
            recvshop_buy_num(recvPacket);
            break;
        case SC_SHOP_BUY:
            recvshop_buy(recvPacket);
            break;
        case SC_BOX_SHOP_INFO:
            recvbox_shop_info(recvPacket);
            break;
        case SC_SHOP_REFRESH:
            recvshop_refresh(recvPacket);
            break;
        case SC_SHOP_ENCOUNTER:
            recvshop_encounter(recvPacket);
            break;
        case SC_BOX_GET_SPRIT_EQUIP_COUNT:
            recvbox_get_spirit_equip_count(recvPacket);
            break;
        case SC_SHOP_AUTO_REFRESH:
            recvshop_auto_refresh(recvPacket);
            break;
        default:
            break;
    }
}

//商店开宝箱信息
bool MB_ShopMgr::sendbox_shop_info(){

    SOCKET_REQUEST_START(CS_BOX_SHOP_INFO);
    SOCKET_REQUEST_END(SC_BOX_SHOP_INFO, MB_ShopMgr::onMsgRecv);
    return true;
}

//商店开宝箱信息
bool MB_ShopMgr::recvbox_shop_info(MB_MsgBuffer* recvPacket){

    m_pShopBoxTempleteArray->removeAllObjects();
    uint16_t data16;
    uint32_t data32;
    uint16_t length;
    int8_t data8;
    
    
    recvPacket->readU16(&data16);
    length = data16;
    for (int i = 0 ; i < length  ; i++)
    {
        MB_ShopBoxTemplete * data = new MB_ShopBoxTemplete();
       
        recvPacket->readU16(&data16);
        data->setID(data16);
        
        recvPacket->readU32(&data32);
        data->setCost1(data32);                 //单次购买价格
        
        recvPacket->readU32(&data32);
        data->setCost10(data32);                //10次购买价格
        
        recvPacket->readU8(&data8);
        data->setisOpenActivity(data8);         //是否开启活动
        
        recvPacket->readU32(&data32);        //活动期间折扣
        data->setDiscount(data32);
        
        recvPacket->readU32(&data32);        //活动结束时间
        data->setEndtime(data32);

        m_pShopBoxTempleteArray->addObject(data);
        data->release();
    
    }
    recvPacket->readU32(&m_uPetCriticTime);
    return true;
}


bool MB_ShopMgr::sendbox_get_spirit_equip_count()
{
    SOCKET_REQUEST_START(CS_BOX_GET_SPRIT_EQUIP_COUNT);
    SOCKET_REQUEST_END(SC_BOX_GET_SPRIT_EQUIP_COUNT, MB_ShopMgr::onMsgRecv);
    return true;
}

//    message recvbox_get_spirit_equip_count[id=12012]{
//required	int32		count1 = 1;
//required	int32		count2 = 2;
//required	int32		needItemTypeID1=3;
//required	int32		needNum1=4;
//required	int32		needItemTypeID2=5;
//required	int32		needNum2=6;
//    }
bool MB_ShopMgr::recvbox_get_spirit_equip_count(MB_MsgBuffer* recvPacket)
{
    uint32_t data32_0;
    uint32_t data32_1;

    MB_ShopBoxTemplete* pShopBoxTemplete0 = NULL;
//    MB_ShopBoxTemplete* pShopBoxTemplete1 = NULL;
    if(m_pShopBoxTempleteArray->count())
    {
        pShopBoxTemplete0 = dynamic_cast<MB_ShopBoxTemplete*>(m_pShopBoxTempleteArray->objectAtIndex(0));
//        pShopBoxTemplete1 = dynamic_cast<MB_ShopBoxTemplete*>(m_pShopBoxTempleteArray->objectAtIndex(1));
        
        recvPacket->readU32(&data32_0);
        recvPacket->readU32(&data32_1);
        pShopBoxTemplete0->setNeedCallTimes(data32_0);
//        pShopBoxTemplete1->setNeedCallTimes(data32_1);
        
        recvPacket->readU32(&data32_0);
        recvPacket->readU32(&data32_1);
        pShopBoxTemplete0->setItemID(data32_0);
        pShopBoxTemplete0->setItemCount(data32_1);
        
        recvPacket->readU32(&data32_0);
        recvPacket->readU32(&data32_1);
//        pShopBoxTemplete1->setItemID(data32_0);
//        pShopBoxTemplete1->setItemCount(data32_1);
    }
    else
    {
    }
    
    
    return true;
}


bool MB_ShopMgr::sendbox_item(uint16_t itemTypeID,uint8_t itemNum)
{
    MB_Message::sharedMB_Message()->showMessage(30);
    SOCKET_REQUEST_START(CS_BOX_ITEM);
    packet->writeU16(itemTypeID);
    packet->writeU8(itemNum);
    SOCKET_REQUEST_END(SC_BOX_ITEM, MB_ShopMgr::onMsgRecv);
    return true;
}



bool MB_ShopMgr::sendbox_shop(int32_t shopid, int8_t type)
{
    SOCKET_REQUEST_START(CS_BOX_SHOP);
    packet->writeU32(shopid);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_BOX_SHOP, MB_ShopMgr::onMsgRecv);
    return true;
}


bool MB_ShopMgr::sendshop_buy_num()
{
    SOCKET_REQUEST_START(CS_SHOP_BUY_NUM);
    SOCKET_REQUEST_END(SC_SHOP_BUY_NUM, MB_ShopMgr::onMsgRecv);
    return true;
}

bool MB_ShopMgr::recvshop_buy_num(MB_MsgBuffer* recvPacket)
{
    uint16_t num;
    uint16_t shopID;
    uint16_t sellID;
    uint16_t buyNum;//已购买次数
    
    recvPacket->readU16(&num);
    for (uint16_t i = 0; i < num; ++i)
    {
        recvPacket->readU16(&shopID);
        recvPacket->readU16(&sellID);
        recvPacket->readU16(&buyNum);
        updateShopGoodsRealNum(shopID, sellID, buyNum);
    }
    return true;
}

bool MB_ShopMgr::sendshop_buy(uint16_t shopid, uint16_t sellID, uint8_t num,uint8_t cointype,int cost)
{
    if(shopGoodsCanBuy(shopid, sellID))
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        
        SOCKET_REQUEST_START(CS_SHOP_BUY);
        packet->writeU16(shopid);
        packet->writeU16(sellID);
        packet->writeU8(num);
        SOCKET_REQUEST_END(SC_SHOP_BUY, MB_ShopData::onMsgRecv);
        m_uCurShopID = shopid;
        m_uCurGoodsID = sellID;
        m_uCurGoodsCount = num;
        m_uCurCoinType = cointype;
        m_uCurCost = cost;
        return true;
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("购买次数已达到上限.");
    }
    return false;
}

bool MB_ShopMgr::recvshop_buy(MB_MsgBuffer* recvPacket)
{
    uint8_t result;
    recvPacket->readU8(&result);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (1 == result)
    {
        autoAddShopGoodsRealNum(m_uCurShopID, m_uCurGoodsID);
        MB_Message::sharedMB_Message()->showMessage("购买成功");
        
        char szShop[50] = {0};
        sprintf(szShop, "商店(%d)购买",m_uCurShopID);
        
        std::string strCoinName = "未知";
        switch (m_uCurCoinType)
        {
            case 1:
                strCoinName = "宝石";
                break;
            case 2:
                strCoinName = "金币";
                break;
            case 3:
                strCoinName = "补天石";
                break;
            default:
                break;
        }
        MB_ShopGoodsItem* pGoodsItem = MB_ShopMgr::getInstance()->getShopGoodsItemByID(m_uCurGoodsID);
        if(pGoodsItem)
        {
            MB_ShopGoodsReward* pReward = dynamic_cast<MB_ShopGoodsReward*>(pGoodsItem->getRewardArray()->objectAtIndex(0));
            
        }
    }
    else
    {
        // 1=> 成功
        // 2=> 宝石不足
        // 3=> 银两不足
        // 4=> 徽章不足
        // 5=> 积分不足
        // 6=> 其他货币不足
        // 7=> vip等级不足
        // 8=> 购买次数超过上限
        // 9=> 您不拥有此奇遇商店
        switch (result)
        {
            case 2:
                MB_Message::sharedMB_Message()->showMessage("宝石不足");
                break;
            case 3:
                MB_Message::sharedMB_Message()->showMessage("金币不足");
                break;
            case 4:
                MB_Message::sharedMB_Message()->showMessage("补天石不足");
                break;
            case 5:
                MB_Message::sharedMB_Message()->showMessage("积分不足");
                break;
            case 6:
                MB_Message::sharedMB_Message()->showMessage("其他货币不足");
                break;
            case 7:
                MB_Message::sharedMB_Message()->showMessage("VIP等级不足");
                break;
            case 8:
                MB_Message::sharedMB_Message()->showMessage("购买次数超过上限");
                break;
            case 9:
                MB_Message::sharedMB_Message()->showMessage("您不拥有此商店, 不能购买");
                break;
            default:
                MB_Message::sharedMB_Message()->showMessage("未知错误");
                break;
        }
    }
    m_uCurGoodsID = 0;
    m_uCurShopID = 0;
    return true;
}


bool MB_ShopMgr::hasBall()
{
    MB_ShopBoxTemplete* pBoxTemplete = dynamic_cast<MB_ShopBoxTemplete*>(m_pShopBoxTempleteArray->objectAtIndex(0));
    if (pBoxTemplete)
    {
        return MB_ItemMgr::getInstance()->getItemEntityCount(pBoxTemplete->getItemID())!=0;
    }
    
    return false;
}

bool MB_ShopMgr::hasStone()
{
//    MB_ShopBoxTemplete* pBoxTemplete = dynamic_cast<MB_ShopBoxTemplete*>(m_pShopBoxTempleteArray->objectAtIndex(1));
//    if (pBoxTemplete)
//    {
//        return MB_ItemMgr::getInstance()->getItemEntityCount(pBoxTemplete->getItemID())!=0;
//    }
    return false;
}

bool MB_ShopMgr::sendshop_encounter()
{
    SOCKET_REQUEST_START(CS_SHOP_ENCOUNTER);
    SOCKET_REQUEST_END(SC_SHOP_ENCOUNTER, MB_ShopMgr::onMsgRecv);
    return true;
}

//刷新商店
bool MB_ShopMgr::sendshop_refresh()
{
    SOCKET_REQUEST_START(CS_SHOP_REFRESH);
    packet->writeU16(MYSTERY_SHOP_ID);
    SOCKET_REQUEST_END(SC_SHOP_REFRESH, MB_ShopMgr::onMsgRecv);
    return true;
}


bool MB_ShopMgr::recvshop_auto_refresh(MB_MsgBuffer *recvPacket)
{
    uint16_t  shopid;//商店ID
    uint32_t  refreshsec;//UnixTime，下次刷新的时间
    recvPacket->readU16(&shopid);
    recvPacket->readU32(&refreshsec);
    
    MB_ShopInfo* pShopInfo = getShopInfoByID(MYSTERY_SHOP_ID);
    MB_MysterShopInfo* pMysteryShopinfo = NULL;
    
    if(pShopInfo)
    {
        pMysteryShopinfo = dynamic_cast<MB_MysterShopInfo*>(pShopInfo);
    }
    else
    {
        return false;
    }
    
    pMysteryShopinfo->setRefreshsec(refreshsec);
    pMysteryShopinfo->getShopGoodsArray()->removeAllObjects();
    
    uint16_t  length;
    recvPacket->readU16(&length);
    for(int i = 0 ; i < length ;i++)
    {
        uint16_t itemid;//商品ID
        recvPacket->readU16(&itemid);
        MB_ShopGoodsItem * itemData = getShopGoodsItemByID(itemid);//new MB_ShopGoodsItem();
        if(itemData)
        {
            itemData->setGoodsID(itemid);
            itemData->setRealBuyNum(0);
            itemData->setBuyNum(1);
            pMysteryShopinfo->getShopGoodsArray()->addObject(itemData);
            //itemData->release();
        }
        else
        {
            MB_LOG("");
        }
    }
    
    return true;
}

bool MB_ShopMgr::recvshop_encounter(MB_MsgBuffer *recvPacket)
{
    uint16_t shopLength ;
    recvPacket->readU16(&shopLength);
    
    for(int j = 0 ; j<shopLength ;j++)
    {
        uint16_t  shopid;//商店ID
        uint32_t  refreshsec;//UnixTime，下次刷新的时间
        recvPacket->readU16(&shopid);
        recvPacket->readU32(&refreshsec);
        
        MB_ShopInfo* pShopInfo = getShopInfoByID(MYSTERY_SHOP_ID);
        MB_MysterShopInfo* pMysteryShopinfo = NULL;

        if(pShopInfo)
        {
            pMysteryShopinfo = dynamic_cast<MB_MysterShopInfo*>(pShopInfo);
        }
        else
        {
            return false;
        }
        
        pMysteryShopinfo->setRefreshsec(refreshsec);
        pMysteryShopinfo->getShopGoodsArray()->removeAllObjects();
        
        uint16_t  length;
        recvPacket->readU16(&length);
        
        if(length!=8)MB_LOG("[错误:] 宝石商店物品数量只能是8个");
        for(int i = 0 ; i < length ;i++)
        {
            uint16_t itemid;//商品ID
            recvPacket->readU16(&itemid);
            MB_ShopGoodsItem * itemData = getShopGoodsItemByID(itemid);//new MB_ShopGoodsItem();
            if(itemData)
            {
                itemData->setGoodsID(itemid);
                itemData->setRealBuyNum(0);
                itemData->setBuyNum(1);
                pMysteryShopinfo->getShopGoodsArray()->addObject(itemData);
                //itemData->release();
            }
            else
            {
                MB_LOG("");
            }
        }
    }
    
    return true;
}

bool MB_ShopMgr::recvshop_refresh(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint8_t result;
    recvPacket->readU8(&result);
    if(result == 1)
    {
        uint16_t shopLength ;
        recvPacket->readU16(&shopLength);
        
        for(int j = 0 ; j<shopLength ;j++)
        {
            uint16_t  shopid;//商店ID
            uint32_t  refreshsec;//UnixTime，下次刷新的时间
            recvPacket->readU16(&shopid);
            recvPacket->readU32(&refreshsec);
            
            MB_ShopInfo* pShopInfo = getShopInfoByID(MYSTERY_SHOP_ID);
            MB_MysterShopInfo* pMysteryShopinfo = NULL;

            if(pShopInfo)
            {
                pMysteryShopinfo = dynamic_cast<MB_MysterShopInfo*>(pShopInfo);
            }
            else
            {
                return false;
            }
            
            pMysteryShopinfo->setRefreshsec(refreshsec);
            pMysteryShopinfo->getShopGoodsArray()->removeAllObjects();
            
            uint16_t  length;
            recvPacket->readU16(&length);
            for(int i = 0 ; i < length ;i++)
            {
                uint16_t itemid;//商品ID
                recvPacket->readU16(&itemid);
                MB_ShopGoodsItem * itemData = getShopGoodsItemByID(itemid);//new MB_ShopGoodsItem();
                if(itemData)
                {
                    itemData->setGoodsID(itemid);
                    itemData->setRealBuyNum(0);
                    itemData->setBuyNum(1);
                    pMysteryShopinfo->getShopGoodsArray()->addObject(itemData);
                    //itemData->release();
                }
                else
                {
                    MB_LOG("");
                }
            }
        }
        
    }else if(result == 2){
        
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
        
    }else {
        
        MB_Message::sharedMB_Message()->showMessage("未知错误");
        
    }
    
    return true;
}

