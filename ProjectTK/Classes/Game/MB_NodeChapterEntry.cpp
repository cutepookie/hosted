//
//  MB_NodeChapterEntry.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#include "MB_NodeChapterEntry.h"
#include "MB_ChapterInterface.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_AbsolvedInterface.h"
#include "MB_FunctionMgr.h"
#include "MB_ChapterData.h"
#include "MB_ServerRewardData.h"

MB_NodeChapterEntry::MB_NodeChapterEntry()
{
	m_pTitle = NULL;
	m_plockBg = NULL;
	m_pIconChild = NULL;
	m_pNowBg = NULL;
	m_pControlButtonIcon = NULL;
	m_bBg = NULL;
}

MB_NodeChapterEntry::~MB_NodeChapterEntry()
{
	CC_SAFE_RELEASE_NULL(m_pTitle);
	CC_SAFE_RELEASE_NULL(m_plockBg);
	CC_SAFE_RELEASE_NULL(m_pIconChild);

	CC_SAFE_RELEASE_NULL(m_pNowBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonIcon);
	CC_SAFE_RELEASE_NULL(m_bBg);

}

bool MB_NodeChapterEntry::init()
{
	CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/pve_node_chapter.ccbi", this);
	CC_SAFE_RELEASE(pCCBReader);

	if (pNode != NULL)
	{
		addChild(pNode);
		onResetWnd();
		return true;
	}

	return false;
}

void MB_NodeChapterEntry::onResetWnd()
{
	MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
	if (pInterface)
	{
		NSGameFunction::CCFunctionInterface* pTemp = NULL;
		MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pTemp);
		MB_AbsolvedInterface* pInstance = (MB_AbsolvedInterface*)(pTemp);
		MB_ChapterData* pData = pInterface->getChapterData();
		MB_ChapterProgress* pProgress = pInterface->getChapterProgress();
		setChapterIcon(pData->getActovateIcon().c_str());
		if (pProgress->getChapterId() > pInterface->getChapterId())
		{
			activate(1);
		}
		else if (pProgress->getChapterId() == pInterface->getChapterId())
		{
			activate(0);
		}
		else
		{
			activate(-1);
		}
	}
}

bool MB_NodeChapterEntry::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ControlButtonIcon", CCControlButton*, m_pControlButtonIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTitle", CCSprite*, m_pTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIconChild", CCNode*, m_pIconChild);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lockBg", CCControlButton*, m_plockBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nowBg", CCNode*, m_pNowBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_bBg", CCControlButton*, m_bBg);


	return false;
}

SEL_MenuHandler MB_NodeChapterEntry::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler MB_NodeChapterEntry::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChapterClicked", MB_NodeChapterEntry::onChapterClicked);
	return NULL;
}

bool MB_NodeChapterEntry::setDataSource(CCFunctionDataSource* pDataSource)
{
	m_pDataSource = dynamic_cast<MB_ChapterInterface*>(pDataSource);

	return m_pDataSource != NULL;
}

void MB_NodeChapterEntry::setChapterIcon(const char* pFile)
{
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFile);
	if (frame)
	{
        m_ChapterFileChar = pFile;
		m_pTitle->setDisplayFrame(frame);

		if (strstr(pFile, "_") != NULL)
		{
			m_plockBg->setPosition(ccp(-1.0, 2));
		}
	}
}

void MB_NodeChapterEntry::onChapterClicked(CCObject* pSender)
{
    if (m_bIsCanToChapter) {
        if (m_plockBg->isVisible()){ MB_Message::sharedMB_Message()->showMessage("尚未解锁该关卡"); return; }
        TutorialTriggerComplete
        MB_ChapterInterface* pInterface = dynamic_cast<MB_ChapterInterface*>(m_pDataSource);
        if (pInterface)
        {
            ChapterFileChar = m_ChapterFileChar;
            pInterface->onEntryClicked(this);
        }
    }
}

void MB_NodeChapterEntry::activate(int index)
{
	//index==-1 为未开启的  index==0为当前该打的    index==1为已经通关的
	if (index == -1)
	{
		m_plockBg->setTouchPriority(99);

		m_pNowBg->setVisible(false);
		m_plockBg->setVisible(true);
	}
	else if (index == 0)
	{
		m_pIconChild->removeFromParentAndCleanup(false);
		m_pIconChild->setPosition(m_pControlButtonIcon->getPreferredSize() / 2 + ccp(-60.1f, -9));
		m_pControlButtonIcon->addChild(m_pIconChild);
		m_pControlButtonIcon->setTouchPriority(99);

		m_pNowBg->setVisible(true);
		m_plockBg->setVisible(false);

		m_bBg->setVisible(false);
		m_pControlButtonIcon->setVisible(true);
	}
	else if (index == 1)
	{
		m_pIconChild->removeFromParentAndCleanup(false);
		m_pIconChild->setPosition(m_bBg->getPreferredSize() / 2 + ccp(0, 1.7f));
		m_bBg->addChild(m_pIconChild);
		m_bBg->setTouchPriority(99);

		m_pNowBg->setVisible(true);
		m_plockBg->setVisible(false);

		m_bBg->setVisible(true);
		m_pControlButtonIcon->setVisible(false);
	}

}
