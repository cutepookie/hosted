
#include "MB_LayerInviteHelp.h"

MB_LayerInviteHelp::MB_LayerInviteHelp(){

    m_pNodeISGet = NULL;
    m_pHasInviteNum = NULL;
    m_pCellSize = NULL;
    m_pNodeInvite1 = NULL;
    m_pNodeInvite2 = NULL;
    m_pFXCode = NULL;
    m_pFXInviter = NULL;
    m_pScrollView = NULL;
    m_pNodeWebChat = NULL;
    m_pIsGet = NULL;
    m_pMessageSend = "";
    
    SOCKET_MSG_REGIST(SC_INVITE_INFO, MB_LayerInviteHelp);
    SOCKET_MSG_REGIST(SC_INVITE_INPUT_INVITE_CODE, MB_LayerInviteHelp);
    SOCKET_MSG_REGIST(SC_INVITE_LIST, MB_LayerInviteHelp);
   
}
MB_LayerInviteHelp::~MB_LayerInviteHelp(){

    CC_SAFE_RELEASE(m_pNodeISGet);
    CC_SAFE_RELEASE(m_pHasInviteNum);
    CC_SAFE_RELEASE(m_pCellSize);
    CC_SAFE_RELEASE(m_pNodeInvite1);
    CC_SAFE_RELEASE(m_pNodeInvite2);
    CC_SAFE_RELEASE(m_pFXCode);
    CC_SAFE_RELEASE(m_pFXInviter);
    CC_SAFE_RELEASE(m_pScrollView);
    CC_SAFE_RELEASE(m_pNodeWebChat);
    CC_SAFE_RELEASE(m_pIsGet);
    

    SOCKET_MSG_UNREGIST(SC_INVITE_INFO);
    SOCKET_MSG_UNREGIST(SC_INVITE_INPUT_INVITE_CODE);
    SOCKET_MSG_UNREGIST(SC_INVITE_LIST);
}
bool MB_LayerInviteHelp::init(){
    
    if(MB_ResWindow::init() == false){
        
        return false;
    }
    
    this->addChild(NSGameHelper::createDisableTouchLayer());
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/gui_invent_help.ccbi", this);
    pCCBReader->release();
    this->addChild(node,1);
    

#ifdef WEBCHATOUT
    if(m_pNodeWebChat)m_pNodeWebChat->setVisible(false);
#else
    
    if(m_pIsGet)
    {
        long lastweixin = MB_RoleData::getInstance()->getLastWeiXinShareSec();
        long timenow = MB_ClientSocket::getInstance()->getServerTime();
        
        if(lastweixin > 0 ){
            
            int lastcount =timenow- lastweixin;
            if( lastcount > (7*24*3600)){
                
                m_pIsGet->setVisible(true);
                
            }else {
                
                struct tm* lastnow = localtime(&lastweixin);
                struct tm* times = localtime(&timenow);
                if (lastnow->tm_mday == 0 && times->tm_mday > 0 ) {
                    
                    m_pIsGet->setVisible(true);
                    
                }else if (lastnow->tm_mday >0 && times->tm_mday < lastnow->tm_mday ) {
                    
                    m_pIsGet->setVisible(true);
                    
                }
                else {
                    
                    m_pIsGet->setString("本周已经分享");
                }
                
            }
            
        }else {
            
            m_pIsGet->setVisible(true);
            
        }

    }
   
#endif
   

    char databuf2[7];
    getSelfCode(databuf2);
    m_pFXCode->setString(databuf2);
    onResetWnd();
    MB_RoleData::getInstance()->sendinvite_info();
    return true;
}
void MB_LayerInviteHelp::onResetWnd(void){

    MB_ResWindow::onResetWnd();
    if (MB_RoleData::getInstance()->getisInputInviteCode()) {
        
        m_pNodeInvite1->setVisible(false);
        m_pNodeInvite2->setVisible(true);
        m_pFXInviter->setString(MB_RoleData::getInstance()->getWhoInviteYou());
        
    }else {
        
        m_pNodeInvite2->setVisible(false);
        m_pNodeInvite1->setVisible(true);
    }
    m_pNodeISGet->setVisible(MB_RoleData::getInstance()->getisInputInviteCode());
    char databuf[50];
    sprintf(databuf, "已邀请好友：%d人",MB_RoleData::getInstance()->getInvireNum());
    m_pHasInviteNum->setString(databuf);
}
MB_LayerInviteHelp * MB_LayerInviteHelp::create(){
    
    MB_LayerInviteHelp *ptr = new MB_LayerInviteHelp();
    if(ptr && ptr->init()){
        
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerInviteHelp::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerInviteHelp::onCloseClicked);
    return NULL;
}
void MB_LayerInviteHelp::onCloseClicked(CCObject *){

//    removeFromParentAndCleanup(true);
    this->popWindow();
}
cocos2d::extension::SEL_CCControlHandler MB_LayerInviteHelp::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWeiBoSendClick",MB_LayerInviteHelp::onWeiBoSendClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onInputCodeClick",MB_LayerInviteHelp::onInputCodeClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onInvateRecordClick",MB_LayerInviteHelp::onInvateRecordClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSMSSendClick",MB_LayerInviteHelp::onSMSSendClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWeiChatClicked", MB_LayerInviteHelp::onWeiChatClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWebChatFriendClick", MB_LayerInviteHelp::onWebChatFriendClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onWebChatGroupClick", MB_LayerInviteHelp::onWebChatGroupClick);
    return NULL;
}
bool MB_LayerInviteHelp::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScrollView", CCNode *, m_pScrollView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cellSize", CCNode *, m_pCellSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeISGet", CCNode *, m_pNodeISGet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pHasInviteNum", CCLabelTTF *,  m_pHasInviteNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeInvite1", CCNode *,m_pNodeInvite1 );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeInvite2", CCNode *,m_pNodeInvite2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFXCode", CCLabelTTF *,m_pFXCode );
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pFXInviter", CCLabelTTF *,m_pFXInviter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeWebChat", CCNode *, m_pNodeWebChat);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pIsGet", CCLabelTTF  *, m_pIsGet);
    
    return false;
}
void MB_LayerInviteHelp::onInputCodeClick(CCObject *){

    MB_Message::sharedMB_Message()->showEditBox("输入邀请码", "点击输入", "确定", this);
}
void MB_LayerInviteHelp::onWeiBoSendClick(CCObject *){

}

void MB_LayerInviteHelp::onSMSSendClick(CCObject *){

//    char databuf[400];
//    sprintf(databuf, WeiboMgr::getInstance()->getRandmessage(0,0),MB_ServerList::getInstance()->getNowServerID(),MB_ServerList::getInstance()->getNowServerName(),m_pFXCode->getString());
//    m_pMessageSend = databuf;
//    WeiboMgr::getInstance()->postSMS(m_pMessageSend.c_str());
}

//微信发好友
void MB_LayerInviteHelp::onWeiChatClicked(cocos2d::CCObject *)
{
//    char databuf[400];
//    sprintf(databuf, WeiboMgr::getInstance()->getRandmessage(0,0),MB_ServerList::getInstance()->getNowServerID(),MB_ServerList::getInstance()->getNowServerName(),m_pFXCode->getString());
//    m_pMessageSend = databuf;
//    MB_WeChatMgr::getInstance()->sendText(m_pMessageSend.c_str(), 0);
}

//微信朋友圈
void MB_LayerInviteHelp::onWeiChatFriendClicked(cocos2d::CCObject *)
{
//    char databuf[400];
//    sprintf(databuf, WeiboMgr::getInstance()->getRandmessage(0,0),MB_ServerList::getInstance()->getNowServerID(),MB_ServerList::getInstance()->getNowServerName(),m_pFXCode->getString());
//    m_pMessageSend = databuf;
//    MB_WeChatMgr::getInstance()->sendText(m_pMessageSend.c_str(), 0);
}

void MB_LayerInviteHelp::onShowMessage(){

//    int type = WeiboMgr::getInstance()->getWeiboType();
//    if(type == WEIBO_TYPE_NO){
//        
//        
//    }else if(type == WEIBO_TYPE_SINA ){
//        
//        WeiboMgr::getInstance()->postWithStringAndImage(m_pMessageSend.c_str(),NULL);
//        
//    }else {
//        
//        WeiboMgr::getInstance()->postWithStringAndImageTC(m_pMessageSend.c_str(),NULL);        
//    }

}
void MB_LayerInviteHelp::onMsgRecv(CCNode* node, SocketResponse* response){

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
            
        case SC_INVITE_INPUT_INVITE_CODE:
            recvinvite_input_invite_code(recvPacket);
            break;
        case SC_INVITE_LIST:
            recvinvite_list(recvPacket);
            break;
        case SC_INVITE_INFO:{
        
            char databuf[50];
            sprintf(databuf, "已邀请好友：%d人",MB_RoleData::getInstance()->getInvireNum());
            m_pHasInviteNum->setString(databuf);
        }
            break;
        default:
            break;
    }
    
}
void MB_LayerInviteHelp::getSelfCode(char *databuf){

    int data = MB_RoleData::getInstance()->getUID();
    databuf[6] = '\0';
    int i = 0;
    for( ; i < 6; i++){
        
        int code = data%36;
        if (code < 10) {
            
            databuf[i] = code +'0';
        }
        else {
            
            databuf[i] = code -10 +'a';
        }
        data = data/36;
        CCLOG("%c %d",databuf[i],data);
        if(data == 0){
            
            break;
        }
    }
    
    if( i != 5 ){
        i++;
        for(int j = i;j < 6; j++){
            
            databuf[j] = 'z';
        }
        
    }
}
void MB_LayerInviteHelp::onInvateRecordClick(CCObject *){

    sendinvite_list();
}
void MB_LayerInviteHelp::setString(const char *codeback){

    sendinvite_input_invite_code(codeback);   

}
bool MB_LayerInviteHelp::sendinvite_input_invite_code(const char *string){

    if(strlen(string) == 0){
        
        MB_Message::sharedMB_Message()->showMessage("输入为空");
        return false;
    }
    if(strcmp(m_pFXCode->getString(), string) == 0){
        
        MB_Message::sharedMB_Message()->showMessage("不能用自己的邀请码");
        return false;
    }
    MB_Message::sharedMB_Message()->showMessage("",6000);
    SOCKET_REQUEST_START(CS_INVITE_INPUT_INVITE_CODE);
    packet->Write(string,strlen(string));
    SOCKET_REQUEST_END(SC_INVITE_INPUT_INVITE_CODE,  MB_LayerInviteHelp::onMsgRecv);
    return  true;
}
bool MB_LayerInviteHelp::recvinvite_input_invite_code(MB_MsgBuffer* recvPacket){

    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t data8;
    recvPacket->readU8(&data8);
    
    if(data8 == 1){
        
        MB_Message::sharedMB_Message()->showMessage("邀请码验证成功");
        MB_RoleData::getInstance()->setisInputInviteCode(true);
        char *str = recvPacket->ReadString();
        MB_RoleData::getInstance()->setWhoInviteYou(str?str:"");
        CC_SAFE_FREE(str);
        dirty();
        
    }else if(data8 == 2){
        
        MB_Message::sharedMB_Message()->showMessage("邀请码格式错误");
        
    }else  if(data8 == 3){
        
        MB_Message::sharedMB_Message()->showMessage("邀请码错误");
        
    }else  if(data8 == 4){
        
        MB_Message::sharedMB_Message()->showMessage("邀请码验证成功");
        dirty();
    }
    return true;

}
bool MB_LayerInviteHelp::sendinvite_list(){
    
    MB_Message::sharedMB_Message()->showMessage("",15);
    SOCKET_REQUEST_START(CS_INVITE_LIST);
    SOCKET_REQUEST_END(SC_INVITE_LIST,  MB_LayerInviteHelp::onMsgRecv);
    return true;

}
bool MB_LayerInviteHelp::recvinvite_list(MB_MsgBuffer *recvPacket){

    MB_Message::sharedMB_Message()->removeALLMessage();
    short length ;
    recvPacket->readU16(&length);
    CCArray * array = new CCArray(length);
    uint8_t data8;
    int data32;
    char *str;
    
    for(int i = 0 ; i < length ;i++){
        
        inviteData *data = new inviteData();
        recvPacket->readU32(&data32);
        data->setRoleID(data32);
        recvPacket->readU8(&data8);
        data->setisMale(data8 == 1);
        recvPacket->readU8(&data8);
        data->setlevel(data8);
        recvPacket->readU8(&data8);
        data->setTitle(data8);
        str = recvPacket->ReadString();
        if(str)data->setRoleName(str);
        CC_SAFE_FREE(str);
        recvPacket->readU8(&data8);
        data->setIspay(data8== 1);
        array->addObject(data);
        data->release();
    }
    MB_RoleData::getInstance()->setInvireNum(length);
    char databuf[50];
    sprintf(databuf, "已邀请好友：%d人",MB_RoleData::getInstance()->getInvireNum());
    m_pHasInviteNum->setString(databuf);
    
    MB_LayerInvite * layer = MB_LayerInvite::create(array);
    this->pushWindow(layer,true);
    layer->_setZOrder(Z_ORDER_OUTSHOW);
    return true;

}
void MB_LayerInviteHelp::onWebChatFriendClick(CCObject *){

//    char databuf[400];
//    sprintf(databuf, WeiboMgr::getInstance()->getRandmessage(0,0),MB_ServerList::getInstance()->getNowServerID(),MB_ServerList::getInstance()->getNowServerName(),m_pFXCode->getString());
//    m_pMessageSend = databuf;
//    MB_WeChatMgr::getInstance()->sendTextAndImage(m_pMessageSend.c_str(), m_pFXCode->getString(), 0);
    

}
void MB_LayerInviteHelp::onWebChatGroupClick(CCObject *){

//    char databuf[400];
//    sprintf(databuf, WeiboMgr::getInstance()->getRandmessage(0,0),MB_ServerList::getInstance()->getNowServerID(),MB_ServerList::getInstance()->getNowServerName(),m_pFXCode->getString());
//    m_pMessageSend = databuf;
//    MB_WeChatMgr::getInstance()->sendTextAndImage(m_pMessageSend.c_str(),m_pFXCode->getString(), 1);
    
    

}
