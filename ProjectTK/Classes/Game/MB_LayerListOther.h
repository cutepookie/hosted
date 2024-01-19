#ifndef __ProjectMB__MB_LayerListOther__
#define __ProjectMB__MB_LayerListOther__


#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerListOther: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCTableViewDataSource
, public CCTableViewDelegate
{
    enum kPageType
    {
        kPageItem,
        kPageFormula,
    };
public:
    MB_LayerListOther();
    ~MB_LayerListOther();
    
    static MB_LayerListOther* create();
    virtual bool init();
    
    virtual void onResetWnd();
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    void refreshCount();
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    
    void onItemPageClicked(CCObject*);
    static bool sortFormulaArray(const CCArray* pArray,std::vector<MB_ItemData*>& result);
    void onCloseClicked(CCObject* pSender);
    void onComposeSuccessed(MB_ResWindow* pRewardWnd,MB_ResWindow* pSender);
protected:
    static bool sortFunction(MB_ItemData* first,MB_ItemData* second);
private:
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCSize m_cellSizeFormula;
    CCSize m_cellSizeItem;
    CCLabelTTF* m_pFXCount;
    std::vector<MB_ItemData*> m_pSortFormulas;
    int m_nCurPage;
};

#endif /* defined(__ProjectMB__MB_LayerListOther__) */
