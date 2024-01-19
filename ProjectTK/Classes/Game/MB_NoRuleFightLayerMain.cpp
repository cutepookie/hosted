//
//  MB_NoRuleFightLayerMain.cpp
//  ProjectMB
//
//  Create by chk on 27/2/2015.
//
//
#include "MB_NoRuleFightLayerMain.h"
#include "MB_FunctionNoRuleFight.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerFunctionRule.h"
MB_NoRuleFightLayerMain::MB_NoRuleFightLayerMain()
{
    m_pLabelNoruleCount	 = NULL;
    m_pNodeSign	 = NULL;
    m_pBtSign	 = NULL;
    m_pNodeFight	 = NULL;
    m_pBtFight	 = NULL;
    m_pTeam0Score	 = NULL;
    m_pTeam1Score	 = NULL;
    m_pSelfScore	 = NULL;
    m_pLabelTime     = NULL;
    m_pLabelWinCount0 = NULL;
    m_pLabelWinCount1 = NULL;
    m_pNodeSelfAt0 = NULL;
    m_pNodeSelfAt1 = NULL;
    m_nLastFightTime = 0;
    m_bCanCsMeleeInfo = true;
    m_bShowRoleInfoPanel = true;
    m_pDJSSpr = NULL;

    
    SOCKET_MSG_REGIST(SC_MELEE_INFO,MB_NoRuleFightLayerMain);
    SOCKET_MSG_REGIST(SC_MELEE_SIGN,MB_NoRuleFightLayerMain);
    SOCKET_MSG_REGIST(SC_MELEE_FIGHT,MB_NoRuleFightLayerMain);
}
MB_NoRuleFightLayerMain::~MB_NoRuleFightLayerMain()
{
    this->unschedule(schedule_selector(MB_NoRuleFightLayerMain::tick));
    CC_SAFE_RELEASE_NULL(m_pLabelNoruleCount);
    CC_SAFE_RELEASE_NULL(m_pNodeSign);
    CC_SAFE_RELEASE_NULL(m_pBtSign);
    CC_SAFE_RELEASE_NULL(m_pNodeFight);
    CC_SAFE_RELEASE_NULL(m_pBtFight);
    CC_SAFE_RELEASE_NULL(m_pTeam0Score);
    CC_SAFE_RELEASE_NULL(m_pTeam1Score);
    CC_SAFE_RELEASE_NULL(m_pLabelTime);
    CC_SAFE_RELEASE_NULL(m_pNodeSelfAt0);
    CC_SAFE_RELEASE_NULL(m_pNodeSelfAt1);
    CC_SAFE_RELEASE_NULL(m_pSelfScore);
    CC_SAFE_RELEASE_NULL(m_pLabelWinCount0);
    CC_SAFE_RELEASE_NULL(m_pLabelWinCount1);
    CC_SAFE_RELEASE_NULL(m_pDJSSpr);
    
    SOCKET_MSG_UNREGIST(SC_MELEE_INFO);
    SOCKET_MSG_UNREGIST(SC_MELEE_SIGN);
    SOCKET_MSG_UNREGIST(SC_MELEE_FIGHT);
}

bool MB_NoRuleFightLayerMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pFunction = dynamic_cast<MB_FunctionNoRuleFight*>(pDataSource);
    m_pDataSource = pDataSource;
    return m_pFunction != NULL;
}

bool MB_NoRuleFightLayerMain::init()
{
    CCNode* pNode = loadResource("res/norule_main_fight.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_pNodeFight->setVisible(false);
        m_pNodeSign->setVisible(false);
        
        
        this->schedule(schedule_selector(MB_NoRuleFightLayerMain::tick));
		return true;
	}
	return false;
}

void MB_NoRuleFightLayerMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_NoRuleFightLayerMain::onResetWnd()
{
    if(m_pFunction)
    {
        m_pNodeFight->setVisible(m_pFunction->getState() == NORULE_FIGHT_BEGIN);
        m_pNodeSign->setVisible(m_pFunction->getState() == NORULE_NOT_SIGN);
        m_pNodeSelfAt0->setVisible(m_pFunction->getNoRuleInfo()->getSelfTeam() == 1);
        m_pNodeSelfAt1->setVisible(m_pFunction->getNoRuleInfo()->getSelfTeam() == 2);
        m_pLabelNoruleCount->setString(CCString::createWithFormat("%d",m_pFunction->getNoRuleInfo()->getLeftTimes())->getCString());
        m_pSelfScore->setString(CCString::createWithFormat("%d",m_pFunction->getNoRuleInfo()->getSelfScore())->getCString());
        m_pTeam0Score->setString(CCString::createWithFormat("%d",m_pFunction->getNoRuleInfo()->getTeam0Score())->getCString());
        m_pTeam1Score->setString(CCString::createWithFormat("%d",m_pFunction->getNoRuleInfo()->getTeam1Score())->getCString());
        m_pLabelWinCount0->setString(CCString::createWithFormat("%d",m_pFunction->getNoRuleInfo()->getWinCount())->getCString());
        m_pLabelWinCount1->setString(m_pLabelWinCount0->getString());
    }
}

void MB_NoRuleFightLayerMain::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_MELEE_INFO:
            m_bCanCsMeleeInfo = true;
            onResetWnd();
            break;
        case SC_MELEE_SIGN:
            onResetWnd();
            break;
        case SC_MELEE_FIGHT:
        {
            uint8_t result = 0;
            pRecv->readU8(&result);//0成功,1等级不够，2功能未开放,3等待复活中 4 未报名,5 没有找到对手,6 战斗结果异常
            if(result == 0)
            {
                onResetWnd();
            }
            else
            {
                m_nLastFightTime = 0;
            }
        }
            break;
        default:
            break;
    }
}


void MB_NoRuleFightLayerMain::tick(float dt)
{
    static float fTemp = 0;
    fTemp += dt;
    if(fTemp >= 1)
    {
        fTemp = 0;
        
        if(m_pFunction)
        {
            int time = m_pFunction->getNoRuleInfo()->getCountdown() - MB_ClientSocket::getInstance()->getServerTime();
            if(time <= 0 && m_bCanCsMeleeInfo)
            {
                m_bCanCsMeleeInfo = false;
                m_pFunction->cs_melee_info();
                return;
            }
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist");
            switch (m_pFunction->getState())
            {
                case NORULE_NOT_SIGN:
                {
                    //                    CCString* str = CCString::createWithFormat("报名倒计时:%s",NSGameHelper::formatTimeStringDHMS(time));
                    m_pLabelTime->setString(NSGameHelper::formatTimeStringHMS_colon(time));
                    m_pDJSSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_txt_baoming_daojishi.png"));
                }
                    break;
                case NORULE_SIGNED:
                {
                    //                    CCString* str = CCString::createWithFormat("战场开始倒计时:%s",NSGameHelper::formatTimeStringDHMS(time));
                    m_pLabelTime->setString(NSGameHelper::formatTimeStringHMS_colon(time));
                    m_pDJSSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_txt_baoming_daojishi.png"));
                }
                    break;
                case NORULE_FIGHT_BEGIN:
                {
                    //                    CCString* str = CCString::createWithFormat("战场结束倒计时:%s",NSGameHelper::formatTimeStringDHMS(time));
                    m_pLabelTime->setString(NSGameHelper::formatTimeStringHMS_colon(time));
                    m_pDJSSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_txt_baoming_daojishi.png"));
                }
                    break;
                default:
                    break;
            }
        }
        
    }
    
}
bool MB_NoRuleFightLayerMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelNoruleCount",CCLabelBMFont*,m_pLabelNoruleCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSign",CCNode*,m_pNodeSign);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtSign",CCMenuItemImage*,m_pBtSign);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeFight",CCNode*,m_pNodeFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtFight",CCMenuItemImage*,m_pBtFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTeam0Score",CCLabelBMFont*,m_pTeam0Score);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTeam1Score",CCLabelBMFont*,m_pTeam1Score);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTime", CCLabelBMFont*, m_pLabelTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelfAt0", CCNode*, m_pNodeSelfAt0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSelfAt1", CCNode*, m_pNodeSelfAt1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSelfScore",CCLabelBMFont*,m_pSelfScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelWinCount0",CCLabelBMFont*,m_pLabelWinCount0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelWinCount1",CCLabelBMFont*,m_pLabelWinCount1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDJSSpr",CCSprite*,m_pDJSSpr);
    
	return false;
}
SEL_MenuHandler MB_NoRuleFightLayerMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_NoRuleFightLayerMain::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onSignClicked",MB_NoRuleFightLayerMain::onSignClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFightClicked",MB_NoRuleFightLayerMain::onFightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClicked",MB_NoRuleFightLayerMain::onRuleClicked);
	return NULL;
}
SEL_CCControlHandler MB_NoRuleFightLayerMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

	return NULL;
}
void MB_NoRuleFightLayerMain::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
void MB_NoRuleFightLayerMain::onSignClicked(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pFunction->cs_melee_sign();
}
void MB_NoRuleFightLayerMain::onFightClicked(CCObject* pSender)
{
    int n = MB_ClientSocket::getInstance()->getServerTime() - m_nLastFightTime;
    if(n < 3)
    {
        MB_Message::sharedMB_Message()->showMessage("休息一会儿");
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    m_pFunction->cs_melee_fight();
    m_nLastFightTime = MB_ClientSocket::getInstance()->getServerTime();
}
void MB_NoRuleFightLayerMain::onRuleClicked(CCObject* pSender)
{
    MB_LayerFunctionRule* pLayer = MB_LayerFunctionRule::create(m_pFunction->getFunctionType());
    if(pLayer)
    {
        pLayer->setShowRoleInfoPanel(true);
        pushWindow(pLayer);
    }
}
