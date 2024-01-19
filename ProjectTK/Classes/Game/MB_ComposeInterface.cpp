//
//  MB_ComposeInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#include "MB_ComposeInterface.h"
#include "MB_NodeComposeEntry.h"
#include "MB_FunctionModule.h"
#include "MB_LayerComposeMain.h"
#define CS_COMBINE_INFO 13207
#define SC_COMBINE_INFO 13208
MB_ComposeInterface::MB_ComposeInterface()
{
    m_nStopTime = 0;
    SOCKET_MSG_REGIST(SC_COMBINE_INFO, MB_ComposeInterface);
    for (int i=0; i<7; ++i)
    {
        m_nItemLuckyStar[i] = 0;
        m_nPetLuckyStar[i] = 0;
    }
}
MB_ComposeInterface::~MB_ComposeInterface()
{
    SOCKET_MSG_UNREGIST(SC_COMBINE_INFO);
}
MB_ResWindow* MB_ComposeInterface::createEntryDialog()
{
    MB_NodeComposeEntry* pInstance = new MB_NodeComposeEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_ComposeInterface::createFunctionDialog()
{
    MB_LayerComposeMain* pInstance = new MB_LayerComposeMain;
    if(pInstance && pInstance->init())
    {
        pInstance->setDataSource(this);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

void MB_ComposeInterface::onLoadingScene()
{
    sendcombine_info();
}

void MB_ComposeInterface::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == SC_COMBINE_INFO)
    {
        recvcombine_info(pRecv);
    }
}

bool MB_ComposeInterface::allowShow()
{
    return true;
}

uint16_t MB_ComposeInterface::getFunctionType()
{
    return kFunctionCompose;
}

/*
 message sendcombine_info[id=13207]{
 
 }

 */

void MB_ComposeInterface::sendcombine_info()
{
    SOCKET_REQUEST_START(CS_COMBINE_INFO);
    SOCKET_REQUEST_END(SC_COMBINE_INFO, NULL);
}

/*
 message recvcombine_info[id=13208]{
 required        int32           stopTime                = 1;
 required        string          content                 = 2;
 repeated        int8            petStarList             = 3;
 repeated        int8            equipStarList           = 4;
 }
 */
void MB_ComposeInterface::recvcombine_info(MB_MsgBuffer* pRecv)
{
    pRecv->readU32(&m_nStopTime);
    char * p = pRecv->ReadString();
    if (p)
    {
        m_szContent = p;
        CC_SAFE_FREE(p);
    }
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    count = count > 7 ? 7 : count;
    
    for (uint16_t i=0; i<count; ++i)
    {
        pRecv->readU8(&m_nPetLuckyStar[i]);
    }
    
    pRecv->readU16(&count);
    count = count > 7 ? 7 : count;
    
    for (uint16_t i=0; i<count; ++i)
    {
        pRecv->readU8(&m_nItemLuckyStar[i]);
    }
}
bool MB_ComposeInterface::isLuckyTime()const
{
    return m_nStopTime > MB_ClientSocket::getInstance()->getServerTime();
}
bool MB_ComposeInterface::isLuckyItemStar(int star)const
{
    if (star<=0 || star >7 || !isLuckyTime())
    {
        return false;
    }
    
    for (int i=0; i<7; ++i)
    {
        if (m_nItemLuckyStar[i]==star)
        {
            return true;
        }
    }
    
    return false;
}

bool MB_ComposeInterface::isLuckyPetStar(int star)const
{
    if (star<=0 || star >7 || !isLuckyTime())
    {
        return false;
    }
    
    for (int i=0; i<7; ++i)
    {
        if (m_nPetLuckyStar[i]==star)
        {
            return true;
        }
    }
    
    return false;
}