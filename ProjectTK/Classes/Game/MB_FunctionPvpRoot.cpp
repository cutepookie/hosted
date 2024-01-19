//
//  MB_FunctionPvpRoot.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#include "MB_FunctionPvpRoot.h"
#include "MB_FunctionModule.h"

bool MB_FunctionPvpMain::initFunctions()
{
    CCFunctionInterface* pInterface = NULL;
    bool ret = false;
    MB_ResWindow* pWnd = NULL;
    
    ret = MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionArena, &pInterface);
    if (ret)
    {
        pWnd = pInterface->createEntryDialog();
        m_pNodes[0]->removeAllChildren();
        m_pNodes[0]->addChild(pWnd);
    }
    
    return true;

}

bool MB_FunctionPvpMain::init()
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/gui_main_command_2.ccbi", this);
    m_pAnimation = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pAnimation);
    CC_SAFE_RELEASE(pCCBReader);
    this->addChild(node);
    
    CCScrollView *scroller = CCScrollView::create(m_pCommandList->getContentSize());
    m_pCommandList->addChild(scroller);
    scroller->setDirection(kCCScrollViewDirectionHorizontal);
    scroller->setTouchPriority(TOUCHPROPERTY);
    
    pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    node = pCCBReader->readNodeGraphFromFile("res/obj_command_list_pvp.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    scroller->setContainer(node);
    node->setContentSize(m_pScrollsize->getContentSize());
    node->setPosition(ccp(0,0));
    
    setTouchEnabled(true);
    return initFunctions();
}