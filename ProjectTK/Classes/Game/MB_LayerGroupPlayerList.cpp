//
//  MB_LayerGroupPlayerList.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#include "MB_LayerGroupPlayerList.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_NodePerfectRacePlayer.h"

MB_LayerGroupPlayerList::MB_LayerGroupPlayerList()
{
    m_pPerfectRaceInterface = NULL;
    m_nGroupId = 0;
    m_pDataList = NULL;
    m_pTableView = NULL;
    
    m_pContainer = NULL;
    m_pGroupTitle = NULL;
    m_pBtnVeiwRecord = NULL;
}

MB_LayerGroupPlayerList::~MB_LayerGroupPlayerList()
{
    m_pPerfectRaceInterface = NULL;
    m_pDataList = NULL;
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pGroupTitle);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    CC_SAFE_RELEASE_NULL(m_pBtnVeiwRecord);
}

// init once only
bool MB_LayerGroupPlayerList::init(int nGroup)
{
    CCNode* pNode = loadResource("res/monsterrace_layer_teamreport.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        MB_CcbAutoMemberWnd* pWnd = MB_CcbAutoMemberWnd::create("res/monsterrace_node_detail.ccbi");
        if (pWnd)
        {
            m_CellSize = (*pWnd)["cellSize"]->getContentSize();
        }
        NSGameHelper::adjustScrollNode(m_pContainer);
        m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
        m_pTableView->retain();
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pContainer->addChild(m_pTableView);
        
        char title[24] = {};
        sprintf(title, "第%d组",nGroup);
        m_pGroupTitle->setString(title);
        requestPlayerList(nGroup);
        return true;
    }
    
    return false;
}

void MB_LayerGroupPlayerList::onResetWnd()
{
    m_pTableView->reloadData();
}
void MB_LayerGroupPlayerList::onCloseClicked(CCObject* pSender)
{
    m_pPerfectRaceInterface->onEntryClicked(this);
}
bool MB_LayerGroupPlayerList::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_container", CCNode*, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_grouptitle", CCLabelTTF*, m_pGroupTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnViewRecord", CCControlButton*, m_pBtnVeiwRecord);
    return false;
}

SEL_MenuHandler MB_LayerGroupPlayerList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerGroupPlayerList::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerGroupPlayerList::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onViewRaceRecord", MB_LayerGroupPlayerList::onViewRaceRecord);
    return NULL;
}

bool MB_LayerGroupPlayerList::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerGroupPlayerList::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_RACE_FIGHT_LIST:
            recvrace_fight_list(recvPacket);
            break;
        default:
            break;
    }

}

void MB_LayerGroupPlayerList::recvrace_fight_list(MB_MsgBuffer* pRecv)
{
    SOCKET_MSG_UNREGIST(SC_RACE_FIGHT_LIST);
    MB_Message::sharedMB_Message()->removeALLMessage();
    m_pDataList = m_pPerfectRaceInterface->queryFightPlayerListByGroupId(m_nGroupId);
    if (m_pDataList)
    {
        onResetWnd();
    }
}

void MB_LayerGroupPlayerList::requestPlayerList(int nGroup)
{
    m_nGroupId = nGroup;
    m_pDataList = m_pPerfectRaceInterface->queryFightPlayerListByGroupId(nGroup);
    if (m_pDataList == NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        SOCKET_MSG_REGIST(SC_RACE_FIGHT_LIST, MB_LayerGroupPlayerList);
        m_pPerfectRaceInterface->sendrace_fight_list(m_nGroupId);
    }
    else
    {
        onResetWnd();
    }
}

CCSize MB_LayerGroupPlayerList::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerGroupPlayerList::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    if (m_pDataList)
    {
        MB_RaceFighter* pPlayer = dynamic_cast<MB_RaceFighter*>(m_pDataList->objectAtIndex(idx)) ;
        CCNode* pNode = MB_NodePerfectRacePlayer::create(pPlayer);
        if (pNode)
        {
            cell->addChild(pNode);
            pNode->setPosition(m_pContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_LayerGroupPlayerList::numberOfCellsInTableView(CCTableView *table)
{
    if (m_pDataList)
    {
        return m_pDataList->count();
    }
    else
    {
        return 0;
    }
    return 0;
}

void MB_LayerGroupPlayerList::onPreRecordClicked(CCObject* pSender)
{
    
}
void MB_LayerGroupPlayerList::onRuleClicked(CCObject* pSender)
{
    
}
void MB_LayerGroupPlayerList::onGroupRecordClicked(CCObject* pSender)
{
    
}

void MB_LayerGroupPlayerList::onViewRaceRecord(CCObject* pSender)
{
    MB_ResWindow* pWnd = m_pPerfectRaceInterface->createGroupRecordDialogByGroupID(m_nGroupId);
    if (pWnd)
    {
        replaceLayer(pWnd);
    }
}