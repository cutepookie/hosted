

#ifndef __ProjectMB__MB_LayerListEquipChange__
#define __ProjectMB__MB_LayerListEquipChange__

#include "Game.h"

#include "MB_LayerRoleInfoHeader.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MB_LayerListEquipChange: public MB_ResWindow
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCTableViewDataSource
{
    
public:
    MB_LayerListEquipChange();
    ~MB_LayerListEquipChange();
    
    static MB_LayerListEquipChange* create(int type = 0, uint8_t itemPos = 0, uint64_t itemUID = 0, uint64_t petUID = 0);
    virtual bool init(int type, uint8_t itemPos, uint64_t itemUID, uint64_t petUID);
    
    virtual void onResetWnd();
    
    void onMsgRecv(CCNode* node, SocketResponse* response);
    
    
    virtual bool                 onAssignCCBMemberVariable      (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    virtual SEL_MenuHandler      onResolveCCBCCMenuItemSelector (CCObject * pTarget,const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector  (CCObject * pTarget,const char* pSelectorName);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    CC_SYNTHESIZE(int, m_kSubType, SubType);
    CC_SYNTHESIZE(uint64_t, m_uItemUID, ItemUID);
    CC_SYNTHESIZE(uint64_t, m_uPetUID, PetUID);
    CC_SYNTHESIZE(uint8_t, m_uItemPos, ItemPos);
    
    void onCloseClicked(CCObject* pSender);
    void refreshCount();
private:
    bool m_bRoleInfoHeaderShow;
private:
    CCNode* m_pTableContainer;
    CCTableView* m_pTableView;
    CCSize m_szCell;
    CCArray* m_pArrayShows; //只是指针,不创建和销毁
    CCNode* m_pNumString;
    CCLabelBMFont* m_pItemCount;
    int allCellCount;
    vector<int> isRunedIdx;
    bool isAllRun;
};

#endif /* defined(__ProjectMB__MB_LayerListEquipChange__) */
