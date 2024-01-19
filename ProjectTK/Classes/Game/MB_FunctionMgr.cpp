//
//  MB_FunctionMgr.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//
#include <time.h>
#include "MB_FunctionMgr.h"
#include "MB_RoomEntry.h"
#include "MB_FunctionModule.h"
#include "MB_TaskSystemInterface.h"
#include "MB_ToyShopInterface.h"
#include "MB_CommandFormation.h"
#include "MB_CommandActivaty.h"
#include "MB_CommandFriend.h"
#include "MB_CommandHome.h"
#include "MB_ComposeInterface.h"
#include "MB_EmailInterface.h"
#include "MB_SpriteRoomInterface.h"
#include "MB_ResearchInstituteInterface.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_AbsolvedInterface.h"
#include "MB_RecoveryEnergyInterface.h"
#include "MB_ChangeCoinInterface.h"
#include "MB_FunctionBigWorldInterface.h"
#include "MB_FunctionActivatedTip.h"
#include "MB_GlobelModalDlgMsgQueue.h"
#include "MB_RechargeSystem.h"
#include "MB_AchievementInterface.h"
#include "MB_DailyInterface.h"
#include "MB_SynopsisConfig.h"
#include "MB_SystemMailData.h"
#include "MB_ConfigActivatyInterface.h"
#include "MB_FunctionRule.h"
#include "MB_IngotsShopInterface.h"
#include "MB_PayShopInterface.h"
#include "MB_ItemShopInterface.h"
#include "MB_MysteryShopInterface.h"
#include "MB_ShowPicInterface.h"
#include "MB_BackpackInterface.h"
#include "MB_FunctionBudokanInterface.h"
#include "MB_RefreshShopInterface.h"
#include "MB_YeShiJieInterface.h"
#include "MB_GiftsInterface.h"
#include "MB_FunctionRanking.h"
#include "MB_FunctionFestival.h"
#include "MB_RuleFightInterface.h"
#include "MB_FunctionKingInterface.h"
#include "MB_FunctionTrainerRoad.h"
#include "MB_FunctionValentineDay.h"
#include "MB_FunctionTrainerTroveInterface.h"
#include "MB_FunctionNoRuleFight.h"
#include "MB_FunctionAprCardInterface.h"
#include "MB_NodeHoverEntry.h"
#include "MB_AbsolvedConfigure.h"

MB_FunctionMgr* MB_FunctionMgr::m_pSingletonInstance = NULL;

MB_FunctionOperator::MB_FunctionOperator()
{
    
}

MB_FunctionOperator::~MB_FunctionOperator()
{
    std::map<int,CCFunctionInterface*>::iterator it = m_pFunctionContainer.begin();
    for (; it != m_pFunctionContainer.end(); ++it)
    {
        CC_SAFE_RELEASE_NULL(it->second);
    }
    m_pFunctionContainer.clear();
}

MB_FunctionMgr::MB_FunctionMgr()
{
    
}

MB_FunctionMgr::~MB_FunctionMgr()
{
    
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

time_t timegm2( struct tm *tm ) {
    time_t t = mktime( tm );
    return t + localtime( &t )->tm_gmtoff;
}
#endif



static int nServerZone = 8;

//返回伺服器今天指定int hour,int min,int sec 的時間戳
static time_t gettime_tWithServerZone(int hour,int min,int sec)
{
    time_t tNow = MB_ClientSocket::getInstance()->getServerTime();
    struct tm *pTemp = gmtime(&tNow);
    
    int n = hour - nServerZone;     //hour是相對伺服器時區的值，这里是用UTC計算，故减去伺服器時區
    if(n<0)n+=24;
    
    pTemp->tm_hour = n;
    pTemp->tm_min = min;
    pTemp->tm_sec = sec;
    return timegm2(pTemp);
}
MB_FunctionMgr* MB_FunctionMgr::getInstance()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new MB_FunctionMgr;
        if (!m_pSingletonInstance->init())
        {
            CCLog("[Error]:init function manapet");
        }
        else
        {
            time_t t = gettime_tWithServerZone(23,59,59);
            t = t - MB_ClientSocket::getInstance()->getServerTime();
            if(t <= 5)
            {
                m_pSingletonInstance->onDayPassed();
            }
            else
            {
                CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(MB_FunctionMgr::onDayPassed), m_pSingletonInstance, t+5, false);
            }
        }
    }
    return m_pSingletonInstance;
}

void MB_FunctionMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pSingletonInstance);
    MB_GlobelModalDlgMsgQueue::destroyInstance();
    MB_RechargeSystem::destroyInstance();
    MB_SynopsisConfig::destroyInstance();
    MB_SystemDataMgr::destroyInstance();
    MB_FunctionRule::destroyInstance();
    MB_AbsolvedConfigure::destroyInstance();
}

void MB_FunctionOperator::insertFunction(int iType,CCFunctionInterface* pInterface)
{
    assert(pInterface);
    
    safeRelease(iType);
    
    m_pFunctionContainer[iType] = pInterface;
}

void MB_FunctionOperator::removeFunction(int iType)
{
    safeRelease(iType);
}

void MB_FunctionOperator::safeRelease(int iType)
{
    CCFunctionInterface* pInterface = m_pFunctionContainer[iType];
    if (pInterface)
    {
        pInterface->release();
        m_pFunctionContainer[iType] = NULL;
        m_pFunctionContainer.erase(iType);
    }
}

bool MB_FunctionOperator::queryFunctionByType(int iType,CCFunctionInterface** lpInterface)
{
    if (m_pFunctionContainer.count(iType)==0)
    {
        return false;
    }
    
    CCFunctionInterface* pInterface = m_pFunctionContainer[iType];
    
    if (pInterface != NULL)
    {
        *lpInterface = pInterface;
        return pInterface != NULL;
    }
    
    return false;
}

bool MB_FunctionMgr::onRoleLevelUp(int nRoleLevel)
{
    std::map<int,CCFunctionInterface*>::iterator it = m_pFunctionContainer.begin();
    while (it != m_pFunctionContainer.end())
    {
        // 若已处理，则返回true,否则返回false
        if (it->second->onRoleLevelUp(nRoleLevel))
        {
            return true;
        }
        ++it;
    }
    
    return false;
}

CCArray* MB_FunctionMgr::getFunctionLevelUpTips(int nLevel)
{
    std::map<int,CCFunctionInterface*>::iterator it = m_pFunctionContainer.begin();
    MB_ResWindow* pTemp = NULL;
    CCArray* pArray = CCArray::create();
    while (it != m_pFunctionContainer.end())
    {
        pTemp = it->second->createFunctionTipsByLevel(nLevel);
        if (pTemp)
        {
            pArray->addObject(pTemp);
        }
        ++it;
    }
    return pArray;
}

bool MB_FunctionMgr::init()
{
    // command
    insertFunction(kFunctionAbsolved, new MB_AbsolvedInterface);
    insertFunction(kFunctionRoom, new MB_RoomEntry);
    insertFunction(kFunctionHome, new MB_CommandHome);
    insertFunction(kFunctionFriend, new MB_CommandFriend);
    insertFunction(kFunctionFormation, new MB_CommandFormation);
    insertFunction(kFunctionActivaty, new MB_CommandActivaty);
    
    // PageVillage
    insertFunction(kFunctionToy, new MB_ToyShopInterface);
    insertFunction(kFunctionTask, new MB_TaskSystemInterface);
    insertFunction(kFunctionCompose, new MB_ComposeInterface);
    insertFunction(kFunctionEmail, new MB_EmailInterface);
    insertFunction(kFunctionAchievement, new MB_AchievementInterface);
    insertFunction(kFunctionDaily, new MB_DailyInterface);

    // PageBigWorld
    insertFunction(kFunctionArena, new MB_Championship);
    insertFunction(kFunctionPetPackage, new MB_SpriteRoomInterface);
    insertFunction(kFunctionResearchInstitute, new MB_ResearchInstituteInterface);
    insertFunction(kFunctionPerfectRace, new MB_PerfectRaceInterface);

    
    // homeland
//    insertFunction(kFunctionHome, new MB_CommandHome);
    insertFunction(kFunctionBigWorld, new MB_FunctionBigWorldInterface);
    
    
    //event
    insertFunction(kActivatyRecoverEnergy, new MB_RecoveryEnergyInterface);
    insertFunction(kFunctionMaoXian, new MB_AdventureEntry);
    
    insertFunction(kFunctionYeShiJie, new MB_YeShiJieInterface);
    insertFunction(kActivatyChangeCoin, new MB_ChangeCoinInterface);
    
    insertFunction(kActivatyConfig, new MB_ConfigActivatyInterface);
    
    
    //worldking
//    insertFunction(kFunctionWorldWar, new MB_WorldKingInterface);
//    insertFunction(kFunction3v3, new MB_3v3MatchInterface);

    //shop
    insertFunction(kFunctionIngotsShop, new MB_IngotsShopInterface);
    insertFunction(kFunctionPayShop, new MB_PayShopInterface);
    insertFunction(kFunctionItemShop, new MB_ItemShopInterface);
    insertFunction(kFunctionMysteryShop, new MB_MysteryShopInterface);
    insertFunction(kFunctionRanking, new MB_FunctionRanking); // 排行榜
    
    insertFunction(kFunctionBudokan,new MB_FunctionBudokanInterface);
    insertFunction(kFunctionBackpack,new MB_BackpackInterface);
    insertFunction(kFunctionPic,new MB_ShowPicInterface);
    insertFunction(kFunctionRefreshShop, new MB_RefreshShopInterface);
    insertFunction(kFunctionRuleFight, new MB_RuleFightInterface);
    insertFunction(kFunctionKing,new MB_FunctionKingInterface);
    insertFunction(kFunctionTrainerRoad, new MB_FunctionTrainerRoad);
    insertFunction(kFunctionTrainerTrove,new MB_FunctionTrainerTroveInterface);
    insertFunction(kFunctionNoRuleFight, new MB_FunctionNoRuleFight);

    insertFunction(kFunctionAprCard, new MB_FunctionAprCardInterface);
    insertFunction(kActivatyGifts, new MB_GiftsInterface);
    
    //自定义活動
    insertFunction(kFunctionFestival, new MB_FunctionFestival);
    insertFunction(kFunctionValentineDay, new MB_FunctionValentineDay);
    return true;
}

MB_ResWindow* MB_FunctionMgr::getFunctionMainWndByType(int kType)
{
    CCFunctionInterface* pInterface = NULL;
    if (queryFunctionByType(kType, &pInterface))
    {
        return pInterface->createFunctionDialog();
    }
    
    return NULL;
}
void MB_FunctionMgr::onDayPassed()
{
    std::map<int,CCFunctionInterface*>::iterator it = m_pFunctionContainer.begin();
    while (it != m_pFunctionContainer.end())
    {
        it->second->onDayPassed();
        ++it;
    }
}
bool MB_FunctionMgr::goFunction(int kType,CCObject* pSender)
{
    MB_ResWindow* pWnd = NULL;
    CCFunctionInterface* pInterface = NULL;
    
    if (kType != kFunctionHome
//        && kType != kFunctionHomeLand
        && kType != kFunctionBigWorld)
    {
        if(queryFunctionByType(kType, &pInterface))
        {
            pInterface->onEntryClicked(pSender);
            
            return true;
        }
        return false;
    }
    
    pWnd = getFunctionMainWndByType(kType);
    if (pWnd)
    {
        //NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(MB_ResWindow::create());
        NSGameFunction::CCFunctionInterface::replaceMainSceneLayer(pWnd);
        NSGameFunction::CCFunctionInterface::removeUnusedResource();
        return true;
    }
    return false;
}

void MB_FunctionMgr::onLoadingScene()
{
    std::map<int,CCFunctionInterface*>::iterator it = m_pFunctionContainer.begin();
    while (it != m_pFunctionContainer.end())
    {
        it->second->onLoadingScene();
        ++it;
    }
    
    initPushMessage();
}

bool MB_FunctionMgr::bindEntry2Target(uint32_t kType,CCNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    
    CCFunctionInterface* pInterface = NULL;
    
    if(queryFunctionByType(kType, &pInterface))
    {
        if (!pInterface->allowShow())
        {
            return false;
        }
        MB_ResWindow* pWnd = pInterface->createEntryDialog();
        if (pWnd)
        {
            pNode->addChild(pWnd);
            return true;
        }
    }else
    {
        MB_NodeHoverEntry2* pInstance = new MB_NodeHoverEntry2();
        if (pInstance &&  pInstance->init() )
        {
            pInstance->setType(kType);
            pInstance->autorelease();
            pNode->addChild(pInstance);
            return true;
        }
    }
    
    return false;
}

bool MB_FunctionMgr::bindMainDialog2Target(uint32_t kType,CCNode* pNode)
{
    if (pNode == NULL)
    {
        return false;
    }
    CCFunctionInterface* pInterface = NULL;
    
    if(queryFunctionByType(kType, &pInterface))
    {
        MB_ResWindow* pWnd = pInterface->createFunctionDialog();
        if (pWnd)
        {
            pNode->addChild(pWnd);
            return true;
        }
    }
    
    return false;
}

static int getSecondsWithEndtime(int hour,int min,int second)
{
    int seconds = 0;
    
    time_t now = time(NULL);
    tm* pNow = localtime(&now);
    int lefthour = -pNow->tm_hour + hour;
    int leftmin = -pNow->tm_min + min;
    int leftsecond = -pNow->tm_sec + second;
    seconds = lefthour * 3600 + leftmin * 60 + leftsecond;
    return seconds;
}

/*
 3	PM 12:25:00	铃铃塔还有5分钟就開始了	15級以上	主人，玲玲塔副本已經開啟，快带我们去擊敗鳳王吧！！		0.8.0	陈明	2014-5-17
 4	PM 18:25:00	研究所还有5分钟就開始了	35級以上	主人，研究所副本已經開啟，快带我们去擊敗超梦吧！！		0.8.0	陈明	2014-5-17
 5	AM 7:58:00	無盡深渊開始了	25級以上	主人，無盡深渊副本已經開啟，快带我们去試练吧！！                0.8.0	陈明	2014-5-17
 
 enum kNotificationType{
 
 kNotificationTypeAdventrue,
 kNotificationTypePvp,
 kNotificationTypeOther,
 kNotificationTypeRocketTeam,
 };
 */
void MB_FunctionMgr::initPushMessage()
{

}

