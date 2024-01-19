

#ifndef __ProjectMB__MB_LayerEventDetail__
#define __ProjectMB__MB_LayerEventDetail__
#include "Game.h"
class MB_MoneyEevntData;
class MB_LayerEventDetail:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver,
public cocos2d::extension::CCTableViewDataSource,
public cocos2d::extension::CCTableViewDelegate
{
private:
    MB_MoneyEevntData *m_pData;
    CCNode* m_pNodeDes;
protected:
    int m_nlength;
    CCSize m_UnitSize;
    CCNode *m_pNodeScroller;
    CCTableView * m_pTabelView;
public:
    MB_LayerEventDetail();
    virtual ~MB_LayerEventDetail();
    virtual bool init(int eventID);
    static  MB_LayerEventDetail * create(int eventID);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual CCSize cellSizeForTable(CCTableView *table) ;
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table) ;
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(CCScrollView* view){
        
    }
    virtual void scrollViewDidZoom(CCScrollView* view){
        
    }

    CC_SYNTHESIZE(int,m_nEventID, EventID);
    CCTableView  * getTable(){
        
        return m_pTabelView;
    }
};

#endif /* defined(__ProjectMB__MB_LayerEventDetail__) */
