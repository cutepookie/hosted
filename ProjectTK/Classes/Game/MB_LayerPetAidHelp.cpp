//
//  MB_LayerPetAidHelp.cpp
//  ProjectTK
//
//  Created by crimoon on 13-12-12.
//
//

#include "MB_LayerPetAidHelp.h"

MB_LayerPetAidHelp::MB_LayerPetAidHelp(){

}
MB_LayerPetAidHelp::~MB_LayerPetAidHelp(){

}
bool MB_LayerPetAidHelp::init(){

    MB_ResWindow::init();
    
    MB_MessageBox3 *message= MB_MessageBox3::create();
    message->setTouchPriority(0);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    message->removeAllChildrenWithCleanup(true);
    message->setTouchEnabled(true);
    message->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
    this->addChild(message);

    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/gui_pet_helpinfo.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    
    return true;
}
bool MB_LayerPetAidHelp::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

    return false;
}
SEL_MenuHandler MB_LayerPetAidHelp::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerPetAidHelp::onCloseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerPetAidHelp::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
void MB_LayerPetAidHelp::onCloseClicked(CCObject *){

    this->popWindow();
}
MB_LayerPetAidHelp * MB_LayerPetAidHelp::create(){

    MB_LayerPetAidHelp *ptr = new MB_LayerPetAidHelp();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}