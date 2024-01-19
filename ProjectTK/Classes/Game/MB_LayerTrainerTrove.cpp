//
//  MB_LayerTrainerTrove.cpp
//  ProjectMB
//
//  Create by wenyong on 27/2/2015.
//
//
#include "MB_LayerTrainerTrove.h"
#include "MB_Message.h"
#include "MB_FunctionModule.h"
#include "MB_LayerFunctionRule.h"
#include "MB_TrainerTroveProtocol.h"
#include "MB_ClientSocket.h"
#include "MB_FunctionTrainerTroveInterface.h"

MB_LayerTrainerTrove::MB_LayerTrainerTrove()
{
    m_pTTFLastFightCount	 = NULL;
    m_pTTFFightTime          = NULL;
    m_pInterface = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    SOCKET_MSG_REGIST(SC_BATTLE_COIN_INFO,MB_LayerTrainerTrove);
    SOCKET_MSG_REGIST(SC_BATTLE_COIN_FIGHT,MB_LayerTrainerTrove);
}
MB_LayerTrainerTrove::~MB_LayerTrainerTrove()
{
    CC_SAFE_RELEASE_NULL(m_pTTFLastFightCount);
    CC_SAFE_RELEASE_NULL(m_pTTFFightTime);
    SOCKET_MSG_UNREGIST(SC_BATTLE_COIN_INFO);
    SOCKET_MSG_UNREGIST(SC_BATTLE_COIN_FIGHT);
}
bool MB_LayerTrainerTrove::init()
{
    CCNode* pNode = loadResource("res/pve_layer_gold.ccbi");
    if(pNode)
	{
		addChild(pNode);
		return true;
	}
	return false;
}

void MB_LayerTrainerTrove::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerTrainerTrove::onResetWnd()
{
    char str[32];
    int lastcount = MB_RoleData::getInstance()->getMoneyDungeonLimit() - m_pInterface->getFightCount();
    sprintf(str,"%d",lastcount);
    m_pTTFLastFightCount->setString(str);
    
    this->unscheduleAllSelectors();
  
    
    //开启计时器
    this->schedule(schedule_selector(MB_LayerTrainerTrove::updataTick),1.0f);
    
}

void MB_LayerTrainerTrove::onEnter()
{
    updataTick(0);
    MB_ResWindow::onEnter();
}

bool MB_LayerTrainerTrove::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLastFightCount",CCLabelTTF*,m_pTTFLastFightCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFFightTime",CCLabelTTF*,m_pTTFFightTime);
	return false;
}
SEL_MenuHandler MB_LayerTrainerTrove::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClick", MB_LayerTrainerTrove::onRuleClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerTrainerTrove::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onEasyFightClick",MB_LayerTrainerTrove::onEasyFightClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onNormalFightClick",MB_LayerTrainerTrove::onNormalFightClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onHardFightClick",MB_LayerTrainerTrove::onHardFightClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerTrainerTrove::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

	return NULL;
}

void MB_LayerTrainerTrove::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg) {
        case SC_BATTLE_COIN_INFO:
            dirty();
            break;
        case SC_BATTLE_COIN_FIGHT:
            dirty();
            break;
        default:
            break;
    }
}

void MB_LayerTrainerTrove::updataTick(float dt)
{
    if (MB_ClientSocket::getInstance()->getServerTime() > m_pInterface->getCoolDown())
    {
        m_pTTFFightTime->setColor(ccc3(255,255,255));
        m_pTTFFightTime->setString("00:00:00");
        this->unscheduleAllSelectors();
    }
    else
    {
        m_pTTFFightTime->setColor(ccc3(255,0,0));
        m_pTTFFightTime->setString(NSGameHelper::formatTimeStringHMS_colon(m_pInterface->getCoolDown()-MB_ClientSocket::getInstance()->getServerTime()));
    }
}
void MB_LayerTrainerTrove::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}

void MB_LayerTrainerTrove::onRuleClick(CCObject* pSender)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionTrainerTrove);
    if (pWnd)
    {
        pWnd->setShowRoleInfoPanel(true);
        pushWindow(pWnd);
    }
}

void MB_LayerTrainerTrove::onEasyFightClick(CCObject* pSender)
{
    if (!checkCanFight()) {
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pInterface->sendBattleCoinFight(kTypeFightEasy);
}
void MB_LayerTrainerTrove::onNormalFightClick(CCObject* pSender)
{
    if (!checkCanFight()) {
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pInterface->sendBattleCoinFight(kTypeFightNormal);
}
void MB_LayerTrainerTrove::onHardFightClick(CCObject* pSender)
{
    if (!checkCanFight()) {
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pInterface->sendBattleCoinFight(kTypeFightHard);
}

bool MB_LayerTrainerTrove::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_FunctionTrainerTroveInterface*>(pDataSource);
    if (m_pInterface) {
        m_pDataSource = pDataSource;
        onResetWnd();
    }
    return m_pInterface != NULL;
}
bool MB_LayerTrainerTrove::checkCanFight()
{
    if (MB_RoleData::getInstance()->getMoneyDungeonLimit() <= m_pInterface->getFightCount())
    {
        MB_Message::sharedMB_Message()->showMessage("挑战次数已满");
        return false;
    }
    if (MB_ClientSocket::getInstance()->getServerTime() < m_pInterface->getCoolDown())
    {
        MB_Message::sharedMB_Message()->showMessage("挑战冷却中");
        return false;
    }
    return true;

}
