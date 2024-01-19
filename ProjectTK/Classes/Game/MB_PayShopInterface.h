//
//  MB_PayShopInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#ifndef __ProjectMB__MB_PayShopInterface__
#define __ProjectMB__MB_PayShopInterface__
#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
//神秘商店
class MB_PayShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_PayShopInterface();
    ~MB_PayShopInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onDayPassed();
    
    void cs_activity_day_pay_mul();
    CC_SYNTHESIZE(uint8_t , m_nDayPayMul , DayPayMul );//每日首冲翻倍倍数  0:未开启 1首充双倍

};

#endif /* defined(__ProjectMB__MB_PayShopInterface__) */
