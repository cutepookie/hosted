//
//  MB_LayerRoleDetail.h
//  ProjectMB
//
//  Create by ChenHongkun on 10/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerRoleDetail__
#define __ProjectMB__MB_LayerRoleDetail__

#include "MB_ResWindow.h"
#include "MB_Message.h"
class MB_LayerRoleDetail : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver,public MB_MessageEditDeleate
{
public:
    CREATE_FUNC(MB_LayerRoleDetail);
	MB_LayerRoleDetail();
	virtual ~MB_LayerRoleDetail();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    bool sendgift_request(const char *string);
    bool recvgift_request(MB_MsgBuffer *recvPacket);
    void onCloseClick(CCObject* pSender);
    void resetCard();
protected:
    void onChangeHeadClicked(CCObject* pSender);
    void onChangeNameClicked(CCObject* pSender);
    
    void addNodeToLayer(CCLayer * layer,int type);
    void onMsgRecv(CCNode* node, SocketResponse* response);
    virtual void setString(const char *codeback);
    
    void onMusicOnClick(CCObject* pSender);
    void onMusicOffClick(CCObject* pSender);
    void onSoundOnClick(CCObject* pSender);
    void onSoundOffClick(CCObject* pSender);
    void onUNRegistClick(CCObject* pSender);
    void onClearClick(CCObject* pSender);
    void onCodeRewardClick(CCObject* pSender);
    
private:
    CCLabelTTF*	m_pRoleName;
    CCLabelBMFont*	m_pRoleLevel;
    CCLabelBMFont*	m_pRoleExp;
    CCLabelBMFont*	m_pRoleVip;
    CCSprite*	m_pRoleCard;
    CCSprite*	m_pRoleFrame;
    int m_nLength;
    std::string m_pCode;
    CCSprite *m_pSpriteExp;
    CCProgressTimer* m_pExpTimer;
    CCEditBox* m_pEditBox;
    CCNode* m_pMusicOpen;
    CCNode* m_pMusicClose;
    CCNode* m_pSoundOpen;
    CCNode* m_pSoundClose;
    CCSprite* m_pVipLevelSpr;
};
#endif /* defined(__ProjectMB__MB_LayerRoleDetail__) */
