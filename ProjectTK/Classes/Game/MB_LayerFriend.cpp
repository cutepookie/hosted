//
//  MB_LayerFriend.cpp
//  ProjectPM
//
//  Create by WenYong on 11/5/2014.
//
//
#include "MB_LayerFriend.h"
#include "MB_FriendDataSource.h"
#include "MB_FunctionModule.h"
#include "MB_FriendDataSyncUpdate.h"
#include "MB_LayerChatMain.h"
#include "MB_ScrollBg.h"
bool isFriendOpen = false;
MB_LayerFriend* MB_LayerFriend::create(bool bChat)
{
    
    MB_LayerFriend* ptr = new MB_LayerFriend();
    if (ptr && ptr->init(bChat))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_RELEASE_NULL(ptr);
    return NULL;
}
MB_LayerFriend::MB_LayerFriend()
{
    isFriendOpen = true;
    btFriend	 = NULL;
    btAddList	 = NULL;
    btGetEnergy	 = NULL;
    btMessage	 = NULL;
    btFight = NULL;
    Node_GetTimes	 = NULL;
    getEnergyTimes	 = NULL;
    NodeAddFriend	 = NULL;
    Account	 = NULL;
    NodeFriendCount	 = NULL;
    ItemCount	 = NULL;
    m_pNodeChangeFriend	 = NULL;
    NodeReceive	 = NULL;
    LastTimes	 = NULL;
    m_pBtGetAllEnergy	 = NULL;
    m_pBtSendAllEnergy = NULL;
    m_pContainer	 = NULL;
    m_pNodeAddSize = NULL;
    m_nTablePage = kFriendTableNormal;
    m_bLastResetPage = kFriendTableCount;
    m_bShowRoleInfoPanel = false;
    m_bShowHomeButton = true;
    m_pNodeFight = NULL;
    m_pTTFFIghtNum = NULL;
    for (int i=0; i<kFriendTableCount; ++i)
    {
        m_pDataSource[i] = NULL;
    }
    
    m_bIsChat = false;
    m_pNodeMsgCount = NULL;
    m_pTTFMsgCount = NULL;
    SOCKET_MSG_REGIST(SC_FRIEND_GET_LIST, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_DELETE, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_NOTIFY_DELETE, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_NEW, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_SEND_ENERGY, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_GIVE_ENERGY_ME, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_ADD, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_EXPLORE, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_GET_ADD_LIST, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_SEND_ENERGY_ME, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_HOMESTEAD_SYNC_MATING_COOL_SECOND, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_HOMESTEAD_SYNC_GER, MB_LayerFriend);
    
    SOCKET_MSG_REGIST(SC_FRIEND_ADD_LIST, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_NEW_ADD, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_AGREE, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_REFUSE, MB_LayerFriend);
    SOCKET_MSG_REGIST(SC_FRIEND_FIGHT,MB_LayerFriend);
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerFriend",true);
    
}
MB_LayerFriend::~MB_LayerFriend()
{
    isFriendOpen = false;
    CC_SAFE_RELEASE_NULL(btFriend);
    CC_SAFE_RELEASE_NULL(btAddList);
    CC_SAFE_RELEASE_NULL(btGetEnergy);
    CC_SAFE_RELEASE_NULL(btMessage);
    CC_SAFE_RELEASE_NULL(btFight);
    CC_SAFE_RELEASE_NULL(Node_GetTimes);
    CC_SAFE_RELEASE_NULL(getEnergyTimes);
    CC_SAFE_RELEASE_NULL(NodeAddFriend);
    CC_SAFE_RELEASE_NULL(Account);
    CC_SAFE_RELEASE_NULL(NodeFriendCount);
    CC_SAFE_RELEASE_NULL(ItemCount);
    CC_SAFE_RELEASE_NULL(m_pNodeChangeFriend);
    CC_SAFE_RELEASE_NULL(NodeReceive);
    CC_SAFE_RELEASE_NULL(LastTimes);
    CC_SAFE_RELEASE_NULL(m_pBtGetAllEnergy);
    CC_SAFE_RELEASE_NULL(m_pBtSendAllEnergy);
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pNodeMsgCount);
    CC_SAFE_RELEASE_NULL(m_pTTFMsgCount);
    CC_SAFE_RELEASE_NULL(m_pNodeAddSize);
    CC_SAFE_RELEASE_NULL(m_pNodeFight);
    CC_SAFE_RELEASE_NULL(m_pTTFFIghtNum);

    for (int i=0; i<kFriendTableCount; ++i)
    {
        CC_SAFE_DELETE(m_pDataSource[i]);
    }
    
    SOCKET_MSG_UNREGIST(SC_FRIEND_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_DELETE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NOTIFY_DELETE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NEW);
    SOCKET_MSG_UNREGIST(SC_FRIEND_SEND_ENERGY);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GIVE_ENERGY_ME);
    SOCKET_MSG_UNREGIST(SC_FRIEND_ADD);
    SOCKET_MSG_UNREGIST(SC_FRIEND_EXPLORE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_GET_ADD_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_SEND_ENERGY_ME);
    SOCKET_MSG_UNREGIST(SC_HOMESTEAD_SYNC_MATING_COOL_SECOND);
    SOCKET_MSG_UNREGIST(SC_HOMESTEAD_SYNC_GER);
    SOCKET_MSG_UNREGIST(SC_FRIEND_ADD_LIST);
    SOCKET_MSG_UNREGIST(SC_FRIEND_NEW_ADD);
    SOCKET_MSG_UNREGIST(SC_FRIEND_AGREE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_REFUSE);
    SOCKET_MSG_UNREGIST(SC_FRIEND_FIGHT);
    CCUserDefault::sharedUserDefault()->setBoolForKey("MB_LayerFriend",false);
}
bool MB_LayerFriend::init(bool bChat)
{
    CCNode* pNode = loadResource("res/friend_layer_list.ccbi");
    if(pNode)
	{
		addChild(pNode);
        NSGameHelper::adjustScrollNode(m_pContainer);
        iniDataSource();
        if(MB_FriendMgr::getInstance()->sendfriend_get_list(1))
        {
            MB_Message::sharedMB_Message()->showMessage("获取好友列表...", 60);
        }
        m_bIsChat = bChat;
        if (MB_FriendMgr::getInstance()->getFriendMsgArray()->count() > 0 && !bChat)
        {
            onMessageClicked(NULL);
        }
        else
        {
            onFriendClicked(this);
        }
        
        
        btFriend->setIsScale(false);
        btAddList->setIsScale(false);
        btGetEnergy->setIsScale(false);
        btFight->setIsScale(false);
        btMessage->setIsScale(false);
        
        
        Account->setFontColor(ccWHITE);
        Account->setFont("", 20);
        Account->setInputMode(kEditBoxInputModeAny);
        addChild(MB_ScrollBg::create(left_top,.5f,1),-1);
		return true;
	}
	return false;
}
void MB_LayerFriend::onResetWnd()
{
    updateTableMenu();
    updateUI();
    m_pDataSource[m_nTablePage]->preReloadData();
    
    
    CCPoint pt;
    if (m_bLastResetPage == m_nTablePage)
    {
        pt = m_pNodeView->getContentOffset();
    }
    
    m_pNodeView->reloadData();
    
    if (m_bLastResetPage == m_nTablePage)
    {
        CCSize container_size = m_pNodeView->getContainer()->getContentSize();
        CCSize node_size = m_pContainer->getContentSize();
        if (container_size.height > node_size.height)
        {
            if (pt.y < -container_size.height+node_size.height-1)
            {
                pt.y = container_size.height-node_size.height;
            }
            else if (pt.y > 0)
            {
                pt.y = 0;
                m_pNodeView->setContentOffset(pt);
            }
            else
            {
                m_pNodeView->setContentOffset(pt);
            }

        }
    }
    m_bLastResetPage = m_nTablePage;
}

void MB_LayerFriend::updateTableMenu()
{
    btFriend->setEnabled(m_nTablePage!=kFriendTableNormal);
    btAddList->setEnabled(m_nTablePage!=kFriendTableAdd);
    btGetEnergy->setEnabled(m_nTablePage!=kFriendTableEnergy);
    btMessage->setEnabled(m_nTablePage!=kFriendTableMessage);
    btFight->setEnabled(m_nTablePage!=kFriendTableFight);
}
bool MB_LayerFriend::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btFriend",CCMenuItemImage*,btFriend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btAddList",CCMenuItemImage*,btAddList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btGetEnergy",CCMenuItemImage*,btGetEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btFight",CCMenuItemImage*,btFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"btMessage",CCMenuItemImage*,btMessage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"Node_GetTimes",CCNode*,Node_GetTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"getEnergyTimes",CCLabelBMFont*,getEnergyTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"NodeAddFriend",CCNode*,NodeAddFriend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"Account",CCEditBox*,Account);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"NodeFriendCount",CCNode*,NodeFriendCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"ItemCount",CCLabelBMFont*,ItemCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeChangeFriend",CCNode*,m_pNodeChangeFriend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"NodeReceive",CCNode*,NodeReceive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"LastTimes",CCLabelTTF*,LastTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtGetAllEnergy",CCControlButton*,m_pBtGetAllEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtSendAllEnergy",CCControlButton*,m_pBtSendAllEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pContainer",CCNode*,m_pContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeMsgCount",CCNode*,m_pNodeMsgCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFMsgCount",CCLabelBMFont*,m_pTTFMsgCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeAddSize", CCNode*,m_pNodeAddSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeFight", CCNode*,m_pNodeFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFFIghtNum", CCLabelBMFont*,m_pTTFFIghtNum);
    
	return false;
}
SEL_MenuHandler MB_LayerFriend::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFriendClicked",MB_LayerFriend::onFriendClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onAddListClicked",MB_LayerFriend::onAddListClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onEnergyClicked",MB_LayerFriend::onEnergyClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFightClicked",MB_LayerFriend::onFightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onMessageClicked",MB_LayerFriend::onMessageClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onSearchClicked",MB_LayerFriend::onSearchClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerFriend::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerFriend::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onGiveMoreFriendClicked",MB_LayerFriend::onGiveMoreFriendClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onGetAllEnergyClicked",MB_LayerFriend::onGetAllEnergyClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onSendAllEnergyClicked",MB_LayerFriend::onSendAllEnergyClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onAutoAddClicked",MB_LayerFriend::onAutoAddClicked);
    
    
	return NULL;
}

void MB_LayerFriend::onFriendClicked(CCObject* pSender)
{
    updateViewContainer(m_nTablePage,kFriendTableNormal);
    
    m_nTablePage = kFriendTableNormal;
    
    m_pNodeView->setDataSource(m_pDataSource[m_nTablePage]);
    m_pDataSource[m_nTablePage]->setTablePage(m_nTablePage);
    onResetWnd();
}

void MB_LayerFriend::onAddListClicked(CCObject* pSender)
{
    updateViewContainer(m_nTablePage,kFriendTableAdd);
    
    m_nTablePage = kFriendTableAdd;
    
    m_pNodeView->setDataSource(m_pDataSource[m_nTablePage]);
    m_pDataSource[m_nTablePage]->setTablePage(m_nTablePage);
    MB_FriendMgr::getInstance()->sendfriend_get_add_list();
    MB_Message::sharedMB_Message()->showMessage("",15);
    onResetWnd();
}


void MB_LayerFriend::onFightClicked(CCObject* pSender)
{
    updateViewContainer(m_nTablePage,kFriendTableFight);
    
    m_nTablePage = kFriendTableFight;
    
    m_pNodeView->setDataSource(m_pDataSource[m_nTablePage]);
    m_pDataSource[m_nTablePage]->setTablePage(m_nTablePage);
    onResetWnd();
}

void MB_LayerFriend::onEnergyClicked(CCObject* pSender)
{
    updateViewContainer(m_nTablePage,kFriendTableEnergy);
    
    m_nTablePage = kFriendTableEnergy;
    
    m_pNodeView->setDataSource(m_pDataSource[m_nTablePage]);
    m_pDataSource[m_nTablePage]->setTablePage(m_nTablePage);
    onResetWnd();
}

void MB_LayerFriend::onMessageClicked(CCObject* pSender)
{
    updateViewContainer(m_nTablePage,kFriendTableMessage);
    
    m_nTablePage = kFriendTableMessage;
    
    m_pNodeView->setDataSource(m_pDataSource[m_nTablePage]);
    m_pDataSource[m_nTablePage]->setTablePage(m_nTablePage);
    
    onResetWnd();
}
bool MB_LayerFriend::iniDataSource()
{
    CC_SAFE_DELETE(m_pDataSource[kFriendTableNormal]);
    CC_SAFE_DELETE(m_pDataSource[kFriendTableAdd]);
    CC_SAFE_DELETE(m_pDataSource[kFriendTableEnergy]);
    CC_SAFE_DELETE(m_pDataSource[kFriendTableMessage]);
    
    m_pDataSource[kFriendTableNormal]   = new MB_OwenFriendDataSource;
    m_pDataSource[kFriendTableAdd]      = new MB_AddFriendDataSource;
    m_pDataSource[kFriendTableEnergy]   = new MB_RPSFriendDataSource;
    m_pDataSource[kFriendTableMessage]      = new MB_MsgFriendDataSource;
    m_pDataSource[kFriendTableFight]      = new MB_FightFriendDataSource;
    
    m_pDataSource[kFriendTableNormal]->setIsMail(m_bIsChat);
    m_pDataSource[kFriendTableAdd]->setIsMail(m_bIsChat);
    m_pDataSource[kFriendTableEnergy]->setIsMail(m_bIsChat);
    m_pDataSource[kFriendTableMessage]->setIsMail(m_bIsChat);
    m_pDataSource[kFriendTableFight]->setIsMail(m_bIsChat);
    
    m_pContainer->removeAllChildren();
    m_pNodeView = CCTableView::create(m_pDataSource[m_nTablePage], m_pContainer->getContentSize());
    m_pNodeView->setDirection(kCCScrollViewDirectionVertical);
    m_pContainer->addChild(m_pNodeView);

    return true;
}
void MB_LayerFriend::onSearchClicked(CCObject* pSender)
{
    std::string roleName = Account->getText();
    if (roleName.length() > 0)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_explore(roleName);
    }
}

void MB_LayerFriend::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}

void MB_LayerFriend::onGiveMoreFriendClicked(CCObject* pSender)
{
    MB_FriendMgr::getInstance()->sendfriend_get_add_list();
    MB_Message::sharedMB_Message()->showMessage("",15);
}

void MB_LayerFriend::onGetAllEnergyClicked(CCObject* pSender)
{
    if(MB_RoleData::getInstance()->getEnergyMax() <= MB_RoleData::getInstance()->getEnergy())
    {
        MB_Message::sharedMB_Message()->showMessage("体力已满, 无法领取");
        return;
    }
    
    MB_Message::sharedMB_Message()->showMessage("提示", "确定全部领取并回赠好友吗?", "确定","取消",this,menu_selector(MB_LayerFriend::onReceiveAllEnergy),NULL);
}

void MB_LayerFriend::onSendAllEnergyClicked(CCObject* pSender) //一键赠送
{
    CCArray* pArray = MB_FriendMgr::getInstance()->getFriendArray();
    MB_DataFriend*  pData = NULL;
    if (pArray->count()>0)
    {
        uint32_t list[500];
        int count = 0;
        CCARRAY_FOREACH_4TYPE(pArray, MB_DataFriend*, pData)
        {
            if (pData == NULL)
            {
                continue;
            }
            if (pData->getCanSendEnergy() != 1)
            {
                continue;
            }
            list[count] = pData->getRoleID();
            pData->setCanSendEnergy(2);
            ++count;
            
        }
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_send_energy(count,list);
        
    }
}

void MB_LayerFriend::onReceiveAllEnergy(CCObject *pSender)
{
    MB_Message::sharedMB_Message()->showMessage("", 15);
    MB_FriendMgr::getInstance()->sendfriend_give_all_enargy();
}

void MB_LayerFriend::onAutoAddClicked(CCObject* pSender)//一键添加
{
    //好友人数检查
//    int nMaxFriend = 0;
//    CCArray* array = MB_RoleData::getInstance()->getVipConfigArray();
//    MB_VipConfig* pTempData = NULL;
//    CCARRAY_FOREACH_4TYPE(array, MB_VipConfig*, pTempData)
//    {
//        if (pTempData->getlevel() == MB_RoleData::getInstance()->getVipLevel())
//        {
//            nMaxFriend = pTempData->getMaxFriendNum();
//        }
//    }
    if (MB_FriendMgr::getInstance()->getFriendArray()->count() >= 100) {
        MB_Message::sharedMB_Message()->showMessage("好友数量已达到上限");
        return;
    }
    
    
    CCArray* pArray = MB_FriendMgr::getInstance()->getExploreArray();
    MB_DataFriend*  pData = NULL;
    if (pArray->count()>0)
    {        
        uint32_t list[500];
        int count = 0;
        CCARRAY_FOREACH_4TYPE(pArray, MB_DataFriend*, pData)
        {
            if (pData == NULL)
            {
                continue;
            }
            if (MB_RoleData::getInstance()->getUID() == pData->getRoleID())
            {
                continue;
            }
            if(pData->getCanAdd() != 1 )
            {
                continue;
            }
            list[count] = pData->getRoleID();
            pData->setCanAdd(0);
            ++count;
        }
        if (count == 0)
        {
            return;
        }
        MB_Message::sharedMB_Message()->showMessage("",15);
        MB_FriendMgr::getInstance()->sendfriend_add(count,list);

    }
}

void MB_LayerFriend::updateViewContainer(int nLastPage,int nNowPage)
{
    if (nLastPage == nNowPage)
    {
        return;
    }
    
    if (nNowPage != kFriendTableAdd && nLastPage != kFriendTableAdd)
    {
        return;
    }
    
    if (nNowPage == kFriendTableAdd && nLastPage != kFriendTableAdd)
    {
        CCSize sz = m_pContainer->getContentSize();
        sz.height -= m_pNodeAddSize->getContentSize().height;
        m_pContainer->setContentSize(sz);
        m_pNodeView->setViewSize(sz);
        CCPoint pt = m_pContainer->getPosition();
        pt.y -= m_pNodeAddSize->getContentSize().height;
        m_pContainer->setPosition(pt);
    }
    
    if (nNowPage != kFriendTableAdd && nLastPage == kFriendTableAdd)
    {
        CCSize sz = m_pContainer->getContentSize();
        sz.height += m_pNodeAddSize->getContentSize().height;
        m_pContainer->setContentSize(sz);
        m_pNodeView->setViewSize(sz);
        CCPoint pt = m_pContainer->getPosition();
        pt.y += m_pNodeAddSize->getContentSize().height;
        m_pContainer->setPosition(pt);
        
    }
}

void MB_LayerFriend::updateUI()
{
    CCArray* pArray = MB_FriendMgr::getInstance()->getFriendArray();
    
    MB_DataFriend* pData = NULL;
    
    int count = 0;
    int SendEnergyCount = 0;
    CCARRAY_FOREACH_4TYPE(pArray, MB_DataFriend*, pData)
    {
        if (pData && pData->getCanGiveEnergy())
        {
            ++count;
        }
        if (pData && pData->getCanSendEnergy() == 1)
        {
            ++SendEnergyCount;
        }
    }
    
    char buf[32] = {};
    if (count!=0)
    {
        sprintf(buf, "%d",count);
        getEnergyTimes->setString(buf);
    }
    Node_GetTimes->setVisible(count!=0);
    int msgCount = MB_FriendMgr::getInstance()->getFriendMsgArray()->count();
    if(m_pNodeMsgCount)m_pNodeMsgCount->setVisible(msgCount!= 0);
    if (msgCount!=0)
    {
        sprintf(buf, "%d",msgCount);
        m_pTTFMsgCount->setString(buf);
    }
    
    NodeAddFriend->setVisible(m_nTablePage==kFriendTableAdd);
    m_pNodeChangeFriend->setVisible(m_nTablePage==kFriendTableAdd);
    NodeReceive->setVisible(m_nTablePage==kFriendTableEnergy);
    
    m_pNodeFight->setVisible(m_nTablePage == kFriendTableFight);
    if (m_nTablePage == kFriendTableFight)
    {
        sprintf(buf,"%d",MB_FriendMgr::getInstance()->getFightTimes());
        m_pTTFFIghtNum->setString(buf);//剩余挑战次数
    }
    
    m_pBtGetAllEnergy->setEnabled(count!=0);
    m_pBtSendAllEnergy->setEnabled(SendEnergyCount != 0);
    
    sprintf(buf, "%d",MB_FriendMgr::getInstance()->getGetEnergyLastTimes());
    LastTimes->setString(buf);
    
    NodeFriendCount->setVisible(m_nTablePage==kFriendTableNormal);
    
//    int nMaxFriend = 0;
//    CCArray* array = MB_RoleData::getInstance()->getVipConfigArray();
//    MB_VipConfig* pTempData = NULL;
//    CCARRAY_FOREACH_4TYPE(array, MB_VipConfig*, pTempData)
//    {
//        if (pTempData->getlevel() == MB_RoleData::getInstance()->getVipLevel())
//        {
//            nMaxFriend = pTempData->getMaxFriendNum();
//        }
//    }
    
    sprintf(buf, "%d",MB_FriendMgr::getInstance()->getFriendArray()->count());
    ItemCount->setString(buf);
}

void MB_LayerFriend::onMsgRecv(CCNode* node, SocketResponse* response)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    assert(response != NULL);
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    switch (Msg) {
        case SC_FRIEND_GET_LIST:
        case SC_FRIEND_NEW:
            if(m_nTablePage == kFriendTableNormal || m_nTablePage==kFriendTableEnergy)
            {
                dirty();
            }
            break;
        case SC_FRIEND_DELETE:
        case SC_FRIEND_NOTIFY_DELETE:
            if(m_nTablePage == kFriendTableNormal)
            {
                dirty();
            }
            break;
        
        case SC_FRIEND_SEND_ENERGY:
        case SC_FRIEND_GIVE_ENERGY:
        case SC_FRIEND_GIVE_ENERGY_ME:
            if(m_nTablePage==kFriendTableEnergy)
            {
                dirty();
            }
            break;
        case SC_FRIEND_EXPLORE:
        case SC_FRIEND_ADD:
        case SC_FRIEND_GET_ADD_LIST:
        case SC_FRIEND_SEND_ENERGY_ME:
            if(m_nTablePage==kFriendTableAdd)
            {
                dirty();
            }
            break;
        case SC_HOMESTEAD_SYNC_MATING_COOL_SECOND:
        case SC_HOMESTEAD_SYNC_GER:
            if (m_nTablePage == kFriendTableNormal)
            {
                uint32_t id = 0;
                recvPacket->readU32(&id);
                int index = m_pDataSource[m_nTablePage]->getIndexByRoleId(id);
                m_pNodeView->updateCellAtIndex(index);
            }
            break;
        case SC_FRIEND_ADD_LIST:
        case SC_FRIEND_NEW_ADD:
        case SC_FRIEND_AGREE:
        case SC_FRIEND_REFUSE:
            if(m_nTablePage==kFriendTableMessage)
            {
                dirty();
            }
            break;
            
        case SC_FRIEND_FIGHT:
            if(m_nTablePage==kFriendTableFight)
            {
                dirty();
            }
            break;
        default:
            break;
    }
}
