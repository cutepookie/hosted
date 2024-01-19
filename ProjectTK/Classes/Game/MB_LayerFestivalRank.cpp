//
//  MB_LayerFestivalRank.cpp
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#include "MB_LayerFestivalRank.h"
#include "MB_NodeFestivalRank.h"
#include "MB_FunctionFestival.h"
#include "MB_FestivalProtocol.h"
#include "MB_Message.h"
#include "MB_ClientSocket.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"

MB_LayerFestivalRank::MB_LayerFestivalRank()
{
    m_pNodePower	 = NULL;
    m_pLabelJoinTimes	 = NULL;
    m_pLabelRank	 = NULL;
    m_pContainer	 = NULL;
    m_pLabelUpRankTimes = NULL;
    m_pFunction = NULL;
    m_pRankArray = NULL;
    m_bRequestData = false;
    m_pTableView = NULL;
    SOCKET_MSG_REGIST(RECV_FESTIVAL_RANK, MB_LayerFestivalRank);
}
MB_LayerFestivalRank::~MB_LayerFestivalRank()
{
    CC_SAFE_RELEASE_NULL(m_pLabelUpRankTimes);
    CC_SAFE_RELEASE_NULL(m_pNodePower);
    CC_SAFE_RELEASE_NULL(m_pLabelJoinTimes);
    CC_SAFE_RELEASE_NULL(m_pLabelRank);
    CC_SAFE_RELEASE_NULL(m_pContainer);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_RANK);
}
bool MB_LayerFestivalRank::init()
{
    CCNode* pNode = loadResource("res/festival_layer_rank.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}

bool MB_LayerFestivalRank::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pFunction = dynamic_cast<MB_FunctionFestival*>(pDataSource);
    if (m_pFunction)
    {
        m_pRankArray = m_pFunction->getRankData();
        return true;
    }
    return false;
}

void MB_LayerFestivalRank::onInitialized()
{
    m_CellSize = MB_NodeFestivalRank::getNodeSize();
    NSGameHelper::adjustScrollNode(m_pContainer);
    m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pContainer->addChild(m_pTableView);
    m_pTableView->setContentOffset(ccp(0,m_pContainer->getContentSize().height-m_pTableView->getContainer()->getContentSize().height));
    onResetWnd();
}

void MB_LayerFestivalRank::onResetWnd()
{
    if (m_pFunction)
    {
        char buf[128] = {};
        sprintf(buf, "%d次",m_pFunction->getTotalTimes());
        m_pLabelJoinTimes->setString(buf);
        if (m_pFunction->getOwenRank()!=0)
        {
            sprintf(buf, "第%d名",m_pFunction->getOwenRank());
            m_pLabelRank->setString(buf);
        }
        else
        {
            m_pLabelRank->setString("未上榜");
        }
        sprintf(buf, "参与次数大于%d次才能上榜",m_pFunction->getMinRankCount());
        m_pLabelUpRankTimes->setString(buf);
        m_pTableView->reloadData();
    }
}
bool MB_LayerFestivalRank::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePower",CCNode*,m_pNodePower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelJoinTimes",CCLabelTTF*,m_pLabelJoinTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelUpRankTimes", CCLabelTTF*, m_pLabelUpRankTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelRank",CCLabelTTF*,m_pLabelRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
	return false;
}
SEL_MenuHandler MB_LayerFestivalRank::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_LayerFestivalRank::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerFestivalRank::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerFestivalRank::onCloseClicked(CCObject* pSender)
{
    popWindow();
}

CCSize MB_LayerFestivalRank::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerFestivalRank::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    idx = m_pRankArray->count()-idx-1;
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCNode* pNode = createCellByIndex(idx);
        if (pNode)
        {
            cell->addChild(pNode);
            pNode->setTag(1);
            pNode->setPosition(m_CellSize.width/2.0f,m_CellSize.height/2.0f);
        }
    }
    else
    {
        cell->removeAllChildren();
        CCNode* pNode = createCellByIndex(idx);
        if (pNode)
        {
            cell->addChild(pNode);
            pNode->setTag(1);
            pNode->setPosition(m_CellSize.width/2.0f,m_CellSize.height/2.0f);
        }
    }
    if (idx == numberOfCellsInTableView(table)-1) // 最后一次
    {
        if (m_pFunction && !m_bRequestData)
        {
            if (m_pFunction->getWeatherAnyRankData())
            {
                MB_Message::sharedMB_Message()->showMessage("",15);
                m_pFunction->send_festival_rank_next();
                m_bRequestData = true;
                if (m_pTableView)
                {
                    m_fContainerHeight = m_pTableView->getContainer()->getContentSize().height;
                }
            }
        }
    }

    return cell;
}

unsigned int MB_LayerFestivalRank::numberOfCellsInTableView(CCTableView *table)
{
    if (m_pRankArray)
    {
        return m_pRankArray->count();
    }
    return 0;
}

void MB_LayerFestivalRank::updateCellNode(int idx,MB_NodeFestivalRank* pNode)
{
    MB_FestivalRankData* pData = dynamic_cast<MB_FestivalRankData*>(m_pRankArray->objectAtIndex(idx));
    if (pData)
    {
        if (pNode && m_pFunction && pData)
        {
            MB_MailReward* pReward = m_pFunction->queryRankReward(pData->getRank());
            pNode->setData(pData);
            pNode->setRewardData(pReward);
        }
    }
    else
    {
        MB_RankReward* pReward = dynamic_cast<MB_RankReward*>(m_pRankArray->objectAtIndex(idx));
        if (pReward && pNode)
        {
            pNode->setRankDataOnly(pReward);
        }
    }
}

CCNode* MB_LayerFestivalRank::createCellByIndex(int idx)
{
    MB_NodeFestivalRank* p = MB_NodeFestivalRank::create();
    updateCellNode(idx,p);
    return p;
}

void MB_LayerFestivalRank::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (!m_pFunction->checkProtocol(pRecv))
    {
        return;
    }
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (nMsg == RECV_FESTIVAL_RANK)
    {
        pRecv->skipU8();
        pRecv->skipU16();
        uint16_t count = 0;
        pRecv->readU16(&count);
        m_bRequestData = (count>=20);
        onResetWnd();
        float offset = -m_pTableView->getContainer()->getContentSize().height + m_fContainerHeight+100;
        m_pTableView->setContentOffset(ccp(0, offset));
    }
}