//
//  MB_MysteryShopEntry.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-1.
//
//

#include "MB_IngotsShopEntry.h"
#include "MB_IngotsShopInterface.h"




MB_IngotsShopEntry::MB_IngotsShopEntry()
{
    SOCKET_MSG_REGIST(SC_SHOP_BUY, MB_IngotsShopEntry);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_VIPLEVEL, MB_IngotsShopEntry);

}
MB_IngotsShopEntry::~MB_IngotsShopEntry()
{
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_VIPLEVEL);
}

void MB_IngotsShopEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
}
void MB_IngotsShopEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg) {
        case SC_SHOP_BUY:
        case SC_ROLE_UPDATE_VIPLEVEL:
            onResetWnd();
            break;
            
        default:
            break;
    }
}

bool MB_IngotsShopEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_IngotsShopInterface*>(pDataSource);
    return m_pDataSource != NULL;
}
