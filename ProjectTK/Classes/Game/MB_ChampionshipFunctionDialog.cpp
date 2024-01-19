//
//  MB_ChampionshipFunctionDialog.cpp
//  ProjectPM
//
//  Created by chk on 14-3-24.
//
//

#include "MB_ChampionshipFunctionDialog.h"
#include "MB_Championship.h"
#include <stdio.h>
#include <time.h>
#include "MB_RoleData.h"
#include "MB_FunctionMgr.h"
#include "MB_MailList.h"
#include "MB_SceneGame.h"
#include "MB_MailData.h"
#include "MB_LayerShopMain.h"
#include "MB_JingjichangTZ.h"
#include "MB_JingjichangZB.h"
#include "MB_ShopMystery.h"
#include "MB_LayerRankJingjichang.h"
MB_ChampionshipFunctionDialog::MB_ChampionshipFunctionDialog()
{
    m_pInterface = NULL;
    m_pSelectedSpr = NULL;
    m_pMailNum      = NULL;
    m_pNodeMailNum  = NULL;
    m_currentPage   = kmPvpTable_Shop;
    m_bShowRoleInfoPanel = true;
}

MB_ChampionshipFunctionDialog::~MB_ChampionshipFunctionDialog()
{
    CC_SAFE_RELEASE(m_pSelectedSpr);
    CC_SAFE_RELEASE(m_pMailNum);
    CC_SAFE_RELEASE(m_pNodeMailNum);
}
bool MB_ChampionshipFunctionDialog::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_Championship*>(pDataSource);
    if (m_pInterface)
    {
        return true;
    }
    return false;
}
bool MB_ChampionshipFunctionDialog::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    m_pNode = CCNode::create();
    addChild(m_pNode);
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/pvp_layer_list.ccbi", this);
    this->addChild(pScene);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    onTZClick(NULL);
    scheduleUpdate();
    return true;
}


void MB_ChampionshipFunctionDialog::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_PvpAndPaiHang);
}

void MB_ChampionshipFunctionDialog::update(float dt)
{
    int unRead =  MailMgr->queryMailUnRead(kmMailsTable_Pvp);
    m_pNodeMailNum->setVisible(unRead);
    if(unRead > 0)
    {
        if (unRead>99) {
            m_pMailNum->setString("!");
        }else
        {
            char  temp[16];
            sprintf(temp, "%d", unRead );
            m_pMailNum->setString(temp);
        }
    }
}
void MB_ChampionshipFunctionDialog::onEnter()
{
    MB_ResWindow::onEnter();
    int unRead =  MailMgr->queryMailUnRead(kmMailsTable_Pvp);
    m_pNodeMailNum->setVisible(unRead);
    if(unRead > 0)
    {
        if (unRead>99) {
            m_pMailNum->setString("!");
        }else
        {
            char  temp[16];
            sprintf(temp, "%d", unRead );
            m_pMailNum->setString(temp);
        }
    }
}

bool MB_ChampionshipFunctionDialog::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "MailNum", CCLabelBMFont*, m_pMailNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMailNum", CCNode *, m_pNodeMailNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSelectedSpr", CCNode*, m_pSelectedSpr);
    
    return false;
}

SEL_MenuHandler MB_ChampionshipFunctionDialog::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char* pSelectorName)
{

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_ChampionshipFunctionDialog::onCloseClicked);
    return NULL;
}


SEL_CCControlHandler MB_ChampionshipFunctionDialog::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTZClick",MB_ChampionshipFunctionDialog::onTZClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onZBClick",MB_ChampionshipFunctionDialog::onZBClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPMClick",MB_ChampionshipFunctionDialog::onPMClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onJJSDClick",MB_ChampionshipFunctionDialog::onJJSDClick);
    return NULL;
}

void MB_ChampionshipFunctionDialog::onCloseClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}

void MB_ChampionshipFunctionDialog::onPMClick(CCObject* pSender)
{
    if (m_currentPage != kmPvpTable_Rank)
    {
        m_pSelectedSpr->setPosition(ccp(400,-2));
        m_currentPage = kmPvpTable_Rank;
        NSGameFunction::CCFunctionInterface* pInterface = NULL;
        MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionRanking, &pInterface);
        if (pInterface)
        {
            MB_LayerRankJingjichang* node = MB_LayerRankJingjichang::create();
            node->setDataSource(pInterface);
            m_pNode->removeAllChildren();
            m_pNode->addChild(node);
        }
    }
}
void MB_ChampionshipFunctionDialog::onJJSDClick(CCObject*)
{
    if (m_currentPage != kmPvpTable_Shop)
    {
        m_pSelectedSpr->setPosition(ccp(560,-2));
        TutorialTriggerComplete
        m_currentPage = kmPvpTable_Shop;
        MB_ShopMystery* node = MB_ShopMystery::create();
        node->onResetWnd();
        m_pNode->removeAllChildren();
        m_pNode->addChild(node);
    }
}
void MB_ChampionshipFunctionDialog::onTZClick(CCObject* pSender)
{
    if (m_currentPage != kmPvpTable_Pvp)
    {
        m_pSelectedSpr->setPosition(ccp(80,-2));
        m_currentPage = kmPvpTable_Pvp;
        MB_JingjichangTZ* layer = MB_JingjichangTZ::create();
        layer->setDataSource(m_pInterface);
        m_pNode->removeAllChildren();
        m_pNode->addChild(layer,0,123);
    }
    
    MB_LOG("onTZClick");
}
void MB_ChampionshipFunctionDialog::onZBClick(CCObject* pSender)
{
    if (m_currentPage != kmPvpTable_Report)
    {
        m_pSelectedSpr->setPosition(ccp(240,-2));
        m_currentPage = kmPvpTable_Report;
        MB_JingjichangZB* layer = MB_JingjichangZB::create();
        layer->setDataSource(m_pInterface);
        m_pNode->removeAllChildren();
        m_pNode->addChild(layer);
        MailMgr->sendhist_get_list(kmMailsTable_Pvp);
    }
    MB_LOG("onZBClick");
}
void MB_ChampionshipFunctionDialog::onResetWnd(void)
{
    CCNode* node = m_pNode->getChildByTag(123);
    if (node) {
        MB_JingjichangTZ* layer = (MB_JingjichangTZ*)node;
        layer->onResetWnd();
    }
}
