//
//  MB_LayerChooseMaterial.cpp
//  ProjectPM
//
//  Created by cri-mac on 14-6-8.
//
//

#include "MB_RandomComposePlatformEx.h"
#include "MB_LayerChooseMaterial.h"
#include "Game.h"
#include "MB_LayerChatMain.h"

MB_LayerChooseMaterial::MB_LayerChooseMaterial()
{
    m_pSelectNode = NULL;
    m_nType = 0;
    m_pNodeList = NULL;
    m_pTitle = NULL;
    m_pDelegate = NULL;
    m_szGuiName = "res/item_layer_list6.ccbi";
    m_pPetButton = NULL;
    m_pEquipButton = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = true;
    MB_LayerChatMain::SetChatMainVisible(false, "MB_LayerChooseMaterial");
}

MB_LayerChooseMaterial::~MB_LayerChooseMaterial()
{
    CC_SAFE_RELEASE_NULL(m_pSelectNode);
    CC_SAFE_RELEASE_NULL(m_pNodeList);
    CC_SAFE_RELEASE_NULL(m_pTitle);
    CC_SAFE_RELEASE_NULL(m_pPetButton);
    CC_SAFE_RELEASE_NULL(m_pEquipButton);
    
    m_nType = 0;
    m_pDelegate = NULL;
//    MB_LayerChatMain::SetChatMainVisible(true, "MB_LayerChooseMaterial");
}

MB_LayerChooseMaterial* MB_LayerChooseMaterial::create(int nType)
{
    MB_LayerChooseMaterial* pInstance = new MB_LayerChooseMaterial;
    if (pInstance && pInstance->init(nType))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}


bool MB_LayerChooseMaterial::init(int nType)
{
    CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    CCNode* pNode = pCCBReader->readNodeGraphFromFile(m_szGuiName.c_str(), this);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    if (pNode == NULL)
    {
        return false;
    }
    
    CCNode* pUntouch = NSGameHelper::createDisableTouchLayer12();
    
    addChild(pUntouch);
    addChild(pNode);
   
    m_nType = nType;
    if(m_nType == kSelectPet)
    {
        NSGameHelper::getAllMonstersUidFromPetMgr(m_pItemList,6,NSGameHelper::filter_unused);
    }
    else
    {
        NSGameHelper::getAllEquipItemsFromItemMgr(m_pItemList,6,NSGameHelper::filter_unused);
    }
    
//    if (m_pItemList.size() == 0)
//    {
//        onResetWnd();
//        return true;
//    }
    
    m_Size = MB_NodeSelect::getUintSize(m_nType);
    
    m_pNodeList->removeAllChildren();
    NSGameHelper::adjustScrollNode(m_pNodeList);
    
    m_pTableView = CCTableView::create(this, m_pNodeList->getContentSize());
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setDirection( kCCScrollViewDirectionVertical);
    m_pNodeList->addChild(m_pTableView);
    
    onResetWnd();
    
    
    m_pPetButton->setIsScale(false);
    m_pEquipButton->setIsScale(false);
    return true;
}


void MB_LayerChooseMaterial::onResetWnd()
{
    m_pItemList.clear();
    if(m_nType == kSelectPet)
    {
        NSGameHelper::getAllMonstersUidFromPetMgr(m_pItemList,6,NSGameHelper::filter_unused);
        m_pEquipButton->setEnabled(true);
        m_pPetButton->setEnabled(false);
    }
    else
    {
        m_pEquipButton->setEnabled(false);
        m_pPetButton->setEnabled(true);
        NSGameHelper::getAllEquipItemsFromItemMgr(m_pItemList,6,NSGameHelper::filter_unused);
    }
    if(m_pTableView)m_pTableView->reloadData();
}

void MB_LayerChooseMaterial::setTitle(const char* pTitle)
{
    m_pTitle->setString(pTitle);
}

bool MB_LayerChooseMaterial::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "chapterText", CCLabelBMFont*, m_pTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_list", CCNode*, m_pNodeList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_selected", CCNode*, m_pSelectNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "tab_pet", CCMenuItemImage*, m_pPetButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "tab_equip", CCMenuItemImage*, m_pEquipButton);
    
    return false;
}

SEL_MenuHandler MB_LayerChooseMaterial::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onPetClicked",MB_LayerChooseMaterial::onPetClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onEquipClicked",MB_LayerChooseMaterial::onEquipClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerChooseMaterial::onBackClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerChooseMaterial::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

CCSize MB_LayerChooseMaterial::cellSizeForTable(CCTableView *table)
{
    return m_Size;
}

CCTableViewCell* MB_LayerChooseMaterial::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    MB_NodeSelect* pUint = MB_NodeSelect::create(m_nType, m_pItemList[idx]);
    if (pUint)
    {
        cell->addChild(pUint);
        pUint->setPosition(ccp(m_pNodeList->getContentSize().width/2.0f,pUint->getNodeSize().height/2.0f));
    }
    
    return cell;
}

unsigned int MB_LayerChooseMaterial::numberOfCellsInTableView(CCTableView *table)
{
    return m_pItemList.size();
}

void MB_LayerChooseMaterial::onBackClicked(CCObject* pObject)
{
    popWindow();
}

void MB_LayerChooseMaterial::onPetClicked(CCObject* pObject)
{
    m_nType = kSelectPet;
    onResetWnd();
}

void MB_LayerChooseMaterial::onEquipClicked(CCObject* pObject)
{
    m_nType = kSelectItem;
    onResetWnd();
}

void MB_LayerChooseMaterial::onNodeSelected(uint64_t nUid,uint16_t nType)
{
    MB_TARGET_PARENT(MB_RandomComposePlatformEx, ptr);
    if(ptr)
    {
        ptr->onNodeSelected(nUid,nType);
        onBackClicked(NULL);
    }
//    if (m_pDelegate)
//    {
//        m_pDelegate->onNodeSelected(nUid, nType);
//        onBackClicked(NULL);
//    }
}
