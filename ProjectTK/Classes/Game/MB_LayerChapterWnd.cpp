//
//  MB_LayerChapterWnd.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#include "MB_LayerChapterWnd.h"
#include "MB_ChapterInterface.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_ChapterData.h"
#include "MB_ServerRewardData.h"
#include "MB_CcbAutoMemberWnd.h"
#include "MB_NodeDungeonUnit.h"
#include "MB_ItemData.h"
#include "MB_AbsolvedInterface.h"
#include "MB_LayerAbsolvedPage.h"
#include "MB_SynopsisConfig.h"
#include "MB_LayerStory.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_GlobelModalDlgMsgQueue.h"
#include "Game.h"
#include "MB_LayerSweep.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_NodePerfectReward.h"
#include "MB_LayerChapterRank.h"
#include "MB_NodeRewardCard.h"
#include "MB_NodePetDuiWu.h"
#include "MB_LayerChatMain.h"
#include "MB_ScrollBg.h"
#include "MB_LayerPetEquipment.h"
MB_LayerChapterWnd::MB_LayerChapterWnd()
{
    m_pBg = NULL;
    m_pWuXianLabel = NULL;
    m_pRootLine = NULL;
    m_pItemMoveNode = NULL;
    m_pMoney= NULL;
    m_pExp= NULL;
    m_pLefttimes= NULL;
    m_pBtnSweep= NULL;
    m_pItem0= NULL;
    m_pItem1= NULL;
    m_pChapterName2 = NULL;
    m_pNodeScroller = NULL;
    m_pNodeContainer = NULL;
    m_pNowdata = NULL;
    m_pScrollView = NULL;
    m_pXuanGuan = NULL;
    m_pReady = NULL;
    m_nDungeonId = 0;
    m_pDungeonList = new CCArray;
    m_bShowTutorial = false;
    m_bPerfect = false;
    m_bComplate = false;
    isToXuanGuan = true;
    m_pTitle = NULL;
    selectIndex = -1;
    //    m_bShowHomeButton = true;
    m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_BATTLE_CHALLENGE, MB_LayerChapterWnd);
    SOCKET_MSG_REGIST(SC_BATTLE_PERFECT_REWARD, MB_LayerChapterWnd);
    
    for (int i=0;i<3; i++) {
        m_pStar[i] = NULL;
    }
    for (int i=0;i<10; i++) {
        m_pPassP[i] = NULL;
    }
    
}

MB_LayerChapterWnd::~MB_LayerChapterWnd()
{
    CC_SAFE_RELEASE_NULL(m_pBg);
    CC_SAFE_RELEASE_NULL(m_pWuXianLabel);
    CC_SAFE_RELEASE_NULL(m_pRootLine);
    CC_SAFE_RELEASE_NULL(m_pItemMoveNode);
    CC_SAFE_RELEASE_NULL(m_pMoney);
    CC_SAFE_RELEASE_NULL(m_pExp);
    CC_SAFE_RELEASE_NULL(m_pLefttimes);
    CC_SAFE_RELEASE_NULL(m_pBtnSweep);
    CC_SAFE_RELEASE_NULL(m_pItem0);
    CC_SAFE_RELEASE_NULL(m_pItem1);
    CC_SAFE_RELEASE_NULL(m_pNodeContainer);
    CC_SAFE_RELEASE_NULL(m_pDungeonList);
    SOCKET_MSG_UNREGIST(SC_BATTLE_CHALLENGE);
    SOCKET_MSG_UNREGIST(SC_BATTLE_PERFECT_REWARD);
    CC_SAFE_RELEASE_NULL(m_pXuanGuan);
    CC_SAFE_RELEASE_NULL(m_pReady);
    CC_SAFE_RELEASE_NULL(m_pNodeScroller);
    CC_SAFE_RELEASE_NULL(m_pChapterName2);
    CC_SAFE_RELEASE_NULL(m_pTitle);
    
    for (int i=0;i<3; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    
    for (int i=0;i<10; i++) {
        CC_SAFE_RELEASE_NULL(m_pPassP[i]);
    }
}
bool MB_LayerChapterWnd::init()
{
    CCNode* pNode = loadResource("res/gui_main_chapterlist.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer12());// 防止点穿
        addChild(pNode);
        MB_ChapterInterface* pInstance = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
        int tempInt = pInstance->getChapterId()%5;if(tempInt==0)tempInt=1;
        pRootNode2 = loadResource(CCString::createWithFormat("res/gui_main_chapterlistPos%d.ccbi",tempInt)->getCString() );
        m_pBg->addChild(pRootNode2);
        lastItemMoveNodeX = m_pItemMoveNode->getPositionX();
        m_bPerfect = pInstance->getBattleInfo()->getPerfect();
        m_bComplate = pInstance->complated();
        initConfigure();
        NSGameHelper::adjustScrollNode(m_pNodeContainer);
        m_pScrollView = CCScrollView::create(m_pNodeContainer->getContentSize());
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
//        m_pScrollView->setSwaller(false);
        m_pNodeContainer->addChild(m_pScrollView);
        m_nLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("PreLevel");
        checkLevelUp();
        CCUserDefault::sharedUserDefault()->getIntegerForKey("PreLevel", MB_RoleData::getInstance()->getLevel());
        
        m_pScrollView->setContentSize(m_pNodeContainer->getContentSize()*1.4f);
        for (int i = 0; i<m_pDungeonList->count(); i++) {
            MB_DungeonData* data = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(i));
            int tutorialIndex = MB_TutorialMgr::getInstance()->getCellIndex();
            MB_NodeDungeonUnit* pUnit =MB_NodeDungeonUnit::create(data, kChapterTypeNormal,i == tutorialIndex);
            pUnit->setTag(999+i);
            pUnit->setDataRouse(this);
            m_pPassP[i]->addChild(pUnit,99);
        }
        
        NSGameHelper::changeParent(m_pScrollView, m_pRootLine);
        m_pRootLine->setPosition( ccp(m_pRootLine->getPositionX(),m_pRootLine->getPositionY())- m_pRootLine->getContentSize()/2);
        
        onResetWnd();
        return true;
    }
    return false;
}
void MB_LayerChapterWnd::onExit()
{
    MB_Audio::getInstance()->playNormalBgm();
    MB_FunctionMainWnd::onExit();
}

void MB_LayerChapterWnd::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_Xuanguan);
}

void MB_LayerChapterWnd::onClickTZDW(CCObject* pSender)
{
    MB_LayerPetEquipment* layer = MB_LayerPetEquipment::create();
    if (m_pSubLayer == NULL) {
        layer->isPopWindow = true;
        pushWindow(layer,true);
        isToXuanGuan = false;
    }
}
void MB_LayerChapterWnd::setReadyUI()
{
    TutorialTriggerComplete;
    MB_DungeonData* m_data = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(selectIndex));
    for (int i = 0; i < 3; i++) {
        m_pStar[i]->setVisible(i<m_data->getBestScore());
    }
    char databuf[40];
    sprintf(databuf, "%d",m_data->getCoin());
    m_pMoney->setString(databuf);
    sprintf(databuf, "%d",m_data->getExpRole());
    m_pExp->setString(databuf);
    
    
    sprintf(databuf, "%d / %d",m_data->getLeftTime(),m_data->getMaxTimes());
    m_pLefttimes->setString(databuf);
    
    if(dynamic_cast<MB_ExpDungeonData *>(m_data) !=  NULL){
        m_pLefttimes->setVisible(false);
        m_pWuXianLabel->setVisible(true);
        NSGameHelper::setBtnFrame(m_pBtnSweep,"xuanguan.plist","btn_wipeout_2.png");
    }
    else
    {
        m_pLefttimes->setVisible(true);
        m_pWuXianLabel->setVisible(false);
        int best_score = m_data->getBestScore();
        int level = MB_RoleData::getInstance()->getLevel();
        int level_limit = MB_RoleData::getInstance()->getRoleSweepLimit();
        if(best_score == 3 && level >= level_limit ){
            NSGameHelper::setBtnFrame(m_pBtnSweep,"xuanguan.plist","btn_wipeout.png");
            
        }else {
            NSGameHelper::setBtnFrame(m_pBtnSweep,"xuanguan.plist","btn_wipeout_2.png");
        }
    }
    
    int tempIndex = 0;
    m_pItem0->removeAllChildren();
    MB_ItemTemplate * item = MB_ItemMgr::getInstance()->getItemTemplateByID(m_data->getDropItem1());
    if (item != NULL) {
        tempIndex++;
        MB_NodeItem *itemIcon = MB_NodeItem::create(m_data->getDropItem1());
        m_pItem0->addChild(itemIcon);
    }
    m_pItem1->removeAllChildren();
    item = MB_ItemMgr::getInstance()->getItemTemplateByID(m_data->getDropItem2());
    if (item != NULL) {
        tempIndex++;
        MB_NodeItem *itemIcon = MB_NodeItem::create(m_data->getDropItem2());
        m_pItem1->addChild(itemIcon);
    }
    
    m_pItemMoveNode->setPositionX(lastItemMoveNodeX- 56.7f*tempIndex);
}
bool MB_LayerChapterWnd::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pDataSource = dynamic_cast<MB_ChapterInterface*>(pDataSource);
    return m_pDataSource != NULL;
}

bool MB_LayerChapterWnd::hasPassed()
{
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInterface)
    {
        return pInterface->complated();
    }
    return false;
}

void MB_LayerChapterWnd::onResetWnd()
{
    m_pNodeScroller->removeAllChildren();
    MB_NodePetDuiWu* npdw;
    if(teamV.size()==0)
    {
        for (int i = 0; i < CARD_IN_GAME; i++) {
            if (MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet!=NULL){
                npdw = MB_NodePetDuiWu::create(MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pPet->getPetID(),true,false);
            }
            else {
                npdw = MB_NodePetDuiWu::create(-1);
            }
            npdw->setTag(i+100);
            npdw->opx2 = npdw->m_nWidth*(.5f + i);
            npdw->opy2 = npdw->getPositionY();
            npdw->setPositionX(npdw->opx2);
            m_pNodeScroller->addChild(npdw);
            
            CCSprite* spr =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_team_empty.png"));
            spr->setPosition(npdw->getPosition());
            m_pNodeScroller->addChild(spr,-1);
        }
    }else
    {
        for (int i = 0; i < CARD_IN_GAME; i++) {
            if (teamV[i]!=-1) {
                npdw = MB_NodePetDuiWu::create(teamV[i],true,false);
            }else
            {
                npdw = MB_NodePetDuiWu::create(-1);
            }
            npdw->setTag(i+100);
            npdw->opx2 = npdw->m_nWidth*(.5f + i);
            npdw->opy2 = npdw->getPositionY();
            npdw->setPositionX(npdw->opx2);
            m_pNodeScroller->addChild(npdw);
            
            CCSprite* spr =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("slot_team_empty.png"));
            spr->setPosition(npdw->getPosition());
            m_pNodeScroller->addChild(spr,-1);
        }
    }
    m_pNodeScroller->setContentSize(CCSize( npdw->m_nWidth*6,m_pNodeScroller->getContentSize().height));
}


void MB_LayerChapterWnd::onEnter()
{
    MB_ResWindow::onEnter();
    if (global_isRePlay) {
        schedule(schedule_selector(MB_LayerChapterWnd::updateToRetry));
    }
    if (m_bIsToHome && MB_GlobelModalDlgMsgQueue::getInstance()->msgCount()==0) {
        m_bIsToHome = false;
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }
    else if(isToXuanGuan)
    {
        swithXuanGuanOrReady(true);
        for (int i = 0; i<m_pDungeonList->count(); i++) {
            MB_DungeonData* data = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(i));
            MB_NodeDungeonUnit* pUnit = (MB_NodeDungeonUnit*)m_pPassP[i]->getChildByTag(i+999);
            if (data->getIsCanTouch()&&data->getBestScore() <= 0)  {
                pUnit->setNow(true,data->getBestScore());
                if(i<5)
                {
                    m_pScrollView->setContentOffset(ccp(0,-870));
                }
                else if (i==5||i==6) {
                    float tempFloat = -m_pPassP[i]->getPositionY()/2+50;
                    m_pScrollView->setContentOffset(ccp(0,tempFloat));
                }
                else
                {
                    m_pScrollView->setContentOffset(ccp(0,0));
                }
            }else
            {
                pUnit->setNow(false,data->getBestScore());
            }
        }
    }else
    {
        isToXuanGuan = true;
    }
    
    

}
bool MB_LayerChapterWnd::onAssignCCBMemberVariable(CCObject* pTarget, const char*
                                                   pMemberVariableName, CCNode* pNode)
{
    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))return true;
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_chaptername2", CCLabelTTF*, m_pChapterName2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_container", CCNode*, m_pNodeContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pXuanGuan", CCNode*, m_pXuanGuan);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pReady", CCNode*, m_pReady);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroller", CCNode*, m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star1", CCNode*, m_pStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star2", CCNode*, m_pStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "star3", CCNode*, m_pStar[2]);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBg", CCNode*, m_pBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pWuXianLabel", CCNode*, m_pWuXianLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMoney", CCLabelBMFont*, m_pMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pExp", CCLabelBMFont*, m_pExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLefttimes", CCLabelBMFont*, m_pLefttimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnSweep", CCControlButton*, m_pBtnSweep);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItem0", CCNode*, m_pItem0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItem1", CCNode*, m_pItem1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemMoveNode", CCNode*, m_pItemMoveNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRootLine", CCNode*, m_pRootLine);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTitle", CCSprite*, m_pTitle);
    
    for (int i=0 ; i<10; i++) {
        char starstr[]="m_pPassP0";
        starstr[8] = i+'0';
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, starstr, CCNode *, m_pPassP[i]);
    }
    return false;
}

SEL_MenuHandler MB_LayerChapterWnd::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerChapterWnd::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPerfectBoxClicked", MB_LayerChapterWnd::onPerfectBoxClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerChapterWnd::onCloseClick);
    
    return NULL;
}

SEL_CCControlHandler MB_LayerChapterWnd::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSweepClicked",MB_LayerChapterWnd::onSweepClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBattleClicked",MB_LayerChapterWnd::onBattleClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickTZDW",MB_LayerChapterWnd::onClickTZDW);
    return NULL;
}


void MB_LayerChapterWnd::swithXuanGuanOrReady(bool isXuanGuan,int index,const char * levelName)
{
    pRootNode2->setVisible(isXuanGuan);
    m_pXuanGuan->setVisible(isXuanGuan);
    m_pReady->setVisible(!isXuanGuan);
    
    if (!isXuanGuan) {
        selectIndex = index;
        setReadyUI();
        m_pChapterName2->setString(levelName);
        if (!m_pReady->getChildByTag(123)) {
            m_pReady->addChild(MB_ScrollBg::create(left_top,0.5f,1),-1,123);
        }
    }
}
void MB_LayerChapterWnd::onCloseClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    if (m_pReady->isVisible()) {
        swithXuanGuanOrReady(true);
    }else
    {
        NSGameFunction::CCFunctionInterface* pInterface = NULL;
        MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
        if (pInterface)
        {
            MB_ChapterInterface* pInstance = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
            pInterface->onEntryClicked(pInstance);
            MB_LayerAbsolvedPage* pPage = dynamic_cast<MB_LayerAbsolvedPage*>(pInterface->getCurrentFunctionWnd());
            if (pPage)
            {
                pPage->setData(pInstance->getType(), pInstance->getPageId());
            }
        }
    }
}

void MB_LayerChapterWnd::onPerfectBoxClicked(CCObject* pSender)
{
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    //    CCArray* rewardArray = pInterface->getChapterData()->getRewardArray();
    
    
    CCArray* rewardArray = CCArray::create();
    MB_RewardData* pTemp;
    CCARRAY_FOREACH_4TYPE(pInterface->getChapterData()->getRewardArray(),MB_RewardData*,pTemp)
    {
        RewardTempleteValue* data = new RewardTempleteValue;
        data->setValueID(pTemp->getTypeId());
        data->setType(kRewardValueTypeItem);//(pTemp->getType());
        data->setNumber(pTemp->getValue());
        
        rewardArray->addObject(data);
        CC_SAFE_RELEASE_NULL(data);
    }
    
    int state;
    if (pInterface->getBattleInfo()->getBattleStar() == 3)
    {
        if (!pInterface->getBattleInfo()->getPerfect())
        {
            state =  kNoReceive;             //没领取
        }
        else
        {
            state =  kHasReceive;             //已领取
        }
    }
    else
    {
        state = kCanNotReceive;
    }
    MB_NodePerfectReward* layer = MB_NodePerfectReward::create(rewardArray,state);
    layer->setDataRouse(this);
    MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWnd(layer);
    goMessageShow();
    //    pushWindow(MB_NodePerfectReward::create(rewardArray,state));
}


bool MB_LayerChapterWnd::initConfigure()
{
    MB_ChapterInterface* pInstance = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInstance)
    {
        MB_ChapterPage* pPage = NULL;
        MB_AbsolvedConfigure::getInstance()->queryChapterPage(pInstance->getType(), pInstance->getPageId(), &pPage);
        if (pPage)
        {
            m_szBackground = pPage->getBackground();
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ChapterFileChar);
            if (frame)
            {
                m_pTitle->setDisplayFrame(frame);
            }
        }
        
        char buff[128] = {};
        sprintf(buff, "config/chapter/chapter_%d.xml",pInstance->getChapterId());
        MB_XmlFile* pFile = MB_XmlFile::create(buff);
        if (pFile)
        {
            CCArray* pArray = CCArray::create();
            MB_XmlNode* pNode = NULL;
            MB_DungeonData* pDungeoData = NULL;
            if(pFile->queryNodesByName("Dungeons|Dungeon", pArray))
            {
                m_pDungeonList->removeAllObjects();
                CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pNode)
                {
                    pDungeoData = new MB_DungeonData;
                    if (initDungeonData(pDungeoData, pNode))
                    {
                        m_pDungeonList->addObject(pDungeoData);
                    }
                    CC_SAFE_RELEASE_NULL(pDungeoData);
                }
            }
        }
    }
    return true;
}

/*
 <Dungeon
 ID = "9"
 Number = "0"
 Name = "大道"
 activeneedpass = "0"
 costenergy = "0"
 maxtimes = "0"
 coin = "0"
 exprole = "0"
 expgeneral = "0"
 dropitem1 = "14001"
 dropitem2 = "0"
 boss_postion = "010000"
 addMorale = "10"
 dungeon_icon = "12403"
 dungeon_level = "0"
 />
 */
bool MB_LayerChapterWnd::initDungeonData(MB_DungeonData* pDungeoData,MB_XmlNode* pNode)
{
    if (pNode==NULL)
    {
        return false;
    }
    
    pDungeoData->setID(pNode->queryAttributeByName("ID")->intValue());
    pDungeoData->setNumber(pNode->queryAttributeByName("Number")->intValue());
    pDungeoData->setActiveNeedPass(pNode->queryAttributeByName("activeneedpass")->intValue());
    pDungeoData->setName(pNode->queryAttributeByName("Name")->getCString());
    pDungeoData->setCostEnergy(pNode->queryAttributeByName("costenergy")->intValue());
    pDungeoData->setMaxTimes(pNode->queryAttributeByName("maxtimes")->intValue());
    pDungeoData->setCoin(pNode->queryAttributeByName("coin")->intValue());
    pDungeoData->setExpRole(pNode->queryAttributeByName("exprole")->intValue());
    pDungeoData->setExpGeneral(pNode->queryAttributeByName("expgeneral")->intValue());
    pDungeoData->setDropItem1(pNode->queryAttributeByName("dropitem1")->intValue());
    pDungeoData->setDropItem2(pNode->queryAttributeByName("dropitem2")->intValue());
    pDungeoData->setBossList(pNode->queryAttributeByName("boss_postion")->getCString());
    pDungeoData->setAddMorale(pNode->queryAttributeByName("addMorale")->intValue());
    pDungeoData->setDungeon_icon(pNode->queryAttributeByName("dungeon_icon")->intValue());
    pDungeoData->setDungeonLevel(pNode->queryAttributeByName("dungeon_level")->intValue());
    
    
    updateDungeonData(pDungeoData);
    return true;
}

MB_DungeonInfo* MB_LayerChapterWnd::getDungeonInfoById(uint16_t nDungeonId)
{
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInterface)
    {
        MB_BattleInfo* pBattle = pInterface->getBattleInfo();
        if (pBattle)
        {
            return pBattle->queryDungeonInfoByDungeonId(nDungeonId);
        }
    }
    return NULL;
}

void MB_LayerChapterWnd::updateDungeonData(MB_DungeonData* pDungeoData)
{
    MB_DungeonInfo* info = getDungeonInfoById(pDungeoData->getID());
    if (info)
    {
        pDungeoData->setBestScore(info->getBestScore());
        pDungeoData->setLeftTime(info->getRestTimes());
    }
    else
    {
        pDungeoData->setBestScore(0);
        pDungeoData->setLeftTime(pDungeoData->getMaxTimes());
        
    }
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInterface)
    {
        MB_ChapterProgress* pProgress = pInterface->getChapterProgress();
        if(pProgress->getDungeonId()<pDungeoData->getID())
        {
            pDungeoData->setIsCanTouch(false);
        }
        else
        {
            pDungeoData->setIsCanTouch(true);
        }
    }
    
}
void MB_LayerChapterWnd::sendbattle_perfect_reward()
{
    MB_ChapterInterface* pInstance = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInstance)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        //        SOCKET_MSG_REGIST(SC_BATTLE_PERFECT_REWARD, MB_LayerChapterWnd);
        SOCKET_REQUEST_START(CS_BATTLE_PERFECT_REWARD);
        packet->writeU16(pInstance->getChapterId());
        SOCKET_REQUEST_END(SC_BATTLE_PERFECT_REWARD, MB_LayerChapterWnd::onMsgRecv);
    }
    
}

/*
 message recvbattle_perfect_reward[id=10209]{
 required	int8		result			=1;//领取结果
 // 1=> 成功
 // 2=> 失败，不能再次领取
 // 3=> 失败，未完美通关
 }
 */
void MB_LayerChapterWnd::recvbattlt_perfect_reward(MB_MsgBuffer* pRecv)
{
    //    SOCKET_MSG_UNREGIST(SC_BATTLE_PERFECT_REWARD);
    uint8_t ret = 0;
    pRecv->readU8(&ret);
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (ret == 1)
    {
        showReward();
        MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
        if (pInterface)
        {
            MB_BattleInfo* pBattle = pInterface->getBattleInfo();
            pBattle->setPerfect(1);
            m_bPerfect = true;
        }
    }
    else if(ret == 2)
    {
        MB_Message::sharedMB_Message()->showMessage("不能再次领取");
    }
    else if(ret == 3)
    {
        MB_Message::sharedMB_Message()->showMessage("未完美通关");
    }
    
    goMessageShow();
}

void MB_LayerChapterWnd::showReward()
{
    MB_ChapterInterface* pInstance = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInstance)
    {
        CCArray* pReward = pInstance->getChapterData()->getRewardArray();
        if (pReward)
        {
            MB_RewardData* pData = NULL;
            RewardTempleteValue* pValue = NULL;
            int type = 0;
            CCArray* pResult = CCArray::create();
            CCARRAY_FOREACH_4TYPE(pReward, MB_RewardData*, pData)
            {
                type = pData->getType() == 1 ? 2 : 1;
                pValue = new RewardTempleteValue;
                pValue->setType(type);
                pValue->setValueID(pData->getTypeId());
                pValue->setNumber(pData->getValue());
                pResult->addObject(pValue);
                CC_SAFE_RELEASE_NULL(pValue);
            }
            
            MB_LayerRewardMore* pWnd = MB_LayerRewardMore::create(pResult);
            if (pWnd)
            {
                pWnd->setCallBack(this, menu_selector(MB_LayerChapterWnd::goMessageShow));
                MB_ResWindow* pLayerMain = dynamic_cast<MB_ResWindow*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN));
                if(pLayerMain)pLayerMain->setShowRoleInfoPanel(true);
                MB_GlobelModalDlgMsgQueue::getInstance()->insertAtIndex(pWnd, 0);
            }
        }
        
    }
}
void MB_LayerChapterWnd::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg)
    {
        case SC_BATTLE_PERFECT_REWARD:
            recvbattlt_perfect_reward(recvPacket);
            break;
        case SC_BATTLE_CHALLENGE:
            recvbattle_challenge(recvPacket);
            break;
        case SC_BATTLE_DUNGEON_RAIDS:
            recvbattle_dungeon_raids(recvPacket);
            break;
        default:
            break;
    }
    
}

void MB_LayerChapterWnd::onNextClick(CCObject*)
{
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    if (pInterface)
    {
        bool ret = MB_AbsolvedConfigure::getInstance()->goChapter(pInterface->getType(), pInterface->getPageId(), pInterface->getChapterId()+1);
        if (!ret)
        {
            MB_Message::sharedMB_Message()->showMessage("当前模式已完全通关，更多关卡将在后续陆续更新");
        }
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("错误的章节数据");
    }
    
}
MB_DungeonData* MB_LayerChapterWnd::queryDungeonDataById(uint16_t id)
{
    MB_DungeonData* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pDungeonList, MB_DungeonData*, pTemp)
    {
        if (pTemp->getID() == id)
        {
            return pTemp;
        }
    }
    return NULL;
}

void MB_LayerChapterWnd::checkLevelUp()
{
    int level = MB_RoleData::getInstance()->getLevel();
    if (m_nLevel != level)
    {
        m_nLevel = level;
        CCArray* pArray = MB_FunctionMgr::getInstance()->getFunctionLevelUpTips(m_nLevel);
        if (pArray->count()!=0)
        {
            MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWndQueue(pArray);
        }
    }
}
void MB_LayerChapterWnd::goMessageShow()
{
    if (MB_GlobelModalDlgMsgQueue::getInstance()->msgCount()==0)
    {
        MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd",false);
        if (m_bIsToHome) {
            m_bIsToHome = false;
            MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
        }
    }
    else
    {
        MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd",true);
        
        MB_GlobelModalDlgMsgQueue::getInstance()->popFront();
    }
}
void MB_LayerChapterWnd::recvbattle_challenge(MB_MsgBuffer* pRecv)
{
    MB_TutorialMgr::getInstance()->SetModelDilogState("battle_challenge", false);
    MB_Message::sharedMB_Message()->removeALLMessage();
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    MB_NetStructFight fight(m_nLevel,m_nPreExp,(char *)m_pNowdata->getBossList(),m_nPreEnery,m_nPreDicovery,m_nPreStar,m_pNowdata->getDungeonLevel());
    MB_ChapterPage* pPage = pInterface->getChapterPage();
    std::string file;
    if (pPage)
    {
        file = CCString::createWithFormat("pic_map/map_bat_%d.jpg",pInterface->getChapterId()%1000)->getCString();
        pPage->loadResource2SpriteCache();
    }
    m_SceneGameIsSetLevelUI = true;
    MB_DungeonData* pData = (MB_DungeonData*)queryDungeonDataById(m_nDungeonId);
    int tempInt = pData->getID()%10000;tempInt = (tempInt-1)/10+1;
    m_SceneGameBigLevel = tempInt;
    m_SceneGameLittleLevel = m_pNowdata->getNumber();
    m_SceneGameLevelName = m_pNowdata->getName();
    
    uint8_t bSucess = 0;
    p_reward  *pReward = fight.recvbattle_challenge(pRecv,file.empty()?NULL:file.c_str(),&bSucess);
    
    if (pReward != NULL)
    {
        if(pReward->score !=0)
        {
            int lefttime = m_pNowdata->getLeftTime();
            lefttime = m_pNowdata->getLeftTime()-1;
            lefttime = lefttime < 0 ? 0 : lefttime;
            m_pNowdata->setLeftTime(lefttime);
        }
        else
        {
            return ;
        }
        MB_DungeonInfo* pInfo = getDungeonInfoById(m_nDungeonId); // 这是进度
        if (pInfo == NULL)
        {
            pInfo = new MB_DungeonInfo;
            if (pData)
            {
                pInfo->setRestTimes(pData->getMaxTimes()-1);
            }
            else
            {
                pInfo->setRestTimes(0);
            }
            pInfo->setDungeonID(m_nDungeonId);
            pInterface->getBattleInfo()->addDungeonInfo(pInfo);
            pInfo->release();
            
            if(pReward->score!=0)
            {
                MB_GlobelModalDlgMsgQueue::getInstance()->clearMsg();
                MB_LayerStoryPlayer* pWnd = tryCreateStoryPlayer(m_nDungeonId,2);
                if (pWnd)
                {
                    pWnd->setTarget(this,menu_selector(MB_LayerChapterWnd::goMessageShow));
                    MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWnd(pWnd);
                }
            }
            
        }
        else
        {
            if(pInfo->getRestTimes()!=0)
            {
                pInfo->setRestTimes(pInfo->getRestTimes()-1);
            }
        }
        if (pInfo->getBestScore() < pReward->score)
        {
            pInfo->setBestScore(pReward->score);
        }
        
        if (m_pNowdata->getBestScore() < pReward->score)
        {
            m_pNowdata->setBestScore( pReward->score );
        }
        if (pReward->preLevel >= 0 && pInterface->getChapterProgress()->getDungeonId() <= m_nDungeonId)
        {
            pInterface->getChapterProgress()->setDungeonId(m_nDungeonId+1);
        }
        MB_DungeonData* p = queryDungeonDataById(m_nDungeonId+1);
        if (p)
        {
            updateDungeonData(p);
        }
        MB_DungeonData *pLastObj = (MB_DungeonData *)m_pDungeonList->lastObject();
        if (pReward->preLevel >= 0 && pLastObj->getID()<pInterface->getChapterProgress()->getDungeonId())
        {
            
            if (pInterface->getChapterStar() == 3)
            {
                
                NSGameFunction::CCFunctionInterface* pRoot = NULL;
                MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pRoot);
                MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(pRoot);
                if (pAbsolved)
                {
                    pAbsolved->addPerfectDungeonID(pInterface->getChapterId());
                }
                if (!m_bPerfect)
                {
                    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
                    
                    
                    CCArray* rewardArray = CCArray::create();
                    MB_RewardData* pTemp;
                    CCARRAY_FOREACH_4TYPE(pInterface->getChapterData()->getRewardArray(),MB_RewardData*,pTemp)
                    {
                        RewardTempleteValue* data = new RewardTempleteValue;
                        data->setValueID(pTemp->getTypeId());
                        data->setType(kRewardValueTypeItem);//(pTemp->getType());
                        data->setNumber(pTemp->getValue());
                        
                        rewardArray->addObject(data);
                        CC_SAFE_RELEASE_NULL(data);
                    }
                    
                    int state;
                    if (pInterface->getBattleInfo()->getBattleStar() == 3)
                    {
                        if (!pInterface->getBattleInfo()->getPerfect())
                        {
                            state =  kNoReceive;             //没领取
                        }
                        else
                        {
                            state =  kHasReceive;             //已领取
                        }
                    }
                    else
                    {
                        state = kCanNotReceive;
                    }
                    MB_NodePerfectReward* layer = MB_NodePerfectReward::create(rewardArray,state);
                    layer->setDataRouse(this);
                    MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWnd(layer);
                }
            }
            
            if (!m_bComplate)
            {
                m_bComplate = true;
                
                int nextchapter = pInterface->getChapterProgress()->getChapterId()+1;
                if (MB_AbsolvedConfigure::getInstance()->chapterExist(pInterface->getType(), nextchapter))
                {
                    pInterface->getChapterProgress()->setChapterId(nextchapter);
                    if (MB_TutorialMgr::getInstance()->getSkipTutorial())
                    {
                        char databuf[200];
                        sprintf(databuf, "您已经成功通关了\"%s\".\n可以开始下一章节", pInterface->getChapterData()->getName().c_str());
                        
                        MB_ResWindow* pWnd = MB_Message::createMessageBox2("战报",databuf,"下一章节","继续本章",this,menu_selector(MB_LayerChapterWnd::onNextClick),menu_selector(MB_LayerChapterWnd::goMessageShow));
                        
                        pWnd->setShowRoleInfoPanel(true);
                        MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWnd(pWnd);
                    }
                }
                else
                {
                    MB_ResWindow* pWnd = MB_Message::createMessageBox1("战报","已通关当前模式的所有章节","确定",NULL,NULL);
                    MB_GlobelModalDlgMsgQueue::getInstance()->addMsgWnd(pWnd);
                }
                
            }
        }
        
        checkLevelUp();
        runAction(CCCallFunc::create(this, callfunc_selector(MB_LayerChapterWnd::goMessageShow)));
    }
    
}
void MB_LayerChapterWnd::onGetRewardClicked(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    sendbattle_perfect_reward();
}
void MB_LayerChapterWnd::sendbattle_challenge(uint8_t type,uint16_t id)
{
    MB_AbsolvedInterface::sendbattle_challenge(type, id);
    m_nDungeonId = id;
    
}
void MB_LayerChapterWnd::requestBattle(CCObject* pSender)
{
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd", false);
    MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
    MB_Message::sharedMB_Message()->showMessage("", 20);
    this->sendbattle_challenge(pInterface->getType(),m_pNowdata->getID());
}
void MB_LayerChapterWnd::onBattleClicked(CCObject* pSender)
{
    MB_DungeonData* data = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(selectIndex));
    if (data == NULL)
    {
        return;
    }
    TutorialForcedTrigpetComplete
    m_nLevel = MB_RoleData::getInstance()->getLevel();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("PreLevel", m_nLevel);
    m_nPreExp = MB_RoleData::getInstance()->getEXP();
    m_nPreDicovery = MB_RoleData::getInstance()->getDiscoveryTimes();
    m_nPreEnery = MB_RoleData::getInstance()->getEnergy();
    m_pNowdata = data;
    m_nPreStar = m_pNowdata->getBestScore();
    
    if (m_nPreStar==0)
    {
        if (MB_RoleData::getInstance()->getEnergy()!=0)
        {
            if(!playPlot(data->getID(),1))
            {
                requestBattle(this);
            }
        }
        else
        {
            requestBattle(this);
        }
    }
    else
    {
        requestBattle(this);
    }
}
MB_LayerStoryPlayer* MB_LayerChapterWnd::tryCreateStoryPlayer(int dungeonId,int condition)
{
    CCArray* pArray = CCArray::create();
    bool ret = MB_SynopsisConfig::getInstance()->querySynopsisItem(dungeonId, condition, &pArray);
    if (ret)
    {
        return MB_LayerStoryPlayer::create(pArray);
    }
    return NULL;
}
bool MB_LayerChapterWnd::playPlot(int dungeonId,int condition)
{
    MB_LayerStoryPlayer* pWnd = tryCreateStoryPlayer(dungeonId,condition);
    if (pWnd)
    {
        pWnd->setTarget(this,menu_selector(MB_LayerChapterWnd::requestBattle));
        CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_MESSAGE);
        MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd", true);
        return true;
    }
    
    return false;
}


void MB_LayerChapterWnd::onSweepClicked(CCObject* pSender)
{
    MB_DungeonData* pData = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(selectIndex));
    if (pData == NULL)
    {
        CCLOG("无法进行扫荡，数据有误");
        return;
    }
    m_pNowdata = pData;
    m_nLevel = MB_RoleData::getInstance()->getLevel();
    m_nPreExp = MB_RoleData::getInstance()->getEXP();
    m_nPreDicovery = MB_RoleData::getInstance()->getDiscoveryTimes();
    m_nPreEnery = MB_RoleData::getInstance()->getEnergy();
    MB_Message::sharedMB_Message()->showMessage("",15);
    
    
    m_nPreValue[0] = MB_RoleData::getInstance()->getLevel();
    m_nPreValue[1] = MB_RoleData::getInstance()->getDiscoveryTimes();
    m_nPreValue[2] = MB_RoleData::getInstance()->getEnergy();
    
    
    SOCKET_MSG_REGIST(SC_BATTLE_DUNGEON_RAIDS, MB_LayerChapterWnd);
    SOCKET_REQUEST_START(CS_BATTLE_DUNGEON_RAIDS);
    packet->writeU16(m_pNowdata->getID());
    SOCKET_REQUEST_END(SC_BATTLE_DUNGEON_RAIDS, NULL);
}

void MB_LayerChapterWnd::recvbattle_dungeon_raids(MB_MsgBuffer* pRecv)
{
    SOCKET_MSG_UNREGIST(SC_BATTLE_DUNGEON_RAIDS);
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t result;
    pRecv->readU8(&result);
    if(result == 1){
        
        uint8_t radisTimes;
        pRecv->readU8(&radisTimes);
        uint16_t datatime;
        pRecv->readU16(&datatime);
        p_reward *read = new p_reward[datatime];
        for(int i = 0 ; i < datatime ; i++){
            
            onSetReward(&(read[i]), pRecv);
        }
        m_pNowdata->setLeftTime(m_pNowdata->getLeftTime() - radisTimes);
        MB_DungeonInfo* pInfo = getDungeonInfoById(m_pNowdata->getID());
        if(pInfo)
        {
            pInfo->setRestTimes(pInfo->getRestTimes()-radisTimes);
        }
        MB_LayerSweep *layer= MB_LayerSweep::create(read,datatime);
        layer->layerChapterWnd = this;
        layer->setBeforeSweepRoleInfo(m_nPreValue[0], m_nPreValue[1],m_nPreValue[2]);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_SWEEP);
        return ;
        
    }else if( result == 2){
        
        MB_Message::sharedMB_Message()->showMessage("体力不足");
        
    }else if( result == 3){
        
        MB_Message::sharedMB_Message()->showMessage("远征次数不足");
        
    }else if( result == 4){
        
        MB_Message::sharedMB_Message()->showMessage("该关卡没完成3星通过");
        
    }else if( result == 5){
        
        MB_Message::sharedMB_Message()->showMessage("该关卡未解锁");
        
    }else if( result == 6){
        
        MB_Message::sharedMB_Message()->showMessage("等级不足，需要角色到达15级");
        
    }else if( result == 7){
        
        MB_Message::sharedMB_Message()->showMessage("vip等级不足，需要vip等级3级");
    }
    return ;
}

void MB_LayerChapterWnd::onSetReward(p_reward *reward,MB_MsgBuffer* recvPacket){
    
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



void MB_LayerChapterWnd::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}
void MB_LayerChapterWnd::updateToRetry(float dt)
{
    if (m_IsCanRetryGame) {
        global_isRePlay = false;
        onBattleClicked(NULL);
        unschedule(schedule_selector(MB_LayerChapterWnd::updateToRetry));
    }
}
void MB_LayerChapterWnd::resetSweep()
{
    char databuf[40];
    MB_DungeonData* m_data = (MB_DungeonData*)(m_pDungeonList->objectAtIndex(selectIndex));
    sprintf(databuf, "%d / %d",m_data->getLeftTime(),m_data->getMaxTimes());
    m_pLefttimes->setString(databuf);
}
