

#include "MB_NodeUnitLogout.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif


MB_NodeUnitLogout::MB_NodeUnitLogout(){

	m_pNodeSize = NULL;
}
MB_NodeUnitLogout::~MB_NodeUnitLogout(){

	CC_SAFE_RELEASE(m_pNodeSize);
}
bool MB_NodeUnitLogout::init(){

	MB_ResWindow::init();

	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
	CCNode*  node = pCCBReader->readNodeGraphFromFile("res/setting_node_logoff.ccbi", this);
	pCCBReader->release();
	this->addChild(node);
	return true;
}
MB_NodeUnitLogout* MB_NodeUnitLogout::create(){

	MB_NodeUnitLogout *ptr = new MB_NodeUnitLogout();
	if (ptr && ptr->init()) {

		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_DELETE(ptr);
	return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitLogout::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

	return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitLogout::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){


	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onUNRegistClick", MB_NodeUnitLogout::onLogoutClick);
	return NULL;
}
bool MB_NodeUnitLogout::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
	return false;
}
void MB_NodeUnitLogout::onLogoutClick(CCObject *){


	MB_Message::sharedMB_Message()->showMessage(" ", 5);
#ifdef PLATFORM_YJ
	MB_YJMgr::getInstance()->goLogout();
#elif defined(YJ_IOS)
	MB_YJMgr_IOS::getInstance()->goLogout();
#else
	MB_ServerList::destroyInstance();
	MB_ClientSocket::destroyInstance();
	CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
	CCScene *pScene = MB_SceneLoginBackground::scene();
	CCDirector::sharedDirector()->popToRootScene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	PlayBackGround(kmBackGround_Login);
#endif

}
