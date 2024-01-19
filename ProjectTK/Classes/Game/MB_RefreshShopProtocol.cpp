//
//  MB_RefreshShopProtocol.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-5.
//
//

#include "MB_RefreshShopProtocol.h"

bool MB_Treasure::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_nType);
    recvPacket->readU16(&m_nTID);
    recvPacket->readU32(&m_nNum);
    recvPacket->readU8(&m_nCostType);
    recvPacket->readU32(&m_nCostVal);
    recvPacket->readU8(&m_isBuy);
    recvPacket->readU8(&m_nIndex);
    return true;
}


MB_TreasureInfo::MB_TreasureInfo()
{
    m_Treasures = new CCArray;
}
MB_TreasureInfo::~MB_TreasureInfo()
{
    CC_SAFE_RELEASE_NULL(m_Treasures);
}

MB_Treasure* MB_TreasureInfo::queryFunctionByIndex(uint16_t index)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_Treasures, obj)
    {
        MB_Treasure* ptr = dynamic_cast<MB_Treasure*>(obj);
        if(ptr && ptr->getIndex() == index)
        {
            return ptr;
        }
    }
    return NULL;
}

bool MB_TreasureInfo::read(MB_MsgBuffer* recvPacket)
{
    char* pString = recvPacket->ReadString();
    if (pString)
    {
        m_activityName = pString;
        CC_SAFE_FREE(pString);
    }
    recvPacket->readU32(&m_ActivityEndTime);
    recvPacket->readU8(&m_Mul);
    recvPacket->readU16(&m_nDiscounts);
    recvPacket->readU32(&m_NextRefreshTime);
    
    m_Treasures->removeAllObjects();
    uint16_t len = 0;
    recvPacket->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_Treasure * p = new MB_Treasure();
        p->read(recvPacket);
        m_Treasures->addObject(p);
        CC_SAFE_RELEASE_NULL(p);
    }
    return true;
}

bool MB_TreasureInfo::read_refresh_goods(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU32(&m_NextRefreshTime);
    
    m_Treasures->removeAllObjects();
    uint16_t len = 0;
    recvPacket->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_Treasure * p = new MB_Treasure();
        p->read(recvPacket);
        m_Treasures->addObject(p);
        CC_SAFE_RELEASE_NULL(p);
    }
    return true;
}

bool MB_TreasureInfo::read_refresh_goods2(MB_MsgBuffer* recvPacket)
{
    m_Treasures->removeAllObjects();
    uint16_t len = 0;
    recvPacket->readU16(&len);
    for (int i = 0; i<len; ++i)
    {
        MB_Treasure * p = new MB_Treasure();
        p->read(recvPacket);
        m_Treasures->addObject(p);
        CC_SAFE_RELEASE_NULL(p);
    }
    return true;
}


bool MB_TreasureInfo::read_new_activity(MB_MsgBuffer* recvPacket)
{
    char* pString = recvPacket->ReadString();
    if (pString)
    {
        m_activityName = pString;
        CC_SAFE_FREE(pString);
    }
    recvPacket->readU32(&m_ActivityEndTime);
    recvPacket->readU8(&m_Mul);
    recvPacket->readU16(&m_nDiscounts);
    return true;
}