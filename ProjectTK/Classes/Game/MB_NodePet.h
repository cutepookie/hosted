

#ifndef __ProjectMB__MB_NodePet__
#define __ProjectMB__MB_NodePet__

#include "Game.h"

class MB_NodePet: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_NodePet();
    ~MB_NodePet();
    
    static MB_NodePet *create(uint64_t petId,bool bCircle = true);
    MB_NodePet(uint64_t petId);
    
    static MB_NodePet *create(uint16_t petTypeID, short petLevel = 0, short petQuality = 0,bool bCircle = true);
    virtual bool init(uint16_t petTypeID, short petLevel, short petQuality,bool bCircle = true);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool init(bool bCircle = true);
    void setPetUID(uint64_t petId);
    int64_t  getData();
    void setMenuTouch(bool iscanTouch);
    void onIconClick(CCObject *);

    void showName(bool b);
    void showLevel(bool b);
    void setNameColorBlack();
    
    bool isTopZorder;
private:
    CCNode* m_pStar[MAX_GER_STAR];
    int64_t m_nPetId;
    int16_t m_nPetTypeID;
    int     m_nPetRank;
    int     m_nPetLevel;
    CCSprite *m_pSprite_face;
    CCSprite *m_pSprite_quality;
    CCSprite *m_pSprite_elite;
    CCLabelBMFont *m_pText_level;
    CCMenu *m_pMenu;
    CCSprite *m_pMask;
    CCNode* m_pLevelNode;
    CCLabelTTF* m_pLabelName;
};
#endif /* defined(__ProjectMB__MB_NodePet__) */
