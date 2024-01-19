//
//  MB_LayerAccountMgr.cpp
//  ProjectSDS
//
//  Created by crimoon00007 on 14-3-10.
//
//

#include "MB_LayerAccountMgr.h"
#include "MB_LayerFirstLogin.h"
#include "md5.h"
#include "../Common/SDS_NetWorkDefine.h"

MB_LayerAccountMgr::MB_LayerAccountMgr()
{
    m_pExistAccountLogin = NULL;
    m_pAccountRegist = NULL;
    m_pChangePassword = NULL;
    m_pFillExistAccount = NULL;
    m_pFillExistPassword = NULL;

    m_pNewAccount = NULL;
    m_pNewPassword1 = NULL;
    m_pNewPassword2 = NULL;
    m_pMobilephoneNumber = NULL;

    m_pChangeOfAccount = NULL;
    m_pChangeOfPassword = NULL;
    m_pChangedPassword1 = NULL;
    m_pChangedPassword2 = NULL;
    
    m_pItemLogin = NULL;
    m_pItemRegister = NULL;
    m_pItemResetPW = NULL;
}

MB_LayerAccountMgr::~MB_LayerAccountMgr()
{
    CC_SAFE_RELEASE_NULL(m_pExistAccountLogin);
    CC_SAFE_RELEASE_NULL(m_pAccountRegist);
    CC_SAFE_RELEASE_NULL(m_pChangePassword);
    CC_SAFE_RELEASE_NULL(m_pAccountRegist);

    CC_SAFE_RELEASE_NULL(m_pChangePassword);
    CC_SAFE_RELEASE_NULL(m_pFillExistAccount);
    CC_SAFE_RELEASE_NULL(m_pFillExistPassword);

    CC_SAFE_RELEASE_NULL(m_pNewAccount);
    CC_SAFE_RELEASE_NULL(m_pNewPassword1);
    CC_SAFE_RELEASE_NULL(m_pNewPassword2);
    CC_SAFE_RELEASE_NULL(m_pMobilephoneNumber);

    CC_SAFE_RELEASE_NULL(m_pChangeOfAccount);
    CC_SAFE_RELEASE_NULL(m_pChangeOfPassword);
    CC_SAFE_RELEASE_NULL(m_pChangedPassword1);
    CC_SAFE_RELEASE_NULL(m_pChangedPassword2);

}

bool MB_LayerAccountMgr::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/login_layer_account.ccbi", this);
    if (pNode)
    {
        addChild(pNode);
    }
    CC_SAFE_RELEASE(pCCBReader);

    onResetWnd();

    m_pFillExistPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pNewPassword1->setInputFlag(kEditBoxInputFlagPassword);
    m_pNewPassword2->setInputFlag(kEditBoxInputFlagPassword);
    m_pChangeOfPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pChangedPassword1->setInputFlag(kEditBoxInputFlagPassword);
    m_pChangedPassword2->setInputFlag(kEditBoxInputFlagPassword);
    
    
    m_pItemLogin->setIsScale(false);
    m_pItemRegister->setIsScale(false);
    m_pItemResetPW->setIsScale(false);
    return true;
}

void MB_LayerAccountMgr::onResetWnd()
{
    onExistAccountLogin(NULL);
    MB_TARGET_PARENT(MB_LayerFirstLogin,ptr);
    if(ptr)
    {
        m_pFillExistAccount->setText(ptr->getAccount().c_str());
        m_pFillExistPassword->setText(ptr->getPassword().c_str());
    }
}

void MB_LayerAccountMgr::onExistAccountLogin(CCObject*)
{
    m_pExistAccountLogin->setVisible(true);
    m_pAccountRegist->setVisible(false);
    m_pChangePassword->setVisible(false);
    m_pItemResetPW->setEnabled(true);
    m_pItemRegister->setEnabled(true);
    m_pItemLogin->setEnabled(false);
}

void MB_LayerAccountMgr::onNewAccountRegist(CCObject*)
{
    m_pExistAccountLogin->setVisible(false);
    m_pAccountRegist->setVisible(true);
    m_pChangePassword->setVisible(false);
    m_pItemResetPW->setEnabled(true);
    m_pItemRegister->setEnabled(false);
    m_pItemLogin->setEnabled(true);
}

void MB_LayerAccountMgr::onChangePassword(CCObject*)
{
    m_pExistAccountLogin->setVisible(false);
    m_pAccountRegist->setVisible(false);
    m_pChangePassword->setVisible(true);
    m_pItemResetPW->setEnabled(false);
    m_pItemRegister->setEnabled(true);
    m_pItemLogin->setEnabled(true);
}

void MB_LayerAccountMgr::onFilledAccountClicked(CCObject*)
{
    const char* pAccount = m_pFillExistAccount->getText();
    m_pFillExistPassword->setText(m_pFillExistAccount->getText());
    const char* pPassword = m_pFillExistPassword->getText();
    if (strlen(pAccount)==0 || strlen(pPassword)==0)
    {
        MB_Message::sharedMB_Message()->showMessage("账号和密码不能为空");
        return;
    }

    MB_TARGET_PARENT(MB_LayerFirstLogin,ptr);
    if(ptr)
    {
        ptr->setAccount(m_pFillExistAccount->getText());
        ptr->setPassword(m_pFillExistPassword->getText());
        ptr->setIsGuestAccount(false);
        ptr->onAccountMgrReturnBack();
    }

}

bool MB_LayerAccountMgr::checkRegistAccount(std::string& acc,
                                            std::string& pwd1,
                                            std::string& pwd2,
                                            std::string& phone)
{
    if (m_pNewAccount->getText() != NULL)
    {
        m_pNewPassword1->setText(m_pNewAccount->getText());
        m_pNewPassword2->setText(m_pNewAccount->getText());
        acc = m_pNewAccount->getText();
        if(MB_DirtyWordsCheck::getInstance()->checkDatabuf(acc.c_str()))
        {
            MB_Message::sharedMB_Message()->showMessage("错误","含有非法字符, 请修改您的名字","确定");
            return false;
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("", "账号不能为空.", "确定");
        MB_LOG("Need input account!");
        return false;
    }
    if( m_pNewPassword1->getText() != NULL)
    {
        pwd1 = m_pNewPassword1->getText();
        if(pwd1.length() == 0){

            MB_Message::sharedMB_Message()->showMessage("", "密码不能为空.", "确定");
            MB_LOG("Need input password!");
            return false;
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("", "密码不能为空.", "确定");
        MB_LOG("Need input password!");
        return false;
    }
    for (int i = 0; i <  pwd1.size(); i++)
    {

        if(!(( pwd1[i] >='a' &&  pwd1[i] <='z' ) || ( pwd1[i] >='A' && pwd1[i] <='Z') || ( pwd1[i] >='0' &&  pwd1[i] <='9')))
        {
            MB_Message::sharedMB_Message()->showMessage("错误","密码只能用数字和字母","确定");
            return false;
        }
    }

    if( m_pNewPassword2->getText() != NULL)
    {
        pwd2 = m_pNewPassword2->getText();
        if(pwd2.length()  == 0){

            MB_Message::sharedMB_Message()->showMessage("", "密码确认不能为空.", "确定");
            MB_LOG("Need input password tiwce!");
            return false;
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("", "密码确认不能为空.", "确定");
        MB_LOG("Need input password tiwce!");
        return false;
    }

    if (m_pMobilephoneNumber->getText() != NULL)
    {
        phone = m_pMobilephoneNumber->getText();
    }

    if (pwd1.compare(pwd2) != 0)
    {
        MB_Message::sharedMB_Message()->showMessage("", "密码不匹配.", "确定");
        MB_LOG("Password is not the same!");
        return false;
    }

    return true;
}

void MB_LayerAccountMgr::recvhttp_regist_account(CCNode* pNode,CCHttpResponse* response)
{
    assert(response != NULL);

    MB_LOG("received regist response!");
    MB_Message::sharedMB_Message()->removeALLMessage();

    if ( response->getResponseCode() != 200)
    {
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
    if(result == 0)
    {

        MB_ServerList::getInstance()->setIsGuest(false);
        MB_TARGET_PARENT(MB_LayerFirstLogin, ptr);
        if (ptr)
        {
            ptr->setAccount(m_pNewAccount->getText());
            ptr->setPassword(m_pNewPassword1->getText());
            //创建成功，跳转到登录界面
            ptr->setIsGuestAccount(false);
            onReturnBackClicked(NULL);
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

void MB_LayerAccountMgr::sendhttp_regist_account(std::string& acc,
                                                std::string& pwd,
                                                std::string& phone)
{
    char pMD5Code[34];
    pwd += "moon_game_password_key";
    GetMD5Code((unsigned char*)pwd.c_str(), pwd.length(), pMD5Code);
    std::string postinfo = "account=" + acc + "&password="+ pMD5Code + "&phoneNum=" + phone + "&devid=" + OCandCppHelper::getUniString();

    std::string url = LOGIN_SERVER_URL;
    url += "create/";

    CCLOG("RegisterAccount:%s",postinfo.c_str());
    //发送http消息
    extension::CCHttpRequest* httpRequest = new extension::CCHttpRequest();
    httpRequest->setRequestType(extension::CCHttpRequest::kHttpPost);
    httpRequest->setUrl(url.c_str());
    httpRequest->setTag("acc create");
    httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
    httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerAccountMgr::recvhttp_regist_account));
    extension::CCHttpClient::getInstance()->send(httpRequest);
    httpRequest->release();

}

void MB_LayerAccountMgr::sendhttp_regist_account_guest(std::string& acc,
                                                      std::string& pwd,
                                                      std::string& phone)
{
    time_t  m_tTimeStamp = time(NULL);
    char curTime[32] = {0};
    sprintf(curTime, "%ld", m_tTimeStamp);
    char pMD5Code[34];
    pwd += "moon_game_password_key";
    GetMD5Code((unsigned char*)pwd.c_str(), pwd.length(), pMD5Code);
    std::string postinfo = LOGIN_SERVER_URL;

    std::string pwd2 =  MB_ServerList::getInstance()->getAccName() + MB_ServerList::getInstance()->getPassword() + curTime + "moon_game_login_key";
    char pMD5CodeFist[34];
    GetMD5Code((unsigned char*)pwd2.c_str(), pwd2.length(), pMD5CodeFist);

    postinfo+= "bind?account=" + acc+ "&loginkey=" + pMD5CodeFist + "&curtime=" + curTime + "&newaccount=" + acc + "&newpassword=" + pMD5Code + "&phoneNum=" + phone + "&devid=" + OCandCppHelper::getUniString();;
    
    CCLOG("RegisterAccount:%s",postinfo.c_str());

    CCHttpRequest* httpRequest = new extension::CCHttpRequest();
    httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
    httpRequest->setUrl(postinfo.c_str());
    httpRequest->setTag("geuest bind");
    httpRequest->setResponseCallback(this, callfuncND_selector(MB_LayerAccountMgr::recvhttp_regist_account));
    extension::CCHttpClient::getInstance()->send(httpRequest);
    httpRequest->release();

}

void MB_LayerAccountMgr::onCommitClicked(CCObject*)
{
    std::string accName, accPassword, accPassword2, phoneNo;
    if (checkRegistAccount(accName, accPassword, accPassword2, phoneNo))
    {
        MB_Message::sharedMB_Message()->showMessage("",30);
        if (this->getTag() == LAYER_TAG_BIND_GUEST)
        {
            sendhttp_regist_account_guest(accName, accPassword, phoneNo);
        }
        else
        {
            sendhttp_regist_account(accName, accPassword, phoneNo);
        }
    }
    else
    {
        CCLog("Input error!");
    }
}


void MB_LayerAccountMgr::onGuestLoginClicked(CCObject*)
{
    MB_TARGET_PARENT(MB_LayerFirstLogin,ptr);
    if(ptr)
    {
        ptr->setIsGuestAccount(true);
    }
    //popWindow();
}

void MB_LayerAccountMgr::onChangeAffirmClicked(CCObject*)
{

}

void MB_LayerAccountMgr::onReturnBackClicked(CCObject*)
{
    MB_TARGET_PARENT(MB_LayerFirstLogin,ptr);
    if(ptr)
    {
        ptr->onAccountMgrReturnBack();
    }
    //popWindow();
}

bool MB_LayerAccountMgr::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_exist_login", CCNode*, m_pExistAccountLogin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_account_regist", CCNode*, m_pAccountRegist);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_change_password", CCNode*, m_pChangePassword);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ExistAccount", CCEditBox*, m_pFillExistAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ExistPassword", CCEditBox*, m_pFillExistPassword);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NewAccount", CCEditBox*, m_pNewAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NewPassword1", CCEditBox*, m_pNewPassword1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NewPassword2", CCEditBox*, m_pNewPassword2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "MobilephoneNumber", CCEditBox*, m_pMobilephoneNumber);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ChangeOfAccount", CCEditBox*, m_pChangeOfAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ChangeOfPassword1", CCEditBox*, m_pChangeOfPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ChangeOfPassword2", CCEditBox*, m_pChangedPassword1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ChangeOfPasswordAffirm", CCEditBox*, m_pChangedPassword2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuimage_login", CCMenuItemImage*, m_pItemLogin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuimage_register", CCMenuItemImage*, m_pItemRegister);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuimage_resetpw", CCMenuItemImage*, m_pItemResetPW);
    return false;
}

SEL_MenuHandler MB_LayerAccountMgr::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onExistAccountLogin", MB_LayerAccountMgr::onExistAccountLogin);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNewAccountRegist", MB_LayerAccountMgr::onNewAccountRegist);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChangePassword", MB_LayerAccountMgr::onChangePassword);
    return NULL;
}

SEL_CCControlHandler MB_LayerAccountMgr::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFilledAccountClick", MB_LayerAccountMgr::onFilledAccountClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerAccountMgr::onCommitClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBackClicked", MB_LayerAccountMgr::onGuestLoginClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChangeAffirmClicked", MB_LayerAccountMgr::onChangeAffirmClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturnBack", MB_LayerAccountMgr::onReturnBackClicked);
    return NULL;
}
