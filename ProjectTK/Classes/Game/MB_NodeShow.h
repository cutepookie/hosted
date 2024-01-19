
#ifndef __ProjectMB__MB_NodeShow__
#define __ProjectMB__MB_NodeShow__

#include "Game.h"


class MB_ActionMgr;

enum ActionMoveType
{
    kMoveSingle         = 1,
    kMoveArray          = 2,
    kMoveFrontRow       = 3,
    kMoveBackRow        = 4,
    kMoveRandomTwo      = 5,
    kMoveRandomTree     = 6,
    kMoveAll            = 7
};
class MB_SceneGame;
class MB_NodeShow :public CCNode ,

public cocos2d::extension::CCBSelectorResolver

, public cocos2d::extension::CCBMemberVariableAssigner{
    
public:
    const CCPoint& getPosBeforeAnimation(){return m_PosBeforeAnimation;}
    CCNode* m_pAnimationNode;
    CCNode* m_pToScaleNode;
private:
    CCPoint     m_PosBeforeAnimation;
    MB_SceneGame* m_pRoot;
    p_fighter *m_pFighter;
    int m_nType;
    bool isSetCallBack;
    CCSprite * m_pSpriteFace;
    CCSprite *m_bSprite;
    CCSprite* m_pCamp;
    CCProgressTimer *m_pBlood;
    CCProgressTimer *m_pSpbar;
    CCNode* m_pDeadSpr;
    int64_t m_nPetID;
    CCBAnimationManager *mAnimationMgr;
    //        CCSprite *m_pElite;
    //        CCSprite *m_pCard;
    CCSprite *m_pStarFrame;
    CCSprite *m_pRankFrame;
    CCNode *m_pDamage;
    CCLabelTTF *m_pPetname;
    CCLabelBMFont *m_pPetLevel;
    
    CCSprite *m_pSp;
    CCNode *m_pCardVisible;

    CCNode* m_pNodeSP;
    std::string  m_ActionName;
    bool m_bBoss;
    bool m_bSetIsDetail;
    CCSprite *sprite;
    p_action*   m_pCurrentAction;
    CCFiniteTimeAction*   m_pStartAction;
    virtual void onExit();
    
    std::string m_strFileName;
public:
    
    static MB_NodeShow * createMB_NodeShow(p_fighter *fighter, int type ,CCNode *rootNode,bool isWorldBoss = false );
    virtual bool init( p_fighter *fighter,int type,CCNode *rootNode,bool isWorldBoss = false );
    MB_NodeShow();
    virtual ~MB_NodeShow();
    void setAnimationMgr( CCBAnimationManager *pAnimationMgr);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    p_fighter *getFighter();
    void callAnimationByName(const char *animationName);
    void removeAndClean();
    void startAction( p_action *list );
    void setSpriteFrame(CCSpriteFrame *frame);
    void changeBooldAndSpPercentage(int per,int index);
    void changeBoold(int bloodt);
    void changeSp(int sp);
    void whenDead();
    void setDetailShow(bool isshow);
    bool isDetailShow();
    CCNode * getDamageNode();
    void setBoss(bool isBoss);
    bool getBoss();
    void playDead();
    void onResetFiter(p_fighter *fighter);
    CC_SYNTHESIZE(MB_ActionMgr *,tk_ActionMgr,ActionMgr);
    
    
    void onStartAction();
    void executeAction();
    void setShowCard();
    void AnimationCompletedCallback();
    CC_SYNTHESIZE(CCPoint, m_nWorldPlace, WorldPlace);
    void setFileName(const char * name );
    const char * getFilaeName();
    void addCapacity(CCNode* node1);
    void removeCapacity();
    void setDead();
    CCSprite * getCard(){
        
        return  m_pSpriteFace;
    }
    CCSprite* m_pSpriteFaceToJump;
    uint8_t kindom;
    CCNode* m_pShadow;
    CCNode* m_pNodeCapacity1;
};

#endif
