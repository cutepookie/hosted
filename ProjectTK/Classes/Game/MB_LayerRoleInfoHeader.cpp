

#include "Game.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_LayerRoleDetail.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LayerRoleInfoHeader::MB_LayerRoleInfoHeader()
{
	m_pMenu = NULL;
	m_pSpriteExp = NULL;
	m_pRoleEnergy = NULL;
    m_pRoleEnergy2=NULL;
	m_pRoleLevel = NULL;
	m_pRoleName = NULL;
	m_pRoleCoin = NULL;
	m_pRoleGold = NULL;
	m_pRoleReputatiton = NULL;
	m_pRoleLevel = NULL;
	m_pNodeSize = NULL;
    m_pRoleExp = NULL;
    m_pLVNameExp = NULL;
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_ENERGY, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_COIN, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_GOLD, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_GOLDBONUS, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_EXP, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_REPUTATION, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_ROLE_BASE_CONFIG, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(SC_GER_REFRESH_POWER, MB_LayerRoleInfoHeader);
	SOCKET_MSG_REGIST(RECV_ROLE_CHANGE_NAME, MB_LayerRoleInfoHeader);
}

MB_LayerRoleInfoHeader::~MB_LayerRoleInfoHeader()
{
	unscheduleAllSelectors();
	CC_SAFE_RELEASE_NULL(m_pMenu);
	CC_SAFE_RELEASE_NULL(m_pSpriteExp);
	CC_SAFE_RELEASE_NULL(m_pRoleEnergy);
    CC_SAFE_RELEASE_NULL(m_pRoleEnergy2);
    CC_SAFE_RELEASE_NULL(m_pRoleExp);
    CC_SAFE_RELEASE_NULL(m_pLVNameExp);
    
	CC_SAFE_RELEASE_NULL(m_pRoleLevel);
	CC_SAFE_RELEASE_NULL(m_pRoleName);
	CC_SAFE_RELEASE_NULL(m_pRoleCoin);
	CC_SAFE_RELEASE_NULL(m_pRoleGold);
	CC_SAFE_RELEASE_NULL(m_pRoleReputatiton);
	CC_SAFE_RELEASE_NULL(m_pNodeSize);
	SOCKET_MSG_UNREGIST(RECV_ROLE_CHANGE_NAME);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_ENERGY);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_COIN);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_GOLD);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_GOLDBONUS);
	SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_EXP);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_REPUTATION);
	SOCKET_MSG_UNREGIST(SC_ROLE_BASE_CONFIG);
	SOCKET_MSG_UNREGIST(SC_GER_REFRESH_POWER);
}

bool static enableMenu(std::map<std::string, bool>& m)
{
	std::map<std::string, bool>::iterator it = m.begin();
	for (; it != m.end(); ++it)
	{
		if (!it->second)
		{
			return false;
		}
	}
	return true;
}


static std::map<std::string, bool> m_MapMenuEnable;

void MB_LayerRoleInfoHeader::setMenuEnable(bool b, const char* key)
{
	m_MapMenuEnable[key] = b;

	MB_SceneMain* pLayerMain = dynamic_cast<MB_SceneMain*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN));
	if (pLayerMain && pLayerMain->getLayerRoleInfoHeader())
	{
		pLayerMain->getLayerRoleInfoHeader()->m_pMenu->setEnabled(enableMenu(m_MapMenuEnable));
	}
}



bool MB_LayerRoleInfoHeader::showRoleInfoHeader(bool b)
{
	bool bOld = false;
	MB_SceneMain* pLayerMain = dynamic_cast<MB_SceneMain*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN));
	if (pLayerMain)
	{
		bOld = pLayerMain->getLayerRoleInfoHeader()->isVisible();
		pLayerMain->getLayerRoleInfoHeader()->setVisible(b);
	}
	return bOld;
}

//void MB_LayerRoleInfoHeader::setMenuEnable(bool b)
//{
//    if(m_pMenu)m_pMenu->setEnabled(b);
//}
CCNode *pScene;
// on "init" you need to initialize your instance
bool MB_LayerRoleInfoHeader::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	//init CCBReader
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	pScene = pCCBReader->readNodeGraphFromFile("res/role_layer_headnotice.ccbi", this);
	this->addChild(pScene);

	//確定用不到了就要释放
	CC_SAFE_RELEASE_NULL(pCCBReader);


	m_pMenu->setTouchPriority(kCCMenuHandlerPriorityHeaderInfo);


	char databuf[50];
	memset(databuf, 0, sizeof(char)* 40);
	sprintf(databuf, "%d", MB_RoleData::getInstance()->getLevel());
	if (m_pRoleLevel)m_pRoleLevel->setString(databuf);

	sprintf(databuf, "%d", MB_RoleData::getInstance()->getGold() + MB_RoleData::getInstance()->getGoldBoune());
	m_pRoleGold->setString(databuf);

	NSGameHelper::LabelFormatNumber(m_pRoleCoin, MB_RoleData::getInstance()->getCoin(), false);

	sprintf(databuf, "%d", MB_RoleData::getInstance()->getReputation());
	m_pRoleReputatiton->setString(databuf);

	m_pExpTimer = CCProgressTimer::create(m_pSpriteExp);
	m_pExpTimer->setType(kCCProgressTimerTypeBar);
	m_pExpTimer->setMidpoint(ccp(0, 1));
	m_pExpTimer->setBarChangeRate(ccp(1, 0));
	m_pExpTimer->setPercentage(0);

	m_pSpriteExp->getParent()->addChild(m_pExpTimer, m_pSpriteExp->getZOrder(), m_pSpriteExp->getTag());
    
	m_pExpTimer->setPosition(m_pSpriteExp->getPosition());
	m_pExpTimer->setAnchorPoint(m_pSpriteExp->getAnchorPoint());
	m_pSpriteExp->removeFromParent();

	updataExp();

	char energystr[20];
	sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergy());
	m_pRoleEnergy->setString(energystr);
    sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergyMax());
    m_pRoleEnergy2->setString(energystr);

	return true;
}



void MB_LayerRoleInfoHeader::updataExp()
{
	char databuf[50] = { 0 };
	int64_t preExp = MB_RoleData::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel() - 1);
	int64_t nextExp = MB_RoleData::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel());
	float m_tPerccent = 100.0f*(MB_RoleData::getInstance()->getEXP() - preExp) / (nextExp - preExp);
	m_tPerccent = m_tPerccent > 100.f ? 100.0f : m_tPerccent;
    sprintf(databuf, "%lld/%lld", MB_RoleData::getInstance()->getEXP() - preExp, nextExp - preExp);
    m_pRoleExp->setString(databuf);
	m_pExpTimer->setPercentage(m_tPerccent);

}




bool MB_LayerRoleInfoHeader::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "headinfo", CCMenu *, m_pMenu);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleEnergy", CCLabelBMFont *, m_pRoleEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleEnergy2", CCLabelBMFont *, m_pRoleEnergy2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleExp", CCLabelBMFont *, m_pRoleExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite *, m_pSpriteExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "spriteEnergy", CCSprite *, m_pSpriteEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roletotalgold", CCLabelBMFont *, m_pRoleGold);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "rolecoin", CCLabelBMFont *, m_pRoleCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "rolereputation", CCLabelBMFont *, m_pRoleReputatiton);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleLevel", CCLabelBMFont *, m_pRoleLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleNameTTF", CCLabelTTF *, m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLVNameExp", CCNode *, m_pLVNameExp);
    

	return true;
}
void MB_LayerRoleInfoHeader::onEnterTransitionDidFinish(){
	char databuf[50];
	memset(databuf, 0, sizeof(char)* 40);

    sprintf(databuf, "%s", MB_RoleData::getInstance()->getName());
    m_pRoleName->setString(databuf);
}
SEL_MenuHandler MB_LayerRoleInfoHeader::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBuyEnergeClick", MB_LayerRoleInfoHeader::onBuyEnergeClick);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChargeClick", MB_LayerRoleInfoHeader::onChargeClick);

	return NULL;
}
SEL_CCControlHandler MB_LayerRoleInfoHeader::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

	return NULL;
}
void MB_LayerRoleInfoHeader::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
	MB_LOG("onNodeLoaded succeed!");
}

void MB_LayerRoleInfoHeader::onChargeClick(CCObject * pSender){
    MB_RoleData::getInstance()->goCharge(((CCNode*)pSender)->getTag());
}


bool MB_LayerRoleInfoHeader::recvrole_update_energy(MB_MsgBuffer *recvPacket){

	char energystr[20];
	sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergy());
	m_pRoleEnergy->setString(energystr);
    sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergyMax());
    m_pRoleEnergy2->setString(energystr);
	return true;

}

void MB_LayerRoleInfoHeader::onMsgRecv(CCNode* node, SocketResponse* response){

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

	case SC_ROLE_UPDATE_ENERGY:
		recvrole_update_energy(recvPacket);
		break;
	case SC_ROLE_UPDATE_COIN:{
								 NSGameHelper::LabelFormatNumber(m_pRoleCoin, MB_RoleData::getInstance()->getCoin(), false);
	}
		break;
	case SC_ROLE_UPDATE_GOLD:
	case SC_ROLE_UPDATE_GOLDBONUS:{

									  char databuf[50];
									  sprintf(databuf, "%d", MB_RoleData::getInstance()->getGold() + MB_RoleData::getInstance()->getGoldBoune());
									  m_pRoleGold->setString(databuf);
									  break;
	}
	case RECV_ROLE_CHANGE_NAME:
		m_pRoleName->setString(MB_RoleData::getInstance()->getName());
		break;
	case SC_ROLE_BUY_ENERGY:{

								char energystr[20];
								sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergy());
								m_pRoleEnergy->setString(energystr);
                                sprintf(energystr, "%d",  MB_RoleData::getInstance()->getEnergyMax());
                                m_pRoleEnergy2->setString(energystr);
								//            float nextpercent = (MB_RoleData::getInstance()->getEnergy()*100.0f/MB_RoleData::getInstance()->getEnergyMax());
	}
		break;
	case SC_ROLE_UPDATE_REPUTATION:{

									   char databuf[50];
									   sprintf(databuf, "%d", MB_RoleData::getInstance()->getReputation());
									   m_pRoleReputatiton->setString(databuf);

	}break;
	case  SC_ROLE_UPDATE_LEVEL:{

								   char databuf[50];
								   sprintf(databuf, "%d", MB_RoleData::getInstance()->getLevel());
								   if (m_pRoleLevel)m_pRoleLevel->setString(databuf);
								   updataExp();

								   char energystr[20];
								   sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergy());
								   m_pRoleEnergy->setString(energystr);
                                   sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergyMax());
                                   m_pRoleEnergy2->setString(energystr);
								   //            float nextpercent = (MB_RoleData::getInstance()->getEnergy()*100.0f/MB_RoleData::getInstance()->getEnergyMax());

								   break;
	}
	case SC_ROLE_UPDATE_EXP:{
								updataExp();
	}
		break;
	case SC_ROLE_BASE_CONFIG:{

								 char energystr[20];
								 sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergy());
								 m_pRoleEnergy->setString(energystr);
                                 sprintf(energystr, "%d", MB_RoleData::getInstance()->getEnergyMax());
                                 m_pRoleEnergy2->setString(energystr);
	}break;
	}
	return;

}
void MB_LayerRoleInfoHeader::onBuyEnergeClick(CCObject *){

	MB_RoleData::getInstance()->buyEenergy();

}

