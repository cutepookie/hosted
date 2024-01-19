//
//  MB_LayerRoleDetail.cpp
//  ProjectMB
//
//  Create by ChenHongkun on 10/9/2014.
//
//
#include "MB_LayerRoleDetail.h"
#include "MB_RoleData.h"
#include "MB_ChangeHead.h"
#include "Game.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "MB_NodeUnit91.h"
#endif

#ifdef PLATFORM_YJ
#include "MB_YJMgr.h"
#endif

#ifdef YJ_IOS
#include "MB_YJMgr_IOS.h"
#endif
//#include "MB_LayerSettingMain.h"
#include "MB_NodeUnitRegist.h"
#include "MB_NodeUnitLogout.h"
#include "MB_NodeUnitCode.h"
#include "MB_NodeUnitMusic.h"
#include "MB_NodeUnitFAQ.h"
#include "MB_LayerVipInfo.h"
#include "MB_NodeUnitClearCache.h"
#include "MB_ChatData.h"
#include "MB_NodeUnit91.h"
#include "MB_LayerChangeName.h"
MB_LayerRoleDetail::MB_LayerRoleDetail()
{
    m_pVipLevelSpr = NULL;
    m_pSpriteExp = NULL;
    m_pEditBox = NULL;
    m_pMusicOpen = NULL;
    m_pMusicClose = NULL;
    m_pSoundOpen = NULL;
    m_pSoundClose = NULL;
    m_pRoleName = NULL;
    m_pRoleLevel = NULL;
    m_pRoleExp = NULL;
    m_pRoleVip = NULL;
    m_pRoleCard = NULL;
    m_pRoleFrame = NULL;
    m_nLength = 0;
    SOCKET_MSG_REGIST(SC_ROLE_CHANGE_HEAD, MB_LayerRoleDetail);
    SOCKET_MSG_REGIST(SC_MESSAGE_TEST, MB_LayerRoleDetail);
    SOCKET_MSG_REGIST(SC_GIFT_REQUEST, MB_LayerRoleDetail);
    SOCKET_MSG_REGIST(RECV_ROLE_CHANGE_NAME, MB_LayerRoleDetail);
    m_bShowRoleInfoPanel = true;
    MB_LayerRoleInfoHeader::setMenuEnable(false, "MB_LayerRoleDetail");
}
MB_LayerRoleDetail::~MB_LayerRoleDetail()
{
    CC_SAFE_RELEASE_NULL(m_pVipLevelSpr);
    CC_SAFE_RELEASE_NULL(m_pSpriteExp);
    CC_SAFE_RELEASE_NULL(m_pEditBox);
    CC_SAFE_RELEASE_NULL(m_pMusicOpen);
    CC_SAFE_RELEASE_NULL(m_pMusicClose);
    CC_SAFE_RELEASE_NULL(m_pSoundOpen);
    CC_SAFE_RELEASE_NULL(m_pSoundClose);
    CC_SAFE_RELEASE_NULL(m_pRoleName);
    CC_SAFE_RELEASE_NULL(m_pRoleLevel);
    CC_SAFE_RELEASE_NULL(m_pRoleExp);
    CC_SAFE_RELEASE_NULL(m_pRoleVip);
    CC_SAFE_RELEASE_NULL(m_pRoleCard);
    CC_SAFE_RELEASE_NULL(m_pRoleFrame);
    SOCKET_MSG_UNREGIST(SC_ROLE_CHANGE_HEAD);
    SOCKET_MSG_UNREGIST(SC_MESSAGE_TEST);
    SOCKET_MSG_UNREGIST(SC_GIFT_REQUEST);
    SOCKET_MSG_UNREGIST(RECV_ROLE_CHANGE_NAME);
    MB_LayerRoleInfoHeader::setMenuEnable(true, "MB_LayerRoleDetail");
}

bool MB_LayerRoleDetail::init()
{
    CCNode* pNode = loadResource("res/Role_infomation.ccbi");
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer());
        addChild(pNode);
        
        onResetWnd();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shangcheng.plist"); m_pVipLevelSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("icon_vip_%d.png",MB_RoleData::getInstance()->getVipLevel())->getCString()));
        return true;
    }
    
    return false;
}
void MB_LayerRoleDetail::resetCard()
{
    NSGameHelper::setRoleIcon(m_pRoleCard, MB_RoleData::getInstance()->getSex(), MB_RoleData::getInstance()->getHead(), MB_RoleData::getInstance()->getTitle());
}

void MB_LayerRoleDetail::onResetWnd()
{
    m_pRoleName->setString(MB_RoleData::getInstance()->getName());
    
    char databuf[50];
    sprintf(databuf, "%d", MB_RoleData::getInstance()->getLevel());
    m_pRoleLevel->setString(databuf);
    int vipLevel = MB_RoleData::getInstance()->getVipLevel();
    sprintf(databuf, "%d", vipLevel);
    m_pRoleVip->setString(databuf);
    
    NSGameHelper::setRoleIcon(m_pRoleCard, MB_RoleData::getInstance()->getSex(), MB_RoleData::getInstance()->getHead(), MB_RoleData::getInstance()->getTitle());
    NSGameHelper::creatMaskSprite(m_pRoleCard);
    
    MB_PetTemplate* petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(MB_RoleData::getInstance()->getHead()%SHAPE_BASE);
    if (petTemplete) {
        m_pRoleFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("slot_type_%d.png",petTemplete->getPetKingdom())->getCString()));
    }
    
    m_pExpTimer = CCProgressTimer::create(m_pSpriteExp);
    m_pExpTimer->setType(kCCProgressTimerTypeBar);
    m_pExpTimer->setMidpoint(ccp(0, 1));
    m_pExpTimer->setBarChangeRate(ccp(1, 0));
    m_pExpTimer->setPercentage(0);
    
    m_pSpriteExp->getParent()->addChild(m_pExpTimer, m_pSpriteExp->getZOrder(), m_pSpriteExp->getTag());
    
    m_pExpTimer->setPosition(m_pSpriteExp->getPosition());
    m_pExpTimer->setAnchorPoint(m_pSpriteExp->getAnchorPoint());
    m_pSpriteExp->removeFromParent();
    
    int64_t preExp = MB_RoleData::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel() - 1);
    int64_t nextExp = MB_RoleData::getInstance()->getExpByLevel(MB_RoleData::getInstance()->getLevel());
    float m_tPerccent = 100.0f*(MB_RoleData::getInstance()->getEXP() - preExp) / (nextExp - preExp);
    m_tPerccent = m_tPerccent > 100.f ? 100.0f : m_tPerccent;
    sprintf(databuf, "%lld/%lld", MB_RoleData::getInstance()->getEXP() - preExp, nextExp - preExp);
    m_pRoleExp->setString(databuf);
    m_pExpTimer->setPercentage(m_tPerccent);
    
    
    if(MB_Audio::getInstance()->getBackGroundOpen()){
        
        m_pMusicOpen->setVisible(false);
        
    }else {
        
        m_pMusicClose->setVisible(false);
        
    }
    if(MB_Audio::getInstance()->getEffectsoundOpen()){
        
        m_pSoundOpen->setVisible(false);
        
    }else {
        
        m_pSoundClose->setVisible(false);
    }

}
void MB_LayerRoleDetail::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    MB_MsgBuffer* recvPacket = response->getResponseData();
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_ROLE_CHANGE_HEAD:
            NSGameHelper::setRoleIcon(m_pRoleCard, MB_RoleData::getInstance()->getSex(), MB_RoleData::getInstance()->getHead(), MB_RoleData::getInstance()->getTitle());
            break;
        case SC_MESSAGE_TEST:
            MB_Message::removeALLMessage();
            uint8_t data8;
            recvPacket->readU8(&data8);
            if (data8 == 1)
            {
                MB_Message::sharedMB_Message()->showMessage("成功");
                onResetWnd();
            }
            else
            {
                char *str = recvPacket->ReadString();
                if (str)MB_Message::sharedMB_Message()->showMessage(" ", str, "确定");
                CC_SAFE_FREE(str);
            }
            break;
        case SC_GIFT_REQUEST:
            recvgift_request(recvPacket);
            break;
        case RECV_ROLE_CHANGE_NAME:
            m_pRoleName->setString(MB_RoleData::getInstance()->getName());
            break;
        default:
            break;
    }
}
bool MB_LayerRoleDetail::recvgift_request(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint8_t data8;
    uint16_t data16;
    uint32_t data32;
    recvPacket->readU8(&data8);
    
    if (data8 == 1){
        CCArray *pArray = CCArray::create();
        recvPacket->readU16(&data16);
        recvPacket->readU32(&data32);//coin;
        if (data32 > 0){
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            data->setValueID(COIN_ID);
            data->setNumber(data32);
            pArray->addObject(data);
            data->release();
        }
        recvPacket->readU32(&data32);//roleExp
        if (data32 > 0){
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            data->setValueID(ROLE_EXP_ID);
            data->setNumber(data32);
            pArray->addObject(data);
            data->release();
        }
        recvPacket->readU32(&data32);//petExp
        if (data32 > 0){
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            data->setValueID(GER_EXP_ID);
            data->setNumber(data32);
            pArray->addObject(data);
            data->release();
        }
        recvPacket->readU32(&data32);//gold
        if (data32 > 0){
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            data->setValueID(GOLD_ID);
            data->setNumber(data32);
            pArray->addObject(data);
            data->release();
        }
        recvPacket->readU32(&data32);//reputation
        if (data32 > 0){
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            data->setValueID(REPUTATION_ID);
            data->setNumber(data32);
            pArray->addObject(data);
            data->release();
        }
        int16_t itemLength;
        recvPacket->readU16(&itemLength);
        for (int i = 0; i < itemLength; i++) {
            
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypeItem);
            pArray->addObject(data);
            data->release();
            recvPacket->readU16(&data16);
            data->setValueID(data16);
            recvPacket->readU8(&data8);
            //item->itemLevel = data8;
            recvPacket->readU8(&data8);
            //item->itemRank = data8;
            recvPacket->readU16(&data16);
            data->setNumber(data16);
        }
        recvPacket->readU16(&itemLength);
        for (int i = 0; i < itemLength; i++) {
            
            recvPacket->readU16(&data16);//rank
            recvPacket->readU16(&data16);//levl
            recvPacket->readU16(&data16);
            RewardTempleteValue * data = new  RewardTempleteValue();
            data->setType(kRewardValueTypePet);
            pArray->addObject(data);
            data->release();
            data->setValueID(data16);
            data->setNumber(1);
        }
        MB_LayerRewardMore* layer = MB_LayerRewardMore::create(pArray);
        
        this->pushWindow(layer);
        
    }
    else if (data8 == 2){
        
        MB_Message::sharedMB_Message()->showMessage("此礼包激活码已经被使用！");
        
    }
    else if (data8 == 3){
        
        MB_Message::sharedMB_Message()->showMessage("礼包激活码无效");
        
    }
    else if (data8 == 4){
        
        m_pCode = "您已经获得过" + m_pCode;
        MB_Message::sharedMB_Message()->showMessage(m_pCode.c_str());
        
    }
    else if (data8 == 5){
        
        MB_Message::sharedMB_Message()->showMessage("未知错误");
        
    }
    else  if (data8 == 6){
        
        MB_Message::sharedMB_Message()->showMessage("请求超时");
        
    }
    else if (data8 == 7)
    {
        MB_Message::sharedMB_Message()->showMessage("当前服务器不可使用");
    }
    else if (data8 == 8)
    {
        MB_Message::sharedMB_Message()->showMessage("已使用与此类型互斥的礼包激活码");
    }
    else if (data8 == 9)
    {
        MB_Message::sharedMB_Message()->showMessage("不在可使用期限内");
    }
    else {
        MB_Message::sharedMB_Message()->showMessage("检查网络");
    }
    
    return true;
}
bool MB_LayerRoleDetail::sendgift_request(const char *string)
{
    if (strlen(string) == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("输入为空");
        return false;
    }
    
    MB_Message::sharedMB_Message()->showMessage(" ", 15);
    SOCKET_REQUEST_START(CS_GIFT_REQUEST);
    packet->Write(string, strlen(string));
    SOCKET_REQUEST_END(SC_GIFT_REQUEST, MB_LayerWeiboSetting::onMsgRecv);
    m_pCode = string;
    return true;
}
void MB_LayerRoleDetail::addNodeToLayer(CCLayer * layer, int type)
{
    switch (type)
    {
        case 1://微博
            break;
        case 2://好友邀請
            break;
        case 3://禮包兑換
        {
            MB_NodeUnitCode *player = MB_NodeUnitCode::create();
            layer->addChild(player);
            player->setTag(m_nLength);
            m_nLength++;
        }
            break;
        case 5:
        {
            //            MB_NodeUnitFAQ *player =   MB_NodeUnitFAQ::create();
            //            layer ->addChild(player);
            //            player->setTag(m_nLength);
            //            m_nLength++;
        }
            break;
        case 6:
        {
            MB_NodeUnitMusic *player = MB_NodeUnitMusic::create();
            layer->addChild(player);
            player->setTag(m_nLength);
            m_nLength++;
        }
            
            break;
        case 7://锁屏
            break;
        case 8://游客注册
        {
        }
            break;
        case 9://注销
        {
            MB_NodeUnitLogout *player = MB_NodeUnitLogout::create();
            layer->addChild(player);
            player->setTag(m_nLength);
            m_nLength++;
        }
            break;
        default:
            break;
    }
}

bool MB_LayerRoleDetail::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleName", CCLabelTTF*, m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleLevel", CCLabelBMFont*, m_pRoleLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleExp", CCLabelBMFont*, m_pRoleExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleVip", CCLabelBMFont*, m_pRoleVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleCard", CCSprite*, m_pRoleCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pRoleFrame", CCSprite*, m_pRoleFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "musicOpen", CCNode*, m_pMusicOpen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "musicClose", CCNode*, m_pMusicClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "soundOpen", CCNode*, m_pSoundOpen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "soundClose", CCNode*, m_pSoundClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pEditBox", CCEditBox*, m_pEditBox);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite*, m_pSpriteExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pVipLevelSpr", CCSprite*, m_pVipLevelSpr);
    return false;
}
SEL_MenuHandler MB_LayerRoleDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerRoleDetail::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMusicOnClick", MB_LayerRoleDetail::onMusicOnClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMusicOffClick", MB_LayerRoleDetail::onMusicOffClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSoundOnClick", MB_LayerRoleDetail::onSoundOnClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSoundOffClick", MB_LayerRoleDetail::onSoundOffClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUNRegistClick", MB_LayerRoleDetail::onUNRegistClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClearClick", MB_LayerRoleDetail::onClearClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCodeRewardClick", MB_LayerRoleDetail::onCodeRewardClick);
    
    return NULL;
}


SEL_CCControlHandler MB_LayerRoleDetail::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChangeHeadClicked", MB_LayerRoleDetail::onChangeHeadClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onChangeNameClicked", MB_LayerRoleDetail::onChangeNameClicked);
    
    return NULL;
}
void MB_LayerRoleDetail::onCloseClick(CCObject* pSender)
{
    removeFromParentAndCleanup(true);
}
void MB_LayerRoleDetail::setString(const char *codeback)
{
    if (strlen(codeback) == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("输入为空");
        return;
    }
    MB_Message::sharedMB_Message()->showMessage("错误", 600);
    SOCKET_REQUEST_START(CS_MESSAGE_TEST);
    packet->Write(codeback, strlen(codeback));
    SOCKET_REQUEST_END(SC_MESSAGE_TEST, MB_LayerSetting::onMsgRecv);
}


void MB_LayerRoleDetail::onChangeHeadClicked(CCObject* pSender)
{
    MB_ChangeHead* layer = MB_ChangeHead::create();
    if (layer != NULL)
    {
        this->addChild(layer, Z_ORDER_OUTSHOW);
    }
}

void MB_LayerRoleDetail::onChangeNameClicked(CCObject* pSender)
{
    MB_LayerChangeName* layer = MB_LayerChangeName::create();
    if (layer != NULL)
    {
        this->addChild(layer, Z_ORDER_OUTSHOW);
    }
}

void MB_LayerRoleDetail::onUNRegistClick(CCObject* pSender)
{
    MB_Message::sharedMB_Message()->showMessage(" ", 5);
#ifdef PLATFORM_YJ
    MB_YJMgr::getInstance()->goLogout();
#elif defined(YJ_IOS)
    MB_YJMgr_IOS::getInstance()->goLogout();
#else
    MB_ServerList::destroyInstance();
    MB_ClientSocket::destroyInstance();
    CCUserDefault::sharedUserDefault()->setBoolForKey("isGameInitOver", false);
    CCScene *pScene = MB_SceneLoginBackground::scene();
    CCDirector::sharedDirector()->popToRootScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    PlayBackGround(kmBackGround_Login);
#endif
}
void MB_LayerRoleDetail::onClearClick(CCObject* pSender)
{
    MB_ChatDataMgr::getInstance()->clearChatCache();
    MB_Message::sharedMB_Message()->showMessage("清除成功");
}
void MB_LayerRoleDetail::onCodeRewardClick(CCObject* pSender)
{
    sendgift_request(m_pEditBox->getText());
}
void MB_LayerRoleDetail::onMusicOnClick(CCObject *){
    
    SETBYKEY("musicOff",false);
    m_pMusicOpen->setVisible(false);
    m_pMusicClose->setVisible(true);
    MB_Audio::getInstance()->setBackGrondOpen(true);
    
}
void MB_LayerRoleDetail::onMusicOffClick(CCObject*){
    
    SETBYKEY("musicOff",true);
    m_pMusicOpen->setVisible(true);
    m_pMusicClose->setVisible(false);
    MB_Audio::getInstance()->setBackGrondOpen(false);
    
}
void MB_LayerRoleDetail::onSoundOnClick(CCObject *){
    
    SETBYKEY("soundOff", false);
    m_pSoundOpen->setVisible(false);
    m_pSoundClose->setVisible(true);
    MB_Audio::getInstance()->setEffectsoundOpen(true);
    
}
void MB_LayerRoleDetail::onSoundOffClick(CCObject *){
    
    SETBYKEY("soundOff", true);
    m_pSoundOpen->setVisible(true);
    m_pSoundClose->setVisible(false);
    MB_Audio::getInstance()->setEffectsoundOpen(false);
    
}
