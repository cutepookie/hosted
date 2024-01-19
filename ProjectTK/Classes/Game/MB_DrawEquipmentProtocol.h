//
//  MB_DrawEquipmentProtocol.h
//  ProjectMB
//
//  Created by wenyong on 15-1-26.
//
//

#ifndef __ProjectMB__MB_DrawEquipmentProtocol__
#define __ProjectMB__MB_DrawEquipmentProtocol__

#include "MB_ServerData.h"
#define SEND_CARD_DISTROY 11101
#define P_CARD 11104
#define P_OPENED_CARD 11103
#define RECV_CARD_DISTROY 11102
#define SEND_CARD_DRAW 11105
#define RECV_CARD_DRAW 11106
#define SEND_CARD_REFRESH 11107
#define RECV_CARD_REFRESH 11108
#define SEND_CARD_ONEKEY 11120
#define RECV_CARD_ONEKEY 11121

/*
 message		p_card[id=11104]{
 required		int8					type				=1;//卡牌類型
 required		int32					value				=2;//卡牌數值
 // type=1 => 精靈ID
 // type=2 => 道具ID
 // type=3 => 元寶數量
 // type=4 => 银两數量
 // type=5 => 声望數量
 }
 */
class RewardTempleteValue;
class MB_DrawCardData : public MB_ServerData
{
public:
    MB_DrawCardData();
    virtual bool read(MB_MsgBuffer* pRecv);
    RewardTempleteValue* convertTemplateValue()const; // autorelease
    virtual bool operator==(const MB_DrawCardData& pData);
private:
    CC_SYNTHESIZE(bool, m_bDraw, isDraw);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nType, Type);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nValue, Value);
};

/*
 message 	p_opened_card[id=11103]{
 required		int8					pos					=1;//记录上次被翻出来時，卡片所在的位置,位置定义由客户端自行决定
 required		int8					type				=2;//卡牌類型
 required		int32					value				=3;//卡牌數值
 // type=1 => 武將ID
 // type=2 => 道具ID
 // type=3 => 元寶數量
 // type=4 => 银两數量
 // type=5 => 声望數量
 }
 */

class MB_CardHistory : public MB_DrawCardData
{
public:
    MB_CardHistory();
    virtual bool read(MB_MsgBuffer* pRecv);
    CC_SYNTHESIZE(uint8_t, m_nPos, Pos);
};
#endif /* defined(__ProjectMB__MB_DrawEquipmentProtocol__) */
