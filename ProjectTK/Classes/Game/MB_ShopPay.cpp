

#include "MB_ShopPay.h"
#include "PayMentViewCocos2d.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif

#include "MB_PayShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerVipInfo.h"
#include "MB_NodeItemBook.h"
#include "MB_DataExchange.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerShopMain.h"
MB_ShopPay::MB_ShopPay() :m_pVipInfo(NULL), m_pScrollView(NULL)
, m_pGold(NULL), m_pPrice(NULL), m_pFirstPay(NULL)
, m_pBuyButton(NULL),m_pVipInfo2(NULL),m_pVipInfoBg(NULL),m_pVipInfoBg2(NULL)
{
    m_pYkNode = NULL;
    m_pBsNode = NULL;
	for (int i = 0; i < 4; ++i)
	{
		m_pFirstPayNode[i] = NULL;
	}
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PAY_EXT, MB_ShopPay);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_GOLD, MB_ShopPay);
	SOCKET_MSG_REGIST(SC_ACTIVITY_DAY_PAY_MUL, MB_ShopPay);
	SOCKET_MSG_REGIST(SC_ROLE_PAY_GET_ORDER, MB_ShopPay);
	SOCKET_MSG_REGIST(SC_ROLE_PAY_ZZ, MB_ShopPay);

	//注册平台
	{
#ifdef PLATFORM_YJ
		MB_YJMgr::getInstance()->registDelegate(this);
#endif
#ifdef YJ_IOS
        MB_YJMgr_IOS::getInstance()->registDelegate(this);
#endif
	}
}

bool MB_ShopPay::init()
{
#ifdef OPEN_PAY
	if (!MB_ShopPageBase::init())
	{
		return false;
	}

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    m_pRoot = pCCBReader->readNodeGraphFromFile("res/shop_layer_paylist.ccbi", this);

	m_pRoot->setVisible(true);
	this->addChild(m_pRoot);
	CC_SAFE_RELEASE_NULL(pCCBReader);
	sDesCommon* pdc;
	pdc = DesTable.getDesCommon("shop_ID.xml", 5);
	m_uShopID = pdc->queryValue("shopid").toInt();

	NSGameHelper::adjustScrollNode(m_pPanel);

	initContianer();

	return true;
#else
	CCNode* pNode = loadResource("res/shop_layer_testdemo.ccbi");
	if (pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;// 屏蔽儲值
#endif
}

MB_ShopPay* MB_ShopPay::create()
{
	MB_ShopPay* layer = new MB_ShopPay();
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

MB_ShopPay::~MB_ShopPay()
{
    CC_SAFE_RELEASE_NULL(m_pVipInfo);
	CC_SAFE_RELEASE_NULL(m_pVipInfo2);
    CC_SAFE_RELEASE_NULL(m_pVipInfoBg);
    CC_SAFE_RELEASE_NULL(m_pVipInfoBg2);
        CC_SAFE_RELEASE_NULL(m_pYkNode);
        CC_SAFE_RELEASE_NULL(m_pBsNode);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PAY_EXT);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_GOLD);
	SOCKET_MSG_UNREGIST(SC_ACTIVITY_DAY_PAY_MUL);
	SOCKET_MSG_UNREGIST(SC_ROLE_PAY_GET_ORDER);
	SOCKET_MSG_UNREGIST(SC_ROLE_PAY_ZZ);

	//反注册平台
#ifdef PLATFORM_YJ
	MB_YJMgr::getInstance()->unregistDelegate(this);
#endif
#ifdef YJ_IOS
    MB_YJMgr_IOS::getInstance()->unregistDelegate(this);
#endif
}

SEL_MenuHandler MB_ShopPay::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	SEL_MenuHandler pHandler = MB_ShopPageBase::onResolveCCBCCMenuItemSelector(pTarget, pSelectorName);
	if (pHandler)
	{
		return pHandler;
	}

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onVipClicked", MB_ShopPay::onVipClicked);  //查看VIP
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_ShopPay::onCloseClick);

	return NULL;
}
SEL_CCControlHandler MB_ShopPay::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBuyClicked",MB_ShopPay::onBuyClicked);
    return NULL;
}
void MB_ShopPay::onCloseClick(CCObject*)
{
	NSGameFunction::CCFunctionInterface::goFunctionHome();
}

void MB_ShopPay::onVipClicked(CCObject* pSender)
{
	//查看VIP
	MB_LayerVipInfo* layer = MB_LayerVipInfo::create(this);
	CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
}

void MB_ShopPay::onBuyClicked(CCObject* pSender)
{
	uint32_t tag = ((CCMenuItemImage*)pSender)->getTag();
	MB_LOG("onBuyClicked TAG:%d", tag);
    if (tag == 11008)//跳转月卡
    {
        MB_TARGET_PARENT(MB_LayerShopMain, ptr)
        {
            if(ptr)
            {
                ptr->autoBuy = true;
                ptr->enterShop(MB_LayerShopMain::kRefreshShop);
            }
        }
    }else
    {
        char* payid = new char[16];
        sprintf(payid, "%d", tag);
        MB_RoleData::getInstance()->setCurPayID(tag);
        
        NSDataExchange::g_bInCharge = true;
#ifdef PLATFORM_YJ
        MB_Message::sharedMB_Message()->showMessage("", 5);
        MB_YJMgr::getInstance()->setPay(payid);
#elif defined(YJ_IOS)
        MB_Message::sharedMB_Message()->showMessage("", 5);
        MB_YJMgr_IOS::getInstance()->setPay(payid);
#else
        MB_Message::sharedMB_Message()->showMessage("购买中...", 9999);
        PayMentViewCocos2d::sharedPayMentView()->setPayment(payid);
#endif
        CC_SAFE_DELETE_ARRAY(payid);
    }
}



bool MB_ShopPay::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget,
	const char *pMemberVariableName,
	cocos2d::CCNode *pNode)
{

	if (MB_ShopPageBase::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
	{
		return true;
	}

	if (0 == strcmp("shopPage5", pMemberVariableName))
	{
		m_Pos = pNode->getPosition();
	}


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopPage5", CCNode *, m_pPageNode);      //儲值頁面根節点
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipInfo", CCLabelBMFont*, m_pVipInfo);   //在儲值xxxx,享受xxxx
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipInfo2", CCLabelBMFont*, m_pVipInfo2);   //在儲值xxxx,享受xxxx
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipInfoBg", CCNode*, m_pVipInfoBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipInfoBg2", CCNode*, m_pVipInfoBg2);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "shopPayPanel", CCNode*, m_pPanel);       //scrolview 容器

        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pYkNode", CCNode*, m_pYkNode);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBsNode", CCNode*, m_pBsNode);
	char buff[20] = { 0 };
	for (int i = 0; i < 4; ++i)
	{
		sprintf(buff, "bonus_node%d", i);
		if (strcmp(buff, pMemberVariableName) == 0)
		{
			m_pFirstPayNode[i] = pNode;
		}
	}

	{
        if (pTarget == this && strcmp(pMemberVariableName, "cellSize") == 0) {
            m_cellSize = CCSize(pNode->getContentSize().width * pNode->getScaleX(), pNode->getContentSize().height * pNode->getScaleY());
            return true;
        }

		if (pTarget == this && strcmp(pMemberVariableName, "gold") == 0) {
			m_pGold = (CCLabelBMFont*)pNode;
			return true;
		}
		if (pTarget == this && strcmp(pMemberVariableName, "price") == 0) {
			m_pPrice = (CCLabelBMFont*)pNode;
			return true;
		}
		if (pTarget == this && strcmp(pMemberVariableName, "firstPay") == 0) {
			m_pFirstPay = pNode;
			return true;
		}
		if (pTarget == this && strcmp(pMemberVariableName, "buyButton") == 0) {
			m_pBuyButton = (CCControlButton*)pNode;
			return true;
		}
		if (pTarget == this && strcmp(pMemberVariableName, "DoubleRewad") == 0)
		{
			m_pDoubleRewad = (CCSprite*)pNode;
			return true;
		}
	}

	return false;
}

void MB_ShopPay::refreshGoldPay()
{
#ifdef OPEN_PAY
	//跟新儲值金額、特權
	if (MB_RoleData::getInstance()->getVipLevel() >= MAX_VIP_LEVEL)
	{
		m_pVipInfo->setVisible(false);
		m_pVipInfo2->setVisible(false);
		m_pVipInfoBg->setVisible(false);
		m_pVipInfoBg2->setVisible(true);
	}
	else
	{
		char strVipInfo[30] = { 0 };
		int vipLevel = MB_RoleData::getInstance()->getVipLevel();
		sprintf(strVipInfo, "%d元", MB_RoleData::getInstance()->getVipLevelUpPay());
		m_pVipInfo->setString(strVipInfo);
		sprintf(strVipInfo, "VIP%d", vipLevel + 1);
		m_pVipInfo2->setString(strVipInfo);
	}
#endif
}


void MB_ShopPay::onResetWnd()
{
#ifdef OPEN_PAY
	//跟新儲值金額、特權
	if (MB_RoleData::getInstance()->getVipLevel() >= MAX_VIP_LEVEL)
	{
        m_pVipInfo->setVisible(false);
        m_pVipInfo2->setVisible(false);
        m_pVipInfoBg->setVisible(false);
        m_pVipInfoBg2->setVisible(true);
	}
	else
    {
        char strVipInfo[30] = { 0 };
        int vipLevel = MB_RoleData::getInstance()->getVipLevel();
        sprintf(strVipInfo, "%d元", MB_RoleData::getInstance()->getVipLevelUpPay());
        m_pVipInfo->setString(strVipInfo);
        sprintf(strVipInfo, "VIP%d", vipLevel + 1);
        m_pVipInfo2->setString(strVipInfo);
    }
	initContianer();
#endif
}

void MB_ShopPay::initContianer()
{
	CCSize containSize = CCSize(m_pPanel->getContentSize().width, 0);

	if (m_pScrollView == NULL)
	{
		m_pScrollView = CCScrollView::create(m_pPanel->getContentSize());
		m_pPanel->addChild(m_pScrollView);
	}
	else
	{
		m_pScrollView->setViewSize(m_pPanel->getContentSize());
	}
	m_pScrollView->getContainer()->removeAllChildren();

	m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    m_pScrollView->setTouchEnabled(false);
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	//獲取高度
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	pCCBReader->readNodeGraphFromFile("res/shop_node_payunit.ccbi", this);
	CC_SAFE_RELEASE_NULL(pCCBReader);

	//如果沒充過值,显示首儲獎勵
	{
		CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
		CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/shop_node_firstpay_gift.ccbi", this);
        pNode->setPosition(ccp(451.2f,745.7f));
        m_pRoot->addChild(pNode,-1);
		CC_SAFE_RELEASE_NULL(pCCBReader);

		MB_FirstPayTemplete* pObj = NULL;
		CCNode* pItem = NULL;
		int i = 0;
		CCARRAY_FOREACH_4TYPE(MB_RoleData::getInstance()->getFirstPayArray(), MB_FirstPayTemplete*, pObj)
		{
			if (i > 4)break;
			m_pFirstPayNode[i]->removeAllChildren();
            
			if (pObj->getType() == 1)
            {
                pItem = MB_NodeItem::create((uint16_t)pObj->getID());
                ((MB_NodeItem*)pItem)->setNum(pObj->getNum());
            }
			else
			{
                 pItem = MB_NodePet::create((uint16_t)pObj->getID());
			}
			if (pItem)m_pFirstPayNode[i]->addChild(pItem);
			++i;
		}
	}

	CCArray* payArray = MB_RoleData::getInstance()->getPayArray();
    payArray->reverseObjects();
	int index = 0;
	for (int i = 0; i < payArray->count(); i++)
	{
		CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
		CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/shop_node_payunit.ccbi", this);
		pNode->setPosition(ccp((i%4+.5f) * m_cellSize.width, -(i/4+.5f) * m_cellSize.height+725));
		m_pScrollView->addChild(pNode);
		CC_SAFE_RELEASE_NULL(pCCBReader);
		//設置具体值
		MB_PayTemplete* payTemplete = (MB_PayTemplete*)payArray->objectAtIndex(i);
        char* tempStr = new char[32];
        if(i ==payArray->count()-1)
        {
            m_pBsNode->setVisible(false);
            m_pYkNode->setVisible(true);
            m_pFirstPay->setVisible(false);
        }else
        {
            m_pBsNode->setVisible(true);
            m_pYkNode->setVisible(false);
            

            sprintf(tempStr, "%d", payTemplete->getGold());
            m_pGold->setString(tempStr);
            
            if (get_int32_pos_bit(MB_RoleData::getInstance()->getPayInfoId(), payTemplete->getID() % 1000) == 1)
            {
                m_pFirstPay->setVisible(false);
            }
            else
            {
                if (payTemplete->getExtreward() > 0)
                {
                    m_pFirstPay->setVisible(true);
                }
                else
                {
                    m_pFirstPay->setVisible(false);
                }
                
                
                CCFunctionInterface* pInterface = NULL;
                if (MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop, &pInterface))
                {
                    MB_PayShopInterface* ppayinterface = dynamic_cast<MB_PayShopInterface*>(pInterface);
                    
                    if (ppayinterface && ppayinterface->getDayPayMul())
                    {
                        m_pFirstPay->setVisible(true);
                    }
                    else
                    {
                        m_pFirstPay->setVisible(false);
                    }
                }
            }
        }
		

		sprintf(tempStr, "￥         %.2f", (float)payTemplete->getPrice());
		{
#ifdef PLATFORM_YJ
			sprintf(tempStr, "￥         %.2f", (float)payTemplete->getPrice());
#endif
#ifdef YJ_IOS
			sprintf(tempStr, "￥         %.2f", (float)payTemplete->getPrice());
#endif
			m_pPrice->setString(tempStr);
			CC_SAFE_DELETE_ARRAY(tempStr);
		}
		//TAG
		m_pBuyButton->setTag(payTemplete->getID());
	}

//    m_pScrollView->setContentSize(containSize);
//    m_pScrollView->getContainer()->setPosition(CCPointMake(0, m_pPanel->getContentSize().height - containSize.height));

}



void  MB_ShopPay::onMsgRecv(CCNode*    node, SocketResponse* response){

	assert(response != NULL);


	//將socket數据读取到序列化結构
	MB_MsgBuffer* recvPacket = response->getResponseData();

	//协议號
	uint16_t Msg;
	recvPacket->Reset();
	recvPacket->skipU16();
	recvPacket->skipU8();
	recvPacket->readU16(&Msg);

    switch (Msg)
    {
        case SC_ROLE_UPDATE_PAY_EXT:
            initContianer();
            break;
        case SC_ROLE_UPDATE_GOLD:
            onResetWnd();
            break;
        case SC_ACTIVITY_DAY_PAY_MUL:
            initContianer();
            break;
		case SC_ROLE_PAY_ZZ:
			refreshGoldPay();
            break;
    }
}

bool MB_ShopPay::hasFirstPayDouble()
{
	CCArray* payArray = MB_RoleData::getInstance()->getPayArray();
	for (int i = 0; i < payArray->count(); i++)
	{
		MB_PayTemplete* payTemplete = (MB_PayTemplete*)payArray->objectAtIndex(i);
		if (get_int32_pos_bit(MB_RoleData::getInstance()->getPayInfoId(), payTemplete->getID() % 1000) != 1)
		{
			return true;
		}
	}
	return false;
}

int MB_ShopPay::get_int32_pos_bit(int data, int pos)
{
	int _mask = 1;
	_mask <<= (pos - 1);
	int result = data & _mask;
	return result >>= (pos - 1);

}


void MB_ShopPay::recv_tencent_pay_check(MB_MsgBuffer* pRecv)
{
}

void MB_ShopPay::recv_appstore_pay_check(MB_MsgBuffer* pRecv)
{
}
