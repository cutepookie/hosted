

#include "MB_NodeItemUnit.h"
#include "MB_LayerListEquip.h"
#include "MB_LayerListEquipChange.h"
#include "MB_LayerItemEnhance.h"
#include "MB_LayerListTreasure.h"
#include "MB_LayerListItemSale.h"
#include "MB_LayerListItemEnhance.h"
#include "MB_LayerItemList.h"
#include "MB_LayerBackpack.h"
#include "MB_LayerItemUpdate.h"
#include "MB_LayerItemDetail.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define NormalStarColor  ccc3(0xff,0xff,0x00)
#define SpecialStarColor ccc3(0xff,0,0)

MB_NodeItemUnit::MB_NodeItemUnit()
{
    m_pNodeChange= NULL;
    m_pNodeNormal1= NULL;
    m_pNodeSale= NULL;
    m_pNodeChoose = NULL;
    m_pNodeOpenOne = NULL;
    m_pNodeUse = NULL;
    m_pNodeIcon= NULL;
    m_bShowTutoral = false;
    for (int i = 0 ; i < MAX_ITEM_ATTR; i++) {
        
        m_pSpriteType[i] = NULL;
        m_pTTFType[i]= NULL;
    }
    
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        m_pStars[i] = NULL;
    }
    m_pSpriteIsChecked= NULL;
    m_pNodeChoose2  = NULL;
    m_pToLeft1 = NULL;
    m_pSpriteIsChecked2 = NULL;
    
    
    m_pLabelName= NULL;
    m_pLabelBeEquip = NULL;
    //m_pTTFCoin = NULL;
    m_pTTFDescription = NULL;
    m_pTTFDescriptionBg = NULL;
    m_pTTFOverTime = NULL;
    
    m_pBtEquipUp= NULL;
    m_pExp = NULL;
    m_pLastTimes = NULL;
    m_uOverTime = 0;
    m_pBtnOpenMore = NULL;
    m_pNodeOpenMore = NULL;
    SOCKET_MSG_REGIST(SC_ITEM_USE, MB_NodeItemUnit);
}

MB_NodeItemUnit::~MB_NodeItemUnit()
{
    CC_SAFE_RELEASE_NULL(m_pAnimationMgr);
    CC_SAFE_RELEASE_NULL(m_pNodeChange);
    CC_SAFE_RELEASE_NULL(m_pNodeNormal1);
    CC_SAFE_RELEASE_NULL(m_pNodeSale);
    CC_SAFE_RELEASE_NULL(m_pNodeChoose);
    CC_SAFE_RELEASE_NULL(m_pNodeOpenOne);
    CC_SAFE_RELEASE_NULL(m_pNodeUse);
    
    CC_SAFE_RELEASE_NULL(m_pNodeIcon);
    for (int i = 0 ; i < MAX_ITEM_ATTR; i++) {
        
        CC_SAFE_RELEASE_NULL(m_pSpriteType[i]);
        CC_SAFE_RELEASE_NULL(m_pTTFType[i]);
    }
    for (int i = 0; i < MAX_ITEM_STAR; i++) {
        CC_SAFE_RELEASE(m_pStars[i]);
    }
    CC_SAFE_RELEASE_NULL(m_pSpriteIsChecked);
    CC_SAFE_RELEASE_NULL(m_pLabelName);
    CC_SAFE_RELEASE_NULL(m_pLabelBeEquip);
    // CC_SAFE_RELEASE_NULL(m_pTTFCoin);
    CC_SAFE_RELEASE_NULL(m_pTTFDescription);
    CC_SAFE_RELEASE_NULL(m_pTTFDescriptionBg);
    CC_SAFE_RELEASE_NULL(m_pTTFOverTime);
    CC_SAFE_RELEASE(m_pExp);
    CC_SAFE_RELEASE(m_pLastTimes);
    CC_SAFE_RELEASE_NULL(m_pBtEquipUp);
    CC_SAFE_RELEASE(m_pNodeChoose2);
    CC_SAFE_RELEASE(m_pToLeft1);
    
    CC_SAFE_RELEASE(m_pSpriteIsChecked2);
    CC_SAFE_RELEASE_NULL(m_pBtnOpenMore);
    CC_SAFE_RELEASE_NULL(m_pNodeOpenMore);
    
    SOCKET_MSG_UNREGIST(SC_ITEM_USE);
}

MB_NodeItemUnit* MB_NodeItemUnit::create(int type, uint64_t itemUID,bool bShowTutorial)
{
    MB_NodeItemUnit* layer = new MB_NodeItemUnit();
    layer->m_bShowTutoral = bShowTutorial;
    if (layer != NULL && layer->init(type, itemUID)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

CCSize MB_NodeItemUnit::m_cellSizeItem = CCSizeZero;

CCSize MB_NodeItemUnit::getUnitSize()
{
    if(m_cellSizeItem.width == 0 || m_cellSizeItem.height == 0)MB_NodeItemUnit::create();
    
    return m_cellSizeItem;
}

bool MB_NodeItemUnit::init(int type, uint64_t itemUID)
{
    if ( !CCLayer::init() )return false;
    
    setSubType(type);
    setItemUID(itemUID);
    
    //init CCBReader
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //读取界面
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_unitopen.ccbi", this);
    m_pAnimationMgr = pCCBReader->getAnimationManager();
    m_pAnimationMgr->retain();
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    if(type == 0 && itemUID == 0)return true;
    
    onResetWnd();
    
    return true;
}

void MB_NodeItemUnit::onResetWnd()
{
    int i = 0;
    m_pNodeChange->setVisible(false);
    m_pNodeNormal1->setVisible(false);
    m_pNodeSale->setVisible(false);
    m_pNodeOpenOne->setVisible(false);
    m_pNodeOpenMore->setVisible(false);
    m_pNodeUse->setVisible(false);
    m_pNodeChoose2->setVisible(false);
    for (i = 0; i < MAX_ITEM_STAR; i++) {
        m_pStars[i]->setVisible(false);
    }
    for (int i = 0 ; i < MAX_ITEM_ATTR; i++) {
        
        m_pSpriteType[i] ->setVisible(false);
        m_pTTFType[i] ->setVisible(false);
    }
    m_pLabelBeEquip->setVisible(false);
    m_pSpriteIsChecked->setVisible(false);
    m_pSpriteIsChecked2->setVisible(false);
    m_pTTFDescription->setVisible(false);
    m_pTTFDescriptionBg->setVisible(false);
    m_pTTFOverTime->setVisible(false);
    
    if (m_kSubType == kListItemTypeEquip)
    {
        m_pNodeNormal1->setVisible(true);
    }
    else if (m_kSubType == kListItemTypeTreasure)
    {
        m_pNodeNormal1->setVisible(true);
    }
    else if (m_kSubType == kListItemTypeTreasureUp)
    {
        m_pNodeChange->setVisible(true);
    }
    else if (m_kSubType == kListItemTypeEquipSale || m_kSubType == kListItemTypeTreasureSale)
    {
        m_pNodeSale->setVisible(true);
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
        if (itemData->getReadyForSell())
        {
            m_pSpriteIsChecked->setVisible(true);
        }
        //        char* temp = new char[32];
        //        sprintf(temp, "%d", MB_ItemMgr::getInstance()->getItemCostByUID(itemData->getItemUID()));
        //        m_pTTFCoin->setString(temp);
        //        CC_SAFE_DELETE_ARRAY(temp);
    }
    else if (m_kSubType == kListItemTypeWeaponUp
             || m_kSubType == kListItemTypeDefenceUp
             || m_kSubType == kListItemTypeHorseUp)
    {
        m_pNodeChange->setVisible(true);
    }
    else if (m_kSubType == kListItemTypeItemEnhance)
    {
        m_pNodeChoose->setVisible(true);
        
    }else if(m_kSubType ==    kListItemTypeLevelUp){
        m_pNodeChoose2->setVisible(true);
    }
    else if(m_kSubType == kListItemTypeOther)
    {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
        MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
        //宝箱则显示打开按钮
        if (itemTemplete->getItemType() == kOTHER_BOX)
        {
            
            if(itemData->getItemNumber() > 1)
            {
                m_pNodeOpenMore->setVisible(true);
                char str[32] = {};
                sprintf(str,"%d",itemData->getItemNumber()>10? 10:itemData->getItemNumber());
                NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtnOpenMore, "fonts/kaicifont.fnt");
                NSGameHelper::setControlButtonTitleAllState(m_pBtnOpenMore, str);
            }
            else
            {
                m_pNodeOpenOne->setVisible(true);
            }
            
        }
        //体力道具
        if(itemTemplete->getItemType() == ENERGY_RECOVERY)
        {
            
            int lastTimes = MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(itemTemplete->getItemID());
            char str[20];
            if (lastTimes >= 0) {
                sprintf(str, "剩余次数:%d",lastTimes);
            }
            m_pLastTimes->setString(str);
            m_pNodeUse->setVisible(true);
        }
        
    }
    else if(m_kSubType == kListItemTypeChange)
    {
        m_pNodeNormal1->setVisible(true);
    }
    initNormal();
}


bool MB_NodeItemUnit::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    if(m_bShowTutoral)
    {
        if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
            return true;
        }
    }
    
    if (strcmp(pMemberVariableName, "cellSize") == 0 && pTarget == this) {
        m_cellSizeItem = pNode->getContentSize();
        return true;
    }
    
    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0)
    {
        CCMenu* menu = dynamic_cast<CCMenu*>(pNode);
        if (menu != NULL) {
            menu->setSwallowsTouches(false);
        }
        return true;
    }
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Exp", CCLabelTTF *, m_pExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LastTimes", CCLabelTTF *, m_pLastTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", CCLabelTTF*, m_pLabelName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "beEquip", CCLabelTTF*, m_pLabelBeEquip);
    char eff[] = "EffetType1";
    char effdes[]="EffetType1Des";
    for (int i = 0 ; i < MAX_ITEM_ATTR; i++) {
        
        eff[9] = '1' + i;
        effdes[9] = '1'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  eff, CCSprite*, m_pSpriteType[i]);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, effdes, CCLabelTTF*, m_pTTFType[i]);
    }
    char* starName = new char[8];
    for (int i = 0; i < MAX_ITEM_STAR; i++)
    {
        sprintf(starName, "star%d", i+1);
        if (pTarget == this && strcmp(pMemberVariableName, starName) == 0) {
            m_pStars[i] = (CCSprite*)pNode;
            m_pStars[i]->retain();
            CC_SAFE_DELETE_ARRAY(starName);
            return true;
        }
    }
    CC_SAFE_DELETE_ARRAY(starName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "choose2", CCNode*,  m_pNodeChoose2);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pToLeft1", CCNode*,  m_pToLeft1);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "change", CCNode*, m_pNodeChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "normal1", CCNode*, m_pNodeNormal1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sale", CCNode*, m_pNodeSale);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "choose", CCNode*, m_pNodeChoose);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PositionSign", CCNode*, m_pNodeIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "isChecked", CCSprite*, m_pSpriteIsChecked);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "isTreChecked", CCSprite*, m_pSpriteIsChecked2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pBtnOpenMore", CCControlButton*, m_pBtnOpenMore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Description", CCLabelTTF*, m_pTTFDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFDescriptionBg", CCNode*, m_pTTFDescriptionBg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "OverTime", CCLabelTTF*, m_pTTFOverTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "openone", CCNode*, m_pNodeOpenOne);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "use", CCNode*, m_pNodeUse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "openmore", CCNode*, m_pNodeOpenMore);
    
    if(strcasecmp("equip_attribute_board", pMemberVariableName) == 0 && pTarget == this)
    {
        bool bVisible = getSubType() == kListItemTypeItemEnhance;
        bVisible |= getSubType() == kListItemTypeEquip;
        bVisible |= getSubType() == kListItemTypeDefenceUp;
        bVisible |= getSubType() == kListItemTypeTreasureUp;
        bVisible |= getSubType() == kListItemTypeHorseUp;
        bVisible |= getSubType() == kListItemTypeChange;
        bVisible |= getSubType() == kListItemTypeWeaponUp;
        
        pNode->setVisible(bVisible);
    }
    return true;
}




SEL_MenuHandler MB_NodeItemUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDetailClicked", MB_NodeItemUnit::onDetailClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEnhanceClicked", MB_NodeItemUnit::onEnhanceClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEnhance2Clicked", MB_NodeItemUnit::onEnhance2Clicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLevelUpClicked", MB_NodeItemUnit::onLevelUpClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSaleClicked", MB_NodeItemUnit::onSaleClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChangeClicked", MB_NodeItemUnit::onChangeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseClicked", MB_NodeItemUnit::onChooseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOpenClicked", MB_NodeItemUnit::onOpenClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUseClicked", MB_NodeItemUnit::onUseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTreChooseClicked", MB_NodeItemUnit::onTreChooseClicked);
    
    return NULL;
}
SEL_CCControlHandler MB_NodeItemUnit::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOpenMoreClicked", MB_NodeItemUnit::onOpenMoreClicked);
    return NULL;
}

void MB_NodeItemUnit::onDetailClicked(cocos2d::CCObject *pSender)
{
    
    MB_ResWindow* layer = MB_LayerItemDetail::create(m_uItemUID);
    MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
    if (pScene)
    {
        pScene->addChild(layer,Z_ORDER_Detail);
    }else{
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, Z_ORDER_OUTSHOW);
    }
    
}

void MB_NodeItemUnit::onLevelUpClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onLevelUpClicked");
    TutorialTriggerComplete
    MB_TARGET_PARENT(MB_LayerListEquip, targetLayer);
    if (targetLayer != NULL)
    {
        MB_LayerItemUpdate* layer = MB_LayerItemUpdate::create(m_uItemUID);
        targetLayer->pushWindow(layer, true);
        return;
    }
    
    MB_TARGET_PARENT2(MB_LayerListEquipChange, targetLayer2);
    if (targetLayer2 != NULL) {
        MB_LayerItemUpdate* layer = MB_LayerItemUpdate::create(m_uItemUID);
        targetLayer2->pushWindow(layer, true);
        return;
    }
    
    MB_TARGET_PARENT2(MB_LayerBackpack, targetLayer3);
    if (targetLayer3 != NULL) {
        MB_LayerItemUpdate* layer = MB_LayerItemUpdate::create(m_uItemUID);
        targetLayer3->pushWindow(layer, true);
        return;
    }
}

void MB_NodeItemUnit::onEnhanceClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onEnhanceClicked");
    MB_TARGET_PARENT(MB_LayerListEquip, targetLayer);
    if (targetLayer != NULL)
    {
        MB_LayerItemEnhance* layer = MB_LayerItemEnhance::create(m_uItemUID);
        targetLayer->pushWindow(layer, true);
        return;
    }
    
    MB_TARGET_PARENT2(MB_LayerListEquipChange, targetLayer2);
    if (targetLayer2 != NULL) {
        MB_LayerItemEnhance* layer = MB_LayerItemEnhance::create(m_uItemUID);
        targetLayer2->pushWindow(layer, true);
        return;
    }
    
    MB_TARGET_PARENT2(MB_LayerBackpack, targetLayer3);
    if (targetLayer3 != NULL) {
        MB_LayerItemEnhance* layer = MB_LayerItemEnhance::create(m_uItemUID);
        targetLayer3->pushWindow(layer, true);
        return;
    }
}

void MB_NodeItemUnit::onEnhance2Clicked(cocos2d::CCObject *pSender)
{
    
}
void MB_NodeItemUnit::onTreChooseClicked(cocos2d::CCObject *pSender){
    CCNode *node;
    for (node = this->getParent() ; dynamic_cast<MB_NodeUpdatePetList *>(node) == NULL; node = node->getParent()) {
        
    }
    
    MB_TARGET_PARENT(MB_NodeUpdatePetList, ptr)
    if (ptr == NULL)
    {
        return;
    }
    
    
    
    CCArray* array = ptr->getSoldList();
    MB_ItemData* data = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    if (data == NULL)
    {
        return;
    }
    if (m_pSpriteIsChecked2->isVisible())
    {
        m_pSpriteIsChecked2->setVisible(false);
        array->removeObject(data);
    }
    else
    {
        if (array->count() >=8 ) {
            
            MB_Message::sharedMB_Message()->showMessage("只能选择8个材料");
            return;
        }
        m_pSpriteIsChecked2->setVisible(true);
        array->addObject(data);
    }
}
void MB_NodeItemUnit::onSaleClicked(cocos2d::CCObject *pSender)
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    
    MB_LOG("onSaleClicked");
    
    itemData->setReadyForSell(!itemData->getReadyForSell());
    m_pSpriteIsChecked->setVisible(itemData->getReadyForSell());
    MB_TARGET_PARENT(MB_LayerListItemSale, targetLayer);
    if (targetLayer != NULL) {
        
        targetLayer->refreshCount();
    }
}
void MB_NodeItemUnit::onInitSelect(bool select){
    
    m_pSpriteIsChecked2->setVisible(select);
    
}
void MB_NodeItemUnit::onChangeClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onChangeClicked");
    
    MB_TARGET_PARENT(MB_LayerListEquipChange, targetLayer);
    if (targetLayer != NULL)
    {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
        MB_ItemMgr::getInstance()->senditem_up_equip(targetLayer->getPetUID(), targetLayer->getItemPos(), m_uItemUID, itemData->getItemPetID());
        MB_Message::sharedMB_Message()->showMessage("", 15);
    }
    
}

void MB_NodeItemUnit::onChooseClicked(cocos2d::CCObject *pSender)
{
}

void MB_NodeItemUnit::onOpenClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onOpenClicked");
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    MB_ShopMgr::getInstance()->sendbox_item(itemData->getItemID());
}

void MB_NodeItemUnit::onOpenMoreClicked(cocos2d::CCObject *pSender)
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    MB_ShopMgr::getInstance()->sendbox_item(itemData->getItemID(),(itemData->getItemNumber()>10)? 10:itemData->getItemNumber());
}

void MB_NodeItemUnit::onUseClicked(cocos2d::CCObject *pSender)
{
    
    MB_LOG("onUseClicked");
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    if(!itemData)return;
    uint16_t tID = itemData->getItemID();
    
    
    //体力道具使用
    if(MB_ItemMgr::getInstance()->getUseItemType(tID) == Energy_ADD)
    {
        if(MB_RoleData::getInstance()->getEnergy() >= MB_RoleData::getInstance()->getEnergyMax())
        {
            //体力值已满，使用失败
            MB_Message::sharedMB_Message()->showMessage("体力值已满, 使用失败");
            return;
        }
        
        if(MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(itemData->getItemID()) <= 0)
        {
            //今日使用次数已达上限，请明日再使用
            MB_Message::sharedMB_Message()->showMessage("今日使用次数已达上限, 请明日再使用");
            return;
        }
    }
    //探索次数道具使用
    else if(MB_ItemMgr::getInstance()->getUseItemType(tID) == Discovery_ADD)
    {
        if(MB_RoleData::getInstance()->getDiscoveryTimes() >= MB_RoleData::getInstance()->getDiscoveryTimesMax())
        {
            //体力值已满，使用失败
            MB_Message::sharedMB_Message()->showMessage("冒险次数已满, 使用失败");
            return;
        }
        
        if(MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(itemData->getItemID()) <= 0)
        {
            //今日使用次数已达上限，请明日再使用
            MB_Message::sharedMB_Message()->showMessage("今日使用次数已达上限, 请明日再使用");
            return;
        }
    }
    //争霸道具使用
    else if(MB_ItemMgr::getInstance()->getUseItemType(tID) == PVP_ADD)
    {
        if(MB_RoleData::getInstance()->getPVPTimes() >= MB_RoleData::getInstance()->getPVPTimesMax())
        {
            //体力值已满，使用失败
            MB_Message::sharedMB_Message()->showMessage("竞技场战斗次数已满，使用失败");
            
            return;
        }
        
        if(MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(itemData->getItemID()) <= 0)
        {
            //今日使用次数已达上限，请明日再使用
            MB_Message::sharedMB_Message()->showMessage("今日使用次数已达上限, 请明日再使用");
            return;
        }
    }
    else
    {
        CCLog("ERROR MB_NodeItemUnit::onUseClicked");
        return;
    }
    MB_TARGET_PARENT(MB_LayerItemList, ptr);
    if (ptr)
    {
        ptr->onItemUsed(itemData);
    }
    
    MB_Message::sharedMB_Message()->showMessage(15);
    MB_ItemMgr::getInstance()->senditem_use(m_uItemUID,1);
    
    
}
void MB_NodeItemUnit::initNormal()
{
    int i = 0;
    char* temp = new char[128];
    
    //icon
    MB_NodeItem* nodeIcon = MB_NodeItem::create(m_uItemUID);
    nodeIcon->showNameCount(false);
    m_pNodeIcon->addChild(nodeIcon);
    //属性
    
    //    bool isTresure = false;
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
    //    if ((itemTemplete->getItemType() >= kTREASURE_PHYSICAL_DAMAGE_ADDTION && itemTemplete->getItemType() <= kTREASURE_REEL_REDUCE)
    //        || (itemTemplete->getItemType() >= kTREASURE_TIANQIAN && itemTemplete->getItemType() <= kTREASURE_ZEDUI))
    //    {
    //        isTresure = true;
    //    }
    //名字
    m_pLabelName->setString(MB_ItemMgr::getInstance()->realName(temp, m_uItemUID));
    //    CCNodeRGBA pDest;
    //    NSGameHelper::setQualityColor(&pDest,itemTemplete->getItemStar());
    //    m_pLabelName->setColor(pDest.getColor());
    
    sDesCommon* pItemCommon = NULL;
    int index = 0;
    if (itemTemplete->containsAtrribute(eItem_Attribute_Type_Attack)) {
        
        m_pSpriteType[index]->setVisible(true);
        pItemCommon = MB_ItemMgr::getInstance()->getItemAttributeCommon(eItem_Attribute_Type_Attack);
        if(pItemCommon){
            
            MB_ItemMgr::getInstance()->setSpriteFrame(m_pSpriteType[index], pItemCommon->queryValue("Icon").toString().c_str());
        }
        sprintf(temp, "%d", int(itemTemplete->getAtrribute(eItem_Attribute_Type_Attack, itemData)));
        m_pTTFType[index]->setString(temp);
        m_pTTFType[index]->setVisible(true);
        index ++;
    }
    if (itemTemplete->containsAtrribute(eItem_Attribute_Type_HP)) {
        m_pSpriteType[index]->setVisible(true);
        pItemCommon = MB_ItemMgr::getInstance()->getItemAttributeCommon(eItem_Attribute_Type_HP);
        if(pItemCommon)MB_ItemMgr::getInstance()->setSpriteFrame(m_pSpriteType[index], pItemCommon->queryValue("Icon").toString().c_str());
        
        sprintf(temp, "%d", int(itemTemplete->getAtrribute(eItem_Attribute_Type_HP, itemData)));
        m_pTTFType[index]->setString(temp);
        m_pTTFType[index]->setVisible(true);
        index ++;
    }
    //特殊属性
    attributeMap& attrMap = itemTemplete->getAtrributeMap();
    for (attributeMap_It iter = attrMap.begin(); iter != attrMap.end(); iter++)
    {
        eItem_Attribute_Type type = iter->first;
        if (type != eItem_Attribute_Type_Attack && type != eItem_Attribute_Type_HP) {
            
            m_pSpriteType[index]->setVisible(true);
            pItemCommon = MB_ItemMgr::getInstance()->getItemAttributeCommon(type);
            if(pItemCommon)MB_ItemMgr::getInstance()->setSpriteFrame(m_pSpriteType[index], pItemCommon->queryValue("Icon").toString().c_str());
            sprintf(temp, "%.0f",   itemTemplete->getAtrribute(type, itemData));
            
            if(type == eItem_Attribute_Type_Absorb || type == eItem_Attribute_Type_DamageBack){
                
                
                sprintf(temp,"%.2f%%",((*iter).second) /100.0f);
                
            }else {
                
                sprintf(temp, "%d",((*iter).second) );
            }
            m_pTTFType[index]->setString(temp);
            m_pTTFType[index]->setVisible(true);
            index ++;
            if(index >= MAX_ITEM_ATTR){
                
                break;
            }
        }
    }
    //星级
    int normalStar      = itemTemplete->getItemStar();
    for (i = 0; i < MAX_ITEM_STAR; i++) {
        if (i < normalStar) {
            m_pStars[i]->setVisible(true);
        }
        else
        {
            m_pStars[i]->setVisible(false);
        }
    }
    
    //是否已装备
    if (itemData->getItemPetID() != 0)
    {
        m_pLabelBeEquip->setVisible(true);
        char* name = new char[64];
        MB_PetMgr::getInstance()->getPetRealName(name, itemData->getItemPetID());
        sprintf(temp, "已被\"%s\"装备", name);
        CC_SAFE_DELETE_ARRAY(name);
        m_pLabelBeEquip->setString(temp);
        m_pAnimationMgr->runAnimationsForSequenceNamed("starequip");
    }
    
    //是否描述
    if (itemTemplete->getItemType() == kOTHER
        ||itemTemplete->getItemType() == kOTHER_BOX
        ||itemTemplete->getItemType() == ENERGY_RECOVERY
        ||itemTemplete->getItemType() == kEXPCARD) {
        m_pTTFDescription->setVisible(true);
        m_pTTFDescriptionBg->setVisible(true);
        m_pNodeIcon->setPosition(ccp(-233.7f-4,0.9f));
        m_pToLeft1->setPosition(ccp(-164.2f-10,31.9f));
        m_pLabelName->setPosition(ccp(-153.3f-10,48.1f));
        m_pTTFDescription->setString(itemTemplete->getItemDesc());
    }
    
    //    //是否衰减
    //    if ( isTresure
    //        && itemData->getItemRank() > 11
    //        && itemData->getItemRankOverTim() > 0 )
    //    {
    //        m_pTTFOverTime->setVisible(true);
    //        m_uOverTime = itemData->getItemRankOverTim();
    //        this->schedule(schedule_selector(MB_NodeItemUnit::tickTime));
    //    }
    //    if ( isTresure ){
    //
    //        if(itemData != NULL && itemData->getItemRank() <(MAX_TREASURE_QUALITY-1)){
    //
    //            m_pExp->setVisible(true);
    //            uint16_t  pre = MB_ItemMgr::getInstance()->getExpByRank(itemData->getItemRank() -1, itemTemplete->getItemStar());
    //            uint16_t  next = MB_ItemMgr::getInstance()->getExpByRank(itemData->getItemRank(), itemTemplete->getItemStar());
    //            char databuf[40];
    //            sprintf(databuf, "经验：%u/%u",itemData->getExp()-pre,next-pre);
    //            m_pExp->setString(databuf);
    //
    //        }else {
    //
    //            m_pExp->setVisible(true);
    //            char databuf[40];
    //            sprintf(databuf, "经验：--/--");
    //            m_pExp->setString(databuf);
    //        }
    //    }
    
    CC_SAFE_DELETE_ARRAY(temp);
}

void MB_NodeItemUnit::tickTime()
{
    //是否衰减
    int timerest = m_uOverTime - MB_ClientSocket::getInstance()->getServerTime();
    if (timerest < 0) {
        timerest = 0;
        m_pTTFOverTime->setString("品阶衰减剩余时间:00:00:00");
    }
    else
    {
        int hour = timerest/3600;
        timerest -= hour * 3600;
        int min = timerest/60;
        timerest -= min * 60;
        char* temp = new char[128];
        sprintf(temp, "品阶衰减剩余时间:%02d:%02d:%02d", hour, min, timerest);
        m_pTTFOverTime->setString(temp);
        CC_SAFE_DELETE_ARRAY(temp);
    }
}

void MB_NodeItemUnit::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //将socket数据读取到序列化结构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议号
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
        case SC_ITEM_USE:
            recvitem_use(recvPacket);
        default:
            break;
    }
    
}

bool MB_NodeItemUnit::recvitem_use(MB_MsgBuffer* recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    //    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    //    if(itemData)
    //    {
    //        onResetWnd();
    //    }
    return true;
}


void MB_NodeItemUnit::setShowSelect(bool bShow)
{
    m_pSpriteIsChecked2->setVisible(bShow);
}
