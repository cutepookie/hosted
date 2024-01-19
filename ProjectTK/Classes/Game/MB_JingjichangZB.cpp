//
//  MB_JingjichangZB.cpp
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#include "MB_JingjichangZB.h"
#include "MB_Championship.h"
#include <stdio.h>
#include <time.h>
#include "MB_RoleData.h"
#include "MB_FunctionMgr.h"
#include "MB_MailList.h"
#include "MB_SceneGame.h"
#include "MB_MailData.h"
#include "MB_LayerShopMain.h"
MB_JingjichangZB::MB_JingjichangZB()
{
    m_pContainer = NULL;
    m_pInterface = NULL;
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PVPTIMES,MB_JingjichangZB);
    SOCKET_MSG_REGIST(SC_PVP_EIGHT_REPLAY, MB_JingjichangZB);
    SOCKET_MSG_REGIST(SC_PVP_GET_FIRST_EIGHT_REPLAYS, MB_JingjichangZB);
    SOCKET_MSG_REGIST(SC_DAILY_DRAW, MB_JingjichangZB);
    SOCKET_MSG_REGIST(SC_HIST_UNREADNUM, MB_JingjichangZB);
    SOCKET_MSG_REGIST(SC_HIST_GET_LIST,MB_JingjichangZB);

    m_bShowRoleInfoPanel = true;
}




MB_JingjichangZB::~MB_JingjichangZB()
{
    CC_SAFE_RELEASE(m_pContainer);
    
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PVPTIMES);
    SOCKET_MSG_UNREGIST(SC_PVP_EIGHT_REPLAY);
    SOCKET_MSG_UNREGIST(SC_PVP_GET_FIRST_EIGHT_REPLAYS);
    SOCKET_MSG_UNREGIST(SC_HIST_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
    SOCKET_MSG_UNREGIST(SC_HIST_UNREADNUM);
}
bool MB_JingjichangZB::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_Championship*>(pDataSource);
    if (m_pInterface)
    {
        return true;
    }
    return false;
}
bool MB_JingjichangZB::hasTitleReward()
{
    bool bTitle = false;
    DailyRewardValue* tempValue = NULL;
    for (int i = 0; i < MB_ItemMgr::getInstance()->getDailyRewardArray()->count(); i++)
    {
        tempValue = (DailyRewardValue*)MB_ItemMgr::getInstance()->getDailyRewardArray()->objectAtIndex(i);
        if (tempValue->getType() == kRewardTypeTitle)
        {
            if (tempValue->getIsGet() == kRewardGetTypeReady)
            {
                bTitle = true;
            }
        }
    }
    return bTitle;
}

bool MB_JingjichangZB::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/pvp_layer_list_ZB.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    NSGameHelper::adjustScrollNode(m_pContainer);
    dirty();
    onResetWnd();
    
    MB_MailList* pmaillist = MB_MailList::create();
    pmaillist->setScrollSize(m_pContainer->getContentSize());
    pmaillist->setCurrentTable(kmMailsTable_Pvp);
    m_pContainer->addChild(pmaillist);
    return true;
}



bool MB_JingjichangZB::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainer", CCNode*, m_pContainer);
    
    return false;
}

SEL_MenuHandler MB_JingjichangZB::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char* pSelectorName)
{

    return NULL;
}


SEL_CCControlHandler MB_JingjichangZB::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


void MB_JingjichangZB::recvpvp_get_first_eight_replays(MB_MsgBuffer* pBuffer)
{
//    MB_LyaerReportTop8* pLayer = MB_LyaerReportTop8::create();
//    if (pLayer)
//    {
//        m_pContainer->removeAllChildren();
//        m_pContainer->addChild(pLayer);
//        pLayer->setData(pBuffer);
//        pLayer->setScrollSize(m_pContainer->getContentSize());
//    }
    MB_Message::sharedMB_Message()->removeALLMessage();
}


void MB_JingjichangZB::recvpvp_eight_replay(MB_MsgBuffer* pBuffer)
{
    // Play record here
    uint8_t ret = 0;
    pBuffer->readU8(&ret);
    if (ret == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("战报已经过期");
        return;
    }
    MB_NetStructFight fighteStruct = MB_NetStructFight();
    recvfight *fight_replay =fighteStruct.recvfight_request(pBuffer);
    
    EightReplay(fight_replay);
}


void MB_JingjichangZB::EightReplay(recvfight *fight_replay)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    fight_replay->type = kFightResultTypeReplay;
    CCScene* pScene = CCTransitionSlideInR::create(0.2f,
                                                   MB_SceneGame::scene(fight_replay,
                                                                       m_pSelectReportInfo.defenderName.c_str(),
                                                                       m_pSelectReportInfo.attackerName.c_str(),
                                                                       m_pSelectReportInfo.replayUid,
                                                                       kmMailsTable_Pvp, kReplayTypeEight)
                                                   );
    
    CCDirector::sharedDirector()->pushScene(pScene);
}



void MB_JingjichangZB::onResetWnd(void)
{
}



void MB_JingjichangZB::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_ROLE_UPDATE_PVPTIMES:
        case SC_PVP_GET_FIRST_EIGHT_REPLAYS:
            recvpvp_get_first_eight_replays(recvPacket);
            break;
        case SC_PVP_EIGHT_REPLAY:
            recvpvp_eight_replay(recvPacket);
            break;
        case SC_DAILY_DRAW:
        {
        }
            break;
        case SC_HIST_UNREADNUM:
            onResetWnd();
            break;
        case SC_HIST_GET_LIST:
            onResetWnd();
            break;
        default:
            break;
    }
}


void MB_JingjichangZB::onBeatBackClicked(MB_NodeReportBox* pBoxObj)
{
    
}
void MB_JingjichangZB::onReplayClicked(MB_NodeReportBox* pBoxObj)
{
    uint64_t uid = pBoxObj->getReportUid();
    pBoxObj->getReportInfo(m_pSelectReportInfo);
    ((MB_Championship*)m_pInterface)->setFightReplayUID(uid);
    ((MB_Championship*)m_pInterface)->sendpvp_eight_replay(uid);
}

void MB_JingjichangZB::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if (MB_DataPVPMgr::getInstance()->getGoFight())
    {
        MB_DataPVPMgr::getInstance()->sendpvp_fight(MB_DataPVPMgr::getInstance()->getFightRoleID(), MB_DataPVPMgr::getInstance()->getFightRank());
        MB_DataPVPMgr::getInstance()->setGoFight(false);
    }
}

