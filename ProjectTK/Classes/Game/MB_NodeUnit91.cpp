
#include "MB_NodeUnit91.h"
MB_NodeUnit91::MB_NodeUnit91(){

	m_pNodeSize = NULL;
}
MB_NodeUnit91::~MB_NodeUnit91(){

	CC_SAFE_RELEASE(m_pNodeSize);
}
bool MB_NodeUnit91::init(){

	if (MB_ResWindow::init() == false){

		return false;
	}
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	pCCBReader->release();
	return true;
}
MB_NodeUnit91 * MB_NodeUnit91::create(){

	MB_NodeUnit91 * ptr = new MB_NodeUnit91();
	if(ptr && ptr->init()){

		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnit91::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

	return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnit91::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "on91AppClick", MB_NodeUnit91::on91AppClick);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBBSClick", MB_NodeUnit91::onBBSClick);

	return NULL;
}
bool MB_NodeUnit91::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
	return false;
}
void MB_NodeUnit91::on91AppClick(CCObject *){

}
void MB_NodeUnit91::onBBSClick(CCObject *){

}
