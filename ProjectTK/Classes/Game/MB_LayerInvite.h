
#ifndef __ProjectMB__MB_LayerInvite__
#define __ProjectMB__MB_LayerInvite__

#include "Game.h"

class MB_LayerInvite:public MB_ResWindow,
public CCBMemberVariableAssigner
,public CCBSelectorResolver,
public cocos2d::extension::CCTableViewDataSource,
public cocos2d::extension::CCTableViewDelegate {
    
    private:

    CCNode *m_pNode;
    CCTableView * m_pTableView;
    CCSize m_pSize;
    int m_nLength;
    CCArray *m_pArray;
    
    public :
    
    MB_LayerInvite();
    ~MB_LayerInvite();
    virtual bool init(CCArray *array);
    static  MB_LayerInvite * create(CCArray *array);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    void onCloseClicked(CCObject *);
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

};

#endif /* defined(__ProjectMB__MB_LayerInvite__) */
