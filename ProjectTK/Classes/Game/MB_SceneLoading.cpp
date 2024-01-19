


#include "MB_SceneLoading.h"
#include "MB_LoginNotice.h"
#include "MB_CardStarConfig.h"
#include "MB_BattleConfigData.h"
#include "MB_FunctionConfig.h"
#include "MB_FunctionMgr.h"
#include "MB_TaskConfigure.h"
#include "MB_ChatData.h"
#include "MB_MailData.h"

#include "MB_GuardInterface.h"

#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif

MB_SceneLoading::MB_SceneLoading(){
    m_nGoUpdate = false;
    SOCKET_MSG_REGIST(SC_ACCOUNT_LOGIN, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_VERSION, MB_SceneLoading);
}

MB_SceneLoading::~MB_SceneLoading(){
    
    SOCKET_MSG_UNREGIST(SC_ACCOUNT_LOGIN);
    SOCKET_MSG_UNREGIST(SC_BOX_SHOP_INFO);
    SOCKET_MSG_UNREGIST(SC_PVP_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_BATTLE_PROGRESS);
    SOCKET_MSG_UNREGIST(SC_GER_INFO);
    SOCKET_MSG_UNREGIST(SC_GER_POS_LIST);
    SOCKET_MSG_UNREGIST(SC_EXPLORE_LIST);
    SOCKET_MSG_UNREGIST(SC_ITEM_BAG);
    SOCKET_MSG_UNREGIST(SC_ITEM_EQUIP);
    SOCKET_MSG_UNREGIST(SC_SHOP_BUY_NUM);
    SOCKET_MSG_UNREGIST(SC_SHOP_ENCOUNTER);
    SOCKET_MSG_UNREGIST(SC_PLUNDER_INFO);
    SOCKET_MSG_UNREGIST(SC_DAILY_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_INFO);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_NOTICE);
    //    SOCKET_MSG_UNREGIST(SC_GATHER_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_ROLE_GET_GUIDE_STATE);
    SOCKET_MSG_UNREGIST(SC_VERSION);
    SOCKET_MSG_UNREGIST(SC_EXPLORE_AUTO_EXPLORE_CHECK);
    SOCKET_MSG_UNREGIST(SC_ROLE_LOGIN_REWARD);
    //    SOCKET_MSG_UNREGIST(SC_KING_ENTER);
    //    SOCKET_MSG_UNREGIST(SC_KING_ENTER_WAIT_FIRST_SESSION);
    SOCKET_MSG_UNREGIST(SC_ITEM_USE_INFO);
}

CCScene * MB_SceneLoading::scene(){
    
    CCScene *scene = CCScene::create();
    
    MB_SceneLoading *node = MB_SceneLoading::create();
    
    scene->addChild(node);
    return scene;
    
    
}
bool MB_SceneLoading::init(){
    
    if (CCLayer::init() == false){
        
        return false;
    }
    
    //     CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    //     CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/main_layer_loading.ccbi", this);
    //
    //     CC_SAFE_RELEASE(pCCBReader);
    //
    //     if (pNode)
    //     {
    //         addChild(pNode);
    //     }
    
    CCSize ws = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite * pLoding = CCSprite::create("loading.png");
    
    addChild(pLoding);
    
    pLoding->setPosition(ccp(ws.width*0.5, ws.height *0.5));
    
    clearData();
    
    m_nCount = 0;
    schedule(schedule_selector(MB_SceneLoading::tick), 1.5f);
    
    if (MB_ClientSocket::getInstance()->getCanAutoConnect() > 1)
    {
        initConnect();
    }
    else
    {
        initData();
    }
    
    return true;
}

void MB_SceneLoading::initConnect()
{
    sendversion();
}

void MB_SceneLoading::clearData()
{
    MB_NotificationMgr::purgeData();
    MB_RoleData::destroyInstance();
    MB_PetMgr::destroyInstance();
    MB_ItemMgr::destroyInstance();
    MB_TeamData::destroyInstance();
    MB_ShopMgr::destroyInstance();
    MB_DataPVPMgr::destroyInstance();
    MB_PublicNoticeData::destroyInstance();
    MB_MailData::destroyInstance();
    MB_MoneyEevntMgr::destroyInstance();
    MB_EventMgr::destroyInstance();
    MB_DataShowPic::destroyInstance();
    MB_FriendMgr::destroyInstance();
    MB_ShopMgr::destroyInstance();
    MB_TutorialMgr::destroyInstance();
    MB_ChatDataMgr::destroyInstance();
    MB_CardPropertyMgr::destroyInstance();
    MB_BattleConfigData::destroyInstance();
    MB_SuitEquipmentMgr::destroyInstance();
    MB_ComposeMgr::destroyInstance();
    MB_FunctionConfigure::destroyInstance();
    MB_FunctionMgr::destroyInstance();
    MB_TaskConfigure::destoryInstance();
    MB_GuardInterface::destroyInstance();
}

void MB_SceneLoading::initData()
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    MB_Message::sharedMB_Message()->showMessage("获取数据中...", 600);
    
    
    SOCKET_MSG_REGIST(SC_ROLE_INFO, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_GER_INFO, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_ITEM_BAG, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_ITEM_EQUIP, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_GER_POS_LIST, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_BATTLE_PROGRESS, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_EXPLORE_LIST, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_SHOP_ENCOUNTER, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_SHOP_BUY_NUM, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_PVP_GET_LIST, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_PLUNDER_INFO, MB_SceneLoading);
    //    SOCKET_MSG_REGIST(SC_GATHER_GET_LIST, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_ROLE_GET_GUIDE_STATE, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_BOX_SHOP_INFO, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_EXPLORE_AUTO_EXPLORE_CHECK, MB_SceneLoading);
    //    SOCKET_MSG_REGIST(SC_KING_ENTER, MB_SceneLoading);
    //    SOCKET_MSG_REGIST(SC_KING_ENTER_WAIT_FIRST_SESSION,MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_ITEM_USE_INFO, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_MESSAGE_NOTICE, MB_SceneLoading);
    SOCKET_MSG_REGIST(SC_ROLE_LOGIN_REWARD, MB_SceneLoading);
    MB_NotificationMgr::getInstence()->removeTips();
    //顺序相关的,不要轻易修改
    MB_EventMgr::getInstence();
    MB_RoleData::getInstance()->sendrole_info();
    MB_RoleData::getInstance()->sendinvite_info();
    MB_PetMgr::getInstance()->sendpet_info();
    MB_ItemMgr::getInstance()->send_role_login_reward();
    MB_ItemMgr::getInstance()->senditem_bag();
    MB_ItemMgr::getInstance()->senditem_equip();
    MB_TeamData::getInstance()->sendpet_pos_list();
    MB_GuardInterface::getInstance()->send_PetGuardInfo();
    MB_ShopMgr::getInstance()->sendshop_encounter();
    PublicNoticeData->sendmessage_notice();
    MB_ShopMgr::getInstance()->sendshop_buy_num();
    MB_ShopMgr::getInstance()->sendbox_shop_info();
    MB_ActionData::getInstance();
    SOCKET_MSG_REGIST(SC_DAILY_GET_LIST, MB_SceneLoading);
    MB_ItemMgr::getInstance()->senddaily_get_list();
    
    MailMgr->sendmail_unread_num();
    MB_MoneyEevntMgr::getInstance()->sendactivity_energy();
    MB_EventMgr::getInstence()->sendworldboss_open_time();
    MB_DataShowPic::getInstance()->sendgather_get_list(PIC_SHOW_TYPE_GER);   //精灵图鉴
    MB_DataShowPic::getInstance()->sendgather_get_list(PIC_SHOW_TYPE_TREASURE);   //精灵图鉴
    MB_DataShowPic::getInstance()->sendgather_get_list(PIC_SHOW_TYPE_EQUIP);   //道具图鉴
    MB_FriendMgr::getInstance()->sendfriend_get_list(1);       //好友
    MB_FriendMgr::getInstance()->sendfriend_add_list();       //好友申请
    //初始化宝箱商店
    MB_ShopMgr::getInstance();
    //tutorial初始化
    MB_TutorialMgr::getInstance()->sendrole_get_guide_state();
    MB_RoleData::getInstance()->sendrole_setting();//设置界面
    
    //    MB_MoneyEevntMgr::getInstance()->sendactivity_sign_emperor_info();
    MB_RoleData::getInstance()->sendrole_buy_coin_value();
    
    MB_ChatDataMgr::getInstance()->onLoadingScene();
    
    MB_FunctionMgr::getInstance()->onLoadingScene();
    MB_ItemMgr::getInstance()->senditem_use_info();
    
    
}
MB_SceneLoading * MB_SceneLoading::create(){
    
    MB_SceneLoading *ptr = new MB_SceneLoading();
    
    if (ptr && ptr->init()) {
        
        ptr->autorelease();
        
        return ptr;
    }
    
    delete ptr;
    
    ptr = NULL;
    
    return ptr;
}

void MB_SceneLoading::tick(float dt){
    
    if (m_nCount >= 13)
    {
        
        if (m_nGoUpdate)
        {
            unscheduleAllSelectors();
            return;
        }
        MB_Message::removeALLMessage();
        CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", true);
        //登陆已经成功,设置成可以自动掉线重连
        MB_ClientSocket::getInstance()->canAutoConnect(2);
        unscheduleAllSelectors();
        CCScene *newScene = MB_SceneMain::scene();
        CCDirector::sharedDirector()->replaceScene(newScene);
        if (!isAutoTanChuSign) {
            //TODODO IOS不自动弹出公告
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
            newScene->addChild(MB_LoginNotice::create(), Z_ORDER_OUTSHOW);
#endif
        }
        PlayBackGround(kmBackGround_Normal);
        
#ifdef PLATFORM_YJ
        MB_YJMgr::getInstance()->enterGame();
#endif
        
#ifdef YJ_IOS
        MB_YJMgr_IOS::getInstance()->enterGame();
#endif
        
    }
}

void MB_SceneLoading::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
        case SC_ROLE_INFO://10102
            MB_DataPVPMgr::getInstance()->sendpvp_get_list();
            m_nCount++;
            break;
        case SC_BATTLE_PROGRESS://10202
        case SC_GER_INFO://10402
        case SC_GER_POS_LIST://10412
        case SC_SHOP_ENCOUNTER:
        case SC_ITEM_BAG://10602
        case SC_ITEM_EQUIP://10605
        case SC_SHOP_BUY_NUM://10702
        case SC_PVP_GET_LIST://10802
        case SC_DAILY_GET_LIST://11002
        case SC_MESSAGE_NOTICE://10303
        case SC_ROLE_GET_GUIDE_STATE:
        case SC_BOX_SHOP_INFO:
        case SC_ROLE_LOGIN_REWARD:
        case SC_ITEM_USE_INFO:
            m_nCount++;
            break;
        case SC_ACCOUNT_LOGIN:
            recvaccount_login(recvPacket);
            break;
        case SC_VERSION:{
            uint8_t result;
            recvPacket->readU8(&result);
            if (result == 1){
                sendaccount_login();
            }
            else if (result == 2){
                m_nGoUpdate = true;
                MB_Message::sharedMB_Message()->showMessage("系统提示","客户端版本需要更新后才可以继续游戏！","更新",this,menu_selector(MB_SceneLoading::goUpdate));
            }
        }
            break;
    }
}

void MB_SceneLoading::sendaccount_login()
{
    
    std::string  accName = MB_ServerList::getInstance()->getAccName();
    std::string  serverKey = MB_ServerList::getInstance()->getServerKey();
    time_t timeStamp = MB_ServerList::getInstance()->getTimeStamp();
    int accid = atoi(MB_ServerList::getInstance()->getAccid().c_str());
    
    const char* oriMac = MB_ClientSocket::getMacAddress();
    std::string strMacAddr = oriMac;
    
    SOCKET_REQUEST_START(CS_ACCOUNT_LOGIN);
    //平台ID
    packet->writeU32(accid);
    //时间戳
    packet->writeU32(timeStamp);
    //账号
    packet->Write(accName.c_str(), sizeof(char)* accName.length());
    //验证密钥
    packet->Write(serverKey.c_str(), sizeof(char)* serverKey.length());
    //Mac地址
    packet->Write(strMacAddr.c_str(), strMacAddr.length());
    //服务器id
    packet->writeU16(MB_ServerList::m_nSelectServerid);
    
    const char* pString = OCandCppHelper::getUniString();
    packet->Write(pString, strlen(pString));
    
    // 渠道ID
    packet->writeU16(NSGameHelper::getSrcType());
    
    SOCKET_REQUEST_END(SC_ACCOUNT_LOGIN, MB_SceneLoading::onMsgRecv);
    
    CC_SAFE_DELETE_ARRAY(oriMac);
    
    
}
void MB_SceneLoading::sendversion(){
    
    MB_Message::sharedMB_Message()->showMessage("登陆中...", 15);
    CCLog("sendversion");
    const char * version = OCandCppHelper::getVervion();
    SOCKET_REQUEST_START(CS_VERSION);
    packet->Write(version, strlen(version));
    SOCKET_REQUEST_END(SC_VERSION, MB_SceneLoading::onMsgRecv);
}
void MB_SceneLoading::goUpdate(CCObject *){
    SET_CHECKED_UPDATE(false);
    CCDirector::sharedDirector()->popToRootScene();
    CCScene *pScene = MB_SceneLoginBackground::scene();
    CCDirector::sharedDirector()->popToRootScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    PlayBackGround(kmBackGround_Normal);
}
void MB_SceneLoading::recvaccount_login(MB_MsgBuffer* recvPacket)
{
    if (m_nGoUpdate){
        
        return;
    }
    uint16_t Data;
    recvPacket->readU16(&Data);
    if (Data == 1)//正确
    {
        uint8_t isCreate = 0;
        recvPacket->readU8(&isCreate);
        if (isCreate == 1) {
            //已创建，获取冒险家信息
            initData();
        }
        else
        {
            MB_LOG("reconnect errcode:%d", isCreate);
        }
        MB_LOG("Login verify succeed!\n");
    }
    else if (Data == 2){
        
        MB_Message::sharedMB_Message()->showMessage("key错误请重试.");
        
    }
    else if (Data == 3){
        
        MB_Message::sharedMB_Message()->showMessage("key超时请重试.");
        
    }
    else if (Data == 4){
        MB_Message::sharedMB_Message()->showMessage("帐号被封禁.");
    }
    else if (Data == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("服务器人数已满, 请稍后重试");
    }
    else {
        
        MB_Message::sharedMB_Message()->showMessage("服务器验证失败, 请重试.");
        
    }
}
