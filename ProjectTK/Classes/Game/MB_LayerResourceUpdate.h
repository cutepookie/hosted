//
//  MB_LayerResourceUpdate.h
//  ProjectMB
//
//  Created by wenyong on 24/11/2014.
//
//
#ifndef __ProjectMB__MB_LayerResourceUpdate__
#define __ProjectMB__MB_LayerResourceUpdate__

#include "MB_ResWindow.h"

class MB_LayerResourceUpdate : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    CREATE_FUNC(MB_LayerResourceUpdate);
	MB_LayerResourceUpdate();
	virtual ~MB_LayerResourceUpdate();
	virtual void onResetWnd();
    virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setUpdateDetail(const char* pDetail);
    void setUpdatePercent(int perCent);
    void visibleProgress(bool bVisible);
    void setClickCallback(CCObject* pTarget,SEL_CallFunc pFunc);
protected:
    std::string m_szResPath;
private:
    CCObject*   m_pTarget;
    SEL_CallFunc m_pFunc;
    CCSprite*   m_pProgressBg;
    CCSprite*   m_pProgressBanner;
    CCLabelTTF*	m_pUpdateDetail;
    CCProgressTimer*   m_pProgress;
};
#endif /* defined(__ProjectMB__MB_LayerResourceUpdate__) */
