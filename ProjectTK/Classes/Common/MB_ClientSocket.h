
#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

#include "SocketRequest.h"
#include "SocketResponse.h"
#ifdef WIN32  
#include <winsock2.h>  
#else  
#include <netdb.h>
#endif  
#include <errno.h>

NS_CC_EXT_BEGIN


#define HEARTBIT_TIME 10.0f
#define HEARTBIT_COUNT 29

//used for heart bit check
class SocketHeartBit: public CCObject
{
private:
    uint32_t m_uiServerTime;
    float m_fHeartBitTime;
    CC_SYNTHESIZE(int,m_nHeartBitCount, HeartBitCount);
    float    m_timepp;
    bool m_bIsConnecting;
    bool m_bIsShowReconnect;
    bool m_bIsKick;
    bool mIsSendAutoconnect;
public:
    SocketHeartBit();
    ~SocketHeartBit();
    
    uint32_t getServerTime(void);
    void     Tick(float delta);
    bool     sendaccount_heart();
    bool     sendautoconnect();
    void     onReconnectClicked(CCObject* pSender);
    void     setConnecting(bool bConnectiong) { m_bIsConnecting = bConnectiong;}
    void     setShowReconnect(bool bShow) { m_bIsShowReconnect = bShow;}
    void     onMsgRecv(CCNode* node, SocketResponse* response);
    
    bool IsSendAutoconnect() ;
    
    void RetSendAutoconnect() ;
    
    void SetSendAutoconnect(bool a ) ;
    
};
//end


class SocketCallback: public CCObject
{
    
public:
    
    SocketCallback(uint16_t proto, CCObject* pOwner, SEL_CallFuncND func)
    {
        m_uProto = proto;
        m_pOwner = pOwner;
        m_cbFunc = func;
    }
    
    CC_SYNTHESIZE(uint16_t, m_uProto, Proto);
    CC_SYNTHESIZE(CCObject*, m_pOwner, Owner);
    CC_SYNTHESIZE(SEL_CallFuncND, m_cbFunc, Func);
};

class MB_ClientSocket : public CCObject
{
public:
    /** Return the shared instance **/
    static MB_ClientSocket *getInstance();
    
    /** Relase the shared instance **/
    static void destroyInstance();
    
    static bool isAlive();
        
    /**
     * Add a get request to task queue
     * @return NULL
     */
    void Send(SocketRequest* request);
    
    uint32_t getServerTime(void);
    static char* getMacAddress();
    
    //設置ip & port
    static void setServerIP(const char* serverIP);
    static void setServerPort(int port);
    static const char* getServerIP();
    static int getServerPort();
    
    //注册無請求的伺服器消息
    void registerResponseObject(int proto, SEL_CallFuncND callBack, CCObject* pCCObject);
    void unregisterResponseObject(int proto, CCObject* pCCObject);
    void clearResponseObjects();
    CCArray* getCallbackArray() { return m_pCallbackArray;}
    
    static void setAutoConnection(bool bAuto);
    static bool getAutoConnection();
    void canAutoConnect(int index);
    int getCanAutoConnect();
    SocketHeartBit* getSocketHeartBit() { return m_socketHeartBit;}    
private:
    MB_ClientSocket();
    virtual ~MB_ClientSocket();
    bool init(void);
    
    /**
     * Init pthread mutex, semaphore, and create new thread for socket requests
     * @return bool
     */
    bool lazyInitThreadSemphore();
    /** Poll function called from main thread to dispatch callbacks when socket requests finished **/
    void dispatchResponseCallbacks(float delta);
    
private:
    int _timeoutForConnect;
    int _timeoutForRead;
    SocketHeartBit* m_socketHeartBit;
    CCArray* m_pCallbackArray;
    int m_nCanAutoConnect;
    
    // std::string reqId;
};

// end of Network group
/// @}
//CCLOG("protoprotoprotoprotoprotoprotoprotoprotoprotoprotoprotoprotoprotoprotoproto===========%d",proto);\

#define SOCKET_REQUEST_START(proto) \
SocketRequest* request = new SocketRequest(); \
MB_MsgBuffer* packet = request->getRequestData(); \
packet->WriteBegin(); \
packet->writeU8(0); \
packet->writeU16(proto)

#define SOCKET_REQUEST_END(proto,callback) \
packet->WriteEnd(); \
request->setTag(proto); \
MB_ClientSocket::getInstance()->Send(request); \
request->release()

#define SOCKET_MSG_REGIST(proto, class) \
MB_ClientSocket::getInstance()->registerResponseObject(proto, callfuncND_selector(class::onMsgRecv), this)

#define SOCKET_MSG_UNREGIST(proto) \
if (MB_ClientSocket::isAlive()) { MB_ClientSocket::getInstance()->unregisterResponseObject(proto, this); }

NS_CC_EXT_END

#endif //__SOCKET_CLIENT_H__
