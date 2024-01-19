//
//  MB_LayerSelfRaceRecord.h
//  ProjectPM
//
//  Create by WenYong on 1/6/2014.
//
//
#ifndef __ProjectMB__MB_LayerSelfRaceRecord__
#define __ProjectMB__MB_LayerSelfRaceRecord__

#include "MB_FunctionMainWnd.h"
#include "MB_PerfectRaceProtocol.h"
class MB_PerfectRaceInterface;
class MB_LayerSelfRaceRecord : public MB_FunctionMainWnd,public CCTableViewDataSource,public MB_RaceRecordDelegate
{
public:
	MB_LayerSelfRaceRecord();
	virtual ~MB_LayerSelfRaceRecord();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void setData(CCArray* pArray);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);

protected:
    void onCloseClick(CCObject* pSender);
private:
    MB_PerfectRaceInterface* m_pInterface;
    CCScale9Sprite*	scale9sprite;
    CCNode*	m_pNodeContainer;
    CCArray*    m_pDataArray;
    CCTableView*    m_pView;
    
    CCSize  m_CellSize;
};
#endif /* defined(__ProjectMB__MB_LayerSelfRaceRecord__) */