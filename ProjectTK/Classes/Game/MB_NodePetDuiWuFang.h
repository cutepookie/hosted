

#ifndef __ProjectMB__MB_NodePetDuiWuFang__
#define __ProjectMB__MB_NodePetDuiWuFang__

#include "Game.h"
class MB_LayerGuard;
class MB_NodePetDuiWuFang: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_NodePetDuiWuFang(uint64_t petId);
    ~MB_NodePetDuiWuFang();
    
    static MB_NodePetDuiWuFang *create(uint64_t petId);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    bool init();
    void onClickDetail(CCObject * pSender);
    void setPetID(uint64_t petId);
    void setParent(MB_LayerGuard* lg,int index);
    float m_nWidth;
    float m_nHeight;
    CCNode* m_pToVis;
    uint64_t m_nPetId;
private:
    MB_LayerGuard* m_pLg;
    int m_nIndex;
    CCSprite *m_pSprite_face;
    CCNode* m_pSize;
    CCSprite* m_pBg;

};
#endif /* defined(__ProjectMB__MB_NodePetDuiWuFang__) */
