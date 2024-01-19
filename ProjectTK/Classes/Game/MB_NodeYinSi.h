//
//  MB_NodeYinSi
//  ProjectTK
//
//  Created by lic
//
//
#ifndef __ProjectMB__MB_NodeYinSi__
#define __ProjectMB__MB_NodeYinSi__

#include "MB_ResWindow.h"
#include "Game.h"
#include "RichText.h"
class MB_NodeYinSi:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    MB_NodeYinSi();
    virtual ~MB_NodeYinSi();
    
    CREATE_FUNC(MB_NodeYinSi)
public:
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void onInitDidFinish (void);
    
    virtual bool init();
    void onEnter()
    {
        MB_ResWindow::onEnter();
        MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_NodeYinSi");
    }
    void setClose();
    void refresh(CCObject*);
protected:
    virtual void onResetWnd(void);
    void onCloseClick(CCObject* pSender);
    void runEnterAction();
private:
    CCNode*           m_pContent;
    CCScrollView* pScrollview;
    int tanchuTimes;
    CCNode* pRootNode;
    CCLayerColor* lc;
};
#endif
