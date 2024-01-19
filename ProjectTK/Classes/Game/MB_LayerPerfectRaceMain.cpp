//
//  MB_LayerPerfectRaceMain.cpp
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#include "MB_LayerPerfectRaceMain.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_NodePerfectRacePlayerHead.h"
#include "MB_FunctionMgr.h"
#include "MB_LayerRaceGuess.h"
MB_LayerPerfectRaceMain::MB_LayerPerfectRaceMain()
{
    for (uint16_t i=0; i<14; ++i)
    {
        m_pLines[i] = NULL;
    }
    for (uint16_t i=0; i<9; ++i)
    {
        m_pHeadNode[i] = NULL;
    }
    for (uint16_t i=0; i<7; ++i)
    {
        m_pControlButton[i] = NULL;
    }
    
    m_pPerfectRaceInterface = NULL;
    m_pTimeTitle = NULL;
    m_pTime = NULL;
    m_pKingName = NULL;
    m_pSelfDetail = NULL;
    m_pGuessButton = NULL;
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    SOCKET_MSG_REGIST(SC_RACE_INFO, MB_LayerPerfectRaceMain);
    SOCKET_MSG_REGIST(SC_RACE_NEW_FIRST, MB_LayerPerfectRaceMain);
    SOCKET_MSG_REGIST(SC_RACE_NEW_STATUS,MB_LayerPerfectRaceMain);
    SOCKET_MSG_REGIST(SC_RACE_GUESS_INFO, MB_LayerPerfectRaceMain);
}

MB_LayerPerfectRaceMain::~MB_LayerPerfectRaceMain()
{
    m_pPerfectRaceInterface->setOpenRaceMainOrRaceApply(false);
    for (uint16_t i=0; i<14; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pLines[i]);
    }
    for (uint16_t i=0; i<9; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pHeadNode[i]);
    }
    for (uint16_t i=0; i<7; ++i)
    {
        CC_SAFE_RELEASE_NULL(m_pControlButton[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pKingName);
    CC_SAFE_RELEASE_NULL(m_pTimeTitle);
    CC_SAFE_RELEASE_NULL(m_pTime);
    CC_SAFE_RELEASE_NULL(m_pSelfDetail);
    CC_SAFE_RELEASE_NULL(m_pGuessButton);
    
    SOCKET_MSG_UNREGIST(SC_RACE_INFO);
    SOCKET_MSG_UNREGIST(SC_RACE_NEW_FIRST);
    SOCKET_MSG_UNREGIST(SC_RACE_NEW_STATUS);
    SOCKET_MSG_UNREGIST(SC_RACE_GUESS_INFO);
}

bool MB_LayerPerfectRaceMain::init()
{
    CCNode* pNode = loadResource("res/monsterrace_layer_semi.ccbi");
    
    if (pNode)
    {
        addChild(NSGameHelper::createDisableTouchLayer1());
        addChild(pNode);
        m_pKingName->setVisible(false);
        onResetWnd();
        schedule(schedule_selector(MB_LayerPerfectRaceMain::updateTime),1.0f);
        m_pPerfectRaceInterface->setOpenRaceMainOrRaceApply(true);
        return true;
    }
    
    return false;
}


void MB_LayerPerfectRaceMain::onEnterTransitionDidFinish()
{
    MB_FunctionMainWnd::onEnterTransitionDidFinish();
    PlayBackGround(ksSound_ShiLianInner);
}
void MB_LayerPerfectRaceMain::updateTime()
{
    if (m_pPerfectRaceInterface->getTimeStap()==STATUS_NOT_OPEN)
    {
        unscheduleAllSelectors();
        return;
    }
    
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shilian.plist"); m_pTimeTitle->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bzzz_txt_%d.png",m_pPerfectRaceInterface->getStep()+1)->getCString()));
    int left_time = m_pPerfectRaceInterface->getTimeStap() - MB_ClientSocket::getInstance()->getServerTime();
    if (left_time <= 0)
    {
        m_pTime->setString("00:00:00");
    }
    else
    {
        const char* pTime = NSGameHelper::formatTimeStringHMS_colon(left_time);
        m_pTime->setString(pTime);
    }

}
void MB_LayerPerfectRaceMain::updateSelfDetail()
{
    if (m_pPerfectRaceInterface->getGroupId()==0)
    {
        m_pSelfDetail->setString("您没有参加本届霸主之战");
    }
    else
    {
        m_pSelfDetail->setVisible(true);
        char buff[64] = {};
        sprintf(buff, "您被分到第%d组",m_pPerfectRaceInterface->getGroupId());
        m_pSelfDetail->setString(buff);
    }
}


void MB_LayerPerfectRaceMain::onResetWnd()
{
    if (m_pPerfectRaceInterface)
    {
        updateTime();
        
        updateSelfDetail();
        
        updateAllPlayer();          //更新9个头像
        
        updaetRecordButton();       //更新回放按钮
        
        updateLine();
    }
}

bool MB_LayerPerfectRaceMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if(MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode))
    {
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_timeTitle", CCSprite*, m_pTimeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_time", CCLabelBMFont*, m_pTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_owen_group", CCLabelTTF*, m_pSelfDetail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ttf_kingname", CCLabelTTF*, m_pKingName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_guess", CCControlButton*, m_pGuessButton);
    char buff[32] = {};
    for (uint16_t i=0; i<14; ++i)
    {
        sprintf(buff, "line_%d", i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*, m_pLines[i]);
    }
    for (uint i=0; i<9; ++i)
    {
        sprintf(buff, "m_pNode%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*, m_pHeadNode[i]);
    }
    for (uint16_t i=0; i<7; ++i)
    {
        sprintf(buff, "btn%d",i+1);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, buff, CCNode*, m_pControlButton[i]);
    }
    
    return false;
}

SEL_MenuHandler MB_LayerPerfectRaceMain::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerPerfectRaceMain::onCloseClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRuleClicked", MB_LayerPerfectRaceMain::onRuleClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerPerfectRaceMain::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRecordClicked", MB_LayerPerfectRaceMain::onRecordClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onGuessClicked", MB_LayerPerfectRaceMain::onGuessClicked);
    return NULL;
}

void MB_LayerPerfectRaceMain::onRecordClicked(CCObject* pSender)
{
    CCNode* pNode = dynamic_cast<CCNode*>(pSender);
    if (pNode)
    {
        m_pPerfectRaceInterface->onFinalRecordClicked(pNode->getTag()+8);
    }
}

void MB_LayerPerfectRaceMain::onGuessClicked(CCObject* pSender)
{
    if (m_pPerfectRaceInterface)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pPerfectRaceInterface->sendrace_guess_info();
//        MB_ResWindow* pWnd = m_pPerfectRaceInterface->createGuessDialog();
//        if (pWnd)
//        {
//            pushWindow(pWnd);
//        }
    }
}

bool MB_LayerPerfectRaceMain::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    if (m_pPerfectRaceInterface)
    {
        m_pDataSource = m_pPerfectRaceInterface;
    }
    
    return m_pPerfectRaceInterface != NULL;
}

void MB_LayerPerfectRaceMain::onMsgRecv(CCNode* node, SocketResponse* response)
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
    
    switch (Msg)
    {
        case SC_RACE_INFO:
            recvrace_info(recvPacket);
            break;
        case SC_RACE_NEW_FIRST:
            onResetWnd();
            break;
        case SC_RACE_NEW_STATUS:
            onResetWnd();
            break;
        case SC_RACE_GUESS_INFO:
            recvrace_guess_info(recvPacket);
            break;
        default:
            break;
    }

}


void MB_LayerPerfectRaceMain::onRuleClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    pushWindow(m_pPerfectRaceInterface->createRuleDialog());
}


void MB_LayerPerfectRaceMain::updateAllPlayer()
{
    int pos = 1;
    MB_RacePos* pRacePos = NULL;
    
    // top 8
    for (pos=1; pos<9; ++pos)
    {
        pRacePos = m_pPerfectRaceInterface->queryFinalPlayerByPos(pos);
        if (pRacePos==NULL)
        {
            return;
        }
        updatePlayer(pRacePos);
    }
    
    // king
    pRacePos = m_pPerfectRaceInterface->queryFinalPlayerByPos(15);
    if (pRacePos)
    {
        updatePlayer(pRacePos);
    }
}

void MB_LayerPerfectRaceMain::updaetRecordButton()
{
    for (int pos=9; pos<16; ++pos)
    {
        if (m_pPerfectRaceInterface->queryFinalPlayerByPos(pos)!=NULL)
        {
            m_pControlButton[pos-9]->setVisible(true);
        }
        else
        {
            m_pControlButton[pos-9]->setVisible(false);
        }
    }
    
    if(m_pPerfectRaceInterface->getStep()>=STATUS_WAIT_FOUR_FIGHT)
    {
        m_pGuessButton->setVisible(!m_pPerfectRaceInterface->getIsLiving());
    }
    else
    {
        m_pGuessButton->setVisible(false);
    }
    
    //直播中不显示时间
    m_pTime->setVisible(!m_pPerfectRaceInterface->getIsLiving());
}

void MB_LayerPerfectRaceMain::checkLine(int pos1,CCNode* pLine1,int pos2,CCNode* pLine2,int targetPos)
{
    MB_RacePos* target = m_pPerfectRaceInterface->queryFinalPlayerByPos(targetPos);
    
    if (target == NULL)
    {
        pLine1->setVisible(false);
        pLine2->setVisible(false);
    }
    else
    {
        MB_RacePos* p1 = m_pPerfectRaceInterface->queryFinalPlayerByPos(pos1);
        MB_RacePos* p2 = m_pPerfectRaceInterface->queryFinalPlayerByPos(pos2);
        if (p1 && p2)
        {
            pLine1->setVisible(target->getRoleId() == p1->getRoleId());
            pLine2->setVisible(target->getRoleId() == p2->getRoleId());
        }
        else
        {
            // exception here
        }
    }
}

void MB_LayerPerfectRaceMain::updateLine()
{
    // 8->4
    checkLine(1, m_pLines[0], 2, m_pLines[1], 9);
    checkLine(3, m_pLines[2], 4, m_pLines[3], 10);
    checkLine(5, m_pLines[4], 6, m_pLines[5], 11);
    checkLine(7, m_pLines[6], 8, m_pLines[7], 12);
    
    // 4->2
    checkLine(9, m_pLines[8], 11, m_pLines[10], 13);
    checkLine(10, m_pLines[9], 12, m_pLines[11], 14);
    
    // 2->1
    checkLine(13, m_pLines[12], 14, m_pLines[13], 15);
}

void MB_LayerPerfectRaceMain::updatePlayer(MB_RacePos* pRacePos)
{
    int pos = pRacePos->getPos();
    if (pos > 0 && pos < 9)
    {
        MB_NodePerfectRacePlayerHead* pNode = MB_NodePerfectRacePlayerHead::create(pRacePos);
        if (pNode)
        {
            pNode->setClickEnable(false);
            m_pHeadNode[pos-1]->removeAllChildren();
            m_pHeadNode[pos-1]->addChild(pNode);
        }
    }
    m_pKingName->setVisible(false);
    if (pos == 15)
    {
        MB_NodePerfectRacePlayerHead* pNode = MB_NodePerfectRacePlayerHead::create(pRacePos);
        if (pNode)
        {
            m_pHeadNode[8]->removeAllChildren();
            m_pHeadNode[8]->addChild(pNode);
            m_pKingName->setString(pNode->getRoleName()->getString());
            m_pKingName->setVisible(true);
            pNode->getRoleName()->setVisible(false);
        }
    }
}


void MB_LayerPerfectRaceMain::recvrace_info(MB_MsgBuffer* pRecv)
{
    if(m_pPerfectRaceInterface->getStep()==STATUS_SIGN)
    {
        m_pPerfectRaceInterface->goNormalLayer();
    }
    else
    {
        onResetWnd();
    }
    
}

/*
 message recvrace_guess_info[id=13430]{
 required        int32           guessCoin               =1;
 required        int32           roleID                  =2;
 repeated        int32           coinValList             =3;
 }
 
 */
void MB_LayerPerfectRaceMain::recvrace_guess_info(MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint32_t nCoin = 0;
    uint32_t nRoleID = 0;
    uint16_t count = 0;
    
    pRecv->readU32(&nCoin);
    pRecv->readU32(&nRoleID);
    
    pRecv->readU16(&count);
    
    uint32_t * pArray = NULL;
    if (count)
    {
        pArray = new uint32_t[count];
    }
    for (int i=0; i<count; ++i)
    {
        pRecv->readU32(&(pArray[i]));
    }
    
    MB_LayerRaceGuess* pWnd = dynamic_cast<MB_LayerRaceGuess*>(m_pPerfectRaceInterface->createGuessDialog());
    if (pWnd)
    {
        pWnd->setCoinList(pArray, count);
        pWnd->setGuessInfo(nRoleID, nCoin);
        pushWindow(pWnd);
    }
    CC_SAFE_DELETE_ARRAY(pArray);
}

void MB_LayerPerfectRaceMain::onCloseClick(CCObject* pSender)
{
    MB_FunctionMgr::getInstance()->goFunction(kFunctionBigWorld,this);
}
