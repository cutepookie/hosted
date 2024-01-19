//
//  MB_LayerTaskMain.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-2.
//
//

#include "MB_LayerTaskMain.h"
#include "MB_TaskSystemInterface.h"
#include "MB_TaskSystemProtocol.h"
#include "MB_NodeTaskItem.h"
#include "MB_ServerRewardData.h"
#include "MB_TaskSystemData.h"
#include "Game.h"

MB_LayerTaskMain::MB_LayerTaskMain()
{
    m_nSelectType = kTaskDaily;
    m_pNodeTaskContainer = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_TASK_GET_INFO, MB_LayerTaskMain);
    SOCKET_MSG_REGIST(SC_TASK_OPERATE, MB_LayerTaskMain);
    SOCKET_MSG_REGIST(SC_TASK_ERROR, MB_LayerTaskMain);
    SOCKET_MSG_REGIST(SC_TASK_NOTIFY, MB_LayerTaskMain);
}
MB_LayerTaskMain::~MB_LayerTaskMain()
{
    m_nSelectType = kTaskUnknow;
    CC_SAFE_RELEASE_NULL(m_pNodeTaskContainer);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    
    SOCKET_MSG_UNREGIST(SC_TASK_GET_INFO);
    SOCKET_MSG_UNREGIST(SC_TASK_OPERATE);
    SOCKET_MSG_UNREGIST(SC_TASK_ERROR);
    SOCKET_MSG_UNREGIST(SC_TASK_NOTIFY);
}
void MB_LayerTaskMain::onResetWnd()
{
    MB_TaskSystemInterface* pInterface = dynamic_cast<MB_TaskSystemInterface*>(m_pDataSource);
    pInterface->sortTask();
    m_pTableView->reloadData();
}

bool MB_LayerTaskMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    MB_TaskSystemInterface* pTarget = dynamic_cast<MB_TaskSystemInterface*>(pDataSource);
    
    if (pTarget)
    {
        m_pDataSource = pTarget;
        return true;
    }
    
    return false;
}

void MB_LayerTaskMain::updateCell(uint32_t nTaskId)
{
    uint32_t count = numberOfCellsInTableView(m_pTableView);
    CCTableViewCell* pCell = NULL;
    for (uint32_t i=0; i<count; ++i)
    {
        pCell = m_pTableView->cellAtIndex(i);
        if(pCell->getTag() == nTaskId)
        {
            m_pTableView->updateCellAtIndex(i);
            return;
        }
    }
}

/*
 //某个任务在某个状态的操作上获得的奖励
 message recvtask_operate[id=20106]{
 required	int8							task_type					=1;//1：主线任务  2：日常任务   3：成就
 required	int32						task_id						=2;
 required	int8							status						=3;//状态
 repeated	p_reward_view		reward						=4;//奖励信息
 }
 */
void MB_LayerTaskMain::recvtask_operate(MB_MsgBuffer* recvPacket)
{
    uint8_t u8 = 0;
    uint32_t u32 = 0;
    recvPacket->readU8(&u8);
    recvPacket->readU32(&u32);
    
    recvPacket->skipU8();//chk 没有读取，导致奖励错误。
    
    
    uint16_t u16 = 0;
    recvPacket->readU16(&u16);
    RewardTempleteValue* pValue = NULL;
    
    std::string strReward = "";
    for (uint16_t i=0; i<u16; ++i)
    {
        pValue = new RewardTempleteValue;
        MB_RewardView::readRewardTemplateValue(pValue, recvPacket);
        char reward[50] = "";
        char name[50] = "";
        if (pValue->getType() == kRewardValueTypeItem)
        {
            MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(pValue->getValueID());
            if (itemTemplete != NULL)
            {
                sprintf(name,"%s",itemTemplete->getItemName());
            }
        }
        else if(pValue->getType() == kRewardValueTypePet)
        {
            MB_PetMgr::getInstance()->getPetRealNameWithType(name, pValue->getValueID());
        }
        sprintf(reward,"获得%s*%d ",name,pValue->getNumber());
        
        strReward.append(reward);
        pValue->release();
    }
    
    MB_Message::sharedMB_Message()->showMessage(strReward.c_str());
}

/*
 //操作错误通知
 message recvtask_error[id=20107]{
 required	int8				result			=1;			//1:任务不存在, 2:等级不足,3：参数错误,4:状态操作不正确,5:操作时发生不可预知的错误
 }
 */
void MB_LayerTaskMain::recvtask_error(MB_MsgBuffer* recvPacket)
{
    uint8_t u8 = 0;
    recvPacket->readU8(&u8);
    switch (u8)
    {
        case 1:
//            MB_Message::sharedMB_Message()->showMessage("任务不存在");
            break;
        case 2:
            MB_Message::sharedMB_Message()->showMessage("等级不足");
            break;
        case 3:
            MB_Message::sharedMB_Message()->showMessage("参数错误");
            break;
        case 4:
            MB_Message::sharedMB_Message()->showMessage("状态操作不正确");
            break;
        case 5:
            MB_Message::sharedMB_Message()->showMessage("操作时发生不可预知的错误");
            break;
        default:
            break;
    }
}

void MB_LayerTaskMain::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_TASK_GET_INFO:
            MB_Message::sharedMB_Message()->removeALLMessage();
            dirty();
            break;
        case SC_TASK_OPERATE:
            MB_Message::sharedMB_Message()->removeALLMessage();
            recvtask_operate(recvPacket);
            dirty();
            break;
        case SC_TASK_ERROR:
            recvtask_error(recvPacket);
            break;
        case SC_TASK_NOTIFY:
        {
        }
            break;
        default:
            break;
    }
}

bool MB_LayerTaskMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_task_container", CCNode*,m_pNodeTaskContainer);
    return false;
}

SEL_MenuHandler MB_LayerTaskMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerTaskMain::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerTaskMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool MB_LayerTaskMain::init()
{
    CCNode* pNode = loadResource("res/task_layer_list.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer12());
        addChild(pNode);
    }
    

    m_szUnitSize = MB_NodeTaskItem::getItemSize();
    NSGameHelper::adjustScrollNode(m_pNodeTaskContainer);
    m_pTableView = CCTableView::create(this, m_pNodeTaskContainer->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pNodeTaskContainer->addChild(m_pTableView);
    m_pTableView->retain();
    onResetWnd();
    return true;
}


void MB_LayerTaskMain::onCloseClicked(CCObject* pSender)
{
    ((MB_ResWindow*)getParent())->dirty();
    removeFromParent();
}


CCSize MB_LayerTaskMain::cellSizeForTable(CCTableView *table)
{
    return m_szUnitSize;
}

CCTableViewCell* MB_LayerTaskMain::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_TaskSystemInterface* pInterface = dynamic_cast<MB_TaskSystemInterface*>(m_pDataSource);
    if (pInterface)
    {
        MB_TaskServerData* pData = pInterface->getTaskServerDataByIndex(m_nSelectType,idx);
        MB_ResWindow* pWnd = MB_NodeTaskItem::create(pData,idx==0);
        if (pWnd)
        {
            cell->setTag(pData->getTaskId());
            cell->addChild(pWnd);
            pWnd->setPosition(m_szUnitSize.width/2.0,m_szUnitSize.height/2.0);
        }
    }
    
    return cell;
}

unsigned int MB_LayerTaskMain::numberOfCellsInTableView(CCTableView *table)
{
    MB_TaskSystemInterface* pInterface = dynamic_cast<MB_TaskSystemInterface*>(m_pDataSource);
    if (pInterface)
    {
        return pInterface->getTaskCountByType(m_nSelectType);
    }
    
    return 0;
}

void MB_LayerTaskMain::onStatusClicked(uint8_t nOperatType,uint32_t nTaskId)
{
    MB_TaskSystemInterface* pInterface = dynamic_cast<MB_TaskSystemInterface*>(m_pDataSource);
    if (pInterface)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        return pInterface->sendtask_operate(nOperatType, nTaskId);
    }
}
