
#ifndef __ProjectMB__MB_SceneLoading__
#define __ProjectMB__MB_SceneLoading__
#include "Game.h"
class MB_SceneLoading : public CCLayer{

private:
    
    int m_nCount;
    bool m_nGoUpdate;
public:

    MB_SceneLoading();
    ~MB_SceneLoading();
    
    virtual bool init();
    static CCScene *scene();
    static MB_SceneLoading *create();
    void initData();
    void clearData();
    void initConnect();
    void tick(float dt);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    //登陆协议
    void sendaccount_login();
    void sendversion();
    void recvaccount_login(MB_MsgBuffer* recvPacket);
    void goUpdate(CCObject *);
    
};
#endif /* defined(__ProjectMB__MB_SceneLoading__) */
