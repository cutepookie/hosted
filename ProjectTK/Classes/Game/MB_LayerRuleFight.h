//
//  MB_LayerRuleFight.h
//  ProjectMB
//
//  Create by chk on 12/1/2015.
//
//
#ifndef __ProjectMB__MB_LayerRuleFight__
#define __ProjectMB__MB_LayerRuleFight__

#include "MB_FunctionModule.h"
#include "MB_NodeReportBox.h"
class MB_RuleFightInterface;
class MB_LayerRuleFight : public MB_FunctionMainWnd
{
public:
    virtual void onReplayClicked(uint64_t uid);
public:
    enum ePage
    {
        eMainPage,
        eMyRecordPage,
        eRankPage,
        eLastWeekRankPage,
        eNonePage,
    };
public:
    static MB_LayerRuleFight* create();
	MB_LayerRuleFight();
	virtual ~MB_LayerRuleFight();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void sendpet_view_other(uint32_t roleid,uint16_t serverid);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void showPage(ePage e,bool force = false);
    void onEnterTransitionDidFinish();
protected:
    void onCloseClick(CCObject* pSender);
    void onMainPageClicked(CCObject* pSender);
    void onMyRecordClicked(CCObject* pSender);
    void onScoreRankClicked(CCObject* pSender);
    void onRuleClicked(CCObject* pSender);
    void onLastWeakRankClicked(CCObject* pSender);
    void onFightClicked(CCObject* pSender);
    void onIconClicked(CCObject*);
    void updateMainInfo();
    void updateRankPage();
    void goBuyRuleFightTimes();
    void tick(float dt);
private:
    CCLabelBMFont*	m_pLabelScore;
    CCLabelBMFont*	m_pLabelTitle;
    CCLabelBMFont*	m_pLabelWinate;
    CCLabelBMFont*	m_pLabelRecoverTime;
    CCLabelBMFont*	m_pLabelLeftCount;
    CCLabelBMFont* m_pLabelFightPower;
    CCLabelTTF* m_pLabelTargetServer;
    CCLabelTTF* m_pLabelName;
    CCNode*	m_pNodeHistory;
    CCMenuItemImage* m_pBtnMainPage2;
    CCMenuItemImage* m_pBtnMyRecord2;
    CCMenuItemImage* m_pBtnRank2;
    CCMenuItemImage* m_pBtnLastWeekRank2;
    CCNode* m_pBtnMainPage;
    CCNode* m_pBtnMyRecord;
    CCNode* m_pBtnRank;
    CCNode* m_pBtnLastWeekRank;
    CCNode* m_pNodeMainPage;
    CCNode* m_pNodeMyRecord;
    ePage m_nCurrentPage;
    
    CCTableView* m_pMyRecordTableView;
    CCScrollView* m_pHistoryScrollView;
    CCSprite* m_pRoleCard;
    CCSprite* m_pIconFrame;
private:
    MB_RuleFightInterface* m_pInterface;
    CCSprite* m_pStar[5];
    CCPoint   starPt[5];
    CCNode* m_pZDLCSpr;
};
#endif /* defined(__ProjectMB__MB_LayerRuleFight__) */
