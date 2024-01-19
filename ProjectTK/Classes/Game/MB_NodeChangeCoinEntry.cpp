//
//  MB_NodeChangeCoinEntry.cpp
//  ProjectPM
//
//  Created by chk on 14-4-29.
//
//


#include "MB_NodeChangeCoinEntry.h"
#include "MB_ChangeCoinInterface.h"
#include "Game.h"
#include "MB_TutorialMgr.h"
#include "MB_AbsolvedInterface.h"
bool MB_NodeChangeCoinEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ChangeCoinInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}



MB_NodeChangeCoinEntry::MB_NodeChangeCoinEntry()
{
    SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_NodeChangeCoinEntry);
}

MB_NodeChangeCoinEntry::~MB_NodeChangeCoinEntry()
{
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
}


bool MB_NodeChangeCoinEntry::init()
{
    MB_NodeHoverEntry::init();
    return true;
}

void MB_NodeChangeCoinEntry::onEntranceClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_CommandActivaty* pInterface = dynamic_cast<MB_CommandActivaty*>(m_pDataSource);
    if(pInterface)
    {
        MB_ResWindow* pLayer = pInterface->createFunctionDialog();
        if(pLayer)
        {
            MB_AbsolvedInterface::replaceMainSceneSubLayer(pLayer);
//            NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()->replaceLayer(pLayer);
        }
    }
}

void MB_NodeChangeCoinEntry::onMsgRecv(CCNode* node, SocketResponse* response)
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
            
        case  SC_ROLE_BUY_ENERGY:
        {
//            if(m_pNodeTre == NULL)return;
//            
//            int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeCoin)-MB_RoleData::getInstance()->getCoinBuyTimes();
//            if(limit > 0 )
//            {
//                m_pNodeTre->setVisible(true);
//                char databuf[10];
//                sprintf(databuf, "%d",limit);
//                m_pTreNumber->setString(databuf);
//            }
//            else
//            {
//                m_pNodeTre->setVisible(false);
//            }
        }
            break;
        default:
            break;
    }
}
