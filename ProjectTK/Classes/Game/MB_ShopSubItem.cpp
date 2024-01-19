

#include "MB_ShopSubItem.h"
#include "MB_ShopData.h"
#include "MB_ShopBase.h"
#include "MB_GameInfoEnum.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerShopMain.h"
MB_ShopSubItem::MB_ShopSubItem()
{
    m_pCanBuyTimes2 = NULL;
    m_pItemName     = NULL;
    m_pMoney        = NULL;
    m_pCanBuyTimes  = NULL;
    m_pMoneyIcon    = NULL;
    m_pItemIcon     = NULL;
    m_pBuy          = NULL;
    m_pDiscribe     = NULL;
    m_pNodeSize     = NULL;
    m_pShopGoodsItem = NULL;
    m_pBuy10 = NULL;
    m_bShowTutorial = false;
    m_uShopID = 0;
    SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_ShopSubItem);
}

MB_ShopSubItem::~MB_ShopSubItem()
{
    CC_SAFE_RELEASE_NULL(m_pCanBuyTimes2);
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pMoney);
    CC_SAFE_RELEASE_NULL(m_pCanBuyTimes);
    CC_SAFE_RELEASE_NULL(m_pMoneyIcon);
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pDiscribe);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pBuy);
    CC_SAFE_RELEASE_NULL(m_pBuy10);
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
    
}

MB_ShopSubItem* MB_ShopSubItem::create(uint16_t shopID, MB_ShopGoodsItem* pGoodsItem, int isSpecial,bool bShowTutril)
{
    MB_ShopSubItem* layer = new MB_ShopSubItem();
    if(layer != NULL)
    {
        layer->m_bShowTutorial = bShowTutril;
    }
    
    if (layer->init(shopID, pGoodsItem, isSpecial)) {
        layer->autorelease();

        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

bool MB_ShopSubItem::init(uint16_t shopID, MB_ShopGoodsItem *pGoodsItem, int isSpecial)
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    m_pShopGoodsItem = pGoodsItem;
    m_uShopID = shopID;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = NULL;
    if (isSpecial == 0)
    {
        node = pCCBReader->readNodeGraphFromFile("res/shop_node_goldunit.ccbi", this);
    }
    else
    {
        node = pCCBReader->readNodeGraphFromFile("res/shop_node_coinunit.ccbi", this);
    }
    this->addChild(node);
    CC_SAFE_DELETE(pCCBReader);
    
    if(m_pShopGoodsItem)
    {
        MB_ShopGoodsReward* pReward = (MB_ShopGoodsReward*)m_pShopGoodsItem->getRewardArray()->objectAtIndex(0);
        
        if (pReward->getRewardType() == kmRewardType_General) {
            MB_NodePet* nodePet = MB_NodePet::create((uint16_t)pReward->getRewardValue());
            m_pItemIcon->addChild(nodePet);
        }
        else
        {
            MB_NodeItem* nodeItem = MB_NodeItem::create((uint16_t)pReward->getRewardValue());
            nodeItem->setDelegate(this);
            m_pItemIcon->addChild(nodeItem);
            
        }
        
        onResetWnd();
    }
    
    return true;
}


bool MB_ShopSubItem::onAssignCCBMemberVariable(CCObject* pTarget,
                                               const char* pMemberVariableName,
                                               CCNode* pNode)
{
    if(m_bShowTutorial)
    {
        if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
        {
            return true;
        }
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "itemname", CCLabelTTF*,m_pItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "moneyicon", CCSprite*,m_pMoneyIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "money", CCLabelBMFont*,m_pMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "canbuynum", CCLabelBMFont*,m_pCanBuyTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PositionSign", CCNode*, m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pDiscribe", CCLabelTTF*,m_pDiscribe);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "buy", CCControlButton*, m_pBuy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "buy10", CCControlButton*, m_pBuy10);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "canbuynum2", CCNode*, m_pCanBuyTimes2);
    
    
    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0) {
        ((CCMenu*)pNode)->setSwallowsTouches(false);
        return true;
    }
    return false;
}


SEL_MenuHandler MB_ShopSubItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_ShopSubItem::onResolveCCBCCControlSelector(CCObject * pTarget,const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "clickbuy", MB_ShopSubItem::onClickBuy);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "clickbuy10", MB_ShopSubItem::onClickBuy10);
    return NULL;
}
void MB_ShopSubItem::onResetWnd(void)
{
    char temp[64];
    if (m_pShopGoodsItem != NULL)
    {
        //item icon 已reward的第一个 item | pet 来显示
        if (m_pShopGoodsItem->getRewardArray()->count() <= 0)
        {
            return;
        }
        
        
        //currency icon and price
        MB_ItemMgr::getInstance()->setSpriteFrame(m_pMoneyIcon,
                                GET_CONFIG_VALUE("currency.xml",
                                                 m_pShopGoodsItem->getCoinType(),
                                                 "Icon").c_str());
        
        sprintf(temp,"%d",m_pShopGoodsItem->getPrice());
        m_pMoney->setString(temp);
        
        //times
        if(-1 != m_pShopGoodsItem->getBuyNum())
        {
            sprintf(temp,"%d",m_pShopGoodsItem->getBuyNum() - m_pShopGoodsItem->getRealBuyNum());
            m_pCanBuyTimes->setString(temp);
            m_pCanBuyTimes->setVisible(true);
            m_pCanBuyTimes2->setVisible(false);
        }
        else
        {
            m_pCanBuyTimes->setVisible(false);
            m_pCanBuyTimes2->setVisible(true);
        }
        
        //item name
        m_pItemName->setString(m_pShopGoodsItem->getName());
        
        //buy
        m_pBuy->setEnabled(MB_ShopMgr::getInstance()->shopGoodsCanBuy(m_pShopGoodsItem));
        
        m_pDiscribe->setString(m_pShopGoodsItem->getDesc());
        
        MB_ShopGoodsReward* pReward = dynamic_cast<MB_ShopGoodsReward*>(m_pShopGoodsItem->getRewardArray()->objectAtIndex(0));
        MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(pReward->getRewardValue());
        if(itemTemplete)showBuy10(itemTemplete->getItemType() == kOTHER_BOX);
    }
}

void MB_ShopSubItem::onClickBuy(CCObject* psender)
{
    if (m_pShopGoodsItem)
    {
        TutorialTriggerComplete
        m_pShopGoodsItem->getCoinType();
        MB_ShopMgr::getInstance()->sendshop_buy(m_uShopID, m_pShopGoodsItem->getGoodsID(),1,m_pShopGoodsItem->getCoinType(),m_pShopGoodsItem->getPrice() * 1);
    }
}

void MB_ShopSubItem::onClickBuy10(CCObject* psender)
{
    if (m_pShopGoodsItem)
    {
        m_pShopGoodsItem->getCoinType();
        
        MB_LayerBuyNumberInput* pLayer = MB_LayerBuyNumberInput::create(this);
        MB_TARGET_PARENT(MB_LayerShopMain, ptr)
        {
            if(ptr)ptr->pushWindow(pLayer);
        }
    }
}

void MB_ShopSubItem::onNumberInputed(int num)
{
    MB_ShopMgr::getInstance()->sendshop_buy(m_uShopID, m_pShopGoodsItem->getGoodsID(),num,m_pShopGoodsItem->getCoinType(),m_pShopGoodsItem->getPrice() * num);
}



void MB_ShopSubItem::onClicked(MB_NodeItem* )
{
    onDetailClicked(NULL);
}

void MB_ShopSubItem::onDetailClicked(cocos2d::CCObject *pSender)
{
    if (m_pShopGoodsItem && m_pShopGoodsItem->getRewardArray()->count() > 0)
    {
        //item icon 已reward的第一个 item | pet 来显示
        MB_ShopGoodsReward* pReward = (MB_ShopGoodsReward*)m_pShopGoodsItem->getRewardArray()->objectAtIndex(0);
        if (pReward->getRewardType() == kmRewardType_General)
        {
            MB_ResWindow* layerDetail = MB_LayerPetDetail::create((uint16_t)pReward->getRewardValue());
            if(layerDetail)CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail,Z_ORDER_OUTSHOW);
        }
        else
        {
            MB_ResWindow* layerDetail = MB_LayerItemDetail::createByType((uint16_t)pReward->getRewardValue());
            MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
            if (pScene)
            {
                pScene->addChild(layerDetail,Z_ORDER_Detail);
            }else{
                CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail, Z_ORDER_OUTSHOW);
            }
        }
    }
}

void MB_ShopSubItem::onMsgRecv(CCNode* node, SocketResponse* response)
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
            
        case SC_SHOP_BUY:
            dirty();
            break;
            
        default:
            break;
    }
}



MB_VIPShopSubItem* MB_VIPShopSubItem::create(uint16_t shopID, MB_ShopGoodsItem* pGoodsItem, int isSpecial,bool bShowTutril)
{
    MB_VIPShopSubItem* layer = new MB_VIPShopSubItem();
    if(layer != NULL)
    {
        layer->m_bShowTutorial = bShowTutril;
    }
    
    if (layer->init(shopID, pGoodsItem, isSpecial)) {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

bool MB_VIPShopSubItem::init(uint16_t shopID, MB_ShopGoodsItem* pGoodsItem, int isSpecial)
{
    if (!CCLayer::init())return false;
    
    m_pShopGoodsItem = pGoodsItem;
    m_uShopID = shopID;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = NULL;

    node = pCCBReader->readNodeGraphFromFile("res/shop_node_vip.ccbi", this);
    this->addChild(node);
    CC_SAFE_DELETE(pCCBReader);
    
    if(m_pShopGoodsItem)
    {
        MB_ShopGoodsReward* pReward = (MB_ShopGoodsReward*)m_pShopGoodsItem->getRewardArray()->objectAtIndex(0);
        
        if (pReward->getRewardType() == kmRewardType_General)
        {
            MB_NodePet* nodePet = MB_NodePet::create((uint16_t)pReward->getRewardValue());
            m_pItemIcon->addChild(nodePet);
        }
        else
        {
            MB_NodeItem* nodeItem = MB_NodeItem::create((uint16_t)pReward->getRewardValue());
            nodeItem->setDelegate(this);
            m_pItemIcon->addChild(nodeItem);
        }
        onResetWnd();
    }
    return true;
}

