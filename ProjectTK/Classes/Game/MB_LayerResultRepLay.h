
#ifndef __ProjectMB__MB_LayerResultRepLay__
#define __ProjectMB__MB_LayerResultRepLay__
#include "Game.h"
class MB_SceneGame;
class MB_LayerResultRepLay: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    
    MB_LayerResultRepLay();
    ~MB_LayerResultRepLay();
    static MB_LayerResultRepLay* create(MB_SceneGame *gameScene);
  	virtual bool init(MB_SceneGame *gameScene);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onReplayClicked (CCObject* sender);
    void onBackClicked (CCObject* sender);
    
private:
    
    CCLabelTTF *m_pEnenmy_Role_Name;
    CCLabelTTF *m_pOur_Role_Name;
    CCNode * m_pEnemy_pos;
    CCNode * m_pOur_pos;
    CCNode * m_pNodeSuccess;
    CCNode * m_pNodeFailed;
    
    bool isClickBack;
};

#endif /* defined(__ProjectMB__MB_LayerResultRepLay__) */
