//
//  MB_LayerRuningCool.cpp
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#include "MB_LayerRuningCool.h"
#include "MB_RunningCoolSceneCreator.h"
#include "MB_NodeRolePKQ.h"
#include "MB_AdventureEntry.h"

#include "MB_LayerFishingReward.h"
#include "MB_RechargeSystem.h"
#include "MB_TutorialMgr.h"
#include "MB_LayerChatMain.h"
#include "MB_FishingRewardData.h"
MB_LayerRuningCool::MB_LayerRuningCool()
{
    m_pNodeRunLand	 = NULL;
    m_pRolePKQ = NULL;
    m_pDataSource = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    
    m_pAutoFishingItem = NULL;
    m_pAutoFishingImage = NULL;
    m_pTextEnableVip = NULL;
    m_pTextRecover = NULL;
    m_pTextDiscoveryTimes = NULL;
    m_pAutoFishing = NULL;
    m_bAutoFishing = false;
//    m_pMenuItemClick = NULL;
    
    SOCKET_MSG_REGIST(SC_EXPLORE_ONE, MB_LayerRuningCool);
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerRuningCool);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRuningCool",true);
    
    
}

void MB_LayerRuningCool::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_RunningCool);
}

MB_LayerRuningCool::~MB_LayerRuningCool()
{
    unscheduleAllSelectors();
    stopAllActions();
    CC_SAFE_RELEASE_NULL(m_pNodeRunLand);
    CC_SAFE_RELEASE_NULL(m_pAutoFishingItem);
    CC_SAFE_RELEASE_NULL(m_pAutoFishingImage);
    CC_SAFE_RELEASE_NULL(m_pTextEnableVip);
    CC_SAFE_RELEASE_NULL(m_pTextRecover);
    CC_SAFE_RELEASE_NULL(m_pTextDiscoveryTimes);
    CC_SAFE_RELEASE_NULL(m_pAutoFishing);

//    CC_SAFE_RELEASE_NULL(m_pMenuItemClick);
    SOCKET_MSG_UNREGIST(SC_EXPLORE_ONE);
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
//    MB_LayerChatMain::SetChatMainVisible(true, "MB_LayerRuningCool");
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerRuningCool",false);
}
bool MB_LayerRuningCool::init()
{
    CCNode* pNode = loadResource("res/fishing_layer_main.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onInitialized();
		return true;
	}
	return false;
}

void MB_LayerRuningCool::onInitialized()
{
    MB_RunningCoolSceneCreator::init();
    m_szWindowSize = CCDirector::sharedDirector()->getWinSize();
    char buf[32] = {};
    sprintf(buf,"%d", m_pDataSource->getAutoVipLimit());
//    m_pTextEnableVip->setString(buf);
    m_pAutoFishing->setSwallowsTouches(true);
    m_pRolePKQ = MB_NodeRolePKQ::create(1);
    m_pNodeRunLand->addChild(m_pRolePKQ);
    m_pNodeRunLand->setPositionX(m_szWindowSize.width/2.0);
    this->setTouchPriority(-200);
    this->setTouchEnabled(true);
    schedule(schedule_selector(MB_LayerRuningCool::updateTick));
    schedule(schedule_selector(MB_LayerRuningCool::updateTime), 1.0);
    updateTime();
}

void MB_LayerRuningCool::onCloseClick(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionYeShiJie, this);
}

void MB_LayerRuningCool::updateTime()
{
    int realTime =  0;
    if(   MB_RoleData::getInstance()->getDiscoveryTimes() <
       MB_RoleData::getInstance()->getDiscoveryTimesMax())
    {
        realTime = MB_RoleData::getInstance()->getNextDscvTime()- MB_ClientSocket::getInstance()->getServerTime();
    }
    char databuf[64] = {};
    if (realTime < 0)
    {
        realTime = 0;
    }
    sprintf(databuf, "%02d:%02d",realTime/60,realTime%60);
    m_pTextRecover->setString(databuf);
    sprintf(databuf, "%d/%d",
            MB_RoleData::getInstance()->getDiscoveryTimes(),
            MB_RoleData::getInstance()->getDiscoveryTimesMax());
    m_pTextDiscoveryTimes->setString(databuf);
}


bool MB_LayerRuningCool::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    CCPoint  des = m_pAutoFishingItem->convertToNodeSpace(point);
    if(des.x > 0 && des.x < m_pAutoFishingItem->getContentSize().width && des.y > 0 && des.y < m_pAutoFishingItem->getContentSize().height)
    {
    }
    else
    {
        if(m_bAutoFishing)
        {
            m_bAutoFishing = false;
            resetAutoJump();
        }
    }
    return false;
}






void MB_LayerRuningCool::updateTick(float dt)
{
    if (m_bAutoFishing)
    {
        if (MB_RoleData::getInstance()->getDiscoveryTimes()>0)
        {
            onJumpCliked(NULL);
        }
        else
        {
            onAotuJumpClicked(NULL);
            showAddTimes();
        }
    }
}



void MB_LayerRuningCool::onResetWnd()
{

}
bool MB_LayerRuningCool::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRunLand",CCNode*,m_pNodeRunLand);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoFishingItem", CCMenuItemImage*, m_pAutoFishingItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoFishingImage", CCMenuItemImage*, m_pAutoFishingImage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextEnableVip", CCLabelBMFont*, m_pTextEnableVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextRecover", CCLabelBMFont*, m_pTextRecover);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDiscoveryTimes", CCLabelBMFont*, m_pTextDiscoveryTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAutoFishing", CCMenu*, m_pAutoFishing);

	return false;
}

void MB_LayerRuningCool::onJumpCliked(CCObject* pSender)
{
    if(pSender)
    {
        TutorialTriggerComplete
    }
        

        
    if (m_pRolePKQ->canJump())
    {
        if (MB_RoleData::getInstance()->getDiscoveryTimes()==0)
        {
            showAddTimes();
            return;
        }
        
        
        //chk  自动做个时间间隔
        static uint32_t nLastTime = 0;
        if(MB_ClientSocket::getInstance()->getServerTime() - nLastTime < 2)return;
        nLastTime = MB_ClientSocket::getInstance()->getServerTime();
        //chk  自动做个时间间隔
        
        m_pRolePKQ->jump();
        CCCallFunc* pFunc = CCCallFunc::create(this, callfunc_selector(MB_LayerRuningCool::onJump2Top));
        m_pNodeRunLand->runAction(CCSequence::create(CCDelayTime::create(0.3),pFunc,NULL));
    }
}

void MB_LayerRuningCool::onJump2Top()
{
    if (m_pDataSource)
    {
        m_pDataSource->sendexplor_one();
    }
}

void MB_LayerRuningCool::onEnter()
{
    MB_FunctionMainWnd::onEnter();
}

SEL_MenuHandler MB_LayerRuningCool::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onJumpCliked", MB_LayerRuningCool::onJumpCliked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAotuFishingClicked", MB_LayerRuningCool::onAotuJumpClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerRuningCool::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerRuningCool::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerRuningCool::onAotuJumpClicked(CCObject* pSender)
{
    if(MB_RoleData::getInstance()->getVipLevel() < m_pDataSource->getAutoVipLimit())
    {
        char databuf[100];
        sprintf(databuf, "主人, 充值成为VIP%d就可以一键冒险哦~~~~",m_pDataSource->getAutoVipLimit());
        MB_Message::sharedMB_Message()->showMessage(databuf);
        return;
    }
    
    m_bAutoFishing = !m_bAutoFishing;
    resetAutoJump();
}

void MB_LayerRuningCool::resetAutoJump()
{
    MB_LayerChatMain::SetChatMainVisible(m_bAutoFishing, "MB_LayerRuningCool");
    m_pAutoFishingImage->setEnabled(!m_bAutoFishing);
}

bool MB_LayerRuningCool::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_AdventureEntry*>(pDataSource);
    return m_pDataSource != NULL;
}

void MB_LayerRuningCool::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    if (SC_EXPLORE_ONE == nMsg)
    {
        recvexplore_one(pRecv);
    }
    else if(SC_ROLE_UPDATE_LEVEL == nMsg)
    {
        recvrole_up(pRecv);
    }
}

void MB_LayerRuningCool::recvrole_up(MB_MsgBuffer* recvPacket)
{
    MB_LayerRoleLevelUp *pLayer = MB_LayerRoleLevelUp::create(MB_RoleData::getInstance()->getLevel()-1, MB_RoleData::getInstance()->getPreDisTimes(), MB_RoleData::getInstance()->getPreEnergy());
    if (pLayer)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer,Z_ORDER_OUTSHOW);
        if (m_bAutoFishing)
        {
            onAotuJumpClicked(NULL);
        }
    }
}

void MB_LayerRuningCool::recvexplore_one(MB_MsgBuffer* recvPacket)
{
    int8_t result;
    recvPacket->readU8(&result);
    if(result == 1){
        
        MB_Message::removeALLMessage();
        MB_FishingRewardData* data = new MB_FishingRewardData();
        
        uint16_t count = 0;
        int32_t data32;
        uint16_t data16;
        int8_t data8;
        
        recvPacket->readU16(&count);
        for (int i = 0; i < count ; i++) {
            data->getRewardArray()->removeAllObjects();
            RewardTempleteValue* item = new RewardTempleteValue;
            
            recvPacket->readU16(&data16);
            item->setValueID(data16);
            recvPacket->readU32(&data32);
            item->setNumber(data32);
            item->setType(kRewardValueTypeItem);
            data->addRewardItem(item);
            
            
            
            CC_SAFE_RELEASE(item);
            
        }
        if(count)MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Reward).c_str());
        recvPacket->readU32(&data32);//冒险家经验
        data->setRoleExp(data32);
        recvPacket->readU32(&data32);//宠物经验
        recvPacket->readU32(&data32);//银两
        data->setCoin(data32);
        recvPacket->readU8(&data8);//暴基
        data->setCrit(data8);
        
        MB_ResWindow* layer = MB_LayerFishingReward::create(data);
        pushWindow(layer);
        
        
        CC_SAFE_RELEASE_NULL(data);
        
    }
    else if(result == 3)
    {
        showAddTimes();
    }
}

void MB_LayerRuningCool::showAddTimes()
{
    if (!MB_RechargeSystem::getInstance()->showRechargeWndByType(Discovery_ADD, NSGameFunction::CCFunctionInterface::getCurrentFunctionWnd()))
    {
        int needMoney = MB_RoleData::getInstance()->getNeedGoldByTime(kBuyTimesTypeDiscovery);
        int limit = MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeDiscovery)-MB_RoleData::getInstance()->getDiscoveryBuyTimes();
        if(limit > 0){
            char databuf[200];
            sprintf(databuf, "您是否需要花费 %d 宝石, 购买 %d 次冒险次数?\n这是今日的第%d次购买, 当前VIP等级每日购买的次数上限是%d次",needMoney,MB_RoleData::getInstance()->getDiscoveryRecoveryTimes(),MB_RoleData::getInstance()->getDiscoveryBuyTimes()+1 ,MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeDiscovery));
            MB_ResWindow* p = MB_Message::sharedMB_Message()->createMessageBox2("再次点击冒险可购买冒险次数", databuf,"确定","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goBuyDiscoveryTimes),NULL);
            if (p)
            {
                addChild(p,Z_ORDER_MESSAGE);
            }
            
        }else {
            
            if(MB_RoleData::getInstance()->getVipLevel() < MAX_VIP_LEVEL){
                
                char databuf[200];
                sprintf(databuf, "您的冒险次数不足了, 并且今日的回复道具的次数已经使用完毕, 充值成为更高级的VIP, 可以立马增加回复次数");
                MB_ResWindow* p = MB_Message::sharedMB_Message()->createMessageBox2("购买次数达到上限", databuf,"充值","取消",MB_RoleData::getInstance() ,menu_selector(MB_RoleData::goCharge),NULL);
                if (p)
                {
                    addChild(p,Z_ORDER_MESSAGE);
                }
                
            }else {
                
                MB_Message::sharedMB_Message()->showMessage("今日的冒险购买次数已经达到上限");
                
            }
            
        }
    }

}
