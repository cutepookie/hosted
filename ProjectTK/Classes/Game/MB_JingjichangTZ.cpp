//
//  MB_JingjichangTZ.cpp
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#include "MB_JingjichangTZ.h"
#include "MB_Championship.h"
#include <stdio.h>
#include <time.h>
#include "MB_RoleData.h"
#include "MB_FunctionMgr.h"
#include "MB_MailList.h"
#include "MB_SceneGame.h"
#include "MB_MailData.h"
#include "MB_LayerShopMain.h"
#include "MB_NodePetDuiWuFang.h"
#include "MB_LayerPetEquipment.h"
#include "MB_ChampionshipFunctionDialog.h"
MB_JingjichangTZ::MB_JingjichangTZ()
{
    m_pNodeScroller = NULL;
    m_pFightPower = NULL;
    m_prest_count = NULL;
    m_pContainer = NULL;
    m_pRest_recovery = NULL;
    m_pInterface = NULL;
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PVPTIMES,MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY,MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_PVP_EIGHT_REPLAY, MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_PVP_GET_FIRST_EIGHT_REPLAYS, MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_DAILY_DRAW, MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_HIST_UNREADNUM, MB_JingjichangTZ);
    SOCKET_MSG_REGIST(SC_HIST_GET_LIST,MB_JingjichangTZ);

    m_bShowRoleInfoPanel = true;
}




MB_JingjichangTZ::~MB_JingjichangTZ()
{
    CC_SAFE_RELEASE(m_pNodeScroller);
    CC_SAFE_RELEASE(m_pFightPower);
    CC_SAFE_RELEASE(m_prest_count);
    CC_SAFE_RELEASE(m_pContainer);
    CC_SAFE_RELEASE(m_pRest_recovery);
    
    
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PVPTIMES);
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
    SOCKET_MSG_UNREGIST(SC_PVP_EIGHT_REPLAY);
    SOCKET_MSG_UNREGIST(SC_PVP_GET_FIRST_EIGHT_REPLAYS);
    SOCKET_MSG_UNREGIST(SC_HIST_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
    SOCKET_MSG_UNREGIST(SC_HIST_UNREADNUM);
}
bool MB_JingjichangTZ::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_Championship*>(pDataSource);
    if (m_pInterface)
    {
        return true;
    }
    return false;
}
bool MB_JingjichangTZ::hasTitleReward()
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

bool MB_JingjichangTZ::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/pvp_layer_list_TZ.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    NSGameHelper::adjustScrollNode(m_pContainer);
    dirty();
    timeTick(0);
    schedule(schedule_selector(MB_JingjichangTZ::timeTick),1.0f);
    onResetWnd();
    
    MB_LayerPVPRanking* layer = MB_LayerPVPRanking::create(m_pContainer->getContentSize());
    m_pContainer->addChild(layer);
    
    return true;
}



bool MB_JingjichangTZ::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "rest_count", CCLabelBMFont*, m_prest_count);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainer", CCNode*, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "rest_recovery", CCLabelBMFont*, m_pRest_recovery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFightPower", CCLabelBMFont*, m_pFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroller", CCNode*, m_pNodeScroller);
    
    return false;
}

SEL_MenuHandler MB_JingjichangTZ::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char* pSelectorName)
{

    return NULL;
}


SEL_CCControlHandler MB_JingjichangTZ::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickTZDW",MB_JingjichangTZ::onClickTZDW);
    return NULL;
}


void MB_JingjichangTZ::recvpvp_get_first_eight_replays(MB_MsgBuffer* pBuffer)
{
    MB_LyaerReportTop8* pLayer = MB_LyaerReportTop8::create();
    if (pLayer)
    {
        m_pContainer->removeAllChildren();
        m_pContainer->addChild(pLayer);
        pLayer->setData(pBuffer);
        pLayer->setScrollSize(m_pContainer->getContentSize());
    }
    MB_Message::sharedMB_Message()->removeALLMessage();
}


void MB_JingjichangTZ::recvpvp_eight_replay(MB_MsgBuffer* pBuffer)
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


void MB_JingjichangTZ::EightReplay(recvfight *fight_replay)
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



void MB_JingjichangTZ::timeTick(float dt){
    
    char databuf[60];
    int  timeCount = 0;
    
    if(MB_RoleData::getInstance()->getPVPTimes() < MAX_PVP_RANKING)
    {
        timeCount = MB_RoleData::getInstance()->getNextPvpcvTime() - MB_ClientSocket::getInstance()->getServerTime();
    }
    
    if (timeCount < 0)
    {
        char* str = new char[32];
        sprintf(str, "%d/%d",MB_RoleData::getInstance()->getPVPTimes(), MAX_PVP_RANKING);
        m_prest_count->setString(str);
        CC_SAFE_DELETE_ARRAY(str);
        timeCount = 0;
    }
    sprintf(databuf, "00:%02d:%02d",timeCount/60,timeCount%60);
    m_pRest_recovery->setString(databuf);
    
    sprintf(databuf, "%llu", MB_TeamData::getInstance()->getFightPower());
    m_pFightPower->setString(databuf);
}


void MB_JingjichangTZ::onResetWnd(void)
{
    char* str = new char[32];
    sprintf(str, "%d/%d",MB_RoleData::getInstance()->getPVPTimes(), MAX_PVP_RANKING);
    m_prest_count->setString(str);
    CC_SAFE_DELETE_ARRAY(str);
    
    m_pNodeScroller->removeAllChildren();
    MB_NodePetDuiWuFang* npdw;
    if(teamV.size()==0)
    {
        for (int i = 0; i < CARD_IN_GAME; i++) {
            if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL){
                npdw = MB_NodePetDuiWuFang::create(MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID());
            }
            else {
                npdw = MB_NodePetDuiWuFang::create(-1);
            }
            npdw->setPosition(ccp( npdw->m_nWidth*(.5f + i),m_pNodeScroller->getContentSize().height/2));
            m_pNodeScroller->addChild(npdw);
        }
    }else
    {
        for (int i = 0; i < CARD_IN_GAME; i++) {
            npdw = MB_NodePetDuiWuFang::create(teamV[i]);
            npdw->setPosition(ccp( npdw->m_nWidth*(.5f + i),m_pNodeScroller->getContentSize().height/2));
            m_pNodeScroller->addChild(npdw);
        }
    }
    m_pNodeScroller->setContentSize(CCSize( npdw->m_nWidth*6,m_pNodeScroller->getContentSize().height));
    
}


void MB_JingjichangTZ::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_ROLE_BUY_ENERGY:
        {
            char* str = new char[32];
            sprintf(str, "%d/%d",MB_RoleData::getInstance()->getPVPTimes(), MAX_PVP_RANKING);
            m_prest_count->setString(str);
            CC_SAFE_DELETE_ARRAY(str);
        }
            break;
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


void MB_JingjichangTZ::onBeatBackClicked(MB_NodeReportBox* pBoxObj)
{
    
}
void MB_JingjichangTZ::onReplayClicked(MB_NodeReportBox* pBoxObj)
{
    uint64_t uid = pBoxObj->getReportUid();
    pBoxObj->getReportInfo(m_pSelectReportInfo);
    ((MB_Championship*)m_pInterface)->setFightReplayUID(uid);
    ((MB_Championship*)m_pInterface)->sendpvp_eight_replay(uid);
}

void MB_JingjichangTZ::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if (MB_DataPVPMgr::getInstance()->getGoFight())
    {
        MB_DataPVPMgr::getInstance()->sendpvp_fight(MB_DataPVPMgr::getInstance()->getFightRoleID(), MB_DataPVPMgr::getInstance()->getFightRank());
        MB_DataPVPMgr::getInstance()->setGoFight(false);
    }
}

void MB_JingjichangTZ::onClickTZDW(CCObject* pSender)
{
    MB_LayerPetEquipment* layer = MB_LayerPetEquipment::create();
    if (m_pSubLayer == NULL) {
        layer->isPopWindow = true;
//        pushWindow(layer,true);
        MB_TARGET_PARENT(MB_ChampionshipFunctionDialog, ptr)
        if(ptr)
        {
            ptr->pushWindow(layer,true);
        }
    }
}

