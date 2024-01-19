//
//  MB_GlobelModalDlgMsgQueue.cpp
//  ProjectPM
//
//  Created by WenYong on 14-5-26.
//
//

#include "MB_GlobelModalDlgMsgQueue.h"
#include "MB_ResWindow.h"
#include "MB_LocalProto.h"
#include "MB_FunctionModule.h"
#include "MB_LayerStory.h"
MB_GlobelAchievementMsgQueue::MB_GlobelAchievementMsgQueue()
{
    m_pMsgQueue = new CCArray;
}
MB_GlobelAchievementMsgQueue::~MB_GlobelAchievementMsgQueue()
{
    CC_SAFE_RELEASE_NULL(m_pMsgQueue);
}


MB_GlobelModalDlgMsgQueue* MB_GlobelModalDlgMsgQueue::getInstance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new MB_GlobelModalDlgMsgQueue;
    }
    return m_pInstance;
}
void MB_GlobelModalDlgMsgQueue::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pInstance);
}

//CCObject* MB_GlobelModalDlgMsgQueue::queryObjectAtIndex(int index)
//{
//    if (index < 0 || index >= msgCount())
//    {
//        return NULL;
//    }
//    
//    return m_pMsgQueue->objectAtIndex(index);
//}

MB_GlobelModalDlgMsgQueue* MB_GlobelModalDlgMsgQueue::m_pInstance = NULL;

void MB_GlobelAchievementMsgQueue::addMsgWnd(MB_ResWindow* pWnd)
{
    if (dynamic_cast<MB_ResWindow*>(pWnd))
    {
        m_pMsgQueue->addObject(pWnd);
    }
}

void MB_GlobelAchievementMsgQueue::addMsgWndQueue(CCArray* pQueue)
{
    MB_ResWindow* pWnd = NULL;
    CCARRAY_FOREACH_4TYPE(pQueue, MB_ResWindow*, pWnd)
    {
        if (pWnd)
        {
            m_pMsgQueue->addObject(pWnd);
        }
    }
}

void MB_GlobelAchievementMsgQueue::onEnter()
{
    CCNode* pScene = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_ACHIVE);
    if (pScene)
    {
        pScene->onEnter();
    }
}

void MB_GlobelAchievementMsgQueue::popFront()
{
    if (msgCount()==0)
    {
        return;
    }
    CCNode* pNode = (CCNode*) m_pMsgQueue->objectAtIndex(0);
    CCNode* pScene = CCDirector::sharedDirector()->getRunningScene();
    pScene->addChild(pNode,2999);
    static CCSize sz = CCDirector::sharedDirector()->getWinSize();
    pNode->setPosition(sz.width/2.0, sz.height/2.0);
    
    MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_AchievementComplate).c_str());
    m_pMsgQueue->removeObjectAtIndex(0);
}

void MB_GlobelModalDlgMsgQueue::popFront()
{
    if (msgCount()==0)
    {
        return;
    }
    
    MB_ResWindow* pNode = (MB_ResWindow*) m_pMsgQueue->objectAtIndex(0);
    CCNode* pScene = CCDirector::sharedDirector()->getRunningScene();
    if(pNode->getShowRoleInfoPanel())
    {
        MB_ResWindow* pwnd = dynamic_cast<MB_ResWindow*>(pScene);
        if(pwnd)pwnd->setShowRoleInfoPanel(pNode->getShowRoleInfoPanel());
    }
    pScene->addChild(pNode,999);
    m_pMsgQueue->removeObjectAtIndex(0);
}

void MB_GlobelAchievementMsgQueue::insertAtIndex(MB_ResWindow* pWnd,int index)
{
    if (index > m_pMsgQueue->count())
    {
        return;
    }
    if (dynamic_cast<MB_ResWindow*>(pWnd))
    {
        m_pMsgQueue->insertObject(pWnd, index);
    }
}

int MB_GlobelAchievementMsgQueue::msgCount()
{
    return m_pMsgQueue->count();
}

void MB_GlobelAchievementMsgQueue::clearMsg()
{
    m_pMsgQueue->removeAllObjects();
}
