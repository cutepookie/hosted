

#include "MB_NodeUnitInvite.h"
//#include "MB_LayerSettingMain.h"
#include "MB_LayerRoleDetail.h"
MB_NodeUnitInvite::MB_NodeUnitInvite(){

    m_pNodeSize = NULL;
}
MB_NodeUnitInvite::~MB_NodeUnitInvite(){

    CC_SAFE_RELEASE(m_pNodeSize);
}
bool MB_NodeUnitInvite::init(){

    if(MB_ResWindow::init() == false){
        
        return false;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/setting_node_invitegift.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    onResetWnd();
    return true;
}
MB_NodeUnitInvite * MB_NodeUnitInvite::create(){

    MB_NodeUnitInvite *ptr  = new MB_NodeUnitInvite();
    if (ptr && ptr->init()) {
        
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitInvite::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return  NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitInvite::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRewardDetailClick", MB_NodeUnitInvite::onRewardDetailClick);
    return  NULL;
}
bool MB_NodeUnitInvite::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
    return false;
}
void MB_NodeUnitInvite::onRewardDetailClick(CCObject *){
    
    MB_TARGET_PARENT(MB_LayerRoleDetail, ptr)
    if (ptr) {
    
    
        MB_LayerInviteHelp * layer =  MB_LayerInviteHelp::create();
        ptr->pushWindow(layer,true);
        layer->_setZOrder(Z_ORDER_OUTSHOW);
    }
}
