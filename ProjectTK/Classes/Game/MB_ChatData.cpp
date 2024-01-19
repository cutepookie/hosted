
#include "MB_ChatData.h"
#include <algorithm>
MB_ChatDataMgr * MB_ChatDataMgr::m_pSharedData = NULL;
MB_ChatDataMgr::MB_ChatDataMgr(){

    m_pChatListWrold = new CCArray();
    m_pGagList = new CCArray();
    m_pChatListFamily = new CCArray();
    m_pChatListPrivate = new CCArray();
    m_iLastSendTime = 0;
    m_iLimitSeconds = 0;

    m_bNewPrivateMsg = false;
    m_bNewPublicMsg = false;
    m_bCanTellServer = true;
    
    SOCKET_MSG_REGIST(SC_TALK_WORLD, MB_ChatDataMgr);
    SOCKET_MSG_REGIST(SC_TALK_WORLD_MESSAGE, MB_ChatDataMgr);
    SOCKET_MSG_REGIST(SC_GET_GAG_LIST , MB_ChatDataMgr);
    SOCKET_MSG_REGIST(SC_TALK_RECENT_LIST, MB_ChatDataMgr);
    SOCKET_MSG_REGIST(SC_TALK_PERSON, MB_ChatDataMgr);
    SOCKET_MSG_REGIST(SC_TALK_PERSON_OFFLINE, MB_ChatDataMgr);
}
MB_ChatDataMgr::~MB_ChatDataMgr(){

    if (m_pSaveFile)
    {
        if(m_pSaveFile->getUserEmailArray())
            m_pSaveFile->getUserEmailArray()->removeAllObjects();
        CC_SAFE_RELEASE_NULL(m_pSaveFile);
    }
    
    m_pGagList->removeAllObjects();
    m_pChatListWrold->removeAllObjects();
    m_pChatListPrivate->removeAllObjects();
    m_vBlackOder.clear();

    CC_SAFE_DELETE(m_pGagList);
    CC_SAFE_DELETE(m_pChatListWrold);
    CC_SAFE_RELEASE_NULL(m_pChatListFamily);
    CC_SAFE_RELEASE_NULL(m_pChatListPrivate);
    SOCKET_MSG_UNREGIST(SC_TALK_WORLD);
    SOCKET_MSG_UNREGIST(SC_TALK_WORLD_MESSAGE);
    SOCKET_MSG_UNREGIST(SC_GET_GAG_LIST);
    SOCKET_MSG_UNREGIST(SC_TALK_RECENT_LIST);
    SOCKET_MSG_UNREGIST(SC_TALK_PERSON);
    SOCKET_MSG_UNREGIST(SC_TALK_PERSON_OFFLINE);
}
MB_ChatDataMgr *MB_ChatDataMgr::getInstance(){

    if(m_pSharedData == NULL){
    
        m_pSharedData = new MB_ChatDataMgr();
//        m_pSharedData->readConfigData();
    }
    return m_pSharedData;
}

void MB_ChatDataMgr::throwIntoBlackOder(uint32_t roleid)
{
    if(!checkInBlackOder(roleid))
    {
        m_vBlackOder.push_back(roleid);
    }
}

bool MB_ChatDataMgr::checkInBlackOder(uint32_t roleid)
{
    return std::find(m_vBlackOder.begin(), m_vBlackOder.end(), roleid)!=m_vBlackOder.end();
}

void MB_ChatDataMgr::readConfigData()
{
    CCArray* pArray = new CCArray;
    if(MB_XmlFile::readNodesFromFile("config/talk_interval.xml","talk|talk",pArray))
    {
        MB_XmlNode* pNode = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
        if (pNode)
        {
            m_iLimitSeconds = pNode->queryAttributeByName("limit")->intValue();
        }
    }
    pArray->release();
}
bool MB_ChatDataMgr::talkCDFinished()
{
    int passtime = MB_ClientSocket::getInstance()->getServerTime() - m_iLastSendTime;
    if (passtime >= m_iLimitSeconds)
    {
        return true;
    }
    
    return false;
}
int MB_ChatDataMgr::getLeftCDTime()
{
    int left = MB_ClientSocket::getInstance()->getServerTime()-m_iLastSendTime;
    return -left + m_iLimitSeconds;
}
void MB_ChatDataMgr::destroyInstance(){

    if(m_pSharedData != NULL){
    
        delete m_pSharedData;
    }
    m_pSharedData = NULL;
}
void MB_ChatDataMgr::onMsgRecv(CCNode* node, SocketResponse* response){

    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_TALK_WORLD_MESSAGE:
            recvtalk_world_message(recvPacket);
            break;
        case SC_TALK_WORLD:
            recvtalk_world(recvPacket);
            break;
        case SC_GET_GAG_LIST:
            recvget_gag_list(recvPacket);
        case SC_TALK_RECENT_LIST:
            recvtalk_recent_list(recvPacket);
            break;
        case SC_TALK_PERSON:
            recvtalk_person(recvPacket);
            break;
        case SC_TALK_PERSON_OFFLINE:
            recvtalk_person_offline(recvPacket);
            break;
        default:
            break;
    }
}

/*
 //獲取最近的聊天记录
 message	sendtalk_recent_list[id=12608,route=talk_server]{
 required        int8                            channel = 1;//頻道，1世界頻道，3联盟頻道
 }
 */
void MB_ChatDataMgr::sendtalk_recent_list(uint8_t type)
{
    SOCKET_REQUEST_START(CS_TALK_RECENT_LIST);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_TALK_RECENT_LIST, MB_ChatDataMgr::onMsgRecv);
}

/*
 message	recvtalk_recent_list[id=12609]{
 required        int8                            channel = 1;//頻道，1世界頻道，3联盟頻道
 repeated		recvtalk_world_message			list	= 1;//聊天记录列表
 }
 */
void MB_ChatDataMgr::recvtalk_recent_list(MB_MsgBuffer *recvPacket)
{
    uint16_t count = 0;
    uint8_t type = 0;
    recvPacket->readU8(&type);
    
    recvPacket->readU16(&count);
    for (uint16_t i=0; i<count; ++i)
    {
        addChatData(recvPacket,type);
    }
}
/*私聊
 message sendtalk_person[id=12610]{
 required       int32          roleID          =1;//私聊角色ID
 required       string         talkMessage  =2;//喊话内容
 }*/
void MB_ChatDataMgr::sendtalk_person(uint32_t roleID,const char* string)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_TALK_PERSON);
    packet->writeU32(roleID);
    packet->Write(string, strlen(string));
    SOCKET_REQUEST_END(SC_TALK_PERSON, MB_ChatDataMgr::onMsgRecv);
}

/*message recvtalk_person[id=12611]{
    required        int8            result      =1;//喊话結果
    // 1 => 成功
    // 2 => 說話太快
    // 3 => 說話内容太長
    // 4 => 不是好友
}*/
void MB_ChatDataMgr::recvtalk_person(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
}

/*message sendtalk_world[id=12601]{
 required       int8            channel          =1;//頻道，1世界頻道，3联盟頻道
 required		  string			talkMessage	=2;//喊话内容
 }*/
bool MB_ChatDataMgr::sendtalk_world(uint8_t type, const char *string){

    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_TALK_WORLD);
    packet->writeU8(type);
    packet->Write(string, strlen(string));
    SOCKET_REQUEST_END(SC_TALK_WORLD, MB_ChatDataMgr::onMsgRecv);
    return true;
}

void MB_ChatDataMgr::sendtalk_person_offline()
{
    SOCKET_REQUEST_START(CS_TALK_PERSON_OFFLINE);
    SOCKET_REQUEST_END(SC_TALK_PERSON_OFFLINE, MB_ChatDataMgr::onMsgRecv);
}


int MB_ChatDataMgr::sortArray(CCObject *p1,CCObject* p2)
{
    if (p1 == NULL || p2 == NULL) {
        return true;
    }
    MB_ChatData* data1 = dynamic_cast<MB_ChatData*>(p1);
    MB_ChatData* data2 = dynamic_cast<MB_ChatData*>(p2);
    
    if (data1 == NULL || data2 == NULL) {
        return true;
    }
    return data1->getTime() < data2->getTime();
}

void MB_ChatDataMgr::recvtalk_person_offline(MB_MsgBuffer *recvPacket)
{
    m_pSaveFile = MB_SaveMsgFile<MB_ChatData>::create(MB_RoleData::getInstance()->getUID(), 0);
    CC_SAFE_RETAIN(m_pSaveFile);
    CCArray* pArray = m_pSaveFile->getUserEmailArray();
    
    MB_ChatData* pObj = NULL;
    CCARRAY_FOREACH_4TYPE(pArray, MB_ChatData*, pObj)
    {
        insertMessage(kChannelPrivate, pObj);
    }
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    for (uint16_t i=0; i<count; ++i)
    {
        addChatData(recvPacket,kChannelPrivate);
    }
    m_bNewPrivateMsg = count>0;
    
    std::sort(m_pChatListPrivate->data->arr,m_pChatListPrivate->data->arr+m_pChatListPrivate->count(),sortArray);
}


bool MB_ChatDataMgr::recvtalk_world(MB_MsgBuffer *recvPacket){

    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result ;
    recvPacket->readU8(&result);
    if(result == 1){
    
        m_iLastSendTime = MB_ClientSocket::getInstance()->getServerTime();
        return true;
        
    }else if(result == 2){
    
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
  
    }else if(result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("说话太快了");
    }
    else if(result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("内容太长了");
    }
    else if(result == 5){
        
        MB_Message::sharedMB_Message()->showMessage("等级太低, 未解锁该功能");
        
    }else if(result == 6){
        
        MB_Message::sharedMB_Message()->showMessage("被GM禁言了");
        
    }else {
    
        CCLog("talk error code %d",result);
    }
    return false;
}
void MB_ChatDataMgr::addChatData(MB_MsgBuffer *recvPacket,uint8_t type)
{
//    //recvPacket->readU8(&type);
    recvPacket->skip(sizeof(uint8_t));
    char * roleName = recvPacket->ReadString();

    MB_ChatData *data = new MB_ChatData();
    data->setChannelType((ChatChannelType)type);
    if(type == kChannelPrivate)
    {
        data->setTargetUID(MB_RoleData::getInstance()->getUID());
        data->setRoleTarget(MB_RoleData::getInstance()->getName());
    }
    if (roleName == NULL)
    {
        data->setRoleName("unknow role");
    }
    else
    {
        data->setRoleName(roleName);
        CC_SAFE_FREE(roleName);
    }
    
    char * message = recvPacket->ReadString();

    if (message == NULL)
    {
        data->setMessage("unknow message");
    }
    else
    {
        data->setMessage(message);
        CC_SAFE_FREE(message);
    }
    
    uint8_t roleTitle;
    recvPacket->readU8(&roleTitle);
    uint64_t timestamp;
    recvPacket->readU64(&timestamp);
    data->setTitle(roleTitle);
    data->setTime(timestamp);
    uint32_t roleId;
    recvPacket->readU32(&roleId);
    data->setRoleID(roleId);
    recvPacket->readU8(&roleTitle);
    data->setFamilyTitle(roleTitle);
    
    char * pLoc = recvPacket->ReadString();
    if (pLoc)
    {
        data->setLocation(pLoc);
        CC_SAFE_FREE(pLoc);
    }
    else
    {
//        data->setLocation("未知區域");
    }
    
    uint8_t isMale;
    recvPacket->readU8(&isMale);
    data->setIsMale(isMale);
    
    uint32_t head;
    recvPacket->readU32(&head);
    data->setHead(head);
    
//    CCLOG("head id : %d",head);
    
    insertMessage(type, data);
    data->release();
}

CCArray* MB_ChatDataMgr::getChatListByType(uint8_t type)
{
    if (type == kChannelFamily)
    {
       return m_pChatListFamily;
    }
    else if(type == kChannelWorld)
    {
        return m_pChatListWrold;
    }
    else if(type == kChannelPrivate)
    {
        return m_pChatListPrivate;
    }
    
    return NULL;
}

void MB_ChatDataMgr::insertMessage(uint8_t type,MB_ChatData *data)
{
    CCArray* pChatList = getChatListByType(type);
    if (pChatList == NULL)
    {
        return;
    }
    
    if(pChatList->count() >= MAX_TALK_MESSAGE){
        
        pChatList->removeObjectAtIndex(0);
    }
    pChatList->addObject(data);
}
/*
 message	recvtalk_world_message[id=12603]{
 required        int8            channel     =1;//頻道，1世界頻道，3联盟頻道
 required		string			roleName	=2;//喊话人的名字
 required		string			message		=3;//喊话内容
 required		int8			roleTitle	=4;//喊话人官爵
 required		int64			timeStamp	=5;//喊话的時間戳
 required		int32			roleID		=6;//喊话人的ID
 required        int8            familyTitle    =7;//喊话人的联盟官职
 required       string                          人的位置  chk
 required     bool          isMale          =9;//性别
 required     int32         head            =10;//自定义头像ID
 }
 */
bool MB_ChatDataMgr::recvtalk_world_message(MB_MsgBuffer *recvPacket){

    uint8_t type = 0;
    recvPacket->readU8(&type);
    char * roleName = recvPacket->ReadString();
    if(strcmp(roleName, MB_RoleData::getInstance()->getName()) == 0){
    
        CC_SAFE_FREE(roleName);
        return false;
    }
    
    MB_ChatData *data = new MB_ChatData();
    data->setChannelType((ChatChannelType)type);
    data->setRoleName(roleName);
    if(type == kChannelPrivate)
    {
        data->setTargetUID(MB_RoleData::getInstance()->getUID());
        data->setRoleTarget(MB_RoleData::getInstance()->getName());
        m_bNewPrivateMsg = true;
    }
    else if(type == kChannelWorld)
    {
        m_bNewPublicMsg = true;
    }
    CC_SAFE_FREE(roleName);
    
    char * message = recvPacket->ReadString();
    if(MB_DirtyWordsCheck::getInstance()->checkDatabuf(message))return false;
    
    if(message)data->setMessage(message);
    CC_SAFE_FREE(message);
    uint8_t roleTitle;
    recvPacket->readU8(&roleTitle);
    uint64_t timestamp;
    recvPacket->readU64(&timestamp);
    data->setTitle(roleTitle);
    data->setTime(timestamp);
    uint32_t roleId;
    recvPacket->readU32(&roleId);
    uint8_t familyTitle = 0;
    recvPacket->readU8(&familyTitle);
    data->setFamilyTitle(familyTitle);
    data->setRoleID(roleId);
    data->setTargetUID(0);
    char *locaton = recvPacket->ReadString();
    if(locaton)
    {
        data->setLocation(locaton);
        CC_SAFE_FREE(locaton);
    }
    
    uint8_t isMale;
    recvPacket->readU8(&isMale);
    data->setIsMale(isMale);
    
    uint32_t head;
    recvPacket->readU32(&head);
    data->setHead(head);
    

    if(type == kChannelPrivate)
    {
        if(m_pChatListPrivate->count() >= MAX_TALK_MESSAGE){
            
            m_pChatListPrivate->removeObjectAtIndex(0);
        }
        m_pChatListPrivate->addObject(data);
        savePrivateChat2File();
    }
    else
    {
        if (!checkInBlackOder(data->getRoleID())) // 如果不在屏蔽列表里面
        {
            if(m_pChatListWrold->count() >= MAX_TALK_MESSAGE){
                
                m_pChatListWrold->removeObjectAtIndex(0);
            }
            m_pChatListWrold->addObject(data);
        }
    }
    
    data->release();
    
    return false;
}
void MB_ChatDataMgr::savePrivateChat2File()
{
    m_pSaveFile->getUserEmailArray()->removeAllObjects();
    m_pSaveFile->getUserEmailArray()->addObjectsFromArray(m_pChatListPrivate);

    m_pSaveFile->saveFile(MB_RoleData::getInstance()->getUID(), 0);
}

void MB_ChatDataMgr::clearChatCache()
{
    m_pSaveFile->getUserEmailArray()->removeAllObjects();
    m_pChatListPrivate->removeAllObjects();
    m_pSaveFile->getUserEmailArray()->addObjectsFromArray(m_pChatListPrivate);
    
    m_pSaveFile->saveFile(MB_RoleData::getInstance()->getUID(), 0);
}

bool MB_ChatDataMgr::sendgag_one(const char *roleName){

    SOCKET_REQUEST_START(CS_GAG_ONE);
    packet->Write(roleName, strlen(roleName));
    SOCKET_REQUEST_END(CS_GAG_ONE, MB_ChatDataMgr::onMsgRecv);
    
    CCObject *m_pName;
    CCARRAY_FOREACH(m_pGagList, m_pName){
    
        if(strcmp(((CCString *)m_pName)->getCString(), roleName) == 0){
        
            return true;
        }
    }
    m_pGagList->addObject(CCString::create(roleName));
    return true;
}
bool MB_ChatDataMgr::sendungag_one(const char *roleName){

    SOCKET_REQUEST_START(CS_UNGAG_ONE);
    packet->Write(roleName, strlen(roleName));
    SOCKET_REQUEST_END(CS_UNGAG_ONE, MB_ChatDataMgr::onMsgRecv);
    CCObject *m_pName;
    CCARRAY_FOREACH(m_pGagList, m_pName){
        
        if(strcmp(((CCString *)m_pName)->getCString(), roleName) == 0){
            
            m_pGagList->removeObject(m_pName);
            return true;
        }
    }
    return true;
}
bool MB_ChatDataMgr::sendget_gag_list(){

    SOCKET_REQUEST_START(CS_GET_GAG_LIST);
    SOCKET_REQUEST_END(SC_GET_GAG_LIST, MB_ChatDataMgr::onMsgRecv);
    return true;

}
bool MB_ChatDataMgr::recvget_gag_list(MB_MsgBuffer *recvPacket){

    uint16_t list ;
    recvPacket->readU16(&list);
    for (int i = 0 ;  i < list ; i++) {
    
        char *roleName = recvPacket->ReadString();
        m_pGagList->addObject(CCString::create(roleName?roleName:""));
        CC_SAFE_FREE(roleName);
    }
    return  true;
}
CCArray * MB_ChatDataMgr::getTalkWorldArray(){

    return m_pChatListWrold;
}
CCArray * MB_ChatDataMgr::getGagArray(){

    return m_pGagList;
}
bool MB_ChatDataMgr::isCheckIsInGAG(const char *roleName){

    CCObject *m_pName;
    CCARRAY_FOREACH(m_pGagList, m_pName){
        
        if(strcmp(((CCString *)m_pName)->getCString(), roleName) == 0){
            
            return true;
        }
    }
    return false;
}

void MB_ChatDataMgr::onLoadingScene()
{
    sendget_gag_list();
    sendtalk_recent_list(kChannelWorld);
    sendtalk_recent_list(kChannelFamily);
    sendtalk_person_offline();
}
