//
//  MB_RandomComposePlatformEx.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-8.
//
//

#include "MB_RandomComposePlatformEx.h"

#include "MB_LayerChooseMaterial.h"
#include "MB_ComposeInterface.h"
#include "MB_FunctionMgr.h"
MB_RandomComposePlatformEx::MB_RandomComposePlatformEx()
{
    m_pBtnEquip = NULL;
    m_pBtnPet = NULL;
    m_pComposeInterface = NULL;
}

MB_RandomComposePlatformEx::~MB_RandomComposePlatformEx()
{
}
MB_RandomComposePlatformEx* MB_RandomComposePlatformEx::create(int nType)
{
    MB_RandomComposePlatformEx* pInstance = new MB_RandomComposePlatformEx;
    if (pInstance && pInstance->init(0,nType))
    {
        pInstance->m_pComposeInterface =  MB_FunctionMgr::getInstance()->queryFunctionByType<MB_ComposeInterface>(kFunctionCompose);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    
    return pInstance;
}


void MB_RandomComposePlatformEx::goSelectItemRandom(int clickIndex)
{
    
    std::vector<uint64_t>   ItemList1,ItemList2;
    NSGameHelper::getAllMonstersUidFromPetMgr(ItemList1,6,NSGameHelper::filter_unused);
    NSGameHelper::getAllEquipItemsFromItemMgr(ItemList2,6,NSGameHelper::filter_unused);
    if (ItemList1.size() == 0 && ItemList2.size() == 0)
    {
        MB_Message::sharedMB_Message()->showMessage("已经没有可放入的材料了");
        return;
    }
    
    if(getInputItemStar() == -1)
    {
        m_nSelected = clickIndex;
        MB_LayerChooseMaterial * pLayer1 = MB_LayerChooseMaterial::create();
        if (pLayer1)
        {
            pLayer1->setDelegate(this);
            pushWindow(pLayer1);
        }
        return;
    }
    
    MB_RandomComposePlatform::goSelectItemRandom(clickIndex);
}




void MB_RandomComposePlatformEx::onEquipAutopickClicked(CCObject* obj)
{
    if(m_pBtnEquip == NULL)m_pBtnEquip = dynamic_cast<CCMenuItemImage*>(obj);
    if (m_nType == 1 || !getIsInputComplate())
    {
        setType(kSelectItem);
    }
    m_nType = 2;
    if(getIsInputComplate())
    {
        if(m_pBtnEquip)
        {
//           NSGameHelper::setMenuItemImage4AllState(m_pBtnEquip, "btn_enter_equip_01.png");
        }
    }
    
    if(m_pBtnPet)
    {
//        NSGameHelper::setMenuItemImage4AllState(m_pBtnPet, "btn_enter_equip_01.png");
        
    }
    
    MB_RandomComposePlatform::onAutoInputClicked(this);
}

void MB_RandomComposePlatformEx::onPetAutopickClicked(CCObject* obj)
{
    if(m_pBtnPet == NULL)m_pBtnPet = dynamic_cast<CCMenuItemImage*>(obj);
    if (m_nType == 2 || !getIsInputComplate())
    {
        setType(kSelectPet);
    }
    m_nType = 1;
    if(getIsInputComplate())
    {
        if(m_pBtnPet)
        {
//            NSGameHelper::setMenuItemImage4AllState(m_pBtnPet, "换一批精灵");
//            NSGameHelper::setMenuItemImage4AllState(m_pBtnPet, "btn_enter_sprit_01.png");
        }
    }
    else
    {
        setType(kSelectPet);
    }
    
    if(m_pBtnEquip)
    {
//       NSGameHelper::setMenuItemImage4AllState(m_pBtnEquip, "自动放入装备");
//        NSGameHelper::setMenuItemImage4AllState(m_pBtnPet, "btn_enter_sprit_01.png");
    }
    MB_RandomComposePlatform::onAutoInputClicked(this);
}

void MB_RandomComposePlatformEx::recvcombine_pet(MB_MsgBuffer* pbuff)
{
    MB_RandomComposePlatform::recvcombine_pet(pbuff);
//    if(m_pBtnPet)NSGameHelper::setMenuItemImage4AllState(m_pBtnPet, "自动放入精灵");
}

void MB_RandomComposePlatformEx::recvcombine_equip(MB_MsgBuffer* pbuff)
{
    MB_RandomComposePlatform::recvcombine_equip(pbuff);
//    if(m_pBtnEquip)NSGameHelper::setMenuItemImage4AllState(m_pBtnEquip, "自动放入装备");
}

bool MB_RandomComposePlatformEx::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    if (MB_RandomComposePlatform::onAssignCCBMemberVariable(this,pMemberVariableName,pNode))
    {
        return true;
    }
    
    return false;
}


SEL_MenuHandler MB_RandomComposePlatformEx::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    SEL_MenuHandler pHandler = MB_RandomComposePlatform::onResolveCCBCCMenuItemSelector(pTarget,pSelectorName);
    if(pHandler)
    {
        return pHandler;
    }
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEquipAutopickClicked", MB_RandomComposePlatformEx::onEquipAutopickClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetAutopickClicked", MB_RandomComposePlatformEx::onPetAutopickClicked);
    return NULL;
}





void MB_RandomComposePlatformEx::resetRandom()
{
    MB_RandomComposePlatform::resetRandom();
}
