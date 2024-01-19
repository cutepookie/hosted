//
//  MB_LayerChapterRank.cpp
//  ProjectMB
//
//  Created by yuanwugang on 14-9-26.
//
//

#include "MB_LayerChapterRank.h"
#include "MB_NodeChapterRankUint.h"
#include "MB_FunctionMgr.h"
#include "MB_NodeChapterRankUint.h"
#include "MB_ChapterData.h"
#include "MB_RoleData.h"
#include "MB_AbsolvedConfigure.h"
#include "MB_ServerRewardData.h"
#include "MB_AbsolvedInterface.h"
MB_LayerChapterRank::MB_LayerChapterRank()
{
    m_pNodeRankList = NULL;
    m_pTTFRank = NULL;
    m_pTTFChapter = NULL;
    m_pTableView = NULL;
    m_pDataArray = NULL;
    SOCKET_MSG_REGIST(SC_BATTLE_RANK,MB_LayerChapterRank);
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerChapterRank");
}
MB_LayerChapterRank::~MB_LayerChapterRank()
{
    CC_SAFE_RELEASE_NULL(m_pNodeRankList);
    CC_SAFE_RELEASE_NULL(m_pTTFRank);
    CC_SAFE_RELEASE_NULL(m_pTTFChapter);
    CC_SAFE_RELEASE_NULL(m_pTableView);
    CC_SAFE_RELEASE_NULL(m_pDataArray);
    
    SOCKET_MSG_UNREGIST(SC_BATTLE_RANK);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerChapterRank");
}
MB_LayerChapterRank* MB_LayerChapterRank::create()
{
    MB_LayerChapterRank* ptr = new MB_LayerChapterRank();
    if (ptr && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
bool MB_LayerChapterRank::init()
{
    CCNode* pNode = loadResource("res/pve_layer_billboard.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        NSGameFunction::CCFunctionInterface* pInterface = NULL;
        if(MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pInterface))
        {
            MB_AbsolvedInterface* temp = dynamic_cast<MB_AbsolvedInterface*>(pInterface);
            temp->sendbattle_rank();
            m_pDataArray = temp->getRankInfoArray();
            m_pDataArray->retain();
            
            
            MB_ChapterRankData* pData = NULL;
            char strRank[32] = "";
            char strChapter[32] = "";
            bool bInRank = false;
            CCARRAY_FOREACH_4TYPE(m_pDataArray, MB_ChapterRankData*, pData)
            {
                if (pData->getRoleID() == MB_RoleData::getInstance()->getUID())
                {
                    sprintf(strRank,"第%d名",pData->getRank());
                    sprintf(strChapter,"%s",pData->getDungeonName().c_str());
                    bInRank = true;
                }
            }
            
            if (!bInRank)
            {
                sprintf(strRank,"未上榜");
                
                NSGameFunction::CCFunctionInterface* pAdmin = NULL;
                MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pAdmin);
                MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(pAdmin);
                if (pAbsolved)
                {
                    MB_ChapterProgress* pProgress = pAbsolved->getChapterProgressByType(pAbsolved->getCurrentType());
                    if (pProgress != NULL)
                    {
                        MB_ChapterDungeonData* dungeonData = MB_AbsolvedConfigure::getInstance()->getChapterDungeonsID(pProgress->getChapterId());
                        if (dungeonData != NULL)
                        {
                            const MB_DungeonData* data = dungeonData->getDungeonDataByID(pProgress->getDungeonId());
                            if(data != NULL)
                            {
                                sprintf(strChapter,"%s",data->getName());
                            }
                            
                        }
                    }
                }
            }
            m_pTTFRank->setString(strRank);
            m_pTTFChapter->setString(strChapter);
        }
        
        m_CellSize = MB_NodeChapterRankUint::getSize();
        
        
        m_pTableView = CCTableView::create(this, m_pNodeRankList->getContentSize());
        CC_SAFE_RETAIN(m_pTableView);
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pNodeRankList->addChild(m_pTableView);
		return true;
	}
	return false;
}
void MB_LayerChapterRank::onResetWnd()
{
    if (m_pDataArray == NULL)
    {
        return;
    }
    m_pTableView->reloadData();
    
    MB_ChapterRankData* pData = NULL;
    char strRank[32] = "";
    char strChapter[32] = "";
    bool bInRank = false;
    CCARRAY_FOREACH_4TYPE(m_pDataArray, MB_ChapterRankData*, pData)
    {
        if (pData->getRoleID() == MB_RoleData::getInstance()->getUID())
        {
            sprintf(strRank,"第%d名",pData->getRank());
            sprintf(strChapter,"%s",pData->getDungeonName().c_str());
            bInRank = true;
        }
    }
    if (!bInRank)
    {
        sprintf(strRank,"未上榜");
        NSGameFunction::CCFunctionInterface* pAdmin = NULL;
        MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionAbsolved, &pAdmin);
        MB_AbsolvedInterface* pAbsolved = dynamic_cast<MB_AbsolvedInterface*>(pAdmin);
        if (pAbsolved)
        {
            MB_ChapterProgress* pProgress = pAbsolved->getChapterProgressByType(pAbsolved->getCurrentType());
            if (pProgress != NULL)
            {
                MB_ChapterDungeonData* dungeonData = MB_AbsolvedConfigure::getInstance()->getChapterDungeonsID(pProgress->getChapterId());
                if (dungeonData != NULL)
                {
                    const MB_DungeonData* data = dungeonData->getDungeonDataByID(pProgress->getDungeonId());
                    if(data != NULL)
                    {
                        sprintf(strChapter,"%s",data->getName());
                    }
                    
                }
            }
        }
        
    }
    m_pTTFRank->setString(strRank);
    m_pTTFChapter->setString(strChapter);
    
    
}
bool MB_LayerChapterRank::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRankList",CCNode*,m_pNodeRankList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFRank",CCLabelTTF*,m_pTTFRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFChapter",CCLabelTTF*,m_pTTFChapter);

    return false;
}
SEL_MenuHandler MB_LayerChapterRank::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerChapterRank::onCloseClick);
    return NULL;
}
SEL_CCControlHandler MB_LayerChapterRank::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_LayerChapterRank::onCloseClick(CCObject* pSender)
{
    popWindow();
}

void MB_LayerChapterRank::onMsgRecv(CCNode* node, SocketResponse* response)
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
        case SC_BATTLE_RANK:
            onResetWnd();
            break;
        default:
            break;
    }
    
}
CCSize MB_LayerChapterRank::cellSizeForTable(CCTableView *table)
{
    return m_CellSize;
}

CCTableViewCell* MB_LayerChapterRank::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }

   
    MB_ChapterRankData* data = dynamic_cast<MB_ChapterRankData*>(m_pDataArray->objectAtIndex(idx));
    
    if (data != NULL)
    {
        MB_ResWindow* layer = MB_NodeChapterRankUint::create(data);
        cell->addChild(layer);
        layer->setTag(data->getRoleID());
        layer->setPosition(m_CellSize.width/2.0,m_CellSize.height/2.0);
    }
    return cell;
}

unsigned int MB_LayerChapterRank::numberOfCellsInTableView(CCTableView *table)
{
    return m_pDataArray->count();
}


