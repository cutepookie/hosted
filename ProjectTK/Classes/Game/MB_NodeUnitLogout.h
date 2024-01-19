
#ifndef __ProjectMB__MB_NodeUnitLogout__
#define __ProjectMB__MB_NodeUnitLogout__
#include "Game.h"
class MB_NodeUnitLogout:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
private:
    
    CCNode *m_pNodeSize;
    
    public :
    
    MB_NodeUnitLogout();
    ~MB_NodeUnitLogout();
    virtual bool init();
    static MB_NodeUnitLogout* create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onLogoutClick(CCObject *);
    CCSize getSize(){
        
        return m_pNodeSize->getContentSize();
    }
};

#endif /* defined(__ProjectMB__MB_NodeUnitLogout__) */
