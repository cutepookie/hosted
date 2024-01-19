//
//  MB_ToyShopInterface.h
//  ProjectPM
//
//  Created by chk on 14-4-10.
//
//

#ifndef __ProjectMB__MB_ToyShopInterface__
#define __ProjectMB__MB_ToyShopInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_DrawCardData;
class MB_ToyShopInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_ToyShopInterface();
    ~MB_ToyShopInterface();
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    
    virtual void onLoadingScene();
    virtual uint16_t getFunctionType();
    
    void send_card_distroy();
    void recv_card_distroy(MB_MsgBuffer* pRecv);
    
    void send_card_refresh();
    void recv_card_refresh(MB_MsgBuffer* pRecv);
    
    void send_card_draw(uint8_t pos);
    void recv_card_draw(MB_MsgBuffer* pRecv);
    
    int getNeedItemNums(){return m_nOpendCount<6?m_pNeedItemNums[m_nOpendCount]:0;}
private:
    CC_SYNTHESIZE_READONLY(CCArray*, m_pCardList, CardList);
    CC_SYNTHESIZE_READONLY(bool, m_isDrawEquipOpen, isDrawEquipOpen);
    CC_SYNTHESIZE_READONLY(uint8_t,m_nOpendCount,OpendCount);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nItemPrice, ItemPrice);
    char m_pNeedItemNums[8];
    virtual void onEntryClicked(CCObject* pSender);
};



#endif /* defined(__ProjectMB__MB_ToyShopInterface__) */
