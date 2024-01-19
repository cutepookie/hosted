//
//  MB_NodeRewardUnit.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-8-29.
//
//

#include "MB_NodeRewardUnit.h"

MB_NodeRewardUnit::MB_NodeRewardUnit()
{
    m_nNum = 1;
    m_nTid = 0;
    m_pItemName = NULL;
    m_pItemIcon = NULL;
    m_pItemFrame = NULL;
}

MB_NodeRewardUnit::~MB_NodeRewardUnit()
{
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pItemFrame);
}

MB_NodeRewardUnit* MB_NodeRewardUnit::create(uint16_t nTID,uint16_t num)
{
    MB_NodeRewardUnit* pInstance = new MB_NodeRewardUnit;
    if (pInstance && pInstance->init(nTID,num))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}


bool MB_NodeRewardUnit::init(uint16_t nTID,uint16_t num)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/suit_node_icon.ccbi", this);
    if (pNode)
    {
        addChild(pNode);
    }
    
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    m_nTid = nTID;
    m_nNum = num;
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nTid);
    if (pTemplate == NULL)
    {
        return false;
    }
    onResetWnd();
    
    return true;
}

void MB_NodeRewardUnit::onResetWnd()
{
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(m_nTid);
    if (pTemplate)
    {
        if (m_nNum > 1)
        {
            char str[32] = {};
            sprintf(str,"%s X%d",pTemplate->getItemName(),m_nNum);
            m_pItemName->setString(str);
        }
        else
        {
            m_pItemName->setString(pTemplate->getItemName());
        }

        NSGameHelper::setSpriteFrame(m_pItemIcon, pTemplate->getItemIcon());
        NSGameHelper::creatMaskSprite(m_pItemIcon);
        NSGameHelper::setHeadFrame(m_pItemFrame, pTemplate->getItemStar(), ITEM_HEADFRAME,0);
        
    }
}


bool MB_NodeRewardUnit::onAssignCCBMemberVariable(CCObject* pTarget,
                                                   const char* pMemberVariableName,
                                                   CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemFrame", CCSprite*, m_pItemFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemIcon", CCSprite*, m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemName", CCLabelTTF*, m_pItemName);
    if(strcmp("scroller", pMemberVariableName) == 0)
    {
        ((CCMenu *)pNode)->setSwallowsTouches(false);
    }
    return false;
}

SEL_MenuHandler MB_NodeRewardUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget,
                                                                   const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_NodeRewardUnit::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                                       const char* pSelectorName)
{
    return NULL;
}

