
#ifndef __ProjectTK__MB_YJMgr__
#define __ProjectTK__MB_YJMgr__

#include "Game.h"
class MB_YJMgr_IOS :public CCObject{
    
private:
    

    
    static MB_YJMgr_IOS *m_pShareUCManager;
    CCObject *m_pDelegate;
    char sid[50];
    
    //public:function< void () > mCallback;
    
    public :
    
    
    MB_YJMgr_IOS();
    ~MB_YJMgr_IOS();
    static MB_YJMgr_IOS * getInstance();
    static void distroy();
    bool IsCheckSetRoleData;
    void registDelegate(CCObject *delegate);
    void unregistDelegate(CCObject *detegate);
    void goLogin();
    int getCurrentLoginState();
    void goLogout();
    void goRegist();
    void setPay(const char * payid);
    bool isAutoLogin();
    void goBuylist();
    void checkSuccess(const char *receipt);
    void onBuySuccess(const char *receipt,int payid,const char *deviceid);
    void onGuestToNormal();
    void removeLoading();
    void openUC();
    void openBBS();
    bool hasLogin();
    void logout();
    void setIsShowFloatButton(bool isshow);
    void setIsShowFloatButton(CCPoint &pos);
    void creatRole();
    void enterGame();
    void roleLevelUp();
    void login(const char * str_1, const char* str_2, const char *str_3, const char *str_4);
    
    void setRoleData();
    
    
    
private:
    std::string urlencode(std::string str_source) ;
    
};

#endif /* defined(__ProjectTK__MB_YJMgr__) */
