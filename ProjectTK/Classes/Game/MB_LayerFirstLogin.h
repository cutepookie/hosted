
#ifndef __ProjectMB__MB_LayerFirstLogin__
#define __ProjectMB__MB_LayerFirstLogin__

#include "Game.h"
class MB_SceneServerList;
class MB_LayerAccountMgr;
class MB_LayerFirstLogin : public MB_ResWindow
	, public CCBMemberVariableAssigner
	, public CCBSelectorResolver
{

	MB_ServerList* m_pTKServerList;
	bool m_bAccIsExist;
	bool m_bIsLoginClicked;
	CCNode *m_pNode;
	std::string m_puin;
	std::string m_paccid;
    CCControlButton* m_pPlayBtn;
	static bool sIsFirstLogin;
	
public:

	MB_LayerFirstLogin();
	~MB_LayerFirstLogin();
	static MB_LayerFirstLogin* create();
	virtual bool init();
	virtual void onResetWnd();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	void onLoginClicked(CCObject *);
	void onLoginStart(const char * str1, const char* str2, const char *str3);
	void onLoginStart(const char * str1, const char* str2, const char *str3, const char *str4);
	void onLoginStart(const char * sid);
	void onLoginStart2(const char * sid, const char * appid);
	void onLoginStart(const char * userid, const char *tocken);

	void setDefaultServerInfo();
	void onHttpMsgRecv(CCNode* node, CCHttpResponse* response);
	void onGuestHttpMsgRecv(CCNode* node, CCHttpResponse* response);
	void onGusetLoginStart();
	void createAccInfo(const char *gusetname, const char *gustpasswd);

	void sendhttp_getServerList();
	void recvhttp_revServerList(CCNode* node, CCHttpResponse* response);
	void sendhttp_account_verify();
	void recvhttp_account_verify(CCNode* node, CCHttpResponse* response);

	void sendhttp_notice_request();
	void recvhttp_notice_request(CCNode* node, CCHttpResponse* response);

	void resetRecentlyServerNode();
	void onServerNodeTouched(CCNode* pSender);
	void onAccountMgrReturnBack();
	void resetAccount();
	void setIsGuestAccount(bool bGuest){ m_bLastIsGuest = bGuest; }

	void saveAccount();
	void loadAccount();
	void onServerListClosed(CCObject* pSender);

	 void onSdkLogin();
	//    void setSkip(bool bSkip){m_bSkipLogin = bSkip;}
protected:
	void onClickServerList(CCObject*);
    void onClickYinSi(CCObject*);
     void onClickGouXuan(CCObject*);
	void onClickInputAccount(CCObject*);
	MB_SceneServerList* getSceneServerList();
	MB_LayerAccountMgr* getSceneAccountMgr();


private:
	CC_SYNTHESIZE(std::string, m_szAccount, Account);
	CC_SYNTHESIZE(std::string, m_szPassword, Password);
	bool                m_bLastIsGuest;
	MB_SceneServerList* m_pSceneList;
	MB_LayerAccountMgr* m_pAccountMgr;
	CCLabelTTF*         m_pAccount;
	CCLabelTTF*         m_pServerID;
	CCLabelTTF*         m_pServerName;
    CCControlButton*    m_pGou;


	CCNode*             m_pNodeServerState1;
	CCNode*             m_pNodeServerState2;
	CCNode*             m_pNodeServerState3;
	CCNode*             m_pNodeAccount;
	CCNode*             m_pNodeServerList;



	bool                m_bCanVersion;
public:
	//static bool                m_bSkipLogin;
};

#endif /* defined(__ProjectMB__MB_LayerFirstLogin__) */
