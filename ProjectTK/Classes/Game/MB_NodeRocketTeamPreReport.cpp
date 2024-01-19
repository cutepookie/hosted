
//

#include "MB_NodeRocketTeamPreReport.h"
#include "MB_LayerWorldBossMain.h"
#include "MB_FunctionModule.h"
MB_NodeRocketTeamPreReport::MB_NodeRocketTeamPreReport(){

    m_pBossLevel = NULL;
    m_pLevelTime = NULL;
    m_pNodeWin = NULL;
    m_pNodeLose = NULL;
    m_pNodeLuckyPlayer = NULL;
    m_pLostInfo = NULL;
    for (int i = 0 ; i < 11 ; i++){

        m_pAttack[i] = NULL;
        m_pUserName[i] = NULL;
    }
}
MB_NodeRocketTeamPreReport::~MB_NodeRocketTeamPreReport(){
    
    CC_SAFE_RELEASE(m_pBossLevel);
    CC_SAFE_RELEASE(m_pLevelTime);
    CC_SAFE_RELEASE(m_pNodeWin);
    CC_SAFE_RELEASE(m_pNodeLose);
    CC_SAFE_RELEASE(m_pNodeLuckyPlayer);
    
    CC_SAFE_RELEASE_NULL(m_pLostInfo);
    for (int i = 0 ; i < 11 ; i++){

        CC_SAFE_RELEASE(m_pAttack[i]);
        CC_SAFE_RELEASE(m_pUserName[i]);

    }
    SOCKET_MSG_UNREGIST(SC_HULA_OPEN);
    SOCKET_MSG_UNREGIST(SC_HULA_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
    SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);

}
bool MB_NodeRocketTeamPreReport::init(int index){

    if(CCLayer::init() == false){
    
        return false;
        
    }
    addChild(NSGameHelper::createDisableTouchLayer());
    m_nIndex = index;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);

    if(index == 0)
    {
        CCNode*  node= pCCBReader->readNodeGraphFromFile("res/station_layer_result.ccbi", this);
        this->addChild(node);
        pCCBReader->release();

        CCBReader* pReader1 = new CCBReader(ccNodeLoaderLibrary);
        CCBReader* pReader2 = new CCBReader(ccNodeLoaderLibrary);
        m_pLostInfo = pReader2->readNodeGraphFromFile("res/station_node_rocket_score.ccbi",this);
        pReader1->release();
        pReader2->release();
        
    }
    else
    {
        CCNode*  node= pCCBReader->readNodeGraphFromFile("res/gui_hulao_score.ccbi", this);
        this->addChild(node);
        pCCBReader->release();

        CCBReader* pReader1 = new CCBReader(ccNodeLoaderLibrary);
        CCBReader* pReader2 = new CCBReader(ccNodeLoaderLibrary);
        m_pLostInfo = pReader2->readNodeGraphFromFile("res/obj_hulao_haveno.ccbi",this);
        pReader1->release();
        pReader2->release();

    }

    //OCandCppHelper::convertScollerViewSuitable(m_pNodeWin)
    m_propertyDirty = false;
    onResetWnd();

    return true;
}

MB_NodeRocketTeamPreReport* MB_NodeRocketTeamPreReport::create(int index){
    
   MB_NodeRocketTeamPreReport * ptr = new MB_NodeRocketTeamPreReport();
    if( ptr && ptr->init(index) ){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
void MB_NodeRocketTeamPreReport::onResetWnd(){

    MB_EventData *m_pData = (MB_EventData *)MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(m_nIndex);
    MB_EventLastReport *m_pReport = m_pData->getEventLastReport();
    
    char databuf[100];
    if (m_nIndex == 0) {
        
            sprintf(databuf,"%d", m_pReport->getBossLevel());
        
    }else {
    
            sprintf(databuf,"%d", m_pReport->getBossLevel());
    }

    m_pBossLevel->setString(databuf);
    sprintf(databuf,"%02d:%02d",m_pReport->getInterValSec()/60,m_pReport->getInterValSec()%60);
    m_pLevelTime->setString(databuf);
    
    if (m_pReport->getHuaInfoList()->count() == 0) {
        m_pNodeLose->setVisible(true);
        m_pNodeWin->setVisible(false);
        m_pNodeLose->addChild(m_pLostInfo);
    }else {
        m_pNodeLose->setVisible(false);
        m_pNodeWin->setVisible(true);
        m_pNodeWin->addChild(m_pLostInfo);
    }
}

cocos2d::SEL_MenuHandler MB_NodeRocketTeamPreReport::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_NodeRocketTeamPreReport::onBackClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeRocketTeamPreReport::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    
    return NULL;
}
bool MB_NodeRocketTeamPreReport::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBossLevel", CCLabelBMFont*, m_pBossLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLevelTime", CCLabelBMFont*, m_pLevelTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeWin", CCNode *, m_pNodeWin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeLose", CCNode *, m_pNodeLose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NodeLuckyPlayer", CCNode *, m_pNodeLuckyPlayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLostInfo", CCNode *, m_pLostInfo);
    
    
    char attack[]="m_pAttack0";
    char username[]="m_pUserName0";
    for (int i = 0 ; i < 10 ; i++)
    {
        attack[9] = '0' +i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  attack, CCLabelTTF*, m_pAttack[i]);
        username[11]= '0'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  username, CCLabelTTF*, m_pUserName[i]);

    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pAttack10" , CCLabelTTF*, m_pAttack[10]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pUserName10" , CCLabelTTF*, m_pUserName[10]);
    return false;
}
void MB_NodeRocketTeamPreReport::onBackClick(CCObject *){
    
//    MB_Message::sharedMB_Message()->showMessage("",15);
//    
//    sendWorldBoss_open();
    popWindow();

}
bool  MB_NodeRocketTeamPreReport::sendhula_open(){
    
    SOCKET_MSG_REGIST(SC_HULA_OPEN,MB_NodeRocketTeamPreReport);
    SOCKET_MSG_REGIST(SC_HULA_INIT_STATE, MB_NodeRocketTeamPreReport);
    SOCKET_REQUEST_START(CS_HULA_OPEN);
    SOCKET_REQUEST_END(SC_HULA_OPEN,MB_NodeRocketTeamPreReport::onMsgRecv);
    return true;
}
bool  MB_NodeRocketTeamPreReport::sendWorldBoss_open(){
    
    SOCKET_MSG_REGIST(SC_NANM_OPEN,MB_NodeRocketTeamPreReport);
    SOCKET_MSG_REGIST(SC_NANM_INIT_STATE, MB_NodeRocketTeamPreReport);
    SOCKET_REQUEST_START(CS_NANM_OPEN);
    SOCKET_REQUEST_END(SC_NANM_OPEN,MB_NodeRocketTeamPreReport::onMsgRecv);
    return true;
}
void  MB_NodeRocketTeamPreReport::onMsgRecv(CCNode* node, SocketResponse* response){

    
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
            
                 
        case SC_HULA_OPEN:{//11111111111
            
            SOCKET_MSG_UNREGIST(SC_HULA_OPEN);
//            MB_EventData *data =(MB_EventData *) MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(m_nIndex);
            MB_Message::removeALLMessage();
//            if (data->getIsOpen() == false) {
//            
//                MB_NodeRocketTeam *layer = MB_NodeRocketTeam::create();
//                replaceLayer(layer); 
//            }
//            NSGameFunction::CCFunctionInterface *pInterface = NULL;
//            MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionLLTower, &pInterface);
//            if (pInterface)
//            {
//                NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(pInterface->createFunctionDialog());
//            }
        }
            break;
        case SC_HULA_INIT_STATE:{
            
            SOCKET_MSG_UNREGIST(SC_HULA_INIT_STATE);
            MB_Message::removeALLMessage();
//            MB_NodeRocketTeam *layer = MB_NodeRocketTeam::create();
//            replaceLayer(layer);
            
        }
            break;
        case SC_NANM_OPEN:{
            
            SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
//            MB_EventData *data =(MB_EventData *) MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(m_nIndex);
            MB_Message::removeALLMessage();
            
            NSGameFunction::CCFunctionInterface *pInterface = NULL;
            MB_FunctionMgr::getInstance()->queryFunctionByType(kFunctionResearchInstitute, &pInterface);
            if (pInterface)
            {
                NSGameFunction::CCFunctionInterface::replaceMainSceneSubLayer(pInterface->createFunctionDialog());
            }
//            if (data->getIsOpen() == false) {
//                
//                MB_NodeNanMan *layer = MB_NodeNanMan::create();
//                replaceLayer(layer);
//            }
        }
            break;
        case SC_NANM_INIT_STATE:{
            
            SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);
            MB_Message::removeALLMessage();
//            MB_NodeNanMan *layer = MB_NodeNanMan::create();
//            replaceLayer(layer);
            
        }
            break;
        default:
            break;
    }

}
