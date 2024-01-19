

#include "Game.h"
#include "MB_LayerFirstLogin.h"
#include "MB_SceneLoginBackground.h"
#include "../Common/SDS_NetWorkDefine.h"
#include "MB_LoginBackground.h"
#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;

//#undef USE_FILE_CHECK
//#define USE_FILE_CHECK 0
MB_SceneLoginBackground::MB_SceneLoginBackground()
{
	m_pLabelVersion = NULL;
}

MB_SceneLoginBackground::~MB_SceneLoginBackground()
{
	CC_SAFE_RELEASE(m_pLabelVersion);
}

#include "MB_LoginBackground.h"
CCScene* MB_SceneLoginBackground::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();


	// 'layer' is an autorelease object
	CCLayer *layer = MB_LoginBackground::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

CCLayer* MB_SceneLoginBackground::create()
{
	return MB_LoginBackground::create();
}
