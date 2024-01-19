

#ifndef __ProjectMB__MB_NodePVPInfo__
#define __ProjectMB__MB_NodePVPInfo__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MB_NodePVPInfo : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_NodePVPInfo();
    ~MB_NodePVPInfo();
    
    static MB_NodePVPInfo* create(MB_DataPVPRank* dataPVPRank,bool bShowTutorial = false);
    
    virtual bool init(MB_DataPVPRank* dataPVPRank);
    virtual void onResetWnd();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onFightClicked(CCObject* pSender);
    void onCompareClick(CCObject* pSender);
    void refreshData(MB_DataPVPRank* dataPVPRank = NULL);
    
private:
    
    CCLabelBMFont* m_pRoleFightPower;
    CCLabelTTF*  m_pRoleName;
    CCLabelBMFont* m_pRoleRank;
    
    CCLabelTTF* m_pRoleReputation;
    CCSprite*   m_pRoleIcon;
    CCNode*     m_pNodeBattle;
    CCLabelBMFont*     m_pLabelLevel;
    MB_DataPVPRank* m_pDataPVPRank;
    
    bool m_bShowTutorial;
    
};

#endif /* defined(__ProjectMB__MB_NodePVPInfo__) */
