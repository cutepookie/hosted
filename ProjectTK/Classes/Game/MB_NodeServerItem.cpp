//
//  MB_NodeServerItem.cpp
//  ProjectMB
//
//  Create by WenYong on 27/8/2014.
//
//
#include "MB_NodeServerItem.h"
#include "MB_LayerFirstLogin.h"

MB_NodeServerItem::MB_NodeServerItem()
{
    m_pSize	 = NULL;
    m_pServerName	 = NULL;
    m_pServerID	 = NULL;
    m_pMenu	 = NULL;
    m_pNodeServerState1 = NULL;
    m_pNodeServerState2 = NULL;
    m_pNodeServerState3 = NULL;
    m_nServerID = 1;
}
MB_NodeServerItem::~MB_NodeServerItem()
{
    CC_SAFE_RELEASE_NULL(m_pSize);
    CC_SAFE_RELEASE_NULL(m_pServerName);
    CC_SAFE_RELEASE_NULL(m_pServerID);
    CC_SAFE_RELEASE_NULL(m_pMenu);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState1);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState2);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState3);
}

MB_NodeServerItem* MB_NodeServerItem::create(int serverId,const char* pServerName,uint8_t nStatus)
{
    MB_NodeServerItem* pInstance = MB_NodeServerItem::create();
    if (pInstance)
    {
        pInstance->setServerInfo(serverId,pServerName,nStatus);
    }
    
    return pInstance;
}

void MB_NodeServerItem::setServerInfo(uint16_t serverId,const char* pServerName,uint8_t nStatus)
{
    char buff[24] = {};
    sprintf(buff, "%d区",serverId);
    m_pServerID->setString(buff);

    m_nServerID = serverId;
    
    m_pNodeServerState1->setVisible(false);
    m_pNodeServerState2->setVisible(false);
    m_pNodeServerState3->setVisible(false);
    switch(nStatus)
    {
        case 1:
            m_pNodeServerState3->setVisible(true);
            break;
        case 2:
            m_pNodeServerState2->setVisible(true);
            break;
        default:
            m_pNodeServerState1->setVisible(true);
            break;
    }
   
    if (m_pServerName)
    {
        m_pServerName->setString(pServerName);
    }
}

bool MB_NodeServerItem::init()
{
    CCNode* pNode = loadResource("res/severchoose_node_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pMenu->setSwallowsTouches(false);
		return true;
	}
	return false;
}
void MB_NodeServerItem::onResetWnd()
{
}
bool MB_NodeServerItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSize",CCNode*,m_pSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pServerName",CCLabelTTF*,m_pServerName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pServerID",CCLabelTTF*,m_pServerID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenu",CCMenu*,m_pMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState1", CCNode*, m_pNodeServerState1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState2", CCNode*, m_pNodeServerState2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeServerState3", CCNode*, m_pNodeServerState3);
    return false;
}
SEL_MenuHandler MB_NodeServerItem::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onServerClicked",MB_NodeServerItem::onServerClicked);
	return NULL;
}
SEL_CCControlHandler MB_NodeServerItem::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_NodeServerItem::onServerClicked(CCObject* pSender)
{
    MB_ServerList::m_nSelectServerid = m_nServerID;
    ServerList* serverList = MB_ServerList::getInstance()->getServerListByID(m_nServerID);
    MB_ClientSocket::setServerIP(serverList->serverIP.c_str());
    MB_ClientSocket::setServerPort(serverList->serverPort);
    MB_TARGET_PARENT(MB_LayerFirstLogin, ptr);
    if (ptr)
    {
        ptr->onServerNodeTouched(this);
    }

}
const CCSize& MB_NodeServerItem::getWndSize()
{
    static CCSize sz = CCSizeMake(-1, -1);
    
    if (sz.width < 0)
    {
        MB_NodeServerItem* pTemp = MB_NodeServerItem::create();
        if (pTemp)
        {
            sz = pTemp->m_pSize->getContentSize();
        }
    }
    return sz;
}