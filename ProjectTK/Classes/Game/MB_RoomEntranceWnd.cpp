//
//  MB_RoomEntranceWnd.cpp
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#include "MB_RoomEntranceWnd.h"
#include "MB_RoomEntry.h"
#include "MB_RoleData.h"
#include "MB_LayerRuningCool.h"
#include "MB_TaskSystemInterface.h"
#include "MB_GiftsInterface.h"
MB_RoomEntranceWnd::MB_RoomEntranceWnd()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRoom",false);
    this->schedule(schedule_selector(MB_RoomEntranceWnd::tick),5);
}
MB_RoomEntranceWnd::~MB_RoomEntranceWnd()
{
}
bool MB_RoomEntranceWnd::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_RoomEntry*>(pDataSource);
    if (m_pDataSource)
    {
        return true;
    }
    return false;
}

void MB_RoomEntranceWnd::onResetWnd()
{
    MB_NodeCommandEntrance::onResetWnd();
    int nCount = 0;
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        nCount += pInterfaceTemp->getComplateTaskCount();
    }
    
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask ,&pInterface))
    {
        MB_TaskSystemInterface* pInterfaceTemp = dynamic_cast<MB_TaskSystemInterface*>(pInterface);
        nCount += pInterfaceTemp->getAchievementCompleteCount();
    }
    
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kActivatyGifts ,&pInterface))
    {
        MB_GiftsInterface* pInterfaceTemp = dynamic_cast<MB_GiftsInterface*>(pInterface);
        MB_DailyRewrdInfo* info = NULL;
        info = pInterfaceTemp->getInfoByType(eGiftTime);
        if (info) {
            nCount += info->getEnableCount();
        }
        info = pInterfaceTemp->getInfoByType(eGiftLevel);
        if (info) {
            nCount += info->getEnableCount();
        }
        info = pInterfaceTemp->getInfoByType(eGiftMLogin);
        if (info) {
            nCount += info->getEnableCount();
        }
    }
    
    if (0!=nCount)
    {
        m_pFlagNode2->setVisible(true);
        if (nCount>99) {
            m_pFlag2->setString("!");
        }else
        {
            char buff[25] = {};
            sprintf(buff, "%d",nCount);
            m_pFlag2->setString(buff);
        }
    }
    else
    {
        m_pFlagNode2->setVisible(false);
    }
}
void MB_RoomEntranceWnd::onMsgRecv(CCNode* node, SocketResponse* response)
{
}

void MB_RoomEntranceWnd::onEntranceClicked(CCObject* pSender)
{
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("MB_LayerRoom",false))
    {
        MB_NodeCommandEntrance::onEntranceClicked(this);
    }
}


void MB_RoomEntranceWnd::tick(float dt)
{
    MB_NodeCommandEntrance::tick(dt);
    onResetWnd();
}


