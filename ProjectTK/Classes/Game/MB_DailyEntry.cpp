//
//  MB_DailyEntry.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-6.
//
//

#include "MB_DailyEntry.h"
#include "MB_FunctionConfig.h"
#include "MB_DailyInterface.h"
#include "MB_ItemData.h"

using namespace NSGameFunction;


MB_DailyEntry::MB_DailyEntry()
{
    SOCKET_MSG_REGIST(SC_DAILY_DRAW,MB_DailyEntry);
}
MB_DailyEntry::~MB_DailyEntry()
{
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
}
bool MB_DailyEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_DailyInterface*>(pDataSource);
    
    return m_pDataSource != NULL;
}


void MB_DailyEntry::onMsgRecv(CCNode* node, SocketResponse* response)
{
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    
    if (Msg == SC_DAILY_DRAW)
    {
        dirty();
    }
}

void MB_DailyEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
    
    CCArray* pArray = MB_ItemMgr::getInstance()->getDailyRewardArray();
    if(pArray->count())
    {
        DailyRewardValue* pData = NULL;
        CCARRAY_FOREACH_4TYPE(pArray, DailyRewardValue*, pData)
        {
            if (pData->getType() == kRewardTypeDaily)
            {
                if(!pData->getIsGet())
                {
                    m_pFlagNode2->setVisible(true);
                    m_pFlag2->setString("1");
                }
                else
                {
                    m_pFlagNode2->setVisible(false);
                }
                break;
            }

        }
    }
}

