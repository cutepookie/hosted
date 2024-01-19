

#ifndef __ProjectMB__MB_NodeDamage__
#define __ProjectMB__MB_NodeDamage__

#include "Game.h"

class MB_NodeDamage :public CCNode,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:

    CCNode *m_pNumber;
    CCBAnimationManager *m_pAnimation;
    
    public :
    
    MB_NodeDamage();
    ~MB_NodeDamage(); 
    static MB_NodeDamage * create(int damage ,bool iscrit);
    bool   init(int damgae,bool iscrit);
    void   whenShowOver();
    void   removeNode();
    void onExit();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
};
#endif /* defined(__ProjectMB__MB_NodeDamage__) */
