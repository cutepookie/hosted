//
//  MB_ServerRewardData.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-3.
//
//

#include "MB_ServerRewardData.h"
#include "Game.h"
void MB_RewardView::readRewardTemplateValue(RewardTempleteValue* value,
                                            MB_MsgBuffer* recvPacket)
{
    uint8_t data8 = 0;
    uint32_t data32 = 0;
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
 //           CC_SAFE_RELEASE_NULL(value);
        }
    }

}

void MB_RewardView::showRewardMoreWithSerbuffer(MB_MsgBuffer *pRecv,MB_ResWindow* pParent)
{
    if (pParent == NULL)
    {
        skipRepeatedSerbuffer(pRecv);
    }
    uint16_t u16 = 0;
    pRecv->readU16(&u16);
    CCArray* pArray = CCArray::create();
    RewardTempleteValue* pValue = NULL;
    
    for (uint16_t i=0; i<u16; ++i)
    {
        pValue = new RewardTempleteValue;
        MB_RewardView::readRewardTemplateValue(pValue, pRecv);
        pArray->addObject(pValue);
        pValue->release();
    }
    
    if (u16>1)
    {
        MB_ResWindow* pWnd = MB_LayerRewardMore::create(pArray);
        if (pWnd)
        {
            pParent->pushWindow(pWnd);
        }
    }
    else if(u16==1)
    {
        RewardTempleteValue* pReward = dynamic_cast<RewardTempleteValue*>(pArray->objectAtIndex(0));
        if (pReward)
        {
            MB_ResWindow* pWnd = MB_LayerRewardOne::create(pReward->getType(), pReward->getValueID(),pReward->getNumber());
            if (pWnd)
            {
                CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_OUTSHOW);
            }
        }
    }
}

/*
 message	p_reward_view[id=12005]{
 required		int8			type			=1;//类型
 // 1=> 银两
 // 2=> 钻石
 // 3=> 声望
 // 4=> 冒险家经验
 // 5=> 宠物经验
 // 6=> 道具
 // 7=> 精灵
 required		int32			value			=2;//值，当类型为道具和精灵时，此字段前16位表示模版ID，后16位表示数量
 }
 */
void MB_RewardView::skipRepeatedSerbuffer(MB_MsgBuffer* pRecv)
{
    uint16_t count = 0;
    pRecv->readU16(&count);
    for (uint16_t i=0; i<count;++i)
    {
        pRecv->skipU8();
        pRecv->skipU32();
    }
}

bool MB_ChapterProgress::read(MB_MsgBuffer* recvPacket)
{
    if (recvPacket == NULL)
    {
        return false;
    }
    
    recvPacket->readU8(&m_nType);
    recvPacket->readU16(&m_nDungeonId);
    recvPacket->readU16(&m_nChapterId);
    recvPacket->readU16(&m_nDungeonCount);
    return true;
}

bool MB_DungeonInfo::read(MB_MsgBuffer *recvPacket)
{
    if (recvPacket == NULL)
    {
        return false;
    }
    
    recvPacket->readU16(&m_nDungeonID);
    recvPacket->readU16(&m_nRestTimes);
    recvPacket->readU8(&m_nBestScore);
    
    return true;
}

MB_BattleInfo::MB_BattleInfo()
{
    m_pDungeonInfoList = new CCArray;
    m_nTotalDungeon = 0;
}
MB_BattleInfo::~MB_BattleInfo()
{
    CC_SAFE_RELEASE_NULL(m_pDungeonInfoList);
}
bool MB_BattleInfo::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_nType);
    recvPacket->readU16(&m_nChapterId);
    updateInfo(recvPacket);
    return true;
}
void MB_BattleInfo::updateInfo(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU8(&m_bPerfect);
    
    uint16_t nCount = 0;
    MB_DungeonInfo* pInfo = NULL;
    m_pDungeonInfoList->removeAllObjects();
    recvPacket->readU16(&nCount);
    for (uint16_t i=0; i<nCount; ++i)
    {
        pInfo = new MB_DungeonInfo;
        if (pInfo->read(recvPacket))
        {
            m_pDungeonInfoList->addObject(pInfo);
        }
        CC_SAFE_RELEASE_NULL(pInfo);
    }
    recvPacket->readU16(&m_nTotalDungeon);
}
void MB_BattleInfo::addDungeonInfo(MB_DungeonInfo* pInfo)
{
    m_pDungeonInfoList->addObject(pInfo);
}

CCArray* MB_BattleInfo::getDungeonInfoList()
{
    return m_pDungeonInfoList;
}

MB_DungeonInfo* MB_BattleInfo::queryDungeonInfoByDungeonId(uint16_t nDungeonId)
{
    MB_DungeonInfo* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pDungeonInfoList, MB_DungeonInfo*, pTemp)
    {
        if (pTemp->getDungeonID() == nDungeonId)
        {
            return pTemp;
        }
    }
    
    return NULL;
}

int MB_BattleInfo::getBattleStar()
{
    if (m_bPerfect)
    {
        return 3;
    }
    else
    {
        MB_DungeonInfo* pDungeon = NULL;
        if (m_pDungeonInfoList->count()==0)
        {
            return 1;
        }
        int max = 0;
        int throw_dungeon = 0;
        CCARRAY_FOREACH_4TYPE(m_pDungeonInfoList, MB_DungeonInfo*, pDungeon)
        {
            if(pDungeon->getBestScore() != 0)
            {
                if(pDungeon->getBestScore() == 3)
                {
                    ++max;
                }
                ++throw_dungeon;
            }
        }
        if (max == m_nTotalDungeon)
        {
            return 3;
        }
        if (throw_dungeon == m_nTotalDungeon)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

MB_PetView::MB_PetView()
{
    m_nRank = 0;
    m_nLevel = 1;
    m_nTypeID = 0;
}
bool MB_PetView::read(MB_MsgBuffer* recvPacket)
{
    if (recvPacket == NULL)
    {
        return false;
    }
    
    recvPacket->readU16(&m_nRank);
    recvPacket->readU16(&m_nLevel);
    recvPacket->readU16(&m_nTypeID);
    
    return true;
}
