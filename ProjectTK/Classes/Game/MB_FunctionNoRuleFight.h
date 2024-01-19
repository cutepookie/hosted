//
//  MB_FunctionNoRuleFight.h
//  ProjectMB
//
//  Created by chk on 15-1-15.
//
//

#ifndef __ProjectMB__MB_FunctionNoRuleFight__
#define __ProjectMB__MB_FunctionNoRuleFight__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
#include "MB_NoRuleFightProtocol.h"
class MB_NoRuleInfo;
class MB_FunctionNoRuleFight : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionNoRuleFight();
    virtual ~MB_FunctionNoRuleFight();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual bool allowShow();
    virtual void onLoadingScene();
    virtual uint16_t getFunctionType();
    
    void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
public:
    void cs_melee_info();
    void sc_melee_info(MB_MsgBuffer*);
    
    void cs_melee_sign();
    void sc_melee_sign(MB_MsgBuffer*);
    
    void cs_melee_fight();
    void sc_melee_fight(MB_MsgBuffer*);
    
    ENoRuleState getState()
    {
        return (ENoRuleState)m_pNoRuleInfo->getState();
    }
    MB_NoRuleInfo* getNoRuleInfo(){return m_pNoRuleInfo;}
private:
    MB_NoRuleInfo* m_pNoRuleInfo;
};

#endif /* defined(__ProjectMB__MB_FunctionNoRuleFight__) */
