//
//  MB_LayerPerfectRaceMain.h
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#ifndef __ProjectMB__MB_LayerPerfectRaceMain__
#define __ProjectMB__MB_LayerPerfectRaceMain__

#include "MB_FunctionMainWnd.h"
class MB_RacePos;
class MB_PerfectRaceInterface;
class MB_LayerPerfectRaceMain:public MB_FunctionMainWnd
{
public:
    MB_LayerPerfectRaceMain();
    ~MB_LayerPerfectRaceMain();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onEnterTransitionDidFinish();
protected:
    void onRuleClicked(CCObject* pSender);
    void onCloseClick(CCObject* pSender);
    void updateTime();
    void updateSelfDetail();
    void updateAllPlayer();
    void updatePlayer(MB_RacePos* pRacePos);
    void updaetRecordButton();
    void checkLine(int pos1,CCNode* pLine1,int pos2,CCNode* pLine2,int targetPos);
    void updateLine();
    void recvrace_info(MB_MsgBuffer* pRecv);
    void onRecordClicked(CCObject* pSender);
    void onGuessClicked(CCObject* pSender);
    void recvrace_guess_info(MB_MsgBuffer* pRecv);
private:
    MB_PerfectRaceInterface*    m_pPerfectRaceInterface;
    CCNode*     m_pLines[14];
    CCNode*     m_pHeadNode[9];
    CCLabelTTF* m_pKingName;
    CCSprite* m_pTimeTitle;
    CCLabelBMFont* m_pTime;
    CCLabelTTF* m_pSelfDetail;
    CCNode*     m_pControlButton[7];        //回放按钮
    CCControlButton* m_pGuessButton;
};


#endif /* defined(__ProjectMB__MB_LayerPerfectRaceMain__) */
