//
//  MB_NodeRefreshShopUnit.cpp
//  ProjectMB
//
//  Create by chk on 5/9/2014.
//
//
#include "MB_NodeRefreshShopUnit.h"
#include "MB_RefreshShopProtocol.h"
#include "MB_ItemData.h"
#include "MB_LayerRefreshShop.h"
#include "MB_RefreshShopInterface.h"
#include "MB_LayerItemDetail.h"
#include "MB_FunctionMgr.h"
MB_NodeRefreshShopUnit::MB_NodeRefreshShopUnit()
{
    m_pNameTtf	 = NULL;
    m_pButBtn	 = NULL;
    m_pCostTtf	 = NULL;
    m_pItemIcon	 = NULL;
    m_pCellSize = NULL;
    m_pTreasure = NULL;
    m_pMask = NULL;
    m_bTutorial = false;
    m_pBuyedBtn = NULL;
}
MB_NodeRefreshShopUnit::~MB_NodeRefreshShopUnit()
{
    CC_SAFE_RELEASE_NULL(m_pBuyedBtn);
    CC_SAFE_RELEASE_NULL(m_pNameTtf);
    CC_SAFE_RELEASE_NULL(m_pButBtn);
    CC_SAFE_RELEASE_NULL(m_pCostTtf);
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pCellSize);
    CC_SAFE_RELEASE_NULL(m_pMask);
}

static CCSize g_UnitSize = CCSizeZero;
CCSize MB_NodeRefreshShopUnit::getUnitSize()
{
    if(g_UnitSize.width == 0 && g_UnitSize.height == 0)
    {
        MB_NodeRefreshShopUnit* unit = MB_NodeRefreshShopUnit::create(NULL);
        g_UnitSize = unit->m_pCellSize->getContentSize();
    }
    
    return g_UnitSize;
}
MB_NodeRefreshShopUnit* MB_NodeRefreshShopUnit::create(MB_Treasure* pTreasure)
{
    MB_NodeRefreshShopUnit* layer = new MB_NodeRefreshShopUnit();
    if(layer)
    {
        layer->m_pTreasure = pTreasure;
        layer->init();
        layer->autorelease();
        return layer;
    }
    CC_SAFE_RELEASE_NULL(layer);
    return NULL;
}
bool MB_NodeRefreshShopUnit::init()
{
    CCNode* pNode = loadResource("res/shop_node_unit.ccbi");
    if(pNode)
	{
		addChild(pNode);
        onResetWnd();

        NSGameHelper::changeParent(m_pButBtn, m_pCostTtf);
        m_pCostTtf->setPosition(ccp(47,-111)+ccp(139.0f/2,149));
        
		return true;
	}
	return false;
}
void MB_NodeRefreshShopUnit::onResetWnd()
{
    if(m_pTreasure == NULL)return;
    
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_pTreasure->getTID());
    if(pTemplate)NSGameHelper::setItemIconDetailByTid(pTemplate->getItemID(),0,NULL,m_pNameTtf,NULL,false);
    char buff[100] = {0};
    sprintf(buff,"%s*%d",m_pNameTtf->getString(),m_pTreasure->getNum());
    m_pNameTtf->setString(buff);
    
    NSGameFunction::CCFunctionInterface *pInterface = NULL;
    if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionRefreshShop ,&pInterface))
    {
        MB_RefreshShopInterface* pInterfaceTemp = dynamic_cast<MB_RefreshShopInterface*>(pInterface);
        if (pInterfaceTemp)
        {
            char buff[20] = {0};
            int value = m_pTreasure->getNum() * m_pTreasure->getCostVal() * pInterfaceTemp->getTreasureInfo()->getMul() * pInterfaceTemp->getTreasureInfo()->getDiscounts() / 10000.0f;
            sprintf(buff, "%d",value);
            m_pCostTtf->setString(buff);
        }
        else
        {
             m_pCostTtf->setString("错误");
        }
    }
    
    m_pButBtn->setVisible(!m_pTreasure->getIsBuy());
    m_pBuyedBtn->setVisible(m_pTreasure->getIsBuy());
}
bool MB_NodeRefreshShopUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(m_bTutorial)TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNameTtf",CCLabelTTF*,m_pNameTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pButBtn",CCControlButton*,m_pButBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pCostTtf",CCLabelBMFont*,m_pCostTtf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemIcon",CCNode*,m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCellSize", CCNode*, m_pCellSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMask", CCSprite*, m_pMask);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBuyedBtn", CCNode*, m_pBuyedBtn);
	return false;
}
SEL_MenuHandler MB_NodeRefreshShopUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_NodeRefreshShopUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBuyClicked",MB_NodeRefreshShopUnit::onBuyClicked);
	return NULL;
}
void MB_NodeRefreshShopUnit::onBuyClicked(CCObject* pSender)
{
    MB_TARGET_PARENT(MB_LayerRefreshShop, ptr)
    if(ptr)
    {
        ptr->sendshop_treasure_buy(m_pTreasure);
    }
    TutorialTriggerComplete
}
