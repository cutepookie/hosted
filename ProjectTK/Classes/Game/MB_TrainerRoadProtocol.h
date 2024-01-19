//
//  MB_TrainerRoadProtocol.h
//  ProjectMB
//
//  Created by wenyong on 15-1-16.
//
//

#ifndef __ProjectMB__MB_TrainerRoadProtocol__
#define __ProjectMB__MB_TrainerRoadProtocol__
#include "MB_ServerData.h"
#include "MB_MsgBuffer.h"


#define CS_ROAD_INFO 14101
#define SC_ROAD_INFO 14102
#define CS_ROAD_RESET 14103
#define SC_ROAD_RESET 14104
#define CS_ROAD_FIGHT 14105
#define SC_ROAD_FIGHT 14106
#define CS_ROAD_FIGHT_EXT 14107
#define SC_ROAD_FIGHT_EXT 14108
#define CS_ROAD_BOX 14109
#define SC_ROAD_BOX 14110

enum ERoadDungeonStatus
{
    //关卡状态，0未通关，1已通关，2已领取，只有最后一个关卡会出现已领取状态，其余关卡只要领取了就跳转为下一关卡未通关状态
    DUNGEON_NOT_PASS = 0,
    DUNGEON_PASSED,
    DUNGEON_REWARDED
};

enum ERoadBoxStatus
{
    BOX_ACTIVATED,  //激活
    BOX_NOT_ACTIVATED,//未激活
    BOX_ACTIVATED_REWARDED,//已领取
};


#define ROLE_BEGIN_ID 101

#endif /* defined(__ProjectMB__MB_TrainerRoadProtocol__) */
