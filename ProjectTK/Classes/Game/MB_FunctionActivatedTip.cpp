//
//  MB_FunctionActivatedTip.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-31.
//
//

#include "MB_FunctionActivatedTip.h"
//#include "MB_NodeDowninfo.h"
#include "MB_FunctionModule.h"
using namespace NSGameFunction;

MB_FunctionActivatedTip::MB_FunctionActivatedTip()
{
    m_pInterface = NULL;
}

MB_FunctionActivatedTip::~MB_FunctionActivatedTip()
{
    m_pInterface = NULL;
}

MB_FunctionActivatedTip* MB_FunctionActivatedTip::create(const char* pFile)
{
    MB_FunctionActivatedTip* pInstance = new MB_FunctionActivatedTip;
    if (pInstance && pInstance->init(pFile))
    {
        pInstance->autorelease();
        return pInstance;
    }
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}

bool MB_FunctionActivatedTip::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    return false;
}

bool MB_FunctionActivatedTip::init(const char* pFile)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(pFile, this);
    
    if (pNode)
    {
//        CCNode* pNode1 = NSGameHelper::createDisableTouchLayer12();
//        addChild(pNode1);
        addChild(pNode);
        CC_SAFE_RELEASE(pCCBReader);
        return true;
    }
    
    CC_SAFE_RELEASE(pCCBReader);
    
    return false;
}

SEL_MenuHandler MB_FunctionActivatedTip::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGoIndexClick", MB_FunctionActivatedTip::onGoFunctionClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_FunctionActivatedTip::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_FunctionActivatedTip::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

void MB_FunctionActivatedTip::onGoFunctionClicked(CCObject *)
{
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd",false);
    TutorialTriggerComplete
    if(MB_TutorialMgr::getInstance()->getRoleLevelUpGoHome())
    {
        MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    }
    else
    {
        if (m_pInterface)
        {
            m_pInterface->onEnterThisFunction(this);
        }
    }
    removeFromParent();
}

void MB_FunctionActivatedTip::onCloseClicked(CCObject *)
{
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerChapterWnd",false);

    removeFromParent();
}

void MB_FunctionActivatedTip::setFunctionInterface(CCFunctionInterface* pInterface)
{
    m_pInterface = pInterface;
}