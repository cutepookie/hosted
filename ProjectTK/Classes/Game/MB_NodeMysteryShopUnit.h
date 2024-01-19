//
//  MB_NodeMysteryShopUnit.h
//  ProjectMB
//
//  Created by chenhongkun on 14-9-12.
//
//

#ifndef __ProjectMB__MB_NodeMysteryShopUnit__
#define __ProjectMB__MB_NodeMysteryShopUnit__
#include "MB_NodeRefreshShopUnit.h"
class MB_PetTemplate;
class MB_ItemTemplate;
class MB_ShopGoodsItem;
class MB_NodeMysteryShopUnit :public MB_NodeRefreshShopUnit
{
public:
    enum EType
    {
        kPet = 0,
        kItem = 1,
    };
public:
    MB_NodeMysteryShopUnit();
    static MB_NodeMysteryShopUnit* create(MB_ShopGoodsItem*,EType type,bool bTutorial = false);
    void onResetWnd();
    bool init();
    
    void onDetailClick(CCObject* pSender);
    void onBuyClicked(CCObject* pSender);
private:
    MB_ShopGoodsItem* m_pShopGoodsItem;
    MB_PetTemplate* m_pMB_PetTemplate;
    MB_ItemTemplate* m_pMB_ItemTemplate;
    EType m_nType;
};

#endif /* defined(__ProjectMB__MB_NodeMysteryShopUnit__) */
