#ifndef __ProjectMB__MB_ChatData__
#define __ProjectMB__MB_ChatData__

#include "Game.h"
#include "MB_MailMsgFile.h"
#include "MB_MailMsgData.h"
#define MAX_TALK_MESSAGE 50


enum ChatChannelType
{
    kChannelWorld = 1,
    kChannelPrivate = 2,
    kChannelFamily = 3,
};


class MB_ChatData : public MB_SaveMsgData
{
private :
    std::string m_strRoleName;  //發起方
    std::string m_strMessage;
public:
    
    MB_ChatData(){
        m_nFamilyTitle = 0;
        m_nHead = 0;
        m_nChannelType = kChannelWorld;
        m_nTime = 0;
    }
    ~MB_ChatData(){
        
    }
    const char *getRoleName(){
        
        return m_strRoleName.c_str();
    }
    void setRoleName(const char *roleName){
        
        m_strRoleName = roleName;
    }
    const char *getMessage(){
        
        return m_strMessage.c_str();
    }
    void setMessage(const char *message){
        
        m_strMessage  = message;
    }
    CC_SYNTHESIZE(uint8_t, m_nFamilyTitle, FamilyTitle);
    CC_SYNTHESIZE(uint8_t,m_nTitle, Title);
    CC_SYNTHESIZE(uint64_t, m_nTime, Time);
    CC_SYNTHESIZE(uint32_t ,m_nRoleID,RoleID);//發送方UID
    CC_SYNTHESIZE(std::string, m_location, Location);
    CC_SYNTHESIZE(uint8_t, m_isMale, IsMale);
    CC_SYNTHESIZE(uint32_t, m_nHead, Head);
    CC_SYNTHESIZE(uint32_t, m_nChannelType, ChannelType);
    
    
    CC_SYNTHESIZE(uint32_t, m_nTargetUID, TargetUID);//接收方UID
    CC_SYNTHESIZE(std::string ,m_strRoleTarget, RoleTarget);//接收方名字
    
    virtual bool init(MB_XmlNode* pNode)
    {
        if (pNode == NULL)
        {
            return false;
        }
        m_nFamilyTitle = pNode->queryAttributeByName("m_nFamilyTitle")->intValue();
        m_nTitle = pNode->queryAttributeByName("m_nTitle")->intValue();
        const char* pTime = pNode->queryAttributeByName("m_nTime")->getCString();
        m_nTime = atoll(pTime);
        
        m_nRoleID = pNode->queryAttributeByName("m_nRoleID")->intValue();
        m_location = pNode->queryAttributeByName("m_location")->getCString();
        m_isMale = pNode->queryAttributeByName("m_isMale")->intValue();
        m_nHead = pNode->queryAttributeByName("m_nHead")->intValue();
        m_strRoleName = pNode->queryAttributeByName("m_strRoleName")->getCString();
        m_strMessage = pNode->queryAttributeByName("m_strMessage")->getCString();
        m_nChannelType = pNode->queryAttributeByName("m_nChannelType")->intValue();
        m_nTargetUID = pNode->queryAttributeByName("m_nTargetUID")->intValue();
        m_strRoleTarget = pNode->queryAttributeByName("m_strRoleTarget")->getCString();
        
        return true;
    }
    
    virtual bool saveEmail(xmlNodePtr ptr)
    {
        char buff[100] = {0};
        sprintf(buff, "%d",m_nFamilyTitle);
        xmlNewProp(ptr,BAD_CAST"m_nFamilyTitle",BAD_CAST buff);
        sprintf(buff, "%d",m_nTitle);
        xmlNewProp(ptr,BAD_CAST"m_nTitle",BAD_CAST buff);
        sprintf(buff, "%lld",m_nTime);
        xmlNewProp(ptr,BAD_CAST"m_nTime",BAD_CAST buff);
        xmlNewProp(ptr,BAD_CAST"m_location",BAD_CAST m_location.c_str());
        
        xmlNewProp(ptr,BAD_CAST"m_strRoleName",BAD_CAST m_strRoleName.c_str());
        xmlNewProp(ptr,BAD_CAST"m_strRoleTarget",BAD_CAST m_strRoleTarget.c_str());
        
        xmlNewProp(ptr,BAD_CAST"m_strMessage",BAD_CAST m_strMessage.c_str());
        sprintf(buff, "%d",m_isMale);
        xmlNewProp(ptr,BAD_CAST"m_isMale",BAD_CAST buff);
        sprintf(buff, "%d",m_nHead);
        xmlNewProp(ptr,BAD_CAST"m_nHead",BAD_CAST buff);
        sprintf(buff, "%d",m_nChannelType);
        xmlNewProp(ptr,BAD_CAST"m_nChannelType",BAD_CAST buff);
        
        sprintf(buff, "%d",m_nRoleID);
        xmlNewProp(ptr,BAD_CAST"m_nRoleID",BAD_CAST buff);
        sprintf(buff, "%d",m_nTargetUID);
        xmlNewProp(ptr,BAD_CAST"m_nTargetUID",BAD_CAST buff);
        return true;
    }
};




class MB_ChatDataMgr:public CCObject
{
private :
    static  MB_ChatDataMgr * m_pSharedData;
    CCArray * m_pChatListWrold;
    CCArray*    m_pChatListFamily;
    CCArray*    m_pChatListPrivate;
    CCArray * m_pGagList;
    void addChatData(MB_MsgBuffer *recvPacket,uint8_t type);
    CC_SYNTHESIZE_READONLY(uint32_t, m_iLastSendTime, LastSendTime);
    CC_SYNTHESIZE_READONLY(uint32_t, m_iLimitSeconds, LimitSeconds);
    void readConfigData();
    CCArray* getChatListByType(uint8_t type);
    void insertMessage(uint8_t type,MB_ChatData *data);
    MB_SaveMsgFile<MB_ChatData> * m_pSaveFile;
    void savePrivateChat2File();
    void clearChatCache();
    std::vector<int32_t> m_vBlackOder;
    CC_SYNTHESIZE_READONLY(bool, m_bCanTellServer, TellServer);
public:
    void throwIntoBlackOder(uint32_t roleid);
    bool checkInBlackOder(uint32_t roleid);
    MB_ChatDataMgr();
    ~MB_ChatDataMgr();
    static MB_ChatDataMgr *getInstance();
    static void destroyInstance();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool sendtalk_world(uint8_t type, const char *string);
    bool recvtalk_world(MB_MsgBuffer *recvPacket);
    bool recvtalk_world_message(MB_MsgBuffer *recvPacket);
    bool sendgag_one(const char *roleName);
    bool sendungag_one(const char *roleName);
    bool sendget_gag_list();
    bool recvget_gag_list(MB_MsgBuffer *recvPacket);
    void sendtalk_recent_list(uint8_t type);
    void recvtalk_recent_list(MB_MsgBuffer *recvPacket);
    
    void recvtalk_person(MB_MsgBuffer *recvPacket);
    void sendtalk_person(uint32_t roleID,const char* string);
    
    void sendtalk_person_offline();
    void recvtalk_person_offline(MB_MsgBuffer *recvPacket);
    
    static int sortArray(CCObject *,CCObject*);
    void onLoadingScene();
    bool talkCDFinished();
    int getLeftCDTime();
    CCArray *getTalkWorldArray();
    CCArray *getGagArray();
    bool isCheckIsInGAG(const char *roleName);
    
    bool m_bNewPublicMsg;
    bool m_bNewPrivateMsg;
    
};
#endif /* defined(__ProjectMB__MB_ChatData__) */
