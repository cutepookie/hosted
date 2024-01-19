//
//  MB_FunctionKingInterface.h
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#ifndef __ProjectMB__MB_FunctionKingInterface__
#define __ProjectMB__MB_FunctionKingInterface__

#include "MB_FunctionModule.h"
class KingInfo;
class MB_FunctionKingInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionKingInterface();
    ~MB_FunctionKingInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    
    void cs_king_open();
    void sc_king_open(MB_MsgBuffer* pRecv);
    void sc_king_init_state(MB_MsgBuffer* pRecv);
    
    void cs_king_close();
    void sc_king_stop(MB_MsgBuffer* pRecv);
    
    void cs_king_fight();
    void sc_king_fight(MB_MsgBuffer* pRecv);
    
    void cs_king_open_time();
    void sc_king_open_time(MB_MsgBuffer* pRecv);
    
    void sc_king_hp_sync(MB_MsgBuffer* pRecv);
    
    void cs_king_reborn();
    bool getIsOpen();
    bool getHasBoss();
    KingInfo* getKingInfo(){return m_pKingInfo;};

protected:
    void setOpenStatus(bool bOpen);
    KingInfo* m_pKingInfo;
};

#endif /* defined(__ProjectMB__MB_FunctionKingInterface__) */
