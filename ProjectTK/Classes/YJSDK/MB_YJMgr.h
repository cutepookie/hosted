
#ifndef __ProjectTK__MB_YJMgr__
#define __ProjectTK__MB_YJMgr__
#define UCCPID 38609
#define UCGAMEID 541807
#define UCSERVERID 3174
#include "Game.h"
class MB_YJMgr :public CCObject{
    
private:
    
    static MB_YJMgr *m_pShareUCManager;
    CCObject *m_pDelegate;
    char sid[50];
    
    public :
    
    MB_YJMgr();
    ~MB_YJMgr();
    static MB_YJMgr* getInstance();
    static void distroy();
    void goLogin();
    int getCurrentLoginState();
	void openurl();
    void goLogout();
    void goRegist();
    virtual void goLogin(const char *sid);
	virtual void login(char* appid, char* channelid, char* userid, char* token);
    void setPay(const char * payid);
    bool isAutoLogin();
    void goBuylist();
    void registDelegate(CCObject *delegate);
    void unregistDelegate(CCObject *detegate);
    void checkSuccess(const char *receipt);
    void onBuySuccess(const char *receipt,int payid,const char *deviceid);
    virtual  void onBuyFail();
    virtual void onBuyCancle();
    void onGuestToNormal();
    void removeLoading();
    void openUC();
    void openBBS();
    void openFAQ();
    bool hasLogin();
    void logout();
    void setIsShowFloatButton(bool isshow);
    void setIsShowFloatButton(CCPoint &pos);
    virtual void EnterBackGroud();
    virtual void EnterFront();   
    void creatRole();
    void enterGame();
    void roleLevelUp();
	void quitGame();
};

#endif /* defined(__ProjectTK__MB_YJMgr__) */
