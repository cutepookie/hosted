//
//  MB_ParsingReward.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-29.
//
//

#include "MB_ParsingReward.h"
MB_ParsingReward::MB_ParsingReward()
{
    m_pArray = new CCArray;
}

MB_ParsingReward::~MB_ParsingReward()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}

MB_ParsingReward* MB_ParsingReward::create(MB_MsgBuffer *recv)
{
    MB_ParsingReward* pReward = new MB_ParsingReward;
    if(pReward && pReward->init(recv))
    {
        pReward->autorelease();
        return pReward;
    }
    CC_SAFE_RELEASE_NULL(pReward);
    return NULL;
}

bool MB_ParsingReward::read(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint8_t data8;
    uint16_t data16;
    uint32_t data32;
    
    if (recvPacket->readU16(&data16))
    {
        if (data16 > 0)
        {   //奖品数量>0
            m_pArray->removeAllObjects();
            for (uint16_t i = 0; i < data16; i++)
            {
                RewardTempleteValue* value = new RewardTempleteValue();
                
                if (recvPacket->readU8(&data8))
                {
                    if (data8 == kShopRewardTypePet)
                    {
                        value->setType(kRewardValueTypePet);
                        recvPacket->readU32(&data32);
                        value->setValueID((data32>>16) & 0x0000FFFF);
                        value->setNumber(data32 & 0x0000FFFF);
                    }
                    else if (data8 == kShopRewardTypeGold)
                    {
                        value->setType(kRewardValueTypeItem);
                        value->setValueID(GOLD_ID);
                        recvPacket->readU32(&data32);
                        value->setNumber(data32);
                    }
                    else if (data8 == kShopRewardTypeReputation)
                    {
                        value->setType(kRewardValueTypeItem);
                        value->setValueID(REPUTATION_ID);
                        recvPacket->readU32(&data32);
                        value->setNumber(data32);
                    }
                    else if (data8 == kShopRewardTypeRoleExp)
                    {
                        value->setType(kRewardValueTypeItem);
                        value->setValueID(ROLE_EXP_ID);
                        recvPacket->readU32(&data32);
                        value->setNumber(data32);
                    }
                    else if (data8 == kShopRewardTypePetExp)
                    {
                        value->setType(kRewardValueTypeItem);
                        value->setValueID(GER_EXP_ID);
                        recvPacket->readU32(&data32);
                        value->setNumber(data32);
                    }
                    else if (data8 == kShopRewardTypeItem)
                    {
                        value->setType(kRewardValueTypeItem);
                        recvPacket->readU32(&data32);
                        value->setValueID((data32>>16) & 0x0000FFFF);
                        value->setNumber(data32 & 0x0000FFFF);
                    }
                    else if (data8 == kShopRewardTypeCoin)
                    {
                        value->setType(kRewardValueTypeItem);
                        value->setValueID(COIN_ID);
                        recvPacket->readU32(&data32);
                        value->setNumber(data32);
                    }
                    else
                    {
                        MB_LOG("unkown reward type:%d", data8);
                        CC_SAFE_RELEASE_NULL(value);
                        return false;
                    }
                    m_pArray->addObject(value);
                    value->release();
                }
            }
        }
    }
    
//    if (recvPacket->readU16(&data16) && recvPacket->readU8(&data8))
//    {
//        MB_ItemMgr::getInstance()->removeItemByTypeID(data16,data8);
//    }
    
    return true;
    
}

CCArray* MB_ParsingReward::getRewardArray()
{
    return m_pArray;
}

bool MB_ParsingReward::init(MB_MsgBuffer *recv)
{
    return read(recv);
}