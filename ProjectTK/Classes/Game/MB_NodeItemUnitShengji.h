
#ifndef __ProjectMB__MB_NodeItemUnitShengji__
#define __ProjectMB__MB_NodeItemUnitShengji__

#include "MB_ResWindow.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_LayerPetUpdate;
class MB_NodeItemUnitShengji: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
{
    
public:
    MB_NodeItemUnitShengji();
    ~MB_NodeItemUnitShengji();
    
    static MB_NodeItemUnitShengji* create(MB_LayerPetUpdate* lie = NULL,uint64_t itemUID = 0);
    static CCSize getUnitSize();
    virtual bool init(MB_LayerPetUpdate* lie = NULL,uint64_t itemUID = 0);
    
    virtual void onResetWnd();
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    void onChooseClicked(CCObject* pSender);
    MB_LayerPetUpdate* m_pLpu;
    CCNode* m_pSelectSpr;
private:
    uint64_t m_uItemUID;
    CCNode* m_pNodeIcon;
    static CCSize m_cellSizeItem;
};

#endif /* defined(__ProjectMB__MB_NodeItemUnitShengji__) */
