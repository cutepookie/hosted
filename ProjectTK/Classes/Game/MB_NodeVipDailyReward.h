//
//  MB_NodeVipDailyReward.h
//  ProjectMB
//
//  Create by wenyong on 23/12/2014.
//
//
#ifndef __ProjectMB__MB_NodeVipDailyReward__
#define __ProjectMB__MB_NodeVipDailyReward__

#include "MB_ResWindow.h"
class MB_MailReward;
class MB_NodeVipDailyReward : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodeVipDailyReward);
	MB_NodeVipDailyReward();
	virtual ~MB_NodeVipDailyReward();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setReceiveEnable(bool bEnable);
    void setMailReward(MB_MailReward* pReward);
    virtual void onInitialized();
protected:
    void onVipClicked(CCObject* pSender);
    void onClickCollect(CCObject* pSender);
private:
    CCNode*	m_pNodeReward;
    CCMenuItemImage*	m_pMenuReceive;
    CCSprite* m_pVipLevelSpr;
    CCNode* m_pVipInfoBg;
    CCNode* m_pVipInfoBg2;
    CCLabelBMFont* m_pVipInfo1;
    CCLabelBMFont* m_pVipInfo2;
    bool isReceiveEnable;
};
#endif /* defined(__ProjectMB__MB_NodeVipDailyReward__) */
