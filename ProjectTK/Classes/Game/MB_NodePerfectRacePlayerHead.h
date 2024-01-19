//
//  MB_NodePerfectRacePlayerHead.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#ifndef __ProjectMB__MB_NodePerfectRacePlayerHead__
#define __ProjectMB__MB_NodePerfectRacePlayerHead__

#include "MB_ResWindow.h"
class MB_RacePos;
class MB_NodePerfectRacePlayerHead:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePerfectRacePlayerHead();
    ~MB_NodePerfectRacePlayerHead();
    virtual bool init(MB_RacePos* pPos);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static MB_NodePerfectRacePlayerHead* create(MB_RacePos* pPos);
    CCLabelTTF* getRoleName();
    void setClickEnable(bool bEnable){m_pMenu->setVisible(bEnable);}
protected:
    void onIconClicked(CCObject* pSender);
private:
    MB_RacePos* m_pRacePlayer;
    CCSprite*   m_pRoleIcon;
    CCSprite*   m_pIconFrame;
    CCLabelTTF* m_pRoleName;
    CCMenu*     m_pMenu;
};
#endif /* defined(__ProjectMB__MB_NodePerfectRacePlayerHead__) */
