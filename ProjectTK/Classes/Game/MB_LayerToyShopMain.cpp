//
//  MB_LayerToyShopMain.cpp
//  ProjectPM
//
//  Created by CHK on 14-3-14.
//
//

#include "MB_LayerToyShopMain.h"
#include "MB_ShopData.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"
#include "MB_RoleData.h"
#include "Game.h"
#include "MB_NodePetCard.h"
#include "MB_ParsingReward.h"
#include "MB_NodeShowCard.h"
#include "MB_ScrollBg.h"
#include "MB_LayerShopMain.h"
#include "MB_DrawEquip.h"
#include "MB_ToyShopInterface.h"
#include "MB_DrawEquipmentProtocol.h"
#include "MB_ShopCallCardDataSource.h"
#include "MB_NodeCallcardUnit.h"
#include "MB_FunctionModule.h"

#define DRAW_EQUIP_MAX 6
MB_LayerToyShopMain::MB_LayerToyShopMain() :
m_pNodeEquip(NULL), m_pNodePet(NULL)
, m_pEquipCostItem(NULL), m_pEquipCostGlod(NULL),
m_pEquipSelfItem(NULL), m_pNodeEquipContainer(NULL)
, m_pBtnEquipRefresh(NULL), m_pBtnEquipBegin(NULL), m_pLabelRate(NULL)
{
    SOCKET_MSG_REGIST(SC_BOX_SHOP_INFO, MB_LayerToyShopMain);
    SOCKET_MSG_REGIST(SC_BOX_GET_SPRIT_EQUIP_COUNT, MB_LayerToyShopMain);
    SOCKET_MSG_REGIST(SC_BOX_SHOP, MB_LayerToyShopMain);
    
    SOCKET_MSG_REGIST(RECV_CARD_DISTROY, MB_LayerToyShopMain);
    SOCKET_MSG_REGIST(RECV_CARD_DRAW, MB_LayerToyShopMain);
    SOCKET_MSG_REGIST(RECV_CARD_REFRESH, MB_LayerToyShopMain);
    
    m_pNodeReward = NULL;
    m_pShielding = NULL;
    m_pFunctionPet = NULL;
    m_pFunctionEquip = NULL;
    m_nLastTag = 0;
    m_pItemEquipGet = new CCArray;
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
    for (int i = 0; i < 6; ++i)
    {
        CCNode* node =MB_DrawEquip::create(NULL);
        m_pItemEquipGet->addObject(node);
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerToyShopMain",true);
}

MB_LayerToyShopMain::~MB_LayerToyShopMain(void)
{
    CC_SAFE_RELEASE_NULL(m_pItemEquipGet);
    CC_SAFE_RELEASE_NULL(m_pShielding);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip);
    CC_SAFE_RELEASE_NULL(m_pNodePet);
    CC_SAFE_RELEASE_NULL(m_pNodeEquipContainer);
    CC_SAFE_RELEASE_NULL(m_pBtnEquipRefresh);
    CC_SAFE_RELEASE_NULL(m_pBtnEquipBegin);
    CC_SAFE_RELEASE_NULL(m_pLabelRate);
    CC_SAFE_RELEASE_NULL(m_pEquipCostItem);
    CC_SAFE_RELEASE_NULL(m_pEquipCostGlod);
    CC_SAFE_RELEASE_NULL(m_pEquipSelfItem);
    CC_SAFE_RELEASE_NULL(m_pFunctionPet);
    CC_SAFE_RELEASE_NULL(m_pFunctionEquip);
//        CC_SAFE_RELEASE_NULL(m_pTableView);
    
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP);
    SOCKET_MSG_UNREGIST(SC_BOX_GET_SPRIT_EQUIP_COUNT);
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP_INFO);
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP);
    
    
    SOCKET_MSG_UNREGIST(RECV_CARD_DISTROY);
    SOCKET_MSG_UNREGIST(RECV_CARD_DRAW);
    SOCKET_MSG_UNREGIST(RECV_CARD_REFRESH);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerToyShopMain",false);
}
bool MB_LayerToyShopMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pInterface = dynamic_cast<MB_ToyShopInterface*>(pDataSource);
    return m_pInterface != NULL;
}

bool MB_LayerToyShopMain::init()
{
    MB_ResWindow::init();
    
    CCNode*  node = loadResource("res/shop_layer_callcard.ccbi");
    this->addChild(node);
    
    
    NodeCallcardUnit = MB_NodeCallcardUnit::create();
    NodeCallcardUnit->layerToyShopMain = this;
    m_pNodePet->addChild(NodeCallcardUnit);
    
    m_pFunctionPet->setIsScale(false);
    m_pFunctionEquip->setIsScale(false);
    
    changeFunction(kCallPet);
    
    addChild(MB_ScrollBg::create(right_bottom,.5f,0),-1);
    return true;
}
void MB_LayerToyShopMain::onExit()
{
    PlayBackGround(kmBackGround_Normal);
    MB_FunctionMainWnd::onExit();
}

void MB_LayerToyShopMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_CallCard);
}

bool MB_LayerToyShopMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    
    char buff[20] = { 0 };
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip", CCNode*, m_pNodeEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet", CCNode*, m_pNodePet);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelRate", CCLabelTTF*, m_pLabelRate);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEquipCostItem", CCLabelBMFont*, m_pEquipCostItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEquipCostGlod", CCLabelBMFont*, m_pEquipCostGlod);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEquipSelfItem", CCLabelBMFont*, m_pEquipSelfItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquipContainer", CCNode*, m_pNodeEquipContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnEquipBegin", CCControlButton*, m_pBtnEquipBegin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnEquipRefresh", CCControlButton*, m_pBtnEquipRefresh);
    
    
    ////////////////////////////
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pFunctionPet",CCMenuItemImage*,m_pFunctionPet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pFunctionEquip",CCMenuItemImage*,m_pFunctionEquip);
    
    for (int i = 0; i < DRAW_EQUIP_MAX; ++i)
    {
        sprintf(buff, "p%d", i);
        if (pTarget == this && 0 == strcmp(pMemberVariableName, buff))
        {
            m_equipPos[i] = pNode->getPosition();
            return false;
        }
    }
    return false;
}

SEL_MenuHandler MB_LayerToyShopMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFunctionPet", MB_LayerToyShopMain::onFunctionPet);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFunctionEquip",MB_LayerToyShopMain::onFunctionEquip);
    return NULL;
}

SEL_CCControlHandler MB_LayerToyShopMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCallEquipClick", MB_LayerToyShopMain::onCallEquipClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEquipRefreshClick",MB_LayerToyShopMain::onEquipRefreshClick);
    return NULL;
}


void MB_LayerToyShopMain::onFunctionPet(CCObject*)
{
    if (m_nCurFun==kCallPet) {
        return;
    }
    changeFunction(kCallPet);
}

void MB_LayerToyShopMain::onFunctionEquip(CCObject*)
{
    if (m_nCurFun==kCallEquip) {
        return;
    }
    changeFunction(kCallEquip);
}

void MB_LayerToyShopMain::onCallEquipClick(CCObject*)
{
    MB_DrawEquip* pObj = NULL;
    CCARRAY_FOREACH_4TYPE(m_pItemEquipGet, MB_DrawEquip*, pObj)
    {
        if (!pObj->getisDraw())pObj->FlipBack();
    }
    this->runAction(CCSequence::create(CCDelayTime::create(.4f), CCCallFunc::create(this, callfunc_selector(MB_LayerToyShopMain::shuffleItemEquips)), NULL));
    m_pBtnEquipBegin->setEnabled(false);
}

void MB_LayerToyShopMain::onEquipRefreshClick(CCObject*)
{
    m_pInterface->send_card_refresh();
}

void MB_LayerToyShopMain::onChooseEquip(uint16_t pos)
{
    m_pInterface->send_card_draw(pos);
}

void MB_LayerToyShopMain::changeFunction(ECallFun e)
{
    m_nCurFun = e;
    m_pNodePet->setVisible(e == kCallPet);
    m_pNodeEquip->setVisible(e == kCallEquip);
    
    if (e == kCallPet)
    {
    }
    else
    {
        resetItemEquips();
    }
    onResetWnd();
}

void MB_LayerToyShopMain::recv_card_draw(MB_MsgBuffer* pRecv)
{
    uint8_t result = 0;
    pRecv->readU8(&result);
    if (result == 1)
    {
        uint8_t pos;
        pRecv->readU8(&pos);
        
        MB_DrawEquip* pObj = NULL;
        int i = 0;
        CCARRAY_FOREACH_4TYPE(m_pItemEquipGet, MB_DrawEquip*, pObj)
        {
            pObj->setDrawCardData((MB_DrawCardData*)m_pInterface->getCardList()->objectAtIndex(i));
            if (pObj->getTag() == pos)
            {
                pObj->FlipFont();
            }
            else
            {
                pObj->runAction(CCSequence::create(CCDelayTime::create(.5f), CCCallFunc::create(pObj, callfunc_selector(MB_DrawEquip::FlipFont)), NULL));
            }
            ++i;
        }
        m_pBtnEquipBegin->setEnabled(m_pInterface->getOpendCount() < 6);
    }
}

void MB_LayerToyShopMain::onMsgDeliver(int Msg, MB_MsgBuffer* pRecv)
{
    switch (Msg)
    {
        case SC_BOX_SHOP:
            recv_box_shop(pRecv);
            break;
        case SC_BOX_GET_SPRIT_EQUIP_COUNT:
        case SC_BOX_SHOP_INFO:
            this->onResetWnd();
            break;
        case RECV_CARD_REFRESH:
        {
            MB_DrawEquip* pObj = NULL;
            int i = 0;
            CCARRAY_FOREACH_4TYPE(m_pItemEquipGet, MB_DrawEquip*, pObj)
            {
                pObj->setDrawCardData((MB_DrawCardData*)m_pInterface->getCardList()->objectAtIndex(i));
                pObj->FlipBackFont();
                ++i;
            }
            m_pBtnEquipBegin->setEnabled(true);
            this->onResetWnd();
        }
            break;
        case RECV_CARD_DRAW:
            recv_card_draw(pRecv);
            this->onResetWnd();
            break;
        case RECV_CARD_DISTROY:
            resetItemEquips();
            break;
        default:
            break;
    }
}

void MB_LayerToyShopMain::onResetWnd()
{
    m_pFunctionPet->setEnabled(m_nCurFun != kCallPet);
    m_pFunctionEquip->setEnabled(m_nCurFun != kCallEquip);
    if (m_nCurFun == kCallPet)
    {
        CCObject* pObj = MB_ShopMgr::getInstance()->getShopBoxTemplete()->objectAtIndex(0);
        MB_ShopBoxTemplete* pBoxTemplete = dynamic_cast<MB_ShopBoxTemplete*>(pObj);
        
        

        char buff[20] = { 0 };
        if (pBoxTemplete)
        {
            //道具数量
            sprintf(buff, "%d", pBoxTemplete->getItemCount());
            NodeCallcardUnit->m_pCostLabels[0]->setString(buff);
            
            //一次花费
            sprintf(buff, "%d", pBoxTemplete->getCost1());
            NodeCallcardUnit->m_pCostLabels[1]->setString(buff);
            
            //十次花费
            sprintf(buff, "%d", pBoxTemplete->getCost10());
            NodeCallcardUnit->m_pCostLabels[2]->setString(buff);
            
            sprintf(buff, "%d", pBoxTemplete->getNeedCallTimes());
            NodeCallcardUnit->m_pNeedCallTimesLabel->setString(buff);
            
            //自己拥有的道具数量
            sprintf(buff, "%d", ItemMgr->getItemEntityCount(pBoxTemplete->getItemID()));
            NodeCallcardUnit->m_pslfCallBallCountLabel->setString(buff);
        }
    }
    else if (m_nCurFun == kCallEquip)
    {
        int nNeed = m_pInterface->getNeedItemNums();
        m_pEquipCostItem->setString(CCString::createWithFormat("%d", nNeed)->getCString());
        m_pEquipCostGlod->setString(CCString::createWithFormat("%d", nNeed * m_pInterface->getItemPrice())->getCString());
        m_pEquipSelfItem->setString(CCString::createWithFormat("%d", ItemMgr->getItemEntityCount(30002))->getCString());
        MB_ItemTemplate* pTemp = ItemMgr->getItemTemplateByID(30002);
        if (pTemp)
        {
            CCString* pstr = CCString::createWithFormat("召唤石不足将直接使用宝石，1%s＝%d宝石", pTemp->getItemName(), m_pInterface->getItemPrice());
            if (m_pLabelRate)m_pLabelRate->setString(pstr->getCString());
        }
        m_pBtnEquipBegin->setEnabled(m_pInterface->getOpendCount() < 6);
    }
}

void MB_LayerToyShopMain::resetItemEquips()
{
    m_pNodeEquipContainer->removeAllChildren();
    MB_DrawEquip* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH_4TYPE(m_pItemEquipGet, MB_DrawEquip*, pObj)
    {
        pObj->setDrawCardData((MB_DrawCardData*)m_pInterface->getCardList()->objectAtIndex(i));
        pObj->onResetWnd();
        pObj->setTag(i);
        m_pNodeEquipContainer->addChild(pObj);
        pObj->setPosition(m_equipPos[i]);
        ++i;
    }
}


void MB_LayerToyShopMain::shuffle(int *pArray, unsigned int nLen)
{
    for (int i = nLen - 1; i >= 0; i--)
    {
        unsigned int j = rand() % (i + 1);
        unsigned int v = pArray[i];
        pArray[i] = pArray[j];
        pArray[j] = v;
    }
}

void MB_LayerToyShopMain::shuffleItemEquips()
{
//    MB_Message::sharedMB_Message()->showMessage("",15);
    static int lastshuffle = 0;
    if (MB_ClientSocket::getInstance()->getServerTime() - lastshuffle < 2)return;
    lastshuffle = MB_ClientSocket::getInstance()->getServerTime();
    
    float ft = .3;
    int pIndx[DRAW_EQUIP_MAX] = { 0, 1, 2, 3, 4, 5 };
    
    CCArray* pArr[DRAW_EQUIP_MAX] = { CCArray::create(), CCArray::create(), CCArray::create(), CCArray::create(), CCArray::create(), CCArray::create() };
    
    shuffle(pIndx, 6);
    for (int j = 0; j < DRAW_EQUIP_MAX; ++j)
    {
        pArr[j]->addObject(CCMoveTo::create(ft, ccp(28.4,167)));
        pArr[j]->addObject(CCMoveTo::create(ft, m_equipPos[pIndx[j]]));
    }
    
    for (int i = 0; i < 4; ++i)
    {
        shuffle(pIndx, DRAW_EQUIP_MAX);
        for (int j = 0; j < DRAW_EQUIP_MAX; ++j)
        {
            pArr[j]->addObject(CCMoveTo::create(ft, m_equipPos[pIndx[j]]));
        }
    }
    
    for (int j = 0; j < DRAW_EQUIP_MAX; ++j)
    {
        pArr[j]->addObject(CCMoveTo::create(ft, m_equipPos[j]));
    }
    
    MB_DrawEquip* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH_4TYPE(m_pItemEquipGet, MB_DrawEquip*, pObj)
    {
        pObj->runAction(CCSequence::create(pArr[i]));
        ++i;
    }
    this->runAction(CCSequence::create(CCDelayTime::create(ft * 8), CCCallFunc::create(this, callfunc_selector(MB_LayerToyShopMain::shuffleItemEquipsComplete)), NULL));
}

void MB_LayerToyShopMain::shuffleItemEquipsComplete()
{
    MB_Message::sharedMB_Message()->removeALLMessage();
}



///////////////////////////
////////抽  精  灵//////////
///////////////////////////


void MB_LayerToyShopMain::goCharge(CCObject*)
{
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if (MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionPayShop, &pInterface))
    {
        pInterface->onEntryClicked(this);
        CCDirector::sharedDirector()->getRunningScene()->removeChild(m_pNodeReward);
    }
}

void MB_LayerToyShopMain::onOnceAgain(CCObject*)
{
    int32_t shopid = 0;
    if (check(m_nLastTag, shopid))
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_ShopMgr::getInstance()->sendbox_shop(shopid, m_nLastTag);
        showShielding();
    }
}
void MB_LayerToyShopMain::onCommit(CCObject*)
{
    isReCreate = true;
}

bool MB_LayerToyShopMain::check(int tag, int32_t& shopID)
{
    CCObject* pObj = MB_ShopMgr::getInstance()->getShopBoxTemplete()->objectAtIndex(0);
    MB_ShopBoxTemplete* pBoxTemplete = dynamic_cast<MB_ShopBoxTemplete*>(pObj);
    if (pBoxTemplete)
    {
        int nNeed = 0;
        
        m_bUseItemCall = (tag == 0);
        if (tag == 1)
        {
            nNeed = pBoxTemplete->getCost1();
        }
        else if (tag == 2)
        {
            nNeed = pBoxTemplete->getCost10();
        }
        if (tag != 0)
        {
            if (nNeed > MB_RoleData::getInstance()->getGold() + MB_RoleData::getInstance()->getGoldBoune())
            {
                MB_ResWindow* pWnd = MB_Message::createMessageBox2("提示", "您的宝石已不足，是否前往充值", "前往", "取消", this, menu_selector(MB_LayerToyShopMain::goCharge), NULL);
                CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_OUTSHOW);
                return false;
            }
        }
        shopID = pBoxTemplete->getID();
        return true;
    }
    return false;
}
void MB_LayerToyShopMain::showShielding()
{
    if (m_pShielding == NULL)
    {
        m_pShielding = NSGameHelper::createDisableTouchLayer();
        CCDirector::sharedDirector()->getRunningScene()->addChild(m_pShielding);
    }
}
void MB_LayerToyShopMain::hideShielding()
{
    if (m_pShielding != NULL)
    {
        m_pShielding->removeFromParent();
        m_pShielding = NULL;
    }
}

void MB_LayerToyShopMain::showRewardCard()
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (m_pNodeReward&&!m_pNodeReward->getParent())
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(m_pNodeReward,Z_ORDER_OUTSHOW);
        CC_SAFE_RELEASE(m_pNodeReward);
    }
}

void MB_LayerToyShopMain::recv_box_shop(MB_MsgBuffer* recvPacket)
{
    uint8_t result = 0;
    
    if (recvPacket->readU8(&result))
    {
        if (result == 1)//成功
        {
            MB_Audio::getInstance()->playEffect(GET_BACKGROUND(kmBackGround_GetOnePet).c_str());
//            CC_SAFE_RELEASE_NULL(m_pNodeReward);
            
            MB_ParsingReward* pRward = MB_ParsingReward::create(recvPacket);
            CCArray* pArray = pRward->getRewardArray();
            if (pArray->count() == 1)
            {
                if (!m_bUseItemCall)
                {
                    MB_RoleData::getInstance()->setChouKaTimes(MB_RoleData::getInstance()->getChouKaTimes() + 1);
                }
                
                RewardTempleteValue* value = dynamic_cast<RewardTempleteValue*>(pArray->objectAtIndex(0));
                if (value != NULL)
                {
                    if (!isReCreate&&m_pNodeReward) {
                        ((MB_LayerRewardOne*)m_pNodeReward)->initPetAgain(value->getType(), value->getValueID(), value->getNumber());
                    }else{
                        MB_LayerRewardOne* layerOne = MB_LayerRewardOne::createPet(value->getType(), value->getValueID(), value->getNumber());
                        layerOne->setShareType(kShareTypeShopBox);
                        layerOne->setTarget(this,menu_selector(MB_LayerToyShopMain::onCommit), menu_selector(MB_LayerToyShopMain::onOnceAgain));
                        m_pNodeReward = layerOne;
                        CC_SAFE_RETAIN(m_pNodeReward);
                    }
                }
            }
            else if (pArray->count() > 1)
            {
                MB_RoleData::getInstance()->setChouKaTimes(MB_RoleData::getInstance()->getChouKaTimes() + 10);
                if (!isReCreate&&m_pNodeReward) {
                    ((MB_LayerRewardOne*)m_pNodeReward)->initTenAgain(pArray, kRewardValueTypePet);
                }else{
                    MB_LayerRewardOne* layer = MB_LayerRewardOne::createTen(pArray, kRewardValueTypePet);
                    layer->setTarget(this, menu_selector(MB_LayerToyShopMain::onCommit), menu_selector(MB_LayerToyShopMain::onOnceAgain));
                    m_pNodeReward = layer;
                    CC_SAFE_RETAIN(m_pNodeReward);
                }
            }
            isReCreate = false;
            //消耗
            if (m_bUseItemCall)
            {
                CCObject* pObj = MB_ShopMgr::getInstance()->getShopBoxTemplete()->objectAtIndex(0);
                MB_ShopBoxTemplete* pBoxTemplete = dynamic_cast<MB_ShopBoxTemplete*>(pObj);
            }
            this->onResetWnd();
            
            showRewardCard();
            hideShielding();
        }
        //失败,道具不足
        else if (result == 2)
        {
            MB_Message::sharedMB_Message()->showMessage("召唤失败, 宝石不足.");
            hideShielding();
        }
        else if (result == 3) //失败,未知原因
        {
            MB_Message::sharedMB_Message()->showMessage("扭蛋失败, 精灵球不足.");
            hideShielding();
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("召唤失败.");
            hideShielding();
        }
    }
}

void MB_LayerToyShopMain::onCallElfClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    CCNode* pTemp = dynamic_cast<CCNode*>(pSender);
    if (pTemp)
    {
        int tag = pTemp->getTag();
        
        int32_t shopid = 0;
        if (check(tag, shopid))
        {
            MB_Message::sharedMB_Message()->showMessage("",5);
            m_nLastTag = tag;
            MB_ShopMgr::getInstance()->sendbox_shop(shopid, tag);
            showShielding();
        }
    }
}
