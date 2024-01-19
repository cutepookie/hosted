//
//  MB_AbsolvedInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#include "MB_AbsolvedInterface.h"
#include "MB_AbsolvedEntranceWnd.h"
#include "MB_LayerAbsolvedPage.h"
#include "MB_ServerRewardData.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_ChapterData.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_LayerRoleInfoHeader.h"
MB_AbsolvedInterface::MB_AbsolvedInterface()
{
    m_pChapterProgress = new CCArray;
    m_pArrayRankInfo = new CCArray;
    m_nCurrentType = kChapterDifficultyNormal;
    m_nCurrentPage = 0;
    SOCKET_MSG_REGIST(SC_BATTLE_PROGRESS, MB_AbsolvedInterface);
    SOCKET_MSG_REGIST(SC_BATTLE_INFO, MB_AbsolvedInterface);
    SOCKET_MSG_REGIST(SC_BATTLE_RANK, MB_AbsolvedInterface);
}

MB_AbsolvedInterface::~MB_AbsolvedInterface()
{
    CC_SAFE_RELEASE_NULL(m_pChapterProgress);
    CC_SAFE_RELEASE_NULL(m_pArrayRankInfo);
    SOCKET_MSG_UNREGIST(SC_BATTLE_PROGRESS);
    SOCKET_MSG_UNREGIST(SC_BATTLE_INFO);
    SOCKET_MSG_UNREGIST(SC_BATTLE_RANK);
    m_vPerfectDungeonID.clear();
    
}

MB_ResWindow* MB_AbsolvedInterface::createEntryDialog()
{
    MB_AbsolvedEntranceWnd* ptr = new MB_AbsolvedEntranceWnd();
    if(ptr && ptr->setDataSource(this) && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}

MB_ResWindow* MB_AbsolvedInterface::createFunctionDialog()
{
    MB_LayerAbsolvedPage* pInstance = new MB_LayerAbsolvedPage;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_AbsolvedInterface::onLoadingScene()
{
    sendbattle_progress();
}

void MB_AbsolvedInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_BATTLE_PROGRESS:
            recvbattle_progress(recvPacket);
            break;
        case SC_BATTLE_INFO:
            recvbattle_info(recvPacket);
            break;
        case SC_BATTLE_RANK:
            recvbattle_rank(recvPacket);
            break;
        default:
            break;
    }

}

void MB_AbsolvedInterface::addPerfectDungeonID(uint16_t id)
{
    m_vPerfectDungeonID[id] = id;
}

bool MB_AbsolvedInterface::isDungeonPerfect(uint16_t id)
{
    return m_vPerfectDungeonID.find(id) != m_vPerfectDungeonID.end();
}

bool MB_AbsolvedInterface::allowShow()
{
    return true;
}

uint16_t MB_AbsolvedInterface::getFunctionType()
{
    return kFunctionAbsolved;
}

void MB_AbsolvedInterface::sendbattle_progress()
{
    SOCKET_REQUEST_START(CS_BATTLE_PROGRESS);
    SOCKET_REQUEST_END(SC_BATTLE_PROGRESS, MB_AbsolvedInterface::onMsgRecv);
}

void MB_AbsolvedInterface::recvbattle_progress(MB_MsgBuffer* recvPacket)
{
    uint16_t count = 0;
    recvPacket->readU16(&count);
    MB_ChapterProgress* pProgress = NULL;
    
    m_pChapterProgress->removeAllObjects();
    
    for (uint16_t i=0; i<count; ++i)
    {
        pProgress = new MB_ChapterProgress;
        if (pProgress->read(recvPacket))
        {
            m_pChapterProgress->addObject(pProgress);
        }
        CC_SAFE_RELEASE_NULL(pProgress);
    }
    
    recvPacket->readU16(&count);
    uint16_t id = 0;
    for (int i=0; i<count; ++i)
    {
        recvPacket->readU16(&id);
        addPerfectDungeonID(id);
    }
    resetCurrentPageId();
}
void MB_AbsolvedInterface::resetCurrentPageId()
{
    MB_ChapterProgress* p = getChapterProgressByType(m_nCurrentType);
    if (p)
    {
        MB_ChapterPage* pPage = NULL;
        MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(m_nCurrentType, p->getChapterId(), &pPage);
        if (pPage)
        {
            m_nCurrentPage = pPage->getPageId();
        }
    }
}
MB_ChapterProgress* MB_AbsolvedInterface::getChapterProgressByType(int nType)
{
    MB_ChapterProgress* pTemp = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pChapterProgress, MB_ChapterProgress*, pTemp)
    {
        if (pTemp->getType() == nType)
        {
            return pTemp;
        }
    }
    return NULL;
}


bool MB_AbsolvedInterface::hasPassed(int nDungeonID)
{
    MB_ChapterProgress* pTemp = getChapterProgressByType(kChapterDifficultyNormal);
    if(pTemp)
    {
        return nDungeonID < pTemp->getDungeonId();
    }
    return false;
}

void MB_AbsolvedInterface::sendbattle_info(uint8_t nType,uint16_t nChapterId)
{
    SOCKET_REQUEST_START(CS_BATTLE_INFO);
    packet->writeU8(nType);
    packet->writeU16(nChapterId);
    SOCKET_REQUEST_END(SC_BATTLE_INFO, MB_AbsolvedInterface::onMsgRecv);
}

void MB_AbsolvedInterface::recvbattle_info(MB_MsgBuffer* recvPacket)
{
    // undeal
}

void MB_AbsolvedInterface::sendbattle_challenge(uint8_t nType,uint16_t nDungeonID)
{
    SOCKET_REQUEST_START(CS_BATTLE_CHALLENGE);
    packet->writeU8(nType);
    packet->writeU16(nDungeonID);
    SOCKET_REQUEST_END(SC_BATTLE_CHALLENGE, NULL);
}

void MB_AbsolvedInterface::recvbattle_challenge(MB_MsgBuffer* recvPacket)
{

}

void MB_AbsolvedInterface::sendbattle_rank()
{
    //發送間隔限制10秒
    static uint32_t nLastTime = 0;
    if (MB_ClientSocket::getInstance()->getServerTime() - nLastTime < 10)
    {
        return;
    }
    nLastTime = MB_ClientSocket::getInstance()->getServerTime();
    
    SOCKET_REQUEST_START(CS_BATTLE_RANK);
    packet->writeU8(1);
    packet->writeU8(1);
    packet->writeU8(50);
    SOCKET_REQUEST_END(SC_BATTLE_RANK, MB_AbsolvedInterface::onMsgRecv);
    MB_Message::sharedMB_Message()->showMessage("",15);
}
void MB_AbsolvedInterface::recvbattle_rank(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t type;
    uint16_t count = 0;
    recvPacket->readU8(&type);
    recvPacket->readU16(&count);
    
    m_pArrayRankInfo->removeAllObjects();
    for (int i = 0;i < count;i++)
    {
        MB_ChapterRankData* data = new MB_ChapterRankData();
        data->read(recvPacket);
        m_pArrayRankInfo->addObject(data);
        CC_SAFE_RELEASE_NULL(data);
    }
}
