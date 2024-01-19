

#include "MB_SceneMain.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif


#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif

#include "MB_LayerChatMain.h"

#include "MB_LayerPetCommand.h"
#include "MB_FunctionModule.h"
#include "MB_LayerHome.h"
#include "MB_LayerCommand.h"

#include "MB_DataExchange.h"
#include "MB_FunctionMainWnd.h"
#include "MB_RoleSoundSystem.h"
#include "MB_TaskSystemInterface.h"
#include "MB_GlobelModalDlgMsgQueue.h"
#include "MB_PerfectRaceInterface.h"

MB_SceneMain::MB_SceneMain()
{
	m_pLayerRoleInfoHeader = NULL;
	m_pLayerWarningHeader = NULL;
	m_pNextMainLayer = NULL;
	m_pLayerHome = NULL;
	m_pPveCommand = NULL;
	m_pPvpCommand = NULL;
	m_pCurrentFunctionWindow = NULL;
	m_nHomeLayerType = kFunctionHome;
	m_bChangeMainLayer = false;

	m_kMainLayerStatus = kSceneMainLayerTypeMain;
	m_nSubLayerStatus = kSubLayerTypeNone;

	SOCKET_MSG_REGIST(SC_PUSH_HIGHLIGHT_INFO, MB_SceneMain);
	if (strlen(MB_ServerList::getInstance()->getInviteCode()) > 0){

		SOCKET_MSG_REGIST(SC_INVITE_INPUT_INVITE_CODE, MB_SceneMain);
	}
}

MB_SceneMain::~MB_SceneMain()
{

	CC_SAFE_RELEASE_NULL(m_pNextMainLayer);
	SOCKET_MSG_UNREGIST(SC_PUSH_HIGHLIGHT_INFO);
	SOCKET_MSG_UNREGIST(SC_INVITE_INPUT_INVITE_CODE);


}
MB_SceneMain* MB_SceneMain::create(CCScene *scene)
{
	MB_SceneMain* layer = new MB_SceneMain();
	if (layer != NULL && layer->init(scene)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}


CCScene* MB_SceneMain::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	CCNode *pScene = MB_LayerCommand::create();
	pScene->setTag(LAYER_MAIN_COMMAND);
	scene->addChild(pScene, Z_ORDER_MAINCOMMAND);
	// 'layer' is an autorelease object
	MB_SceneMain *layer = MB_SceneMain::create(scene);
	//标记
	layer->setTag(LAYER_SCENE_MAIN);
	// add layer as a child to scene
	scene->addChild(layer, Z_ORDER_SCENEMAIN);

	return scene;
}

bool MB_SceneMain::init(CCScene *scene)
{

	MB_EventMgr::getInstence();
	m_pLayerHome = MB_ResWindow::create();
	addChild(m_pLayerHome);

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    CC_SAFE_RELEASE_NULL(pCCBReader);

	m_pSubLayer = MB_ResWindow::create();
	addChild(m_pSubLayer, 99);


	//    enterLayer(kSceneMainLayerTypeMain, kSubLayerTypeNone);
	m_nHomeLayerType = kFunctionHome;
	m_pLayerHome->addChild(MB_FunctionMgr::getInstance()->getFunctionMainWndByType(kFunctionHome));

	schedule(schedule_selector(MB_SceneMain::tickOfRecovery), 1);


	MB_LayerChatMain *chat = MB_LayerChatMain::create();
	chat->setTag(LAYER_CHAT_TAG);
	scene->addChild(chat, Z_ORDER_CHAT);
	//chat->setPositionY(CCDirector::sharedDirector()->getWinSize().height/2.0-60);

	if (strlen(MB_ServerList::getInstance()->getInviteCode()) > 0){

		MB_Message::sharedMB_Message()->showMessage("", 20);
		SOCKET_REQUEST_START(CS_INVITE_INPUT_INVITE_CODE);
		packet->Write(MB_ServerList::getInstance()->getInviteCode(), strlen(MB_ServerList::getInstance()->getInviteCode()));
		SOCKET_REQUEST_END(SC_INVITE_INPUT_INVITE_CODE, MB_SceneMain::onMsgRecv);
		MB_ServerList::getInstance()->setInviteCode("");
	}

	onEnterLayerRoleInfoHeader();
	onEnterLayerWarningHeader();
	m_pLayerRoleInfoHeader->setVisible(true);

	return true;
}

void MB_SceneMain::tickOfRecovery(float dt){


	time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
	MB_MoneyEventEnergy*  pEvnet = MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
	MB_MoneyEventEnergy*  pEvnet2 = MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
	if (nowtime >= pEvnet->getStartTime() && nowtime < pEvnet->getEnTime()) {

		if (pEvnet->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy1_1") == false){
		}

	}
	else if (nowtime >= pEvnet2->getStartTime() && nowtime < pEvnet2->getEnTime()){

		if (pEvnet2->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy2_1") == false){
		}
	}
	MB_MoneySignEmperor * emper = MB_MoneyEevntMgr::getInstance()->getSignEmperor();
	if (emper != NULL)
	{
		time_t nowtimeemper = emper->getLastRequestTime();
		struct tm * timestruct1 = localtime(&nowtime);
		struct tm *timestruct2 = localtime(&nowtimeemper);
		if (timestruct1->tm_mday != timestruct2->tm_mday || timestruct1->tm_mon != timestruct2->tm_mon){

			MB_MoneyEevntMgr::getInstance()->sendactivity_sign_emperor_info();
		}

		if (timestruct1->tm_hour == 0 && timestruct1->tm_min == 0 && timestruct1->tm_sec == 0)
		{
			MB_ItemMgr::getInstance()->initUseItemLastTimes();
		}
	}


	//重置体力道具使用次数（本地读取）

}
bool MB_SceneMain::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	//引导
	if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
		return true;
	}

	return true;
}

SEL_MenuHandler MB_SceneMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMainClicked", MB_SceneMain::onMainClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPVEClicked", MB_SceneMain::onPVEClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPVPClicked", MB_SceneMain::onPVPClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRoleClicked", MB_SceneMain::onRoleClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShopClicked", MB_SceneMain::onShopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOtherClicked", MB_SceneMain::onOtherClicked);
	return NULL;
}

SEL_CCControlHandler MB_SceneMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

void MB_SceneMain::animaitionOver()
{

}

void MB_SceneMain::onMainClicked(cocos2d::CCObject *pSender)
{
	TutorialTriggerComplete

		enterLayer(kSceneMainLayerTypeMain, kSubLayerTypeNone);
}

void MB_SceneMain::onPVEClicked(cocos2d::CCObject *pSender)
{
	TutorialTriggerComplete

	if (m_pPveCommand == NULL) {

		m_pPveCommand = MB_FunctionPveMain::create();//MB_LayerPveCommand::create();
		this->addChild(m_pPveCommand, Z_ORDER_PVECOMMAND);
		m_pPveCommand->onOpen();

	}
	else {

		m_pPveCommand->onClose();
		m_pPveCommand = NULL;
	}
	if (m_pPvpCommand != NULL){

		m_pPvpCommand->onClose();
		m_pPvpCommand = NULL;
	}
}

void MB_SceneMain::onPVPClicked(cocos2d::CCObject *pSender)
{
	//    MB_LOG("pvp clicked!");
	//    if (m_kMainLayerStatus == kSceneMainLayerTypePVP) {
	//        return;
	////    }
	//    if(MB_RoleData::getInstance()->getLevel() < MB_RoleData::getInstance()->getRolePvpLimit() ){
	//    
	//        char databuf[50];
	//        
	//        sprintf(databuf, "冒险家，此功能%d级开放",
	//                MB_RoleData::getInstance()->getRolePvpLimit());
	//        
	//        MB_Message::sharedMB_Message()->showMessage(databuf);
	//        
	//        return;
	//    }
	//    
	//    enterLayer(kSceneMainLayerTypePVP, kSubLayerTypeRanking);
	if (m_pPvpCommand == NULL) {

		m_pPvpCommand = MB_FunctionPvpMain::create();//MB_LayerPvpCommand::create();
		this->addChild(m_pPvpCommand, Z_ORDER_PVECOMMAND);
		m_pPvpCommand->onOpen();

	}
	else {

		m_pPvpCommand->onClose();
		m_pPvpCommand = NULL;
	}
	if (m_pPveCommand != NULL){

		m_pPveCommand->onClose();
		m_pPveCommand = NULL;
	}
}

void MB_SceneMain::onRoleClicked(cocos2d::CCObject *pSender)
{
	TutorialTriggerComplete

		enterLayer(kSceneMainLayerTypePet, kSubLayerTypePet);
}

void MB_SceneMain::onShopClicked(cocos2d::CCObject *pSender)
{
	TutorialTriggerComplete
		enterLayer(kSceneMainLayerTypeShop, kSubLayerTypeGeneral);
}

void MB_SceneMain::onOtherClicked(cocos2d::CCObject *pSender)
{
	//    if (m_kMainLayerStatus == kSceneMainLayerTypeOther) {
	//        return;
	//    }
	enterLayer(kSceneMainLayerTypeActivity, kSceneMainLayerTypeActivity);
}

bool MB_SceneMain::onEnterLayerRoleInfoHeader()
{
	if (m_pLayerRoleInfoHeader != NULL){

		return  true;
	}

	m_pLayerRoleInfoHeader = MB_LayerRoleInfoHeader::create();
	if (m_pLayerRoleInfoHeader != NULL)
	{
		addChild(m_pLayerRoleInfoHeader, Z_ORDER_RoleInfoHeader);
		return true;
	}
	else
	{
		return false;
	}
}

bool MB_SceneMain::onExitLayerRoleInfoHeader()
{
	if (m_pLayerRoleInfoHeader != NULL) {

		removeChild(m_pLayerRoleInfoHeader, true);

		m_pLayerRoleInfoHeader = NULL;

		return true;
	}
	else
	{
		return false;
	}
}

MB_LayerRoleInfoHeader* MB_SceneMain::getLayerRoleInfoHeader()
{
	return m_pLayerRoleInfoHeader;
}

bool MB_SceneMain::onEnterLayerWarningHeader()
{
	m_pLayerWarningHeader = MB_LayerWarningHeader::create();

	if (m_pLayerWarningHeader != NULL)
	{
		addChild(m_pLayerWarningHeader, Z_ORDER_WarningHeader);
		return true;
	}
	else
	{
		return false;
	}
}

bool MB_SceneMain::onExitLayerWarningHeader()
{
	if (m_pLayerWarningHeader != NULL) {

		removeChild(m_pLayerWarningHeader);
		m_pLayerWarningHeader = NULL;
		return true;
	}
	else
	{
		return false;
	}
}

MB_LayerWarningHeader* MB_SceneMain::getLayerWarningHeader()
{
	return m_pLayerWarningHeader;
}

void MB_SceneMain::goLayerHome()
{
	replaceSubLayer(MB_ResWindow::create());
	onEnterLayerMap();
}

static void updateNode(CCNode* pNode)
{
	if (pNode == NULL || pNode->getChildrenCount() == 0)
	{
		return;
	}

	MB_ResWindow* pWnd = dynamic_cast<MB_ResWindow*>(pNode->getChildren()->objectAtIndex(0));
	if (pWnd)
	{
		pWnd->onResetWnd();
	}
}
bool MB_SceneMain::onEnterLayerMap()
{
	if (m_pLayerHome->getChildrenCount() != 0)
	{
		updateNode(m_pLayerHome);
	}
	else
	{
		MB_FunctionMgr::getInstance()->goFunction(m_nHomeLayerType, this);
	}
	return true;
}

bool MB_SceneMain::onExitLayerMap(){

	if (m_pLayerHome != NULL) {

		removeChild(m_pLayerHome);
		m_pLayerHome = NULL;
		return true;
	}
	else
	{
		return false;
	}
}


void MB_SceneMain::updateLayerStatus(int mainLayer, int subLayer)
{
	setMainLayerStatus(mainLayer);
	setSubLayerStatus(subLayer);
	updateButton();
	onCloseCommander();
}

void MB_SceneMain::enterLayer(int mainLayer, int subLayer)
{
	/*
	setMainLayerStatus(mainLayer);
	setSubLayerStatus(subLayer);
	updateButton();
	onCloseCommander();
	*/
	//    updateLayerStatus(mainLayer,subLayer);
	//    if (m_kMainLayerStatus == kSceneMainLayerTypeMain)
	//    {
	//        if (m_pSubLayer)
	//        {
	//            replaceSubLayer(MB_ResWindow::create());
	//            MB_ResWindow* pWnd = MB_FunctionMgr::getInstance()->getFunctionMainWndByType(m_nHomeLayerType);
	//            if (pWnd)
	//            {
	//                replaceMainLayer(pWnd);
	//            }
	//        }
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypePVE)
	//    {
	//
	////        MB_ResWindow* layer = MB_LayerMainCampaign::create(m_nSubLayerStatus);
	////        replaceSubLayer(layer);
	////        layer->setTag(LAYER_MAIN_CAMPAIGN_TAG);
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypePVP)
	//    {
	//        MB_ResWindow* layer = MB_LayerPVP::create(m_nSubLayerStatus);
	//        replaceSubLayer(layer);
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypePet)
	//    {
	//        MB_ResWindow* layer = MB_LayerPetCommand::create(m_nSubLayerStatus);
	//        replaceSubLayer(layer);
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypeShop)
	//    {
	//        NSGameFunction::CCFunctionInterface *pInterface = NULL;
	//        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionMysteriousShop,&pInterface))
	//        {
	//            MB_ResWindow* layer = pInterface->createFunctionDialog();
	//            m_pSubLayer->replaceLayer(layer, true);
	//        }
	//        
	//
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypeActivity)
	//    {
	//        MB_ResWindow* layer = MB_LayerAllEvent::create((kSubLayerType)m_nSubLayerStatus);
	//        replaceSubLayer(layer);
	//    }
	//    else if (m_kMainLayerStatus == kSceneMainLayerTypeOther)
	//    {
	//        MB_ResWindow* layer = MB_LayerSettingMain::create();
	//        replaceSubLayer(layer);
	//    }
	//    else
	//    {
	//        MB_LOG("enter layer failed. maintype:%d, subtype:%d", m_kMainLayerStatus, m_nSubLayerStatus);
	//    }

}
MB_ResWindow* MB_SceneMain::getFunctionWindow()
{
	if (m_pSubLayer == NULL)
	{
		m_pSubLayer = MB_ResWindow::create();
		m_pCurrentFunctionWindow = m_pSubLayer;
	}

	return m_pCurrentFunctionWindow;
}
void MB_SceneMain::replaceSubLayer(MB_ResWindow* pWnd)
{
    if (m_pSubLayer && pWnd)
    {
        m_pSubLayer->replaceLayer(pWnd, true);
        m_pCurrentFunctionWindow = pWnd;
        m_pLayerHome->removeAllChildren();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        m_pLayerRoleInfoHeader->setVisible(pWnd->getShowRoleInfoPanel());
        ((MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN))->m_pLayerRoleInfoHeader->m_pLVNameExp->setVisible(pWnd->getShowEXP());
        ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(pWnd->getShowHomeButtonPanel());
        PlayRoleSoundByNode(pWnd);
	}
}
void MB_SceneMain::changeMainLayer(CCObject* pSender)
{
	if (m_pNextMainLayer == NULL)
	{
		return;
	}
	m_pLayerHome->removeAllChildren();
	m_pLayerRoleInfoHeader->setVisible(m_pNextMainLayer->getShowRoleInfoPanel());
    ((MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN))->m_pLayerRoleInfoHeader->m_pLVNameExp->setVisible(m_pNextMainLayer->getShowEXP());
	m_pLayerHome->addChild(m_pNextMainLayer);
	{
		m_nHomeLayerType = kFunctionHome;
	}
	CC_SAFE_RELEASE_NULL(m_pNextMainLayer);
}
void MB_SceneMain::replaceMainLayer(MB_ResWindow* pWnd)
{
	if (pWnd)
	{
		replaceSubLayer(MB_ResWindow::create());
		m_pLayerHome->removeAllChildren();
		m_pLayerRoleInfoHeader->setVisible(pWnd->getShowRoleInfoPanel());
        ((MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN))->m_pLayerRoleInfoHeader->m_pLVNameExp->setVisible(pWnd->getShowEXP());
        ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(pWnd->getShowHomeButtonPanel());
		m_pLayerHome->addChild(pWnd);
        
		m_nHomeLayerType = kFunctionHome;
        
	}
}

void MB_SceneMain::onCloseCommander(){

	if (m_pPveCommand != NULL){

		m_pPveCommand->onClose();
		m_pPveCommand = NULL;
	}
	if (m_pPvpCommand != NULL){

		m_pPvpCommand->onClose();
		m_pPvpCommand = NULL;
	}
}
void MB_SceneMain::updateButton()
{

}
void MB_SceneMain::onExit(){
	MB_ResWindow::onExit();
}
void MB_SceneMain::onEnter(){


#ifdef YJ_IOS
	if(MB_YJMgr_IOS::getInstance()->IsCheckSetRoleData){
		MB_YJMgr_IOS::getInstance()->creatRole();
		MB_YJMgr_IOS::getInstance()->IsCheckSetRoleData = false;
	}
#endif

#ifdef PLATFORM_YJ

	if(MB_RoleData::getInstance()->IsCheckSetRoleData){
		MB_YJMgr::getInstance()->creatRole();
		MB_RoleData::getInstance()->IsCheckSetRoleData = false;
	}
#endif

	MB_ResWindow::onEnter();



	MB_TaskSystemInterface* pTask = MB_FunctionMgr::getInstance()->queryFunctionByType<MB_TaskSystemInterface>(kFunctionTask);
	if (pTask)
	{
		pTask->playAchievementMsg();
	}


	kSceneTipLayerType type = MB_RoleData::getInstance()->getWillShowLayer();

	if (type != kSceneTipLayerTypeNone)
	{

		NSGameFunction::CCFunctionInterface* pInterface = NULL;
		MB_RoleData::getInstance()->setWillShowLayer(kSceneTipLayerTypeNone);

		if (type == kSceneTipLayerTypePet)
		{
			//            MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionMysteriousShop, &pInterface);
			//            if (pInterface)
			//            {
			//                pInterface->onEntryClicked(NULL);
			//            }
			//this->enterLayer(kSceneMainLayerTypeShop,kSubLayerTypeBox);

		}
		else if (type == kSceneTipLayerTypeItem)
		{
			//            MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionMysteriousShop, &pInterface);
			//            if (pInterface)
			//            {
			//                pInterface->onEntryClicked(NULL);
			//            }
			//this->enterLayer(kSceneMainLayerTypeActivity, kSubLayerTypeNone);

		}
		else if (type == kSceneTipLayerTypePetEntrance)
		{
			MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPetPackage, &pInterface);
			if (pInterface)
			{
				pInterface->onEntryClicked(NULL);
			}
		}
		else if (type == kSceneTipLayerTypePetUp)
		{
			MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionFormation, &pInterface);
			if (pInterface)
			{
				pInterface->onEntryClicked(this);
			}

		}
		else if (type == kSceneTipLayerTypeAdventure)
		{

			MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionRoom, &pInterface);
			if (pInterface)
			{
				pInterface->onEntryClicked(NULL);
			}
		}
		else if (type == kSceneTipLayerTypeItemEntrance)
		{
			//            MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionEquipStore, &pInterface);
			//            if (pInterface)
			//            {
			//                pInterface->onEntryClicked(NULL);
			//            }

		}
		else if (type == kSceneTipLayerTypeHome)
		{
			MB_ResWindow* pWnd = MB_FunctionMgr::getInstance()->getFunctionMainWndByType(m_nHomeLayerType);
			if (pWnd)
			{
				//NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(MB_ResWindow::create());
				NSGameFunction::CCFunctionInterface::replaceMainSceneLayer(pWnd);
				NSGameFunction::CCFunctionInterface::removeUnusedResource();
			}

		}
		else if (type == kSceneTipLayerTypeShopToy)
		{
			MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionToy, &pInterface);
			if (pInterface)
			{
				pInterface->onEntryClicked(NULL);
			}
		}
		else if (type == kSceneTipLayerTypeBackpack)
		{
			MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionBackpack, &pInterface);
			if (pInterface)
			{
				pInterface->onEntryClicked(NULL);
			}
		}


	}
}
void MB_SceneMain::onMsgRecv(CCNode* node, SocketResponse* response){

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
	case SC_PUSH_HIGHLIGHT_INFO:
		//            m_pNodeBossEffect->setVisible((MB_EventMgr::getInstence()->getIsRocketTeamOnLine() && MB_RoleData::getInstance()->getLevel() >= MB_RoleData::getInstance()->getRoleRocketTeamLimit() )|| (MB_EventMgr::getInstence()->getIsNanMOnLine() && MB_RoleData::getInstance()->getLevel() >= MB_RoleData::getInstance()->getRoleNanMLimit()));
		break;
	case SC_INVITE_INPUT_INVITE_CODE:{

										 MB_Message::sharedMB_Message()->removeALLMessage();
										 uint8_t data8;
										 recvPacket->readU8(&data8);

										 if (data8 == 1){

											 MB_Message::sharedMB_Message()->showMessage("邀请码验证成功");
											 MB_RoleData::getInstance()->setisInputInviteCode(true);
											 char *str = recvPacket->ReadString();
											 MB_RoleData::getInstance()->setWhoInviteYou(str ? str : "");
											 CC_SAFE_FREE(str);


										 }
										 else {

											 MB_Message::sharedMB_Message()->showMessage("好友邀请码不正确. 您可以在设置的邀请有礼中重新输入！");

										 }

	}
		break;
	default:
		break;
	}
}

