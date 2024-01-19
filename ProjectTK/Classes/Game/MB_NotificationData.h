

#ifndef __ProjectMB__MB__NotificationData__
#define __ProjectMB__MB__NotificationData__
#include "Game.h"
enum kNotificationType{
    
    kNotificationTypeAdventrue,
    kNotificationTypePvp,
    kNotificationTypeOther,
    kNotificationTypeRocketTeam,
};
class MB_NotificationData:public CCObject{
   
    private:
    
        std::string m_strMessage;
        std::string m_strMessageName;
    
    public:
    
        MB_NotificationData();
        ~MB_NotificationData();
        const char *getMessage();
        const char *getMessageName();
        void setMessage(const char *message);
        void setMessageName(const char *messageName);
        CC_SYNTHESIZE(int ,m_nTime, Time);
        CC_SYNTHESIZE(int ,m_nRecordTime, RecordTime);
        CC_SYNTHESIZE(int ,m_nType, Type);
    
};
class MB_NotificationMgr{

    private:
    
        static MB_NotificationMgr * m_pSharedMgr;
        CCArray *m_pNotificationMgr;
    
    public:
    
        MB_NotificationMgr();
        ~MB_NotificationMgr();
        static void purgeData();
        static MB_NotificationMgr *getInstence();
        bool setLocalTips(const char *message,float time,const char *messageName,int type);
        void removeTipsByName(const char * messageName);
        void loadTips();
        void removeTips();
    
};
#endif /* defined(__ProjectMB__MB__Notification__) */
