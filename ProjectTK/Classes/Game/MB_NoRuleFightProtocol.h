//
//  MB_NoRuleFightProtocol.h
//  ProjectMB
//
//  Created by chk on 15-1-16.
//
//

#ifndef __ProjectMB__MB_NoRuleFightProtocol__
#define __ProjectMB__MB_NoRuleFightProtocol__
#include "MB_ServerData.h"
#include "MB_MsgBuffer.h"


//message cs_melee_info[id=20301,route=melee_server]{
//}
//
//message sc_melee_info[id=20302]{
//required	int8		leftTimes		=1;//剩余报名次数
//required    int8    	melee_status    =2;//混斗状态（1: 未报名; 2: 已报名; 3: 战场已开始）
//required	int32		countdown		=3;//倒计时
//required 	int32		miaomiao_score	=4;//喵喵积分
//required	int32		pipi_score		=5;//皮卡丘积分
//required	int16		self_score		=6;//贡献积分
//required	int8		camp			=7;//所属阵营 (1:喵喵阵营； 2:皮卡丘阵营)
//required	int8		cur_win_times	=8;//当前连胜次数
//}

class MB_NoRuleInfo:public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* pRecv)
    {
        pRecv->readU8(&m_nLeftTimes);
        pRecv->readU8(&m_nState);
        pRecv->readU32(&m_nCountdown);
        pRecv->readU32(&m_nTeam0Score);
        pRecv->readU32(&m_nTeam1Score);
        pRecv->readU16(&m_nSelfScore);
        pRecv->readU8(&m_nSelfTeam);
        pRecv->readU8(&m_nWinCount);
        return true;
    }
private:
    CC_SYNTHESIZE_READONLY(uint8_t, m_nLeftTimes, LeftTimes);
    CC_SYNTHESIZE(uint8_t, m_nState, State);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nCountdown, Countdown);
    CC_SYNTHESIZE(uint32_t, m_nTeam0Score, Team0Score);
    CC_SYNTHESIZE(uint32_t, m_nTeam1Score, Team1Score);
    CC_SYNTHESIZE(uint16_t, m_nSelfScore, SelfScore);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nSelfTeam, SelfTeam);
    CC_SYNTHESIZE(uint8_t, m_nWinCount, WinCount);
};

////报名
//message cs_melee_sign[id=20303]{
//}
//
//message sc_melee_sign[id=20304]{
//    required 	int8		result			=1;//报名结果（0:报名成功; 1:等级不足; 2:暂未开始报名）
//}
//
//message cs_melee_fight[id=20305]{
//}
//
//message sc_melee_fight[id=20306,route=melee_server]{
//    required 		int8 				result			=1;// 0成功,1等级不够，2功能未开放,3等待复活中 4 未报名,5 没有找到对手,6 战斗结果异常
//    required		int16				add_score		=2;//获得的积分
//    required		int32				miaomiao_score	=3;//喵喵积分
//    required		int32				pipi_score		=4;//皮卡丘积分
//    required        p_mail_reward       reward          =5;// 连胜奖励
//    repeated		sc_fight_request 	fightInfo		=6;// 战斗录像，列表长度最多为1个
//}



#define CS_MELEE_INFO 20301
#define SC_MELEE_INFO 20302
#define CS_MELEE_SIGN 20303
#define SC_MELEE_SIGN 20304
#define CS_MELEE_FIGHT 20305
#define SC_MELEE_FIGHT 20306


enum ENoRuleState
{
    NORULE_NOT_SIGN = 1,    //未报名
    NORULE_SIGNED,          //已报名
    NORULE_FIGHT_BEGIN      //战场已开始
};

#endif /* defined(__ProjectMB__MB_NoRuleFightProtocol__) */
