

#include "Game.h"
#include "MB_SceneRegist.h"
#include "aescrypt.h"
#include "password.h"
#include "md5.h"
#include "../Common/SDS_NetWorkDefine.h"
#include "MB_LayerRoleDetail.h"
USING_NS_CC;
USING_NS_CC_EXT;


MB_SceneRegist::MB_SceneRegist()
{
    m_bShowRoleInfoPanel = true;
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_SceneRegist", true);
}

MB_SceneRegist::~MB_SceneRegist()
{
    unscheduleAllSelectors();
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->unregisterCCNodeLoader("MB_SceneRegist");
    
    CC_SAFE_RELEASE_NULL(m_pEditName);
    CC_SAFE_RELEASE_NULL(m_pEditPassword);
    CC_SAFE_RELEASE_NULL(m_pEditPasswordConfirm);
    CC_SAFE_RELEASE_NULL(m_pEditPhone);
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_SceneRegist", false);
}



MB_SceneRegist * MB_SceneRegist::create(int LayerTag){

    MB_SceneRegist *ptr = new MB_SceneRegist();
    ptr->setTag(LayerTag);
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
        
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_SceneRegist::init()
{
	if ( !MB_ResWindow::init() )
	{
		return false;
	}
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("MB_SceneRegist", MB_SceneRegistLoader::loader());
    
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile( (this->getTag() == LAYER_TAG_BIND_GUEST? "res/main_layer_regist.ccbi" : "res/gui_login_regist.ccbi"), this);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    this->addChild(pScene);
    
    //确定用不到了就要释放
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    m_pEditName->setFontColor(ccBLACK);
    m_pEditPassword->setFontColor(ccBLACK);
    m_pEditPasswordConfirm->setFontColor(ccBLACK);
    m_pEditPhone->setFontColor(ccBLACK);
	return true;
}

bool MB_SceneRegist::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if ( 0 == strcmp(pMemberVariableName, "Account")) {
        
        initAccountEditBox( (CCEditBox*)pNode);
        
    }
    else if (0 == strcmp(pMemberVariableName, "Password")) {
        
        initPasswordEditBox( (CCEditBox*)pNode);
        
    }
    else if (0 == strcmp(pMemberVariableName, "Password2")) {
        
        initPassword2EditBox((CCEditBox*)pNode);
    }
    else if (0 == strcmp(pMemberVariableName, "MobilephoneNumber")) {
        initPhoneEditBox((CCEditBox*)pNode);
    }
    
    return true;
}

SEL_MenuHandler MB_SceneRegist::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_SceneRegist::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_SceneRegist::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCommitClicked",MB_SceneRegist::onCommitClicked);
    
    return NULL;
}
void MB_SceneRegist::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    MB_LOG("onNodeLoaded succeed!");
}

void MB_SceneRegist::onCommitClicked(CCObject* pSender)
{
    std::string accName, accPassword, accPassword2, phoneNo;
    
    if (m_pEditName->getText() != NULL)
    {
        accName = m_pEditName->getText();
        if(MB_DirtyWordsCheck::getInstance()->checkDatabuf(accName.c_str())){
            
            MB_Message::sharedMB_Message()->showMessage("含有非法字符，请修改您的名字");
            return;
        }
        
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("账号不能为空.");
        MB_LOG("Need input account!");
        return;
    }
    
    if( m_pEditPassword->getText() != NULL)
    {
        accPassword = m_pEditPassword->getText();
        if(accPassword.length() == 0){
        
            MB_Message::sharedMB_Message()->showMessage("密码不能为空.");
            MB_LOG("Need input password!");
            return;

        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("密码不能为空.");
        MB_LOG("Need input password!");
        return;
    }
    for (int i = 0; i <  accPassword.size(); i++) {
        
        if(!(( accPassword[i] >='a' &&  accPassword[i] <='z' ) || ( accPassword[i] >='A' && accName[i] <='Z') || ( accPassword[i] >='0' &&  accPassword[i] <='9'))){
            
            MB_Message::sharedMB_Message()->showMessage("密码只能用数字和字母");
            return;
        }
    }

    if( m_pEditPasswordConfirm->getText() != NULL)
    {
        accPassword2 = m_pEditPasswordConfirm->getText();
        if(accPassword2.length()  == 0){
        
            MB_Message::sharedMB_Message()->showMessage("密码确认不能为空.");
            MB_LOG("Need input password tiwce!");
            return;
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("密码确认不能为空.");
        MB_LOG("Need input password tiwce!");
        return;
    }
    
    if (m_pEditPhone->getText() != NULL) {
        phoneNo = m_pEditPhone->getText();
    }
    
    if (accPassword.compare(accPassword2) != 0) {
        MB_Message::sharedMB_Message()->showMessage("密码不匹配.");
        MB_LOG("Password is not the same!");
        return;
    }
    
    MB_Message::sharedMB_Message()->showMessage("",30);
    
    if (this->getTag() == LAYER_TAG_BIND_GUEST) {
        
        time_t  m_tTimeStamp = time(NULL);
        char curTime[32] = {0};
        sprintf(curTime, "%ld", m_tTimeStamp);
        char pMD5Code[34];
        accPassword += "moon_game_password_key";
        GetMD5Code((unsigned char*)accPassword.c_str(), accPassword.length(), pMD5Code);
        std::string postinfo = LOGIN_SERVER_URL;
        
        std::string pwd2 =  MB_ServerList::getInstance()->getAccName() + MB_ServerList::getInstance()->getPassword() + curTime + "moon_game_login_key";
        char pMD5CodeFist[34];
        GetMD5Code((unsigned char*)pwd2.c_str(), pwd2.length(), pMD5CodeFist);
        
        postinfo+= "bind?account=" + MB_ServerList::getInstance()->getAccName()+ "&loginkey=" + pMD5CodeFist + "&curtime=" + curTime + "&newaccount=" + accName + "&newpassword=" + pMD5Code + "&phoneNum=" + phoneNo;
        
        CCHttpRequest* httpRequest = new extension::CCHttpRequest();
        httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
        httpRequest->setUrl(postinfo.c_str());
        httpRequest->setTag("geuest bind");
        httpRequest->setResponseCallback(this, callfuncND_selector(MB_SceneRegist::onHttpMsgRecv));
        extension::CCHttpClient::getInstance()->send(httpRequest);
        httpRequest->release();

        
    }else {
    
        char pMD5Code[34];
        accPassword += "moon_game_password_key";
        GetMD5Code((unsigned char*)accPassword.c_str(), accPassword.length(), pMD5Code);
        
        std::string postinfo = "account=" + accName + "&password="+ pMD5Code + "&phoneNum=" + phoneNo + "&devid=" + OCandCppHelper::getUniString();
        
        std::string url = LOGIN_SERVER_URL;
        url += "create/";
        
        //发送http消息
        extension::CCHttpRequest* httpRequest = new extension::CCHttpRequest();
        httpRequest->setRequestType(extension::CCHttpRequest::kHttpPost);
        httpRequest->setUrl(url.c_str());
        httpRequest->setTag("acc create");
        httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
        httpRequest->setResponseCallback(this, callfuncND_selector(MB_SceneRegist::onHttpMsgRecv));
        extension::CCHttpClient::getInstance()->send(httpRequest);
        httpRequest->release();
    }
}

void MB_SceneRegist::onBackClicked(CCObject* pSender)
{
    removeFromParent();
}

void MB_SceneRegist::initAccountEditBox(CCEditBox* editBox)
{
    editBox->setFontColor(ccWHITE);
    editBox->setInputMode(kEditBoxInputModeACSII);
    editBox->setDelegate(this);
    
    m_pEditName = editBox;
    m_pEditName->retain();
}

void MB_SceneRegist::initPasswordEditBox(CCEditBox* editBox)
{
    editBox->setFontColor(ccWHITE);
    editBox->setInputFlag(kEditBoxInputFlagPassword);
    editBox->setInputMode(kEditBoxInputModeSingleLine);
    editBox->setDelegate(this);
    
    m_pEditPassword = editBox;
    m_pEditPassword->retain();
}

void MB_SceneRegist::initPassword2EditBox(CCEditBox* editBox)
{
    editBox->setFontColor(ccWHITE);
    editBox->setInputFlag(kEditBoxInputFlagPassword);
    editBox->setInputMode(kEditBoxInputModeSingleLine);
    editBox->setDelegate(this);
    
    m_pEditPasswordConfirm = editBox;
    m_pEditPasswordConfirm->retain();
}

void MB_SceneRegist::initPhoneEditBox(CCEditBox* editBox)
{
    editBox->setFontColor(ccWHITE);
    editBox->setDelegate(this);
    
    m_pEditPhone = editBox;
    m_pEditPhone->retain();
}

void MB_SceneRegist::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    m_pEditName->setPosition(m_pEditName->getPosition());
    m_pEditPassword->setPosition(m_pEditPassword->getPosition());
    m_pEditPasswordConfirm->setPosition(m_pEditPasswordConfirm->getPosition());
    m_pEditPhone->setPosition(m_pEditPhone->getPosition());
    
    MB_LOG("editBox %p DidBegin !", editBox);
}

void MB_SceneRegist::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    MB_LOG("editBox %p DidEnd !", editBox);
    std::string str = editBox->getText();
    int pos;
    do {
        pos = str.find("\xe2\x80\x86");
        if (pos != std::string::npos) {
            str.replace(pos, 3, "");
        }
        else
        {
            break;
        }
    } while (1);
    
    editBox->setText(str.c_str());
}

void MB_SceneRegist::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    MB_LOG("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void MB_SceneRegist::editBoxReturn(CCEditBox* editBox)
{
    MB_LOG("editBox %p was returned !");
    
}

void MB_SceneRegist::onHttpMsgRecv(CCNode* node, CCHttpResponse* response)
{
    assert(response != NULL);
    
    MB_LOG("received regist response!");
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    if ( response->getResponseCode() != 200) {
        MB_LOG("couldn't connect to the account server.");
        MB_Message::sharedMB_Message()->showMessage("错误", "服务器连接失败, 请检查网络.", "确定");
        return;
    }
    Json::Reader reader;
    Json::Value  root;
    std::string data ;
    std::string responseData;
    data.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
    reader.parse(data, root);
    int result = root["result"].asInt();
    if(result == 0){
        
        MB_ServerList::getInstance()->setIsGuest(false);
        createAccInfo();
        //创建成功，跳转到登录界面
        onBackClicked(NULL);
        
        CCNode* pNode = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(ROLED_ETAIL_TAG);
        if(pNode && dynamic_cast<MB_LayerRoleDetail*>(pNode))
        {
            ((MB_LayerRoleDetail*)pNode)->onResetWnd();
        }
        
        MB_LOG("go to : MB_SceneLogin!\n");

    }else if(result == 1){
    
        MB_Message::sharedMB_Message()->showMessage("帐号已存在");
        
    }else if(result == 2){    
        
        MB_Message::sharedMB_Message()->showMessage("格式错误");
        
    } else if(result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("帐号名称有非法字符");
        
    }else if(result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("验证失败");
        
    }else {
    
        MB_Message::sharedMB_Message()->showMessage("未知错误");
    }
    return;
}

void MB_SceneRegist::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case 10002://登陆注册反馈
            uint16_t Data;
            recvPacket->readU16(&Data);
            if (Data == 1)
            {
                CCScene *newScene =  MB_SceneMain::scene();
                CCDirector::sharedDirector()->replaceScene(newScene);
                MB_LOG("Login regist succeed!\n");
            }
            else
            {
                MB_LOG("Login regist failed! errCode: %d\n",Data);
            }
            break;
        default:
            break;
    }
}

void MB_SceneRegist::createAccInfo()
{
    //定义文档和节点指针
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    
    xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST "Signature");
    
    //设置根节点
    xmlDocSetRootElement(doc,root_node);
    
    xmlNodePtr node;
    //char value[1024];
    
    node = xmlNewNode(NULL,BAD_CAST "AccountInfo");
    xmlAddChild(root_node,node);
    
    xmlNewProp(node,BAD_CAST "Account",BAD_CAST m_pEditName->getText());
    xmlNewProp(node,BAD_CAST "Password",BAD_CAST m_pEditPassword->getText());
    xmlNewProp(node,BAD_CAST "IsGuest" ,BAD_CAST (MB_ServerList::getInstance()->getIsGuest() ? "1":"0"));
    xmlNewProp(node,BAD_CAST "ServerID",BAD_CAST "-1");
    
    //存储xml文档
    std::string fullPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.xml";
    std::string fullAESPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "account.cb";
    int nRel = xmlSaveFormatFileEnc(fullPathName.c_str(), doc, "UTF-8", 1);
    
    if (nRel != -1)
    {
        printf("Info.xml被创建，写入%d个字节\n", nRel);
    }
    
    //释放文档内节点动态申请的内存
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


