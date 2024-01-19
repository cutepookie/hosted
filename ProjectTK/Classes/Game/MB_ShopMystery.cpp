//
//  MB_ShopMystery.cpp
//  ProjectTK
//
//  Created by CHK on 14-3-11.
//
//

#include "MB_ShopMystery.h"
#include "MB_ShopData.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_MysteryShopInterface.h"
#include "MB_TutorialMgr.h"
#include "MB_LayerItemDetail.h"
#include "MB_FunctionModule.h"

#include "MB_NodeMysteryShopUnit.h"
MB_ShopMystery::MB_ShopMystery():m_pRefreshTime(NULL),m_pFreshCount(NULL),m_pPageNode(NULL)
{
    m_pMysteryShopInterface = NULL;
    m_pContainerNode = NULL;
    m_nBackFuntion = kFunctionHome;
    m_bPlayerRefresh = false;
    SOCKET_MSG_REGIST(SC_SHOP_REFRESH,MB_ShopMystery);
    SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_ShopMystery);
    SOCKET_MSG_REGIST(SC_SHOP_ENCOUNTER, MB_ShopMystery);
    SOCKET_MSG_REGIST(SC_SHOP_AUTO_REFRESH, MB_ShopMystery);
    
    this->schedule(schedule_selector(MB_ShopMystery::tick));
}


MB_ShopMystery::~MB_ShopMystery(void)
{
    this->unschedule(schedule_selector(MB_ShopMystery::tick));
    CC_SAFE_RELEASE_NULL(m_pFreshCount);
    CC_SAFE_RELEASE_NULL(m_pRefreshTime);
    CC_SAFE_RELEASE_NULL(m_pPageNode);
    CC_SAFE_RELEASE_NULL(m_pContainerNode);
    
    SOCKET_MSG_UNREGIST(SC_SHOP_REFRESH);
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
    SOCKET_MSG_UNREGIST(SC_SHOP_ENCOUNTER);
    SOCKET_MSG_UNREGIST(SC_SHOP_AUTO_REFRESH);
}

bool MB_ShopMystery::init()
{
    MB_ResWindow::init();
    
    m_bShowRoleInfoPanel = true;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/shop_layer_refresh.ccbi", this);
   
    node->setVisible(true);
    this->addChild(node);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    QUERY_FUNCTION_BEGIN(MB_MysteryShopInterface, kFunctionMysteryShop, pInterface);
    m_pMysteryShopInterface = pInterface;
    QUERY_FUNCTION_END;
    
    return m_pMysteryShopInterface!=NULL;
}


bool MB_ShopMystery::onAssignCCBMemberVariable (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopPage2", CCNode*, m_pPageNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRefreshTime", CCLabelBMFont*, m_pRefreshTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFreshCount", CCLabelBMFont*, m_pFreshCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainerNode", CCNode*, m_pContainerNode);
    return false;
}


void MB_ShopMystery::tick(float dt)
{
    MB_ResWindow::tick(dt);
    this->tickFresh(dt);
}

SEL_MenuHandler MB_ShopMystery::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetDetailClick",MB_ShopMystery::onDetailIconClicked);//绑定 神秘商店详细信息回调
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick",MB_ShopMystery::onCloseClick);
    
    return NULL;
}

void MB_ShopMystery::onCloseClick(CCObject*)
{
    MB_FunctionMgr::getInstance()->goFunction(m_nBackFuntion, this);
}

void MB_ShopMystery::sendshop_buy(uint16_t sellID, uint8_t num,uint8_t cointype,int cost)
{
    MB_ShopMgr::getInstance()->sendshop_buy(MYSTERY_SHOP_ID,sellID,num,cointype,cost);
}

void MB_ShopMystery::onBuyClicked(CCObject* pSender)
{
}

SEL_CCControlHandler MB_ShopMystery::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPetClicked", MB_ShopMystery::onBuyClicked);//绑定 神秘商店购买回调
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onQuickFreeClick", MB_ShopMystery::onQuickFreeClick);//刷新回调
    return NULL;
}


void MB_ShopMystery::onQuickFreeClick(CCObject* pSender)
{
    int freshcount =  atoi(m_pFreshCount->getString()) ;
    if(freshcount <= 0 && (MB_RoleData::getInstance()->getGoldBoune()+MB_RoleData::getInstance()->getGold()) < 10)
    {
        MB_Message::sharedMB_Message()->showMessage("宝石和商人信件都不足");
        return;
    }
    if(freshcount>0)m_bPlayerRefresh = true;
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_ShopMgr::getInstance()->sendshop_refresh();
}

void MB_ShopMystery::onDetailIconClicked(CCObject* pSender)
{
}

void MB_ShopMystery::onMsgRecv (CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_SHOP_REFRESH:
            m_bPlayerRefresh = false;
        case SC_SHOP_ENCOUNTER:
        case SC_SHOP_AUTO_REFRESH:
        case SC_SHOP_BUY:
        {
            onResetWnd();
        }
            break;
        default:
            break;
    }
}

void MB_ShopMystery::onResetWnd()
{
    m_pContainerNode->removeAllChildren();
    MB_ShopInfo* pShopInfo = MB_ShopMgr::getInstance()->getShopInfoByID(MYSTERY_SHOP_ID);
    
    if(!pShopInfo)return;
    
    MB_ShopGoodsItem* pMB_ItemData = NULL;
    int i = 0;
    CCSize size = MB_NodeMysteryShopUnit::getUnitSize();
    CCARRAY_FOREACH_4TYPE(pShopInfo->getShopGoodsArray(), MB_ShopGoodsItem*, pMB_ItemData)
    {
        CCNode* pNode = NULL;
        if(i<4)
        {
            pNode = MB_NodeMysteryShopUnit::create(pMB_ItemData, MB_NodeMysteryShopUnit::kPet);
        }
        else
        {
            pNode = MB_NodeMysteryShopUnit::create(pMB_ItemData, MB_NodeMysteryShopUnit::kItem,i==4);
        }
        m_pContainerNode->addChild(pNode);
        pNode->setPosition(ccp(i%4 * size.width + size.width/2, int(i/4) * size.height + size.height/2));
        ++i;
    }
    
    //刷新道具数量
    char buff[20] = {0};
    sprintf(buff, "%d",MB_ItemMgr::getInstance()->getItemEntityCount(FRESH_ID));
    m_pFreshCount->setString(buff);
    tickFresh(0);
}


void MB_ShopMystery::tickFresh(float dt)
{
    MB_ShopInfo* pShopInfo = MB_ShopMgr::getInstance()->getShopInfoByID(MYSTERY_SHOP_ID);
    if(pShopInfo && m_pRefreshTime)
    {
        //刷新时间
        MB_MysterShopInfo* pMysteryShopInfo = dynamic_cast<MB_MysterShopInfo*>(pShopInfo);
        int lefttime = pMysteryShopInfo->getRefreshsec() - MB_ClientSocket::getInstance()->getServerTime();
        if(lefttime<0)lefttime=0;
        m_pRefreshTime->setString(NSGameHelper::formatTimeStringHMS_colon(lefttime));
    }
}


void MB_ShopMystery::ShowPageNode(bool b)
{
    if(m_pPageNode)
    {
        m_pPageNode->setVisible(b);
    }
}




