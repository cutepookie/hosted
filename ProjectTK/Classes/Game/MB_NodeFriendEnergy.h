//
//  MB_NodeFriendReceiveLife.h
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeFriendEnergy__
#define __ProjectMB__MB_NodeFriendEnergy__

#include "MB_ResWindow.h"
class MB_DataFriend;
class MB_NodeFriendEnergy : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeFriendEnergy();
	virtual ~MB_NodeFriendEnergy();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setData(MB_DataFriend* pData);
    static MB_NodeFriendEnergy* create(MB_DataFriend* pData);
    CCSize getNodeSize();
    
    static const CCSize& getUISize();
protected:
    void onRoleInfoClicked(CCObject* pSender);
    void onGiveEnergyClicked(CCObject* pSender);
    void onSendEnergyClicked(CCObject* pSender);
private:
    CCNode*	size;
    CCSprite*	roleIcon;
    CCLabelBMFont*	m_pNodeLevel;
    CCLabelTTF*	roleName;
    CCLabelBMFont*	fightPower;
    CCLabelTTF*	status;
    CCMenuItemImage*	m_pBtSendEnergy;
    CCMenuItemImage*	m_pBtGiveEnergy;
    MB_DataFriend*      m_pData;
};
#endif /* defined(__ProjectMB__MB_NodeFriendEnergy__) */
