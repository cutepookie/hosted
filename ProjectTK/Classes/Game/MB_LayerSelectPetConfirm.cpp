//
//  MB_LayerSelectPetConfirm.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-25.
//
//

#include "MB_LayerSelectPetConfirm.h"
#include "MB_LayerSelectMonster.h"
#include "Game.h"

MB_LayerSelectPetConfirm::MB_LayerSelectPetConfirm():m_nSelectIndex(0)
{
    
}

MB_LayerSelectPetConfirm* MB_LayerSelectPetConfirm::create(uint16_t index)
{
    MB_LayerSelectPetConfirm* pInstance = new MB_LayerSelectPetConfirm;
    if (pInstance && pInstance->init(index))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}

bool MB_LayerSelectPetConfirm::init(uint16_t nSelectIndex)
{
    if (nSelectIndex > 2)
    {
        return false;
    }
    
    const char* res[] = \
    {
        "res/gui_role_petconfirm1.ccbi",
        "res/gui_role_petconfirm2.ccbi",
        "res/gui_role_petconfirm3.ccbi"
    };
    
    m_nSelectIndex = nSelectIndex;
    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(res[m_nSelectIndex], this);

    if (pNode)
    {
        CCSize win_sz = CCDirector::sharedDirector()->getWinSize();
        CCLayerColor* pLayer = CCLayerColor::create(ccc4(68, 68, 68, 68), win_sz.width, win_sz.height);
        pLayer->addChild(NSGameHelper::createDisableTouchLayer());
        addChild(pLayer);
        addChild(pNode);
    }
    
    CC_SAFE_RELEASE(pCCBReader);
    
    return true;

}

SEL_MenuHandler MB_LayerSelectPetConfirm::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


SEL_CCControlHandler MB_LayerSelectPetConfirm::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onConfirmClicked", MB_LayerSelectPetConfirm::onConfirmClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancelClicked", MB_LayerSelectPetConfirm::onCancelClicked);
    return NULL;
}

void MB_LayerSelectPetConfirm::onCancelClicked(CCObject* pSender)
{
    popWindow();
}

void MB_LayerSelectPetConfirm::goGeneralStep(uint16_t index)
{
    // go general step
    MB_TARGET_PARENT(MB_LayerSelectMonster, ptr);
    if (ptr)
    {
        ptr->onMonsterSelectConfirmed(index);
    }
}

void MB_LayerSelectPetConfirm::onConfirmClicked(CCObject* pSender)
{
    goGeneralStep(m_nSelectIndex);
    popWindow();
}