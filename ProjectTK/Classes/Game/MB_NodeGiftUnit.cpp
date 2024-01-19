//
//  MB_NodeGiftUnit.cpp
//  ProjectMB
//
//  Create by chk on 17/12/2014.
//
//
#include "MB_NodeGiftUnit.h"
#include "MB_FunctionModule.h"
#include "MB_LayerMainGift1.h"
#include "MB_NodeItemBook.h"
#include "MB_LayerItemDetail.h"
MB_NodeGiftUnit* MB_NodeGiftUnit::create(MB_DailyRewrd* pData)
{
    MB_NodeGiftUnit* pNode = new MB_NodeGiftUnit;
    if (pNode)
    {
        pNode->m_pData = pData;
        if(pNode->init())
        {
            pNode->autorelease();
            return pNode;
        }
        CC_SAFE_RELEASE_NULL(pNode);
        return NULL;
    }
    
    CC_SAFE_RELEASE_NULL(pNode);
    return NULL;
}

static CCSize gUnitSize = CCSizeZero;
CCSize MB_NodeGiftUnit::getUnitSize()
{
    if(gUnitSize.width == 0 || gUnitSize.height == 0)
    {
        MB_NodeGiftUnit* pNode = MB_NodeGiftUnit::create(NULL);
        if(pNode)gUnitSize = pNode->size->getContentSize();
    }
    return gUnitSize;
}

MB_NodeGiftUnit::MB_NodeGiftUnit()
{
    m_pState = NULL;
    size	 = NULL;
    m_pLabelNeedValue	 = NULL;
    m_pBtGive	 = NULL;
    m_pData = NULL;
    m_pNodePos = NULL;
}
MB_NodeGiftUnit::~MB_NodeGiftUnit()
{
    CC_SAFE_RELEASE_NULL(m_pState);
    CC_SAFE_RELEASE_NULL(size);
    CC_SAFE_RELEASE_NULL(m_pLabelNeedValue);
    CC_SAFE_RELEASE_NULL(m_pBtGive);
    CC_SAFE_RELEASE_NULL(m_pNodePos);
}

bool MB_NodeGiftUnit::init()
{
    CCNode* pNode = NULL;
    if(m_pData)
    {
        //1在线时长礼包，2等级礼包，3连续登陆礼包
        const char* szccbi[] = {"","res/gift_node_time.ccbi","res/gift_node_lvup.ccbi","res/gift_node_login_goon.ccbi"};
        pNode = loadResource(szccbi[m_pData->getType()]);
    }
    else
    {
        pNode = loadResource("res/gift_node_login_goon.ccbi");
    }
    
    if(pNode)
    {
        addChild(pNode);
        onResetWnd();
        
        return true;
    }
    return false;
}

void MB_NodeGiftUnit::onResetWnd()
{
    if (m_pData)
	{
        NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtGive, "fonts/anniudanzi.fnt");
        m_pBtGive->setLabelAnchorPoint(ccp(0.5f,0.65f));
        //特殊处理 连续登陆
        if(eGiftMLogin == m_pData->getType())
        {
            if(m_pData->getIsGet())
            {
                m_pBtGive->setVisible(false);
                m_pState->setVisible(true);
//                NSGameHelper::setControlButtonTitleAllState(m_pBtGive,"已领取");
//                NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtGive, "fonts/anniudanziGray.fnt");
            }
            else
            {
                if(m_pData->getNeedValue()>m_pData->getNowValue())
                {
                    m_pBtGive->setVisible(false);
                    m_pState->setVisible(false);
//                    NSGameHelper::setControlButtonTitleAllState(m_pBtGive,"不可领取");
//                    NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtGive, "fonts/anniudanziGray.fnt");
                }
                else if(m_pData->getNeedValue() == m_pData->getNowValue())
                {
//                    NSGameHelper::setControlButtonTitleAllState(m_pBtGive,"领取奖励");
                }
                else
                {
                    m_pBtGive->setVisible(false);
                    m_pState->setVisible(true);
//                    NSGameHelper::setControlButtonTitleAllState(m_pBtGive,"已领取");
//                    NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtGive, "fonts/anniudanziGray.fnt");
                }
            }
        }
        else
        {
            if(m_pData->getIsGet())
            {
                m_pBtGive->setVisible(false);
                m_pState->setVisible(true);
                //                NSGameHelper::setControlButtonTitleAllState(m_pBtGive,"已领取");
                //                NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtGive, "fonts/anniudanziGray.fnt");}
            }
            else if (!m_pData->getEnable())
            {
                m_pBtGive->setVisible(false);
                m_pState->setVisible(false);
            }
        }
        addItem(m_pData->getMailRewards()->converIDNUM2RewardTempleteValue());
        char buff[100] = {0};
        switch (m_pData->getType())
        {
            case eGiftTime:
            {
                m_pLabelNeedValue->setString(NSGameHelper::convertDeltaTime2String(m_pData->getNeedValue()).c_str());
                m_pBtGive->setEnabled(m_pData->getEnable());
            }
                break;
            case eGiftMLogin:
            {
                sprintf(buff, "%d天",m_pData->getNeedValue());
                m_pLabelNeedValue->setString(buff);
                m_pBtGive->setEnabled(m_pData->getEnable());
            }
                break;
            case eGiftLevel:
            {
                sprintf(buff, "%d级",m_pData->getNeedValue());
                m_pLabelNeedValue->setString(buff);
                m_pBtGive->setEnabled(m_pData->getEnable());
            }
                break;
            default:
                break;
        }
    }
}
void MB_NodeGiftUnit::onClicked(MB_NodeItem* pItem)
{
    MB_ResWindow* layerDetail = MB_LayerItemDetail::createByType(pItem->getItemType());
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->addChild(layerDetail,Z_ORDER_Detail);
    }else{
        CCDirector::sharedDirector()->getRunningScene()->addChild(layerDetail, Z_ORDER_OUTSHOW);
    }
}

void MB_NodeGiftUnit::addItem(CCArray* pReward)
{
    RewardTempleteValue* pObj = NULL;
    int indxe = 0;
    CCSize size = CCSizeMake(95, 95);
    if(pReward)
    {
        CCARRAY_FOREACH_4TYPE(pReward,RewardTempleteValue*,pObj)
        {
            if(pObj->getType() == 1)
            {
                MB_NodeItem* pItem = MB_NodeItem::create(pObj->getValueID());
                pItem->showNameCount(false);
                pItem->setNum(pObj->getNumber());
                pItem->showNameCount(true);
                pItem->setDelegate(this);
                m_pNodePos->addChild(pItem);
                pItem->setScale(0.78f);
                pItem->setPosition(indxe * size.width + size.width/2,8);
            }
            else
            {
                MB_NodePet * pPet = MB_NodePet::create(pObj->getValueID());
                pPet->showLevel(false);
                pPet->showName(false);
                m_pNodePos->addChild(pPet);
                pPet->showName(true);
                pPet->setScale(0.78f);
                pPet->setPosition(indxe * size.width + size.width/2,0);
            }
            ++indxe;
        }
    }
}
bool MB_NodeGiftUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size",CCNode*,size);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePos",CCNode*,m_pNodePos);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelNeedValue",CCLabelTTF*,m_pLabelNeedValue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGive",CCControlButton*,m_pBtGive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pState",CCNode*,m_pState);
    
    return false;
}
SEL_MenuHandler MB_NodeGiftUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}
SEL_CCControlHandler MB_NodeGiftUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_NodeGiftUnit::onCommitClicked);
    return NULL;
}
void MB_NodeGiftUnit::onCommitClicked(CCObject* pSender)
{
    if (m_pData->getType()==1) {
        MB_TARGET_PARENT(MB_LayerMainGift1, ptr)
        {
            ptr->cs_daily_reward_get(m_pData->getType(), m_pData->getNeedValue());
        }
    }
    else if (m_pData->getType()==2){
        MB_TARGET_PARENT(MB_LayerMainGift2, ptr)
        {
            ptr->cs_daily_reward_get(m_pData->getType(), m_pData->getNeedValue());
        }
    }else if (m_pData->getType()==3){
        MB_TARGET_PARENT(MB_LayerMainGift3, ptr)
        {
            ptr->cs_daily_reward_get(m_pData->getType(), m_pData->getNeedValue());
        }
    }
}
