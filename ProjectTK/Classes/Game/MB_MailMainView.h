
#ifndef __MB__MB_MailMainView__
#define __MB__MB_MailMainView__
#include "MB_ResWindow.h"
#include "Game.h"
#include "MB_CommonType.h"
#include "MB_MailSubItem.h"

class MB_MailMainView:
public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCTableViewDataSource ,
public CCTableViewDelegate
{
public:
    MB_MailMainView();
    virtual ~MB_MailMainView();
    
    CREATE_FUNC(MB_MailMainView);
public:
    virtual bool init();
    CCArray  * getRewardArray(){
        
        return  m_pRewardArray;
    }
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual CCSize               cellSizeForTable                (CCTableView *table);
    virtual CCTableViewCell*     tableCellAtIndex                (CCTableView *table, unsigned int idx);
    virtual unsigned int         numberOfCellsInTableView        (CCTableView *table);
    virtual void                 tableCellTouched                (CCTableView* table, CCTableViewCell* cell);
    virtual void                 scrollViewDidScroll             (CCScrollView* view);
    virtual void                 scrollViewDidZoom               (CCScrollView* view);
    
    
public:
    virtual void onInitDidFinish    (void);
public:
    virtual void onMessage          (unsigned int msg ,cocos2d::CCObject* param);
protected:
    
    void OnClose        (CCObject* pSender);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void OnRequestMails (void);
    
    virtual void recvmail_draw_reward(MB_MsgBuffer* pRecv);
protected:
    MB_MailSubItem* generateItemInCache(int index);
    void            clearCache(void);
protected:
    virtual void onResetWnd(void);
protected:
    CCNode*              m_pPositionSign;
    CCTableView*         m_pTableView;
    CCArray * m_pRewardArray;
    
protected:
    std::vector<MB_MailSubItem*>      m_subItemCache;
//    MB_MailSelectMore*                m_pSelectMore;
protected:
    kmMailsTable                      m_currentPage;
    CCSize                            m_itemSize;
    int                               m_nLastPage;
};
#endif
