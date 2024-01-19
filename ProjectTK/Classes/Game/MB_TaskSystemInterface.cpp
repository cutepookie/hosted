//
//  MB_TaskSystemInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_TaskSystemInterface.h"
#include "MB_NodeTaskEntranceWnd.h"
#include "MB_LayerTaskMain.h"
#include "MB_FunctionModule.h"
#include "MB_TaskSystemProtocol.h"
#include "MB_TaskSystemData.h"
#include "MB_AchievementComplate.h"
#include "MB_TaskConfigure.h"
#include "MB_GlobelModalDlgMsgQueue.h"

#include "MB_TutorialMgr.h"
MB_TaskSystemInterface::MB_TaskSystemInterface()
{
    m_pMainTaskList = new CCArray;
    m_pDailyTaskList = new CCArray;
    m_pAchievementList = new CCArray;
    m_ArrayTaskComplate = new CCArray;
    m_pMsgQueue = new MB_GlobelAchievementMsgQueue;
    
    SOCKET_MSG_REGIST(SC_TASK_GET_INFO, MB_TaskSystemInterface);
    SOCKET_MSG_REGIST(SC_TASK_OPERATE, MB_TaskSystemInterface);
    SOCKET_MSG_REGIST(SC_TASK_ERROR, MB_TaskSystemInterface);
    SOCKET_MSG_REGIST(SC_TASK_NOTIFY, MB_TaskSystemInterface);
    m_bMsgLocked = true;
    m_bDelay = false;
}

MB_TaskSystemInterface::~MB_TaskSystemInterface()
{
    CC_SAFE_RELEASE_NULL(m_pDailyTaskList);
    CC_SAFE_RELEASE_NULL(m_pMainTaskList);
    CC_SAFE_RELEASE_NULL(m_pAchievementList);
    CC_SAFE_RELEASE_NULL(m_ArrayTaskComplate);
    CC_SAFE_RELEASE_NULL(m_pMsgQueue);
    SOCKET_MSG_UNREGIST(SC_TASK_GET_INFO);
    SOCKET_MSG_UNREGIST(SC_TASK_OPERATE);
    SOCKET_MSG_UNREGIST(SC_TASK_ERROR);
    SOCKET_MSG_UNREGIST(SC_TASK_NOTIFY);
}

MB_ResWindow* MB_TaskSystemInterface::createEntryDialog()
{
    MB_NodeTaskEntry* pInstance = new MB_NodeTaskEntry();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init() )
    {
        pInstance->setType(getFunctionType());
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

MB_ResWindow* MB_TaskSystemInterface::createFunctionDialog()
{
    MB_LayerTaskMain* pInstance = new MB_LayerTaskMain();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init() )
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}

bool MB_TaskSystemInterface::allowShow()
{
    return true;
}

uint16_t MB_TaskSystemInterface::getFunctionType()
{
    return kFunctionTask;
}

void MB_TaskSystemInterface::onLoadingScene()
{
    sendtask_get_info();
}

void MB_TaskSystemInterface::sendtask_get_info()
{
    SOCKET_REQUEST_START(CS_TASK_GET_INFO);
    SOCKET_REQUEST_END(SC_TASK_GET_INFO, MB_TaskSystemInterface::onMsgRecv);
}

/*
 message recvtask_get_info[id=20104]{
 repeated	p_task							main_task_list					=1;//主线任务
 repeated p_task							today_task_list				=2;//日常任务
 repeated	p_task							ach_task_list					=3;//成就
 }
 */
void MB_TaskSystemInterface::recvtask_get_info(MB_MsgBuffer* recvPacket)
{
    uint16_t u16 = 0;
    recvPacket->readU16(&u16);
    MB_TaskServerData* pData = NULL;
    
    for (uint16_t i=0; i<u16; ++i)
    {
        pData = new MB_TaskServerData;
        if (pData->read(recvPacket))
        {
            m_pMainTaskList->addObject(pData);
        }
        pData->release();
    }
    
    recvPacket->readU16(&u16);
    for (uint16_t i=0; i<u16; ++i)
    {
        pData = new MB_TaskServerData;
        if (pData->read(recvPacket))
        {
            m_pDailyTaskList->addObject(pData);
        }
        pData->release();
    }
    
    recvPacket->readU16(&u16);
    for (uint16_t i=0; i<u16; ++i)
    {
        pData = new MB_TaskServerData;
        if (pData->read(recvPacket))
        {
            if(pData->getTaskId() >= 20119
               && pData->getTaskId() <= 20125)
            {
                CCLOG("pData->getTaskId()%d",pData->getTaskId());
            }
            
                
            m_pAchievementList->addObject(pData);
        }
        pData->release();
    }
    
    MB_TaskServerData::sortTask(m_pMainTaskList);
    MB_TaskServerData::sortTask(m_pDailyTaskList);
    MB_TaskServerData::sortTask(m_pAchievementList);
}

void MB_TaskSystemInterface::sendtask_operate(uint8_t nType,uint32_t nTaskId)
{
    SOCKET_REQUEST_START(CS_TASK_OPERATE);
    packet->writeU8(nType);
    packet->writeU32(nTaskId);
    SOCKET_REQUEST_END(SC_TASK_OPERATE, MB_TaskSystemInterface::onMsgRecv);
}

/*
 //某个任务在某个状态的操作上获得的奖励
 message recvtask_operate[id=20106]{
 required	int8							task_type					=1;//1：主线任务  2：日常任务   3：成就
 required	int32						task_id						=2;
 required	int8							status						=3;//状态
 repeated	p_reward_view		reward						=4;//奖励信息
 }
 */
void MB_TaskSystemInterface::recvtask_operate(MB_MsgBuffer* recvPacket)
{
    uint32_t u32 = 0;
    uint8_t u8 = 0;
    uint8_t u8_satus = 0;
    recvPacket->readU8(&u8);
    recvPacket->readU32(&u32);
    recvPacket->readU8(&u8_satus);
    
//    MB_TaskServerData* pData = NULL;
//    
//    pData = getTaskServerData(u32,u8);
//    if (pData)
//    {
//        pData->setStatus(u8_satus);
//    }

}

/*
 //操作错误通知
 message recvtask_error[id=20107]{
 required	int8				result			=1;			//1:任务不存在, 2:等级不足,3：参数错误,4:状态操作不正确,5:操作时发生不可预知的错误
 }
 */
void MB_TaskSystemInterface::recvtask_error(MB_MsgBuffer* recvPacket)
{
    uint8_t error = 0;
    recvPacket->readU8(&error);
    // other operate with error number
}

/*
 //任务变化通知
 message recvtask_notify_change[id=20108]{
 required	int8				task_type				=1;					//1：主线任务  2：日常任务   3：成就
 repeated	p_task			updata_task_list	=2;					//更新认为(现有任务列表有就更新  没有就加上)
 repeated	int32			del_task_id			=3;					//要删除的任务的id列表
 }
 */
void MB_TaskSystemInterface::recvtask_notify_change(MB_MsgBuffer* recvPacket)
{
    uint8_t u8 = 0;
    recvPacket->readU8(&u8);
    uint16_t u16 = 0;
    recvPacket->readU16(&u16);
    MB_TaskServerData data;
    for (uint16_t i=0; i<u16; ++i)
    {
        data.read(recvPacket);
        updateTask(&data,u8);
    }
    
    recvPacket->readU16(&u16);
    uint32_t u32 = 0;
    for (uint16_t i=0; i<u16; ++i)
    {
        recvPacket->readU32(&u32);
        deleteTaskByTaskId(u32,u8);
    }
}

MB_TaskServerData* MB_TaskSystemInterface::getTaskServerDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    pTarget = getDailyTaskDataById(nTaskId);
    if (pTarget == NULL)
    {
        pTarget = getMainTaskDataById(nTaskId);
    }
    if (pTarget == NULL)
    {
        pTarget = getAchievementTaskDataById(nTaskId);
    }
    
    return pTarget;
}

MB_TaskServerData* MB_TaskSystemInterface::getDailyTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pDailyTaskList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            return pTarget;
        }
    }
    
    return NULL;
}

void MB_TaskSystemInterface::addDailyTaskData(MB_TaskServerData* pTask)
{
    if (pTask)
    {
        m_pDailyTaskList->addObject(pTask);
    }
}
void MB_TaskSystemInterface::addMainTaskData(MB_TaskServerData* pTask)
{
    if (pTask)
    {
        m_pMainTaskList->addObject(pTask);
    }
}
void MB_TaskSystemInterface::addAchievementTaskData(MB_TaskServerData* pTask)
{
    if (pTask)
    {
        m_pAchievementList->addObject(pTask);
    }
}
MB_TaskServerData* MB_TaskSystemInterface::getAchievementTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pAchievementList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            return pTarget;
        }
    }
    
    return NULL;
}
MB_TaskServerData* MB_TaskSystemInterface::getMainTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pMainTaskList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            return pTarget;
        }
    }
    
    return NULL;
}

MB_TaskServerData* MB_TaskSystemInterface::getTaskServerData(uint32_t nTaskId,uint16_t nType)
{
    MB_TaskServerData* pData = NULL;
    if (nType == kTaskMain)
    {
        pData = getMainTaskDataById(nTaskId);
    }
    else if(nType == kTaskDaily)
    {
        pData = getDailyTaskDataById(nTaskId);
    }
    else if(nType == kTaskAchievement)
    {
        pData = getAchievementTaskDataById(nTaskId);
    }

    return pData;
}
void MB_TaskSystemInterface::updateTask(MB_TaskServerData* pUpdateData,uint16_t nType)
{
    if (pUpdateData != NULL)
    {
        MB_TaskServerData* pData = NULL;
        if (nType == kTaskMain)
        {
            pData = getMainTaskDataById(pUpdateData->getTaskId());
            if (pData == NULL)
            {
                pData = new MB_TaskServerData;
                *pData = *pUpdateData;
                addMainTaskData(pData);
                pData->release();
                return;
            }
            else
            {
                *pData = *pUpdateData;
            }
        }
        else if (nType == kTaskDaily)
        {
            pData = getDailyTaskDataById(pUpdateData->getTaskId());
            
            
            if (pData == NULL)
            {
                pData = new MB_TaskServerData;
                *pData = *pUpdateData;
                addDailyTaskData(pData);
                pData->release();
                return;
            }
            else
            {
                *pData = *pUpdateData;
            }
        }
        else if(nType == kTaskAchievement)
        {
            pData = getAchievementTaskDataById(pUpdateData->getTaskId());
            if (pData == NULL)
            {
                pData = new MB_TaskServerData;
                *pData = *pUpdateData;
                addAchievementTaskData(pData);
                pData->release();
            }
            else
            {
                *pData = *pUpdateData;
            }
            
            
            if (pData->getStatus() == TASK_STATUS_COMPLATE)
            {
				//完成成就
                MB_AchievementComplate* pWnd = MB_AchievementComplate::create(pData);
                if (pWnd)
                {
                    m_pMsgQueue->addMsgWnd(pWnd);
                    delayPlay();
                }
            }
        }
    }
}


void MB_TaskSystemInterface::delayPlay()
{
    if (!m_bDelay)
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(MB_TaskSystemInterface::onDelayPlay), this, 3.0, false);
        m_bDelay = true;
    }
}

void MB_TaskSystemInterface::onDelayPlay(float dt)
{
    if(m_bMsgLocked)
    {
        msgQueueUnlock();
        playAchievementMsg();
    }
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MB_TaskSystemInterface::onDelayPlay), this);
    m_bDelay = false;
}

void MB_TaskSystemInterface::playAchievementMsg()
{
    if (m_bMsgLocked)
    {
        return;
    }
    if (m_pMsgQueue->msgCount()==0)
    {
        msgQueueLock();
        return;
    }
    m_pMsgQueue->popFront();
}


bool MB_TaskSystemInterface::deleteDailyTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pDailyTaskList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            m_pDailyTaskList->removeObject(pTarget);
            return true;
        }
    }
    
    return false;
}

bool MB_TaskSystemInterface::deleteMainTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pMainTaskList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            m_pMainTaskList->removeObject(pTarget);
            return true;
        }
    }
    
    return false;
}

bool MB_TaskSystemInterface::deleteAchievementTaskDataById(uint32_t nTaskId)
{
    MB_TaskServerData* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pAchievementList, MB_TaskServerData*, pTarget)
    {
        if (pTarget->getTaskId() == nTaskId)
        {
            m_pAchievementList->removeObject(pTarget);
            return true;
        }
    }
    
    return false;
}

bool MB_TaskSystemInterface::deleteTaskByTaskId(uint32_t nTaskId,uint16_t nType)
{
    if (nType == kTaskMain)
    {
        return deleteMainTaskDataById(nTaskId);
    }
    if (nType == kTaskDaily)
    {
        return deleteDailyTaskDataById(nTaskId);
    }
    if (nType == kTaskAchievement)
    {
        return deleteAchievementTaskDataById(nTaskId);
    }
    return false;
}

uint32_t MB_TaskSystemInterface::getDailyTaskComplateCount()const
{
    MB_TaskServerData* pData = NULL;

    uint32_t nCount = 0;
    CCARRAY_FOREACH_4TYPE(m_pDailyTaskList, MB_TaskServerData*, pData)
    {
        if (pData->getStatus() == TASK_STATUS_COMPLATE)
        {
            ++nCount;
        }
    }
    
    return nCount;
}

uint32_t MB_TaskSystemInterface::getMainTaskComplateCount()const
{
    MB_TaskServerData* pData = NULL;
    
    uint32_t nCount = 0;
    CCARRAY_FOREACH_4TYPE(m_pMainTaskList, MB_TaskServerData*, pData)
    {
        if (pData->getStatus() == TASK_STATUS_COMPLATE)
        {
            ++nCount;
        }
    }
    
    return nCount;
}

uint32_t MB_TaskSystemInterface::getAchievementCompleteCount()const
{
    MB_TaskServerData* pData = NULL;
    
    uint32_t nCount = 0;
    CCARRAY_FOREACH_4TYPE(m_pAchievementList, MB_TaskServerData*, pData)
    {
        if (pData->getStatus() == TASK_STATUS_COMPLATE)
        {
            ++nCount;
        }
    }
    
    return nCount;
}

uint32_t MB_TaskSystemInterface::getComplateTaskCount()const
{
    return getMainTaskComplateCount() + getDailyTaskComplateCount(); //+ getAchievementCompleteCount();
}

void MB_TaskSystemInterface::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
            //TODODO SC_TASK_GET_INFO这个协议不删除已完成任务
        case SC_TASK_GET_INFO:
            recvtask_get_info(recvPacket);
            break;
        case SC_TASK_OPERATE:
            recvtask_operate(recvPacket);
            break;
        case SC_TASK_ERROR:
            recvtask_error(recvPacket);
            break;
        case SC_TASK_NOTIFY:
            recvtask_notify_change(recvPacket);
            break;
        default:
            break;
    }

}

MB_TaskServerData* MB_TaskSystemInterface::getTaskServerDataByIndex(uint32_t nType,uint32_t nIndex)const
{
    if (nType == kTaskMain)
    {
        return getMainTaskDataByIndex(nIndex);
    }
    
    if (nType == kTaskDaily)
    {
        return getDailyTaskDataByIndex(nIndex);
    }
    
    if (nType == kTaskAchievement)
    {
        return getAchievementTaskDataByIndex(nIndex);
    }
    
    return NULL;
}

void MB_TaskSystemInterface::sortTask()
{
    MB_TaskServerData::sortTask(m_pMainTaskList);
    MB_TaskServerData::sortTask(m_pDailyTaskList);
    MB_TaskServerData::sortTask(m_pAchievementList);
}


MB_TaskServerData* MB_TaskSystemInterface::getDailyTaskDataByIndex(uint32_t nIndex)const
{
    if (nIndex >= m_pDailyTaskList->count())
    {
        return NULL;
    }
    
    return dynamic_cast<MB_TaskServerData*>(m_pDailyTaskList->objectAtIndex(nIndex));
}

MB_TaskServerData* MB_TaskSystemInterface::getMainTaskDataByIndex(uint32_t nIndex)const
{
    if (nIndex >= m_pMainTaskList->count())
    {
        return NULL;
    }
    
    return dynamic_cast<MB_TaskServerData*>(m_pMainTaskList->objectAtIndex(nIndex));
}

MB_TaskServerData* MB_TaskSystemInterface::getAchievementTaskDataByIndex(uint32_t nIndex)const
{
    if (nIndex >= m_pAchievementList->count())
    {
        return NULL;
    }
    
    return dynamic_cast<MB_TaskServerData*>(m_pAchievementList->objectAtIndex(nIndex));
}

void MB_TaskSystemInterface::onEntryClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_ResWindow* pMain = MB_TaskSystemInterface::createFunctionDialog();
    if (pMain)
    {
        replaceMainSceneSubLayer(pMain);
    }
}

uint32_t MB_TaskSystemInterface::getTaskCountByType(uint32_t nType)
{
    if (nType == kTaskDaily)
    {
        return m_pDailyTaskList->count();
    }
    if (nType == kTaskMain)
    {
        return m_pMainTaskList->count();
    }
    if (nType == kTaskAchievement)
    {
        return m_pAchievementList->count();
    }
    
    return 0;
}
uint32_t MB_TaskSystemInterface::getMainTaskCount()const
{
    return m_pMainTaskList->count();
}
uint32_t MB_TaskSystemInterface::getDailyTaskCount()const
{
    return m_pDailyTaskList->count();
}
uint32_t MB_TaskSystemInterface::getAchievementCount()const
{
    return m_pAchievementList->count();
}

bool MB_TaskSystemInterface::getAchievementArray(CCArray* array,int type)
{
    if (array == NULL) {
        return false;
    }
    if (type == 1)
    {
        MB_TaskServerData* pdata = NULL;
        CCARRAY_FOREACH_4TYPE(m_pAchievementList, MB_TaskServerData*, pdata)
        {
            if (pdata->getStatus() == TASK_STATUS_UNACCEPT || pdata->getStatus() == TASK_STATUS_ACCEPTED)
            {
                array->addObject(pdata);
                
            }
        }
        return true;
    }
    else if(type == 2)
    {
        MB_TaskServerData* pdata = NULL;
        CCARRAY_FOREACH_4TYPE(m_pAchievementList, MB_TaskServerData*, pdata)
        {
            if (pdata->getStatus() == TASK_STATUS_COMPLATE || pdata->getStatus() == TASK_STATUS_COMITED)
            {
                array->addObject(pdata);
                
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
