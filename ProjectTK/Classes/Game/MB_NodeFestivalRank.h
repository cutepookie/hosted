//
//  MB_NodeFestivalRank.h
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#ifndef __ProjectMB__MB_NodeFestivalRank__
#define __ProjectMB__MB_NodeFestivalRank__

#include "MB_ResWindow.h"
class MB_FestivalRankData;
class MB_MailReward;
class MB_RankReward;
class MB_NodeFestivalRank : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodeFestivalRank);
	MB_NodeFestivalRank();
	virtual ~MB_NodeFestivalRank();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static const CCSize& getNodeSize();
    void setData(MB_FestivalRankData* pData);
    void setRewardData(MB_MailReward* pRewardData);
    void setRankDataOnly(MB_RankReward* pRankReward);
protected:
    void replaceReward(CCNode* pRoot,CCNode* pTarget);
    void onIconClicked(CCObject* pSender);
private:
    MB_FestivalRankData* m_pData;
    CCNode*	m_pNodeSize;
    CCLabelBMFont*	m_pNodeRankNum;
    CCSprite*	m_pSpriteFrame;
    CCSprite*	m_pRoleHeader;
    CCLabelBMFont*	m_pNodeLv;
    CCLabelTTF*	m_pLabelRoleName;
    CCLabelTTF*	m_pLabelJoinTimes;
    CCNode* m_pNodeReward1;
    CCNode* m_pNodeReward2;
    CCNode* m_pNodeReward3;
    CCMenu* m_pNodeMenu;
};
#endif /* defined(__ProjectMB__MB_NodeFestivalRank__) */
