//
//  MB_NodeConfigActivatyEntry.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-12.
//
//

#include "MB_NodeConfigActivatyEntry.h"
#include "MB_ConfigActivatyInterface.h"
#include "MB_ActivatyMgr.h"
#include "MB_ActivatyMainLayer.h"
#include "MB_MoneyEevntData.h"

MB_NodeConfigActivatyEntry::MB_NodeConfigActivatyEntry(int eventID)
{
    m_nEventID = eventID;
}


MB_NodeConfigActivatyEntry::~MB_NodeConfigActivatyEntry()
{
}


bool MB_NodeConfigActivatyEntry::init()
{
    if(MB_NodeSubActivatyEntry::init() == false)
    {
        return false;
    }
    
//    m_pFrameNormal = ((CCSprite*)m_pMenuItem->getNormalImage())->displayFrame();
//    m_pFrameSelect = ((CCSprite*)m_pMenuItem->getSelectedImage())->displayFrame();
//    m_pFrameNormal->retain();
//    m_pFrameSelect->retain();

    MB_MoneyEevntData* pEventData = NULL;
    CCARRAY_FOREACH_4TYPE(MB_MoneyEevntMgr::getInstance()->getEventList(), MB_MoneyEevntData*, pEventData)
    {
        if(pEventData->getActivityID() == m_nEventID)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("activities.plist");
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pEventData->getIconRrc());
            if(frame)
            {
                m_pIcon->setDisplayFrame(frame);
            }
            m_pName->setString( pEventData->getActivyName());
            break;
        }
    }
    return true;
}

void MB_NodeConfigActivatyEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
}

void MB_NodeConfigActivatyEntry::onEntranceClicked(CCObject* pSender)
{
    MB_ConfigActivatyInterface* pInterface = dynamic_cast<MB_ConfigActivatyInterface*>(m_pDataSource);
    if(pInterface)
    {
        MB_MoneyEevntData * data = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(m_nEventID);
        if(data != NULL)
        {
            if (m_pMainWnd)
            {
                m_pMainWnd->movetoShow(m_nEventID);
            }
            
            if(data->getUnitList()->count() > 0 )
            {
                MB_Message::sharedMB_Message()->removeALLMessage();
//                MB_ResWindow* pLayer = pInterface->getCurrentFunctionWnd();
                
//                MB_TARGET_PARENT(MB_ActivatyMainLayer, pLayer);
//                if(pLayer)
                {
//                    MB_ActivatyMainLayer* pActivatyMainLayer = dynamic_cast<MB_ActivatyMainLayer*>(pLayer);
                    if (m_pMainWnd)
                    {
                        m_pMainWnd->setCurActivaty(pInterface->createFunctionDialog(m_nEventID));
                    }

                }
            }
            else
            {
                MB_MoneyEevntMgr::getInstance()->sendactivity_info(m_nEventID);
            }
        }
        MB_ActivatyMgr::getInstance()->lockEntry(this);
    }
}

