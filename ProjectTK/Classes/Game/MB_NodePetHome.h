

#ifndef __ProjectMB__MB_NodePetHome__
#define __ProjectMB__MB_NodePetHome__

#include "Game.h"
class MB_LayerHome;
class MB_NodePetHome: public CCNode
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    ~MB_NodePetHome();
    
    static MB_NodePetHome *create(MB_LayerHome* layerHome,uint64_t petId);
    MB_NodePetHome(MB_LayerHome* layerHome,uint64_t petId);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool init();
    
    void onIconClick(CCObject *);

    void showAll(bool b);
private:
    CCSprite* m_pSprite_kuang;
    MB_LayerHome* m_pLayerHome;
    int64_t m_nPetId;
    CCSprite *m_pSprite_face;
    CCLabelBMFont *m_pText_level;
    CCNode *m_pNodeStar;
    CCSprite *m_pStar[MAX_GER_STAR];
};
#endif /* defined(__ProjectMB__MB_NodePetHome__) */
