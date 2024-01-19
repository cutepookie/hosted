//
//  MB_NodeTaskEntranceWnd.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_NodeTaskEntranceWnd.h"
#include "MB_TaskSystemInterface.h"
#include "MB_TaskSystemProtocol.h"
#include "MB_ClientSocket.h"

MB_NodeTaskEntranceWnd::MB_NodeTaskEntranceWnd()
{
    m_pEntryName = NULL;
    m_pNodeFlag = NULL;
    m_pNodeShowNumber = NULL;
    m_pParticlesEffect = NULL;
    
    
    SOCKET_MSG_REGIST(SC_TASK_GET_INFO, MB_NodeTaskEntranceWnd);
    SOCKET_MSG_REGIST(SC_TASK_OPERATE, MB_NodeTaskEntranceWnd);
    SOCKET_MSG_REGIST(SC_TASK_NOTIFY, MB_NodeTaskEntranceWnd);
}

MB_NodeTaskEntranceWnd::~MB_NodeTaskEntranceWnd()
{
    CC_SAFE_RELEASE_NULL(m_pEntryName);
    CC_SAFE_RELEASE_NULL(m_pNodeFlag);
    CC_SAFE_RELEASE_NULL(m_pNodeShowNumber);
    CC_SAFE_RELEASE_NULL(m_pParticlesEffect);
    
    SOCKET_MSG_UNREGIST(SC_TASK_GET_INFO);
    SOCKET_MSG_UNREGIST(SC_TASK_OPERATE);
    SOCKET_MSG_UNREGIST(SC_TASK_NOTIFY);
}

bool MB_NodeTaskEntranceWnd::setDataSource(CCFunctionDataSource* pDataSource)
{
    MB_TaskSystemInterface* pTarget = dynamic_cast<MB_TaskSystemInterface*>(pDataSource);
    if (pTarget)
    {
        m_pDataSource = pTarget;
        return true;
    }
    
    return false;
}

bool MB_NodeTaskEntranceWnd::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_entryname", CCLabelTTF*, m_pEntryName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_shownumber", CCLabelTTF*, m_pNodeShowNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag", CCNode*, m_pNodeFlag);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_particle", CCParticleSystemQuad*, m_pParticlesEffect);
    
    return false;
}

SEL_MenuHandler MB_NodeTaskEntranceWnd::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTaskEntranceClicked", MB_NodeTaskEntranceWnd::onTaskEntranceClicked);
    
    return NULL;
}

SEL_CCControlHandler MB_NodeTaskEntranceWnd::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool MB_NodeTaskEntranceWnd::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/obj_index_task.ccbi", this);
    if (pNode)
    {
        addChild(pNode);
    }
    
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    onResetWnd();
    
    return pNode != NULL;
}

void MB_NodeTaskEntranceWnd::onMsgRecv(CCNode* node, SocketResponse* response)
{
    onResetWnd();
}

void MB_NodeTaskEntranceWnd::onTaskEntranceClicked(CCObject* pSender)
{
    if (m_pDataSource)
    {
        ((MB_TaskSystemInterface*)m_pDataSource)->onEnterThisFunction(this);
    }
}

void MB_NodeTaskEntranceWnd::onResetWnd()
{
    uint32_t nCount = ((MB_TaskSystemInterface*)m_pDataSource)->getComplateTaskCount();
    if (0!=nCount)
    {
        m_pNodeFlag->setVisible(true);
        char buff[25] = {};
        sprintf(buff, "%d",nCount);
        m_pNodeShowNumber->setString(buff);
    }
    else
    {
        m_pNodeFlag->setVisible(false);
    }
}

bool MB_NodeTaskEntranceWndEx::setDataSource(NSGameFunction::CCFunctionDataSource *pDataSource)
{
        return m_pDataSource = dynamic_cast<MB_TaskSystemInterface*>(pDataSource);
}



//////////////////////////////////////////////////////////////////////////////////////////////////
MB_NodeTaskEntry::MB_NodeTaskEntry()
{
    SOCKET_MSG_REGIST(SC_TASK_GET_INFO, MB_NodeTaskEntry);
    SOCKET_MSG_REGIST(SC_TASK_OPERATE, MB_NodeTaskEntry);
    SOCKET_MSG_REGIST(SC_TASK_NOTIFY, MB_NodeTaskEntry);
}

MB_NodeTaskEntry::~MB_NodeTaskEntry()
{
    SOCKET_MSG_UNREGIST(SC_TASK_GET_INFO);
    SOCKET_MSG_UNREGIST(SC_TASK_OPERATE);
    SOCKET_MSG_UNREGIST(SC_TASK_NOTIFY);
}
void MB_NodeTaskEntry::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    onResetWnd();
}
bool MB_NodeTaskEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_TaskSystemInterface*>(pDataSource);
    return m_pDataSource != NULL;
}
void MB_NodeTaskEntry::onResetWnd()
{
    MB_NodeHoverEntry::onResetWnd();
    
    MB_TaskSystemInterface* pInterface = dynamic_cast<MB_TaskSystemInterface*>(m_pDataSource);
    if (pInterface)
    {
        uint32_t nCount = pInterface->getComplateTaskCount();
        if (0!=nCount)
        {
            m_pFlagNode2->setVisible(true);
            if (nCount>99) {
                m_pFlag2->setString("!");
            }else
            {
                char buff[25] = {};
                sprintf(buff, "%d",nCount);
                m_pFlag2->setString(buff);
            }
        }
        else
        {
            m_pFlagNode2->setVisible(false);
        }
    }
}
