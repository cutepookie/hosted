//
//  MB_LayerRankJingjichang.cpp
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#include "MB_LayerRankJingjichang.h"
#include "MB_RankingDataSource.h"
#include "MB_FunctionRanking.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionRankingProtocol.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_AbsolvedInterface.h"
#include "MB_ServerRewardData.h"
#include "MB_LayerEqCompare.h"

MB_LayerRankJingjichang::MB_LayerRankJingjichang()
{
    m_pContainer = NULL;
    m_pTableView = NULL;
    m_pInterface = NULL;
    m_bShowRoleInfoPanel = true;
    rds = new MB_RankDataSourceArena;
    SOCKET_MSG_REGIST(RECV_RANK_INFO, MB_LayerRankJingjichang);
}
MB_LayerRankJingjichang::~MB_LayerRankJingjichang()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    SOCKET_MSG_UNREGIST(RECV_RANK_INFO);
}
bool MB_LayerRankJingjichang::init()
{
    CCNode* pNode = loadResource("res/pvp_layer_list_PH.ccbi");
    if(pNode)
    {
        addChild(pNode);
        onInitialized();

        return true;
    }
    return false;
}

void MB_LayerRankJingjichang::onInitialized()
{
    NSGameHelper::adjustScrollNode(m_pContainer);
    m_pTableView = CCTableView::create(rds, m_pContainer->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pContainer->addChild(m_pTableView);
    m_pTableView->setContentOffset(ccp(0, m_pTableView->getContainer()->getContentSize().height-m_pContainer->getContentSize().height));
    m_pInterface->send_rank_arena();
}

void MB_LayerRankJingjichang::onResetWnd()
{

}
bool MB_LayerRankJingjichang::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pContainer", CCNode *, m_pContainer);
    return false;
}
SEL_MenuHandler MB_LayerRankJingjichang::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerRankJingjichang::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerRankJingjichang::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


void MB_LayerRankJingjichang::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}


void MB_LayerRankJingjichang::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == RECV_RANK_INFO)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        uint8_t type = 0;
        pRecv->readU8(&type);
        resetData();
    }
}
void MB_LayerRankJingjichang::resetData()
{
    rds->setDataArray(m_pInterface->getArrayDataByType(2));
    m_pTableView->setDataSource(rds);
    m_pTableView->reloadData();
    m_pTableView->setContentOffset(ccp(0, -m_pTableView->getContainer()->getContentSize().height+m_pContainer->getContentSize().height));
}
bool MB_LayerRankJingjichang::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_FunctionRanking*>(pDataSource);
    return m_pInterface!=NULL;
}


