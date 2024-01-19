//
//  MB_LayerChapterRank.h
//  ProjectMB
//
//  Created by yuanwugang on 14-9-26.
//
//

#ifndef __ProjectMB__MB_LayerChapterRank__
#define __ProjectMB__MB_LayerChapterRank__

#include "MB_ResWindow.h"

class MB_LayerChapterRank:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public cocos2d::extension::CCTableViewDataSource
{
public:
    MB_LayerChapterRank();
    ~MB_LayerChapterRank();
    static MB_LayerChapterRank* create();
    virtual bool init();
    virtual void onResetWnd();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
protected:
    void onCloseClick(CCObject* pSender);
    
private:
    CCNode*     m_pNodeRankList;
    CCLabelTTF* m_pTTFRank;
    CCLabelTTF* m_pTTFChapter;
    
    CCTableView* m_pTableView;
    CCSize       m_CellSize;
    
    CCArray*    m_pDataArray;
};

#endif /* defined(__ProjectMB__MB_LayerChapterRank__) */
