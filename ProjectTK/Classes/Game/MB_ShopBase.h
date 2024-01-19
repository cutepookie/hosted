

#ifndef ProjectMB_MB_ShopBase_h
#define ProjectMB_MB_ShopBase_h

#include "MB_ResWindow.h"
#include "MB_ShopSubItem.h"


#include "MB_FunctionMainWnd.h"

//////////////////////////////////////
class MB_ShopPageBase:public MB_ResWindow
,public CCTableViewDataSource
,public CCTableViewDelegate
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
{
public:
    MB_ShopPageBase();
    virtual        ~MB_ShopPageBase();
    
    virtual bool init();
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    virtual CCSize                  cellSizeForTable                (CCTableView *table);
    
    virtual CCTableViewCell*        tableCellAtIndex                (CCTableView *table, unsigned int idx);
    
    virtual unsigned int            numberOfCellsInTableView        (CCTableView *table);
    
    virtual void                    tableCellTouched                (CCTableView* table, CCTableViewCell* cell);
    
    virtual void                    scrollViewDidScroll             (CCScrollView* view);
    
    virtual void                    scrollViewDidZoom               (CCScrollView* view);
    
    void ShowPageNode(bool b);
    
    virtual void                    onResetWnd                      (void);
protected:
    CCSize                          m_cellSize;
    MB_ShopInfo*                    m_pShopInfo;
    CCTableView*                    m_pTableView;
private:
    CC_SYNTHESIZE(uint16_t,m_uShopID,ShopID);
    
    int m_nListLength;
    CCNode* m_pPanel;               //容器
    CCNode * m_pPageNode;           //关联的显示节点
    CCArray *m_pArray;
    
    CCPoint m_Pos;
};


#endif
