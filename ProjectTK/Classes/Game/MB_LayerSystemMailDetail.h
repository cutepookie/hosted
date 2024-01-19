//
//  MB_LayerSystemMailDetail.h
//  ProjectPM
//
//  Create by WenYong on 10/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerSystemMailDetail__
#define __ProjectMB__MB_LayerSystemMailDetail__

#include "MB_ResWindow.h"

struct sMailCell;
class RichText;
class MB_LayerSystemMailDetail : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_LayerSystemMailDetail();
	virtual ~MB_LayerSystemMailDetail();
    static MB_LayerSystemMailDetail* create(uint64_t uid);
	virtual void onResetWnd();
	virtual bool init(uint64_t uid);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setMailUid(uint64_t uid);
protected:
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onCloseClicked(CCObject* pSender);
    void onComitClicked(CCObject* pSender);
    void updateRewardNode(sMailCell* pCell);
    void setTitle(const char* pTitle);
    void setContent(const char* pContent);
    void preProcessText(std::string& text, sMailCell* ret);
    void preProcessTitleText(std::string& text,sMailCell* ret);
    void deleteEmail();
private:
    uint64_t    m_nMailUID;
    CCScale9Sprite*	m_pScal9Sprite;
    bool        m_bTensiled;
    bool        m_bRewardMail;
    bool        m_bHasReward;
    CCNode*	m_pNodeContent;
    CCNode*	m_pMailTitle;
    CCControlButton*	m_pBtnCommit;
    CCNode*	m_pNodeRewardList;
    CCArray* m_pTemplateValueArray;
    RichText* m_pRichText;
};
#endif /* defined(__ProjectMB__MB_LayerSystemMailDetail__) */