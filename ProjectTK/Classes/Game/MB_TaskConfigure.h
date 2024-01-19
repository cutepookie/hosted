//
//  MB_TaskConfigure.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef __ProjectMB__MB_TaskConfigure__
#define __ProjectMB__MB_TaskConfigure__

#include "MB_TaskSystemData.h"


/*
 <tasks>
    <task id="1001" type="1" name="出发，真新镇" description="完成关卡“妖精世界-出发真新镇" >
        <condition type="100" target="30001" value="1"/>
        <rewards>
            <reward typeid="3050" value="1"/>
            <reward typeid="3060" value="1"/>
        </rewards>
    </task>
 </tasks>
*/

enum ConditionType
{
    kConditionClearance = 100,
    kConditionKill      = 200,
    kConditionLevelUp   = 300,
    kConditionStrengthenEquip = 405,
    kConditionStrengthenMonster = 204,
    kConditionUnknow,
};
class MB_TaskConfigure
{
public:
    virtual ~MB_TaskConfigure();
    static MB_TaskConfigure* getInstance();
    static void destoryInstance();
    MB_TaskData* getTaskDataById(uint32_t nTid);
    int getTaskByType(CCArray* pOut,uint16_t nType);
protected:
    bool init(const char* pFile);
private:
    MB_TaskConfigure();
    static MB_TaskConfigure* m_pSingletonInstance;
    CCArray*        m_pArray;
};

#endif /* defined(__ProjectMB__MB_TaskConfigure__) */
