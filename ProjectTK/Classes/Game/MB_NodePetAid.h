

#ifndef __ProjectMB__MB_NodePetAid__
#define __ProjectMB__MB_NodePetAid__

#include "Game.h"

class MB_PetData;
class MB_NodePetAid: public MB_ResWindow
//class MB_NodePetAid: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    
    MB_NodePetAid();
    ~MB_NodePetAid();
    
    static MB_NodePetAid *create(uint64_t petId ,uint8_t type,bool bShowTutorial = false);
    static MB_NodePetAid *createType(MB_PetData *petData,uint8_t type);
    static MB_NodePetAid *createType(uint16_t petType);
    virtual bool init(uint16_t getType);
    virtual bool init(MB_PetData *petData,uint8_t type);
    virtual bool init();
    MB_NodePetAid(uint64_t petId);
    CC_SYNTHESIZE(uint8_t, m_nType, Type);
    CC_SYNTHESIZE(uint8_t, m_nIndex, Index);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onMsgRecv(CCNode* node, SocketResponse* response);

    
    int64_t  getData();
    void setMenuTouch(bool iscanTouch);
    void onIconClick(CCObject *);
    void setActive(bool isActive);
    void setIsSelect(bool isSelect);
    CCSize getNodeSize();
    
private:
    
    bool m_bShowTutorial;
    int64_t m_nPetId;
    CCSprite *m_pSprite_face;
    CCSprite *m_pSprite_quality;
//    CCSprite *m_pElite;
    CCMenu *m_pMenu;
    CCNode *m_pNodActive;
//    CCNode *m_pNodeMainPet;
//    CCNode *m_pNodeLiPet;
    CCLabelTTF *m_pInfo;
    CCNode * m_pNodeSelect;
};

#endif /* defined(__ProjectMB__MB_NodePetAid__) */
