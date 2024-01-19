//
//  MB_NodeBannerEntry.h
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#ifndef __ProjectMB__MB_NodeBannerEntry__
#define __ProjectMB__MB_NodeBannerEntry__

#include "MB_FunctionModule.h"

class MB_NodeBannerEntry : public NSGameFunction::CCFunctionWnd
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    static MB_NodeBannerEntry* create(int Type);
	MB_NodeBannerEntry();
	virtual ~MB_NodeBannerEntry();
	virtual void onResetWnd();
	virtual bool init();
    virtual void setType(int type);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void setEnable();
    virtual void setDisable();
    bool setDataSource(CCFunctionDataSource* pDataSource){m_pDataSource=pDataSource;return true;}
    static const CCSize& getUnitSize();
    void showActivities(bool bShow,bool isLevelLimit = false);
    virtual CCNode* loadResource(const char* pName);
protected:
    virtual void onChapterClicked(CCObject* pSender);
    bool setItemImage(const char* pFile);
    void goFunction(CCObject* pSender);
protected:
    int m_nType;
    bool m_bEnable;
    CCNode*	m_pNodeSize;
    CCMenu*	scroller;
    CCMenuItemImage*	m_pMenuItemImage;
    CCBAnimationManager*    m_pAnimation;
    CCNode* m_pNoAcitveSpr;
    bool m_bisLevelLimit;
};
#endif /* defined(__ProjectMB__MB_NodeBannerEntry__) */
