//
//  MB_Championship.h
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#ifndef __ProjectMB__MB_Championship__
#define __ProjectMB__MB_Championship__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

//PVP 爭霸
class MB_Championship:public NSGameFunction::CCFunctionInterface
{
public:
    MB_Championship();
    ~MB_Championship();
public:
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    
    virtual void onLoadingScene(){};
    virtual void onMsgRecv(CCNode* node, SocketResponse* response){};
    virtual uint16_t getFunctionType();
    
    virtual void onEntryClicked(CCObject* pSender);
    
    void sendpvp_get_first_eight_replays();                              //
    void sendpvp_eight_replay(uint64_t uid);                             //八强戰鬥重播
    
    CC_SYNTHESIZE(uint64_t, m_nFightReplayUID,FightReplayUID);          //八强选中的戰鬥ID，用於重播戰鬥
protected:
};

#endif /* defined(__ProjectMB__MB_Championship__) */
