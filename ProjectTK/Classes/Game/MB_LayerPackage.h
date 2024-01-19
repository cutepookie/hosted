//
//  MB_LayerPackage.h
//  ProjectPM
//
//  Create by WenYong on 19/6/2014.
//
//
#ifndef __ProjectMB__MB_LayerPackage__
#define __ProjectMB__MB_LayerPackage__

#include "MB_ResWindow.h"

class MB_LayerPackage : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    CREATE_FUNC(MB_LayerPackage);
	MB_LayerPackage();
	virtual ~MB_LayerPackage();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
protected:
    void updateNode(CCNode* pNode);
private:
    CCNode*	m_pNodeStore;
    CCNode*	m_pNodeMonsters;
    CCNode*	m_pNodeEquip;
};
#endif /* defined(__ProjectMB__MB_LayerPackage__) */