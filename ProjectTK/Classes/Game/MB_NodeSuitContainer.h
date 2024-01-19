//
//  MB_NodeSuitContainer.h
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeSuitContainer__
#define __ProjectMB__MB_NodeSuitContainer__

#include "MB_ResWindow.h"

class MB_NodeSuitContainer : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_NodeSuitContainer();
	virtual ~MB_NodeSuitContainer();
	virtual void onResetWnd();
    CREATE_FUNC(MB_NodeSuitContainer);
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    int getCapability()const{return 3;}
    bool pushSuitItem(CCNode* pNode,uint16_t index);
    CCSize getNodeSize()const;
protected:
private:
    CCNode*	m_pNodeSize;
    CCNode* m_pNodeItems[6];
    
};
#endif /* defined(__ProjectMB__MB_NodeSuitContainer__) */
