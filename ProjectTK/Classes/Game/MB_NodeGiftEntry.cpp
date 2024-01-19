//
//  MB_NodeGiftEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//
#include "MB_NodeGiftEntry.h"
#include "MB_GiftsInterface.h"
#include "MB_AbsolvedInterface.h"
MB_NodeGiftEntry::MB_NodeGiftEntry()
{
    this->schedule(schedule_selector(MB_NodeGiftEntry::tick),5);
}


MB_NodeGiftEntry::~MB_NodeGiftEntry()
{
    this->unschedule(schedule_selector(MB_NodeGiftEntry::tick));
}

void MB_NodeGiftEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    onResetWnd();
}

bool MB_NodeGiftEntry::init()
{
    MB_NodeHoverEntry::init();
    onResetWnd();
    return true;
}

void MB_NodeGiftEntry::tick(float dt)
{
    MB_NodeHoverEntry::tick(dt);
    onResetWnd();
}
void MB_NodeGiftEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
    
    MB_GiftsInterface* pInterface = dynamic_cast<MB_GiftsInterface*>(m_pDataSource);
    if(pInterface)
    {
        int count = 0;
        
        MB_DailyRewrdInfo* info = NULL;
        info = pInterface->getInfoByType(eGiftTime);
        if (info) {
            count += info->getEnableCount();
        }
        info = pInterface->getInfoByType(eGiftLevel);
        if (info) {
            count += info->getEnableCount();
        }
        info = pInterface->getInfoByType(eGiftMLogin);
        if (info) {
            count += info->getEnableCount();
        }

        if (count > 0)
        {
            m_pFlagNode2->setVisible(true);
            if (count>99) {
                m_pFlag2->setString("!");
            }else
            {
                char buff[32] = {};
                sprintf(buff,"%d",count);
                m_pFlag2->setString(buff);
            }
        }
        else
        {
            m_pFlagNode2->setVisible(false);
        }
    }
}

void MB_NodeGiftEntry::onEntranceClicked(CCObject* pSender)
{
    MB_GiftsInterface* pInterface = dynamic_cast<MB_GiftsInterface*>(m_pDataSource);
    if(pInterface)
    {
        MB_ResWindow* pLayer = pInterface->createFunctionDialog();
        if(pLayer)
        {
            MB_AbsolvedInterface::replaceMainSceneSubLayer(pLayer);
//            NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()->replaceLayer(pLayer);
        }
    }
//    onResetWnd();
}

