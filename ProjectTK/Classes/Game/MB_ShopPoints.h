

#ifndef ProjectMB_MB_ShopPoints_h
#define ProjectMB_MB_ShopPoints_h

#include "MB_ShopBase.h"
#include "MB_RoleSoundSystem.h"
class MB_ShopMain;
class MB_ShopPoints:public MB_ShopPageBase
{
    friend class MB_ShopMain;
    MB_ShopPoints(void);
public:
    static MB_ShopPoints* create();
    
    virtual        ~MB_ShopPoints(void);
    
    
    virtual bool    onAssignCCBMemberVariable       (CCObject* pTarget,
                                                     const char* pMemberVariableName,
                                                     CCNode* pNode);
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    unsigned int numberOfCellsInTableView(CCTableView *table);
    void onCloseClick(CCObject*);
    void onResetWnd();
    
    void onMsgRecv (CCNode*    node, SocketResponse* response);
    
    virtual bool init();
    
    void onEnter()
    {
        MB_ResWindow::onEnter();
        PlayRoleSound(kSoundEnterShop_3);
    }
};



#endif
