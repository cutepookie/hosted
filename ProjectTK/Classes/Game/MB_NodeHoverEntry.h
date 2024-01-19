//
//  MB_NodeHoverEntry.h
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#ifndef __ProjectMB__MB_NodeHoverEntry__
#define __ProjectMB__MB_NodeHoverEntry__

//#include "MB_FunctionEntranceWnd.h"
//typedef MB_FunctionEntranceWnd MB_NodeHoverEntry;
#include "MB_FunctionModule.h"
class MB_NodeHoverEntry : public CCFunctionWnd,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_NodeHoverEntry();
	virtual ~MB_NodeHoverEntry();
	virtual void onResetWnd();
    virtual void setType(int type);
	virtual bool init();
    bool setDataSource(CCFunctionDataSource* pDataSource){m_pDataSource = pDataSource;return true;}
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    CCControlButton*    m_pMenuItemImage;
protected:
    virtual void onEntranceClicked(CCObject* pSender);
protected:
    CCMenu*	scroller;
    
    CCSprite*	m_pNameLabel;
    CCNode*	m_pFlagNode2;
    CCLabelBMFont*	m_pFlag2;
    int m_nType;
    CCBAnimationManager* m_pAnimation;
};
class MB_NodeHoverEntry2 : public MB_NodeHoverEntry
{
protected:
    virtual void onEntranceClicked(CCObject* pSender);
};
#endif /* defined(__ProjectMB__MB_NodeHoverEntry__) */
