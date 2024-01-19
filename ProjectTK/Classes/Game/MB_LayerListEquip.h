

#ifndef __ProjectMB__MB_LayerListEquip__
#define __ProjectMB__MB_LayerListEquip__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerListEquip: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCTableViewDataSource
, public CCTableViewDelegate
{
    
public:
    MB_LayerListEquip();
    ~MB_LayerListEquip();
    
    static MB_LayerListEquip* create(int type = 0);
    virtual bool init(int type);

    virtual void onResetWnd();
    void onBackClicked(CCObject* pSender);
    
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
    void onMsgRecv(CCNode* node, SocketResponse* response);
    CC_SYNTHESIZE(int, m_kSubType, SubType);
    
    void onSaleClicked(CCObject* pSender);
    void updateButton();
    void getListUnion();
private:
    CCNode* m_pTableContainer;
    CCNode* m_pTableContainer2;
    CCTableView* m_pTableView;
    CCSize m_cellSize;
    CCLabelTTF* m_pLabelItemCount;
    CCNode* m_pNodeSale;
    CCLabelTTF *m_pComonItemPiece3Num;
    CCLabelTTF *m_pComonItemPiece4Num;
    CCLabelTTF *m_pComonItemPiece5Num;
    CCNode *m_pNodeItem;
    CCLabelTTF *m_pItemNumber;
    CCNode* m_pNodePiece;
    int m_nLength;
};

#endif /* defined(__ProjectMB__MB_LayerListEquip__) */
