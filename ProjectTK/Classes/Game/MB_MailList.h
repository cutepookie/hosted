//
//  MB_MailList
//  ProjectTK
//
//  Created by lic
//
//

#ifndef __MB__MB_MailList__
#define __MB__MB_MailList__
#include "MB_ResWindow.h"
#include "Game.h"

class MB_MailList:public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCTableViewDataSource
,public CCTableViewDelegate
{
    
public:
    MB_MailList();
    virtual ~MB_MailList();
    
    CREATE_FUNC(MB_MailList)
    
    CC_PROPERTY(kmMailsTable, m_currentTable, CurrentTable)
    bool init();
    virtual void                 onInitDidFinish(void);
    virtual void                 onMessage(unsigned int msg ,cocos2d::CCObject* param);
    
    virtual CCSize               cellSizeForTable                (CCTableView *table);
    virtual CCTableViewCell*     tableCellAtIndex                (CCTableView *table, unsigned int idx);
    virtual unsigned int         numberOfCellsInTableView        (CCTableView *table);
    virtual void                 tableCellTouched                (CCTableView* table, CCTableViewCell* cell);
    virtual void                 scrollViewDidScroll             (CCScrollView* view);
    virtual void                 scrollViewDidZoom               (CCScrollView* view);
    void setScrollSize(const CCSize& sz);
public:
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
protected:
    virtual void onResetWnd(void);
    void            onMsgRecv         (CCNode* node, SocketResponse* response);
    
private:
    CCNode*                         m_playout;
    CCTableView*                    m_pTableView;
//    std::vector<MB_MailSubItem*>    m_subItemCache;
    CCSize                          m_itemSize;
};
#endif