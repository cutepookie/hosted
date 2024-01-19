//
//  MB_FunctionTrainerRoad.h
//  ProjectMB
//
//  Created by wenyong on 15-1-15.
//
//

#ifndef __ProjectMB__MB_FunctionTrainerRoad__
#define __ProjectMB__MB_FunctionTrainerRoad__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_TrainerRoadProtocol.h"
class MB_FunctionTrainerRoad : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionTrainerRoad();
    virtual ~MB_FunctionTrainerRoad();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual void onLoadingScene();
    virtual uint16_t getFunctionType();
    
    void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
public:
    void send_road_info();
    void recv_road_info(MB_MsgBuffer*);
   
    void send_road_reset();
    void recv_road_reset(MB_MsgBuffer*);
    
    void send_road_fight(std::string);
    void recv_road_fight(MB_MsgBuffer*);
    
    void send_road_fight_ext(std::string);
    void recv_road_fight_ext(MB_MsgBuffer*);
    
    void send_road_box();
    void recv_road_box(MB_MsgBuffer*);
private:
    void recv_fight_reward(MB_MsgBuffer*);
private:
    
    CC_SYNTHESIZE_READONLY(uint8_t, m_nResetTimes, ResetTimes);//重置次數
    CC_SYNTHESIZE_READONLY(uint8_t, m_nCurID, CurID);//當前關卡ID，从101開始
    CC_SYNTHESIZE_READONLY(ERoadDungeonStatus, m_nStatus, Status);//關卡狀態，0未通關，1已通關，2已領取，只有最后一个關卡会出现已領取狀態，其余關卡只要領取了就跳轉為下一關卡未通關狀態
    CC_SYNTHESIZE_READONLY(uint8_t, m_nExtID, ExtID);//神秘關卡ID，0表示當前無神秘關卡
    
    std::string m_strGateName;
    
};

#endif /* defined(__ProjectMB__MB_FunctionTrainerRoad__) */
