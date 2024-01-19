//
//  MB_NodePerfectRacePlayer.h
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#ifndef __ProjectMB__MB_NodePerfectRacePlayer__
#define __ProjectMB__MB_NodePerfectRacePlayer__

#include "MB_ResWindow.h"
class MB_RaceFighter;
class MB_NodePerfectRacePlayer:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePerfectRacePlayer();
    ~MB_NodePerfectRacePlayer();
    virtual bool init(MB_RaceFighter* pPlayer);
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    static MB_NodePerfectRacePlayer* create(MB_RaceFighter* pPlayer);
    
protected:
    void onCheckClicked(CCObject* pSender);
    void onIconClick(CCObject* pSender);
private:
    MB_RaceFighter* m_pPlayer;
    
    CCNode*     m_pNodeEmemy;
    CCNode*     m_pNodeFriend;
    
    CCLabelTTF* m_pRoleLevel;
    CCLabelTTF* m_pRolePower;
    CCLabelTTF* m_pRoleName;
//    CCNode*     m_pNodeLevel;
    CCSprite*   m_pIcon;
    CCSprite*   m_pFrame;
    
};

#endif /* defined(__ProjectMB__MB_NodePerfectRacePlayer__) */
