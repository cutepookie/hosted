//
//  MB_LayerComposeMain.h
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-18.
//
//

#ifndef __ProjectMB__MB_LayerComposeMain__
#define __ProjectMB__MB_LayerComposeMain__

#include "MB_FunctionMainWnd.h"
class MB_LayerFormulaList;
class MB_ComposeInterface;
class MB_LayerComposeMain:public MB_FunctionMainWnd
{
public:

    CREATE_FUNC(MB_LayerComposeMain);

    MB_LayerComposeMain();

    virtual ~MB_LayerComposeMain();

    virtual bool init();

    virtual void onResetWnd();

    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);

    void onFormulaClicked(CCObject* pSender);

    void onComposeSuccessed(MB_ResWindow* pRewardWnd,MB_ResWindow* pSender);

    void onRuleClicked(CCObject* pObject);
    
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
protected:

    void onMonsterComposeClicked(CCObject* pObject);

    void onCardComposeClicked(CCObject* pObject);

    void onCloseClick(CCObject* pObject);
    
    void onSaleClicked(CCObject* pObject);

    void onTickUpdate(float dt);
protected:

    void goComposeCard();

    void goComposeItem();

    void goComposePlatform(uint16_t nComposeID,uint16_t nType);

private:
    MB_LayerFormulaList* m_pShowList;
    CCNode*             m_pNodeDisplay;
    CCLabelTTF*             m_pActiveDesc;
    CCLabelTTF*             m_pLeftTime;
    CCNode*             m_pNodeActive;
    CCNode*             m_pNodeContainer;
    MB_ComposeInterface* m_pComposeInterface;
};

#endif /* defined(__ProjectMB__MB_LayerComposeMain__) */
