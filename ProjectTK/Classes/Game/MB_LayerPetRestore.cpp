//
//  MB_LayerPetRestore.cpp
//  ProjectPM
//
//  Create by WenYong on 30/5/2014.
//
//
#include "MB_LayerPetRestore.h"
#include "MB_FunctionModule.h"
#include "MB_ServerRewardData.h"
#include "MB_petData.h"
#include "MB_NodeItemBook.h"
#include "MB_LayerPetEnhance.h"
#include "MB_LayerPetEnhanceSpecial.h"
#include "MB_LayerCommand.h"
#include "MB_LayerPetEquipment.h"
#include "MB_ScrollBg.h"
MB_LayerPetRestore::MB_LayerPetRestore()
{
    isUpdateUI = false;
    m_pPetCard	 = NULL;
    m_pPetNameSrc	 = NULL;
    m_pTextLevelSrc	 = NULL;
    m_pTextAttackSrc	 = NULL;
    m_pTextLifeSrc	 = NULL;
    m_pTextLevelDes	 = NULL;
    m_pTextAttackDes	 = NULL;
    m_pTextLifeDes	 = NULL;
    m_pStar[4]	 = NULL;
    m_pStar[1]	 = NULL;
    m_pStar[2]	 = NULL;
    m_pStar[3]	 = NULL;
    m_pStar[5]	 = NULL;
    m_pStar[6]	 = NULL;
    m_pStar[0]	 = NULL;
    m_pNodeCommit	 = NULL;
    m_pButtonCommit	 = NULL;
    m_pReward	 = NULL;
    m_pAnimation = NULL;
    m_pRewardArray = new CCArray;
    m_nPetUid = 0;
    m_bCanExit = true;

    
    m_bShowRoleInfoPanel = true;
    
    SOCKET_MSG_REGIST(SC_GER_DOWN_RANK,MB_LayerPetRestore);
    
    isHomeButtonShow =  ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->isVisible();
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(false);
}
MB_LayerPetRestore::~MB_LayerPetRestore()
{
    CC_SAFE_RELEASE_NULL(m_pPetCard);
    CC_SAFE_RELEASE_NULL(m_pPetNameSrc);
    CC_SAFE_RELEASE_NULL(m_pTextLevelSrc);
    CC_SAFE_RELEASE_NULL(m_pTextAttackSrc);
    CC_SAFE_RELEASE_NULL(m_pTextLifeSrc);
    CC_SAFE_RELEASE_NULL(m_pTextLevelDes);
    CC_SAFE_RELEASE_NULL(m_pTextAttackDes);
    CC_SAFE_RELEASE_NULL(m_pTextLifeDes);
    CC_SAFE_RELEASE_NULL(m_pStar[4]);
    CC_SAFE_RELEASE_NULL(m_pStar[1]);
    CC_SAFE_RELEASE_NULL(m_pStar[2]);
    CC_SAFE_RELEASE_NULL(m_pStar[3]);
    CC_SAFE_RELEASE_NULL(m_pStar[5]);
    CC_SAFE_RELEASE_NULL(m_pStar[6]);
    CC_SAFE_RELEASE_NULL(m_pStar[0]);
    CC_SAFE_RELEASE_NULL(m_pNodeCommit);
    CC_SAFE_RELEASE_NULL(m_pButtonCommit);
    CC_SAFE_RELEASE_NULL(m_pReward);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pRewardArray);
    SOCKET_MSG_UNREGIST(SC_GER_DOWN_RANK)
    

}

MB_LayerPetRestore* MB_LayerPetRestore::create(uint64_t uid)
{
    MB_LayerPetRestore* pInstance = new MB_LayerPetRestore;
    if (pInstance && pInstance->init())
    {
        pInstance->setUid(uid);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}
void MB_LayerPetRestore::setUid(uint64_t uid)
{
    m_nPetUid = uid;
    
    onResetWnd();
}
bool MB_LayerPetRestore::init()
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/card_layer_decompose.ccbi", this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    if(pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        for (int i=0; i<7; ++i)
        {
            m_pStarPt[i] = m_pStar[i]->getPosition();
        }
        addChild(MB_ScrollBg::create(right_bottom,.5f,3),-1);
        return true;
    }
    return false;
}
void MB_LayerPetRestore::onResetWnd()
{
    if (m_nPetUid==0)
    {
        m_pNodeCommit->setVisible(false);
        setStars(0);
        return;
    }
    
    MB_PetData* pData = MB_PetMgr::getInstance()->getPetDataByUID(m_nPetUid);
    if (pData)
    {
        m_pReward->removeAllChildren();
        m_pPetCard->removeAllChildren();
        char buff[64] = {};
        MB_PetTemplate* petTemplete = pData->getTemplete();
        
        if (pData->getPetQuallity()==0)
        {
            if (petTemplete)
            {
                int attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), pData->getPetLevel(), 0);
                sprintf(buff, "%d",attack1);
                m_pTextAttackSrc->setString(buff);
                m_pTextAttackDes->setString(buff);
                
                int hp1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), pData->getPetLevel(), 0);
                sprintf(buff, "%d",hp1);
                m_pTextLifeSrc->setString(buff);
                m_pTextLifeDes->setString(buff);
                
                sprintf(buff, "%d",pData->getPetLevel());
                m_pTextLevelSrc->setString(buff);
                m_pTextLevelDes->setString(buff);
                
                sprintf(buff, "%s+%d",petTemplete->getPetName(),pData->getPetQuallity());
                m_pPetNameSrc->setString(buff);
            }
            m_pNodeCommit->setVisible(false);
        }
        else
        {
            if (petTemplete)
            {
                int attack1 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), pData->getPetLevel(), pData->getPetQuallity());
                sprintf(buff, "%d",attack1);
                m_pTextAttackSrc->setString(buff);
                int attack2 = MB_PetMgr::getInstance()->calPetAttack(petTemplete->getPetAttack(), pData->getPetLevel(), pData->getPetQuallity()-1);
                sprintf(buff, "%d",attack2);
                m_pTextAttackDes->setString(buff);
                
                int hp1 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), pData->getPetLevel(), pData->getPetQuallity());
                sprintf(buff, "%d",hp1);
                m_pTextLifeSrc->setString(buff);
                int hp2 = MB_PetMgr::getInstance()->calPetHP(petTemplete->getPetHpMax(), pData->getPetLevel(), pData->getPetQuallity()-1);
                sprintf(buff, "%d",hp2);
                m_pTextLifeDes->setString(buff);
                
                sprintf(buff, "%d",pData->getPetLevel());
                m_pTextLevelSrc->setString(buff);
                m_pTextLevelDes->setString(buff);
                
                sprintf(buff, "%s+%d",petTemplete->getPetName(pData->getPetQuallity()/10+1),pData->getPetQuallity()%10);
                m_pPetNameSrc->setString(buff);
                MB_NodePetView* pView = MB_NodePetView::create(pData->getPetTypeID(), 1, 0);
                if (pView)
                {
                    m_pReward->addChild(pView);
                }
            }
            m_pNodeCommit->setVisible(true);
        }
        setStars(petTemplete->getPetStar());
        CCSprite* pCard = CCSprite::create();
        NSGameHelper::setMonsterCardDetailByTid(petTemplete->getPetTypeID(), pData->getPetQuallity(), pCard);
        m_pPetCard->addChild(pCard);
    }
    else
    {
        m_pNodeCommit->setVisible(false);
        setStars(0);
    }
}


void MB_LayerPetRestore::setStars(int nStar)
{
    for (int i=0; i<7; ++i)
    {
        m_pStar[i]->setPosition(m_pStarPt[i]);
    }
    
    NSGameHelper::centerStars(m_pStar, 7, nStar);
}

void MB_LayerPetRestore::onMsgRecv(CCNode* node, SocketResponse* response)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    assert(response != NULL);
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    if (Msg == SC_GER_DOWN_RANK)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        recvpet_down_rank(recvPacket);
    }
}
bool MB_LayerPetRestore::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPetCard",CCNode*,m_pPetCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPetNameSrc",CCLabelTTF*,m_pPetNameSrc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLevelSrc",CCLabelBMFont*,m_pTextLevelSrc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextAttackSrc",CCLabelBMFont*,m_pTextAttackSrc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLifeSrc",CCLabelBMFont*,m_pTextLifeSrc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLevelDes",CCLabelBMFont*,m_pTextLevelDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextAttackDes",CCLabelBMFont*,m_pTextAttackDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTextLifeDes",CCLabelBMFont*,m_pTextLifeDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar4",CCSprite*,m_pStar[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar1",CCSprite*,m_pStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar2",CCSprite*,m_pStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar3",CCSprite*,m_pStar[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar5",CCSprite*,m_pStar[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar6",CCSprite*,m_pStar[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pStar7",CCSprite*,m_pStar[6]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCommit",CCNode*,m_pNodeCommit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pButtonCommit",CCControlButton*,m_pButtonCommit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pReward",CCNode*,m_pReward);
	return false;
}
SEL_MenuHandler MB_LayerPetRestore::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerPetRestore::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerPetRestore::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onCommitClicked",MB_LayerPetRestore::onCommitClicked);
	return NULL;
}

void MB_LayerPetRestore::onCloseClick(CCObject* pSender)
{
    if (!m_bCanExit)
    {
        return;
    }
    if (isUpdateUI) {
        MB_LayerPetDetail* ptr =  dynamic_cast<MB_LayerPetDetail*>(getLogicParent());
        if (ptr) {
            ptr->resetBaseInfo();
        }
    }
    ((MB_LayerCommand*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_MAIN_COMMAND))->rootNode->setVisible(isHomeButtonShow);
    popWindow(true);
}

void MB_LayerPetRestore::onCommitClicked(CCObject* pSender)
{
    if (m_nPetUid==0)
    {
        return ;
    }
    MB_Message::sharedMB_Message()->showMessage("",15);
    sendpet_down_rank(m_nPetUid);
}

/*
 message     recvpet_down_rank[id=10476]{
 required    int8                result          =1;//0表示成功,1卡牌不存在，2经验卡牌不能退化，3品阶为0，无法退化，4钻石不足
 repeated    p_pet_view          add_pet_list    =2;//退化得到的卡牌
 }
 
 struct p_pet_view_
 {
 uint16_t			petQuality; //精灵品阶
 uint16_t			petLevel;   //精灵等级
 uint16_t			petTypeID;  //精灵模版ID
 };
 */
void MB_LayerPetRestore::recvpet_down_rank(MB_MsgBuffer* pRecv)
{
    uint8_t u8 = 0;
    pRecv->readU8(&u8);
    if (u8 == 0)
    {
        isUpdateUI = true;
        if (global_layerPetEquipment!=NULL) {
            global_layerPetEquipment->isUpdateUI = true;
        }

        uint16_t u16 = 0;
        pRecv->readU16(&u16);
        MB_PetView* pView = NULL;
        m_pRewardArray->removeAllObjects();
        for (uint16_t i=0; i<u16; ++i)
        {
            pView = new MB_PetView;
            if (pView->read(pRecv))
            {
                m_pRewardArray->addObject(pView);
            }
            CC_SAFE_RELEASE_NULL(pView);
        }

        m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_LayerPetRestore::onAnimationFinished));
        m_pAnimation->runAnimationsForSequenceNamed("restore");
        m_bCanExit = false;
        
        {
            MB_TARGET_PARENT(MB_LayerPetEnhance, ptr);
            if (ptr)
            {
                ptr->dirty();
            }
        }
        
        {
            MB_TARGET_PARENT(MB_LayerPetEnhanceSpecial, ptr)
            if(ptr)
            {
                ptr->dirty();
            }
        }
    }
    else if(u8==1)
    {
        MB_Message::sharedMB_Message()->showMessage("卡牌不存在");
    }
    else if(u8==2)
    {
        MB_Message::sharedMB_Message()->showMessage("经验卡牌不能退化");
    }
    else if(u8==3)
    {
        MB_Message::sharedMB_Message()->showMessage("品阶为0, 无法退化");
    }
    else if(u8==4)
    {
        MB_Message::sharedMB_Message()->showMessage("宝石不足");
    }
}

/*
 // 武将降品
 message     sendpet_down_rank[id=10475]{
 required    int64               srcPetID        =1;//选择降低品阶的武将ID
 }
 */
void MB_LayerPetRestore::sendpet_down_rank(uint64_t uid)
{
    SOCKET_REQUEST_START(CS_GER_DOWN_RANK);
    packet->WriteUINT64(uid);
    SOCKET_REQUEST_END(SC_GER_DOWN_RANK, NULL);
}

void MB_LayerPetRestore::onAnimationFinished()
{
    if (m_pRewardArray->count()!=0)
    {
        MB_ResWindow* pWnd = MB_LayerRewardMore::create(m_pRewardArray);
        if (pWnd)
        {
            pWnd->setShowRoleInfoPanel(false);
            pushWindow(pWnd);
            m_pRewardArray->removeAllObjects();
        }
    }
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    m_bCanExit = true;
    onResetWnd();
}

void MB_LayerPetRestore::onExit()
{
    MB_ResWindow::onExit();
    
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
    
    if (m_pRewardArray->count()!=0)
    {
        MB_ResWindow* pWnd = MB_LayerRewardMore::create(m_pRewardArray);
        if (pWnd)
        {
            CCFunctionInterface::getCurrentFunctionWnd()->pushWindow(pWnd);
        }
    }
}
