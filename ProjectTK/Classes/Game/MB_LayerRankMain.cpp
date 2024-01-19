//
//  MB_LayerRankMain.cpp
//  ProjectMB
//
//  Create by wenyong on 24/12/2014.
//
//
#include "MB_LayerRankMain.h"
#include "MB_RankingDataSource.h"
#include "MB_FunctionRanking.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionRankingProtocol.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_AbsolvedInterface.h"
#include "MB_ServerRewardData.h"
#include "MB_LayerEqCompare.h"

MB_LayerRankMain::MB_LayerRankMain()
{
    m_pSelectedSpr = NULL;
    m_pNodePower	 = NULL;
    m_pNodePowerValue	 = NULL;
    m_pNodePowerRank	 = NULL;
    m_pNodeLevel	 = NULL;
    m_pNodeLevelPower	 = NULL;
    m_pNodeLvelRank	 = NULL;
    m_pNodeAbsolved	 = NULL;
    m_pNodeAbsolvedChapter	 = NULL;
    m_pNodeAbsolvedDungeon	 = NULL;
    m_pNodeAbsolvedRank	 = NULL;
    m_pContainer	 = NULL;
    m_pTableView = NULL;
    m_nRankType = kRankDefault;
    m_pInterface = NULL;
    m_bShowRoleInfoPanel = true;
    m_pDataSource[0] = new MB_RankDataSourceLevel;
    m_pDataSource[1] = new MB_RankDataSourcePower;
    m_pDataSource[2] = new MB_RankDataSourceArena;
    m_pDataSource[3] = new MB_RankDataSourceAbsolved;
    SOCKET_MSG_REGIST(RECV_RANK_INFO, MB_LayerRankMain);
}
MB_LayerRankMain::~MB_LayerRankMain()
{
    CC_SAFE_RELEASE_NULL(m_pSelectedSpr);
    CC_SAFE_RELEASE_NULL(m_pNodePower);
    CC_SAFE_RELEASE_NULL(m_pNodePowerValue);
    CC_SAFE_RELEASE_NULL(m_pNodePowerRank);
    CC_SAFE_RELEASE_NULL(m_pNodeLevel);
    CC_SAFE_RELEASE_NULL(m_pNodeLevelPower);
    CC_SAFE_RELEASE_NULL(m_pNodeLvelRank);
    CC_SAFE_RELEASE_NULL(m_pNodeAbsolved);
    CC_SAFE_RELEASE_NULL(m_pNodeAbsolvedChapter);
    CC_SAFE_RELEASE_NULL(m_pNodeAbsolvedDungeon);
    CC_SAFE_RELEASE_NULL(m_pNodeAbsolvedRank);
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_DELETE(m_pDataSource[0]);
    CC_SAFE_DELETE(m_pDataSource[1]);
    CC_SAFE_DELETE(m_pDataSource[2]);
    CC_SAFE_DELETE(m_pDataSource[3]);
    SOCKET_MSG_UNREGIST(RECV_RANK_INFO);
}
bool MB_LayerRankMain::init()
{
    CCNode* pNode = loadResource("res/rank_layer_all.ccbi");
    if(pNode)
    {
        addChild(pNode);
        onInitialized();
        
        return true;
    }
    return false;
}

void MB_LayerRankMain::onExit()
{
    PlayBackGround(ksSound_YeShiJie);
    MB_FunctionMainWnd::onExit();
}

void MB_LayerRankMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_PvpAndPaiHang);
}

void MB_LayerRankMain::onInitialized()
{
    NSGameHelper::adjustScrollNode(m_pContainer);
    m_pTableView = CCTableView::create(m_pDataSource[m_nRankType], m_pContainer->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pContainer->addChild(m_pTableView);
    m_pTableView->setContentOffset(ccp(0, m_pTableView->getContainer()->getContentSize().height-m_pContainer->getContentSize().height));
    onFriendClicked(this);
}

bool MB_LayerRankMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePower",CCNode*,m_pNodePower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePowerValue",CCLabelBMFont*,m_pNodePowerValue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePowerRank",CCLabelTTF*,m_pNodePowerRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevel",CCNode*,m_pNodeLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLevelPower",CCLabelBMFont*,m_pNodeLevelPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeLvelRank",CCLabelTTF*,m_pNodeLvelRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeAbsolved",CCNode*,m_pNodeAbsolved);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeAbsolvedChapter",CCLabelTTF*,m_pNodeAbsolvedChapter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeAbsolvedDungeon",CCLabelTTF*,m_pNodeAbsolvedDungeon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeAbsolvedRank",CCLabelTTF*,m_pNodeAbsolvedRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSelectedSpr",CCNode*,m_pSelectedSpr);
    
    return false;
}
SEL_MenuHandler MB_LayerRankMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerRankMain::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerRankMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onFriendClicked",MB_LayerRankMain::onFriendClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onEnergyClicked",MB_LayerRankMain::onEnergyClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onAddListClicked",MB_LayerRankMain::onAddListClicked);
    return NULL;
}

void MB_LayerRankMain::onFriendClicked(CCObject* pSender)
{
    if (m_nRankType != kRankPower) {
        m_pSelectedSpr->setPosition(ccp(107.5f,-1.8f));
        m_nRankType = kRankPower;
        resetMenuStatus();
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pInterface->send_rank_power();
    }
}

void MB_LayerRankMain::onEnergyClicked(CCObject* pSender)
{
    if (m_nRankType != kRankLevel) {
        m_pSelectedSpr->setPosition(ccp(323.5f,-1.8f));
        m_nRankType = kRankLevel;
        resetMenuStatus();
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pInterface->send_rank_level();
    }
}

void MB_LayerRankMain::onAddListClicked(CCObject* pSender)
{
    if (m_nRankType != kRankAbsolved) {
        m_pSelectedSpr->setPosition(ccp(532.5f,-1.8f));
        m_nRankType = kRankAbsolved;
        resetMenuStatus();
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pInterface->send_rank_absolved();
    }
}


void MB_LayerRankMain::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}

void MB_LayerRankMain::resetMenuStatus()
{
    m_pNodePower->setVisible(m_nRankType==kRankPower);
    m_pNodeLevel->setVisible(m_nRankType==kRankLevel);
    m_pNodeAbsolved->setVisible(m_nRankType==kRankAbsolved);
}

void MB_LayerRankMain::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == RECV_RANK_INFO)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        uint8_t type = 0;
        pRecv->readU8(&type);
        m_nRankType = type-1;
        resetData();
    }
}

bool MB_LayerRankMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_FunctionRanking*>(pDataSource);
    return m_pInterface!=NULL;
}

void MB_LayerRankMain::resetData()
{
    if (m_nRankType >= 0 && m_nRankType < 4)
    {
        m_pDataSource[m_nRankType]->setDataArray(m_pInterface->getArrayDataByType(m_nRankType));
        m_pTableView->setDataSource(m_pDataSource[m_nRankType]);
        m_pTableView->reloadData();
        m_pTableView->setContentOffset(ccp(0, -m_pTableView->getContainer()->getContentSize().height+m_pContainer->getContentSize().height));
    }
    char buf[128] = {};
    uint8_t rank = m_pInterface->getOwnRank(m_nRankType);
    if (m_nRankType == kRankLevel)
    {
        sprintf(buf, "%d",MB_RoleData::getInstance()->getLevel());
        m_pNodeLevelPower->setString(buf);
        if (rank==0)
        {
            m_pNodeLvelRank->setString("未上榜");
        }
        else
        {
            sprintf(buf, "%d",rank);
            m_pNodeLvelRank->setString(buf);
        }
    }
    else if (m_nRankType == kRankPower)
    {
        sprintf(buf, "%lld",MB_TeamData::getInstance()->getFightPower());
        m_pNodePowerValue->setString(buf);
        if (rank==0)
        {
            m_pNodePowerRank->setString("未上榜");
        }
        else
        {
            sprintf(buf, "%d",rank);
            m_pNodePowerRank->setString(buf);
        }
    }
    else if(m_nRankType == kRankAbsolved)
    {
        MB_AbsolvedInterface* pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, (CCFunctionInterface**)&pInterface))
        {
            MB_ChapterProgress* p = pInterface->getChapterProgressByType(kChapterDifficultyNormal);
            if (p)
            {
                uint16_t i = p->getChapterId();
                MB_ChapterData* pData = MB_AbsolvedConfigure::getInstance()->getChapterDataById(i,1);
                if (pData)
                {
                    m_pNodeAbsolvedChapter->setString(pData->getName().c_str());
                }
                const MB_DungeonData * pa = MB_AbsolvedConfigure::getInstance()->getChapterDungeonDataById(i, p->getDungeonId());
                if (pa)
                {
                    m_pNodeAbsolvedDungeon->setString(pa->getName());
                }
            }
        }
        if (rank==0)
        {
            m_pNodeAbsolvedRank->setString("未上榜");
        }
        else
        {
            sprintf(buf, "%d",rank);
            m_pNodeAbsolvedRank->setString(buf);
        }
    }
}

void MB_LayerRankMain::sendpet_view_other(uint32_t roleid)
{
    if(roleid == MB_RoleData::getInstance()->getUID())return;
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_TeamData::getInstance()->sendpet_view_other(roleid,0);
}
