//
#include "MB_ClientSocket.h"
// #include "platform/CCThread.h"
#include "cocos2d.h"
#include <queue>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/socket.h>
#if CC_PLATFORM_IOS ==  CC_TARGET_PLATFORM
#include <sys/sysctl.h>
#include <net/if_dl.h>
#else
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include "JavaCppHelper.h"
#endif
#include <arpa/inet.h>
#include <net/if.h>
#include "MB_DefineProto.h"
#include "Game.h"
#include <unistd.h>

#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif

using namespace std;

NS_CC_EXT_BEGIN

static pthread_t        s_socketSendThread;
static pthread_t        s_socketRecvThread;
static pthread_mutex_t  s_socketRequestQueueMutex;
static pthread_mutex_t  s_socketSendMutex;
static pthread_mutex_t  s_socketResponseQueueMutex;
static sem_t *          s_pSocketSem = NULL;
static int              s_socketHandle;

#define SOCKET_SELECTOR(className) callfuncND_selector(className##::onMsgRecv)

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define SOCKETREQUEST_USE_NAMED_SEMAPHORE 1
#else
#define SOCKETREQUEST_USE_NAMED_SEMAPHORE 0
#endif

#if SOCKETREQUEST_USE_NAMED_SEMAPHORE
#endif
#define SOCKETREQUEST_SEMAPHORE "socket_Semap_moongamehorePKQ"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef int int32_t;
#endif

#define BUF_SIZE 1024

static bool s_bNeedQuit = false;
static bool s_isConnect = false;

static MB_ClientSocket *s_pMB_ClientSocket = NULL; // pointer to singleton


static CCArray* s_socketRequestQueue = NULL;
static CCArray* s_socketResponseQueue = NULL;

static std::string s_pServerIP;
static int s_iServerPort;
//static CCArray* s_socketResponseQueueWait = NULL;


static int Close()
{
    return (close(s_socketHandle));
}

static int getError()
{
    return (errno);
}

static void setConnect(bool isConnect)
{
    s_isConnect = isConnect;
    MB_LOG("socket connected : %d", (int)s_isConnect);
}

static bool getConnect()
{
    return s_isConnect;
}

static void handle_send_quit(int signo)
{
    MB_LOG("send thread quit");
    if (s_socketRequestQueue != NULL)
    {
        s_socketRequestQueue->removeAllObjects();
    }
    
    if (s_socketResponseQueue != NULL) {
        s_socketResponseQueue->removeAllObjects();
    }
    
    if (s_pSocketSem != NULL) {
#if SOCKETREQUEST_USE_NAMED_SEMAPHORE
        sem_unlink(SOCKETREQUEST_SEMAPHORE);
        sem_close(s_pSocketSem);
#else
        sem_destroy(s_pSocketSem);
#endif
        
        s_pSocketSem = NULL;
    }
    
    MB_LOG("thread send is killed.");
    //通知重連失敗
    if (MB_ClientSocket::isAlive())
    {
        MB_ClientSocket::getInstance()->getSocketHeartBit()->setConnecting(false);
    }
    
    //MB_LOG("thread handle send sig %d \n", signo);
    pthread_exit(NULL);
}

static void handle_recv_quit(int signo)
{
    shutdown(s_socketHandle, SHUT_RDWR);
    Close();
    setConnect(false);
    sem_post(s_pSocketSem);
    //MB_LOG("thread handle recv sig %d \n", signo);
    if(s_socketSendThread != 0 && pthread_kill(s_socketSendThread, 0)!= ESRCH)
    {
        MB_LOG("send thread killed");
        pthread_kill(s_socketSendThread, SIGABRT);
        s_socketSendThread = 0;
    }
    pthread_exit(NULL);
    //    setConnect(false);
}

static int Connect()
{
    struct sigaction siga;
    siga.sa_handler = SIG_IGN;
    sigaction( SIGPIPE, &siga, 0 );
    
    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;
    
    struct hostent* hp;
    
    const char* ip;
    unsigned short port;
    do {
        
        ip = MB_ClientSocket::getServerIP();
        port = MB_ClientSocket::getServerPort();
        if (strcmp("", ip) == 0) {
            MB_LOG("ip:%s",ip);
            sleep(1);
        }
        else
        {
            break;
        }
    } while (1);
    //////////////
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    int err;
    char seraddr[INET_ADDRSTRLEN];
    short serport;
    
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_CANONNAME;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_addr = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;
    
    char buff[1024];
    sprintf(buff, "%d", port);
    if ((err = getaddrinfo(ip, buff, &hint, &ailist)) != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(err));
        return -1;
    }
    bool isConnectOk = false;
    printf("getaddrinfo ok\n");
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        
        sinp = (struct sockaddr_in *)aip->ai_addr;
        if (inet_ntop(sinp->sin_family, &sinp->sin_addr, seraddr, INET_ADDRSTRLEN) != NULL)
        {
            CCLOG("server address is %s\n", seraddr);
        }
        serport = ntohs(sinp->sin_port);
        CCLOG("server port is %d\n", serport);
        if ((s_socketHandle = socket(aip->ai_family, SOCK_STREAM, 0)) < 0) {
            CCLOG("create socket failed: %s\n", strerror(errno));
            isConnectOk = false;
            continue;
        }
        CCLOG("create socket ok\n");
        if (connect(s_socketHandle, aip->ai_addr, aip->ai_addrlen) < 0) {
            
            CCLOG("can't connect to %s: %s\n", ip, strerror(errno));
            continue;
        }
        break;
    }
    
    //////////////
    /*
     hp = gethostbyname(ip);
     if(!hp){
     MB_LOG("gethostbyname failed ip:%s.",ip);
     
     struct in_addr ipAddr;
     memset(&ipAddr, 0, sizeof(in_addr));
     
     if (!inet_aton(ip, &ipAddr))
     {
     MB_LOG("無法轉換ip地址 %s.", ip);
     return -1;
     }
     
     if ((hp = gethostbyaddr((const char *)&ipAddr, sizeof(in_addr), AF_INET)) == NULL)
     {
     //            MB_LOG("no name associated with %s", ip);
     return -1;
     }
     
     }
     memset(&sa, 0, sizeof(sa));
     memcpy((char*)&sa.sin_addr, hp->h_addr, hp->h_length);
     sa.sin_family = hp->h_addrtype;
     sa.sin_port = htons(port);
     
     s_socketHandle = socket(sa.sin_family, SOCK_STREAM, 0);
     if(s_socketHandle < 0){
     MB_LOG( "socket創建失敗\n" );
     return -1;
     }
     
     //設置超時
     struct timeval timeo;
     socklen_t len = sizeof(timeo);
     timeo.tv_sec = 1;
     timeo.tv_usec = 0;
     if (setsockopt(s_socketHandle, SOL_SOCKET, SO_RCVTIMEO, &timeo, len) == -1)
     {
     //MB_LOG( "setsockopt failed. errcode:%d\n", getError());
     return 0;
     }
     
     if(::connect(s_socketHandle, (sockaddr*)&sa, sizeof(sa)) < 0)
     {
     MB_LOG( "無法鏈接到socket. errcode:%d\n", getError());
     ::close(s_socketHandle);
     return -1;
     }
     */
    MB_LOG("连接成功 ip: %s:%d ",ip,port);
    return 0;
}

static int Send(const char* buf, int len, int flags)
{
    pthread_mutex_lock(&s_socketSendMutex);
    int bytes;
    int count = 0;
    
    while ( count < len )
    {
        //        //测試协议輸出用
        //        std::string fullPathName = CCFileUtils::sharedFileUtils()->getWritablePath() + "log.txt";
        //        FILE* file = fopen(fullPathName.c_str(), "wb");
        //        fwrite(buf, 1, len, file);
        //        fclose(file);
        
        bytes = send(s_socketHandle, buf + count, len - count, flags);
        if ( bytes == -1 || bytes == 0 )
        {
            pthread_mutex_unlock(&s_socketSendMutex);
            //Close();
            return getError();
        }
        //MB_LOG("socket send succeed!");
        count += bytes;
    }
    
    pthread_mutex_unlock(&s_socketSendMutex);
    
    return 0;
}

static int Recv()
{
    //pthread_mutex_lock(&s_socketResponseQueueMutex);
    char recvBuf[BUF_SIZE] = "\0";
    vector<char> vbuf;
    uint16_t len,addlen,totalsize = 0;
    uint32_t oldSize;
    int size = recv(s_socketHandle, recvBuf, 2, 0);
    if (size > 1) {
        len = (recvBuf[0] << 8) + (0xFF & recvBuf[1]);
        memset(recvBuf, 0, BUF_SIZE * sizeof(char) );
        totalsize += size;
        //MB_LOG("socket recv succeed!\n");
    }
    else
    {
        //pthread_mutex_unlock(&s_socketResponseQueueMutex);
        return size;
    }
    
    //收不到len長度会出问题
    while (len > totalsize)
    {
        addlen = len - totalsize;
        if (addlen > BUF_SIZE) {
            size = recv(s_socketHandle, recvBuf, BUF_SIZE, 0);
        }
        else{
            size = recv(s_socketHandle, recvBuf, addlen, 0);
        }
        
        //异常处理
        if (size < 0)
        {
            //超時继续等待
            if (getError() == EAGAIN)
            {
                continue;
            }
            else
            {
                //扔掉这个包
                return size;
            }
        }
        
        totalsize += size;
        // resize to new length
        oldSize = (uint32_t)vbuf.size();
        vbuf.resize(oldSize + size);
        // copy directly into the vector's memory
        memcpy(&vbuf[oldSize], recvBuf, size);
        
        memset(recvBuf, 0, BUF_SIZE * sizeof(char) );
    }
    
    //pthread_mutex_unlock(&s_socketResponseQueueMutex);
    
    SocketResponse* response = NULL;
    SocketRequest*  request = NULL;
    MB_MsgBuffer* serbuf = new MB_MsgBuffer();
    serbuf->Write( &vbuf[0], len - 2);
    uint16_t protoNumber;
    //忽略長度字段
    serbuf->skipU16();
    //忽略压缩字段
    serbuf->skipU8();
    serbuf->readU16(&protoNumber);
    serbuf->Reset();
    delete serbuf;
#ifdef DEBUG
    MB_LOG("recv msg: %d",protoNumber);
#else
    MB_LOG("recv msg: %d",protoNumber^1024);
#endif
    pthread_mutex_lock(&s_socketResponseQueueMutex);
    
    //取當前時間
    //time_t sec;
    //time(&sec);
    //bool bSucceed = false;
    
    //    for (int _i = 0; _i < s_socketResponseQueueWait->count(); _i++)
    //    {
    //        response = dynamic_cast<SocketResponse*>(s_socketResponseQueueWait->objectAtIndex(_i));
    //        request = response->getSocketRequest();
    //
    //        if( protoNumber == request->getTag())
    //        {
    //            //去掉头的長度len-2
    //            response->setResponseData( &vbuf[0], len - 2);
    //            response->setSucceed(true);
    //            s_socketResponseQueue->addObject(response);
    //            s_socketResponseQueueWait->removeObjectAtIndex(_i);
    //            //bSucceed = true;
    //            //break;
    //        }
    //        else
    //        {
    //            //超出15秒销毁
    //            if (sec - response->getStartTime() > 15000) {
    //                s_socketResponseQueueWait->removeObjectAtIndex(_i);
    //                CC_SAFE_RELEASE_NULL(response);
    //            }
    //        }
    //    }
    
    //处理伺服器群發消息
    //if (!bSucceed)
    {
        CCObject* obj = NULL;
        CCArray* pCallbackArray = MB_ClientSocket::getInstance()->getCallbackArray();
        SocketCallback* sc = NULL;
        CCARRAY_FOREACH(pCallbackArray, obj)
        {
            sc = (SocketCallback*)obj;
            if (sc->getProto() == protoNumber) {
                request = new SocketRequest();
                request->setTag(protoNumber);
                request->setResponseCallback(sc->getOwner(), sc->getFunc());
                response = new SocketResponse(request);
                response->setResponseData( &vbuf[0], len - 2);
                response->setSucceed(true);
                s_socketResponseQueue->addObject(response);
                request->release();
            }
        }
    }
    
    pthread_mutex_unlock(&s_socketResponseQueueMutex);
    
    // resume dispatcher selector
    CCDirector::sharedDirector()->getScheduler()->resumeTarget(MB_ClientSocket::getInstance());
    
    return len;
}

static void* socketRecvThread(void *data)
{
    int size = 0;
    signal(SIGQUIT,handle_recv_quit);
    MB_LOG("开始接收socket");
    
    while (true) {
        
        if (s_bNeedQuit)
        {
            break;
        }
        
        if (!getConnect())
        {
            break;
        }
        
        size = Recv();
        
        if ( (size < 0 && getError() != EAGAIN) || size == 0)
        {
            //这里可能存在把刚連接上的断開的bug
            shutdown(s_socketHandle, SHUT_RDWR);
            Close();
            setConnect(false);
            break;
        }
    }
    
    sem_post(s_pSocketSem);
    MB_LOG("socket接受线程退出.");
    pthread_exit(NULL);
    
    return 0;
}

// Worker thread
static void* socketSendThread(void *data)
{
    //連接伺服器，參數传递后面補充
    signal(SIGABRT,handle_send_quit);
    MB_LOG("socket写入线程开始");
    
    int error = Connect();
    if(error)
    {
        MB_LOG("socket send thread start failed.");
    }
    else
    {
        //確认連接上了再建立接受線程
        
        setConnect(true);
        
        //        pthread_attr_t attr;
        //        sched_param param;
        //        int newprio=20;
        //        pthread_attr_init(&attr);
        //        pthread_attr_getschedparam(&attr, &param);
        //        param.sched_priority=newprio;
        //        pthread_attr_setschedparam(&attr, &param);
        //        pthread_create(&s_socketRecvThread, &attr, socketRecvThread, NULL);
        
        pthread_create(&s_socketRecvThread, NULL, socketRecvThread, NULL);
        pthread_detach(s_socketRecvThread);
        pthread_join(s_socketRecvThread, NULL);
        //bug,可能存在接受線程还沒有建立就已經收到消息了，sleep不行就加信號量
        sleep(1);
    }
    
    SocketRequest *request = NULL;
    
    while (!error)
    {
        // Wait for socket request tasks from main thread
        int semWaitRet = sem_wait(s_pSocketSem);
        if (semWaitRet < 0) {
            //MB_LOG("SocketRequest thread semaphore error: %s\n", strerror(errno));
            break;
        }
        
        if (s_bNeedQuit)
        {
            break;
        }
        
        if (!getConnect())
        {
            break;
        }
        
        // step 1: send socket request if the requestQueue isn't empty
        request = NULL;
        
        pthread_mutex_lock(&s_socketRequestQueueMutex); //Get request task from queue
        if (0 != s_socketRequestQueue->count())
        {
            request = dynamic_cast<SocketRequest*>(s_socketRequestQueue->objectAtIndex(0));
            s_socketRequestQueue->removeObjectAtIndex(0);
            // request's refcount = 1 here
        }
        pthread_mutex_unlock(&s_socketRequestQueueMutex);
        
        if (NULL == request)
        {
            continue;
        }
        else
        {
            Send((const char*)request->getRequestData()->GetData(), request->getRequestDataSize(), 0);
            
            //            pthread_mutex_lock(&s_socketResponseQueueMutex);
            //            SocketResponse* response = new SocketResponse(request);
            //            s_socketResponseQueueWait->addObject(response);
            //            pthread_mutex_unlock(&s_socketResponseQueueMutex);
            request->release();
        }
        
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    pthread_mutex_lock(&s_socketRequestQueueMutex);
    if (s_socketRequestQueue != NULL)
    {
        s_socketRequestQueue->removeAllObjects();
    }
    pthread_mutex_unlock(&s_socketRequestQueueMutex);
    
    pthread_mutex_lock(&s_socketResponseQueueMutex);
    if (s_socketResponseQueue != NULL) {
        s_socketResponseQueue->removeAllObjects();
    }
    pthread_mutex_unlock(&s_socketResponseQueueMutex);
    
    if (s_pSocketSem != NULL) {
#if SOCKETREQUEST_USE_NAMED_SEMAPHORE
        sem_unlink(SOCKETREQUEST_SEMAPHORE);
        sem_close(s_pSocketSem);
#else
        sem_destroy(s_pSocketSem);
#endif
        
        s_pSocketSem = NULL;
    }
    
    MB_LOG("socket写入线程退出");
    //通知重連失敗
    if (MB_ClientSocket::isAlive())
    {
        MB_ClientSocket::getInstance()->getSocketHeartBit()->setConnecting(false);
    }
    pthread_exit(NULL);
    
    return 0;
}


// MB_ClientSocket implementation
MB_ClientSocket* MB_ClientSocket::getInstance()
{
    if (s_pMB_ClientSocket == NULL) {
        s_pMB_ClientSocket = new MB_ClientSocket();
    }
    
    return s_pMB_ClientSocket;
}

void MB_ClientSocket::destroyInstance()
{
    //MB_LOG("destroy socketclient");
    if(s_pMB_ClientSocket){
        
        CC_ASSERT(s_pMB_ClientSocket);
        
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MB_ClientSocket::dispatchResponseCallbacks), s_pMB_ClientSocket);
        s_pMB_ClientSocket->release();
        s_pMB_ClientSocket = NULL;
        if(s_socketSendThread != 0 && pthread_kill(s_socketSendThread, 0)!= ESRCH)
        {
            MB_LOG("send thread killed");
            pthread_kill(s_socketSendThread, SIGABRT);
            s_socketSendThread = 0;
        }
        if(s_socketRecvThread != 0 && pthread_kill(s_socketRecvThread, 0)!= ESRCH)
        {
            pthread_kill(s_socketRecvThread, SIGQUIT);
            s_socketRecvThread = 0;
        }
    }
}

bool MB_ClientSocket::isAlive()
{
    if (s_pMB_ClientSocket == NULL) {
        return false;
    }
    return true;
}

MB_ClientSocket::MB_ClientSocket()
:m_socketHeartBit(NULL)
,m_nCanAutoConnect(0)
{
    s_pServerIP = "";
    s_iServerPort = 0;
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
                                                                   schedule_selector(MB_ClientSocket::dispatchResponseCallbacks), this, 0, false);
    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    //lazyInitThreadSemphore();
    
    if (m_socketHeartBit == NULL)
    {
        m_socketHeartBit = new SocketHeartBit();
    }
    
    m_pCallbackArray = CCArray::create();
    m_pCallbackArray->retain();
    
    s_socketRequestQueue = CCArray::create();
    s_socketRequestQueue->retain();
    
    s_socketResponseQueue = CCArray::create();
    s_socketResponseQueue->retain();
    
    //        s_socketResponseQueueWait = new CCArray();
    //        s_socketResponseQueueWait->init();
    
    pthread_mutex_init(&s_socketRequestQueueMutex, NULL);
    pthread_mutex_init(&s_socketSendMutex, NULL);
    pthread_mutex_init(&s_socketResponseQueueMutex, NULL);
    
}

MB_ClientSocket::~MB_ClientSocket()
{
    s_bNeedQuit = true;
    setConnect(false);
    
    if (s_pSocketSem != NULL) {
        sem_post(s_pSocketSem);
    }
    
    pthread_mutex_destroy(&s_socketRequestQueueMutex);
    pthread_mutex_destroy(&s_socketSendMutex);
    pthread_mutex_destroy(&s_socketResponseQueueMutex);
    
    CC_SAFE_RELEASE_NULL(m_pCallbackArray);
    CC_SAFE_RELEASE_NULL(s_socketRequestQueue);
    CC_SAFE_RELEASE_NULL(s_socketResponseQueue);
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(m_socketHeartBit);
    CC_SAFE_RELEASE_NULL(m_socketHeartBit);
    s_pMB_ClientSocket = NULL;
    
}

//Lazy create semaphore & mutex & thread
bool MB_ClientSocket::lazyInitThreadSemphore()
{
    if (s_pSocketSem != NULL) {
        return true;
    }
    else
    {
#if SOCKETREQUEST_USE_NAMED_SEMAPHORE
        s_pSocketSem = sem_open(SOCKETREQUEST_SEMAPHORE, O_CREAT, 0644, 0);
        if (s_pSocketSem == SEM_FAILED) {
            MB_LOG("Open SocketRequest Semaphore failed");
            s_pSocketSem = NULL;
            return false;
        }
#else
        s_pSocketSem = new sem_t();
        int semRet = sem_init(s_pSocketSem, 0, 0);
        if (semRet < 0) {
            MB_LOG("Init SocketRequest Semaphore failed");
            return false;
        }
        
#endif
        
        //        pthread_attr_t attr;
        //        sched_param param;
        //        int newprio=20;
        //        pthread_attr_init(&attr);
        //        pthread_attr_getschedparam(&attr, &param);
        //        param.sched_priority=newprio;
        //        pthread_attr_setschedparam(&attr, &param);
        //        pthread_create(&s_socketSendThread, &attr, socketSendThread, NULL);
        
        pthread_create(&s_socketSendThread, NULL, socketSendThread, NULL);
        pthread_detach(s_socketSendThread);
        pthread_join(s_socketSendThread, NULL);
        s_bNeedQuit = false;
    }
    
    return true;
}

uint32_t MB_ClientSocket::getServerTime()
{
    return m_socketHeartBit?m_socketHeartBit->getServerTime():0;
}

//Add a get task to queue
void MB_ClientSocket::Send(SocketRequest* request)
{
    if (false == lazyInitThreadSemphore())
    {
        return;
    }
    
    if (!request)
    {
        return;
    }
    
    request->retain();
    
    pthread_mutex_lock(&s_socketRequestQueueMutex);
    s_socketRequestQueue->addObject(request);
    pthread_mutex_unlock(&s_socketRequestQueueMutex);
    
    // Notify thread start to work
    sem_post(s_pSocketSem);
}

// Poll and notify main thread if responses exists in queue
void MB_ClientSocket::dispatchResponseCallbacks(float delta)
{
    // MB_LOG("MB_ClientSocket::dispatchResponseCallbacks is running");
    
    SocketResponse* response = NULL;
    
    pthread_mutex_lock(&s_socketResponseQueueMutex);
    if (s_socketResponseQueue->count())
    {
        response = dynamic_cast<SocketResponse*>(s_socketResponseQueue->objectAtIndex(0));
        s_socketResponseQueue->removeObjectAtIndex(0);
    }
    pthread_mutex_unlock(&s_socketResponseQueueMutex);
    
    //MB_LOG("Server Ack: %s\n",response->getResponseData());
    
    if (response)
    {
        SocketRequest *request = response->getSocketRequest();
        CCObject *pTarget = request->getTarget();
        SEL_CallFuncND pSelector = request->getSelector();
        
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((CCNode *)this, response);
        }
        
        response->release();
    }
    
    if (0 == s_socketResponseQueue->count())
    {
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    }
    
}

void MB_ClientSocket::setServerIP(const char *serverIP)
{
    s_pServerIP = serverIP;
    //MB_LOG("MB_ClientSocket::setServerIP:%s",s_pServerIP.c_str());
}

void MB_ClientSocket::setServerPort(int port)
{
    s_iServerPort = port;
    //MB_LOG("MB_ClientSocket::setServerPort:%d",s_iServerPort);
}

const char* MB_ClientSocket::getServerIP()
{
    return s_pServerIP.c_str();
}

int MB_ClientSocket::getServerPort()
{
    return s_iServerPort;
}

void MB_ClientSocket::registerResponseObject(int proto, SEL_CallFuncND callBack, CCObject* pCCObject)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_pCallbackArray, obj)
    {
        SocketCallback* sc = (SocketCallback*)obj;
        if (sc->getProto() == proto && sc->getOwner() == pCCObject) {
            MB_LOG("already registed proto:%d", proto);
            return;
        }
    }
    
    SocketCallback* responseObject = new SocketCallback(proto, pCCObject, callBack);
    m_pCallbackArray->addObject(responseObject);
    responseObject->release();
}

void MB_ClientSocket::unregisterResponseObject(int proto, CCObject* pCCObject)
{
    CCObject* obj = NULL;
    
    CCARRAY_FOREACH(m_pCallbackArray, obj)
    {
        SocketCallback* sc = (SocketCallback*)obj;
        if (sc->getProto() == proto && sc->getOwner() == pCCObject) {
            
            //清理socket接收隊列
            pthread_mutex_lock(&s_socketResponseQueueMutex);
            CCARRAY_FOREACH(s_socketResponseQueue, obj)
            {
                SocketResponse* response = (SocketResponse*)obj;
                SocketRequest* request = response->getSocketRequest();
                if (request->getTarget() == sc->getOwner() && sc->getProto() == request->getTag()) {
                    //MB_LOG("s_socketResponseQueue unregist proto:", request->getTag());
                    s_socketResponseQueue->removeObject(obj);
                }
            }
            pthread_mutex_unlock(&s_socketResponseQueueMutex);
            
            m_pCallbackArray->removeObject(sc);
            return;
        }
    }
    //MB_LOG("The proto (%d) doesn't exist, unregist fail.", proto);
}

void MB_ClientSocket::clearResponseObjects()
{
    m_pCallbackArray->removeAllObjects();
}

void MB_ClientSocket::canAutoConnect(int index)
{
    m_nCanAutoConnect = index;
}

int MB_ClientSocket::getCanAutoConnect()
{
    return m_nCanAutoConnect;
}

// Return the local MAC addy
// Courtesy of FreeBSD hackers email list
// Accidentally munged during previous update. Fixed thanks to mlamb.
#if CC_PLATFORM_IOS ==  CC_TARGET_PLATFORM
char* MB_ClientSocket::getMacAddress()
{
    int                    mib[6];
    size_t                len;
    char                *buf;
    unsigned char        *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl    *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        printf("Error: if_nametoindex error/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1/n");
        return NULL;
    }
    
    if ((buf = (char*)malloc(len)) == NULL) {
        printf("Could not allocate memory. error!/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2");
        return NULL;
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    // NSString *outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    char* outstring = new char[32];
    sprintf(outstring, "%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
    free(buf);
    
    return outstring;
}
#else
char* MB_ClientSocket::getMacAddress()
{
    char *address = JavaCppHelper::getInstance()->getMacAddress();
    return address;
}
#endif
//***************************************************************************************
//心跳检测類

SocketHeartBit::SocketHeartBit()
:m_uiServerTime(0)
,m_fHeartBitTime(HEARTBIT_TIME)
,m_nHeartBitCount(0)
,m_timepp(0.0f)
,m_bIsConnecting(false)
,m_bIsShowReconnect(false)
,mIsSendAutoconnect(false)
{
    m_bIsKick = false;
    //初始一个暂停的心跳
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector( schedule_selector(SocketHeartBit::Tick), this, 0, false);
}

SocketHeartBit::~SocketHeartBit()
{
    SOCKET_MSG_UNREGIST(SC_ACCOUNT_HEART);
    SOCKET_MSG_UNREGIST(SC_ACCOUNT_KICK);
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
}

uint32_t SocketHeartBit::getServerTime()
{
    return m_uiServerTime;
}

void SocketHeartBit::SetSendAutoconnect(bool a ) {
    mIsSendAutoconnect  = a;
}

bool SocketHeartBit::IsSendAutoconnect() {
    return mIsSendAutoconnect ;
}

void SocketHeartBit::RetSendAutoconnect() {
    mIsSendAutoconnect  = false;
}

void SocketHeartBit::Tick(float delta)
{
    m_fHeartBitTime += delta;
    m_timepp        += delta;
    if(m_timepp>1.0f)
    {
        uint32_t tempCount = (uint32_t)m_timepp;
        m_uiServerTime += tempCount;
        m_timepp -= tempCount;
    }
    
    if ((m_fHeartBitTime > HEARTBIT_TIME ) && getConnect())
    {
        m_fHeartBitTime = 0.f;
        //發送心跳包
        sendaccount_heart();
    }
    // 是否需要自動鏈接 && 是否已經開始自動連接 && 是否能够自動連接 && 是否已断開
    if (!m_bIsConnecting && !m_bIsShowReconnect && MB_ClientSocket::getInstance()->getCanAutoConnect() > 0 && !s_isConnect) {
        MB_Message::sharedMB_Message()->removeALLMessage();
        TutorialForcedTrigpetComplete
        MB_Message::sharedMB_Message()->showMessage("","服务器已断开", "确定", this, menu_selector(SocketHeartBit::onReconnectClicked));
        
        m_bIsShowReconnect = true;
    }
}

void SocketHeartBit::onReconnectClicked(CCObject* pSender)
{
    //MB_Message::sharedMB_Message()->showMessage("",30);
    //sendautoconnect();
#ifdef PLATFORM_YJ
	MB_YJMgr::getInstance()->quitGame();
#endif

#ifdef YJ_IOS
	MB_YJMgr_IOS::getInstance()->quitGame();
#endif
}

bool SocketHeartBit::sendaccount_heart()
{
    //重複發一次,让send線程退出来
    if (m_nHeartBitCount > HEARTBIT_COUNT)
    {
        setConnect(false);
    }
    else
    {
        m_nHeartBitCount++;
    }
    
    SOCKET_MSG_REGIST(SC_ACCOUNT_HEART, SocketHeartBit);
    if(m_bIsKick == false){
        
        SOCKET_MSG_REGIST(SC_ACCOUNT_KICK, SocketHeartBit);
        m_bIsKick  = true;
    }
    
    SOCKET_REQUEST_START(CS_ACCOUNT_HEART);
    SOCKET_REQUEST_END(SC_ACCOUNT_HEART, SocketHeartBit::onMsgRecv);
    
    return true;
}

bool SocketHeartBit::sendautoconnect()
{
    m_bIsShowReconnect = false;
    m_bIsConnecting = true;
    MB_ClientSocket::getInstance()->clearResponseObjects();
    return sendaccount_heart();
}

void SocketHeartBit::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    if (Msg == SC_ACCOUNT_HEART)
    {
        SOCKET_MSG_UNREGIST(SC_ACCOUNT_HEART);
        
        m_nHeartBitCount = 0;
        uint32_t Data;
        recvPacket->readU32(&Data);
        if (Data > 0)
        {
            m_timepp = 0.0f;
            m_uiServerTime = Data;
        }
        else
        {
            MB_LOG("server time < 0: %d\n",Data);
        }
        
        if (m_bIsConnecting)
        {
            m_bIsConnecting = false;
            //            MB_Message::sharedMB_Message()->removeALLMessage();
            
            if (MB_ClientSocket::getInstance()->getCanAutoConnect() > 1)
            {
                CCDirector::sharedDirector()->popToRootScene();
                CCScene * scene =  MB_SceneReconnect::scene();
                CCLayer* layer = MB_SceneLoading::create();
                scene->addChild(layer);
                CCDirector::sharedDirector()->replaceScene(scene);
            }
            else
            {
                CCScene* pScene = MB_SceneLoginBackground::scene();
                CCDirector::sharedDirector()->popToRootScene();
                CCDirector::sharedDirector()->replaceScene(pScene);
                PlayBackGround(kmBackGround_Login);
            }
            
        }
    }
    else if(Msg == SC_ACCOUNT_KICK){
        
        uint8_t data8;
        recvPacket->readU8(&data8);
        if(data8 == 1){
            
            MB_Message::sharedMB_Message()->showMessage("帐号异地登录强制下线");
            
        }else if(data8 == 2){
            
            MB_Message::sharedMB_Message()->showMessage("帐号被封禁强制下线");
            
        }else {
            
            MB_Message::sharedMB_Message()->showMessage("帐号强制下线，未知原因");
        }
        
        
    }
    else
    {
        MB_LOG("unkown proto id: %d\n", Msg);
    }
}

NS_CC_EXT_END


