
#ifndef __ProjectMB__MB_NodeReplayPetUnite__
#define __ProjectMB__MB_NodeReplayPetUnite__

#include "Game.h"
class MB_NodeReplayPetUnite: public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
    
public:
    
    MB_NodeReplayPetUnite();
    ~MB_NodeReplayPetUnite();
    static  MB_NodeReplayPetUnite* create(uint16_t type,uint16_t rank,uint16_t level ,bool isDead);
  	virtual bool init(uint16_t type,uint16_t rank,uint16_t level ,bool isDead);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setPet(uint16_t type,int petRank);
private:
    CCLabelBMFont *m_pQiangHua;
    CCLabelBMFont *m_pLevel;
    
    CCNode *m_pNodeIsDead;
    CCSprite* m_pSprite_face;
    CCSprite* m_pBg;
    CCSprite *m_pStar[MAX_GER_STAR];
    CCNode* m_pSize;
};

#endif /* defined(__ProjectMB__MB_NodeReplayPetUnite__) */
