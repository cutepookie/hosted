//
//  MB_SceneLoginBackground.cpp
//  ProjectMB
//
//  Created by wenyong on 14-9-6.
//
//

#include "MB_LoginBackground.h"
#include "SDS_NetWorkDefine.h"
#include "OCandCppHelper.h"
#include "MB_Message.h"
#include "MB_LayerFirstLogin.h"
#include "MB_UpdateSystem.h"
#include "MB_LayerResourceUpdate.h"
#include "MB_ResourcesPackageUpdate.h"
#include "RichText.h"
USING_NS_CC;
USING_NS_CC_EXT;

MB_LoginBackground::MB_LoginBackground()
{
	m_pPecentTTF = NULL;
	m_pUpdateProgress = NULL;
	m_bCanUpdate = true;
	m_bCanTouch = false;
	isEndUpdate = true;
	MB_PackageUpdateMgr::getInstance()->setDelegate(this);
}

MB_LoginBackground::~MB_LoginBackground()
{
	CC_SAFE_RELEASE_NULL(m_pPecentTTF);
}
bool MB_LoginBackground::init()
{
	MB_ResWindow::init();
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCSprite * pBG;
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
//    if (screenSize.height < 960) {
//        pBG = CCSprite::create("bg_320_480.png");
//    }
//    else if (screenSize.height < 1136)
//    {
//        pBG = CCSprite::create("bg_640_960.png");
//    }
//    else if (screenSize.height < 1334)
//    {
//        pBG = CCSprite::create("bg_640_1136.png");
//    }
//    else if (screenSize.height < 2208)
//    {
//        pBG = CCSprite::create("bg_640_1136.png");
//        //pBG = CCSprite::create("bg_750_1334.png");
//
//    }
//    else if (screenSize.height < 2436)
//    {
//        pBG = CCSprite::create("bg_1242_2208.png");
//        pBG->setScale(.5f);
//    }
//    else{
//
//        pBG = CCSprite::create("bg_1125_2436.png");
//        pBG->setScale(.55f);
//    }
    pBG = CCSprite::create("bg/bg_start.jpg");
	addChild(pBG);
	CCSize ws = CCDirector::sharedDirector()->getWinSize();
	pBG->setPosition(ccp(ws.width*0.5, ws.height*0.5));


	//CCSprite * pLogo = CCSprite::create("logo.png");
	//addChild(pLogo);

	//pLogo->setPosition(ccp(ws.width*0.5, ws.height - pLogo->getContentSize().height*1.2));

	CCLabelTTF * channel = CCLabelTTF::create();

	channel->setString(OCandCppHelper::getChannelAndVer().c_str());

	channel->setAnchorPoint(ccp(0, 1));

	channel->setHorizontalAlignment(kCCTextAlignmentLeft);
	channel->setFontSize(15);

	channel->setPosition(ccp(0, ws.height));

	addChild(channel, 999);


	pRootNode = loadResource("res/login_layer_background.ccbi");
	if (pRootNode)
	{
		addChild(pRootNode);
	}
	m_pPecentTTF->setVisible(false);
	onFinishedInitialize();
	return true;
}


CCScene* MB_LoginBackground::scene()
{
	CCScene *scene = CCScene::create();

	MB_LoginBackground *layer = MB_LoginBackground::create();

	scene->addChild(layer);

	return scene;
}

void MB_LoginBackground::setSomeVisible(bool b)
{
	m_pPecentTTF->setVisible(b);
	m_pUpdateProgress->visibleProgress(b);
}
void MB_LoginBackground::onFinishedInitialize()
{
	// old code
	if (m_bCanUpdate)
	{
		this->runAction(CCCallFunc::create(this, callfunc_selector(MB_LoginBackground::sendMainVersionCheck)));
		m_pPecentTTF->setZOrder(2);
		m_pUpdateProgress = MB_LayerResourceUpdate::create();
		pRootNode->addChild(m_pUpdateProgress);
		m_pUpdateProgress->setClickCallback(this, callfunc_selector(MB_LoginBackground::onUpdateComplated));
		setSomeVisible(false);
		isEndUpdate = false;
	}
	else
	{

		MB_LayerFirstLogin *layer = MB_LayerFirstLogin::create();
		pushWindow(layer);
	}
}



bool MB_LoginBackground::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pPecentTTF", CCLabelTTF*, m_pPecentTTF);
	return true;
}

SEL_MenuHandler MB_LoginBackground::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MB_LoginBackground::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}


void MB_LoginBackground::onUpdateComplated()
{
	if (m_bCanTouch && m_bCanUpdate)
	{
		m_bCanTouch = false;
		m_bCanUpdate = false;
		onSuccess();
	}
	else
	{
		if (m_pUpdateProgress)setSomeVisible(false);
	}
}

void MB_LoginBackground::sendMainVersionCheck()
{
	//TODODO 热更新开关
#if 1
	if (m_pUpdateProgress){
		m_pUpdateProgress->setVisible(true);
	}
	MB_PackageUpdateMgr::getInstance()->sendupdate_check();
	scheduleUpdate();
#else
	if (m_pUpdateProgress)m_pUpdateProgress->removeFromParent();
	MB_LayerFirstLogin *layer = MB_LayerFirstLogin::create();
	pushWindow(layer);
#endif

}

void MB_LoginBackground::update(float dt)
{
	if (MB_PackageUpdateMgr::getInstance()->updateState != -1)
	{
		if (MB_PackageUpdateMgr::getInstance()->updateState == 1)
		{
			isEndUpdate = true;
			m_pPecentTTF->setVisible(false);
			if (m_pUpdateProgress){ m_pUpdateProgress->removeFromParent(); m_pUpdateProgress = NULL; }
			MB_LayerFirstLogin *layer = MB_LayerFirstLogin::create();
			pushWindow(layer);
		}
		unscheduleUpdate();
	}
}


void MB_LoginBackground::onEnter()
{
	MB_ResWindow::onEnter();
	//MB_AudioMgr::getInstance()->playMusic(kAudioMusicLogin);
}


// Error caused by creating a file to store downloaded data
//kCreateFile,
// Error caused by network
//-- network unavaivable
//-- timeout
//-- ...

//kNetwork,
// There is not a new version

//kNoNewVersion,
// Error caused in uncompressing stage
// -- can not open zip file
// -- can not read file global information
// -- can not read file information
// -- can not create a directory
// -- ...

//kUncompress,

void MB_LoginBackground::onError(AssetsManager::ErrorCode errorCode)
{
	m_bCanTouch = true;
	if (errorCode == AssetsManager::kCreateFile)
	{
		MB_Message::sharedMB_Message()->showMessage("无法创建下载文件，请重新安装游戏");
	}
	else if (errorCode == AssetsManager::kNetwork)
	{
		MB_Message::sharedMB_Message()->showMessage("网络超时，点击任意位置重试");
		m_bCanUpdate = true;
	}
	else if (errorCode == AssetsManager::kNoNewVersion)
	{
		//showMessage("没有发现新版本资源");
	}
	else
	{
		MB_Message::sharedMB_Message()->showMessage("解压资源失败");
	}
}

void MB_LoginBackground::onProgress(int percent)
{
	if (!isEndUpdate)
	{
        if (percent>0) {
            char buf[16] = {};
            sprintf(buf, "%d%%", percent);
            m_pPecentTTF->setString(buf);
            m_pUpdateProgress->setUpdatePercent(percent);
        }
	}
}

void MB_LoginBackground::onSuccess()
{
	isEndUpdate = true;
	removeAllChildren();
	m_pUpdateProgress = NULL;
	m_bCanUpdate = false;
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	init();
	MB_PackageUpdateMgr::destroyInstance();


	if (m_pUpdateProgress)
	{
		setSomeVisible(false);
	}
}

void MB_LoginBackground::onNoPatchUpdate()
{
	if (m_pUpdateProgress)
	{
		setSomeVisible(false);
	}
	MB_LayerFirstLogin *layer = MB_LayerFirstLogin::create();
	pushWindow(layer);
	MB_PackageUpdateMgr::destroyInstance();
}
