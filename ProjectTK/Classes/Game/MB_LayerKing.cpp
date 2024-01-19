//
//  MB_LayerKing.cpp
//  ProjectMB
//
//  Created by yuanwugang on 15-1-14.
//
//

#include "MB_LayerKing.h"
#include "MB_LayerFunctionRule.h"
#include "MB_FunctionModule.h"
#include "MB_FunctionKingInterface.h"
#include "MB_KingProtocol.h"
#include "MB_NodeRocketTeamDamage.h"
MB_LayerKing::MB_LayerKing()
{
    m_pFunction = NULL;
    m_pTTFLastTimeTitle = NULL;
    m_pTTFLastTimeValue = NULL;
    m_pTTFReviveTime = NULL;
    m_pNodeRevive = NULL;
    for (int i = 0;i < 4;i++)
    {
        m_pSpriteBoosHead[i] = NULL;
        m_pTTFBoosName[i] = NULL;
    }
    m_pNodeFightInfo = NULL;
    m_pTTFCurBossName = NULL;
    m_pSpriteBossHP = NULL;
    m_pTTFBossHp = NULL;
    m_pBossHP = NULL;
    m_pNodeHarm = NULL;
    m_pBtFight = NULL;
    m_bHasKing = false;
    m_pTTFReviveMoney = NULL;
    m_bShowRoleInfoPanel = true;
    m_bFirstEnter = true;
    SOCKET_MSG_REGIST(SC_KING_OPEN, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_INIT_STATE, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_STOP, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_FIGHT, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_OPEN_TIME, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_HP_SYNC, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_KING_HARM_BROADCAST, MB_LayerKing);
    SOCKET_MSG_REGIST(SC_PUSH_HIGHLIGHT_INFO, MB_LayerKing);
}
MB_LayerKing::~MB_LayerKing()
{
    if (m_pFunction && !m_bFirstEnter)
    {
        m_pFunction->cs_king_close();
    }

    CC_SAFE_RELEASE_NULL(m_pTTFLastTimeTitle);
    CC_SAFE_RELEASE_NULL(m_pTTFLastTimeValue);
    CC_SAFE_RELEASE_NULL(m_pTTFReviveTime);
    CC_SAFE_RELEASE_NULL(m_pNodeRevive);
    for (int i = 0;i < 4;i++)
    {
        CC_SAFE_RELEASE_NULL(m_pSpriteBoosHead[i]);
        CC_SAFE_RELEASE_NULL(m_pTTFBoosName[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pNodeFightInfo);
    CC_SAFE_RELEASE_NULL(m_pTTFCurBossName);
    CC_SAFE_RELEASE_NULL(m_pSpriteBossHP);
    CC_SAFE_RELEASE_NULL(m_pTTFBossHp);
    CC_SAFE_RELEASE_NULL(m_pNodeHarm);
    CC_SAFE_RELEASE_NULL(m_pBtFight);
    CC_SAFE_RELEASE_NULL(m_pTTFReviveMoney);
    CC_SAFE_RELEASE_NULL(m_pBossHP);
    SOCKET_MSG_UNREGIST(SC_KING_OPEN);
    SOCKET_MSG_UNREGIST(SC_KING_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_KING_STOP);
    SOCKET_MSG_UNREGIST(SC_KING_FIGHT);
    SOCKET_MSG_UNREGIST(SC_KING_OPEN_TIME);
    SOCKET_MSG_UNREGIST(SC_KING_HP_SYNC);
    SOCKET_MSG_UNREGIST(SC_KING_HARM_BROADCAST);
    SOCKET_MSG_UNREGIST(SC_PUSH_HIGHLIGHT_INFO);
}
bool MB_LayerKing::init()
{
    CCNode* node = loadResource("res/king_layer_main.ccbi");
    if (node)
    {
        this->addChild(node);
        
        //开启计时器
        this->schedule(schedule_selector(MB_LayerKing::updataTick),1.0f);
        return true;
    }
    return false;
}
void MB_LayerKing::onResetWnd()
{
    if (m_pBossHP == NULL)
    {
        m_pSpriteBossHP->setVisible(false);
        CCNode *node=m_pSpriteBossHP->getParent();
        CCPoint pos=m_pSpriteBossHP->getPosition();
        int z= m_pSpriteBossHP->getZOrder();
        float scalex = m_pSpriteBossHP->getScaleX();
        float scaley = m_pSpriteBossHP->getScaleY();
        
        CCSprite* sprite =CCSprite::createWithSpriteFrame(m_pSpriteBossHP->displayFrame());
        m_pBossHP = CCProgressTimer::create(sprite);
        CC_SAFE_RETAIN(m_pBossHP);
        m_pBossHP->setType(kCCProgressTimerTypeBar);
        m_pBossHP->setMidpoint(ccp(0,1));
        m_pBossHP->setBarChangeRate(ccp(1, 0));
        m_pBossHP->setPosition(pos);
        m_pBossHP->setScaleX(scalex);
        m_pBossHP->setScaleY(scaley);
        node->addChild(m_pBossHP ,z );
    }
    resetBoosInfo();
    resetBossIcon();
    updataTick(0);
    
}
bool MB_LayerKing::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLastTimeTitle",CCLabelTTF*,m_pTTFLastTimeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFLastTimeValue",CCLabelTTF*,m_pTTFLastTimeValue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFReviveTime",CCLabelTTF*,m_pTTFReviveTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeRevive",CCNode*,m_pNodeRevive);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeFightInfo",CCNode*,m_pNodeFightInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFCurBossName",CCLabelTTF*,m_pTTFCurBossName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFBossHp",CCLabelTTF*,m_pTTFBossHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSpriteBossHP",CCSprite*,m_pSpriteBossHP);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeHarm",CCNode*,m_pNodeHarm);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtFight",CCMenuItemImage*,m_pBtFight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pTTFReviveMoney",CCLabelTTF*,m_pTTFReviveMoney);
    char str1[64] = "m_pSpriteBoosHead1";
    char str2[64] = "m_pTTFBoosName1";
    for (int i = 0;i < 4;i++)
    {
        str1[17] = '1'+i;
        str2[14] = '1'+i;
        if (strcmp(str1,pMemberVariableName) == 0)
        {
            CCB_MEMBERVARIABLEASSIGNER_GLUE(this,str1,CCSprite*,m_pSpriteBoosHead[i]);
        }
        if (strcmp(str2,pMemberVariableName) == 0)
        {
            CCB_MEMBERVARIABLEASSIGNER_GLUE(this,str2,CCLabelTTF*,m_pTTFBoosName[i]);
        }
    }

    return false;
}
SEL_MenuHandler MB_LayerKing::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onFightClicked",MB_LayerKing::onFightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicker",MB_LayerKing::onCloseClicker);
    return NULL;
}
SEL_CCControlHandler MB_LayerKing::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onRuleClicked",MB_LayerKing::onRuleClicked);
   
    return NULL;
}

void MB_LayerKing::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    switch (nMsg)
    {
        case SC_KING_OPEN:
            MB_Message::sharedMB_Message()->removeALLMessage();
            onResetWnd();
            break;
        case SC_KING_INIT_STATE:
            MB_Message::sharedMB_Message()->removeALLMessage();
            onResetWnd();
            break;
        case SC_KING_STOP:
            onResetWnd();
            for (int i = 4;i > 0;i--)
            {
                m_pSpriteBoosHead[i-1]->setColor(ccc3(255,255,255));
            }
            
            break;
        case SC_KING_FIGHT:
            MB_Message::sharedMB_Message()->removeALLMessage();
            onResetWnd();
            m_pBtFight->setEnabled(true);
            break;
        case SC_KING_OPEN_TIME:

            break;
        case SC_KING_HP_SYNC:
            resetBoosInfo();
            break;
        case SC_KING_HARM_BROADCAST:
            sc_king_harm_broadcast(pRecv);
            break;
            
        case SC_PUSH_HIGHLIGHT_INFO:
            uint8_t data8;
            pRecv->readU8(&data8);
            if(data8 == 1)
            {
                m_pFunction->cs_king_open();
            }
            break;
        default:
            break;
    }
}
/*
 // 广播玩家造成的伤害
 message	sc_hula_harm_broadcast[id=14011]{
 repeated	p_hula_harm	harmList		=1;//玩家造成的伤害列表，为时间逆序发送到客户端，列表第一个为最近的一次伤害
 }
 */
void MB_LayerKing::sc_king_harm_broadcast(MB_MsgBuffer* pRecv)
{
    uint16_t data16;
    int data64;
    pRecv->readU16(&data16);
    for(int i = 0 ; i < data16 ; i++){
        
        char *str =pRecv->ReadString();
        pRecv->readU64(&data64);
        MB_NodeRocketTeamDamage *ptr = MB_NodeRocketTeamDamage::create(data64,str);
        int rangeX = m_pNodeHarm->getContentSize().width;
        int rangeY = m_pNodeHarm->getContentSize().height;
        ptr->setPosition(ccp(rand()%rangeX,rand()%rangeY));
        m_pNodeHarm->addChild(ptr);
        CC_SAFE_FREE(str);
    }
}

bool MB_LayerKing::setDataSource(CCFunctionDataSource* pDataSource)
{
    if (pDataSource)
    {
        m_pFunction = dynamic_cast<MB_FunctionKingInterface*>(pDataSource);
        return m_pFunction != NULL;
    }
    return false;
}
void MB_LayerKing::onRuleClicked(CCObject*)
{
    MB_ResWindow* pWnd = MB_LayerFunctionRule::create(kFunctionKing);
    if (pWnd)
    {
        pWnd->setShowRoleInfoPanel(true);
        pushWindow(pWnd);
    }
}
void MB_LayerKing::onFightClicked(CCObject*)
{

    if (!m_bHasKing || !m_pFunction->getIsOpen())
    {
        MB_Message::sharedMB_Message()->showMessage("活动未开启");
        return;
    }

    static int lasttime = 0;
    uint32_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
    int reborntime = m_pFunction->getKingInfo()->getRebornTime() - nowtime;
    if (reborntime <= 0 && (nowtime - lasttime > 0))
    {
        lasttime = nowtime;
        m_pBtFight->setEnabled(false);
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pNodeHarm->removeAllChildren();
        m_pFunction->cs_king_fight();
    }
    else
    {
        
        int money = atoi(m_pTTFReviveMoney->getString());
        if (MB_RoleData::getInstance()->getGold()+MB_RoleData::getInstance()->getGoldBoune() >= money && (nowtime - lasttime > 0)) {
            lasttime = nowtime;
            m_pBtFight->setEnabled(false);
            MB_Message::sharedMB_Message()->showMessage("",15);
            m_pNodeHarm->removeAllChildren();
            m_pFunction->cs_king_reborn();
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("等待复活中");
        }
        
        
    }
    
}
void MB_LayerKing::onCloseClicker(CCObject*)
{

    MB_FunctionMgr::getInstance()->goFunction(kFunctionHome, this);
}

void MB_LayerKing::onEnter()
{
    MB_FunctionMainWnd::onEnter();
    if (m_bFirstEnter)
    {
        MB_Message::sharedMB_Message()->showMessage("",15);
        m_pFunction->cs_king_open();
        m_bFirstEnter = false;
    }
}



void MB_LayerKing::resetBoosInfo()
{
    bool bIsOpen = m_pFunction->getIsOpen();
    if (bIsOpen)
    {
        bool bShow = false;
        m_pNodeFightInfo->setVisible(true);
        for (int i = 4;i > 0;i--)
        {
            KingBossState* bossState = m_pFunction->getKingInfo()->getBossStateByID(i);
            if (bossState != NULL && bossState->getCurHP() != 0)
            {
                m_pBossHP->setPercentage(bossState->getCurHP()*100.0f/bossState->getMaxHP());
                char str[134] = "";
                sprintf(str,"%llu/%llu",bossState->getCurHP(),bossState->getMaxHP());
                m_pTTFBossHp->setString(str);
                m_pTTFCurBossName->setString(bossState->getRoleName().c_str());
                bShow = true;
                break;
            }
        }
        m_pBossHP->setVisible(bShow);
        m_pTTFBossHp->setVisible(bShow);
        m_pTTFCurBossName->setVisible(bShow);
        m_pNodeFightInfo->setVisible(bShow);
    }
    else
    {
        m_pNodeFightInfo->setVisible(false);
    }
}

void MB_LayerKing::resetBossIcon()
{

    for (int i = 4;i > 0;i--)
    {
        KingBossInfo* bossInfo = m_pFunction->getKingInfo()->getBossInfoByID(i);
        if (bossInfo)
        {
            m_bHasKing = true;
            m_pTTFBoosName[i-1]->setString(bossInfo->getRoleName().c_str());
            NSGameHelper::setRoleIcon(m_pSpriteBoosHead[i-1], bossInfo->getIsMale(), bossInfo->getHead(), bossInfo->getTitle());
        }
    }
    
    bool bIsOpen = m_pFunction->getIsOpen();
    if (bIsOpen && m_bHasKing)
    {
        for (int i = 4;i > 0;i--)
        {
            KingBossState* bossState = m_pFunction->getKingInfo()->getBossStateByID(i);
            if (m_pSpriteBoosHead[i-1])
            {
                if (bossState != NULL && bossState->getCurHP() == 0)
                {
                    m_pSpriteBoosHead[i-1]->setColor(ccc3(128,128,128));
                }
                else
                {
                    m_pSpriteBoosHead[i-1]->setColor(ccc3(255,255,255));
                }
            }
        }
    }

}


void MB_LayerKing::updataTick(float dt)
{
    m_pNodeRevive->setVisible(false);
    bool bIsOpen = m_pFunction->getIsOpen();
    uint32_t nowtime = MB_ClientSocket::getInstance()->getServerTime();
    if(bIsOpen)
    {
        for (int i = 4;i > 0;i--)
        {
            KingBossState* bossState = m_pFunction->getKingInfo()->getBossStateByID(i);
            if (bossState != NULL)
            {
                if (bossState->getCurHP() != 0)
                {
                    break;
                }
                else
                {
                    m_pSpriteBoosHead[i-1]->setColor(ccc3(128,128,128));
                }
            }

        }
        
        //复活倒计时
        int reborntime = m_pFunction->getKingInfo()->getRebornTime() -nowtime;
        if (reborntime > 0 && m_bHasKing)
        {
            m_pNodeRevive->setVisible(true);
            char str[32] = "";
            sprintf(str,"%d",reborntime);
            m_pTTFReviveTime->setString(str);
        }
       

        //精灵王结束倒计时
        m_pTTFLastTimeTitle->setString("精灵王结束倒计时");
        int lasttime = m_pFunction->getKingInfo()->getEndTime() - nowtime;
        if (lasttime > 0) {
            const char* str = NSGameHelper::formatTimeStringHMS(lasttime);
            m_pTTFLastTimeValue->setString(str);
        }
        else
        {
            m_pTTFLastTimeValue->setString("--:--");
        }
        
    }
    else
    {
        m_pTTFLastTimeTitle->setString("精灵王开始倒计时");
        int lasttime = m_pFunction->getKingInfo()->getOpenTime() - nowtime;
        if (lasttime > 0) {
            const char* str = NSGameHelper::formatTimeStringHMS(lasttime);
            m_pTTFLastTimeValue->setString(str);
        }
        else
        {
            m_pTTFLastTimeValue->setString("--:--");
        }
    }
    
    
    if (m_bHasKing)
    {
        m_pTTFLastTimeValue->setVisible(true);
    }
    else
    {
        m_pTTFLastTimeTitle->setString("活动未开启");
        m_pTTFLastTimeValue->setVisible(false);
    }
}

