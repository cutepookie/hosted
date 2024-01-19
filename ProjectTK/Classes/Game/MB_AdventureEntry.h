//
//  MB_AdventureEntry.h
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//探险進入接口

#ifndef __ProjectMB__MB_AdventureEntry__
#define __ProjectMB__MB_AdventureEntry__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_FunctionModule.h"
class MB_AdventureEntry : public NSGameFunction::CCFunctionInterface
{   
public:
    MB_AdventureEntry();
    ~MB_AdventureEntry();
    
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    //virtual void onEntryClicked(CCObject* pSender);
    
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    int getAutoVipLimit(){return m_pAutoVipLimit;};
    bool sendexplore_auto_explore_check();
    bool recvexplore_auto_explore_check(MB_MsgBuffer *recvPacket);
    void sendexplor_one();
private:
    uint8_t m_pAutoVipLimit;
};

#endif /* defined(__ProjectMB__MB_AdventureEntry__) */
