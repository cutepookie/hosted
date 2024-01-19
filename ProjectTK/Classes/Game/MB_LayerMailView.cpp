//
//  MB_LayerMailView.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-9.
//
//

#include "MB_LayerMailView.h"
#include "MB_MailData.h"
#include "MB_NodeMailSystem.h"

MB_LayerMailView::MB_LayerMailView()
{
    m_itemSize = MB_NodeMailSystem::getNodeSize();
}

void MB_LayerMailView::onInitDidFinish()
{
    MB_MailMainView::onInitDidFinish();
    m_itemSize = MB_NodeMailSystem::getNodeSize();
    if(m_pTableView)m_pTableView->reloadData();
}

void MB_LayerMailView::recvmail_draw_reward(MB_MsgBuffer* pRecv)
{
    dirty();
}

CCTableViewCell* MB_LayerMailView::tableCellAtIndex (CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }

    int64_t uid;
    uid = MailMgr->getMails(m_currentPage)[idx]->mailUID;
    if (m_currentPage == kmMailsTable_System)
    {
        MB_ResWindow* node = MB_NodeMailSystem::create(uid);
        if (node)
        {
            node->setPosition(ccp(m_itemSize.width/2.0f,m_itemSize.height/2.0f));
            cell->addChild(node);
        }
    }
    else if(m_currentPage == kmMailsTable_Preson)
    {
        MB_MailSubItem* node = MB_MailSubItem::create();
        if (node)
        {
            node->setMailUid(uid);
            node->dirty();
            node->setPosition(ccp(m_itemSize.width/2.0f,m_itemSize.height/2.0f));
            cell->addChild(node);
        }
    }
    
    return cell;
}


