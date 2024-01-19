//
//  MB_NodeRuleRankUnit.h
//  ProjectMB
//
//  Create by chk on 12/1/2015.
//
//
#ifndef __ProjectMB__MB_NodeRuleRankUnit__
#define __ProjectMB__MB_NodeRuleRankUnit__

#include "MB_ResWindow.h"

class RuleFighter;
class MB_NodeRuleRankUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    
    static MB_NodeRuleRankUnit* create(RuleFighter*);
    static CCSize getUnitSize();
	MB_NodeRuleRankUnit();
	virtual ~MB_NodeRuleRankUnit();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
//    void setIndex(int i){m_pLabelIndex->setString(CCString::createWithFormat("%d",i)->getCString());};
protected:
    void onIconClicked(CCObject* pSender);
private:
    CCNode*	m_pNodeSize;
    CCLabelBMFont*	m_pNodeRankNum;
    CCNode*    m_pPaiMingNode;
    CCSprite*	m_pSpriteFrame;
    CCSprite*	m_pRoleHeader;
    CCLabelBMFont*	m_pNodeLv;
    CCLabelTTF*	m_pLabelName;
    CCLabelTTF*	m_pLabelServer;
    CCLabelBMFont*	m_pLabelWinRate;
    CCLabelBMFont*	m_pLabelScore;
    RuleFighter* m_pFighter;
    CCNode* m_NumOne;
    CCNode* m_pNumOneLine;
};


class Hist;
class RichText;
class MB_NodeHistoryUnit: public MB_ResWindow
{
    MB_NodeHistoryUnit();
public:
    static MB_NodeHistoryUnit* create(Hist*);
    virtual void onResetWnd();
    virtual bool init();
    
    CCSize getShowSize();
private:
    Hist* m_pHist;
    RichText* m_pRichText;
};

#endif /* defined(__ProjectMB__MB_NodeRuleRankUnit__) */
