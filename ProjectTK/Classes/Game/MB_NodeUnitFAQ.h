
#ifndef __ProjectMB__MB_NodeUnitFAQ__
#define __ProjectMB__MB_NodeUnitFAQ__

#include "Game.h"

class MB_NodeUnitFAQ:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
    private:
    
    public :
    
    MB_NodeUnitFAQ();
    ~MB_NodeUnitFAQ();
    virtual bool init();
    static MB_NodeUnitFAQ* create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onEnterClicked(CCObject *);
    
};

#endif /* defined(__ProjectMB__MB_NodeUnitFAQ__) */
