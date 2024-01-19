//
//  MB_LayerAchievementWnd.cpp
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#include "MB_LayerAchievementWnd.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_ServerRewardData.h"
#include "MB_TaskSystemProtocol.h"
#include "MB_FunctionMgr.h"
#include "MB_TaskSystemInterface.h"
#include "MB_TaskSystemData.h"
#include "MB_LayerAchievementItem.h"
#include "Game.h"


MB_LayerAchievementWnd::MB_LayerAchievementWnd()
{
    arrayAchievement = CCArray::create();
    m_pNodeList	 = NULL;
    m_pTableView = NULL;
    SOCKET_MSG_REGIST(SC_TASK_GET_INFO, MB_LayerAchievementWnd);
    SOCKET_MSG_REGIST(SC_TASK_OPERATE, MB_LayerAchievementWnd);
    SOCKET_MSG_REGIST(SC_TASK_ERROR, MB_LayerAchievementWnd);
    SOCKET_MSG_REGIST(SC_TASK_NOTIFY, MB_LayerAchievementWnd);
}
MB_LayerAchievementWnd::~MB_LayerAchievementWnd()
{
    CC_SAFE_RELEASE_NULL(m_pNodeList);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    SOCKET_MSG_UNREGIST(SC_TASK_GET_INFO);
    SOCKET_MSG_UNREGIST(SC_TASK_OPERATE);
    SOCKET_MSG_UNREGIST(SC_TASK_ERROR);
    SOCKET_MSG_UNREGIST(SC_TASK_NOTIFY);
}
bool MB_LayerAchievementWnd::init()
{
    CCNode* pNode = loadResource("res/achievement_layer_main.ccbi");
    if(pNode == NULL)
	{
		return false;
		
	}
	addChild(pNode);
    reloadArray();
//    MB_CcbAutoMemberWnd* pWnd = MB_CcbAutoMemberWnd::create("res/achievement_node_unit.ccbi");
//    if (pWnd)
//    {
//        m_szUnitSize = (*pWnd)["size"]->getContentSize();
//    }

    m_szUnitSize = MB_LayerAchievementItem::create(NULL)->getItemSize();
    
    NSGameHelper::adjustScrollNode(m_pNodeList);
    m_pTableView = CCTableView::create(this, m_pNodeList->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pNodeList->addChild(m_pTableView);
    m_pTableView->retain();
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    if(!MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
    {
        return false;
    }
    return true;
}
void MB_LayerAchievementWnd::onResetWnd()
{
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    if(!MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
    {
        return;
    }
    ((MB_TaskSystemInterface*)pInterface)->sortTask();
    
    //可领取任务数量
    uint32_t nCount = 0;
    nCount = ((MB_TaskSystemInterface*)pInterface)->getAchievementCompleteCount();
    
    
    reloadArray();
    m_pTableView->reloadData();
}

void MB_LayerAchievementWnd::onCloseClicked(CCObject* pSender)
{
    ((MB_ResWindow*)getParent())->dirty();
    removeFromParent();
}
bool MB_LayerAchievementWnd::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"node_List",CCNode*,m_pNodeList);
    
	return false;
}
SEL_MenuHandler MB_LayerAchievementWnd::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerAchievementWnd::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerAchievementWnd::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}


CCSize MB_LayerAchievementWnd::cellSizeForTable(CCTableView *table)
{
    return m_szUnitSize;
}
void MB_LayerAchievementWnd::reloadArray()
{
    arrayAchievement = CCArray::create();
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
    {
        ((MB_TaskSystemInterface*)pInterface)->getAchievementArray(arrayAchievement,kUnComplateSelect);
        ((MB_TaskSystemInterface*)pInterface)->getAchievementArray(arrayAchievement,kComplateSelect);
        vector<int> vec;
        for (int i=0; i<arrayAchievement->count(); i++) {
              MB_TaskServerData* data = dynamic_cast<MB_TaskServerData*>(arrayAchievement->objectAtIndex(i));
            if (data->getStatus()==TASK_STATUS_COMITED) {
                vec.push_back(i);
            }
        }
        for (int i=0; i<vec.size(); i++) {
            CCObject* obj = arrayAchievement->objectAtIndex(vec[i]);
            obj->retain();
            arrayAchievement->removeObject(obj);
            arrayAchievement->insertObject(obj, 0);
            obj->release();
        }
    }
}
CCTableViewCell* MB_LayerAchievementWnd::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    reloadArray();
    if (idx >= arrayAchievement->count())
    {
        return NULL;
    }
    MB_TaskServerData* data = dynamic_cast<MB_TaskServerData*>(arrayAchievement->objectAtIndex(idx));
    MB_LayerAchievementItem* pWnd = MB_LayerAchievementItem::create(data);
    cell->setTag(data->getTaskId());
    cell->addChild(pWnd);
    pWnd->setPosition(m_szUnitSize.width/2.0,m_szUnitSize.height/2.0);
    if(idx==0)
    {
        pWnd->m_pLine->setVisible(false);
    }
    return cell;
}

unsigned int MB_LayerAchievementWnd::numberOfCellsInTableView(CCTableView *table)
{
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
    {
        CCArray* array = CCArray::create();
        ((MB_TaskSystemInterface*)pInterface)->getAchievementArray(array,kUnComplateSelect);
        if (((MB_TaskSystemInterface*)pInterface)->getAchievementArray(array,kComplateSelect))
        {
            return array->count();
        }
    }
    return 0;
}


void MB_LayerAchievementWnd::onMsgRecv(CCNode* node, SocketResponse* response)
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
    switch (Msg)
    {
        case SC_TASK_GET_INFO:
            dirty();
            break;
        case SC_TASK_OPERATE:
            recvtask_operate(recvPacket);
            break;
        case SC_TASK_ERROR:
            recvtask_error(recvPacket);
            break;
        case SC_TASK_NOTIFY:
            dirty();
            break;
        default:
            break;
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
void MB_LayerAchievementWnd::recvtask_operate(MB_MsgBuffer* recvPacket)
{
    uint8_t u8 = 0;
    uint32_t u32 = 0;
    recvPacket->readU8(&u8);
    recvPacket->readU32(&u32);
    if (u8 == kTaskAchievement)
    {
        // need update the unit
        NSGameFunction::CCFunctionInterface* pInterface = NULL;
        if(!MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionTask,&pInterface))
        {
            return;
        }
        ((MB_TaskSystemInterface*)pInterface)->sortTask();
        reloadArray();
        m_pTableView->reloadData();
        //        updateCell(u32);
    }
    
    recvPacket->skipU8();
    
    uint16_t u16 = 0;
    recvPacket->readU16(&u16);
//    CCArray* pArray = CCArray::create();
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
//        pArray->addObject(pValue);
        pValue->release();
    }
    
    MB_Message::sharedMB_Message()->showMessage(strReward.c_str());
    
    
//    if (u16)
//    {
//        MB_ResWindow* pWnd = MB_LayerRewardMore::create(pArray);
//        if (pWnd)
//        {
//            pushWindow(pWnd,true);
//        }
//    }
}

/*
 //操作错误通知
 message recvtask_error[id=20107]{
 required	int8				result			=1;			//1:任务不存在, 2:等级不足,3：参数错误,4:状态操作不正确,5:操作时发生不可预知的错误
 }
 */
void MB_LayerAchievementWnd::recvtask_error(MB_MsgBuffer* recvPacket)
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

