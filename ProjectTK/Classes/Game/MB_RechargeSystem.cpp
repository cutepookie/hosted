//
//  MB_RechargeSystem.cpp
//  ProjectPM
//
//  Created by WenYong on 14-6-6.
//
//

#include "MB_RechargeSystem.h"
#include "MB_ItemData.h"
#include "MB_LayerRechargeItemList.h"

MB_RechargeSystem* MB_RechargeSystem::m_pThisInstance = NULL;

MB_RechargeSystem* MB_RechargeSystem::getInstance()
{
    if (m_pThisInstance == NULL)
    {
        m_pThisInstance = new MB_RechargeSystem;
    }
    return m_pThisInstance;
}

void MB_RechargeSystem::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(m_pThisInstance);
}

MB_RechargeSystem::~MB_RechargeSystem()
{
    
}

MB_RechargeSystem::MB_RechargeSystem()
{
}

/*
 Energy_ADD = 1,                 //体力道具
 Discovery_ADD = 2,              //探索次数道具
 PVP_ADD = 3,                    //争霸次数道具
 */
bool MB_RechargeSystem::showRechargeWndByType(int RechargeType,MB_ResWindow* pParent)
{
//    static const char* text[] = {"","补充体力","补充冒险次数","增加挑战次数"};
    if (RechargeType<1 || RechargeType >3)
    {
        return false;
    }
    std::vector<uint16_t> vContainer;
    MB_ItemMgr::getInstance()->getUseItemTidByType(RechargeType,vContainer);
    std::vector<uint16_t>::iterator it = vContainer.begin();
    
    std::vector<uint64_t> vItems;
    for (; it!=vContainer.end(); )
    {
        if(MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(*it)==0)
        {
            it = vContainer.erase(it);
        }
        else
        {
            NSGameHelper::getOtherItemByTypeID(*it, vItems);
            ++it;
        }
    }
    
    vContainer.clear();
    if (vItems.empty())
    {
        return false;
    }
    
    if (pParent)
    {
        MB_LayerRechargeItemList* pWnd = MB_LayerRechargeItemList::create();
        if (pWnd)
        {
            pWnd->setTitle(RechargeType);
            pWnd->setItems(vItems);
            pParent->setShowRoleInfoPanel(true);
            if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_CHAT_TAG)) {
                CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd,Z_ORDER_CHAT+1);
            }else
            {
                pParent->pushWindow(pWnd);
            }

            return true;
        }
    }
    
    return false;
}
