

#include "MB_LayerListEquipChange.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_ScrollBg.h"
//#include <algorithm>
USING_NS_CC;
USING_NS_CC_EXT;
#define actionSpanTime (0.05f)
#define actionMoveTime (0.25f)
//pvp排行逻辑功能类
MB_LayerListEquipChange::MB_LayerListEquipChange()
{
    isAllRun = true;
    m_szCell = CCSize(640,140);
    m_pNumString = NULL;
    m_pItemCount= NULL;
    m_pTableContainer = NULL;
    m_pTableView = NULL;
    m_pArrayShows = new CCArray();
    m_bShowRoleInfoPanel = false;
    SOCKET_MSG_REGIST(SC_ITEM_UP_EQUIP, MB_LayerListEquipChange);
}

MB_LayerListEquipChange::~MB_LayerListEquipChange()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pArrayShows);
    CC_SAFE_RELEASE_NULL(m_pNumString);
    CC_SAFE_RELEASE_NULL(m_pItemCount);
    
    SOCKET_MSG_UNREGIST(SC_ITEM_UP_EQUIP);
}

MB_LayerListEquipChange* MB_LayerListEquipChange::create(int type, uint8_t itemPos, uint64_t itemUID, uint64_t petUID)
{
    MB_LayerListEquipChange* layer = new MB_LayerListEquipChange();
    if (layer != NULL && layer->init(type, itemPos, itemUID, petUID)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerListEquipChange::init(int type, uint8_t itemPos, uint64_t itemUID, uint64_t petUID)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    setSubType(type);
    setItemPos(itemPos);
    setItemUID(itemUID);
    setPetUID(petUID);
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //读取界面
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/card_layer_switchequipment.ccbi", this);
    this->addChild(pNode);
    
    CC_SAFE_RELEASE_NULL(pCCBReader);
    OCandCppHelper::convertScollerViewSuitable(m_pTableContainer);
    NSGameHelper::adjustScrollNode(m_pTableContainer);
    
    onResetWnd();
    refreshCount();
    pNode->addChild(MB_ScrollBg::create(left_bottom,0.5f),-1);
	return true;
}

void MB_LayerListEquipChange::onResetWnd()
{
    //生成列表
    m_pArrayShows->removeAllObjects();
    
    if (m_uItemPos == kItemPosTreasure1)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getWingArray());
    }
    else if (m_uItemPos == kItemPosTreasure2)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getRuneStoreArray());
    }
    else if (m_uItemPos == kItemPosTreasure3)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getTotermArray());
    }
    else if (m_uItemPos == kItemPosEquip1)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getWeaponArray());
    }
    else if (m_uItemPos == kItemPosEquip2)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getHeadwareArray());
    }
    else if (m_uItemPos == kItemPosEquip3)
    {
        m_pArrayShows->addObjectsFromArray(MB_ItemMgr::getInstance()->getDefenceArray());
    }
    
    //列表中清除当前装备
    MB_ItemData* itemData = NULL;
    CCArray* equipedArray = CCArray::create();
    for (int i = 0; i < m_pArrayShows->count(); i++)
    {
        itemData = (MB_ItemData*)m_pArrayShows->objectAtIndex(i);
        if (itemData->getItemUID() == m_uItemUID) {
            m_pArrayShows->removeObjectAtIndex(i);
            i--;
            continue;
        }
        
        //将已装备的排在最后面
        if (itemData->getItemPetID() != 0)
        {
            equipedArray->addObject(itemData);
            m_pArrayShows->removeObjectAtIndex(i);
            i--;
        }
    }
    m_pArrayShows->addObjectsFromArray(equipedArray);
    CC_SAFE_RELEASE_NULL(equipedArray);
    allCellCount =m_pArrayShows->count()/PERLINEITEM + ((m_pArrayShows->count()%PERLINEITEM) == 0? 0:1);
    //建立or刷新列表
    if (m_pTableView == NULL)
    {
        CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pTableContainer->addChild(tableView);
        m_pTableView = tableView;
    }
    else
    {
        m_pTableView->reloadData();
    }
}

bool MB_LayerListEquipChange::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScrollsize", CCNode *, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNumString", CCNode *, m_pNumString);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemCount", CCLabelBMFont *, m_pItemCount);
    return true;
}

SEL_MenuHandler MB_LayerListEquipChange::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerListEquipChange::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerListEquipChange::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


void MB_LayerListEquipChange::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_ITEM_UP_EQUIP:
            MB_Message::sharedMB_Message()->removeALLMessage();
            popWindow(true);
            TutorialTriggerComplete
            break;
            
        default:
            break;
    }
    
}

void MB_LayerListEquipChange::onCloseClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onCloseClicked");
    TutorialTriggerComplete
    popWindow(true);
//    removeFromParent();
}

void MB_LayerListEquipChange::refreshCount()
{
    char temp[10] = {0};
    int count = m_pArrayShows->count();
    sprintf(temp, "%d", count);
    m_pItemCount->setString(temp);
    m_pNumString->setPositionX(130-(NSGameHelper::get_length(count)-2)*7);
}






CCSize MB_LayerListEquipChange::tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
    if (allCellCount-1==idx) {
        return m_szCell+CCSize(0,LASTCELLADDHEIGHT);
    }
    return m_szCell;
};
CCTableViewCell* MB_LayerListEquipChange::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    CCLayer* layer = CCLayer::create();
    layer->setContentSize(m_szCell);
    
    for (int i = idx*PERLINEITEM;i < (idx+1)*PERLINEITEM && i < m_pArrayShows->count();i++)
    {
        MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pArrayShows->objectAtIndex(i));
        if (itemData == NULL)
        {
            return cell;
        }
        MB_NodeItem* nodeIcon = MB_NodeItem::create(itemData->getItemUID(),KXUANZEZHUANGBEI);
        nodeIcon->setIsEquiped();
        if (allCellCount-1==idx) {
            nodeIcon->setPosition(ccp(m_szCell.width/PERLINEITEM*(i%PERLINEITEM)*0.93f + 74, m_szCell.height/2+15+LASTCELLADDHEIGHT));
        }else
        {
            nodeIcon->setPosition(ccp(m_szCell.width/PERLINEITEM*(i%PERLINEITEM)*0.93f + 74, m_szCell.height/2+15));
        }
        layer->addChild(nodeIcon);
    }
    cell->addChild(layer);
    bool isContains = false;
    for (int i =0; i<isRunedIdx.size(); i++) {
        if (isRunedIdx[i] == idx) {
            isContains = true;
            break;
        }
    }
    
    if (isAllRun||!isContains)
    {
        if (isAllRun&&idx>7) {
            return cell;
        }
        isRunedIdx.push_back(idx);
        if (isAllRun) {
            NSGameHelper::runMoveAndOptAction(layer, idx*actionSpanTime, actionMoveTime, true,true);
        }else
        {
            NSGameHelper::runMoveAndOptAction(layer, 0, actionMoveTime, true,true);
        }
    }
    return cell;
}

unsigned int MB_LayerListEquipChange::numberOfCellsInTableView(CCTableView *table)
{
    return allCellCount;
}

