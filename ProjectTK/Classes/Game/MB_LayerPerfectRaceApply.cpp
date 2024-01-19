//
//  MB_LayerPerfectRaceApply.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#include "MB_LayerPerfectRaceApply.h"
#include "MB_PerfectRaceInterface.h"

static const uint32_t day_seconds = 24 * 60 * 60;

MB_LayerPerfectRaceApply::MB_LayerPerfectRaceApply()
{
    m_pTimeTitle = NULL;
    m_pTime = NULL;
    m_pSigned = NULL;
    m_pBtnSign = NULL;
    m_pSpriteKingName = NULL;
    m_pPerfectRaceInterface = NULL;
    m_pNodeKingName = NULL;
    
    SOCKET_MSG_REGIST(SC_RACE_INFO, MB_LayerPerfectRaceApply);
    SOCKET_MSG_REGIST(SC_RACE_AUTO_UNSIGN, MB_LayerPerfectRaceApply);
    SOCKET_MSG_REGIST(SC_RACE_AUTO_SIGN, MB_LayerPerfectRaceApply);
    SOCKET_MSG_REGIST(SC_RACE_SIGN, MB_LayerPerfectRaceApply);
}

MB_LayerPerfectRaceApply::~MB_LayerPerfectRaceApply()
{
    m_pPerfectRaceInterface->setOpenRaceMainOrRaceApply(false);
    CC_SAFE_RELEASE_NULL(m_pTimeTitle);
    CC_SAFE_RELEASE_NULL(m_pTime);
    CC_SAFE_RELEASE_NULL(m_pSigned);
    CC_SAFE_RELEASE_NULL(m_pBtnSign);
    CC_SAFE_RELEASE_NULL(m_pSpriteKingName);
    CC_SAFE_RELEASE_NULL(m_pNodeKingName);
    SOCKET_MSG_UNREGIST(SC_RACE_INFO);
    SOCKET_MSG_UNREGIST(SC_RACE_SIGN);
    SOCKET_MSG_UNREGIST(SC_RACE_AUTO_UNSIGN);
    SOCKET_MSG_UNREGIST(SC_RACE_AUTO_SIGN);
    m_pPerfectRaceInterface = NULL;
}

bool MB_LayerPerfectRaceApply::init()
{
    CCNode* pNode = loadResource("res/monsterrace_layer_application.ccbi");
    
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        onResetWnd();
        schedule( schedule_selector(MB_LayerPerfectRaceApply::updateTime),1.0f);
        m_pPerfectRaceInterface->setOpenRaceMainOrRaceApply(true);
        return true;
    }
    
    return false;
}

void MB_LayerPerfectRaceApply::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerPerfectRaceApply::onResetWnd()
{
    if (m_pPerfectRaceInterface)
    {
        if(m_pPerfectRaceInterface->getKingName().empty())
        {
            m_pNodeKingName->setVisible(false);
        }
        else
        {
            m_pNodeKingName->setVisible(true);
            m_pSpriteKingName->setString(m_pPerfectRaceInterface->getKingName().c_str());
        }
        
        if (m_pPerfectRaceInterface->getIsSign())
        {
            m_pSigned->setVisible(true);
            m_pBtnSign->setVisible(false);
        }
        else
        {
            m_pSigned->setVisible(false);
            m_pBtnSign->setVisible(true);
        }
        
        updateTime();
    }
}

bool MB_LayerPerfectRaceApply::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_timeTitle", CCSprite*,m_pTimeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_time", CCLabelBMFont*,m_pTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_signed", CCLabelTTF*,m_pSigned);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_sign", CCControlButton*,m_pBtnSign);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_lastking", CCNode*,m_pNodeKingName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_lastkingname", CCLabelTTF*,m_pSpriteKingName);
    return false;
}

SEL_MenuHandler MB_LayerPerfectRaceApply::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPerfectRaceApply::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRaceRuleClicked", MB_LayerPerfectRaceApply::onRaceRuleClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerPerfectRaceApply::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPreRaceRecordClicked", MB_LayerPerfectRaceApply::onPreRaceRecordClicked);

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGroupRecordClicked", MB_LayerPerfectRaceApply::onGroupRecordClicked);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSignClicked", MB_LayerPerfectRaceApply::onSignClicked);
    
    
    return NULL;
}

bool MB_LayerPerfectRaceApply::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerPerfectRaceApply::updateTime()
{
    if (m_pPerfectRaceInterface->getStep()!=STATUS_SIGN)
    {
        m_pTimeTitle->setVisible(false);
        m_pTime->setVisible(false);
    }
    else
    {
        m_pTimeTitle->setVisible(true);
        m_pTime->setVisible(true);
        int time = m_pPerfectRaceInterface->getTimeStap()-MB_ClientSocket::getInstance()->getServerTime();
        if (time <= 0)
        {
            m_pTime->setString("00:00:00");
        }
        else
        {
            m_pTime->setString(NSGameHelper::formatTimeStringHMS(time));
        }
    }
}

void MB_LayerPerfectRaceApply::onPreRaceRecordClicked(CCObject* pSender)
{
    m_pPerfectRaceInterface->onPreRecordClicked(this);
}

void MB_LayerPerfectRaceApply::onRaceRuleClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    pushWindow(m_pPerfectRaceInterface->createRuleDialog());
}

void MB_LayerPerfectRaceApply::onGroupRecordClicked(CCObject* pSender)
{
    
}

void MB_LayerPerfectRaceApply::onSignClicked(CCObject* pSender)
{
    if (m_pPerfectRaceInterface)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        
        m_pPerfectRaceInterface->sendrace_sign();
    }
}

void MB_LayerPerfectRaceApply::onCloseClicked(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld, this);
}
/*
 message recvrace_sign[id=13411]{
 required        int8            reason_code             = 1;//错误提示码，0表示成功
 }
 */
void MB_LayerPerfectRaceApply::recvrace_sign(MB_MsgBuffer* pRecv)
{
    uint8_t u8 = 0;
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    pRecv->readU8(&u8);
    if (u8 == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("已报名参加霸主之战");
        m_pPerfectRaceInterface->setIsSign(true);
    }
    else
    {
        showError(u8);
    }
    onResetWnd();
}
void MB_LayerPerfectRaceApply::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    uint8_t u8 = 0;
    switch (Msg)
    {
        case SC_RACE_SIGN:
            recvrace_sign(recvPacket);
            break;
        case SC_RACE_INFO:
            recvrace_info(recvPacket);
            break;
        case SC_RACE_AUTO_SIGN:
        case SC_RACE_AUTO_UNSIGN:
            MB_Message::sharedMB_Message()->removeALLMessage();
            
            recvPacket->readU8(&u8);
            if (u8 !=0 )
            {
                showError(u8);
            }
            break;
        default:
            break;
    }
}

/*
 -define(REASON_CODE_NOT_SIGN_TIME, 1).
 -define(REASON_CODE_ROLE_LEVEL_NOT_ENOUGH, 2).
 -define(REASON_CODE_ROLE_ALREADY_SIGN, 3).
 -define(REASON_CODE_SIGN_NUM_IS_MAX, 4).
 -define(REASON_CODE_LOCAL_RACE_SERVER_IS_DOWN, 5).
 -define(REASON_CODE_CAN_NOT_GET_ROLE_INFO_FOR_RACE_SIGN, 6).
 */
void MB_LayerPerfectRaceApply::showError(uint8_t code)
{
    const char* pError[] = {"","不在报名时间内","角色等级不够","角色已报名","报名名额已满","系统错误","获取角色信息失败"};
    if (code==0||code>6)
    {
        return ;
    }
    
    MB_Message::sharedMB_Message()->showMessage(pError[code]);
}
void MB_LayerPerfectRaceApply::recvrace_info(MB_MsgBuffer* pRecv)
{
    if (m_pPerfectRaceInterface->getStep()!=STATUS_SIGN)
    {
        m_pPerfectRaceInterface->goNormalLayer();
    }
}
