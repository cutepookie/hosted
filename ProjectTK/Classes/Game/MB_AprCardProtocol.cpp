//
//  MB_AprCardProtocol.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-3-10.
//
//

#include "MB_AprCardProtocol.h"
#include "MB_MsgBuffer.h"

/*
 message sc_activity_month[id=11914]{
 required    int32               dayPayGold          =1;//当日累計儲值寶石
 required    int8                leftDays            =2;//月卡剩余天數
 required    bool                isDraw              =3;//今日是否已經領取
 required    int16               needPayGold         =4;//購買月卡需要儲值寶石
 required    int16               monthPrice          =5;//購買月卡的寶石价格
 required    int16               dayGetGold          =6;//月卡每日可領取寶石
 }
 */
bool MB_AprCardData::read(MB_MsgBuffer* recvPacket)
{
    recvPacket->readU32(&m_uPayGold);
    recvPacket->readU8(&m_uLeftDay);
    recvPacket->readU8(&m_bIsDraw);
    recvPacket->readU16(&m_uNeedPayGold);
    recvPacket->readU16(&m_uMonthPrice);
    recvPacket->readU16(&m_uGetGold);
    return true;
}
