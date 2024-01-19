//
//  MB_NodeReportBox.h
//  ProjectTK
//
//  Created by crimoon00007 on 13-12-25.
//
//

#ifndef __ProjectMB__MB_NodeReportBox__
#define __ProjectMB__MB_NodeReportBox__

#include "Game.h"
class RichText;
struct p_pvp_replay_info
{
    std::string attackerName;
    std::string defenderName;
    uint16_t  attackerNewRank;//决斗者新排名（一定是上升~~打赢了才显示）
    uint16_t  defenderNewRank;//被决斗者新排名
    uint64_t  replayUid;
    uint32_t  time;            //战斗发生的时间戳
};

class MB_NodeReportBox:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:

    MB_NodeReportBox();
    ~MB_NodeReportBox();

    virtual bool init();

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);


    uint32_t getTime()const;

    void visableBeatBackMenu(bool bVisable);
    bool isVisableBeatBackMenu();
    void visableReplayMenu(bool bVisbale);
    bool isVisableReplayMenu();
    bool getNodeSize(CCSize& sz);

    void getReportInfo(p_pvp_replay_info& info)const;
    void setReportInfo(const p_pvp_replay_info& info);
    CREATE_FUNC(MB_NodeReportBox);

protected:
    void setTime(uint32_t time);
    void setRichBoxString(const char* pString);
    virtual void onBeatBackClicked(CCObject* obj);
    virtual void onReplayClicked(CCObject* obj);
    void    setTimeLable(const char* pData);
private:
    CC_SYNTHESIZE(uint64_t, m_iReportUid, ReportUid);
    p_pvp_replay_info       m_ReportInfo;
    uint32_t                m_iReportTime;
    CCNode*                 m_pMenuBeatBack;
    CCNode*                 m_pMenuReplay;
    CCLabelTTF*             m_pTimeText;
    CCNode*                 m_pNodeRichBox;
    CCNode*                 m_pNodeSize;
    RichText*                m_pRichBox;
};

class MB_ReportBoxDelegate
{
public:
    virtual void onBeatBackClicked(MB_NodeReportBox* pBoxObj)   = 0;
    virtual void onReplayClicked(MB_NodeReportBox* pBoxObj)     = 0;
};

#endif /* defined(__ProjectMB__MB_NodeReportBox__) */
