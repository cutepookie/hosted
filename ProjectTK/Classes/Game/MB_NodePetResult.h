

#ifndef __ProjectMB__MB_NodePetResult__
#define __ProjectMB__MB_NodePetResult__

#include "Game.h"
class MB_LayerHome;
class MB_NodePetResult: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePetResult(uint64_t petId);
    ~MB_NodePetResult();
    
    static MB_NodePetResult *create(uint64_t petId);

    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    bool init();
    void onClickDetail(CCObject * pSender);
    void setPetID(uint64_t petId);
    float m_nWidth;
    float m_nHeight;
    float opy2;
    float opx2;
    float opx;
    int m_nZorder;
    void setSelectedState(bool isSelected);
    void setAllAnchpoint(CCNode* node,CCPoint ap);
    void setShangZhen(bool b);
    CCNode* m_pMoveNode;
    CCNode* m_pToVis;
    uint64_t m_nPetId;
    CCNode* m_pInteam;
    CCControlButton* m_pDetailBtn;
    CCSprite *m_pStar[MAX_GER_STAR];
private:

    CCSprite *m_pSprite_face;
    CCLabelBMFont *m_pText_level;
    CCNode *m_pNodeStar;
    CCNode* m_pSize;
    CCSprite* m_pBg;
    CCLabelBMFont * m_pQiangHua;
    CCLabelTTF * roleName;

};
#endif /* defined(__ProjectMB__MB_NodePetResult__) */
