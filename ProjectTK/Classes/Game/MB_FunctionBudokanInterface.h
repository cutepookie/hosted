//
//  MB_FunctionBudokanInterface.h
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#ifndef __ProjectMB__MB_FunctionBudokanInterface__
#define __ProjectMB__MB_FunctionBudokanInterface__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_BudokanProtocol.h"

class MB_FunctionBudokanInterface : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionBudokanInterface();
    ~MB_FunctionBudokanInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onEntryClicked(CCObject* pSender);
    
    bool getIsOpen();
    void sendbudokan_info();
    void recvbudokan_info(MB_MsgBuffer* pRecv);
    
    // 請求購買加成
    void sendbudokan_buy(uint8_t type);
    void recvbudokan_buy(MB_MsgBuffer* pRecv);
    
    // 請求戰鬥
    void sendbudokan_fight();
    void recvbudokan_fight(MB_MsgBuffer* pRecv);
    
    //一键扫塔
    void sendbuduokan_raids();
    void recvbudokan_raids(MB_MsgBuffer* pRecv);
    MB_BudokanData* getBudokanData(){return m_pBudokanData;};
    MB_BudokanConfig* getBudokanConfig(){return m_pBudokanConfig;};
private:
    MB_BudokanData*    m_pBudokanData;
    MB_BudokanConfig*  m_pBudokanConfig;
    
    int m_nBuyType;
    
};
#endif /* defined(__ProjectMB__MB_FunctionBudokanInterface__) */
