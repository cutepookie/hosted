//
//  MB_LayerGroupRecordLive.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-24.
//
//

#include "MB_LayerGroupRecordLive.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_NodeGroupRecordLive.h"
#include "MB_NodePerfectRaceRround.h"
#include "MB_LocalProto.h"
#include "MB_LayerPerfectRaceMain.h"
#define LIVE_MAX_RECORD  10

MB_LayerGroupRecordLive::MB_LayerGroupRecordLive()
{
    m_pContainer = NULL;
    m_pTableView = NULL;
    m_pGroupLabel = NULL;
    m_pPerfectRaceInterface = NULL;
    m_pResultLabel = NULL;
    m_pLiveList = new CCArray;
    m_bShowRoleInfoPanel = false;
    SOCKET_MSG_REGIST(SC_RACE_NEW_FIGHT, MB_LayerGroupRecordLive);
    SOCKET_MSG_REGIST(SC_RACE_REPLAY, MB_LayerGroupRecordLive);
    m_nGroupID = 0;
}

MB_LayerGroupRecordLive::~MB_LayerGroupRecordLive()
{
    m_pPerfectRaceInterface = NULL;
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pGroupLabel);
    CC_SAFE_RELEASE_NULL(m_pLiveList);
    CC_SAFE_RELEASE_NULL(m_pResultLabel);
    SOCKET_MSG_UNREGIST(SC_RACE_NEW_FIGHT);
    SOCKET_MSG_UNREGIST(SC_RACE_REPLAY);
}

bool MB_LayerGroupRecordLive::init()
{
    CCNode* pNode = loadResource("res/gui_kingrace_going.ccbi");
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
        
        m_pResultLabel->setString("");
        m_pResultLabel->setPositionY(m_pResultLabel->getPositionY() - adjustHeight);
        m_pTableView = CCTableView::create(this, m_pContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pContainer->addChild(m_pTableView);
        onResetWnd();
    
        return true;
    }
    return false;
}

void MB_LayerGroupRecordLive::onEnter()
{
    MB_FunctionMainWnd::onEnter();
    m_pPerfectRaceInterface->sendrace_enter();
}

void MB_LayerGroupRecordLive::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    if(m_pPerfectRaceInterface->getIsLiving() == false)
    {
        m_pPerfectRaceInterface->goGroupRecordLayer(m_nGroupID);
    }
}

void MB_LayerGroupRecordLive::onExit()
{
    MB_FunctionMainWnd::onExit();
    m_pPerfectRaceInterface->sendrace_leave();
}

void MB_LayerGroupRecordLive::onResetWnd()
{
    m_pTableView->reloadData();
    m_pTableView->setContentOffset(ccp(0, 0));
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist"); m_pGroupLabel->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bzzz_txt_%d.png",m_pPerfectRaceInterface->getStep()+1)->getCString()));
}

bool MB_LayerGroupRecordLive::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_container", CCNode*, m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "label_group", CCSprite*, m_pGroupLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pResultLabel", CCLabelTTF*, m_pResultLabel);
    return false;
}

SEL_MenuHandler MB_LayerGroupRecordLive::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerGroupRecordLive::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerGroupRecordLive::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

bool MB_LayerGroupRecordLive::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerGroupRecordLive::onMsgRecv(CCNode* node, SocketResponse* response)
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
    if (Msg == SC_RACE_REPLAY)
    {
        recvrace_replay(recvPacket);
    }
}

void MB_LayerGroupRecordLive::onCloseClicked(CCObject* pSender)
{
    m_pPerfectRaceInterface->onEntryClicked(this);
}

CCSize MB_LayerGroupRecordLive::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerGroupRecordLive::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    idx = numberOfCellsInTableView(table)-idx-1;
    
    MB_RaceRecord *pRecord = dynamic_cast<MB_RaceRecord*>(m_pLiveList->objectAtIndex(idx));
    if (pRecord)
    {
        MB_NodeGroupRecordLive* pNode = MB_NodeGroupRecordLive::create(pRecord);
        if (pNode != NULL)
        {
            cell->addChild(pNode);
            pNode->setPosition(m_pContainer->getContentSize().width/2.0, m_CellSize.height/2.0);
        }
    }
    else
    {
        CCString* pString = dynamic_cast<CCString*>(m_pLiveList->objectAtIndex(idx));
        MB_NodePerfectRaceRround* pNode = MB_NodePerfectRaceRround::create(0);
        if (pNode)
        {
            pNode->forceSetShowString(pString->getCString());
            cell->addChild(pNode);
            pNode->setPosition(m_pContainer->getContentSize().width/2.0, m_CellSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_LayerGroupRecordLive::numberOfCellsInTableView(CCTableView *table)
{
    return m_pLiveList->count();
}

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
void MB_LayerGroupRecordLive::recvrace_new_fight(MB_MsgBuffer* pRecv)
{
    MB_RaceRecord* pRecord = new MB_RaceRecord;
    static int laststep = 0;
    if (pRecord->read(pRecv))
    {
        m_nGroupID = pRecord->getGroupId();
        if (pRecord->getGroupId()>8)
        {
            // 决赛战报
            return ;
        }
        if (laststep != pRecord->getStep())
        {
            laststep = pRecord->getStep();
            m_pLiveList->addObject(CCString::create(pTitle[laststep-1]));
        }
        m_pLiveList->addObject(pRecord);
        if (pRecord->getStep()==1)
        {
            if (pRecord->m_vResultList[0])
            {
                CCString* pString = CCString::createWithFormat("恭喜%s在第%d组出线，进入决赛阶段",pRecord->getAtkName().c_str(),pRecord->getGroupId());
                m_pResultLabel->setString(pString->getCString());
//                m_pLiveList->addObject(pString);
            }
            else
            {
                CCString* pString = CCString::createWithFormat("恭喜%s在第%d组出线，进入决赛阶段",pRecord->getDefName().c_str(),pRecord->getGroupId());
//                m_pLiveList->addObject(pString);
                m_pResultLabel->setString(pString->getCString());
            }
        }
        if (m_pLiveList->count() > LIVE_MAX_RECORD)
        {
            m_pLiveList->removeObjectAtIndex(0);
        }
        onResetWnd();
    }
}
