
//
#include "MB_NodeUnitRegist.h"
#include "MB_LayerRoleDetail.h"
MB_NodeUnitRegist::MB_NodeUnitRegist(){

	m_pNodeSize = NULL;
}
MB_NodeUnitRegist::~MB_NodeUnitRegist(){

	CC_SAFE_RELEASE(m_pNodeSize);
}
bool MB_NodeUnitRegist::init(){

	MB_ResWindow::init();

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode*  node = pCCBReader->readNodeGraphFromFile("res/setting_node_account.ccbi", this);
	pCCBReader->release();
	this->addChild(node);
	return true;
}
MB_NodeUnitRegist* MB_NodeUnitRegist::create(){

	MB_NodeUnitRegist *ptr = new MB_NodeUnitRegist();
	if (ptr && ptr->init()) {

		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitRegist::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){


	return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitRegist::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRegistClick", MB_NodeUnitRegist::onRegistClick);
	return NULL;
}
bool MB_NodeUnitRegist::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
	return  false;
}
void MB_NodeUnitRegist::onRegistClick(CCObject *){
	MB_SceneRegist * layer = MB_SceneRegist::create(LAYER_TAG_BIND_GUEST);
	CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
}
