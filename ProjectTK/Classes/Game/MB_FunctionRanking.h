//
//  MB_FunctionRanking.h
//  ProjectMB
//
//  Created by wenyong on 14-12-24.
//
//

#ifndef __ProjectMB__MB_FunctionRanking__
#define __ProjectMB__MB_FunctionRanking__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"

class MB_FunctionRanking : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionRanking();
    ~MB_FunctionRanking();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    static void send_rank_level();
    static void send_rank_power();
    static void send_rank_absolved();
    static void send_rank_arena();
    virtual void onLoadingScene(){};
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual CCArray* getArrayDataByType(int type);
    virtual uint8_t getOwnRank(uint8_t nType);
private:
    static void send_rank_info(uint8_t nType);
    CCArray*    m_pDataSource[4];
};

#endif /* defined(__ProjectMB__MB_FunctionRanking__) */
