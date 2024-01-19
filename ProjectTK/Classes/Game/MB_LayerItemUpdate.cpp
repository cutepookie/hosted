

#include "MB_LayerItemUpdate.h"
#include "MB_ScrollBg.h"
#include "MB_GameInfoEnum.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerBackpack.h"
#define COST_ENOUGH_COLOR   ccc3(255,211,0)
#define COST_UNENOUGH_COLOR ccc3(255,0,0)


MB_LayerItemUpdate::MB_LayerItemUpdate()
{
    m_pJianTouA = NULL;
    m_pJianTouB = NULL;
    if (global_layerBackpack!=NULL) {
        global_layerBackpack->isResetWnd = false;
    }
    isUpdateUI = false;
    m_pTextDetailA1_Title= NULL;
    m_pTextDetailA2_Title= NULL;
    m_pTextDetailA1= NULL;
    m_pTextDetailA2= NULL;
    m_pTextDetailB1= NULL;
    m_pTextDetailB2= NULL;
    m_pItemLevel2 = NULL;
	m_pPosition = NULL;
	m_pItemName = NULL;
	m_pItemLevel = NULL;
	m_pItemCost = NULL;
	m_pItemCard = NULL;
	m_pEnhance = NULL;
	m_pAutoEnhance = NULL;
	m_uItemUID = 0;
	m_animationIndex = 0;
	m_animateRunning = false;
    for (int i = 0; i < MAX_ANIMATION_NUM; ++i)
    {
        m_pAnimationNode[i] = NULL;
    }
	m_pAnimationMgr = NULL;

	SOCKET_MSG_REGIST(SC_ITEM_MAX_REINFORCE, MB_LayerItemUpdate);
	SOCKET_MSG_REGIST(SC_ITEM_REINFORCE, MB_LayerItemUpdate);
	m_bShowRoleInfoPanel = true;
    lastShowRoleInfoPanel = MB_LayerRoleInfoHeader::showRoleInfoHeader(getShowRoleInfoPanel());
	m_pNodeEquip[0] = NULL;
	m_pNodeEquip[1] = NULL;
	m_pNodeEquip[2] = NULL;
	m_pNodeEquip[3] = NULL;
	m_pNodeEquip[4] = NULL;
	m_pNodeEquip[5] = NULL;
	m_pDataStruct = NULL;
	m_pOwerLabel = NULL;
}

MB_LayerItemUpdate::~MB_LayerItemUpdate()
{
    if (global_layerBackpack!=NULL) {
        global_layerBackpack->isResetWnd = true;
    }
    if (global_layerItemDetail) {
        global_layerItemDetail->setVisible(true);
    }
	SOCKET_MSG_UNREGIST(SC_ITEM_MAX_REINFORCE);
	SOCKET_MSG_UNREGIST(SC_ITEM_REINFORCE);

	CC_SAFE_RELEASE_NULL(m_pAnimationMgr);
    CC_SAFE_RELEASE_NULL(m_pJianTouA);
    CC_SAFE_RELEASE_NULL(m_pJianTouB);
	CC_SAFE_RELEASE_NULL(m_pPosition);
	CC_SAFE_RELEASE_NULL(m_pItemName);
	CC_SAFE_RELEASE_NULL(m_pItemLevel);
	CC_SAFE_RELEASE_NULL(m_pItemCost);
    CC_SAFE_RELEASE_NULL(m_pEnhance);
    CC_SAFE_RELEASE_NULL(m_pItemLevel2);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA1_Title);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA2_Title);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA1);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA2);
    CC_SAFE_RELEASE_NULL(m_pTextDetailB1);
    CC_SAFE_RELEASE_NULL(m_pTextDetailB2);
    CC_SAFE_RELEASE_NULL(m_pAutoEnhance);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[0]);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[1]);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[2]);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[3]);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[4]);
	CC_SAFE_RELEASE_NULL(m_pNodeEquip[5]);
	CC_SAFE_RELEASE_NULL(m_pOwerLabel);
    for (int i = 0; i < MAX_ANIMATION_NUM; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pAnimationNode[i]);
    }
}

MB_LayerItemUpdate* MB_LayerItemUpdate::create(uint64_t itemUID)
{
	MB_LayerItemUpdate* layer = new MB_LayerItemUpdate();
	if (layer != NULL && layer->init(itemUID)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool MB_LayerItemUpdate::init(uint64_t itemUID)
{
	if (!CCLayer::init())return false;
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_layer_strengthen.ccbi", this);
	this->addChild(NSGameHelper::createDisableTouchLayer());
	this->addChild(pNode);
    m_pAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimationMgr);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    for (int i = 0; i < MAX_ANIMATION_NUM; i++)
    {
        m_pAnimationNode[i]->setVisible(false);
    }

    MB_ItemData* pMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(itemUID);
    if (pMB_ItemData)
    {
        m_pDataStruct = MB_TeamData::getInstance()->getTeamMemberByUID(pMB_ItemData->getItemPetID());
    }else{
        m_pDataStruct = NULL;
    }
    resetItemUID(itemUID);
    addChild(MB_ScrollBg::create(right_bottom,.5f,2),-1);
	return true;
}

void MB_LayerItemUpdate::onResetWnd()
{
	onRefreshNameAndLevel();
	onRefreshAtrr();
	onRefreshEnhanceButton();
	onRefreshCost();
	onRefreshCard();
	//    initEquips();
}

void MB_LayerItemUpdate::initEquips()
{
	CCArray* pArr = CCArray::create();

	if (m_pDataStruct)
	{
		if (m_pDataStruct->m_pEquip1)pArr->addObject(m_pDataStruct->m_pEquip1);
		if (m_pDataStruct->m_pEquip2)pArr->addObject(m_pDataStruct->m_pEquip2);
		if (m_pDataStruct->m_pEquip3)pArr->addObject(m_pDataStruct->m_pEquip3);
		if (m_pDataStruct->m_pTreasure1)pArr->addObject(m_pDataStruct->m_pTreasure1);
		if (m_pDataStruct->m_pTreasure2)pArr->addObject(m_pDataStruct->m_pTreasure2);
		if (m_pDataStruct->m_pTreasure3)pArr->addObject(m_pDataStruct->m_pTreasure3);
	}
	else
	{
		pArr->addObject(MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID));
	}

	for (int i = 0; i < 6; ++i)
	{
		m_pNodeEquip[i]->removeAllChildren();
		if (i < pArr->count())
		{
			MB_ItemData* pMB_ItemData = dynamic_cast<MB_ItemData*>(pArr->objectAtIndex(i));
			MB_NodeItem* pNode = MB_NodeItem::create(pMB_ItemData->getItemUID());
            pNode->showNameCount(false);
			pNode->setDelegate(this);
			m_pNodeEquip[i]->addChild(pNode);
			pNode->setSelected(m_uItemUID == pMB_ItemData->getItemUID());
			if (pNode->isSelected())m_pSelectItem = pNode;
		}
		else
		{
            MB_NodeItem* pNode = MB_NodeItem::create((uint64_t)0);
			m_pNodeEquip[i]->addChild(pNode);
            pNode->showNameCount(false);
            pNode->showNameStar(false);
            pNode->setOnClickEnable(false);
        }
	}
}

void MB_LayerItemUpdate::resetItemUID(uint64_t itemUID)
{
	setItemUID(itemUID);
	MB_ItemData* pMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
	if (pMB_ItemData)
	{
		m_nCurSelectItemLevel = pMB_ItemData->getItemLevel();
	}
	initEquips();
	onResetWnd();
}

void MB_LayerItemUpdate::onClicked(MB_NodeItem* pNodeItem)
{
	if (!m_animateRunning)
	{
		resetItemUID(pNodeItem->getItemId());
	}
}

bool MB_LayerItemUpdate::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))return true;

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PositionSign", CCNode*, m_pPosition);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ItemName", CCLabelTTF*, m_pItemName)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "level", CCLabelBMFont*, m_pItemLevel)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "level2", CCLabelBMFont*, m_pItemLevel2)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cost", CCLabelBMFont*, m_pItemCost)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "AutoEnhance", CCControlButton*, m_pEnhance)
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Enhance", CCControlButton*, m_pAutoEnhance)
    
    for (int i = 0; i < MAX_ANIMATION_NUM; i++) {
        char temp[32];
        sprintf(temp, "n%d", i + 1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, temp, CCNode *, m_pAnimationNode[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip1", CCNode*, m_pNodeEquip[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip2", CCNode*, m_pNodeEquip[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip3", CCNode*, m_pNodeEquip[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip4", CCNode*, m_pNodeEquip[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip5", CCNode*, m_pNodeEquip[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip6", CCNode*, m_pNodeEquip[5]);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pOwerLabel", CCLabelTTF*, m_pOwerLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA1_Title", CCLabelTTF*, m_pTextDetailA1_Title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA2_Title", CCLabelTTF*, m_pTextDetailA2_Title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA1", CCLabelBMFont*, m_pTextDetailA1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA2", CCLabelBMFont*, m_pTextDetailA2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailB1", CCLabelBMFont*, m_pTextDetailB1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailB2", CCLabelBMFont*, m_pTextDetailB2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJianTouA", CCNode*, m_pJianTouA);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJianTouB", CCNode*, m_pJianTouB);
    return true;
}

SEL_MenuHandler MB_LayerItemUpdate::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerItemUpdate::onCloseClick);
	return NULL;
}

SEL_CCControlHandler MB_LayerItemUpdate::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAutoUpdateClick", MB_LayerItemUpdate::onClickAutoEnhance);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUpdateClick", MB_LayerItemUpdate::onClickEnhance);

	return NULL;
}

void MB_LayerItemUpdate::onCloseClick(CCObject* pSender)
{
    TutorialTriggerComplete
    if(isUpdateUI)
    {
        if (global_layerItemDetail!=NULL) {
            global_layerItemDetail->onReSet();
        }
    }
    removeFromParent();
    MB_LayerRoleInfoHeader::showRoleInfoHeader(lastShowRoleInfoPanel);
}

void MB_LayerItemUpdate::onClickAutoEnhance(CCObject* pSender)
{
	MB_ItemData* pdata;
	pdata = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
	if (pdata)
	{
		m_nCurSelectItemLevel = pdata->getItemLevel();
		//等級是否超上限
		if (pdata->getItemLevel() >= MB_RoleData::getInstance()->getLevel()) {
            MB_Message::sharedMB_Message()->showMessage("装备的等级已经达到当前玩家等级.");
			return;
		}
		MB_ItemMgr::getInstance()->senditem_max_reinforce(m_uItemUID, pdata->getItemPetID());
	}
}


void MB_LayerItemUpdate::onClickEnhance(CCObject* pSender)
{
	TutorialTriggerComplete
		MB_ItemData* pdata;
	pdata = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);

	if (pdata)
	{
		m_nCurSelectItemLevel = pdata->getItemLevel();
		//等級是否超上限
		if (pdata->getItemLevel() >= MB_RoleData::getInstance()->getLevel()) {
            MB_Message::sharedMB_Message()->showMessage("装备的等级已经达到当前玩家等级.");
			return;
		}
		MB_ItemMgr::getInstance()->senditem_reinforce(m_uItemUID, pdata->getItemPetID());
	}
}

void MB_LayerItemUpdate::onMsgRecv(CCNode* node, SocketResponse* response)
{
	assert(response != NULL);

	//將socket數据读取到序列化結构
	MB_MsgBuffer* recvPacket = response->getResponseData();

	//协议號
	uint16_t Msg = 0;
	recvPacket->Reset();
	recvPacket->skipU16();
	recvPacket->skipU8();
	recvPacket->readU16(&Msg);

	switch (Msg) {
	case SC_ITEM_REINFORCE:
	case SC_ITEM_MAX_REINFORCE:
		playEnhancePreAnim();
		break;
	default:
		break;
	}
}

void MB_LayerItemUpdate::onRefreshCard(void)
{
    m_pPosition->removeAllChildren();
    m_pItemCard = MB_NodeItem::create(m_uItemUID);
    m_pItemCard->showNameCount(false);
    m_pPosition->addChild(m_pItemCard);
}

void MB_LayerItemUpdate::onRefreshNameAndLevel(void)
{
	char* temp = new char[8];
	MB_ItemData*       pItemEntity = NULL;
	MB_ItemTemplate*   pItemTemplate = NULL;
	if (m_animateRunning)
	{
		//临時的當前等級
		std::vector<uint16_t>& levelList = ItemMgr->getEnhanceLevelList();
		int tempLevel = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID)->getItemLevel();
		int index = (m_animationIndex > 0) ? (m_animationIndex - 1) : 0;
		for (int i = levelList.size() - 1; i > index; i--) {
			tempLevel -= levelList[i];
		}
		sprintf(temp, "%d", tempLevel);
		m_pItemLevel->setString(temp);
        sprintf(temp, "%d", tempLevel+1);
        m_pItemLevel2->setString(temp);
	}
	else
	{
		pItemEntity = ItemMgr->getItemDataByUID(m_uItemUID);
		pItemTemplate = ItemMgr->getItemTemplateByID(pItemEntity ? pItemEntity->getItemID() : 0);
        //显示名称
        char* str = new char[32];
        MB_ItemMgr::getInstance()->realName(str, m_uItemUID);
        m_pItemName->setString(str);
        
		sprintf(temp, "%d", pItemEntity ? pItemEntity->getItemLevel() : 0);
		m_pItemLevel->setString(temp);
        sprintf(temp, "%d", pItemEntity ? pItemEntity->getItemLevel()+1 : 0);
        m_pItemLevel2->setString(temp);
	}

	CC_SAFE_DELETE_ARRAY(temp);

	char buff[100] = { 0 };
	if (m_pDataStruct)
    {
        char temp[128] = {0};
        char* name = new char[64];
        MB_PetMgr::getInstance()->getPetRealName(name, m_pDataStruct->m_pPet->getPetID());
        sprintf(temp, "已被\"%s\"装备", name);
        CC_SAFE_DELETE_ARRAY(name);
        m_pOwerLabel->setString(temp);
    }
    else
    {
        m_pOwerLabel->setString("未被装备");
    }
}

void MB_LayerItemUpdate::onRefreshAtrr(void)
{
	MB_ItemData*               pItemEntity;
	MB_ItemTemplate*           pItemTemplate;
	pItemEntity = ItemMgr->getItemDataByUID(m_uItemUID);
	pItemTemplate = ItemMgr->getItemTemplateByID(pItemEntity ? pItemEntity->getItemID() : 0);

	if (pItemTemplate&&pItemEntity)
	{
		eItem_Attribute_Type iat[MAX_ATRR_NUM];
		for (int i = 0; i < MAX_ATRR_NUM; ++i)
			iat[i] = eItem_Attribute_Type_Count;
		attributeMap& attributes = pItemTemplate->getAtrributeMap();
		attributeMap_It it = attributes.begin();
		for (int i = 0; (i < MAX_ATRR_NUM) && (it != attributes.end()); i++, it++)
			iat[i] = it->first;
        
        m_pTextDetailA1_Title->setVisible(false);
        m_pTextDetailA1->setVisible(false);
        m_pTextDetailB1->setVisible(false);
        m_pJianTouA->setVisible(false);
        m_pTextDetailA2_Title->setVisible(false);
        m_pTextDetailA2->setVisible(false);
        m_pTextDetailB2->setVisible(false);
        m_pJianTouB->setVisible(false);
        
        
		for (int i = 0; i < MAX_ATRR_NUM; i++)
		{
			if (eItem_Attribute_Type_Count != iat[i])
			{
				if (ItemMgr->getItemAttributeCommon(iat[i]))
				{
                    if(i==0)
                    {
                        m_pTextDetailA1_Title->setVisible(true);
                        m_pTextDetailA1->setVisible(true);
                        m_pTextDetailB1->setVisible(true);
                        m_pJianTouA->setVisible(true);
                        m_pTextDetailA1_Title->setString(ItemMgr->attrConvertToTitle(iat[i]).c_str());
                        m_pTextDetailA1->setString(ItemMgr->attrConvertToDesValue(iat[i], pItemTemplate->getAtrribute(iat[i], m_nCurSelectItemLevel, pItemEntity->getItemRank())).c_str());
                        m_pTextDetailB1->setString(ItemMgr->attrConvertToDesValue(iat[i], pItemTemplate->getAtrribute(iat[i], m_nCurSelectItemLevel + 1, pItemEntity->getItemRank())).c_str());
                    }else if(i==1)
                    {
                        m_pTextDetailA2_Title->setVisible(true);
                        m_pTextDetailA2->setVisible(true);
                        m_pTextDetailB2->setVisible(true);
                        m_pJianTouB->setVisible(true);
                        m_pTextDetailA2_Title->setString(ItemMgr->attrConvertToTitle(iat[i]).c_str());
                        m_pTextDetailA2->setString(ItemMgr->attrConvertToDesValue(iat[i], pItemTemplate->getAtrribute(iat[i], m_nCurSelectItemLevel, pItemEntity->getItemRank())).c_str());
                        m_pTextDetailB2->setString(ItemMgr->attrConvertToDesValue(iat[i], pItemTemplate->getAtrribute(iat[i], m_nCurSelectItemLevel + 1, pItemEntity->getItemRank())).c_str());
                    }
				}
			}
		}
	}
}

void MB_LayerItemUpdate::onRefreshCost(void)
{
	int  cost;
	bool enough;

	cost = ItemMgr->getEnhanceItemCostByUID(m_uItemUID);
	NSGameHelper::LabelFormatNumber(m_pItemCost, cost, true,"");
	enough = MB_RoleData::getInstance()->getCurrency(kmCurrency_Type_silver) >= cost;
	m_pItemCost->setColor(enough ? COST_ENOUGH_COLOR : COST_UNENOUGH_COLOR);
//    if (!enough) {
//        m_pEnhance->setEnabled(false);
//        m_pAutoEnhance->setEnabled(false);
//    }
}

void MB_LayerItemUpdate::onRefreshEnhanceButton(void)
{
	MB_ItemData* pItemEntity;
	pItemEntity = ItemMgr->getItemDataByUID(m_uItemUID);

	if (m_animateRunning || !pItemEntity)
	{
		m_pEnhance->setEnabled(false);
		m_pAutoEnhance->setEnabled(false);
	}
	else
	{
		m_pEnhance->setEnabled(true);
		m_pAutoEnhance->setEnabled(true);
	}
}

void MB_LayerItemUpdate::playEnhanceAnimation()
{
	m_animateRunning = true;
	std::vector<uint16_t>& levelList = ItemMgr->getEnhanceLevelList();
	if (levelList.size() > m_animationIndex)
	{
		m_pAnimationMgr->runAnimationsForSequenceNamed("EnhanceAnimation");
		m_pAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerItemUpdate::playEnhancePreAnim));
		onRefreshAnimation(levelList[m_animationIndex]);

		m_nCurSelectItemLevel += levelList[m_animationIndex];
		if (m_pSelectItem)m_pSelectItem->setLevelNum(m_nCurSelectItemLevel);

		MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Equip_Level_Up).c_str());
		m_animationIndex++;
	}
	else
	{
		MB_ItemData* pdata = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
		if (pdata)
		{
			m_nCurSelectItemLevel = pdata->getItemLevel();
			if (m_pSelectItem)m_pSelectItem->setLevelNum(m_nCurSelectItemLevel);
		}


		for (int i = 0; i < MAX_ANIMATION_NUM; i++)
		{
			m_pAnimationNode[i]->setVisible(false);
		}
		m_animationIndex = 0;
		m_animateRunning = false;
		levelList.clear();
	}
	dirty();
}

void MB_LayerItemUpdate::onExit()
{
    if(m_pAnimationMgr!=NULL)m_pAnimationMgr->setAnimationCompletedCallback(NULL, NULL);
	MB_ResWindow::onExit();
}
void MB_LayerItemUpdate::playEnhancePreAnim()
{
    isUpdateUI = true;
	if (ItemMgr->getEnhanceLevelList().size() > m_animationIndex)
	{
		m_animateRunning = true;
		this->schedule(schedule_selector(MB_LayerItemUpdate::tickParticle));
	}
	else
	{
		playEnhanceAnimation();
	}
}

void MB_LayerItemUpdate::tickParticle(float dt)
{
	//    if (m_pPreAnim->isActive() == false)
	{
		playEnhanceAnimation();
		this->unschedule(schedule_selector(MB_LayerItemUpdate::tickParticle));
	}
}

void MB_LayerItemUpdate::onRefreshAnimation(int animationLevel)
{
	animationLevel--;
	animationLevel = MAX(0, animationLevel);
	animationLevel = MIN(MAX_ANIMATION_NUM - 1, animationLevel);
	for (int i = 0; i < MAX_ANIMATION_NUM; i++)
	{
		m_pAnimationNode[i]->setVisible(false);
	}
	m_pAnimationNode[animationLevel]->setVisible(true);
}

