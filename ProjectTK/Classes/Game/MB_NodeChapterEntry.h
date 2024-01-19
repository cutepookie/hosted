//
//  MB_NodeChapterEntry.h
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#ifndef __ProjectMB__MB_NodeChapterEntry__
#define __ProjectMB__MB_NodeChapterEntry__

#include "MB_FunctionModule.h"

class MB_NodeChapterEntry:public CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodeChapterEntry();
    ~MB_NodeChapterEntry();
    virtual bool init();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setChapterIcon(const char* pFile);
    void activate(int index);
protected:
    void onChapterClicked(CCObject* pSender);
private:
    CCSprite*        m_pTitle;
    CCControlButton*   m_pControlButtonIcon;
    CCControlButton*                 m_plockBg;
    CCNode*                 m_pIconChild;
    CCNode*                 m_pNowBg;
    CCControlButton* m_bBg;
    const char* m_ChapterFileChar;
//    CCParticleSystemQuad*   m_pEffect1;
//    CCParticleSystemQuad*   m_pEffect2;
};

#endif /* defined(__ProjectMB__MB_NodeChapterEntry__) */
