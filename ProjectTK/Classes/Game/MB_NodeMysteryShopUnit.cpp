//
//  MB_NodeMysteryShopUnit.cpp
//  ProjectMB
//
//  Created by chenhongkun on 14-9-12.
//
//

#include "MB_NodeMysteryShopUnit.h"
#include "MB_petData.h"
#include "MB_ItemData.h"
#include "MB_ShopMystery.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerPetDetail.h"
MB_NodeMysteryShopUnit::MB_NodeMysteryShopUnit()
{
    m_pMB_PetTemplate = NULL;
    m_pMB_ItemTemplate = NULL;
    m_pShopGoodsItem = NULL;
}

MB_NodeMysteryShopUnit* MB_NodeMysteryShopUnit::create(MB_ShopGoodsItem* goodsItem,EType type,bool bTutorial)
{
    MB_NodeMysteryShopUnit* layer = new MB_NodeMysteryShopUnit();
    if(layer)
    {
        layer->m_pShopGoodsItem = goodsItem;
        layer->m_nType = type;
        layer->m_bTutorial = bTutorial;
        layer->init();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}

bool MB_NodeMysteryShopUnit::init()
{
    MB_NodeRefreshShopUnit::init();
    
    if (m_nType == kItem)
    {
        MB_ItemMgr* pItemMgr = MB_ItemMgr::getInstance();
        MB_ShopGoodsItem* pItem = MB_ShopMgr::getInstance()->getShopGoodsItemByID(m_pShopGoodsItem->getGoodsID());
        MB_ShopGoodsReward* pReward = dynamic_cast<MB_ShopGoodsReward*>(pItem->getRewardArray()->objectAtIndex(0));
        m_pMB_ItemTemplate = pItemMgr->getItemTemplateByID(pReward->getRewardValue());
    }
    else
    {
        MB_PetMgr* pPetMgr = MB_PetMgr::getInstance();
        MB_ShopGoodsItem* pItem = MB_ShopMgr::getInstance()->getShopGoodsItemByID(m_pShopGoodsItem->getGoodsID());
        MB_ShopGoodsReward* pReward = dynamic_cast<MB_ShopGoodsReward*>(pItem->getRewardArray()->objectAtIndex(0));
        m_pMB_PetTemplate =  pPetMgr->getPetTemplateByID(pReward->getRewardValue());
    }
    
    onResetWnd();
    return true;
}

void MB_NodeMysteryShopUnit::onResetWnd()
{
    if(m_nType == kItem)
    {
        if(m_pMB_ItemTemplate == NULL)return;
        NSGameHelper::setItemIconDetailByTid(m_pMB_ItemTemplate->getItemID(),0,NULL,m_pNameTtf,NULL,false);
        MB_NodeItem* nodeIcon = MB_NodeItem::create(m_pMB_ItemTemplate->getItemID(),kDAOJU);
        nodeIcon->showNameCount(false);
        m_pItemIcon->addChild(nodeIcon);
    }
    else
    {
        if(m_pMB_PetTemplate == NULL)return;
        NSGameHelper::setMonsterIconDetailByTid(m_pMB_PetTemplate->getPetTypeID(),0,NULL,m_pNameTtf,NULL,true);
        MB_NodePet* nodeIcon = MB_NodePet::create(m_pMB_PetTemplate->getPetTypeID(),1);
        nodeIcon->showName(false);
        m_pItemIcon->addChild(nodeIcon);
    }
    
    //单价
    char buff[20] = {0};
    sprintf(buff, "%d",m_pShopGoodsItem->getPrice());
    m_pCostTtf->setString(buff);
    
    //货币图标
    MB_ItemMgr::getInstance()->setSpriteFrame(NULL,GET_CONFIG_VALUE("currency.xml",m_pShopGoodsItem->getCoinType(),"Icon").c_str());
    
    //购买按钮状态
    bool b = m_pShopGoodsItem->getBuyNum() > m_pShopGoodsItem->getRealBuyNum();
    m_pButBtn->setVisible(b);
    m_pBuyedBtn->setVisible(!b);
}

void MB_NodeMysteryShopUnit::onDetailClick(CCObject* pSender)
{
    if(m_nType == kItem)
    {
        MB_ResWindow* layer= MB_LayerItemDetail::createByType(m_pMB_ItemTemplate->getItemID());
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(layer,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
        }
    }
    else
    {
        MB_PetData* pData = MB_PetMgr::createInstance(m_pMB_PetTemplate);
        MB_LayerPetDetail* layer= MB_LayerPetDetail::create(pData);
        layer->setAllBtnShowFalse();
        if(layer)CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
    }
}
void MB_NodeMysteryShopUnit::onBuyClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_ShopMystery, ptr)
    if(ptr)
    {
        ptr->sendshop_buy(m_pShopGoodsItem->getGoodsID(),m_pShopGoodsItem->getBuyNum(),m_pShopGoodsItem->getCoinType(),m_pShopGoodsItem->getPrice() * m_pShopGoodsItem->getBuyNum());
    }
    TutorialTriggerComplete
}
