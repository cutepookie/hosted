//
//  MB_ToyShopInterface.cpp
//  ProjectPM
//
//  Created by chk on 14-4-10.
//
//

#include "MB_ToyShopInterface.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionConfig.h"
#include "MB_LayerToyShopMain.h"
#include "MB_LayerCommand.h"
#include "MB_CallShopEntry.h"
#include "MB_DrawEquipmentProtocol.h"
MB_ToyShopInterface::MB_ToyShopInterface()
{
    m_pCardList = new CCArray;
    SOCKET_MSG_REGIST(RECV_CARD_DISTROY, MB_ToyShopInterface);
    SOCKET_MSG_REGIST(RECV_CARD_DRAW, MB_ToyShopInterface);
    SOCKET_MSG_REGIST(RECV_CARD_REFRESH, MB_ToyShopInterface);
}

MB_ToyShopInterface::~MB_ToyShopInterface()
{
    CC_SAFE_RELEASE_NULL(m_pCardList);
    SOCKET_MSG_UNREGIST(RECV_CARD_DISTROY);
    SOCKET_MSG_UNREGIST(RECV_CARD_DRAW);
    SOCKET_MSG_UNREGIST(RECV_CARD_REFRESH);
}

uint16_t MB_ToyShopInterface::getFunctionType()
{
    return kFunctionToy;
}

MB_ResWindow* MB_ToyShopInterface::createEntryDialog()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerToyShopMain",false);
    MB_NodeCallShopEntry* pInstance = new MB_NodeCallShopEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_ToyShopInterface::createFunctionDialog()
{
    MB_LayerToyShopMain* pLayer = new MB_LayerToyShopMain();
    if(pLayer && pLayer->setDataSource(this) && pLayer->init())
    {
        MB_LayerCommand* LayerCommand = dynamic_cast<MB_LayerCommand*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND));
        if(LayerCommand)LayerCommand->setSelectedSprPos(4);
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_RELEASE(pLayer);
    return NULL;
}
void MB_ToyShopInterface::onEntryClicked(CCObject* pSender)
{
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("LayerToyShopMain",false)) {
        NSGameFunction::CCFunctionInterface::onEntryClicked(pSender);
    }
}
bool MB_ToyShopInterface::allowShow()
{
    return true;
}

void MB_ToyShopInterface::onLoadingScene()
{
    send_card_distroy();
}

void MB_ToyShopInterface::send_card_refresh()
{
    SOCKET_REQUEST_START(SEND_CARD_REFRESH);
    SOCKET_REQUEST_END(RECV_CARD_REFRESH, NULL);
}


void MB_ToyShopInterface::recv_card_refresh(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 1:
        {
            MB_Message::sharedMB_Message()->removeALLMessage();
            m_pCardList->removeAllObjects();
            m_nOpendCount = 0;
            uint16_t count = 0;
            pRecv->readU16(&count);
            for (uint16_t i=0; i<count; ++i)
            {
                MB_DrawCardData* pData = new MB_DrawCardData;
                if (pData->read(pRecv))
                {
                    m_pCardList->addObject(pData);
                }
                pData->release();
            }
            break;
        }
        case 2:
            MB_Message::sharedMB_Message()->showMessage("刷新失败-银两不足");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("刷新失败-您刷得太快了");
            break;
        case 4:
            MB_Message::sharedMB_Message()->showMessage("刷新失败-未知错误");
            break;
        default:
            break;
    }
}

void MB_ToyShopInterface::send_card_draw(uint8_t pos)
{
    SOCKET_REQUEST_START(SEND_CARD_DRAW);
    packet->writeU8(pos);
    SOCKET_REQUEST_END(RECV_CARD_DRAW, NULL);
}

int getOldPos(CCArray* pArr,MB_DrawCardData* pData)
{
    MB_DrawCardData* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH_4TYPE(pArr, MB_DrawCardData*, pObj)
    {
        if(pObj->getType() == pData->getType() && pObj->getValue() == pData->getValue() && !pObj->getisDraw())
        {
            return i;
        }
        ++i;
    }
    return 0;
}

/*
 message		sc_card_draw[id=11106]{
 required		int8			result			=1;//抽取结果，如果抽取成功，前端自行删除点将令
 // 1=> 抽取成功
 // 2=> 抽取失败-点将令或者元宝不足
 // 3=> 抽取失败-卡牌已领完了，还领个毛啊
 // 4=> 抽取失败-未知错误
 required		int8			pos				=2;//请求的卡片抽取未知
 repeated		p_card			card			=3;//如果抽到，则列表长度为1个，如果没抽到，则列表长度为0
 }
 */
void MB_ToyShopInterface::recv_card_draw(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    switch (result)
    {
        case 1:
        {
            ++m_nOpendCount;
            MB_Message::sharedMB_Message()->removeALLMessage();
            uint8_t pos;
            pRecv->readU8(&pos);
            uint16_t count;
            pRecv->readU16(&count);
            for (int i = 0; i<count; ++i)
            {
                MB_DrawCardData* pDistroy = new MB_DrawCardData;
                if (pDistroy->read(pRecv))
                {
                    pDistroy->setisDraw(true);
                    int old = getOldPos(m_pCardList,pDistroy);
                    if(old != pos)m_pCardList->exchangeObjectAtIndex(old,pos);
                    m_pCardList->replaceObjectAtIndex(pos, pDistroy);
                }
                RewardTempleteValue* pTemplete = pDistroy->convertTemplateValue();
                MB_LayerRewardOne* pLayer = MB_LayerRewardOne::create(pTemplete->getType(), pTemplete->getValueID(),pTemplete->getNumber());
                if(pLayer)
                {
                    pLayer->setShowRoleInfoPanel(true);
                    CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer,Z_ORDER_OUTSHOW);
                }
                pDistroy->release();
            }
        }
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("道具或宝石不足");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("已经抽完");
            break;
        default:
            break;
    }
}

//MB_DrawCardData* MB_ToyShopInterface::getDrawCardDataByPos(int pos)
//{
//    MB_DrawCardData* pObj = NULL;
//    CCARRAY_FOREACH_4TYPE(m_pCardList, MB_DrawCardData*, pObj)
//    {
//        if(pObj->getPos() == pos)return pObj;
//    }
//    return NULL;
//}

void MB_ToyShopInterface::send_card_distroy()
{
    SOCKET_REQUEST_START(SEND_CARD_DISTROY);
    SOCKET_REQUEST_END(RECV_CARD_DISTROY, NULL);
}

/*
 message		sc_card_get_list[id=11102]{
 required       bool                    isOpen              =1;//是否开放
 repeated		p_opened_card			openedCardList		=2;//已抽取的卡牌列表
 repeated		p_card					cardList			=3;//等待抽取的卡牌列表
 repeated       int8                    needNumList         =4;//数组，抽第N次需要的个数就取数组的第N个元素的值，数组下标从1开始
 required       int8                    goldPrice           =5;//一个道具的宝石价格
 }
 */

void MB_ToyShopInterface::recv_card_distroy(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_isDrawEquipOpen);
    
    CCArray* pTempArr = CCArray::create();
    
    pRecv->readU16(&m_nOpendCount);
    for (uint16_t i=0; i<m_nOpendCount; ++i)
    {
        MB_CardHistory* pDistroy = new MB_CardHistory;
        if (pDistroy->read(pRecv))
        {
            pTempArr->addObject(pDistroy);
        }
        pDistroy->release();
    }
    
    
    m_pCardList->removeAllObjects();
    uint16_t count = 0;
    pRecv->readU16(&count);
    for (uint16_t i=0; i<count; ++i)
    {
        MB_DrawCardData* pData = new MB_DrawCardData;
        if (pData->read(pRecv))
        {
            m_pCardList->addObject(pData);
        }
        pData->release();
    }
    
    MB_CardHistory* pObj = NULL;
    CCARRAY_FOREACH_4TYPE(pTempArr, MB_CardHistory*, pObj)
    {
        if(pObj->getPos() >= m_pCardList->count())
            m_pCardList->addObject(pObj);
        else
            m_pCardList->insertObject(pObj, pObj->getPos());
    }
    
    pRecv->readU16(&count);
    for (uint16_t i=0; i<count; ++i)
    {
        pRecv->readU8(&m_pNeedItemNums[i]);
    }
    pRecv->readU32(&m_nItemPrice);
}




void MB_ToyShopInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case RECV_CARD_REFRESH:
            recv_card_refresh(pRecv);
            break;
        case RECV_CARD_DRAW:
            recv_card_draw(pRecv);
            break;
        case RECV_CARD_DISTROY:
            recv_card_distroy(pRecv);
            break;
        default:
            break;
    }
}

