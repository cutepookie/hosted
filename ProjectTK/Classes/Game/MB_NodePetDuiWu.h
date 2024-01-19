

#ifndef __ProjectMB__MB_NodePetDuiWu__
#define __ProjectMB__MB_NodePetDuiWu__

#include "Game.h"
class MB_LayerHome;
class MB_NodePetDuiWu: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePetDuiWu(uint64_t petId,bool isH = true);
    ~MB_NodePetDuiWu();
    
    static MB_NodePetDuiWu *create(uint64_t petId,bool isH = true,bool isSetBtn = true);

    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    bool init(bool isSetBtn);
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
    void setShouHu(bool b);
    CCNode* m_pMoveNode;
    CCNode* m_pToVis;
    uint64_t m_nPetId;
    CCNode* m_pInteam;
    CCControlButton* m_pDetailBtn;
    CCSprite *m_pStar[MAX_GER_STAR];
    CCNode* m_pInguard;
private:
    CCSprite *m_pSprite_face;
    CCLabelBMFont *m_pText_level;
    CCNode *m_pNodeStar;
    CCNode* m_pSize;
    CCNode* m_pBgHighlight;
    bool m_bIsH;
};
#endif /* defined(__ProjectMB__MB_NodePetDuiWu__) */
