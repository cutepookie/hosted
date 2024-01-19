//
//  MB_NodeGroupRecordLive.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#ifndef __ProjectMB__MB_NodeGroupRecordLive__
#define __ProjectMB__MB_NodeGroupRecordLive__

#include "MB_ResWindow.h"
class MB_RaceRecord;
class MB_NodeGroupRecordLive:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeGroupRecordLive();
    ~MB_NodeGroupRecordLive();
    virtual bool init(MB_RaceRecord* pRecord);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static MB_NodeGroupRecordLive* create(MB_RaceRecord* pRecord);
    uint64_t getRecordUid();
protected:
    void onReplayClicked(CCObject* pSender);
private:
    CCLabelTTF*     m_pAtkName;
    CCLabelTTF*     m_pDefName;
    CCLabelTTF*     m_pLabelWin;
//    CCLabelTTF*     m_pAtkStatus;
//    CCLabelTTF*     m_pDefStatus;
    
    MB_RaceRecord*  m_pRaceRecord;
    
    CCSprite*       m_pAtkWin;
    CCSprite*       m_pAtkLose;
    CCSprite*       m_pDefWin;
    CCSprite*       m_pDefLose;
};
#endif /* defined(__ProjectMB__MB_NodeGroupRecordLive__) */
