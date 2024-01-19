//
//  MB_FunctionPveRoot.cpp
//  ProjectPM
//
//  Created by WenYong on 14-3-26.
//
//

#include "MB_FunctionPveRoot.h"
#include "MB_FunctionModule.h"
#include "Game.h"

MB_FunctionPveMain::MB_FunctionPveMain()
{
    for (int i=0; i<8; ++i)
    {
        m_pNodes[i] = NULL;
    }
    m_pAnimation = NULL;
    m_pCommandList = NULL;
    m_pScrollsize = NULL;
}

MB_FunctionPveMain::~MB_FunctionPveMain()
{
    for (int i=0; i<8; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pNodes[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pAnimation);
    CC_SAFE_RELEASE_NULL(m_pCommandList);
    CC_SAFE_RELEASE_NULL(m_pScrollsize);
}



bool MB_FunctionPveMain::init()
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
    node = pCCBReader->readNodeGraphFromFile("res/obj_command_list_pve.ccbi", this);
    CC_SAFE_RELEASE(pCCBReader);
    scroller->setContainer(node);
    node->setContentSize(m_pScrollsize->getContentSize());
    node->setPosition(ccp(0,0));

    setTouchEnabled(true);
    return initFunctions();
}

bool MB_FunctionPveMain::initFunctions()
{
    CCFunctionInterface* pInterface = NULL;
    bool ret = false;
    MB_ResWindow* pWnd = NULL;
    
    ret = MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
    if (ret)
    {
        pWnd = pInterface->createEntryDialog();
        m_pNodes[0]->removeAllChildren();
        m_pNodes[0]->addChild(pWnd);
    }
//    ret = MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionRoom, &pInterface);
//    if (ret)
//    {
//        pWnd = pInterface->createEntryDialog();
//        m_pNodes[1]->removeAllChildren();
//        m_pNodes[1]->addChild(pWnd);
//    }
    return true;
}

void MB_FunctionPveMain::onResetWnd()
{
    MB_ResWindow* pChild = NULL;
    for (int i=0; i<8; ++i)
    {
        pChild = dynamic_cast<MB_ResWindow*>(m_pNodes[i]->getChildByTag(i));
        if (pChild)
        {
            pChild->onResetWnd();
        }
    }
}

bool MB_FunctionPveMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    char buf[10] = {};
    for (int i=0; i<8; ++i)
    {
        sprintf(buf, "%d", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buf, CCNode*, m_pNodes[i]);
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scrollsize", CCNode *,  m_pScrollsize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCommandList", CCNode *, m_pCommandList);
    return false;
}

void MB_FunctionPveMain::onOpen(){
    
    m_pAnimation->setAnimationCompletedCallback(NULL,NULL);
    m_pAnimation->runAnimationsForSequenceNamed("open");
    MB_Message::sharedMB_Message()->removeALLMessage();
}
void MB_FunctionPveMain::onClose(){
    
    m_pAnimation->setAnimationCompletedCallback(this, callfunc_selector(MB_FunctionPveMain::onCloseComplete));
    m_pAnimation->runAnimationsForSequenceNamed("close");
    MB_Message::sharedMB_Message()->showMessage(10);
}
void MB_FunctionPveMain::onCloseComplete(){
    
    MB_Message::sharedMB_Message()->removeALLMessage();
    this->removeFromParent();
    //m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
}
void MB_FunctionPveMain::onExit(){
    
    CCLayer::onExit();
    m_pAnimation->setAnimationCompletedCallback(NULL, NULL);
}

bool MB_FunctionPveMain::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint point =  pTouch->getLocation();
    point =  m_pScrollsize->convertToNodeSpace(point);
    if(point.x < 0 || point.x > m_pScrollsize->getContentSize().width  ||  point.y > m_pScrollsize->getContentSize().height){
        
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene != NULL) {
            
            pScene->onCloseCommander();
        }
        
    }
    return false;
}

void MB_FunctionPveMain::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCHPROPERTY, false);
}
