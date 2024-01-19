//
//  MB_NodeRewardCard.cpp
//  ProjectPM
//
//  Create by WenYong on 23/7/2014.
//
//
#include "MB_NodeRewardCard.h"
#include "MB_ItemData.h"
#include "MB_NodeItemIcon.h"
#include "MB_NodeTanChuangUnit.h"
MB_NodeRewardCard::MB_NodeRewardCard()
{
    m_pNodeSize	 = NULL;
    m_pNodeItem	 = NULL;
    m_pNodePet	 = NULL;
    m_nTypeID = 0;
    m_nType = 0;
}
MB_NodeRewardCard::~MB_NodeRewardCard()
{
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pNodeItem);
    CC_SAFE_RELEASE_NULL(m_pNodePet);
}
bool MB_NodeRewardCard::init()
{
    CCNode* pNode = loadResource("res/card_node_rewardcard.ccbi");
    if(pNode)
	{
		addChild(pNode);
        setContentSize(m_pNodeSize->getContentSize());
		return true;
	}
	return false;
}
CCSize& MB_NodeRewardCard::getNodeSize()
{
    static CCSize sz = CCSize(-1,-1);
    
    if (sz.width < 0.0)
    {
        MB_NodeRewardCard* pCard = new MB_NodeRewardCard;
        if (pCard->loadResource("res/card_node_rewardcard.ccbi"))
        {
            sz = pCard->m_pNodeSize->getContentSize();
        }
    }
    return sz;
}
void MB_NodeRewardCard::onResetWnd()
{
    if (m_nType == kRewardValueTypePet)
    {
        updatePet();
    }
    else if(m_nType == kRewardValueTypeItem)
    {
        updateItem();
    }
}

void MB_NodeRewardCard::updateItem()
{
    MB_ItemTemplate* pItem = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nTypeID);
    if (pItem)
    {
        CCNode* pNode = MB_NodeTanChuangUnit::create(m_nTypeID,m_nRank,m_nLevel,true);
        if(pNode)
        {
            m_pNodeItem->removeAllChildren();
            m_pNodeItem->addChild(pNode);
        }
    }
}
void MB_NodeRewardCard::updatePet()
{
    MB_PetTemplate* pPet = MB_PetMgr::getInstance()->getPetTemplateByID(m_nTypeID);
    if (pPet)
    {
        CCNode* pNode = MB_NodeTanChuangUnit::create(pPet->getPetTypeID(), m_nRank,m_nLevel,false);
        
        if (pNode)
        {
            m_pNodePet->removeAllChildren();
            m_pNodePet->addChild(pNode);
        }
    }
}
bool MB_NodeRewardCard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeSize",CCNode*,m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeItem",CCNode*,m_pNodeItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodePet",CCNode*,m_pNodePet);
	return false;
}
void MB_NodeRewardCard::setDetail(uint16_t kType,uint16_t nTypeID,uint16_t nRank,uint32_t nLevel)
{
    m_nTypeID = nTypeID;
    m_nType = kType;
    m_nRank = nRank;
    m_nLevel = nLevel;
    
    onResetWnd();
}

MB_NodeRewardCard* MB_NodeRewardCard::create(MB_RewardDataDetail* pData)
{
    if (pData == NULL)
    {
        return NULL;
    }
    
    MB_NodeRewardCard* pInstance = new MB_NodeRewardCard;
    if (pInstance && pInstance->init())
    {
        pInstance->setDetail(pData->m_nType, pData->m_nTypeID,pData->m_nRank,pData->m_nLevel);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return NULL;
}
