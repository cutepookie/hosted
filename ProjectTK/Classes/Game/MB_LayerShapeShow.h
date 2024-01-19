//
//  MB_LayerShapeShow.h
//  ProjectMB
//
//  Create by wenyong on 23/12/2014.
//
//
#ifndef __ProjectMB__MB_LayerShapeShow__
#define __ProjectMB__MB_LayerShapeShow__

#include "MB_ResWindow.h"

class MB_PetTemplate;
class MB_LayerShapeShow : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_LayerShapeShow);
	MB_LayerShapeShow();
	virtual ~MB_LayerShapeShow();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void setTypeId(uint16_t tid);
    virtual void setTemplate(MB_PetTemplate* pTemp,const char* skillName);
protected:
    void onCloseClicked(CCObject* pSender);
private:
    CCSprite*	m_pShap1;
    CCSprite*	m_pShap2;
    CCSprite*	m_pShap3;
    CCLabelTTF* m_pLabelTitle;
    
    CCLabelTTF* m_pNameShap1;
    CCLabelTTF* m_pNameShap2;
    CCLabelTTF* m_pNameShap3;
};
#endif /* defined(__ProjectMB__MB_LayerShapeShow__) */