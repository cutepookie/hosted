

#include "MB_MailMainView.h"
#include "MB_MailData.h"
#include "MB_CommonType.h"
#include "MB_FunctionModule.h"
#include "MB_NodeMailSystem.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_ScrollBg.h"
//---------------------------------------------//
//======    构造|析构
//---------------------------------------------//
MB_MailMainView::MB_MailMainView()
{
    m_pPositionSign     = NULL;
    m_pTableView        = NULL;
    m_currentPage       = kmMailsTable_System;
    m_nLastPage    = 0;
    m_subItemCache.clear();
    m_itemSize.setSize(0.0f, 0.0f);
    m_pRewardArray = new CCArray();
    SOCKET_MSG_REGIST(SC_MAIL_DRAW_REWARD, MB_MailMainView);
    SOCKET_MSG_REGIST(SC_MAIL_UNREAD_NUM,MB_MailMainView);
    SOCKET_MSG_REGIST(SC_MAIL_INFO, MB_MailMainView);
    SOCKET_MSG_REGIST(SC_MAIL_DELETE, MB_MailMainView);
    SOCKET_MSG_REGIST(SC_MAIL_AGREE_FRIEND, MB_MailMainView);
    SOCKET_MSG_REGIST(SC_MAIL_MORE, MB_MailMainView);
    SOCKET_MSG_REGIST(SC_FRIEND_REMOVE_REQUEST, MB_MailMainView);
    
}
bool MB_MailMainView::init(){

    if(MB_ResWindow::init() == false){
        
        return false;
    }
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * node = pCCBReader->readNodeGraphFromFile("res/mail_layer_list.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    node->addChild(MB_ScrollBg::create(left_top,0.5f),-1);
    
    onInitDidFinish();
    return true;
}
MB_MailMainView::~MB_MailMainView()
{
    CC_SAFE_RELEASE_NULL(m_pPositionSign);
    for(int i = 0;i<m_subItemCache.size();++i)
        CC_SAFE_RELEASE_NULL(m_subItemCache[i]);
    CC_SAFE_RELEASE_NULL(m_pRewardArray);
    SOCKET_MSG_UNREGIST(SC_MAIL_DRAW_REWARD);
    SOCKET_MSG_UNREGIST(SC_MAIL_UNREAD_NUM);
    SOCKET_MSG_UNREGIST(SC_MAIL_INFO);
    SOCKET_MSG_UNREGIST(SC_MAIL_DELETE);
    SOCKET_MSG_UNREGIST(SC_MAIL_AGREE_FRIEND);
    SOCKET_MSG_UNREGIST(SC_MAIL_MORE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_REMOVE_REQUEST);
}


bool MB_MailMainView::onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode)
{
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PositionSign", CCNode*, m_pPositionSign);
    return false;
}

SEL_MenuHandler MB_MailMainView::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnClose",MB_MailMainView::OnClose);
    return NULL;
}
SEL_CCControlHandler MB_MailMainView::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){

    return NULL;
}

void MB_MailMainView::onMessage(unsigned int msg, cocos2d::CCObject *param)
{
    dirty();
}

void MB_MailMainView::onInitDidFinish()
{
    m_itemSize = MB_MailSubItem::create()->getUiDesignSize();
    NSGameHelper::adjustScrollNode(m_pPositionSign);
    m_pTableView = CCTableView::create(this, m_pPositionSign->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pPositionSign->addChild(m_pTableView);
    m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
    OnRequestMails();
}


CCSize MB_MailMainView::cellSizeForTable(CCTableView *table)
{
    return m_itemSize;
}

CCTableViewCell* MB_MailMainView::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    if(MailMgr->getMails(m_currentPage).size()>idx)
    {
        MB_MailSubItem *node = generateItemInCache(idx);
        
        node->setPosition(ccp(m_itemSize.width/2.0f,m_itemSize.height/2.0f));
        node->dirty();
        cell->removeAllChildren();
        
        if (node->getParent())
            node->getParent()->removeAllChildren();
        
        cell->addChild(node);
    }
    
    return cell ;
}

unsigned int MB_MailMainView::numberOfCellsInTableView(CCTableView *table)
{
    int num = MailMgr->getMails(m_currentPage).size();
    return  num ;
}

void MB_MailMainView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
}

void MB_MailMainView::scrollViewDidScroll(CCScrollView* view)
{
}

void MB_MailMainView::scrollViewDidZoom(CCScrollView* view)
{
}

//---------------------------------------------//
//======    事件回调
//---------------------------------------------//

//--------------menu----------//
void MB_MailMainView::OnClose(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
    MB_LOG("OnClose");
}

void MB_MailMainView::OnRequestMails()
{
    MailMgr->sendmail_info(m_currentPage);
    dirty();
}

MB_MailSubItem* MB_MailMainView::generateItemInCache(int index)
{
    MB_MailSubItem* ret = NULL;
    bool needNew = true;
    
    int64_t uid;
    uid = MailMgr->getMails(m_currentPage)[index]->mailUID;
    
    for (int i = 0; i<m_subItemCache.size(); ++i)
    {
        if (m_subItemCache[i]->getMailUid() == uid)
        {
            ret = m_subItemCache[i];
            needNew = false;
            break;
        }
    }
    
    if (needNew)
    {
        for (int i = 0; i<m_subItemCache.size(); ++i)
        {
            if (m_subItemCache[i]->getMailUid() == 0)
            {
                ret = m_subItemCache[i];
                ret->setMailUid(uid);
                needNew = false;
                break;
            }
        }
    }
    
    if (needNew)
    {
        ret = MB_MailSubItem::create();
        ret->retain();
        ret->setMailUid(uid);
        m_subItemCache.push_back(ret);
    }
    return ret;
}

void MB_MailMainView::clearCache()
{
    for (int i = 0; i<m_subItemCache.size(); ++i)
        m_subItemCache[i]->setMailUid(0);
}

//---------------------------------------------//
//======    界面刷新
//---------------------------------------------//
void MB_MailMainView::onResetWnd(void)
{
    if(m_pTableView != NULL){
        
        clearCache();
        CCPoint pt;
        if (m_nLastPage == m_currentPage)
        {
            pt = m_pTableView->getContentOffset();
        }
        
        m_pTableView->reloadData();
        
        if (m_nLastPage == m_currentPage)
        {
            CCSize container_size = m_pTableView->getContainer()->getContentSize();
            CCSize node_size = m_pPositionSign->getContentSize();
            if (container_size.height > node_size.height)
            {
                if (pt.y < -container_size.height+node_size.height-1)
                {
                    pt.y = container_size.height-node_size.height;
                }
//                else if (pt.y > 0)
//                {
//                    pt.y = 0;
//                    m_pTableView->setContentOffset(pt);
//                }
//                else
//                {
//                    m_pTableView->setContentOffset(pt);
//                }
            }
        }
        m_nLastPage = m_currentPage;
        //m_pTableView->setContentOffset(m_pTableView->minContainerOffset());
    }
   //to do sth. here.
}

void MB_MailMainView::recvmail_draw_reward(MB_MsgBuffer* pRecv)
{
    uint8_t     data8;
    pRecv->readU8(&data8);
    if(data8 == 1){
        
        if(m_pRewardArray->count() == 0){
            
            dirty();
            
        }else   if(m_pRewardArray->count() == 1){
            
            RewardTempleteValue * reward = (RewardTempleteValue * )m_pRewardArray->objectAtIndex(0);
            MB_LayerRewardOne* layer = MB_LayerRewardOne::create(reward->getType(),reward->getValueID(),reward->getNumber());
            layer->setShareType(kShareTypeMail);
            CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_OUTSHOW);
            dirty();
        }else {
            
            MB_LayerRewardMore* layer = MB_LayerRewardMore::create(m_pRewardArray);
            this->pushWindow(layer);
            dirty();
        }
        

    }
}
void MB_MailMainView::onMsgRecv(CCNode* node, SocketResponse* response){

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
      
        case SC_MAIL_DRAW_REWARD:{
            
            recvmail_draw_reward(recvPacket);
        }
            break;
        case SC_MAIL_UNREAD_NUM:{
            
//            char temp[8];
//            if(MailMgr->queryMailUnRead(kmMailsTable_Preson) > 0){
//                
////                m_pNodeMailPerson->setVisible(true);
//                sprintf(temp,"%d",MailMgr->queryMailUnRead(kmMailsTable_Preson));
//                m_pMailNumPreson->setString(temp);
//                
//            }else {
//                
////                m_pNodeMailPerson->setVisible(false);
//            }
//            if (MailMgr->queryMailUnRead(kmMailsTable_System) >0) {
//                
////                m_pNodeMailSystem->setVisible(true);
//                
//                sprintf(temp,"%d",MailMgr->queryMailUnRead(kmMailsTable_System));
//                m_pMailNumSystem->setString(temp);
//                
//            }else {
            
//                m_pNodeMailSystem->setVisible(false);
//            }
//            if (MailMgr->queryMailUnRead(kmMailsTable_Union) >0) {
//                
//                m_pNodeMailUnion->setVisible(true);
//                sprintf(temp,"%d",MailMgr->queryMailUnRead(kmMailsTable_Union));
//                m_pMailNumUnion->setString(temp);
//                
//            }else {
//                
//                m_pNodeMailUnion->setVisible(false);
//            }
        }
            break;
        case SC_MAIL_INFO:
        case SC_MAIL_DELETE:
        case SC_MAIL_AGREE_FRIEND:
        case SC_MAIL_MORE:
        case SC_FRIEND_REMOVE_REQUEST:
             dirty();
            break;
        default:
            break;
    }
}
