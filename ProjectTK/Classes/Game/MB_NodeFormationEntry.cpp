//
//  MB_NodeFormationEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-10.
//
//

#include "MB_NodeFormationEntry.h"
#include "MB_CommandFormation.h"
#include "MB_TeamData.h"
#include "MB_DefineProto.h"
#include "MB_ClientSocket.h"
bool MB_NodeFormationEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_CommandFormation*>(pDataSource);
    
    return m_pDataSource != NULL;
}

MB_NodeFormationEntry::MB_NodeFormationEntry()
{
    SOCKET_MSG_REGIST(SC_GER_STANDUP, MB_NodeFormationEntry);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_NodeFormationEntry);
    SOCKET_MSG_REGIST(SC_GER_POS_LIST, MB_NodeFormationEntry);
}

MB_NodeFormationEntry::~MB_NodeFormationEntry()
{
    SOCKET_MSG_UNREGIST(SC_GER_STANDUP);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    SOCKET_MSG_UNREGIST(SC_GER_POS_LIST);
}

void MB_NodeFormationEntry::onResetWnd()
{
    MB_NodeCommandEntrance::onResetWnd();
    
//    int count = MB_TeamData::getInstance()->getEmptyCount();
//    //队伍红点数量提示缺少的能够上阵角色数量
//    if (count !=0 )
//    {
//        m_pFlagNode2->setVisible(true);
//        if (count>99) {
//            m_pFlag2->setString("!");
//        }else
//        {
//            char buff[12] = {};
//            sprintf(buff, "%d",count);
//            m_pFlag2->setString(buff);
//        }
//    }
//    else
//    {
//        m_pFlagNode2->setVisible(false);
//    }
}

bool MB_NodeFormationEntry::init()
{
    bool ret = MB_NodeCommandEntrance::init();
    onResetWnd();
    return ret;
}
void MB_NodeFormationEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    onResetWnd();
}
