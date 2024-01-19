//
//  MB_LayerPetAidHelp.h
//  ProjectTK
//
//  Created by crimoon on 13-12-12.
//
//

#ifndef __ProjectMB__MB_LayerPetAidHelp__
#define __ProjectMB__MB_LayerPetAidHelp__

#include "Game.h"

class  MB_LayerPetAidHelp: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    public:
    
    MB_LayerPetAidHelp();
    ~MB_LayerPetAidHelp();
    virtual bool init();
    static MB_LayerPetAidHelp * create();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onCloseClicked(CCObject *);
    private:
   
};


#endif /* defined(__ProjectMB__MB_LayerPetAidHelp__) */
