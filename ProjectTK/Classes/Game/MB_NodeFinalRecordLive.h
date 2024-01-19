//
//  MB_NodeFinalRecordLive.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#ifndef __ProjectMB__MB_NodeFinalRecordLive__
#define __ProjectMB__MB_NodeFinalRecordLive__

#include "MB_ResWindow.h"
class MB_RaceRoundRecord;
class MB_NodeFinalRecordLive:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeFinalRecordLive();
    ~MB_NodeFinalRecordLive();
    virtual bool init(MB_RaceRoundRecord* pRoundRecord);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static MB_NodeFinalRecordLive* create(MB_RaceRoundRecord* pRoundRecord);
protected:
    void onReplayClicked(CCObject* pSender);
private:
    MB_RaceRoundRecord* m_pRoundRecord;
    CCLabelTTF*     m_pAtkName;
    CCLabelTTF*     m_pDefName;
    CCLabelBMFont*     m_pAtkScore;
    CCLabelBMFont*     m_pDefScore;
    CCNode*     m_pLabelWin;
};
#endif /* defined(__ProjectMB__MB_NodeFinalRecordLive__) */
