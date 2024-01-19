//
//  MB_LayerGroupHistoryRecord.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-25.
//
//

#include "MB_LayerGroupHistoryRecord.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_NodeGroupRecordLive.h"
#include "MB_NodePerfectRaceRround.h"
#define MAX_REQUEST_RECORD 20

MB_LayerGroupHistoryRecord::MB_LayerGroupHistoryRecord()
{
    m_pContainer = NULL;
    m_pTableView = NULL;
    m_pPerfectRaceInterface = NULL;
    m_pResultLabel = NULL;
    m_nStartRecord = 0;
    m_nCurrentRound = 0;
    m_nStartRecord = 0;
    m_nLastTouched = 0;
    m_bRequest = 0;
    m_pGrouptitle = NULL;
    m_nShowCount = MAX_REQUEST_RECORD;
    m_pGroupRecord = new CCArray;
    m_nEndRecord = MAX_REQUEST_RECORD;
    SOCKET_MSG_REGIST(SC_RACE_HISTORY, MB_LayerGroupHistoryRecord);
    SOCKET_MSG_REGIST(SC_RACE_REPLAY, MB_LayerGroupHistoryRecord);
}

MB_LayerGroupHistoryRecord::~MB_LayerGroupHistoryRecord()
{
    m_pPerfectRaceInterface = NULL;
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    CC_SAFE_RELEASE_NULL(m_pGroupRecord);
    CC_SAFE_RELEASE_NULL(m_pGrouptitle);
    CC_SAFE_RELEASE_NULL(m_pResultLabel);
    SOCKET_MSG_UNREGIST(SC_RACE_HISTORY);
    SOCKET_MSG_UNREGIST(SC_RACE_REPLAY);
}

bool MB_LayerGroupHistoryRecord::init(int nGroup)
{
    if (nGroup > 8 || nGroup < 1)
    {
        return false;
    }
    
    CCNode* pNode = loadResource("res/monsterrace_layer_report1.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        
        MB_CcbAutoMemberWnd* pWnd = MB_CcbAutoMemberWnd::create("res/monsterrace_node_title1.ccbi");
        if (pWnd)
        {
            m_CellSize = (*pWnd)["cellSize"]->getContentSize();
        }
        float adjustHeight = m_pContainer->getContentSize().height;
        NSGameHelper::adjustScrollNode(m_pContainer);
        adjustHeight = m_pContainer->getContentSize().height - adjustHeight;
        
        m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pContainer->addChild(m_pTableView);
        m_pTableView->retain();
        m_pResultLabel->setString("");
        m_pResultLabel->setPositionY(m_pResultLabel->getPositionY() - adjustHeight);
        selectGroup(nGroup);
        onResetWnd();
        return true;
    }
    return false;
}

void MB_LayerGroupHistoryRecord::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    m_nLastTouched = cell->getIdx();
}
void MB_LayerGroupHistoryRecord::scrollViewDidScroll(CCScrollView* view)
{
    return;
    CCPoint pt = view->getContentOffset();
    if (pt.y > 0)
    {
        m_pPerfectRaceInterface->sendrace_history(0, m_nGroupId, m_nStartRecord, MAX_REQUEST_RECORD);
    }
    else if (pt.y < -view->getContainer()->getContentSize().height+m_pContainer->getContentSize().height)
    {
        
        pt.y = -view->getContainer()->getContentSize().height+m_pContainer->getContentSize().height;
        view->setContentOffset(pt);
    }
}

void MB_LayerGroupHistoryRecord::onResetWnd()
{
    const char* p[] = {"","第一组","第二组","第三组","第四组","第五组","第六组","第七组","第八组"};
    m_pGrouptitle->setString(p[m_nGroupId]);
    m_pTableView->reloadData();
}

bool MB_LayerGroupHistoryRecord::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_container", CCNode*, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_grouptitle", CCLabelTTF*, m_pGrouptitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pResultLabel", CCLabelTTF*, m_pResultLabel);
    return false;
}

SEL_MenuHandler MB_LayerGroupHistoryRecord::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerGroupHistoryRecord::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerGroupHistoryRecord::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool MB_LayerGroupHistoryRecord::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerGroupHistoryRecord::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (Msg == SC_RACE_HISTORY)
    {
        recvrace_history(recvPacket);
    }
    if (Msg == SC_RACE_REPLAY)
    {
        recvrace_replay(recvPacket);
    }
}



void MB_LayerGroupHistoryRecord::selectGroup(int nGroupId)
{
    m_nGroupId = nGroupId;
    m_nShowCount = 1;
    m_bRequest++;
    m_nStartRecord = 0;
    m_pGroupRecord->removeAllObjects();
    m_pPerfectRaceInterface->sendrace_history(0, m_nGroupId, m_nStartRecord, MAX_REQUEST_RECORD);

}

void MB_LayerGroupHistoryRecord::onCloseClicked(CCObject* pSender)
{
    m_pPerfectRaceInterface->onEntryClicked(this);
}

CCSize MB_LayerGroupHistoryRecord::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerGroupHistoryRecord::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    if (idx > m_pGroupRecord->count() - MAX_REQUEST_RECORD)
    {
        if(m_bRequest==0)
        {
            m_bRequest++;
            m_pPerfectRaceInterface->sendrace_history(0, m_nGroupId, m_nStartRecord, MAX_REQUEST_RECORD);
        }
    }
    
    idx = m_pGroupRecord->count()-idx-1;
    MB_RaceRecord* pRecord = dynamic_cast<MB_RaceRecord*>(m_pGroupRecord->objectAtIndex(idx));
    if (pRecord)
    {
        MB_NodeGroupRecordLive* pNode = MB_NodeGroupRecordLive::create(pRecord);
        if (pNode)
        {
            cell->addChild(pNode);
            pNode->setPosition(m_pContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
        }
    }
    else
    {
        CCString* pString = dynamic_cast<CCString*>(m_pGroupRecord->objectAtIndex(idx));
        MB_NodePerfectRaceRround* pNode = MB_NodePerfectRaceRround::create(0);
        if (pNode)
        {
            pNode->forceSetShowString(pString->getCString());
            cell->addChild(pNode);
            pNode->setPosition(m_pContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
        }

    }
    
    return cell;
}

unsigned int MB_LayerGroupHistoryRecord::numberOfCellsInTableView(CCTableView *table)
{
    return m_pGroupRecord->count();
}

/*
 message recvrace_history[id=13405]{
 required        int8            round                    =1;//当前所在轮数
 required        int8            group_id                =2;//分组的编号1至8,正赛为0
 repeated        p_race_rec      history_list            =3;//战报列表
 }
 */

static const char* pTitle[] =
{
    "2进1",
    "4进2",
    "8进4",
    "16进8",
    "32进16",
    "64进32",
    "128进64",
    "256进128",
    "512进256",
};
void MB_LayerGroupHistoryRecord::recvrace_history(MB_MsgBuffer* pRecv)
{
    uint8_t value = 0;
    pRecv->readU8(&value);
    m_nCurrentRound = value;
    pRecv->readU8(&value);
    if (value != m_nGroupId)
    {
        // not the same group id
        return;
    }
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    MB_RaceRecord* pRaceRecord = NULL;
    int step = 0;
    m_nStartRecord+=count;
    for (uint16_t i=0; i<count; ++i)
    {
        pRaceRecord = new MB_RaceRecord;
        if (pRaceRecord->read(pRecv))
        {
            step = pRaceRecord->getStep();
            if (step - m_nCurrentRound==1)
            {
                if (pRaceRecord->getStep() == 1)
                {
                    std::string winner,loser;
                    pRaceRecord->getName(winner, loser);
                    char buff[100] = {0};
                    sprintf(buff, "恭喜%s小组出线,进入决赛",winner.c_str());
//                    m_pGroupRecord->addObject(CCString::createWithFormat("-----恭喜%s小组出线,进入决赛-----",winner.c_str()));
                    m_pResultLabel->setString(buff);
                }
                m_pGroupRecord->addObject(CCString::create(pTitle[step-1]));
                m_pGroupRecord->addObject(pRaceRecord);
            }
            else
            {
                if (pRaceRecord->getStep() == 0)
                {
                    // exception here. this window just for group record
                }
                m_pGroupRecord->addObject(pRaceRecord);
            }
            m_nCurrentRound = step;
        }
    }
    if (m_nShowCount == 1)
    {
        m_pTableView->reloadData();
        m_nShowCount = 0;
    }
    else
    {
        CCPoint pt = m_pTableView->getContentOffset();
        m_pTableView->reloadData();
        pt.y = pt.y - count * m_CellSize.height;
        m_pTableView->setContentOffset(pt);
    }
    m_bRequest--;
}
