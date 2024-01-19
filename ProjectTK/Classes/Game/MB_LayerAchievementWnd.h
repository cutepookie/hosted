//
//  MB_LayerAchievementWnd.h
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerAchievementWnd__
#define __ProjectMB__MB_LayerAchievementWnd__

#include "MB_ResWindow.h"


enum kAChievementState
{
    kUnComplateSelect = 1,
    kComplateSelect,
};

class MB_LayerAchievementWnd : public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCTableViewDataSource
{
public:
	MB_LayerAchievementWnd();
	virtual ~MB_LayerAchievementWnd();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual CCSize cellSizeForTable(CCTableView *);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
protected:
    void onCloseClicked(CCObject* pSender);
    void recvtask_error(MB_MsgBuffer* recvPacket);
    void recvtask_operate(MB_MsgBuffer* recvPacket);
    void reloadArray();
private:
    CCNode*             m_pNodeList;
    
    CCTableView*        m_pTableView;
    CCSize              m_szUnitSize;
    CCArray* arrayAchievement;
    
};
#endif /* defined(__ProjectMB__MB_LayerAchievementWnd__) */
