//
//  MB_LayerRefreshShop.cpp
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#include "MB_LayerRefreshShop.h"
#include "MB_FunctionModule.h"
#include "MB_RefreshShopInterface.h"
#include "Game.h"
#include "MB_RefreshShopProtocol.h"

#include "MB_LocalProto.h"
#include "MB_NodeRefreshShopUnit.h"
#include "MB_RoleSoundSystem.h"
//#include "MB_RoleSoundProtocol.h"
MB_LayerRefreshShop* MB_LayerRefreshShop::create()
{
    MB_LayerRefreshShop* layer = new MB_LayerRefreshShop();
    if(layer)
    {
        layer->init();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}
void MB_LayerRefreshShop::onEnter()
{
    NSGameFunction::CCFunctionWnd::onEnter();
    MB_Message::sharedMB_Message()->showMessage(60);
    m_pInterface->sendshop_treasure_info();
    PlayRoleSound(kSoundEnterShop_1);
}

void MB_LayerRefreshShop::onExit()
{
    this->unschedule(schedule_selector(MB_ResWindow::tick));
    NSGameFunction::CCFunctionWnd::onExit();
}

MB_LayerRefreshShop::MB_LayerRefreshShop()
{
    m_pPromotionsNode	 = NULL;
    m_pTimeTtf	 = NULL;
    m_pNameTtf	 = NULL;
    m_pNextRefreshTimeTtf	 = NULL;
    m_pRefreshTimeTtf	 = NULL;
    m_pContainerNode	 = NULL;
    m_pInterface = NULL;
//    m_pTableView = NULL;
    m_pFreshCount = NULL;
    m_pCurTreasure = NULL;
    m_bPlayerRefresh = false;
    
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_INFO, MB_LayerRefreshShop);
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_NEW_ACTIVITY, MB_LayerRefreshShop);
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_NEW_SHOP, MB_LayerRefreshShop);
    SOCKET_MSG_REGIST(SC_SHOP_TREASURE_BUY, MB_LayerRefreshShop);
    SOCKET_MSG_REGIST(SC_SHOP_REFRESH2, MB_LayerRefreshShop);
}
MB_LayerRefreshShop::~MB_LayerRefreshShop()
{
    this->unschedule(schedule_selector(MB_LayerRefreshShop::tick));
    CC_SAFE_RELEASE_NULL(m_pPromotionsNode);
    CC_SAFE_RELEASE_NULL(m_pTimeTtf);
    CC_SAFE_RELEASE_NULL(m_pNameTtf);
    CC_SAFE_RELEASE_NULL(m_pNextRefreshTimeTtf);
    CC_SAFE_RELEASE_NULL(m_pRefreshTimeTtf);
    CC_SAFE_RELEASE_NULL(m_pContainerNode);
    CC_SAFE_RELEASE_NULL(m_pFreshCount);
    
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_INFO);
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_NEW_ACTIVITY);
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_NEW_SHOP);
    SOCKET_MSG_UNREGIST(SC_SHOP_TREASURE_BUY);
    SOCKET_MSG_UNREGIST(SC_SHOP_REFRESH2);
}
bool MB_LayerRefreshShop::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_RefreshShopInterface*>(pDataSource);
    return m_pInterface != NULL;
}
bool MB_LayerRefreshShop::init()
{
    CCNode* pNode = loadResource("res/shop_layer_advance.ccbi");
    if(pNode)
	{
        m_bShowRoleInfoPanel = true;
		addChild(pNode);
        
        NSGameFunction::CCFunctionInterface *pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionRefreshShop ,&pInterface))
            m_pInterface = dynamic_cast<MB_RefreshShopInterface*>(pInterface);
        
        this->schedule(schedule_selector(MB_LayerRefreshShop::tick));
        
        onResetWnd();
		return true;
	}
	return false;
}
void MB_LayerRefreshShop::tick(float dt)
{
    CCFunctionWnd::tick(dt);
    //刷新倒计时时间
    m_pRefreshTimeTtf->setString(NSGameHelper::formatTimeStringHMS_colon(m_pInterface->getTreasureInfo()->getNextRefreshTime() - MB_ClientSocket::getInstance()->getServerTime()));
    
    //结束倒计时时间
    m_pTimeTtf->setString(NSGameHelper::formatTimeStringHMS_colon(m_pInterface->getTreasureInfo()->getActivityEndTime() - MB_ClientSocket::getInstance()->getServerTime()));
}
void MB_LayerRefreshShop::onResetWnd()
{
    m_pContainerNode->removeAllChildren();
    CCArray* pArray = m_pInterface->getTreasureInfo()->getTreasures();
    MB_Treasure* pObj = NULL;
    int i = 0;
    CCSize size = MB_NodeRefreshShopUnit::getUnitSize();
    CCARRAY_FOREACH_4TYPE(pArray, MB_Treasure*, pObj)
    {
        if(pObj)
        {
            CCNode* pNode = MB_NodeRefreshShopUnit::create(pObj);
            m_pContainerNode->addChild(pNode);
            pNode->setPosition(ccp(i%4 * size.width + size.width/2, int(i/4) * size.height + size.height/2));
            ++i;
        }
    }
    
    m_pPromotionsNode->setVisible(m_pInterface->getTreasureInfo()->getActivityEndTime() != 0);
    
    m_pNameTtf->setString(m_pInterface->getTreasureInfo()->getActivityName().c_str());
    time_t ttt = m_pInterface->getTreasureInfo()->getNextRefreshTime();
    struct tm *pTemp = localtime(&ttt);
    char buff[100] = {0};
    sprintf(buff, "%02d:%02d",pTemp->tm_hour,pTemp->tm_min);
    m_pNextRefreshTimeTtf->setString(buff); //下次刷新

    sprintf(buff, "%d",MB_ItemMgr::getInstance()->getItemEntityCount(30004));
    
    m_pFreshCount->setString(buff);
    tick(0);
}

void MB_LayerRefreshShop::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    
}

void MB_LayerRefreshShop::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_SHOP_TREASURE_INFO:
            MB_Message::sharedMB_Message()->removeALLMessage();
            onResetWnd();
            break;
        case SC_SHOP_TREASURE_NEW_ACTIVITY:
            recvshop_treasure_new_activity();
            break;
        case SC_SHOP_TREASURE_NEW_SHOP:
            onResetWnd();
            break;
        case SC_SHOP_REFRESH2:
        {
            
            MB_Message::sharedMB_Message()->removeALLMessage();
            char result;
            recvPacket->readU8(&result);
            if(0 == result)
            {
                onResetWnd();
            }
            else if (1 == result)
            {
                MB_Message::sharedMB_Message()->showMessage("宝石不足");
            }
            m_bPlayerRefresh = false;
        }
            break;
        case SC_SHOP_TREASURE_BUY:
            recvshop_treasure_buy(recvPacket);
            break;
        default:
            break;
    }
}

//0成功，1商品不存在，2已经购买过，3金币不足，4钻石不足，5声望不足
void MB_LayerRefreshShop::recvshop_treasure_buy(MB_MsgBuffer* recvPacket)
{
    int8_t result = 0;
    int8_t index = 0;
    recvPacket->readU8(&result);
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    switch (result)
    {
        case 0:
        {
            MB_Message::sharedMB_Message()->showMessage("购买成功");
            recvPacket->readU8(&index);
            
            MB_Treasure* ptr = m_pInterface->getTreasureInfo()->queryFunctionByIndex(index);
            if(ptr)ptr->setIsBuy(true);
//            CCPoint p = m_pTableView->getContentOffset();
            onResetWnd();
//            m_pTableView->setContentOffset(p);
            
            
            std::string strCoinName = "未知";
            switch (m_pCurTreasure->getCostType())
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
            
        }
            break;
        case 1:
            MB_Message::sharedMB_Message()->showMessage("商品不存在");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("已经购买过");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("金币不足");
            break;
        case 4:
            MB_Message::sharedMB_Message()->showMessage("宝石不足");
            break;
        case 5:
            MB_Message::sharedMB_Message()->showMessage("补天石不足");
            break;
        default:
            break;
    }
}

void MB_LayerRefreshShop::recvshop_treasure_new_activity()
{
    onResetWnd();
}
bool MB_LayerRefreshShop::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPromotionsNode",CCNode*,m_pPromotionsNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTimeTtf",CCLabelTTF*,m_pTimeTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameTtf",CCLabelTTF*,m_pNameTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNextRefreshTimeTtf",CCLabelTTF*,m_pNextRefreshTimeTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRefreshTimeTtf",CCLabelTTF*,m_pRefreshTimeTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainerNode",CCNode*,m_pContainerNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pFreshCount",CCLabelTTF*,m_pFreshCount);
    
	return false;
}

SEL_MenuHandler MB_LayerRefreshShop::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick",MB_LayerRefreshShop::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerRefreshShop::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onQuickFreeClick",MB_LayerRefreshShop::onQuickFreeClick);
    return NULL;
}

void MB_LayerRefreshShop::onQuickFreeClick(CCObject*)
{
    if(MB_ItemMgr::getInstance()->getItemEntityCount(30004)>0)m_bPlayerRefresh = true;
    MB_Message::sharedMB_Message()->showMessage("", 5);
    m_pInterface->sendshop_refresh2();
}

void MB_LayerRefreshShop::onCloseClick(CCObject*)
{
    NSGameFunction::CCFunctionInterface::goFunctionHome();
}

void MB_LayerRefreshShop::sendshop_treasure_buy(MB_Treasure* pTreasure)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pCurTreasure = pTreasure;
    m_pInterface->sendshop_treasure_buy(pTreasure->getIndex());
}
