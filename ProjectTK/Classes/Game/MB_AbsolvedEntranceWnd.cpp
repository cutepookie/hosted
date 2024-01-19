//
//  MB_AbsolvedEntranceWnd.cpp
//  ProjectPM
//
//  Created by crimoon on 14-3-25.
//
//

#include "MB_AbsolvedEntranceWnd.h"
#include "MB_LayerHome.h"
#include "MB_RoleData.h"
#include "MB_AbsolvedInterface.h"
#include "MB_ServerRewardData.h"
#include "MB_AbsolvedConfigure.h"
MB_AbsolvedEntranceWnd::MB_AbsolvedEntranceWnd()
{
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_LEVEL, MB_AbsolvedEntranceWnd);
	SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_AbsolvedEntranceWnd);
	SOCKET_MSG_REGIST(SC_ROLE_UPDATE_ENERGY, MB_AbsolvedEntranceWnd);
}

MB_AbsolvedEntranceWnd::~MB_AbsolvedEntranceWnd()
{
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_LEVEL);
	SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
	SOCKET_MSG_UNREGIST(SC_ROLE_UPDATE_ENERGY);
}
bool MB_AbsolvedEntranceWnd::setDataSource(CCFunctionDataSource* pDataSource)
{
	m_pDataSource = dynamic_cast<MB_AbsolvedInterface*>(pDataSource);
	if (m_pDataSource)
	{
		return true;
	}
	return false;
}
void MB_AbsolvedEntranceWnd::onResetWnd()
{
	MB_NodeCommandEntrance::onResetWnd();
}
void MB_AbsolvedEntranceWnd::onMsgRecv(CCNode* node, SocketResponse* response)
{
	assert(response != NULL);

	//將socket數据读取到序列化結构
	MB_MsgBuffer* recvPacket = response->getResponseData();

	//协议號
	uint16_t Msg = 0;
	recvPacket->Reset();
	recvPacket->skipU16();
	recvPacket->skipU8();
	recvPacket->readU16(&Msg);

	switch (Msg)
	{
	case SC_ROLE_UPDATE_LEVEL:
	case SC_ROLE_BUY_ENERGY:
	case SC_ROLE_UPDATE_ENERGY:
		this->onResetWnd();
		break;
	default:
		break;
	}
}

void MB_AbsolvedEntranceWnd::onEntranceClicked(CCObject* pSender)
{
    if (m_bIsCanToChapter) {
        m_bIsCanToChapter = false;
        float winWidth = CCDirector::sharedDirector()->getWinSize().width;
        sceneNode = CCDirector::sharedDirector()->getRunningScene();
        sceneNode->runAction(CCSequence::create(CCMoveTo::create(fabsf(-winWidth - sceneNode->getPositionX()) / MOVESCENESPEED, ccp(-winWidth, 0)), CCCallFunc::create(this, callfunc_selector(MB_AbsolvedEntranceWnd::finish2)), NULL));
    }
}
void MB_AbsolvedEntranceWnd::finish2()
{
	NSGameFunction::CCFunctionInterface* pInterface = NULL;
	MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface);
	if (pInterface)
	{
		MB_AbsolvedInterface* pInstance = (MB_AbsolvedInterface*)pInterface;
		MB_ChapterProgress* pProgress = pInstance->getChapterProgressByType(pInstance->getCurrentType());
		MB_ChapterPage* pPage = NULL;
		MB_AbsolvedConfigure::getInstance()->queryPageByTypeAndChapterId(pInstance->getCurrentType(), pProgress->getChapterId(), &pPage);
		m_bToPageID = pPage->getPageId();
		m_bNowPassPageID = pPage->getPageId();
		pInterface->onEntryClicked(this);
	}
	float winWidth = CCDirector::sharedDirector()->getWinSize().width;
	sceneNode->setPositionX(winWidth);
	sceneNode->runAction(CCSequence::create(CCMoveTo::create((winWidth) / MOVESCENESPEED, ccp(0, 0)), NULL));
    m_bIsCanToChapter = true;
}
