#include "MB_NodeUnitClearCache.h"
#include "MB_LayerRoleDetail.h"
#include "MB_ChatData.h"
MB_NodeUnitClearCache::MB_NodeUnitClearCache(){

    m_pNodeSize = NULL;
}
MB_NodeUnitClearCache::~MB_NodeUnitClearCache(){

    CC_SAFE_RELEASE(m_pNodeSize);
}
bool MB_NodeUnitClearCache::init(){

    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/setting_node_input.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    return true;
}
MB_NodeUnitClearCache* MB_NodeUnitClearCache::create(){

    MB_NodeUnitClearCache *ptr = new MB_NodeUnitClearCache();
    if (ptr && ptr->init()) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitClearCache::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitClearCache::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClearClick", MB_NodeUnitClearCache::onClearClick);
    return NULL;
}
bool MB_NodeUnitClearCache::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
    return  false;
}
void MB_NodeUnitClearCache::onClearClick(CCObject *)
{
    MB_ChatDataMgr::getInstance()->clearChatCache();
    MB_Message::sharedMB_Message()->showMessage("清除成功");
}
