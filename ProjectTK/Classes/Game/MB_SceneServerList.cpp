

#include "MB_SceneServerList.h"
#include "MB_NodeServerInfo.h"
#include "Game.h"
#include "../Common/SDS_NetWorkDefine.h"
#include "MB_LayerFirstLogin.h"
#include "MB_SceneRoleDemoFight.h"
#include "MB_LayerServerPanel.h"

USING_NS_CC;
USING_NS_CC_EXT;



MB_SceneServerList::MB_SceneServerList()
{
    m_pTableContainer = NULL;
    m_nIsGoUpdate = false;
    isLoadingOver = false;
    
    
}

MB_SceneServerList::~MB_SceneServerList()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    unscheduleAllSelectors();

    
}

CCScene* MB_SceneServerList::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	MB_SceneServerList *layer = MB_SceneServerList::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MB_SceneServerList::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    

    
    CCNode* pNode = MB_LayerServerPanel::create();
    if (pNode)
    {
        addChild(pNode);
    }
	return true;
}

bool MB_SceneServerList::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ServerList", CCNode *, m_pTableContainer);
    if (strcmp(pMemberVariableName, "CellSize") == 0 && pTarget == this) {
        m_cellSize = pNode->getContentSize();
    }
    return true;
}

SEL_MenuHandler MB_SceneServerList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_SceneServerList::onBackClicked);
    return NULL;
}
SEL_CCControlHandler MB_SceneServerList::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

void MB_SceneServerList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
/*
    //发送登陆消息 MB_SOURCE
    sendversion();
    http_sendserver_info(serverList->serverID);
*/
}

CCSize MB_SceneServerList::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

void MB_SceneServerList::onBackClicked(CCObject *pSender)
{
    MB_TARGET_PARENT(MB_LayerFirstLogin, ptr);
    if (ptr)
    {
        ptr->onServerListClosed(this);
    }
}
CCTableViewCell* MB_SceneServerList::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    
    if (MB_ServerList::getInstance()->getLatestServerIDsCount() == 0) {
        if (idx == 0)
        {

                CCLabelTTF* label = CCLabelTTF::create("全部服务器", "", 28);
                label ->setColor(ccYELLOW);
                label->setDimensions(m_cellSize);
                label->setAnchorPoint(CCPointZero);
                label->setPosition(CCPointZero);
                label->setHorizontalAlignment(kCCTextAlignmentCenter);
                label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
                cell->addChild(label);
                label->setPositionX(m_cellSize.width/2.0);
            
        }
        else if (idx < numberOfCellsInTableView(table))
        {

                
                int serverIndex = (idx-1)*2;
                ServerList* serverList = MB_ServerList::getInstance()->getServerListByIndex(serverIndex);
                MB_NodeServerInfo* serverInfo = new MB_NodeServerInfo();
                char* serverZone = new char[16];
                sprintf(serverZone, "%d区",serverList->serverID);
                serverInfo->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);

                CCNode* pNode = CCNode::create();
                pNode->addChild(serverInfo);
                CC_SAFE_RELEASE_NULL(serverInfo);

                serverIndex++;
                serverList = MB_ServerList::getInstance()->getServerListByIndex(serverIndex);
                if (serverList)
                {
                    MB_NodeServerInfo* serverInfo1 = new MB_NodeServerInfo();
                    sprintf(serverZone, "%d区",serverList->serverID);
                    serverInfo1->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);
                    pNode->addChild(serverInfo1);
                    serverInfo1->setPositionX(serverInfo1->getPositionX()+serverInfo1->getNodeSize().width);
                    CC_SAFE_RELEASE_NULL(serverInfo1);
                }

                CC_SAFE_DELETE_ARRAY(serverZone);
                cell->addChild(pNode);
                pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));

            
        }
    }
    else
    {
        if (idx == 0)
        {

                CCLabelTTF* label = CCLabelTTF::create("最近登陆过的服务器", "", 28);
                label->setAnchorPoint(CCPointZero);
                label->setPosition(CCPointZero);
                label ->setColor(ccYELLOW);
                label->setDimensions(m_cellSize);
                label->setHorizontalAlignment(kCCTextAlignmentCenter);
                label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
                cell->addChild(label);
                label->setPositionX(m_cellSize.width/2.0);
            
        }
        else if ( idx == 1)
        {

                CCNode* pNode = CCNode::create();
                
                int serverID = MB_ServerList::getInstance()->getLatestServerIDByIndex(0);
                if (serverID != -1)
                {
                    ServerList* serverList = MB_ServerList::getInstance()->getServerListByID(serverID);
                    if(serverList)
                    {
                        MB_NodeServerInfo* serverInfo = new MB_NodeServerInfo();
                        char* serverZone = new char[16];
                        sprintf(serverZone, "%d区",serverID);
                        serverInfo->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);
                        CC_SAFE_DELETE_ARRAY(serverZone);

                        pNode->addChild(serverInfo);
                        serverInfo->release();
                    }
                }
                serverID = MB_ServerList::getInstance()->getLatestServerIDByIndex(1);
                if (serverID != -1)
                {
                    ServerList* serverList = MB_ServerList::getInstance()->getServerListByID(serverID);
                    if (serverList)
                    {
                        MB_NodeServerInfo* serverInfo = new MB_NodeServerInfo();
                        char* serverZone = new char[16];
                        sprintf(serverZone, "%d区",serverID);
                        serverInfo->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);
                        CC_SAFE_DELETE_ARRAY(serverZone);
                        pNode->addChild(serverInfo);
                        serverInfo->setPositionX(serverInfo->getPositionX()+serverInfo->getNodeSize().width);
                        serverInfo->release();
                    }
                }

                cell->addChild(pNode);
                pNode->setPosition(CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
            
        }
        else if (idx == 2)
        {

                CCLabelTTF* label = CCLabelTTF::create("全部服务器", "", 28);
                label ->setColor(ccYELLOW);
                label->setDimensions(m_cellSize);
                label->setAnchorPoint(CCPointZero);
                label->setPosition(CCPointZero);
                label->setHorizontalAlignment(kCCTextAlignmentCenter);
                label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
                cell->addChild(label);
                label->setPositionX(m_cellSize.width/2.0);
            
        }
        else if (idx < numberOfCellsInTableView(table))
        {
            int serverIndex = (idx-3)*2;
            ServerList* serverList = MB_ServerList::getInstance()->getServerListByIndex(serverIndex);
            MB_NodeServerInfo* serverInfo = new MB_NodeServerInfo();
            char* serverZone = new char[16];
            sprintf(serverZone, "%d区",serverList->serverID);
            serverInfo->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);

            CCNode* pNode = CCNode::create();
            pNode->addChild(serverInfo);
            CC_SAFE_RELEASE_NULL(serverInfo);

            serverIndex = idx*2 - 5;
            serverList = MB_ServerList::getInstance()->getServerListByIndex(serverIndex);
            if (serverList)
            {
                MB_NodeServerInfo* serverInfo1 = new MB_NodeServerInfo();
                sprintf(serverZone, "%d区",serverList->serverID);
                serverInfo1->init(serverZone, serverList->name.c_str(), serverList->serverStatus,serverList->serverID);
                pNode->addChild(serverInfo1);
                serverInfo1->setPositionX(serverInfo1->getPositionX()+serverInfo1->getNodeSize().width);
                CC_SAFE_RELEASE_NULL(serverInfo1);
            }

            CC_SAFE_DELETE_ARRAY(serverZone);
            cell->addChild(pNode);
            pNode->setPosition( CCPointMake(m_cellSize.width/2, m_cellSize.height/2));
        }
    }

    return cell;
}

unsigned int MB_SceneServerList::numberOfCellsInTableView(CCTableView *table)
{
    //latest数量 + serverlist数量 + 最近 + 全部 + 末尾空cell
    int last_servers_count = MB_ServerList::getInstance()->getLatestServerIDsCount();
    int server_list_count  = MB_ServerList::getInstance()->getServerListCount();

    last_servers_count = last_servers_count == 0 ? 0 : 2;
    server_list_count = ((server_list_count%2)==0) ? server_list_count/2 : (server_list_count/2 + 1);
    server_list_count += 1; // 添加标题

    return last_servers_count + server_list_count;
}

void MB_SceneServerList::sendaccount_login()
{
    SOCKET_MSG_REGIST(SC_ACCOUNT_LOGIN, MB_SceneServerList);
    
    MB_Message::sharedMB_Message()->showMessage("登陆中...",15);
    std::string  accName = MB_ServerList::getInstance()->getAccName();
    std::string  serverKey = MB_ServerList::getInstance()->getServerKey();
    time_t timeStamp = MB_ServerList::getInstance()->getTimeStamp();
    int accid = atoi(MB_ServerList::getInstance()->getAccid().c_str());
    
    const char* oriMac = MB_ClientSocket::getMacAddress();
    std::string strMacAddr = oriMac;
    CCLOG("sendaccout_login %s",oriMac);
    SOCKET_REQUEST_START(CS_ACCOUNT_LOGIN);
    //平台ID
    packet->writeU32(accid);
    //时间戳
    packet->writeU32(timeStamp);
    //账号
    packet->Write( accName.c_str(), sizeof(char) * accName.length());
    //验证密钥
    packet->Write( serverKey.c_str(), sizeof(char) * serverKey.length());
    //Mac地址
    packet->Write(strMacAddr.c_str(), strMacAddr.length());
    //服务器id
    packet->writeU16(MB_ServerList::m_nSelectServerid);
    
    const char* pString = OCandCppHelper::getUniString();
    packet->Write(pString, strlen(pString));
    CCLOG("GetUniString %s", pString);
    // 渠道ID
    packet->writeU16(NSGameHelper::getSrcType());
    
    SOCKET_REQUEST_END(SC_ACCOUNT_LOGIN, MB_SceneServerList::onMsgRecv);
    
    CC_SAFE_DELETE_ARRAY(oriMac);
    

}
void MB_SceneServerList::sendversion(){
   
    ServerList* pList = MB_ServerList::getInstance()->getServerListByID(MB_ServerList::m_nSelectServerid);
    if (pList && pList->serverStatus == 1 && 0)
    {
        MB_Message::sharedMB_Message()->showMessage("服务器维护中, 请稍后重试");
        return;
    }
    SOCKET_MSG_REGIST(SC_VERSION, MB_SceneServerList);
    MB_Message::sharedMB_Message()->showMessage("登陆中...",15);
    const char * version = OCandCppHelper::getVervion();
    SOCKET_REQUEST_START(CS_VERSION);
    packet->Write( version , strlen(version));
    SOCKET_REQUEST_END(SC_VERSION, MB_SceneServerList::onMsgRecv);
    
    http_sendserver_info(MB_ServerList::m_nSelectServerid);

}
void MB_SceneServerList::recvaccount_login(MB_MsgBuffer* recvPacket)
{
    SOCKET_MSG_UNREGIST(SC_ACCOUNT_LOGIN);
    if(m_nIsGoUpdate){
     
        return;
    }
    MB_Message::sharedMB_Message()->removeALLMessage();

    CCLOG("recvaccout_login");
    uint16_t Data;
    recvPacket->readU16(&Data);
    if (Data == 1)//正确
    {
        //断线重连标记
        MB_ClientSocket::getInstance()->canAutoConnect(1);
        bool isCreate = false;
        //冒险家是否创建
        recvPacket->readU8(&isCreate);
        if (isCreate)
        {
            //精灵是否创建
            MB_ServerList::getInstance()->setisCreateRole(true);

            recvPacket->readU8(&isCreate); // 是否选择了精灵
            MB_ServerList::getInstance()->setIsSelectParnter(isCreate);
            if (!isCreate)  // 未选择精灵
            {
                CCScene* pScene = MB_SceneRoleCreate::scene();
                CCDirector::sharedDirector()->replaceScene(pScene);
            }
            else
            {
                //是否显示邀请码
                uint8_t data8;
                recvPacket->readU8(&data8);
                MB_ServerList::getInstance()->setIsShowCode(data8 == 2);
                if (isCreate == 1) {
                    
                    CCScene* pScene = MB_SceneLoading::scene();
                    CCDirector::sharedDirector()->replaceScene(pScene);
                }
            }
        }
        else
        {
            //精灵是否创建
            MB_ServerList::getInstance()->setisCreateRole(false);
            recvPacket->readU8(&isCreate);
            //是否显示邀请码
            uint8_t data8;
            recvPacket->readU8(&data8);
            MB_ServerList::getInstance()->setIsShowCode(data8 == 2);
            
            MB_SceneRoleDemoFight* pNode = MB_SceneRoleDemoFight::create();
            if (pNode)
            {
                CCDirector::sharedDirector()->getRunningScene()->addChild(pNode);
                pNode->start();
            }
            else
            {
                CCScene* pScene = MB_SceneRoleCreate::scene();
                if (pScene)
                {
                    CCDirector::sharedDirector()->popToRootScene();
                    CCDirector::sharedDirector()->replaceScene(pScene);
                }
            }
        }
    }
    else if(Data == 2){
        
        MB_Message::sharedMB_Message()->showMessage("key错误请重试.");
        
    }else if(Data == 3){
        
        MB_Message::sharedMB_Message()->showMessage("key超时请重试.");
        
    }else if(Data == 4){
        
        MB_Message::sharedMB_Message()->showMessage("帐号被封禁.");
        
        
    }
    else if(Data == 5)
    {
        MB_Message::sharedMB_Message()->showMessage("服务器人数已满, 请稍后重试");
    }
    else {
        
        MB_Message::sharedMB_Message()->showMessage("服务器验证失败, 请重试.");
        
    }

}

bool MB_SceneServerList::http_sendserver_info(int serverID)
{
    char strServerID[32] = {0};
    sprintf(strServerID, "%d", serverID);
    std::string postinfo = LOGIN_SERVER_URL;
    postinfo+= "select?accid=" + MB_ServerList::getInstance()->getAccid() + "&serverID=" + strServerID;
    
    CCHttpRequest* httpRequest = new extension::CCHttpRequest();
    httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
    httpRequest->setUrl(postinfo.c_str());
    httpRequest->setTag("send serverid");
    //httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
    //httpRequest->setResponseCallback(this, callfuncND_selector(MB_SceneLogin::onHttpMsgRecv));
    extension::CCHttpClient::getInstance()->send(httpRequest);
    httpRequest->release();
    MB_ServerList::m_nSelectServerid = serverID;
    
    {
    
    
#ifdef POST_SERVER_URL
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        std::string postinfo = POST_SERVER_URL;
        postinfo+= "record_dev?accid="+ MB_ServerList::getInstance()->getAccid() +"&devid=" + OCandCppHelper::getDeviceTocken();
        CCHttpRequest* httpRequest = new extension::CCHttpRequest();
        httpRequest->setRequestType(extension::CCHttpRequest::kHttpGet);
        httpRequest->setUrl(postinfo.c_str());
        httpRequest->setTag("send serverid");
        //httpRequest->setRequestData(postinfo.c_str(), postinfo.length());
        //httpRequest->setResponseCallback(this, callfuncND_selector(MB_SceneLogin::onHttpMsgRecv));
        extension::CCHttpClient::getInstance()->send(httpRequest);
        httpRequest->release();
#endif
#endif
    }
    return true;
}

void MB_SceneServerList::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg) {
        case SC_ACCOUNT_LOGIN://登陆信息反馈
            recvaccount_login(recvPacket);
            break;
        case SC_VERSION:{
            SOCKET_MSG_UNREGIST(SC_VERSION);
            uint8_t result;
            recvPacket->readU8(&result);
            CCLog("version result");
            if(result == 1){
                sendaccount_login();

                //version ok
            }else if(result == 2){
            
                m_nIsGoUpdate = true;
                MB_Message::sharedMB_Message()->showMessage("系统提示","客户端版本需要更新后才可以继续游戏！","更新",this,menu_selector(MB_SceneServerList::goUpdate));
            }
        }
            break;
        default:
            break;
    }
    
}
void MB_SceneServerList::goUpdate(CCObject *){

    SET_CHECKED_UPDATE(false);
    CCDirector::sharedDirector()->popToRootScene();
    CCScene *pScene = MB_SceneLoginBackground::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    PlayBackGround(kmBackGround_Normal);
}

