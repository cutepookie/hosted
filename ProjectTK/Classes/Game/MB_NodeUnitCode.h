
#ifndef __ProjectMB__MB_NodeUnitCode__
#define __ProjectMB__MB_NodeUnitCode__

#include "Game.h"

class MB_NodeUnitCode:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
//,public MB_MessageEditDeleate
{
    
private:
    CCNode *m_pNodeSize;
    CCEditBox* m_pEditBox;
public :
    
    MB_NodeUnitCode();
    ~MB_NodeUnitCode();
    virtual bool init();
    static MB_NodeUnitCode * create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onCodeRewardClick(CCObject *);
//    virtual void setString(const char *codeback);
    CCSize getSize()
    {
        return m_pNodeSize->getContentSize();
    }
    
};

#endif /* defined(__ProjectMB__MB_NodeUnitCode__) */
