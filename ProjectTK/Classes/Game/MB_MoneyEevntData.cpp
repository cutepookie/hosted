
#include "MB_MoneyEevntData.h"
#include "Game.h"
#include <algorithm>

using namespace NSGameFunction;

MB_MoneyEevntMgr *  MB_MoneyEevntMgr::m_pShareMoneyMgr = NULL;
MB_MoneyEevntUnit::MB_MoneyEevntUnit(){

    m_pItemList = NULL;
    m_pReward = new CCArray();
}
MB_MoneyEevntUnit::~MB_MoneyEevntUnit(){
    
    
    if(   m_pItemList != NULL){
        
        for (p_item_view * item =  m_pItemList ; item != NULL; ){
            
            p_item_view * itemForFree = item;
            item = item->next;
            free(itemForFree);
        }
        m_pItemList = NULL;
    }
    m_pReward->removeAllObjects();
    CC_SAFE_DELETE(m_pReward);
}
p_item_view * MB_MoneyEevntUnit::getItemList(){
    
    return   m_pItemList;
}
void MB_MoneyEevntUnit::setIemList(p_item_view *  itemList){
    
    if(m_pItemList != NULL){
        
        for (p_item_view * item =  m_pItemList ; item != NULL; ){
         
            p_item_view * itemForFree = item;
            item = item->next;
            free(itemForFree);
        }
        m_pItemList = NULL;
    }
    
    m_pItemList  = itemList;
}
MB_MoneyEevntUnit *MB_MoneyEevntData::getUnitByID(uint16_t drawID){

    CCObject *obj;
    CCARRAY_FOREACH(m_pActivyUnit, obj){
    
        if(((MB_MoneyEevntUnit *) obj)->getDrawID() == drawID){
        
            return  (MB_MoneyEevntUnit *)obj;
        }
    }
    return NULL;
}
MB_MoneyEevntData::MB_MoneyEevntData(){

    m_nTypeValue = 0;
    m_pActivyUnit = new CCArray();
}
MB_MoneyEevntData::~MB_MoneyEevntData(){

    m_pActivyUnit->removeAllObjects();
    CC_SAFE_DELETE(m_pActivyUnit);
}
CCArray *MB_MoneyEevntData::getUnitList(){

    return m_pActivyUnit;
}

MB_MoneyEevntMgr::MB_MoneyEevntMgr(){

    m_pArray = new CCArray();
    m_pNativeArray = new CCArray();
    m_nHasChange = false;
    m_pEventEnergy[0] = new MB_MoneyEventEnergy();
    m_pEventEnergy[1] = new MB_MoneyEventEnergy();
    m_pEventEnergy[2] = new MB_MoneyEventEnergy();
    m_pSignEmperor = new MB_MoneySignEmperor();
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy1_1", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy1_2", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy2_1", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy2_2", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy3_1", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isClickEnergy3_2", false);
    SOCKET_MSG_REGIST(SC_ACTIVITY_GET_LIST, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_DRAW, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_INFO, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_UPDATE,  MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_RECORD_UPDATE,  MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_ENERGY ,  MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ROLE_GET_ENERGY, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_SIGN_EMPEROR_INFO, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_SIGN_GET_REWARD, MB_MoneyEevntMgr);
    SOCKET_MSG_REGIST(SC_ACTIVITY_SIGN_UP, MB_MoneyEevntMgr);
}
MB_MoneyEevntMgr::~MB_MoneyEevntMgr(){

    m_pFunction2Activity.clear();
    m_uActivatyIDList.clear();
    m_pArray->removeAllObjects();
    CC_SAFE_DELETE(m_pSignEmperor);
    CC_SAFE_DELETE(m_pArray);
    CC_SAFE_DELETE(m_pNativeArray);
    CC_SAFE_DELETE(m_pEventEnergy[0]);
    CC_SAFE_DELETE(m_pEventEnergy[1]);
    CC_SAFE_DELETE(m_pEventEnergy[2]);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_DRAW);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_INFO);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_UPDATE);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_RECORD_UPDATE);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_ENERGY);
    SOCKET_MSG_UNREGIST(SC_ROLE_GET_ENERGY);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_SIGN_EMPEROR_INFO);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_SIGN_GET_REWARD);
    SOCKET_MSG_UNREGIST(SC_ACTIVITY_SIGN_UP);
}
void  MB_MoneyEevntMgr::destroyInstance(){

    if(m_pShareMoneyMgr){
    
        delete  m_pShareMoneyMgr;
        m_pShareMoneyMgr = NULL;
    }
}

MB_MoneyEevntMgr * MB_MoneyEevntMgr::getInstance(){

    if(m_pShareMoneyMgr == NULL){
    
        m_pShareMoneyMgr = new  MB_MoneyEevntMgr();
    }
    return  m_pShareMoneyMgr;
}
CCArray * MB_MoneyEevntMgr::getEventList(){

    return  m_pArray;
}

CCArray* MB_MoneyEevntMgr::getNativeEventList()
{
    return m_pNativeArray;
}
void MB_MoneyEevntMgr::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_ACTIVITY_GET_LIST:
            recvactivity_get_list(recvPacket);
            break;
        case SC_ACTIVITY_INFO:
            recvactivity_info(recvPacket);
            break;
        case SC_ACTIVITY_DRAW:
            recvactivity_draw(recvPacket);
            break;
        case SC_ACTIVITY_UPDATE:
            {
                
                uint16_t data16;
                recvPacket->readU16(&data16);
                MB_MoneyEevntData * data = getEventDataByActivityID(data16);
                recvPacket->readU16(&data16);
                if(data != NULL){
                    MB_MoneyEevntUnit * unit =  data->getUnitByID(data16);
                    
                    if(unit != NULL){
                        
                        recvPacket->readU16(&data16);
                        unit->setCanDrawTimes(data16);
                    }
                }
            }
            break;
        case SC_ACTIVITY_RECORD_UPDATE:
        {
            uint16_t data16;
            recvPacket->readU16(&data16);
            MB_MoneyEevntData * data = getEventDataByActivityID(data16);
            if(data){
            
                uint32_t data32;
                recvPacket->readU32(&data32);
                data->setTypeValue(data32);
                
            }
            break;
        }
        case SC_ACTIVITY_ENERGY:{
        
            recvactivity_energy(recvPacket);
        }
            break;
        case SC_ROLE_GET_ENERGY:{
        
            recvrole_get_energy(recvPacket);
            break;
        }
        case SC_ACTIVITY_SIGN_EMPEROR_INFO:
            recvactivity_sign_emperor_info(recvPacket);
            break;
        case SC_ACTIVITY_SIGN_GET_REWARD:
            recvactivity_sign_get_reward(recvPacket);
            break;
        case SC_ACTIVITY_SIGN_UP:
            recvactivity_sign_up(recvPacket);
            break;
        default:
        
            break;
    }
    
}
bool MB_MoneyEevntMgr::recvactivity_record_update(MB_MsgBuffer* recvPacket){
    
    return true;
}
bool MB_MoneyEevntMgr::sendactivity_get_list(){

    SOCKET_REQUEST_START(CS_ACTIVITY_GET_LIST);
    SOCKET_REQUEST_END(SC_ACTIVITY_GET_LIST, MB_MoneyEevntMgr::onMsgRecv);
    return true;
}
bool MB_MoneyEevntMgr::sendactivity_energy(){

    SOCKET_REQUEST_START(CS_ACTIVITY_ENERGY);
    SOCKET_REQUEST_END(SC_ACTIVITY_ENERGY, MB_MoneyEevntMgr::onMsgRecv);
    
    return true;
}
bool MB_MoneyEevntMgr::recvactivity_energy(MB_MsgBuffer* recvPacket){

     uint8_t data8;
     uint16_t data16;
     uint32_t data32;
     recvPacket->readU16(&data16);
    for (int i = 0 ; i < data16 && i < 3; i++) {
        
        recvPacket->readU32(&data32);
        m_pEventEnergy[i]->setStartTime(data32);
        recvPacket->readU32(&data32);
        m_pEventEnergy[i]->setEnTime(data32);
        recvPacket->readU8(&data8);
        m_pEventEnergy[i]->setEnergy(data8);
        recvPacket->readU8(&data8);
        m_pEventEnergy[i]->setIsGet(data8);
        
        recvPacket->readU8(&data8);
        m_pEventEnergy[i]->setEnergyMin(data8);
        recvPacket->readU8(&data8);
        m_pEventEnergy[i]->setOneClickGet(data8);
        recvPacket->readU8(&data8);
        m_pEventEnergy[i]->setClickSeconds(data8);
    }
    
     return true;
}
bool MB_MoneyEevntMgr::recvactivity_get_list(MB_MsgBuffer* recvPacket){
    
    m_nHasChange = false;
    CCArray *array = CCArray::create();
    uint16_t List;
    recvPacket->readU16(&List);
    for (int i = 0 ; i < List; i++) {
        
        MB_MoneyEevntData *data = new MB_MoneyEevntData();
        uint16_t data16;
        recvPacket->readU16(&data16);
        data->setActivityID(data16);
        char * str = recvPacket->ReadString();
        if(str)
        data->setIconRrc(str);
        CC_SAFE_FREE(str);
        str  = recvPacket->ReadString();
        if(str)
        data->setActivyName(str);
        CC_SAFE_FREE(str);
        array->addObject(data);
        data->release();
        
    }          
    CCObject *temp1;
    CCObject *temp2;
    CCArray *arrayForDelete = CCArray::create();
    CCArray *arrayForAdd = CCArray::create();
    CCARRAY_FOREACH(m_pArray, temp1){
      
        bool isfordelete = true;
        CCARRAY_FOREACH(array, temp2){
            
            if(((MB_MoneyEevntData *)temp1)->getActivityID() == ((MB_MoneyEevntData *)temp2)->getActivityID()){
            
                isfordelete = false;
                break;
            }
        }
        if(isfordelete){
        
            arrayForDelete->addObject(temp1);
        }
    }
    CCARRAY_FOREACH(arrayForDelete, temp1){
        
        m_pArray->removeObject(temp1);
        m_nHasChange = true;
    }
    CCARRAY_FOREACH(array, temp1){
        
        bool isforadd = true;
        CCARRAY_FOREACH(m_pArray, temp2){
            
            if(((MB_MoneyEevntData *)temp1)->getActivityID() == ((MB_MoneyEevntData *)temp2)->getActivityID()){
                
                isforadd = false;
                break;
            }
        }
        if(isforadd){
            
            arrayForAdd->addObject(temp1);
        }
    }
    CCARRAY_FOREACH(arrayForAdd, temp1){
        
        m_pArray->addObject(temp1);
        m_nHasChange = true;
    }
    return true;
}

bool MB_MoneyEevntMgr::recvactivity_get_list2(MB_MsgBuffer* recvPacket){
    
    m_pNativeArray->removeAllObjects();
    uint16_t List;
    recvPacket->readU16(&List);
    for (int i = 0 ; i < List; i++) {
        
        MB_MoneyEevntData *data = new MB_MoneyEevntData();
        uint32_t data32;
        recvPacket->readU32(&data32);
        data->setActivityID(data32);
        recvPacket->readU32(&data32);
        data->setStopTime(data32);
        char * str = recvPacket->ReadString();
        if(str)
            data->setActivyName(str);
        CC_SAFE_FREE(str);
        str  = recvPacket->ReadString();
        if(str)
            data->setDescription(str);
        CC_SAFE_FREE(str);
        m_pNativeArray->addObject(data);
        data->release();
        
    }
    return true;
}

bool MB_MoneyEevntMgr::recvsort(MB_MsgBuffer* recvPacket)
{
    uint16_t len;
    recvPacket->readU16(&len);
    uint32_t data32;
    m_uActivatyIDList.clear();
    for (int i = 0;i < len; i++ )
    {
        recvPacket->readU32(&data32);
        m_uActivatyIDList.push_back(data32);
    }
    return true;
}

std::vector<uint32_t> MB_MoneyEevntMgr::getActivatyIDList()
{
    return m_uActivatyIDList;
}
MB_MoneyEevntData *MB_MoneyEevntMgr::getEventDataByActivityID(uint16_t activityID){

    CCObject *obj ;
    CCARRAY_FOREACH(m_pArray, obj){
    
        if( ((MB_MoneyEevntData *) obj)->getActivityID() == activityID){
        
            return  (MB_MoneyEevntData *)obj;
        }
    }
    return NULL;
}
bool MB_MoneyEevntMgr::sendrole_get_energy(int8_t click_times)
{
    SOCKET_REQUEST_START(CS_ROLE_GET_ENERGY);
    packet->writeU8(click_times);
    SOCKET_REQUEST_END(SC_ROLE_GET_ENERGY, MB_MoneyEevntMgr::onMsgRecv);

    return true;
}
bool MB_MoneyEevntMgr::recvrole_get_energy(MB_MsgBuffer* recvPacket){
    
    uint8_t data8 ;
    recvPacket->readU8(&data8);
    if(data8 == 1){
    
        int nowtime = MB_ClientSocket::getInstance()->getServerTime();
        if(nowtime < m_pEventEnergy[1]->getStartTime()){
        
            m_pEventEnergy[0]->setIsGet(2);
        
        }
        else if(nowtime < m_pEventEnergy[2]->getStartTime())
        {
            m_pEventEnergy[1]->setIsGet(2);
        }
        else {
            
            m_pEventEnergy[2]->setIsGet(2);
        }
        
    }
    return true;
}
bool MB_MoneyEevntMgr::sendactivity_info(uint16_t activityID){
    
    
    SOCKET_REQUEST_START(CS_ACTIVITY_INFO);
    packet->writeU16(activityID);
    SOCKET_REQUEST_END(SC_ACTIVITY_INFO, MB_MoneyEevntMgr::onMsgRecv);

    return true;
}
bool MB_MoneyEevntMgr::recvactivity_info(MB_MsgBuffer *recvPacket){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint16_t data16;
    uint8_t data8;
    uint32_t data32;
    recvPacket->readU16(&data16);
    MB_MoneyEevntData * data = getEventDataByActivityID(data16);
    if(data == NULL){
    
        return false;
    }
    
    recvPacket->readU8(&data8);
    data->setType(data8);
    char *str;
    str = recvPacket->ReadString();
    if(str != NULL)
    data->setDescription(str);
    CC_SAFE_FREE(str);
    recvPacket->readU16(&data16);
    uint16_t length = data16;
    data->getUnitList()->removeAllObjects();
    
    for (int i = 0;  i < length; i++) {
        
        MB_MoneyEevntUnit * unit = new MB_MoneyEevntUnit();
        recvPacket->readU16(&data16);
        unit->setDrawID(data16);
        str = recvPacket->ReadString();
        if(str != NULL)
        unit->setDescription(str);
        CC_SAFE_FREE(str);
        short sdata16;
        recvPacket->readU16(&sdata16);
        unit->setMaxDrawTimes(sdata16);
        recvPacket->readU16(&data16);
        unit->setAlreadyDrawTimes(data16);
        recvPacket->readU16(&data16);
        unit->setCanDrawTimes(data16);
        recvPacket->readU32(&data32);
        unit->setCoin(data32);
        recvPacket->readU32(&data32);
        unit->setRoleExp(data32);
        recvPacket->readU32(&data32);
        unit->setPetExp(data32);
        recvPacket->readU32(&data32);
        unit->setGold(data32);
        recvPacket->readU32(&data32);
        unit->setReputation(data32);
        p_item_view *moveItem = NULL;
        p_item_view *head = NULL;
        int16_t itemLength;
        recvPacket->readU16(&itemLength);
        for (int i= 0; i < itemLength ; i++) {
            p_item_view *item = (p_item_view *)malloc(sizeof(p_item_view));
            item->next = NULL;
            recvPacket->readU16(&item->itemTypeId);
            uint8_t data8;
            recvPacket->readU8(&data8);
            item->itemLevel = data8;
            recvPacket->readU8(&data8);
            item->itemRank = data8;
            recvPacket->readU16(&item->itemNum);
            
            if (head == NULL) {
               
                head= moveItem =item;
                
            }else {
                
                moveItem->next = item;
                moveItem = item;
                
            }
        }
        
        recvPacket->readU16(&itemLength);
        for (int i= 0; i < itemLength ; i++) {
            
            p_item_view *item = (p_item_view *)malloc(sizeof(p_item_view));
            item->next = NULL;
            recvPacket->readU16(&item->itemRank);
            recvPacket->readU16(&item->itemLevel);
            recvPacket->readU16(&item->itemTypeId);
            
            item->itemNum = -1;
            if (head == NULL) {
                head = moveItem =item;
                
            }else{
                
                moveItem->next = item;
                moveItem = item;
            }
                        
        }        
        unit->setIemList(head);
        
        uint16_t rewardlength;
        recvPacket->readU16(&rewardlength);
        for (int i = 0 ; i < rewardlength; i++) {
            
            MB_EventReward *reward = new MB_EventReward();
            unit->getReward()->addObject(reward);
            reward->release();
            reward->setIsPet(0);
            recvPacket->readU8(&data8);
            if(data8 == 1){
            
                reward->setItemType(COIN_ID);
                recvPacket->readU32(&data32);
                reward->setNum(data32);
                
            }else if(data8 == 2){
                
                reward->setItemType(GOLD_ID);
                recvPacket->readU32(&data32);
                reward->setNum(data32);
                
            }else if(data8 == 3){
                
                reward->setItemType(REPUTATION_ID);
                recvPacket->readU32(&data32);
                reward->setNum(data32);
                
            }else if(data8 == 4){
                
                reward->setItemType(ROLE_EXP_ID);
                recvPacket->readU32(&data32);
                reward->setNum(data32);
                
            }else if(data8 == 5){
                
                reward->setItemType(GER_EXP_ID);
                recvPacket->readU32(&data32);
                reward->setNum(data32);
                
            }else if(data8 == 6){
                
                recvPacket->readU16(&data16);
                reward->setItemType(data16);
                recvPacket->readU16(&data16);
                reward->setNum(data16);
                
            }else if(data8 == 7){
                
                recvPacket->readU16(&data16);
                reward->setItemType(data16);
                recvPacket->readU16(&data16);
                reward->setNum(data16);
                reward->setIsPet(1);
            }

            
            
        }
        
        data->getUnitList()->addObject(unit);
        unit->release();
    }
    int sdata;
    recvPacket->readU32(&sdata);
    data->setStartTime(sdata);
    recvPacket->readU32(&sdata);
    data->setStopTime(sdata);
    recvPacket->readU32(&data32);
    data->setTypeValue(data32);
    recvPacket->readU8(&data8);
    if(data8 == 1){
    
        data->setStopTime(-1);//是否永久
    
    }
    recvPacket->readU8(&data8);//是否每日刷新
    return true;
}

bool MB_MoneyEevntMgr::sendactivity_draw(uint16_t activityID,uint16_t drawID){
    
    SOCKET_REQUEST_START(CS_ACTIVITY_DRAW);
    packet->writeU16(activityID);
    packet->writeU16(drawID);
    SOCKET_REQUEST_END(SC_ACTIVITY_DRAW, MB_MoneyEevntMgr::onMsgRecv);
    return true;
}
bool MB_MoneyEevntMgr::recvactivity_draw(MB_MsgBuffer* recvPacket){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    recvPacket->readU8(&result);
    if(result == 1){
    

        uint16_t data16;
        recvPacket->readU16(&data16);
        MB_MoneyEevntData * data = getEventDataByActivityID(data16);
        if(data == NULL)return false;
        recvPacket->readU16(&data16);
        MB_MoneyEevntUnit * unit =  data->getUnitByID(data16);
        recvPacket->readU16(&data16);
        unit->setAlreadyDrawTimes(data16);
        recvPacket->readU16(&data16);
        unit->setCanDrawTimes(data16);
        
    }else {
    
        MB_Message::sharedMB_Message()->showMessage("领取失败");
    }

    return true;
}
MB_MoneyEventEnergy*  MB_MoneyEevntMgr::getEventEnergyByIndex(int index){
    
    return m_pEventEnergy[index];
}
bool  MB_MoneyEevntMgr::sendactivity_sign_emperor_info(){
    
    SOCKET_REQUEST_START(CS_ACTIVITY_SIGN_EMPEROR_INFO);
    SOCKET_REQUEST_END(SC_ACTIVITY_SIGN_EMPEROR_INFO, MB_MoneyEevntMgr);
    m_pSignEmperor->setLastRequestTime(time(NULL));
    return true;
}
bool  MB_MoneyEevntMgr::recvactivity_sign_emperor_info(MB_MsgBuffer* recvPacket){

    uint8_t data8;
    recvPacket->readU8(&data8);
    m_pSignEmperor->setIsSign(data8);
    recvPacket->readU8(&data8);
    m_pSignEmperor->setSignDay(data8);
    recvPacket->readU8(&data8);
    m_pSignEmperor->setisGetBox(data8);
    recvPacket->readU8(&data8);
    m_pSignEmperor->setIsEmperor(data8);

    char * str = recvPacket->ReadString();
    if(str){
    
        m_pSignEmperor->setEmperor(str);
        CC_SAFE_FREE(str);
        m_pSignEmperor->setIsHasEmperor(1);
    
    }else {
    
        m_pSignEmperor->setIsHasEmperor(0);
    }
    
    return true;
}
bool  MB_MoneyEevntMgr::sendactivity_sign_get_reward(){

    SOCKET_REQUEST_START(CS_ACTIVITY_SIGN_GET_REWARD);
    SOCKET_REQUEST_END(SC_ACTIVITY_SIGN_GET_REWARD, MB_MoneyEevntMgr);
    return true;
}
bool  MB_MoneyEevntMgr::recvactivity_sign_get_reward(MB_MsgBuffer* recvPacket){

    uint8_t result;
    recvPacket->readU8(&result);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if(result == 1){
     
        m_pSignEmperor->setisGetBox(1);
        
    }if(result == 2){
        
        MB_Message::sharedMB_Message()->showMessage("已领取过了");
        
    }else if(result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("未达到领取条件");
    }
    else if(result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("未知错误");
    }
    return true;
}
bool  MB_MoneyEevntMgr::sendactivity_sign_up(){
  
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_ACTIVITY_SIGN_UP);
    SOCKET_REQUEST_END(SC_ACTIVITY_SIGN_UP, MB_MoneyEevntMgr);
    return true;
}
bool  MB_MoneyEevntMgr::recvactivity_sign_up(MB_MsgBuffer* recvPacket){

    uint8_t result;
    recvPacket->readU8(&result);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if(result == 1){
    
        m_pSignEmperor->setIsSign(1);
        m_pSignEmperor->setSignDay(m_pSignEmperor->getSignDay() +1);
        
    }else  if(result == 2){
   
        MB_Message::sharedMB_Message()->showMessage("已签过到");
        
    }else if(result == 3){
    
        MB_Message::sharedMB_Message()->showMessage("未达到签到条件");
        
    }else if(result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("未知错误");
    }
    return true;
}

void MB_MoneyEevntMgr::addFunctionActivity(NSGameFunction::CCFunctionInterface* pFunction)
{
    if(std::find(m_pFunction2Activity.begin(), m_pFunction2Activity.end(), pFunction)==m_pFunction2Activity.end())
    {
        m_pFunction2Activity.push_back(pFunction);
    }
}

void MB_MoneyEevntMgr::removeFunctionActivity(NSGameFunction::CCFunctionInterface* pFunction)
{
    std::vector<NSGameFunction::CCFunctionInterface*>::iterator it = m_pFunction2Activity.begin();
    std::vector<NSGameFunction::CCFunctionInterface*>::iterator end = m_pFunction2Activity.end();
    while (it!=end)
    {
        if (*it == pFunction)
        {
            it = m_pFunction2Activity.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}