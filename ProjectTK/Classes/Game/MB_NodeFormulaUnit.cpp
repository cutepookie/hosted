//
//  MB_NodeFormulaUnit.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#include "MB_NodeFormulaUnit.h"
#include "MB_LayerComposeMain.h"

MB_NodeFormulaUnit::MB_NodeFormulaUnit()
{
    m_pComplateNode = NULL;
    m_pItemName = NULL;
    m_pItemIcon = NULL;
    m_pBgFrame = NULL;
    m_pSpriteDebris = NULL;
}

MB_NodeFormulaUnit::~MB_NodeFormulaUnit()
{
    CC_SAFE_RELEASE_NULL(m_pComplateNode);
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pBgFrame);
    CC_SAFE_RELEASE_NULL(m_pSpriteDebris);
    
}

MB_NodeFormulaUnit* MB_NodeFormulaUnit::create(uint16_t nComposeID)
{
    MB_NodeFormulaUnit* pInstance = new MB_NodeFormulaUnit;
    if (pInstance && pInstance->init(nComposeID))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}


bool MB_NodeFormulaUnit::init(uint16_t nComposeID)
{
    MB_ComposeTemplate* pTemplate = MB_ComposeMgr::getInstance()->getComposeTemplateByID(nComposeID);
    if (pTemplate == NULL)
    {
        CCLog("[Error]:Can not find the compose id %d",nComposeID);
        return false;
    }
    m_nType = pTemplate->getComposeType();
    m_nComposeID = nComposeID;

    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_card2.ccbi", this);
    if (pNode)
    {
        addChild(pNode);
    }

    CC_SAFE_RELEASE_NULL(pCCBReader);

    setTag(m_nComposeID);

    onResetWnd();

    return true;
}

void MB_NodeFormulaUnit::onResetWnd()
{
    bool ret = false;
    if (m_nType == 1)
    {
        ret = NSGameHelper::getPetMaterialComplateStatus(m_nComposeID);
    }
    else if(m_nType == 2)
    {
        ret = NSGameHelper::getItemMaterialComplateStatus(m_nComposeID);
    }

    setComplateStatus(ret);

    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nComposeID);

    if (pTemplate)
    {
        m_pItemName->setString(pTemplate->getItemName());
//        CCNodeRGBA pDest;
//        NSGameHelper::setQualityColor(&pDest,pTemplate->getItemStar());
//        m_pItemName->setColor(pDest.getColor());
        NSGameHelper::setSpriteFrame(m_pItemIcon, pTemplate->getItemIcon());
        NSGameHelper::setHeadFrame(m_pBgFrame, pTemplate->getItemStar(), ITEM_HEADFRAME,0);
        NSGameHelper::creatMaskSprite(m_pItemIcon);
    }
    
    m_pSpriteDebris->setVisible(pTemplate->getIsDebris());
}

// turn to compose gui
void MB_NodeFormulaUnit::onFormulaClicked(CCObject* pObject)
{
    MB_TARGET_PARENT(MB_LayerComposeMain, ptr);
    if (ptr)
    {
        ptr->onFormulaClicked(this);
    }
}

bool MB_NodeFormulaUnit::onAssignCCBMemberVariable(CCObject* pTarget,
                                                   const char* pMemberVariableName,
                                                   CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "complate", CCNode*, m_pComplateNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bgframe", CCSprite*, m_pBgFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "IconFrame", CCSprite*, m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", CCLabelTTF*, m_pItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDebris", CCNode*, m_pSpriteDebris);
    if(strcmp("scroller", pMemberVariableName) == 0)
    {
        ((CCMenu *)pNode)->setSwallowsTouches(false);
    }
    return false;
}

SEL_MenuHandler MB_NodeFormulaUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget,
                                                                   const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFormulaClicked", MB_NodeFormulaUnit::onFormulaClicked);
    return NULL;
}

SEL_CCControlHandler MB_NodeFormulaUnit::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                                       const char* pSelectorName)
{
    return NULL;
}

void MB_NodeFormulaUnit::setComplateStatus(bool bStatus)
{
    m_pComplateNode->setVisible(bStatus);
}
