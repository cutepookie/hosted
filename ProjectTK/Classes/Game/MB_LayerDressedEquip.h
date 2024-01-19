//
//  MB_LayerDressedEquip.h
//  ProjectMB
//
//  Create by ChenHongkun on 23/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerDressedEquip__
#define __ProjectMB__MB_LayerDressedEquip__

#include "MB_ResWindow.h"
#include "MB_TeamData.h"
#include "MB_LayerRoleInfoHeader.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerDressedEquip : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver, public CCTableViewDataSource

{
public:
    static MB_LayerDressedEquip* create(TeamDataStruct*);
	MB_LayerDressedEquip();
	virtual ~MB_LayerDressedEquip();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
    bool m_bRoleInfoHeaderShow;
protected:
    void onCloseClicked(CCObject* pSender);
private:
    CCNode*	m_pTableContainer;
    CCTableView* m_pTableView;
    CCArray* m_pArrayShows;
    CCLabelBMFont* m_pChapterText;
    TeamDataStruct* m_pDataStruct;
};
#endif /* defined(__ProjectMB__MB_LayerDressedEquip__) */
