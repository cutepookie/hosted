//
//  MB_NodeSignItemView.h
//  ProjectMB
//
//  Create by ChenHongkun on 17/11/2014.
//
//
#ifndef __ProjectMB__MB_NodeSignItemView__
#define __ProjectMB__MB_NodeSignItemView__

#include "MB_ResWindow.h"
#include "MB_NodeItem.h"
class MB_NodeSignItemView : public MB_ResWindow
,public CCBMemberVariableAssigner,public MB_NodeItemDelegate
{
public:
	MB_NodeSignItemView();
	virtual ~MB_NodeSignItemView();
    
    static MB_NodeSignItemView* create(CCArray*,int);
	virtual void onResetWnd();
	virtual bool init(CCArray*,int);
    bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onClicked(MB_NodeItem* );
    static CCSize getNodeSize();
protected:
    CCLabelBMFont* m_pLabelDay;
    CCNode* m_pNodeSize;
    CCNode* m_pNodeItem;
    CCNode* m_pTodayBg;
private:
};
#endif /* defined(__ProjectMB__MB_NodeSignItemView__) */
