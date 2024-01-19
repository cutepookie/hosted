//
//  MB_FunctionTrainerTroveInterface.h
//  ProjectMB
//
//  Created by yuanwugang on 15-2-27.
//
//

#ifndef __ProjectMB__MB_FunctionTrainerTroveInterface__
#define __ProjectMB__MB_FunctionTrainerTroveInterface__



#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_TrainerTroveProtocol.h"

class MB_BattleCoinData;
class MB_FunctionTrainerTroveInterface : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionTrainerTroveInterface();
    ~MB_FunctionTrainerTroveInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();

    void sendBattleCoinInfo();
    void recvBattleCoinInfo(MB_MsgBuffer* pRecv);
    void sendBattleCoinFight(uint8_t type);
    void recvBattleCoinFight(MB_MsgBuffer* pRecv);

    int getFightCount();
    int getCoolDown();
    
private:
    MB_BattleCoinData* m_pData;
};

#endif /* defined(__ProjectMB__MB_FunctionTrainerTroveInterface__) */
