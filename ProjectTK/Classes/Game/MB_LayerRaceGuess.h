//
//  MB_LayerRaceGuess.h
//  ProjectPM
//
//  Create by WenYong on 22/6/2014.
//
//
#ifndef __ProjectMB__MB_LayerRaceGuess__
#define __ProjectMB__MB_LayerRaceGuess__

#include "MB_FunctionMainWnd.h"
#include "MB_NodeSelectControl.h"
class MB_PerfectRaceInterface;
class MB_LayerRaceGuess : public MB_FunctionMainWnd,public MB_ControlEventDelegate
{
public:
	MB_LayerRaceGuess();
	virtual ~MB_LayerRaceGuess();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgDeliver(int nMsg,MB_MsgBuffer* pRecv);
    virtual void onControlClicked(CCObject* pControl);
    void setCoinList(uint32_t *pArray,uint16_t len);
    void setGuessInfo(uint32_t nRoleID,uint32_t nCoin);
    void getSelectInfo(uint32_t& nRoleID,uint32_t& nCoin);
protected:
    void intUI();
    void onCloseClick(CCObject* pSender);
    void onBetClick(CCObject* pSender);
    void updatePlayer(int pos);
    void updateMoney(int pos);
    void onNewPlayerSelect(int pos);
    void onNewMoneySelect(int pos);
    void setGuessedRole(uint32_t nRoleID);
    void setGuessedCoin(uint32_t nCoin);
    uint32_t getSelectRoleID();
    uint32_t getSelectMoney();
private:
    CCNode* m_pNodePlayers[8];
    CCNode* m_pNodeCoin[3];
    CCControlButton*    m_pBtnGuess;
    MB_PerfectRaceInterface*    m_pPerfectRaceInterface;
    int     m_nSelectPlayer;
    int     m_nSelectMoney;
    bool    m_bGuessed;
    uint32_t    m_nCoins[3];
};
#endif /* defined(__ProjectMB__MB_LayerRaceGuess__) */