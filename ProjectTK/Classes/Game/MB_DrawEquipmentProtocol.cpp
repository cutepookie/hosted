//
//  MB_DrawEquipmentProtocol.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-26.
//
//

#include "MB_DrawEquipmentProtocol.h"
#include "MB_ClientSocket.h"
#include "MB_ItemData.h"

MB_DrawCardData::MB_DrawCardData()
{
    m_nType = 0;
    m_nValue = 0;
    m_bDraw = false;
}

bool MB_DrawCardData::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nType);
    pRecv->readU32(&m_nValue);
    return true;
}

/*
 #define COIN_ID 30007//21100//钱幣图标
 #define GOLD_ID 30008//21101 //元寶
 #define REPUTATION_ID 30006//21102//徽章
 */
RewardTempleteValue* MB_DrawCardData::convertTemplateValue()const // autorelease
{
    RewardTempleteValue* p = new RewardTempleteValue;
    p->autorelease();
    
    if (m_nType == 1) // 精靈
    {
        p->setType(kRewardValueTypePet);
        p->setValueID(m_nValue);
        p->setNumber(1);
    }
    else
    {
        p->setType(kRewardValueTypeItem);
        if (m_nType == 2)
        {
            p->setNumber(1);
            p->setValueID(m_nValue);
        }
        else if(m_nType == 3)
        {
            p->setValueID(GOLD_ID);
            p->setNumber(m_nValue);
        }
        else if (m_nType == 4)
        {
            p->setNumber(m_nValue);
            p->setValueID(COIN_ID);
        }
        else if(m_nType == 5)
        {
            p->setNumber(m_nValue);
            p->setValueID(REPUTATION_ID);
        }
    }
    return p;
}

bool MB_DrawCardData::operator==(const MB_DrawCardData& pData)
{
    return pData.m_nType == m_nType && pData.m_nValue == m_nValue && pData.m_bDraw == m_bDraw;
}

MB_CardHistory::MB_CardHistory()
{
    m_nPos = 0;
    m_bDraw = true;
}

bool MB_CardHistory::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nPos);
    return MB_DrawCardData::read(pRecv);
}