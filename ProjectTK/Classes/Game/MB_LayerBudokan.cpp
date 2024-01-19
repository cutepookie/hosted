//
//  MB_LayerBudokan.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-8-28.
//
//

#include "MB_LayerBudokan.h"
#include "MB_FunctionBudokanInterface.h"
#include "MB_NodeRewardUnit.h"
#include "MB_NodeItemBook.h"
#include "MB_LayerBudokanSweep.h"
#include "MB_LayerFunctionRule.h"

MB_LayerBudokan::MB_LayerBudokan()
{
    m_pTTFAddAtt	 = NULL;
    m_pTTFAddHP	 = NULL;
    m_pTTFTimes = NULL;
    m_pTTFNowDungeon = NULL;
    m_pInterface = NULL;
    
    m_pBtMoneyAddBuf = NULL;
    m_pBtGoldAddBuf = NULL;
    m_pBtFight = NULL;
    m_pBtAutoFight = NULL;
    
    m_pNodeReward1 = NULL;
    m_pNodeReward2 = NULL;
    m_pNodeReward3 = NULL;
    m_pNodeReward4 = NULL;
    m_pSprinteBoss = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    m_NodePassed = NULL;
    m_bAutoFight = false;
    m_pTTFMaxDungeon = NULL;
    SOCKET_MSG_REGIST(SC_BUDUOKAN_INFO,MB_LayerBudokan);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_BUY,MB_LayerBudokan);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_FIGHT,MB_LayerBudokan);
    SOCKET_MSG_REGIST(SC_BUDUOKAN_RAIDS,MB_LayerBudokan);
}
MB_LayerBudokan::~MB_LayerBudokan()
{
    
    CC_SAFE_RELEASE_NULL(m_pTTFNowDungeon);
    CC_SAFE_RELEASE_NULL(m_pTTFAddAtt);
    CC_SAFE_RELEASE_NULL(m_pTTFAddHP);
    CC_SAFE_RELEASE_NULL(m_pTTFTimes);
    CC_SAFE_RELEASE_NULL(m_pBtMoneyAddBuf);
    CC_SAFE_RELEASE_NULL(m_pBtGoldAddBuf);
    CC_SAFE_RELEASE_NULL(m_pBtFight);
    CC_SAFE_RELEASE_NULL(m_pBtAutoFight);
    CC_SAFE_RELEASE_NULL(m_pNodeReward1);
    CC_SAFE_RELEASE_NULL(m_pNodeReward2);
    CC_SAFE_RELEASE_NULL(m_pNodeReward3);
    CC_SAFE_RELEASE_NULL(m_pNodeReward4);
    CC_SAFE_RELEASE_NULL(m_pSprinteBoss);
    CC_SAFE_RELEASE_NULL(m_NodePassed);
    CC_SAFE_RELEASE_NULL(m_pTTFMaxDungeon);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_INFO);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_BUY);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_FIGHT);
    SOCKET_MSG_UNREGIST(SC_BUDUOKAN_RAIDS);
}
bool MB_LayerBudokan::init()
{

    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/station_layer_towerend.ccbi", this);
    if (pScene == NULL) {
        CC_SAFE_RELEASE_NULL(pCCBReader);
        return false;
    }
    this->addChild(pScene);

    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    
	return true;
}

void MB_LayerBudokan::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerBudokan::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_BUDUOKAN_INFO:
            dirty();
            break;
        case SC_BUDUOKAN_BUY:
            dirty();
            break;
        case SC_BUDUOKAN_FIGHT:
            dirty();
            break;
        case SC_BUDUOKAN_RAIDS:
            recvbudokan_raids(pRecv);
            dirty();
            break;
        default:
            break;
    }
}


void MB_LayerBudokan::onResetWnd()
{
    if(m_pInterface == NULL)
    {
        return;
    }
    
    MB_BudokanConfig* config = m_pInterface->getBudokanConfig();
    MB_BudokanChapterData* chapterData = NULL;
    int nCurDungenNum = m_pInterface->getBudokanData()->getCurDungeonNum();
    chapterData = config->getChapterDataByID(m_pInterface->getBudokanData()->getDungeonID());
    
    char str[32] = {};

    
    bool bLastDungeon = false;
    if(chapterData == NULL)
    {
        bLastDungeon = true;
        nCurDungenNum--;//最高关卡
//        chapterData = config->getChapterDataByID(m_pInterface->getBudokanData()->getDungeonID());
//        m_pSprinteBoss->setColor(ccGRAY);
    }
    m_NodePassed->setVisible(bLastDungeon);
    
    //最高层数
    int maxDungeon;
    if (m_pInterface->getBudokanData()->getMaxDungeonNum() > nCurDungenNum-1)
    {
        maxDungeon = m_pInterface->getBudokanData()->getMaxDungeonNum();
    }
    else
    {
        if(bLastDungeon)
        {
            maxDungeon = nCurDungenNum;
        }
        else
        {
            maxDungeon = nCurDungenNum-1;
        }
    }
    sprintf(str,"%d",maxDungeon);
    m_pTTFMaxDungeon->setString(str);
    
    
    sprintf(str,"%d",nCurDungenNum);
    m_pTTFNowDungeon->setString(str);
    
    sprintf(str,"%d",m_pInterface->getBudokanData()->getChallengeTimes());
    m_pTTFTimes->setString(str);
    
    sprintf(str,"%d%s",m_pInterface->getBudokanData()->getAddAttack(),"%");
    m_pTTFAddAtt->setString(str);
    
    sprintf(str,"%d%s",m_pInterface->getBudokanData()->getAddHp(),"\%");
    m_pTTFAddHP->setString(str);
    
    //按钮状态
    if (m_pInterface->getBudokanData()->getCoinBuyTimes() == 0 && m_pInterface->getBudokanData()->getLastTime() > 0 && m_pInterface->getIsOpen())
    {
        m_pBtGoldAddBuf->setEnabled(true);
    }
    else
    {
        m_pBtGoldAddBuf->setEnabled(false);
    }
    if (m_pInterface->getBudokanData()->getMoneyBuyTimes() == 0 && m_pInterface->getBudokanData()->getLastTime() > 0 && m_pInterface->getIsOpen())
    {
        m_pBtMoneyAddBuf->setEnabled(true);
    }
    else
    {
        m_pBtMoneyAddBuf->setEnabled(false);
    }
    
    if (m_pInterface->getBudokanData()->getChallengeTimes() == 0 || bLastDungeon)
    {
        m_pBtFight->setEnabled(false);
        m_pBtAutoFight->setEnabled(false);
    }
    else
    {
        m_pBtFight->setEnabled(true);
        m_pBtAutoFight->setEnabled(true);
    }
    
    
    //怪物显示
    if (chapterData == NULL)
    {
        return;
    }
    MB_PetTemplate* boosTemplete  = MB_PetMgr::getInstance()->getPetTemplateByID(chapterData->getBoosID());
    if (boosTemplete == NULL)
    {
        return;
    }
    CCLOG("%s",boosTemplete->getPetCard());
    NSGameHelper::setSpriteFrame(m_pSprinteBoss,boosTemplete->getPetCard());//形态？
    
    
    //奖励
    m_pNodeReward1->removeAllChildren();
    MB_NodeItem* node1 = MB_NodeItem::create(chapterData->getRewordID1());
    if (node1 != NULL)
    {
        node1->setNum(chapterData->getNum1());
        m_pNodeReward1->addChild(node1);
    }
    
    m_pNodeReward2->removeAllChildren();
    MB_NodeItem* node2 = MB_NodeItem::create(chapterData->getRewordID2());
    if (node2 != NULL)
    {
        node2->setNum(chapterData->getNum2());
        m_pNodeReward2->addChild(node2);
    }
    
    m_pNodeReward3->removeAllChildren();
    MB_NodeItem* node3 = MB_NodeItem::create(chapterData->getRewordID3());
    if (node3 != NULL)
    {
        node3->setNum(chapterData->getNum3());
        m_pNodeReward3->addChild(node3);
    }
    
    m_pNodeReward4->removeAllChildren();
    MB_NodeItem* node4 = MB_NodeItem::create(chapterData->getRewordID4());
    if (node4 != NULL)
    {
        node4->setNum(chapterData->getNum4());
        m_pNodeReward4->addChild(node4);
    }
}

bool MB_LayerBudokan::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_FunctionBudokanInterface*>(pDataSource);
    if (m_pInterface) {
        m_pDataSource = pDataSource;
        onResetWnd();
    }
    return m_pInterface != NULL;
}

bool MB_LayerBudokan::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAddAtt",CCLabelBMFont*,m_pTTFAddAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFAddHP",CCLabelBMFont*,m_pTTFAddHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFTimes",CCLabelBMFont*,m_pTTFTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtMoneyAddBuf",CCControlButton*,m_pBtMoneyAddBuf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGoldAddBuf",CCControlButton*,m_pBtGoldAddBuf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtFight",CCControlButton*,m_pBtFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtAutoFight",CCControlButton* ,m_pBtAutoFight);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward1",CCNode*,m_pNodeReward1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward2",CCNode*,m_pNodeReward2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward3",CCNode*,m_pNodeReward3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeReward4",CCNode*,m_pNodeReward4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSprinteBoss",CCSprite*,m_pSprinteBoss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_NodePassed", CCNode*, m_NodePassed);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFMaxDungeon",CCLabelBMFont*,m_pTTFMaxDungeon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFNowDungeon",CCLabelBMFont*,m_pTTFNowDungeon);
    
	return false;
}
SEL_MenuHandler MB_LayerBudokan::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onRuleClick",MB_LayerBudokan::onRuleClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerBudokan::onCloseClick);


	return NULL;
}
SEL_CCControlHandler MB_LayerBudokan::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onFightClicked",MB_LayerBudokan::onFightClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onAutoFightClicked",MB_LayerBudokan::onAutoFightClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onMoneyInspirationClicked",MB_LayerBudokan::onMoneyInspirationClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onGoldInspirationClicked",MB_LayerBudokan::onGoldInspirationClicked);
	return NULL;
}
void MB_LayerBudokan::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
void MB_LayerBudokan::onMoneyInspirationClicked(CCObject* pSender)
{
    m_pInterface->sendbudokan_buy(2);
}
void MB_LayerBudokan::onGoldInspirationClicked(CCObject* pSender)
{
    m_pInterface->sendbudokan_buy(1);
}
void MB_LayerBudokan::onFightClicked(CCObject* pSender)
{
    m_pInterface->sendbudokan_fight();
}
void MB_LayerBudokan::onAutoFightClicked(CCObject* pSender)
{
    
    if (MB_RoleData::getInstance()->getVipLevel() >= 3)
    {
        MB_Message::sharedMB_Message()->showMessage("",30);
        m_pInterface->sendbuduokan_raids();

    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("vip8及以上玩家开放一键扫荡,充值可提升vip等级");
    }
    
}

void MB_LayerBudokan::onRuleClick(CCObject* pSender)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionBudokan);
    if (pWnd)
    {
        pWnd->setShowRoleInfoPanel(true);
        pushWindow(pWnd);
    }
}

//一键扫塔
/*
 message sc_hron_raids[id=11308]{
 required        int8            result      =1;
 // 0 => 扫荡成功
 // 1 => 无可扫荡关卡
 // 2 => 等级不足
 // 3 => vip等级不足
 // 4 => 活动结束了
 // 255 => 支付参数错误
 required        int16           dungeonID   =2;//新的关卡ID
 repeated        p_reward        reward      =3;//战斗奖励
 }
 */
void MB_LayerBudokan::recvbudokan_raids(MB_MsgBuffer* pRecv)
{
    uint8_t result;
    uint16_t data16;
    pRecv->readU8(&result);
    if (result == 0)
    {
        pRecv->readU16(&data16);
        pRecv->readU16(&data16);
        p_reward *read = new p_reward[data16];
        for(int i = 0 ; i < data16 ; i++){
            
            onSetReward(&(read[i]), pRecv);
        }

        MB_LayerBudokanSweep* layer = MB_LayerBudokanSweep::create(read,data16);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_SWEEP);
    }
    else if(result == 1)
    {
        MB_Message::sharedMB_Message()->showMessage("您已经在历史最高层数");
    }
    else if(result == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("等级不足");
    }
    else if(result == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("vip等级不足");
    }
    else if(result == 4)
    {
        MB_Message::sharedMB_Message()->showMessage("活动结束了");
    }
    else if(result == 255)
    {
        MB_Message::sharedMB_Message()->showMessage("支付参数错误");
    }
    
}

void MB_LayerBudokan::onSetReward(p_reward *reward,MB_MsgBuffer* recvPacket){
    
    reward->petExp = NULL;
    reward->item = NULL;
    reward->roleExp = 0;
    
    recvPacket->readU32(&(reward->coin));
    recvPacket->readU32(&(reward->roleExp));
    int16_t petExpLength;
    recvPacket->readU16(&petExpLength);
    p_petExp *movePoint = NULL;
    for (int i= 0; i < petExpLength ; i++) {
        p_petExp * temp =(p_petExp *)malloc(sizeof(p_petExp));
        temp ->next = NULL;
        recvPacket->readU8(&(temp->petPos));
        recvPacket->readU32(&(temp->addExp));
        recvPacket->readU8(&(temp->isUpgraded));
        if ( reward->petExp == NULL) {
            
            reward->petExp = movePoint = temp;
            
        }else {
            movePoint->next = temp;
            movePoint = temp;
        }
        
    }
    recvPacket->readU32(&(reward->gold));
    p_item_view *moveItem = NULL;
    int16_t itemLength;
    recvPacket->readU16(&itemLength);
    for (int i= 0; i < itemLength ; i++) {
        p_item_view *item = (p_item_view *)malloc(sizeof(p_item_view));
        item->next = NULL;
        recvPacket->readU16(&item->itemTypeId);
        uint8_t data8;
        recvPacket->readU8(&data8);
        item->itemLevel = data8;
        recvPacket->readU8(&data8);
        item->itemRank = data8;
        recvPacket->readU16(&item->itemNum);
        
        if (reward->item == NULL) {
            reward->item = moveItem =item;
            
        }else {
            
            moveItem->next = item;
            moveItem = item;
        }
    }
    
    recvPacket->readU16(&itemLength);
    for (int i= 0; i < itemLength ; i++)
    {
        p_item_view *item = (p_item_view *)malloc(sizeof(p_item_view));
        item->next = NULL;
        recvPacket->readU16(&item->itemRank);
        recvPacket->readU16(&item->itemLevel);
        recvPacket->readU16(&item->itemTypeId);
        item->itemNum = -1;
        if (reward->item == NULL) {
            reward->item = moveItem =item;
        }else{
            
            moveItem->next = item;
            moveItem = item;
        }
    }
    recvPacket->readU32(&(reward->reputation));
}

