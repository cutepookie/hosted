//
//  MB_LayerServerPanel.h
//  ProjectMB
//
//  Create by WenYong on 27/8/2014.
//
//
#ifndef __ProjectMB__MB_LayerServerPanel__
#define __ProjectMB__MB_LayerServerPanel__

#include "MB_ResWindow.h"

class MB_LayerServerPanel : public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCTableViewDataSource
{
public:
    CREATE_FUNC(MB_LayerServerPanel);
	MB_LayerServerPanel();
	virtual ~MB_LayerServerPanel();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    void selectRange(uint16_t begin,uint16_t end);
protected:
    void onCloseClick(CCObject* pSender);
    void onOldServerClicked(CCObject* pSender);
    void resetServerZone(int newIndex);
private:
    int     m_nSelectIndex;
    CCTableView*    m_pTableView;
    CCScrollView*   m_pScrollView;
    
    CCNode*	m_pServerContainer;
    CCNode*	m_pServerView;
    CCNode*	m_pNodeLastLogin;
    CCNode* m_pNodeServerState1;
    CCNode* m_pNodeServerState2;
    CCNode* m_pNodeServerState3;
    
    CCLabelTTF* m_pTTFName;
    CCLabelTTF* m_pTTFID;
    
    
};
#endif /* defined(__ProjectMB__MB_LayerServerPanel__) */