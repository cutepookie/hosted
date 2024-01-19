//
//  MB_LayerServerPanel.cpp
//  ProjectMB
//
//  Create by WenYong on 27/8/2014.
//
//
#include "MB_LayerServerPanel.h"
#include "MB_NodeServerZone.h"
#include "MB_LayerServerContainer.h"
#include "MB_NodeServerItem.h"
#include "MB_FunctionModule.h"
#include "MB_ServerList.h"
#include "MB_LayerFirstLogin.h"

#define SERVER_PAGE_LIST    16 // 每页显示的数量

MB_LayerServerPanel::MB_LayerServerPanel()
{
    m_pServerContainer	 = NULL;
    m_pServerView	 = NULL;
    m_pScrollView = NULL;
    m_nSelectIndex = 0;
    m_pTableView = NULL;
    
    m_pNodeLastLogin = NULL;
    m_pNodeServerState1 = NULL;
    m_pNodeServerState2 = NULL;
    m_pNodeServerState3 = NULL;
    
    m_pTTFName = NULL;
    m_pTTFID = NULL;
}
MB_LayerServerPanel::~MB_LayerServerPanel()
{
    CC_SAFE_RELEASE_NULL(m_pServerContainer);
    CC_SAFE_RELEASE_NULL(m_pServerView);
    m_pScrollView = NULL;
    m_pTableView = NULL;
    
    CC_SAFE_RELEASE_NULL(m_pNodeLastLogin);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState1);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState2);
    CC_SAFE_RELEASE_NULL(m_pNodeServerState3);
    CC_SAFE_RELEASE_NULL(m_pTTFName);
    CC_SAFE_RELEASE_NULL(m_pTTFID);
}
bool MB_LayerServerPanel::init()
{
    CCNode* pNode = loadResource("res/severchoose_layer.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pTableView = CCTableView::create(this, m_pServerContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pServerContainer->addChild(m_pTableView);
        m_pTableView->reloadData();
        m_pTableView->setSwaller(false);
        
        m_pScrollView = CCScrollView::create(m_pServerView->getContentSize());
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pServerView->addChild(m_pScrollView);
        m_pScrollView->setSwaller(false);
        
        selectRange(1,SERVER_PAGE_LIST);
        
        onResetWnd();
		return true;
	}
	return false;
}
void MB_LayerServerPanel::onResetWnd()
{
    int id = MB_ServerList::getInstance()->getLatestServerIDByIndex(0);
    if(id!=-1)
    {
        ServerList* serverData = NULL;
        serverData = MB_ServerList::getInstance()->getServerListByID(id);
        if(serverData)
        {
            m_pNodeLastLogin->setVisible(true);
            m_pNodeServerState1->setVisible(false);
            m_pNodeServerState2->setVisible(false);
            m_pNodeServerState3->setVisible(false);
            switch(serverData->serverStatus)
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
            m_pTTFName->setString(serverData->name.c_str());
            char str[32];
            sprintf(str,"%d服",id);
            m_pTTFID->setString(str);
        }
        else
        {
            m_pNodeLastLogin->setVisible(false);
        }
    }
    else
    {
        m_pNodeLastLogin->setVisible(false);
    }
    
}
bool MB_LayerServerPanel::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pServerContainer",CCNode*,m_pServerContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pServerView",CCNode*,m_pServerView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLastLogin",CCNode*,m_pNodeLastLogin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeServerState1",CCNode*,m_pNodeServerState1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeServerState2",CCNode*,m_pNodeServerState2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeServerState3",CCNode*,m_pNodeServerState3);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFName",CCLabelTTF*,m_pTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFID",CCLabelTTF*,m_pTTFID);
    
	return false;
}
SEL_MenuHandler MB_LayerServerPanel::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerServerPanel::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onOldServerClicked",MB_LayerServerPanel::onOldServerClicked);
    
	return NULL;
}
SEL_CCControlHandler MB_LayerServerPanel::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerServerPanel::onCloseClick(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_SceneServerList, ptr);
    if (ptr)
    {
        ptr->onBackClicked(this);
    }
}
void MB_LayerServerPanel::onOldServerClicked(CCObject* pSender)
{
    int id = MB_ServerList::getInstance()->getLatestServerIDByIndex(0);
    if(id!=-1)
    {
        ServerList* serverData = NULL;
        serverData = MB_ServerList::getInstance()->getServerListByID(id);
        if (serverData) {
            MB_ServerList::m_nSelectServerid = id;
            MB_ClientSocket::setServerIP(serverData->serverIP.c_str());
            MB_ClientSocket::setServerPort(serverData->serverPort);
        }
        MB_TARGET_PARENT(MB_LayerFirstLogin, ptr);
        if (ptr)
        {
            ptr->onServerNodeTouched(this);
        }
    }
    
}


CCSize MB_LayerServerPanel::cellSizeForTable(CCTableView *table)
{
    return MB_NodeServerZone::getWndSize();
}

CCTableViewCell* MB_LayerServerPanel::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if(cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
        
    }
    cell->removeAllChildren();

    int begin = idx * SERVER_PAGE_LIST + 1;
    MB_NodeServerZone* pNode = MB_NodeServerZone::create(begin, begin-1+SERVER_PAGE_LIST);
    if (pNode)
    {
        cell->addChild(pNode,0,1);
        if (idx == m_nSelectIndex)
        {
            pNode->select(true);
        }
        else
        {
            pNode->select(false);
        }
    }
    
    return cell;
}

unsigned int MB_LayerServerPanel::numberOfCellsInTableView(CCTableView *table)
{
    int count = MB_ServerList::getInstance()->getServerListCount();
    count = ((count % SERVER_PAGE_LIST) == 0) ? (count / SERVER_PAGE_LIST) : (count / SERVER_PAGE_LIST + 1);
    return count;
}

void MB_LayerServerPanel::resetServerZone(int newIndex)
{
    CCTableViewCell* pCell = NULL;
    if (newIndex == m_nSelectIndex)
    {
        pCell = m_pTableView->cellAtIndex(m_nSelectIndex);
        if (pCell)
        {
            MB_NodeServerZone* pTemp = dynamic_cast<MB_NodeServerZone*>(pCell->getChildByTag(1));
            if (pTemp)
            {
                pTemp->select(true);
            }
        }
        return;
    }
    
    pCell = m_pTableView->cellAtIndex(newIndex);
    if (pCell)
    {
        MB_NodeServerZone* pTemp = dynamic_cast<MB_NodeServerZone*>(pCell->getChildByTag(1));
        if (pTemp)
        {
            pTemp->select(true);
        }
    }
    else
    {
        return;
    }
    
    pCell = m_pTableView->cellAtIndex(m_nSelectIndex);
    if (pCell)
    {
        MB_NodeServerZone* pTemp = dynamic_cast<MB_NodeServerZone*>(pCell->getChildByTag(1));
        if (pTemp)
        {
            pTemp->select(false);
        }
    }
    
    m_nSelectIndex = newIndex;
}

void MB_LayerServerPanel::selectRange(uint16_t begin,uint16_t end)
{
    CCNode* pNode = MB_LayerServerContainer::create(begin, end);
    if (pNode)
    {
        resetServerZone(begin/SERVER_PAGE_LIST);
        m_pScrollView->setContainer(pNode);
        m_pScrollView->setContentOffset(ccp(0, m_pScrollView->getViewSize().height-pNode->getContentSize().height));
    }
}
