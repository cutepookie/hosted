//
//  MB_LayerComposeRule.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-4-16.
//
//

#include "MB_LayerComposeRule.h"

#include "MB_FunctionModule.h"



MB_LayerComposeRule::MB_LayerComposeRule()
{
    m_bShowRoleInfoPanel = true;
}

MB_LayerComposeRule::~MB_LayerComposeRule()
{
}

MB_LayerComposeRule* MB_LayerComposeRule::create(int nType)
{
    MB_LayerComposeRule* pInstance = new MB_LayerComposeRule;
    if (pInstance && pInstance->init(nType))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

bool MB_LayerComposeRule::init(int nType)
{
    MB_ResWindow::init();
    
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    std::string ccbfile = "";
    if(nType == eRandomRule)
    {
        ccbfile = "res/compose_layer_rule.ccbi";
    }
    else
    {
        ccbfile = "res/gui_compose_rule.ccbi";
    }
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(ccbfile.c_str(), this);
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer12());
        addChild(pNode);
    }
    CC_SAFE_RELEASE_NULL(pCCBReader);
    onResetWnd();
    return true;
}

void MB_LayerComposeRule::onResetWnd()
{
    MB_ResWindow::onResetWnd();
}

bool MB_LayerComposeRule::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return false;
}

SEL_MenuHandler MB_LayerComposeRule::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClosedClicked", MB_LayerComposeRule::onClosedClicked);
    return NULL;
}

void MB_LayerComposeRule::onClosedClicked(CCObject*)
{
    popWindow();
}

SEL_CCControlHandler MB_LayerComposeRule::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}