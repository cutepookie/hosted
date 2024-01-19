//
//  MB_LayerItemList.h
//  ProjectPM
//
//  Create by WenYong on 6/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerItemList__
#define __ProjectMB__MB_LayerItemList__

#include "MB_ResWindow.h"
class MB_ItemData;
class MB_LayerItemList : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
	MB_LayerItemList();
	virtual ~MB_LayerItemList();
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onItemUsed(MB_ItemData* itemUID);
    void setTitle(int index);
    virtual void setItems(std::vector<uint64_t>& items);
protected:
    void onCloseClick(CCObject* pSender);
    std::vector<uint64_t> m_vContainer;
    CCSprite*	m_pTitleSpr;
    CCNode*     m_pNodeContainer;
    CCLabelTTF* m_pDescText;
};
#endif /* defined(__ProjectMB__MB_LayerItemList__) */
