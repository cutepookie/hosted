//
//  MB_NodeFriendInvite.h
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeFriendInvite__
#define __ProjectMB__MB_NodeFriendInvite__

#include "MB_ResWindow.h"


class MB_DataFriend;
enum InviteMode
{
    kModeInvite = 1,
    kModeMsg = 2,
    kModeMailAdd= 3,
};
class MB_NodeFriendInvite : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_NodeFriendInvite* create(MB_DataFriend* pData);
	MB_NodeFriendInvite();
	virtual ~MB_NodeFriendInvite();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setData(MB_DataFriend* pData);
    void setMode(int mode);
    CCSize getNodeSize();
    static const CCSize& getUISize();
protected:
    void updateMode();
    void onAddClicked(CCObject* pSender);
    void onAgreeClicked(CCObject* pSender);
    void onRefuseClicked(CCObject* pSender);
private:
    CCNode*	cellSize;
    CCSprite*	roleIcon;
    CCLabelTTF*	roleName;
    CCLabelBMFont*	fightPower;
    CCLabelBMFont*	m_pNodeLevel;
    CCLabelTTF*	status;
    CCNode*	nodeAdd;
    CCMenuItemImage*	btAdd;
    CCNode*	m_pNodeMsg;
    MB_DataFriend*  m_pData;
    uint32_t    m_nSelectRoleID;
    int mode;
};
#endif /* defined(__ProjectMB__MB_NodeFriendInvite__) */
