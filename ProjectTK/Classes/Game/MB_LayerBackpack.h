//
//  MB_LayerBackpack.h
//  ProjectMB
//
//  Create by chenhongkun on 2/9/2014.
//
//
#ifndef __ProjectMB__MB_LayerBackpack__
#define __ProjectMB__MB_LayerBackpack__

#include "MB_FunctionMainWnd.h"
class MB_BackpackInterface;
class MB_ItemData;
class MB_LayerBackpack : public NSGameFunction::CCFunctionWnd,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    enum EPageType
    {
        kPageItem,
        kPageDebris,
        kPageEquip,
        kNoType,
    };
public:
	MB_LayerBackpack();
	virtual ~MB_LayerBackpack();
    
    static MB_LayerBackpack* create();
    virtual bool setDataSource(CCFunctionDataSource* pDataSource);
	virtual void onResetWnd();
	virtual bool init();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void onEquipPageClicked(CCObject* pSender = NULL);
    void onItemPageClicked(CCObject* pSender = NULL);
    void onItemDebrisClicked(CCObject* pSender = NULL);
    void onCloseClick(CCObject* pSender);
    
    bool isAnimation;
    bool isResetWnd;
private:
    CCNode*	m_pScrollsize;
    CCMenuItemImage*	m_pPageEquipBtn;
    CCMenuItemImage*	m_pPageItemBtn;
    CCMenuItemImage*    m_pPageDebrisBtn;
    CCLabelBMFont*	m_pItemCount;
    CCNode* m_pNumString;
    EPageType m_nPageType;
    MB_ResWindow* m_pEquipLayer;
    MB_ResWindow* m_pItemLayer;
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    void refreshCount();
    void updateIsContains(float dt);
    void updateIsContains2(float dt);
    void updateIsContains3(float dt);
protected:
    MB_BackpackInterface* m_pInterface;
    CCTableViewDataSource* m_pDataSource;
    CCTableView* m_pTableView;
    bool m_bChangePage;
    CCNode*     m_pNodeDebrisNum;
    CCNode*     m_pNodeItemNum;
    CCLabelBMFont* m_pTTFDebrisNum;
    CCLabelBMFont* m_pTTFItemNum;
};
#endif /* defined(__ProjectMB__MB_LayerBackpack__) */
