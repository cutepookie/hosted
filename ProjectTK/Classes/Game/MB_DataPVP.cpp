
#include "MB_DataPVP.h"
#include "Game.h"
#include "MB_RechargeSystem.h"
#include "MB_SceneGame.h"
//pvp排行數据,單例
static MB_DataPVPMgr* s_pDataPVPMgr = NULL;

MB_DataPVPMgr* MB_DataPVPMgr::getInstance(){
    
    if(s_pDataPVPMgr == NULL )
    {
        s_pDataPVPMgr = new  MB_DataPVPMgr();
    }
    
    return  s_pDataPVPMgr;
}

void MB_DataPVPMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pDataPVPMgr);
    s_pDataPVPMgr = NULL;
}

MB_DataPVPMgr::MB_DataPVPMgr()
{
    m_PVPRankArray = CCArray::create();
    m_PVPRankArray->retain();
    
    m_pTargetRole = new MB_DataPVPRank();
    m_bGoFight = false;
    SOCKET_MSG_REGIST(SC_PVP_GET_LIST, MB_DataPVPMgr);
    SOCKET_MSG_REGIST(SC_PVP_FIGHT, MB_DataPVPMgr);
}

MB_DataPVPMgr::~MB_DataPVPMgr()
{
    CC_SAFE_DELETE(m_pTargetRole);
    
    SOCKET_MSG_UNREGIST(SC_PVP_FIGHT);
    SOCKET_MSG_UNREGIST(SC_PVP_GET_LIST);
    
    CC_SAFE_RELEASE(m_PVPRankArray);
}

void MB_DataPVPMgr::setTarget(MB_DataPVPRank *dataPVPRank)
{
    m_pTargetRole->setRoleFightPower(dataPVPRank->getRoleFightPower());
    m_pTargetRole->setIsMale(dataPVPRank->getIsMale());
    m_pTargetRole->setRoleID(dataPVPRank->getRoleID());
    m_pTargetRole->setRoleLevel(dataPVPRank->getRoleLevel());
    m_pTargetRole->setRoleName(dataPVPRank->getRoleName());
    m_pTargetRole->setRoleRank(dataPVPRank->getRoleRank());
    m_pTargetRole->setRoleTitle(dataPVPRank->getRoleTitle());
}

bool MB_DataPVPMgr::sendpvp_get_list()
{
    SOCKET_REQUEST_START(CS_PVP_GET_LIST);
    SOCKET_REQUEST_END(SC_PVP_GET_LIST, MB_DataPVPMgr::onMsgRecv);
    
    return true;
}

bool MB_DataPVPMgr::recvpvp_get_list(MB_MsgBuffer *recvPacket)
{
    uint8_t data8;
    uint16_t data16;
    uint32_t data32;
    uint64_t data64;
    
    m_PVPRankArray->removeAllObjects();
    //獲取自身排名
    if (!recvPacket->readU16(&data16)) {
        MB_LOG("recvpvp_get_list myRank fail.");
        return false;
    }
    else
    {
        m_uRoleRank = data16;
    }
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    MB_DataPVPRank* pvpInfoNode = NULL;
    
    for (uint16_t i = 0; i < count; ++i) {
        
        pvpInfoNode = new MB_DataPVPRank();
        
        if (recvPacket->readU32(&data32)) {
            pvpInfoNode->setRoleID(data32);
        }
        if (recvPacket->readU8(&data8)) {
            pvpInfoNode->setIsMale(data8);
        }
        if (recvPacket->readU8(&data8)) {
            pvpInfoNode->setRoleLevel(data8);
        }
        if (recvPacket->readU8(&data8)) {
            pvpInfoNode->setRoleTitle(data8);
        }
        
        char* roleName = recvPacket->ReadString();
        if (roleName != NULL)
        {
            pvpInfoNode->setRoleName(roleName);
            CC_SAFE_FREE(roleName);
        }
        
        if (recvPacket->readU64(&data64)) {
            pvpInfoNode->setRoleFightPower(data64);
        }
        
        if (recvPacket->readU16(&data16)) {
            pvpInfoNode->setRoleRank(data16);
        }
        if (recvPacket->readU32(&data32)) {
            pvpInfoNode->setHead(data32);
        }
        else
        {
            MB_LOG("parse recvpvp_fight fail.");
            return false;
        }
        
        //local
        if (canFight(m_uRoleRank, pvpInfoNode->getRoleRank()))
        {
            pvpInfoNode->setCanFight(true);
        }
        else
        {
            pvpInfoNode->setCanFight(false);
        }
        
        m_PVPRankArray->addObject(pvpInfoNode);
        pvpInfoNode->release();
        
    }
    
    //加入自身
    if (m_uRoleRank > 15 || m_uRoleRank == 11) {
        pvpInfoNode = new MB_DataPVPRank();
        pvpInfoNode->setRoleID(MB_RoleData::getInstance()->getUID());
        pvpInfoNode->setIsMale(MB_RoleData::getInstance()->getSex());
        pvpInfoNode->setRoleLevel(MB_RoleData::getInstance()->getLevel());
        pvpInfoNode->setRoleTitle(MB_RoleData::getInstance()->getTitle());
        pvpInfoNode->setRoleName(MB_RoleData::getInstance()->getName());
        pvpInfoNode->setRoleFightPower(MB_TeamData::getInstance()->getFightPower());
        pvpInfoNode->setRoleRank(m_uRoleRank);
        m_PVPRankArray->addObject(pvpInfoNode);
        pvpInfoNode->release();
    }
    return true;
}

bool MB_DataPVPMgr::sendpvp_fight(uint32_t roleID, uint16_t rank)
{
    if(!checkTimes()) return true;
    
    MB_Message::sharedMB_Message()->showMessage("",10);
    
    SOCKET_REQUEST_START(CS_PVP_FIGHT);
    packet->writeU32(roleID);
    packet->writeU16(rank);
    SOCKET_REQUEST_END(SC_PVP_FIGHT,MB_DataPVPMgr::onMsgRecv);
    return true;
}

bool MB_DataPVPMgr::recvpvp_fight(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    uint16_t myRank = 0;
    uint32_t data32 = 0;
    MB_Message::sharedMB_Message()->removeALLMessage();
    recvPacket->readU8(&result);
    if (result == 1) {
        
        recvPacket->readU16(&myRank);
        recvPacket->readU32(&data32);
        uint16_t num;
        recvPacket->readU16(&num);
        
        if (num > 0) {
            
            MB_NetStructFight structFight;
            recvfight* fight = structFight.recvfight_request(recvPacket);
            
            p_result_ranking* fightResult = new p_result_ranking();
            fight->type = kFightResultTypePVPRanking;
            fightResult->_myOldRank = m_uRoleRank;
            fightResult->_dataPVPRank = m_pTargetRole;
            fightResult->_isSuccess = fight->issuccess;
            fightResult->_addCoin = data32;
            if (fight->issuccess) {
                
                fightResult->_myRank = myRank;
                m_uRoleRank = myRank;
            }
            CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fight,fightResult));
        }
    }
    else if (result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("","发起决斗失败, 对方玩家的排名已经发生变化, 请重新选择.","确定");
    }
    else if (result == 3)
    {
        if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(PVP_ADD, NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
        {
            int needMoney = MB_RoleData::getInstance()->getNeedGoldByTime(kBuyTimesTypePvp);
            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypePvp)-MB_RoleData::getInstance()->getPvpBuyTimes();
            if(limit > 0){
                
                char databuf[400];
                sprintf(databuf, "您是否需要花费 %d 宝石, 购买 %d 次竞技场次数?\n这是今日的第%d次购买, 当前VIP等级每日购买的次数上限是%d次",needMoney,MB_RoleData::getInstance()->getPvpRecoveryTimes(),
                        MB_RoleData::getInstance()->getPvpBuyTimes() + 1 ,MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypePvp));
                MB_Message::sharedMB_Message()->showMessage("购买竞技场次数", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyPvpTimes),NULL);
                
                
            }else {
                
                if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL){
                    
                    char databuf[400];
                    sprintf(databuf, "您的竞技场次数不足了, 并且今日的回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数");
                    MB_Message::sharedMB_Message()->showMessage("购买次数达到上限", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                    
                    
                }else {
                    
                    MB_Message::sharedMB_Message()->showMessage("今日的竞技场次数已经达到上限");
                }
                
            }

        }
        
    }
    else if(result == 4)
    {
        MB_LOG("发起决斗失败，点得太快了，上一次战斗还在计算中");
        return  false;
    }
    else if(result == 5)
    {
        MB_LOG("发起决斗失败，该主攻正在被别的玩家决斗中");
        return  false;
    }
    else if(result == 6)
    {
        MB_LOG("发起决斗失败，不能决斗自己");
        return  false;
    }
    else
    {
        MB_LOG("recvpvp_fight fail. errcode:%d",result);
        return false;
    }
    
    return true;
}

void MB_DataPVPMgr::onMsgRecv(CCNode* node, SocketResponse* response)
{
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
        case SC_PVP_GET_LIST:
            recvpvp_get_list(recvPacket);
            break;
        case SC_PVP_FIGHT:
            recvpvp_fight(recvPacket);
            break;
            
        default:
            break;
    }
}

/*  
 >15: 只要排名>10都可以决鬥
 >6:  只决鬥前面排名挨着的5位
 <=6: 只决鬥非自己的前6位
*/
bool MB_DataPVPMgr::canFight(uint16_t myRank, uint16_t tagRank)
{
    if (myRank > 15)
    {
        if (tagRank > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (myRank > 6) {
            
            uint16_t subRank = myRank - tagRank;
            if ( subRank > 0 && subRank <= 5 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (tagRank <=6 && tagRank != myRank)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

bool MB_DataPVPMgr::checkTimes()
{
    if(MB_RoleData::getInstance()->getPVPTimes() <= 0)
    {
        
        if (MB_RechargeSystem::getInstance()->showRechargeWndByType(PVP_ADD, NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
        {
            return false;
        }
        else
        {
            int needMoney = MB_RoleData::getInstance()->getNeedGoldByTime(kBuyTimesTypePvp);
            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypePvp)-MB_RoleData::getInstance()->getPvpBuyTimes();
            if(limit > 0)
            {
                char databuf[400];
                sprintf(databuf, "您是否需要花费 %d 宝石, 购买 %d 次竞技场次数?\n这是今日的第%d次购买, 当前VIP等级每日购买的次数上限是%d次",needMoney,MB_RoleData::getInstance()->getPvpRecoveryTimes(),
                        MB_RoleData::getInstance()->getPvpBuyTimes() + 1 ,MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypePvp));
                MB_Message::sharedMB_Message()->showMessage("购买竞技场次数", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyPvpTimes),NULL);
            }
            else
            {
                if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL)
                {
                    char databuf[400];
                    sprintf(databuf, "您的竞技场次数不足了, 并且今日的回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数");
                    MB_Message::sharedMB_Message()->showMessage("购买次数达到上限", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                }
                else
                {
                    MB_Message::sharedMB_Message()->showMessage("今日的竞技场次数已经达到上限");
                }
            }
        }
        return false;
    }
    return true;
}
