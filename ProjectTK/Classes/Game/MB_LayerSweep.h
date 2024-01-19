//
//  MB_LayerSweep.h
//  ProjectMB
//
//  Create by chk on 8/10/2014.
//
//
#ifndef __ProjectMB__MB_LayerSweep__
#define __ProjectMB__MB_LayerSweep__

#include "MB_ResWindow.h"
#include "Game.h"
class MB_LayerChapterWnd;
class MB_LayerSweep : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
    
public:
    MB_LayerSweep();
    static std::string strCurDungeonName;
    static MB_LayerSweep * create(p_reward *pReward,uint16_t length);
	virtual ~MB_LayerSweep();
	virtual void onResetWnd();
    virtual bool init(p_reward *pReward,uint16_t length);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onExit();
    
    void setBeforeSweepRoleInfo(int nPreRoleLv,int nPreDis,int nPreEnergy);
    MB_LayerChapterWnd* layerChapterWnd;
protected:
    void onCloseClick(CCObject* pSender);
    virtual void checkSweepLevelUp();
    virtual void showOver(float);
    void addReward(RewardTempleteValue* p);
    

    CCScrollView* m_pScrollView;
    CCLabelTTF*	m_pOver;
    CCLabelTTF*	m_pNameLabel;
    CCNode*	m_pNodeProcess;
    CCLabelBMFont*	m_pCoinLabel;
    CCLabelBMFont*	m_pExpLabel;
    CCNode*	m_pNodeContainer;
    CCLabelBMFont* m_pProcessLabel;
    CCLabelBMFont* m_pProcessLabel2;
    
    p_reward *m_pReward;
    uint8_t m_nRewardLength;
    uint8_t m_nNowshow;
    
    int m_n;
    int m_nCoin;
    int m_nExp;
    int m_nPreValue[3];
    
    CCArray* m_pRewards;
};
#endif /* defined(__ProjectMB__MB_LayerSweep__) */
