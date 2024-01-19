//
//  MB_LayerHome.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-9.
//
//

#include "MB_LayerHome.h"
#include "MB_SceneMain.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerPackage.h"
#include "MB_NodeRewardCard.h"
#include "MB_LayerRewardMoreCard.h"
#include "MB_LayerChatMain.h"
#include "MB_NodeHoverEntry.h"
#include "MB_NodePetHome.h"
#include "MB_FunctionEntranceWnd.h"
#include "MB_ServerRewardData.h"
#include "MB_AbsolvedInterface.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_AchievementComplate.h"
#include "MB_LayerWorldBossMain.h"
#include "MB_PayShopInterface.h"
#define SPLITE_DELTA    50

MB_LayerHome::MB_LayerHome()
{
    isYueKa = false;
    m_pworldBossStar = NULL;
    m_pworldBossTime = NULL;
    m_pWorldBossBtn = NULL;
    node_worldBoss = NULL;
    m_pToAddNode = NULL;
    moveDown= NULL;
    m_pSCBtn = NULL;
    moveUp= NULL;
    m_pVipLevelSpr = NULL;
    sceneNode = NULL;
    isTouchLeftMove = false;
    m_pCloseJS = NULL;
    m_pCardName = NULL;
    m_pCardIcon = NULL;
    m_pLeft = NULL;
    m_pRight = NULL;
    m_pLeftLong = NULL;
    m_pXiangxi = NULL;
    //    m_pNodeKingStatue = NULL;
    m_pNodeReward = NULL;
    m_pNodeEmail = NULL;
    m_pFightPower = NULL;
    m_pNodeVipPack = NULL;
    m_pNodeCharge = NULL;
    m_pNodeDaily = NULL;
    //    m_pNodeHomeLand = NULL;
    m_pNodeActivaty = NULL;
    m_pNodeYeShiJie = NULL;
    m_pNodePic = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
    m_bShowEXP = true;
    m_pNodeGift = NULL;
    
    node_flag_yljk = NULL;
    node_flag_mx = NULL;
    flag_yljk = NULL;
    flag_mx = NULL;
    node_flag_main= NULL;
    flag_main= NULL;
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        m_iconHomeNode[i] = NULL;
    }
    m_pNodeKing = NULL;
    m_pNodeAprCard = NULL;
    isOn = true;
    
    SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_LayerHome);
    MB_LayerChatMain::SetChatMainVisible(true, "MB_LayerHome");
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerHome",true);
}

MB_LayerHome::~MB_LayerHome()
{
    CC_SAFE_RELEASE_NULL(m_pworldBossStar);
    CC_SAFE_RELEASE_NULL(m_pworldBossTime);
    CC_SAFE_RELEASE_NULL(m_pWorldBossBtn);
    CC_SAFE_RELEASE_NULL(node_worldBoss);
    CC_SAFE_RELEASE_NULL(m_pToAddNode);
    CC_SAFE_RELEASE_NULL(moveDown);
    CC_SAFE_RELEASE_NULL(moveUp);
    CC_SAFE_RELEASE_NULL(m_pVipLevelSpr);
    CC_SAFE_RELEASE_NULL(m_pCloseJS);
    CC_SAFE_RELEASE_NULL(m_pLeft);
    CC_SAFE_RELEASE_NULL(m_pRight);
    CC_SAFE_RELEASE_NULL(m_pLeftLong);
    CC_SAFE_RELEASE_NULL(m_pCardName);
    CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pNodeEmail);
    CC_SAFE_RELEASE_NULL(m_pCardIcon);
    CC_SAFE_RELEASE_NULL(m_pNodeActivaty);
    CC_SAFE_RELEASE_NULL(m_pXiangxi);
    CC_SAFE_RELEASE_NULL(m_pSCBtn);
    
    CC_SAFE_RELEASE_NULL(m_pFightPower);
    CC_SAFE_RELEASE_NULL(m_pNodeVipPack);
    CC_SAFE_RELEASE_NULL(m_pNodeCharge);
    CC_SAFE_RELEASE_NULL(node_flag_yljk);
    CC_SAFE_RELEASE_NULL(node_flag_mx);
    CC_SAFE_RELEASE_NULL(flag_yljk);
    CC_SAFE_RELEASE_NULL(flag_mx);
    CC_SAFE_RELEASE_NULL(m_pNodeDaily);
    CC_SAFE_RELEASE_NULL(m_pNodeYeShiJie);
    CC_SAFE_RELEASE_NULL(m_pNodePic);
    CC_SAFE_RELEASE_NULL(m_pNodeGift);
    CC_SAFE_RELEASE_NULL(m_pNodeKing);
    CC_SAFE_RELEASE_NULL(m_pNodeAprCard);
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        CC_SAFE_RELEASE_NULL(m_iconHomeNode[i]);
    }
    CC_SAFE_RELEASE_NULL(node_flag_main);
    CC_SAFE_RELEASE_NULL(flag_main);
    
    SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerHome");
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerHome",false);
}



void MB_LayerHome::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    {
        onResetWnd();
    }
}
bool MB_LayerHome::init()
{
    CCLayer::init();
    this->setTouchEnabled(true);
    CCNode* rootNode = loadResource("res/main_layer_background.ccbi");
    if (rootNode)
    {
        removeAllChildren();
        addChild(rootNode);
        onResetWnd();
        leftP = m_pLeft->getPosition();
        rightP = m_pRight->getPosition();
        leftLongP = m_pLeftLong->getPosition();
        closeJSP = m_pCloseJS->getPosition();
        xiangxiP = m_pXiangxi->getPosition();
        upP = moveUp->getPosition();
        downP = moveDown->getPosition();
        
        CCSprite* spr = (CCSprite*)m_pNodeKing->getChildByTag(99);
        leftMoveRect = CCRectApplyAffineTransform(CCRect(spr->getPositionX()-spr->getContentSize().width *.5f,spr->getPositionY()-spr->getContentSize().height*.5f,spr->getContentSize().width,spr->getContentSize().height), m_pNodeKing->nodeToParentTransform());
        
        
               CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shangcheng.plist"); m_pVipLevelSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("icon_vip_%d.png",MB_RoleData::getInstance()->getVipLevel())->getCString()));
        
        
        
        NSGameHelper::changeParent(m_pWorldBossBtn, m_pToAddNode);
        m_pToAddNode->setPosition(m_pWorldBossBtn->getContentSize()/2);
        
        m_pworldBossStar->runAction(CCRepeatForever::create( CCSequence::create(CCScaleTo::create(2,.85f),CCEaseElasticInOut::create(CCScaleTo::create(.4f, .9f,1), .2f) ,CCScaleTo::create(.5f, .85f,.9f),CCEaseElasticOut::create(CCScaleTo::create(.4f, 1.1f,1.1f),0.01f),NULL)));

        
        MB_EventMgr::getInstence()->sendworldboss_open();
        schedule(schedule_selector(MB_LayerHome::tickCountToStart2),.1f);
        return initFunctions();
    }

    return false;
}
void MB_LayerHome::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    MB_Audio::getInstance()->playNormalBgm();
    
    MB_FunctionItem* pItem =  MB_FunctionConfigure::getInstance()->queryFunctionItemByType(kFunctionYeShiJie);
    if (pItem)
    {
        if(pItem->getNeedLevel()<=MB_RoleData::getInstance()->getLevel())
        {
            iTimes = MB_RoleData::getInstance()->getDiscoveryTimes();
            if (iTimes > 0)
            {
                node_flag_main->setVisible(true);
                char databuf[20];
                sprintf(databuf,"%d",iTimes);
                flag_main->setString(databuf);
                
                node_flag_mx->setVisible(true);
                flag_mx->setString(databuf);
            }
            else
            {
                node_flag_main->setVisible(false);
                node_flag_mx->setVisible(false);
            }
        }
        else
        {
            node_flag_main->setVisible(false);
            node_flag_mx->setVisible(false);
        }
    }
    
    int yljkLimit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeCoin)-MB_RoleData::getInstance()->getCoinBuyTimes();
    iTimes+=yljkLimit;
    if (yljkLimit>0) {
        node_flag_yljk->setVisible(true);
        node_flag_main->setVisible(true);
        char databuf[20];
        sprintf(databuf,"%d",iTimes);
        flag_main->setString(databuf);
        
        sprintf(databuf,"%d",yljkLimit);
        flag_yljk->setString(databuf);
    }else
    {
         node_flag_yljk->setVisible(false);
        if(iTimes==0)
        {
            node_flag_main->setVisible(false);
        }
    }
    
    CCFunctionInterface* pInterface = NULL;
    if (MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop, &pInterface))
    {
        MB_PayShopInterface* ppayinterface = dynamic_cast<MB_PayShopInterface*>(pInterface);
        
        if (ppayinterface && ppayinterface->getDayPayMul() == 0)
        {
            isYueKa = true;
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hometown.plist");
            CCSpriteFrame *pSprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_icn_yueka.png");
            if (pSprFrame)
            {
                m_pSCBtn->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateNormal);
                m_pSCBtn->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateHighlighted);
                m_pSCBtn->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateSelected);
                m_pSCBtn->setBackgroundSpriteFrameForState(pSprFrame, CCControlStateDisabled);
                m_pSCBtn->setPreferredSize(CCSize(110,79));
                m_pSCBtn->setPositionY(-3);
            }
        }
    }
}
void MB_LayerHome::onResetWnd()
{
    updateNode(m_pNodeEmail);
    updateNode(m_pNodeGift);
    updateNode(m_pNodeVipPack);
    updateNode(m_pNodeCharge);
    updateNode(m_pNodeDaily);
    updateNode(m_pNodeActivaty);
    updateNode(m_pNodeYeShiJie);
    updateNode(m_pNodePic);
    updateNode(m_pNodeKing);
    updateNode(m_pNodeAprCard);
    
    char databuf[50];
    memset(databuf, 0, sizeof(char)* 40);
    sprintf(databuf, "%llu", MB_TeamData::getInstance()->getFightPower());
    m_pFightPower->setString(databuf);
    
    bool b = false;
    MB_PetData * iconData = NULL;
    for (int i = 0 ; i <CARD_IN_GAME;  i++) {
        MB_PetData *  data;
        if(teamV.size()==0)
        {
            data = MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet;
        }else
        {
            if (teamV[i]==-1) {
                data = NULL;
            }else
            {
                data = MB_PetMgr::getInstance()->getPetDataByUID(teamV[i]);
            }
        }
        if(data != NULL){
            if (iconData==NULL) {
                iconData = data;
            }
            
            if (!b) {
                if (nowHomeShowPetTypeID==0) {
                    nowHomeShowPetTypeID = data->getPetTypeID();
                    b = true;
                    setCardIcon(data);
                }else if(data->getPetTypeID() == nowHomeShowPetTypeID)
                {
                    b = true;
                    setCardIcon(data);
                }
            }
            m_iconHomeNode[i]->addChild(MB_NodePetHome::create(this,data->getPetID()));
        }else
        {
            m_iconHomeNode[i]->addChild(MB_NodePetHome::create(NULL,-1));
        }
    }
    if (!b) {
        setCardIcon(iconData);
    }
}
void MB_LayerHome::setCardIcon(MB_PetData *  data)
{
    m_pPetData = data;
    MB_PetTemplate *petTempelete = data->getTemplete();
    CCTexture2D *textrue = CCTextureCache::sharedTextureCache()->addImage(petTempelete->getPetCard(data->getPetQuallity()/10+1));
    if(textrue !=NULL){
        CCSpriteFrame *frame  =CCSpriteFrame::createWithTexture(textrue,CCRect(0,0,textrue->getContentSize().width,textrue->getContentSize().height));
        m_pCardIcon->setDisplayFrame(frame);
    }
    char databuf[50];
    MB_PetMgr::getInstance()->getPetRealName(databuf, data->getPetID());
    m_pCardName->setString(databuf);
}
void MB_LayerHome::updateNode(CCNode* pNode)
{
    if (pNode==NULL || pNode->getChildrenCount()==0)
    {
        return;
    }
    
    MB_ResWindow* pWnd = dynamic_cast<MB_ResWindow*>(pNode->getChildren()->objectAtIndex(0));
    if (pWnd)
    {
        pWnd->onResetWnd();
    }
}

bool MB_LayerHome::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode))return true;
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pworldBossStar", CCNode*, m_pworldBossStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pworldBossTime", CCLabelBMFont*, m_pworldBossTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pWorldBossBtn", CCNode*, m_pWorldBossBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_worldBoss", CCNode*, node_worldBoss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToAddNode", CCNode*, m_pToAddNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCloseJS", CCNode*, m_pCloseJS);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_email", CCNode*, m_pNodeEmail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCardIcon", CCSprite*, m_pCardIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCardName", CCLabelTTF*, m_pCardName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pXiangxi", CCNode*, m_pXiangxi);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipLevelSpr", CCSprite*, m_pVipLevelSpr);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFightPower", CCLabelBMFont*, m_pFightPower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeVipPack", CCNode*, m_pNodeVipPack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeCharge", CCNode*, m_pNodeCharge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_activety", CCNode*, m_pNodeActivaty);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_daily", CCNode*, m_pNodeDaily);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_yeshijie", CCNode*, m_pNodeYeShiJie);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_Pic",CCNode*, m_pNodePic);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_gift",CCNode*, m_pNodeGift);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_spriteking",CCNode*,m_pNodeKing);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_spriteAprCard",CCNode*,m_pNodeAprCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLeft",CCNode*,m_pLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRight",CCNode*,m_pRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLeftLong",CCNode*,m_pLeftLong);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "moveDown",CCNode*,moveDown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "moveUp",CCNode*,moveUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_main",CCNode*,node_flag_main);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_main", CCLabelBMFont*, flag_main);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSCBtn", CCControlButton*, m_pSCBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_yljk",CCNode*,node_flag_yljk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_yljk", CCLabelBMFont*, flag_yljk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_flag_mx",CCNode*,node_flag_mx);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "flag_mx", CCLabelBMFont*, flag_mx);
    char star[]= "m_pIconHome0";
    for (int i = 0 ; i < CARD_IN_GAME; i++) {
        
        star[11] = '0' +i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,star,CCNode *,m_iconHomeNode[i]);
    }
    return false;
}

SEL_MenuHandler MB_LayerHome::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_LayerHome::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCardInfoClicked",MB_LayerHome::onCardInfoClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCloseJSClicked",MB_LayerHome::onCloseJSClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCallCardClick",MB_LayerHome::onCallCardClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onWorldBossClicked",MB_LayerHome::onWorldBossClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onMXClicked",MB_LayerHome::onMXClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onYLJKClicked",MB_LayerHome::onYLJKClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onSCClicked",MB_LayerHome::onSCClicked);
    return NULL;
}

void MB_LayerHome::onCardInfoClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)//
    {
        pScene->replaceSubLayer(MB_LayerPetDetail::create(m_pPetData,true));
    }
}

void MB_LayerHome::onMXClicked(CCObject* pSender){
   MB_FunctionMgr::getInstance()->goFunction(kFunctionMaoXian, this);//冒险
}
void MB_LayerHome::onYLJKClicked(CCObject* pSender){
    MB_FunctionMgr::getInstance()->goFunction(kActivatyChangeCoin, this);//妖灵金库
}
void MB_LayerHome::onSCClicked(CCObject* pSender){
    if (isYueKa) {
        MB_RoleData::getInstance()->goCharge(5);//月卡
    }else
    {
        MB_RoleData::getInstance()->goCharge(3);//充值
    }
}
void MB_LayerHome::onCloseJSClicked(CCObject* pSender)
{
    onAndOffBtn();
}

bool MB_LayerHome::initFunctions()
{
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionEmail, m_pNodeEmail);
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionPayShop, m_pNodeCharge);
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionIngotsShop, m_pNodeVipPack);
    
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionDaily, m_pNodeDaily);
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionActivaty, m_pNodeActivaty);
    
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionYeShiJie, m_pNodeYeShiJie);
    setYDSJ();
    
    
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionPic, m_pNodePic);
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionAbsolved,m_pNodeKing);
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionJianShang,m_pNodeAprCard);
    
    MB_FunctionMgr::getInstance()->bindEntry2Target(kFunctionGongGao, m_pNodeGift);
    
    ((MB_FunctionEntranceWnd*)m_pNodeKing->getChildren()->objectAtIndex(m_pNodeKing->getChildrenCount()-1))->m_pScroller->setTouchPriority(129);
    return true;
}


void MB_LayerHome::setYDSJ()
{
    int count =m_pNodeYeShiJie->getChildrenCount();
    CCArray* children = m_pNodeYeShiJie->getChildren();
    CCNode* pN =dynamic_cast<MB_NodeHoverEntry*>(children->objectAtIndex(count-1))->m_pMenuItemImage;
    CCPoint p =ccp(pN->getContentSize().width/2,pN->getContentSize().height/2 );
    for (int i = 3; i<count-1; i++) {
        CCNode* pNode =dynamic_cast<CCNode*>(children->objectAtIndex(3));
        pNode->retain();
        pNode->removeFromParentAndCleanup(false);
        pN->addChild(pNode);
        pNode->release();
        pNode->setPosition(pNode->getPosition()+  p);
    }
}
void MB_LayerHome::registerWithTouchDispatcher(void){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 128 , false);
}
bool MB_LayerHome::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (leftMoveRect.containsPoint(pTouch->getLocation())) {
        isTouchLeftMove = true;
        if (sceneNode==NULL) {
            sceneNode = CCDirector::sharedDirector()->getRunningScene();
        }
    }
    return true;
}
void MB_LayerHome::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint point = pTouch->getDelta();
    if (isTouchLeftMove) {
        sceneNode->setPositionX(sceneNode->getPositionX() + point.x);
        if (sceneNode->getPositionX()>0) {
            sceneNode->setPositionX(0);
        }
    }else
    {
        m_pCardIcon->setPosition(ccp( m_pCardIcon->getPositionX() + point.x, m_pCardIcon->getPositionY() + point.y));
    }
}
void MB_LayerHome::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchLeftMove) {
        addChild(NSGameHelper::createDisableTouchLayer(),0,999);// 防止点穿
        float winWidth = CCDirector::sharedDirector()->getWinSize().width;
        if (m_bIsCanToChapter) {
            if (fabs(sceneNode->getPositionX()) < 5) {
                m_bIsCanToChapter = true;
            }else
            {
                m_bIsCanToChapter = false;
            }
            if (sceneNode->getPositionX()>-winWidth/4) {
                sceneNode->runAction(CCSequence::create(CCMoveTo::create(-sceneNode->getPositionX()/MOVESCENESPEED , ccp(0,0)) ,CCCallFunc::create(this, callfunc_selector(MB_LayerHome::finish)),NULL)  );
            }else
            {
                
                sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(-winWidth-sceneNode->getPositionX())/MOVESCENESPEED , ccp(-winWidth,0)) ,CCCallFunc::create(this, callfunc_selector(MB_LayerHome::finish2)),NULL)  );
            }
        }
        isTouchLeftMove = false;
    }
}

void MB_LayerHome::finish()
{
    removeChildByTag(999);
    m_bIsCanToChapter = true;
}
void MB_LayerHome::finish2()
{
    NSGameFunction::CCFunctionInterface* pInterface = NULL;
    MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
    MB_AbsolvedInterface* pInstance = (MB_AbsolvedInterface*)pInterface;
    if (pInterface)
    {
        MB_ChapterProgress* pProgress = pInstance->getChapterProgressByType(pInstance->getCurrentType());
        MB_ChapterPage* pPage = NULL;
        MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(pInstance->getCurrentType(), pProgress->getChapterId(), &pPage);
        m_bToPageID = pPage->getPageId();
        m_bNowPassPageID = pPage->getPageId();
        pInterface->onEntryClicked(this);
    }
    float winWidth = CCDirector::sharedDirector()->getWinSize().width;
    sceneNode->setPositionX(winWidth);
    sceneNode->runAction(CCSequence::create(CCMoveTo::create(winWidth/MOVESCENESPEED , ccp(0,0)) ,NULL)  );
    m_bIsCanToChapter = true;
}
void MB_LayerHome::onMsgRecv(CCNode* node, SocketResponse* response){
    
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_GER_REFRESH_POWER:
        {
            char databuf[100] = { 0 };
            sprintf(databuf, "%llu", MB_TeamData::getInstance()->getFightPower());
            if (m_pFightPower)m_pFightPower->setString(databuf);
        }
            break;
    }
    return;
    
}
void MB_LayerHome::onAndOffBtn()
{
    isOn = !isOn;
    CCSize sz = CCDirector::sharedDirector()->getWinSize();
    CCNode* pChatNode = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_CHAT_TAG);
    CCNode* LayerCommand = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND);
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    CCNode* lrih =pScene->m_pLayerRoleInfoHeader;
    
    if (isOn) {
        m_pCloseJS->runAction(CCMoveTo::create(.3f, closeJSP));
        m_pXiangxi->runAction(CCMoveTo::create(.3f, xiangxiP));
        m_pLeft->runAction(CCMoveTo::create(.3f, leftP));
        m_pRight->runAction(CCMoveTo::create(.3f, rightP));
        m_pLeftLong->runAction(CCMoveTo::create(.3f, leftLongP));
        pChatNode->runAction(CCMoveTo::create(.3f, ccp(0,0)));
        LayerCommand->runAction(CCMoveTo::create(.3f, ccp(0,0)));
        lrih->runAction(CCMoveTo::create(.3f, ccp(0,0)));
        moveUp->runAction(CCMoveTo::create(.3f, upP));
        moveDown->runAction(CCMoveTo::create(.3f, downP));
        
    }else
    {
        m_pCloseJS->runAction(CCMoveTo::create(.3f,ccp(closeJSP.x-100,closeJSP.y)));
        m_pXiangxi->setPositionX(xiangxiP.x-300);
        m_pLeft->setPositionX(leftP.x-200);
        m_pRight->setPositionX(rightP.x+200);
        m_pLeftLong->setPositionX(leftLongP.x-450);
        pChatNode->setPositionX(-200);
        LayerCommand->setPositionY(-200);
        lrih->setPositionY(200);
        moveUp->setPositionY(upP.y+320);
        moveDown->setPositionY(downP.y- 320);
        
    }
}
void MB_LayerHome::onCallCardClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionToy, this);
}
void MB_LayerHome::onWorldBossClicked(CCObject* pSender)
{
    int levelLimit = MB_FunctionConfigure::getInstance()->getFunctionLimitLevel(401);
    //等级达到
    if(MB_RoleData::getInstance()->getLevel() >= levelLimit)
    {
        NSGameFunction::CCFunctionInterface *pInterface = NULL;
        MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionResearchInstitute, &pInterface);
        if (pInterface)
        {
            MB_LayerWorldBossMain* lwbm = (MB_LayerWorldBossMain*)pInterface->createFunctionDialog();
            lwbm->isToHome = true;
            NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(lwbm);
        }
    }else
    {
        char databuf[40];
        sprintf(databuf, "此功能%d级开放",levelLimit);
        MB_Message::sharedMB_Message()->showMessage(databuf);
    }
}
void MB_LayerHome::tickCountToStart(float dt){
    
    int timetick = m_nWorldBossBeginTime - MB_ClientSocket::getInstance()->getServerTime();
    
    if (timetick < 0) {
        
        timetick = 0;
    }
    char databuf[40];
    sprintf(databuf, "%02d:%02d:%02d",timetick/3600,timetick%3600/60,timetick%3600%60);
    m_pworldBossTime->setString(databuf);
}
void MB_LayerHome::tickCountToStart2(float dt)
{
    MB_EventData* ed = (MB_EventData* )MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(0);
    if (ed->getBeginTime()!=0) {
        unschedule(schedule_selector(MB_LayerHome::tickCountToStart2));

        if (ed->getIsOpen()) {
            m_pworldBossTime->setVisible(false);
        }else
        {
            m_pworldBossTime->setVisible(true);
            m_nWorldBossBeginTime = ed->getBeginTime();
            schedule(schedule_selector(MB_LayerHome::tickCountToStart),1);
            tickCountToStart(0);
        }
    }
}

void MB_LayerHome::tick(float dt)
{
    MB_FunctionMainWnd::tick(dt);
    
    //领取体力
    {
        static float fTemp = 0;
        fTemp += dt;
        if(fTemp >= 1)
        {
            fTemp = 0;
            bool bIsCanGive = false;
            time_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
            MB_MoneyEventEnergy*  pEvnet1 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(0);
            MB_MoneyEventEnergy*  pEvnet2 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(1);
            MB_MoneyEventEnergy*  pEvnet3 =  MB_MoneyEevntMgr::getInstance()->getEventEnergyByIndex(2);
            if (nowtime  >= pEvnet1->getStartTime() && nowtime  < pEvnet1->getEnTime()) {
                
                if(pEvnet1->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy1_2") == false){
                    bIsCanGive = true;
                }
                
            }
            else if(nowtime >= pEvnet2->getStartTime() && nowtime  <  pEvnet2->getEnTime() && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy2_2") == false){
                
                if(pEvnet2->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy2_2") == false)
                {
                    bIsCanGive = true;
                }
            }
            else if(nowtime >= pEvnet3->getStartTime() && nowtime  <  pEvnet3->getEnTime() && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy3_2") == false){
                
                if(pEvnet3->getIsGet() != 2 && CCUserDefault::sharedUserDefault()->getBoolForKey("isClickEnergy3_2") == false)
                {
                    bIsCanGive = true;
                }
            }
            if (bIsCanGive) {
                node_flag_main->setVisible(bIsCanGive);
                char databuf[100];
                sprintf(databuf,"%d",iTimes+1);
                flag_main->setString(databuf);
            }else if(iTimes==0)
            {
                node_flag_main->setVisible(bIsCanGive);
            }
            if (pEvnet1->getIsGet() == 2 && pEvnet2->getIsGet() == 2 && pEvnet3->getIsGet() == 2)
            {
                this->unschedule(schedule_selector(MB_ResWindow::tick));
            }
        }
    }
}

