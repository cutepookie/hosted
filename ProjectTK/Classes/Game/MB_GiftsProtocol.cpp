//
//  MB_GiftsProtocol.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#include "MB_GiftsProtocol.h"
#include "MB_GiftsInterface.h"

bool MB_ID_NUM::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU16(&m_nTypeID);
    pRecv->readU32(&m_nNum);
    return true;
}


MB_MailReward::MB_MailReward()
{
    m_pItemList = new CCArray;
    m_pPetList = new CCArray;
}
MB_MailReward::~MB_MailReward()
{
    CC_SAFE_RELEASE_NULL(m_pItemList);
    CC_SAFE_RELEASE_NULL(m_pPetList);
}

bool MB_MailReward::read(MB_MsgBuffer* pRecv)
{
    m_pItemList->removeAllObjects();
    int len = 0;
    pRecv->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_ID_NUM* pDr = new MB_ID_NUM;
        pDr->read(pRecv);
        m_pItemList->addObject(pDr);
        CC_SAFE_RELEASE_NULL(pDr);
    }
    
    m_pPetList->removeAllObjects();
    pRecv->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_ID_NUM* pDr = new MB_ID_NUM;
        pDr->read(pRecv);
        m_pPetList->addObject(pDr);
        CC_SAFE_RELEASE_NULL(pDr);
    }
    return true;
}

CCArray* MB_MailReward::converIDNUM2RewardTempleteValue()
{
    CCArray* pArray = CCArray::create();
    
    MB_ID_NUM* obj = NULL;
    RewardTempleteValue* pValue = NULL;
    CCARRAY_FOREACH_4TYPE(m_pItemList, MB_ID_NUM*, obj)
    {
        pValue = new RewardTempleteValue;
        pValue->setType(kRewardValueTypeItem);
        pValue->setNumber(obj->getNum());
        pValue->setValueID(obj->getTypeID());
        pArray->addObject(pValue);
        pValue->release();
    }
    
    CCARRAY_FOREACH_4TYPE(m_pPetList, MB_ID_NUM*, obj)
    {
        pValue = new RewardTempleteValue;
        pValue->setType(kRewardValueTypePet);
        pValue->setNumber(obj->getNum());
        pValue->setValueID(obj->getTypeID());
        pArray->addObject(pValue);
        pValue->release();
    }
    return pArray;
}

uint32_t MB_DailyRewrd::getEnable()
{
    if(m_bIsGet)return false;
    
    if (m_nType == eGiftTime)
        return m_nNowValue + MB_ClientSocket::getInstance()->getServerTime() - MB_GiftsInterface::m_LoginTime >= m_nNeedValue;
    else if(m_nType == eGiftMLogin)
        return m_nNowValue == m_nNeedValue;
    else
        return m_nNowValue >= m_nNeedValue;
}



MB_DailyRewrd::MB_DailyRewrd()
{
    m_pMailRewards = new MB_MailReward;
}
MB_DailyRewrd::~MB_DailyRewrd()
{
    CC_SAFE_RELEASE_NULL(m_pMailRewards);
}
bool MB_DailyRewrd::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU32(&m_nNeedValue);
    pRecv->readU8(&m_bIsGet);
    
    m_pMailRewards->read(pRecv);
    return true;
}

MB_DailyRewrdInfo::MB_DailyRewrdInfo()
{
    m_pDailyRewards = new CCArray;
}
MB_DailyRewrdInfo::~MB_DailyRewrdInfo()
{
    CC_SAFE_RELEASE_NULL(m_pDailyRewards);
}
bool MB_DailyRewrdInfo::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nType);
    pRecv->readU32(&m_nNowValue);
    
    int len = 0;
    pRecv->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_DailyRewrd* pDr = new MB_DailyRewrd;
        pDr->read(pRecv);
        pDr->m_nType = m_nType;
        pDr->m_nNowValue = m_nNowValue;
        m_pDailyRewards->addObject(pDr);
        CC_SAFE_RELEASE_NULL(pDr);
    }
    return true;
}

MB_DailyRewrd* MB_DailyRewrdInfo::getRewardByNeedValue(int needValue)
{
    MB_DailyRewrd* obj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pDailyRewards, MB_DailyRewrd*, obj)
    {
        if (obj->getNeedValue() == needValue)
        {
            return obj;
        }
    }
    return NULL;
}

int MB_DailyRewrdInfo::getUnGetCount()
{
    if(m_pDailyRewards == NULL)return 0;
    int n = 0;
    MB_DailyRewrd* obj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pDailyRewards, MB_DailyRewrd*, obj)
    {
        if(!obj->getIsGet())++n;
    }
    return n;
}


int MB_DailyRewrdInfo::getEnableCount()
{
    if(m_pDailyRewards == NULL)return 0;
    int n = 0;
    MB_DailyRewrd* obj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pDailyRewards, MB_DailyRewrd*, obj)
    {
        if(obj->getEnable())++n;
    }
    return n;
}