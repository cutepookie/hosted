
#ifndef __ProjectMB__MB_NodeItemUnitJingLian__
#define __ProjectMB__MB_NodeItemUnitJingLian__

#include "MB_ResWindow.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MB_LayerItemEnhance;
class MB_NodeItemUnitJingLian: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
{
    
public:
    MB_NodeItemUnitJingLian();
    ~MB_NodeItemUnitJingLian();
    
    static MB_NodeItemUnitJingLian* create(MB_LayerItemEnhance* lie = NULL,uint64_t itemUID = 0);
    static CCSize getUnitSize();
    virtual bool init(MB_LayerItemEnhance* lie = NULL,uint64_t itemUID = 0);
    
    virtual void onResetWnd();
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    void onChooseClicked(CCObject* pSender);
    MB_LayerItemEnhance* m_pLie;
    CCNode* m_pSelectSpr;
private:
    uint64_t m_uItemUID;
    CCNode* m_pNodeIcon;
    static CCSize m_cellSizeItem;
};

#endif /* defined(__ProjectMB__MB_NodeItemUnitJingLian__) */
