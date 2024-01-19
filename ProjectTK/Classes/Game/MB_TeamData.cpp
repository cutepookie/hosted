

#include "Game.h"
#include "MB_TeamData.h"
#include "MB_SceneGame.h"
#include "MB_LayerPetEquipment.h"
#include "MB_PetData.h"
#include "MB_LayerGuard.h"
static MB_TeamData* s_pTeamData = NULL; // pointer to singleton
/*
LieutenantData::LieutenantData(){
    
    m_nSpecialID = 0;
    m_nAtkID = 0;
    m_nHP = 0;
    m_nLock1 = 0;
    m_nLock2 = 0;
    m_nLock3 = 0;
    m_pEquip1 = NULL;
    m_pEquip2 = NULL;
    m_pEquip3 = NULL;
    m_pPet = NULL;
    m_nIsUlock = 0;
}
bool LieutenantData::isActive(){

    if(m_pPet == NULL){
    
        return false;
        
    }else {
    
        LiBoxTemlete * temp = MB_TeamData::getInstance()->getLiBoxTemleteByID(m_nSpecialID);
        if(temp == NULL){
        
            return false;
        }
        if(temp->getValue() == m_pPet->getPetTypeID()){
        
            return true;
        }
        
    }
    return false;
}
uint32_t LieutenantData::getFighterChange(){
    
    if(m_pPet != NULL)
    {
        return (MB_TeamData::getInstance()->getFightPowerToAddByFightPower(m_pPet->getPetFightPower()));
    }
    return  0;
}
LieutenantData::~LieutenantData(){
    
    CC_SAFE_RELEASE_NULL(m_pPet);
    CC_SAFE_RELEASE_NULL(m_pEquip1);
    CC_SAFE_RELEASE_NULL(m_pEquip2);
    CC_SAFE_RELEASE_NULL(m_pEquip3);
}


void LieutenantData::setPet(MB_PetData *data){
    
    CC_SAFE_RELEASE_NULL(m_pPet);
    m_pPet = data;
    CC_SAFE_RETAIN(m_pPet);
}
void LieutenantData::setEquip1(MB_ItemData *data){
    
    CC_SAFE_RELEASE_NULL( m_pEquip1);
    m_pEquip1 = data;
    CC_SAFE_RETAIN(m_pEquip1);
}

void LieutenantData::setEquip2(MB_ItemData *data){
    
    CC_SAFE_RELEASE_NULL(m_pEquip2);
    m_pEquip2 = data;
    CC_SAFE_RETAIN(m_pEquip2);
}
void LieutenantData::setEquip3(MB_ItemData *data){
    
    CC_SAFE_RELEASE_NULL( m_pEquip3);
    m_pEquip3 = data;
    CC_SAFE_RETAIN(m_pEquip3);
}
MB_PetData *LieutenantData::getPet(){
    
    return m_pPet;
}
MB_ItemData * LieutenantData::getEquip1(){
    
    return m_pEquip1;
}

MB_ItemData * LieutenantData::getEquip2(){
    
    return m_pEquip2;
}

MB_ItemData * LieutenantData::getEquip3(){
    
    return m_pEquip3;
}*/
MB_TeamData::MB_TeamData()
{
    //m_pLiData = CCArray::create();
    m_mapLiBox = CCArray::create();
    m_mapFightPower = CCArray::create();
    
    for (int i = 0; i < MEMBER_NUM; i++) {
        
        m_pTeamData[i] = new TeamDataStruct();
        m_pTeamData[i]->m_pPet = NULL;
        m_pTeamData[i]->m_pEquip1 = NULL;
        m_pTeamData[i]->m_pEquip2 = NULL;
        m_pTeamData[i]->m_pEquip3 = NULL;
        m_pTeamData[i]->m_pTreasure1 = NULL;
        m_pTeamData[i]->m_pTreasure2 = NULL;
        m_pTeamData[i]->m_pTreasure3 = NULL;
        m_pTeamData[i]->m_pTreasure4 = NULL;
        m_pTeamData[i]->m_pTreasure5 = NULL;
        m_pTeamData[i]->m_pTreasure6 = NULL;
        m_pTeamData[i]->m_pTreasure7 = NULL;
        m_pTeamData[i]->m_pTreasure8 = NULL;
//        LieutenantData *data = new LieutenantData();
//        m_pLiData->addObject(data);
//        data->release();
    }
    m_nFreeTimes = 0;
    CC_SAFE_RETAIN(m_mapLiBox);
    CC_SAFE_RETAIN(m_mapFightPower);
//    CC_SAFE_RETAIN(m_pLiData);
    m_nCurIndex = -1;
//    initLiboxTemplete();
//    initBoxes();
//    initBoxes2();
    initFightPowerToAddMap();
    SOCKET_MSG_REGIST(SC_GER_POS_LIST, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_POS_LIST , MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_INFO_LIST, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_TIE_INFO, MB_TeamData);
    SOCKET_MSG_REGIST(SC_GER_STANDUP, MB_TeamData);
    SOCKET_MSG_REGIST(SC_GER_MOVE_POS, MB_TeamData);
    SOCKET_MSG_REGIST(SC_GER_VIEW_OTHER, MB_TeamData);
    SOCKET_MSG_REGIST(SC_GER_REFRESH_POWER, MB_TeamData);
    SOCKET_MSG_REGIST(SC_GER_VIEW_OTHER_DTL, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_TEAM_VIEW_OTHER_DTL, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_UNTIE, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_STANDUP, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_MOVE_POS, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_LOCK_CLO, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_UNLOCK_CLO, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_REFRESH_CLO,MB_TeamData);
//    SOCKET_MSG_REGIST(SC_GER_LIEU_REFRESH_FREETIMES, MB_TeamData);
//    SOCKET_MSG_REGIST(SC_TEAM_VIEW_OTHER, MB_TeamData);

}

MB_TeamData::~MB_TeamData()
{
    for (int i = 0; i < MEMBER_NUM; i++) {
        
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pPet);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip1);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip2);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip3);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure1);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure2);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure3);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure4);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure5);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure6);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure7);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure8);
        CC_SAFE_DELETE(m_pTeamData[i]);
  
    }
    
//    m_pLiData->removeAllObjects();
//    CC_SAFE_RELEASE(m_pLiData);
    m_mapLiBox->removeAllObjects();
    CC_SAFE_RELEASE(m_mapLiBox);
    m_mapFightPower->removeAllObjects();
    CC_SAFE_RELEASE(m_mapFightPower);
    SOCKET_MSG_UNREGIST(SC_GER_REFRESH_POWER);
    SOCKET_MSG_UNREGIST(SC_GER_STANDUP);
    SOCKET_MSG_UNREGIST(SC_GER_MOVE_POS);
    SOCKET_MSG_UNREGIST(SC_GER_POS_LIST);
    SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER);
    SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER_DTL);
//    SOCKET_MSG_UNREGIST(SC_TEAM_VIEW_OTHER_DTL);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_POS_LIST);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_INFO_LIST);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_STANDUP);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_MOVE_POS);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_LOCK_CLO);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_UNLOCK_CLO);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_REFRESH_CLO);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_UNTIE);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_TIE_INFO);
//    SOCKET_MSG_UNREGIST(SC_GER_LIEU_REFRESH_FREETIMES);
//    SOCKET_MSG_UNREGIST(SC_TEAM_VIEW_OTHER);
}

MB_TeamData* MB_TeamData::getInstance()
{
    if (s_pTeamData == NULL)
    {
        s_pTeamData = new MB_TeamData();
    }
    
    return s_pTeamData;
}

void MB_TeamData::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pTeamData);
    s_pTeamData = NULL;
}

bool MB_TeamData::sendpet_standup(uint8_t petPos, uint64_t petID)
{
    
    SOCKET_REQUEST_START(CS_GER_STANDUP);
    packet->writeU8(petPos);
    packet->WriteUINT64(petID);
    SOCKET_REQUEST_END(SC_GER_STANDUP, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::sendpet_zhenxing(uint64_t petId1,uint64_t petId2,uint64_t petId3,uint64_t petId4,uint64_t petId5,uint64_t petId6,uint64_t equipId1,uint64_t equipId2,uint64_t equipId3,uint64_t equipId4,uint64_t equipId5,uint64_t equipId6)
{
    SOCKET_REQUEST_START(CS_GER_XIAZHEN);
    packet->WriteUINT64(petId1);
    packet->WriteUINT64(petId2);
    packet->WriteUINT64(petId3);
    packet->WriteUINT64(petId4);
    packet->WriteUINT64(petId5);
    packet->WriteUINT64(petId6);
    packet->WriteUINT64(equipId1);
    packet->WriteUINT64(equipId2);
    packet->WriteUINT64(equipId3);
    packet->WriteUINT64(equipId4);
    packet->WriteUINT64(equipId5);
    packet->WriteUINT64(equipId6);
    SOCKET_REQUEST_END(SC_GER_POS_LIST, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_standup(MB_MsgBuffer *recvPacket)
{
    uint8_t result = 0;
    MB_Message::removeALLMessage();
    if (recvPacket->readU8(&result))
    {
        if (result == 1)
        {
        
            uint8_t petPos;
            uint64_t petID;
            if (recvPacket->readU8(&petPos)
            && recvPacket->readU64(&petID))
            {
                petUpByPetID(petPos, petID);
            }
            //更新排序
            MB_PetMgr::getInstance()->sortPetDataArray();
            return true;
        }
        else
        {
            //TODODO 这里是精灵上阵限制条件
            MB_LOG("SC_GER_STANDUP errorcode:%d", result);
            if (result == 2) {
                MB_Message::sharedMB_Message()->showMessage("请求数据错误");
            }
            else if (result == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("该精灵不存在");
            }
            else if (result == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("不能上阵相同精灵");
            }
            else if (result == 5)
            {
                MB_Message::sharedMB_Message()->showMessage("经验卡牌不能上阵");
            }
            else if (result == 6)
            {
                MB_Message::sharedMB_Message()->showMessage("守护中已有相同精灵");
            }
        }
    }
    
    return false;
}


bool MB_TeamData::sendpet_move_pos(uint8_t petPos, uint8_t targetPos)
{
    
    SOCKET_REQUEST_START(CS_GER_MOVE_POS);
    packet->writeU8(petPos);
    packet->writeU8(targetPos);
    SOCKET_REQUEST_END(SC_GER_MOVE_POS, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_move_pos(MB_MsgBuffer *recvPacket)
{
    
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1)
    {
        uint8_t petPos, targetPos;
        
        if (recvPacket->readU8(&petPos)
            && recvPacket->readU8(&targetPos))
        {
            exchangePetPos(petPos, targetPos);
            //排序更新
            MB_PetMgr::getInstance()->sortPetDataArray();
            return true;
        }
        
    }
    else
    {
        MB_LOG("SC_GER_MOVE_POS errorcode:%d", result);
    }
    return false;
}

bool MB_TeamData::sendpet_pos_list()
{
    SOCKET_REQUEST_START(CS_GER_POS_LIST);
    SOCKET_REQUEST_END(SC_GER_POS_LIST, MB_TeamData::onMsgRecv);
    return true;
}
bool  MB_TeamData::recvpet_refresh_power(MB_MsgBuffer* recvPacket){

    uint8_t data8;
    uint64_t data64;
    uint16_t data16;
    recvPacket->readU16(&data16);
    for (int i = 0 ; i < data16; i++) {
        
        recvPacket->readU8(&data8);
        recvPacket->readU64(&data64);
        
        if(m_pTeamData[data8-1]->m_pPet != NULL){
        
            m_pTeamData[data8-1]->m_pPet->setPetFightPower(data64);
        }
    }
    return true;
}


TeamDataStruct* MB_TeamData::getTeamMemberByUID(uint64_t uid)
{
    for (int i = 0; i < MEMBER_NUM; i++)
    {
        if(m_pTeamData[i] && m_pTeamData[i]->m_pPet)
        {
            if(uid == m_pTeamData[i]->m_pPet->getPetID())
            {
                return m_pTeamData[i];
            }
        }
    }
    return NULL;
}


bool MB_TeamData::recvpet_pos_list(MB_MsgBuffer *recvPacket)
{
    uint16_t petNum, itemNum;
    uint64_t petID,itemUID;
    uint8_t petPos;
    
    for (int i = 0; i < MEMBER_NUM; i++) {
        
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pPet);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip1);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip2);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pEquip3);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure1);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure2);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure3);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure4);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure5);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure6);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure7);
        CC_SAFE_RELEASE_NULL(m_pTeamData[i]->m_pTreasure8);
    }
    
    recvPacket->readU16(&petNum);
    for (int i = 0; i < petNum; i++)
    {
        recvPacket->readU64(&petID);
        recvPacket->readU8(&petPos);
        //服务器是从1开始计数
        petPos--;
        m_pTeamData[petPos]->m_pPet = MB_PetMgr::getInstance()->getPetDataByUID(petID);
        if (m_pTeamData[petPos]->m_pPet != NULL)
        {
            m_pTeamData[petPos]->m_pPet->retain();
        }
        
        if (recvPacket->readU16(&itemNum))
        {
            for (int j = 0; j < itemNum; j++)
            {
                if (recvPacket->readU64(&itemUID))
                {
                    equipUpByItemUID(petPos, itemUID);
                }
            }
        }
        else
        {
            return false;
        }
    }
    
    //排序精灵列表,需要队伍信息,所以在这里排序
    MB_PetMgr::getInstance()->sortPetDataArray();
    
    if (global_layerPetEquipment!=NULL) {
        if (global_layerPetEquipment->toShowDetailPetUID!=0) {
            MB_ResWindow* layerDetail = MB_LayerPetDetail::createWithPetID(global_layerPetEquipment->toShowDetailPetUID);
            global_layerPetEquipment->setMyTouchEnable(false);
            global_layerPetEquipment->pushWindow(layerDetail,true);
            global_layerPetEquipment->toShowDetailPetUID = 0;
        }else if(global_layerPetEquipment->isToOnClickGHYSSH!=-1) {
            MB_LayerGuard* layer = MB_LayerGuard::create(global_layerPetEquipment->isToOnClickGHYSSH);
            if (layer != NULL){
                global_layerPetEquipment->pushWindow(layer, true);
            }
            global_layerPetEquipment->isToOnClickGHYSSH = -1;
        }
    }
    MB_Message::sharedMB_Message()->removeAllZuZhiMessage();
    return true;
}
/*
bool MB_TeamData::sendpet_lieu_refresh_freetimes(){
    
    SOCKET_REQUEST_START(CS_GER_LIEU_REFRESH_FREETIMES);
    SOCKET_REQUEST_END(SC_GER_LIEU_REFRESH_FREETIMES, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_lieu_refresh_freetimes(MB_MsgBuffer *recvPacket){

    recvPacket->readU16(&m_nFreeTimes);
    return true;
}
bool  MB_TeamData::sendpet_lieu_pos_list(){
    
    SOCKET_REQUEST_START(CS_GER_LIEU_POS_LIST);
    SOCKET_REQUEST_END(SC_GER_LIEU_POS_LIST, MB_TeamData::onMsgRecv);
    return true;
    
}
bool  MB_TeamData::recvpet_lieu_pos_list(MB_MsgBuffer* recvPacket){
    
    
    uint16_t petNum, itemNum;
    uint64_t petID,itemUID;
    uint8_t petPos;
    
    for (int i = 0; i < MEMBER_NUM; i++) {
        
        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(i);
        data->setPet(NULL);
        data->setEquip1(NULL);
        data->setEquip2(NULL);
        data->setEquip3(NULL);
        data->setAtkID(0);
        data->setHP(0);
        data->setSpecialID(0);
    }
    recvPacket->readU16(&petNum);
    for (int i = 0; i < petNum; i++)
    {
        recvPacket->readU64(&petID);
        recvPacket->readU8(&petPos);
        //服务器是从1开始计数
        petPos--;
        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
        data->setPet(MB_PetMgr::getInstance()->getPetDataByUID(petID));
        if (recvPacket->readU16(&itemNum))
        {
            for (int j = 0; j < itemNum; j++)
            {
                if (recvPacket->readU64(&itemUID))
                {
                    equipUpLiByItemUID(petPos, itemUID);
                }
            }
        }
        else
        {
            return false;
        }
    }
    
    //排序精灵列表,需要队伍信息,所以在这里排序
    MB_PetMgr::getInstance()->sortPetDataArray();
    return false;
}
bool MB_TeamData::sendpet_lieu_info_list(){

    SOCKET_REQUEST_START(CS_GER_LIEU_INFO_LIST);
    SOCKET_REQUEST_END(SC_GER_LIEU_INFO_LIST, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_lieu_info_list(MB_MsgBuffer* recvPacket){

    uint16_t numLock;
    uint8_t petPos;
    uint16_t specialID;
    uint8_t  isLock1;
    uint16_t attAddID;
    uint8_t  isLock2;
    uint16_t hpAddID;
    uint8_t  isLock3;
    
    recvPacket->readU16(&numLock);
    for (int i = 0; i < numLock; i++ ) {
        
        recvPacket->readU8(&petPos);
        recvPacket->readU16(&specialID);
        recvPacket->readU8(&isLock1);
        recvPacket->readU16(&attAddID);
        recvPacket->readU8(&isLock2);
        recvPacket->readU16(&hpAddID);
        recvPacket->readU8(&isLock3);
        petPos--;
        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
        data->setSpecialID(specialID);
        data->setHP(hpAddID);
        data->setAtkID(attAddID);
        data->setLock1(isLock1);
        data->setLock2(isLock2);
        data->setLock3(isLock3);
    }
    
    return true;
}
bool MB_TeamData::sendpet_lieu_standup(uint8_t petPos, uint64_t petID){

    SOCKET_REQUEST_START(CS_GER_LIEU_STANDUP);
    packet->writeU8(petPos);
    packet->WriteUINT64(petID);
    SOCKET_REQUEST_END(SC_GER_LIEU_STANDUP, MB_TeamData::onMsgRecv);
    return true;

}
bool MB_TeamData::recvpet_lieu_standup(MB_MsgBuffer* recvPacket){

    uint8_t result = 0;
    MB_Message::removeALLMessage();
    if (recvPacket->readU8(&result))
    {
        if (result == 1)
        {
 
            uint8_t petPos;
            uint64_t petID;
            if (recvPacket->readU8(&petPos)
                && recvPacket->readU64(&petID))
            {
                petUpLiByPetID(petPos, petID);
            }
            //更新排序
            MB_PetMgr::getInstance()->sortPetDataArray();
            return true;
        }
        else
        {
            MB_LOG("SC_GER_STANDUP errorcode:%d", result);
            if (result == 2) {
                MB_Message::sharedMB_Message()->showMessage("请求数据错误");
            }
            else if (result == 3)
            {
                MB_Message::sharedMB_Message()->showMessage("该精灵不存在");
            }
            else if (result == 4)
            {
                MB_Message::sharedMB_Message()->showMessage("不能上阵相同精灵");
            
            } else if (result == 5)
            {
                MB_Message::sharedMB_Message()->showMessage("副将未解锁");
            }
            
        }
    }
    
    return false;
}

bool MB_TeamData::sendpet_lieu_untie(uint8_t petPos){

    SOCKET_REQUEST_START(CS_GER_LIEU_UNTIE);
    packet->writeU8(petPos);
    SOCKET_REQUEST_END(SC_GER_LIEU_UNTIE, MB_LayerResultPVPRanking);
    return true;
}
bool MB_TeamData::recvpet_lieu_untie(MB_MsgBuffer * recvPacket){
   
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    recvPacket->readU8(&result);
    if(result == 1){
        
        MB_Message::sharedMB_Message()->removeALLMessage();
        uint8_t petPos;
        uint16_t specialID;
        uint8_t  isLock1;
        uint16_t attAddID;
        uint8_t  isLock2;
        uint16_t hpAddID;
        uint8_t  isLock3;
        uint16_t length;
        
        recvPacket->readU16(&length);
        for (int i = 0; i < length ; i++) {
            
            recvPacket->readU8(&petPos);
            recvPacket->readU16(&specialID);
            recvPacket->readU8(&isLock1);
            recvPacket->readU16(&attAddID);
            recvPacket->readU8(&isLock2);
            recvPacket->readU16(&hpAddID);
            recvPacket->readU8(&isLock3);
            petPos--;
            LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
            data->setSpecialID(specialID);
            data->setHP(hpAddID);
            data->setAtkID(attAddID);
            data->setLock1(isLock1);
            data->setLock2(isLock2);
            data->setLock3(isLock3);
            data->setIsUlock(1);
            data->setPet(NULL);
       
        }

        
    }else {
    
    
        if (result == 2) {
          
            MB_Message::sharedMB_Message()->showMessage("等级不足");
        }
        else if (result == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("消耗品不足");
        }
        else if (result == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("未知错误");
            
        }else {
        
            CCLog("untie error %d",result);
        }

    }
    return true;
}
bool MB_TeamData::sendpet_lieu_move_pos(uint8_t petPos, uint8_t targetPos){

    if(petPos <= 0 || targetPos <= 0){
    
        MB_Message::sharedMB_Message()->removeALLMessage();
        return false;
    }
    
    SOCKET_REQUEST_START(CS_GER_LIEU_MOVE_POS);
    packet->writeU8(petPos);
    packet->writeU8(targetPos);
    SOCKET_REQUEST_END(SC_GER_LIEU_MOVE_POS, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_lieu_move_pos(MB_MsgBuffer *recvPacket){

    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1)
    {
        uint8_t petPos, targetPos;
        
        if (recvPacket->readU8(&petPos)
            && recvPacket->readU8(&targetPos))
        {
            exchangeLiPetPos(petPos, targetPos);
            //排序更新
            MB_PetMgr::getInstance()->sortPetDataArray();
            return true;
        }
        
    }
    else
    {
        MB_LOG("SC_GER_MOVE_POS errorcode:%d", result);
    }
    return false;
}
bool MB_TeamData::sendpet_lieu_lock_clo(uint8_t petPos, uint8_t num){

    SOCKET_REQUEST_START(CS_GER_LIEU_LOCK_CLO);
    packet->writeU8(petPos);
    packet->writeU8(num);
    m_pNowLockOpPos = petPos;
    m_pNowLockOpNum = num;
    SOCKET_REQUEST_END(SC_GER_LIEU_LOCK_CLO, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_lieu_lock_clo(MB_MsgBuffer *recvPacket){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    recvPacket->readU8(&result);
    if(result == 1){
        
        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(--m_pNowLockOpPos);
        
        if (m_pNowLockOpNum == 1) {
            
           data->setLock1(1);
            
        }else if (m_pNowLockOpNum == 2){
       
           data->setLock2(1);
            
        }else if (m_pNowLockOpNum == 3){
        
            data->setLock3(1);
        }
        return  true;
        
    }else if(result == 2){
    
        MB_Message::sharedMB_Message()->showMessage("该格子已锁定");
        
    }else if(result == 3){
    
        MB_Message::sharedMB_Message()->showMessage("该格子未解锁");
        
    }else if(result == 4){
    
        MB_Message::sharedMB_Message()->showMessage("资源不足, 无法锁定");
        
    }else if(result == 5){
    
        MB_Message::sharedMB_Message()->showMessage("不能锁定更多的格子");

    }else {
    
        CCLog("recvpet_lieu_lock_clo errorcode %d",result);
    }
    return false;
}
bool MB_TeamData::sendpet_lieu_unlock_clo(uint8_t petPos, uint8_t num){

    SOCKET_REQUEST_START(CS_GER_LIEU_UNLOCK_CLO);
    packet->writeU8(petPos);
    packet->writeU8(num);
    m_pNowLockOpPos = petPos;
    m_pNowLockOpNum = num;
    SOCKET_REQUEST_END(SC_GER_LIEU_UNLOCK_CLO, MB_TeamData::onMsgRecv);
    return true;
}
bool MB_TeamData::recvpet_lieu_unlock_clo(MB_MsgBuffer *recvPacket){

    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    recvPacket->readU8(&result);
    if(result == 1){
        
        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(--m_pNowLockOpPos);
        if (m_pNowLockOpNum == 1) {
            
            data->setLock1(0);
            
        }else if (m_pNowLockOpNum == 2){
            
            data->setLock2(0);
            
        }else if (m_pNowLockOpNum == 3){
            
            data->setLock3(0);
        }
        
        return  true;
        
    }else if(result == 2){
        
        MB_Message::sharedMB_Message()->showMessage("该格子未锁定");
        
    }else if(result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("该格子未解锁");
        
    }else if(result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("未知错误");
        
    }else {
        
        CCLog("recvpet_lieu_unlock_clo errorcode %d",result);
    }
    return false;
}
bool MB_TeamData::sendpet_lieu_refresh_clo(uint8_t petPos){

    SOCKET_REQUEST_START(CS_GER_LIEU_REFRESH_CLO);
    packet->writeU8(petPos);
    SOCKET_REQUEST_END(SC_GER_LIEU_REFRESH_CLO, MB_TeamData::onMsgRecv);
    return true;
}
*/
//bool MB_TeamData::getIsLockedByValue(uint8_t index,uint16_t value)
//{
//    LieutenantData * data = getLiMemberByIndex(index);
//    LiBoxTemlete *box = NULL;
//    if(data->getLock2()!=1)// 未锁定
//    {
//        box = getLiBoxTemleteByID(data->getAtkID());
//        if(box->getValue()>=value)
//        {
//            return true;
//        }
//    }
//    if(data->getLock3()!=1)
//    {
//        box = getLiBoxTemleteByID(data->getHP());
//        if(box->getValue()>=value)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//bool MB_TeamData::getUp4StarIsLocked(uint8_t index)
//{
//    static const uint16_t value = 1800;
//    return getIsLockedByValue(index,value);
//}
//bool MB_TeamData::recvpet_lieu_refresh_clo(MB_MsgBuffer *recvPacket){
//
//    MB_Message::sharedMB_Message()->removeALLMessage();
//    uint8_t result;
//    recvPacket->readU8(&result);
//    if(result == 1){
//    
//        uint8_t petPos;
//        uint16_t specialID;
//        uint8_t  isLock1;
//        uint16_t attAddID;
//        uint8_t  isLock2;
//        uint16_t hpAddID;
//        uint8_t  isLock3;
//        recvPacket->readU8(&petPos);
//        recvPacket->readU16(&specialID);
//        recvPacket->readU8(&isLock1);
//        recvPacket->readU16(&attAddID);
//        recvPacket->readU8(&isLock2);
//        recvPacket->readU16(&hpAddID);
//        recvPacket->readU8(&isLock3);
//        petPos--;
//        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
//        data->setSpecialID(specialID);
//        data->setHP(hpAddID);
//        data->setAtkID(attAddID);
//        data->setLock1(isLock1);
//        data->setLock2(isLock2);
//        data->setLock3(isLock3);
//        if(m_nFreeTimes > 0){
//        
//            m_nFreeTimes--;
//        }
//        return  true;
//    
//    }else if(result == 2) {
//    
//         MB_Message::sharedMB_Message()->showMessage("未解锁该副将");
//        
//    }else if(result == 3) {
//        
//         MB_Message::sharedMB_Message()->showMessage("消耗品不足");
//        
//    }else {
//    
//        CCLog("SC_GER_LIEU_REFRESH_CLO erroe code unknow %d",result);
//    }
//    return false;
//}
//bool MB_TeamData::sendpet_lieu_tie_info(){
//
//    SOCKET_REQUEST_START(CS_GER_LIEU_TIE_INFO);
//    SOCKET_REQUEST_END(SC_GER_LIEU_TIE_INFO, MB_TeamData::onMsgRecv);
//    return true;
//}
//bool MB_TeamData::recvpet_lieu_tie_info(MB_MsgBuffer *recvPacket){
//
//    uint16_t data16;
//    uint8_t pos;
//    recvPacket->readU16(&data16);
//    
//    for (int i = 0 ; i < data16; i++) {
//    
//        recvPacket->readU8(&pos);
//        pos--;
//        LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(pos);
//        data->setIsUlock(1);
//
//    }
//    return true;
//}

bool MB_TeamData::sendpet_view_other(uint32_t roleID,uint16_t serverid)
{
    MB_Message::sharedMB_Message()->showMessage("",10);
    SOCKET_REQUEST_START(CS_GER_VIEW_OTHER);
    packet->writeU32(roleID);
    packet->writeU16(serverid);
    m_nLastServerID = serverid;
    SOCKET_REQUEST_END(SC_GER_VIEW_OTHER, MB_LayerResultPVPRanking);
    return true;
}

bool MB_TeamData::recvpet_view_other(MB_MsgBuffer *recvPacket)
{
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    MB_DataTeamCompare* dataTeamCompare = new MB_DataTeamCompare();
    
    if (recvPacket->readU32(&data32)) {
        dataTeamCompare->setRoleID(data32);
    }
    
    char* roleName = recvPacket->ReadString();
    if (roleName != NULL) {
        dataTeamCompare->setRoleName(roleName);
    }
    CC_SAFE_FREE(roleName);
    
    if (recvPacket->readU16(&data16)) {
        dataTeamCompare->setRoleLevel(data16);
    }
    
    if (recvPacket->readU64(&data64)) {
        dataTeamCompare->setRoleFightPower(data64);
    }
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    for (int i = 0; i < count; ++i) {
        MB_PetData* petData = new MB_PetData();
        if (recvPacket->readU16(&data16)) {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetTypeID(data16);
        }
        dataTeamCompare->getTeamArray()->addObject(petData);
        petData->release();
    }
    //打开队伍比较界面
    if (global_sceneGame==NULL) {
        CCDirector::sharedDirector()->getRunningScene()->addChild(MB_SceneTeamCompare::scene(dataTeamCompare));
    }else
    {
        global_sceneGame->addChild(MB_SceneTeamCompare::scene(dataTeamCompare),999);
    }
    CC_SAFE_RELEASE(dataTeamCompare);
    return true;
}

bool MB_TeamData::equipUpByItemUID(uint8_t petPos, uint64_t itemUID)
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(itemUID);
    
    if (itemData == NULL || petPos >= MEMBER_NUM) {
        MB_LOG("equipUpByItemUID failed. petPos:%d itemUID:%llu",petPos, itemUID);
        return false;
    }
    
    uint8_t itemPos = itemData->getItemPos();
    
    if (itemPos == kItemPosEquip1)
    {
        if (m_pTeamData[petPos]->m_pEquip1 != NULL) {
            m_pTeamData[petPos]->m_pEquip1->release();
        }
        m_pTeamData[petPos]->m_pEquip1 = itemData;
        itemData->retain();
    }
    else if (itemPos == kItemPosEquip2)
    {
        if (m_pTeamData[petPos]->m_pEquip2 != NULL) {
            m_pTeamData[petPos]->m_pEquip2->release();
        }
        m_pTeamData[petPos]->m_pEquip2 = itemData;
        itemData->retain();
    }
    else if (itemPos == kItemPosEquip3)
    {
        if (m_pTeamData[petPos]->m_pEquip3 != NULL) {
            m_pTeamData[petPos]->m_pEquip3->release();
        }
        m_pTeamData[petPos]->m_pEquip3 = itemData;
        itemData->retain();
    }
    else if (itemPos >= kItemPosTreasure1 && itemPos <=kItemPosTreasure8)
    {
        if (canEquipTreasure(petPos, itemPos, itemUID))
        {
            if (itemPos == kItemPosTreasure1)
            {
                if (m_pTeamData[petPos]->m_pTreasure1 != NULL) {
                    m_pTeamData[petPos]->m_pTreasure1->release();
                }
                m_pTeamData[petPos]->m_pTreasure1 = itemData;
                itemData->retain();
            }
            else if (itemPos == kItemPosTreasure2)
            {
                if (m_pTeamData[petPos]->m_pTreasure2 != NULL) {
                    m_pTeamData[petPos]->m_pTreasure2->release();
                }
                m_pTeamData[petPos]->m_pTreasure2 = itemData;
                itemData->retain();
            }
            else if (itemPos == kItemPosTreasure3)
            {
                if (m_pTeamData[petPos]->m_pTreasure3 != NULL) {
                    m_pTeamData[petPos]->m_pTreasure3->release();
                }
                m_pTeamData[petPos]->m_pTreasure3 = itemData;
                itemData->retain();
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else
    {
        MB_LOG("item equip position unkown, itemPos:%d petPos:%d",itemPos, petPos);
        return false;
    }
    
    return true;
}

bool MB_TeamData::equipDownByItemUID(uint8_t petPos, uint64_t itemUID)
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(itemUID);
    
    if (itemData == NULL || petPos >= MEMBER_NUM) {
        MB_LOG("equipUpByItemUID failed. petPos:%d itemUID:%llu",petPos, itemUID);
        return false;
    }
    
    uint8_t itemPos = itemData->getItemPos();
    
    if (itemPos == kItemPosEquip1)
    {
        if (m_pTeamData[petPos]->m_pEquip1 != NULL) {
            
            m_pTeamData[petPos]->m_pEquip1->release();
        }
        m_pTeamData[petPos]->m_pEquip1 = NULL;
    }
    else if (itemPos == kItemPosEquip2)
    {
        if (m_pTeamData[petPos]->m_pEquip2 != NULL) {
            m_pTeamData[petPos]->m_pEquip2->release();
        }
        m_pTeamData[petPos]->m_pEquip2 = NULL;
    }
    else if (itemPos == kItemPosEquip3)
    {
        if (m_pTeamData[petPos]->m_pEquip3 != NULL) {
            m_pTeamData[petPos]->m_pEquip3->release();
        }
        m_pTeamData[petPos]->m_pEquip3 = NULL;
    }
    else if (itemPos == kItemPosTreasure1)
    {
        if (m_pTeamData[petPos]->m_pTreasure1 != NULL) {
            m_pTeamData[petPos]->m_pTreasure1->release();
        }
        m_pTeamData[petPos]->m_pTreasure1 = NULL;
    }
    else if (itemPos == kItemPosTreasure2)
    {
        if (m_pTeamData[petPos]->m_pTreasure2 != NULL) {
            m_pTeamData[petPos]->m_pTreasure2->release();
        }
        m_pTeamData[petPos]->m_pTreasure2 = NULL;
    }
    else if (itemPos == kItemPosTreasure3)
    {
        if (m_pTeamData[petPos]->m_pTreasure3 != NULL) {
            m_pTeamData[petPos]->m_pTreasure3->release();
        }
        m_pTeamData[petPos]->m_pTreasure3 = NULL;
    }
    else
    {
        MB_LOG("item equip position unkown, itemPos:%d petPos:%d",itemPos, petPos);
        return false;
    }
    
    return true;
}

bool MB_TeamData::petUpByPetID(uint8_t petPos, uint64_t petID)
{
    //服务器从1计数
    petPos--;
    
    //替换精灵
    if (m_pTeamData[petPos]->m_pPet != NULL)
    {
        //下阵精灵修改血量公攻击力
        MB_PetData* petData = m_pTeamData[petPos]->m_pPet;
        MB_PetTemplate* templete = MB_PetMgr::getInstance()->getPetTemplateByID(petData->getPetTypeID());
        if(templete != NULL){
            
            petData->setPetAttack(MB_PetMgr::getInstance()->calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
            petData->setPetHpMax(MB_PetMgr::getInstance()->calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
        }
        CC_SAFE_RELEASE_NULL(m_pTeamData[petPos]->m_pPet);
    }
    m_pTeamData[petPos]->m_pPet = MB_PetMgr::getInstance()->getPetDataByUID(petID);
    m_pTeamData[petPos]->m_pPet->retain();
    
    //装备ID改到新精灵身上
    if (m_pTeamData[petPos]->m_pEquip1 != NULL)
    {
        m_pTeamData[petPos]->m_pEquip1->setItemPetID(petID);
    }
    if (m_pTeamData[petPos]->m_pEquip2 != NULL) {
        m_pTeamData[petPos]->m_pEquip2->setItemPetID(petID);
    }
    if (m_pTeamData[petPos]->m_pEquip3 != NULL) {
        m_pTeamData[petPos]->m_pEquip3->setItemPetID(petID);
    }
    if (m_pTeamData[petPos]->m_pTreasure1 != NULL) {
        m_pTeamData[petPos]->m_pTreasure1->setItemPetID(petID);
    }
    if (m_pTeamData[petPos]->m_pTreasure2 != NULL) {
        m_pTeamData[petPos]->m_pTreasure2->setItemPetID(petID);
    }
    if (m_pTeamData[petPos]->m_pTreasure3 != NULL) {
        m_pTeamData[petPos]->m_pTreasure3->setItemPetID(petID);
    }
    return true;
}

bool MB_TeamData::exchangePetPos(uint8_t petPos, uint8_t targetPos)
{
    petPos--;
    targetPos--;
    TeamDataStruct* teamDS = m_pTeamData[petPos];
    m_pTeamData[petPos] = m_pTeamData[targetPos];
    m_pTeamData[targetPos] = teamDS;
    return true;
}

uint8_t MB_TeamData::getPetPosByPetID(uint64_t petID)
{
    for (int i = 0; i < MEMBER_NUM; i++) {
       
        if (m_pTeamData[i]->m_pPet != NULL && m_pTeamData[i]->m_pPet->getPetID() == petID)
        {
            return i;
        }
    }
//    MB_LOG("getPetPosByPetID failed.");
    return MEMBER_NUM;
}

bool MB_TeamData::canEquipTreasure(uint8_t petPos, uint8_t itemPos, uint64_t itemUID)
{
    MB_ItemData* treasure = MB_ItemMgr::getInstance()->getEquipByUID(itemUID);  //yuanwugang 
    if (treasure == NULL) {
        MB_LOG("no exist treasure. itemUID:%llu", itemUID);
        return false;
    }
    
//    uint8_t treasureItemType = MB_ItemMgr::getInstance()->getItemTemplateByID(treasure->getItemID())->getItemType();
//    uint32_t itemID;
//    uint8_t itemType;
//    if (m_pTeamData[petPos]->m_pTreasure1 != NULL && itemPos != kItemPosTreasure1)
//    {
//        itemID = m_pTeamData[petPos]->m_pTreasure1->getItemID();
//        itemType = MB_ItemMgr::getInstance()->getItemTemplateByID(itemID)->getItemType();
//        if (itemType == treasureItemType)
//        {
//            MB_LOG("same treasure type equiped, itemType:%d, itemPos:%d", itemType, itemPos);
//            return false;
//        }
//        
//    }
//    if (m_pTeamData[petPos]->m_pTreasure2 != NULL && itemPos != kItemPosTreasure2)
//    {
//        itemID = m_pTeamData[petPos]->m_pTreasure2->getItemID();
//        itemType = MB_ItemMgr::getInstance()->getItemTemplateByID(itemID)->getItemType();
//        if (itemType == treasureItemType)
//        {
//            MB_LOG("same treasure type equiped, itemType:%d, itemPos:%d", itemType, itemPos);
//            return false;
//        }
//        
//    }
//    if (m_pTeamData[petPos]->m_pTreasure3 != NULL && itemPos != kItemPosTreasure3)
//    {
//        itemID = m_pTeamData[petPos]->m_pTreasure3->getItemID();
//        itemType = MB_ItemMgr::getInstance()->getItemTemplateByID(itemID)->getItemType();
//        if (itemType == treasureItemType)
//        {
//            MB_LOG("same treasure type equiped, itemType:%d, itemPos:%d", itemType, itemPos);
//            return false;
//        }
//        
//    }
    
    return true;
}


uint64_t MB_TeamData::getFightPower()
{
    uint64_t fightPower = 0;
    for (int i = 0; i < MEMBER_NUM; ++i) {
        if (m_pTeamData[i]->m_pPet != NULL) {
            
            fightPower += m_pTeamData[i]->m_pPet->getPetFightPower();
        }
    }
    return fightPower;
}
bool MB_TeamData::sendpet_view_other_dtl(uint32_t roleID,uint16_t serverid){
    
    MB_Message::sharedMB_Message()->showMessage("",30);
    SOCKET_REQUEST_START(CS_GER_VIEW_OTHER_DTL);
    packet->writeU32(roleID);
    packet->writeU16(serverid);
    SOCKET_REQUEST_END(SC_GER_VIEW_OTHER_DTL, MB_TeamData::onMsgRecv);    
    return true;
}
//bool MB_TeamData::sendteam_view_other_dtl(uint32_t roleID)
//{
//    MB_Message::sharedMB_Message()->showMessage("",30);
//    SOCKET_REQUEST_START(CS_TEAM_VIEW_OTHER_DTL);
//    packet->writeU32(roleID);
//    SOCKET_REQUEST_END(SC_TEAM_VIEW_OTHER_DTL, MB_TeamData::onMsgRecv);
//    return true;
//}
bool MB_TeamData::recvpet_view_other_dtl(MB_MsgBuffer* recvPacket){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    return true;
}
bool MB_TeamData::recvteam_view_other_dtl(MB_MsgBuffer* recvPacket){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    return true;
}


void MB_TeamData::senditem_up_all_equip(uint64_t uid)
{
    SOCKET_REQUEST_START(CS_ITEM_UP_ALL_EQUIP);
    packet->WriteUINT64(uid);
    SOCKET_REQUEST_END(SC_ITEM_UP_ALL_EQUIP, MB_TeamData::onMsgRecv);
}
void MB_TeamData::onMsgRecv(CCNode* node, SocketResponse* response)
{
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
            
        case SC_GER_POS_LIST:
            recvpet_pos_list(recvPacket);
            break;
        case SC_GER_MOVE_POS:
            recvpet_move_pos(recvPacket);
            break;
        case SC_GER_STANDUP:
            recvpet_standup(recvPacket);
            break;
        case SC_GER_VIEW_OTHER:
            recvpet_view_other(recvPacket);
            break;
        case SC_GER_REFRESH_POWER:
            recvpet_refresh_power(recvPacket);
            break;
        case SC_GER_VIEW_OTHER_DTL:
            recvpet_view_other_dtl(recvPacket);
            break;
//        case SC_TEAM_VIEW_OTHER_DTL:
//            recvteam_view_other_dtl(recvPacket);
//            break;
//        case SC_GER_LIEU_POS_LIST:
//            recvpet_lieu_pos_list(recvPacket);
//            break;
//        case SC_GER_LIEU_INFO_LIST:
//            recvpet_lieu_info_list(recvPacket);
//            break;
//        case SC_GER_LIEU_STANDUP:
//            recvpet_lieu_standup(recvPacket);
//            break;
//        case SC_GER_LIEU_UNTIE:
//            recvpet_lieu_untie(recvPacket);
//            break;
//        case SC_GER_LIEU_MOVE_POS:
//            recvpet_lieu_move_pos(recvPacket);
//            break;
//        case SC_GER_LIEU_LOCK_CLO:
//            recvpet_lieu_lock_clo(recvPacket);
//            break;
//        case SC_GER_LIEU_UNLOCK_CLO:
//            recvpet_lieu_unlock_clo(recvPacket);
//            break;
//        case SC_GER_LIEU_REFRESH_CLO:
//            recvpet_lieu_refresh_clo(recvPacket);
//            break;
//        case SC_GER_LIEU_TIE_INFO:
//            recvpet_lieu_tie_info(recvPacket);
//            break;
//        case SC_GER_LIEU_REFRESH_FREETIMES:
//            recvpet_lieu_refresh_freetimes(recvPacket);
//            break;
//        case SC_TEAM_VIEW_OTHER:
//            recvteam_view_other(recvPacket);
//            break;
        default:
            break;
    }

}

int MB_TeamData::getLimitLevelByIndex(int index)
{
    if (index == 0)
    {
        return 1;
    }
    else if (index == 1)
    {
        return 2;
    }
    else if (index == 2)
    {
        return 5;
    }
    else if (index == 3)
    {
        return 10;
    }
    else if (index == 4)
    {
        return 20;
    }
    else if (index == 5)
    {
        return 30;
    }
    else
    {
        return 99;
    }
}
int MB_TeamData::getLimitPet(){
    
    int level = MB_RoleData::getInstance()->getLevel();
    return getLimitPetByLevel(level);
}
int MB_TeamData::getEmptyCount()
{
    int count = 0;
    for (int i = 0; i < MEMBER_NUM; ++i)
    {
        if(m_pTeamData[i]->m_pPet)
        {
            ++count;
        }
    }
    return getLimitPetByLevel(MB_RoleData::getInstance()->getLevel()) - count;
}
int MB_TeamData::getLimitPetByLevel(int level){

     
   if(level >= 25 ){
        
        return 6;
   
   }else if(level >= 20){
       
       return 5;
       
   } else if(level >= 10 ){
       
       return 4;
       
   }else {
       
       return 3;
       
   }
}
TeamDataStruct* MB_TeamData::checkInTeamData(MB_PetData *data){
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        TeamDataStruct * team = getTeamMemberByIndex(i);
        if (team->m_pPet != NULL && team->m_pPet->getPetID() == data->getPetID() ) {
            return team;
        }
    }
    return NULL;
}
bool MB_TeamData::checkInTeam(MB_PetData *data){
    
    
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        
        TeamDataStruct * team = getTeamMemberByIndex(i);
        
        if (team->m_pPet != NULL && team->m_pPet->getPetID() == data->getPetID() ) {
            
            return true;
        }
    }
    return false;
}
bool MB_TeamData::checkInTeam(uint64_t petID){
    for (int i = 0 ; i < CARD_IN_GAME ; i++) {
        
        TeamDataStruct * team = getTeamMemberByIndex(i);
        
        if (team->m_pPet != NULL && team->m_pPet->getPetID() == petID) {
            
            return true;
        }
    }
    return false;
}
bool MB_TeamData::isTeamNone(){
    
    int  count = 0;
    for (int i= 0; i<CARD_IN_GAME; i++) {
        
        if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet == NULL) {
            
            count++;
        }
        
    }
    if(count == 6){
        
        MB_Message::sharedMB_Message()->showMessage("不能战斗", "没有安排队伍","确定",NULL,NULL,NULL,NULL, NULL);
        
        return true;
    }
    return  false;
    
}

uint64_t MB_TeamData::getSelectPetID()
{
    if (m_nCurIndex == -1) {
        
        for (int i = 0; i < CARD_IN_GAME; i++) {
            if (m_pTeamData[i]->m_pPet != NULL) {
                
                m_nCurIndex = i;
                break;
            }
        }
    }
    CCAssert(m_nCurIndex > -1, "");
    
    MB_PetData* petData = getTeamMemberByIndex(m_nCurIndex)->m_pPet;
    if (petData != NULL) {
        
        return petData->getPetID();
    }
    else
    {
        MB_LOG("choose no exist pet index:%d",m_nCurIndex);
        for (int i = 0; i < CARD_IN_GAME; i++) {
            
            petData = getTeamMemberByIndex(i)->m_pPet;
            if (petData != NULL) {
                
                return petData->getPetID();
            }
        }
    }
    
    return -1;
}
//void MB_TeamData::initLiboxTemplete(){
//
//    
//    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/LiBoxTemlete.xml");
//    if (!g_sharedDoc)
//    {
//       
//        return ;
//    }
//    
//    xmlNodePtr root;
//    root=xmlDocGetRootElement(g_sharedDoc);
//    xmlNodePtr curNode = root->xmlChildrenNode;
//    char* value;
//    while(curNode != NULL) {
//        
//        if (xmlStrcmp(curNode->name,BAD_CAST "libox")) {
//            
//            curNode = curNode->next;
//            continue;
//        }
//        struct _xmlAttr * attr = curNode->properties;
//        if (attr != NULL) {
//            
//            LiBoxTemlete * tempData = new LiBoxTemlete();
//            for (; attr != NULL; attr = attr->next ) {
//                
//                if (!xmlStrcmp(attr->name,BAD_CAST "liid"))
//                {
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setID(atoi(value));
//                    CC_SAFE_FREE(value);
//                    
//                }else if (!xmlStrcmp(attr->name,BAD_CAST "type")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setType(atoi(value));
//                    CC_SAFE_FREE(value);
//                    
//                }else if (!xmlStrcmp(attr->name,BAD_CAST "name")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setName(value);
//                    CC_SAFE_FREE(value);
//                    
//                }else if (!xmlStrcmp(attr->name,BAD_CAST "icon")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setIcon(value);
//                    CC_SAFE_FREE(value);
//                }else if (!xmlStrcmp(attr->name,BAD_CAST "star")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setStar(atoi(value));
//                    CC_SAFE_FREE(value);
//                }else if (!xmlStrcmp(attr->name,BAD_CAST "value")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    tempData->setValue(atoi(value));
//                    CC_SAFE_FREE(value);
//                }                
//            }
//            m_mapLiBox->addObject(tempData);
//            tempData->release();
//        }
//        else
//        {
//            MB_LOG("Error:empty libox in templete.");
//        }
//        
//        curNode = curNode->next;
//    }
//    
//    xmlFreeDoc(g_sharedDoc);
//}
//void MB_TeamData::initBoxes(){
//    
//    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/pet_assistant.xml");
//    if (!g_sharedDoc)
//    {
//        return ;
//    }
//    xmlNodePtr root;
//    root=xmlDocGetRootElement(g_sharedDoc);
//    xmlNodePtr curNode = root->xmlChildrenNode;
//    char* value;
//    while(curNode != NULL) {
//
//        if (!xmlStrcmp(curNode->name,BAD_CAST "ant")) {
//            
//            struct _xmlAttr * attr = curNode->properties;
//            if (attr != NULL) {
//                
//                uint8_t index = 0;
//                uint8_t level = 0;
//                uint32_t reputation = 0;
//                for (; attr != NULL; attr = attr->next ) {
//                    
//                    if (!xmlStrcmp(attr->name,BAD_CAST "index"))
//                    {
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        index = atoi(value) -1;
//                        CC_SAFE_FREE(value);
//                        
//                    }else if (!xmlStrcmp(attr->name,BAD_CAST "level")){
//                        
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        level = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }else if (!xmlStrcmp(attr->name,BAD_CAST "reputation")){
//                        
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        reputation = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }
//                }
//                if( index < MEMBER_NUM){
//                    
//                    LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(index);
//                    data->setReputation(reputation);
//                    data->setLockLevel(level);
//                }
//            }
//            else
//            {
//                MB_LOG("Error:empty libox in templete.");
//            }
//
//        }
//        curNode = curNode->next;
//    }
//    xmlFreeDoc(g_sharedDoc);
//}
//
//void MB_TeamData::initBoxes2()
//{
//    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/pet_assistant_lock.xml");
//    if (!g_sharedDoc)
//    {
//        return ;
//    }
//    xmlNodePtr root = xmlDocGetRootElement(g_sharedDoc);
//    xmlNodePtr curNode = root->xmlChildrenNode;
//    char* value;
//    while(curNode != NULL) {
//        
//        if (!xmlStrcmp(curNode->name,BAD_CAST "lock")) {
//            
//            struct _xmlAttr * attr = curNode->properties;
//            if (attr != NULL) {
//                
//                uint8_t index = 0;
//                uint16_t costtype = 0;
//                uint16_t costnum = 0;
//                uint16_t gold = 0;
//                for (; attr != NULL; attr = attr->next ) {
//                    
//                    if (!xmlStrcmp(attr->name,BAD_CAST "pos"))
//                    {
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        index = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }else if (!xmlStrcmp(attr->name,BAD_CAST "costtype")){
//                        
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        CCLog("costtype %s",value);
//                        costtype = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }else if (!xmlStrcmp(attr->name,BAD_CAST "costnum")){
//                        
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        CCLog("costnum %s",value);
//                        costnum = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }else if (!xmlStrcmp(attr->name,BAD_CAST "gold")){
//                        
//                        value = (char*)xmlNodeGetContent(attr->children);
//                        CCLog("gold %s",value);
//                        gold = atoi(value);
//                        CC_SAFE_FREE(value);
//                        
//                    }
//                }
//                m_nCost[index].m_nLockCost = costnum;
//                m_nCost[index].m_nLockGold = gold;
//                m_nCost[index].m_nLockCostType = costtype;
//            }
//            else
//            {
//                MB_LOG("Error:empty libox in templete.");
//            }
//            
//        }
//        curNode = curNode->next;
//    }
//    xmlFreeDoc(g_sharedDoc);
//}
//LiBoxTemlete *MB_TeamData::getLiBoxTemleteByID(uint16_t liboxid){
//    
//    CCObject *obj;
//    CCARRAY_FOREACH(m_mapLiBox, obj){
//    
//        LiBoxTemlete * data = (LiBoxTemlete *)obj;
//        if(data->getID() == liboxid){
//        
//            return data;
//        }
//    }
//    CCLog("not find libox %d",liboxid);
//    return NULL;
//
//}

int MB_TeamData::IsUnLockDestiny(MB_DestinyData *data,TeamDataStruct *tdata){
    
    if(tdata == NULL){
        
        return 0;
    }
    if (data->getDestinyType() == 1) {
        
        if (IsFindInTeam(data->getDestinyNeed1())){
            if(IsFindInTeam(data->getDestinyNeed2())){
                if(IsFindInTeam(data->getDestinyNeed3())){
                    if(IsFindInTeam(data->getDestinyNeed4())) {
            
                        return 1;
                    }
                }
            }
        }
        
        if (IsFindInLiTeam(data->getDestinyNeed1(),false)){
            if(IsFindInLiTeam(data->getDestinyNeed2(),false)){
                if(IsFindInLiTeam(data->getDestinyNeed3(),false)){
                    if(IsFindInLiTeam(data->getDestinyNeed4(),false)) {
                        
                        return 2;
                    }
                }
            }
        }

        
    }else {
        
        
        if(IsFindInItem(data->getDestinyNeed1(),tdata)){
            if(IsFindInItem(data->getDestinyNeed2(),tdata)){
               if(IsFindInItem(data->getDestinyNeed3(),tdata)){
                   if(IsFindInItem(data->getDestinyNeed4(),tdata)) {
            
                       return 1;
                   }
               }
           }
        }
    }
    
    return 0;
}
bool MB_TeamData::IsFindInLiTeam(int petType,bool isLi){
 
    if(MB_PetMgr::getInstance()->getPetTemplateByID(petType) == NULL){
        
        return true;
    }
//    for(int i = 0 ;i < MEMBER_NUM ; i++){
//        
//        LieutenantData*  data = MB_TeamData::getInstance()->getLiMemberByIndex(i);
//        if (data->getPet()!= NULL) {
//            
//            if(data->getPet()->getPetTypeID() == petType && (data->isActive() || isLi)){
//                
//                return true;
//            }
//        }
//    }
//    return false ;
    return false;
}
bool MB_TeamData::IsFindInTeam(int petType){
    
    if(MB_PetMgr::getInstance()->getPetTemplateByID(petType) == NULL){
        
        return true;
    }
    for (int i = 0 ; i < MEMBER_NUM; i++) {
        
        TeamDataStruct*  data = MB_TeamData::getInstance()->getTeamMemberByIndex(i);
        if (data->m_pPet != NULL) {
            
            if(data->m_pPet->getPetTypeID() == petType ){
                
                return true;
            }
        }
    }
    return false ;
}

bool MB_TeamData::IsFindInItem(int ItemType,TeamDataStruct* tdata){
    
    if(MB_ItemMgr::getInstance()->getItemTemplateByID(ItemType) == NULL) {
        
        return true;
    }
    if (tdata->m_pEquip1 != NULL ) {
        
        if (tdata->m_pEquip1->getItemID() == ItemType) {
            
            return true;
            
        }
    }
    if (tdata->m_pEquip2 != NULL){
        
        if (tdata->m_pEquip2->getItemID()== ItemType ) {
            
            return true;
        }
        
    }
    if (tdata->m_pEquip3 != NULL){
        
        if (tdata->m_pEquip3->getItemID()== ItemType ) {
            
            return true;
        }
        
    }
    if (tdata->m_pTreasure1 != NULL){
        
        if (tdata->m_pTreasure1->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure2 != NULL){
        
        if (tdata->m_pTreasure2->getItemID()== ItemType ) {
            
            return true;
        }
    }
    if (tdata->m_pTreasure3 != NULL){
        
        if (tdata->m_pTreasure3->getItemID()== ItemType ) {
            
            return true;
        }
    }
//    if (tdata->m_pTreasure4 != NULL){
//        
//        if (tdata->m_pTreasure4->getItemID()== ItemType ) {
//            
//            return true;
//        }
//    }
//    if (tdata->m_pTreasure5 != NULL){
//        
//        if (tdata->m_pTreasure5->getItemID()== ItemType ) {
//            
//            return true;
//        }
//    }
//    if (tdata->m_pTreasure6 != NULL){
//        
//        if (tdata->m_pTreasure6->getItemID()== ItemType ) {
//            
//            return true;
//        }
//    }
//    if (tdata->m_pTreasure7 != NULL){
//        
//        if (tdata->m_pTreasure7->getItemID()== ItemType ) {
//            
//            return true;
//        }
//    }
//    if (tdata->m_pTreasure8 != NULL){
//        
//        if (tdata->m_pTreasure8->getItemID()== ItemType ) {
//            
//            return true;
//        }
//    }
    return false;
}

//int MB_TeamData::IsUnLockDestiny(MB_DestinyData *data,LieutenantData *tdata){
//    
//    if(tdata == NULL){
//    
//        return 0;
//    }
//    if (data->getDestinyType() == 1) {
//        
//        
//        if ( IsFindInLiTeam(data->getDestinyNeed1(),true)){
//            
//            if( IsFindInLiTeam(data->getDestinyNeed2(),true)){
//            
//                if(IsFindInLiTeam(data->getDestinyNeed3(),true)){
//                    
//                    if(IsFindInLiTeam(data->getDestinyNeed4(),true)) {
//                        
//                        return 2;
//                    }
//                }
//            }
//        }
//        if(tdata->isActive()){
//            
//            if ( IsFindInTeam(data->getDestinyNeed1())){
//                
//                if( IsFindInTeam(data->getDestinyNeed2())){
//                    
//                    if(IsFindInTeam(data->getDestinyNeed3())){
//                        
//                        if(IsFindInTeam(data->getDestinyNeed4())) {
//                            
//                            return 1;
//                        }
//                    }
//                }
//            }
//        }
//        
//    }else {
//        
//        if (IsFindInItem(data->getDestinyNeed1(),tdata)){
//            if(IsFindInItem(data->getDestinyNeed2(),tdata)){
//                if(IsFindInItem(data->getDestinyNeed3(),tdata))
//                    if(IsFindInItem(data->getDestinyNeed3(),tdata)){
//                        
//                        return 1;
//                }
//         
//            }
//        }
//    }
//    return 0;
//}
//bool MB_TeamData::IsFindInItem(int ItemType,LieutenantData * tdata){
//
//    if(MB_ItemMgr::getInstance()->getItemTemplateByID(ItemType) == NULL){
//    
//        return true;
//    }
//    
//    if (tdata->getEquip1() != NULL ) {
//        
//        if (tdata->getEquip1()->getItemID() == ItemType) {
//            
//            return true;
//            
//        }
//    }
//    if (tdata->getEquip2() != NULL){
//        
//        if (tdata->getEquip2()->getItemID()== ItemType ) {
//            
//            return true;
//        }
//        
//    }
//    if (tdata->getEquip3() != NULL){
//        
//        if (tdata->getEquip3()->getItemID()== ItemType ) {
//            
//            return true;
//        }
//        
//    }
//    return false;
//}


//换精灵
//bool MB_TeamData::petUpLiByPetID(uint8_t petPos, uint64_t petID){
//
//    //服务器从1计数
//    petPos--;
//    LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
//    //替换精灵
//    MB_PetData* petData = data->getPet();
//    if (petData  != NULL)
//    {
//        //下阵精灵修改血量公攻击力
//     
//        MB_PetTemplate* templete = MB_PetMgr::getInstance()->getPetTemplateByID(petData->getPetTypeID());
//        if(templete != NULL){
//            
//            petData->setPetAttack(MB_PetMgr::getInstance()->calPetAttack(templete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity()));
//            petData->setPetHpMax(MB_PetMgr::getInstance()->calPetHP(templete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity()));
//        }
//       
//    }
//    data->setPet(MB_PetMgr::getInstance()->getPetDataByUID(petID));
//    //装备ID改到新精灵身上
//    
//    if (data->getEquip1() != NULL)
//    {
//       data->getEquip1()->setItemPetID(petID);
//    }
//    if (data->getEquip2() != NULL)
//    {
//        data->getEquip2()->setItemPetID(petID);
//    }
//    if (data->getEquip3() != NULL)
//    {
//        data->getEquip3()->setItemPetID(petID);
//    }
//    return true;
//    
//}
////换装备
//bool MB_TeamData::equipUpLiByItemUID(uint8_t petPos, uint64_t itemUID){
//
//    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(itemUID);
//    
//    if (itemData == NULL || petPos >= MEMBER_NUM) {
//        MB_LOG("equipUpByItemUID failed. petPos:%d itemUID:%llu",petPos, itemUID);
//        return false;
//    }
//    uint8_t itemPos = itemData->getItemPos();
//    LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
//
//    if (itemPos == kItemPosEquip1)
//    {
//        data->setEquip1(itemData);
//    }
//    else if (itemPos == kItemPosEquip2)
//    {
//        data->setEquip2(itemData);
//    }
//    else if (itemPos == kItemPosEquip3)
//    {
//         data->setEquip3(itemData);
//    }
//    else
//    {
//        MB_LOG("item equip position unkown, itemPos:%d petPos:%d",itemPos, petPos);
//        return false;
//    }
//    
//    return true;
//}
////卸装备
//bool MB_TeamData::equipDownLiByItemUID(uint8_t petPos, MB_ItemData* itemData ){
//    
//    if (itemData == NULL || petPos >= MEMBER_NUM) {
//        
//        MB_LOG("equipLiUpByItemUID failed. petPos:%d itemUID:%llu",petPos);
//        return false;
//    }
//    uint8_t itemPos = itemData->getItemPos();
//    LieutenantData * data = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
//
//    if (itemPos == kItemPosEquip1)
//    {
//        data->setEquip1(NULL);
//    }
//    else if (itemPos == kItemPosEquip2)
//    {
//       data->setEquip2(NULL);
//    }
//    else if (itemPos == kItemPosEquip3)
//    {
//       data->setEquip3(NULL);
//    }
//    else
//    {
//        MB_LOG("item equip position unkown, itemPos:%d petPos:%d",itemPos, petPos);
//        return false;
//    }
//    return true;
//}
////精灵换位
//bool MB_TeamData::exchangeLiPetPos(uint8_t petPos, uint8_t targetPos){
//   
//    petPos--;
//    targetPos--;
//    LieutenantData * data1 = (LieutenantData *)m_pLiData->objectAtIndex(petPos);
//    LieutenantData * data2 = (LieutenantData *)m_pLiData->objectAtIndex(targetPos);
//    
//    MB_PetData *tempPet = data1->getPet();
//    MB_ItemData *tempEq1 = data1->getEquip1();
//    MB_ItemData *tempEq2 = data1->getEquip2();
//    MB_ItemData *tempEq3 = data1->getEquip3();
// 
//    data1->setPet(data2->getPet());
//    data1->setEquip1(data2->getEquip1());
//    data1->setEquip2(data2->getEquip2());
//    data1->setEquip3(data2->getEquip3());
//    
//    data2->setPet(tempPet);
//    data2->setEquip1(tempEq1);
//    data2->setEquip2(tempEq2);
//    data2->setEquip3(tempEq3);
//    return true;
//}
//boxFreshCost * MB_TeamData::getCostByLockNum(int lockNum){
//    
//    return  &(m_nCost[lockNum]);
//}
void MB_TeamData::initFightPowerToAddMap(){

    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/card_buff.xml");
    if (!g_sharedDoc)
    {
        return ;
    }
    xmlNodePtr root;
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (!xmlStrcmp(curNode->name,BAD_CAST "battle")) {
            
            struct _xmlAttr * attr = curNode->properties;
            if (attr != NULL) {
           
                MB_FightDataCover *data = new MB_FightDataCover();
                
                for (; attr != NULL; attr = attr->next ) {
                    
                    if (!xmlStrcmp(attr->name,BAD_CAST "fightpower"))
                    {
                        value = (char*)xmlNodeGetContent(attr->children);
                        data->setFightPower(atoi(value));
                        CC_SAFE_FREE(value);
                        
                    }else if (!xmlStrcmp(attr->name,BAD_CAST "toadd")){
                        
                        value = (char*)xmlNodeGetContent(attr->children);
                        data->setAddPower(atoi(value));
                        CC_SAFE_FREE(value);
                        
                    }
                }
                m_mapFightPower->addObject(data);
                data->release();
            }
            else
            {
                MB_LOG("Error:empty libox in templete.");
            }
            
        }
        curNode = curNode->next;
    }
    xmlFreeDoc(g_sharedDoc);
    
//    CCLog("xml init1 over");
}
uint32_t MB_TeamData::getFightPowerToAddByFightPower(uint32_t fightpower){

    CCObject *obj;
    uint32_t toAdd  = 0;
    CCARRAY_FOREACH(m_mapFightPower, obj){
    
        MB_FightDataCover *data = (MB_FightDataCover *)obj;
        if( fightpower < data->getFightPower()){
        
            break;
        }
        toAdd = data->getAddPower();
    }
    return  toAdd;
}



//检查套装是否激活
bool MB_TeamData::checkSuitActivate(MB_ItemData* pItem,TeamDataStruct* pTs)
{
    uint16_t nCount = 0;
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(pItem->getItemID());
    if(pTemplate && pTs)
    {
        uint16_t nSuitID = pTemplate->getSuitID();
        
        if(nSuitID == 0)return false;
        
        const MB_SuitTemplate* pSuitTemplate = MB_SuitEquipmentMgr::getInstance()->getSuitTemplateBy(nSuitID);
        MB_SuitTemplate* pTemp = const_cast<MB_SuitTemplate*>(pSuitTemplate);
        
        if(pTs->m_pEquip1 && pTs->m_pEquip1->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pEquip2 && pTs->m_pEquip2->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pEquip3 && pTs->m_pEquip3->isSuitPart(nSuitID))++nCount;
        
        if(pTs->m_pTreasure1 && pTs->m_pTreasure1->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure2 && pTs->m_pTreasure2->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure3 && pTs->m_pTreasure3->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure4 && pTs->m_pTreasure4->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure5 && pTs->m_pTreasure5->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure6 && pTs->m_pTreasure6->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure7 && pTs->m_pTreasure7->isSuitPart(nSuitID))++nCount;
        if(pTs->m_pTreasure8 && pTs->m_pTreasure8->isSuitPart(nSuitID))++nCount;
        
        CCArray* pArray = CCArray::create();
        return pTemp->getActivateOptionsByPartCount(pArray,nCount);
    }
    return false;
}
//
//bool MB_TeamData::sendteam_view_other(uint32_t roleID)
//{
//    MB_Message::sharedMB_Message()->showMessage("",10);
//    SOCKET_REQUEST_START(CS_TEAM_VIEW_OTHER);
//    packet->writeU32(roleID);
//    SOCKET_REQUEST_END(SC_TEAM_VIEW_OTHER, MB_LayerResultPVPRanking);
//    return true;
//}

bool MB_TeamData::recvteam_view_other(MB_MsgBuffer *recvPacket)
{
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    MB_DataTeamCompare* dataTeamCompare = new MB_DataTeamCompare();
    
    if (recvPacket->readU32(&data32)) {
        dataTeamCompare->setRoleID(data32);
    }
    
    char* roleName = recvPacket->ReadString();
    if (roleName != NULL) {
        dataTeamCompare->setRoleName(roleName);
    }
    CC_SAFE_FREE(roleName);
    
    if (recvPacket->readU16(&data16)) {
        dataTeamCompare->setRoleLevel(data16);
    }
    
    if (recvPacket->readU64(&data64)) {
        dataTeamCompare->setRoleFightPower(data64);
    }
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    for (int i = 0; i < count; ++i) {
        MB_PetData* petData = new MB_PetData();
        if (recvPacket->readU16(&data16)) {
            petData->setPetQuallity(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetLevel(data16);
        }
        if (recvPacket->readU16(&data16)) {
            petData->setPetTypeID(data16);
        }
        dataTeamCompare->getTeamArray()->addObject(petData);
        petData->release();
    }
    
    //打开队伍比较界面
    CCDirector::sharedDirector()->pushScene(MB_SceneTeamCompare_Old::scene(dataTeamCompare,true));
    CC_SAFE_RELEASE(dataTeamCompare);
    return true;
}
