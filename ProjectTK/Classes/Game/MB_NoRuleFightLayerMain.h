//
//  MB_NoRuleFightLayerMain.h
//  ProjectMB
//
//  Create by chk on 27/2/2015.
//
//
#ifndef __ProjectMB__MB_NoRuleFightLayerMain__
#define __ProjectMB__MB_NoRuleFightLayerMain__

#include "MB_FunctionMainWnd.h"
class MB_FunctionNoRuleFight;
class MB_NoRuleFightLayerMain : public MB_FunctionMainWnd
{
public:
	MB_NoRuleFightLayerMain();
	virtual ~MB_NoRuleFightLayerMain();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void tick(float dt);
    void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    void onEnterTransitionDidFinish();
protected:
    void onCloseClicked(CCObject* pSender);
    void onSignClicked(CCObject* pSender);
    void onFightClicked(CCObject* pSender);
    void onRuleClicked(CCObject* pSender);
private:
    CCLabelBMFont*	m_pLabelNoruleCount;
    CCNode*	m_pNodeSign;
//    CCLabelTTF*	m_pLabelSingState;
    CCMenuItemImage*	m_pBtSign;
    CCNode*	m_pNodeFight;
    CCMenuItemImage*	m_pBtFight;
    CCLabelBMFont*	m_pTeam0Score;
    CCLabelBMFont*	m_pTeam1Score;
    CCLabelBMFont*	m_pSelfScore;
    CCLabelBMFont*	m_pLabelWinCount0;
    CCLabelBMFont*	m_pLabelWinCount1;
    CCLabelBMFont* m_pLabelTime;
    MB_FunctionNoRuleFight* m_pFunction;
    CCNode* m_pNodeSelfAt0;
    CCNode* m_pNodeSelfAt1;
    int m_nLastFightTime;
    bool m_bCanCsMeleeInfo;
    CCSprite* m_pDJSSpr;
};
#endif /* defined(__ProjectMB__MB_NoRuleFightLayerMain__) */
