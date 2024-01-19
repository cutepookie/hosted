//
//  MB_LayerFriend.h
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerFriend__
#define __ProjectMB__MB_LayerFriend__

#include "MB_ResWindow.h"
extern bool isFriendOpen;

class MB_FriendDataSouce;
enum FriendTablePage
{
    kFriendTableNormal = 0,
    kFriendTableAdd    = 1,
    kFriendTableEnergy = 2,
    kFriendTableMessage    = 3,
    kFriendTableFight = 4,
    kFriendTableCount,
};

class MB_LayerFriend : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    static MB_LayerFriend* create(bool bChat = false);
	MB_LayerFriend();
	virtual ~MB_LayerFriend();
	virtual void onResetWnd();
	virtual bool init(bool bChat);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
protected:
    void onFriendClicked(CCObject* pSender);
    void onAddListClicked(CCObject* pSender);
    void onFightClicked(CCObject* pSender);
    void onEnergyClicked(CCObject* pSender);
    void onMessageClicked(CCObject* pSender);
    void onSearchClicked(CCObject* pSender);
    void onCloseClicked(CCObject* pSender);
    void onGiveMoreFriendClicked(CCObject* pSender);
    void onGetAllEnergyClicked(CCObject* pSender);
    void onSendAllEnergyClicked(CCObject* pSender);
    void onReceiveAllEnergy(CCObject* pSender);
    
    void onAutoAddClicked(CCObject* pSender);
protected:
    bool iniDataSource();
    void updateTableMenu();
    void updateUI();
    void updateViewContainer(int nLastPage,int nNowPage);
private:
    CCMenuItemImage*	btFriend;
    CCMenuItemImage*	btAddList;
    CCMenuItemImage*	btGetEnergy;
    CCMenuItemImage*	btMessage;
    CCMenuItemImage*    btFight;
    CCNode*	Node_GetTimes;
    CCLabelBMFont*	getEnergyTimes;
    CCNode*	NodeAddFriend;
    CCEditBox*	Account;
    CCNode*	NodeFriendCount;
    CCLabelBMFont*	ItemCount;
    CCNode*	m_pNodeChangeFriend;
    CCNode*	NodeReceive;
    CCLabelTTF*	LastTimes;
    CCControlButton*	m_pBtGetAllEnergy;
    CCControlButton*	m_pBtSendAllEnergy;
    CCNode*	m_pContainer;
    CCNode* m_pNodeAddSize;
    MB_FriendDataSouce*     m_pDataSource[kFriendTableCount];
    int             m_nTablePage;
    CCTableView*    m_pNodeView;
    bool        m_bIsChat;
    int         m_bLastResetPage;
    CCNode*     m_pNodeMsgCount;
    CCLabelBMFont* m_pTTFMsgCount;
    CCLabelBMFont* m_pTTFFIghtNum;
    CCNode*     m_pNodeFight;
};
#endif /* defined(__ProjectMB__MB_LayerFriend__) */
