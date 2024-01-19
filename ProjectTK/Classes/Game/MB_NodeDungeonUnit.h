

#ifndef __ProjectMB__MB_NodeDungeonUnit__
#define __ProjectMB__MB_NodeDungeonUnit__

#include "Game.h"
class MB_DungeonData;
class MB_LayerChapterWnd;
class MB_NodeDungeonUnit:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
private:
    
    CCLabelTTF *m_pLevel_name;
    CCSprite *m_pStar[3];
    CCNode *m_pSprite_back;
    //        CCSprite *m_pPass;
    CCSprite * m_pSpriteBack;
    MB_DungeonData* m_data;
    CCNode *m_pNodeBattleWarn;
    CCNode *m_pNodeBattleWarn2;
    
    CCSprite* m_pSpr;
public:
    MB_NodeDungeonUnit();
    ~MB_NodeDungeonUnit();
    MB_NodeDungeonUnit(MB_DungeonData *);
    virtual bool init();
    virtual void onEnter();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    MB_DungeonData* getData() { return m_data;}
    void setData(MB_DungeonData* data) { m_data = data;}
    void setPass();
    static MB_NodeDungeonUnit *create(MB_DungeonData *data,uint8_t type,bool bShowTutorial = false);
    CC_SYNTHESIZE(uint8_t, m_nType, type);
    virtual void onResetWnd();
    void onSweepClick(CCObject *);
    void onGoSweepClick(CCObject *);
    void onClickReady(CCObject *);
    void setDataRouse(MB_LayerChapterWnd* pChapterLayer){m_pChapterLayer = pChapterLayer;};
    CC_SYNTHESIZE(bool, m_bShowTutorial, ShowTutorial);
    MB_LayerChapterWnd*  m_pChapterLayer;
    void setNow(bool b,int bestScore);
    CCControlButton* m_pBtnReady;
};

#endif /* defined(__ProjectMB__File__) */
