
#ifndef __ProjectMB__MB_LayerInviteHelp__
#define __ProjectMB__MB_LayerInviteHelp__

#include "Game.h"

class MB_LayerInviteHelp:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver,
public MB_MessageEditDeleate{
    
    private:
    
    CCNode* m_pScrollView;
    CCNode* m_pCellSize;
    CCNode *m_pNodeISGet;
    CCLabelTTF *m_pHasInviteNum;
    CCNode *m_pNodeInvite1;
    CCNode *m_pNodeInvite2;
    CCLabelTTF *m_pFXCode;
    CCLabelTTF *m_pFXInviter;
    std::string m_pMessageSend;
    CCNode * m_pNodeWebChat;
    CCLabelTTF *m_pIsGet;
    
    public :
    
    MB_LayerInviteHelp();
    ~MB_LayerInviteHelp();
    virtual bool init();
    static  MB_LayerInviteHelp * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onResetWnd                  (void);
    void onCloseClicked(CCObject *);
    void onInputCodeClick(CCObject *);
    void onWeiBoSendClick(CCObject *);
    void onSMSSendClick(CCObject *);
    void onInvateRecordClick(CCObject *);
    void onWeiChatClicked(CCObject *);
    void onWeiChatFriendClicked(CCObject *);
    void onShowMessage();
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void getSelfCode(char *databuf);
    virtual void setString(const char *codeback);    
    bool sendinvite_input_invite_code(const char *string);
    bool recvinvite_input_invite_code(MB_MsgBuffer* recvPacket);
    bool sendinvite_list();
    bool recvinvite_list(MB_MsgBuffer *recvPacket);
    void onWebChatFriendClick(CCObject *);
    void onWebChatGroupClick(CCObject *);
};

#endif /* defined(__ProjectMB__MB_InviteHelp__) */
