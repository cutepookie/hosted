//
//  MB_LayerPerfectRaceApply.h
//  ProjectPM
//
//  Created by WenYong on 14-4-23.
//
//

#ifndef __ProjectMB__MB_LayerPerfectRaceApply__
#define __ProjectMB__MB_LayerPerfectRaceApply__

#include "MB_FunctionMainWnd.h"

class MB_PerfectRaceInterface;

class MB_LayerPerfectRaceApply:public MB_FunctionMainWnd
{
public:
    MB_LayerPerfectRaceApply();
    ~MB_LayerPerfectRaceApply();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onEnterTransitionDidFinish();
protected:
    void updateTime();
    void onPreRaceRecordClicked(CCObject* pSender);
    void onRaceRuleClicked(CCObject* pSender);
    void onGroupRecordClicked(CCObject* pSender);
    void onSignClicked(CCObject* pSender);
    void onCloseClicked(CCObject* pSender);
    void recvrace_sign(MB_MsgBuffer* pRecv);
    void recvrace_info(MB_MsgBuffer* pRecv);
    void showError(uint8_t code);
private:
    MB_PerfectRaceInterface* m_pPerfectRaceInterface;
    CCSpriteFrame*      m_pSelectFrame;
    CCSpriteFrame*      m_pUnselectFrame;
    CCSprite*     m_pTimeTitle;
    CCLabelBMFont*     m_pTime;
    CCLabelTTF*     m_pSigned;
    CCControlButton*m_pBtnSign;
    CCLabelTTF*     m_pSpriteKingName;
    CCNode*         m_pNodeKingName;
};

#endif /* defined(__ProjectMB__MB_LayerPerfectRaceApply__) */
