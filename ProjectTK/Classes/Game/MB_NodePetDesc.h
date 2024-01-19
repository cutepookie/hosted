//
//  MB_NodePetDesc.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_NodePetDerecv_
#define __ProjectMB__MB_NodePetDerecv_

#include "MB_ResWindow.h"

class MB_NodePetDesc : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    CREATE_FUNC(MB_NodePetDesc);
	MB_NodePetDesc();
	virtual ~MB_NodePetDesc();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    bool setText(const char* pText);
    static MB_NodePetDesc* create(const char* pText);
protected:
private:
    CCNode*	m_pNodeSize;
    CCLabelTTF*	m_pTextDesc;
};
#endif /* defined(__ProjectMB__MB_NodePetDerecv_) */