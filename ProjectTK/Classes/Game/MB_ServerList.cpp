
#include "Game.h"
#include "MB_ServerList.h"


static MB_ServerList* s_pServerList = NULL;

MB_ServerList::MB_ServerList(){

    m_pLatestServerIDs = new unsigned int[2];
    m_pServerList = NULL;
    m_bIsGuest = false;

    m_pInviteCode = "";
    m_nIsShowCode = 0;

    m_selectServerId = -1;
    m_bCreatedRole = false;
    m_bSelectParnter = false;
}
void MB_ServerList::initList(CCHttpResponse* response)
{
    CC_SAFE_DELETE_ARRAY(m_pLatestServerIDs);
    CC_SAFE_DELETE_ARRAY(m_pServerList);
    
    std::string responseData;
    responseData.assign(&(response->getResponseData()->front()), response->getResponseData()->size());
    
    //解析最近登陆id
    int firstPos = 0;
    firstPos = responseData.find('&',firstPos);
    int lastPos = responseData.find('&', firstPos+1);
    std::string strLatestID = responseData.substr(firstPos+1, lastPos-firstPos - 1);
    if (/*NSGameHelper::getSrcType()>NSGameHelper::ACCOUNT_TYPE_NORMAL*/0)
    {
        if (parseLatestServerIDs2(strLatestID.c_str()) != 0)
        {
            //MB_LOG("id 数据错误");
        }
    }
    else
    {
        if (!loadRecentlyServerList())
        {
            //MB_LOG("id 数据错误");
        }
    }

    
    //解析服务器列表
    firstPos = lastPos+1;
    lastPos = responseData.find('&', firstPos+1);
    std::string strServerList = responseData.substr(firstPos, lastPos - firstPos);
    if (parseServerList(strServerList) != 0)
    {
        //MB_LOG("列表 数据错误");
    }
    
    firstPos = lastPos+1;
    lastPos = responseData.size();
    m_strKey = responseData.substr(firstPos, lastPos - firstPos);
    
   // setSelectInfo();

}
bool MB_ServerList::initList(Json::Value &reuslt){
    
    CC_SAFE_DELETE_ARRAY(m_pLatestServerIDs);
    CC_SAFE_DELETE_ARRAY(m_pServerList);
    m_pLatestServerIDs = new unsigned int[2];
    
    std::string strLatestID = reuslt["login_history"].asString();
    CCLog("server %s",strLatestID.c_str());
    
    if (/*NSGameHelper::getSrcType()>NSGameHelper::ACCOUNT_TYPE_NORMAL*/0)
    {
        if (parseLatestServerIDs2(strLatestID.c_str()) != 0)
        {
            //MB_LOG("id 数据错误");
        }
    }
    else
    {
        if (!loadRecentlyServerList())
        {
            //MB_LOG("id 数据错误");
        }
    }
    

    
    std::string sever_list = reuslt["server_list"].asString();
    if ( parseServerList2(sever_list) != 0)
    {
        //MB_LOG("id 列表数据错误");
        return false;
    }
    
    m_strKey = reuslt["login_ticket"].asString();
    setSelectInfo();
    return true;
}

bool MB_ServerList::saveRecentlyServerList()
{
//    if (NSGameHelper::getSrcType() > NSGameHelper::ACCOUNT_TYPE_NORMAL)
//    {
//        return true;
//    }
    std::string file = CCFileUtils::sharedFileUtils()->getWritablePath() + "serverlist";
    FILE* pFile = fopen(file.c_str(), "wb");
    if (pFile)
    {
        fwrite(&m_iLatestServerIDsCount, sizeof(int), 1, pFile);
        for (int i=0; i<m_iLatestServerIDsCount; ++i)
        {
            fwrite(&m_pLatestServerIDs[i], sizeof(unsigned int), 1, pFile);
        }
        fclose(pFile);
        return true;
    }
    else
    {
        CCLog("read recently server list failed");
    }
    return false;
}

bool MB_ServerList::loadRecentlyServerList()
{
//    if (NSGameHelper::getSrcType() > NSGameHelper::ACCOUNT_TYPE_NORMAL)
//    {
//        return true;
//    }
    std::string file = CCFileUtils::sharedFileUtils()->getWritablePath() + "serverlist";
    FILE* pFile = fopen(file.c_str(), "rb");
    if (pFile)
    {
        int count = 0;
        fread(&count, sizeof(int), 1, pFile);
        m_iLatestServerIDsCount = count;
        if (count<3)
        {
            unsigned int id = 0;
            for (int i=0; i<count; ++i)
            {
                fread(&id, sizeof(unsigned int), 1, pFile);
                m_pLatestServerIDs[i] = id;
            }
            return true;
        }
        else
        {
            m_pLatestServerIDs[0] = -1;
            m_iLatestServerIDsCount = 0;
            return false;
        }
    }
    else
    {
        m_pLatestServerIDs[0] = -1;
        m_iLatestServerIDsCount = 0;
        return false;
    }
    m_iLatestServerIDsCount = 0;
    return false;
}

int MB_ServerList::parseLatestServerIDs2(const char *strLatestServerIDs){

    int num = 0;
    int length = strlen(strLatestServerIDs);
    if(length != 0){
    
        num = 1;
    }
    for (int i = 0 ; strLatestServerIDs[i] != '\0'; i++) {
        
        if(strLatestServerIDs[i] == ','){
        
            num++;
        }
    }
    if (num == 0) {
        num = 1;
        CC_SAFE_DELETE_ARRAY(m_pLatestServerIDs);
        m_pLatestServerIDs = new unsigned int[num];
        m_pLatestServerIDs[0] = -1;
        m_iLatestServerIDsCount = 0;
        return 0;
    }    
    m_iLatestServerIDsCount = num;
    CC_SAFE_DELETE_ARRAY(m_pLatestServerIDs);
    m_pLatestServerIDs = new unsigned int[num];
    memset(m_pLatestServerIDs, 0, num * sizeof(unsigned int));
    char strid[10];
    int startpos = 0;
    for (int i = 0 ; i < num ; i++) {
        
        int j = 0;
        for ( ;strLatestServerIDs[j+startpos] != ',' && strLatestServerIDs[j+startpos] != '\0'; j++) {
            
            strid[j] = strLatestServerIDs[j+startpos];
        }
        strid[j] = '\0';
        startpos = j+startpos +1;
        m_pLatestServerIDs[i] = atoi(strid);
    
    }
    return 0;
}
int MB_ServerList::parseServerList2(std::string &strServerList){

    int num = 0;
    int endPos = strServerList.length();
    int count = 1;
    for (int i = 0; i < endPos; i++) {
        
        if(strServerList[i] == ','){
        
            count ++;
        }
    }
    num = count/4;
    if(endPos == 0){
        
        num  = 0;
    }
    
    m_iServerListCount = num;    
    if (num == 0) {
        MB_LOG("server list num error.");
        return -1;
    }
    m_iServerListCount = num;
    m_pServerList = new ServerList[num];
    int lastPos = -1;
    int  firstPos  =0;
    std::string str;
    for (int i = 0; i < num; i++) {
        
        //status
        firstPos = lastPos + 1;
        if (firstPos == std::string::npos) {
            MB_LOG("列表status 数据错误");
            break;
        }
        lastPos = strServerList.find(',', firstPos);
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverStatus = atoi(str.c_str());
        
        //name
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表name 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
//        MB_LOG("server name:%s",str.c_str());
        m_pServerList[i].name = str;
        
        //id
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表id 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverID = atoi(str.c_str());
        
        //ip
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表ip 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverIP = str;
        
        //port
        firstPos = lastPos + 1;
        lastPos = strServerList.find('\n', firstPos);
        if (lastPos == std::string::npos) {
            lastPos = endPos;
            str = strServerList.substr(firstPos, lastPos-firstPos);
        }
        else
        {
            str = strServerList.substr(firstPos, lastPos-firstPos);
        }
        m_pServerList[i].serverPort = atoi(str.c_str());
    }
    
    return 0;
    
}
MB_ServerList::~MB_ServerList()
{
    CC_SAFE_DELETE_ARRAY(m_pServerList);
    CC_SAFE_DELETE_ARRAY(m_pLatestServerIDs);
}

MB_ServerList* MB_ServerList::getInstance()
{
    if(s_pServerList == NULL){
        s_pServerList = new MB_ServerList();
    }

    return s_pServerList;
}
int MB_ServerList::getNowServerID(){

    return m_nSelectServerid;
}
const char * MB_ServerList::getNowServerName(){
    
    for (int i = 0 ; i < m_iServerListCount ; i++) {
        
        if(m_pServerList[i].serverID == m_nSelectServerid ){
            
            return m_pServerList[i].name.c_str();
            
        }
    }
    return  " ";
}
void MB_ServerList::destroyInstance()
{
    if(s_pServerList){
    
        CC_SAFE_RELEASE_NULL(s_pServerList);
    }
}

int MB_ServerList::parseServerList(std::string strServerList)
{
    int firstPos = 0;
    int lastPos = strServerList.find(',', firstPos);
    std::string str = strServerList.substr(firstPos,lastPos - firstPos);
    int num = atoi(str.c_str());
    
    m_iServerListCount = num;
    
    if (num == 0) {
        MB_LOG("server list num error.");
        return -1;
    }
    m_iServerListCount = num;
    m_pServerList = new ServerList[num];
    int endPos = strServerList.size();
    
    for (int i = 0; i < num; i++) {
        
        //status
        firstPos = lastPos + 1;
        if (firstPos == std::string::npos) {
            MB_LOG("列表status 数据错误");
            break;
        }
        lastPos = strServerList.find(',', firstPos);
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverStatus = atoi(str.c_str());
        
        //name
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表name 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].name = str;
        
        //id
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表id 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverID = atoi(str.c_str());
        
        //ip
        firstPos = lastPos + 1;
        lastPos = strServerList.find(',', firstPos);
        if (lastPos == std::string::npos) {
            MB_LOG("列表ip 数据错误");
            break;
        }
        str = strServerList.substr(firstPos, lastPos - firstPos);
        m_pServerList[i].serverIP = str;
        
        //port
        firstPos = lastPos + 1;
        lastPos = strServerList.find('\n', firstPos);
        if (lastPos == std::string::npos) {
            lastPos = endPos;
            str = strServerList.substr(firstPos, lastPos-firstPos);
        }
        else
        {
            str = strServerList.substr(firstPos, lastPos-firstPos);
        }
        m_pServerList[i].serverPort = atoi(str.c_str());
        
    }
    
    return 0;
}

int MB_ServerList::parseLatestServerIDs(std::string strLatestServerIDs)
{
    int firstPos = 0;
    int lastPos = strLatestServerIDs.find(',', firstPos);
    std::string strID = strLatestServerIDs.substr(firstPos,lastPos - firstPos);
    //没有最近登陆的情况
    int num = atoi(strID.c_str());
    if (num == 0) {
        num = 1;
        m_pLatestServerIDs = new unsigned int[num];
        m_pLatestServerIDs[0] = -1;
        m_iLatestServerIDsCount = 0;
        return 0;
    }
    
    m_iLatestServerIDsCount = num;
    m_pLatestServerIDs = new unsigned int[num];
    memset(m_pLatestServerIDs, 0, num * sizeof(unsigned int));
    
    int endPos = strLatestServerIDs.size();
    
    for (int i = 0; i < num; i++ ) {
        
        firstPos = lastPos + 1;
        lastPos = strLatestServerIDs.find(',', firstPos);
        
        if (lastPos == std::string::npos) {
            lastPos = endPos;
            strID = strLatestServerIDs.substr(firstPos, lastPos - firstPos);
            m_pLatestServerIDs[i] = atoi(strID.c_str());
            break;
        }
        else{
            strID = strLatestServerIDs.substr(firstPos, lastPos - firstPos);
            m_pLatestServerIDs[i] = atoi(strID.c_str());
        }
    }
    return 0;
}

void MB_ServerList::setSelectInfo()
{
    int serverID = -1;
    if (m_iLatestServerIDsCount == 0)
    {
        for (int i = 0; i < m_iServerListCount; i++) {
            
            if (serverID < m_pServerList[i].serverID)
            {
                serverID = m_pServerList[i].serverID;
            }
        }
    }
    else
    {
        serverID = m_pLatestServerIDs[0];
    }
    
    ServerList* serverList = getServerListByID(serverID);
    if (serverList==NULL)
    {
        serverID = m_pServerList[0].serverID;
        serverList = getServerListByID(serverID);
        m_iLatestServerIDsCount = 0;
    }
    m_selectServerId = serverID;
    m_nSelectServerid = serverID;
    
    m_pSelectIP = serverList->serverIP;
    m_iSelectPort = serverList->serverPort;
    
    addRecentlyServerId(MB_ServerList::m_nSelectServerid);
    saveRecentlyServerList();
}

ServerList* MB_ServerList::getServerListByID(int serverID)
{
    for (int i = 0; i < m_iServerListCount; i++) {
        if (serverID == m_pServerList[i].serverID) {
            
            return &m_pServerList[i];
        }
    }
    return NULL;
}

void MB_ServerList::addRecentlyServerId(unsigned int sid)
{
//    if (NSGameHelper::getSrcType() > NSGameHelper::ACCOUNT_TYPE_NORMAL)
//    {
//        return ;
//    }
    if (m_iLatestServerIDsCount==0)
    {
        m_pLatestServerIDs[0] = sid;
        m_iLatestServerIDsCount = 1;
    }
    else
    {
        if (sid != m_pLatestServerIDs[0])
        {
            m_iLatestServerIDsCount = 2;
            m_pLatestServerIDs[1] = m_pLatestServerIDs[0];
            m_pLatestServerIDs[0] = sid;
        }
    }
}

ServerList* MB_ServerList::getServerListByIndex(int index)
{
    if (index < m_iServerListCount) {
        return &m_pServerList[index];
    }
    return NULL;
}

uint32_t MB_ServerList::getLatestServerIDByIndex(int index)
{
    if (index >= m_iLatestServerIDsCount) {
        return -1;
    }
    
    return m_pLatestServerIDs[index];
}
uint16_t MB_ServerList::m_nSelectServerid = 0;

const char * MB_ServerList::getInviteCode(){
    
    return m_pInviteCode.c_str();
}
void  MB_ServerList::setInviteCode(const char *inviteCode){
    
    m_pInviteCode = inviteCode;
}
