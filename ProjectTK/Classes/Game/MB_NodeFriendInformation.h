//
//  MB_NodeFriendInformation.h
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeFriendInformation__
#define __ProjectMB__MB_NodeFriendInformation__

#include "MB_ResWindow.h"
class MB_DataFriend;
class MB_NodeFriendInformation : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_NodeFriendInformation* create(MB_DataFriend* pData);
	MB_NodeFriendInformation();
	virtual ~MB_NodeFriendInformation();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setData(MB_DataFriend* pData);
    CCSize getNodeSize();
    void setIsMail(bool bMail);
    static const CCSize& getUISize();
    
    void tryDeleteFriend();
protected:
    void onRoleInfoClicked(CCObject* pSender);
    void onDelClicked(CCObject* pSender);
    void onChatClicked(CCObject* pSender);
    
private:
    CCNode*	size;
    CCSprite*	roleIcon;
    CCLabelBMFont*	m_pNodeLevel;
    CCMenuItemImage*	m_pBtHeadInfo;
    CCLabelTTF*	roleName;
    CCLabelBMFont*	fightPower;
    CCLabelTTF* status;
    MB_DataFriend*  m_pData;
    uint32_t    m_nSelectRoleID;
};
#endif /* defined(__ProjectMB__MB_NodeFriendInformation__) */
