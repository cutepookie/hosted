

#include "MB_NodeUnitFAQ.h"
#include "MB_FunctionMgr.h"
MB_NodeUnitFAQ::MB_NodeUnitFAQ(){

}
MB_NodeUnitFAQ::~MB_NodeUnitFAQ(){

}
bool MB_NodeUnitFAQ::init(){

    if(MB_ResWindow::init() == false){
        
        return false;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/setting_node_bugmail.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    return true;

}
MB_NodeUnitFAQ* MB_NodeUnitFAQ::create(){

    MB_NodeUnitFAQ * ptr = new MB_NodeUnitFAQ();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitFAQ::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitFAQ::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onEnterClicked",  MB_NodeUnitFAQ::onEnterClicked);
    return NULL;

}
bool MB_NodeUnitFAQ::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget,
                                               const char * pMemberVariableName,
                                               cocos2d::CCNode * pNode)
{
    
    return false;
}
void MB_NodeUnitFAQ::onEnterClicked(CCObject *)
{
    MB_ResWindow* pWindow = MB_FunctionMgr::getInstance()->getFunctionMainWndByType(kFunctionYeShiJie);
    if (pWindow)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(pWindow,Z_ORDER_OUTSHOW);
    }
}
