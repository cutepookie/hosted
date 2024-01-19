

#ifndef __ProjectMB__MB_LayerListTreasure__
#define __ProjectMB__MB_LayerListTreasure__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerListTreasure: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCTableViewDataSource
, public CCTableViewDelegate
{
    
public:
    MB_LayerListTreasure();
    ~MB_LayerListTreasure();
    
    static MB_LayerListTreasure* create(int type = 0);
    virtual bool init(int type);
    
    virtual void onResetWnd();
    
//    void onMsgRecv(CCNode* node, SocketResponse* response);
    
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
    
    CC_SYNTHESIZE(int, m_kSubType, SubType);
    
    void onSaleClicked(CCObject* pSender);
    void onTreasureClicked(CCObject* pSender);
    void onPieceClicked(CCObject* pSender);
    void onPVPTreasureClicked(CCObject* pSender);
    
private:
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCSize m_cellSize;
    CCLabelTTF* m_pLabelItemCount;
    //CCNode* m_pNodeSale;
    CCMenuItemImage* m_pButtonTreasure;
    CCMenuItemImage* m_pButtonPiece;
    CCNode* m_pNodePiece;
};

#endif /* defined(__ProjectMB__MB_LayerListTreasure__) */
