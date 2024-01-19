//
//  MB_LayerRegistration.cpp
//  ProjectMB
//
//  Create by WenYong on 28/8/2014.
//
//
#include "MB_LayerRegistration.h"
#include "MB_LayerCalender.h"
#include "MB_FunctionModule.h"
#include "MB_ItemData.h"
#include "MB_NodeSignItemView.h"
#include "MB_LoginNotice.h"


#define MAXSHOWNUM 30

MB_LayerRegistration::MB_LayerRegistration()
{
    tutorial	 = NULL;
    m_pCalendarContainer	 = NULL;
    m_pRewardContainer	 = NULL;
    m_pBtnRequest = NULL;
    m_uIsGet = kRewardGetTypeDisable;
    m_uValue = 0;
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
    m_bShowEXP = true;
    m_pTableView = NULL;
    SOCKET_MSG_REGIST(SC_DAILY_DRAW, MB_LayerRegistration);
    SOCKET_MSG_REGIST(SC_ROLE_LOGIN_REWARD, MB_LayerRegistration);
}
MB_LayerRegistration::~MB_LayerRegistration()
{
    CC_SAFE_RELEASE_NULL(tutorial);
    CC_SAFE_RELEASE_NULL(m_pCalendarContainer);
    CC_SAFE_RELEASE_NULL(m_pRewardContainer);
    CC_SAFE_RELEASE_NULL(m_pBtnRequest);
    m_uValue = 0;
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
    SOCKET_MSG_UNREGIST(SC_ROLE_LOGIN_REWARD);
}
bool MB_LayerRegistration::init()
{
    addChild(NSGameHelper::createDisableTouchLayer());// 防止点穿
    CCNode* pNode = loadResource("res/sign_layer.ccbi");
    if(pNode)
	{
		addChild(pNode);
        
        CCNode* pNode = MB_LayerCalender::create();
        if (pNode)
        {
            m_pCalendarContainer->addChild(pNode);
            pNode->setPosition(0, m_pCalendarContainer->getContentSize().height - pNode->getContentSize().height);
        }
        NSGameHelper::adjustScrollNode(m_pRewardContainer);
        
        m_pTableView = CCTableView::create(this, m_pRewardContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pTableView->setSwaller(false);
        //    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pRewardContainer->addChild(m_pTableView);

        onResetWnd();
        
        NSGameHelper::runOptActionIn(this, .25f, true);
		return true;
	}
	return false;
}
void MB_LayerRegistration::onResetWnd()
{
    DailyRewardValue* tempValue = NULL;
    for (int i = 0; i < MB_ItemMgr::getInstance()->getDailyRewardArray()->count(); i++)
    {
        tempValue = (DailyRewardValue*)MB_ItemMgr::getInstance()->getDailyRewardArray()->objectAtIndex(i);
        if (tempValue->getType() == kRewardTypeDaily)
        {
            break;
        }
    }
    
    //如果为空,则表示没有配置当前领取,默认显示第一个领取项,并且提示为不能领取
    CCArray* pArray = MB_ItemMgr::getInstance()->getDailyRewardTempleteArray();
    if (tempValue != NULL)
    {
        m_uIsGet = tempValue->getIsGet();
        m_uValue = tempValue->getValue();
    }
    else
    {
        m_uValue = ((RewardTemplete*)pArray->objectAtIndex(0))->getID();
        m_uIsGet = kRewardGetTypeDisable;
    }
    
    if (m_uIsGet == kRewardGetTypeDisable)
    {
        m_pBtnRequest->setEnabled(false);
    }
    else if (m_uIsGet == kRewardGetTypeReady)
    {
        m_pBtnRequest->setEnabled(true);
    }
    else if (m_uIsGet == kRewardGetTypeAlready)
    {
        m_pBtnRequest->setEnabled(false);
    }

    m_pTableView->reloadData();
    
}
bool MB_LayerRegistration::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCalendarContainer",CCNode*,m_pCalendarContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRewardContainer",CCNode*,m_pRewardContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnRequest", CCControlButton*, m_pBtnRequest);
	return false;
}
SEL_MenuHandler MB_LayerRegistration::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerRegistration::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerRegistration::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRequestReward", MB_LayerRegistration::onRequestReward);
	return NULL;
}
void MB_LayerRegistration::onCloseClick(CCObject* pSender)
{
    addChild(NSGameHelper::createDisableTouchLayerAll());
    NSGameHelper::runOptActionOut(this, .25f, true);
    runAction(CCSequence::create(CCDelayTime::create(.25f),CCCallFunc::create(this, callfunc_selector(MB_LayerRegistration::finish)),NULL));
    TutorialTriggerComplete
}
void MB_LayerRegistration::finish()
{
    removeFromParent();
    if (isAutoTanChuSign) {
        isAutoTanChuSign = false;
        if(!MB_TutorialMgr::getInstance()->getHasTutorialDilog())
        {
            CCDirector::sharedDirector()->getRunningScene()->addChild(MB_LoginNotice::create(), Z_ORDER_OUTSHOW);
        }
    }
}
void MB_LayerRegistration::onRequestReward(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_ItemMgr::getInstance()->senddaily_draw(2);
}

void MB_LayerRegistration::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (nMsg == SC_DAILY_DRAW)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        m_pBtnRequest->setEnabled(false);
        
        uint8_t result;
        pRecv->readU8(&result);
        
        if (result == 1)
        {
            CCArray* pArray = MB_ItemMgr::getInstance()->getDailyRewardTempleteArray();
            if (m_uIsGet == kRewardGetTypeReady)
            {
                RewardTemplete* rewardTemplete = NULL;
                for (int i = 0; i < pArray->count(); i++)
                {
                    rewardTemplete = (RewardTemplete*)pArray->objectAtIndex(i);
                    if (rewardTemplete->getID() == m_uValue)
                    {
                        CCArray* valueArray = rewardTemplete->getValueArray();
                        
                        
                        MB_LayerRewardMore* rewardMore = MB_LayerRewardMore::create(valueArray);
                        rewardMore->setTag(999);
                        rewardMore->setShowRoleInfoPanel(false);
                        this->pushWindow(rewardMore);
                        schedule(schedule_selector(MB_LayerRegistration::updateClose));
                        return;
                    }
                }
            }
            schedule(schedule_selector(MB_LayerRegistration::updateClose));
        }
    }
    else if(SC_ROLE_LOGIN_REWARD == nMsg)
    {
        dirty();
    }
}
void MB_LayerRegistration::updateClose(float dt)
{
    if (getChildByTag(999)==NULL) {
        onCloseClick(NULL);
        unschedule(schedule_selector(MB_LayerRegistration::updateClose));
    }
}

CCSize MB_LayerRegistration::cellSizeForTable(CCTableView *table)
{
    return MB_NodeSignItemView::getNodeSize();
}
CCTableViewCell* MB_LayerRegistration::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    CCArray* pArray = MB_ItemMgr::getInstance()->getDailyRewardTempleteArray();
    RewardTemplete* curTemplete = NULL;

    curTemplete = dynamic_cast<RewardTemplete*>(pArray->objectAtIndex((m_uValue+idx - 1)%pArray->count()));
    if (curTemplete != NULL)
    {
        MB_NodeSignItemView* pContainer = MB_NodeSignItemView::create(curTemplete->getValueArray(),idx);
        if (pContainer)
        {
            cell->addChild(pContainer);
            pContainer->setPosition(pContainer->getContentSize().width/2,pContainer->getContentSize().height/2);
        }
    }
        
    
    return cell;

}
unsigned int MB_LayerRegistration::numberOfCellsInTableView(CCTableView *table)
{
    return MAXSHOWNUM;
}
