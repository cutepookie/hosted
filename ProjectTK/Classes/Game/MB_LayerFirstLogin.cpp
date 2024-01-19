
#include "MB_LayerFirstLogin.h"
#include "../Common/SDS_NetWorkDefine.h"
#include "MB_LayerAccountMgr.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_LayerScrollMessage.h"

#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif
#include "MB_NodeYinSi.h"



#include "aescrypt.h"
#include "password.h"
#include "md5.h"

bool MB_LayerFirstLogin::sIsFirstLogin = true;

MB_LayerFirstLogin::MB_LayerFirstLogin(){
	extension::CCHttpClient::getInstance();

#ifdef PLATFORM_YJ
	MB_YJMgr::getInstance()->registDelegate(this);
	m_pTKServerList = NULL;
	m_bAccIsExist = false;
	m_bIsLoginClicked = false;
#endif

#ifdef YJ_IOS
    MB_YJMgr_IOS::getInstance()->registDelegate(this);
	m_pTKServerList = NULL;
	m_bAccIsExist = false;
	m_bIsLoginClicked = false;
#endif
    m_pPlayBtn = NULL;
	m_pAccount = NULL;
	m_pServerID = NULL;
	m_pServerName = NULL;
    m_pGou = NULL;
	m_pNodeServerState1 = NULL;
	m_pNodeServerState2 = NULL;
	m_pNodeServerState3 = NULL;
	m_pSceneList = NULL;
	m_pAccountMgr = NULL;
	m_bLastIsGuest = false;
	m_pNodeAccount = NULL;
	m_pNodeServerList = NULL;
	m_bCanVersion = false;
	if (MB_ClientSocket::isAlive() == true)
	{
		MB_ClientSocket::destroyInstance();
	}
}
MB_LayerFirstLogin::~MB_LayerFirstLogin()
{
#ifdef PLATFORM_YJ
	MB_YJMgr::getInstance()->unregistDelegate(this);
#endif
#ifdef YJ_IOS
    MB_YJMgr_IOS::getInstance()->unregistDelegate(this);
#endif
    CC_SAFE_RELEASE(m_pPlayBtn);
	CC_SAFE_RELEASE(m_pAccount);
	CC_SAFE_RELEASE(m_pServerID);
	CC_SAFE_RELEASE(m_pServerName);
    CC_SAFE_RELEASE(m_pGou);
	CC_SAFE_RELEASE(m_pNodeServerState1);
	CC_SAFE_RELEASE(m_pNodeServerState2);
	CC_SAFE_RELEASE(m_pNodeServerState3);
	CC_SAFE_RELEASE_NULL(m_pNodeServerList);
	CC_SAFE_RELEASE_NULL(m_pNodeAccount);
    
	m_bCanVersion = false;
}

//bool MB_LayerFirstLogin::m_bSkipLogin = false;
MB_LayerFirstLogin* MB_LayerFirstLogin::create(){
	MB_LayerFirstLogin*  ptr = new MB_LayerFirstLogin();
	if (ptr && ptr->init()){

		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}
bool MB_LayerFirstLogin::init(){

	if (MB_ResWindow::init() == false){

		return false;
	}
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

	m_pNode = pCCBReader->readNodeGraphFromFile("res/login_layer_defult.ccbi", this);


	this->addChild(m_pNode);
	pCCBReader->release();

    m_pPlayBtn->setTouchPriority(1);
	// 在此發送伺服器列表請求
	//sendhttp_getServerList();
	m_pNodeAccount->setVisible(false);
	m_pNodeServerList->setVisible(false);
	//    CCLOG("PlatForm:%d",NSGameHelper::getSrcType());
	if (NSGameHelper::getSrcType() == NSGameHelper::ACCOUNT_TYPE_NORMAL)
	{
		loadAccount();
		m_pNodeAccount->setVisible(true);
		m_pNodeServerList->setVisible(true);
		sendhttp_getServerList();
	}
	else
	{
		if (!m_bCanVersion)
		{
			onSdkLogin();
		}
    }
    
	return true;
}

void MB_LayerFirstLogin::sendhttp_account_verify()
{
	//發送登入消息
	CCLOG("MB_LayerFirstLogin::sendhttp_account_verify");
	char pMD5Code[34];
	std::string acc = getAccount();
	if (acc.empty())
	{
		MB_Message::sharedMB_Message()->showMessage("账号不能为空!");
		return;
	}

	time_t  m_tTimeStamp = time(NULL);
	char curTime[32] = { 0 };
	sprintf(curTime, "%ld", m_tTimeStamp);
	if (m_bLastIsGuest == false)
	{
		std::string pwd = getPassword();
		pwd += "moon_game_password_key";
		GetMD5Code((unsigned char*)pwd.c_str(), pwd.length(), pMD5Code);

	}
	else
	{
		strcpy(pMD5Code, getPassword().c_str());
	}

	std::string pwd2 = acc + pMD5Code + curTime + "moon_game_login_key";
	GetMD5Code((unsigned char*)pwd2.c_str(), pwd2.length(), pMD5Code);

	std::string postinfo = LOGIN_SERVER_URL;
	postinfo += "baseinfo/?account=" + acc + "&loginkey=" + pMD5Code + "&curtime=" + curTime + std::string("&version=") + OCandCppHelper::getVervion();


	CCLOG("%s", postinfo.c_str());
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	//httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::recvhttp_account_verify));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
}

void MB_LayerFirstLogin::recvhttp_account_verify(CCNode* node, CCHttpResponse* response)
{
	MB_Message::sharedMB_Message()->removeALLMessage();
	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);
	int result = root["result"].asInt();

	if (result == 0)
	{
		MB_Message::sharedMB_Message()->removeALLMessage();

		int acc = root["accid"].asInt();
		char accid[64];
		sprintf(accid, "%d", acc);
		if (m_pTKServerList == NULL)
		{
			m_pTKServerList = MB_ServerList::getInstance();
		}
		m_pTKServerList->initList(root);
		resetRecentlyServerNode();

		setDefaultServerInfo();
		//保存成功登入的賬號密碼
		m_pTKServerList->setAccName(getAccount().c_str());
		m_pTKServerList->setPassword(getPassword().c_str());
		m_pTKServerList->setAccid(accid);
		m_pTKServerList->setServerKey(root["login_ticket"].asString());
		int timeStamp = atoi(root["valid_time"].asString().c_str());
		m_pTKServerList->setTimeStamp(timeStamp);
		MB_LOG("http登陆成功");
		m_pTKServerList->setIsGuest(m_bLastIsGuest);
		if (m_bAccIsExist == false) {
			//重新生成info文件
			saveAccount();
		}

		m_bCanVersion = true;

		m_pPlayBtn->setTouchEnabled(true);
		m_pNodeServerList->setVisible(true);

		MB_LOG("go to : MB_SceneServerList!\n");
		if (NSGameHelper::getSrcType() == NSGameHelper::ACCOUNT_TYPE_NORMAL)
		{
			onLoginClicked(NULL);
		}
	}
	else if (result == 1)
	{
		MB_Message::sharedMB_Message()->showMessage("帐号不存在");
	}
	else if (result == 2)
	{
		MB_Message::sharedMB_Message()->showMessage("账号或密码不正确");
	}
	else  if (result == 3)
	{
		MB_Message::sharedMB_Message()->showMessage("格式错误");
	}
	else
	{
		MB_Message::sharedMB_Message()->showMessage("连接服务器失败, 请确认网络连接");
	}
	return;
}

void MB_LayerFirstLogin::onAccountMgrReturnBack()
{
	saveAccount();
	getSceneAccountMgr()->setVisible(false);
	m_pPlayBtn->setTouchEnabled(true);
	resetAccount();
}

void MB_LayerFirstLogin::resetAccount()
{
	if (m_szAccount.empty())
	{
		m_pAccount->setString("游客体验");
	}
	else
	{
		if (m_szAccount.length() >= 8)
			m_pAccount->setString(m_szAccount.substr(0, 8).c_str());
		else
			m_pAccount->setString(m_szAccount.c_str());
	}

}
void MB_LayerFirstLogin::sendhttp_getServerList()
{
	std::string postinfo = LOGIN_SERVER_URL;
	char buff[200] = {};
	sprintf(buff, "server_list?srctype=%d&version=%s", NSGameHelper::getSrcType(), OCandCppHelper::getVervion());
	postinfo += buff;


	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::recvhttp_revServerList));

	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
//    MB_Message::sharedMB_Message()->showMessage("", 15);
}

void MB_LayerFirstLogin::recvhttp_revServerList(CCNode* node, CCHttpResponse* response)
{
	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);
	int result = root["result"].asInt();
//    MB_Message::sharedMB_Message()->removeALLMessage();
	if (result == 0)
	{
		m_pTKServerList = MB_ServerList::getInstance();
		if (m_pTKServerList->initList(root))
		{
			getSceneServerList()->setVisible(false);
			resetRecentlyServerNode();
		}
	}
	else
	{
		MB_Message::sharedMB_Message()->showMessage("服务器列表获取失败");
	}
}
void MB_LayerFirstLogin::onServerNodeTouched(CCNode* pSender)
{
	if (m_pSceneList)
	{
		getSceneServerList()->setVisible(false);
		m_pPlayBtn->setTouchEnabled(true);
		MB_ServerList::getInstance()->addRecentlyServerId(MB_ServerList::m_nSelectServerid);
		MB_ServerList::getInstance()->saveRecentlyServerList();
		resetRecentlyServerNode();
	}
}

void MB_LayerFirstLogin::onServerListClosed(CCObject* pSender)
{
	getSceneServerList()->setVisible(false);
    m_pPlayBtn->setTouchEnabled(true);
}

void MB_LayerFirstLogin::resetRecentlyServerNode()
{
	int id = MB_ServerList::m_nSelectServerid;
	if (id == 0)
	{
		return;
	}
	ServerList* serverList = MB_ServerList::getInstance()->getServerListByID(id);
	char buff[10] = {};
	sprintf(buff, "%d区", id);
	m_pServerName->setString(serverList->name.c_str());
	m_pServerID->setString(buff);

	m_pNodeServerState1->setVisible(false);
	m_pNodeServerState2->setVisible(false);
	m_pNodeServerState3->setVisible(false);
	switch (serverList->serverStatus)
	{
	case 1:
		m_pNodeServerState3->setVisible(true);
		break;
	case 2:
		m_pNodeServerState2->setVisible(true);
		break;
	default:
		m_pNodeServerState1->setVisible(true);
		break;
	}
}

void MB_LayerFirstLogin::onResetWnd()
{
}
bool MB_LayerFirstLogin::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LabelAccount", CCLabelTTF *, m_pAccount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ServerID", CCLabelTTF *, m_pServerID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ServerName", CCLabelTTF *, m_pServerName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Gou", CCControlButton *, m_pGou);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState1", CCNode*, m_pNodeServerState1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState2", CCNode*, m_pNodeServerState2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState3", CCNode*, m_pNodeServerState3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_account", CCNode*, m_pNodeAccount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerList", CCNode*, m_pNodeServerList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPlayBtn", CCControlButton*, m_pPlayBtn);
    
	return false;
}

SEL_MenuHandler MB_LayerFirstLogin::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickInputAccount", MB_LayerFirstLogin::onClickInputAccount);

	return NULL;
}

SEL_CCControlHandler MB_LayerFirstLogin::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLoginClicked", MB_LayerFirstLogin::onLoginClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickServerList", MB_LayerFirstLogin::onClickServerList);
        CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickYinSi", MB_LayerFirstLogin::onClickYinSi);
        CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickGouXuan", MB_LayerFirstLogin::onClickGouXuan);
	return NULL;
}

MB_SceneServerList* MB_LayerFirstLogin::getSceneServerList()
{
	if (m_pSceneList == NULL)
	{
		m_pSceneList = MB_SceneServerList::create();
		pushWindow(m_pSceneList);
	}
	return m_pSceneList;
}
MB_LayerAccountMgr* MB_LayerFirstLogin::getSceneAccountMgr()
{
	if (m_pAccountMgr == NULL)
	{
		m_pAccountMgr = MB_LayerAccountMgr::create();
		pushWindow(m_pAccountMgr);
	}
	return m_pAccountMgr;
}
void MB_LayerFirstLogin::onClickServerList(CCObject*)
{
	getSceneServerList()->setVisible(true);
	m_pPlayBtn->setTouchEnabled(false);
}
void MB_LayerFirstLogin::onClickYinSi(CCObject*)
{
#ifdef PLATFORM_YJ
    MB_YJMgr::getInstance()->openurl();
#elif defined(YJ_IOS)
//    MB_YJMgr_IOS::getInstance()->goLogin();
#endif
}
void MB_LayerFirstLogin::onClickGouXuan(CCObject*)
{
    m_pGou->setEnabled(!m_pGou->isEnabled());
}

void MB_LayerFirstLogin::onClickInputAccount(CCObject*)
{
	getSceneAccountMgr()->setVisible(true);
	getSceneAccountMgr()->openAccountLoginNode();
	m_pPlayBtn->setTouchEnabled(false);
}


void MB_LayerFirstLogin::onLoginClicked(CCObject *){
    if(!m_pGou->isEnabled()){
        MB_Message::sharedMB_Message()->showMessage("需要勾选我已阅读并同意才可登入游戏");
    }else
    {
        if (!m_bCanVersion)
        {
            if (NSGameHelper::getSrcType() == NSGameHelper::ACCOUNT_TYPE_NORMAL)
            {
                if (m_szAccount.empty())
                {
                    //遊客登入
                    setIsGuestAccount(true);
                    m_pPlayBtn->setTouchEnabled(true);
                    
                }
                else
                {
                    MB_Message::sharedMB_Message()->showMessage("", 15);
                    sendhttp_account_verify();// verify again
                }
            }
            else
            {
                onSdkLogin();
            }
        }
        else
        {
            getSceneServerList()->setVisible(false);
            getSceneServerList()->sendversion();
        }
    }
}

void MB_LayerFirstLogin::onSdkLogin()
{
    if (m_bIsChangeRole > 0)
    {
#ifdef PLATFORM_YJ
        MB_YJMgr::getInstance()->login(change_appid, change_channelid, change_userid, change_token);
#endif
    }
    else
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
#ifdef PLATFORM_YJ
        MB_YJMgr::getInstance()->goLogin();
#elif defined(YJ_IOS)
        MB_YJMgr_IOS::getInstance()->goLogin();
#endif
    }
}
void MB_LayerFirstLogin::onLoginStart(const char * str_1, const char* str_2, const char *str_3){
    
    //發送登入消息
    MB_Message::sharedMB_Message()->showMessage(" ", 600);
    m_pPlayBtn->setTouchEnabled(false);
    m_paccid = str_1;
    m_puin = str_2;
    std::string sid = str_3;
    std::string postinfo = LOGIN_SERVER_URL;
    
    postinfo += "&devid=";
    postinfo += OCandCppHelper::getUniString();
    postinfo += "&version=";
    postinfo += OCandCppHelper::getVervion();
    
    //    CCLOG("LoginServer : %s",postinfo.c_str());
    
    CCHttpRequest* httpRequest = new extension::CCHttpRequest();
    httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
    httpRequest->setUrl(postinfo.c_str());
    httpRequest->setTag("get server list");
    //httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
    httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
    extension::CCHttpClient::getInstance()->send(httpRequest);
    httpRequest->release();
}

void MB_LayerFirstLogin::onLoginStart(const char * str_1, const char* str_2, const char *str_3, const char *str_4){

	//發送登入消息
	MB_Message::sharedMB_Message()->showMessage(" ", 600);
	m_pPlayBtn->setTouchEnabled(false);
	std::string postinfo = LOGIN_SERVER_URL;
	m_paccid = str_1;
	m_puin = str_1;
#if defined(PLATFORM_YJ)
	postinfo += "loginquick?appid=";
	postinfo += str_1;
	postinfo += "&channelid=";
	postinfo += str_2;
	postinfo += "&userid=";
	postinfo += str_3;
	postinfo += "&token=";
	postinfo += str_4;
#endif
#if defined(YJ_IOS)
	postinfo += "loginquickios?appid=";
	postinfo += str_1;
	postinfo += "&channelid=";
	postinfo += str_2;
	postinfo += "&userid=";
	postinfo += str_3;
	postinfo += "&token=";
	postinfo += str_4;
#endif
	postinfo += "&devid=";
	postinfo += OCandCppHelper::getUniString();
	postinfo += "&version=";
	postinfo += OCandCppHelper::getVervion();

	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	//httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();


}

void MB_LayerFirstLogin::onLoginStart2(const char * sid, const char * appid)
{
	m_paccid = m_puin = sid;
	//發送登入消息
	//MB_Message::sharedMB_Message()->showMessage(" ", 600);
	m_pPlayBtn->setTouchEnabled(false);
	std::string postinfo = LOGIN_SERVER_URL;
	postinfo += "&devid=";
	postinfo += OCandCppHelper::getUniString();
	postinfo += "&version=";
	postinfo += OCandCppHelper::getVervion();
	CCLOG("=============================%s", postinfo.c_str());
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	//httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
}


void MB_LayerFirstLogin::onLoginStart(const char * sid)
{
	m_paccid = m_puin = sid;
	//發送登入消息
	MB_Message::sharedMB_Message()->showMessage(" ", 600);
	m_pPlayBtn->setTouchEnabled(false);
	std::string postinfo = LOGIN_SERVER_URL;
	postinfo += "&devid=";
	postinfo += OCandCppHelper::getUniString();
	postinfo += "&version=";
	postinfo += OCandCppHelper::getVervion();
	CCLOG("=============================%s", postinfo.c_str());
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	//httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();


}
void MB_LayerFirstLogin::onLoginStart(const char * userid, const char *tocken){
	m_paccid = m_puin = userid;
	MB_Message::sharedMB_Message()->showMessage(" ", 600);
	m_pPlayBtn->setTouchEnabled(false);
	std::string postinfo = LOGIN_SERVER_URL;
	postinfo += "&devid=";
	postinfo += OCandCppHelper::getUniString();
	postinfo += "&version=";
	postinfo += OCandCppHelper::getVervion();
	//    CCLOG(postinfo.c_str());
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("get server list");
	//httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();

}
void MB_LayerFirstLogin::onGusetLoginStart(){

	//發送登入消息
	MB_Message::sharedMB_Message()->showMessage(" ", 600);
	m_pPlayBtn->setTouchEnabled(false);
	std::string postinfo = LOGIN_SERVER_URL;
	const char *macaddress = OCandCppHelper::getUniString();
	postinfo += "guest?macaddr=";
	postinfo += macaddress;
	postinfo += "&devid=";
	postinfo += OCandCppHelper::getUniString();
	postinfo += "&version=";
	postinfo += OCandCppHelper::getVervion();
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(postinfo.c_str());
	httpRequest->setTag("guest login");
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onGuestHttpMsgRecv));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();
}
void MB_LayerFirstLogin::onGuestHttpMsgRecv(CCNode* node, CCHttpResponse* response){

	assert(response != NULL);
	MB_LOG("received server list response!");

	if (response->getResponseCode() != 200) {

		MB_Message::sharedMB_Message()->removeALLMessage();
		MB_Message::sharedMB_Message()->showMessage("连接超时, 请检查网路");
		m_pPlayBtn->setTouchEnabled(true);
		//        MB_LOG("couldn't connect to the account server.");
		return;
	}

	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);
	int result = root["result"].asInt();
	if (result == 1){

		std::string account = root["account"].asString().c_str();
		std::string password = root["password"].asString().c_str();
		time_t  m_tTimeStamp = time(NULL);
		//CCLOG(account.c_str());
		char curTime[32] = { 0 };
		sprintf(curTime, "%ld", m_tTimeStamp);
		m_bAccIsExist = true;
		MB_ServerList::getInstance()->setIsGuest(true);
		std::string pwd2 = account + password + curTime + "moon_game_login_key";
		char pMD5Code[34];
		GetMD5Code((unsigned char*)pwd2.c_str(), pwd2.length(), pMD5Code);
		std::string postinfo = LOGIN_SERVER_URL;
		postinfo += "baseinfo/?account=";
		postinfo += account;
		postinfo += "&loginkey=";
		postinfo += pMD5Code;
		postinfo += "&curtime=";
		postinfo += curTime;
		postinfo += (std::string("&version=") + OCandCppHelper::getVervion());
		m_puin = account;
		CCHttpRequest* httpRequest = new extension::CCHttpRequest();
		httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
		httpRequest->setUrl(postinfo.c_str());
		httpRequest->setTag("get server list");
		httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::onHttpMsgRecv));
		extension::CCHttpClient::getInstance()->send(httpRequest);
		httpRequest->release();
		MB_ServerList::getInstance()->setPassword(password.c_str());

	}
	else {

		MB_Message::sharedMB_Message()->removeALLMessage();
		MB_Message::sharedMB_Message()->showMessage("被禁止使用游客帐号");
	}

}
void MB_LayerFirstLogin::sendhttp_notice_request()
{
	CCHttpRequest* httpRequest = new extension::CCHttpRequest();
	httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
	httpRequest->setUrl(NOTICE_SERVER_URL);
	httpRequest->setTag("request server notice");
	httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerFirstLogin::recvhttp_notice_request));
	extension::CCHttpClient::getInstance()->send(httpRequest);
	httpRequest->release();

}
void MB_LayerFirstLogin::recvhttp_notice_request(CCNode* node, CCHttpResponse* response)
{
	assert(response != NULL);

	CCLOG("%d", response->getResponseCode());
	if (response->getResponseCode() != 200)
	{
		MB_Message::sharedMB_Message()->removeALLMessage();
		MB_Message::sharedMB_Message()->showMessage("公告服务器连接超时, 请检查网路");
		//MB_LOG("couldn't connect to the account server.");
	}
	else
	{
		Json::Reader reader;
		Json::Value  root;
		std::string data;
		std::string responseData;
		data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
		reader.parse(data, root);

		std::string notice = root["notice"].asString();
		//        MB_LayerScrollMessage* pLayer = MB_LayerScrollMessage::create();
		//        if (pLayer)
		//        {
		//            pLayer->setMessage(notice.c_str());
		//            addChild(pLayer);
		//        }
		//        else
		{
			MB_Message::sharedMB_Message()->showMessage("提示:", notice.c_str(), "确定");
		}

	}
}
void MB_LayerFirstLogin::onHttpMsgRecv(CCNode* node, CCHttpResponse* response)
{
	assert(response != NULL);
	MB_LOG("received server list response!");
	MB_Message::sharedMB_Message()->removeALLMessage();
	if (response->getResponseCode() != 200)
	{
		m_pPlayBtn->setTouchEnabled(true);
		MB_LOG("couldn't connect to the account server.");
		sendhttp_notice_request();

		return;
	}
	m_bIsChangeRole = 0;
	
	Json::Reader reader;
	Json::Value  root;
	std::string data;
	std::string responseData;
	data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
	reader.parse(data, root);
	int result = root["result"].asInt();
	MB_Message::sharedMB_Message()->removeALLMessage();
	if (result == 0)
	{
		if (m_pTKServerList == NULL)
		{
			m_pTKServerList = MB_ServerList::getInstance();
			//            resetRecentlyServerNode();
		}
		m_pTKServerList->initList(root);
		resetRecentlyServerNode();
		//setDefaultServerInfo();
		//保存成功登入的賬號密碼
		int acc = root["accid"].asInt();
		char accid[64];
		sprintf(accid, "%d", acc);
		m_pTKServerList->setAccid(accid);

		int timeStamp = atoi(root["valid_time"].asString().c_str());
		m_pTKServerList->setTimeStamp(timeStamp);
		MB_LOG("http登陆成功");
		if (MB_ClientSocket::isAlive() == true) {
			MB_LOG("socket is old");
			MB_ClientSocket::destroyInstance();
		}
		else
		{
			MB_LOG("socket is new");
		}
		setDefaultServerInfo();
		m_pTKServerList->setAccName(m_puin.c_str());//91下记录的uni 我门伺服器為guestid
#ifdef PLATFORM_YJ   //i
#elif defined(YJ_IOS)// ??
#else
		m_pTKServerList->setIsGuest(true);
		createAccInfo(m_puin.c_str(), m_pTKServerList->getPassword().c_str());
#endif
		MB_Message::sharedMB_Message()->removeALLMessage();
		MB_LOG("go to : MB_SceneServerList!\n");
		if (m_bLastIsGuest)
		{
			getSceneServerList()->sendversion();
		}
		else
		{
			m_bCanVersion = true;
			m_pNodeServerList->setVisible(true);
			m_pPlayBtn->setTouchEnabled(true);
		}
		return;
	}
	else
	{
		if (result == 1)
		{
			MB_Message::sharedMB_Message()->showMessage("帐号不存在");
		}
		else if (result == 2)
		{
			MB_Message::sharedMB_Message()->showMessage("账号或密码不正确");
		}
		else  if (result == 3)
		{
			MB_Message::sharedMB_Message()->showMessage("格式错误");
		}
		else if (result == 4)
		{
			MB_Message::sharedMB_Message()->showMessage("账号验证超时，请重试");
		}
		else
		{
			MB_Message::sharedMB_Message()->showMessage("连接服务器失败, 请确认网络连接");
		}
	}
	m_pPlayBtn->setTouchEnabled(true);

	return;
}

void  MB_LayerFirstLogin::createAccInfo(const char *gusetname, const char *gustpasswd){

	//定义文档和節点指针
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "Signature");
	//設置根節点
	xmlDocSetRootElement(doc, root_node);
	xmlNodePtr node;
	//char value[1024];

	node = xmlNewNode(NULL, BAD_CAST "AccountInfo");
	xmlAddChild(root_node, node);

	xmlNewProp(node, BAD_CAST "Account", BAD_CAST gusetname);
	xmlNewProp(node, BAD_CAST "Password", BAD_CAST gustpasswd);
	xmlNewProp(node, BAD_CAST "IsGuest", BAD_CAST "1");
	xmlNewProp(node, BAD_CAST "ServerID", BAD_CAST "-1");
	//存储xml文档
	std::string fullPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.xml";
	std::string fullAESPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.cb";
	int nRel = xmlSaveFormatFileEnc(fullPathName.c_str(), doc, "UTF-8", 1);

	if (nRel != -1)
	{
		printf("Info.xml被创建，写入%d个字节\n", nRel);
	}

	//释放文档内節点動态申請的内存
	xmlFreeDoc(doc);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	FILE* srcfile = NULL;
	FILE* destfile = NULL;
	if ((srcfile = fopen(fullPathName.c_str(), "r")) == NULL)
	{
		MB_LOG("info src file open fail.\n");
		return;
	}
	if ((destfile = fopen(fullAESPathName.c_str(), "w")) == NULL)
	{
		fclose(srcfile);
		remove(fullPathName.c_str());
		MB_LOG("info dest file open fail.\n");
		return;
	}

	unsigned char pwd2[516];
	memset(pwd2, 0, 516);
	passwd_to_utf16(aeskey, 258, 1024, pwd2);
	int ret = encrypt_stream(srcfile, destfile, pwd2, 512);
	if (ret == 0) {
		MB_LOG("encrypt succeed!\n");
	}
	else
	{
		MB_LOG("encrypt fail!");
	}
	fclose(srcfile);
	fclose(destfile);
	remove(fullPathName.c_str());
#endif
}
void MB_LayerFirstLogin::setDefaultServerInfo()
{
	MB_ClientSocket::getInstance()->setServerIP(m_pTKServerList->getSelectIP());
	MB_ClientSocket::getInstance()->setServerPort(m_pTKServerList->getSelectPort());
}


void MB_LayerFirstLogin::saveAccount()
{
	//定义文档和節点指针
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");

	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "Signature");

	//設置根節点
	xmlDocSetRootElement(doc, root_node);

	xmlNodePtr node;
	//char value[1024];

	node = xmlNewNode(NULL, BAD_CAST "AccountInfo");
	xmlAddChild(root_node, node);

	xmlNewProp(node, BAD_CAST "Account", BAD_CAST m_szAccount.c_str());
	xmlNewProp(node, BAD_CAST "Password", BAD_CAST m_szPassword.c_str());
	xmlNewProp(node, BAD_CAST "IsGuest", BAD_CAST(m_bLastIsGuest ? "1" : "0"));

	//存储xml文档
	std::string fullPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.xml";
	std::string fullAESPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.cb";
	int nRel = xmlSaveFormatFileEnc(fullPathName.c_str(), doc, "UTF-8", 1);

	if (nRel != -1)
	{
		printf("Info.xml被创建，写入%d个字节\n", nRel);
	}

	//释放文档内節点動态申請的内存
	xmlFreeDoc(doc);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	FILE* srcfile = NULL;
	FILE* destfile = NULL;
	if ((srcfile = fopen(fullPathName.c_str(), "r")) == NULL)
	{
		MB_LOG("info src file open fail.\n");
		return;
	}
	if ((destfile = fopen(fullAESPathName.c_str(), "w")) == NULL)
	{
		fclose(srcfile);
		remove(fullPathName.c_str());
		MB_LOG("info dest file open fail.\n");
		return;
	}

	unsigned char pwd2[516];
	memset(pwd2, 0, 516);
	passwd_to_utf16(aeskey, 258, 1024, pwd2);
	int ret = encrypt_stream(srcfile, destfile, pwd2, 512);
	if (ret == 0) {
		MB_LOG("encrypt succeed!\n");
	}
	else
	{
		MB_LOG("encrypt fail!");
	}
	fclose(srcfile);
	fclose(destfile);
	remove(fullPathName.c_str());
#endif

}

void MB_LayerFirstLogin::loadAccount()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fullAESPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.cb";
	FILE* srcfile = fopen(fullAESPathName.c_str(), "r");

	if (srcfile != NULL)
	{

		unsigned char pwd2[516];
		memset(pwd2, 0, 516);
		passwd_to_utf16(aeskey, 258, 1024, pwd2);
		char * ret = decrypt_streamTobuffer(srcfile, pwd2, 512);
		fclose(srcfile);
		if (ret != NULL)
		{

			MB_LOG("decrypt succeed!\n");
			xmlDocPtr g_sharedDoc = xmlReadMemory(ret, strlen(ret), NULL, "utf-8", XML_PARSE_RECOVER);
#else

	std::string fullAESPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.xml";

	xmlDocPtr g_sharedDoc = xmlReadFile(fullAESPathName.c_str(), "utf-8", XML_PARSE_RECOVER);
	if (g_sharedDoc == NULL)
	{
		return;
	}
#endif
	xmlNodePtr root;
	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	while (curNode != NULL)
	{
		if (xmlStrcmp(curNode->name, BAD_CAST "AccountInfo"))
		{
			curNode = curNode->next;
			continue;
		}
		struct _xmlAttr * attr = curNode->properties;
		while (attr != NULL)
		{

			if (!xmlStrcmp(attr->name, BAD_CAST "Account"))
			{
				char * value = (char*)xmlNodeGetContent(attr->children);
				m_szAccount = value;
				free(value);
			}

			if (!xmlStrcmp(attr->name, BAD_CAST "Password"))
			{
				char * value = (char*)xmlNodeGetContent(attr->children);
				m_szPassword = value;
				free(value);
			}
			if (!xmlStrcmp(attr->name, BAD_CAST "IsGuest"))
			{
				char * value = (char*)xmlNodeGetContent(attr->children);
				m_bLastIsGuest = (atoi(value) == 1);
				free(value);
			}
			attr = attr->next;
		}

		curNode = curNode->next;
	}

	xmlFreeDoc(g_sharedDoc);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	free(ret);
}
	}
#endif
	m_bAccIsExist = true;
	resetAccount();
}


