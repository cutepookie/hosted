

#include "MB_NodeServerInfo.h"
#include "MB_LayerFirstLogin.h"
#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

MB_NodeServerInfo::MB_NodeServerInfo()
{
    m_nServerID = -1;
}

bool MB_NodeServerInfo::init(const char* strServerZone, const char* strServerName, int serverStatus,unsigned int sid)
{
    m_strServerZone = strServerZone;
    m_strServerName = strServerName;
    m_uServerStatus = serverStatus;
    m_nServerID = sid;
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pNode = pCCBReader->readNodeGraphFromFile("res/obj_gameserver.ccbi", this);
    this->addChild(pNode);
    
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    return true;
}

MB_NodeServerInfo::~MB_NodeServerInfo()
{
}
void MB_NodeServerInfo::onZoneNodeClick(CCObject* pSender)
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
bool MB_NodeServerInfo::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if(strcmp(pMemberVariableName, "node_menu")==0)
    {
        CCMenu* pm =dynamic_cast<CCMenu*>(pNode);
        if(pm)
        {
            pm->setSwallowsTouches(false);
        }
    }
    if (strcmp(pMemberVariableName, "CellSize")==0)
    {
        m_ContentSize =  pNode->getContentSize();
    }
    if (strcmp(pMemberVariableName, "ServerZone") == 0)
    {
        ((CCLabelTTF*)pNode)->setString(m_strServerZone.c_str());
    }
    else if (strcmp(pMemberVariableName, "ServerName") == 0)
    {
        ((CCLabelTTF*)pNode)->setString(m_strServerName.c_str());
    }
    else if (strcmp(pMemberVariableName, "ServerStatus") == 0)
    {
        if (m_uServerStatus == 1)
        {
            ((CCLabelTTF*)pNode)->setColor(ccGRAY);
            ((CCLabelTTF*)pNode)->setString("维护");
        }
        else if (m_uServerStatus == 2)
        {
            ((CCLabelTTF*)pNode)->setColor(ccGREEN);
            ((CCLabelTTF*)pNode)->setString("新");
        }
        else
        {
            ((CCLabelTTF*)pNode)->setColor(ccRED);
            ((CCLabelTTF*)pNode)->setString("爆满");
        }
        
//        switch (m_uServerStatus) {
//            case 1:
//                ((CCLabelTTF*)pNode)->setString("维护");
//                ((CCLabelTTF*)pNode)->setFillColor(ccGRAY);
//                break;
//            case 2:
//                ((CCLabelTTF*)pNode)->setString("新");
//                ((CCLabelTTF*)pNode)->setFillColor(ccYELLOW);
//                break;
//            case 3:
//                ((CCLabelTTF*)pNode)->setString("爆满");
//                ((CCLabelTTF*)pNode)->setFillColor(ccRED);
//                break;
//            case 4:
//                ((CCLabelTTF*)pNode)->setString("拥挤");
//                ((CCLabelTTF*)pNode)->setFillColor(ccORANGE);
//                break;
//            case 5:
//                ((CCLabelTTF*)pNode)->setString("流畅");
//                ((CCLabelTTF*)pNode)->setFillColor(ccGREEN);
//                break;
//                
//            default:
//                break;
//        }
    }
    return false;
}

SEL_MenuHandler MB_NodeServerInfo::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onZoneNodeClick", MB_NodeServerInfo::onZoneNodeClick);
    return NULL;
}
SEL_CCControlHandler MB_NodeServerInfo::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
