//
//  MB_LayerFinalHistoryRecord.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-25.
//
//

#include "MB_LayerFinalHistoryRecord.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_NodeFinalRecordLive.h"

MB_LayerFinalHistoryRecord::MB_LayerFinalHistoryRecord()
{
    m_pAtkName = NULL;
    m_pDefName = NULL;
    m_pAtkScore = NULL;
    m_pDefScore = NULL;
    m_pTableView = NULL;
    m_pContainer = NULL;
    m_pRaceRecord = NULL;
    m_pLivingData = new CCArray;
    SOCKET_MSG_REGIST(SC_RACE_REPLAY,MB_LayerFinalHistoryRecord);
}

MB_LayerFinalHistoryRecord::~MB_LayerFinalHistoryRecord()
{
    CC_SAFE_RELEASE_NULL(m_pAtkName);
    CC_SAFE_RELEASE_NULL(m_pDefName);
    CC_SAFE_RELEASE_NULL(m_pAtkScore);
    CC_SAFE_RELEASE_NULL(m_pDefScore);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pLivingData);
    SOCKET_MSG_UNREGIST(SC_RACE_REPLAY);
}

bool MB_LayerFinalHistoryRecord::init(MB_RaceRecord* pRaceRecord)
{
    if (pRaceRecord == NULL)
    {
        return false;
    }
    
    m_pRaceRecord = pRaceRecord;
    CCNode* pNode = loadResource("res/monsterrace_layer_report2.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        
        MB_CcbAutoMemberWnd* pWnd = MB_CcbAutoMemberWnd::create("res/monsterrace_node_title2.ccbi");
        if (pWnd)
        {
            m_CellSize = (*pWnd)["cellSize"]->getContentSize();
        }
        NSGameHelper::adjustScrollNode(m_pContainer);
        m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pContainer->addChild(m_pTableView);
        m_pTableView->retain();
        m_pLivingData->removeAllObjects();
        m_pRaceRecord->resolvRaceRecord(&m_pLivingData);
        onResetWnd();
        return true;
    }
    return false;
}

void MB_LayerFinalHistoryRecord::onResetWnd()
{
    if (m_pLivingData)
    {
        int winner_score,loser_score;
        std::string winner_name,loser_name;
        if (m_pRaceRecord)
        {
//            m_pRaceRecord->getScore(winner_score, loser_score);
//            m_pRaceRecord->getName(winner_name, loser_name);
            m_pRaceRecord->getResult(winner_score,loser_score,winner_name,loser_name);
            char buff[64] = {};
            sprintf(buff, "%d",winner_score);
            m_pAtkScore->setString(buff);
            sprintf(buff, "%d",loser_score);
            m_pDefScore->setString(buff);
            m_pAtkName->setString(winner_name.c_str());
            m_pDefName->setString(loser_name.c_str());
        }
        m_pTableView->reloadData();
    }
    
}

bool MB_LayerFinalHistoryRecord::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_role_atk", CCLabelTTF*, m_pAtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_role_def", CCLabelTTF*, m_pDefName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_atk_score", CCLabelTTF*, m_pAtkScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_def_score", CCLabelTTF*, m_pDefScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_container", CCNode*, m_pContainer);
    return false;
}

SEL_MenuHandler MB_LayerFinalHistoryRecord::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerFinalHistoryRecord::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerFinalHistoryRecord::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

bool MB_LayerFinalHistoryRecord::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerFinalHistoryRecord::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    if (Msg == SC_RACE_NEW_FIGHT)
    {
        recvrace_new_fight(recvPacket);
    }
    else if(Msg == SC_RACE_REPLAY)
    {
        recvrace_replay(recvPacket);
    }
}

void MB_LayerFinalHistoryRecord::recvrace_new_fight(MB_MsgBuffer* pRecv)
{
    onResetWnd();
}

CCSize MB_LayerFinalHistoryRecord::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerFinalHistoryRecord::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_RaceRoundRecord* pRound = dynamic_cast<MB_RaceRoundRecord*>(m_pLivingData->objectAtIndex(idx));
    
    MB_NodeFinalRecordLive* pNode = MB_NodeFinalRecordLive::create(pRound);
    if (pNode)
    {
        cell->addChild(pNode);
        pNode->setPosition(m_pContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
    }
    
    return cell;
    
}

unsigned int MB_LayerFinalHistoryRecord::numberOfCellsInTableView(CCTableView *table)
{
    return m_pLivingData->count();
}


void MB_LayerFinalHistoryRecord::onCloseClicked(CCObject* pSender)
{
    popWindow();
}

