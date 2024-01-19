

#ifndef ProjectMB_MB_ShopIngots_h
#define ProjectMB_MB_ShopIngots_h

#include "MB_ShopBase.h"

#include "MB_RoleSoundSystem.h"
//礼包商店
class MB_ShopMain;
class MB_NodeVipDailyReward;
class MB_IngotsShopInterface;
class MB_ShopIngots:public MB_ShopPageBase
{
    friend class MB_ShopMain;
    MB_ShopIngots(void);
public:
    static MB_ShopIngots* create();
    
    virtual        ~MB_ShopIngots(void);
        virtual CCSize cellSizeForTable(CCTableView *table);
    virtual bool    onAssignCCBMemberVariable       (CCObject* pTarget,const char* pMemberVariableName,CCNode* pNode);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    unsigned int numberOfCellsInTableView(CCTableView *table);
    
    void onMsgRecv (CCNode*    node, SocketResponse* response);
    
    void onResetWnd();
    
    void onEnter()
    {
        MB_ShopPageBase::onEnter();
        PlayRoleSound(kSoundEnterVipShop);
    }
    
    virtual bool init();
private:
    CCNode* m_pNodeVipDes;
    CCNode* m_pNodeDailyVipReward;
    MB_NodeVipDailyReward* m_pNodeReward;
    MB_IngotsShopInterface* m_pInterface;
};


#endif
