

#ifndef __ProjectMB__MB_MoneyEevntData__
#define __ProjectMB__MB_MoneyEevntData__

#include "../Common/GameLib/GameFunctionEntry/CCFunctionEntryInterface.h"
class p_item_view;
class MB_MoneyEevntUnit:public CCObject{

    private:
    
        std::string m_pDescription;
        p_item_view *m_pItemList;
        CCArray *m_pReward;
    
    public :
    
        MB_MoneyEevntUnit();
        ~MB_MoneyEevntUnit();
        p_item_view * getItemList();
        void setIemList(p_item_view *  itemList);
        CC_SYNTHESIZE(uint16_t,m_nDrawID, DrawID);
        const char * getDescription(){
        
            return  m_pDescription.c_str();
        }
        void setDescription(const char *description){
        
            m_pDescription = description;
        }
        CCArray *getReward(){
        
            return m_pReward;
        }
        CC_SYNTHESIZE(short, m_nMaxDrawTimes, MaxDrawTimes);
        CC_SYNTHESIZE(uint16_t, m_nCanDrawTimes, CanDrawTimes);
        CC_SYNTHESIZE(uint16_t, m_nAlreadyDrawTimes, AlreadyDrawTimes);
        CC_SYNTHESIZE(uint32_t, m_nCoin, Coin);
        CC_SYNTHESIZE(uint32_t, m_nRoleExp, RoleExp);
        CC_SYNTHESIZE(uint32_t, m_nPetExp, PetExp);
        CC_SYNTHESIZE(uint32_t, m_nGold, Gold);
        CC_SYNTHESIZE(uint32_t, m_nReputation, Reputation);
  
};
//需要的材料
class MB_EventReward:public CCObject{

    public:
    
    MB_EventReward(){
        
    }
    ~MB_EventReward(){
    
    }
    CC_SYNTHESIZE(int16_t, m_nItemType,ItemType);
    CC_SYNTHESIZE(int8_t, m_nIsPet,IsPet);
    CC_SYNTHESIZE(int,m_nNum, Num);
};
class MB_MoneyEevntData:public CCObject{
   
    private:
    
        CCArray *m_pActivyUnit;
        std::string m_pIconRrc;
        std::string m_pActivyName;
        std::string m_pDescription;
    
    public:
    
        MB_MoneyEevntData();
        ~MB_MoneyEevntData();
        CCArray *getUnitList();
        const char * getIconRrc(){
        
            return m_pIconRrc.c_str();
        }
        const char * getActivyName(){
        
            return m_pActivyName.c_str();
        }
        void setIconRrc(const char *iconRrc){
            
            m_pIconRrc = iconRrc;
        }
        void setActivyName(const char *activyName){
        
            m_pActivyName = activyName;
        }
        const char * getDescription(){
        
           return  m_pDescription.c_str();
        }
        void setDescription(const char *description){
        
            m_pDescription = description;
        }
        CC_SYNTHESIZE(uint32_t, m_nActivityID, ActivityID)
        CC_SYNTHESIZE(uint8_t, m_nType,Type)
        CC_SYNTHESIZE(int,m_nStartTime, StartTime);
        CC_SYNTHESIZE(int,m_nStopTime, StopTime);
        CC_SYNTHESIZE(uint32_t,m_nTypeValue, TypeValue);
        MB_MoneyEevntUnit *getUnitByID(uint16_t drawID);
    
};

class MB_MoneyEventEnergy:public CCObject {

    public:
    
        MB_MoneyEventEnergy(){
        }
        ~MB_MoneyEventEnergy(){
        }
        CC_SYNTHESIZE(int, m_nStartTime, StartTime);
        CC_SYNTHESIZE(int, m_nEndTime, EnTime);
        CC_SYNTHESIZE(uint8_t, m_nEnergy, Energy);
        CC_SYNTHESIZE(uint8_t, m_nIsGet,IsGet);
        CC_SYNTHESIZE(uint8_t,m_nEnergyMin,EnergyMin);//体力领取下限
        CC_SYNTHESIZE(uint8_t,m_nOneClickGet,OneClickGet);//单次点击获得次数
        CC_SYNTHESIZE(uint8_t,m_nClickSeconds,ClickSeconds);//点击时间长度，单位秒
};
class MB_MoneySignEmperor:public CCObject{

    private :
    
        std::string m_strEmperor;
    
    public :
    
        MB_MoneySignEmperor(){
    
            m_strEmperor = "";
            m_nIsHasEmperor = 0;
            m_nBoxID = 0;
            m_nLastRequestTime = 0;
        }
        ~MB_MoneySignEmperor(){
        }
        CC_SYNTHESIZE(uint8_t, m_nIsSign, IsSign);
        CC_SYNTHESIZE(uint8_t, m_nSignDay, SignDay);
        CC_SYNTHESIZE(uint8_t, m_nIsGetBox, isGetBox);
        CC_SYNTHESIZE(uint8_t, m_nIsEmperor, IsEmperor);
        const char *getEmperer(){
            
            return m_strEmperor.c_str();
        }
        void setEmperor(const char *emperor){
        
            m_strEmperor = emperor;
        }
        CC_SYNTHESIZE(time_t, m_nLastRequestTime, LastRequestTime);
        CC_SYNTHESIZE(uint8_t , m_nIsHasEmperor,IsHasEmperor);
        CC_SYNTHESIZE(uint16_t, m_nBoxID, BoxID);
    
};
class MB_MoneyEevntMgr:public CCObject{

    private:
  
        static MB_MoneyEevntMgr * m_pShareMoneyMgr;
        CCArray *m_pArray;
        CCArray* m_pNativeArray;
        MB_MoneyEventEnergy* m_pEventEnergy[3];
        MB_MoneySignEmperor * m_pSignEmperor;
    std::vector<NSGameFunction::CCFunctionInterface*>  m_pFunction2Activity;
    std::vector<uint32_t> m_uActivatyIDList;
    public :
    void addFunctionActivity(NSGameFunction::CCFunctionInterface* pFunction);
    void removeFunctionActivity(NSGameFunction::CCFunctionInterface* pFunction);
    const std::vector<NSGameFunction::CCFunctionInterface*>& getFunctionActivity()
    {
        return m_pFunction2Activity;
    }
        MB_MoneyEevntMgr();
        ~MB_MoneyEevntMgr();
        static MB_MoneyEevntMgr * getInstance();
        static void destroyInstance();    
        CC_SYNTHESIZE(bool, m_nHasChange,hasChange);
        CCArray *getEventList();
        CCArray* getNativeEventList();
        std::vector<uint32_t> getActivatyIDList();
        MB_MoneySignEmperor * getSignEmperor(){
    
            return m_pSignEmperor;
        }
        void onMsgRecv(CCNode* node, SocketResponse* response);
        bool sendactivity_get_list();
        bool recvactivity_get_list(MB_MsgBuffer* recvPacket);
        bool recvactivity_get_list2(MB_MsgBuffer* recvPacket);
        bool recvsort(MB_MsgBuffer* recvPacket);
        bool sendactivity_info(uint16_t activityID);
        bool recvactivity_info(MB_MsgBuffer *recvPacket);
        bool sendactivity_draw(uint16_t activityID,uint16_t drawID);
        bool recvactivity_draw(MB_MsgBuffer* recvPacket);
        bool recvactivity_record_update(MB_MsgBuffer* recvPacket);
        bool sendactivity_energy();
        bool sendrole_get_energy(int8_t click_times = 1);
        bool recvrole_get_energy(MB_MsgBuffer* recvPacket);
        bool recvactivity_energy(MB_MsgBuffer* recvPacket);
        bool sendactivity_sign_emperor_info();
        bool recvactivity_sign_emperor_info(MB_MsgBuffer* recvPacket);
        bool sendactivity_sign_get_reward();
        bool recvactivity_sign_get_reward(MB_MsgBuffer* recvPacket);
        bool sendactivity_sign_up();
        bool recvactivity_sign_up(MB_MsgBuffer* recvPacket);
    
        MB_MoneyEevntData *getEventDataByActivityID(uint16_t activityID);
        MB_MoneyEventEnergy* getEventEnergyByIndex(int index);
};
#endif /* defined(__ProjectMB__MB_MoneyEevntData__) */
