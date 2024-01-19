//
//  MB_GiftLevelDataSource.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14/12/17.
//
//

#include "MB_GiftDataSource.h"
#include "MB_NodeGiftUnit.h"
#include "MB_GiftsInterface.h"
#include <algorithm>
//1在线時長禮包，2等級禮包，3連续登入禮包
//eGiftTime = 1,
//eGiftLevel = 2,
//eGiftMLogin = 3,
MB_GiftLevelDataSource::MB_GiftLevelDataSource(MB_GiftsInterface* pInterface)
{
    m_pDatas = pInterface->getInfoByType(eGiftLevel)->getInfo();
}

MB_GiftTimeDataSource::MB_GiftTimeDataSource(MB_GiftsInterface* pInterface)
{
    m_pDatas = pInterface->getInfoByType(eGiftTime)->getInfo();
}

MB_GiftMLoginDataSource::MB_GiftMLoginDataSource(MB_GiftsInterface* pInterface)
{
    m_pDatas = pInterface->getInfoByType(eGiftMLogin)->getInfo();
}

MB_GiftLevelDataSource::~MB_GiftLevelDataSource()
{
}


static bool less2(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1)
{
    bool s0 =  ((MB_DailyRewrd*)in_pCcObj0)->getIsGet();
    bool s1 =  ((MB_DailyRewrd*)in_pCcObj1)->getIsGet();
    
    if(s0 && !s1)
    {
        return false;
    }
    else if(!s0 && s1)
    {
        return true;
    }
    if(((MB_DailyRewrd*)in_pCcObj0)->getNeedValue() < ((MB_DailyRewrd*)in_pCcObj1)->getNeedValue())
    {
        return true;
    }
    return false;
}




void MB_GiftTimeDataSource::sortData()
{
    std::stable_sort(m_pDatas->data->arr, m_pDatas->data->arr + m_pDatas->data->num, less2);
}


void MB_GiftLevelDataSource::sortData()
{
    std::stable_sort(m_pDatas->data->arr, m_pDatas->data->arr + m_pDatas->data->num, less2);
}

CCSize MB_GiftLevelDataSource::cellSizeForTable(CCTableView *table)
{
    return MB_NodeGiftUnit::getUnitSize();
}

CCTableViewCell* MB_GiftLevelDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_NodeGiftUnit* pNode = MB_NodeGiftUnit::create((MB_DailyRewrd*)m_pDatas->objectAtIndex(idx));
    if(pNode)
    {
        cell->addChild(pNode);
        pNode->setPosition(MB_NodeGiftUnit::getUnitSize().width/2, MB_NodeGiftUnit::getUnitSize().height/2);
    }
    
    return cell;
}

unsigned int MB_GiftLevelDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDatas->count();
}
