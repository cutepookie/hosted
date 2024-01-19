

#include "MB_NotificationData.h"

MB_NotificationData::MB_NotificationData(){

}
MB_NotificationData::~MB_NotificationData(){

}

const char * MB_NotificationData::getMessage(){
    
    return m_strMessage.c_str();
}
const char * MB_NotificationData::getMessageName(){

     return m_strMessageName.c_str();
}
void MB_NotificationData::setMessage(const char *message){

    m_strMessage = message;
}
void MB_NotificationData::setMessageName(const char *messageName){

    m_strMessageName = messageName;
}
MB_NotificationMgr * MB_NotificationMgr::m_pSharedMgr = NULL;
MB_NotificationMgr::MB_NotificationMgr(){
    
    m_pNotificationMgr = new CCArray();
}
MB_NotificationMgr::~MB_NotificationMgr(){

    m_pNotificationMgr->removeAllObjects();
    CC_SAFE_DELETE(m_pNotificationMgr);
}
MB_NotificationMgr *MB_NotificationMgr::getInstence(){
    
    if (m_pSharedMgr == NULL) {
        
        m_pSharedMgr = new MB_NotificationMgr();

    }
    return m_pSharedMgr;

}
void MB_NotificationMgr::purgeData(){
    
    if (m_pSharedMgr != NULL) {
        
        delete m_pSharedMgr;
        m_pSharedMgr = NULL;
    }

}
bool MB_NotificationMgr::setLocalTips(const char *message,float addtime,const char *messageName,int type){
    
    CCObject *obj;
    CCARRAY_FOREACH(m_pNotificationMgr, obj){
        
        
        const  char * unitkey = ((MB_NotificationData *)obj)->getMessageName();
        if(strcmp(unitkey, messageName) == 0){
        
            return false;
        }
    }
    
    MB_NotificationData * data = new MB_NotificationData();
    data->setMessage(message);
    data->setMessageName(messageName);
    int recordtime = time(NULL);
    data->setRecordTime(recordtime);
    data->setTime(addtime);
    data->setType(type);
    m_pNotificationMgr->addObject(data);
    data->release();
    return true;
    
}
void MB_NotificationMgr::removeTipsByName(const char * messageName){

    CCObject *obj;
    CCARRAY_FOREACH(m_pNotificationMgr, obj){
        const  char * unitkey = ((MB_NotificationData *)obj)->getMessageName();
        if(strcmp(unitkey, messageName) == 0){
            
            m_pNotificationMgr->removeObject(obj);
            return;
        }
    }
}
void MB_NotificationMgr::loadTips(){

    int socketTime = time(NULL);
    CCObject *obj;
    bool advertrue = CCUserDefault::sharedUserDefault()->getBoolForKey("adventure");
    CCArray removeArray;
    CCARRAY_FOREACH(m_pNotificationMgr, obj){    
      
        MB_NotificationData * data =  (MB_NotificationData *)obj;
        float addtime =  data->getTime() - (socketTime - data->getRecordTime());
        
        if (addtime <= 0) {
            
            removeArray.addObject(obj);
            continue;
        }
        if (data->getType() == kNotificationTypeAdventrue && advertrue ) {
        
            OCandCppHelper::setLocalTips(data->getMessage(),addtime, data->getMessageName());
        }
        
    }
    CCARRAY_FOREACH(&removeArray, obj){
    
        m_pNotificationMgr->removeObject(obj);
    }
    
}
void MB_NotificationMgr::removeTips(){
  
    CCObject *obj;
    CCARRAY_FOREACH(m_pNotificationMgr, obj){
        
        MB_NotificationData * data =  (MB_NotificationData *)obj;
        OCandCppHelper::cancelLocalTips(data->getMessageName());
    }
    m_pNotificationMgr->removeAllObjects();
}
