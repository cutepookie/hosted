//
//  MB_FestivalProtocol.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#include "MB_FestivalProtocol.h"
#include "MB_MsgBuffer.h"
#include "MB_GiftsProtocol.h"
MB_FestivalRankData::MB_FestivalRankData()
{
    m_nRoleID = 0;
    m_bIsMale = false;
    m_nTitle = 0;
    m_nHead = 0;
    m_nLevel = 0;
    m_nTotalCount = 0;
    m_nRank = 0;
}

MB_FestivalRankData::~MB_FestivalRankData()
{
    
}

bool MB_FestivalRankData::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU32(&m_nRoleID);
    pRecv->readU8(&m_bIsMale);
    pRecv->readU8(&m_nTitle);
    pRecv->readU32(&m_nHead);
    pRecv->readU16(&m_nLevel);
    char* p = pRecv->ReadString();
    if (p)
    {
        m_szRoleName = p;
        free(p);
    }
    pRecv->readU32(&m_nTotalCount);
    pRecv->readU16(&m_nRank);
    return true;
}

MB_FestivalRankReward::MB_FestivalRankReward()
{
    m_pMainReward = new MB_MailReward;
}

MB_FestivalRankReward::~MB_FestivalRankReward()
{
    CC_SAFE_RELEASE_NULL(m_pMainReward);
}

bool MB_FestivalRankReward::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU16(&m_nRankStart);
    pRecv->readU16(&m_nRankEnd);
    m_pMainReward->read(pRecv);
    return true;
}