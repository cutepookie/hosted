//
//  MB_ComposeInterface.h
//  ProjectPM
//
//  Created by WenYong on 14-4-11.
//
//

#ifndef __ProjectMB__MB_ComposeInterface__
#define __ProjectMB__MB_ComposeInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_ComposeInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_ComposeInterface();
    ~MB_ComposeInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    void sendcombine_info();
    void recvcombine_info(MB_MsgBuffer* pRecv);
    bool isLuckyItemStar(int star)const;
    bool isLuckyPetStar(int star)const;
    bool isLuckyTime()const;
private:
    CC_SYNTHESIZE_READONLY(uint32_t, m_nStopTime, StopTime);
    CC_SYNTHESIZE_READONLY(std::string, m_szContent, Content);
    uint8_t m_nItemLuckyStar[7];
    uint8_t m_nPetLuckyStar[7];
};

#endif /* defined(__ProjectMB__MB_ComposeInterface__) */
