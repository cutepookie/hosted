
#include "Game.h"
#include "MB_RoleData.h"

#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif

#include "PayMentViewCocos2d.h"

#include "MB_FunctionMgr.h"
#include "MB_RuleFightInterface.h"
#include "MB_FunctionModule.h"
#include "MB_DataExchange.h"
#include "MB_RechargeSystem.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerShopMain.h"

static MB_RoleData* s_pRoleData = NULL; // pointer to singleton

bool MB_RoleData::IsCheckSetRoleData = false;

MB_RoleData::MB_RoleData()
{
	m_iUid = 0;

	//注册协议
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_EXP, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_COIN, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_REPUTATION, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_GOLD, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_GOLDBONUS, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_VIPLEVEL, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_ENERGY, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_DISCOVERYTIMES, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PVPTIMES, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PLUNDERTIMES, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_RANDOMPVPTIMES, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_SINGLEPVPTIMES, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_INFO, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_TITLE, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_TOKEN, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_BASE_CONFIG, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_PAY_IOS, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_ENCOUNTERFREENUM, MB_RoleData);
	SOCKET_MSG_REGIST(SC_EXPLORE_FREE, MB_RoleData);
	SOCKET_MSG_REGIST(SC_INVITE_INFO, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_PUSH_SETTING, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_WEIBOCOUNT, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_SETTING, MB_RoleData);
	SOCKET_MSG_REGIST(SC_CHALLENGEGOD_INFO, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_BUY_COIN_VALUE, MB_RoleData);
	SOCKET_MSG_REGIST(SC_REBATE_UPDATE, MB_RoleData);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_PAY_EXT, MB_RoleData);
	SOCKET_MSG_REGIST(RECV_ROLE_CHANGE_NAME, MB_RoleData);

	SOCKET_MSG_REGIST(SC_ROLE_PAY_ZZ, MB_RoleData);

	m_nWillShowLayer = kSceneTipLayerTypeNone;
	m_pRoleNormalLimit = 0;
	m_pRoleAdventureLimit = 0;
	m_pRoleCarbonLimit = 0;
	m_pRoleRocketTeamLimit = 0;
	m_pRoleHuaRongLimit = 0;
	m_pRolePlunderLimit = 0;
	m_pRolePvpLimit = 0;
	m_pRoleKingLimit = 0;
	m_pRoleNanMLimit = 0;
	m_pRoleChangbanLimit = 0;
	m_pRoleChallengeGodLimit = 0;
	m_iChallengeEachPayPrice = 0;
	m_iChallengeFreeTimes = 0;
	m_iChallengePetPos = 0;
	m_iChallengeGodTimes = 0;
	m_iChallengePayTimes = 0;
	m_pRoleAidLimit = 0;
	m_pRoleOnesLimit = 0;
	m_pRoleChatLimit = 0;
	m_pRoleWushuangLimit = 0;
	m_iDiscoveryBuyTimes = 0;
	m_iEnergyBuyTimes = 0;
	m_iPvpBuyTimes = 0;
	//    m_iPlunderBuyTimes = 0;
	m_iCoinBuyTimes = 0;
	m_iPlunderMax = 15;
	m_iEnergy = 200;
	m_iDiscoveryTimes = 100;
	m_uCurPayID = 0;
	m_nisBindWeibo = false;
	m_nInviteNum = 0;
	m_nGetFirstPayRewardNum = 0;
	m_nisInputInviteCode = false;
	m_pisPvpPushOpen = false;
	m_pisPushNightMute = false;
	m_iDiscoveryTimes = 0;
	m_iDiscoveryTimesMax = 0;
	m_nWeiboCount = 0;
	m_pLastWeiXinShareSec = 0;
	m_iPVPTimesMax = MAX_PVP_RANKING;
	m_iPlunderMax = MAX_PVP_TREASURE;
	for (int i = 0; i < 9; i++) {

		m_nSetting[i] = 0;
	}
	m_nSttingLength = 0;
	m_iNextPvpcvTime = 0;
	//    m_iNextPlundercvTime = 0;
	m_pPayArray = CCArray::create();
	m_pPayArray->retain();

	m_pFirstPayArray = CCArray::create();
	m_pFirstPayArray->retain();
	initFirstPayTemplete();

	if (!initPayTemplete())
	{
		MB_LOG("initPayTemplete failed.");
	}
	loadLevelLimit();
	m_pVipConig = new CCArray();
	initVipConfig();
}

MB_RoleData::~MB_RoleData()
{
	CC_SAFE_RELEASE_NULL(m_pVipConig);
	CC_SAFE_RELEASE_NULL(m_pPayArray);
	CC_SAFE_RELEASE_NULL(m_pFirstPayArray);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_EXP);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_COIN);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_REPUTATION);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_GOLD);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_GOLDBONUS);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_VIPLEVEL);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_ENERGY);;
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_DISCOVERYTIMES);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PVPTIMES);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PLUNDERTIMES);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_RANDOMPVPTIMES);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_SINGLEPVPTIMES);
	SOCKET_MSG_UNREGIST(SC_ROLE_INFO);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_TITLE);
	SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
	SOCKET_MSG_UNREGIST(SC_ROLE_TOKEN);
	SOCKET_MSG_UNREGIST(SC_ROLE_BASE_CONFIG);
	SOCKET_MSG_UNREGIST(SC_ROLE_PAY_IOS);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_ENCOUNTERFREENUM);
	SOCKET_MSG_UNREGIST(SC_EXPLORE_FREE);
	SOCKET_MSG_UNREGIST(SC_INVITE_INFO);
	SOCKET_MSG_UNREGIST(SC_ROLE_PUSH_SETTING);
	SOCKET_MSG_UNREGIST(SC_ROLE_PAY_91);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_WEIBOCOUNT);
	SOCKET_MSG_UNREGIST(SC_ROLE_SETTING);
	SOCKET_MSG_UNREGIST(SC_CHALLENGEGOD_INFO);
	SOCKET_MSG_UNREGIST(SC_ROLE_BUY_COIN_VALUE);
	SOCKET_MSG_UNREGIST(SC_REBATE_UPDATE);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_PAY_EXT);
	SOCKET_MSG_UNREGIST(RECV_ROLE_CHANGE_NAME);
	SOCKET_MSG_UNREGIST(SC_ROLE_PAY_ZZ);

}
void MB_RoleData::checkIsNewUser(){

	std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("UserName");
	if (strcmp(str.c_str(), m_sName.c_str()) != 0){

		SETBYKEY("musicOff", false);
		SETBYKEY("soundOff", false);
		SETBYKEY("adventure", true);
		SETBYKEY("LockScreen", true);
		CCUserDefault::sharedUserDefault()->setFloatForKey("posofbattle", 10);
		CCUserDefault::sharedUserDefault()->setFloatForKey("posofbattle2", 10);
		CCUserDefault::sharedUserDefault()->setStringForKey("UserName", m_sName.c_str());
		CCUserDefault::sharedUserDefault()->flush();

	}
	MB_Audio::getInstance()->setBackGrondOpen(!CCUserDefault::sharedUserDefault()->getBoolForKey("musicOff"));
	MB_Audio::getInstance()->setEffectsoundOpen(!CCUserDefault::sharedUserDefault()->getBoolForKey("soundOff"));
	OCandCppHelper::setLockSceen(GETBYKEY("LockScreen"));
	OCandCppHelper::removeAllMessage();

}
MB_RoleData* MB_RoleData::getInstance()
{
	if (s_pRoleData == NULL)
	{
		s_pRoleData = new MB_RoleData();
	}

	return s_pRoleData;
}

void MB_RoleData::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(s_pRoleData);
	s_pRoleData = NULL;

}

void MB_RoleData::setDescription(const char * description){

	m_sDescription = description;
}

const char * MB_RoleData::getDescription(){

	return  m_sDescription.c_str();
}

void MB_RoleData::setName(const char * name)
{
	m_sName = name;
}

int MB_RoleData::getCurrency(kmCurrency_Type type)
{
	int ret = 0;
	switch (type)
	{
	case kmCurrency_Type_Ingots:
		ret = getGold();
		break;
	case kmCurrency_Type_silver:
		ret = getCoin();
		break;
	case kmCurrency_Type_prestige:
		ret = getReputation();
		break;
	case kmCurrency_Type_points:
		ret = getGoldUsed();
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

const char * MB_RoleData::getName()
{
	return m_sName.c_str();
}

bool MB_RoleData::sendrole_change_location()
{
	SOCKET_REQUEST_START(CS_ROLE_CHANGE_LOCATION);
	packet->Write(NSDataExchange::g_LocationName.c_str(), NSDataExchange::g_LocationName.length());
	SOCKET_REQUEST_END(CS_ROLE_CHANGE_LOCATION, NULL);
	return true;
}

bool MB_RoleData::sendrole_token(const char *token){

	SOCKET_REQUEST_START(CS_ROLE_TOKEN);
	packet->Write(token, strlen(token));
	SOCKET_REQUEST_END(SC_ROLE_TOKEN, MB_RoleData::onMsgRecv);
	return true;
}
bool MB_RoleData::recvrole_token(MB_MsgBuffer *recvPacket){


	return true;
}
bool MB_RoleData::sendrole_info()
{
	SOCKET_REQUEST_START(CS_ROLE_INFO);
	SOCKET_REQUEST_END(SC_ROLE_INFO, MB_RoleData::onMsgRecv);
	return true;
}

bool MB_RoleData::sendrole_challengegod_info()
{
	//    SOCKET_REQUEST_START(CS_CHALLENGEGOD_INFO);
	//    SOCKET_REQUEST_END(SC_CHALLENGEGOD_INFO, MB_RoleData::onMsgRecv);
	return true;
}

bool MB_RoleData::recvrole_info(MB_MsgBuffer *recvPacket)
{
	uint8_t data8;
	uint16_t data16;
	uint32_t data32;
	uint64_t data64;

	if (recvPacket->readU32(&data32))
	{
		setUID(data32);
	}

	char* roleName = recvPacket->ReadString();
	if (roleName != NULL)
	{
		setName(roleName);
		CC_SAFE_FREE(roleName);
		checkIsNewUser();
	}

	if (recvPacket->readU8(&data8))
	{
		setSex(data8);
	}

	char* desc = recvPacket->ReadString();
	if (desc != NULL) {
		setDescription(desc);
		CC_SAFE_FREE(desc);
	}

	if (recvPacket->readU32(&data32)) {
		setClan(data32);
	}
	if (recvPacket->readU16(&data16))
	{
		m_iLevel = data16;
	}
	if (recvPacket->readU64(&data64)) {
		setEXP(data64);
	}
	if (recvPacket->readU32(&data32))
	{
		m_iCoin = data32;
	}
	if (recvPacket->readU32(&data32))
	{
		m_iReputation = data32;
	}
	if (recvPacket->readU32(&data32))
	{
		m_iGold = data32;
	}
	if (recvPacket->readU32(&data32)) {
		m_iGoldBoune = data32;
	}
	if (recvPacket->readU32(&data32)) {
		setGoldUsed(data32);
	}
	if (recvPacket->readU8(&data8)) {
		setVipLevel(data8);
	}
	if (recvPacket->readU32(&data32)) {
		setGoldPay(data32);
	}
	if (recvPacket->readU16(&data16)) {
		setEnergy(data16);
	}
	if (recvPacket->readU16(&data16)) {
		setEnergyBuyTimes(data16);
	}
	if (recvPacket->readU32(&data32)) {
		setNextEnergyTime(data32);
	}
	if (recvPacket->readU8(&data8)) {
		setDiscoveryTimes(data8);
	}
	if (recvPacket->readU32(&data32)) {
		setNextDscvTime(data32);
	}
	if (recvPacket->readU8(&data8)) {
		setPVPTimes(data8);
	}
	if (recvPacket->readU8(&data8)) {
		QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
			pInterface->setRuleTimes(data8);
		QUERY_FUNCTION_END
			//        setPlunderTimes(data8);//秩序戰场的次數
	}
	if (recvPacket->readU8(&data8)) {
		setRandomPVPTime(data8);
	}
	if (recvPacket->readU8(&data8)) {
		setSinglePVPTime(data8);
	}
	if (recvPacket->readU8(&data8)) {

		setTitle(data8);
	}
	if (recvPacket->readU8(&data8)) {

		setEnCounterFreeNum(data8);
	}
	if (recvPacket->readU8(&data8)) {

		setisPvpPushopen(data8 == 1);
	}
	if (recvPacket->readU8(&data8)) {

		setisPushNightMute(data8 == 1);
	}
	if (recvPacket->readU16(&data16)) {

		setDiscoveryBuyTimes(data16);
	}
	if (recvPacket->readU16(&data16)) {

		setPvpBuyTimes(data16);
	}
	if (recvPacket->readU16(&data16)) {
		QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
			pInterface->setRuleBuyTimes(data16);
		QUERY_FUNCTION_END
			//        setPlunderBuyTimes(data16);//今日rule已購買次數
	}
	if (recvPacket->readU16(&data16)) {

		setCoinBuyTimes(data16);
	}

	if (recvPacket->readU8(&data8)){

		setWeiboCount(data8);
	}
	if (recvPacket->readU32(&data32)){

		setNextPvpcvTime(data32);
	}
	if (recvPacket->readU32(&data32)){
		QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
			pInterface->setNextRuleTime(data32);
		QUERY_FUNCTION_END
			//        setNextPlundercvTime(data32); //秩序戰场恢複的時間
	}
	if (recvPacket->readU16(&data16)) {

		setChallengeGodTimes(data16);
	}
	if (recvPacket->readU16(&data16)) {

		setChallengePayTimes(data16);
	}
	if (recvPacket->readU32(&m_pLastWeiXinShareSec)){

	}
	if (recvPacket->readU32(&data32)){
		setHead(data32);
	}
	if (recvPacket->readU32(&data32)){
		setPayInfoId(data32);
		// 0000 0000 0000 0000 0000 0000 0000 0000
		// 每一位代表一个儲值档位 0表示沒有儲值双倍 1表示儲值成功
		//1100007 - 1100001 最后的位數代表最高
	}

#ifdef YJ_IOS
	MB_YJMgr_IOS::getInstance()->setRoleData();
#endif


	if (recvPacket->readU8(&data8))
	{
		setPveHasFailed(data8);
	}
	else
	{
		MB_LOG("接收玩家信息错误");
		return false;
	}
	//v1.0.5 chk
	uint8_t alienTimes = 0;
	int32_t lastAlienTime = 0;
	recvPacket->readU8(&alienTimes);
	recvPacket->readU32(&lastAlienTime);

	//儲值排序
	if (recvPacket->readU16(&data16))
	{
		MB_PayTemplete* payTemplete = NULL;
		for (int i = 0; i < data16; i++)
		{
			uint16_t gold = 0;
			if (recvPacket->readU16(&gold))
			{
				CCARRAY_FOREACH_4TYPE(m_pPayArray, MB_PayTemplete*, payTemplete)
				{
					if (payTemplete->getGold() == gold && i < m_pPayArray->count())
					{
						m_pPayArray->exchangeObject(m_pPayArray->objectAtIndex(i), payTemplete);
					}
				}
			}
		}
	}
	if (recvPacket->readU32(&data32)) {
		setChouKaTimes(data32);
		CCLog("ChouKaTimes=========%d", getChouKaTimes());
	}
	return true;
}
bool MB_RoleData::sendrole_push_setting(uint8_t type, uint16_t data){

	SOCKET_REQUEST_START(CS_ROLE_PUSH_SETTING);
	packet->writeU8(type);
	packet->writeU16(data);
	SOCKET_REQUEST_END(SC_ROLE_PUSH_SETTING, MB_RoleData::onMsgRecv);
	return true;
}
bool MB_RoleData::recvrole_push_setting(MB_MsgBuffer *recvPacket){

	uint8_t data8;
	uint16_t data16;
	recvPacket->readU8(&data8);
	if (data8 == 1){

		recvPacket->readU8(&data8);
		recvPacket->readU16(&data16);
		if (data8 == 1){

			setisPvpPushopen(data16 == 1);
		}
		else if (data8 == 2) {

			setisPushNightMute(data16 == 1);
		}
	}
	return true;
}
bool MB_RoleData::sendrole_buy_energy(uint8_t type){

	MB_Message::sharedMB_Message()->showMessage("", 2000);
	SOCKET_REQUEST_START(CS_ROLE_BUY_ENERGY);
	packet->writeU8(type);
	SOCKET_REQUEST_END(SC_ROLE_BUY_ENERGY, MB_RoleData::onMsgRecv);
	return true;
}
//bool MB_RoleData::sendexplore_free(){
//    
//    int needmoney = this->getExplorFreeNeedMonney();
//    if(needmoney > (this->getGoldBoune() +this->getGold())){
//        
//        MB_Message::sharedMB_Message()->showMessage("  ","您的寶石不足, 是否要立即進行儲值？","儲值","取消",this,menu_selector(MB_RoleData::goCharge),NULL);
//        return false;
//    }
//    SOCKET_REQUEST_START(CS_EXPLORE_FREE);
//    SOCKET_REQUEST_END(SC_EXPLORE_FREE, MB_RoleData::onMsgRecv);
//    return true;
//}
bool MB_RoleData::recvexplore_free(MB_MsgBuffer *recvPacket){
	uint8_t data;
	recvPacket->readU8(&data);
	if (data == 2){

		MB_Message::sharedMB_Message()->showMessage("宝石不足");

	}
	else if (data == 3){

		MB_Message::sharedMB_Message()->showMessage("不能再激活了");
	}

	return true;
}
bool MB_RoleData::recvrole_buy_energy(MB_MsgBuffer *recvPacket){

	uint8_t data;
	uint8_t type;

	if (recvPacket->readU8(&data))
	{
		if (recvPacket->readU8(&type)){

			if (data == 1){

				MB_Message::removeALLMessage();
				uint16_t data16;
				uint16_t dataTimes;
				recvPacket->readU16(&data16);
				recvPacket->readU16(&dataTimes);
				switch (type){

				case kBuyTimesTypeEnergy:{

											 setEnergy(data16);
											 setEnergyBuyTimes(dataTimes);
											 MB_Message::sharedMB_Message()->showMessage("您的体力回复了.");
											 break;
				}
				case kBuyTimesTypeDiscovery:{

												setDiscoveryTimes(data16);
												setDiscoveryBuyTimes(dataTimes);
												MB_Message::sharedMB_Message()->showMessage("购买成功.");
												break;
				}
				case kBuyTimesTypePvp:{

										  setPVPTimes(data16);
										  setPvpBuyTimes(dataTimes);
										  MB_Message::sharedMB_Message()->showMessage("购买成功.");
										  break;
				}
				case kBuyTimesTypeRuleFight:
				{
											   QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
												   pInterface->setRuleTimes(data16);
											   pInterface->setRuleBuyTimes(dataTimes);
											   QUERY_FUNCTION_END
												   MB_Message::sharedMB_Message()->showMessage("购买成功.");
											   break;
				}
				case kBuyTimesTypeCoin:{

										   setCoinBuyTimes(dataTimes);
										   break;
				}
				default:
					break;
				}
			}
			else
			{
				MB_LOG("recvrolebuy_energy errorcode:%d", data);
				MB_Message::sharedMB_Message()->removeALLMessage();
				if (data == 2)
				{
					MB_Message::sharedMB_Message()->showMessage("购买失败", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
				}
				else if (data == 3)
				{
					if (getVipLevel() < 12)
					{
						switch (type)
						{
						case kBuyTimesTypeEnergy:
						{
													MB_Message::sharedMB_Message()->showMessage("购买失败", "您今日回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
													break;
						}
						case kBuyTimesTypeDiscovery:
						{
													   MB_Message::sharedMB_Message()->showMessage("购买次数使用完毕", "您今日的冒险次数已经购买完毕, 充值提升VIP等级, 可以增加购买次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
													   break;
						}
						case kBuyTimesTypePvp:
						{
												 MB_Message::sharedMB_Message()->showMessage("购买次数达到上限", "您今日的竞技场次数已达上限, 充值提升VIP等级, 可以增加购买次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
												 break;
						}
						case kBuyTimesTypeRuleFight:
						{
													   MB_Message::sharedMB_Message()->showMessage("购买次数达到上限", "您今日的秩序战场战斗次数已达上限, 充值提升VIP等级, 可以增加购买次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
													   break;
						}
						case kBuyTimesTypeCoin:
						{
												  MB_Message::sharedMB_Message()->showMessage("招财次数达到上限", "您今日的招财次数已达上限, 充值提升VIP等级, 可以增加招财次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
												  break;
						}
						default:
							break;
						}
					}
					else
					{
						switch (type)
						{
						case kBuyTimesTypeEnergy:
						{
													MB_Message::sharedMB_Message()->showMessage("今日体力回复购买次数已经使用完毕");
													break;
						}
						case kBuyTimesTypeDiscovery:
						{
													   MB_Message::sharedMB_Message()->showMessage("今日冒险购买次数已经使用完毕");
													   break;
						}
						case kBuyTimesTypePvp:
						{
												 MB_Message::sharedMB_Message()->showMessage("今日竞技场次数已达上限");
												 break;
						}
						case kBuyTimesTypeRuleFight:
						{
													   MB_Message::sharedMB_Message()->showMessage("今日秩序战场次数");
													   break;
						}
						case kBuyTimesTypeCoin:
						{
												  MB_Message::sharedMB_Message()->showMessage("今日招财次数已达上限");
												  break;
						}
						default:
							break;
						}
					}
				}
				else if (data == 4)
				{
					MB_Message::sharedMB_Message()->showMessage("未知错误.");
				}
			}
		}
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_level(MB_MsgBuffer *recvPacket)
{
	uint16_t data;
	if (recvPacket->readU16(&data))
	{
		m_iLevel = data;
		sendrole_buy_coin_value();
#if defined(PLATFORM_YJ)
		MB_YJMgr::getInstance()->roleLevelUp();
#elif defined(YJ_IOS)
		MB_YJMgr_IOS::getInstance()->roleLevelUp();
#endif
		return true;
	}
	return false;
}

bool MB_RoleData::recvrole_update_exp(MB_MsgBuffer *recvPacket)
{
	uint64_t data;
	if (recvPacket->readU64(&data))
	{
		setEXP(data);
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_coin(MB_MsgBuffer *recvPacket)
{
	uint32_t data;
	if (recvPacket->readU32(&data))
	{
		m_iCoin = data;
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_reputation(MB_MsgBuffer *recvPacket)
{
	uint32_t data;
	if (recvPacket->readU32(&data))
	{
		m_iReputation = data;
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_gold(MB_MsgBuffer *recvPacket)
{
	uint32_t data;
	if (recvPacket->readU32(&data))
	{
		m_iGold = data;
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_goldbonus(MB_MsgBuffer *recvPacket)
{
	uint32_t data;
	if (recvPacket->readU32(&data))
	{
		m_iGoldBoune = data;
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_viplevel(MB_MsgBuffer *recvPacket)
{
	uint8_t data;
	if (recvPacket->readU8(&data))
	{
		setVipLevel(data);
		sendrole_challengegod_info();
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_energy(MB_MsgBuffer *recvPacket)
{
	uint16_t data;
	if (recvPacket->readU16(&data))
	{
		setEnergy(data);

	}
	uint32_t data32;
	if (recvPacket->readU32(&data32))
	{
		setNextEnergyTime(data32);

	}
	return false;
}
bool MB_RoleData::recvrole_update_discoverytimes(MB_MsgBuffer *recvPacket)
{
	uint8_t data8;
	if (recvPacket->readU8(&data8))
	{
		MB_LOG("discovery %d", data8);
		setDiscoveryTimes(data8);
	}
	uint32_t data32;
	if (recvPacket->readU32(&data32))
	{
		setNextDscvTime(data32);

	}
	return false;
}
bool MB_RoleData::recvrole_update_pvptimes(MB_MsgBuffer *recvPacket)
{
	uint8_t data;
	if (recvPacket->readU8(&data))
	{
		setPVPTimes(data);

	}
	uint32_t data32;
	if (recvPacket->readU32(&data32))
	{
		setNextPvpcvTime(data32);

	}
	return false;
}

//废弃
bool MB_RoleData::recvrole_update_plundertimes(MB_MsgBuffer *recvPacket)
{
	uint8_t data;
	if (recvPacket->readU8(&data))
	{
		//        setPlunderTimes(data);
	}
	uint32_t data32;
	if (recvPacket->readU32(&data32))
	{
		//        setNextPlundercvTime(data32);

	}
	return false;
}
bool MB_RoleData::recvrole_update_randompvptimes(MB_MsgBuffer *recvPacket)
{
	uint8_t data;
	if (recvPacket->readU8(&data))
	{
		setRandomPVPTime(data);
		return true;
	}
	return false;
}
bool MB_RoleData::recvrole_update_singlepvptimes(MB_MsgBuffer *recvPacket)
{
	uint8_t data;
	if (recvPacket->readU8(&data))
	{
		setSinglePVPTime(data);
		return true;
	}
	return false;
}

/*
 message recvchallengeGod_info[id=12702]{
 required	int16	freeTimes	=1;//免费贈送的决鬥次數
 required	int16	buyTimes	=2;//購買的次數
 required	int8	petPos		=3;//出戰精靈的位置
 required	int8	price		=4;//單次購買的价格
 }
 */
bool MB_RoleData::recvrole_update_challengegodtimes(MB_MsgBuffer *recvPacket)
{
	uint16_t first = 0;
	uint16_t second = 0;
	if (recvPacket->readU16(&first) && recvPacket->readU16(&second))
	{
		// 設置决鬥次數
		setChallengeGodTimes(first + second);
		setChallengeFreeTimes(first);
		setChallengePayTimes(second);
		recvPacket->readU8(&first);
		setChallengePetPos(first);
		recvPacket->readU8(&second);
		setChallengeEachPayPrice(second);
		return true;
	}

	return false;
}
bool MB_RoleData::recvrole_update_list(MB_MsgBuffer* recvPacket)
{
	MB_LOG("TO DO:SC_ROLE_UPDATE_LIST");
	return true;
}
bool MB_RoleData::recvrole_update_encounterFreeNum(MB_MsgBuffer *recvPacket){

	int8_t data8;
	recvPacket->readU8(&data8);
	setEnCounterFreeNum(data8);
	return true;

}
bool MB_RoleData::recvrole_update_weibocount(MB_MsgBuffer *recvPacket){

	uint8_t data8;
	recvPacket->readU8(&data8);
	this->setWeiboCount(data8);
	return true;
}
bool MB_RoleData::recvrole_update_title(MB_MsgBuffer *recvPacket){

	recvPacket->readU8(&m_iTitle);

	return true;
}
bool MB_RoleData::sendrole_setting(){

	SOCKET_REQUEST_START(CS_ROLE_SETTING);
	SOCKET_REQUEST_END(SC_ROLE_SETTING, MB_RoleData::onMsgRecv);
	return true;
}
bool MB_RoleData::recvrole_setting(MB_MsgBuffer *recvPacket){

	recvPacket->readU16(&m_nSttingLength);
	for (int i = 0; i < m_nSttingLength; i++) {

		recvPacket->readU8(&m_nSetting[i]);
	}
	return true;
}
uint16_t MB_RoleData::getSettinglength(){

	return m_nSttingLength;
}
uint8_t  * MB_RoleData::getSettings(){

	return  m_nSetting;
}
void MB_RoleData::send_role_change_name(const char *pName)
{
	SOCKET_REQUEST_START(SEND_ROLE_CHANGE_NAME);
	packet->Write(pName, strlen(pName));
	SOCKET_REQUEST_END(RECV_ROLE_CHANGE_NAME, NULL);
	m_pChangedName = pName;
}
bool  MB_RoleData::sendrole_pay_91(const char *receipt, int payID, const char *deviceID){

	std::string strReceipt = receipt;
	std::string strDeviceID = deviceID;
	const char* oriMac = MB_ClientSocket::getMacAddress();
	std::string strMac = oriMac;

	SOCKET_REQUEST_START(CS_ROLE_PAY_91);
	packet->Write(strReceipt.c_str(), strReceipt.length());
	packet->writeU32(payID);
	packet->Write(strDeviceID.c_str(), strDeviceID.length());
	packet->Write(strMac.c_str(), strMac.length());
	SOCKET_REQUEST_END(SC_ROLE_PAY_91, MB_RoleData::onMsgRecv);

	CC_SAFE_DELETE_ARRAY(oriMac);
	return  true;
}

void DE_FIRST_PAY()
{
	MB_FirstPayTemplete* pObj = NULL;
	MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Reward).c_str());
}

bool  MB_RoleData::recvrole_pay_91(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();
	if (recvPacket->readU8(&result)) {
		if (result == 1) {
			MB_LOG("pay succeed.");
			char* receipt = recvPacket->ReadString();
			CC_SAFE_FREE(receipt);
			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首儲禮包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {

					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
					//                    MB_Message::sharedMB_Message()->showMessage("首充大礼包", getFirstPayDesc(), "确定");
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("", "充值收据非法.", "确定");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("", "重复的充值收据", "确定");
				char* receipt = recvPacket->ReadString();
				CC_SAFE_FREE(receipt);
			}
		}
	}
	return true;
}



bool MB_RoleData::recvrole_pay_uc(MB_MsgBuffer* recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::recvrole_pay_ZZ(MB_MsgBuffer* recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::recvrole_pay_wdj(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}

bool MB_RoleData::recvrole_pay_360(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首儲禮包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::recvrole_pay_mi(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::recvrole_pay_az(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::recvrole_pay_dk(MB_MsgBuffer *recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}

bool MB_RoleData::recvrole_pay_dl(MB_MsgBuffer* recvPacket){

	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {

			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2) {

				MB_Message::sharedMB_Message()->showMessage("订单无效");
			}
			else if (result == 3)
			{
				MB_Message::sharedMB_Message()->showMessage("订单重复");
			}
		}
	}
	return true;
}
bool MB_RoleData::sendrole_pay_ios(const char* receipt, const char* deviceID)
{
	std::string strReceipt = receipt;
	std::string strDeviceID = deviceID;
	const char* oriMac = MB_ClientSocket::getMacAddress();
	std::string strMac = oriMac;
	SOCKET_REQUEST_START(CS_ROLE_PAY_IOS);
	packet->Write(strReceipt.c_str(), strReceipt.length());
	packet->writeU32(1001);
	packet->Write(strDeviceID.c_str(), strDeviceID.length());
	packet->Write(strMac.c_str(), strMac.length());

	packet->writeU8(0);

	SOCKET_REQUEST_END(SC_ROLE_PAY_IOS, MB_RoleData::onMsgRecv);

	CC_SAFE_DELETE_ARRAY(oriMac);
	return true;
}
bool MB_RoleData::recvrole_pay_ios(MB_MsgBuffer *recvPacket)
{
	int8_t result, data8;
	uint32_t data32;

	MB_Message::sharedMB_Message()->removeALLMessage();

	if (recvPacket->readU8(&result)) {
		if (result == 1) {
			MB_LOG("pay succeed.");
			char* receipt = recvPacket->ReadString();
			if (receipt)
			{
				PayMentViewCocos2d::sharedPayMentView()->removeCoord(receipt);
			}
			CC_SAFE_FREE(receipt);
			if (recvPacket->readU32(&data32)) {
				setGoldPay(data32);
			}
			//判断首充礼包
			if (recvPacket->readU8(&data8))
			{
				if (data8 == 1) {
					MB_ResWindow* layer = MB_Message::createMessageBox1("首充大礼包", getFirstPayDesc(), "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
					DE_FIRST_PAY();
				}
				else
				{
					MB_ResWindow* layer = MB_Message::createMessageBox1("", "充值成功!", "确定", NULL, NULL);
					layer->setTag(MESSAGE_TAG + 1);
					CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
				}
			}
		}
		else
		{
			MB_LOG("pay failed. errcode:%d", result);
			if (result == 2 || result == 4) {
				char* receipt = recvPacket->ReadString();
				if (receipt)
				{
					PayMentViewCocos2d::sharedPayMentView()->removeCoord(receipt);
				}
				CC_SAFE_FREE(receipt);
				MB_Message::sharedMB_Message()->showMessage("", "充值收据非法.", "确定");
			}
			else if (result == 3)
			{
				char* receipt = recvPacket->ReadString();
				if (receipt)
				{
					PayMentViewCocos2d::sharedPayMentView()->removeCoord(receipt);
				}
				CC_SAFE_FREE(receipt);
				MB_Message::sharedMB_Message()->showMessage("", "重复的充值收据", "确定");
			}
			else
			{
				MB_Message::sharedMB_Message()->showMessage("", "充值验证失败, 请重启客户端尝试验证", "确定");
			}
		}
	}
	return true;
}


bool MB_RoleData::recvrole_pay_yyb(MB_MsgBuffer *recvPacket)
{
	return true;

}

void MB_RoleData::goreSendPayOrder(CCObject *)
{
}


void MB_RoleData::onMsgRecv(CCNode* node, SocketResponse* response)
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

	case SC_ROLE_INFO:
		recvrole_info(recvPacket);
		break;

	case SC_ROLE_UPDATE_LEVEL:
		recvrole_update_level(recvPacket);
		break;

	case SC_ROLE_UPDATE_LIST:
		recvrole_update_list(recvPacket);
		break;

	case SC_ROLE_UPDATE_EXP:
		recvrole_update_exp(recvPacket);
		break;
	case RECV_ROLE_CHANGE_NAME:
	{
								  uint8_t u8 = 0;
								  recvPacket->readU8(&u8);
								  if (u8 == 0)
								  {
									  setName(m_pChangedName.c_str());
								  }
	}
		break;
	case SC_ROLE_UPDATE_COIN:
		recvrole_update_coin(recvPacket);
		break;

	case SC_ROLE_UPDATE_REPUTATION:
		recvrole_update_reputation(recvPacket);
		break;

	case SC_ROLE_UPDATE_GOLD:
		recvrole_update_gold(recvPacket);
		break;

	case SC_ROLE_UPDATE_GOLDBONUS:
		recvrole_update_goldbonus(recvPacket);
		break;

	case SC_ROLE_UPDATE_VIPLEVEL:
		recvrole_update_viplevel(recvPacket);
		break;

	case SC_ROLE_UPDATE_ENERGY:
		recvrole_update_energy(recvPacket);
		break;

	case SC_ROLE_UPDATE_DISCOVERYTIMES:
		recvrole_update_discoverytimes(recvPacket);
		break;

	case SC_ROLE_UPDATE_PVPTIMES:
		recvrole_update_pvptimes(recvPacket);
		break;

	case SC_ROLE_UPDATE_PLUNDERTIMES:
		recvrole_update_plundertimes(recvPacket);
		break;

	case SC_ROLE_UPDATE_RANDOMPVPTIMES:
		recvrole_update_randompvptimes(recvPacket);
		break;

	case SC_ROLE_UPDATE_SINGLEPVPTIMES:
		recvrole_update_singlepvptimes(recvPacket);
		break;
	case SC_ROLE_UPDATE_TITLE:
		recvrole_update_title(recvPacket);
		break;
	case SC_ROLE_BUY_ENERGY:
		recvrole_buy_energy(recvPacket);
		break;
	case SC_ROLE_TOKEN:
		recvrole_token(recvPacket);
		break;
	case SC_ROLE_BASE_CONFIG:
		recvrole_base_config(recvPacket);
		break;
	case SC_ROLE_PAY_IOS:
		recvrole_pay_ios(recvPacket);
		break;
	case SC_EXPLORE_FREE:
		recvexplore_free(recvPacket);
		break;
	case SC_ROLE_UPDATE_ENCOUNTERFREENUM:
		recvrole_update_encounterFreeNum(recvPacket);
		break;
	case SC_INVITE_INFO:
		recvinvite_info(recvPacket);
		break;
	case SC_ROLE_PUSH_SETTING:
		recvrole_push_setting(recvPacket);
		break;
	case SC_ROLE_UPDATE_WEIBOCOUNT:
		recvrole_update_weibocount(recvPacket);
		break;
	case SC_ROLE_SETTING:
		recvrole_setting(recvPacket);
		break;
	case SC_CHALLENGEGOD_INFO:
		recvrole_update_challengegodtimes(recvPacket);
		break;
	case SC_ROLE_BUY_COIN_VALUE:
		recvrole_buy_coin_value(recvPacket);
		break;
	case SC_REBATE_UPDATE:
		//            if (MB_GiftMoneyMgr::getInstance()->getIsOpen())
		//            {
		//                MB_GiftMoneyMgr::getInstance()->sendactivity_rebate_info();
		//            }
		//            break;
	case SC_ROLE_UPDATE_PAY_EXT:
	{
								   uint32_t pay_ext;
								   recvPacket->readU32(&pay_ext);
								   setPayInfoId(pay_ext);
	}
	case SC_ROLE_PAY_ZZ:
		recvrole_pay_ZZ(recvPacket);
		break;
	default:
		break;
	}

}
bool MB_RoleData::sendrole_buy_coin_value(){

	SOCKET_REQUEST_START(CS_ROLE_BUY_COIN_VALUE);
	SOCKET_REQUEST_END(SC_ROLE_BUY_COIN_VALUE, MB_RoleData::onMsgRecv);

	return true;
}
bool MB_RoleData::recvrole_buy_coin_value(MB_MsgBuffer* recvPacket){

	recvPacket->readU32(&m_nBuyCoinValue);
	return true;
}
bool MB_RoleData::sendinvite_info(){

	SOCKET_REQUEST_START(CS_INVITE_INFO);
	SOCKET_REQUEST_END(SC_INVITE_INFO, MB_RoleData::onMsgRecv);

	return true;
}
bool MB_RoleData::recvinvite_info(MB_MsgBuffer* recvPacket){

	uint8_t data8;
	uint16_t data16;
	char * str;
	if (recvPacket->readU8(&data8)){

		setisBindWeibo(data8 == 1);
	}
	if (recvPacket->readU8(&data8)){

		setisInputInviteCode(data8 == 1);
	}
	if (recvPacket->readU16(&data16)){

		setInvireNum(data16);
	}
	str = recvPacket->ReadString();
	if (str != NULL){

		setWhoInviteYou(str);
		CC_SAFE_FREE(str);

	}
	else {

		setWhoInviteYou(" ");

	}
	if (recvPacket->readU16(&data16)){

		setGetFirstPayRewardNum(data16);
	}

	return true;

}
bool MB_RoleData::recvrole_base_config(MB_MsgBuffer* recvPacket){

	uint8_t data8;
	if (recvPacket->readU8(&data8)) {

		setEnergyMax(data8);
	}
	if (recvPacket->readU8(&data8)) {

		setDiscoveryTimesMax(data8);
	}
	return true;
}
int64_t MB_RoleData::getExpByLevel(int level){

	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_level_up.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;

	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "level")) {
			curNode = curNode->next;
			continue;
		}
		bool isgetValue = false;
		int64_t exp = 0;
		struct _xmlAttr * attr = curNode->properties;
		for (; attr != NULL; attr = attr->next) {

			if (!xmlStrcmp(attr->name, BAD_CAST "value"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				int readLevel = atoi(value);
				CC_SAFE_FREE(value);
				if (level == readLevel) {

					isgetValue = true;
				}

			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "exp")){

				value = (char*)xmlNodeGetContent(attr->children);
				exp = atol(value);
				CC_SAFE_FREE(value);

			}
		}
		if (isgetValue) {

			xmlFreeDoc(g_sharedDoc);
			return exp;
		}


		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
	return 0;

}
int32_t MB_RoleData::getLevelByExp(int64_t exp){


	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_level_up.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;
	uint32_t nowlevel = 1;
	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "level")) {
			curNode = curNode->next;
			continue;
		}

		struct _xmlAttr * attr = curNode->properties;
		for (; attr != NULL; attr = attr->next) {

			if (!xmlStrcmp(attr->name, BAD_CAST "value"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				nowlevel = atoi(value);
				CC_SAFE_FREE(value);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "exp"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				int64_t nowexp = atol(value);
				CC_SAFE_FREE(value);
				if (nowexp > exp){

					xmlFreeDoc(g_sharedDoc);
					return nowlevel;
				}


			}
		}

		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
	return 0;

}
int64_t MB_RoleData::getExpByExp(int64_t exp){

	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_level_up.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;

	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "level")) {
			curNode = curNode->next;
			continue;
		}

		struct _xmlAttr * attr = curNode->properties;
		for (; attr != NULL; attr = attr->next) {

			if (!xmlStrcmp(attr->name, BAD_CAST "exp"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				int64_t nowexp = atol(value);
				CC_SAFE_FREE(value);
				if (nowexp > exp){

					xmlFreeDoc(g_sharedDoc);
					return nowexp;
				}


			}
		}

		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
	return -1;


}
void MB_RoleData::initVipConfig(){

	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/vip_limit.xml");

	if (!g_sharedDoc)
	{
		return;
	}

	xmlNodePtr root;
	char* value;
	root = xmlDocGetRootElement(g_sharedDoc);
	struct _xmlAttr * attr = root->properties;
	for (; attr != NULL; attr = attr->next) {

		if (!xmlStrcmp(attr->name, BAD_CAST "energyrecovery")) {

			value = (char*)xmlNodeGetContent(attr->children);
			int  data = atoi(value);
			CC_SAFE_FREE(value);
			setEnergyRecoveryTimes(data);

		}
		else if (!xmlStrcmp(attr->name, BAD_CAST "dicoveryrecovery")) {

			value = (char*)xmlNodeGetContent(attr->children);
			int  data = atoi(value);
			CC_SAFE_FREE(value);
			setDiscoveryRecoveryTimes(data);

		}
		else if (!xmlStrcmp(attr->name, BAD_CAST "pvprecovery")) {

			value = (char*)xmlNodeGetContent(attr->children);
			int  data = atoi(value);
			CC_SAFE_FREE(value);
			setPvpRecoveryTimes(data);

		}
		//        else if (!xmlStrcmp(attr->name,BAD_CAST "plunderrecovery")) {
		//            
		//            value = (char*)xmlNodeGetContent(attr->children);
		//            int  data = atoi(value);
		//            CC_SAFE_FREE(value);
		//            setPlunderRecoveryTimes(data);
		//        }
		else if (!xmlStrcmp(attr->name, BAD_CAST "coinrecovery")) {

			value = (char*)xmlNodeGetContent(attr->children);
			int  data = atoi(value);
			CC_SAFE_FREE(value);
			setCoinRecoveryimes(data);
		}
		else if (!xmlStrcmp(attr->name, BAD_CAST "rulefightrecovery")) {

			value = (char*)xmlNodeGetContent(attr->children);
			int  data = atoi(value);
			CC_SAFE_FREE(value);
			setRuleFightRecoveryTimes(data);
		}


	}
	xmlNodePtr curNode = root->xmlChildrenNode;
	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "vip")) {
			curNode = curNode->next;
			continue;
		}
		MB_VipConfig * vip = new MB_VipConfig();
		struct _xmlAttr * attr = curNode->properties;
		for (; attr != NULL; attr = attr->next) {

			if (!xmlStrcmp(attr->name, BAD_CAST "level")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int  data = atoi(value);
				CC_SAFE_FREE(value);
				vip->setlevel(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "energybuymax")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int  data = atoi(value);
				CC_SAFE_FREE(value);
				vip->setEnergyBuyLimit(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "dicoverybuymax")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int  data = atoi(value);
				CC_SAFE_FREE(value);
				vip->setDiscoveryLimit(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "pvpbuymax")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int  data = atoi(value);
				CC_SAFE_FREE(value);
				vip->setPvpLimit(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "coinbuymax")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int  data = atoi(value);
				CC_SAFE_FREE(value);
				vip->setCoinBuyLimit(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "lvuppay")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int64_t data = atoll(value);
				CC_SAFE_FREE(value);
				vip->setLvuppay(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "maxfriendnum")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int64_t data = atoll(value);
				CC_SAFE_FREE(value);
				vip->setMaxFriendNum(data);

			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "rulefightbuymax")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int64_t data = atoll(value);
				CC_SAFE_FREE(value);
				vip->setRuleFightBuyLimit(data);
			}
			else  if (!xmlStrcmp(attr->name, BAD_CAST "moneydungeon")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int64_t data = atoll(value);
				CC_SAFE_FREE(value);
				vip->setMoneyDungeon(data);

			}
		}
		m_pVipConig->addObject(vip);
		vip->release();
		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
	return;
}

bool MB_RoleData::initFirstPayTemplete()
{
	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/shop/first_pay.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;
	while (curNode != NULL)
	{
		struct _xmlAttr * attr = curNode->properties;

		if (attr != NULL)
		{
			MB_FirstPayTemplete* payTemplete = new MB_FirstPayTemplete();

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "id"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				payTemplete->setID(atoi(value));
				CC_SAFE_FREE(value);
				attr = attr->next;
			}

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "num"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				payTemplete->setNum(atof(value));
				CC_SAFE_FREE(value);
				attr = attr->next;
			}

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "rewardtype"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				payTemplete->setType(atof(value));
				CC_SAFE_FREE(value);
				attr = attr->next;
			}



			m_pFirstPayArray->addObject(payTemplete);
			payTemplete->release();
		}

		curNode = curNode->next;
	}

	xmlFreeDoc(g_sharedDoc);

	return true;
}

bool MB_RoleData::initPayTemplete()
{
	xmlDocPtr g_sharedDoc = NULL;
	//if (NSGameHelper::getSrcType() == NSGameHelper::ACCOUNT_TYPE_NORMAL)
	//{
	//	g_sharedDoc = MB_XmlReader::readXml("config/shop/paylist_app.xml");
	//}
	//else
	{
		g_sharedDoc = MB_XmlReader::readXml("config/shop/paylist.xml");
	}

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;
	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "pay")
			&& xmlStrcmp(curNode->name, BAD_CAST "firstPay"))
		{
			curNode = curNode->next;
			continue;
		}

		struct _xmlAttr * attr = curNode->properties;

		if (attr != NULL) {

			if (attr&&!xmlStrcmp(attr->name, BAD_CAST "desc"))
			{
				value = (char*)xmlNodeGetContent(attr->children);
				setFirstPayDesc(value);
				CC_SAFE_FREE(value);
				curNode = curNode->next;
				continue;
			}

			MB_PayTemplete* payTemplete = new MB_PayTemplete();
			while (attr != NULL) {

				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "id"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setID(atoi(value));
					CC_SAFE_FREE(value);

				}


				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "icon"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setIconName(value);
					CC_SAFE_FREE(value);

				}

				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "gold"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setGold(atoi(value));
					CC_SAFE_FREE(value);

				}
				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "extreward"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setExtreward(atoi(value));
					CC_SAFE_FREE(value);

				}
				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "bonus"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setBonus(atoi(value));
					CC_SAFE_FREE(value);

				}

				if (attr&&!xmlStrcmp(attr->name, BAD_CAST "price"))
				{
					value = (char*)xmlNodeGetContent(attr->children);
					payTemplete->setPrice(atof(value));
					CC_SAFE_FREE(value);

				}

				attr = attr->next;

			}

			//加入到模板中
			m_pPayArray->addObject(payTemplete);
			payTemplete->release();

		}

		curNode = curNode->next;
	}

	m_pPayArray->reverseObjects();//倒序
	xmlFreeDoc(g_sharedDoc);

	return true;
}

int MB_RoleData::getNowBuyLimit(kBuyTimesType type){

	MB_VipConfig * obj = NULL;
	if (this->getVipLevel() >= m_pVipConig->count()){

		obj = (MB_VipConfig *)m_pVipConig->lastObject();

	}
	else {

		obj = (MB_VipConfig *)m_pVipConig->objectAtIndex(this->getVipLevel());

	}
	switch (type) {

	case  kBuyTimesTypeEnergy:

		return   obj->getEnergyBuyLimit();
		break;
	case  kBuyTimesTypeDiscovery:

		return   obj->getDiscoveryLimit();
		break;
	case  kBuyTimesTypePvp:

		return   obj->getPvpLimit();
		break;
	case  kBuyTimesTypeRuleFight:
		return  obj->getRuleFightBuyLimit();
		break;
	case  kBuyTimesTypeCoin:

		return   obj->getCoinBuyLimit();
		break;
	default:
		break;
	}
	return -1;
}

int MB_RoleData::getMoneyDungeonLimit()
{
	MB_VipConfig * obj = NULL;
	if (this->getVipLevel() >= m_pVipConig->count()){

		obj = (MB_VipConfig *)m_pVipConig->lastObject();

	}
	else {

		obj = (MB_VipConfig *)m_pVipConig->objectAtIndex(this->getVipLevel());

	}
	return obj->getMoneyDungeon();
}

int MB_RoleData::getNeedGold(){

	return getNeedGoldByTime(kBuyTimesTypeEnergy);

}
int MB_RoleData::getNeedGoldByTime(int type){

	char searchWord[20];
	char searchChildWord[20];
	searchWord[0] = '\0';
	searchChildWord[0] = '\0';
	int buyTimes = 0;
	switch (type) {
	case kBuyTimesTypeEnergy:{

								 buyTimes = this->getEnergyBuyTimes();
								 strcpy(searchWord, "rolebuyenergy");
								 strcpy(searchChildWord, "energybuy");

	}
		break;
	case kBuyTimesTypeDiscovery:{

									buyTimes = this->getDiscoveryBuyTimes();
									strcpy(searchWord, "rolebuydiscover");
									strcpy(searchChildWord, "discoverbug");
	}
		break;
	case kBuyTimesTypePvp:{

							  buyTimes = this->getPvpBuyTimes();
							  strcpy(searchWord, "rolebuyPVPtime");
							  strcpy(searchChildWord, "PVP");
	}
		break;
	case kBuyTimesTypeRuleFight:
	{
								   QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
									   buyTimes = pInterface->getRuleBuyTimes();
								   strcpy(searchWord, "rulefight");
								   strcpy(searchChildWord, "buy");
								   QUERY_FUNCTION_END;
	}
		break;
	case kBuyTimesTypeCoin:{

							   buyTimes = this->getCoinBuyTimes();
							   strcpy(searchWord, "rolebuycoin");
							   strcpy(searchChildWord, "coinbug");
	}
		break;
	default:
		break;
	}

	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_dailybuy.xml");

	if (!g_sharedDoc)
	{
		return false;
	}

	xmlNodePtr root;

	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;

	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST searchWord)) {
			curNode = curNode->next;
			continue;
		}
		xmlNodePtr child = curNode->xmlChildrenNode;
		while (child != NULL) {

			if (xmlStrcmp(child->name, BAD_CAST searchChildWord)) {
				child = child->next;
				continue;
			}
			struct _xmlAttr * attr = child->properties;
			if (!xmlStrcmp(attr->name, BAD_CAST "times")) {

				value = (char*)xmlNodeGetContent(attr->children);
				int times = atoi(value);
				CC_SAFE_FREE(value);
				if (times == buyTimes){

					attr = attr->next;
					if (!xmlStrcmp(attr->name, BAD_CAST "gold")){

						value = (char*)xmlNodeGetContent(attr->children);
						int needmoney = atoi(value);
						CC_SAFE_FREE(value);
						xmlFreeDoc(g_sharedDoc);
						return needmoney;
					}
				}
			}
			child = child->next;
		}
		break;
	}
	xmlFreeDoc(g_sharedDoc);
	return 0;

}
//int MB_RoleData::getExplorFreeNeedMonney(){
//
//    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_unlock_money.xml");
//    
//    if (!g_sharedDoc)
//    {
//        return -1;
//    }
//    
//    xmlNodePtr root;
//    
//    root=xmlDocGetRootElement(g_sharedDoc);
//    xmlNodePtr curNode = root->xmlChildrenNode;
//    char* value;
//    
//    while(curNode != NULL) {
//        
//        if (xmlStrcmp(curNode->name,BAD_CAST "pos")) {
//            curNode = curNode->next;
//            continue;
//        }
//        
//        struct _xmlAttr * attr = curNode->properties;
//        if (!xmlStrcmp(attr->name,BAD_CAST "value")) {
//            
//            value = (char*)xmlNodeGetContent(attr->children);
//            int pos = atoi(value) -1;
//            CC_SAFE_FREE(value);
//            if(pos  == m_iEnCounterFreeNum){
//                
//                attr = attr->next;
//                if(!xmlStrcmp(attr->name,BAD_CAST "needmoney")){
//                    
//                    value = (char*)xmlNodeGetContent(attr->children);
//                    int needmoney = atoi(value);
//                    CC_SAFE_FREE(value);
//                    xmlFreeDoc(g_sharedDoc);
//                    return needmoney;
//                }
//            }
//        }
//        
//        curNode = curNode->next;
//    }
//    xmlFreeDoc(g_sharedDoc);
//    return -1;
//}
void MB_RoleData::buyEenergy(){

	if (this->getEnergy() >= this->getEnergyMax()){

		MB_Message::sharedMB_Message()->showMessage("购买体力", "体力已满无需购买", "确定");
		return;

	}
	else{

		if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(Energy_ADD, CCFunctionInterface::getCurrentFunctionWnd()))
		{
			int needmoney = this->getNeedGold();
			char databuf[100];
			sprintf(databuf, "是否需要花费%d宝石回复%d点体力？", needmoney, getEnergyRecoveryTimes());
			MB_Message::sharedMB_Message()->showMessage("购买体力", databuf, "确定", "取消", this, menu_selector(MB_RoleData::goBuyEnergy), NULL);
			return;
		}

		int limit = MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeEnergy) - MB_RoleData::getInstance()->getEnergyBuyTimes();
		if (limit <= 0){

			if (MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL){

				char databuf[200];
				sprintf(databuf, "您的体力不足了, 并且今日的体力回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数.");
				MB_Message::sharedMB_Message()->showMessage("购买体力", databuf, "充值", "取消", MB_RoleData::getInstance(), menu_selector(MB_RoleData::goCharge), NULL);

			}
			else {

				MB_Message::sharedMB_Message()->showMessage("今日体力购买次数已达上限");
			}
			return;
		}
	}
}
void MB_RoleData::goBuyEnergy(CCObject *){

	int needmoney = this->getNeedGold();
	if (needmoney > (this->getGoldBoune() + this->getGold())){

		MB_Message::sharedMB_Message()->showMessage("购买体力", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

	}
	else {

		CCLOG("buyEnergy %d %d", this->getEnergyBuyTimes(), this->getNowBuyLimit(kBuyTimesTypeEnergy));
		if (this->getEnergyBuyTimes() >= this->getNowBuyLimit(kBuyTimesTypeEnergy)) {

			MB_Message::sharedMB_Message()->showMessage("购买体力", "您今日体力回复次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

		}
		else {

			MB_Message::sharedMB_Message()->showMessage("买体力", 600);
			sendrole_buy_energy(kBuyTimesTypeEnergy);
		}
	}

}
void  MB_RoleData::goBuyDiscoveryTimes(CCObject *){

	int needmoney = this->getNeedGoldByTime(kBuyTimesTypeDiscovery);
	if (needmoney > (this->getGoldBoune() + this->getGold())){

		MB_Message::sharedMB_Message()->showMessage("购买冒险次数", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

	}
	else {

		if (this->getDiscoveryBuyTimes() >= this->getNowBuyLimit(kBuyTimesTypeDiscovery)) {

			MB_Message::sharedMB_Message()->showMessage("购买次数使用完毕", "您今日冒险购买次数已使用完毕, 充值提升VIP等级, 可以增加购买次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

		}
		else {

			MB_Message::sharedMB_Message()->showMessage("买冒险", 600);
			sendrole_buy_energy(kBuyTimesTypeDiscovery);
		}
	}

}
void MB_RoleData::goBuyCoin(CCObject * obj){

	int needmoney = this->getNeedGoldByTime(kBuyTimesTypeCoin);
	if (needmoney > (this->getGoldBoune() + this->getGold()))
	{
		MB_Message::sharedMB_Message()->showMessage("购买失败", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
	}
	else
	{
		if (this->getCoinBuyTimes() >= this->getNowBuyLimit(kBuyTimesTypeCoin))
		{
			MB_Message::sharedMB_Message()->showMessage("招财次数达到上限", "您今日招财次数已达上限, 充值提升VIP等级, 可以增加招财次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
		}
		else
		{
			MB_Message::sharedMB_Message()->showMessage("买冒险", 600);

			CCControlButton* pBtn = dynamic_cast<CCControlButton*>(obj);
			if (pBtn)pBtn->setEnabled(false);
			sendrole_buy_energy(kBuyTimesTypeCoin);
		}
	}
}

void MB_RoleData::goBuyRuleFight(CCObject * obj)
{
	int needmoney = this->getNeedGoldByTime(kBuyTimesTypeRuleFight);
	if (needmoney > (this->getGoldBoune() + this->getGold()))
	{
		MB_Message::sharedMB_Message()->showMessage("购买失败", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
	}
	else
	{
		int rulebuytimes = 0;
		QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
			rulebuytimes = pInterface->getRuleBuyTimes();
		QUERY_FUNCTION_END

		if (rulebuytimes >= this->getNowBuyLimit(kBuyTimesTypeRuleFight))
		{
			MB_Message::sharedMB_Message()->showMessage("购买挑战次数失败", "您今日购买挑战次数已达上限, 充值提升VIP等级, 可以增加挑战次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);
		}
		else
		{
			MB_Message::sharedMB_Message()->showMessage("", 15);
			CCControlButton* pBtn = dynamic_cast<CCControlButton*>(obj);
			if (pBtn)pBtn->setEnabled(false);
			sendrole_buy_energy(kBuyTimesTypeRuleFight);
		}
	}
}

int MB_RoleData::getVipLevelUpPay() {

	uint8_t viplevel = getVipLevel();
	if (viplevel >= MAX_VIP_LEVEL) {
		return 0;
	}

	MB_VipConfig* vipInfo = (MB_VipConfig*)m_pVipConig->objectAtIndex(viplevel + 1);
	int needPay = vipInfo->getLvuppay() / 10 - getGoldPay() / 200;
	return needPay;
}

void MB_RoleData::goBuyPvpTimes(CCObject *){

	int needmoney = this->getNeedGoldByTime(kBuyTimesTypePvp);
	if (needmoney > (this->getGoldBoune() + this->getGold())){


		MB_Message::sharedMB_Message()->showMessage("购买竞技场次数", "您的宝石不足, 是否要立即进行充值？", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

	}
	else {

		if (this->getPvpBuyTimes() >= this->getNowBuyLimit(kBuyTimesTypePvp)) {

			MB_Message::sharedMB_Message()->showMessage("购买次数达到上限", "您今日竞技场次数已达上限, 充值提升VIP等级, 可以增加购买次数.", "充值", "取消", this, menu_selector(MB_RoleData::goCharge), NULL);

		}
		else {

			MB_Message::sharedMB_Message()->showMessage("买争霸", 600);
			sendrole_buy_energy(kBuyTimesTypePvp);
		}
	}
}


void MB_RoleData::goCharge(int index){
   
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    MB_ResWindow* pWnd;
    if (MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop, &pInterface) && pInterface)
    {
        if (index==3) {//充值
            pWnd = MB_LayerShopMain::createPayShop();
            if (pWnd)
            {
                pInterface->replaceMainSceneSubLayer(pWnd);
            }
        }else if(index==5) {//月卡
            pWnd = MB_LayerShopMain::createRefreshShop();
            if (pWnd)
            {
                pInterface->replaceMainSceneSubLayer(pWnd);
            }
        }
        else
        {
            pWnd = MB_LayerShopMain::createItemShop();
            if (pWnd)
            {
                pInterface->replaceMainSceneSubLayer(pWnd);
            }
        }
    }
}
//功能等級限制
void MB_RoleData::loadLevelLimit(){
    
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/role_level_limit.xml");
    if (!g_sharedDoc)
    {
        return;
    }
    xmlNodePtr root;
    root = xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while (curNode != NULL) {
        
        if (!xmlStrcmp(curNode->name, BAD_CAST "rolenormal")) {
            
            struct _xmlAttr * attr = curNode->properties;
            for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleNormalLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleadventure")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleAdventureLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolecarbon")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setCarbonLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolehulao")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleRocketTeamLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolehuarong")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleHuaRongLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleplunder")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRolePlunderLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolepvp")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRolePvpLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleking")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleKingLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleworldboss")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleNanMLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolechangban")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleChangbanLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolepet")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					// setRolePetLimit(atoi(value));
					setRoleChallengeGodLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleaid")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleAidLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleones")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleOnesLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleonessign")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleOnesSignLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolegwushuang")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleWushuangLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolepurgatory")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleAdvanceLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolechat")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleChatLimit(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "rolesweep")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleSweepLimit(atoi(value));
					CC_SAFE_FREE(value);

				}
				else if (!xmlStrcmp(attr->name, BAD_CAST "vip")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleSweepVip(atoi(value));
					CC_SAFE_FREE(value);
					break;
				}
			}

		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "roleemperor")) {

			struct _xmlAttr * attr = curNode->properties;
			for (; attr != NULL; attr = attr->next) {

				if (!xmlStrcmp(attr->name, BAD_CAST "level")){

					value = (char*)xmlNodeGetContent(attr->children);
					setRoleEmperorLimit(atoi(value));
					CC_SAFE_FREE(value);
				}
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
}
MB_VipConfig::MB_VipConfig(){

}
MB_VipConfig::~MB_VipConfig(){

}
const char * MB_TitleTemplete::getTitleName(){

	return m_strTitleName.c_str();
}
const char * MB_TitleTemplete::getMFaceFrame(){

	return m_strMfaceFrame.c_str();

}
const char * MB_TitleTemplete::getMCardFrame(){

	return m_strMcardFrame.c_str();
}
const char * MB_TitleTemplete::getFFaceFrame(){

	return m_strFfaceFrame.c_str();
}
const char * MB_TitleTemplete::getFCardFrame(){

	return m_strFcardFrame.c_str();

}
void MB_TitleTemplete::setTitleName(const char * titleName){

	m_strTitleName = titleName;
}
void MB_TitleTemplete::setMFaceFrame(const char * mfaceFrame){

	m_strMfaceFrame = mfaceFrame;

}
void MB_TitleTemplete::setMCardFrame(const char * mcardFrame){

	m_strMcardFrame = mcardFrame;
}
void MB_TitleTemplete::setFFaceFrame(const char * ffaceFrame){

	m_strFfaceFrame = ffaceFrame;
}
void MB_TitleTemplete::setFCardFrame(const char * fcardFrame){

	m_strFcardFrame = fcardFrame;
}


MB_TitleMgr::MB_TitleMgr(){

	initTitleData();
}
void MB_TitleMgr::initTitleData(){

	xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/arena_level.xml");
	if (!g_sharedDoc)
	{
		return;
	}
	xmlNodePtr root;
	root = xmlDocGetRootElement(g_sharedDoc);
	xmlNodePtr curNode = root->xmlChildrenNode;
	char* value;

	while (curNode != NULL) {

		if (xmlStrcmp(curNode->name, BAD_CAST "title")) {
			curNode = curNode->next;
			continue;
		}
		MB_TitleTemplete * title = new MB_TitleTemplete();
		struct _xmlAttr * attr = curNode->properties;
		for (; attr != NULL; attr = attr->next) {

			if (!xmlStrcmp(attr->name, BAD_CAST "titleId")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setTitleID(atoi(value));
				CC_SAFE_FREE(value);

			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "titleName")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setTitleName(value);
				CC_SAFE_FREE(value);
			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "titleName")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setTitleName(value);
				CC_SAFE_FREE(value);
			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "mface")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setMFaceFrame(value);
				CC_SAFE_FREE(value);

			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "mcard")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setMCardFrame(value);
				CC_SAFE_FREE(value);
			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "fface")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setFFaceFrame(value);
				CC_SAFE_FREE(value);

			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "fcard")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setFCardFrame(value);
				CC_SAFE_FREE(value);
			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "level_need")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setLeveLNeed(atoi(value));
				CC_SAFE_FREE(value);
			}
			else if (!xmlStrcmp(attr->name, BAD_CAST "rank_need")){

				value = (char*)xmlNodeGetContent(attr->children);
				title->setRankNeed(atoi(value));
				CC_SAFE_FREE(value);
			}

		}
		m_mapTitle.insert(TitleEntry(title->getTitleID(), title));
		curNode = curNode->next;
	}
	xmlFreeDoc(g_sharedDoc);
}
void buyEenergy(){
}
MB_TitleMgr::~MB_TitleMgr(){

}
MB_TitleTemplete * MB_TitleMgr::getTitleByID(uint8_t titleID){

	TitleMap::iterator titleTempleteIterator = m_mapTitle.find(titleID);
	if (titleTempleteIterator != m_mapTitle.end()) {

		return titleTempleteIterator->second;
	}
	else
	{
		MB_LOG("ID:%d title not exist.", titleID);
		return  NULL;
	}


}
MB_TitleMgr *MB_TitleMgr::getInstance(){

	if (m_pSharedTitleMgr == NULL) {

		m_pSharedTitleMgr = new MB_TitleMgr();
	}
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
	return m_pSharedTitleMgr;
}
void MB_TitleMgr::purgeData(){

	if (m_pSharedTitleMgr != NULL) {

		delete m_pSharedTitleMgr;
	}

	m_pSharedTitleMgr = NULL;

}

MB_TitleMgr * MB_TitleMgr::m_pSharedTitleMgr = NULL;
