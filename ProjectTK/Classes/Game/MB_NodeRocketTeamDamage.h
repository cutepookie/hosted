
#ifndef __ProjectMB__MB_NodeRocketTeamDamage__
#define __ProjectMB__MB_NodeRocketTeamDamage__

#include "Game.h"
class MB_NodeRocketTeamDamage :public CCNode,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
    CCNode *m_pNumber;
    CCLabelTTF *m_pAttackName;
    CCBAnimationManager *m_pAnimation;
    
    public :
    
    MB_NodeRocketTeamDamage();
    ~MB_NodeRocketTeamDamage();
    static MB_NodeRocketTeamDamage  * create(uint64_t damage , const char *username);
    bool   init(uint64_t damgae,const char * username);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void whenShowOver();
    void onExit();
};
#endif /* defined(__ProjectMB__MB_NodeRocketTeamDamage__) */
