//
//  MB_LayerYeShiJieMain.h
//  ProjectPM
//
//  Created by WenYong on 14-5-17.
//
//

#ifndef __ProjectMB__MB_LayerYeShiJieMain__
#define __ProjectMB__MB_LayerYeShiJieMain__

#include "MB_FunctionMainWnd.h"

class MB_LayerYeShiJieMain:public MB_FunctionMainWnd
{
public:
    MB_LayerYeShiJieMain();
    ~MB_LayerYeShiJieMain();
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onCloseClick(CCObject* pSender);
    void onLHSCClicked(CCObject* pSender);
    void onJJCClicked(CCObject* pSender);
    void onSLZSClicked(CCObject* pSender);
    void onTJWQClicked(CCObject* pSender);
    void onDXJKClicked(CCObject* pSender);
    void onMXClicked(CCObject* pSender);
    void onPMJBClicked(CCObject* pSender);
    void onHEGClicked(CCObject* pSender);
    void onEnterTransitionDidFinish();
    void tick(float dt);
private:
    CCControlButton* btn;
    CCNode* m_pHCGBtn;
    CCNode* m_pLHSCBtn;
    CCNode* m_pJJCBtn;
    CCNode* m_pSLZSBtn;
    CCNode* m_pTJWQBtn;
    CCNode* m_pMXBtn;
    CCNode* m_pDXJKBtn;
    CCNode* m_pPMJBBtn;
    CCNode* m_pSLNode;
    CCNode* node_flag_mx;
    CCNode* node_flag_wq;
    CCNode* node_flag_yljk;
    CCLabelBMFont* flag_mx;
    CCLabelBMFont* flag_yljk;
};

#endif /* defined(__ProjectMB__MB_LayerYeShiJieMain__) */
