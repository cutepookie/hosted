//
//  MB_LayerWorld.h
//  ProjectPM
//
//  Create by WenYong on 18/6/2014.
//
//
#ifndef __ProjectMB__MB_LayerWorld__
#define __ProjectMB__MB_LayerWorld__

#include "MB_ResWindow.h"

class MB_LayerWorld : public MB_ResWindow,
public CCBMemberVariableAssigner,
public CCBSelectorResolver,
public CCTableViewDataSource
{
public:
	MB_LayerWorld();
	virtual ~MB_LayerWorld();
	virtual void onResetWnd();
	CREATE_FUNC(MB_LayerWorld);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx) ;
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    bool bindTutorialPostion(int kFuntionType);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
protected:
    int functionIndex(int kFuntionType);
    virtual bool init();
    void onCloseClick(CCObject* pSender);
    void ready4Data();
    void pushValidateType(int type);
private:
    CCTableView*        m_pView;
    CCNode*             m_pContainer;
    CCSize              m_CellSize;
    std::vector<int>    m_nTypes;
    CCNode*             m_pNodeTutorial;
};
#endif /* defined(__ProjectMB__MB_LayerWorld__) */
