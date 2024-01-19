//
//  MB_LayerBackpack.cpp
//  ProjectMB
//
//  Create by chenhongkun on 2/9/2014.
//
//
#include "MB_LayerBackpack.h"
#include "MB_FunctionMgr.h"
#include "MB_BackpackInterface.h"
#include "MB_FunctionModule.h"
#include <algorithm>
#include "Game.h"
#include "MB_ParsingReward.h"
#include "MB_LayerRewardOne.h"
#include "MB_ScrollBg.h"
#include "MB_LayerItemDetail.h"
MB_LayerBackpack::MB_LayerBackpack()
{
    isResetWnd = true;
    isAnimation = true;
    m_pNumString = NULL;
    m_pScrollsize	 = NULL;
    m_pPageEquipBtn	 = NULL;
    m_pPageItemBtn	 = NULL;
    m_pPageDebrisBtn = NULL;
    m_pItemCount	 = NULL;
    m_nPageType = kNoType;
    m_pInterface = NULL;
    m_pEquipLayer = NULL;
    m_pItemLayer = NULL;
    m_pDataSource = NULL;
    m_pNodeDebrisNum = NULL;
    m_pNodeItemNum = NULL;
    m_pTTFDebrisNum = NULL;
    m_pTTFItemNum = NULL;
    
    m_bChangePage = true;
    m_bShowRoleInfoPanel = false;
    SOCKET_MSG_REGIST(SC_BOX_ITEM, MB_LayerBackpack);
    SOCKET_MSG_REGIST(SC_ITEM_USE, MB_LayerBackpack);
    SOCKET_MSG_REGIST(SC_COMBINE_GER, MB_LayerBackpack);
    SOCKET_MSG_REGIST(SC_COMBINE_EQUIP, MB_LayerBackpack);
    SOCKET_MSG_REGIST(SC_ITEM_UPDATE, MB_LayerBackpack);
    SOCKET_MSG_REGIST(SC_ITEM_COMPOUND, MB_LayerBackpack);
}
MB_LayerBackpack::~MB_LayerBackpack()
{
    global_layerBackpack = NULL;
    CC_SAFE_RELEASE_NULL(m_pNumString);
    CC_SAFE_RELEASE_NULL(m_pScrollsize);
    CC_SAFE_RELEASE_NULL(m_pPageEquipBtn);
    CC_SAFE_RELEASE_NULL(m_pPageDebrisBtn);
    CC_SAFE_RELEASE_NULL(m_pPageItemBtn);
    CC_SAFE_RELEASE_NULL(m_pItemCount);
    CC_SAFE_RELEASE_NULL(m_pEquipLayer);
    CC_SAFE_RELEASE_NULL(m_pItemLayer);
    CC_SAFE_RELEASE_NULL(m_pNodeDebrisNum);
    CC_SAFE_RELEASE_NULL(m_pNodeItemNum);
    CC_SAFE_RELEASE_NULL(m_pTTFDebrisNum);
    CC_SAFE_RELEASE_NULL(m_pTTFItemNum);
    SOCKET_MSG_UNREGIST(SC_BOX_ITEM);
    SOCKET_MSG_UNREGIST(SC_ITEM_USE);
    SOCKET_MSG_UNREGIST(SC_COMBINE_GER);
    SOCKET_MSG_UNREGIST(SC_COMBINE_EQUIP);
    SOCKET_MSG_UNREGIST(SC_ITEM_UPDATE);
    SOCKET_MSG_UNREGIST(SC_ITEM_COMPOUND);
}
MB_LayerBackpack* MB_LayerBackpack::create()
{
    MB_LayerBackpack* layer = new MB_LayerBackpack();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}
bool MB_LayerBackpack::init()
{
    if ( !CCLayer::init() )return false;
    global_layerBackpack = this;
    loadResource("res/item_node_unitopen.ccbi");
    
    CCNode* pNode = loadResource("res/item_layer_debrislist.ccbi");
    if(pNode)
    {
        addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pScrollsize);
        
        NSGameFunction::CCFunctionInterface *pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionBackpack ,&pInterface))
             m_pInterface = dynamic_cast<MB_BackpackInterface*>(pInterface);

        m_pDataSource = m_pInterface->getEquipDataSource();
        
        ((MB_EquipBackpackDataSource*)m_pDataSource)->isRunedIdx.clear();
        ((MB_EquipBackpackDataSource*)m_pDataSource)->isAllRun = true;
        scheduleOnce(schedule_selector(MB_LayerBackpack::updateIsContains), .5f);
        
        CCTableView* tableView = CCTableView::create(m_pDataSource, m_pScrollsize->getContentSize());
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pScrollsize->addChild(tableView);
        m_pTableView = tableView;
        m_pTableView->setSwaller(false);
        m_pTableView->setTouchPriority(-99);
        
        
        onEquipPageClicked();
        
        m_pPageEquipBtn->setIsScale(false);
        m_pPageDebrisBtn->setIsScale(false);
        m_pPageItemBtn->setIsScale(false);
        
        pNode->addChild(MB_ScrollBg::create(left_bottom,0.5f),-1);
        return true;
    }
	return false;
}

void MB_LayerBackpack::updateIsContains(float dt)
{
    ((MB_EquipBackpackDataSource*)m_pDataSource)->isAllRun = false;
}
void MB_LayerBackpack::updateIsContains2(float dt)
{
    ((MB_ItemBackpackDataSource*)m_pDataSource)->isAllRun = false;
}
void MB_LayerBackpack::updateIsContains3(float dt)
{
    ((MB_ItemDebrisDataSource*)m_pDataSource)->isAllRun = false;
}
bool MB_LayerBackpack::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_BackpackInterface*>(pDataSource);
    return m_pInterface != NULL;
}

bool MB_LayerBackpack::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pScrollsize",CCNode*,m_pScrollsize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPageEquipBtn",CCMenuItemImage*,m_pPageEquipBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPageDebrisBtn",CCMenuItemImage*,m_pPageDebrisBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPageItemBtn",CCMenuItemImage*,m_pPageItemBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemCount",CCLabelBMFont*,m_pItemCount);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeDebrisNum",CCNode*,m_pNodeDebrisNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeItemNum",CCNode*,m_pNodeItemNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFDebrisNum",CCLabelBMFont*,m_pTTFDebrisNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFItemNum",CCLabelBMFont*,m_pTTFItemNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNumString",CCNode*,m_pNumString);
    
	return false;
}

SEL_MenuHandler MB_LayerBackpack::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onEquipPageClicked",MB_LayerBackpack::onEquipPageClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onItemPageClicked",MB_LayerBackpack::onItemPageClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onItemDebrisClicked",MB_LayerBackpack::onItemDebrisClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerBackpack::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerBackpack::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerBackpack::onEquipPageClicked(CCObject* pSender)
{
    if (m_nPageType == kPageEquip) {
        return;
    }

    m_bChangePage = true;
    m_nPageType = kPageEquip;
    isAnimation = true;
    onResetWnd();
}
void MB_LayerBackpack::onItemPageClicked(CCObject* pSender)
{
    if (m_nPageType == kPageItem) {
        return;
    }
    m_bChangePage = true;
    m_nPageType = kPageItem;
    isAnimation = true;
    onResetWnd();
}

void MB_LayerBackpack::onItemDebrisClicked(CCObject* pSender)
{
    if (m_nPageType == kPageDebris) {
        return;
    }
    m_bChangePage = true;
    m_nPageType = kPageDebris;
    isAnimation = true;
    onResetWnd();
    TutorialTriggerComplete
}

void MB_LayerBackpack::onCloseClick(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}



void MB_LayerBackpack::onResetWnd()
{
    m_pPageEquipBtn->setEnabled(m_nPageType != kPageEquip);
    m_pPageDebrisBtn->setEnabled(m_nPageType != kPageDebris);
    m_pPageItemBtn->setEnabled(m_nPageType != kPageItem);

    if(m_nPageType == kPageItem)
    {
        MB_ItemMgr::getInstance()->sortOtherArray();
        m_pDataSource = m_pInterface->getMB_ItemDataSource();
        ((MB_ItemBackpackDataSource*)m_pDataSource)->isRunedIdx.clear();
        ((MB_ItemBackpackDataSource*)m_pDataSource)->isAllRun = true;
        scheduleOnce(schedule_selector(MB_LayerBackpack::updateIsContains2), .5f);
        m_pTableView->setDataSource(m_pDataSource);


    }
    else if(m_nPageType == kPageEquip)
    {
        m_pDataSource = m_pInterface->getEquipDataSource();
        ((MB_EquipBackpackDataSource*)m_pDataSource)->isRunedIdx.clear();
        ((MB_EquipBackpackDataSource*)m_pDataSource)->isAllRun = true;
        scheduleOnce(schedule_selector(MB_LayerBackpack::updateIsContains), .5f);
        m_pTableView->setDataSource(m_pDataSource);
    }
    else if(m_nPageType == kPageDebris)
    {
        MB_ItemMgr::getInstance()->sortDebrisArray();
        m_pDataSource = m_pInterface->getDebrisDataSource();
        ((MB_ItemDebrisDataSource*)m_pDataSource)->isRunedIdx.clear();
        ((MB_ItemDebrisDataSource*)m_pDataSource)->isAllRun = true;
        scheduleOnce(schedule_selector(MB_LayerBackpack::updateIsContains3), .5f);
        m_pTableView->setDataSource(m_pDataSource);
    }
  
    CCPoint offset = m_pTableView->getContentOffset();
    m_pTableView->reloadData();
    if(!m_bChangePage && m_nPageType == kPageEquip)m_pTableView->setContentOffset(offset);
    m_bChangePage = false;
    refreshCount();
    
    m_pNodeItemNum->setVisible(false);
    m_pNodeDebrisNum->setVisible(false);
    
    //可合成数量
    int num = 0;
    CCArray* array = MB_ItemMgr::getInstance()->getItemDebrisArray();
    MB_ItemData* itemData = NULL;
    CCARRAY_FOREACH_4TYPE(array, MB_ItemData*, itemData)
    {
        MB_ItemTemplate* templete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
        int n = itemData->getItemNumber()/templete->getComposeNum();
        if(n > 0)
        {
            num += n;
        }
    }
    if(num > 0)
    {
        m_pNodeDebrisNum->setVisible(true);
        if (num>99) {
            m_pTTFDebrisNum->setString("!");
        }else
        {
            char str[32] = "";
            sprintf(str,"%d",num);
            m_pTTFDebrisNum->setString(str);
        }
    }
    //可用道具
    num = 0;
    array = MB_ItemMgr::getInstance()->getOtherArray();
    itemData = NULL;
    CCARRAY_FOREACH_4TYPE(array, MB_ItemData*, itemData)
    {
        MB_ItemTemplate* templete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
        if(templete->getItemType() == kOTHER_BOX)
        {
            num += itemData->getItemNumber();
        }
    }
    if(num > 0)
    {
        m_pNodeItemNum->setVisible(true);
        if (num>99) {
            m_pTTFItemNum->setString("!");
        }else
        {
            char str[32] = "";
            sprintf(str,"%d",num);
            m_pTTFItemNum->setString(str);
        }
    }
    
    MB_LayerRewardOne* rewardOne  = (MB_LayerRewardOne*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(14555);
    if (rewardOne!=NULL) {
        rewardOne->restTouch();
    }
    MB_LayerRewardMore2* rewardMore2  = (MB_LayerRewardMore2*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(14556);
    if (rewardMore2!=NULL) {
        rewardMore2->restTouch();
    }
}

void MB_LayerBackpack::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg) {
        case SC_BOX_ITEM:
        {
            if (global_layerItemDetail==NULL) {
                onResetWnd();
            }
            int result = 0;
            if (recvPacket->readU8(&result))
            {
                if (result == 1)//成功
                {
                    MB_ParsingReward* pRward = MB_ParsingReward::create(recvPacket);
                    CCArray* pArray = pRward->getRewardArray();
                    if(pArray->count() == 1)
                    {
                        RewardTempleteValue* rewardValue = dynamic_cast<RewardTempleteValue*>(pArray->objectAtIndex(0));
                        if (rewardValue != NULL)
                        {
                            MB_LayerRewardOne* rewardOne = MB_LayerRewardOne::create(rewardValue->getType(), rewardValue->getValueID(), rewardValue->getNumber());
                            rewardOne->setShareType(kShareTypeListBox);
                            CCDirector::sharedDirector()->getRunningScene()->addChild(rewardOne,Z_ORDER_OUTSHOW,14555);
                        }
                    }
                    else if(pArray->count() > 1)
                    {
                        MB_LayerRewardMore2* rewardMore = MB_LayerRewardMore2::create(pArray);
                        if(rewardMore != NULL)
                        {
                            CCDirector::sharedDirector()->getRunningScene()->addChild(rewardMore,Z_ORDER_OUTSHOW,14556);
                        }
                    }
                    
                    
                    int16_t   itemTypeID = 0;
                    int8_t  num = 0;
                    recvPacket->readU16(&itemTypeID);
                    recvPacket->readU8(&num);
                }
                else if (result == 2) {
                    MB_Message::sharedMB_Message()->showMessage("开启失败, 道具不足.");
                }
                else //失败,未知原因
                {
                    MB_Message::sharedMB_Message()->showMessage("开启失败.");
                }
            }
        }
            break;
        case SC_ITEM_USE:
        case SC_COMBINE_GER:
        case SC_COMBINE_EQUIP:
        case SC_ITEM_UPDATE:
        {
            if (global_layerItemDetail==NULL) {
                onResetWnd();
            }
        }
            break;
        case SC_ITEM_COMPOUND:
        {
            uint8_t result;
            recvPacket->readU8(&result);
            if(result == 1)
            {
                uint16_t data16;
                recvPacket->readU16(&data16);
                MB_ItemTemplate *templete = NULL ;
                templete = MB_ItemMgr::getInstance()->getItemTemplateByID(data16);

                if (templete != NULL)
                {
                    if (global_layerItemDetail==NULL) {
                        onResetWnd();
                    }
                    MB_LayerRewardOne* rewardOne = MB_LayerRewardOne::create(kRewardValueTypeItem,templete->getComposeItemID(),1);
                    CCDirector::sharedDirector()->getRunningScene()->addChild(rewardOne,Z_ORDER_OUTSHOW);
                    return;
                }
            }
            else
            {
                MB_Message::sharedMB_Message()->showMessage("材料不足");
            }
            
        }
            break;
        default:
            break;
    }
}

void MB_LayerBackpack::refreshCount()
{
    char temp[100] = {0};
    unsigned int count;
    if(m_nPageType == kPageItem)
    {
        count = MB_ItemMgr::getInstance()->getOtherArray()->count();
    }
    else if(m_nPageType == kPageDebris)
    {
        count =MB_ItemMgr::getInstance()->getItemDebrisArray()->count();
    }
    else
    {
        count =MB_ItemMgr::getInstance()->getEquipArray()->count();
    }
    sprintf(temp, "%d", count);
    m_pItemCount->setString(temp);
    
    m_pNumString->setPositionX(130-(NSGameHelper::get_length(count)-2)*7);
}

