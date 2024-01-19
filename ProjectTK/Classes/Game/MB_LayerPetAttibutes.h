//
//  MB_LayerPetAttibutes.h
//  ProjectMB
//
//  Create by WenYong on 25/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerPetAttibutes__
#define __ProjectMB__MB_LayerPetAttibutes__

#include "MB_ResWindow.h"
class MB_PetData;
class MB_LayerPetAttibutes : public MB_ResWindow,public CCBMemberVariableAssigner
{
public:
	MB_LayerPetAttibutes();
	virtual ~MB_LayerPetAttibutes();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    static MB_LayerPetAttibutes* create(MB_PetData* pData);
    
protected:
    void installAttribute(CCArray* pArray);
private:
    MB_PetData*        m_pData;
    CCLabelTTF*     m_pAttribute[16];
    CCNode*         m_pNodeSize;
};
#endif /* defined(__ProjectMB__MB_LayerPetAttibutes__) */