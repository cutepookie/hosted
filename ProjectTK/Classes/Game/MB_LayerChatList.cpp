
#include "MB_LayerChatList.h"
#include "MB_NodeChatInformation.h"
#include "MB_LayerChatMain.h"
#include "MB_DataExchange.h"
#include "MB_FunctionModule.h"
#include "MB_LayerFriend.h"
#include "MB_ChatData.h"
#include "MB_LayerEqCompare.h"
#include "MB_LayerCommand.h"
#include "MB_DirtyWordsCheck.h"
#include "MB_ScrollBg.h"
MB_LayerChatList::MB_LayerChatList()
{
	m_pNodeChat = NULL;
	m_pNodeEdit = NULL;
	m_pNodeFeedBack = NULL;
	m_pEditChat = NULL;
	m_pMenuItem = NULL;
	m_pSendButton = NULL;
	m_pTargetName = NULL;
	SOCKET_MSG_REGIST(SC_TALK_WORLD_MESSAGE, MB_LayerChatList);
	SOCKET_MSG_REGIST(SC_TALK_WORLD, MB_LayerChatList);
	SOCKET_MSG_REGIST(SC_TALK_PERSON, MB_LayerChatList);
	m_nChannelType = kChannelWorld;

	m_pScrollView = NULL;
	m_pChatNodes = new CCArray;
	m_pPrivateNode = NULL;
	m_pNodeNewPersonMsg = NULL;
	m_pNodeNewWorldMsg = NULL;
	m_pPrivateBtn = NULL;
	m_pWorldBtn = NULL;
	MB_LayerRoleInfoHeader::setMenuEnable(false, "MB_LayerChatList");
}

uint32_t MB_LayerChatList::m_nPrivateChatRoleID = 0;
std::string MB_LayerChatList::m_strPrivateChatRoleName = "";

MB_LayerChatList::~MB_LayerChatList(){
    MB_LayerRoleInfoHeader::setMenuEnable(true, "MB_LayerChatList");
    MB_LayerChatMain::SetChatMainVisible(!isFriendOpen, "MB_LayerChatList");

	CC_SAFE_RELEASE(m_pNodeChat);
	CC_SAFE_RELEASE(m_pNodeEdit);
	CC_SAFE_RELEASE(m_pMenuItem);
	CC_SAFE_RELEASE_NULL(m_pNodeFeedBack);
	CC_SAFE_RELEASE_NULL(m_pSendButton);
	SOCKET_MSG_UNREGIST(SC_TALK_WORLD_MESSAGE);
	SOCKET_MSG_UNREGIST(SC_TALK_WORLD);
	SOCKET_MSG_UNREGIST(SC_TALK_PERSON);

	m_pChatNodes->removeAllObjects();
	CC_SAFE_RELEASE_NULL(m_pChatNodes);
	CC_SAFE_RELEASE_NULL(m_pPrivateNode);
	CC_SAFE_RELEASE_NULL(m_pTargetName);
	CC_SAFE_RELEASE_NULL(m_pNodeNewWorldMsg);
	CC_SAFE_RELEASE_NULL(m_pNodeNewPersonMsg);
	CC_SAFE_RELEASE_NULL(m_pPrivateBtn);
	CC_SAFE_RELEASE_NULL(m_pWorldBtn);
}
MB_LayerChatList  * MB_LayerChatList::create(){

	MB_LayerChatList *ptr = new MB_LayerChatList();
	if (ptr && ptr->init()){

		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}

bool MB_LayerChatList::init(){

	MB_ResWindow::init();

	this->addChild(NSGameHelper::createDisableTouchLayer());

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode* m_pNode = pCCBReader->readNodeGraphFromFile("res/chat_layer.ccbi", this);
	pCCBReader->release();
	this->addChild(m_pNode);

	m_pWorldBtn->setIsScale(false);
	m_pPrivateBtn->setIsScale(false);
	NSGameHelper::adjustScrollNode(m_pNodeChat);

	m_pScrollView = CCScrollView::create(m_pNodeChat->getContentSize());
	m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
	m_pScrollView->setAnchorPoint(CCPointZero);
	m_pNodeChat->addChild(m_pScrollView);


	if (m_nPrivateChatRoleID != 0 && m_strPrivateChatRoleName != "")
	{
		m_pTargetName->setString(m_strPrivateChatRoleName.c_str());
	}
	else
	{
		m_pTargetName->setString("");
	}

	m_pNodeNewWorldMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPublicMsg);
	m_pNodeNewPersonMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPrivateMsg);


	onResetWnd();
    addChild(MB_ScrollBg::create(left_bottom,.5f,0),-1);
	return  true;
}



void MB_LayerChatList::onEnter()
{
	MB_ResWindow::onEnter();

	MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerChatList");
}
void MB_LayerChatList::onExit()
{
	MB_ResWindow::onExit();
	MB_LayerChatMain::SetChatMainVisible(true, "MB_LayerChatList");
}

MB_NodeChatInformation* MB_LayerChatList::queryItemByData(MB_ChatData* data)
{
	MB_NodeChatInformation* pTemp = NULL;
	CCARRAY_FOREACH_4TYPE(m_pChatNodes, MB_NodeChatInformation*, pTemp)
	{
		if (pTemp && pTemp->getChatData() == data)
		{
			return pTemp;
		}
	}

	MB_NodeChatInformation* pNode = MB_NodeChatInformation::create(data);
	m_pChatNodes->addObject(pNode);

	return pNode;
}

void MB_LayerChatList::sendpet_view_other_dtl(uint32_t roleid, uint16_t serverid)
{
	SOCKET_MSG_REGIST(SC_GER_VIEW_OTHER_DTL, MB_LayerChatList);
	MB_TeamData::getInstance()->sendpet_view_other_dtl(roleid, serverid);
}

void MB_LayerChatList::removeNodeNotUsed()
{
	MB_NodeChatInformation* pTemp = NULL;
	for (int i = m_pChatNodes->count() - 1; i >= 0; --i)
	{
		pTemp = dynamic_cast<MB_NodeChatInformation*>(m_pChatNodes->objectAtIndex(i));
		if (pTemp && pTemp->getChatData()->getChannelType() == m_nChannelType && pTemp->getParent() == NULL)
		{
			m_pChatNodes->removeObjectAtIndex(i);
		}
	}
}

#define CHAT_GAP 5
void MB_LayerChatList::resetChatNodes()
{
	float offsety = m_pScrollView->getContentOffset().y;
	float nLastHeight = m_pScrollView->getContentSize().height;

	m_pScrollView->getContainer()->removeAllChildren();

	float fy = 100.0f;
	float fLastMsgHeight = 0.0f;
	time_t lastTime = MB_ClientSocket::getInstance()->getServerTime();

	MB_NodeChatTime* pTimeNode = NULL;


	MB_ChatData* pTemp = NULL;
	CCArray* pArray = getCurrentChatList();
	if (pArray == NULL)return;

	for (int i = pArray->count() - 1; i >= 0; --i)
	{
		pTemp = dynamic_cast<MB_ChatData*>(pArray->objectAtIndex(i));
		if (pTemp)
		{
			MB_NodeChatInformation* pNode = queryItemByData(pTemp);
			m_pScrollView->getContainer()->addChild(pNode);
			pNode->setPosition(pNode->getNodeSize().width / 2, fy + pNode->getNodeSize().height + CHAT_GAP);
			fy += pNode->getNodeSize().height + CHAT_GAP;

			time_t dic = lastTime - pTemp->getTime();
			if (dic >= 60 * 3)
			{
				pTimeNode = MB_NodeChatTime::create(pTemp->getTime());
				m_pScrollView->getContainer()->addChild(pTimeNode);
				pTimeNode->setPosition(pTimeNode->getNodeSize().width / 2, fy + pTimeNode->getNodeSize().height);
				fy += pTimeNode->getNodeSize().height;
			}
			lastTime = pTemp->getTime();
			if (fLastMsgHeight == 0.0f)fLastMsgHeight = pNode->getNodeSize().height + CHAT_GAP;
		}
	}

	removeNodeNotUsed();



	m_pScrollView->getContainer()->setContentSize(CCSize(m_pScrollView->getViewSize().width, fy));
	if (fy < m_pScrollView->getViewSize().height)
	{
		m_pScrollView->setContentOffset(ccp(0, m_pScrollView->getViewSize().height - fy));
	}
	else
	{
		if (offsety == 0)
			m_pScrollView->setContentOffset(ccp(0, 0));
		else
			m_pScrollView->setContentOffset(ccp(0, offsety - fLastMsgHeight));
	}
}

void MB_LayerChatList::onResetWnd()
{
	MB_ResWindow::onResetWnd();

	m_pEditChat->setTouchEnabled(true);
	if (!MB_FunctionConfigure::getInstance()->getIsRoleOutOfRestrict(kActivatyChat) && m_nChannelType == kChannelWorld)
	{
		m_pEditChat->setTouchEnabled(false);
	}

	m_pPrivateBtn->setEnabled(m_nChannelType != kChannelPrivate);
	m_pWorldBtn->setEnabled(m_nChannelType == kChannelPrivate);

	CCSize size = m_pNodeChat->getContentSize();
	if (m_nChannelType == kChannelPrivate)
	{
		size.height = m_pNodeChat->getContentSize().height - 70;
		m_pScrollView->setPositionY(70);
	}
	else
	{
		m_pScrollView->setPositionY(0);
	}
	m_pScrollView->setViewSize(size);

	m_pPrivateNode->setVisible(kChannelPrivate == m_nChannelType);
	resetChatNodes();
	resetStatus();
}

cocos2d::SEL_MenuHandler MB_LayerChatList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSendTouch", MB_LayerChatList::onSendTouch);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerChatList::onBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChannelWorldClicked", MB_LayerChatList::onChannelWorldClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChannelPrivateClicked", MB_LayerChatList::onChannelPrivateClicked);
	return NULL;
}

void MB_LayerChatList::onChannelWorldClicked(CCObject *)
{
	MB_ChatDataMgr::getInstance()->m_bNewPublicMsg = false;
	m_pNodeNewWorldMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPublicMsg);

	m_nChannelType = kChannelWorld;
	onResetWnd();
}

void MB_LayerChatList::onChannelPrivateClicked(CCObject *)
{
	MB_ChatDataMgr::getInstance()->m_bNewPrivateMsg = false;
	m_pNodeNewPersonMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPrivateMsg);

	m_nChannelType = kChannelPrivate;
	onResetWnd();
}

cocos2d::extension::SEL_CCControlHandler MB_LayerChatList::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerChatList::onCommitClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGogClicked", MB_LayerChatList::onGogClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFriendClicked", MB_LayerChatList::onFriendClicked);
	return NULL;
}


bool MB_LayerChatList::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChat", CCNode *, m_pNodeChat);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuItem", CCMenuItemImage *, m_pMenuItem);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "SendButton", CCControlButton *, m_pSendButton);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_feedback", CCNode*, m_pNodeFeedBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPrivateNode", CCNode*, m_pPrivateNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTargetName", CCLabelTTF*, m_pTargetName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNewPersonMsg", CCNode*, m_pNodeNewPersonMsg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNewWorldMsg", CCNode*, m_pNodeNewWorldMsg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPrivateBtn", CCMenuItemImage*, m_pPrivateBtn);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pWorldBtn", CCMenuItemImage*, m_pWorldBtn);
	if (0 == strcmp(pMemberVariableName, "m_pNodeEdit"))
	{
		initEdit((CCEditBox*)pNode);
	}
	return false;
}
void MB_LayerChatList::initEdit(CCEditBox *pEdit){

	m_pEditChat = pEdit;
	m_pEditChat->setFontColor(ccWHITE);
    m_pEditChat->setFont("", 20);
	m_pEditChat->setInputMode(kEditBoxInputModeAny);
	m_pEditChat->setDelegate(this);

}
void MB_LayerChatList::onBackClicked(CCObject *){

	this->removeFromParentAndCleanup(true);
}
void  MB_LayerChatList::editBoxEditingDidBegin(CCEditBox* editBox){


}
void MB_LayerChatList::onCommitClicked(CCObject *){

	std::string strdata = m_pEditChat->getText();
	if (!NSGameHelper::safeContentChect(strdata))
	{
		MB_Message::sharedMB_Message()->showMessage("内容包含限制字符");
		return;
	}


	MB_DirtyWordsCheck::getInstance()->replaceDirtys(&strdata);

	if (strdata.length() == 0){

		MB_Message::sharedMB_Message()->showMessage("不能发送空信息哦！");

		return;

	}
	else {

		if (m_nChannelType == kChannelPrivate)
		{
			if (m_strPrivateChatRoleName.length() == 0)
			{
				MB_Message::sharedMB_Message()->showMessage("请选择私聊好友");
				return;
			}
			m_pString = strdata;
			MB_ChatDataMgr::getInstance()->sendtalk_person(m_nPrivateChatRoleID, strdata.c_str());
		}
		else if (m_nChannelType == kChannelWorld)
		{
			m_pString = strdata;
			MB_ChatDataMgr::getInstance()->sendtalk_world(m_nChannelType, strdata.c_str());
		}
	}
}
void MB_LayerChatList::editBoxTextChanged(CCEditBox* editBox, const std::string& text) {

}
void MB_LayerChatList::editBoxReturn(CCEditBox* editBox){

}
void MB_LayerChatList::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
	MB_LOG("editBox %p DidEnd !", editBox);
	std::string str = editBox->getText();
	int pos;
	do {
		pos = str.find("\xe2\x80\x86");
		if (pos != std::string::npos) {
			str.replace(pos, 3, "");
		}
		else
		{
			break;
		}
	} while (1);

	MB_DirtyWordsCheck::getInstance()->replaceDirtys(&str);

	editBox->setText(str.c_str());
}
void MB_LayerChatList::resetStatus()
{
	if (MB_ChatDataMgr::getInstance()->talkCDFinished())
	{
		enableTalk();
	}
	else
	{
		this->schedule(schedule_selector(MB_LayerChatList::updateStatus), 1.0);
	}
}
void MB_LayerChatList::enableTalk()
{
	m_pSendButton->setEnabled(true);
	//    NSGameHelper::setControlButtonTitleAllState(m_pSendButton, "发送");
}

void MB_LayerChatList::updateStatus(float dt)
{
	if (MB_ChatDataMgr::getInstance()->talkCDFinished())
	{
		enableTalk();
		this->unschedule(schedule_selector(MB_LayerChatList::updateStatus));
	}
	else
	{
		int left = MB_ChatDataMgr::getInstance()->getLeftCDTime();
		if (left < 0)
		{
			enableTalk();
			this->unschedule(schedule_selector(MB_LayerChatList::updateStatus));
			return;
		}
		//        char buff[24] = {};
		//        sprintf(buff, "发送%dS",left);
		m_pSendButton->setEnabled(false);
		//        NSGameHelper::setControlButtonTitleAllState(m_pSendButton, buff);
	}
}
CCArray* MB_LayerChatList::getCurrentChatList()
{
	return MB_ChatDataMgr::getInstance()->getChatListByType(m_nChannelType);
}
void  MB_LayerChatList::onMsgRecv(CCNode* node, SocketResponse* response)
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
	case SC_TALK_WORLD_MESSAGE:
	{
								  uint8_t type = 0;
								  recvPacket->readU8(&type);
								  resetChatNodes();

								  m_pNodeNewWorldMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPublicMsg);
								  m_pNodeNewPersonMsg->setVisible(MB_ChatDataMgr::getInstance()->m_bNewPrivateMsg);
	}
		break;
	case SC_TALK_WORLD:
	{
						  uint8_t result;
						  recvPacket->readU8(&result);
						  if (result == 1)
						  {
							  recvPacket->readU8(&result);
							  m_pEditChat->setText("");
							  MB_ChatData *data = new MB_ChatData();
							  data->setChannelType(kChannelWorld);
							  data->setRoleName(MB_RoleData::getInstance()->getName());
							  data->setLocation(NSDataExchange::g_LocationName);
							  data->setMessage(m_pString.c_str());
							  data->setTitle(MB_RoleData::getInstance()->getTitle());
							  data->setTime(MB_ClientSocket::getInstance()->getServerTime());
							  data->setRoleID(MB_RoleData::getInstance()->getUID());
							  data->setIsMale(MB_RoleData::getInstance()->getSex());
							  data->setHead(MB_RoleData::getInstance()->getHead());
							  data->setTargetUID(0);
							  MB_ChatDataMgr::getInstance()->insertMessage(kChannelWorld, data);
							  data->release();
							  if (m_nChannelType == kChannelWorld)
							  {
								  resetChatNodes();
								  resetStatus();
							  }
						  }
	};
		break;
	case SC_TALK_PERSON:
	{
						   uint8_t result;
						   recvPacket->readU8(&result);
						   switch (result) {
						   case 1:
						   {
									 recvPacket->readU8(&result);
									 m_pEditChat->setText("");
									 MB_ChatData *data = new MB_ChatData();
									 data->setChannelType(kChannelPrivate);
									 data->setRoleName(MB_RoleData::getInstance()->getName());
									 data->setLocation(NSDataExchange::g_LocationName);
									 data->setMessage(m_pString.c_str());
									 data->setTitle(MB_RoleData::getInstance()->getTitle());
									 data->setTime(MB_ClientSocket::getInstance()->getServerTime());
									 data->setRoleID(MB_RoleData::getInstance()->getUID());
									 data->setIsMale(MB_RoleData::getInstance()->getSex());
									 data->setHead(MB_RoleData::getInstance()->getHead());
									 data->setTargetUID(MB_LayerChatList::m_nPrivateChatRoleID);
									 data->setRoleTarget(MB_LayerChatList::m_strPrivateChatRoleName);
									 MB_ChatDataMgr::getInstance()->insertMessage(kChannelPrivate, data);
									 data->release();
									 if (m_nChannelType == kChannelPrivate)
									 {
										 resetChatNodes();
										 resetStatus();
									 }
									 MB_ChatDataMgr::getInstance()->savePrivateChat2File();

						   }
							   break;
						   case 2:
							   MB_Message::sharedMB_Message()->showMessage("说话太快");
							   break;
						   case 3:
							   MB_Message::sharedMB_Message()->showMessage("说话内容太长");
							   break;
						   case 4:
							   MB_Message::sharedMB_Message()->showMessage("不是好友");
							   break;
						   default:
							   break;
						   }
	}
		break;
	case SC_GER_VIEW_OTHER_DTL:
		onPetTeamDataDtl(recvPacket);
		SOCKET_MSG_UNREGIST(SC_GER_VIEW_OTHER_DTL);
		break;
	default:
		break;
	}
}


void MB_LayerChatList::onPetTeamDataDtl(MB_MsgBuffer* recvPacket)
{
	uint16_t data16;
	uint32_t data32;
	uint64_t data64;
	uint8_t data8;
	char *str;
	std::string fullname;
	recvPacket->readU32(&data32);//冒险家id
	str = recvPacket->ReadString();//冒险家名字
	if (str != NULL)fullname = str;
	CC_SAFE_FREE(str);

	recvPacket->readU16(&data16);//等级
	recvPacket->readU64(&data64);//战斗力
	TeamDataStruct *temaData[6];
	for (int i = 0; i < CARD_IN_GAME; i++) {

		temaData[i] = new TeamDataStruct;
		temaData[i]->m_pPet = NULL;
		temaData[i]->m_pEquip1 = NULL;
		temaData[i]->m_pEquip2 = NULL;
		temaData[i]->m_pEquip3 = NULL;
		temaData[i]->m_pTreasure1 = NULL;
		temaData[i]->m_pTreasure2 = NULL;
		temaData[i]->m_pTreasure3 = NULL;
		temaData[i]->m_pTreasure4 = NULL;
		temaData[i]->m_pTreasure5 = NULL;
		temaData[i]->m_pTreasure6 = NULL;
		temaData[i]->m_pTreasure7 = NULL;
		temaData[i]->m_pTreasure8 = NULL;

	}
	uint16_t petList;
	recvPacket->readU16(&petList);
	for (int i = 0; i < petList; i++) {

		MB_PetData * data = new MB_PetData();
		recvPacket->readU64(&data64);
		data->setPetID(data64);
		recvPacket->readU16(&data16);
		data->setPetTypeID(data16);
		recvPacket->readU16(&data16);
		data->setPetQuallity(data16);
		recvPacket->readU16(&data16);
		data->setPetLevel(data16);
		recvPacket->readU32(&data32);
		data->setPetAttack(data32);
		recvPacket->readU32(&data32);
		data->setPetHpMax(data32);
		recvPacket->readU64(&data64);
		data->setPetFightPower(data64);
		recvPacket->readU64(&data64);
		data->setPetExp(data64);
		temaData[i]->m_pPet = data;
		CCLog("pet pos %d", i);

	}
	uint16_t eqList;
	recvPacket->readU16(&eqList);
	for (int i = 0; i < eqList; i++) {

		MB_ItemData *data = new MB_ItemData();
		recvPacket->readU64(&data64);
		data->setItemPetID(data64);
		recvPacket->readU16(&data16);
		data->setItemID(data16);
		recvPacket->readU8(&data8);
		data->setItemLevel(data8);
		recvPacket->readU8(&data8);
		data->setItemRank(data8);
		recvPacket->readU64(&data64);
		data->setItemPetID(data64);
		recvPacket->readU8(&data8);
		data->setItemPos(data8);
		recvPacket->readU32(&data32);
		data->setItemRankOverTim(data32);
		recvPacket->readU16(&data16);
		data->setExp(data16);
		for (int i = 0; i < CARD_IN_GAME; i++) {

			if (temaData[i]->m_pPet != NULL && temaData[i]->m_pPet->getPetID() == data->getItemPetID()){

				if (data->getItemPos() == kItemPosEquip1){

					temaData[i]->m_pEquip1 = data;

				}
				else if (data->getItemPos() == kItemPosEquip2){

					temaData[i]->m_pEquip2 = data;

				}
				else if (data->getItemPos() == kItemPosEquip3){

					temaData[i]->m_pEquip3 = data;
				}
				if (data->getItemPos() == kItemPosTreasure1){

					temaData[i]->m_pTreasure1 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure2){

					temaData[i]->m_pTreasure2 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure3){

					temaData[i]->m_pTreasure3 = data;
				}
				if (data->getItemPos() == kItemPosTreasure4){

					temaData[i]->m_pTreasure4 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure5){

					temaData[i]->m_pTreasure5 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure6){

					temaData[i]->m_pTreasure7 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure7){

					temaData[i]->m_pTreasure7 = data;

				}
				else if (data->getItemPos() == kItemPosTreasure8){

					temaData[i]->m_pTreasure8 = data;
				}
			}
		}
	}
	uint16_t posList;
	recvPacket->readU16(&posList);

	for (int i = 0; i < posList; i++) {

		uint64_t petid;
		recvPacket->readU64(&petid);
		uint8_t pos;
		recvPacket->readU8(&pos);
		pos--;
		for (int j = 0; j < CARD_IN_GAME; j++) {

			if (temaData[j]->m_pPet && temaData[j]->m_pPet->getPetID() == petid){

				if (j != pos){

					TeamDataStruct * temp = temaData[j];
					temaData[j] = temaData[pos];
					temaData[pos] = temp;
					break;

				}

			}
		}
	}
	int index = 0;
	uint16_t atkadd;
	uint16_t hpadd;
	recvPacket->readU16(&atkadd);
	recvPacket->readU16(&hpadd);
	CCArray *array = CCArray::create();
	uint16_t list;
	recvPacket->readU16(&list);
	for (int i = 0; i < list; i++)
	{
		recvPacket->skipU16();
		//        Lieu_ViewData * lvdata = new Lieu_ViewData();
		//        array->addObject(lvdata);
		//        lvdata->release();
		//        
		//        recvPacket->readU16(&data16);
		//        lvdata->setPetType(data16);

	}
	MB_LayerEqCompare *layer = MB_LayerEqCompare::create(temaData, array, index, fullname.c_str(), atkadd, hpadd);
	for (int i = 0; i < CARD_IN_GAME; i++) {

		delete temaData[i];
	}
	CC_SAFE_DELETE_ARRAY(str);
	addChild(layer);
}

void MB_LayerChatList::personChat(int32_t roleid, const char* name, bool updata)
{
	if (updata)onChannelPrivateClicked(NULL);
	m_pTargetName->setString(name);
	m_nPrivateChatRoleID = roleid;
	m_strPrivateChatRoleName = name;
}
void MB_LayerChatList::onSendTouch(CCObject *){

	MB_ActivatyRestrict* pItem = MB_FunctionConfigure::getInstance()->queryActivatRestrictItemByType(kActivatyChat);
	if (m_nChannelType == kChannelWorld && pItem && !pItem->isActivated())
	{
		char databuf[100];
		int vipLevel = pItem->getRestrictVipLevel();
			sprintf(databuf, "VIP%d级才可以使用聊天功能", vipLevel);

		MB_Message::sharedMB_Message()->showMessage(databuf);
		return;
	}

}
void MB_LayerChatList::onFriendClicked(CCObject *)
{
	MB_LayerFriend* layer = MB_LayerFriend::create(true);
	if (layer)
	{
		CCFunctionInterface::replaceMainSceneSubLayer(layer);
        isFriendOpen = true;
	}
	onBackClicked(NULL);
}
void MB_LayerChatList::goCharge(CCObject *){

	MB_RoleData::getInstance()->goCharge(3);
	this->removeFromParentAndCleanup(true);
}

void MB_LayerChatList::onGogClicked(CCObject *){

	//    MB_LayerGagList *layer = MB_LayerGagList::create();
	//    this->pushWindow(layer);
}
