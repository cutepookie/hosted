//
//  MB_FunctionBudokanInterface.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#include "MB_FunctionBudokanInterface.h"
#include "MB_NodeBudokanEntry.h"
#include "MB_LayerBudokan.h"
#include "MB_SceneGame.h"
MB_FunctionBudokanInterface::MB_FunctionBudokanInterface()
{
    m_pBudokanData = new MB_BudokanData();
    m_pBudokanConfig = new MB_BudokanConfig();
    m_pBudokanConfig->init("config/Budokan_dungeon.xml");
    
    SOCKET_MSG_REGIST(SC_BUDUOKAN_INFO,MB_FunctionBudokanInterface);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_BUY,MB_FunctionBudokanInterface);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_FIGHT,MB_FunctionBudokanInterface);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_RAIDS,MB_FunctionBudokanInterface);
}
MB_FunctionBudokanInterface::~MB_FunctionBudokanInterface()
{
    CC_SAFE_RELEASE_NULL(m_pBudokanData);
    CC_SAFE_RELEASE_NULL(m_pBudokanConfig);
    
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_INFO);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_BUY);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_FIGHT);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_RAIDS);
}
MB_ResWindow* MB_FunctionBudokanInterface::createEntryDialog()
{
    return MB_NodeBudokanEntry::create();
}
MB_ResWindow* MB_FunctionBudokanInterface::createFunctionDialog()
{
    MB_LayerBudokan* pInstance = new MB_LayerBudokan;
    if (pInstance && pInstance->init() && pInstance->setDataSource(this) )
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}
void MB_FunctionBudokanInterface::onLoadingScene()
{
    SOCKET_REQUEST_START(CS_BUDUOKAN_INFO);
    SOCKET_REQUEST_END(SC_BUDUOKAN_INFO, NULL);
}


void MB_FunctionBudokanInterface::onMsgRecv(CCNode* node, SocketResponse* response)
{
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_BUDUOKAN_INFO:
            recvbudokan_info(recvPacket);
            break;
        case SC_BUDUOKAN_BUY:
            recvbudokan_buy(recvPacket);
            break;
        case SC_BUDUOKAN_FIGHT:
            recvbudokan_fight(recvPacket);
            break;
        case SC_BUDUOKAN_RAIDS:
            recvbudokan_raids(recvPacket);
        default:
            break;
    }

}
bool MB_FunctionBudokanInterface::allowShow()
{
    return true;
}
uint16_t MB_FunctionBudokanInterface::getFunctionType()
{
    return kFunctionBudokan;
}
void MB_FunctionBudokanInterface::onEntryClicked(CCObject* pSender)
{
    MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if(pFunctionItem)
    {
        if(pFunctionItem->getNeedLevel()>MB_RoleData::getInstance()->getLevel())
        {
            char databuf[40];
            sprintf(databuf, "此功能%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
        }
        else
        {
            MB_BudokanConfig* config = getBudokanConfig();
            MB_BudokanChapterData* chapterData = NULL;
            chapterData = config->getChapterDataByID(getBudokanData()->getDungeonID());
            if (chapterData == NULL)
            {
                MB_Message::sharedMB_Message()->showMessage("您已通关结晶塔, 请明天继续挑战");
                return;
            }
            
            MB_ResWindow* pWnd = createFunctionDialog();
            if (pWnd)
            {
                replaceMainSceneSubLayer(pWnd);
            }
        }
    }
}

bool MB_FunctionBudokanInterface::getIsOpen()
{
    if (m_pBudokanData == NULL) {
        return false;
    }
    bool isOpen = m_pBudokanData->getIsOpen();
    if (MB_ClientSocket::getInstance()->getServerTime() > m_pBudokanData->getLastTime())
    {
        isOpen = !isOpen;
        sendbudokan_info();
    }
    return isOpen;
}

void MB_FunctionBudokanInterface::sendbudokan_info()
{
    static uint32_t lasttime = MB_ClientSocket::getInstance()->getServerTime();
    if (MB_ClientSocket::getInstance()->getServerTime() - lasttime < 10)
    {
        return;
    }
    lasttime = MB_ClientSocket::getInstance()->getServerTime();
    SOCKET_REQUEST_START(CS_BUDUOKAN_INFO);
    SOCKET_REQUEST_END(SC_BUDUOKAN_INFO, NULL);
}

// 道馆界面信息返回
/*message recvhron_info[id=11302]{
	required       int16           curDungeonNum	    =1;//當前是挑戰第几關
	required       int16           attackAdd		    =2;//當前攻擊增加百分比
	required       int16           hpAdd			    =3;//當前血量增加百分比
	required       int16           dungeonID		    =3;//關卡ID
	required       int8            challengeTimes       =5;//生命值
    required       bool            isOpen               = 6;//是否開啟
    required       int32           nextTime             = 7;//下次切換狀態的時間
    required       int8            coinBuyTimes         = 8;//金幣購買次數
    required       int8            goldBuyTimes         = 9;//钻石購買次數
}*/
void MB_FunctionBudokanInterface::recvbudokan_info(MB_MsgBuffer* pRecv)
{
    m_pBudokanData->read(pRecv);
}

// 請求購買加成
void MB_FunctionBudokanInterface::sendbudokan_buy(uint8_t type)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_BUDUOKAN_BUY);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_BUDUOKAN_BUY, NULL);
    m_nBuyType = type;

}
/*
 message	 recvhron_buy[id=11304]{
 required	int8			result		=1;//請求結果
 // 1=> 購買成功
 // 2=> 購買失敗-金幣不足
 // 3=> 購買失敗-钻石不足
 // 4=> 購買失敗-活動已經結束了
 // 5=> 購買失敗-您已經結束挑戰了
 // 6=> 購買失敗-您已經購買過了
 required	int16			attackAdd	=2;//購買成功時此值有效，當前攻擊增加百分比
 required	int16			hpAdd		=3;//購買成功時此值有效，當前血量增加百分比
 }
 */
void MB_FunctionBudokanInterface::recvbudokan_buy(MB_MsgBuffer* pRecv)
{
    uint8_t data8;
    uint16_t data16;
    pRecv->readU8(&data8);
    if (data8 == 1)
    {
        pRecv->readU16(&data16);
        m_pBudokanData->setAddAttack(data16);
        pRecv->readU16(&data16);
        m_pBudokanData->setAddHp(data16);
        
        if (m_nBuyType == 1)
        {
            m_pBudokanData->setCoinBuyTimes(m_pBudokanData->getCoinBuyTimes()+1);
        }
        else if(m_nBuyType == 2)
        {
            m_pBudokanData->setMoneyBuyTimes(m_pBudokanData->getMoneyBuyTimes()+1);
        }
    }
    else if(data8 == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("购买失败, 金币不足");
    }
    else if(data8 == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("购买失败, 宝石不足");
    }
    else if(data8 == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("购买失败, 活动已经结束了");
    }
    else if(data8 == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("购买失败, 您已经结束挑战了");
    }
    else if(data8 == 6)
    {
        MB_Message::sharedMB_Message()->showMessage("购买失败, 您已经购买过了");
    }
}

// 请求战斗
void MB_FunctionBudokanInterface::sendbudokan_fight()
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_BUDUOKAN_FIGHT);
    SOCKET_REQUEST_END(SC_BUDUOKAN_FIGHT, NULL);
}
/*
 message recvhron_fight[id=11306]{
 required   int8                result		    =1;//請求戰鬥結果
 // 1 => 戰鬥勝利
 // 2 => 戰鬥失敗
 // 3 => 請求失敗-活動結束了
 // 4 => 請求失敗-您今天挑戰次數沒有了
 required   int16               dungeonID       =2;//新的關卡ID
 required   int16               curDungeonNum   =3;//新的第几關
 required   int8                challengeTimes  =4;//新的剩餘挑戰次數
 repeated   recvfight_request    fightInfo	   =5;//戰鬥具体信息
 repeated   p_reward            rewardInfo	   =6;//獎勵信息
 }
 */
void MB_FunctionBudokanInterface::recvbudokan_fight(MB_MsgBuffer* pRecv)
{
    uint8_t data8;
    uint16_t data16;
    pRecv->readU8(&data8);
    if (data8 == 1 || data8 == 2)
    {
        if (data8 == 2)//失敗清空buf
        {
            m_pBudokanData->setAddAttack(0);
            m_pBudokanData->setAddHp(0);
            m_pBudokanData->setCoinBuyTimes(0);
            m_pBudokanData->setMoneyBuyTimes(0);
        }
        
        pRecv->readU16(&data16);
        m_pBudokanData->setDungeonID(data16);
        pRecv->readU16(&data16);
        m_pBudokanData->setCurDungeonNum(data16);
        pRecv->readU8(&data8);
        m_pBudokanData->setChallengeTimes(data8);
        
        //戰鬥具体信息
        MB_NetStructFight fight;
        short data16 ;
        pRecv->readU16(&data16);
        recvfight * fightresult = fight.recvfight_request(pRecv);
        //獎勵信息
        p_reward *reward = fight.recvfight_reward(pRecv);
        fightresult->type = kFightResultTypeHuRong;
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::scene(fightresult,reward,0));
            
        
    }
    else if(data8 == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败, 活动结束了");
    }
    else if(data8 == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("请求失败, 您今天剩余体力没有了");
    }

}

//一键扫塔
/*
 message sc_hron_raids[id=11308]{
 required        int8            result      =1;
 // 0 => 掃蕩成功
 // 1 => 無可掃蕩關卡
 // 2 => 等級不足
 // 3 => vip等級不足
 // 4 => 活動結束了
 // 5 => 支付參數錯誤
 required        int16           dungeonID   =2;//新的關卡ID
 repeated        p_reward        reward      =3;//戰鬥獎勵
 }
 */
void MB_FunctionBudokanInterface::sendbuduokan_raids()
{
    SOCKET_REQUEST_START(CS_BUDUOKAN_RAIDS);
    SOCKET_REQUEST_END(SC_BUDUOKAN_RAIDS, NULL);
}
void MB_FunctionBudokanInterface::recvbudokan_raids(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    uint16_t data16;
    pRecv->readU8(&result);
    if (result == 0)
    {
        pRecv->readU16(&data16);
        m_pBudokanData->setDungeonID(data16);
        m_pBudokanData->setCurDungeonNum(m_pBudokanData->getMaxDungeonNum()+1);
    }
}
