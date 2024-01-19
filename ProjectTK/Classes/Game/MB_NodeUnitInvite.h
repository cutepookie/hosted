
#ifndef __ProjectMB__MB_NodeUnitInvite__
#define __ProjectMB__MB_NodeUnitInvite__

#include "Game.h"

class MB_NodeUnitInvite:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:
    
    CCNode *m_pNodeSize;
    
    public :
    
    MB_NodeUnitInvite();
    ~MB_NodeUnitInvite();
    virtual bool init();
    static MB_NodeUnitInvite * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onRewardDetailClick(CCObject *);
    CCSize getSize(){
        
        return m_pNodeSize->getContentSize();
    }
};

#endif /* defined(__ProjectMB__MB_NodeUnitInvite__) */
