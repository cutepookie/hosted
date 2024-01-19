//
//  MB_NodeRuleReportUnit.h
//  ProjectMB
//
//  Create by chk on 13/1/2015.
//
//
#ifndef __ProjectMB__MB_NodeRuleReportUnit__
#define __ProjectMB__MB_NodeRuleReportUnit__

#include "MB_ResWindow.h"

class Hist;
class RichText;
class MB_NodeRuleReportUnit : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static CCSize getUnitSize();
    static MB_NodeRuleReportUnit* create(Hist*);
	MB_NodeRuleReportUnit();
	virtual ~MB_NodeRuleReportUnit();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
protected:
    void OnClickReplay(CCObject* pSender);
private:
    CCNode*	m_pNodeSize;
    CCLabelTTF*	m_pLabelTime;
    Hist* m_pHist;
    CCLabelTTF*       Description;
    CCNode* m_pWin;
    CCNode* m_pLose;
};
#endif /* defined(__ProjectMB__MB_NodeRuleReportUnit__) */
