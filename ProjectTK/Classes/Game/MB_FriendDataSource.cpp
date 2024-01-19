//
//  MB_FriendDataSource.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-12.
//
//

#include "MB_FriendDataSource.h"
#include "MB_DataFriend.h"
#include "MB_NodeFriendInformation.h"
#include "MB_NodeFriendInvite.h"
#include "MB_NodeFriendEnergy.h"
#include "MB_LayerFriend.h"
#include "MB_NodeFriendFight.h"

void MB_FriendDataSouce::setIsMail(bool bMail)
{
    m_bMail = bMail;
}

void MB_FriendDataSouce::setTablePage(int kTablePage)
{
    m_nTablePage = kTablePage;
}

void MB_FriendDataSouce::setItemSize(const CCSize& sz)
{
    m_ItemSize = sz;
}

CCSize MB_FriendDataSouce::cellSizeForTable(CCTableView *table)
{
    return m_ItemSize;
}

MB_OwenFriendDataSource::MB_OwenFriendDataSource()
{
    m_ItemSize = MB_NodeFriendInformation::getUISize();
    m_pArray = new CCArray;
}

MB_OwenFriendDataSource::~MB_OwenFriendDataSource()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}
void MB_OwenFriendDataSource::preReloadData()
{
    m_pArray->removeAllObjects();
    m_pArray->addObjectsFromArray(MB_FriendMgr::getInstance()->getFriendArray());
 
    
    m_pArray->sortArray(MB_OwenFriendDataSource::sort);
}

//排序 在线 等級 戰鬥力
bool MB_OwenFriendDataSource::sort(CCObject* ob1,CCObject* ob2)
{
   MB_DataFriend* data1 = dynamic_cast<MB_DataFriend*>(ob1);
   MB_DataFriend* data2 = dynamic_cast<MB_DataFriend*>(ob2);
    if (data1 == NULL || data2 == NULL)
    {
        return true;
    }
    
    if (data1->getLogoutTime() == 0 && data2->getLogoutTime() != 0)
    {
        return true;
    }
    else if(data1->getLogoutTime() != 0 && data2->getLogoutTime() == 0)
    {
        return false;
    }
    
    if (data1->getLevel() > data2->getLevel())
    {
        return true;
    }
    else if (data1->getLevel() < data2->getLevel())
    {
        return false;
    }
    
    if (data1->getFightPower() > data2->getFightPower())
    {
        return true;
    }
    else if (data1->getFightPower() < data2->getFightPower())
    {
        return false;
    }
    return true;
}

int MB_OwenFriendDataSource::getIndexByRoleId(uint32_t id)
{
    MB_DataFriend* pTemp = NULL;
    
    int index = 0;
    CCARRAY_FOREACH_4TYPE(m_pArray, MB_DataFriend*, pTemp)
    {
        if (pTemp->getRoleID() == id)
        {
            return m_pArray->count() - index - 1;
        }
        ++index;
    }
    return 0;
}

CCTableViewCell* MB_OwenFriendDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    idx = m_pArray->count() - idx - 1;
    MB_DataFriend* pData = dynamic_cast<MB_DataFriend*>(m_pArray->objectAtIndex(idx));
    if (pData)
    {
        MB_NodeFriendInformation* pWnd = MB_NodeFriendInformation::create(pData);
        if (pWnd)
        {
            pWnd->setIsMail(m_bMail);
            cell->addChild(pWnd);
            pWnd->setPosition(m_ItemSize.width/2.0,m_ItemSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_OwenFriendDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArray->count();
}


MB_AddFriendDataSource::MB_AddFriendDataSource()
{
    m_ItemSize = MB_NodeFriendInvite::getUISize();
}

CCTableViewCell* MB_AddFriendDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_DataFriend* pData = dynamic_cast<MB_DataFriend*>(MB_FriendMgr::getInstance()->getExploreArray()->objectAtIndex(idx));
    if (pData)
    {
        MB_NodeFriendInvite* pWnd = MB_NodeFriendInvite::create(pData);
        if (pWnd)
        {
            pWnd->setMode(kModeInvite);
            cell->addChild(pWnd);
            pWnd->setPosition(m_ItemSize.width/2.0,m_ItemSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_AddFriendDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return MB_FriendMgr::getInstance()->getExploreArray()->count();
}


MB_RPSFriendDataSource::MB_RPSFriendDataSource()
{
    m_pArray = new CCArray;
    m_ItemSize = MB_NodeFriendEnergy::getUISize();
}

MB_RPSFriendDataSource::~MB_RPSFriendDataSource()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}

void MB_RPSFriendDataSource::preReloadData()
{
    CCArray* pArray = MB_FriendMgr::getInstance()->getFriendArray();
    
    MB_DataFriend* pTemp = NULL;
    
    m_pArray->removeAllObjects();
    CCARRAY_FOREACH_4TYPE(pArray, MB_DataFriend*, pTemp)
    {
        if (pTemp && (pTemp->getCanGiveEnergy() || pTemp->getCanSendEnergy() == 1))
        {
            m_pArray->addObject(pTemp);
        }
    }
}

CCTableViewCell* MB_RPSFriendDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_DataFriend* pData = dynamic_cast<MB_DataFriend*>(m_pArray->objectAtIndex(idx));
    if (pData)
    {
        MB_NodeFriendEnergy* pWnd = MB_NodeFriendEnergy::create(pData);
        if (pWnd)
        {
            cell->addChild(pWnd);
            pWnd->setPosition(m_ItemSize.width/2.0,m_ItemSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_RPSFriendDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArray->count();
}

CCTableViewCell* MB_MsgFriendDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_DataMsgFriend* pData = dynamic_cast<MB_DataMsgFriend*>(m_pArray->objectAtIndex(idx));
    if (pData)
    {
        MB_NodeFriendInvite* pWnd = MB_NodeFriendInvite::create(pData);
        if (pWnd)
        {
            pWnd->setMode(kModeMsg);
            cell->addChild(pWnd);
            pWnd->setPosition(m_ItemSize.width/2.0,m_ItemSize.height/2.0);
        }
    }
    
    return cell;

}

MB_MsgFriendDataSource::MB_MsgFriendDataSource()
{
    m_pArray = new CCArray;
}
MB_MsgFriendDataSource::~MB_MsgFriendDataSource()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}
void MB_MsgFriendDataSource::preReloadData()
{
    m_pArray->removeAllObjects();
    m_pArray->addObjectsFromArray(MB_FriendMgr::getInstance()->getFriendMsgArray());
    
    sort();
}

void MB_MsgFriendDataSource::sort()
{
//    int count = m_pArray->count();
//    if (count < 2)
//    {
//        return;
//    }
//    
//    for(int j=0;j<count-1;j++)
//    {
//        for(int i=0;i<count-1-j;i++)
//        {
//            MB_DataFriend* p1 = (MB_DataFriend*)m_pArray->objectAtIndex(i);
//            MB_DataFriend* p2 = (MB_DataFriend*)m_pArray->objectAtIndex(i+1);
//            if(p1->getLevel()<p2->getLevel())
//            {
//                m_pArray->exchangeObjectAtIndex(i, i+1);
//            }
//        }
//    }
}

unsigned int MB_MsgFriendDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArray->count();
}

MB_FightFriendDataSource::MB_FightFriendDataSource()
{
    m_ItemSize = MB_NodeFriendFight::getUISize();
    m_pArray = new CCArray;
}
MB_FightFriendDataSource::~MB_FightFriendDataSource()
{
    CC_SAFE_RELEASE_NULL(m_pArray);
}
void MB_FightFriendDataSource::preReloadData()
{
    m_pArray->removeAllObjects();
    m_pArray->addObjectsFromArray(MB_FriendMgr::getInstance()->getFriendArray());
    m_pArray->sortArray(MB_FightFriendDataSource::sort);
}
CCTableViewCell* MB_FightFriendDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    idx = m_pArray->count() - idx - 1;
    MB_DataFriend* pData = dynamic_cast<MB_DataFriend*>(m_pArray->objectAtIndex(idx));
    if (pData)
    {
        MB_NodeFriendFight* pWnd = MB_NodeFriendFight::create(pData);
        if (pWnd)
        {
            cell->addChild(pWnd);
            pWnd->setPosition(m_ItemSize.width/2.0,m_ItemSize.height/2.0);
        }
    }
    return cell;
}
//可戰鬥 排序 在线 等級 戰鬥力
bool MB_FightFriendDataSource::sort(CCObject* ob1,CCObject* ob2)
{
    MB_DataFriend* data1 = dynamic_cast<MB_DataFriend*>(ob1);
    MB_DataFriend* data2 = dynamic_cast<MB_DataFriend*>(ob2);
    if (data1 == NULL || data2 == NULL)
    {
        return true;
    }
    
    if(data1->getCanFight() && !data2->getCanFight())
    {
        return true;
    }
    else if(!data1->getCanFight() != 0 && data2->getCanFight())
    {
        return false;
    }

    
    if (data1->getLogoutTime() == 0 && data2->getLogoutTime() != 0)
    {
        return true;
    }
    else if(data1->getLogoutTime() != 0 && data2->getLogoutTime() == 0)
    {
        return false;
    }
    
    if (data1->getLevel() > data2->getLevel())
    {
        return true;
    }
    else if (data1->getLevel() < data2->getLevel())
    {
        return false;
    }
    
    if (data1->getFightPower() > data2->getFightPower())
    {
        return true;
    }
    else if (data1->getFightPower() < data2->getFightPower())
    {
        return false;
    }
    return true;
}

unsigned int MB_FightFriendDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArray->count();
}
