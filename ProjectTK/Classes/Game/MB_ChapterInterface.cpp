//
//  MB_ChapterInterface.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-16.
//
//

#include "MB_ChapterInterface.h"
#include "MB_NodeChapterEntry.h"
#include "MB_LayerChapterWnd.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_ChapterData.h"
#include "MB_AbsolvedInterface.h"
#include "MB_ServerRewardData.h"
#include "MB_GlobelModalDlgMsgQueue.h"

MB_ChapterInterface::MB_ChapterInterface()
{
    m_nType = 0;
    m_nChapterId = 0;
    m_nPageId = 0;
    m_pBattleInfo = NULL;
}

MB_ChapterInterface::~MB_ChapterInterface()
{
    m_nType = 0;
    m_nChapterId = 0;
    m_nPageId = 0;
    CC_SAFE_RELEASE_NULL(m_pBattleInfo);
}

MB_ResWindow* MB_ChapterInterface::createEntryDialog()
{
    MB_NodeChapterEntry* pInstance = new MB_NodeChapterEntry;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}

MB_ResWindow* MB_ChapterInterface::createFunctionDialog()
{
    MB_LayerChapterWnd* pInstance = new MB_LayerChapterWnd;
    if (pInstance && pInstance->setDataSource(this) && pInstance->init())
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}
bool MB_ChapterInterface::hasRequestedData()
{
    return m_pBattleInfo != NULL;
}
void MB_ChapterInterface::onLoadingScene()
{
    
}

bool MB_ChapterInterface::allowShow()
{
    return true;
}

MB_ChapterProgress* MB_ChapterInterface::getChapterProgress()
{
    CCFunctionInterface* pAbsolvedInterface = NULL;
    MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pAbsolvedInterface);
    if (pAbsolvedInterface)
    {
        MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(pAbsolvedInterface);
        if (pAbsolved)
        {
            return pAbsolved->getChapterProgressByType(m_nType);
        }
    }
    
    return NULL;
}
/*
 message recvbattle_info[id=10204]{
 required	int8		type			// 1:普通關卡   2:困难關卡  3:最困难關卡
 required	int16		chapterID		=1;//章節ID
 required	bool		perfectRewarded	=2;//是否領取過完美通關獎勵
 repeated	p_dungeon	dungeonInfo		=3;//每个關卡的信息
 }
 */
void MB_ChapterInterface::recvbattle_info(MB_MsgBuffer* recvPacket)
{MB_Message::sharedMB_Message()->removeALLMessage();
    
    SOCKET_MSG_UNREGIST(SC_BATTLE_INFO);
    uint8_t type = 0;
    uint16_t id =0;
    MB_Message::sharedMB_Message()->removeALLMessage();
    recvPacket->readU8(&type);
    if (m_pBattleInfo==NULL)
    {
        m_pBattleInfo = new MB_BattleInfo;
    }
    if (type == m_nType)
    {
        m_pBattleInfo->setType(type);
        recvPacket->readU16(&id);
        m_pBattleInfo->setChapterId(id);
        m_pBattleInfo->updateInfo(recvPacket);
    }

    enterChapter();
}

bool MB_ChapterInterface::enterChapter()
{
    MB_GlobelModalDlgMsgQueue::getInstance()->clearMsg();
    MB_ResWindow* pWnd = createFunctionDialog();
    if (pWnd)
    {
        MB_LayerChapterWnd* p = dynamic_cast<MB_LayerChapterWnd*>(pWnd);
        
        NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(pWnd);
        NSGameFunction::CCFunctionInterface::removeUnusedResource();
        if (p)
        {
            p->goMessageShow();
        }
        return true;
    }
    
    MB_Message::sharedMB_Message()->showMessage("尚未开启该章节");
    return false;
}
void MB_ChapterInterface::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_BATTLE_INFO:
            recvbattle_info(recvPacket);
            break;
        default:
            break;
    }
    
}
MB_ChapterData* MB_ChapterInterface::getChapterData()
{
    MB_ChapterData* pData = NULL;
    
    MB_AbsolvedConfigure::getInstance()->queryChapterData(m_nType,m_nPageId,m_nChapterId,&pData);
    
    return pData;
}
void MB_ChapterInterface::onEntryClicked(CCObject* pSender)
{
    //
    NSGameFunction::CCFunctionInterface* pAdmin = NULL;
    MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pAdmin);
    MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(pAdmin);
    if (pAbsolved)
    {
        MB_ChapterProgress* pProgress = pAbsolved->getChapterProgressByType(m_nType);
        if (pProgress->getChapterId()>=m_nChapterId)
        {
            if (hasRequestedData())
            {
                enterChapter();
                
            }
            else
            {
                MB_Message::sharedMB_Message()->showMessage("",15);
                SOCKET_MSG_REGIST(SC_BATTLE_INFO, MB_ChapterInterface);
                MB_AbsolvedInterface::sendbattle_info(m_nType, m_nChapterId);
                return;
            }
        }
    }
}
int MB_ChapterInterface::getChapterStar()
{
    if (m_pBattleInfo)
    {
        return m_pBattleInfo->getBattleStar();
    }
    return 0;
}
MB_BattleInfo* MB_ChapterInterface::getBattleInfo()
{
    return m_pBattleInfo;
}
MB_ChapterPage* MB_ChapterInterface::getChapterPage()
{
    MB_ChapterPage* pPage = NULL;
    MB_AbsolvedConfigure::getInstance()->queryChapterPage(m_nType, m_nPageId, &pPage);
    return pPage;
}

bool MB_ChapterInterface::complated()
{
    return getChapterProgress()->getChapterId() > getChapterData()->getChapterId();
}
