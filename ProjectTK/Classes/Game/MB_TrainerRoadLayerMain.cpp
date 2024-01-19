//
//  MB_TrainerRoadLayerMainpp
//  ProjectMB
//
//  Create by wenyong on 15/1/2015.
//
//
#include "MB_TrainerRoadLayerMain.h"
#include "MB_FunctionTrainerRoad.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_TrainerRoadLayerMap.h"
#include "MB_FunctionMgr.h"
#include "MB_Message.h"
#include "MB_GiftsProtocol.h"
MB_TrainerRoadLayerMain::MB_TrainerRoadLayerMain()
{
    m_pResetTimes	 = NULL;
    m_pFunction = NULL;
    m_pNodeMap = NULL;
    m_pLayerMap = NULL;
    m_pScrollView = NULL;
    m_pNodeExt = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    SOCKET_MSG_REGIST(SC_ROAD_INFO,MB_TrainerRoadLayerMain);
    SOCKET_MSG_REGIST(SC_ROAD_RESET,MB_TrainerRoadLayerMain);
    SOCKET_MSG_REGIST(SC_ROAD_FIGHT,MB_TrainerRoadLayerMain);
    SOCKET_MSG_REGIST(SC_ROAD_FIGHT_EXT,MB_TrainerRoadLayerMain);
    SOCKET_MSG_REGIST(SC_ROAD_BOX,MB_TrainerRoadLayerMain);
}
MB_TrainerRoadLayerMain::~MB_TrainerRoadLayerMain()
{
    CC_SAFE_RELEASE_NULL(m_pResetTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeMap);
    CC_SAFE_RELEASE_NULL(m_pNodeExt);
    
    SOCKET_MSG_UNREGIST(SC_ROAD_INFO);
    SOCKET_MSG_UNREGIST(SC_ROAD_RESET);
    SOCKET_MSG_UNREGIST(SC_ROAD_FIGHT);
    SOCKET_MSG_UNREGIST(SC_ROAD_FIGHT_EXT);
    SOCKET_MSG_UNREGIST(SC_ROAD_BOX);
}
bool MB_TrainerRoadLayerMain::init()
{
    CCNode* pNode = loadResource("res/road_layer_background.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}
void MB_TrainerRoadLayerMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
    static uint8_t nLastExtid = m_pFunction->getExtID();
    if(nLastExtid == 0 && m_pFunction->getExtID() != 0)
    {
        MB_Message::sharedMB_Message()->showMessage("发现神秘关卡", "发现神秘关卡，快去挑战吧", "确定");
    }
    nLastExtid = m_pFunction->getExtID();
}
void MB_TrainerRoadLayerMain::onResetWnd()
{
    m_pLayerMap->onResetWnd();
    m_pResetTimes->setString(CCString::createWithFormat("%d",m_pFunction->getResetTimes())->getCString());
    
    m_pNodeExt->setVisible(m_pFunction->getExtID() != 0);
    
//    m_pScrollView->getContainer()->stopAllActions();
//    CCNode* pNode = m_pLayerMap->getActivtedNode();
//    if(pNode)
//    {
//        CCSize size = CCDirector::sharedDirector()->getWinSize();
//        float fy = pNode->getPositionY();
//        if(fy < size.height /2)
//        {
//            fy = 0;
//            m_pScrollView->setContentOffsetInDuration(CCPointMake(0, fy), 1);
//        }
//        else if(fy > m_pLayerMap->getLayerSize().height - size.height /2)
//        {
//            fy = size.height - m_pLayerMap->getLayerSize().height;
//            m_pScrollView->setContentOffsetInDuration(CCPointMake(0, fy), 1);
//        }
//        else
//        {
//            m_pScrollView->setContentOffsetInDuration(CCPointMake(0, size.height/2-fy), 1);
//        }
//    }
    
    int nCurIndex = m_pFunction->getCurID() - ROLE_BEGIN_ID;
    m_pScrollView->setContentOffset(ccp( 0,-4364+nCurIndex*220));
}

void MB_TrainerRoadLayerMain::onInitialized()
{
    m_pLayerMap = MB_TrainerRoadLayerMap::create(m_pFunction);
    
    CCNode* pContainer = CCNode::create();
    m_pNodeMap->addChild(pContainer);
    pContainer->setContentSize(m_pLayerMap->getLayerSize());
    
    m_pScrollView= CCScrollView::create(CCDirector::sharedDirector()->getWinSize());
    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    pContainer->addChild(m_pScrollView);
    m_pScrollView->setSwaller(false);
//    m_pScrollView->setBounceable(false);
    
    m_pLayerMap->setContentSize(m_pLayerMap->getLayerSize());
    m_pScrollView->setContainer(m_pLayerMap);
    m_pScrollView->setContentSize(pContainer->getContentSize());
    

    onResetWnd();
}

bool MB_TrainerRoadLayerMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pFunction = dynamic_cast<MB_FunctionTrainerRoad*>(pDataSource);
    m_pDataSource = pDataSource;
    return m_pFunction != NULL;
}

void MB_TrainerRoadLayerMain::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    switch (nMsg)
    {
        case SC_ROAD_BOX:
            recv_road_box(pRecv);
        case SC_ROAD_INFO:
        case SC_ROAD_RESET:
        case SC_ROAD_FIGHT:
        case SC_ROAD_FIGHT_EXT:
            onResetWnd();
            break;
        default:
            break;
    }
}

void MB_TrainerRoadLayerMain::recv_road_box(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    
    uint16_t len = 0;
    pRecv->readU16(&len);
    if(len)
    {
        MB_MailReward* pMailReward = new MB_MailReward();
        pMailReward->read(pRecv);
        CCArray* pArray = pMailReward->converIDNUM2RewardTempleteValue();
        
        MB_ResWindow* pRewardWnd = NULL;
        if (pArray->count()>3)
        {
            pRewardWnd = MB_LayerRewardMore2::create(pArray);
            pRewardWnd->setShowRoleInfoPanel(false);
        }
        else
        {
            pRewardWnd = MB_LayerRewardMore::create(pArray);
            pRewardWnd->setShowRoleInfoPanel(false);
        }
        if (pRewardWnd)
        {
            pushWindow(pRewardWnd);
        }
        CC_SAFE_DELETE(pMailReward);
    }
}

bool MB_TrainerRoadLayerMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pResetTimes",CCLabelBMFont*,m_pResetTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMap", CCNode*, m_pNodeMap);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeExt",CCNode*,m_pNodeExt);
	return false;
}
SEL_MenuHandler MB_TrainerRoadLayerMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_TrainerRoadLayerMain::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onResetClicked",MB_TrainerRoadLayerMain::onResetClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onExtClicked",MB_TrainerRoadLayerMain::onExtClicked);
	return NULL;
}
void MB_TrainerRoadLayerMain::onExtClicked(CCObject*)
{
    MB_Message::sharedMB_Message()->showMessage(5);
    m_pFunction->send_road_fight_ext("神秘关卡");
}
SEL_CCControlHandler MB_TrainerRoadLayerMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_TrainerRoadLayerMain::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
void MB_TrainerRoadLayerMain::onResetClicked(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage(5);
    m_pFunction->send_road_reset();
}

void MB_TrainerRoadLayerMain::send_road_fight(std::string str)
{
    MB_Message::sharedMB_Message()->showMessage(5);
    m_pFunction->send_road_fight(str);
}
//void MB_TrainerRoadLayerMain::send_road_fight_ext()
//{
//    MB_Message::sharedMB_Message()->showMessage(5);
//    m_pFunction->send_road_fight_ext("神秘关卡");
//}
void MB_TrainerRoadLayerMain::send_road_box()
{
    MB_Message::sharedMB_Message()->showMessage(5);
    m_pFunction->send_road_box();
}





