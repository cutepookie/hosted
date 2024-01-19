#include "MB_LayerPetEnhanceSpecial.h"
#include "MB_RoleSoundSystem.h"
#include "MB_LayerPetRestore.h"
#include "MB_NodePetTeam.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerPetEnhance.h"
#include "MB_ScrollBg.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LayerPetEnhanceSpecial::MB_LayerPetEnhanceSpecial()
{
    isUpdateUI = false;
    m_uPetID = 0;
    m_pTTFLevel1 = NULL;
    m_pTTFLevel2 = NULL;
    m_pCard = NULL;
    m_pTTFAttack1 = NULL;
    m_pTTFAttack2 = NULL;
    m_pTTFLife1 = NULL;
    m_pTTFLife2 = NULL;
    for (int i = 0; i < MAX_ITEM_RANKGOD; ++i) {
        m_pCostIcon[i] = NULL;
        m_pTextCostName[i] = NULL;
        m_pNodeCover[i] = NULL;
        m_pNodeCost[i] = NULL;
    }
    for (int i = 0; i < MAX_GER_STAR; i++) {
        m_pStar[i] = NULL;
    }
    m_pPetName1 = NULL;
    m_pNodeRank = NULL;
    m_pNodeRankMaxTip = NULL;
    m_pNodeGod = NULL;
    m_pNodeSaint = NULL;
    
    m_pCCBAnimationMgr = NULL;
    m_bShowRoleInfoPanel = true;
    m_nNowShape = 1;
    m_nNextShape = 1;
    SOCKET_MSG_REGIST(SC_GER_UP_RANK, MB_LayerPetEnhanceSpecial);
}

MB_LayerPetEnhanceSpecial::~MB_LayerPetEnhanceSpecial()
{
    SOCKET_MSG_UNREGIST(SC_GER_UP_RANK);
    CC_SAFE_RELEASE_NULL(m_pTTFLevel1);
    CC_SAFE_RELEASE_NULL(m_pTTFLevel2);
    CC_SAFE_RELEASE_NULL(m_pCard);
    CC_SAFE_RELEASE_NULL(m_pTTFLife1);
    CC_SAFE_RELEASE_NULL(m_pTTFLife2);
    CC_SAFE_RELEASE_NULL(m_pTTFAttack1);
    CC_SAFE_RELEASE_NULL(m_pTTFAttack2);
    for (int i = 0; i < MAX_ITEM_RANKGOD; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pCostIcon[i]);
        CC_SAFE_RELEASE_NULL(m_pTextCostName[i]);
        CC_SAFE_RELEASE_NULL(m_pNodeCover[i]);
        CC_SAFE_RELEASE_NULL(m_pNodeCost[i]);
    }
    for (int i = 0; i < MAX_GER_STAR; i++) {
        CC_SAFE_RELEASE_NULL(m_pStar[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pPetName1);
    CC_SAFE_RELEASE_NULL(m_pNodeSaint);
    CC_SAFE_RELEASE_NULL(m_pNodeGod);
    CC_SAFE_RELEASE_NULL(m_pNodeRankMaxTip);
    CC_SAFE_RELEASE_NULL(m_pNodeRank);
    
    CC_SAFE_RELEASE(m_pCCBAnimationMgr);
    
//    CC_SAFE_RELEASE(m_pNodeEff);
    
}
MB_LayerPetEnhanceSpecial* MB_LayerPetEnhanceSpecial::create(uint64_t petID)
{
    MB_LayerPetEnhanceSpecial* layer = new MB_LayerPetEnhanceSpecial();
    if (layer && layer->init(petID)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

// on "init" you need to initialize your instance
bool MB_LayerPetEnhanceSpecial::init(uint64_t petID)
{
    CCLOG("MB_LayerPetEnhanceSpecial::init");
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    m_uPetID = petID;
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/card_layer_breakthrough.ccbi", this);
    this->addChild(NSGameHelper::createDisableTouchLayer1());
    this->addChild(pScene);
    m_pCCBAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pCCBAnimationMgr);

    CC_SAFE_RELEASE_NULL(pCCBReader);
    
                                                          
                                                          
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetID);
    m_nNowShape = NSGameHelper::getShapeTypeByRank(petData->getPetQuallity());
    if(petData->getPetQuallity()%10 == 9)
    {
        m_nNextShape = m_nNowShape+1;
    }
    else
    {
        m_nNextShape = m_nNowShape;
    }
                                                
    onResetWnd();
    int m_nStar = petData->getTemplateStar();
    NSGameHelper::centerStars(m_pStar, MAX_GER_STAR, m_nStar);
    addChild(MB_ScrollBg::create(right_bottom,.5f,3),-1);
	return true;
}

void MB_LayerPetEnhanceSpecial::onExit()
{
    m_pCCBAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
    MB_ResWindow::onExit();
}


void MB_LayerPetEnhanceSpecial::resetPetID(uint64_t petID)
{
    if (m_uPetID == petID) {
        return;
    }
    
    m_uPetID = petID;
    dirty();
}

void MB_LayerPetEnhanceSpecial::resetCostPetID(uint64_t petID)
{
    if (m_uPetID == petID) {
        return;
    }
    dirty();
}

void MB_LayerPetEnhanceSpecial::onResetWnd()
{
    if (m_uPetID == 0)
    {
        m_pTTFAttack1->setString("");
        m_pTTFAttack2->setString("");
        m_pTTFLife1->setString("");
        m_pTTFLife2->setString("");
        for (int i = 0; i < MAX_ITEM_RANKGOD; ++i) {
            m_pCostIcon[i]->setVisible(false);
            m_pCostIcon[i]->removeAllChildren();
            m_pTextCostName[i]->setString("");
            m_pNodeCover[i]->setVisible(false);
        }
        
        m_pNodeRank->setVisible(true);
        m_pNodeRankMaxTip->setVisible(false);
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
        //获取名字
        const char* str1 = MB_PetMgr::getInstance()->getPetRealName(petData->getPetTypeID(),petData->getPetQuallity());
        m_pPetName1->setString(str1);
        m_pPetName1->setVisible(true);
        CC_SAFE_DELETE_ARRAY(str1);
        
        //获取名字
        MB_PetTemplate* petTemplete = petData->getTemplete();
        if (petData->getPetQuallity() == 9) {
            m_pNodeRank->setVisible(false);
            m_pNodeGod->setVisible(true);
            m_pNodeSaint->setVisible(false);
            m_pNodeRankMaxTip->setVisible(false);
        }
        else if (petData->getPetQuallity() == 19)
        {
            m_pNodeSaint->setVisible(true);
            m_pNodeRankMaxTip->setVisible(false);
            m_pNodeRank->setVisible(false);
            m_pNodeGod->setVisible(false);
        }
        else if (petData->getPetQuallity() == 20)
        {
            m_pNodeRankMaxTip->setVisible(true);
            m_pNodeRank->setVisible(false);
            m_pNodeGod->setVisible(false);
            m_pNodeSaint->setVisible(false);
        }
        else
        {
            m_pNodeGod->setVisible(false);
            m_pNodeRank->setVisible(true);
            m_pNodeRankMaxTip->setVisible(false);
            m_pNodeSaint->setVisible(false);
        }
        //卡片
        m_pCard->removeAllChildren();
        MB_NodePetCard* petCard = MB_NodePetCard::create(m_uPetID);
        m_pCard->addChild(petCard);
        m_pCard->setVisible(true);
        
        char strInfo1[128] = "";
        char strInfo2[128] = "";
        sprintf(strInfo1, "%u", petData->getPetLevel());
        m_pTTFLevel1->setString(strInfo1);
        m_pTTFLevel2->setString(strInfo1);
        
        int nextQuallity = petData->getPetQuallity()+1;
        if (petData->getPetQuallity() == 20) {
            nextQuallity = petData->getPetQuallity();
        }
        //计算裸身的当前和预估
        int attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), petData->getPetQuallity());
        int attack2 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), petData->getPetLevel(), nextQuallity);
        sprintf(strInfo1,"%d",attack1);
        sprintf(strInfo2,"%d",attack2);
        m_pTTFAttack1->setString(strInfo1);
        m_pTTFAttack2->setString(strInfo2);
        
        int hp1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), petData->getPetQuallity());
        int hp2 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), petData->getPetLevel(), nextQuallity);
        sprintf(strInfo1,"%d",hp1);
        sprintf(strInfo2,"%d",hp2);
        m_pTTFLife1->setString(strInfo1);
        m_pTTFLife2->setString(strInfo2);
        //计算材料
        CCArray* costArray = NULL;
        uint16_t rankGodID = 0;
        if (petData->getPetQuallity() == 9)
        {
            rankGodID = petTemplete->getRankGodID();
            
        }
        else if (petData->getPetQuallity() == 19)
        {
            rankGodID = petTemplete->getRankSaintID();
        }

        for (int i = 0; i < MB_PetMgr::getInstance()->getPetGodArray()->count(); i++)
        {
            MB_PetQualityCostSpecialTemplete* costTemplete = (MB_PetQualityCostSpecialTemplete*)MB_PetMgr::getInstance()->getPetGodArray()->objectAtIndex(i);
            if (costTemplete->getCostID() == rankGodID) {
                costArray = costTemplete->getCostArray();
                break;
            }
        }
        //没有找到材料模板
        if (costArray == NULL) {
            MB_LOG("Pet rank up err! rank:%d", rankGodID);
            return;
        }
        
        char* strTempName = new char[128];
        for (int i = 0; i < costArray->count(); ++i)
        {
            if (i < MAX_ITEM_RANKGOD)
            {
                MB_PetQualityCostSpecialTempleteValue* costItem = (MB_PetQualityCostSpecialTempleteValue*)costArray->objectAtIndex(i);
                MB_NodeItem* nodeItem = MB_NodeItem::create(costItem->getItemTypeID(),kNINWNONE);
                nodeItem->showNameCount(false);
                m_pCostIcon[i]->addChild(nodeItem);
            
                int Num = 0;
                int NeedNum = 0;
                MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(costItem->getItemTypeID());
    
                
                NeedNum = costItem->getNum();
                if (costItem->getItemTypeID() == COIN_ID)
                {
                    Num = MB_RoleData::getInstance()->getCoin();
                    if (Num >= NeedNum)
                    {
                        m_pNodeCover[i]->setVisible(false);
                    }
                    else
                    {
                        m_pTextCostName[i]->setColor(ccRED);
                        m_pNodeCover[i]->setVisible(true);
                    }
                }
                else if (costItem->getItemTypeID() == REPUTATION_ID)
                {
                    Num = MB_RoleData::getInstance()->getReputation();
                    if (Num >= NeedNum)
                    {
                        m_pNodeCover[i]->setVisible(false);
                    }
                    else
                    {
                        m_pTextCostName[i]->setColor(ccRED);
                        m_pNodeCover[i]->setVisible(true);
                    }
                }
                else if (costItem->getItemTypeID() == GOLD_ID)
                {
                    Num = MB_RoleData::getInstance()->getGold();
                    if (Num >= NeedNum)
                    {
                        m_pNodeCover[i]->setVisible(false);
                    }
                    else
                    {
                        m_pTextCostName[i]->setColor(ccRED);
                        m_pNodeCover[i]->setVisible(true);
                    }
                }
                else
                {
                    Num = MB_ItemMgr::getInstance()->getItemEntityCount(costItem->getItemTypeID());
                    if (Num >= NeedNum)
                    {
                        m_pNodeCover[i]->setVisible(false);
                    }
                    else
                    {
                        m_pTextCostName[i]->setColor(ccRED);
                        m_pNodeCover[i]->setVisible(true);
                    }
                }

                if(itemTemplete)
                {
                    sprintf(strTempName, "%s* %d/%d",itemTemplete->getItemName(), Num,NeedNum);
                }
                m_pTextCostName[i]->setString(strTempName);
                if (Num >= NeedNum)
                {
                    m_pTextCostName[i]->setColor(ccWHITE);
                }
                else
                {
                    m_pTextCostName[i]->setColor(ccRED);
                }
            }
        }
        CC_SAFE_DELETE_ARRAY(strTempName);
    }
    
}

bool MB_LayerPetEnhanceSpecial::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCard", CCNode*, m_pCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFLevel1", CCLabelBMFont*, m_pTTFLevel1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFLevel2", CCLabelBMFont*, m_pTTFLevel2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFAttack1", CCLabelBMFont*, m_pTTFAttack1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFAttack2", CCLabelBMFont*, m_pTTFAttack2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFLife1", CCLabelBMFont*, m_pTTFLife1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFLife2", CCLabelBMFont*, m_pTTFLife2);
    char strCostIcon[] = "m_pCostIcon1";
    char strTextCostName[] = "m_pTextCostName1";
    char strNodeCover[] = "nodeCover1";
    char strNodeCost[] = "NodeCost1";
    for (int i = 0; i < MAX_ITEM_RANKGOD; ++i)
    {
        strCostIcon[11] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strCostIcon, CCNode*, m_pCostIcon[i]);
        strTextCostName[15] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strTextCostName, CCLabelTTF*, m_pTextCostName[i]);
        strNodeCover[9] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strNodeCover, CCNode*, m_pNodeCover[i]);
        strNodeCost[8] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strNodeCost, CCNode*, m_pNodeCost[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRank", CCNode*, m_pNodeRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRankMaxTip", CCNode*, m_pNodeRankMaxTip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGod", CCNode*, m_pNodeGod);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSaint", CCNode*, m_pNodeSaint);
    char strStar[] = "m_pStar1";
    for (int i = 0; i < MAX_GER_STAR; i++) {
        strStar[7] = '1' + i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, strStar, CCSprite*, m_pStar[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPetName1", CCLabelTTF*, m_pPetName1);

    return true;
}

SEL_MenuHandler MB_LayerPetEnhanceSpecial::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPetEnhanceSpecial::onCloseClick);
    return NULL;
}

SEL_CCControlHandler MB_LayerPetEnhanceSpecial::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRankClicked", MB_LayerPetEnhanceSpecial::onRankClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGodClicked", MB_LayerPetEnhanceSpecial::onGodClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSaintClicked", MB_LayerPetEnhanceSpecial::onSaintClicked);
    return NULL;
}
void MB_LayerPetEnhanceSpecial::onCloseClick(cocos2d::CCObject *pSender)
{
    if (isUpdateUI) {
        MB_LayerPetDetail* ptr =  dynamic_cast<MB_LayerPetDetail*>(getLogicParent());
        if (ptr) {
            ptr->resetBaseInfo();
        }
    }
    popWindow(true);
}

void MB_LayerPetEnhanceSpecial::onRankClicked(cocos2d::CCObject *pSender)
{
    MB_ResWindow* layer = MB_LayerPetEnhance::create(kPetEnhanceEntrMain,m_uPetID);
    this->replaceLayer(layer);
}

void MB_LayerPetEnhanceSpecial::onGodClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("MB_LayerPetEnhanceSpecial onGodClicked");
    
    for (int i = 0; i < MAX_ITEM_RANKGOD; i++) {
        if (m_pNodeCover[i]->isVisible() == true)
        {
            MB_Message::sharedMB_Message()->showMessage("材料不足.");
            return;
        }
    }
    
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_PetMgr::getInstance()->sendpet_up_rank(m_uPetID, 0);
    
}

void MB_LayerPetEnhanceSpecial::onSaintClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("MB_LayerPetEnhanceSpecial onSaintClicked");

    for (int i = 0; i < MAX_ITEM_RANKGOD; i++) {
        if (m_pNodeCover[i]->isVisible() == true)
        {
            MB_Message::sharedMB_Message()->showMessage("材料不足.");
            return;
        }
    }
    
    MB_Message::sharedMB_Message()->showMessage("",15);
    MB_PetMgr::getInstance()->sendpet_up_rank(m_uPetID, 0);
}
void MB_LayerPetEnhanceSpecial::onMsgRecv(CCNode* node, SocketResponse* response)
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

bool MB_LayerPetEnhanceSpecial::recvpet_up_rank(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1)
    {
        isUpdateUI = true;
        dirty();
        m_pCCBAnimationMgr->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerPetEnhanceSpecial::OnAnimationOver));
        m_pCCBAnimationMgr->runAnimationsForSequenceNamed("rankup");
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_ZhuanSheng).c_str());
    }
    return true;
}

void MB_LayerPetEnhanceSpecial::OnAnimationOver()
{
    m_pCCBAnimationMgr->setAnimationCompletedCallback(NULL,NULL);
//    m_pNodeEff->setVisible(false);
    MB_PetData* petData = MB_PetMgr::getInstance()->getPetDataByUID(m_uPetID);
    m_nNowShape = NSGameHelper::getShapeTypeByRank(petData->getPetQuallity());
    m_nNextShape = m_nNowShape;
    onResetWnd();
    if (m_nNowShape >= 3 || (petData->getPetQuallity() != 9 && petData->getPetQuallity() != 19))
    {
        for (int i = 0; i < MAX_ITEM_RANKGOD; i++)
        {
            m_pNodeCost[i]->setVisible(false);
        }
    }
}


void MB_LayerPetEnhanceSpecial::onEnter()
{
    MB_ResWindow::onEnter();
    if (m_nNowShape == 1)
    {
        PlayRoleSound(kSoundEnterFirstTranform);
    }
    else if(m_nNowShape == 2)
    {
        PlayRoleSound(kSoundEnterSecondTranform);
    }
    
}
