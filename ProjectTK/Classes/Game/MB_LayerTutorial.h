

#ifndef __ProjectMB__MB_LayerTutorial__
#define __ProjectMB__MB_LayerTutorial__

#include "Game.h"

class MB_LayerTutorial: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
{
public:
    
    MB_LayerTutorial();
    ~MB_LayerTutorial();
    
    static MB_LayerTutorial* create(CCNode* pNode);
    virtual bool init(CCNode* pNode);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onSkipClicked(CCObject* pSender);

    virtual void onEnter()
    {
        MB_ResWindow::onEnter();
    }
private:
    CCMenu* m_pMenu;
    CCControlButton* m_pButtonSkip;
    CCNode* m_pSkipLayer;
    CCNode* pTargetNode;
};

#endif /* defined(__ProjectMB__MB_LayerTutorial__) */
