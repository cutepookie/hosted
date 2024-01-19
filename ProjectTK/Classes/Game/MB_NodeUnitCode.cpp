

#include "MB_NodeUnitCode.h"
#include "MB_LayerRoleDetail.h"

MB_NodeUnitCode::MB_NodeUnitCode(){

    m_pNodeSize = NULL;
    m_pEditBox = NULL;
  
}
MB_NodeUnitCode::~MB_NodeUnitCode(){

    CC_SAFE_RELEASE(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pEditBox);
}
bool MB_NodeUnitCode::init(){

    if(MB_ResWindow::init() == false)return false;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/setting_node_giftexchange.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    return true;
}
MB_NodeUnitCode * MB_NodeUnitCode::create(){
    
    MB_NodeUnitCode* ptr = new MB_NodeUnitCode();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitCode::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitCode::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCodeRewardClick", MB_NodeUnitCode::onCodeRewardClick);
    return NULL;
}
bool MB_NodeUnitCode::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEditBox", CCEditBox *, m_pEditBox);
    return false;
}
void MB_NodeUnitCode::onCodeRewardClick(CCObject *)
{
    MB_TARGET_PARENT(MB_LayerRoleDetail,ptr);
    if(ptr)ptr->sendgift_request(m_pEditBox->getText());
}