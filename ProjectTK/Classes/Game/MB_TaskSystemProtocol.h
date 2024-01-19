//
//  MB_TaskSystemProtocol.h
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#ifndef ProjectMB_MB_TaskSystemProtocol_h
#define ProjectMB_MB_TaskSystemProtocol_h


/*
 
 message		p_task[id=20101]{
 required	int32					task_id				=1;			//任务id
 required	int8						status				=2;			//任务状态  1:未接  2：已接  3：已完成 4:已提交（用于每日任务和成就的显示）
 required	int32					trigpet_num	=4;			//触发了的个数（比如当前杀了多少个怪）
 }
 
 //得到任务数据
 message sendtask_get_info[id=20103]{
 }
 message recvtask_get_info[id=20104]{
 repeated	p_task							main_task_list					=1;//主线任务
 repeated p_task							today_task_list				=2;//日常任务
 repeated	p_task							ach_task_list					=3;//成就
 }
 //接受和提交任务
 message sendtask_operate[id=20105]{
 required	int8				operate_code			=1; //1接受任务  2提交任务
 required	int32			task_id						=2;
 }
 //某个任务在某个状态的操作上获得的奖励
 message recvtask_operate[id=20106]{
 required	int8							task_type					=1;//1：主线任务  2：日常任务   3：成就
 required	int32						task_id						=2;
 required	int8							status						=3;//状态
 repeated	p_reward_view		reward						=4;//奖励信息
 }
 //操作错误通知
 message recvtask_error[id=20107]{
 required	int8				result			=1;			//1:任务不存在, 2:等级不足,3：参数错误,4:状态操作不正确,5:操作时发生不可预知的错误
 }
 //任务变化通知
 message recvtask_notify_change[id=20108]{
 required	int8				task_type				=1;					//1：主线任务  2：日常任务   3：成就
 repeated	p_task			updata_task_list	=2;					//更新认为(现有任务列表有就更新  没有就加上)
 repeated	int32			del_task_id			=3;					//要删除的任务的id列表
 }
 */

#define P_TASK              20101

#define CS_TASK_GET_INFO    20103

#define SC_TASK_GET_INFO    20104

#define CS_TASK_OPERATE     20105

#define SC_TASK_OPERATE     20106

#define SC_TASK_ERROR       20107

#define SC_TASK_NOTIFY      20108

enum TaskType
{
    kTaskMain = 1,
    kTaskDaily = 2,
    kTaskAchievement = 3,
    kTaskUnknow
};
#endif
