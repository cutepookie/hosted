//
//  MB_LayerAccountMgr.h
//  ProjectSDS
//
//  Created by crimoon00007 on 14-3-10.
//
//

#ifndef __ProjectSDS__MB_LayerAccountMgr__
#define __ProjectSDS__MB_LayerAccountMgr__

#include "Game.h"
class MB_LayerAccountMgr : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_LayerAccountMgr();
    virtual ~MB_LayerAccountMgr();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    CREATE_FUNC(MB_LayerAccountMgr);
    void openAccountLoginNode(){onExistAccountLogin(NULL);}
protected:
    void onExistAccountLogin(CCObject*);
    void onNewAccountRegist(CCObject*);
    void onChangePassword(CCObject*);

    void onFilledAccountClicked(CCObject*);
    void onCommitClicked(CCObject*);
    void onGuestLoginClicked(CCObject*);
    void onChangeAffirmClicked(CCObject*);
    void onReturnBackClicked(CCObject*);

    bool checkRegistAccount(std::string& acc,std::string& pwd1,std::string& pwd2,std::string& phone);

    void sendhttp_regist_account(std::string& acc,std::string& pwd,std::string& phone);
    void sendhttp_regist_account_guest(std::string& acc,std::string& pwd,std::string& phone);
    void recvhttp_regist_account(CCNode* pNode,CCHttpResponse* response);
private:
    CCNode*         m_pExistAccountLogin;
    CCNode*         m_pAccountRegist;
    CCNode*         m_pChangePassword;
    CCEditBox*      m_pFillExistAccount;
    CCEditBox*      m_pFillExistPassword;

    CCEditBox*      m_pNewAccount;
    CCEditBox*      m_pNewPassword1;
    CCEditBox*      m_pNewPassword2;
    CCEditBox*      m_pMobilephoneNumber;

    CCEditBox*      m_pChangeOfAccount;
    CCEditBox*      m_pChangeOfPassword;
    CCEditBox*      m_pChangedPassword1;
    CCEditBox*      m_pChangedPassword2;
    
    CCMenuItemImage* m_pItemLogin;
    CCMenuItemImage* m_pItemRegister;
    CCMenuItemImage* m_pItemResetPW;
};

#endif /* defined(__ProjectSDS__MB_LayerAccountMgr__) */
