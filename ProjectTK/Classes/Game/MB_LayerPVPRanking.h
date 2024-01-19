

#ifndef __ProjectMB__MB_LayerPVPRankingRanking__
#define __ProjectMB__MB_LayerPVPRankingRanking__

#include "Game.h"

USING_NS_CC;
USING_NS_CC_EXT;

//争霸分页 显示窗口
class MB_LayerPVPRanking : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public CCTableViewDataSource
,public CCTableViewDelegate
{
public:
    MB_LayerPVPRanking();
    ~MB_LayerPVPRanking();
    
    static MB_LayerPVPRanking* create(const CCSize& sz);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(const CCSize& sz);
    
    virtual void onResetWnd();
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    void refreshRestCount();
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    void setScrollSize(const CCSize& sz);
private:
    
    CCSize m_cellSize;
    CCTableView* m_pTableView;
    
};

#endif /* defined(__ProjectMB__MB_LayerPVPRanking__) */
