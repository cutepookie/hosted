
#include "MB_ActivatyMainLayer.h"
#include "MB_LayerEventUnit.h"

#include "MB_LayerItemDetail.h"
MB_LayerEventUnit::MB_LayerEventUnit(){

	m_pCancollect = NULL;
	m_pMutilCollect = NULL;
	m_pCollectBt = NULL;
	for (int i = 0; i < 4; i++) {

		m_pMoney[i] = NULL;
		m_pIcon[i] = NULL;
	}
	m_pNodeSize = NULL;

	SOCKET_MSG_REGIST(SC_ACTIVITY_UPDATE, MB_LayerEventUnit);
	SOCKET_MSG_REGIST(SC_ACTIVITY_DRAW, MB_LayerEventUnit);
}
MB_LayerEventUnit::~MB_LayerEventUnit(){


	CC_SAFE_RELEASE(m_pCancollect);
	CC_SAFE_RELEASE(m_pMutilCollect);

	for (int i = 0; i < 4; i++) {

		CC_SAFE_RELEASE(m_pMoney[i]);
		CC_SAFE_RELEASE(m_pIcon[i]);
	}
	CC_SAFE_RELEASE(m_pCollectBt);
	CC_SAFE_RELEASE(m_pNodeSize);
	SOCKET_MSG_UNREGIST(SC_ACTIVITY_DRAW);
	SOCKET_MSG_UNREGIST(SC_ACTIVITY_UPDATE);


}
bool MB_LayerEventUnit::init(int type){

	if (MB_ResWindow::init() == false){

		return false;
	}

	m_nType = type;
	char filename[100];
    if (type == 0){
        
        sprintf(filename, "res/activity_node_des.ccbi");
        
    }
	else if ((type == 2)||(type == 3)||(type == 4)||(type == 6)||(type == 7)){

		sprintf(filename, "res/activity_node_get.ccbi");

	}
	else if ((type == 1)||(type == 5)){

		sprintf(filename, "res/activity_node_exchange");

	}
	else
	{
		CCLOG("ERROR: not found ccb");
	}
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode*  node = pCCBReader->readNodeGraphFromFile(filename, this);
	pCCBReader->release();
	this->addChild(node);
	return true;
}
MB_LayerEventUnit * MB_LayerEventUnit::create(int type){

	MB_LayerEventUnit *ptr = new MB_LayerEventUnit();
	if (ptr && ptr->init(type)){

		ptr->autorelease();
		return  ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerEventUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickCollect", MB_LayerEventUnit::onClickCollect);
	return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerEventUnit::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

	return NULL;
}
bool MB_LayerEventUnit::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCancollect", CCLabelBMFont *, m_pCancollect);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMutilCollect", CCLabelTTF *, m_pMutilCollect);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCollectBt", CCMenuItemImage *, m_pCollectBt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoney0", CCLabelTTF *, m_pMoney[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoney1", CCLabelTTF *, m_pMoney[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoney2", CCLabelTTF *, m_pMoney[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoney3", CCLabelTTF *, m_pMoney[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIcon0", CCNode *, m_pIcon[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIcon1", CCNode *, m_pIcon[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIcon2", CCNode *, m_pIcon[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIcon3", CCNode *, m_pIcon[3]);

	return false;
}
void MB_LayerEventUnit::onClickCollect(CCObject *){

	sendactivity_draw(m_nActitvyID, m_nUnitID);
}
CCSize MB_LayerEventUnit::getUnitSize(){

	return m_pNodeSize->getContentSize();
}
void MB_LayerEventUnit::setActivityAndUnit(int activity, int ID){

	m_nActitvyID = activity;
	m_nUnitID = ID;
	MB_MoneyEevntData *data = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(m_nActitvyID);
	if (data == NULL)return;

	MB_MoneyEevntUnit *unit = data->getUnitByID(m_nUnitID);
	m_pMutilCollect->setString(unit->getDescription());
	for (int i = 0; i < 4; i++){

		if (m_pMoney[i] != NULL){

			m_pMoney[i]->setString("");
			m_pIcon[i]->removeAllChildren();
		}
	}

	if (data->getType() == 1){

		int index = 0;
		CCObject *obj;
		CCARRAY_FOREACH(unit->getReward(), obj){

			MB_EventReward* data = (MB_EventReward *)obj;
			if (data->getNum() > 0){

				addIcon(data->getItemType(), data->getNum(), &index, 0, 0, data->getIsPet());

			}
		}
		index = 3;

		if (unit->getCoin() > 0){

			addIcon(COIN_ID, unit->getCoin(), &index, 0, 0, false);
		}
		if (unit->getRoleExp() > 0){

			addIcon(ROLE_EXP_ID, unit->getRoleExp(), &index, 0, 0, false);

		}
		if (unit->getPetExp() > 0){

			addIcon(GER_EXP_ID, unit->getPetExp(), &index, 0, 0, false);
		}
		if (unit->getGold() > 0){

			addIcon(GOLD_ID, unit->getGold(), &index, 0, 0, false);
		}
		if (unit->getReputation() > 0){

			addIcon(REPUTATION_ID, unit->getReputation(), &index, 0, 0, false);
		}

		for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next){

			addIcon(item->itemTypeId, item->itemNum, &index, item->itemLevel, item->itemRank, item->itemNum < 0);
		}
		this->recvactivity_draw(NULL);


	}
	else if (data->getType() == 5){

		int index = 0;
		CCObject *obj;
		CCARRAY_FOREACH(unit->getReward(), obj){

			MB_EventReward* data = (MB_EventReward *)obj;
			if (data->getNum() > 0){

				addIcon(data->getItemType(), data->getNum(), &index, 0, 0, data->getIsPet());

			}
		}
		index = 1;

		if (unit->getCoin() > 0){

			addIcon(COIN_ID, unit->getCoin(), &index, 0, 0, false);
		}
		if (unit->getRoleExp() > 0){

			addIcon(ROLE_EXP_ID, unit->getRoleExp(), &index, 0, 0, false);

		}
		if (unit->getPetExp() > 0){

			addIcon(GER_EXP_ID, unit->getPetExp(), &index, 0, 0, false);
		}
		if (unit->getGold() > 0){

			addIcon(GOLD_ID, unit->getGold(), &index, 0, 0, false);
		}
		if (unit->getReputation() > 0){

			addIcon(REPUTATION_ID, unit->getReputation(), &index, 0, 0, false);
		}

		for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next){

			addIcon(item->itemTypeId, item->itemNum, &index, item->itemLevel, item->itemRank, item->itemNum < 0);
		}
		this->recvactivity_draw(NULL);


	}
	else {


		int index = 0;
		if (unit->getCoin() > 0){

			addIcon(COIN_ID, unit->getCoin(), &index, 0, 0, false);
		}
		if (unit->getRoleExp() > 0){

			addIcon(ROLE_EXP_ID, unit->getRoleExp(), &index, 0, 0, false);

		}
		if (unit->getPetExp() > 0){

			addIcon(GER_EXP_ID, unit->getPetExp(), &index, 0, 0, false);
		}
		if (unit->getGold() > 0){

			addIcon(GOLD_ID, unit->getGold(), &index, 0, 0, false);
		}
		if (unit->getReputation() > 0){

			addIcon(REPUTATION_ID, unit->getReputation(), &index, 0, 0, false);
		}

		for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next){

			addIcon(item->itemTypeId, item->itemNum, &index, item->itemLevel, item->itemRank, (item->itemNum < 0));
		}
		this->recvactivity_draw(NULL);
	}

}
bool MB_LayerEventUnit::addIcon(int16_t typeId, int num, int *index, int level, int rank, bool isPet){

	if ((*index) > 3){

		return false;
	}
	if (isPet == false){

		MB_ItemTemplate * templete = MB_ItemMgr::getInstance()->getItemTemplateByID(typeId);
		if (templete != NULL) {

			MB_NodeItem * node = MB_NodeItem::create((uint16_t)typeId);
            node->showNameCount(false);
            node->isTopZorder = true;
			m_pIcon[(*index)]->addChild(node);
			char databuf[50];
			if (num > 0){

				sprintf(databuf, "%s*%d", templete->getItemName(), num);

			}
			else if (rank > 0) {

				sprintf(databuf, "%s +%d", templete->getItemName(), rank);

			}
			else {

				sprintf(databuf, "%s", templete->getItemName());
			}
			m_pMoney[(*index)]->setString(databuf);

			(*index)++;
		}

	}
	else {

		MB_PetTemplate *templete = MB_PetMgr::getInstance()->getPetTemplateByID(typeId);
		if (templete == NULL)
		{
			return NULL;
		}
		char dataneed[100];
		const char * databuf = MB_PetMgr::getInstance()->getPetRealName(typeId, rank);
		if (num > 0)
		{
			sprintf(dataneed, "%s*%d", databuf, num);
		}
		else
		{
			sprintf(dataneed, "%s", databuf);
		}
		m_pMoney[(*index)]->setString(dataneed);
		CC_SAFE_DELETE_ARRAY(databuf);
		MB_NodePet * node = MB_NodePet::create(typeId, level, rank);
		node->showLevel(false);
        node->showName(false);
        node->isTopZorder = true;
		m_pIcon[(*index)]->addChild(node);
		(*index)++;
	}
	return true;
}
bool  MB_LayerEventUnit::sendactivity_draw(uint16_t activityID, uint16_t drawID){

	MB_Message::sharedMB_Message()->showMessage(" ", 600);
	MB_MoneyEevntMgr::getInstance()->sendactivity_draw(activityID, drawID);
	return true;
}

// 1=> 兑换活动
// 2=> 累计充值
// 3=> 定额充值
// 4=> 充值天数
// 5=> 兑换活动2
// 6=> 消费活动

bool MB_LayerEventUnit::recvactivity_draw(MB_MsgBuffer* recvPacket){

	MB_MoneyEevntData *data = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(m_nActitvyID);
	if (data == NULL)return false;
	MB_MoneyEevntUnit *unit = data->getUnitByID(m_nUnitID);
	uint16_t actitvyid = 0;
	uint16_t unitID = 0;
	bool isget = false;
	if (recvPacket != NULL)
	{
		uint8_t result;
		recvPacket->readU8(&result);
		if (result == 1)
		{
			recvPacket->readU16(&actitvyid);
			if (actitvyid == m_nActitvyID)
			{
				recvPacket->readU16(&unitID);

				if (unitID == m_nUnitID)
				{
					if (data->getType() == 1){

						isget = true;
						MB_LayerRewardOne* layer = NULL;
						if (unit->getCoin() > 0)
						{
							layer = MB_LayerRewardOne::create(kRewardValueTypeItem, COIN_ID, unit->getCoin());
							layer->setShareType(kShareTypeChange);
						}
						if (unit->getRoleExp() > 0)
						{
							layer = MB_LayerRewardOne::create(kRewardValueTypeItem, ROLE_EXP_ID, unit->getRoleExp());
							layer->setShareType(kShareTypeChange);
						}
						if (unit->getPetExp() > 0)
						{
							layer = MB_LayerRewardOne::create(kRewardValueTypeItem, GER_EXP_ID, unit->getPetExp());
							layer->setShareType(kShareTypeChange);
						}
						if (unit->getGold() > 0)
						{
							layer = MB_LayerRewardOne::create(kRewardValueTypeItem, GOLD_ID, unit->getGold());
							layer->setShareType(kShareTypeChange);
						}
						if (unit->getReputation() > 0)
						{
							layer = MB_LayerRewardOne::create(kRewardValueTypeItem, REPUTATION_ID, unit->getReputation());
							layer->setShareType(kShareTypeChange);
						}
						for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next)
						{
							layer = MB_LayerRewardOne::create(item->itemNum < 0 ? kRewardValueTypePet : kRewardValueTypeItem, item->itemTypeId, item->itemNum < 0 ? 1 : item->itemNum);
							layer->setShareType(kShareTypeChange);
						}
						MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
						if (ptr != NULL){

							CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
						}

					}
					else if (data->getType() == 5){

						CCArray *rewardArray = CCArray::create();
						if (unit->getCoin() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(COIN_ID);
							reward->setNumber(unit->getCoin());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getRoleExp() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(ROLE_EXP_ID);
							reward->setNumber(unit->getRoleExp());
							rewardArray->addObject(reward);
							reward->release();

						}
						if (unit->getPetExp() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(GER_EXP_ID);
							reward->setNumber(unit->getPetExp());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getGold() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(GOLD_ID);
							reward->setNumber(unit->getGold());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getReputation() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(REPUTATION_ID);
							reward->setNumber(unit->getReputation());
							rewardArray->addObject(reward);
							reward->release();

						}

						for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(item->itemNum >= 0 ? kRewardValueTypeItem : kRewardValueTypePet);
							reward->setValueID(item->itemTypeId);
							reward->setNumber(item->itemNum >= 0 ? item->itemNum : 1);
							rewardArray->addObject(reward);
							reward->release();
						}

						MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
						if (ptr != NULL){

							MB_ResWindow* player = MB_LayerRewardMore::create(rewardArray);
//                            player->setShowRoleInfoPanel(false);
							ptr->pushWindow(player);
						}

					}
					else {


						CCArray *rewardArray = CCArray::create();
						if (unit->getCoin() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(COIN_ID);
							reward->setNumber(unit->getCoin());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getRoleExp() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(ROLE_EXP_ID);
							reward->setNumber(unit->getRoleExp());
							rewardArray->addObject(reward);
							reward->release();

						}
						if (unit->getPetExp() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(GER_EXP_ID);
							reward->setNumber(unit->getPetExp());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getGold() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(GOLD_ID);
							reward->setNumber(unit->getGold());
							rewardArray->addObject(reward);
							reward->release();
						}
						if (unit->getReputation() > 0){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(kRewardValueTypeItem);
							reward->setValueID(REPUTATION_ID);
							reward->setNumber(unit->getReputation());
							rewardArray->addObject(reward);
							reward->release();

						}

						for (p_item_view * item = unit->getItemList(); item != NULL; item = item->next){

							RewardTempleteValue* reward = new  RewardTempleteValue();
							reward->setType(item->itemNum >= 0 ? kRewardValueTypeItem : kRewardValueTypePet);
							reward->setValueID(item->itemTypeId);
							reward->setNumber(item->itemNum >= 0 ? item->itemNum : 1);
							rewardArray->addObject(reward);
							reward->release();
						}

						MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
						if (ptr != NULL){

							MB_ResWindow* player = MB_LayerRewardMore::create(rewardArray);
//                            player->setShowRoleInfoPanel(false);
							ptr->pushWindow(player);
						}
					}

				}
			}
		}
	}

	if (data->getType() == 7)
	{
		int candrwatimes = unit->getMaxDrawTimes() - unit->getAlreadyDrawTimes();
		if (candrwatimes <= 0)
		{
			if (m_pCollectBt)
			{
				m_pCollectBt->setEnabled(false);
			}
		}
		char databuf[128];
		if (unit->getMaxDrawTimes() >= 0)
		{
			sprintf(databuf, "%d/%d", candrwatimes, unit->getMaxDrawTimes());
		}
		else
		{
			sprintf(databuf, "无限");
		}
		m_pCancollect->setString(databuf);
	}

	if (data->getType() != 1 && data->getType() != 5 && data->getType() != 7)
	{
		if (unit->getCanDrawTimes() <= 0)
		{
			if (m_pCollectBt)
			{
				m_pCollectBt->setEnabled(false);
			}
		}
		char databuf[128];
		if (unit->getMaxDrawTimes() >= 0)
		{
			sprintf(databuf, "%d/%d", unit->getMaxDrawTimes() - unit->getAlreadyDrawTimes(), unit->getMaxDrawTimes());
		}
		else
		{
			sprintf(databuf, "无限");
		}
		m_pCancollect->setString(databuf);
	}
	else if (data->getType() == 5){


		int canGettimes = unit->getMaxDrawTimes() - unit->getAlreadyDrawTimes();
		char databuf[128];
		if (unit->getMaxDrawTimes() >= 0){

			sprintf(databuf, "%d/%d", canGettimes, unit->getMaxDrawTimes());

		}
		else {

			canGettimes = 100000;
			sprintf(databuf, "无限");
		}
		m_pCancollect->setString(databuf);

		int count = canGettimes;
		CCObject *obj;
		int index = 0;
		CCARRAY_FOREACH(unit->getReward(), obj){

			MB_EventReward *edata = (MB_EventReward *)obj;
			int num = 0;
			if (edata->getIsPet()){

				num = MB_PetMgr::getInstance()->getPetNumByType(edata->getItemType());

			}
			else {


				if (edata->getItemType() == COIN_ID){

					num = MB_RoleData::getInstance()->getCoin();

				}
				else if (edata->getItemType() == GOLD_ID){

					num = MB_RoleData::getInstance()->getGold() + MB_RoleData::getInstance()->getGoldBoune();

				}
				else if (edata->getItemType() == REPUTATION_ID){

					num = MB_RoleData::getInstance()->getReputation();

				}
				else {

					num = MB_ItemMgr::getInstance()->getItemNumForExchangeByType(edata->getItemType());
				}
			}
			int canChange = num / edata->getNum();
			if (canChange < count){

				count = canChange;
			}
			index++;
		}
		if (count <= 0)
		{
			if (m_pCollectBt)
			{
				m_pCollectBt->setEnabled(false);
			}
		}
		else
		{
			if (count > canGettimes)
			{
				count = canGettimes;
			}
		}

	}
	else if (data->getType() == 1){

		int canGettimes = unit->getMaxDrawTimes() - unit->getAlreadyDrawTimes();
		char databuf[128];
		if (unit->getMaxDrawTimes() >= 0){

			sprintf(databuf, "%d/%d", canGettimes, unit->getMaxDrawTimes());

		}
		else {

			canGettimes = 100000;
			sprintf(databuf, "无限");
		}
		m_pCancollect->setString(databuf);

		int count = canGettimes;
		CCObject *obj;
		int index = 0;
		CCARRAY_FOREACH(unit->getReward(), obj){

			MB_EventReward *edata = (MB_EventReward *)obj;
			int num = 0;
			if (edata->getIsPet()){

				num = MB_PetMgr::getInstance()->getPetNumByType(edata->getItemType());

			}
			else {


				if (edata->getItemType() == COIN_ID){

					num = MB_RoleData::getInstance()->getCoin();

				}
				else if (edata->getItemType() == GOLD_ID){

					num = MB_RoleData::getInstance()->getGold() + MB_RoleData::getInstance()->getGoldBoune();

				}
				else if (edata->getItemType() == REPUTATION_ID){

					num = MB_RoleData::getInstance()->getReputation();

				}
				else {

					num = MB_ItemMgr::getInstance()->getItemNumForExchangeByType(edata->getItemType());
				}
			}
			int canChange = num / edata->getNum();
			if (canChange < count){

				count = canChange;
			}
			index++;

		}


		if (count <= 0){

			if (m_pCollectBt){

				m_pCollectBt->setEnabled(false);
			}

		}
		else {

			if (count > canGettimes){

				count = canGettimes;
			}
			if (m_pCollectBt){

				m_pCollectBt->setEnabled(true);
			}

		}
	}


	//
	MB_Message::sharedMB_Message()->removeALLMessage();
	if (unit->getAlreadyDrawTimes() >= unit->getMaxDrawTimes() && unit->getMaxDrawTimes() >= 0)
	{
		if (m_pCollectBt)
		{
			m_pCollectBt->setEnabled(false);
		}

//        if ((data->getType() == 1 || data->getType() == 5) && recvPacket != NULL)
//        {
//            if (actitvyid == m_nActitvyID && unitID == m_nUnitID &&  isget == false)
//            {
//                MB_Message::sharedMB_Message()->showMessage("兑换次数耗尽.");
//            }
//        }
	}

	return  true;
}
void MB_LayerEventUnit::onMsgRecv(CCNode* node, SocketResponse* response){

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
	case SC_ACTIVITY_DRAW:
		recvactivity_draw(recvPacket);
		break;
	case SC_ACTIVITY_UPDATE:{
								recvactivity_draw(NULL);

	}break;
	default:

		break;
	}

}
