//
//  MB_FunctionArenaTip.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-4-29.
//


#include "MB_FunctionArenaTip.h"
#include "MB_FunctionModule.h"
//#include "MB_NodeDowninfo.h"
using namespace NSGameFunction;

MB_FunctionArenaTip::MB_FunctionArenaTip()
{
    m_pInterface = NULL;
}

MB_FunctionArenaTip::~MB_FunctionArenaTip()
{
    m_pInterface = NULL;
}

MB_FunctionArenaTip* MB_FunctionArenaTip::create(const char* pFile)
{
    MB_FunctionArenaTip* pInstance = new MB_FunctionArenaTip;
    if (pInstance && pInstance->init(pFile))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}

bool MB_FunctionArenaTip::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    return false;
}

bool MB_FunctionArenaTip::init(const char* pFile)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pFile, this);
    
    if (pNode)
    {
        CCNode* pNode1 = NSGameHelper::createDisableTouchLayer();
        addChild(pNode1);
        addChild(pNode);
        CC_SAFE_RELEASE(pCCBReader);
        return true;
    }
    
    CC_SAFE_RELEASE(pCCBReader);
    
    return false;
}

SEL_MenuHandler MB_FunctionArenaTip::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGoIndexClick", MB_FunctionArenaTip::onGoFunctionClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_FunctionArenaTip::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_FunctionArenaTip::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

void MB_FunctionArenaTip::onGoFunctionClicked(CCObject *)
{
    TutorialTriggerComplete
    NSGameFunction::CCFunctionInterface::goFunctionHome();
    
    //    if (m_pInterface)
    //    {
    //        m_pInterface->onEnterThisFunction(this);
    //    }
    popWindow();
}

void MB_FunctionArenaTip::onCloseClicked(CCObject *)
{
//    if (g_pDodeDowninfo)
//    {
//        // un check
//        g_pDodeDowninfo->goMessageBox(this);
//    }
    popWindow();
}

void MB_FunctionArenaTip::setFunctionInterface(CCFunctionInterface* pInterface)
{
    m_pInterface = pInterface;
}