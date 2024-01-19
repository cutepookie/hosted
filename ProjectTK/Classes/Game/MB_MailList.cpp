
#include "MB_MailList.h"
#include "MB_MailData.h"
#include "MB_MailReportSubItem.h"
//---------------------------------------------//
//======    构造|析构
//---------------------------------------------//
MB_MailList::MB_MailList()
{
    m_playout     = NULL;
    m_pTableView  = NULL;
//    m_pSelectMore = NULL;
    m_currentTable = kmMailsTable_Num;
    m_itemSize.setSize(0,0);
    SOCKET_MSG_REGIST(SC_HIST_GET_LIST,MB_MailList);
    SOCKET_MSG_REGIST(SC_HIST_MORE,MB_MailList);
}

MB_MailList::~MB_MailList()
{
    CC_SAFE_RELEASE(m_playout);
    CC_SAFE_RELEASE(m_pTableView);
//    CC_SAFE_RELEASE(m_pSelectMore);
    SOCKET_MSG_UNREGIST(SC_HIST_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_HIST_MORE);
//    for(int i = 0;i<m_subItemCache.size();++i)
//        CC_SAFE_RELEASE(m_subItemCache[i]);
    

}

bool MB_MailList::init()
{
    MB_ResWindow::init();
    
    CCNode* pNode = loadResource("res/pvp_node_list.ccbi");
    this->addChild(pNode);
    
    onInitDidFinish();
    
    return true;
}



void MB_MailList::onInitDidFinish(void)
{
    m_itemSize = MB_MailReportSubItem::create()->getUiDesignSize();

    m_pTableView = CCTableView::create(this, CCSizeMake(m_playout->getContentSize().width,
                                                        m_playout->getContentSize().height));
    m_pTableView->retain();
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_playout->addChild(m_pTableView);
    m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
}
void MB_MailList::setScrollSize(const CCSize& sz)
{
    if (m_pTableView)
    {
        m_pTableView->setViewSize(sz);
        m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
    }
}
void MB_MailList::onMessage(unsigned int msg ,cocos2d::CCObject* param)
{
    dirty();
}

void MB_MailList::setCurrentTable(kmMailsTable var)
{
    m_currentTable = var;
    dirty();
}

kmMailsTable MB_MailList::getCurrentTable()
{
    return m_currentTable;
}

CCSize MB_MailList::cellSizeForTable(CCTableView *table)
{
    return m_itemSize;
}

CCTableViewCell* MB_MailList::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    if(MailMgr->getMails(m_currentTable).size()>idx)
    {
        int64_t uid = MailMgr->getMails(m_currentTable)[idx]->mailUID;
        
        MB_MailReportSubItem* node = MB_MailReportSubItem::create();
        node->setPosition(ccp(m_itemSize.width/2.0f,m_itemSize.height/2.0f-15));
        node->setMailUid(uid);
        node->dirty();
        cell->addChild(node);
    }

    return cell ;
}

unsigned int MB_MailList::numberOfCellsInTableView(CCTableView *table)
{
    return MailMgr->getMails(m_currentTable).size();
}

void MB_MailList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
}

void MB_MailList::scrollViewDidScroll(CCScrollView* view)
{
}

void MB_MailList::scrollViewDidZoom(CCScrollView* view)
{
}

bool MB_MailList::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "layout", CCNode*, m_playout);
    return false;
}


void MB_MailList::onResetWnd(void)
{
//    clearCache();
    m_pTableView->reloadData();
    m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
   //to do sth. here.
}
void MB_MailList::onMsgRecv(cocos2d::CCNode *node, cocos2d::extension::SocketResponse *response)
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
        case SC_HIST_GET_LIST:{
        
            dirty();
            break;
        }
        case SC_HIST_MORE:{

            uint8_t data8;
            uint16_t data16;
            recvPacket->readU8(&data8);
            recvPacket->readU8(&data8);
            recvPacket->readU16(&data16);
            if(data16 == 0)
            {
                MB_Message::sharedMB_Message()->showMessage("没有更多内容了");
            }
            else
            {
                dirty();
            }
            
            break;
        }
            break;
        default:
            break;
    };
}
