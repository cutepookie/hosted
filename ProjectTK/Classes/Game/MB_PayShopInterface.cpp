//
//  MB_PayShopInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//
#include "MB_PayShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_PayShopEntry.h"
#include "MB_ShopPay.h"
#include "MB_LayerShopMain.h"



MB_ResWindow* MB_PayShopInterface::createEntryDialog()
{
    MB_PayShopEntry* pInstance = new MB_PayShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}
MB_PayShopInterface::MB_PayShopInterface()
{
    m_nDayPayMul = 0;
    SOCKET_MSG_REGIST(SC_ACTIVITY_DAY_PAY_MUL, MB_PayShopInterface);
}

MB_PayShopInterface::~MB_PayShopInterface()
{
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_DAY_PAY_MUL);
}


MB_ResWindow* MB_PayShopInterface::createFunctionDialog()
{
    return MB_LayerShopMain::createItemShop();
}

void MB_PayShopInterface::onLoadingScene()
{
    cs_activity_day_pay_mul();
}



void MB_PayShopInterface::cs_activity_day_pay_mul()
{
    SOCKET_REQUEST_START(CS_ACTIVITY_DAY_PAY_MUL);
    SOCKET_REQUEST_END(SC_ACTIVITY_DAY_PAY_MUL, NULL);
}


void MB_PayShopInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == SC_ACTIVITY_DAY_PAY_MUL)
    {
        pRecv->readU8(&m_nDayPayMul);
    }
};
bool MB_PayShopInterface::allowShow()
{
    return true;
}

uint16_t MB_PayShopInterface::getFunctionType()
{
    return kFunctionPayShop;
}

void MB_PayShopInterface::onDayPassed()
{
}
