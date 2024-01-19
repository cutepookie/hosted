//
//  MB_NodeServerItem.h
//  ProjectMB
//
//  Create by WenYong on 27/8/2014.
//
//
#ifndef __ProjectMB__MB_NodeServerItem__
#define __ProjectMB__MB_NodeServerItem__

#include "MB_ResWindow.h"


class MB_NodeServerItem : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodeServerItem);
    static MB_NodeServerItem* create(int serverId,const char* pServerName,uint8_t nStatus);
    static const CCSize& getWndSize();
	MB_NodeServerItem();
	virtual ~MB_NodeServerItem();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setServerInfo(uint16_t serverId,const char* pServerName,uint8_t nStatus);
protected:
    void onServerClicked(CCObject* pSender);
private:
    CCNode*	m_pSize;
    CCNode* m_pNodeServerState1;
    CCNode* m_pNodeServerState2;
    CCNode* m_pNodeServerState3;
    CCLabelTTF*	m_pServerName;
    CCLabelTTF*	m_pServerID;
    CCMenu*	m_pMenu;
    uint16_t m_nServerID;
};
#endif /* defined(__ProjectMB__MB_NodeServerItem__) */