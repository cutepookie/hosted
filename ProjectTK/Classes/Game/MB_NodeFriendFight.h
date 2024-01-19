//
//  MB_NodeFriendFight.h
//  ProjectMB
//
//  Create by wenyong on 17/3/2015.
//
//
#ifndef __ProjectMB__MB_NodeFriendFight__
#define __ProjectMB__MB_NodeFriendFight__

#include "MB_ResWindow.h"

class MB_DataFriend;
class MB_NodeFriendFight : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeFriendFight();
	virtual ~MB_NodeFriendFight();
	virtual void onResetWnd();
    static MB_NodeFriendFight* create(MB_DataFriend* pData);
	virtual bool init();
    void setData(MB_DataFriend* pData);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    CCSize getNodeSize();
    static const CCSize& getUISize();
protected:
    void onRoleInfoClicked(CCObject* pSender);
    void onFightClick(CCObject* pSender);
private:
    CCNode*	size;
    CCSprite*	roleIcon;
    CCLabelBMFont*	m_pNodeLevel;
    CCLabelTTF*	roleName;
    CCLabelBMFont*	fightPower;
    CCMenuItemImage*	m_pBtFight;
    MB_DataFriend*      m_pData;
    CCLabelTTF* status;
};
#endif /* defined(__ProjectMB__MB_NodeFriendFight__) */
