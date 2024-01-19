//
//  MB_FunctionRankingProtocol.cpp
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#include "MB_FunctionRankingProtocol.h"
#include "MB_MsgBuffer.h"

bool MB_RankData::read(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nRank);
    pRecv->readU32(&m_nRoleID);
    pRecv->readU16(&m_nLevel);
    char* p = pRecv->ReadString();
    if (p)
    {
        m_szName = p;
        CC_SAFE_FREE(p);
    }
    
    pRecv->readU32(&m_nHead);
    pRecv->readU8(&m_nTitle);
    pRecv->readU8(&m_bMale);
    pRecv->readU64(&m_nPower);
    pRecv->readU16(&m_nChapter);
    p = pRecv->ReadString();
    if (p)
    {
        m_szDungeonName = p;
        CC_SAFE_FREE(p);
    }
    return true;
}
