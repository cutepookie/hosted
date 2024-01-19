//
//  MB_PerfectRaceInterface.h
//  ProjectPM
//
//  Created by wenyong on 14-4-14.
//
//

#ifndef __ProjectMB__MB_PerfectRaceInterface__
#define __ProjectMB__MB_PerfectRaceInterface__

#include "MB_FunctionModule.h"
#include "MB_PerfectRaceProtocol.h"

enum LayerDirection
{
    kDirectionNone = 0,
    kDirectionNormal = 1,
    kDirectionPreRecord = 2,
    kDirectionGroupRecord = 3
};

enum GoupsStaus
{
    kRaceStatusReady      = 1,    // 准备比赛
    kRaceStatusLiving     = 2,    // 直播中
    kRaceStatusOver       = 3,    // 比赛结束
    kRaceStatusUnknow,
};
class MB_PerfectRaceInterface: public NSGameFunction::CCFunctionInterface
{
public:
    MB_PerfectRaceInterface();
    ~MB_PerfectRaceInterface();
    virtual MB_ResWindow* createEntryDialog();
    virtual MB_ResWindow* createFunctionDialog();
    virtual MB_ResWindow* createRuleDialog();
    virtual MB_ResWindow* createGroupPlayerDialog(int nGroup);
    virtual MB_ResWindow* createApplyDialog();
    virtual MB_ResWindow* createGroupRecordDialog();
    virtual MB_ResWindow* createGroupRecordDialogByGroupID(int nGroup);
    virtual MB_ResWindow* createFinalRecordDialog(MB_RaceRecord* pRecord);
    virtual MB_ResWindow* createFinalLivingDialog();
    virtual MB_ResWindow* createGroupLivingDialog();
    virtual MB_ResWindow* createSelfRaceRecordDialog();
    virtual MB_ResWindow* createGuessDialog();
    virtual void onLoadingScene();
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual bool allowShow();
    virtual uint16_t getFunctionType();
    virtual void onEntryClicked(CCObject* pSender);
    
    void onPreRecordClicked(CCObject* pSender);
//    void onRuleClicked(CCObject* pSender);
    void onGroupRecordClicked(CCObject* pSender);
    void onFinalRecordClicked(int pos);
    void onLiveingClicked(CCObject* pSender);
    void onOpenGroup(int nGroupId);
    void onRequestRecord(uint64_t uid);
    void setDirection(int dir);
    
    int getGroupRaceStatus(int Group);
    
    void openFinalRecord(MB_RaceRecordWithPos* pRecrod);
    void goNormalLayer();
    void goLiving(CCObject* pSender);
    void goPreRecordLayer();
    //void goGroupPlayerLayer();
    
    void goGroupRecordLayer(int nGroup);
    bool getIsLiving();
    bool checkEnableFunction();
    CCArray* queryFightPlayerListByGroupId(int nGroupId);
    CCArray* queryRecordListByGroupId(int nGroupId);
    CCArray* getSelfRecordArray()const{return m_pSelfRecord;}
    MB_RacePos* queryFinalPlayerByPos(int pos);
    MB_RacePos* queryFinalPlayerByRoleID(uint32_t nRoleID,uint16_t nMaxPos);
    MB_RaceRecordWithPos* queryFinalRecordByPos(uint8_t nPos);
    void autoTimeCountDown();
public:
    void sendrace_history(uint8_t nStep,uint8_t nGroupId,uint16_t nStart,uint16_t nCount);
    
    void sendrace_replay(uint64_t nReplayId);
    
    void sendrace_fight_list(uint8_t nGroupId);
    
    void sendrace_sign();
    
    void sendrace_info();
    
    void sendrace_enter();
    
    void sendrace_leave();
    
    void sendrace_is_open();             //请求是否可以进入华丽大赛
    
    void sendrace_pos_history(uint8_t nPos);
    
    void sendrace_auto_unsign();
    
    void sendrace_auto_sign();
    
    void sendrace_self_record();
    
    void sendrace_guess_info();
    
    void sendrace_guess(uint32_t nRoleID,uint32_t nGuessCoin);
protected:
    
    void recvrace_info(MB_MsgBuffer* pRecv);
    
    void recvrace_fight_list(MB_MsgBuffer* pRecv);
    
    void recvrace_new_fight(MB_MsgBuffer* pRecv);
    
    void recvrace_pos_history(MB_MsgBuffer* pRecv);
    
    void recvrace_new_first(MB_MsgBuffer* pRecv);
    
    void recvrace_new_status(MB_MsgBuffer* pRecv);
    
    void recvrace_is_open(MB_MsgBuffer* pRecv);
    
    void recvrace_auto_unsign(MB_MsgBuffer* pRecv);
    
    void recvrace_auto_sign(MB_MsgBuffer* pRecv);
    
    
    void recvrace_self_record(MB_MsgBuffer* pRecv);
    
private:
    CC_SYNTHESIZE_READONLY(bool, m_bCanEnter, CanEnter);          //是否能进入
    CC_SYNTHESIZE_READONLY(uint8_t, m_nStep, Step);
    CC_SYNTHESIZE_READONLY(uint32_t, m_nTimeStap, TimeStap);
    CC_SYNTHESIZE_READONLY(uint16_t, m_nSessionId, SessionId);
    CC_SYNTHESIZE(bool, m_bIsSign, IsSign);
    CC_SYNTHESIZE_READONLY(std::string, m_szKingName, KingName);
    CC_SYNTHESIZE_READONLY(uint8_t, m_nGroupId, GroupId);
    CC_SYNTHESIZE_READONLY(bool, m_bAutoSign, AutoSign);
    CC_SYNTHESIZE(bool,m_bOpenNewWnd , OpenNewWnd);                 //收到数据是否强制开启新窗口
    CC_SYNTHESIZE(bool, m_bOpenRaceMainOrRaceApply, OpenRaceMainOrRaceApply);//是否在主界面或者报名界面
    
    CCArray*        m_pRaceRecordList;
    bool            m_bTimeCountDownRuning;
    int             m_nDirection;
    int             m_nTargetPosRecord;
//    CCNode*         m_nTimerNode;
    CCArray*        m_pFighterList[8];// 选手列表
    CCArray*        m_pRecordList[8]; // 战报列表
    CCArray*        m_pFinalRecord;   // 决赛战报
    CCArray*        m_pSelfRecord;  // 自己的战报
};
#endif /* defined(__ProjectMB__MB_PerfectRaceInterface__) */
