//
//  MB_LayerItemDetail.h
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#ifndef __ProjectMB__MB_LayerItemDetail__
#define __ProjectMB__MB_LayerItemDetail__
#include "MB_NodeItem.h"
#include "MB_ResWindow.h"
class MB_ItemData;
class MB_LayerItemDetail : public MB_ResWindow,public CCBMemberVariableAssigner,public CCBSelectorResolver
{
public:
    MB_LayerItemDetail();
    virtual ~MB_LayerItemDetail();
    virtual void onResetWnd(){};
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    void setItemUID(uint64_t uid);
    void setItemTID(uint16_t tid);
    static MB_LayerItemDetail* create(uint64_t nUid,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    static MB_LayerItemDetail* createByType(uint16_t nTid,NODEITEMNOWWINDOW nowWindow = kDAOJU);
    static bool showItemDetailByTID(uint16_t nTid);
    static bool showItemDetailByUID(uint64_t nUid);
    void onReSet(bool isReSet = false);
    int detail_type;
    uint8_t detail_itemPos;
    uint64_t detail_petID;
    CC_SYNTHESIZE(int, m_kSubType, SubType);
protected:
    void onCloseClicked(CCObject* pSender);
    void onClickQH(CCObject* pSender);
    void onClickJL(CCObject* pSender);
    void onClickZB(CCObject* pSender);
    void onClickHC(CCObject* pSender);
    void onUseClicked(CCObject* pSender);
    void onOpenClicked(CCObject* pSender);
    void onOpenMoreClicked(CCObject* pSender);
    void resetByTID(uint16_t nTypeID,MB_ItemData* pMB_ItemData=NULL);
    void setItem(MB_ItemTemplate* pTemplate);
private:
    CCNode*	m_pNodeEquipProperty;
    CCNode* m_pNodeDescProperty;
    CCLabelTTF*	m_pItemName;
    CCLabelBMFont*	m_pProperty[4];
    CCLabelTTF* m_pPropertyTitle[4];
    CCLabelTTF* m_pLabelBeEquip;
    CCNode* m_pNodeIcon;
    CCLabelTTF*	m_pDescribe;
    
    uint64_t    m_nItemUID;
    uint16_t    m_nItemTID;
    CCControlButton* m_pZBBtn;
    NODEITEMNOWWINDOW m_eNowWindow;
    bool isSet;
    CCNode* m_pJLBtn;
    CCNode* m_pQHBtn;
    CCSprite* m_pBgEquip;
    CCNode* m_pBgItem;
    CCNode* m_pSuiPian;
    CCNode* m_pBaoWu;
    CCNode* m_pHCBtn;
    CCNode* m_pMoveNode;
    CCLabelBMFont* m_pNum1;
    CCLabelBMFont* m_pNum2;
    CCNode* m_pNodeOpenOne;
    CCNode* m_pNodeUse;
    CCNode* m_pNodeOpenMore;
    CCControlButton* m_pBtnOpenMore;
    CCLabelTTF* m_pLastTimes;
    CCNode* m_pMoveDown;
};
#endif /* defined(__ProjectMB__MB_LayerItemDetail__) */
