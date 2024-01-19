//
//  MB_NodeSuitName.h
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#ifndef __ProjectMB__MB_NodeSuitName__
#define __ProjectMB__MB_NodeSuitName__

#include "MB_ResWindow.h"

class MB_NodeSuitName : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    CREATE_FUNC(MB_NodeSuitName);
	MB_NodeSuitName();
	virtual ~MB_NodeSuitName();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    void setName(const char* pName);
    CCSize getNodeSize()const;
protected:
private:
    CCNode*	m_pNodeSize;
    CCLabelTTF*	m_pSuitName;
    std::string m_szSuitName;
};
#endif /* defined(__ProjectMB__MB_NodeSuitName__) */
