

#ifndef __ProjectMB__MB_LayerResultHuaRong__
#define __ProjectMB__MB_LayerResultHuaRong__

#include "Game.h"
class MB_LayerResultHuaRong :public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
    private:

    CCLabelTTF *m_pMorale;
    CCNode *m_pItem[5];
    CCLabelTTF *m_pItemName[5];
    bool m_bIsPopScene;
    
    public :
    
    MB_LayerResultHuaRong();
    ~MB_LayerResultHuaRong();
    static MB_LayerResultHuaRong  * create(recvfight *fightResult,p_reward *result );
    bool   init(recvfight *fightResult,p_reward *result);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onCallPetClick(CCObject *);
};

#endif /* defined(__ProjectMB__MB_LayerResultHuaRong__) */
