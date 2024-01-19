//
//  MB_LayerBudokan.h
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#ifndef __ProjectMB__MB_LayerBudokan__
#define __ProjectMB__MB_LayerBudokan__

#include "MB_FunctionModule.h"

class MB_FunctionBudokanInterface;
class MB_LayerBudokan : public MB_FunctionMainWnd
{
public:
	MB_LayerBudokan();
	virtual ~MB_LayerBudokan();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    void onEnterTransitionDidFinish();
protected:
    void onCloseClick(CCObject* pSender);
    void onMoneyInspirationClicked(CCObject* pSender);
    void onGoldInspirationClicked(CCObject* pSender);
    void onFightClicked(CCObject* pSender);
    void onAutoFightClicked(CCObject* pSender);
    void onRuleClick(CCObject* pSender);
    void recvbudokan_raids(MB_MsgBuffer* pRecv);
    void onSetReward(p_reward *reward,MB_MsgBuffer* recvPacket);
private:
    CCLabelBMFont*	m_pTTFAddAtt;
    CCLabelBMFont*	m_pTTFAddHP;
    CCLabelBMFont* m_pTTFTimes;
    CCNode* m_pNodeReward1;
    CCNode* m_pNodeReward2;
    CCNode* m_pNodeReward3;
    CCNode* m_pNodeReward4;
    CCControlButton* m_pBtMoneyAddBuf;
    CCControlButton* m_pBtGoldAddBuf;
    CCControlButton* m_pBtFight;
    CCControlButton* m_pBtAutoFight;
    CCSprite*   m_pSprinteBoss;
    MB_FunctionBudokanInterface* m_pInterface;
    CCNode* m_NodePassed;
    CCLabelBMFont* m_pTTFMaxDungeon;
    CCLabelBMFont* m_pTTFNowDungeon;
    
    bool m_bAutoFight;
};

#endif /* defined(__ProjectMB__MB_LayerBudokan__) */
