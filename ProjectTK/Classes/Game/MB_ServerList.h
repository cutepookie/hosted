

#ifndef __ProjectMB__MB_ServerList__
#define __ProjectMB__MB_ServerList__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

typedef struct {
    std::string name;
    int         serverID;
    std::string serverIP;
    int         serverPort;
    int         serverStatus;
}ServerList;

class MB_ServerList: public CCObject
{
private:
    
    MB_ServerList();
    ServerList*     m_pServerList;
    unsigned int*   m_pLatestServerIDs;
    std::string     m_strKey;
    std::string     m_pSelectIP;
    int             m_iSelectPort;
    int             m_iServerListCount;
    int             m_iLatestServerIDsCount;
    std::string     m_sAccName;
    std::string     m_sPassword;
    time_t          m_tTimeStamp;
    std::string     m_sAccid;
    CC_SYNTHESIZE(bool, m_bCreatedRole, isCreateRole);
    CC_SYNTHESIZE(bool, m_bSelectParnter, IsSelectParnter);
    std::string     m_pInviteCode;
    

    CC_SYNTHESIZE(unsigned int, m_selectServerId, SelectServerId);

public:
    
    void initList(CCHttpResponse* response);
    bool initList(Json::Value &reuslt);
    ~MB_ServerList();
    static MB_ServerList* getInstance();
    static void destroyInstance();
    
    int parseServerList(std::string strServerList);
    int parseServerList2(std::string &strServerList);
    int parseLatestServerIDs(std::string strLatestServerIDs);
    int parseLatestServerIDs2(const char *strLatestServerIDs);
    ServerList* getServerList()                 { return m_pServerList;}
    std::string getServerKey()                  { return m_strKey;}
    void setServerKey(const std::string& key)   { m_strKey = key;}
    int         getServerListCount()            { return m_iServerListCount;}
    int         getLatestServerIDsCount()       { return m_iLatestServerIDsCount;}
    const char* getSelectIP()                   { return m_pSelectIP.c_str();}
    int         getSelectPort()                 { return m_iSelectPort;}
    void        setAccName(const char* accName) { m_sAccName = accName;}
    std::string getAccName()                    { return m_sAccName;}
    void        setAccid(const char* accid) { m_sAccid = accid;}
    std::string getAccid()                    { return m_sAccid;}
    void        setPassword(const char* pwd)    { m_sPassword = pwd;}
    std::string getPassword()                   { return m_sPassword;}
    void        setTimeStamp(time_t time)       { m_tTimeStamp = time;}
    time_t      getTimeStamp()                  { return m_tTimeStamp;}
    CC_SYNTHESIZE(bool, m_bIsGuest, IsGuest);
    uint32_t    getLatestServerIDByIndex(int i);
    ServerList* getServerListByIndex(int index);
    void setSelectInfo();
    ServerList* getServerListByID(int serverID);
    int getNowServerID();
    const char * getNowServerName();
    //服务器id
    static uint16_t m_nSelectServerid;

    void  setInviteCode(const char *inviteCode);
    const char * getInviteCode();
    CC_SYNTHESIZE(uint8_t, m_nIsShowCode, IsShowCode);

    void addRecentlyServerId(unsigned int sid);
    bool saveRecentlyServerList();
    bool loadRecentlyServerList();
    
};

#endif /* defined(__ProjectMB__MB_ServerList__) */
