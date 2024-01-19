
#include "MB_LayerEventChangeCoin.h"
#include "MB_TutorialMgr.h"
#include "MB_SceneGame.h"
#include "MB_FunctionMgr.h"
MB_LayerEventChangeCoin::MB_LayerEventChangeCoin(){
    
    m_pNodeChange = NULL;
    m_pCanGetMoney = NULL;
    m_pLeftTime = NULL;
    m_pNeedGold = NULL;
    m_pNodeTimeOver = NULL;
    m_pChangeBtn = NULL;
    m_pMenuSkip = NULL;
    m_bShowRoleInfoPanel = true;
    SOCKET_MSG_REGIST(SC_ROLE_BUY_ENERGY, MB_LayerEventChangeCoin);
    SOCKET_MSG_REGIST(SC_ROLE_BUY_COIN_VALUE, MB_LayerEventChangeCoin);
    SOCKET_MSG_REGIST(SC_ROLE_INFO, MB_LayerEventChangeCoin);
}
MB_LayerEventChangeCoin::~MB_LayerEventChangeCoin(){
    
    CC_SAFE_RELEASE(m_pNodeChange);
    CC_SAFE_RELEASE(m_pCanGetMoney);
    CC_SAFE_RELEASE(m_pLeftTime);
    CC_SAFE_RELEASE(m_pNeedGold);
    CC_SAFE_RELEASE(m_pNodeTimeOver);
    CC_SAFE_RELEASE_NULL(m_pChangeBtn);
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_ENERGY);
    SOCKET_MSG_UNREGIST(SC_ROLE_BUY_COIN_VALUE);
    SOCKET_MSG_UNREGIST(SC_ROLE_INFO);
    CC_SAFE_RELEASE_NULL(m_pMenuSkip);
}
bool MB_LayerEventChangeCoin::init(){
    
    if(MB_ResWindow::init() == false){
        
        return false;
    }
    
    m_bShowRoleInfoPanel = true;
    
    char filename[100];
    sprintf(filename, "res/moneydrawing_layer.ccbi");
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile(filename, this);
    pCCBReader->release();
    this->addChild(NSGameHelper::createDisableTouchLayer12());
    this->addChild(node);
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("SkipFightChangeCoin") == true)
    {
        m_pMenuSkip->setNormalSpriteFrame(((CCSprite *)m_pMenuSkip->getSelectedImage())->displayFrame());
    }
    else
    {
        m_pMenuSkip->setNormalSpriteFrame(((CCSprite *)m_pMenuSkip->getDisabledImage())->displayFrame());
    }
    
    onResetWnd();
    return true;
}

void MB_LayerEventChangeCoin::recvfight_request(MB_MsgBuffer* pRecv)
{
    int32_t getCoin = 0;//战斗造成伤害获得
    int32_t winCoin = 0;//战斗胜利额外获得
    
    pRecv->readU32(&getCoin);
    pRecv->readU32(&winCoin);
    
    int len = 0;
    pRecv->readU16(&len);
    if(len && CCUserDefault::sharedUserDefault()->getBoolForKey("SkipFightChangeCoin") == false)
    {
        MB_NetStructFight structFight;
        recvfight* fight = structFight.recvfight_request(pRecv);
        fight->type =  kFightResultTypeChangeCoin;
        fight->m_pReplayCallBackTarget = this;
        fight->m_pReplayCallBack = callback_selector1st(MB_LayerEventChangeCoin::onReplayCallBack);
        CCDirector::sharedDirector()->pushScene(MB_SceneGame::sceneChangeCoin(fight,getCoin,winCoin,"pic_map/pic_map_7.png"));
    }
    else
    {
        char databuf[100];
        sprintf(databuf, "招财成功, 获得了金币%d。",getCoin+winCoin);
        MB_Message::sharedMB_Message()->showMessage(databuf);
    }
}


MB_LayerEventChangeCoin * MB_LayerEventChangeCoin::create(){
    
    MB_LayerEventChangeCoin *ptr = new MB_LayerEventChangeCoin();
    if(ptr && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
    
}
cocos2d::SEL_MenuHandler MB_LayerEventChangeCoin::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClosedClicked",  MB_LayerEventChangeCoin::onClosedClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onAotuFishingClicked",MB_LayerEventChangeCoin::onSkipFightClicked);
    return NULL;
}

void MB_LayerEventChangeCoin::onSkipFightClicked(CCObject*)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("SkipFightChangeCoin",CCUserDefault::sharedUserDefault()->getBoolForKey("SkipFightChangeCoin") == false);
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("SkipFightChangeCoin"))
    {
        m_pMenuSkip->setNormalSpriteFrame(((CCSprite *)m_pMenuSkip->getSelectedImage())->displayFrame());
    }else
    {
        m_pMenuSkip->setNormalSpriteFrame(((CCSprite *)m_pMenuSkip->getDisabledImage())->displayFrame());
    }
}

void MB_LayerEventChangeCoin::onClosedClicked(CCObject*)
{
    TutorialTriggerComplete
    removeFromParent();
}

cocos2d::extension::SEL_CCControlHandler MB_LayerEventChangeCoin::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChangeClick",  MB_LayerEventChangeCoin::onChangeClick);
    return NULL;
}
bool MB_LayerEventChangeCoin::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    TutorialAssignLayerWindow
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChange", CCNode *, m_pNodeChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCanGetMoney", CCLabelBMFont *, m_pCanGetMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLeftTime", CCLabelBMFont *, m_pLeftTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNeedGold", CCLabelBMFont *, m_pNeedGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTimeOver", CCNode *, m_pNodeTimeOver);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pChangeBtn", CCControlButton *,m_pChangeBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuSkip", CCMenuItemImage *,m_pMenuSkip);
    
    
    return false;
}

void MB_LayerEventChangeCoin::onResetWnd(void){
    
    int needMoney = MB_RoleData::getInstance()->getNeedGoldByTime(kBuyTimesTypeCoin);
    int limit =MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeCoin)-MB_RoleData::getInstance()->getCoinBuyTimes();
    char databuf[200];
    sprintf(databuf, "%d",  MB_RoleData::getInstance()->getBuyConinValue());
    m_pCanGetMoney->setString(databuf);
    sprintf(databuf, "%d/%d",limit, MB_RoleData::getInstance()->getNowBuyLimit(kBuyTimesTypeCoin));
    m_pLeftTime->setString(databuf);
    sprintf(databuf, "%d",needMoney);
    m_pNeedGold->setString(databuf);
    if(limit > 0){
        
//        m_pNodeChange->setVisible(true);
        m_pNodeTimeOver->setVisible(false);
       
        
    }else {
        
//        m_pNodeChange->setVisible(false);
        m_pNodeTimeOver->setVisible(true);
    }
}
void MB_LayerEventChangeCoin::onChargeClick(CCObject *){
    
    MB_Message::sharedMB_Message()->showMessage("招财次数达到上限","招财次数已达上限, 充值成为更高vip可增加购买次数","充值","取消",MB_RoleData::getInstance(),menu_selector(MB_RoleData::goCharge),NULL);
}
void MB_LayerEventChangeCoin::onChangeClick(CCObject * obj)
{
    MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerEventChangeCoin", true);
    TutorialTriggerComplete
    MB_RoleData::getInstance()->goBuyCoin(obj);
}
void MB_LayerEventChangeCoin::onMsgRecv(CCNode* node, SocketResponse* response){
    
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
        case  SC_ROLE_BUY_ENERGY:
            MB_TutorialMgr::getInstance()->SetModelDilogState("MB_LayerEventChangeCoin", false);
            
            if(m_pChangeBtn)m_pChangeBtn->setEnabled(true);
            uint8_t data;
            uint8_t type;
            if (recvPacket->readU8(&data))
            {
                if(recvPacket->readU8(&type))
                {
                    if(data == 1)
                    {
                        MB_Message::removeALLMessage();
                        uint16_t data16;
                        uint16_t dataTimes;
                        recvPacket->readU16(&data16);
                        recvPacket->readU16(&dataTimes);
                        
                       
                        recvfight_request(recvPacket);

                    }
                }
            }
            dirty();
            break;
        case SC_ROLE_BUY_COIN_VALUE:{
        
            char databuf[200];
            sprintf(databuf, "%d",  MB_RoleData::getInstance()->getBuyConinValue());
            m_pCanGetMoney->setString(databuf);
            
        }break;
        case SC_ROLE_INFO:
            onResetWnd();
            break;
        default:
            break;
    }
}
