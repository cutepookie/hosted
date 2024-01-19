

#ifndef __ProjectMB__MB_LayerPetCommand__
#define __ProjectMB__MB_LayerPetCommand__

#include "Game.h"

#define Pet_Page_Num  2

class MB_LayerPetCommand : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{

public :
    
    MB_LayerPetCommand ();
    ~MB_LayerPetCommand ();
  
    
    static MB_LayerPetCommand* create(int type);
    
    virtual bool init(int type);
    virtual void onResetWnd();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onTeamClicked  (CCObject* pSender);
    void onPetEquipClicked    (CCObject* pSender);
    
    void enterTeamPage      (void);
    void enterPetEquip      (void);

private:
   
    CC_SYNTHESIZE(int, m_kLayerPetType, LayerPetType);

};
#endif /* defined(__ProjectMB__MB_LayerPetCommand __) */
