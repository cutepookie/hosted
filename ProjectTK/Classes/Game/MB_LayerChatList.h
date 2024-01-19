
#ifndef __ProjectMB__MB_LayerChatList__
#define __ProjectMB__MB_LayerChatList__
#include "Game.h"

class MB_ChatData;
class MB_NodeChatInformation;
class MB_LayerChatList :public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver,
public CCEditBoxDelegate
{
private:
    CCNode *m_pNodeChat;
    CCNode *m_pNodeEdit;
    CCNode* m_pPrivateNode;
    CCLabelTTF *m_pLabelMoney;
    CCEditBox *m_pEditChat;
    CCMenuItemImage *m_pMenuItem;
    CCSize m_nNodeSize;
    CCLabelTTF* m_pTargetName;
    CCTableView *m_pTableView;
    std::string m_pString;
    CCControlButton*        m_pSendButton;
    CCNode*     m_pNodeFeedBack;
    //频道，1世界频道，3联盟频道
    uint8_t   m_nChannelType;
    CCArray*    getCurrentChatList();
    void resetStatus();
    void updateStatus(float dt);
    void enableTalk();
    CCScrollView* m_pScrollView;
    MB_NodeChatInformation* queryItemByData(MB_ChatData* data);
    void removeNodeNotUsed();
    void resetChatNodes();
    CCArray* m_pChatNodes;
    void onChannelWorldClicked(CCObject *);
    void onChannelPrivateClicked(CCObject *);
    void onFriendClicked(CCObject *);

    CCNode* m_pNodeNewPersonMsg;
    CCNode* m_pNodeNewWorldMsg;

    CCMenuItemImage* m_pPrivateBtn;
    CCMenuItemImage* m_pWorldBtn;
    
    bool m_bRoleInfoVisiable;
    
public:
    static uint32_t m_nPrivateChatRoleID;
    static std::string m_strPrivateChatRoleName;
    static void PersonChatSence(uint32_t roleID,const char* rolename)
    {
        CCLayer *layer = MB_LayerChatList::create();
        layer->setTag(LAYER_CHAT_LIST_TAG);
        
        MB_LayerChatList* pChatList = dynamic_cast<MB_LayerChatList*>(layer);
        pChatList->personChat(roleID, rolename);
        
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer,Z_ORDER_CHATLIST);
    }
    void onEnter();
    void onExit();
public:
    MB_LayerChatList();
    ~MB_LayerChatList();
    virtual bool init();
    virtual void onResetWnd();
    static  MB_LayerChatList  * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onBackClicked(CCObject *);
    void onCommitClicked(CCObject *);
    void initEdit(CCEditBox *pEdit);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text) ;
    virtual void editBoxReturn(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void onSendTouch(CCObject *);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void goCharge(CCObject *);
    void onGogClicked(CCObject *);    
    void personChat(int32_t roleid,const char* name,bool updata = true);

    void onPetTeamDataDtl(MB_MsgBuffer* recvPacket);
    void sendpet_view_other_dtl(uint32_t roleid,uint16_t serverid);
};

#endif /* defined(__ProjectMB__MB_LayerChatList__) */
