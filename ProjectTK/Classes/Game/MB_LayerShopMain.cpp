//
//  MB_LayerShopMain.cpp
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#include "MB_LayerShopMain.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerRefreshShop.h"
#include "MB_ShopPoints.h"
#include "MB_ShopIngots.h"
#include "MB_ShopPay.h"
#include "MB_ShopMystery.h"
#include "MB_FunctionAprCardInterface.h"
#include "MB_LayerAprCard.h"
MB_LayerShopMain::MB_LayerShopMain()
{
    m_pSelectedSpr = NULL;
    m_pNodePageRoot	 = NULL;
    m_pMenuItemShop	 = NULL;
    m_pMenuRefreshShop	 = NULL;
    m_pMenuPayShop	 = NULL;
    m_pMenuBerryShop = NULL;
    m_pTextVipFlag = NULL;
    m_pNodeVipPageFlag = NULL;
    m_bShowRoleInfoPanel = true;
    m_nCurrentShop = -1;
    autoBuy = false;
}
MB_LayerShopMain::~MB_LayerShopMain()
{
    CC_SAFE_RELEASE_NULL(m_pSelectedSpr);
    CC_SAFE_RELEASE_NULL(m_pMenuBerryShop);
    CC_SAFE_RELEASE_NULL(m_pNodePageRoot);
    CC_SAFE_RELEASE_NULL(m_pMenuItemShop);
    CC_SAFE_RELEASE_NULL(m_pMenuRefreshShop);
    CC_SAFE_RELEASE_NULL(m_pMenuPayShop);
    CC_SAFE_RELEASE_NULL(m_pTextVipFlag);
    CC_SAFE_RELEASE_NULL(m_pNodeVipPageFlag);
}
void MB_LayerShopMain::onMsgRecv(CCNode* node, SocketResponse* response)
{
    onResetWnd();
}
bool MB_LayerShopMain::init()
{
    CCNode* pNodeRoot = loadResource("res/main_layer_shops.ccbi");
    if(pNodeRoot)
	{
		addChild(pNodeRoot);
        onInitialized();
		return true;
	}
	return false;
}
void MB_LayerShopMain::onExit()
{
//    PlayBackGround(kmBackGround_Normal);
    MB_ResWindow::onExit();
}

void MB_LayerShopMain::onEnterTransitionDidFinish()
{
    MB_ResWindow::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_Shop);
}
MB_LayerShopMain* MB_LayerShopMain::createRefreshShop()
{
    MB_LayerShopMain* pMain = MB_LayerShopMain::create();
    if (pMain->enterShop(kRefreshShop))
    {
        return pMain;
    }
    return NULL;
}

MB_LayerShopMain* MB_LayerShopMain::createItemShop()
{
    MB_LayerShopMain* pMain = MB_LayerShopMain::create();
    if (pMain->enterShop(kItemShop))
    {
        return pMain;
    }
    return NULL;
}

MB_LayerShopMain* MB_LayerShopMain::createVipShop()
{
    MB_LayerShopMain* pMain = MB_LayerShopMain::create();
    if (pMain->enterShop(kVipShop))
    {
        return pMain;
    }
    return NULL;
}

MB_LayerShopMain* MB_LayerShopMain::createPayShop()
{
    MB_LayerShopMain* pMain = MB_LayerShopMain::create();
    if (pMain->enterShop(kPayShop))
    {
        return pMain;
    }
    return NULL;
}

MB_LayerShopMain* MB_LayerShopMain::createBerryShop()
{
    MB_LayerShopMain* pMain = MB_LayerShopMain::create();
    if (pMain->enterShop(kBerryShop))
    {
        return pMain;
    }
    return pMain;
}

void MB_LayerShopMain::onInitialized()
{
    onResetWnd();
}
void MB_LayerShopMain::onResetWnd()
{
    int count = MB_ShopMgr::getInstance()->getShopCanBuyCount(4);
    if (count != 0)
    {
        m_pNodeVipPageFlag->setVisible(true);
        if (count>99) {
            m_pTextVipFlag->setString("!");
        }else
        {
            char buf[16] = {};
            sprintf(buf, "%d",count);
            m_pTextVipFlag->setString(buf);
        }
    }
    else
    {
        m_pNodeVipPageFlag->setVisible(false);
    }
}

void MB_LayerShopMain::switchShop(int type)
{
    if (type != m_nCurrentShop)
    {
        m_nCurrentShop = type;
        resetShopPage();
    }
}


void MB_LayerShopMain::resetShopPage()
{
    MB_ResWindow* pWindow = NULL;
    if (m_nCurrentShop==kItemShop)//========道具商城
    {
        m_pSelectedSpr->setPosition(ccp(80,-2));

        pWindow = MB_ShopPoints::create();
//        m_pPageName1->setString("道具商城");
    }
    else if(m_nCurrentShop==kVipShop)//=========vip
    {
        m_pSelectedSpr->setPosition(ccp(560,-2));
        pWindow = MB_ShopIngots::create();
//        m_pPageName1->setString("礼包商店");
    }
    else if(m_nCurrentShop==kRefreshShop)//========月卡
    {
        m_pSelectedSpr->setPosition(ccp(400,-2));
        NSGameFunction::CCFunctionInterface *pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAprCard ,&pInterface))
        {
            MB_FunctionAprCardInterface* pInterfaceTemp = dynamic_cast<MB_FunctionAprCardInterface*>(pInterface);
            pWindow = pInterfaceTemp->createFunctionDialog();
            if (autoBuy) {
                autoBuy = false;
                ((MB_LayerAprCard*)pWindow)->onBuyClicked(NULL);
            }
            
        }
//        m_pPageName1->setString("宝石商店");
    }
    else if(m_nCurrentShop==kPayShop)//========充值
    {
        m_pSelectedSpr->setPosition(ccp(240,-2));
        pWindow = MB_ShopPay::create();
//        m_pPageName1->setString("充值商店");
    }
    else if(m_nCurrentShop==kBerryShop)
    {
        CCFunctionInterface* pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionMysteryShop,&pInterface))
        {
            pWindow = MB_ShopMystery::create();
            if (pWindow)
            {
                pWindow->onResetWnd();
            }
        }

//        m_pPageName1->setString("补天石商店");
    }
    else
    {
        CCLOG("Unknow shop type:%d",m_nCurrentShop);
    }
    
    if (pWindow)
    {
        m_pNodePageRoot->removeAllChildren();
        m_pNodePageRoot->addChild(pWindow);
    }
}

bool MB_LayerShopMain::enterShop(int type)
{
    if (type > kShopCount || type < 0)
    {
        return false;
    }
    
    if(type == kBerryShop && MB_RoleData::getInstance()->getLevel() <15)
    {
        MB_Message::sharedMB_Message()->showMessage("补天石商店将在15级开放");
        return false;
    }
    
    switchShop(type);
    
    return true;
}

bool MB_LayerShopMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePageRoot",CCNode*,m_pNodePageRoot);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuItemShop",CCMenuItemImage*,m_pMenuItemShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuRefreshShop",CCMenuItemImage*,m_pMenuRefreshShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuPayShop",CCMenuItemImage*,m_pMenuPayShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuBerryShop",CCMenuItemImage*,m_pMenuBerryShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeVipPageFlag",CCNode*,m_pNodeVipPageFlag);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextVipFlag",CCLabelBMFont*,m_pTextVipFlag);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSelectedSpr",CCNode*,m_pSelectedSpr);
    
	return false;
}
SEL_MenuHandler MB_LayerShopMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_LayerShopMain::onCloseClicked);


	return NULL;
}
SEL_CCControlHandler MB_LayerShopMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onItemShopClicked",MB_LayerShopMain::onItemShopClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onRefreshShopClicked",MB_LayerShopMain::onRefreshShopClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onPayShopCicked",MB_LayerShopMain::onPayShopCicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onVipShopClicked",MB_LayerShopMain::onVipShopClicked);
	return NULL;
}
void MB_LayerShopMain::onCloseClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    if (global_isYeShiJieToShop) {
        global_isYeShiJieToShop = false;
        MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
    }else
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }
}
void MB_LayerShopMain::onVipShopClicked(CCObject* pSender)
{
    enterShop(kVipShop);
}
void MB_LayerShopMain::onItemShopClicked(CCObject* pSender)
{
    enterShop(kItemShop);
}
void MB_LayerShopMain::onRefreshShopClicked(CCObject* pSender)
{
    enterShop(kRefreshShop);
}
void MB_LayerShopMain::onPayShopCicked(CCObject* pSender)
{
    enterShop(kPayShop);
}
