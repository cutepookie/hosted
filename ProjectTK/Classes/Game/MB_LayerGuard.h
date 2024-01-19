//
//  MB_LayerGuard.h
//  ProjectMB
//
//  Create by wenyong on 3/3/2015.
//
//
#ifndef __ProjectMB__MB_LayerGuard__
#define __ProjectMB__MB_LayerGuard__

#include "MB_ResWindow.h"
#include "MB_GuardProtocol.h"
#include "MB_LocalProto.h"
class MB_LayerGuard : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver,public cocos2d::extension::CCTableViewDataSource
{
public:
    MB_LayerGuard();
    virtual ~MB_LayerGuard();
    virtual void onResetWnd();
    
    static MB_LayerGuard* create(int index = 0);
    
    virtual bool init(int index);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setSelectPetID(int index,bool isF = false);
    
    void setPetGuard(uint64_t uid);
protected:
    void onCloseClick(CCObject* pSender);
    void onLockClicked1(CCObject* pSender);
    void onLockClicked2(CCObject* pSender);
    void onLockClicked3(CCObject* pSender);
    void onLockClicked4(CCObject* pSender);
    void onLockClicked5(CCObject* pSender);
    void onLockClicked6(CCObject* pSender);
    void onChangeClicked(CCObject* pSender);
    void onRuleClicked(CCObject* pSender);
    
    virtual void onMsgRecv(CCNode* node, SocketResponse* response);
    void onResetShow();
    int getLockNum();
    bool setLockCost(int index);
    
    
    void onConfirmChange(CCObject *pSender);
    void goCharge(CCObject*);
    void reloadArray();
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
private:
    CCLabelBMFont*	m_pTTFCost;
    CCLabelTTF*	m_pTTFAttribute[4];
    CCLabelTTF*	m_pTTFAttributeEX[GUARD_ATTR_MAX];
    CCMenuItemImage*	m_pMenuLock[GUARD_ATTR_MAX];
    CCNode* m_pNodeLock[6];
    uint64_t m_nSelectIndex;
    bool m_bLock[6];
    CCNode* m_pNodeScroller;
    CCNode *m_pYlNode[CARD_IN_GAME];
    CCArray *m_pArray;
    CCSize m_objUnitSize;
    CCNode* m_pScrollsize;
    int m_nListSize;
    CCTableView *m_pTableView;
    bool isUpdateUI;
    bool isHomeButtonShow;
};
#endif /* defined(__ProjectMB__MB_LayerGuard__) */
