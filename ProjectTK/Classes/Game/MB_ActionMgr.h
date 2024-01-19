

#ifndef __ProjectMB__MB_ActionMgr__
#define __ProjectMB__MB_ActionMgr__
#include "Game.h"


USING_NS_CC;
USING_NS_CC_EXT;

enum effectPosType{
    
    kPosTypeSelf = 0,
    kPosTypeMoveToTarget,
    kPosTypeTarget,
    kPosTypeOur,
    kPosTypeEnemy,
    
};
//
// MB_Charactor
//
/** @brief MB_Charactor 基於 CCObjct .
 
 All features from CCobject are valid, plus the following new features:

 -执行動画逻辑
*/
class MB_NodeShow;
class MB_ActionMgr: public CCObject,
public CCBMemberVariableAssigner
{
private:
    MB_NodeShow *m_pNowactionNode;
    CCNode *m_pRootNode;
    bool isActionDead;
    bool effectdead;
    static std::map<std::string,CCData *> m_pCCBiCache;
    CCPoint m_Point;
    CCNode * m_pSprite;
public:
    MB_ActionMgr(MB_NodeShow *,CCNode *);
    ~MB_ActionMgr();
    void playKillTheAnimation(p_action *list);
    void playKillAnimation();
    void AttackactionOver(MB_Action *action);
    void goPlay();
    void goReStart();
    void removeNodeAndCleanUp(CCNode *p);
    void stopEmit(CCNode* node);
    void effect(const char *filename, CCPoint &from,CCPoint &to,float starttime,float time, int flip, int turnMove,int  actionType,effectPosType type = kPosTypeSelf );
    void addReelEffct();
    void delReelEffect();
    void rotationNode(CCNode* pNode,const CCPoint& to,const CCPoint& from);
    CC_SYNTHESIZE(p_action *,m_pList,List);
    CCData * readFileNode(const char *filename);
    static void puargeCache();
    bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    void playSkillsRead(uint16_t tid,uint8_t rank,char* skillName,bool isScaleAction = false);
    void onSkillsReadOver();
    bool goShock();//震屏
    void addAngryEffct();
    void delAngryffect();
    
    bool m_bIsScaleAction;
};


class MB_NodeSkillsRead : public MB_ResWindow,public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    MB_NodeSkillsRead();
    virtual ~MB_NodeSkillsRead();
    
    CREATE_FUNC(MB_NodeSkillsRead);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void onExit();
    void setCallBackFuc();
    void onAnimationOver();
    void setCardTid(uint16_t tid,uint8_t rank,char* name,bool isScaleAction = false);
    void setCallBack(CCObject *target,SEL_CallFunc backFunc);
private:
    CCBAnimationManager* m_pAnimation;
    CCSprite* m_pSpriteCard1;
    CCSprite* m_pStar;
    CCObject* m_pTarget;
    SEL_CallFunc m_pFunction;
    CCLabelTTF* m_pTTFName1;
    CCNode* m_pSkill;
    CCNode* m_pNode1;
    CCNode* pNode;
    CCLayerColor* bgColor;
};

class MB_NodeSkill:public CCNode
{
public:
    static MB_NodeSkill* create(CCNode* pNode)
    {
        MB_NodeSkill* pInstance = new MB_NodeSkill;
        if (pInstance && pInstance->init())
        {
            pInstance->addChild(pNode);
            pInstance->setScale(2);
            pInstance->autorelease();
            return pInstance;
        }
        
        CC_SAFE_RELEASE_NULL(pInstance);
        return NULL;
    }
};
#endif /* defined(__ProjectMB__MB_ActionMgr__) */
