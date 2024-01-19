
#include "MB_NetStructFight.h"
#include "MB_RechargeSystem.h"
#include "MB_SceneGame.h"
MB_NetStructFight::MB_NetStructFight(){

    m_nLevel = MB_RoleData::getInstance()->getLevel();
    m_nPreExp = MB_RoleData::getInstance()->getEXP();
    m_pBossList = NULL;
}
MB_NetStructFight::~MB_NetStructFight(){

    CC_SAFE_DELETE_ARRAY(m_pBossList);
}
MB_NetStructFight::MB_NetStructFight(int preLevel,int64_t preExp,char *bossList,
                                     int perenpety, int predistime,int prestar,
                                     uint16_t doungeLevel){
    
    m_nLevel = preLevel;
    m_nPreExp = preExp;
    if(bossList == NULL){
    
        m_pBossList = NULL;
        
    }else {
    
        m_pBossList = new char[8];
        strcpy(m_pBossList, bossList);
        
    }    
    m_nPreEnpety = perenpety;
    m_nPreDistime = predistime;
    m_nPrestar = prestar;
    m_nDoungeLevel = doungeLevel;
    
}
recvfight * MB_NetStructFight::recvfight_request(MB_MsgBuffer* recvPacket){
    
    recvfight * fightResult = (recvfight * )malloc(sizeof(recvfight));
    if(m_pBossList == NULL){
        for(int i = 0; i < 6;i++ ){
            
            fightResult->isBoss[i] = '0';
        }
    }else {
        for(int i = 0; i < 6;i++ ){
            
            fightResult->isBoss[i] = m_pBossList[i];
        }
    }
    this->structDatas(recvPacket,fightResult);
    return fightResult;
    
}

 p_reward * MB_NetStructFight::recvfight_reward(MB_MsgBuffer* recvPacket){

    /**************result*********************/
     p_reward * reword =(p_reward *)malloc(sizeof(p_reward));
     
     reword->petExp = NULL;
     reword->item = NULL;
     reword->roleExp = 0;
     reword->reputation = 0;
     reword->coin = 0;
     reword->roleExp = 0;
     reword->gold = 0;
     reword->score = 0;
     reword->preLevel = 0;
     reword->preEnergy = 0;
     reword->preDiscovery = 0;
     reword->preStar = 0;
     
    short result = 0;
    if (recvPacket->readU16(&result))
    { 
        if(result>0){
            
            recvPacket->readU32(&(reword->coin));
            recvPacket->readU32(&(reword->roleExp));
            
            int16_t petExpLength;
            recvPacket->readU16(&petExpLength);
            p_petExp *movePoint = NULL;
            for (int i= 0; i < petExpLength ; i++) {
                p_petExp * temp =(p_petExp *)malloc(sizeof(p_petExp));
                temp ->next = NULL;
                recvPacket->readU8(&(temp->petPos));
                recvPacket->readU32(&(temp->addExp));
                recvPacket->readU8(&(temp->isUpgraded));
                if ( reword->petExp == NULL) {
                    
                    reword->petExp = movePoint = temp;
                    
                }else {
                    movePoint->next = temp;
                    movePoint = temp;
                }
                
            }
            recvPacket->readU32(&(reword->gold));
            p_item_view *moveItem = NULL;
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
                
                if (reword->item == NULL) {
                    reword->item = moveItem =item;
                    
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
                if (reword->item == NULL) {
                    reword->item = moveItem =item;
                    
                }else{
                    
                    moveItem->next = item;
                    moveItem = item;
                }
                
                
            }
            
            recvPacket->readU32(&(reword->reputation));
            
        }
    }
  
    return reword;
}
 p_reward * MB_NetStructFight::recvfight_sore(MB_MsgBuffer* recvPacket, p_reward * reward){

    recvPacket->readU8(&(reward->score));

    return reward;
}
void MB_NetStructFight::structDatas(MB_MsgBuffer* recvPacket,recvfight *fightResult){

    /***************pfightData****************/
    uint16_t p_fighter_size;
    recvPacket->readU16(&p_fighter_size);
    
    if (p_fighter_size==1)
    {
        CCLOG("Error: only one fighter in the struct!");
    }
    p_fighter * head = NULL;
    p_fighter *temp=NULL;    
    for (int i =0 ; i <  p_fighter_size ; i++) {
       
                p_fighter * nowdata = (p_fighter *)malloc(sizeof(p_fighter));
                nowdata->next=NULL;
                if(head == NULL){
                    
                    fightResult->fighterList = temp = head = nowdata;
                    
                }else {
                
                    temp->next = nowdata;
                    temp = nowdata;
                }
                recvPacket->readU64(&nowdata->petId);
                recvPacket->readU16(&nowdata->petTypeID);
                recvPacket->readU8(&nowdata->petPos);     
                recvPacket->readU64(&nowdata->petHp);
                recvPacket->readU64(&nowdata->petHpMax);
                recvPacket->readU32(&nowdata->petSp);
                char data8;
                recvPacket->readU8(&data8);
                nowdata->petQuality = (data8 >0 ?data8 :0);
                recvPacket->readU16(&nowdata->petLevel);
        
    }
    /**********************actionList**********************************/
    
    uint16_t p_action_size;
    recvPacket->readU16(& p_action_size);
    fightResult->fighterList=head;
    
    int p_action_num =  p_action_size;
    
    p_action * head2 = NULL;
    p_action *temp2=NULL;
    for (int i =0 ; i < p_action_num ; i++) {
    
        p_action * nowdata = (p_action  *)malloc(sizeof(p_action));
        nowdata->next=NULL;
        if(head == NULL){
        
            fightResult->actionList = temp2 = head2 = nowdata;
        
        }else {
            
            head2 = nowdata;
            nowdata->next = temp2;
            temp2=nowdata;
            
        }
        recvPacket->readU8(&nowdata->petPos);
        uint8_t actionId;
        recvPacket->readU8(&actionId);
        
        nowdata->action = MB_ActionData::getInstance()->getActionByID(actionId);
        
        short target_num;
        recvPacket->readU16(& target_num);
        
        for (int i=0; i < target_num; i++) {
            
            recvPacket->readU8(&nowdata->targetPos[i]);
        }
        nowdata->targetPos[target_num]='\0';
        recvPacket->readU8(&nowdata->addSp);
        recvPacket->readU32(&nowdata->addHp);
        recvPacket->readU8(&nowdata->state);
        
    }    
    fightResult->actionList = head2;
  
    char issucces;
    recvPacket->readU8(&issucces);
    fightResult->issuccess = issucces;


}
p_reward * MB_NetStructFight::recvexplore_challenge_encounter(MB_MsgBuffer* recvPacket){

    uint8_t is_scuccess;
    recvPacket->readU8(&is_scuccess);
    uint16_t data;
    recvPacket->readU16(&data);
    
    if(is_scuccess == 1){
        
        recvfight *  fightresult = recvfight_request(recvPacket);
        p_reward *reward = recvfight_reward(recvPacket);
        recvfight_sore(recvPacket, reward);
        reward->score = 0;
        reward->preStar = m_nPrestar;
        
        fightresult->type = kFightResultTypePVE;
        
        if ( fightresult->issuccess == 1) {
            
            reward->preLevel = m_nLevel;
            reward->preExp = m_nPreExp;
            reward->preEnergy = m_nPreEnpety;
            reward->preDiscovery = m_nPreDistime;
            
        }else {        
            
            reward->preLevel = -1;//如果失败方便值0 方便判断
            reward->preExp = m_nPreExp;
            reward->preEnergy = 0;
            reward->preDiscovery = 0;
        }
     
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,reward,m_nDoungeLevel));
        
        return  reward;
        
    }else  if(is_scuccess == 2)
    {
      
        if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(Energy_ADD,NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
        {
            int needMoney = MB_RoleData::getInstance()->getNeedGold();
            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeEnergy)-MB_RoleData::getInstance()->getEnergyBuyTimes();
            if(limit > 0)
            {
                char databuf[200];
                sprintf(databuf, "您的体力不足了, 您可以消耗%d宝石, 来补充20点体力, 您今天还可以购买 %d次。",needMoney,limit);
                MB_Message::sharedMB_Message()->showMessage("提示", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyEnergy),NULL);
            }
            else
            {
                
                if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL)
                {
                    
                    char databuf[200];
                    sprintf(databuf, "您的体力不足了, 并且今日的体力回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数");
                    MB_Message::sharedMB_Message()->showMessage("提示", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                    
                }
                else
                {
                    
                    MB_Message::sharedMB_Message()->showMessage("今日体力购买次数已经达到上限");
                }
                
            }
        }
        
    }else if(is_scuccess == 3){
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG, true);
        MB_Message::sharedMB_Message()->showMessage("决斗成功不能再决斗");
        
    }
    else if(is_scuccess == 4){
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG, true);
        MB_Message::sharedMB_Message()->showMessage("该关卡未激活, 请完成前面的关卡");
        
    }
    else if(is_scuccess == 5){
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG, true);
        MB_Message::sharedMB_Message()->showMessage("您不拥有该关卡");
        
    }
    return NULL;
}
uint8_t  MB_NetStructFight::recvexplore_challenge_state(MB_MsgBuffer* recvPacket){
    
    uint8_t  data8;
    recvPacket->readU8(&data8);
    return  data8;
}
p_reward * MB_NetStructFight::recvbattle_challenge(MB_MsgBuffer* recvPacket,const char* pBackground,uint8_t *bSuccess)
{
    uint8_t is_scuccess;
    recvPacket->readU8(&is_scuccess);
    uint16_t data;
    recvPacket->readU16(&data);
    bool bFirstFailed = false;
    if(bSuccess)*bSuccess = is_scuccess;
    if(is_scuccess == 1)
    {
        recvfight *  fightresult =  recvfight_request(recvPacket);
        p_reward *reward = recvfight_reward(recvPacket);
        recvfight_sore(recvPacket, reward);
        fightresult->type = kFightResultTypePVE;
        reward->preStar = m_nPrestar;
        if (fightresult->issuccess == 1) {
            
             reward->preLevel = m_nLevel;
             reward->preExp = m_nPreExp;
             reward->preEnergy = m_nPreEnpety;
             reward->preDiscovery = m_nPreDistime;
        
        }else {
            
             reward->preLevel = -1;
             reward->preExp = m_nPreExp;
             reward->preEnergy = 0;
             reward->preDiscovery = 0;
            if (!MB_RoleData::getInstance()->getPveHasFailed())
            {
                bFirstFailed = true;
                MB_RoleData::getInstance()->setPveHasFailed(true);
            }
        }
        CCScene* pBattle = MB_SceneGame::scene(fightresult,reward,m_nDoungeLevel,pBackground,bFirstFailed);
        
        
        
        CCDirector::sharedDirector()->pushScene(pBattle);
        return reward;
        
        
    }else if(is_scuccess == 2){
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG, true);
        MB_Message::sharedMB_Message()->showMessage("此关卡已经达到今日的远征上限");
        
    }
    else  if(is_scuccess == 3)
    {
        if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(Energy_ADD, NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
        {
            int needMoney = MB_RoleData::getInstance()->getNeedGold();
            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeEnergy)-MB_RoleData::getInstance()->getEnergyBuyTimes();
            if(limit > 0)
            {
                char databuf[200];
                sprintf(databuf, "您的体力不足了, 您可以消耗%d宝石, 来补充20点体力, 您今天还可以购买 %d次。",needMoney,limit);
                MB_Message::sharedMB_Message()->showMessage("提示", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyEnergy),NULL);
            }
            else
            {
                
                if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL)
                {
                    
                    char databuf[200];
                    sprintf(databuf, "您的体力不足了，并且今日的体力回复的次数已经使用完毕，充值成为更高级的VIP，可以立马增加回复次数");
                    MB_Message::sharedMB_Message()->showMessage("提示", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                    
                }
                else
                {
                    MB_Message::sharedMB_Message()->showMessage("今日体力购买次数已达上限");
                }
            }
        }
    }
    else if(is_scuccess == 4){
        
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(MESSAGE_TAG, true);
        MB_Message::sharedMB_Message()->showMessage("", "您还不能决斗这个章节！","确定");
        
    }

    return NULL;
}
