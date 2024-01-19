//
//  MB_AprCardProtocol.h
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#ifndef __ProjectMB__MB_AprCardProtocol__
#define __ProjectMB__MB_AprCardProtocol__

#include "MB_ServerData.h"


#define CS_ACTIVITY_MONTH   11913   
#define SC_ACTIVITY_MONTH   11914
#define CS_ACTIVITY_MONTH_BUY   11915
#define SC_ACTIVITY_MONTH_BUY   11916   
#define CS_ACTIVITY_MONTH_DRAW  11917
#define SC_ACTIVITT_MONTH_DRAW  11918


const std::string aprcard_status_notify = "aprcard_open_status_changed";
class MB_AprCardData : public MB_ServerData
{
public:
    virtual bool read(MB_MsgBuffer* recvPacket);
protected:
    CC_SYNTHESIZE(uint32_t,m_uPayGold, PayGold);   //当日累計儲值寶石3;
    CC_SYNTHESIZE(uint8_t,m_uLeftDay, LeftDay);     //月卡剩余天數
    CC_SYNTHESIZE(bool,m_bIsDraw, IsDraw);          //今日是否已經領取
    CC_SYNTHESIZE(uint16_t,m_uNeedPayGold, NeedPayGold);//購買月卡需要儲值寶石
    CC_SYNTHESIZE(uint16_t,m_uMonthPrice, MonthPrice);  //購買月卡的寶石价格
    CC_SYNTHESIZE(uint16_t,m_uGetGold, GetGold);        //月卡每日可領取寶石
};

    
    
#endif /* defined(__ProjectMB__MB_AprCardProtocol__) */
