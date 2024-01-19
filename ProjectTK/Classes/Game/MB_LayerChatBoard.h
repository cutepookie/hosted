
#ifndef __ProjectMB__MB_LayerChatBoard__
#define __ProjectMB__MB_LayerChatBoard__

#include "Game.h"

class MB_LayerChatBoard:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
    std::string m_strRoleName;
    CCLabelTTF *m_pRoleName;
    uint32_t m_nRoleId;
    
    public :
    
    MB_LayerChatBoard();
    ~MB_LayerChatBoard();
    virtual bool init(const char *roleName,uint32_t roleID);
    static MB_LayerChatBoard * create(const char *roleName,uint32_t roleID);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void onMailClick(CCObject *);
    void onAddFriendClick(CCObject *);
    void onCompareClick(CCObject *);
    void onGagClick(CCObject *);
    void onCloseClick(CCObject *);
    void onMsgRecv(CCNode* node, SocketResponse* response);
protected:
    void throwIntoBlackOder(CCObject* pSender);
    void tellServer(CCObject* pSender);
};

#endif /* defined(__ProjectMB__MB_LayerChatBoard__) */
