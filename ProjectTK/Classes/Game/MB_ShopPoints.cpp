
#include "MB_ShopPoints.h"
#include "MB_ShopData.h"
#include "MB_RoleData.h"


MB_ShopPoints::MB_ShopPoints()
{
    SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_ShopPoints);
}

bool MB_ShopPoints::init()
{
    MB_ShopPageBase::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/shop_layer_friends.ccbi", this);

    node->setVisible(true);
    this->addChild(node);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    sDesCommon* pdc;
    pdc = DesTable.getDesCommon("shop_ID.xml",3);
    m_uShopID = pdc->queryValue("shopid").toInt();
    
    return true;
}

MB_ShopPoints* MB_ShopPoints::create()
{
    MB_ShopPoints* layer = new MB_ShopPoints();
    if(layer)
    {
        layer->init();
        layer->autorelease();
        layer->onResetWnd();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}

MB_ShopPoints::~MB_ShopPoints()
{
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
}

//道具商店，数据来只配置，且不用更新
void MB_ShopPoints::onResetWnd()
{
    MB_ShopPageBase::onResetWnd();
//    m_pTableView->reloadData();
//    m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
}




bool MB_ShopPoints::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget,
                                              const char *pMemberVariableName,
                                              cocos2d::CCNode *pNode)
{
    TutorialAssignLayerWindow

    if(0 == strcmp("shopPage3", pMemberVariableName))
    {
        m_Pos = pNode->getPosition();
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shoppropPanel", CCNode *, m_pPanel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopPage3", CCNode *, m_pPageNode);
    
    return false;
}
SEL_MenuHandler MB_ShopPoints::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    SEL_MenuHandler pHandler = MB_ShopPageBase::onResolveCCBCCMenuItemSelector(pTarget, pSelectorName);
    if(pHandler)return pHandler;
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick",MB_ShopPoints::onCloseClick);
    
    return NULL;
}
void MB_ShopPoints::onCloseClick(CCObject*)
{
    NSGameFunction::CCFunctionInterface::goFunctionHome();
}
unsigned int MB_ShopPoints::numberOfCellsInTableView(CCTableView *table)
{
    return m_pShopInfo->getShopGoodsArray()->count();
}

CCTableViewCell* MB_ShopPoints::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    MB_ShopGoodsItem *node = (MB_ShopGoodsItem*)m_pShopInfo->getShopGoodsArray()->objectAtIndex(idx);
    MB_ShopSubItem* pSubItem = MB_ShopSubItem::create(m_uShopID, node,0,idx == 0);
    pSubItem->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
    cell->addChild(pSubItem);
    return cell ;
}

void  MB_ShopPoints::onMsgRecv (CCNode*node, SocketResponse* response){
    
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
        case SC_SHOP_BUY:
        {
            uint8_t result;
            recvPacket->readU8(&result);
            if(result == kmShopBuy_Result_Success){
                
                this->onResetWnd();
            }
        }
            break;
    }
}
