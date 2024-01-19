//
//  MB_ComposeMgr.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_ComposeMgr.h"
#include "MB_ComposeTemplate.h"

MB_ComposeMgr* MB_ComposeMgr::m_pSingletonInstance = NULL;

MB_ComposeMgr::MB_ComposeMgr()
{
    SOCKET_MSG_REGIST(SC_COMBINE_FAIL, MB_ComposeMgr);
    SOCKET_MSG_REGIST(SC_COMBINE_GER,MB_ComposeMgr);
    SOCKET_MSG_REGIST(SC_COMBINE_EQUIP,MB_ComposeMgr);
}

MB_ComposeMgr::~MB_ComposeMgr()
{
    std::map<uint16_t, MB_ComposeTemplate*>::iterator it = m_pComposeContainer.begin();

    for (;it!=m_pComposeContainer.end(); ++it)
    {
        CC_SAFE_RELEASE_NULL(it->second);
    }

    SOCKET_MSG_UNREGIST(SC_COMBINE_FAIL);
    SOCKET_MSG_UNREGIST(SC_COMBINE_GER);
    SOCKET_MSG_UNREGIST(SC_COMBINE_EQUIP);
    m_pComposeContainer.clear();
    m_RandomConbineCosts.clear();
}

MB_ComposeMgr* MB_ComposeMgr::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_ComposeMgr;
        if (!m_pSingletonInstance->init())
        {
            CCLog("[Error]:failed to init compose manapet!");
        }
    }

    return m_pSingletonInstance;
}

void MB_ComposeMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSingletonInstance);
}


bool MB_ComposeMgr::init()
{
    MB_XmlFile* pFile2 = MB_XmlFile::create("config/item/combine.xml");
//    MB_XmlFile* pFile2 = MB_XmlFile::create("config/item/RandomCombine.xml");
    if ( pFile2 == NULL)
    {
        return false;
    }

    CCArray* pArray = CCArray::create();
//    if (!pFile->queryNodesByName("Composes|compose", pArray))
//    {
//        return false;
//    }
//
    MB_XmlNode* pChild = NULL;
//    MB_ComposeTemplate* pTemplate = NULL;
//
//    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pChild)
//    {
//        pTemplate = new MB_ComposeTemplate;
//        if (pTemplate->init(pChild))
//        {
//            m_pComposeContainer[pTemplate->getComposeID()] = pTemplate;
//        }
//    }

    /*
     <RandomCombine>
     <Monster>
     <Combine star="" cost="" />
     </Monster>
     <Item>
     <Combine star="" cost="" />
     </Item>
     </RandomCombine>
     */
    pArray->removeAllObjects();
    pFile2->queryNodesByName("RandomCombine|Monster|Combine", pArray);
    uint16_t star = 0;
    uint64_t cost = 0;
    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pChild)
    {
        star = pChild->queryAttributeByName("star")->intValue() + 1 * 1000;
        cost = pChild->queryAttributeByName("cost")->intValue();
        m_RandomConbineCosts[star] = cost;
    }

    pArray->removeAllObjects();
    pFile2->queryNodesByName("RandomCombine|Item|Combine", pArray);
    star = 0;
    cost = 0;
    CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pChild)
    {
        star = pChild->queryAttributeByName("star")->intValue() + 2 * 1000;
        cost = pChild->queryAttributeByName("cost")->intValue();
        m_RandomConbineCosts[star] = cost;
    }

    return true;
}

// type 1 == pet
// type 2 == item
uint64_t MB_ComposeMgr::getRandomCombine(int nStar,int nType)
{
    return m_RandomConbineCosts[nStar + nType * 1000];
}

MB_ComposeTemplate* MB_ComposeMgr::getComposeTemplateByID(uint16_t nID)
{
    return m_pComposeContainer[nID];
}

void MB_ComposeMgr::sendcombine_do(uint8_t nCombineType,
                                  uint16_t nComposeID,
                                  uint8_t nComposeType,
                                  uint64_t* pUidList,
                                  uint16_t nCount)
{
    SOCKET_REQUEST_START(CS_COMBINE_DO);
    packet->writeU8(nCombineType);
    packet->writeU16(nComposeID);
    packet->writeU8(nComposeType);
    packet->writeU16(nCount);

    for (uint16_t i=0; i<nCount; ++i)
    {
        uint64_t u64 = pUidList[i];
        packet->WriteUINT64(u64);
    }
    SOCKET_REQUEST_END(SC_COMBINE_FAIL, MB_ComposeMgr::onMsgRecv);
}

void MB_ComposeMgr::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_COMBINE_GER:
            recvcombine_pet(recvPacket);
            break;
        case SC_COMBINE_EQUIP:
            recvcombine_equip(recvPacket);
            break;
        case SC_COMBINE_FAIL:
            recvcombine_fail(recvPacket);
            break;
        default:
            break;
    }
}

void MB_ComposeMgr::recvcombine_fail(MB_MsgBuffer* pbuff)
{

}

void MB_ComposeMgr::recvcombine_pet(MB_MsgBuffer* pbuff)
{

}

void MB_ComposeMgr::recvcombine_equip(MB_MsgBuffer* pbuff)
{

}
