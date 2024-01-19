//
//  MB_GiftsInterface.cpp
//  ProjectPM
//
//  Created by chenhongkun on 14-6-12.
//
//


#include "MB_GiftsInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_NodeGiftEntry.h"
#include "MB_LayerMainGift1.h"
#include "MB_GiftDataSource.h"

MB_GiftsInterface::MB_GiftsInterface()
{
    m_pList = new CCArray;
    m_pLevelDataSource = NULL;
    m_pTimeDataSource = NULL;
    m_pMLoginDataSource = NULL;
    SOCKET_MSG_REGIST(SC_DAILY_REWARD_LIST, MB_GiftsInterface);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_GiftsInterface);
}

MB_GiftsInterface::~MB_GiftsInterface()
{
    CC_SAFE_RELEASE_NULL(m_pList);
    CC_SAFE_DELETE(m_pLevelDataSource);
    CC_SAFE_DELETE(m_pTimeDataSource);
    CC_SAFE_DELETE(m_pMLoginDataSource);
    SOCKET_MSG_UNREGIST(SC_DAILY_REWARD_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
}

MB_DailyRewrdInfo* MB_GiftsInterface::getInfoByType(EGiftType type)
{
    MB_DailyRewrdInfo* pObj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pList, MB_DailyRewrdInfo*, pObj)
    {
        if(pObj->getType() == type)
        {
            return pObj;
        }
    }
    return NULL;
}
//MB_GiftLevelDataSource* m_pLevelDataSource;
//MB_GiftTimeDataSource* m_pTimeDataSource;
//MB_GiftMLoginDataSource* m_pMLoginDataSource;
CCTableViewDataSource* MB_GiftsInterface::getDataSourceByType(EGiftType type)
{
    switch (type)
    {
        case eGiftLevel:
            return m_pLevelDataSource;
            break;
        case eGiftMLogin:
            return m_pMLoginDataSource;
            break;
        case eGiftTime:
            return m_pTimeDataSource;
            break;
        default:
            return NULL;
            break;
    }
}

MB_ResWindow* MB_GiftsInterface::createEntryDialog()
{
    MB_NodeGiftEntry* ptr = new MB_NodeGiftEntry();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->setType(getFunctionType());
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}

MB_ResWindow* MB_GiftsInterface::createFunctionDialogSelf(EGiftType e)
{
    MB_FunctionMainWnd* ptr;
    if(e==eGiftTime)
    {
        ptr = new MB_LayerMainGift1();
    }else if(e==eGiftLevel)
    {
        ptr = new MB_LayerMainGift2();
    }else if(e==eGiftMLogin)
    {
        ptr = new MB_LayerMainGift3();
    }
    
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
void MB_GiftsInterface::onLoadingScene()
{
    cs_daily_reward_list();
}

void MB_GiftsInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_DAILY_REWARD_LIST:
            sc_daily_reward_list(recvPacket);
            break;
        case SC_ROLE_UPDATE_LEVEL:
        {
            MB_DailyRewrdInfo* pInfo = getInfoByType((EGiftType)eGiftLevel);
            if(pInfo)
            {
                MB_DailyRewrd* obj = NULL;
                CCARRAY_FOREACH_4TYPE(pInfo->getInfo(),MB_DailyRewrd*,obj)
                {
                    if(obj)obj->setNowValue(MB_RoleData::getInstance()->getLevel());
                }
            }
        }
            break;
        default:
            break;
    }
}

uint16_t MB_GiftsInterface::getFunctionType()
{
    return kActivatyGifts;
}

void MB_GiftsInterface::cs_daily_reward_list()
{
    SOCKET_REQUEST_START(CS_DAILY_REWARD_LIST);
    SOCKET_REQUEST_END(SC_DAILY_REWARD_LIST, MB_GiftsInterface::onMsgRecv);
}

uint32_t MB_GiftsInterface::m_LoginTime = 0;

//message sc_daily_reward_list[id=11008]{
//    repeated        p_daily_reward_info list        =1;//各种禮包信息
//}
void MB_GiftsInterface::sc_daily_reward_list(MB_MsgBuffer* pRecv)
{
    int len = 0;
    pRecv->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_DailyRewrdInfo* temp = new MB_DailyRewrdInfo;
        temp->read(pRecv);
        
        MB_DailyRewrdInfo* temp1 = getInfoByType((EGiftType)temp->getType());
        
        if(temp1)
        {
            temp1->setType(temp->getType());
            temp1->setNowValue(temp->getNowValue());
            temp1->getInfo()->removeAllObjects();
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(temp->getInfo(), pObj)
            {
                temp1->getInfo()->addObject(pObj);
            }
        }
        else
        {
            m_pList->addObject(temp);
        }
        
        CC_SAFE_RELEASE_NULL(temp);
    }
    
    if(NULL == m_pLevelDataSource)
    {
        m_pLevelDataSource = new MB_GiftLevelDataSource(this);
        m_pTimeDataSource = new MB_GiftTimeDataSource(this);
        m_pMLoginDataSource = new MB_GiftMLoginDataSource(this);
        
        m_LoginTime = MB_ClientSocket::getInstance()->getServerTime();
    }
}

//message cs_daily_reward_get[id=11011]{
//    required        int8            type            =1;//1在线時長禮包，2等級禮包，3連续登入禮包
//    required        int32           needValue       =2;//用需要条件标记要領取哪个档位的禮包，type=1，在线累計分钟數，type=2，當前等級，type=3，累計連续登入天數
//}
void MB_GiftsInterface::cs_daily_reward_get(uint8_t type,uint32_t needValue)
{
    SOCKET_REQUEST_START(CS_DAILY_REWARD_GET);
    packet->writeU8(type);
    packet->writeU32(needValue);
    SOCKET_REQUEST_END(SC_DAILY_REWARD_GET, MB_GiftsInterface::onMsgRecv);
}


////message sc_daily_reward_get[id=11012]{
////    required        int8            type            =1;//1在线時長禮包，2等級禮包，3連续登入禮包
////    required        int32           needValue       =2;//用需要条件标记要領取哪个档位的禮包，type=1，在线累計分钟數，type=2，當前等級，type=3，累計連续登入天數
////    required        int8            result          =3;//0成功，1已領取，   2不满足条件，根据type决定，type=1在线時長不足，type=2等級不足，type=3連续登入天數不足， 3無此禮包配置
////}
//void MB_GiftsInterface::sc_daily_reward_get(MB_MsgBuffer* pRecv)
//{
////    uint8_t type;
////    uint32_t needValue;
////    uint8_t result;
////    pRecv->readU8(&type);
////    pRecv->readU32(&needValue);
////    pRecv->readU8(&result);
//}











