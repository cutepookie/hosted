//
//  MB_PerfectRaceInterface.cpp
//  ProjectPM
//
//  Created by wenyong on 14-4-14.
//
//

#include "MB_PerfectRaceInterface.h"
#include "MB_PerfectRaceProtocol.h"
#include "MB_PerfectRaceEntrance.h"
#include "MB_LayerPerfectRaceRule.h"
#include "MB_LayerPerfectRaceApply.h"
#include "MB_LayerGroupPlayerList.h"
#include "MB_LayerPerfectRaceMain.h"
#include "MB_LayerGroupHistoryRecord.h"
#include "MB_LayerFinalHistoryRecord.h"
#include "MB_LayerFinalRecordLive.h"
#include "MB_LayerGroupRecordLive.h"
#include "MB_RoleSoundSystem.h"
#include "MB_LayerSelfRaceRecord.h"
#include "MB_LayerRaceGuess.h"

void MB_PerfectRaceInterface::setDirection(int dir)
{
    m_nDirection = dir;
}

MB_PerfectRaceInterface::MB_PerfectRaceInterface()
{
    m_bCanEnter = true;
    m_pRaceRecordList = new CCArray;
    m_pFinalRecord = new CCArray;
    m_nDirection = kDirectionNone;
    m_bTimeCountDownRuning = false;
    m_bOpenNewWnd = false;
    m_bOpenRaceMainOrRaceApply = false;
    m_pSelfRecord = new CCArray;
    m_nTargetPosRecord = 0;
    for (uint16_t i=0; i<8; ++i)
    {
        m_pFighterList[i] = NULL;
    }
    for (uint16_t i=0; i<8; ++i)
    {
        m_pRecordList[i] = NULL;
    }
    
    SOCKET_MSG_REGIST(SC_RACE_INFO, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_FIGHT_LIST, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_POS_HISTORY, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_NEW_FIRST, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_NEW_STATUS,MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_IS_OPEN,MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_AUTO_SIGN, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_AUTO_UNSIGN, MB_PerfectRaceInterface);
    SOCKET_MSG_REGIST(SC_RACE_SELF_RECORD, MB_PerfectRaceInterface);
    
//    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
//    pScheduler->scheduleSelector(schedule_selector(MB_PerfectRaceInterface::autoTimeCountDown),this,10.0f,kCCRepeatForever,0.0f,false);
//    pScheduler->unscheduleSelector(schedule_selector(MB_PerfectRaceInterface::autoTimeCountDown), this);
    
}

MB_PerfectRaceInterface::~MB_PerfectRaceInterface()
{
//    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
//    pScheduler->scheduleSelector(schedule_selector(MB_PerfectRaceInterface::autoTimeCountDown),this,1.0f,kCCRepeatForever,0.0f,false);
//    pScheduler->unscheduleSelector(schedule_selector(MB_PerfectRaceInterface::autoTimeCountDown), this);
    
    CC_SAFE_RELEASE_NULL(m_pRaceRecordList);
    CC_SAFE_RELEASE_NULL(m_pFinalRecord);
//    m_bTimeCountDownRuning = false;
//    CC_SAFE_RELEASE_NULL(m_nTimerNode);
    CC_SAFE_RELEASE_NULL(m_pSelfRecord);
    for (uint16_t i=0; i<8; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pFighterList[i]);
    }
    for (uint16_t i=0; i<8; ++i)
    {
        m_pRecordList[i] = NULL;
    }
    
    SOCKET_MSG_UNREGIST(SC_RACE_INFO);
    SOCKET_MSG_UNREGIST(SC_RACE_FIGHT_LIST);
    SOCKET_MSG_UNREGIST(SC_RACE_POS_HISTORY);
    SOCKET_MSG_UNREGIST(SC_RACE_NEW_FIRST);
    SOCKET_MSG_UNREGIST(SC_RACE_NEW_STATUS);
    SOCKET_MSG_UNREGIST(SC_RACE_IS_OPEN);
    SOCKET_MSG_UNREGIST(SC_RACE_AUTO_UNSIGN);
    SOCKET_MSG_UNREGIST(SC_RACE_AUTO_SIGN);
    SOCKET_MSG_UNREGIST(SC_RACE_SELF_RECORD);
}

MB_ResWindow* MB_PerfectRaceInterface::createEntryDialog()
{
    MB_PerfectRaceEntrance* pInstance = new MB_PerfectRaceEntrance();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->setType(kFunctionPerfectRace);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
    
}

MB_ResWindow* MB_PerfectRaceInterface::createFinalLivingDialog()
{
    MB_LayerFinalRecordLive* pInstance = new MB_LayerFinalRecordLive;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createFunctionDialog()
{
    MB_LayerPerfectRaceMain* pInstance = new MB_LayerPerfectRaceMain;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createRuleDialog()
{
    return MB_LayerPerfectRaceRule::create();
}

MB_ResWindow* MB_PerfectRaceInterface::createApplyDialog()
{
    MB_LayerPerfectRaceApply* pInstance = new MB_LayerPerfectRaceApply;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createGroupRecordDialog()
{
    return createGroupRecordDialogByGroupID(1);
}

MB_ResWindow* MB_PerfectRaceInterface::createGroupRecordDialogByGroupID(int nGroup)
{
    MB_LayerGroupHistoryRecord* pInstance = new MB_LayerGroupHistoryRecord;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init(nGroup))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;

}

MB_ResWindow* MB_PerfectRaceInterface::createGroupPlayerDialog(int nGroup)
{
    MB_LayerGroupPlayerList* pInstance = new MB_LayerGroupPlayerList;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init(nGroup))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createFinalRecordDialog(MB_RaceRecord* pRecord)
{
    MB_LayerFinalHistoryRecord* pInstance = new MB_LayerFinalHistoryRecord;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init(pRecord))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createGroupLivingDialog()
{
    MB_LayerGroupRecordLive* pInstance = new MB_LayerGroupRecordLive();
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createSelfRaceRecordDialog()
{
    MB_LayerSelfRaceRecord* pInstance = new MB_LayerSelfRaceRecord;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_PerfectRaceInterface::createGuessDialog()
{
    MB_LayerRaceGuess* pInstance = new MB_LayerRaceGuess;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

void MB_PerfectRaceInterface::onLoadingScene()
{
    sendrace_is_open();
    sendrace_info();
}

void MB_PerfectRaceInterface::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_RACE_INFO:
            recvrace_info(recvPacket);
            break;
        case SC_RACE_FIGHT_LIST:
            recvrace_fight_list(recvPacket);
            break;
        case SC_RACE_NEW_FIGHT:
            recvrace_new_fight(recvPacket);
            break;
        case SC_RACE_POS_HISTORY:
            recvrace_pos_history(recvPacket);
            break;
        case SC_RACE_NEW_FIRST:
            recvrace_new_first(recvPacket);
            break;
        case SC_RACE_NEW_STATUS:
            recvrace_new_status(recvPacket);
            break;
        case SC_RACE_IS_OPEN:
            recvrace_is_open(recvPacket);
            break;
        case SC_RACE_AUTO_SIGN:
            recvrace_auto_sign(recvPacket);
            break;
        case SC_RACE_AUTO_UNSIGN:
            recvrace_auto_unsign(recvPacket);
            break;
        case SC_RACE_SELF_RECORD:
            recvrace_self_record(recvPacket);
            break;
        default:
            break;
    }
}
bool MB_PerfectRaceInterface::allowShow()
{
    return true;
}
uint16_t MB_PerfectRaceInterface::getFunctionType()
{
    return kFunctionPerfectRace;
}

bool MB_PerfectRaceInterface::checkEnableFunction()
{
    int level = MB_RoleData::getInstance()->getLevel();
    
    MB_FunctionItem* pItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kFunctionPerfectRace);
    if (level < pItem->getNeedLevel())
    {
        char buff[64] = {};
        sprintf(buff, "%d级以上才能参加",pItem->getNeedLevel());
        MB_Message::sharedMB_Message()->showMessage(buff);
        return false;
    }
    
    if(!getCanEnter())
    {
        MB_Message::sharedMB_Message()->showMessage("霸主之战还未开始报名");
        return false;
    }
    
    return true;
}

void MB_PerfectRaceInterface::onFinalRecordClicked(int pos)
{
    if (pos < 9 || pos > 15)
    {
        return;
    }
    
    MB_RaceRecordWithPos* pRecord = queryFinalRecordByPos(pos);
    if (pRecord)
    {
        openFinalRecord(pRecord);
    }
    else
    {
        m_nTargetPosRecord = pos;
        MB_Message::sharedMB_Message()->showMessage("",15);
        sendrace_pos_history(m_nTargetPosRecord);
    }
    
}
void MB_PerfectRaceInterface::onEntryClicked(CCObject* pSender)
{
    if (!checkEnableFunction())
    {
        return;
    }
    
    
    
    //不用请求新数据，跳转到NormalLayer
    if (dynamic_cast<MB_LayerPerfectRaceRule*>(pSender)
        || dynamic_cast<MB_LayerGroupPlayerList*>(pSender)
        || dynamic_cast<MB_LayerGroupHistoryRecord*>(pSender)
        || dynamic_cast<MB_LayerFinalHistoryRecord*>(pSender)
        || dynamic_cast<MB_LayerGroupRecordLive*>(pSender)
        || dynamic_cast<MB_LayerPerfectRaceApply*>(pSender))
    {
        m_nDirection = kDirectionNone;
        goNormalLayer();
        return;
    }
    
    //标记收到数据强制打开窗口
    if(dynamic_cast<MB_PerfectRaceEntrance*>(pSender))
    {
        m_bOpenNewWnd = true;
    }
    
    //请求数据跳转
    m_nDirection = kDirectionNormal;
    MB_Message::sharedMB_Message()->showMessage("",15);
    sendrace_info();
}

void MB_PerfectRaceInterface::sendrace_history(uint8_t nStep,uint8_t nGroupId,uint16_t nStart,uint16_t nCount)
{
    SOCKET_REQUEST_START(CS_RACE_HISTORY);
    packet->writeU8(nStep);
    packet->writeU8(nGroupId);
    packet->writeU16(nStart);
    packet->writeU16(nCount);
    SOCKET_REQUEST_END(SC_RACE_HISTORY, NULL);
}

void MB_PerfectRaceInterface::sendrace_replay(uint64_t nReplayId)
{
    SOCKET_REQUEST_START(CS_RACE_REPLAY);
    packet->WriteUINT64(nReplayId);
    SOCKET_REQUEST_END(SC_RACE_REPLAY, NULL);
}

void MB_PerfectRaceInterface::sendrace_fight_list(uint8_t nGroupId)
{
    SOCKET_REQUEST_START(CS_RACE_FIGHT_LIST);
    packet->writeU8(nGroupId);
    SOCKET_REQUEST_END(SC_RACE_FIGHT_LIST, NULL);
}

void MB_PerfectRaceInterface::sendrace_sign()
{
    SOCKET_REQUEST_START(CS_RACE_SIGN);
    SOCKET_REQUEST_END(SC_RACE_SIGN, NULL);
}

void MB_PerfectRaceInterface::sendrace_info()
{
    SOCKET_REQUEST_START(CS_RACE_INFO);
    SOCKET_REQUEST_END(SC_RACE_INFO, NULL);
}

void MB_PerfectRaceInterface::sendrace_enter()
{
    SOCKET_REQUEST_START(CS_RACE_ENTER);
    SOCKET_REQUEST_END(CS_RACE_ENTER, NULL);
}

void MB_PerfectRaceInterface::sendrace_leave()
{
    SOCKET_REQUEST_START(CS_RACE_LEAVE);
    SOCKET_REQUEST_END(CS_RACE_LEAVE, NULL);
}

void MB_PerfectRaceInterface::sendrace_is_open()
{
    SOCKET_REQUEST_START(CS_RACE_IS_OPEN);
    SOCKET_REQUEST_END(SC_RACE_IS_OPEN, NULL);
}

void MB_PerfectRaceInterface::sendrace_guess_info()
{
    SOCKET_REQUEST_START(CS_RACE_GUESS_INFO);
    SOCKET_REQUEST_END(SC_RACE_GUESS_INFO, NULL);
}
/*
 message sendrace_guess[id=13431]{
 required        int32           guessCoin               =1;
 required        int32           roleID                  =2;
 }
 */
void MB_PerfectRaceInterface::sendrace_guess(uint32_t nRoleID,uint32_t nGuessCoin)
{
    SOCKET_REQUEST_START(CS_RACE_GUESS);
    packet->writeU32(nGuessCoin);
    packet->writeU32(nRoleID);
    SOCKET_REQUEST_END(SC_RACE_GUESS, NULL);
}
void MB_PerfectRaceInterface::sendrace_auto_unsign()
{return; // 1.0.5
    SOCKET_REQUEST_START(CS_RACE_AUTO_UNSIGN);
    SOCKET_REQUEST_END(SC_RACE_AUTO_UNSIGN, NULL);
}

void MB_PerfectRaceInterface::sendrace_auto_sign()
{return;// 1.0.5
    SOCKET_REQUEST_START(CS_RACE_AUTO_SIGN);
    SOCKET_REQUEST_END(SC_RACE_AUTO_SIGN, NULL);
}

/*
 message recvrace_info[id=13413]{
 required        int8            status                  = 1;//活动的阶段:0未开启，1报名...
 required        int32           timestamp               = 2;//当前状态结束的时间戳，为0表示永久等待
 required        int16           session_id              = 3;//当前是第几届
 required        bool            is_sign                 = 4;//是否报名
 repeated        p_race_pos      list                    = 5;//已出的八强对阵
 required        string          champion_name           = 6;//精灵王名字
 required        int8            self_group_id           = 7;//自己所在分组ID
 required        bool            autoSign                = 8;//是否自动报名
 }
 */
void MB_PerfectRaceInterface::recvrace_info(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nStep);
    pRecv->readU32(&m_nTimeStap);
    pRecv->readU16(&m_nSessionId);
    pRecv->readU8(&m_bIsSign);
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    m_pRaceRecordList->removeAllObjects();
    MB_RacePos* pRaceRecord = NULL;
    
    
//    CCLOG("-------------------------");
//    CCLOG("当前状态：%d",m_nStep);
    for (uint16_t i=0; i<count; ++i)
    {
        pRaceRecord = new MB_RacePos;
        if (pRaceRecord->read(pRecv))
        {
            m_pRaceRecordList->addObject(pRaceRecord);
//            CCLOG("位置:%d  RoleId:%ld",pRaceRecord->getPos(),pRaceRecord->getRoleId());
        }
        CC_SAFE_RELEASE_NULL(pRaceRecord);
    }
//    CCLOG("-------------------------");
    char* pName = pRecv->ReadString();
    if (pName)
    {
        m_szKingName = pName;
        CC_SAFE_FREE(pName);
    }
    
    pRecv->readU8(&m_nGroupId);
    
    pRecv->readU8(&m_bAutoSign);
    
    //收到消息界面跳转情况
    //1、在主界面和报名界面直接更新
     if(m_bOpenRaceMainOrRaceApply)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        goNormalLayer();
    }
    else
    {
       MB_Message::sharedMB_Message()->removeALLMessage();
        if (m_nDirection == kDirectionNormal && m_bOpenNewWnd)      //强制打开窗口
        {
            goNormalLayer();
            m_bOpenNewWnd = false;
        }
    }
    
    m_bTimeCountDownRuning = true;
}

bool MB_PerfectRaceInterface::getIsLiving()
{
    int step = getStep();
    if (step > STATUS_WAIT_PRE_FIHGT1)
    {
        return (step % 2) != 0;
    }
    
    return false;
}
/*
// 通知客户端华丽大赛是否开放
message recvrace_is_open[id=13421]{
    required        bool            is_open                 = 1;//是否开放华丽大赛
}
 */
void MB_PerfectRaceInterface::recvrace_is_open(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_bCanEnter);
}

void MB_PerfectRaceInterface::onPreRecordClicked(CCObject* pSender)
{
    if (getSessionId()==1)
    {
        MB_Message::sharedMB_Message()->showMessage("本届是第一届霸主之战");
    }
    else
    {
        m_nDirection = kDirectionPreRecord;
        onEntryClicked(NULL);
    }
}

/*
 #define STATUS_NOT_OPEN            0
 #define STATUS_SIGN                1
 #define STATUS_WAIT_PRE_FIHGT1     2
 #define STATUS_PRE_FIGHT1          3
 #define STATUS_WAIT_PRE_FIHGT2     4
 #define STATUS_PRE_FIGHT2          5
 #define STATUS_WAIT_PRE_FIHGT3     6
 #define STATUS_PRE_FIGHT3          7
 #define STATUS_WAIT_PRE_FIHGT4     8
 #define STATUS_PRE_FIGHT4          9
 #define STATUS_WAIT_PRE_FIHGT5     10
 #define STATUS_PRE_FIGHT5          11
 #define STATUS_WAIT_PRE_FIHGT6     12
 #define STATUS_PRE_FIGHT6          13
 #define STATUS_WAIT_PRE_FIHGT7     14
 #define STATUS_PRE_FIGHT7          15
 #define STATUS_WAIT_PRE_FIHGT8     16
 #define STATUS_PRE_FIGHT8          17
 #define STATUS_WAIT_FOUR_FIGHT     18
 #define STATUS_FOUR_FIGHT          19
 #define STATUS_WAIT_TWO_FIGHT      20
 #define STATUS_TWO_FIGHT           21
 #define STATUS_WAIT_FINAL_FIGHT    22
 #define STATUS_FINAL_FIGHT         23
*/
int MB_PerfectRaceInterface::getGroupRaceStatus(int Group)
{
    if (Group < 1 || Group > 9 || m_nStep < 2)
    {
        return kRaceStatusUnknow;
    }
    
    if (m_nStep > 17)
    {
        return kRaceStatusOver;
    }
    
    int step = Group * 2;
    
    if (m_nStep == step)
    {
        return kRaceStatusReady;
    }
    if (m_nStep == (step+1))
    {
        return kRaceStatusLiving;
    }
    if (m_nStep > step)
    {
        return kRaceStatusOver;
    }
    
    return kRaceStatusReady;
}

//void MB_PerfectRaceInterface::onRuleClicked(CCObject* pSender)
//{
//    MB_ResWindow* pWnd = createRuleDialog();
//    if (pWnd)
//    {
//        replaceMainSceneSubLayer(pWnd);
//    }
//    else
//    {
//        CCLOG("show rule dialog error");
//    }
//}

void MB_PerfectRaceInterface::onGroupRecordClicked(CCObject* pSender)
{
    MB_ResWindow* pLayer = createGroupRecordDialog();
    if (pLayer)
    {
        replaceMainSceneSubLayer(pLayer);
    }
}

void MB_PerfectRaceInterface::onLiveingClicked(CCObject* pSender)
{
    goLiving(pSender);
}
void MB_PerfectRaceInterface::goLiving(CCObject* pSender)
{
    MB_ResWindow* pWnd = NULL;
    if (getStep() == 0)
    {
        pWnd = createFinalLivingDialog();
    }
    else
    {
        pWnd = createGroupLivingDialog();
    }
    if (pWnd)
    {
        replaceMainSceneSubLayer(pWnd);
    }
    else
    {
        CCLOG("show living dialog error");
    }
}
void MB_PerfectRaceInterface::onOpenGroup(int nGroupId)
{
    MB_ResWindow* pWnd = createGroupPlayerDialog(nGroupId);
    if (pWnd)
    {
        replaceMainSceneSubLayer(pWnd);
    }
    else
    {
        CCLOG("enter group player dialog error");
    }
}

void MB_PerfectRaceInterface::autoTimeCountDown()
{
    if(!m_bTimeCountDownRuning || !m_bCanEnter)return;

    int lefttime = getTimeStap() - MB_ClientSocket::getInstance()->getServerTime();

    if (lefttime < 0 && !getIsLiving())
    {
        sendrace_info();
    }
}

void MB_PerfectRaceInterface::goNormalLayer()
{
    if (getStep() == STATUS_SIGN)
    {
        MB_ResWindow* pWnd = createApplyDialog();
        if (pWnd)
        {
            replaceMainSceneSubLayer(pWnd);
            PlayRoleSound(kSoundEnterRace);
        }
        else
        {
            CCLOG("enter apply window error");
        }
    }
    else
    {
        MB_ResWindow* pWnd = createFunctionDialog();
        if (pWnd)
        {
            replaceMainSceneSubLayer(pWnd);
            PlayRoleSound(kSoundEnterRace);
        }
        else
        {
            CCLOG("enter main window error");
        }
    }
}

void MB_PerfectRaceInterface::goPreRecordLayer()
{
    MB_Message::sharedMB_Message()->showMessage("未开放的功能");
}

//void MB_PerfectRaceInterface::goGroupRecordLayer()
//{
//    MB_ResWindow* pWnd = MB_LayerGroupPlayerList::create();
//    if (pWnd)
//    {
//        replaceMainSceneSubLayer(pWnd);
//    }
//    else
//    {
//        CCLOG("enter group player list error");
//    }
//}

void MB_PerfectRaceInterface::goGroupRecordLayer(int nGroup)
{
    MB_ResWindow* pLayer = createGroupRecordDialogByGroupID(nGroup);
    if (pLayer)
    {
        replaceMainSceneSubLayer(pLayer);
    }
}

CCArray* MB_PerfectRaceInterface::queryFightPlayerListByGroupId(int nGroupId)
{
    int index = nGroupId-1;
    if (index<0 || index>8)
    {
        return NULL;
    }
    
    return m_pFighterList[index];
}

CCArray* MB_PerfectRaceInterface::queryRecordListByGroupId(int nGroupId)
{
    int index = nGroupId-1;
    if (index<0 || index>8)
    {
        return NULL;
    }
    
    return m_pRecordList[index];
}


/*
 message recvrace_fight_list[id=13409]{
 required        int8              group_id                =1;//分组的编号1至8
 repeated        p_race_fighter    fighter_list            =2;//参赛者列表
 }
 */
void MB_PerfectRaceInterface::recvrace_fight_list(MB_MsgBuffer* pRecv)
{
    uint8_t u8 = 0;
    pRecv->readU8(&u8);
    
    if (u8 > 8 || u8 == 0)
    {
        return;
    }
    
    CCArray *pArray = m_pFighterList[u8-1];
    if (pArray == NULL)
    {
        pArray = new CCArray;
        m_pFighterList[u8-1] = pArray;
    }
    
    pArray->removeAllObjects();
    
    uint16_t u16 = 0;
    pRecv->readU16(&u16);
    
    MB_RaceFighter* pFighter = NULL;
    for (uint16_t i=0; i<u16; ++i)
    {
        pFighter = new MB_RaceFighter;
        if (pFighter->read(pRecv))
        {
            pArray->addObject(pFighter);
        }
        
        CC_SAFE_RELEASE_NULL(pFighter);
    }
}

void MB_PerfectRaceInterface::sendrace_pos_history(uint8_t nPos)
{
    SOCKET_REQUEST_START(CS_RACE_POS_HISTORY);
    packet->writeU8(nPos);
    SOCKET_REQUEST_END(SC_RACE_POS_HISTORY, NULL);
}

MB_RacePos* MB_PerfectRaceInterface::queryFinalPlayerByPos(int pos)
{
    MB_RacePos* pTarget = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRaceRecordList, MB_RacePos*, pTarget)
    {
        if (pTarget->getPos() == pos)
        {
            return pTarget;
        }
    }
    return NULL;
}

MB_RacePos* MB_PerfectRaceInterface::queryFinalPlayerByRoleID(uint32_t nRoleID,uint16_t nMaxPos)
{
    MB_RacePos* pTarget = NULL;
    CCARRAY_FOREACH_4TYPE(m_pRaceRecordList, MB_RacePos*, pTarget)
    {
        if (pTarget->getRoleId() == nRoleID && nMaxPos >= pTarget->getPos())
        {
            return pTarget;
        }
    }
    return NULL;
}

/*
 // 新的战斗
 message     recvrace_new_fight[id=13401]{
 required        p_race_rec           new_fight         =1;//新的战斗
 }
 */
void MB_PerfectRaceInterface::recvrace_new_fight(MB_MsgBuffer* pRecv)
{
    MB_RaceRecord* pRecord = new MB_RaceRecord;
    if (pRecord->read(pRecv))
    {
        int index = pRecord->getGroupId() - 1;
        if (index>=0 && index < 8)
        {
            if (m_pRecordList[index] == NULL)
            {
                m_pRecordList[index] = new CCArray;
            }
            m_pRecordList[index]->addObject(pRecord);
        }
        CC_SAFE_RELEASE_NULL(pRecord);
    }
}

/*
 // 返回对阵图对应位置的战斗历史信息
 message recvrace_pos_history[id=13418]{
 required        int8            pos                  =1;//对阵图对应的位置
 required        p_race_rec      race_rec             =2;//战斗历史信息
 }

 */
void MB_PerfectRaceInterface::recvrace_pos_history(MB_MsgBuffer* pRecv)
{
    uint8_t pos = 0;
    pRecv->readU8(&pos);
    
    MB_RaceRecordWithPos* pRecord = queryFinalRecordByPos(pos);
    if (pRecord == NULL)
    {
        pRecord = new MB_RaceRecordWithPos(pos);
        pRecord->read(pRecv);
        m_pFinalRecord->addObject(pRecord);
        //CCLOG("AtkRoleId:%ld DefRoleId:%ld pos: %d",pRecord->getAtkRoleId(),pRecord->getDefRoleId(),pRecord->getPos());
    }
    
    if (pos == m_nTargetPosRecord)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        openFinalRecord(pRecord);
    }
}

/*
// 更新直播结束后新产生的小组第一
message recvrace_new_first[id=13419]{
    required        p_race_pos      new_pos              =1;//新产生的小组第一信息
}*/
void MB_PerfectRaceInterface::recvrace_new_first(MB_MsgBuffer* pRecv)
{
    MB_RacePos* pRaceRecord = new MB_RacePos;
    if (pRaceRecord->read(pRecv))
    {
        m_pRaceRecordList->addObject(pRaceRecord);
//        CCLOG("新产生的小组第一信息  位置:%d  RoleId:%ld",pRaceRecord->getPos(),pRaceRecord->getRoleId());
    }
    CC_SAFE_RELEASE_NULL(pRaceRecord);
}

/*
// 更新华丽大赛状态和倒计时时间
message recvrace_new_status[id=13420]{
    required        int8            status                  = 1;//活动的阶段:0未开启，1报名...
    required        int32           timestamp               = 2;//当前状态结束的时间戳，为0表示永久等待
}
*/
void MB_PerfectRaceInterface::recvrace_new_status(MB_MsgBuffer* pRecv)
{
    pRecv->readU8(&m_nStep);
    pRecv->readU32(&m_nTimeStap);
    //服务器没有推送 4强、半决赛、决赛结果。
    if(m_nStep == STATUS_WAIT_TWO_FIGHT         //请求4强
       ||m_nStep == STATUS_NOT_OPEN             //请求决赛
       ||m_nStep == STATUS_WAIT_FINAL_FIGHT)    //请求半决赛
    {
//        CCLOG("请求数据,当前状态：%d",m_nStep);
        sendrace_info();
    }
}

MB_RaceRecordWithPos* MB_PerfectRaceInterface::queryFinalRecordByPos(uint8_t nPos)
{
    MB_RaceRecordWithPos* pTarget = NULL;
    
    CCARRAY_FOREACH_4TYPE(m_pFinalRecord, MB_RaceRecordWithPos*, pTarget)
    {
        if (nPos == pTarget->getPos())
        {
            return pTarget;
        }
    }
    return NULL;
}

void MB_PerfectRaceInterface::openFinalRecord(MB_RaceRecordWithPos* pRecrod)
{
    MB_ResWindow* pWnd = createFinalRecordDialog(pRecrod);
    if (pWnd)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,100);
    }
    else
    {
        CCLOG("enter final record error");
    }

}

void MB_PerfectRaceInterface::onRequestRecord(uint64_t uid)
{
    
}

/*
 message recvrace_auto_sign[id=13424]{
 required        int8            reason_code             = 1;//错误提示码，0表示成功
 }
 */
void MB_PerfectRaceInterface::recvrace_auto_unsign(MB_MsgBuffer* pRecv)
{
    uint8_t ret = 0;
    pRecv->readU8(&ret);
    if (ret == 0)
    {
        m_bAutoSign = false;
    }
}

/*
 message recvrace_auto_unsign[id=13426]{
 required        int8            reason_code             = 1;//错误提示码，0表示成功
 }
 */
void MB_PerfectRaceInterface::recvrace_auto_sign(MB_MsgBuffer* pRecv)
{
    uint8_t ret = 0;
    pRecv->readU8(&ret);
    if (ret == 0)
    {
        m_bAutoSign = true;
    }
}

void MB_PerfectRaceInterface::sendrace_self_record()
{
    SOCKET_REQUEST_START(CS_RACE_SELF_RECORD);
    SOCKET_REQUEST_END(SC_RACE_SELF_RECORD, NULL);
}

/*
 message recvrace_self_history[id=13428]{
 repeated        p_race_rec      history_list            =1;//战报列表
 }

 */
void MB_PerfectRaceInterface::recvrace_self_record(MB_MsgBuffer* pRecv)
{
    uint16_t repeated = 0;
    pRecv->readU16(&repeated);
    MB_RaceRecord* pRecord = NULL;
    m_pSelfRecord->removeAllObjects();
    for (uint16_t i=0; i<repeated; ++i)
    {
        pRecord = new MB_RaceRecord;
        if (pRecord->read(pRecv))
        {
            m_pSelfRecord->addObject(pRecord);
        }
        CC_SAFE_RELEASE_NULL(pRecord);
    }
}
