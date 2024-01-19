//
//  MB_TaskSystemData.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_TaskSystemData__
#define __ProjectMB__MB_TaskSystemData__

#include "../Common/GameLib/CCGameLib.h"
#include "MB_ServerData.h"

/*//任务状态  1:未接  2：已接  3：已完成 4:已提交（用于每日任务和成就的显示）*/
#define TASK_STATUS_UNACCEPT    1
#define TASK_STATUS_ACCEPTED    2
#define TASK_STATUS_COMPLATE    3
#define TASK_STATUS_COMITED     4

#define TASK_OPERATE_ACCEPTE    1
#define TASK_OPERATE_COMMIT     2


/*<condition type="100" target="30001" value="1"/>*/
class MB_TaskCondition:public CCObject
{
public:
    MB_TaskCondition();
    static MB_TaskCondition* create(MB_XmlNode* pNode);
    bool init(const MB_XmlNode* pNode);
    bool init(uint16_t nType,uint16_t nTarget,uint64_t nValue,uint16_t nShowType);
    
private:
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType, Type);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTarget, Target);
    CC_SYNTHESIZE_READONLY(uint64_t, m_nValue, Value);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nShowType, ShowType);
};

/*<reward typeid="3050" value="1"/>*/
class MB_TaskReward:public CCObject
{
public:
    MB_TaskReward();
    static MB_TaskReward* create(MB_XmlNode* pNode);
    bool init(MB_XmlNode* pNode);
    static MB_TaskReward* create(uint16_t nTid,uint32_t nValue,uint16_t nType);
    bool init(uint16_t nTid,uint32_t nValue,uint16_t nType);
    CCNode* createRewardNode();
    void setIcon(CCSprite* sprite);
private:
    CC_SYNTHESIZE_READONLY(uint16_t,m_nTid,TypeID);
    CC_SYNTHESIZE_READONLY(uint32_t,m_nValue,Value);
    CC_SYNTHESIZE_READONLY(uint16_t,m_nRewardType,RewardType);
};


/*
 <task id="1001" type="1" name="出发，真新镇" description="完成关卡“妖精世界-出发真新镇" >
    <condition type="100" target="30001" value="1"/>
    <rewards>
        <reward typeid="3050" value="1"/>
        <reward typeid="3060" value="1"/>
    </rewards>
 </task>
 */
class MB_TaskData:public CCObject
{
public:
    MB_TaskData();
    virtual ~MB_TaskData();
    static MB_TaskData* create(MB_XmlNode* pNode);
    bool init(MB_XmlNode* pNode);
    CCArray* getTaskRewardArray();
    MB_TaskCondition* getTaskCondition();
    CCNode* createRewardNode();
    void setRewardIcon(CCSprite* sprite);
    void setAchievmentIcon(CCSprite* sprite);
private:
    CCArray*            m_pReward;
    MB_TaskCondition*   m_pCondition;
    CC_SYNTHESIZE_READONLY(uint32_t, m_nTypeId, TypeId);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nType,  Type);
    CC_SYNTHESIZE_READONLY(std::string, m_szName, Name);
    CC_SYNTHESIZE_READONLY(std::string, m_szDescription, Description);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nChangePageID, ChangePageID);
    CC_SYNTHESIZE_READONLY(std::string, m_szIcon, Icon);
};


class MB_TaskServerData:public MB_ServerData
{
public:
    MB_TaskServerData();
    virtual ~MB_TaskServerData();
    virtual bool read(MB_MsgBuffer* recvPacket);
    MB_TaskServerData& operator=(const MB_TaskServerData& right);
private:
    CC_SYNTHESIZE(uint32_t, m_nTaskId, TaskId);
    CC_SYNTHESIZE(uint8_t, m_nStatus, Status);
    CC_SYNTHESIZE(uint32_t, m_nValue, Value);
    
public:
    static bool less(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1);
    static void sortTask(CCArray* in_pCcArrTasks);
};







#endif /* defined(__ProjectMB__MB_TaskSystemData__) */
