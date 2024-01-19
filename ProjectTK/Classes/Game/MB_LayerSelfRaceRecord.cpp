//
//  MB_LayerSelfRaceRecord.cpp
//  ProjectPM
//
//  Create by WenYong on 1/6/2014.
//
//
#include "MB_LayerSelfRaceRecord.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_NodeGroupRecordLive.h"
#include "MB_NodePerfectRaceRround.h"
#include "MB_CcbAutoMemberWnd.h"
MB_LayerSelfRaceRecord::MB_LayerSelfRaceRecord()
{
    scale9sprite	 = NULL;
    m_pNodeContainer	 = NULL;
    m_pInterface = NULL;
    m_pDataArray = new CCArray;
    m_pView = NULL;
    SOCKET_MSG_REGIST(SC_RACE_SELF_RECORD, MB_LayerSelfRaceRecord);
    SOCKET_MSG_REGIST(SC_RACE_REPLAY, MB_LayerSelfRaceRecord);
}
MB_LayerSelfRaceRecord::~MB_LayerSelfRaceRecord()
{
    CC_SAFE_RELEASE_NULL(scale9sprite);
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    CC_SAFE_RELEASE_NULL(m_pDataArray);
    SOCKET_MSG_UNREGIST(SC_RACE_SELF_RECORD);
    SOCKET_MSG_UNREGIST(SC_RACE_REPLAY);
}

bool MB_LayerSelfRaceRecord::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pInterface)
    {
        m_pDataSource = m_pInterface;
    }
    return m_pInterface != NULL;
}
bool MB_LayerSelfRaceRecord::init()
{
    CCNode* pNode = loadResource("res/monsterrace_layer_personalreport.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer1());
		addChild(pNode);
        
        MB_CcbAutoMemberWnd* pWnd = MB_CcbAutoMemberWnd::create("res/monsterrace_node_title1.ccbi");
        if (pWnd)
        {
            m_CellSize = (*pWnd)["cellSize"]->getContentSize();
        }
        NSGameHelper::adjustScrollNode(m_pNodeContainer);
        
        m_pView = CCTableView::create(this, m_pNodeContainer->getContentSize());
        m_pView->setDirection(kCCScrollViewDirectionVertical);
        m_pNodeContainer->addChild(m_pView);
        
        if (/*m_pInterface->getSelfRecordArray()->count()==0*/1)
        {
            MB_Message::sharedMB_Message()->showMessage("",15);
            m_pInterface->sendrace_self_record();
        }
        else
        {
            setData(m_pInterface->getSelfRecordArray());
        }
		return true;
	}
	return false;
}

void MB_LayerSelfRaceRecord::onResetWnd()
{
    m_pView->reloadData();
}
static const char* pTitle[] =
{
    "",
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
void MB_LayerSelfRaceRecord::setData(CCArray* pArray)
{
    if (pArray==NULL||pArray->count()==0)
    {
        return;
    }
    m_pDataArray->removeAllObjects();
    
    MB_RaceRecord* pTemp = dynamic_cast<MB_RaceRecord*>(pArray->objectAtIndex(0));
    
    CCARRAY_FOREACH_4TYPE(pArray, MB_RaceRecord*, pTemp)
    {
        m_pDataArray->addObject(CCString::create(pTitle[pTemp->getStep()]));
        m_pDataArray->addObject(pTemp);
    }

    onResetWnd();
}
bool MB_LayerSelfRaceRecord::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"scale9sprite",CCScale9Sprite*,scale9sprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeContainer",CCNode*,m_pNodeContainer);
	return false;
}
SEL_MenuHandler MB_LayerSelfRaceRecord::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerSelfRaceRecord::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerSelfRaceRecord::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerSelfRaceRecord::onCloseClick(CCObject* pSender)
{
    popWindow();
}
CCSize MB_LayerSelfRaceRecord::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerSelfRaceRecord::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

    idx = m_pDataArray->count()-idx-1;
    MB_RaceRecord* pRecord = dynamic_cast<MB_RaceRecord*>(m_pDataArray->objectAtIndex(idx));
    if (pRecord)
    {
        MB_NodeGroupRecordLive* pNode = MB_NodeGroupRecordLive::create(pRecord);
        if (pNode)
        {
            cell->addChild(pNode);
            pNode->setPosition(m_pNodeContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
        }
    }
    else
    {
        CCString* pString = dynamic_cast<CCString*>(m_pDataArray->objectAtIndex(idx));
        MB_NodePerfectRaceRround* pNode = MB_NodePerfectRaceRround::create(0);
        if (pNode)
        {
            pNode->forceSetShowString(pString->getCString());
            cell->addChild(pNode);
            pNode->setPosition(m_pNodeContainer->getContentSize().width/2.0,m_CellSize.height/2.0);
        }
        
    }
    return cell;
}

unsigned int MB_LayerSelfRaceRecord::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDataArray->count();
}

void MB_LayerSelfRaceRecord::onMsgRecv(CCNode* node, SocketResponse* response)
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
    if (Msg == SC_RACE_SELF_RECORD)
    {
        setData(m_pInterface->getSelfRecordArray());
    }
    else if(Msg == SC_RACE_REPLAY)
    {
        recvrace_replay(recvPacket);
    }
}