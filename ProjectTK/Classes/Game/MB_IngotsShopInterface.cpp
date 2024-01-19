//
//  MB_IngotsShopInterface.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//
#include "MB_IngotsShopInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_IngotsShopEntry.h"
#include "MB_ShopIngots.h"
#include "MB_LayerShopMain.h"
#include "MB_GiftsProtocol.h"
#include "MB_LayerRoleDetail.h"

MB_IngotsShopInterface::MB_IngotsShopInterface()
{
    SOCKET_MSG_REGIST(RECV_DAILY_VIP_DRAW, MB_IngotsShopInterface);
    SOCKET_MSG_REGIST(RECV_DAILY_VIP_INFO, MB_IngotsShopInterface);
    m_bReceived = false;
    m_pMailReward = new MB_MailReward;
}

MB_IngotsShopInterface::~MB_IngotsShopInterface()
{
    SOCKET_MSG_UNREGIST(RECV_DAILY_VIP_DRAW);
    SOCKET_MSG_UNREGIST(RECV_DAILY_VIP_INFO);
    CC_SAFE_RELEASE_NULL(m_pMailReward);
}

MB_ResWindow* MB_IngotsShopInterface::createEntryDialog()
{
    MB_IngotsShopEntry* pInstance = new MB_IngotsShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_IngotsShopInterface::createFunctionDialog()
{
//    return MB_LayerShopMain::createVipShop();
    return MB_ShopIngots::create();
}

void MB_IngotsShopInterface::onLoadingScene()
{
    send_daily_vip_info();
}

void MB_IngotsShopInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == RECV_DAILY_VIP_DRAW)
    {
        recv_daily_vip_draw(pRecv);
    }
    else if (nMsg == RECV_DAILY_VIP_INFO)
    {
        recv_daily_vip_info(pRecv);
    }
}

bool MB_IngotsShopInterface::allowShow()
{
    return true;
}

uint16_t MB_IngotsShopInterface::getFunctionType()
{
    return kFunctionIngotsShop;
}

void MB_IngotsShopInterface::onDayPassed()
{
    
}

/*
 message cs_daily_vip_info[id=11013]{
 
 }
 
 message sc_daily_vip_info[id=11014]{
 required        bool            isDraw          =1;
 required        p_mail_reward   list            =2;
 }
 
 message cs_daily_vip_draw[id=11015]{
 
 }
 
 message sc_daily_vip_draw[id=11016]{
 required        int8            result          =1;//0成功，1已領取，2沒有禮包可領
 }
 */
void MB_IngotsShopInterface::send_daily_vip_info()
{
    SOCKET_REQUEST_START(SEND_DAILY_VIP_INFO);
    SOCKET_REQUEST_END(RECV_DAILY_VIP_INFO, NULL);
}

void MB_IngotsShopInterface::recv_daily_vip_info(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_bReceived);
    
    m_pMailReward->read(pRecv);
}

void MB_IngotsShopInterface::send_daily_vip_draw()
{
    SOCKET_REQUEST_START(SEND_DAILY_VIP_DRAW);
    SOCKET_REQUEST_END(RECV_DAILY_VIP_DRAW, NULL);
}

void MB_IngotsShopInterface::recv_daily_vip_draw(MB_MsgBuffer* pRecv)
{
    uint8_t i = 0;
    pRecv->readU8(&i);
    m_bReceived = (i==0);
}


void MB_IngotsShopInterface::onEntryClicked(CCObject* pSender)
{
    MB_ResWindow *layer = MB_LayerRoleDetail::create();
    CCScene * pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene != NULL) {
        
        pScene->addChild(layer, Z_ORDER_ROLEDETAIL, ROLED_ETAIL_TAG);
    }
}
