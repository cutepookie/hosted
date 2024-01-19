
#ifndef __ProjectMB__MB_NodeUnit91__
#define __ProjectMB__MB_NodeUnit91__

#include "Game.h"

class MB_NodeUnit91:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
private:
    
    CCNode *m_pNodeSize;
    
    public :
    
    MB_NodeUnit91();
    ~MB_NodeUnit91();
    virtual bool init();
    static MB_NodeUnit91 * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void on91AppClick(CCObject *);
    void onBBSClick(CCObject *);
    CCSize getSize(){
    
        return m_pNodeSize->getContentSize();
    }

};
#endif /* defined(__ProjectMB__MB_NodeUnit91__) */
