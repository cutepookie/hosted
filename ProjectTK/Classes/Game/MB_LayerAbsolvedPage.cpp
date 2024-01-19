//
//  MB_LayerAbsolvedPage.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-15.
//
//

#include "MB_LayerAbsolvedPage.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_ChapterData.h"
#include "MB_AbsolvedInterface.h"
#include "Game.h"
#include "MB_ServerRewardData.h"
#include "MB_ChapterInterface.h"
#include "MB_GlobelModalDlgMsgQueue.h"
#include "MB_LayerChatMain.h"
#include "MB_LayerHome.h"
MB_LayerAbsolvedPage::MB_LayerAbsolvedPage()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pChapterNode[i] = NULL;
	}
	for (int i = 0; i < 5; ++i)
	{
		m_pGuanQia_Dian[i] = NULL;
	}
	m_bPageComplate = false;
	m_pPageBackground = NULL;
	m_nType = 0;
	m_nPageId = 0;
	m_nUsedNode = 0;
	m_CurrentBattleInfo = new MB_BattleInfo;
	m_pChapterInterfaceList = new CCArray;
	m_pChapterContainer = NULL;
	m_bShowRoleInfoPanel = true;
	m_bShowEXP = true;

	m_pNanDu_putong = NULL;
	m_pNanDu_kunnan = NULL;
	sceneNode = NULL;
	m_pGuanPointNode = NULL;
}
void MB_LayerAbsolvedPage::complatePage()
{
	m_bPageComplate = true;
}
bool MB_LayerAbsolvedPage::setDataSource(CCFunctionDataSource* pDataSource)
{
	m_pDataSource = dynamic_cast<MB_AbsolvedInterface*>(pDataSource);
	return m_pDataSource != NULL;
}

MB_LayerAbsolvedPage::~MB_LayerAbsolvedPage()
{
	for (int i = 0; i < 5; ++i)
	{
		CC_SAFE_RELEASE_NULL(m_pChapterNode[i]);
	}
	for (int i = 0; i < 5; ++i)
	{
		CC_SAFE_RELEASE_NULL(m_pGuanQia_Dian[i]);
	}
	CC_SAFE_RELEASE_NULL(m_pPageBackground);
	CC_SAFE_RELEASE_NULL(m_CurrentBattleInfo);
	CC_SAFE_RELEASE_NULL(m_pChapterInterfaceList);
	CC_SAFE_RELEASE_NULL(m_pChapterContainer);
	CC_SAFE_RELEASE_NULL(m_pNanDu_putong);
	CC_SAFE_RELEASE_NULL(m_pNanDu_kunnan);
	CC_SAFE_RELEASE_NULL(m_pGuanPointNode);

	MB_AbsolvedInterface* pInstance = dynamic_cast<MB_AbsolvedInterface*>(m_pDataSource);
	if (pInstance)
	{
		pInstance->resetCurrentPageId();
	}
	removeCurrentPageResource();
}

void MB_LayerAbsolvedPage::onLoadingScene()
{

}

void MB_LayerAbsolvedPage::onMsgRecv(CCNode* node, SocketResponse* response)
{
	assert(response != NULL);

	//将socket数据读取到序列化结构
	MB_MsgBuffer* recvPacket = response->getResponseData();

	//协议号
	uint16_t Msg = 0;
	recvPacket->Reset();
	recvPacket->skipU16();
	recvPacket->skipU8();
	recvPacket->readU16(&Msg);

	switch (Msg)
	{
	case SC_BATTLE_INFO:
		break;
	default:
		break;
	}
}

bool MB_LayerAbsolvedPage::init()
{
	CCNode* pNode = loadResource("res/pve_layer_chapter.ccbi");
	if (pNode)
	{
		addChild(pNode);
		this->setTouchEnabled(true);
		MB_AbsolvedInterface* pInstance = ((MB_AbsolvedInterface*)m_pDataSource);
		int type = pInstance->getCurrentType();
        if (m_bToPageID==-1) {
            MB_AbsolvedInterface* pInstance = ((MB_AbsolvedInterface*)m_pDataSource);
            int type = pInstance->getCurrentType();
            MB_ChapterProgress* pProgress = pInstance->getChapterProgressByType(pInstance->getCurrentType());
            MB_ChapterPage* pPage = NULL;
            MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(pInstance->getCurrentType(), pProgress->getChapterId(), &pPage);
            if (pPage)
            {
                m_bToPageID = pPage->getPageId();
            }
            else
            {
                m_bToPageID = pInstance->getCurrentPage();
            }
            m_bNowPassPageID = m_bToPageID;
        }
		setData(type, m_bToPageID);
		setTouchEnabled(true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("PreLevel", MB_RoleData::getInstance()->getLevel());
        m_pNanDu_putong->setVisible(m_nType == kChapterDifficultyNormal);
        m_pNanDu_kunnan->setVisible(m_nType == kChapterDifficultyHard);
		return true;
	}
	return false;
}
float dianPX[3] = { 297.6f, 280, 264 };
bool MB_LayerAbsolvedPage::setData(int nType, int nPageId)
{
	if (nType < 0
		|| nType > 2)
	{
		return false;
	}

	m_nType = nType;
	m_nPageId = nPageId;
	m_bToPageID = m_nPageId;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("xuanguan.plist");

	for (int i = 0; i<5; i++) {
		if (m_bNowPassPageID<4 && i>m_bNowPassPageID) {
			m_pGuanQia_Dian[i]->setVisible(false);
		}
		if (i == m_bToPageID - 1) {
            m_pGuanQia_Dian[m_bToPageID - 1]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("map_indi_select.png"));
            m_pGuanQia_Dian[m_bToPageID - 1]->setOpacity(255);
		}else
        {
            m_pGuanQia_Dian[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("map_dot.png"));
            m_pGuanQia_Dian[i]->setOpacity(127);
        }
	}
	if (m_bNowPassPageID>3) {
		m_pGuanPointNode->setPositionX(251.6f);
	}
	else
	{
		m_pGuanPointNode->setPositionX(dianPX[m_bNowPassPageID - 1]);
	}


	MB_AbsolvedInterface* pRoot = dynamic_cast<MB_AbsolvedInterface*>(m_pDataSource);
	if (pRoot)
	{
		pRoot->setCurrentPage(m_nPageId);
		pRoot->setCurrentType(m_nType);
	}

	MB_ChapterPage* pPage = NULL;
	MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId, &pPage);
	if (pPage)
	{
		pPage->loadResource2SpriteCache();
	}

	initChapterInterface();
	resetChapters();
	onResetWnd();

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	return true;
}

bool MB_LayerAbsolvedPage::initChapterInterface()
{
	MB_ChapterPage* pPage = NULL;

	MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId, &pPage);
	MB_ChapterInterface* pInterface = NULL;
	CCArray* pArray = pPage->getChapterArray();
	MB_ChapterData* pData = NULL;
	m_pChapterInterfaceList->removeAllObjects();
	CCARRAY_FOREACH_4TYPE(pArray, MB_ChapterData*, pData)
	{
		MB_AbsolvedConfigure::getInstance()->queryChapterInterface(m_nType, m_nPageId, pData->getChapterId(), &pInterface);
		if (pInterface)
		{
			m_pChapterInterfaceList->addObject(pInterface);
		}
	}

	MB_AbsolvedInterface* pRoot = dynamic_cast<MB_AbsolvedInterface*>(m_pDataSource);
	if (pRoot)
	{
		MB_ChapterProgress* pProgress = pRoot->getChapterProgressByType(m_nType);
		MB_ChapterPage* pProgressPage = NULL;
		MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(m_nType, pProgress->getChapterId(), &pProgressPage);
		if (pProgressPage->getPageId() > m_nPageId)
		{
			complatePage();
		}
	}
	return true;
}

void MB_LayerAbsolvedPage::onResetWnd()
{
	MB_ChapterPage* pPage = NULL;

	MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId, &pPage);
	MB_ResWindow* pLayer = NULL;
	if (pPage)
	{
		pPage->loadResource2SpriteCache();
		NSGameHelper::setSpriteFrameWithFrameCache(m_pPageBackground, pPage->getBackground().c_str());
		for (int i = 0; i < m_nUsedNode; ++i)
		{
			pLayer = dynamic_cast<MB_ResWindow*>(m_pChapterNode[i]->getChildByTag(0));
			if (pLayer)
			{
				pLayer->onResetWnd();
			}
		}
	}

	pPage = NULL;
	MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId - 1, &pPage);
	//m_pNodeLeftAni->setVisible(pPage != NULL);

	MB_AbsolvedInterface* pInstance = ((MB_AbsolvedInterface*)m_pDataSource);
	MB_ChapterProgress* pProgress = pInstance->getChapterProgressByType(m_nType);
	pPage = NULL;
	MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(m_nType, pProgress->getChapterId(), &pPage);
}

bool MB_LayerAbsolvedPage::queryChapterInterfaceByChapterId(int nChapterId, MB_ChapterInterface** pInterface)
{
	MB_ChapterInterface* pChapter = NULL;
	CCARRAY_FOREACH_4TYPE(m_pChapterInterfaceList, MB_ChapterInterface*, pChapter)
	{
		if (pChapter->getChapterId() == nChapterId)
		{
			*pInterface = pChapter;
			return true;
		}
	}
	return false;
}

void MB_LayerAbsolvedPage::resetChapters()
{
	MB_ChapterInterface* pChapter = NULL;
	MB_ChapterData* pData = NULL;
	MB_ResWindow* pLayer = NULL;
	int index = 0;
	CCSize container_size = m_pChapterContainer->getContentSize();
	CCPoint pt;
	CCARRAY_FOREACH_4TYPE(m_pChapterInterfaceList, MB_ChapterInterface*, pChapter)
	{
		pLayer = pChapter->createEntryDialog();
		if (pLayer == NULL)
		{
			continue;
		}

		MB_AbsolvedConfigure::getInstance()->queryChapterData(m_nType, m_nPageId, pChapter->getChapterId(), &pData);
		if (pData)
		{
			pt = pData->getLocation();
			pt.x = container_size.width * pt.x / 100;
			pt.y = container_size.height * pt.y / 100;
			m_pChapterNode[index]->setPosition(pt);
			m_pChapterNode[index]->removeAllChildren();
			m_pChapterNode[index]->addChild(pLayer);
			pLayer->setTag(0);
			++index;
		}
	}

	m_nUsedNode = index;

	for (; index < 5; ++index)
	{
		m_pChapterNode[index]->setVisible(false);
	}
}

int MB_LayerAbsolvedPage::calcChapterStarById(int nChapterId)
{
	if (m_CurrentBattleInfo->getChapterId() == nChapterId)
	{
		return m_CurrentBattleInfo->getBattleStar();
	}
	else
	{
		if (((MB_AbsolvedInterface*)m_pDataSource)->isDungeonPerfect(nChapterId))
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}
bool MB_LayerAbsolvedPage::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
	{
		return true;
	}

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_chapter_node", CCNode*, m_pChapterContainer);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite_bg", CCSprite*, m_pPageBackground);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNanDu_putong", CCNode*, m_pNanDu_putong);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNanDu_kunnan", CCNode*, m_pNanDu_kunnan);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pGuanPointNode", CCNode*, m_pGuanPointNode);

	char buff[25] = {};
	for (int i = 0; i < 5; ++i)
	{
		sprintf(buff, "node_%d", i + 1);
		CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*, m_pChapterNode[i]);
	}
	for (int i = 0; i < 5; ++i)
	{
		sprintf(buff, "m_pGuanQia_Dian%d", i);
		CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCSprite*, m_pGuanQia_Dian[i]);
	}
	return false;
}

SEL_MenuHandler MB_LayerAbsolvedPage::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerAbsolvedPage::onCloseClick);
	return NULL;
}

SEL_CCControlHandler MB_LayerAbsolvedPage::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNormalClicked", MB_LayerAbsolvedPage::onNormalClicked);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHardClicked", MB_LayerAbsolvedPage::onHardClicked);
	return NULL;
}
void MB_LayerAbsolvedPage::onCloseClick(CCObject* pSender)
{
    if (m_bIsCanToChapter) {
        m_bIsCanToChapter = false;
        m_bToPageID = 0;
        float winWidth = CCDirector::sharedDirector()->getWinSize().width;
        sceneNode = CCDirector::sharedDirector()->getRunningScene();
        sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(winWidth - sceneNode->getPositionX()) / MOVESCENESPEED, ccp(winWidth, 0)), CCCallFunc::create(this, callfunc_selector(MB_LayerAbsolvedPage::finish2)), NULL));
    }
}


void MB_LayerAbsolvedPage::selectChapterDiffcuty(int kDiffcutyType)
{
	MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(m_pDataSource);
	MB_ChapterProgress* pProgress = pAbsolved->getChapterProgressByType(kDiffcutyType);
	MB_ChapterPage* pPage = NULL;
	if (pProgress)
	{
		removeCurrentPageResource();
		if (MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(kDiffcutyType, pProgress->getChapterId(), &pPage))
		{
			setData(kDiffcutyType, pPage->getPageId());
		}
		else
		{
		}
	}
}

void MB_LayerAbsolvedPage::removeCurrentPageResource()
{
	MB_ChapterPage* pPage = NULL;
	if (MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId, &pPage))
	{
		pPage->removeResourceFromSpriteCache();
	}
}

void MB_LayerAbsolvedPage::onNormalClicked(CCObject* pSender)
{
	if (m_nType == kChapterDifficultyNormal)
	{
		return;
	}
	else
	{
		m_pNanDu_putong->setVisible(true);
		m_pNanDu_kunnan->setVisible(false);
		selectChapterDiffcuty(kChapterDifficultyNormal);
	}
}

void MB_LayerAbsolvedPage::onHardClicked(CCObject* pSender)
{
	if (m_nType == kChapterDifficultyHard)
	{
		return;
	}
	else
	{
		if (MB_RoleData::getInstance()->getLevel() < 20)
		{
			MB_Message::sharedMB_Message()->showMessage("20级开启困难难度");
			return;
		}
		m_pNanDu_putong->setVisible(false);
		m_pNanDu_kunnan->setVisible(true);
		selectChapterDiffcuty(kChapterDifficultyHard);
	}
}


bool MB_LayerAbsolvedPage::pageExist(int pageId)
{
	MB_ChapterPage* page = NULL;
	MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, pageId, &page);
	if (page == NULL)
	{
		return false;
	}
	return true;
}

void MB_LayerAbsolvedPage::onFlipLeft()
{
}
void MB_LayerAbsolvedPage::onFlipRight()
{
	//        onTurnRightClicked(this);
}
//void MB_LayerAbsolvedPage::onTurnRightClicked(CCObject*)
//{
//    if (pageExist(m_nPageId+1))
//    {
//        setData(m_nType, m_nPageId+1);
//    }
//}

void MB_LayerAbsolvedPage::goChapter(int id)
{
	MB_ChapterInterface* pInterface = NULL;
	queryChapterInterfaceByChapterId(id, &pInterface);

	if (pInterface == NULL)
	{
		//        onTurnRightClicked(this);
		queryChapterInterfaceByChapterId(id, &pInterface);
		if (pInterface)
		{
			pInterface->onEntryClicked(this);
		}
		else
		{
			MB_Message::sharedMB_Message()->showMessage("当前页的所有章节已通过，请切换到其他章节页");
		}
	}
	else
	{
		pInterface->onEntryClicked(this);
	}
}

bool MB_LayerAbsolvedPage::containChapter(int id)
{
	MB_ChapterInterface* pInterface = NULL;
	return queryChapterInterfaceByChapterId(id, &pInterface);
}


void MB_LayerAbsolvedPage::registerWithTouchDispatcher(void){

	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128, false);
}
bool MB_LayerAbsolvedPage::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	if (sceneNode == NULL) {
		sceneNode = CCDirector::sharedDirector()->getRunningScene();
	}
	return true;
}
void MB_LayerAbsolvedPage::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCPoint point = pTouch->getDelta();
	sceneNode->setPositionX(sceneNode->getPositionX() + point.x);
	if (m_nPageId == m_bNowPassPageID + 1) {
		if (sceneNode->getPositionX() < 0) {
			sceneNode->setPositionX(0);
		}
	}
}
void MB_LayerAbsolvedPage::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bIsCanToChapter) {
        m_bIsCanToChapter = false;
        addChild(NSGameHelper::createDisableTouchLayer(), 0, 999);// 防止点穿
        float winWidth = CCDirector::sharedDirector()->getWinSize().width;
        if (sceneNode->getPositionX()<-winWidth / 4) {
            sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(-winWidth - sceneNode->getPositionX()) / MOVESCENESPEED, ccp(-winWidth, 0)), CCCallFunc::create(this, callfunc_selector(MB_LayerAbsolvedPage::finish3)), NULL));
            
        }
        else if (sceneNode->getPositionX()>winWidth / 4)
        {
            sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(winWidth - sceneNode->getPositionX()) / MOVESCENESPEED, ccp(winWidth, 0)), CCCallFunc::create(this, callfunc_selector(MB_LayerAbsolvedPage::finish2)), NULL));
        }
        else
        {
            if (fabs(sceneNode->getPositionX()) < 5) {
                m_bIsCanToChapter = true;
            }
            sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(sceneNode->getPositionX()) / MOVESCENESPEED, ccp(0, 0)), CCCallFunc::create(this, callfunc_selector(MB_LayerAbsolvedPage::finish)), NULL));
        }
    }
}
void MB_LayerAbsolvedPage::onEnter()
{
    MB_LayerFlipFunctionWnd::onEnter();
    PlayRoleSound(kSoundEnterPve);
    if (global_tutorialNode!=NULL) {
        global_tutorialNode->setPositionX(global_tutorialNode->getPositionX()+640);
        setTouchEnabled(false);
    }
}

void MB_LayerAbsolvedPage::finish()
{
	removeChildByTag(999);
    m_bIsCanToChapter = true;
}
void MB_LayerAbsolvedPage::finish2()
{
	if (m_bToPageID > 1) {
		m_bToPageID--;
		NSGameFunction::CCFunctionInterface* pInterface = NULL;
		MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
		if (pInterface)
		{
			pInterface->onEntryClicked(this);
		}
	}
	else
	{
		MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
	}

	float winWidth = CCDirector::sharedDirector()->getWinSize().width;
	sceneNode->setPositionX(-winWidth);
	sceneNode->runAction(CCSequence::create(CCMoveTo::create((winWidth) / MOVESCENESPEED, ccp(0, 0)), NULL));
    m_bIsCanToChapter = true;
}
void MB_LayerAbsolvedPage::finish3()
{
	m_bToPageID++;
	NSGameFunction::CCFunctionInterface* pInterface = NULL;
	MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
	if (pInterface)
	{
		pInterface->onEntryClicked(this);
	}
	float winWidth = CCDirector::sharedDirector()->getWinSize().width;
	sceneNode->setPositionX(winWidth);
	sceneNode->runAction(CCSequence::create(CCMoveTo::create((winWidth) / MOVESCENESPEED, ccp(0, 0)), NULL));
    m_bIsCanToChapter = true;
}
