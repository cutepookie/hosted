//
//  MB_LayerFinalRecordLive.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_LayerFinalRecordLive.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_NodeFinalRecordLive.h"
#include "MB_NodePerfectRaceRround.h"

MB_LayerFinalRecordLive::MB_LayerFinalRecordLive()
{
    m_bIsRuningSchedule = false;
    m_nCurrentLength = 0;
}

CCTableViewCell* MB_LayerFinalRecordLive::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    MB_RaceRoundRecord* pRoundRecord = dynamic_cast<MB_RaceRoundRecord*>(m_pLiveList->objectAtIndex(idx));
    CCNode* pNode = NULL;
    if (pRoundRecord)
    {
        pNode = MB_NodeFinalRecordLive::create(pRoundRecord);
        if (pNode)
        {
            cell->addChild(pNode);
        }
    }
    else
    {
        CCString* pString = dynamic_cast<CCString*>(m_pLiveList->objectAtIndex(idx));
        pNode = MB_NodePerfectRaceRround::create(0);
        if (pNode)
        {
            ((MB_NodePerfectRaceRround*)(pNode))->forceSetShowString(pString->getCString());
            cell->addChild(pNode);
        }
    }
    if (pNode);
    {
        pNode->setPosition(m_pContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
    }
    return cell;
}


void MB_LayerFinalRecordLive::recvrace_new_fight(MB_MsgBuffer* pRecv)
{
    MB_RaceRecord* pRaceRecord = new MB_RaceRecord;
    if (pRaceRecord->read(pRecv))
    {
        pRaceRecord->resolvRaceRecord(&m_pLiveList);
        MB_RaceRoundRecord* pRoundRecord = dynamic_cast<MB_RaceRoundRecord*>(m_pLiveList->lastObject());
        const char* pRound = getMatchRound(m_pPerfectRaceInterface->getStep());
        if (pRoundRecord->getAtkScore() > pRoundRecord->getDefScore())
        {
            m_pLiveList->addObject(CCString::createWithFormat("恭喜%s在%s中胜出",pRoundRecord->getAtkName().c_str(),pRound));
        }
        else
        {
            m_pLiveList->addObject(CCString::createWithFormat("恭喜%s在%s中胜出",pRoundRecord->getDefName().c_str(),pRound));
        }
        star();
    }
    CC_SAFE_RELEASE_NULL(pRaceRecord);
}

void MB_LayerFinalRecordLive::star()
{
    if (!m_bIsRuningSchedule)
    {
        schedule(schedule_selector(MB_LayerFinalRecordLive::tickRuningSchedule), 1.5);
    }
}

void MB_LayerFinalRecordLive::tickRuningSchedule(float dt)
{
    if (m_nCurrentLength < m_pLiveList->count())
    {
        ++m_nCurrentLength;
        onResetWnd();
    }
    else
    {
        unscheduleAllSelectors();
    }
}