//
//  MB_FunctionFestival.h
//  ProjectMB
//
//  Created by wenyong on 15-1-13.
//
//

#ifndef __ProjectMB__MB_FunctionFestival__
#define __ProjectMB__MB_FunctionFestival__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
class MB_MailReward;
class MB_FunctionFestival : public NSGameFunction::CCFunctionInterface
{
public:
    MB_FunctionFestival();
    virtual ~MB_FunctionFestival();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual MB_ResWindow* createRankDialog();
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    void send_festival_info();
    void recv_festival_info(MB_MsgBuffer* pRecv);
    void send_festival_join_once();
    void send_festival_join_tenth();
    void send_festival_open_box();
    void recv_festival_join_result(MB_MsgBuffer* pRecv);
    void send_festival_rank();
    void recv_festival_rank(MB_MsgBuffer* pRecv);
    void send_festival_rank_next();
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual void onLoadingScene();
    MB_MailReward* queryRankReward(uint32_t rank);
    const std::string& getName();
    CCArray* getRankData(){return m_pRankArray;}
    bool getWeatherAnyRankData(){return m_bAnyRankData;}
    virtual bool checkProtocol(MB_MsgBuffer* pRecv);
    virtual void fillInRewardData(CCArray* pTarget,uint16_t rank);
protected:
    void send_festival_rank(uint16_t start,uint16_t end);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nStartTime, StartTime);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nEndTime, EndTime);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nTotalTimes, TotalTimes);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nFreeTimes, FreeTimes);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nLeftJoinTimes, LeftJoinTimes);
    
    CC_SYNTHESIZE_READONLY(uint8_t, m_nMinRankCount, MinRankCount);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nOwenRank, OwenRank);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nBoxTimes, BoxTimes);
    CC_SYNTHESIZE_READONLY(std::string, m_szDescription, Description);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nOncePrice,OncePrice);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nTenthPrice,TenthPrice);
    
    std::string m_szName;
    
    uint16_t    m_nStartRequestRank;
    uint16_t    m_nEndRequestRank;
    bool        m_bAnyRankData;
    CCArray*    m_pRankArray;
    CCArray*    m_pRankReward;
};

#endif /* defined(__ProjectMB__MB_FunctionFestival__) */
