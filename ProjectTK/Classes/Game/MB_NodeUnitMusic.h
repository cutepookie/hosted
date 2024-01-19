
#ifndef __ProjectMB__MB_NodeUnitMusic__
#define __ProjectMB__MB_NodeUnitMusic__

#include "Game.h"

class MB_NodeUnitMusic:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
private:
    
    CCNode *m_pNodeSize;
    CCControlButton *m_pMusicOpen;
    CCControlButton *m_pMusicClose;
    CCControlButton *m_pSoundOpen;
    CCControlButton *m_pSoundClose;
    
    public :
    
    static CCSize getUnitSize();
    
    MB_NodeUnitMusic();
    ~MB_NodeUnitMusic();
    virtual bool init();
    static MB_NodeUnitMusic* create();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onSoundOnClick(CCObject *);
    void onSoundOffClick(CCObject *);
    void onMusicOnClick(CCObject *);
    void onMusicOffClick(CCObject*);
    CCSize getSize(){
        
        return m_pNodeSize->getContentSize();
    }

};

#endif /* defined(__ProjectMB__MB_NodeUnitMusic__) */
