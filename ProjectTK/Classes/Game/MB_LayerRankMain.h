//
//  MB_LayerRankMain.h
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerRankMain__
#define __ProjectMB__MB_LayerRankMain__

#include "MB_FunctionMainWnd.h"

class MB_RankDataSource;
class MB_FunctionRanking;
class MB_LayerRankMain : public MB_FunctionMainWnd
{
public:
    // 1:等级榜, 2:战斗力榜, 3:pvp榜, 4:关卡榜
    enum RankType
    {
        kRankLevel=0,
        kRankPower,
        kRankArena,
        kRankAbsolved,
        kRankCount,
        kRankDefault=kRankLevel,
    };
    MB_LayerRankMain();
    virtual ~MB_LayerRankMain();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    
    void sendpet_view_other(uint32_t roleid);
    void onExit();
    void onEnterTransitionDidFinish();
protected:
    void onFriendClicked(CCObject* pSender);
    void onEnergyClicked(CCObject* pSender);
    void onAddListClicked(CCObject* pSender);
    void onCloseClicked(CCObject* pSender);
    void onInitialized();
    void resetData();
    void resetMenuStatus();
private:
    CCNode*	m_pNodePower;
    CCLabelBMFont*	m_pNodePowerValue;
    CCLabelTTF*	m_pNodePowerRank;
    CCNode*	m_pNodeLevel;
    CCLabelBMFont*	m_pNodeLevelPower;
    CCLabelTTF*	m_pNodeLvelRank;
    CCNode*	m_pNodeAbsolved;
    CCLabelTTF*	m_pNodeAbsolvedChapter;
    CCLabelTTF*	m_pNodeAbsolvedDungeon;
    CCLabelTTF*	m_pNodeAbsolvedRank;
    CCNode*	m_pContainer;
    CCNode* m_pSelectedSpr;
private:
    int m_nRankType;
    CCTableView* m_pTableView;
    MB_RankDataSource*  m_pDataSource[kRankCount];
    MB_FunctionRanking* m_pInterface;
};
#endif /* defined(__ProjectMB__MB_LayerRankMain__) */
