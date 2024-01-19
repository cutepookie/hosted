

#ifndef __ProjectMB__MB_NodePetCard__
#define __ProjectMB__MB_NodePetCard__
#include "Game.h"

class MB_NodePetCard:public CCLayer,
public CCBMemberVariableAssigner
,public CCBSelectorResolver {
    
private:
    
    CCSprite *m_pCardFace;
    CCSprite *m_pCountry;
    int64_t m_nPetId;
    CCSprite *m_pQuallity;
    CCSprite *m_pElite;
    CCBAnimationManager* m_pAnimMgr;
    uint16_t m_nPetTypeId;
    CCLabelTTF *m_pPetName;
    CCSprite * m_pStar[MAX_GER_STAR];
    CCSprite * m_pRank;
    CCNode* m_pNodeSize;
public :
    
    MB_NodePetCard();
    ~MB_NodePetCard();
    
    //创建卡牌图标 根据当前卡牌阶数选择状态
    static MB_NodePetCard* create(int64_t petId);
    //根据品阶选择创建对应形态卡牌    
    static MB_NodePetCard* create(int16_t petTypeId,int rank);
    
    static MB_NodePetCard* createWithType(uint16_t petTypeID);
    static MB_NodePetCard* createWithFirstType(uint16_t petTypeID);
    virtual bool initWithFirstType(uint16_t petTypeId,int rank);
    virtual bool init( int64_t petId);
    virtual bool initWithType(uint16_t petTypeId);
    virtual bool initWithType(uint16_t petTypeId,int rank);
    
    uint16_t getPetTypeId();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    CCSprite *getRectSprite();
    CCBAnimationManager* getAnimationManager() { return m_pAnimMgr;}
    void runAnimation();
};

#endif /* defined(__ProjectMB__MB_NodePetCard__) */
