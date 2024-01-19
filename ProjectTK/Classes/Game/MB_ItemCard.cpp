
#include "MB_ItemCard.h"
#include "MB_ItemData.h"

MB_ItemCard::MB_ItemCard()
{
    m_pIcon      = NULL;
//    m_pFrame     = NULL;
//    m_pCardIcon  = NULL;
    m_pTypeIcon  = NULL;
    m_itemID     = 0;
    m_itemUID    = 0;
    m_pScroll    = NULL;
    m_pOverTime  = NULL;
//    m_pCardFrame = NULL;
    m_bCircleFrame = false;
}

MB_ItemCard::~MB_ItemCard()
{
    CC_SAFE_RELEASE(m_pIcon);
//    CC_SAFE_RELEASE(m_pFrame);
    CC_SAFE_RELEASE(m_pTypeIcon);
//    CC_SAFE_RELEASE(m_pCardIcon);
    CC_SAFE_RELEASE(m_pScroll);
    CC_SAFE_RELEASE(m_pOverTime);
//    CC_SAFE_RELEASE_NULL(m_pCardFrame);
}

MB_ItemCard* MB_ItemCard::create(uint64_t itemUID,bool bCircleFrame)
{
    MB_ItemCard* layer = new MB_ItemCard();
    if (layer != NULL && layer->init(itemUID,bCircleFrame)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

bool MB_ItemCard::init(uint64_t itemUID,bool bCircleFrame)
{
    CCLayer::init();
//    m_bCircleFrame = bCircleFrame;
    m_itemUID = itemUID;
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/item_node_card.ccbi", this);
    this->addChild(node);
    CC_SAFE_DELETE(pCCBReader);
    
    onResetWnd();
    
    return true;
}

void MB_ItemCard::setItemID(uint16_t var)
{
    m_itemID = var;
    m_itemUID = 0;
    onResetWnd();
}

uint16_t MB_ItemCard::getItemID()
{
    return m_itemID;
}

void MB_ItemCard::setItemUID(uint64_t var)
{
    m_itemUID = var;
    m_itemID = 0;
    dirty();
}

uint64_t MB_ItemCard::getItemUID()
{
    return m_itemUID;
}
//assign
bool MB_ItemCard::onAssignCCBMemberVariable(CCObject* pTarget,
                                            const char* pMemberVariableName,
                                            CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cardbg", CCSprite *, m_pCardIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCardFace", CCNode *, m_pIcon);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pQuallity", CCSprite *, m_pFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTypeIcon", CCSprite *, m_pTypeIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "moreinfo", CCNode *, m_pScroll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "time", CCSprite *, m_pOverTime);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCardFrame", CCSprite *, m_pCardFrame);
    
    
    return false;
}

cocos2d::SEL_MenuHandler MB_ItemCard::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_ItemCard::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

void MB_ItemCard::animateComplete()
{
    dirty();
}

void MB_ItemCard::onResetWnd(void)
{
    MB_ItemMgr*    pItemMgr;
    MB_ItemData*       pItemEntity;
    MB_ItemTemplate*   pItemTemplate;
    
    pItemMgr        = MB_ItemMgr::getInstance();
    pItemEntity     = pItemMgr->getItemDataByUID(m_itemUID);
    pItemTemplate   = pItemMgr->getItemTemplateByID(pItemEntity?pItemEntity->getItemID():m_itemID);

    //找不到模板
    if (pItemTemplate == NULL)
    {
        return;
    }
    
    int quality;
    quality = pItemTemplate->getItemStar();
    if (pItemEntity) {
        quality += pItemEntity->getItemRank()/10;
    }
    
    if(pItemTemplate)
    {
        m_pIcon->removeAllChildrenWithCleanup(true);
        MB_NodeItem* pNodeItem = MB_NodeItem::create(pItemTemplate->getItemID());
        pNodeItem->showNameCount(false);
        if(pNodeItem)m_pIcon->addChild(pNodeItem);
        
    }

    m_pScroll->setVisible(false);

}

