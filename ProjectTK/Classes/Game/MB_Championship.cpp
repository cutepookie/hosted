//
//  MB_Championship.cpp
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#include "MB_Championship.h"
#include "MB_ChampionshipFunctionDialog.h"
#include "MB_ChampionshipEntryDialog.h"
#include "MB_ChampionshipEntryDialog.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionConfig.h"
MB_Championship::MB_Championship()
{
}

MB_Championship::~MB_Championship()
{

}

void MB_Championship::sendpvp_eight_replay(uint64_t uid)
{
    SOCKET_REQUEST_START(CS_PVP_EIGHT_REPLAY);
    packet->WriteUINT64(uid);
    SOCKET_REQUEST_END(SC_PVP_EIGHT_REPLAY,MB_Championship::onMsgRecv);
}

void MB_Championship::sendpvp_get_first_eight_replays()
{    
    SOCKET_REQUEST_START(CS_PVP_GET_FIRST_EIGHT_REPLAYS);
    SOCKET_REQUEST_END(SC_PVP_GET_FIRST_EIGHT_REPLAYS, MB_Championship::onMsgRecv);
    MB_Message::sharedMB_Message()->showMessage("",15);
}

void MB_Championship::onEntryClicked(CCObject* pSender)
{
    MB_FunctionItem* pFunctionItem = MB_FunctionConfigure::getInstance()->queryFunctionItemByType(getFunctionType());
    if(pFunctionItem)
    {
        //int num = MB_RoleData::getInstance()->getPVPTimes();
        int roleLevel = MB_RoleData::getInstance()->getLevel();
        //等級達到
        if(roleLevel >= pFunctionItem->getNeedLevel())
        {
            MB_ResWindow* pWind = this->createFunctionDialog();
            replaceMainSceneSubLayer(pWind);
        }
        else
        {
            char databuf[40];
            sprintf(databuf, "该功能将在%d级开放",pFunctionItem->getNeedLevel());
            MB_Message::sharedMB_Message()->showMessage(databuf);
        }
    }
}

uint16_t MB_Championship::getFunctionType()
{
    return kFunctionArena;
}

MB_ResWindow* MB_Championship::createEntryDialog()
{
    return MB_ChampionshipEntryDialog::create();
}

MB_ResWindow* MB_Championship::createFunctionDialog()
{
    MB_ChampionshipFunctionDialog* m_pFunctionDialog =  new MB_ChampionshipFunctionDialog();
    if(m_pFunctionDialog)
    {
        bool b = ((MB_ChampionshipFunctionDialog*)m_pFunctionDialog)->setDataSource(this);
        if(b && m_pFunctionDialog->init())
        {
            m_pFunctionDialog->autorelease();
            return m_pFunctionDialog;
        }
        else
        {
            CC_SAFE_RELEASE_NULL(m_pFunctionDialog);
        }
    }
    return NULL;

}

bool MB_Championship::allowShow()
{
    return true;
}
