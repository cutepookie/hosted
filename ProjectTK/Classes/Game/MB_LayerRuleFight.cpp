//
//  MB_LayerRuleFight.cpp
//  ProjectMB
//
//  Create by chk on 12/1/2015.
//
//
#include "MB_LayerRuleFight.h"
#include "MB_FunctionMgr.h"
#include "MB_RuleFightInterface.h"
#include "MB_LayerFunctionRule.h"
#include "MB_NodeRuleRankUnit.h"

#define RULE_FIGHT_MAX_COUNT 30

MB_LayerRuleFight* MB_LayerRuleFight::create()
{
    MB_LayerRuleFight* pLayer = new MB_LayerRuleFight;
    if (pLayer && pLayer->init())
    {
        pLayer->autorelease();
        return pLayer;
    }
    
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

MB_LayerRuleFight::MB_LayerRuleFight()
{
    m_pZDLCSpr = NULL;
    m_pLabelScore	 = NULL;
    m_pLabelTitle	 = NULL;
    m_pLabelWinate	 = NULL;
    m_pLabelRecoverTime	 = NULL;
    m_pLabelLeftCount	 = NULL;
    m_pIconFrame = NULL;
    m_pBtnMainPage= NULL;
    m_pBtnMyRecord= NULL;
    m_pBtnRank= NULL;
    m_pBtnLastWeekRank= NULL;
    m_pNodeHistory	 = NULL;
    m_pBtnMainPage2 = NULL;
    m_pBtnMyRecord2 = NULL;
    m_pNodeMainPage = NULL;
    m_pNodeMyRecord = NULL;
    m_pMyRecordTableView = NULL;
    m_pHistoryScrollView = NULL;
    m_pBtnRank2 = NULL;
    m_pBtnLastWeekRank2 = NULL;
    m_pStar[0] = NULL;
    m_pStar[1] = NULL;
    m_pStar[2] = NULL;
    m_pStar[3] = NULL;
    m_pStar[4] = NULL;
    m_pRoleCard = NULL;
    m_pLabelFightPower = NULL;
    m_pLabelTargetServer = NULL;
    m_pLabelName = NULL;
    QUERY_FUNCTION_BEGIN(MB_RuleFightInterface, kFunctionRuleFight, pInterface)
    m_pInterface = pInterface;
    QUERY_FUNCTION_END
    
    SOCKET_MSG_REGIST(SC_RULE_LAST_RANK, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_RULE_FIGHT, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_RULE_INFO, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_RULE_RANK, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_HIST_NEW, MB_LayerRuleFight);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_RULETIMES, MB_LayerRuleFight);
    m_nCurrentPage = eNonePage;
    this->schedule(schedule_selector(MB_LayerRuleFight::tick));
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
}
MB_LayerRuleFight::~MB_LayerRuleFight()
{
    m_pInterface->cs_rule_leave();
    
    CC_SAFE_RELEASE_NULL(m_pZDLCSpr);
    CC_SAFE_RELEASE_NULL(m_pIconFrame);
    CC_SAFE_RELEASE_NULL(m_pLabelScore);
    CC_SAFE_RELEASE_NULL(m_pLabelTitle);
    CC_SAFE_RELEASE_NULL(m_pLabelWinate);
    CC_SAFE_RELEASE_NULL(m_pLabelRecoverTime);
    CC_SAFE_RELEASE_NULL(m_pLabelLeftCount);
    CC_SAFE_RELEASE_NULL(m_pNodeHistory);
    CC_SAFE_RELEASE_NULL(m_pBtnMainPage2);
    CC_SAFE_RELEASE_NULL(m_pBtnMyRecord2);
    CC_SAFE_RELEASE_NULL(m_pNodeMainPage);
    CC_SAFE_RELEASE_NULL(m_pNodeMyRecord);
    CC_SAFE_RELEASE_NULL(m_pBtnRank2);
    CC_SAFE_RELEASE_NULL(m_pBtnLastWeekRank2);
    
    CC_SAFE_RELEASE_NULL(m_pBtnMainPage);
    CC_SAFE_RELEASE_NULL(m_pBtnMyRecord);
    CC_SAFE_RELEASE_NULL(m_pBtnRank);
    CC_SAFE_RELEASE_NULL(m_pBtnLastWeekRank);
    
    CC_SAFE_RELEASE(m_pMyRecordTableView);
    CC_SAFE_RELEASE(m_pHistoryScrollView);
    CC_SAFE_RELEASE_NULL(m_pStar[0]);
    CC_SAFE_RELEASE_NULL(m_pStar[1]);
    CC_SAFE_RELEASE_NULL(m_pStar[2]);
    CC_SAFE_RELEASE_NULL(m_pStar[3]);
    CC_SAFE_RELEASE_NULL(m_pStar[4]);
    CC_SAFE_RELEASE_NULL(m_pRoleCard);
    CC_SAFE_RELEASE_NULL(m_pLabelFightPower);
    CC_SAFE_RELEASE_NULL(m_pLabelTargetServer);
    CC_SAFE_RELEASE_NULL(m_pLabelName);
    SOCKET_MSG_UNREGIST(SC_RULE_LAST_RANK);
    SOCKET_MSG_UNREGIST(SC_RULE_FIGHT);
    SOCKET_MSG_UNREGIST(SC_RULE_INFO);
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
    SOCKET_MSG_UNREGIST(SC_RULE_RANK);
    SOCKET_MSG_UNREGIST(SC_HIST_NEW);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_RULETIMES);
}
bool MB_LayerRuleFight::init()
{
    CCNode* pNode = loadResource("res/worldwar_layer_list.ccbi");
    if(pNode)
	{
		addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pNodeMyRecord);
        for (int i = 0; i < 5; i++)
        {
            starPt[i] = m_pStar[i]->getPosition();
        }
		return true;
	}
	return false;
}

void MB_LayerRuleFight::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerRuleFight::showPage(ePage e,bool force)
{
    if (!force && m_nCurrentPage == e)return;
    
    m_pBtnMainPage2->setVisible(true);
    m_pBtnMyRecord2->setVisible(true);
    m_pBtnRank2->setVisible(true);
    m_pBtnLastWeekRank2->setVisible(true);
    m_pBtnMainPage->setVisible(false);
    m_pBtnMyRecord->setVisible(false);
    m_pBtnRank->setVisible(false);
    m_pBtnLastWeekRank->setVisible(false);
    
    m_nCurrentPage = e;
    
    if (m_pMyRecordTableView && m_pMyRecordTableView->getParent())m_pMyRecordTableView->removeFromParent();
    if (m_pHistoryScrollView && m_pHistoryScrollView->getParent())m_pHistoryScrollView->removeFromParent();
    m_pNodeMyRecord->setPositionY(869);
    if (m_pHistoryScrollView!=NULL) {
        m_pHistoryScrollView->setViewSize(CCSize(640,600));
    }
    switch (m_nCurrentPage)
    {
        case eMainPage:
            m_pNodeMainPage->setVisible(true);
            m_pNodeMyRecord->setVisible(false);
            m_pBtnMainPage2->setVisible(false);
            m_pBtnMainPage->setVisible(true);
            m_pZDLCSpr->setVisible(true);
            m_pNodeMyRecord->setPositionY(360);
            if (m_pHistoryScrollView!=NULL) {
                m_pHistoryScrollView->setViewSize(CCSize(640,165));
            }
            updateMainInfo();
            break;
        case eMyRecordPage:
            m_pNodeMainPage->setVisible(false);
            m_pNodeMyRecord->setVisible(true);
            m_pBtnMyRecord2->setVisible(false);
            m_pBtnMyRecord->setVisible(true);
            m_pZDLCSpr->setVisible(false);
            updateRankPage();
            break;
        case eRankPage:
            m_pNodeMainPage->setVisible(false);
            m_pNodeMyRecord->setVisible(true);
            m_pBtnRank2->setVisible(false);
            m_pBtnRank->setVisible(true);
            m_pZDLCSpr->setVisible(false);
            updateRankPage();
            break;
        case eLastWeekRankPage:
            m_pNodeMainPage->setVisible(false);
            m_pNodeMyRecord->setVisible(true);
            m_pBtnLastWeekRank2->setVisible(false);
            m_pBtnLastWeekRank->setVisible(true);
            m_pZDLCSpr->setVisible(false);
            updateRankPage();
            break;
        default:
            break;
    }
}

void MB_LayerRuleFight::updateRankPage()
{
    if (m_pMyRecordTableView == NULL)
    {
        m_pMyRecordTableView = CCTableView::create(m_pInterface->getMyRecordDataSource(), m_pNodeMyRecord->getContentSize());
        m_pMyRecordTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pMyRecordTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pNodeMyRecord->addChild(m_pMyRecordTableView);
        CC_SAFE_RETAIN(m_pMyRecordTableView);
    }
    else
    {
        m_pNodeMyRecord->addChild(m_pMyRecordTableView);
    }

    switch (m_nCurrentPage)
    {
        case eMyRecordPage:
            m_pMyRecordTableView->setDataSource(m_pInterface->getMyRecordDataSource());
            m_pMyRecordTableView->reloadData();
            break;
        case eRankPage:
            m_pMyRecordTableView->setDataSource(m_pInterface->getRankDataSource());
            m_pMyRecordTableView->reloadData();
            break;
        case eLastWeekRankPage:
            m_pMyRecordTableView->setDataSource(m_pInterface->getLastWeekRankDataSource());
            m_pMyRecordTableView->reloadData();
            break;
        default:
            break;
    }
}

void MB_LayerRuleFight::updateMainInfo()
{
    if (m_pInterface)
    {
        char buff[30] = {0};
        sprintf(buff, "%d",m_pInterface->getRuleInfo()->getScore());
        m_pLabelScore->setString(buff);
        
        MB_RuleFightConfig* pCfg = MB_RuleConfigMgr::getInstance()->queryByScore(m_pInterface->getRuleInfo()->getScore());
        
        if(pCfg)
        {
            m_pLabelTitle->setString(pCfg->getTitle().c_str());
            
            for (int i = 0; i < 5; i++)
            {
                m_pStar[i]->setPosition(starPt[i]);
            }
            int n = 5 *(float)(m_pInterface->getRuleInfo()->getScore() - pCfg->getMinScore())/(float)(pCfg->getMaxScore() - pCfg->getMinScore())+1;
            NSGameHelper::centerStars(m_pStar, 5, n);
        }
        else
        {
            m_pLabelTitle->setString("");
        }
        

        string str = "";
        sprintf(buff, "%d战           ",m_pInterface->getRuleInfo()->getFightTimes());
        str+=buff;
        sprintf(buff, "%d连胜            ",m_pInterface->getRuleInfo()->getWinConTimes());
        str+=buff;
        if(m_pInterface->getRuleInfo()->getFightTimes() == 0)
        {
            str+="0%胜率";
        }
        else
        {
            sprintf(buff, "%d%%胜率",int((float)m_pInterface->getRuleInfo()->getWinTimes()/(float)m_pInterface->getRuleInfo()->getFightTimes()*100));
            str+=buff;
        }
        m_pLabelWinate->setString(str.c_str());
        
        sprintf(buff, "%d/%d",m_pInterface->getRuleTimes(),RULE_FIGHT_MAX_COUNT);
        m_pLabelLeftCount->setString(buff);
        int realTime =  0;
        if(   MB_RoleData::getInstance()->getDiscoveryTimes() <
           MB_RoleData::getInstance()->getDiscoveryTimesMax())
        {
            realTime = m_pInterface->getNextRuleTime() - MB_ClientSocket::getInstance()->getServerTime();
        }
        char databuf[64] = {};
        if (realTime < 0)
        {
            realTime = 0;
        }
        sprintf(databuf, "%02d:%02d",realTime/60,realTime%60);
        m_pLabelRecoverTime->setString(databuf);

        if(m_pRoleCard)NSGameHelper::setRoleIcon(m_pRoleCard, m_pInterface->getRuleInfo()->getTarFighter()->getIsMale(), m_pInterface->getRuleInfo()->getTarFighter()->getHead(),m_pInterface->getRuleInfo()->getTarFighter()->getTitle(),m_pIconFrame);
        
        if(m_pLabelFightPower)m_pLabelFightPower->setString(CCString::createWithFormat("%lld",m_pInterface->getRuleInfo()->getTarFighter()->getFightPower())->getCString());
        
        ServerList* pList = MB_ServerList::getInstance()->getServerListByID(NSGameHelper::getServerByRoleID(m_pInterface->getRuleInfo()->getTarFighter()->getRoleID()));
        if(pList && m_pLabelTargetServer)m_pLabelTargetServer->setString(pList->name.c_str());
        
        if(m_pLabelName)m_pLabelName->setString(m_pInterface->getRuleInfo()->getTarFighter()->getRoleName().c_str());
    }
    
    if (m_pHistoryScrollView == NULL)
    {
        m_pHistoryScrollView = CCScrollView::create(m_pNodeHistory->getContentSize());
        m_pHistoryScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pNodeHistory->addChild(m_pHistoryScrollView);
        CC_SAFE_RETAIN(m_pHistoryScrollView);
    }
    else
    {
        m_pNodeHistory->addChild(m_pHistoryScrollView);
    }

    m_pHistoryScrollView->getContainer()->removeAllChildren();
    CCObject* pObj = NULL;
    float fY = 0.0f;
    CCARRAY_FOREACH(m_pInterface->getRuleInfo()->getList(), pObj)
    {
        Hist* pTemp = (Hist*)pObj;
        MB_NodeHistoryUnit* pUnit = pTemp->getUnit();
        m_pHistoryScrollView->addChild(pUnit);
        pUnit->setPosition(ccp(0,fY));
        fY += pUnit->getShowSize().height;
    }
    
    
    if(fY < m_pNodeHistory->getContentSize().height)
    {
        fY = m_pNodeHistory->getContentSize().height;
    }
    m_pHistoryScrollView->setContentSize(CCSizeMake(m_pNodeHistory->getContentSize().width, fY));
    if(m_pNodeHistory->getContentSize().height > m_pNodeHistory->getContentSize().height)
    {
        m_pHistoryScrollView->setContentOffset(ccp(0, m_pNodeHistory->getContentSize().height));
    }
    else
    {
        m_pHistoryScrollView->setContentOffset(ccp(0, m_pNodeHistory->getContentSize().height - m_pNodeHistory->getContentSize().height));
    }
}

void MB_LayerRuleFight::onResetWnd()
{
}

void MB_LayerRuleFight::tick(float dt)
{
    if(m_pInterface->getRuleTimes() == RULE_FIGHT_MAX_COUNT)
    {
        m_pLabelRecoverTime->setString("00:00");
    }
    else
    {
        int realTime =  0;
        if(   MB_RoleData::getInstance()->getDiscoveryTimes() <
           MB_RoleData::getInstance()->getDiscoveryTimesMax())
        {
            realTime = m_pInterface->getNextRuleTime() - MB_ClientSocket::getInstance()->getServerTime();
        }
        char databuf[64] = {};
        if (realTime < 0)
        {
            realTime = 0;
        }
        sprintf(databuf, "%02d:%02d",realTime/60,realTime%60);
        m_pLabelRecoverTime->setString(databuf);
    }
}

bool MB_LayerRuleFight::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pZDLCSpr",CCNode*,m_pZDLCSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelScore",CCLabelBMFont*,m_pLabelScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelTitle",CCLabelBMFont*,m_pLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelWinate",CCLabelBMFont*,m_pLabelWinate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelRecoverTime",CCLabelBMFont*,m_pLabelRecoverTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelLeftCount",CCLabelBMFont*,m_pLabelLeftCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeHistory",CCNode*,m_pNodeHistory);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnMainPage2",CCMenuItemImage*,m_pBtnMainPage2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnMyRecord2",CCMenuItemImage*,m_pBtnMyRecord2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnRank2",CCMenuItemImage*,m_pBtnRank2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnLastWeekRank2",CCMenuItemImage*,m_pBtnLastWeekRank2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnMainPage",CCNode*,m_pBtnMainPage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnMyRecord",CCNode*,m_pBtnMyRecord);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnRank",CCNode*,m_pBtnRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnLastWeekRank",CCNode*,m_pBtnLastWeekRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMainPage",CCNode*,m_pNodeMainPage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMyRecord",CCNode*,m_pNodeMyRecord);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleCard",CCSprite*,m_pRoleCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pIconFrame",CCSprite*,m_pIconFrame);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelFightPower",CCLabelBMFont*,m_pLabelFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelTargetServer",CCLabelTTF*,m_pLabelTargetServer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelName",CCLabelTTF*,m_pLabelName);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar0",CCSprite*,m_pStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar1",CCSprite*,m_pStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar2",CCSprite*,m_pStar[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar3",CCSprite*,m_pStar[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar4",CCSprite*,m_pStar[4]);
    
	return false;
}
SEL_MenuHandler MB_LayerRuleFight::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerRuleFight::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onMainPageClicked",MB_LayerRuleFight::onMainPageClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onMyRecordClicked",MB_LayerRuleFight::onMyRecordClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onScoreRankClicked",MB_LayerRuleFight::onScoreRankClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClicked",MB_LayerRuleFight::onRuleClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onLastWeakRankClicked",MB_LayerRuleFight::onLastWeakRankClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFightClicked",MB_LayerRuleFight::onFightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onIconClicked",MB_LayerRuleFight::onIconClicked);
	return NULL;
}

void MB_LayerRuleFight::onIconClicked(CCObject*)
{
    uint64_t roleid = m_pInterface->getRuleInfo()->getTarFighter()->getRoleID();
    sendpet_view_other(roleid,0);
}

void MB_LayerRuleFight::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_RULE_LAST_RANK:
        {
            showPage(eLastWeekRankPage);
            break;
        }
        case SC_RULE_RANK:
        {
            showPage(eRankPage);
            break;
        }
        case SC_ROLE_BUY_ENERGY:
        case SC_RULE_FIGHT:
        case SC_RULE_INFO:
        case SC_HIST_NEW:
        case SC_ROLE_UPDATE_RULETIMES:
        {
            showPage(m_nCurrentPage,true);
        }
            break;
        default:
            break;
    }
}

SEL_CCControlHandler MB_LayerRuleFight::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerRuleFight::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
void MB_LayerRuleFight::onMainPageClicked(CCObject* pSender)
{
    showPage(eMainPage);
}
void MB_LayerRuleFight::onMyRecordClicked(CCObject* pSender)
{
    showPage(eMyRecordPage);
}
void MB_LayerRuleFight::onScoreRankClicked(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",5);
    m_pInterface->cs_rule_rank();
}

void MB_LayerRuleFight::onRuleClicked(CCObject* pSender)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionRuleFight);
    pWnd->setShowRoleInfoPanel(true);
    if (pWnd)pushWindow(pWnd);
}
void MB_LayerRuleFight::onLastWeakRankClicked(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",5);
    m_pInterface->cs_rule_last_rank();
}
void MB_LayerRuleFight::onFightClicked(CCObject* pSender)
{
    if(m_pInterface->getRuleTimes())
    {
        MB_Message::sharedMB_Message()->showMessage("",5);
        m_pInterface->cs_rule_fight();
    }
    else
    {
        char databuf[100];
        sprintf(databuf, "是否需要花费%d宝石回复%d点挑战次数？",MB_RoleData::getInstance()->getNeedGoldByTime(kBuyTimesTypeRuleFight),MB_RoleData::getInstance()->getRuleFightRecoveryTimes());
        MB_ResWindow* pWnd = MB_Message::sharedMB_Message()->showMessage("购买挑战次数",databuf,"确定","取消",this,menu_selector(MB_LayerRuleFight::goBuyRuleFightTimes),NULL);
        pWnd->setTag(MESSAGE_TAG+1);
    }
}

void MB_LayerRuleFight::goBuyRuleFightTimes()
{
    MB_RoleData::getInstance()->goBuyRuleFight(this);
}

void MB_LayerRuleFight::onReplayClicked(uint64_t uid)
{
    MB_Message::sharedMB_Message()->showMessage("", 5);
    m_pInterface->cs_hist_replay(uid);
}

void MB_LayerRuleFight::sendpet_view_other(uint32_t roleid,uint16_t serverid)
{
    if(roleid == MB_RoleData::getInstance()->getUID())return;
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_TeamData::getInstance()->sendpet_view_other(roleid,serverid);
}
