//  Description:道具升品

#ifndef __ProjectMB__MB_LayerItemEnhance__
#define __ProjectMB__MB_LayerItemEnhance__

#include "Game.h"
#include "MB_LayerRoleInfoHeader.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_NodeItemUnitJingLian;
class MB_LayerItemEnhance : public MB_ResWindow
,public CCBMemberVariableAssigner
,public CCBSelectorResolver
,public MB_NodeItemDelegate
,public CCTableViewDataSource
{
public:
    MB_LayerItemEnhance();
    ~MB_LayerItemEnhance();
    
    static MB_LayerItemEnhance* create(uint64_t itemUID = 0);
    
	virtual bool init(uint64_t itemUID);
    
    
    virtual void onResetWnd();
    void resetItemUID(uint64_t itemUID);
    void resetCostItemUID(MB_NodeItemUnitJingLian* iujl, uint64_t itemUID);
	
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void onCloseClicked(CCObject* pSender);
    void onCommitClicked(CCObject* pSender);
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    bool recvitem_up_rank(MB_MsgBuffer* recvPacket);
    
    void onCommit(CCObject* pSender);
    void onCancel(CCObject* pSender);
    
    MB_ItemData* getCostItem();
    
    void sortData();
    
    
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    MB_NodeItemUnitJingLian* m_pIujl;
private:
    bool m_bRoleInfoHeaderShow;
private:
    virtual void onClicked(MB_NodeItem* );
    void initEquips();
    uint64_t m_uItemUID;
    uint64_t m_uItemUIDCost;
    

    CCLabelTTF* m_pItemName1;
    CCNode* m_pCard;
//    CCSprite* m_pExpBar;
    CCLabelTTF* m_pTextRank_Title;
    CCLabelTTF* m_pTextDetailA1_Title;
    CCLabelTTF* m_pTextDetailA2_Title;
    CCLabelBMFont* m_pTextRank1;
    CCLabelBMFont* m_pTextDetailA1;
    CCLabelBMFont* m_pTextDetailA2;
    CCLabelBMFont* m_pTextRank2;
    CCLabelBMFont* m_pTextDetailB1;
    CCLabelBMFont* m_pTextDetailB2;
    CCNode* m_pJianTouA;
    CCNode* m_pJianTouB;
    CCNode* m_pCostIcon;
    CCLabelTTF* m_pTextCostName;
    CCLabelBMFont* m_pTextCostCoin;
    CCControlButton* m_pButtonCommit;
    CCControlButton* m_pButtonChangeCost;
    CCLabelTTF* m_pTTFMaxRank;
    CCNode* m_pNodeCost1;
    CCNode* m_pNodeCost2;

    CCBAnimationManager* m_pCCBAnimationMgr;
    CCLabelTTF* m_pOwerLabel;
    CCNode* m_pNodeEquip[6];
    TeamDataStruct* m_pDataStruct;
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCArray* m_pArrayCanChoose;
    CCSize m_szCell;
    bool isUpdateUI;
    bool isSetCost;
    bool lastShowRoleInfoPanel;
};

#endif /* defined(__ProjectMB__MB_LayerItemEnhance__) */
