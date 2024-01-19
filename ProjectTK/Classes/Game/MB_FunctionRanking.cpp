//
//  MB_FunctionRanking.cpp
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#include "MB_FunctionRanking.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionRankingEntry.h"
#include "MB_FunctionRankingProtocol.h"
#include "MB_LayerRankMain.h"

MB_FunctionRanking::MB_FunctionRanking()
{
    m_pDataSource[0] = new CCArray;
    m_pDataSource[1] = new CCArray;
    m_pDataSource[2] = new CCArray;
    m_pDataSource[3] = new CCArray;
    SOCKET_MSG_REGIST(RECV_RANK_INFO, MB_FunctionRanking);
}

MB_FunctionRanking::~MB_FunctionRanking()
{
    CC_SAFE_RELEASE_NULL(m_pDataSource[0]);
    CC_SAFE_RELEASE_NULL(m_pDataSource[1]);
    CC_SAFE_RELEASE_NULL(m_pDataSource[2]);
    CC_SAFE_RELEASE_NULL(m_pDataSource[3]);
    SOCKET_MSG_UNREGIST(RECV_RANK_INFO);
}

MB_ResWindow* MB_FunctionRanking::createEntryDialog()
{
    MB_FunctionRankingEntry* pInstance = new MB_FunctionRankingEntry;
    if (pInstance&&pInstance->setDataSource(this)&&pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_FunctionRanking::createFunctionDialog()
{
    MB_LayerRankMain* pMain = new MB_LayerRankMain;
    if (pMain&&pMain->setDataSource(this)&&pMain->init())
    {
        pMain->autorelease();
        return pMain;
    }
    CC_SAFE_RELEASE_NULL(pMain);
    return NULL;
}

bool MB_FunctionRanking::allowShow()
{
    return true;
}

uint16_t MB_FunctionRanking::getFunctionType()
{
    return kFunctionRanking;
}

/// 1:等級榜, 2:戰鬥力榜, 3:pvp榜, 4:關卡榜

void MB_FunctionRanking::send_rank_level()
{
    send_rank_info(1);
}

void MB_FunctionRanking::send_rank_power()
{
    send_rank_info(2);
}

void MB_FunctionRanking::send_rank_absolved()
{
    send_rank_info(4);
}

void MB_FunctionRanking::send_rank_arena()
{
    send_rank_info(3);
}

/*
 message cs_rank_info[id=13701]{
 required    int8                    rankType            = 1;// 1:等級榜, 2:戰鬥力榜, 3:pvp榜, 4:關卡榜
 required    int8                    type                = 2;// 1:普通關卡 2:困难關卡 3:最困难關卡
 required    int8                    start               = 3;// 从第几名開始請求
 required    int8                    num                 = 4;// 請求多少个
 }
 */
void MB_FunctionRanking::send_rank_info(uint8_t nType)
{
    SOCKET_REQUEST_START(SEND_RANK_INFO);
    packet->writeU8(nType);
    packet->writeU8(1);
    packet->writeU8(0);
    packet->writeU8(50);
    SOCKET_REQUEST_END(RECV_RANK_INFO, NULL);
}


/*
 message sc_rank_info[id=13702]{
 required    int8                    rankType            = 1;// 1:等級榜, 2:戰鬥力榜, 3:pvp榜, 4:關卡榜
 required    int8                    type                = 2;// 1:普通關卡   2:困难關卡  3:最困难關卡
 repeated    p_rank_info             list                = 3;// 排行榜數据
 }
 */
void MB_FunctionRanking::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (RECV_RANK_INFO == nMsg)
    {
        uint8_t type = 0;
        pRecv->readU8(&type);
        pRecv->skipU8();// 暂時保留
        uint16_t count = 0;
        pRecv->readU16(&count);
        
        if (type>=1&&type<=4)
        {
            m_pDataSource[type-1]->removeAllObjects();
            MB_RankData* pData = NULL;
            for (uint16_t i=0; i<count; ++i)
            {
                pData = new MB_RankData;
                if (pData->read(pRecv))
                {
                    m_pDataSource[type-1]->addObject(pData);
                }
                CC_SAFE_RELEASE_NULL(pData);
            }
        }
    }
}

CCArray* MB_FunctionRanking::getArrayDataByType(int type)
{
    if (type >= 0 && type < 4)
    {
        return m_pDataSource[type];
    }
    return NULL;
}

uint8_t MB_FunctionRanking::getOwnRank(uint8_t nType)
{
    CCArray* pArray = getArrayDataByType(nType);
    if (pArray)
    {
        MB_RankData* pData = NULL;
        uint32_t myid = MB_RoleData::getInstance()->getUID();
        CCARRAY_FOREACH_4TYPE(pArray, MB_RankData*, pData)
        {
            if (pData->getRoleID()==myid)
            {
                return pData->getRank();
            }
        }
    }
    return 0;
}
