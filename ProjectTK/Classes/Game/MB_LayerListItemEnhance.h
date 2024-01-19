

#ifndef __ProjectMB__MB_LayerListItemEnhance__
#define __ProjectMB__MB_LayerListItemEnhance__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerListItemEnhance: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCTableViewDataSource
, public CCTableViewDelegate
{
    
public:
    MB_LayerListItemEnhance();
    ~MB_LayerListItemEnhance();
    
    static MB_LayerListItemEnhance* create(uint64_t itemUID);
    virtual bool init(uint64_t itemUID);
    
    virtual void onResetWnd();
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    CC_SYNTHESIZE(uint64_t, m_uItemUID, ItemUID);
    
    void onCloseClicked(CCObject* pSender);
    
    void sortData();
private:
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCSize m_cellSize;
    CCArray* m_pArrayCanChoose;
};

#endif /* defined(__ProjectMB__MB_LayerListItemEnhance__) */
