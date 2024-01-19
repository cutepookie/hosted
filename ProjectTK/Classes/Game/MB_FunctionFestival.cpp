//
//  MB_FunctionFestival.cpp
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#include "MB_FunctionFestival.h"
#include "MB_LayerFestivalRank.h"
#include "MB_LayerFestivalMain.h"
#include "MB_FunctionModule.h"
#include "MB_FestivalProtocol.h"
#include "MB_GiftsProtocol.h"
#include "MB_NodeFestivalEntery.h"
#include "MB_LayerFestivalMain.h"
#include "MB_MoneyEevntData.h"

MB_FunctionFestival::MB_FunctionFestival()
{
    m_nStartTime = 0;
    m_nEndTime = 0;
    m_nTotalTimes = 0;
    m_nFreeTimes = 0;
    m_nLeftJoinTimes = 0;
    m_pRankReward = new CCArray;
    m_pRankArray = new CCArray;
    m_nMinRankCount = 0;
    m_nOwenRank = 0;
    m_nBoxTimes = 0;
    m_nOncePrice = 0;
    m_nTenthPrice = 0;
    m_nStartRequestRank = 0;
    m_nEndRequestRank = 0;
    m_bAnyRankData = true;
    SOCKET_MSG_REGIST(RECV_FESTIVAL_INFO, MB_FunctionFestival);
    SOCKET_MSG_REGIST(RECV_FESTIVAL_CLICK, MB_FunctionFestival);
    SOCKET_MSG_REGIST(RECV_FESTIVAL_RANK, MB_FunctionFestival);
}

MB_FunctionFestival::~MB_FunctionFestival()
{
    m_nMinRankCount = 0;
    m_nOwenRank = 0;
    m_nBoxTimes = 0;
    CC_SAFE_RELEASE_NULL(m_pRankReward);
    CC_SAFE_RELEASE_NULL(m_pRankArray);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_INFO);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_CLICK);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_RANK);
    MB_MoneyEevntMgr::getInstance()->removeFunctionActivity(this);
}

MB_ResWindow* MB_FunctionFestival::createEntryDialog()
{
    MB_NodeFestivalEntery* pEntry = new MB_NodeFestivalEntery;
    if (pEntry && pEntry->setDataSource(this) && pEntry->init())
    {
        pEntry->autorelease();
        return pEntry;
    }
    
    CC_SAFE_RELEASE_NULL(pEntry);
    return NULL;
}

void MB_FunctionFestival::onLoadingScene()
{
    send_festival_info();
}

MB_ResWindow* MB_FunctionFestival::createFunctionDialog()
{
    MB_LayerFestivalMain* p = new MB_LayerFestivalMain;
    if (p && p->setDataSource(this) && p->init())
    {
        p->autorelease();
        return p;
    }
    return NULL;
}

MB_ResWindow* MB_FunctionFestival::createRankDialog()
{
    MB_LayerFestivalRank* p = new MB_LayerFestivalRank;
    if (p && p->setDataSource(this) && p->init())
    {
        p->autorelease();
        return p;
    }
    
    CC_SAFE_RELEASE_NULL(p);
    return NULL;
}

bool MB_FunctionFestival::allowShow()
{
    return true;
}

const std::string& MB_FunctionFestival::getName()
{
    if (m_szName.empty())
    {
        MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
        if (pItem)
        {
            m_szName = pItem->getFunctionName();
            return m_szName;
        }
        m_szName = " ";
    }
    return m_szName;
}

uint16_t MB_FunctionFestival::getFunctionType()
{
    return kFunctionFestival;
}

void MB_FunctionFestival::send_festival_info()
{
    SOCKET_REQUEST_START(SEND_FESTIVAL_INFO);
    packet->writeU32(getActivityID());
    SOCKET_REQUEST_END(RECV_FESTIVAL_INFO,NULL);
}

bool MB_FunctionFestival::checkProtocol(MB_MsgBuffer *pRecv)
{
    uint32_t uid = 0;
    pRecv->readU32(&uid);
    return uid==getActivityID();
}

/*message sc_festival_info[id=13902]{
 required        int32                   id                      = 1;
 required        int32                   startTimestamp          = 1;//開始時間戳
 required        int32                   stopTimestamp           = 2;//結束時間戳
 required        int32                   totalCount              = 3;//累計次數
 required        int32                   totalGetCount           = 4;//當前可領取累計次數獎勵，為0表示無獎勵
 required        int32                   freeCount               = 5;//免费次數
 required        int16                   nextTotalCount          = 6;//得到累計次數獎勵需要次數
 required        int16                   price                   = 7;
 required        int16                   tenPrice                = 8;
 required        string                  info                    = 9;
 repeated        p_festival_rank_reward  rewardList              = 10;//排行榜獎勵信息
 }
*/
void MB_FunctionFestival::recv_festival_info(MB_MsgBuffer* pRecv)
{
    if (!checkProtocol(pRecv))
    {
        return;
    }
    pRecv->readU32(&m_nStartTime);
    pRecv->readU32(&m_nEndTime);
    pRecv->readU32(&m_nTotalTimes);
    pRecv->readU32(&m_nBoxTimes);
    pRecv->readU32(&m_nFreeTimes);
    pRecv->readU16(&m_nLeftJoinTimes);
    
    pRecv->readU16(&m_nOncePrice);
    pRecv->readU16(&m_nTenthPrice);
    char* p = pRecv->ReadString();
    if (p)
    {
        m_szDescription = p;
        free(p);
    }
    
    uint16_t count = 0;
    pRecv->readU16(&count);

    MB_FestivalRankReward* pReward = NULL;
    m_pRankReward->removeAllObjects();
    
    for (int i=0; i<count; ++i)
    {
        pReward = new MB_FestivalRankReward;
        if (pReward->read(pRecv))
        {
            m_pRankReward->addObject(pReward);
        }
        CC_SAFE_RELEASE_NULL(pReward);
    }
    
    int server_time = MB_ClientSocket::getInstance()->getServerTime();
    if (server_time>m_nStartTime
        && server_time<m_nEndTime)
    {
        MB_MoneyEevntMgr::getInstance()->addFunctionActivity(this);
    }
    else
    {
        MB_MoneyEevntMgr::getInstance()->removeFunctionActivity(this);
    }
}

/*
 message cs_festival_click[id=13903]{
 required        int32                   id                      = 1;
 required        int8            clickType               = 1;//點擊類型，0單次，1十次,2累計次數寶箱
 }
 */
void MB_FunctionFestival::send_festival_join_once()
{
    SOCKET_REQUEST_START(SEND_FESTIVAL_CLICK);
    packet->writeU32(getActivityID());
    packet->writeU8(0);
    SOCKET_REQUEST_END(RECV_FESTIVAL_CLICK, NULL);
}

void MB_FunctionFestival::send_festival_join_tenth()
{
    SOCKET_REQUEST_START(SEND_FESTIVAL_CLICK);
    packet->writeU32(getActivityID());
    packet->writeU8(1);
    SOCKET_REQUEST_END(RECV_FESTIVAL_CLICK, NULL);
}

void MB_FunctionFestival::send_festival_open_box()
{
    SOCKET_REQUEST_START(SEND_FESTIVAL_CLICK);
    packet->writeU32(getActivityID());
    packet->writeU8(2);
    SOCKET_REQUEST_END(RECV_FESTIVAL_CLICK, NULL);

}

/*
 message sc_festival_click[id=13904]{
 required        int32                   id                      = 1;
 required        int8            clickType               = 1;//點擊類型，0單次，1十次,2累計次數寶箱
 required        int8            result                  = 2;//0成功，1系統錯誤， 2活動已關閉，3 元寶不足， 4無累計次數獎勵可領取,5無此累計次數寶箱
 required        int16           nextTotalCount          = 3;//新的得到累計次數獎勵需要次數，為0表示不更新當前累計次數显示
 required        int32           totalCount              = 4;//累計次數
 required        int32           totalGetCount           = 5;//當前可領取累計次數獎勵，為0表示無獎勵
 required        int32           freeCount               = 6;//免费次數
 repeated        p_mail_reward   clickReward             = 7;//本次點擊得到的獎勵,單次一个數組元素，十次则十个數組元素
 }
 */
void MB_FunctionFestival::recv_festival_join_result(MB_MsgBuffer* pRecv)
{
    if (!checkProtocol(pRecv))
    {
        return;
    }
    pRecv->skipU8(); // 交由界面处理
    uint8_t result = 0;
    pRecv->readU8(&result);
    if (result==0)
    {
        pRecv->readU16(&m_nLeftJoinTimes);
        
        pRecv->readU32(&m_nTotalTimes);
        pRecv->readU32(&m_nBoxTimes);
        pRecv->readU32(&m_nFreeTimes);
    }
    // 交由界面处理
}

/*
 message cs_festival_rank[id=13905,route=festival_server]{
 required        int32                   id                      = 1;
 required        int16           start                   = 1;//排名起始位置
 required        int16           num                     = 2;//請求多少个
 }
 */
void MB_FunctionFestival::send_festival_rank()
{
    m_nStartRequestRank = 1;
    m_nEndRequestRank = 20;
    m_bAnyRankData = true;
    m_pRankArray->removeAllObjects();
    send_festival_rank(m_nStartRequestRank,m_nEndRequestRank);
}

void MB_FunctionFestival::send_festival_rank_next()
{
    if (m_bAnyRankData)
    {
        m_nStartRequestRank += 20;
        m_nEndRequestRank += 20;
        send_festival_rank(m_nStartRequestRank, m_nEndRequestRank);
    }
}

void MB_FunctionFestival::send_festival_rank(uint16_t start,uint16_t end)
{
    SOCKET_REQUEST_START(SEND_FESTIVAL_RANK);
    packet->writeU32(getActivityID());
    packet->writeU16(start);
    packet->writeU16(end);
    SOCKET_REQUEST_END(RECV_FESTIVAL_RANK, NULL);
}
/*
 message sc_festival_rank[id=13906]{
 required        int32                   id                      = 1;
 required        int8                    minRankCount            = 1;//上榜需要次數
 required        int16                   selfRank                = 2;//自己的排名，沒上榜為0
 repeated        p_festival_rank         rankList                = 3;//排行榜數組
 }
 */
void MB_FunctionFestival::recv_festival_rank(MB_MsgBuffer* pRecv)
{
    if (!checkProtocol(pRecv))
    {
        return;
    }
    pRecv->readU8(&m_nMinRankCount);
    pRecv->readU16(&m_nOwenRank);
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    
    MB_FestivalRankData* pRankData = NULL;
    for (uint16_t i=0; i<count; ++i)
    {
        pRankData = new MB_FestivalRankData;
        if (pRankData->read(pRecv))
        {
            m_pRankArray->addObject(pRankData);
        }
        CC_SAFE_RELEASE_NULL(pRankData);
    }
    m_bAnyRankData = (count==20);

    if (!m_bAnyRankData)
    {
        if(m_pRankArray->count()==0)
        {
            fillInRewardData(m_pRankArray, 1);
        }
        else
        {
            MB_FestivalRankData* p = (MB_FestivalRankData*)m_pRankArray->lastObject();
            uint16_t rank = p->getRank();
            fillInRewardData(m_pRankArray, rank+1);
        }
    }
}

void MB_FunctionFestival::fillInRewardData(CCArray* pTarget,uint16_t rank)
{
    MB_FestivalRankReward* p = NULL;
    MB_RankReward* pReward = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRankReward, MB_FestivalRankReward*,p)
    {
        if (p->getRankStart()>rank)
        {
            for (uint16_t i=p->getRankStart(); i<=p->getRankEnd(); ++i)
            {
                pReward = new MB_RankReward;
                pReward->setRank(i);
                pReward->setReward(p->getReward());
                m_pRankArray->addObject(pReward);
                pReward->release();
            }
        }
        else
        {
            if (p->getRankEnd()>=rank)
            {
                for (uint16_t i=rank; i<=p->getRankEnd(); ++i)
                {
                    pReward = new MB_RankReward;
                    pReward->setRank(i);
                    pReward->setReward(p->getReward());
                    m_pRankArray->addObject(pReward);
                    pReward->release();
                }
            }
        }
    }
}

void MB_FunctionFestival::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if(RECV_FESTIVAL_INFO == nMsg)
    {
        recv_festival_info(pRecv);
    }
    else if(RECV_FESTIVAL_CLICK == nMsg)
    {
        recv_festival_join_result(pRecv);
    }
    else if(RECV_FESTIVAL_RANK == nMsg)
    {
        recv_festival_rank(pRecv);
    }
}

MB_MailReward* MB_FunctionFestival::queryRankReward(uint32_t rank)
{
    MB_FestivalRankReward* pReward = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRankReward, MB_FestivalRankReward*, pReward)
    {
        if (rank >= pReward->getRankStart() && rank <= pReward->getRankEnd())
        {
            return pReward->getReward();
        }
    }
    return NULL;
}