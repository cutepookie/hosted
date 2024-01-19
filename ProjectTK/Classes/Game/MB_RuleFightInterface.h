//
//  MB_RuleFightInterface.h
//  ProjectPM
//
//  Created by chk
//
//

#ifndef __ProjectMB__MB_RuleFightInterface__
#define __ProjectMB__MB_RuleFightInterface__

#include "MB_FunctionModule.h"
#include "MB_RuleFightProtocol.h"
#include "MB_RuleFightDataSource.h"

class MB_LayerRuleFight;
class SResultData;
class MB_RuleFightInterface:public NSGameFunction::CCFunctionInterface
{
public:
    MB_RuleFightInterface();
    ~MB_RuleFightInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onLoadingScene();
    
    void cs_rule_info();
    void cs_rule_rank();
    void p_rule_fighter(MB_MsgBuffer* pRecv,CCArray* pArray);
    
    void cs_rule_fight();
    void cs_rule_last_rank();
    
    void cs_hist_replay(uint64_t id);
    void sc_hist_replay(MB_MsgBuffer* pRecv,SResultData*);
    
    void cs_rule_leave();
public:
    CC_SYNTHESIZE(uint16_t, m_nRuleBuyTimes, RuleBuyTimes);
    CC_SYNTHESIZE(uint32_t, m_nNextRuleTime, NextRuleTime);
    CC_SYNTHESIZE(uint8_t, m_nRuleTimes, RuleTimes);    //
    CC_SYNTHESIZE(RuleFightInfo*, m_pRuleInfo, RuleInfo);
    CC_SYNTHESIZE_READONLY(MB_RuleFightDataSource*, m_pMyRecordDataSource, MyRecordDataSource);
    CC_SYNTHESIZE_READONLY(MB_RuleRankDataSource*, m_pRankDataSource, RankDataSource);
    CC_SYNTHESIZE_READONLY(MB_LastWeekRankDataSource*, LastWeekRankDataSource, LastWeekRankDataSource);
private:
    CC_SYNTHESIZE_READONLY(CCArray* ,m_pRankList,RankList);     //排行榜
    CC_SYNTHESIZE_READONLY(CCArray* ,m_pLastWeekRank,LastWeekRank);//上周排行榜
    CC_SYNTHESIZE(uint64_t, m_nFightReplayUID,FightReplayUID);
    
    CC_SYNTHESIZE(uint64_t, m_nReplayRoleID,ReplayRoleID);   
    
    bool m_bUpMainLayer;
    MB_LayerRuleFight* m_pMainLayer;
};
#endif /* defined(__ProjectMB__MB_RuleFightInterface__) */
