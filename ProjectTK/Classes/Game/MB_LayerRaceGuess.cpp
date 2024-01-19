//
//  MB_LayerRaceGuess.cpp
//  ProjectPM
//
//  Create by WenYong on 22/6/2014.
//
//
#include "MB_LayerRaceGuess.h"
#include "MB_PerfectRaceInterface.h"
#include "MB_NodeSelectControl.h"

MB_LayerRaceGuess::MB_LayerRaceGuess()
{
    m_pNodePlayers[0]	 = NULL;
    m_pNodePlayers[1]	 = NULL;
    m_pNodePlayers[2]	 = NULL;
    m_pNodePlayers[3]	 = NULL;
    m_pNodePlayers[4]	 = NULL;
    m_pNodePlayers[5]	 = NULL;
    m_pNodePlayers[6]	 = NULL;
    m_pNodePlayers[7]	 = NULL;
    m_pNodeCoin[0]	 = NULL;
    m_pNodeCoin[1]	 = NULL;
    m_pNodeCoin[2]	 = NULL;
    m_pBtnGuess = NULL;
    m_nCoins[0] = 0;
    m_nCoins[1] = 0;
    m_nCoins[2] = 0;
    m_nSelectMoney   = 1;
    m_nSelectPlayer  = 1;
    
    m_bShowRoleInfoPanel = true;
    m_bShowEXP = true;
    
    m_pPerfectRaceInterface = NULL;
    SOCKET_MSG_REGIST(SC_RACE_GUESS, MB_LayerRaceGuess);
    
    m_bGuessed = false;
}
MB_LayerRaceGuess::~MB_LayerRaceGuess()
{
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[0]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[1]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[2]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[3]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[4]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[5]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[6]);
    CC_SAFE_RELEASE_NULL(m_pNodePlayers[7]);
    CC_SAFE_RELEASE_NULL(m_pNodeCoin[0]);
    CC_SAFE_RELEASE_NULL(m_pNodeCoin[1]);
    CC_SAFE_RELEASE_NULL(m_pNodeCoin[2]);
    CC_SAFE_RELEASE_NULL(m_pBtnGuess);
    
    m_pPerfectRaceInterface = NULL;
    SOCKET_MSG_UNREGIST(SC_RACE_GUESS);
}
bool MB_LayerRaceGuess::init()
{
    CCNode* pNode = loadResource("res/monsterrace_layer_bet.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        intUI();
		return true;
	}
	return false;
}
void MB_LayerRaceGuess::onResetWnd()
{
    if (m_pPerfectRaceInterface)
    {
        updatePlayer(1);
        updatePlayer(2);
        updatePlayer(3);
        updatePlayer(4);
        updatePlayer(5);
        updatePlayer(6);
        updatePlayer(7);
        updatePlayer(8);
        
        updateMoney(1);
        updateMoney(2);
        updateMoney(3);
    }
    m_pBtnGuess->setEnabled(!m_bGuessed);
}

void MB_LayerRaceGuess::updatePlayer(int pos)
{
    int index = pos - 1;
    if (index < 0 || index > 7)
    {
        return ;
    }
    
    MB_NodeSelectPlayer* pButton = dynamic_cast<MB_NodeSelectPlayer*>(m_pNodePlayers[index]->getChildByTag(pos));
    
    if (pButton)
    {
        pButton->onResetWnd();
    }
    else
    {
        MB_RacePos* pPos = m_pPerfectRaceInterface->queryFinalPlayerByPos(pos);
        if (pPos)
        {
            pButton = MB_NodeSelectPlayer::create();
            pButton->setText(pPos->getRoleName().c_str());
            pButton->setHeadID(pPos->getIsMale(),pPos->getHead(),pPos->getTitle());
            pButton->setTag(pos);
            m_pNodePlayers[index]->addChild(pButton);
        }
    }
    
    if (pButton)
    {
        if (m_nSelectPlayer==pos)
        {
            pButton->select();
        }
        else
        {
            pButton->unselect();
        }
    }
}

void MB_LayerRaceGuess::updateMoney(int pos)
{
    int index = pos - 1;
    if (index < 0 || index > 2)
    {
        return ;
    }
    
    MB_NodeSelectButton* pButton = dynamic_cast<MB_NodeSelectButton*>(m_pNodeCoin[index]->getChildByTag(pos+10));
    
    if (pButton)
    {
        pButton->onResetWnd();
    }
    else
    {
        pButton = MB_NodeSelectCoin::create();
        pButton->setText("");
        pButton->setTag(pos+10);
        m_pNodeCoin[index]->addChild(pButton);

    }
    
    if (pButton)
    {
        if (m_nSelectMoney==pos)
        {
            pButton->select();
        }
        else
        {
            pButton->unselect();
        }
    }
}

void MB_LayerRaceGuess::intUI()
{
    onResetWnd();
}

bool MB_LayerRaceGuess::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode1",CCNode*,m_pNodePlayers[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode2",CCNode*,m_pNodePlayers[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode3",CCNode*,m_pNodePlayers[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode4",CCNode*,m_pNodePlayers[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode5",CCNode*,m_pNodePlayers[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode6",CCNode*,m_pNodePlayers[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode7",CCNode*,m_pNodePlayers[6]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNode8",CCNode*,m_pNodePlayers[7]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCoin1",CCNode*,m_pNodeCoin[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCoin2",CCNode*,m_pNodeCoin[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeCoin3",CCNode*,m_pNodeCoin[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnGuess",CCControlButton*,m_pBtnGuess);
	return false;
}
SEL_MenuHandler MB_LayerRaceGuess::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerRaceGuess::onCloseClick);
	return NULL;
}
SEL_CCControlHandler MB_LayerRaceGuess::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onBetClick",MB_LayerRaceGuess::onBetClick);
	return NULL;
}

bool MB_LayerRaceGuess::setDataSource(CCFunctionDataSource* pDataSource)
{
    m_pPerfectRaceInterface = dynamic_cast<MB_PerfectRaceInterface*>(pDataSource);
    
    m_pDataSource = m_pPerfectRaceInterface;
    
    return m_pDataSource != NULL;
}
void MB_LayerRaceGuess::onCloseClick(CCObject* pSender)
{
    popWindow();
}
void MB_LayerRaceGuess::onBetClick(CCObject* pSender)
{
    if (m_bGuessed || m_pPerfectRaceInterface==NULL)
    {
        return;
    }
    
    MB_Message::sharedMB_Message()->showMessage("",15);
    uint32_t nRoleID = 0;
    uint32_t nGuessCoin = 0;
    getSelectInfo(nRoleID,nGuessCoin);
    if(nRoleID == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("不能竞猜该玩家");
        return;
    }
    m_pPerfectRaceInterface->sendrace_guess(nRoleID,nGuessCoin);
}
void MB_LayerRaceGuess::getSelectInfo(uint32_t& nRoleID,uint32_t& nCoin)
{
    if (m_pPerfectRaceInterface==NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("数据异常");
        return;
    }
    
    nRoleID = getSelectRoleID();
    nCoin = getSelectMoney();
}


void MB_LayerRaceGuess::onNewPlayerSelect(int pos)
{
    if (pos != m_nSelectPlayer)
    {
        int old = m_nSelectPlayer;
        m_nSelectPlayer = pos;
        updatePlayer(old);
        updatePlayer(m_nSelectPlayer);
    }
}
void MB_LayerRaceGuess::onNewMoneySelect(int pos)
{
    if (pos != m_nSelectMoney)
    {
        int old = m_nSelectMoney;
        m_nSelectMoney = pos;
        updateMoney(old);
        updateMoney(m_nSelectMoney);
    }
}
void MB_LayerRaceGuess::onControlClicked(CCObject* pControl)
{
    if (m_bGuessed)
    {
        MB_Message::sharedMB_Message()->showMessage("已竞猜, 不可再选择");
        return;
    }
    MB_NodeSelectControl* pTarget = dynamic_cast<MB_NodeSelectControl*>(pControl);
    
    if (pControl)
    {        
        int tag = pTarget->getTag();
        if (tag < 10)
        {
            onNewPlayerSelect(tag);
        }
        else
        {
            onNewMoneySelect(tag-10);
        }
    }
}

/*
 message recvrace_guess[id=13432]{
 required        int8            result                  =1;//0成功，1金币不足，2不在竞猜时间内，3已竞猜,4非法RoleID，5非法金币数量
 }
 */
void MB_LayerRaceGuess::onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    if (nMsg == SC_RACE_GUESS)
    {
        uint8_t u8 = 0;
        pRecv->readU8(&u8);
        if (u8 == 0)
        {
            MB_Message::sharedMB_Message()->showMessage("竞猜成功");
            m_bGuessed = true;
            m_pBtnGuess->setEnabled(!m_bGuessed);
        }
        else if(u8 == 1)
        {
            MB_Message::sharedMB_Message()->showMessage("金币不足");
        }
        else if(u8 == 2)
        {
            MB_Message::sharedMB_Message()->showMessage("不在竞猜时间内");
        }
        else if(u8 == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("已竞猜");
        }
        else if(u8 == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("选择的选手不正确");
        }
        else if(u8 == 5)
        {
            MB_Message::sharedMB_Message()->showMessage("非法金币数量");
        }
    }
}

void MB_LayerRaceGuess::setCoinList(uint32_t *pArray,uint16_t len)
{
    len = len > 3 ? 3 : len;
    MB_NodeSelectControl* pControl = NULL;
    char buff[64] = {};
    for (uint16_t i=0; i<len; ++i)
    {
        m_nCoins[i] = pArray[i];
        pControl = dynamic_cast<MB_NodeSelectControl*>(m_pNodeCoin[i]->getChildByTag(11+i));
        if (pControl)
        {
            sprintf(buff, "%d",pArray[i]);
            pControl->setText(buff);
        }
    }
}
void MB_LayerRaceGuess::setGuessInfo(uint32_t nRoleID,uint32_t nCoin)
{
    
    setGuessedRole(nRoleID);
    setGuessedCoin(nCoin);
    
    m_bGuessed = (nRoleID!=0);
    m_pBtnGuess->setEnabled(!m_bGuessed);
}

void MB_LayerRaceGuess::setGuessedRole(uint32_t nRoleID)
{
    if (m_pPerfectRaceInterface)
    {
        MB_RacePos* pPos = m_pPerfectRaceInterface->queryFinalPlayerByRoleID(nRoleID,8);
        if (pPos)
        {
            int old = m_nSelectPlayer;
            m_nSelectPlayer = pPos->getPos();
            updatePlayer(old);
            updatePlayer(m_nSelectPlayer);
        }
    }
}
void MB_LayerRaceGuess::setGuessedCoin(uint32_t nCoin)
{
    for (int i=0; i<3; ++i)
    {
        if (m_nCoins[i]==nCoin)
        {
            int old = m_nSelectMoney;
            m_nSelectMoney = i+1;
            updateMoney(old);
            updateMoney(m_nSelectMoney);
        }
    }
}

uint32_t MB_LayerRaceGuess::getSelectRoleID()
{
    MB_RacePos* pPos = m_pPerfectRaceInterface->queryFinalPlayerByPos(m_nSelectPlayer);
    if (pPos)
    {
        return pPos->getRoleId();
    }
    return 0;
}

uint32_t MB_LayerRaceGuess::getSelectMoney()
{
    int index = m_nSelectMoney-1;
    if (index < 0 || index > 2)
    {
        return 0;
    }
    
    return m_nCoins[index];
}
