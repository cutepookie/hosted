//
//  MB_LayerFestivalMain.cpp
//  ProjectMB
//
//  Create by wenyong on 13/1/2015.
//
//
#include "MB_LayerFestivalMain.h"
#include "MB_FunctionFestival.h"
#include "MB_FestivalProtocol.h"
#include "MB_ClientSocket.h"
#include "MB_Message.h"
#include "MB_FunctionMgr.h"
#include "MB_GiftsProtocol.h"
#include "MB_LayerFunctionRule.h"
#include "MB_NodeFestivalRank.h"
#include "MB_FunctionActivityDesc.h"
#include "MB_ActivatyMainLayer.h"

bool MB_LayerFestivalMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pFunction = dynamic_cast<MB_FunctionFestival*>(pDataSource);
    m_pDataSource = pDataSource;
    return m_pFunction != NULL;
}

MB_LayerFestivalMain::MB_LayerFestivalMain()
{
    m_pJoinTimes	 = NULL;
    m_pNodeUnActiviteAll	 = NULL;
    m_pLeftJoinTimes	 = NULL;
    m_pNodeShouldReceiveAll	 = NULL;
    m_pNodeReceivedAll	 = NULL;
    m_pNodeFreeTimes	 = NULL;
    m_pLabelFreeTimes	 = NULL;
    m_pNodeUnFreeTimes	 = NULL;
    m_pLabelPriceByOnce	 = NULL;
    m_pLabelPriceByTenTimes	 = NULL;
    m_pNodeDes = NULL;
    m_pFunction = NULL;
    m_pEventName = NULL;
    m_pEventName1 = NULL;
    m_pMenuImageBox = NULL;
    SOCKET_MSG_REGIST(RECV_FESTIVAL_CLICK, MB_LayerFestivalMain);
    SOCKET_MSG_REGIST(RECV_FESTIVAL_INFO, MB_LayerFestivalMain);
}
MB_LayerFestivalMain::~MB_LayerFestivalMain()
{
    CC_SAFE_RELEASE_NULL(m_pJoinTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeUnActiviteAll);
    CC_SAFE_RELEASE_NULL(m_pLeftJoinTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeShouldReceiveAll);
    CC_SAFE_RELEASE_NULL(m_pNodeReceivedAll);
    CC_SAFE_RELEASE_NULL(m_pNodeFreeTimes);
    CC_SAFE_RELEASE_NULL(m_pLabelFreeTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeUnFreeTimes);
    CC_SAFE_RELEASE_NULL(m_pLabelPriceByOnce);
    CC_SAFE_RELEASE_NULL(m_pLabelPriceByTenTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeDes);
    CC_SAFE_RELEASE_NULL(m_pEventName);
    CC_SAFE_RELEASE_NULL(m_pEventName1);
    CC_SAFE_RELEASE_NULL(m_pMenuImageBox);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_CLICK);
    SOCKET_MSG_UNREGIST(RECV_FESTIVAL_INFO);
}
bool MB_LayerFestivalMain::init()
{
    CCNode* pNode = loadResource("res/festival_layer_activity.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}

void MB_LayerFestivalMain::onInitialized()
{
    if (m_pFunction)
    {
        MB_FunctionActivityDesc* pNodeLayer =  MB_FunctionActivityDesc::create();
        pNodeLayer ->setPosition(ccp(m_pNodeDes->getContentSize().width/2.0f,m_pNodeDes->getContentSize().height/2.0f));
        pNodeLayer->setClostTime(m_pFunction->getEndTime());
        pNodeLayer->setDiscription(m_pFunction->getDescription().c_str());
        pNodeLayer->setNomCount(0,0);
        m_pNodeDes->addChild(pNodeLayer);
    }
    m_pMenuImageBox->setIsScale(false);
    onResetWnd();
}

void MB_LayerFestivalMain::onResetWnd()
{
    if (m_pFunction)
    {
        char buf[64] = {};
        sprintf(buf, "%d次",m_pFunction->getTotalTimes());
        m_pJoinTimes->setString(buf);
        // m_pNodeShouldReceiveAll 可领取宝箱
        // m_pNodeUnActiviteAll 再参与...可获得宝箱
        // m_pNodeReceivedAll 已领取完全部宝箱
        
        if (m_pFunction->getLeftJoinTimes()!=0) // 还有可激活的宝箱
        {
            if (m_pFunction->getBoxTimes()!=0)  // 如果还有宝箱没有领取
            {
                m_pNodeShouldReceiveAll->setVisible(true);
                m_pNodeUnActiviteAll->setVisible(false);
                m_pNodeReceivedAll->setVisible(false);
            }
            else
            {
                m_pNodeUnActiviteAll->setVisible(true);
                m_pNodeShouldReceiveAll->setVisible(false);
                m_pNodeReceivedAll->setVisible(false);
            }
        }
        else // 宝箱已经全部激活
        {
            if (m_pFunction->getBoxTimes())
            {
                m_pNodeShouldReceiveAll->setVisible(true);
                m_pNodeUnActiviteAll->setVisible(false);
                m_pNodeReceivedAll->setVisible(false);
            }
            else
            {
                m_pNodeReceivedAll->setVisible(true);
                m_pNodeShouldReceiveAll->setVisible(false);
                m_pNodeUnActiviteAll->setVisible(false);
            }
        }
        
        m_pMenuImageBox->setEnabled(m_pFunction->getBoxTimes());
        
        if (m_pNodeUnActiviteAll->isVisible())
        {
            sprintf(buf, "%d次",m_pFunction->getLeftJoinTimes());
            m_pLeftJoinTimes->setString(buf);
        }
        
        sprintf(buf, "%d",m_pFunction->getOncePrice());
        m_pLabelPriceByOnce->setString(buf);
        sprintf(buf, "%d",m_pFunction->getTenthPrice());
        m_pLabelPriceByTenTimes->setString(buf);
        
        m_pNodeUnFreeTimes->setVisible(m_pFunction->getFreeTimes()==0);
        m_pNodeFreeTimes->setVisible(m_pFunction->getFreeTimes());
        sprintf(buf, "免费%d次",m_pFunction->getFreeTimes());
        m_pLabelFreeTimes->setString(buf);
        
        m_pEventName1->setString(m_pFunction->getName().c_str());
        m_pEventName->setString(m_pFunction->getName().c_str());
    }
}

bool MB_LayerFestivalMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pJoinTimes",CCLabelTTF*,m_pJoinTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeUnActiviteAll",CCNode*,m_pNodeUnActiviteAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLeftJoinTimes",CCLabelTTF*,m_pLeftJoinTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeShouldReceiveAll",CCNode*,m_pNodeShouldReceiveAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReceivedAll",CCNode*,m_pNodeReceivedAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeFreeTimes",CCNode*,m_pNodeFreeTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelFreeTimes",CCLabelTTF*,m_pLabelFreeTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeUnFreeTimes",CCNode*,m_pNodeUnFreeTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelPriceByOnce",CCLabelTTF*,m_pLabelPriceByOnce);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelPriceByTenTimes",CCLabelTTF*,m_pLabelPriceByTenTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeDes",CCNode*,m_pNodeDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pEventName",CCLabelTTF*,m_pEventName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pEventName1",CCLabelTTF*,m_pEventName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMenuImageBox",CCMenuItemImage*,m_pMenuImageBox);
	return false;
}
SEL_MenuHandler MB_LayerFestivalMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onBoxClicked",MB_LayerFestivalMain::onBoxClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onJoinOneTimeClicked",MB_LayerFestivalMain::onJoinOneTimeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onJoinTenTimesClicked",MB_LayerFestivalMain::onJoinTenTimesClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClicked",MB_LayerFestivalMain::onRuleClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRankClicked",MB_LayerFestivalMain::onRankClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onChargeClicked",MB_LayerFestivalMain::onChargeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerFestivalMain::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerFestivalMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
	return NULL;
}

void MB_LayerFestivalMain::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}
void MB_LayerFestivalMain::onChargeClicked(CCObject* pSender)
{
    goCharge(pSender);
}


void MB_LayerFestivalMain::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    if(!m_pFunction->checkProtocol(pRecv))
    {
        return;
    }
    if(RECV_FESTIVAL_CLICK == nMsg)
    {
        recv_festival_click(pRecv);
    }
    else if (RECV_FESTIVAL_INFO == nMsg)
    {
        dirty();
    }
    else if(RECV_FESTIVAL_RANK == nMsg)
    {
        SOCKET_MSG_UNREGIST(RECV_FESTIVAL_RANK);
        MB_ResWindow* pWnd = m_pFunction->createRankDialog();
        if (pWnd)
        {
            pWnd->setShowRoleInfoPanel(true);
            MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
            if (ptr)
            {
                ptr->pushWindow(pWnd);
            }
            else
            {
                CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_OUTSHOW);
            }
        }
    }
}

/*
 message sc_festival_click[id=13904]{
 required        int8            clickType               = 1;//点击类型，0单次，1十次,2累计次数宝箱
 required        int8            result                  = 2;////0成功，1系统错误， 2活动已关闭，3 元宝不足， 4无累计次数奖励可
 required        int16           ruleCount               = 3;//新的得到累计次数奖励需要次数，为0表示不更新当前累计次数显示
 required        int32           totalCount              = 4;//累计次数
 required        int32           totalGetCount           = 5;//当前可领取累计次数奖励，为0表示无奖励
 required        int32           freeCount               = 6;//免费次数
 repeated        p_mail_reward   clickReward             = 7;//本次点击得到的奖励,单次一个数组元素，十次则十个数组元素
 }
 */
void MB_LayerFestivalMain::recv_festival_click(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->skipU8();
    pRecv->readU8(&result);
    if(result == 0)
    {
        pRecv->skipU16();
        pRecv->skipU32();
        pRecv->skipU32();
        pRecv->skipU32();
        
        uint16_t count = 0;
        pRecv->readU16(&count);
        
        CCArray* pArray = CCArray::create();
        MB_MailReward reader;
        for (uint16_t i=0; i<count; ++i)
        {
            reader.read(pRecv);
            pArray->addObjectsFromArray(reader.converIDNUM2RewardTempleteValue());
        }

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
            MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
            if (ptr)
            {
                ptr->pushWindow(pRewardWnd);
            }
            else
            {
                pushWindow(pRewardWnd);
            }
        }
        
        dirty();
    }
    else if (result==3)
    {
        MB_Message::sharedMB_Message()->showMessage("提示","您的宝石已不足，是否前往充值", "前往", "取消", this,menu_selector(MB_LayerFestivalMain::goCharge), NULL);
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("活动已经结束");
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("系统错误");
    }
    else if(result == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("没有可领取的奖励");
    }
}

void MB_LayerFestivalMain::goCharge(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionPayShop, this);
}

void MB_LayerFestivalMain::onBoxClicked(CCObject* pSender)
{
    if (m_pFunction)
    {
        if (m_pFunction->getBoxTimes()==0)
        {
            MB_Message::sharedMB_Message()->showMessage("没有可领取的宝箱");
            return;
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("",15);
            m_pFunction->send_festival_open_box();
        }
    }
}
void MB_LayerFestivalMain::onJoinOneTimeClicked(CCObject* pSender)
{
    if (m_pFunction)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pFunction->send_festival_join_once();
    }
}
void MB_LayerFestivalMain::onJoinTenTimesClicked(CCObject* pSender)
{
    if (m_pFunction)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pFunction->send_festival_join_tenth();
    }
}
void MB_LayerFestivalMain::onRuleClicked(CCObject* pSender)
{
    if (m_pFunction)
    {
        MB_LayerFunctionRule* pLayer = MB_LayerFunctionRule::create(m_pFunction->getFunctionType());
        if(pLayer)
        {
            MB_TARGET_PARENT(MB_ActivatyMainLayer, ptr);
            if (ptr)
            {
                ptr->pushWindow(pLayer);
            }
            else
            {
                pushWindow(pLayer);
            }

        }
    }
}

void MB_LayerFestivalMain::onRankClicked(CCObject* pSender)
{
    if (m_pFunction)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        SOCKET_MSG_REGIST(RECV_FESTIVAL_RANK, MB_LayerFestivalMain);
        m_pFunction->send_festival_rank();
    }
}
