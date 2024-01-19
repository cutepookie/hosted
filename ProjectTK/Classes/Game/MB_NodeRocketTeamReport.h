

#ifndef __ProjectMB__MB_NodeRocketTeamReport__
#define __ProjectMB__MB_NodeRocketTeamReport__

#include "Game.h"
class MB_EventData;
class MB_NodeRocketTeamReport:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
private:


    CCLabelTTF *m_pAttack[10];
    CCLabelTTF *m_pUserName[10];
    CCScale9Sprite *m_pSprite[10];
    int m_nType;
    
    public :
    
    MB_NodeRocketTeamReport();
    ~MB_NodeRocketTeamReport();
    virtual bool init();
    static  MB_NodeRocketTeamReport* create();
    static  MB_NodeRocketTeamReport* create(int type);
    virtual bool init(int type);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onResetWnd();
    void onCloseClick(CCObject*);
        
};
#endif /* defined(__ProjectMB__MB_NodeRocketTeamReport__) */
