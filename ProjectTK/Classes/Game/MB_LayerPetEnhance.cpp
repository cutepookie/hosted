

#include "MB_LayerPetEnhance.h"
#include "MB_LayerPetEnhanceSpecial.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_RoleSoundSystem.h"
#include "MB_LayerPetRestore.h"
#include "MB_LayerPetEquipment.h"
#include "MB_LayerCommand.h"
#include "MB_NodePetDuiWu.h"
#include "MB_ScrollBg.h"
#define LAYER_TAG 50
#define NODE_GER_TAG 50
#define MAX_SHOW_CMD 6
#define AIDLAYER 300
#define TARGETX 200
#define TARGETX_2 375
#define SCALESPAN 80
#define SCALEX (0.97f)
#define SCALEY (0.9f)
#define SUOXIAOX 150
#define M_KaiPaiYiDongHuiFuSpeed (150.0f)
#define XIAZHENY -200
#define NPOSX 80
USING_NS_CC;
USING_NS_CC_EXT;

bool compare2(CCObject *_petData1,CCObject *_petData2)
{
    MB_PetData* petData1 = (MB_PetData*)_petData1;
    MB_PetData* petData2 = (MB_PetData*)_petData2;
    if (petData1->getTemplateStar() > petData2->getTemplateStar())return true;
    else if (petData1->getTemplateStar() < petData2->getTemplateStar())return false;
    if (petData1->getPetLevel() > petData2->getPetLevel())return true;
    else if (petData1->getPetLevel() < petData2->getPetLevel())return false;
    if (petData1->getPetQuallity() > petData2->getPetQuallity())return true;
    else if (petData1->getPetQuallity() < petData2->getPetQuallity())return false;
    if (petData1->getPetTypeID() > petData2->getPetTypeID())return true;
    else if (petData1->getPetTypeID() < petData2->getPetTypeID())return false;
    return false;
}
MB_LayerPetEnhance::MB_LayerPetEnhance()
{
    m_CostPetIcon = NULL;
    isFirstTouch = false;
    m_nType = kPetEnhanceEntrMain;
    isUpdateUI = false;
    m_uPetID = 0;
    m_uPetIDCost = 0;
    m_nListSize = 0;
    m_pPetName1 = NULL;
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    selectNpdw = NULL;
    m_pNodeNaveigation = NULL;
    m_pCard = NULL;
    m_pTextLevel1 = NULL;
    m_pTextAttack1 = NULL;
    m_pTextLife1 = NULL;
    m_pTextLevel2 = NULL;
    m_pTextAttack2 = NULL;
    m_pTextLife2 = NULL;
    m_pCostIcon = NULL;
    m_pTextCostName = NULL;
    m_pTextCostCoin = NULL;
    m_pButtonCommit = NULL;
    m_pNodeRankMaxTip = NULL;
    m_pNodeGod = NULL;
    m_pNodeSaint = NULL;
    m_pNodePetCost = NULL;
    m_pNodeCoinCost = NULL;
    m_pAllRoleArray = NULL;
    m_pCCBAnimationMgr = NULL;
    m_bShowRoleInfoPanel = true;
    m_pLayerType = kPetTeamTypeEnhanceCost;
    SOCKET_MSG_REGIST(SC_GER_UP_RANK, MB_LayerPetEnhance);
    
    isHomeButtonShow =  ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->isVisible();
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(false);
}

MB_LayerPetEnhance::~MB_LayerPetEnhance()
{
    SOCKET_MSG_UNREGIST(SC_GER_UP_RANK);
    
    CC_SAFE_RELEASE_NULL(m_pCard);
    CC_SAFE_RELEASE_NULL(m_pPetName1);
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    
    CC_SAFE_RELEASE_NULL(m_pNodeNaveigation);
    CC_SAFE_RELEASE_NULL(m_pTextLevel1);
    CC_SAFE_RELEASE_NULL(m_pTextAttack1);
    CC_SAFE_RELEASE_NULL(m_pTextLife1);
    CC_SAFE_RELEASE_NULL(m_pTextLevel2);
    CC_SAFE_RELEASE_NULL(m_pTextAttack2);
    CC_SAFE_RELEASE_NULL(m_pTextLife2);
    CC_SAFE_RELEASE_NULL(m_pCostIcon);
    CC_SAFE_RELEASE_NULL(m_pTextCostName);
    CC_SAFE_RELEASE_NULL(m_pTextCostCoin);
    CC_SAFE_RELEASE_NULL(m_pButtonCommit);
    CC_SAFE_RELEASE_NULL(m_pNodeSaint);
    CC_SAFE_RELEASE_NULL(m_pNodeGod);
    CC_SAFE_RELEASE_NULL(m_pNodeRankMaxTip);
    CC_SAFE_RELEASE_NULL(m_pNodePetCost);
    CC_SAFE_RELEASE_NULL(m_pNodeCoinCost);
    CC_SAFE_RELEASE(m_pCCBAnimationMgr);
    
    
}
MB_LayerPetEnhance* MB_LayerPetEnhance::create(PetEnhanceEntr kPetEnhanceEntrMain, uint64_t petID)
{
    MB_LayerPetEnhance* layer = new MB_LayerPetEnhance();
    if (layer && layer->init(kPetEnhanceEntrMain, petID)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

CCPoint starPt[MAX_GER_STAR];
bool MB_LayerPetEnhance::init(PetEnhanceEntr type, uint64_t petID)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    m_nType = type;
    m_uPetID = petID;

    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/card_layer_rank.ccbi", this);
    this->addChild(NSGameHelper::createDisableTouchLayer1());
    this->addChild(pScene);
    m_pCCBAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pCCBAnimationMgr);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    for (int i=0; i<MAX_GER_STAR; ++i)
    {
        starPt[i] = m_pStar[i]->getPosition();
    }
    
    
    reloadArray();
    initFunctions();
    scheduleUpdate();
    onResetWnd();
    
    addChild(MB_ScrollBg::create(right_bottom,.5f,3),-1);
	return true;
}

void MB_LayerPetEnhance::onEnter()
{
    MB_ResWindow::onEnter();
    PlayRoleSound(kSoundEnterRankUp);
}

void MB_LayerPetEnhance::resetPetID(uint64_t petID)
{
    if (m_uPetID == petID) {
        return;
    }
    
    m_uPetID = petID;
    m_uPetIDCost = 0;
    dirty();
}

void MB_LayerPetEnhance::resetCostPetID(uint64_t petID)
{
    if (m_uPetID == petID) {
        return;
    }
    
    m_uPetIDCost = petID;
    dirty();
}

void MB_LayerPetEnhance::onResetWnd()
{
    if (m_uPetID == 0)
    {
        m_pPetName1->setString("");
        m_pPetName1->setVisible(false);
        for (int i = 0; i < MAX_GER_STAR; i++) {
            m_pStar[i]->setVisible(false);
        }
        m_pTextLevel1->setString("");
        m_pTextAttack1->setString("");
        m_pTextLife1->setString("");
        m_pTextLevel2->setString("");
        m_pTextAttack2->setString("");
        m_pTextLife2->setString("");
        m_pCostIcon->setVisible(false);
        m_pCostIcon->removeAllChildren();
        m_pTextCostName->setString("");
        m_pTextCostCoin->setString("");
        m_pButtonCommit->setEnabled(false);
        m_pNodeRankMaxTip->setVisible(false);
        m_pNodePetCost->setVisible(true);
        m_pNodeCoinCost->setVisible(true);
        m_pNodeGod->setVisible(false);
        m_pNodeSaint->setVisible(false);
    }
    else
    {
        MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetID);
        if (petData == NULL) {
            MB_LOG("petUID:%llu not exist.", m_uPetID);
            //不存在的时候就当没有设置重新刷一遍
            m_uPetID = 0;
            dirty();
            return;
        }

        MB_PetTemplate* petTemplete = petData->getTemplete();
        
        for (int i=0; i<MAX_GER_STAR; ++i)
        {
            m_pStar[i]->setPosition(starPt[i]);
        }
        NSGameHelper::centerStars(m_pStar, MAX_GER_STAR, petTemplete->getPetStar());
        
        if (petData->getPetQuallity() == 9) {
            m_pNodeGod->setVisible(true);
            m_pNodeSaint->setVisible(false);
            m_pNodeRankMaxTip->setVisible(false);
            m_pNodePetCost->setVisible(false);
            m_pNodeCoinCost->setVisible(false);
            m_pButtonCommit->setVisible(false);
        }
        else if (petData->getPetQuallity() == 19)
        {
            m_pNodeSaint->setVisible(true);
            m_pNodeRankMaxTip->setVisible(false);
            m_pNodePetCost->setVisible(false);
            m_pNodeCoinCost->setVisible(false);
            m_pNodeGod->setVisible(false);
            m_pButtonCommit->setVisible(false);
        }
        else if (petData->getPetQuallity() == 20)
        {
            m_pNodeRankMaxTip->setVisible(true);
            m_pNodePetCost->setVisible(false);
            m_pNodeCoinCost->setVisible(false);
            m_pNodeGod->setVisible(false);
            m_pNodeSaint->setVisible(false);
            m_pButtonCommit->setVisible(false);
        }
        else
        {
            m_pNodeGod->setVisible(false);
            m_pNodeRankMaxTip->setVisible(false);
            m_pNodePetCost->setVisible(true);
            m_pNodeCoinCost->setVisible(true);
            m_pNodeSaint->setVisible(false);
            m_pButtonCommit->setVisible(true);
        }
        
        if (m_pCard->getChildrenCount()==0) {
            m_pCard->removeAllChildren();
            MB_NodePetCard* petCard = MB_NodePetCard::create(petData->getPetID());
            m_pCard->addChild(petCard);
            m_pCard->setVisible(true);
        }
        //品阶
        //计算材料
        MB_PetData* costMB_PetData;
        if(0 == m_uPetIDCost)
        {
            costMB_PetData = getCosePet(petData->getPetID(),petData->getPetTypeID());
        }
        else
        {
            costMB_PetData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetIDCost);
        }
        
        MB_PetTemplate* costMB_PetTemplate = NULL;
        char* strInfo1 = new char[128];
        char* strInfo2 = new char[128];
        if (petData->getPetQuallity() == 9
            || petData->getPetQuallity() == 19
            || petData->getPetQuallity() == 20) {
            costMB_PetData = NULL;
            m_uPetIDCost = 0;
        }
        if (costMB_PetData != NULL)
        {
            int restQuality = petData->getPetQuallity();
            int nextQuality = restQuality + costMB_PetData->getPetQuallity()+1;
            int nShape = NSGameHelper::getShapeTypeByRank(restQuality);
            if (NSGameHelper::getShapeTypeByRank(nextQuality) > nShape)
            {
                nextQuality = (nShape - 1)*10 + 9;
            }
            if (restQuality == 20) {
                nextQuality = 20;
            }
            //获取名字
            const char* str1 = MB_PetMgr::getInstance()->getPetRealName(petData->getPetTypeID(),restQuality);
            m_pPetName1->setString(str1);
            m_pPetName1->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str1);
            
            m_uPetIDCost = costMB_PetData->getPetID();
            costMB_PetTemplate = MB_PetMgr::getInstance()->getPetTemplateByID(costMB_PetData->getPetTypeID());
            
            //材料icon
            if(m_CostPetIcon == NULL)
            {
                m_pCostIcon->removeAllChildren();
                m_CostPetIcon = MB_NodePet::create(costMB_PetData->getPetID());
                m_CostPetIcon->showLevel(false);
                m_pCostIcon->addChild(m_CostPetIcon);
                m_pCostIcon->setVisible(true);
            }else
            {
                m_CostPetIcon->setPetUID(costMB_PetData->getPetID());
            }
            
            //材料名称
            const char* str = MB_PetMgr::getInstance()->getPetRealName(costMB_PetData->getPetTypeID(), costMB_PetData->getPetQuallity());
            m_pTextCostName->setColor(ccWHITE);
            m_pTextCostName->setString(str);
            m_pTextCostName->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str);
            
            uint64_t coin1 = 0,coin2 = 0,coin3 = 0;
            bool ok1 = false, ok2 = false, ok3 = false;
            CCArray* costArray = MB_PetMgr::getInstance()->getPetQualityCostArray();
            
            int64_t exp2 = petData->getPetExp() + costMB_PetData->getPetExp();
            int16_t level2 = MB_PetMgr::getInstance()->calLevelByExp(exp2);
            sprintf(strInfo1, "%d", petData->getPetLevel());
            sprintf(strInfo2, "%d", level2);
            m_pTextLevel1->setString(strInfo1);
            m_pTextLevel2->setString(strInfo2);
            
            //计算裸身的当前和预估
            int attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity());
            int attack2 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), level2, nextQuality);
            sprintf(strInfo1, "%d", attack1);
            sprintf(strInfo2, "%d", attack2);
            m_pTextAttack1->setString(strInfo1);
            m_pTextAttack2->setString(strInfo2);
            
            int hp1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity());
            int hp2 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), level2, nextQuality);
            sprintf(strInfo1, "%d", hp1);
            sprintf(strInfo2, "%d", hp2);
            m_pTextLife1->setString(strInfo1);
            m_pTextLife2->setString(strInfo2);
            //计算金钱
            for (int i = 0; i < costArray->count(); ++i)
            {
                MB_PetQualityCostTemplete* costTemplete = (MB_PetQualityCostTemplete*)costArray->objectAtIndex(i);
                if (!ok1) {
                    if (costTemplete->getQuality() == petData->getPetQuallity() && costTemplete->getStar() == petTemplete->getPetStar()) {
                        ok1 = true;
                        coin1 = costTemplete->getCoin();
                    }
                }
                if (!ok2) {
                    if (costTemplete->getQuality() == costMB_PetData->getPetQuallity() && costTemplete->getStar() == costMB_PetTemplate->getPetStar()) {

                        ok2 = true;
                        coin2 = costTemplete->getCoin();
                        
                        if (coin2 == 0) {
                            
                        }
                    }
                }
                if (!ok3) {
                    if (costTemplete->getQuality() == MIN(nextQuality, MAX_GER_QUALITY - 1) && costTemplete->getStar() == petTemplete->getPetStar()) {
                        ok3 = true;
                        coin3 = costTemplete->getCoin();
                    }
                }
                if (ok1 && ok2 && ok3) {
                    if (coin2 + coin1 > coin3)
                    {
                        coin3 = 0;
                    }
                    else
                    {
                        coin3 = coin3 - coin2 - coin1;
                    }
                    break;
                }
            }
            if (MB_RoleData::getInstance()->getCoin() < coin3)
            {
                m_pTextCostCoin->setColor(ccRED);
            }
            else
            {
                m_pTextCostCoin->setColor(ccWHITE);
            }
            NSGameHelper::LabelFormatNumber(m_pTextCostCoin, coin3,true);

            m_pTextCostCoin->setVisible(true);
        }
        else
        {
            int restQuality = petData->getPetQuallity();
            int nextQuality = restQuality + 1;
            int nShape = NSGameHelper::getShapeTypeByRank(restQuality);
            if (NSGameHelper::getShapeTypeByRank(nextQuality)>nShape)
            {
                nextQuality = (nShape - 1)*10 + 9;
            }
            
            if (restQuality == 20) {
                nextQuality = 20;
            }
            if(restQuality != 9 && restQuality != 19 && restQuality != 20)
            {
                m_pNodePetCost->setVisible(false);
            }
            
            //获取名字
            const char* str1 = MB_PetMgr::getInstance()->getPetRealName(petData->getPetTypeID(),restQuality);
            m_pPetName1->setString(str1);
            m_pPetName1->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str1);
            
            
            
            costMB_PetTemplate = petData->getTemplete();
            m_uPetIDCost = petData->getPetTypeID();
            //材料icon
            m_pCostIcon->removeAllChildren();
            MB_NodePet* petIcon = MB_NodePet::create(costMB_PetTemplate->getPetTypeID());
            petIcon->showLevel(false);
            m_pCostIcon->addChild(petIcon);
            m_pCostIcon->setVisible(true);
            //材料名称
            const char* str = MB_PetMgr::getInstance()->getPetRealName(costMB_PetTemplate->getPetTypeID(), 0);
            m_pTextCostName->setColor(ccRED);
            m_pTextCostName->setString(str);
            m_pTextCostName->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str);
            
            uint64_t coin1 = 0, coin3 = 0;
            bool ok1 = false, ok3 = false;
            CCArray* costArray = MB_PetMgr::getInstance()->getPetQualityCostArray();
            
            sprintf(strInfo1, "%d", petData->getPetLevel());
            sprintf(strInfo2, "%d", petData->getPetLevel());
            m_pTextLevel1->setString(strInfo1);
            m_pTextLevel2->setString(strInfo2);
            
            //计算裸身的当前和预估
            int attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity());
            int attack2 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), nextQuality);
            sprintf(strInfo1, "%d", attack1);
            sprintf(strInfo2, "%d", attack2);
            m_pTextAttack1->setString(strInfo1);
            m_pTextAttack2->setString(strInfo2);

            int hp1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity());
            int hp2 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), nextQuality);
            sprintf(strInfo1, "%d", hp1);
            sprintf(strInfo2, "%d", hp2);
            m_pTextLife1->setString(strInfo1);
            m_pTextLife2->setString(strInfo2);
            
            //计算金钱
            for (int i = 0; i < costArray->count(); ++i)
            {
                MB_PetQualityCostTemplete* costTemplete = (MB_PetQualityCostTemplete*)costArray->objectAtIndex(i);
                if (!ok1) {
                    if (costTemplete->getQuality() == petData->getPetQuallity() && costTemplete->getStar() == petTemplete->getPetStar()) {
                        ok1 = true;
                        coin1 = costTemplete->getCoin();
                    }
                }
                
                if (!ok3) {
                    if (costTemplete->getQuality() == MIN(nextQuality, MAX_GER_QUALITY - 1) && costTemplete->getStar() == petTemplete->getPetStar()) {
                        ok3 = true;
                        coin3 = costTemplete->getCoin();
                    }
                }
                if (ok1 && ok3) {
                    coin3 = coin3 - coin1;
                    break;
                }
            }

            NSGameHelper::LabelFormatNumber(m_pTextCostCoin, coin3,true);
            if (MB_RoleData::getInstance()->getCoin() < coin3)
            {
                m_pTextCostCoin->setColor(ccRED);
            }
            else
            {
                m_pTextCostCoin->setColor(ccWHITE);
            }
            m_pTextCostCoin->setVisible(true);
        }
        CC_SAFE_DELETE_ARRAY(strInfo1);
        CC_SAFE_DELETE_ARRAY(strInfo2);
    }
}

bool MB_LayerPetEnhance::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCard", CCNode*, m_pCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetName1", CCLabelTTF*, m_pPetName1);
    char strStar[] = "m_pStar1";
    for (int i = 0; i < MAX_GER_STAR; i++) {
        strStar[7] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strStar, CCSprite*, m_pStar[i]);
    }
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLevel1", CCLabelBMFont*, m_pTextLevel1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextAttack1", CCLabelBMFont*, m_pTextAttack1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLife1", CCLabelBMFont*, m_pTextLife1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLevel2", CCLabelBMFont*, m_pTextLevel2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextAttack2", CCLabelBMFont*, m_pTextAttack2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextLife2", CCLabelBMFont*, m_pTextLife2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCostIcon", CCNode*, m_pCostIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextCostName", CCLabelTTF*, m_pTextCostName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextCostCoin", CCLabelBMFont*, m_pTextCostCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pButtonCommit", CCControlButton*, m_pButtonCommit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRankMaxTip", CCNode*, m_pNodeRankMaxTip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGod", CCNode*, m_pNodeGod);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSaint", CCNode*, m_pNodeSaint);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_costpet", CCNode*, m_pNodePetCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_coin", CCNode*, m_pNodeCoinCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNaveigation", CCNode*, m_pNodeNaveigation);
    
    return true;
}

SEL_MenuHandler MB_LayerPetEnhance::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPetEnhance::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerPetEnhance::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerPetEnhance::onCommitClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGodClicked", MB_LayerPetEnhance::onGodClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSaintClicked", MB_LayerPetEnhance::onSaintClicked);
    
    return NULL;
}


void MB_LayerPetEnhance::onCloseClicked(cocos2d::CCObject *pSender)
{
    if (isUpdateUI) {
        MB_LayerPetDetail* ptr =  dynamic_cast<MB_LayerPetDetail*>(getLogicParent());
        if (ptr) {
            ptr->resetBaseInfo();
        }
    }
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(isHomeButtonShow);
    popWindow(true);
}
void MB_LayerPetEnhance::onCommitClicked(cocos2d::CCObject *pSender)
{
    m_pScollerView->getContainer()->stopAllActions();
    m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    ScolltoCenter();
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetID);
    //已经是最大品阶
    if (petData->getPetQuallity() >= MAX_GER_QUALITY)
    {
        MB_Message::sharedMB_Message()->showMessage("已经达到最大品阶.");
        return;
    }
    else
    {
        MB_PetData* costMB_PetData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetIDCost);
        if (costMB_PetData == NULL) {
            MB_Message::sharedMB_Message()->showMessage("进化需要吞噬一张相同星级的精灵卡.");
            return;
        }
        else if (m_pTextCostCoin->getColor().r == ccRED.r
                 && m_pTextCostCoin->getColor().g == ccRED.g
                 && m_pTextCostCoin->getColor().b == ccRED.b)
        {
            MB_Message::sharedMB_Message()->showMessage("进化需要消耗的金币不足.");
            return;
        }
        
        if (costMB_PetData->getPetQuallity() > 0)
        {
            MB_Message::sharedMB_Message()->showMessage("消耗提示", "消耗的材料品阶大于0级, 您是否需要继续?", "继续", "取消", this, menu_selector(MB_LayerPetEnhance::onCommit), NULL);
            return;
        }
        
        if (costMB_PetData->getPetLevel() > 1)
        {
            MB_Message::sharedMB_Message()->showMessage("消耗提示", "消耗的材料等级大于1级, 您是否需要继续?", "继续", "取消", this, menu_selector(MB_LayerPetEnhance::onCommit), NULL);
            return;
        }
        
        
    }
    onCommit();
    
}

void MB_LayerPetEnhance::onCommit()
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_PetMgr::getInstance()->sendpet_up_rank(m_uPetID, m_uPetIDCost);
}



void MB_LayerPetEnhance::onGodClicked(cocos2d::CCObject *pSender)
{
    MB_ResWindow* layer = MB_LayerPetEnhanceSpecial::create(m_uPetID);
    this->replaceLayer(layer);
}

void MB_LayerPetEnhance::onSaintClicked(cocos2d::CCObject *pSender)
{
    MB_ResWindow* layer = MB_LayerPetEnhanceSpecial::create(m_uPetID);
    this->replaceLayer(layer);
}

void MB_LayerPetEnhance::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg) {
            
        case SC_GER_UP_RANK:
            recvpet_up_rank(recvPacket);
            break;
            
        default:
            break;
    }

}

bool MB_LayerPetEnhance::recvpet_up_rank(MB_MsgBuffer *recvPacket)
{
    CCLOG("recvpet_up_rank");
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1)
    {
        isUpdateUI = true;
        if (global_layerPetEquipment!=NULL) {
            global_layerPetEquipment->isUpdateUI = true;
        }
        
        m_uPetIDCost = 0;
        dirty();
        m_pCCBAnimationMgr->runAnimationsForSequenceNamed("rankup");
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Card_Rank_Up).c_str());
        
        onCommitEnd();
    }
    return true;
}

//获取默认材料
MB_PetData* MB_LayerPetEnhance::getCosePet(uint64_t PetID,uint16_t PetTypeID)
{
    CCArray* pArray = CCArray::create();
    pArray->removeAllObjects();
    //    CCArray *tempList  =CCArray::create();
    CCObject *petData;
    
    MB_PetTemplate* petTemp = MB_PetMgr::getInstance()->getPetTemplateByID(PetTypeID);
    uint8_t uPetStar = petTemp->getPetStar();
    CCARRAY_FOREACH(MB_PetMgr::getInstance()->getPetDataArray(), petData)
    {
        //查找同星级 不是同张卡牌 没上阵的卡牌 不是经验卡牌 作为材料
        MB_PetTemplate* petCost = ((MB_PetData*)petData)->getTemplete();
        if(!petCost)
        {
            continue;
        }
        uint8_t uPetCostStar = petCost->getPetStar();
        if (uPetStar != uPetCostStar
            || ((MB_PetData*)petData)->getPetID() == PetID
            || MB_TeamData::getInstance()->checkInTeam((MB_PetData *)petData)
            || NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID())
            || NSGameHelper::checkIsGuardPet(((MB_PetData*)petData)->getPetTypeID())) //守护过滤
        {
            continue;
        }
        
        if(NSGameHelper::checkIsGuardPet(((MB_PetData*)petData)->getPetID())) //守护
        {
            continue;
        }
        
        if (((MB_PetData *)petData)->getIsHomelandPet())
        {
            continue;
        }
    
        pArray->addObject(petData);
    }
    
    //排序
    if (pArray->count() > 0) {
        sortArray(pArray,PetTypeID);
        return (MB_PetData*)(pArray->objectAtIndex(0));
    }
    return  NULL;
}

//材料排序，Id相同优先 其次品阶升序  等级升序 ID升序
void MB_LayerPetEnhance::sortArray(CCArray* pArray,uint16_t nPetTypeID)
{
    CCArray* dataArray = pArray;
    int nListSize = dataArray->count();
    MB_PetData *petData1,*petData2;
    int nSameIDCount = 0;
    //优先同ID
    for(int i = 0;i < nListSize;++i)
    {
        for (int j = i+1; j < nListSize; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            
            if (petData1->getPetTypeID() == nPetTypeID)
            {
                nSameIDCount++;
                break;
            }
            
            if (petData2->getPetTypeID() == nPetTypeID)
            {
                nSameIDCount++;
                dataArray->exchangeObjectAtIndex(i,j);
                break;
            }
        }
    }
    petData1 = (MB_PetData*)dataArray->objectAtIndex(nListSize-1);
    if (petData1->getPetTypeID() == nPetTypeID)
    {
        nSameIDCount++;
    }
    //同ID 品阶升序
    for(int i = 0;i < nSameIDCount;++i)
    {
        for (int j = i+1; j < nSameIDCount; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            if (petData1->getPetQuallity() > petData2->getPetQuallity())
            {
                dataArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //同ID品阶  等级升序
    for(int i = 0;i < nSameIDCount;++i)
    {
        for (int j = i+1; j < nSameIDCount; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity())
            {
                break;
            }
            if (petData1->getPetLevel() > petData2->getPetLevel())
            {
                dataArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //不同ID   品阶升序
    for(int i = nSameIDCount;i < nListSize;++i)
    {
        for (int j = i+1; j < nListSize; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() > petData2->getPetQuallity())
            {
                dataArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //不同ID 同品阶  等级升序
    for(int i = nSameIDCount;i < nListSize;++i)
    {
        for (int j = i+1; j < nListSize; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity())
            {
                break;
            }
            if (petData1->getPetLevel() > petData2->getPetLevel())
            {
                dataArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }

    //不同ID 同品阶  同等级  ID升序
    for(int i = nSameIDCount;i < nListSize;++i)
    {
        for (int j = i+1; j < nListSize; ++j)
        {
            petData1 = (MB_PetData*)dataArray->objectAtIndex(i);
            petData2 = (MB_PetData*)dataArray->objectAtIndex(j);
            
            if (petData1->getPetQuallity() != petData2->getPetQuallity()
                || petData1->getPetLevel() != petData2->getPetLevel())
            {
                break;
            }
            if (petData1->getPetTypeID() > petData2->getPetTypeID())
            {
                dataArray->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
}


void MB_LayerPetEnhance::ScolltoCenter()
{
    if(selectNpdw!=NULL)
    {
        int offset =-selectNpdw->opx2+200;
        m_pScollerView->getContainer()->stopAllActions();
        m_pScollerView->unschedule(schedule_selector(CCScrollView::deaccelerateScrolling));
        m_pScollerView->getContainer()->runAction(CCMoveTo::create(fabsf(m_pScollerView->getContainer()->getPositionX()-offset)/400, ccp(offset,0)));
    }
}
void MB_LayerPetEnhance::scrollViewDidScroll(CCScrollView* view)
{
    if (isFirstTouch && view->isTouchMoved () == false && fabsf(view->getScrollDistance().x)<1.5f) {
        ScolltoCenter();
    }else if(fabsf(view->getScrollDistance().x)<.1f)
    {
        isFirstTouch = true;
    }
}

void MB_LayerPetEnhance::reloadArray()
{
    if (m_pAllRoleArray) m_pAllRoleArray->removeAllObjects();
    else m_pAllRoleArray = new CCArray();
    MB_PetData* petData2 = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetID);
    MB_PetTemplate* petTemp = petData2->getTemplete();
    uint8_t uPetStar = petTemp->getPetStar();
    
    CCObject *petData;
    CCArray* pArray = MB_PetMgr::getInstance()->getPetDataArray();
    CCARRAY_FOREACH(pArray, petData){
        
        if (m_pLayerType == kPetTeamTypeEnhanceCost)
        {
            //查找同星级 不是同张卡牌 没上阵的卡牌 不是经验卡牌 作为材料
            MB_PetTemplate* petCost = ((MB_PetData*)petData)->getTemplete();
            if(!petCost)
            {
                continue;
            }
            uint8_t uPetCostStar = petCost->getPetStar();
            if (uPetStar != uPetCostStar
                || ((MB_PetData*)petData)->getPetID() == m_uPetID
                || MB_TeamData::getInstance()->checkInTeam((MB_PetData *)petData)
                || NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID())
                || NSGameHelper::checkIsGuardPet(((MB_PetData*)petData)->getPetID()))
            {
                continue;
            }
            if (((MB_PetData*)petData)->getIsHomelandPet())
            {
                continue;
            }
        }
        
        //上阵列表和升级选择 屏蔽经验卡牌
        if(m_pLayerType == kPetTeamTypeEquipment
           || m_pLayerType == kPetTeamTypeUpdate
           || m_pLayerType == kPetTeamTypeMove
           || m_pLayerType == kPetGuardTypeSelect )
        {
            if (NSGameHelper::checkIsExperienceCard(((MB_PetData*)petData)->getPetTypeID())) {
                continue;
            }
        }
        
        if (m_pLayerType == kPetGuardTypeSelect) //上阵守护 不显示队形里的精灵
        {
            if (MB_TeamData::getInstance()->checkInTeam((MB_PetData*)petData))
            {
                continue;
            }
        }
        m_pAllRoleArray->addObject(petData);
    }
    
    
    
    m_nListSize = m_pAllRoleArray->count();
    //排序
    if (m_nListSize > 1) {
        m_pAllRoleArray->sortArray(compare2);
    }
}
bool MB_LayerPetEnhance::initFunctions()
{
    m_pScollerView = CCScrollView::create(m_pNodeNaveigation->getContentSize());
    m_pScollerView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pNodeNaveigation->addChild(m_pScollerView);
    m_pScollerView->setSwaller(false);
    m_pScollerView->setDelegate(this);
    int nPosX = NPOSX;
    int nPosY = 95;
    m_pScollerView->setClippingToBounds(false);
    m_pTestNode = CCNode::create();
    m_pScollerView->addChild(m_pTestNode);
    for (int i = 0; i < m_nListSize; i++)
    {
        MB_PetData* petData = (MB_PetData*)m_pAllRoleArray->objectAtIndex(i);
        if (petData!=NULL) {
            MB_NodePetDuiWu* npdw = MB_NodePetDuiWu::create(petData->getPetID(),false);
            npdw->m_nZorder =99999-i;
            m_pTestNode->addChild(npdw,npdw->m_nZorder);
            npdw->opx2 =nPosX+npdw->m_nWidth;
            npdw->opy2 = nPosY;
            npdw->opx =npdw->m_pMoveNode->getPositionX();
            npdw->m_pInteam->setVisible(false);
            npdw->setPosition(ccp(npdw->opx2,npdw->opy2));
            nPosX += npdw->m_nWidth;
            npdw->m_pDetailBtn->setTouchEnabled(false);
        }
    }
    m_pScollerView->setContentSize(CCSize( nPosX+444, m_pNodeNaveigation->getContentSize().height));
    
    update(0);

    m_pScollerView->getContainer()->stopAllActions();
    m_pScollerView->schedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    if(m_nListSize==2)
    {
        m_pScollerView->m_tScrollDistance = ccp(-5.6f,0);
    }else
    {
        m_pScollerView->setContentOffset(ccp(-m_pScollerView->getContentSize().width+640+300,0));
        m_pScollerView->m_tScrollDistance = ccp(-16.1f,0);
    }

    return true;
}
void MB_LayerPetEnhance::update(float dt)
{
    CCArray* children = m_pTestNode->getChildren();
    if (children!=NULL) {
        for (int i=0; i< children->count();i++) {
            MB_NodePetDuiWu* npdw =  (MB_NodePetDuiWu*)children->objectAtIndex(i);
            CCPoint p = m_pTestNode->convertToWorldSpace( npdw->getPosition());
            if (npdw!=selectNpdw&&  p.x+25>TARGETX&&p.x+25< TARGETX+npdw->m_nWidth) {
                if (!(selectNpdw!=NULL&&selectNpdw->m_nPetId == npdw->m_nPetId)) {
                    if (selectNpdw!=NULL) {
                        selectNpdw->setSelectedState(false);
                    }
                    selectNpdw = npdw;
                    resetCostPetID(selectNpdw->m_nPetId);
                    npdw->setSelectedState(true);
                }
            }
            
            float span =fabs(p.x-TARGETX);
            if (span>SCALESPAN) {
                npdw->m_pMoveNode->setScale(SCALEX,SCALEY);
            }else
            {
                float sx =SCALEX+(1-SCALEX)* (1-(span/SCALESPAN));sx =sx>1?1:sx;sx = sx<SCALEX?SCALEX:sx;
                float sy =SCALEY+(1-SCALEY)* (1-(span/SCALESPAN));sy =sy>1?1:sy;sy = sy<SCALEY?SCALEY:sy;
                npdw->m_pMoveNode->setScale(sx,sy);
            }
            
            span = p.x-TARGETX_2;
            if (span>0) {
                float tempFloat =span/(660-TARGETX_2);
                npdw->m_pMoveNode->setPositionX(npdw->opx-tempFloat*SUOXIAOX);
            }else
            {
                npdw->m_pMoveNode->setPositionX(npdw->opx);
            }
        }
    }
}

int MB_LayerPetEnhance::insertZhen(uint64_t petId)
{
    MB_PetData* petData1;
    for (int i = 0; i < m_nListSize; ++i)
    {
        petData1 = (MB_PetData*)m_pAllRoleArray->objectAtIndex(i);
        
        if (petData1->getPetID()==petId) {
            m_pAllRoleArray->removeObjectAtIndex(i);
            return i;
        }
    }
}
void MB_LayerPetEnhance::onCommitEnd()
{
    m_pScollerView->setContentSize(CCSize(m_pScollerView->getContentSize().width-selectNpdw->m_nWidth,m_pScollerView->getContentSize().height));
    CCArray* children = m_pTestNode->getChildren();
    float tempOpx2 = selectNpdw->opx2;
    int _pos = children->count()-1-insertZhen(selectNpdw->m_nPetId);
    MB_NodePetDuiWu* npdw;
    if (_pos == 0) {
        m_pScollerView->getContainer()->stopAllActions();
        m_pScollerView->m_tScrollDistance = ccp(6.5f,0);
        m_pScollerView->schedule(schedule_selector(CCScrollView::deaccelerateScrolling));
    }else
    {
        for (int i= 0; i<_pos;i++) {
            npdw = (MB_NodePetDuiWu*)children->objectAtIndex(i);
            npdw->m_nZorder++;
            npdw->setZOrder(npdw->m_nZorder);
            npdw->opx2-=npdw->m_nWidth;
            npdw->setPositionX(npdw->opx2);
        }
    }

    m_pTestNode->removeChild(selectNpdw);
    --m_nListSize;
    children = m_pTestNode->getChildren();
    if (children->count()==0) {
        selectNpdw = NULL;
    }else
    {
        selectNpdw = (MB_NodePetDuiWu*)children->objectAtIndex(0);
        resetCostPetID(selectNpdw->m_nPetId);
    }
    
    update(0);
}
