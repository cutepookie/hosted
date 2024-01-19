//
//  MB_JingjichangTZ.h
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#ifndef __ProjectMB__MB_JingjichangTZ__
#define __ProjectMB__MB_JingjichangTZ__

#include "MB_FunctionMainWnd.h"
#include "MB_NodeReportBox.h"




class MB_Championship;


//精靈榜功能窗口
class MB_JingjichangTZ:public MB_FunctionMainWnd
,public MB_ReportBoxDelegate
{
    friend class MB_Championship;
public:
    MB_JingjichangTZ();
    ~MB_JingjichangTZ();
    CREATE_FUNC(MB_JingjichangTZ);
    virtual bool init();
    
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    
    virtual void onBeatBackClicked(MB_NodeReportBox* pBoxObj);
    virtual void onReplayClicked(MB_NodeReportBox* pBoxObj);
    
    virtual void onEnterTransitionDidFinish();

public:
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onResetWnd(void);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    uint64_t getSelectReportTop8Uid(){return m_pSelectReportInfo.replayUid;}
protected:
    NSGameFunction::CCFunctionInterface*  m_pInterface;
    //--------------menu----------//
    void timeTick(float dt);
protected:
    void recvpvp_get_first_eight_replays(MB_MsgBuffer* pBuffer);
    void recvpvp_eight_replay(MB_MsgBuffer* pBuffer);
protected:
    void EightReplay(recvfight *fight_replay);

    bool hasTitleReward();
    void onClickTZDW(CCObject* pSender);
private:
    CCLabelBMFont*          m_prest_count;
    CCNode*             m_pContainer;
    CCLabelBMFont *         m_pRest_recovery;
    CCLabelBMFont *         m_pFightPower;
    // 1.2.1 精靈榜优化
    p_pvp_replay_info   m_pSelectReportInfo;
    CCNode* m_pNodeScroller;
};

#endif /* defined(__ProjectMB__MB_JingjichangTZ__) */
