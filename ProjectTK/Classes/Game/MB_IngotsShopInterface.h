//
//  MB_IngotsShopInterface.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#ifndef __ProjectMB__MB_IngotsShopInterface__
#define __ProjectMB__MB_IngotsShopInterface__
#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
//神秘商店


#define SEND_DAILY_VIP_INFO 11013
#define RECV_DAILY_VIP_INFO 11014
#define SEND_DAILY_VIP_DRAW 11015
#define RECV_DAILY_VIP_DRAW 11016
class MB_MailReward;
class MB_IngotsShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_IngotsShopInterface();
    ~MB_IngotsShopInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onDayPassed();
    bool getReceived()const{return m_bReceived;}
    MB_MailReward* getReward()const{return m_pMailReward;}
    static void send_daily_vip_draw();
    virtual void onEntryClicked(CCObject* pSender);
protected:
    void send_daily_vip_info();
    void recv_daily_vip_info(MB_MsgBuffer* pRecv);
    
    void recv_daily_vip_draw(MB_MsgBuffer* pRecv);
private:
    bool        m_bReceived;
    MB_MailReward*    m_pMailReward;
};

#endif /* defined(__ProjectMB__MB_IngotsShopInterface__) */
