//
//  MB_NodeServerZone.h
//  ProjectMB
//
//  Created by WenYong on 27/8/2014.
//
//
#ifndef __ProjectMB__MB_NodeServerZone__
#define __ProjectMB__MB_NodeServerZone__

#include "MB_ResWindow.h"

class MB_NodeServerZone : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_NodeServerZone);
    static MB_NodeServerZone* create(int beginID,int endID);
    static const CCSize& getWndSize();
	MB_NodeServerZone();
	virtual ~MB_NodeServerZone();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setDetail(int beginID,int endID);
    void select(bool bSelect);
protected:
    void onServerZoneClicked(CCObject* pSender);
private:
    uint16_t    m_nBeginID;
    uint16_t    m_nEndID;
    CCNode*	size;
    CCNode* m_pNodeSelect;
    CCLabelTTF*	m_pBeginServerZone;
    CCLabelTTF*	m_pEndServerZone;
    CCMenu*	m_pNodeMenu;
    CCMenuItemImage* m_pMenuImage;
};
#endif /* defined(__ProjectMB__MB_NodeServerZone__) */