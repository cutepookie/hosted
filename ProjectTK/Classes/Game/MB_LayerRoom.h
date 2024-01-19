//
//  MB_LayerRoom.h
//  ProjectMB
//
//  Create by wenyong on 26/11/2014.
//
//
#ifndef __ProjectMB__MB_LayerRoom__
#define __ProjectMB__MB_LayerRoom__

#include "MB_FunctionMainWnd.h"
class MB_LayerRoom : public MB_FunctionMainWnd
{
public:
    CREATE_FUNC(MB_LayerRoom);
	MB_LayerRoom();
	virtual ~MB_LayerRoom();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void tick(float dt);
    void onCloseClick(CCObject* pSender);
    void onBSXSClicked(CCObject* pSender);
    void onSLRWClicked(CCObject* pSender);
    void onLXDLLBClicked(CCObject* pSender);
    void onDJLBClicked(CCObject* pSender);
    void onZXJLClicked(CCObject* pSender);
    void onExit();
    void onEnterTransitionDidFinish();
private:
    CCLabelBMFont* m_pTxtFlag[5];
    CCNode* m_pNodeFlag[5];
};
#endif /* defined(__ProjectMB__MB_LayerRoom__) */
