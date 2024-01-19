//
//  MB_NodeDestinyContainer.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_NodeDestinyContainer__
#define __ProjectMB__MB_NodeDestinyContainer__

#include "MB_ResWindow.h"

class MB_PetData;
class MB_NodeDestinyContainer : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
    CREATE_FUNC(MB_NodeDestinyContainer);
    static MB_NodeDestinyContainer* create(MB_PetData* pData);
	MB_NodeDestinyContainer();
	virtual ~MB_NodeDestinyContainer();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    bool setData(MB_PetData* pData);
protected:
private:
    CCNode* m_pNodeSize;
    CCNode* m_pContainer;
};

#endif /* defined(__ProjectMB__MB_NodeDestinyContainer__) */