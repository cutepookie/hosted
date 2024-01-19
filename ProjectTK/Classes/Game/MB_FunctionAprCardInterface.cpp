//
//  MB_FunctionAprCardInterface.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#include "MB_FunctionAprCardInterface.h"
#include "MB_NodeAprCardEntry.h"
#include "MB_LayerAprCard.h"
#include "MB_AprCardProtocol.h"
#include "MB_DataExchange.h"
#include "PayMentViewCocos2d.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif
MB_FunctionAprCardInterface::MB_FunctionAprCardInterface()
{
    m_pData = new MB_AprCardData();
    SOCKET_MSG_REGIST(SC_ACTIVITY_MONTH, MB_FunctionAprCardInterface);
    SOCKET_MSG_REGIST(SC_ACTIVITY_MONTH_BUY, MB_FunctionAprCardInterface);
    SOCKET_MSG_REGIST(SC_ACTIVITT_MONTH_DRAW, MB_FunctionAprCardInterface);
}
MB_FunctionAprCardInterface::~MB_FunctionAprCardInterface()
{
    CC_SAFE_RELEASE_NULL(m_pData);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_MONTH);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_MONTH_BUY);
    SOCKET_MSG_UNREGIST(SC_ACTIVITT_MONTH_DRAW);
}
MB_ResWindow* MB_FunctionAprCardInterface::createEntryDialog()
{
    MB_NodeAprCardEntry* node = new MB_NodeAprCardEntry();
    if (node && node->setDataSource(this) && node->init())
    {
        node->setType(getFunctionType());
        node->autorelease();
        return node;
    }
    CC_SAFE_RELEASE_NULL(node);
    return NULL;
}
MB_ResWindow* MB_FunctionAprCardInterface::createFunctionDialog()
{
    MB_LayerAprCard* node = new MB_LayerAprCard();
    if (node && node->setDataSource(this) && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_RELEASE_NULL(node);
    return NULL;
}

void MB_FunctionAprCardInterface::onLoadingScene()
{
    sendActivity_Month();
}
void MB_FunctionAprCardInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (nMsg) {
        case SC_ACTIVITY_MONTH:
            recvActivity_Month(pRecv);
            break;
        case SC_ACTIVITY_MONTH_BUY:
            recvActivity_Month_Buy(pRecv);
            break;
        case SC_ACTIVITT_MONTH_DRAW:
            recvActivity_Month_Draw(pRecv);
            break;
            
        default:
            break;
    }
    CCNotificationCenter::sharedNotificationCenter()->postNotification(aprcard_status_notify.c_str());
}
bool MB_FunctionAprCardInterface::allowShow()
{
    return true;
}
uint16_t MB_FunctionAprCardInterface::getFunctionType()
{
    return kFunctionAprCard;
}


void MB_FunctionAprCardInterface::sendActivity_Month()
{
    SOCKET_REQUEST_START(CS_ACTIVITY_MONTH);
    SOCKET_REQUEST_END(SC_ACTIVITY_MONTH,NULL);
}
void MB_FunctionAprCardInterface::recvActivity_Month(MB_MsgBuffer* pRecv)
{
    m_pData->read(pRecv);
}
void MB_FunctionAprCardInterface::sendActivity_Month_Buy()
{
//    SOCKET_REQUEST_START(CS_ACTIVITY_MONTH_BUY);
//    SOCKET_REQUEST_END(SC_ACTIVITY_MONTH_BUY,NULL);
    
    int tag = 11008;
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
void MB_FunctionAprCardInterface::recvActivity_Month_Buy(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    pRecv->readU8(&result);
    if (result == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("购买月卡成功");
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("当日充值宝石不足");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("月卡还未过期");
    }
}
void MB_FunctionAprCardInterface::sendActivity_Month_Draw()
{
    SOCKET_REQUEST_START(CS_ACTIVITY_MONTH_DRAW);
    SOCKET_REQUEST_END(SC_ACTIVITT_MONTH_DRAW,NULL);
}
void MB_FunctionAprCardInterface::recvActivity_Month_Draw(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    pRecv->readU8(&result);
    if (result == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("领取成功");
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("已领取");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("月卡未激活");
    }
}
