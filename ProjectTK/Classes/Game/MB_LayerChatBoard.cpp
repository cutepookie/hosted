
#include "MB_LayerChatBoard.h"
#include "MB_LayerChatList.h"
#include "MB_ChatData.h"

#define SEND_REPORT_ROLE    12614
#define RECV_REPORT_ROLE    12615
MB_LayerChatBoard::MB_LayerChatBoard(){

    m_pRoleName = NULL;
    SOCKET_MSG_REGIST(RECV_REPORT_ROLE, MB_LayerChatBoard);
}
MB_LayerChatBoard::~MB_LayerChatBoard(){

    SOCKET_MSG_UNREGIST(RECV_REPORT_ROLE);
    CC_SAFE_RELEASE(m_pRoleName);
}
bool MB_LayerChatBoard::init(const char *roleName,uint32_t roleID){

    MB_ResWindow::init();
    m_strRoleName = roleName;
    m_nRoleId = roleID;
    MB_MessageBox3 *message= MB_MessageBox3::create();
    message->setTouchPriority(0);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    message->removeAllChildrenWithCleanup(true);
    message->setTouchEnabled(true);
    message->setPosition( ccp(winSize.width/2.0f,winSize.height *0.5));
    this->addChild(message);
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode * m_pNodeSize = pCCBReader->readNodeGraphFromFile("res/chat_layer_function.ccbi", this);
    pCCBReader->release();
    this->addChild(m_pNodeSize);
    
    m_pRoleName->setString(roleName);
    return true;
}
MB_LayerChatBoard * MB_LayerChatBoard::create(const char *roleName,uint32_t roleID){

    MB_LayerChatBoard* ptr = new MB_LayerChatBoard();
    if (ptr && ptr->init(roleName , roleID)) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerChatBoard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerChatBoard::onCloseClick);
    return  NULL;
}


cocos2d::extension::SEL_CCControlHandler MB_LayerChatBoard::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMailClick", MB_LayerChatBoard::onMailClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAddFriendClick",MB_LayerChatBoard::onAddFriendClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCompareClick",MB_LayerChatBoard::onCompareClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGagClick",MB_LayerChatBoard::onGagClick);
    return  NULL;
}
bool MB_LayerChatBoard::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleName", CCLabelTTF *, m_pRoleName);
    return false;
}

// 已经改成举报功能
void MB_LayerChatBoard::onMailClick(CCObject *)
{    
    if (!MB_ChatDataMgr::getInstance()->getTellServer())
    {
        MB_Message::sharedMB_Message()->showMessage("提示","举报次数过于频繁，请稍后再试","确定");
    }
    else
    {
        MB_Message::sharedMB_Message()->showMessage("提示", "举报功能使用于以下用途：非法言论,恶意刷屏,乱发广告,色情信息,欺诈信息等.请勿恶意举报!", "确定","取消",this,menu_selector(MB_LayerChatBoard::tellServer),NULL,NULL);
    }
}

void MB_LayerChatBoard::onMsgRecv(CCNode* node, SocketResponse* response)
{
    MB_MsgBuffer* pRecv = response->getResponseData();
    //协议号
    uint16_t Msg = 0;
    pRecv->Reset();
    pRecv->skipU16();
    pRecv->skipU8();
    pRecv->readU16(&Msg);
    
    if (Msg == RECV_REPORT_ROLE)
    {
        MB_Message::sharedMB_Message()->removeALLMessage();
        uint8_t result = 0;
        pRecv->readU8(&result);
    
        if (result == 0)
        {
            MB_Message::sharedMB_Message()->showMessage("举报成功");
        }
        else if(result == 1)
        {
            MB_Message::sharedMB_Message()->showMessage("举报过于频繁，请稍后再试");
        }
        else if(result == 2)
        {
            MB_Message::sharedMB_Message()->showMessage("角色不存在");
        }
        onCloseClick(NULL);
    }
}
void MB_LayerChatBoard::tellServer(CCObject* pSender)
{
    SOCKET_REQUEST_START(SEND_REPORT_ROLE);
    packet->writeU32(m_nRoleId);
    SOCKET_REQUEST_END(RECV_REPORT_ROLE, NULL);
}
void MB_LayerChatBoard::onAddFriendClick(CCObject *)
{
    MB_Message::sharedMB_Message()->showMessage("",15);
    uint32_t uid[10] = {0};
    uid[0] = m_nRoleId;
    if(m_nRoleId == MB_RoleData::getInstance()->getUID())
    {
        MB_Message::sharedMB_Message()->showMessage("不能添加自己");
        onCloseClick(NULL);
        return;
    }
    MB_FriendMgr::getInstance()->sendfriend_add(1,uid);
    
    onCloseClick(NULL);
}
void MB_LayerChatBoard::onCompareClick(CCObject *)
{
    MB_TARGET_PARENT(MB_LayerChatList, ptr);
    if(ptr)
    {
        ptr->sendpet_view_other_dtl(m_nRoleId, 0);
    }
    onCloseClick(NULL);
//    MB_TeamData::getInstance()->sendpet_view_other(m_nRoleId,0);
}
void MB_LayerChatBoard::onGagClick(CCObject *)
{
    MB_Message::sharedMB_Message()->showMessage("提示", "屏蔽后，您不会再看到对方的聊天信息，重新登录后可以自动解除屏蔽", "确定", "取消",this, menu_selector(MB_LayerChatBoard::throwIntoBlackOder),NULL,NULL);
}

void MB_LayerChatBoard::throwIntoBlackOder(CCObject* pSender)
{
    MB_ChatDataMgr::getInstance()->throwIntoBlackOder(m_nRoleId);
    onCloseClick(NULL);
}
void MB_LayerChatBoard::onCloseClick(CCObject *)
{
    this->removeFromParent();
}