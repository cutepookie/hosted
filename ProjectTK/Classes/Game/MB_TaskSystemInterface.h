//
//  MB_TaskSystemInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_TaskSystemInterface__
#define __ProjectMB__MB_TaskSystemInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_GlobelAchievementMsgQueue;
class MB_TaskServerData;

class MB_TaskSystemInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_TaskSystemInterface();
    ~MB_TaskSystemInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onLoadingScene();
    virtual void onEntryClicked(CCObject* pSender);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    uint32_t getMainTaskCount()const;
    uint32_t getDailyTaskCount()const;
    uint32_t getAchievementCount()const;
    
    MB_TaskServerData* getTaskServerDataById(uint32_t nTaskId);
    MB_TaskServerData* getTaskServerData(uint32_t nTaskId,uint16_t nType);
    
    MB_TaskServerData* getDailyTaskDataById(uint32_t nTaskId);
    MB_TaskServerData* getMainTaskDataById(uint32_t nTaskId);
    MB_TaskServerData* getAchievementTaskDataById(uint32_t nTaskId);
    
    void addDailyTaskData(MB_TaskServerData* pTask);
    void addMainTaskData(MB_TaskServerData* pTask);
    void addAchievementTaskData(MB_TaskServerData* pTask);
    
    MB_TaskServerData* getTaskServerDataByIndex(uint32_t nType,uint32_t nIndex)const;
    MB_TaskServerData* getDailyTaskDataByIndex(uint32_t nIndex)const;
    MB_TaskServerData* getMainTaskDataByIndex(uint32_t nIndex)const;
    MB_TaskServerData* getAchievementTaskDataByIndex(uint32_t nIndex)const;
    
    uint32_t getDailyTaskComplateCount()const;
    uint32_t getMainTaskComplateCount()const;
    uint32_t getAchievementCompleteCount()const;
    uint32_t getComplateTaskCount()const;
    uint32_t getTaskCountByType(uint32_t nType);
    
    bool deleteDailyTaskDataById(uint32_t nTaskId);
    bool deleteMainTaskDataById(uint32_t nTaskId);
    bool deleteAchievementTaskDataById(uint32_t nTaskId);
    
    void updateTask(MB_TaskServerData* pUpdateData,uint16_t nType);
    bool deleteTaskByTaskId(uint32_t nTaskId,uint16_t nType);
    void sendtask_operate(uint8_t nType,uint32_t nTaskId);
    
    void sortTask();
    bool getAchievementArray(CCArray* array,int type);
    CCArray* getTaskComplateArray(){return m_ArrayTaskComplate;};
    void playAchievementMsg();
    void msgQueueLock(){m_bMsgLocked=true;}
    void msgQueueUnlock(){m_bMsgLocked=false;}
    
    void delayPlay();
    void onDelayPlay(float dt);
protected:
    void sendtask_get_info();
    void recvtask_get_info(MB_MsgBuffer* recvPacket);

    void recvtask_operate(MB_MsgBuffer* recvPacket);
    void recvtask_error(MB_MsgBuffer* recvPacket);
    void recvtask_notify_change(MB_MsgBuffer* recvPacket);
    MB_GlobelAchievementMsgQueue*      m_pMsgQueue;
private:
    CCArray*            m_pAchievementList;
    CCArray*            m_pMainTaskList;
    CCArray*            m_pDailyTaskList;
    CCArray*            m_ArrayTaskComplate;
    bool                m_bMsgLocked;
    bool                m_bDelay;
};

#endif /* defined(__ProjectMB__MB_TaskSystemInterface__) */
