

#ifndef __ProjectMB__MB_NodeUnitRegist__
#define __ProjectMB__MB_NodeUnitRegist__
#include "Game.h"

class MB_NodeUnitRegist:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
    private:
    
    CCNode *m_pNodeSize;
        
    public :
    
    MB_NodeUnitRegist();
    ~MB_NodeUnitRegist();
    virtual bool init();
    static MB_NodeUnitRegist* create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onRegistClick(CCObject *);
    CCSize getSize(){
        
        return m_pNodeSize->getContentSize();
    }
};

#endif /* defined(__ProjectMB__File__) */
