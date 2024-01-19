

#include "MB_LayerItemEnhance.h"
#include "MB_LayerRoleInfoHeader.h"
#include "MB_RoleSoundSystem.h"
#include "MB_ScrollBg.h"
#include "MB_NodeItemUnitJingLian.h"
#include "MB_LayerItemDetail.h"
#include "MB_LayerBackpack.h"
#define ENHANCECELLNUM 6
USING_NS_CC;
USING_NS_CC_EXT;
MB_LayerItemEnhance::MB_LayerItemEnhance()
{
    if (global_layerBackpack!=NULL) {
        global_layerBackpack->isResetWnd = false;
    }
    isSetCost = false;
    isUpdateUI = false;
    m_pIujl = NULL;
    m_pArrayCanChoose = new CCArray();
    m_pTableView = NULL;
    m_uItemUID = 0;
    m_uItemUIDCost = 0;
    m_pTableContainer = NULL;
    m_pItemName1 = NULL;
    m_pTextRank_Title = NULL;
    m_pTextDetailA1_Title = NULL;
    m_pTextDetailA2_Title = NULL;
    m_pCard = NULL;
    m_pTextRank1 = NULL;
    m_pTextDetailA1 = NULL;
    m_pTextDetailA2 = NULL;
    m_pTextRank2 = NULL;
    m_pTextDetailB1 = NULL;
    m_pTextDetailB2 = NULL;
    m_pJianTouA = NULL;
    m_pJianTouB = NULL;
    m_pCostIcon = NULL;
    m_pTextCostName = NULL;
    m_pTextCostCoin = NULL;
    m_pButtonCommit = NULL;
    
    m_pCCBAnimationMgr = NULL;
    m_pTTFMaxRank = NULL;
    m_pNodeCost1 = NULL;
    m_pNodeCost2 = NULL;
    m_bShowRoleInfoPanel = true;
    lastShowRoleInfoPanel = MB_LayerRoleInfoHeader::showRoleInfoHeader(getShowRoleInfoPanel());
    m_pNodeEquip[0] = NULL;
    m_pNodeEquip[1] = NULL;
    m_pNodeEquip[2] = NULL;
    m_pNodeEquip[3] = NULL;
    m_pNodeEquip[4] = NULL;
    m_pNodeEquip[5] = NULL;
    m_pDataStruct = NULL;
    m_pOwerLabel = NULL;
    
    
    SOCKET_MSG_REGIST(SC_ITEM_UP_RANK, MB_LayerItemEnhance);
}

MB_LayerItemEnhance::~MB_LayerItemEnhance()
{
    if (global_layerBackpack!=NULL) {
        global_layerBackpack->isResetWnd = true;
    }
    if (global_layerItemDetail) {
        global_layerItemDetail->setVisible(true);
    }
    SOCKET_MSG_UNREGIST(SC_ITEM_UP_RANK);
    CC_SAFE_RELEASE_NULL(m_pJianTouA);
    CC_SAFE_RELEASE_NULL(m_pJianTouB);
    CC_SAFE_RELEASE_NULL(m_pArrayCanChoose);
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pTextRank_Title);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA1_Title);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA2_Title);
    CC_SAFE_RELEASE_NULL(m_pCard);
    CC_SAFE_RELEASE_NULL(m_pItemName1);
    CC_SAFE_RELEASE_NULL(m_pTextRank1);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA1);
    CC_SAFE_RELEASE_NULL(m_pTextDetailA2);
    CC_SAFE_RELEASE_NULL(m_pTextRank2);
    CC_SAFE_RELEASE_NULL(m_pTextDetailB1);
    CC_SAFE_RELEASE_NULL(m_pTextDetailB2);
    CC_SAFE_RELEASE_NULL(m_pCostIcon);
    CC_SAFE_RELEASE_NULL(m_pTextCostName);
    CC_SAFE_RELEASE_NULL(m_pTextCostCoin);
    CC_SAFE_RELEASE_NULL(m_pButtonCommit);
    CC_SAFE_RELEASE_NULL(m_pOwerLabel);
    CC_SAFE_RELEASE(m_pCCBAnimationMgr);
    CC_SAFE_RELEASE(m_pTTFMaxRank);
    CC_SAFE_RELEASE(m_pNodeCost1);
    CC_SAFE_RELEASE(m_pNodeCost2);
    
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[0]);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[1]);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[2]);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[3]);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[4]);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip[5]);
}

MB_LayerItemEnhance* MB_LayerItemEnhance::create(uint64_t itemUID)
{
    MB_LayerItemEnhance* layer = new MB_LayerItemEnhance();
    if (layer && layer->init(itemUID)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

bool MB_LayerItemEnhance::init(uint64_t itemUID)
{
	if ( !CCLayer::init() )return false;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode *pScene = pCCBReader->readNodeGraphFromFile("res/item_layer_rank.ccbi", this);
    this->addChild(NSGameHelper::createDisableTouchLayer());
    this->addChild(pScene);
    m_pCCBAnimationMgr = pCCBReader->getAnimationManager();
    CC_SAFE_RETAIN(m_pCCBAnimationMgr);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    m_szCell =MB_NodeItemUnitJingLian::getUnitSize();
    m_szCell = CCSize(m_szCell.width*ENHANCECELLNUM,m_szCell.height) ;
    
    resetItemUID(itemUID);
    
    CCTableView* tableView = CCTableView::create(this, m_pTableContainer->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableContainer->addChild(tableView);
    m_pTableView = tableView;
    m_pTableView->reloadData();
    addChild(MB_ScrollBg::create(right_bottom,.5f,2),-1);
	return true;
}

void MB_LayerItemEnhance::resetItemUID(uint64_t itemUID)
{
    if (m_uItemUID == itemUID)return;
    
    m_uItemUID = itemUID;
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    if(itemData)
    {
        m_pDataStruct = MB_TeamData::getInstance()->getTeamMemberByUID(itemData->getItemPetID());
        initEquips();
    }
    else
        m_pDataStruct = NULL;
    
    m_uItemUIDCost = 0;
    
    m_pArrayCanChoose->removeAllObjects();
    MB_ItemData* itemData2 = MB_ItemMgr::getInstance()->getItemDataByUID(itemUID);
    int nStar = (MB_ItemMgr::getInstance()->getItemTemplateByID(itemData2->getItemID()))->getItemStar();
    uint8_t type = itemData2->getItemType();
    for (int i = 0; i < MB_ItemMgr::getInstance()->getItemDataArray()->count(); i++)
    {
        itemData = (MB_ItemData*)MB_ItemMgr::getInstance()->getItemDataArray()->objectAtIndex(i);
        int nStar2 = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID())->getItemStar();
        //不是同类道具||是主道具 || 已经装备了 || 星级不同
        if (type != itemData->getItemType() || itemData->getItemUID() == itemUID || itemData->getItemPetID() != 0 || nStar != nStar2)
        {
            continue;
        }
        m_pArrayCanChoose->addObject(itemData);
    }
    //排序
    if(m_pArrayCanChoose->count() > 1)
    {
        sortData();
    }
    if (m_pTableView!=NULL) {
        isSetCost = false;
        m_pTableView->reloadData();
    }
    dirty();
}

void MB_LayerItemEnhance::resetCostItemUID(MB_NodeItemUnitJingLian* iujl,uint64_t itemUID)
{
    if (m_uItemUID == itemUID) {
        return;
    }
    if (m_pIujl!=NULL) {
        m_pIujl->m_pSelectSpr->setVisible(false);
    }
    m_pIujl = iujl;
    m_uItemUIDCost = itemUID;

    dirty();
}

void MB_LayerItemEnhance::initEquips()
{
    CCArray* pArr = CCArray::create();
    
    if(m_pDataStruct)
    {
        if(m_pDataStruct->m_pEquip1)pArr->addObject(m_pDataStruct->m_pEquip1);
        if(m_pDataStruct->m_pEquip2)pArr->addObject(m_pDataStruct->m_pEquip2);
        if(m_pDataStruct->m_pEquip3)pArr->addObject(m_pDataStruct->m_pEquip3);
        if(m_pDataStruct->m_pTreasure1)pArr->addObject(m_pDataStruct->m_pTreasure1);
        if(m_pDataStruct->m_pTreasure2)pArr->addObject(m_pDataStruct->m_pTreasure2);
        if(m_pDataStruct->m_pTreasure3)pArr->addObject(m_pDataStruct->m_pTreasure3);
    }
    else
    {
        pArr->addObject(MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID));
    }
    
    for (int i = 0; i<6; ++i)
    {
        m_pNodeEquip[i]->removeAllChildren();
        if(i < pArr->count())
        {
            MB_ItemData* pMB_ItemData = dynamic_cast<MB_ItemData*>(pArr->objectAtIndex(i));
            MB_NodeItem* pNode = MB_NodeItem::create(pMB_ItemData->getItemUID());
            pNode->setDelegate(this);
            m_pNodeEquip[i]->addChild(pNode);
            pNode->setSelected(m_uItemUID == pMB_ItemData->getItemUID());
            pNode->showNameCount(false);
        }
        else
        {
            MB_NodeItem* pNode = MB_NodeItem::create((uint64_t)0);
            m_pNodeEquip[i]->addChild(pNode);
            pNode->showNameCount(false);
            pNode->showNameStar(false);
            pNode->setOnClickEnable(false);
            
        }
    }
}

void MB_LayerItemEnhance::onClicked(MB_NodeItem* pNodeItem)
{
    m_pButtonCommit->setEnabled(true);
    resetItemUID(pNodeItem->getItemId());
}

void MB_LayerItemEnhance::onResetWnd()
{
    m_pTTFMaxRank->setVisible(false);
    m_pNodeCost1->setVisible(true);
    m_pNodeCost2->setVisible(true);
    
    if (m_uItemUID == 0)
    {
        m_pItemName1->setString("");
        m_pItemName1->setVisible(false);
        m_pTextRank1->setString("");
        m_pTextDetailA1->setString("");
        m_pTextDetailA2->setString("");
        m_pTextRank2->setString("");
        m_pTextDetailB1->setString("");
        m_pTextDetailB2->setString("");
        m_pCostIcon->removeAllChildren();
        m_pCostIcon->setVisible(false);
        m_pTextCostName->setString("");
        m_pTextCostCoin->setString("");
        m_pButtonCommit->setEnabled(false);
        m_pNodeCost1->setVisible(true);
        m_pNodeCost2->setVisible(true);
        m_pOwerLabel->setString("");
    }
    else
    {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
        
        if (itemData == NULL)
        {
            MB_LOG("itemUID:%llu not exist.", m_uItemUID);
            //不存在的时候就当没有设置重新刷一遍
            m_uItemUID = 0;
            dirty();
            return;
        }
        else
        {
            //不是装备不能升品
            if (itemData->getItemType() == kWEAPON              //兵器
                || itemData->getItemType() == kARMOR            //战甲
                || itemData->getItemType() == kITEM_WING        //翅膀
                || itemData->getItemType() == kITEM_HEADWEAR    //头饰
                || itemData->getItemType() == kITEM_TOTEM       //图腾
                || itemData->getItemType() == kITEM_RUNESTONE)  //符石
            {
            }
            else
            {
                MB_LOG("not a equip itemid:%d", itemData->getItemID());
                return;
            }
        }
        
        MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
        
        //显示卡片
        m_pCard->removeAllChildren();
        MB_NodeItem* pNodeItem = MB_NodeItem::create(itemData->getItemUID());
        pNodeItem->showNameCount(false);
        m_pCard->addChild(pNodeItem);
        m_pCard->setVisible(true);
        
        if(m_pDataStruct)
        {
            char temp[128] = {0};
            char* name = new char[64];
            MB_PetMgr::getInstance()->getPetRealName(name, m_pDataStruct->m_pPet->getPetID());
            sprintf(temp, "已被\"%s\"装备", name);
            CC_SAFE_DELETE_ARRAY(name);
            m_pOwerLabel->setString(temp);
        }
        else
        {
            m_pOwerLabel->setString("未被装备");
        }
        
        //查找材料道具
        MB_ItemData* costMB_ItemData = NULL;
        if (0 !=  m_uItemUIDCost)
        {
            costMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUIDCost);
        }
        
        MB_ItemTemplate* costMB_ItemTemplate = NULL;
        char* strInfo1 = new char[128];
        char* strInfo2 = new char[128];
        
        m_pButtonCommit->setVisible(true);
        
        if (itemData->getItemRank() == MAX_EQUIP_QUALITY)
        {
            int Quality = MAX_EQUIP_QUALITY;
            int NextQuality = MAX_EQUIP_QUALITY;
            
            //显示名称
            char* str = new char[32];
            MB_ItemMgr::getInstance()->realName(str, itemData->getItemUID());
            m_pItemName1->setString(str);
            m_pItemName1->setVisible(true);
            
            CC_SAFE_DELETE_ARRAY(str);
            

            m_pTTFMaxRank->setVisible(true);
            m_pButtonCommit->setVisible(false);
            m_pNodeCost1->setVisible(false);
            m_pNodeCost2->setVisible(false);
            
            sprintf(strInfo1, "%d", Quality);
            sprintf(strInfo2, "%d", NextQuality);
            m_pTextRank1->setString(strInfo1);
            m_pTextRank2->setString(strInfo2);
            
            attributeMap& attributes = itemTemplete->getAtrributeMap();
            attributeMap_It it = attributes.begin();
            float attrValue = 0.0f;
            std::string attrStr;
            //最多处理三个属性
            if (it != attributes.end()) {
                m_pJianTouA->setVisible(true);
                m_pTextDetailA1_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                m_pTextDetailA1->setString(attrStr.c_str());
                m_pTextDetailA1->setVisible(true);
                m_pTextDetailB1->setString(attrStr.c_str());
                m_pTextDetailB1->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA1_Title->setString(attrStr.c_str());
                it++;
            }
            else
            {
                m_pJianTouA->setVisible(false);
                m_pTextDetailA1_Title->setVisible(false);
                m_pTextDetailA1->setVisible(false);
                m_pTextDetailB1->setVisible(false);
            }
            
            if (it != attributes.end()) {
                m_pJianTouB->setVisible(true);
                m_pTextDetailA2_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                m_pTextDetailA2->setString(attrStr.c_str());
                m_pTextDetailA2->setVisible(true);
                m_pTextDetailB2->setString(attrStr.c_str());
                m_pTextDetailB2->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA2_Title->setString(attrStr.c_str());
                
                it++;
            }
            else
            {
                m_pJianTouB->setVisible(false);
                m_pTextDetailA2_Title->setVisible(false);
                m_pTextDetailA2->setVisible(false);
                m_pTextDetailB2->setVisible(false);
            }
        }
        else if (costMB_ItemData != NULL)
        {
            int Quality = itemData->getItemRank();
            int NextQuality = itemData->getItemRank()+costMB_ItemData->getItemRank()+1;
            if (Quality >= 10)
            {
                Quality = NextQuality = 10;
            }
            if (NextQuality >= 10)
            {
                NextQuality = 10;
            }
            //显示名称
            char* str = new char[32];
            MB_ItemMgr::getInstance()->realName(str, itemData->getItemUID());
            m_pItemName1->setString(str);
            m_pItemName1->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str);
            //是否遮罩
            m_uItemUIDCost = costMB_ItemData->getItemUID();
            costMB_ItemTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(costMB_ItemData->getItemID());
            
            m_pCostIcon->removeAllChildren();
            MB_NodeItem* itemIcon = MB_NodeItem::create(costMB_ItemData->getItemUID());
            itemIcon->showNameCount(false);
            m_pCostIcon->addChild(itemIcon);
            m_pCostIcon->setVisible(true);
            
            char* str1 = new char[32];
            MB_ItemMgr::getInstance()->realName(str1, costMB_ItemData->getItemUID());
            m_pTextCostName->setString(str1);
            CC_SAFE_DELETE_ARRAY(str1);
            
            uint64_t coin1 = 0,coin2 = 0,coin3 = 0;
            bool ok1 = false, ok2 = false, ok3 = false;
            CCArray* costArray = MB_ItemMgr::getInstance()->getItemQualityCostArray();
            
            int16_t level2 = (itemData->getItemLevel() > costMB_ItemData->getItemLevel()) ? itemData->getItemLevel():costMB_ItemData->getItemLevel();
            if (level2 > MB_RoleData::getInstance()->getLevel()) {
                level2 = MB_RoleData::getInstance()->getLevel();
            }
            sprintf(strInfo1, "%d", Quality);
            m_pTextRank1->setString(strInfo1);
            sprintf(strInfo2, "%d", NextQuality);
            m_pTextRank2->setString(strInfo2);
            
            attributeMap& attributes = itemTemplete->getAtrributeMap();
            attributeMap_It it = attributes.begin();
            float attrValue = 0.0f;
            std::string attrStr, attrStr2;
            //最多处理三个属性
            if (it != attributes.end()) {
                m_pJianTouA->setVisible(true);
                m_pTextDetailA1_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                //升品后属性
                attrValue = itemTemplete->getAtrribute(it->first, level2, NextQuality);
                attrStr2 = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                
                m_pTextDetailA1->setString(attrStr.c_str());
                m_pTextDetailA1->setVisible(true);
                m_pTextDetailB1->setString(attrStr2.c_str());
                m_pTextDetailB1->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA1_Title->setString(attrStr.c_str());
                it++;
            }
            else
            {
                m_pJianTouA->setVisible(false);
                m_pTextDetailA1_Title->setVisible(false);
                m_pTextDetailA1->setVisible(false);
                m_pTextDetailB1->setVisible(false);
            }
            
            if (it != attributes.end()) {
                m_pJianTouB->setVisible(true);
                m_pTextDetailA2_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                //升品后属性
                attrValue = itemTemplete->getAtrribute(it->first, level2, NextQuality);
                attrStr2 = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                
                
                m_pTextDetailA2->setString(attrStr.c_str());
                m_pTextDetailA2->setVisible(true);
                m_pTextDetailB2->setString(attrStr2.c_str());
                m_pTextDetailB2->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA2_Title->setString(attrStr.c_str());
                it++;
            }
            else
            {
                m_pJianTouB->setVisible(false);
                m_pTextDetailA2_Title->setVisible(false);
                m_pTextDetailA2->setVisible(false);
                m_pTextDetailB2->setVisible(false);
            }
            
            
            for (int i = 0; i < costArray->count(); ++i)
            {
                MB_ItemQualityCostTemplete* costTemplete = (MB_ItemQualityCostTemplete*)costArray->objectAtIndex(i);
                if (!ok1) {
                    if (costTemplete->getQuality() == itemData->getItemRank() && costTemplete->getStar() == itemTemplete->getItemStar()) {
                        ok1 = true;
                        coin1 = costTemplete->getCoin();
                    }
                }
                if (!ok2) {
                    if (costTemplete->getQuality() == costMB_ItemData->getItemRank() && costTemplete->getStar() == costMB_ItemTemplate->getItemStar()) {
                        ok2 = true;
                        coin2 = costTemplete->getCoin();
                    }
                }
                if (!ok3) {
                    if (costTemplete->getQuality() == NextQuality && costTemplete->getStar() == itemTemplete->getItemStar()) {
                        ok3 = true;
                        coin3 = costTemplete->getCoin();
                    }
                }
                if (ok1 && ok2 && ok3) {
                    if (coin1 + coin2 > coin3)
                    {
                        coin3 = 0;
                    }
                    else
                    {
                        coin3 = coin3 - coin2 - coin1;
                    }
                    
                    break;
                }
            }
            
            if (MB_RoleData::getInstance()->getCoin() < coin3)
            {
                m_pTextCostCoin->setColor(ccRED);
            }
            else
            {
                m_pTextCostCoin->setColor(ccWHITE);
            }
            
            m_pTextCostName->setColor(ccWHITE);
            NSGameHelper::LabelFormatNumber(m_pTextCostCoin, coin3,true,"");
        }
        else
        {
            int Quality = itemData->getItemRank();
            int NextQuality = itemData->getItemRank()+1;
            if (Quality >= 10)
            {
                Quality = NextQuality = 10;
            }
            if (NextQuality >= 10)
            {
                NextQuality = 10;
            }
            //显示名称
            char* str = new char[32];
            MB_ItemMgr::getInstance()->realName(str, itemData->getItemUID());
            m_pItemName1->setString(str);
            m_pItemName1->setVisible(true);
            CC_SAFE_DELETE_ARRAY(str);
            

            m_uItemUIDCost = 0;
            costMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
            costMB_ItemTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
            
            m_pCostIcon->removeAllChildren();
            
            char* str1 = new char[32];
//            MB_ItemMgr::getInstance()->realNameByTypeID(str1, costMB_ItemTemplate->getItemID());
            
            sprintf(str1,"%d星同类型装备不足",itemTemplete->getItemStar());
            m_pTextCostName->setColor(ccRED);
            m_pTextCostName->setString(str1);
            CC_SAFE_DELETE_ARRAY(str1);
            
            uint64_t coin1 = 0,coin3 = 0;
            bool ok1 = false, ok3 = false;
            CCArray* costArray = MB_ItemMgr::getInstance()->getItemQualityCostArray();
            
            
            sprintf(strInfo1, "%d", Quality);
            sprintf(strInfo2, "%d", NextQuality);
            m_pTextRank1->setString(strInfo1);
            m_pTextRank2->setString(strInfo2);
            
            attributeMap& attributes = itemTemplete->getAtrributeMap();
            attributeMap_It it = attributes.begin();
            float attrValue = 0.0f;
            std::string attrStr, attrStr2;
            //最多处理三个属性
            if (it != attributes.end()) {
                m_pJianTouA->setVisible(true);
                m_pTextDetailA1_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                //升品后属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData->getItemLevel(),NextQuality);
                attrStr2 = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                
                m_pTextDetailA1->setString(attrStr.c_str());
                m_pTextDetailA1->setVisible(true);
                m_pTextDetailB1->setString(attrStr2.c_str());
                m_pTextDetailB1->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA1_Title->setString(attrStr.c_str());
                it++;
            }
            else
            {
                m_pJianTouA->setVisible(false);
                m_pTextDetailA1_Title->setVisible(false);
                m_pTextDetailA1->setVisible(false);
                m_pTextDetailB1->setVisible(false);
            }
            
            if (it != attributes.end()) {
                m_pJianTouB->setVisible(true);
                m_pTextDetailA2_Title->setVisible(true);
                //当前道具属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData);
                attrStr = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                //升品后属性
                attrValue = itemTemplete->getAtrribute(it->first, itemData->getItemLevel(), NextQuality);
                attrStr2 = MB_ItemMgr::getInstance()->attrConvertToDesValue(it->first, attrValue);
                
                m_pTextDetailA2->setString(attrStr.c_str());
                m_pTextDetailA2->setVisible(true);
                m_pTextDetailB2->setString(attrStr2.c_str());
                m_pTextDetailB2->setVisible(true);
                
                attrStr = MB_ItemMgr::getInstance()->attrConvertToTitle(it->first);
                m_pTextDetailA2_Title->setString(attrStr.c_str());
                it++;
            }
            else
            {
                m_pJianTouB->setVisible(false);
                m_pTextDetailA2_Title->setVisible(false);
                m_pTextDetailA2->setVisible(false);
                m_pTextDetailB2->setVisible(false);
            }
            
            for (int i = 0; i < costArray->count(); ++i)
            {
                MB_ItemQualityCostTemplete* costTemplete = (MB_ItemQualityCostTemplete*)costArray->objectAtIndex(i);
                if (!ok1) {
                    if (costTemplete->getQuality() == itemData->getItemRank() && costTemplete->getStar() == itemTemplete->getItemStar()) {
                        ok1 = true;
                        coin1 = costTemplete->getCoin();
                    }
                }
                if (!ok3) {
                    if (costTemplete->getQuality() == NextQuality && costTemplete->getStar() == itemTemplete->getItemStar()) {
                        ok3 = true;
                        coin3 = costTemplete->getCoin();
                    }
                }
                if (ok1 && ok3) {
                    coin3 = coin3 - coin1;
                    break;
                }
            }
            sprintf(strInfo1, "%llu",coin3);
            if (MB_RoleData::getInstance()->getCoin() < coin3)
            {
                m_pTextCostCoin->setColor(ccRED);
            }
            else
            {
                m_pTextCostCoin->setColor(ccWHITE);
            }
            m_pTextCostCoin->setString(strInfo1);
        }
        
        CC_SAFE_DELETE_ARRAY(strInfo1);
        CC_SAFE_DELETE_ARRAY(strInfo2);
    }
}

void MB_LayerItemEnhance::sortData()
{
    MB_ItemData *MB_ItemData1,*MB_ItemData2;
    int nDataCount = m_pArrayCanChoose->count();
    //品阶升序
    for(int i = 0;i < nDataCount;++i)
    {
        for (int j = i+1; j < nDataCount; ++j)
        {
            MB_ItemData1 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
            MB_ItemData2 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(j);
            
            if (MB_ItemData1->getItemRank() > MB_ItemData2->getItemRank())
            {
                m_pArrayCanChoose->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
    
    //同品阶  等级升序
    for(int i = 0;i < nDataCount;++i)
    {
        for (int j = i+1; j < nDataCount; ++j)
        {
            MB_ItemData1 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
            MB_ItemData2 = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(j);
            
            if (MB_ItemData1->getItemRank() != MB_ItemData2->getItemRank())
            {
                break;
            }
            if (MB_ItemData1->getItemLevel() > MB_ItemData2->getItemLevel())
            {
                m_pArrayCanChoose->exchangeObjectAtIndex(i,j);
            }
            
        }
    }
}
bool MB_LayerItemEnhance::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCard", CCNode*, m_pCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pItemName1", CCLabelTTF*, m_pItemName1);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextRank1", CCLabelBMFont*, m_pTextRank1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA1", CCLabelBMFont*, m_pTextDetailA1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA2", CCLabelBMFont*, m_pTextDetailA2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextRank2", CCLabelBMFont*, m_pTextRank2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailB1", CCLabelBMFont*, m_pTextDetailB1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailB2", CCLabelBMFont*, m_pTextDetailB2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pCostIcon", CCNode*, m_pCostIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextCostName", CCLabelTTF*, m_pTextCostName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextCostCoin", CCLabelBMFont*, m_pTextCostCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pButtonCommit", CCControlButton*, m_pButtonCommit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTTFMaxRank", CCLabelTTF*, m_pTTFMaxRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCost1", CCNode*, m_pNodeCost1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCost2", CCNode*, m_pNodeCost2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip1", CCNode*, m_pNodeEquip[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip2", CCNode*, m_pNodeEquip[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip3", CCNode*, m_pNodeEquip[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip4", CCNode*, m_pNodeEquip[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip5", CCNode*, m_pNodeEquip[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip6", CCNode*, m_pNodeEquip[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pOwerLabel", CCLabelTTF*, m_pOwerLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextRank_Title", CCLabelTTF*, m_pTextRank_Title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA1_Title", CCLabelTTF*, m_pTextDetailA1_Title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTextDetailA2_Title", CCLabelTTF*, m_pTextDetailA2_Title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTableContainer", CCNode*, m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJianTouA", CCNode*, m_pJianTouA);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pJianTouB", CCNode*, m_pJianTouB);
    return true;
}

SEL_MenuHandler MB_LayerItemEnhance::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerItemEnhance::onCloseClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerItemEnhance::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCommitClicked", MB_LayerItemEnhance::onCommitClicked);
    return NULL;
}

void MB_LayerItemEnhance::onCloseClicked(cocos2d::CCObject *pSender)
{
    if (isUpdateUI) {
        if (global_layerItemDetail!=NULL) {
            global_layerItemDetail->onReSet();
        }
    }
    removeFromParent();
    MB_LayerRoleInfoHeader::showRoleInfoHeader(lastShowRoleInfoPanel);
}

void MB_LayerItemEnhance::onCommitClicked(cocos2d::CCObject *pSender)
{
    MB_ItemData* costMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUIDCost);
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
    
    //允许精炼判断
    if ( (itemTemplete->getItemType() <= kHORSE && itemData->getItemRank() >= MAX_EQUIP_QUALITY)
        || (itemTemplete->getItemType() > kHORSE && itemTemplete->getItemType() <= kTREASURE_REEL_REDUCE && itemData->getItemRank() >= MAX_TREASURE_QUALITY))
    {
        MB_Message::sharedMB_Message()->showMessage("已经达到最大品阶.");
        return;
    }
    else if (costMB_ItemData == NULL)
    {
        MB_Message::sharedMB_Message()->showMessage("精炼需要吞噬一张相同星级, 相同部位的装备卡.");
        return;
    }
    else if (m_pTextCostCoin->getColor().r == ccRED.r
             && m_pTextCostCoin->getColor().g == ccRED.g
             && m_pTextCostCoin->getColor().b == ccRED.b)
    {
        MB_Message::sharedMB_Message()->showMessage("精炼需要消耗的金币不足.");
        return;
    }
    
    
    if (costMB_ItemData->getItemLevel() > 1) {
        MB_Message::sharedMB_Message()->showMessage("消耗提示", "消耗的材料等级大于1级, 您是否需要继续?", "继续", "取消", this, menu_selector(MB_LayerItemEnhance::onCommit), menu_selector(MB_LayerItemEnhance::onCancel));
    }
    else if (costMB_ItemData->getItemRank() > 0) {
        MB_Message::sharedMB_Message()->showMessage("消耗提示", "消耗的材料品阶大于0级, 您是否需要继续?", "继续", "取消", this, menu_selector(MB_LayerItemEnhance::onCommit), menu_selector(MB_LayerItemEnhance::onCancel));
    }
    else if (costMB_ItemData->getItemPetID() != 0) {
        char* name = new char[20];
        char* message = new char[100];
        MB_PetMgr::getInstance()->getPetRealName(name, costMB_ItemData->getItemPetID());
        sprintf(message, "消耗的材料已经被%s装备, 您是否需要继续?", name);
        MB_Message::sharedMB_Message()->showMessage("消耗提示", message, "继续", "取消", this, menu_selector(MB_LayerItemEnhance::onCommit), menu_selector(MB_LayerItemEnhance::onCancel));
        CC_SAFE_DELETE_ARRAY(name);
        CC_SAFE_DELETE_ARRAY(message);
    }
    else
    {
        onCommit(this);
    }
}


void MB_LayerItemEnhance::onMsgRecv(CCNode* node, SocketResponse* response)
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
            
        case SC_ITEM_UP_RANK:
            recvitem_up_rank(recvPacket);
            break;
            
        default:
            break;
    }
    
}

bool MB_LayerItemEnhance::recvitem_up_rank(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1)
    {
        isUpdateUI = true;
        int nDataCount = m_pArrayCanChoose->count();
        //品阶升序
        for(int i = 0;i < nDataCount;++i)
        {
            MB_ItemData* item = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
            if (item->getItemUID() == m_uItemUIDCost) {
                m_pArrayCanChoose->removeObjectAtIndex(i);
                break;
            }
        }
        m_uItemUIDCost = 0;
        dirty();
        MB_Message::sharedMB_Message()->removeALLMessage();
        m_pCCBAnimationMgr->runAnimationsForSequenceNamed("rankup");
        MB_Audio::getInstance()->playEffect(GET_BACKGROUND(ksSound_Equip_Rank_Up).c_str());
        isSetCost = false;
        m_pTableView->reloadData();
    }
    return true;
}

void MB_LayerItemEnhance::onCommit(cocos2d::CCObject *pSender)
{
    MB_Message::sharedMB_Message()->showMessage("",5.0f);
    uint64_t srcPetID = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID)->getItemPetID();
    uint64_t foodPetID = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUIDCost)->getItemPetID();
    MB_ItemMgr::getInstance()->senditem_up_rank(m_uItemUID, m_uItemUIDCost, srcPetID, foodPetID);
}

void MB_LayerItemEnhance::onCancel(cocos2d::CCObject *pSender)
{
    MB_LOG("canceled.");
}

MB_ItemData* MB_LayerItemEnhance::getCostItem()
{
    if (m_pArrayCanChoose->count()==0)
    {
        return NULL;
    }
    return (MB_ItemData*)(m_pArrayCanChoose->objectAtIndex(0));
}


CCSize MB_LayerItemEnhance::cellSizeForTable(CCTableView *table)
{
    return m_szCell;
}

CCTableViewCell* MB_LayerItemEnhance::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    CCLayer* layer = CCLayer::create();
    layer->setContentSize(m_szCell);
    
    int index = idx;
    for (int i = index*ENHANCECELLNUM;i < (index+1)*ENHANCECELLNUM && i < m_pArrayCanChoose->count();i++)
    {
        MB_ItemData* itemData = (MB_ItemData*)m_pArrayCanChoose->objectAtIndex(i);
        MB_NodeItemUnitJingLian* pNode = MB_NodeItemUnitJingLian::create(this,itemData->getItemUID());
        layer->addChild(pNode);
        if (m_uItemUIDCost==itemData->getItemUID()) {
            pNode->onChooseClicked(NULL);
        }
        else if(!isSetCost && i==0)
        {
            isSetCost = true;
            pNode->onChooseClicked(NULL);
        }
        pNode->setPosition(ccp(m_szCell.width/ENHANCECELLNUM*(0.5 + i%ENHANCECELLNUM) + 21, m_szCell.height/2));
    }
    cell->addChild(layer);
    return cell;
}

unsigned int MB_LayerItemEnhance::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrayCanChoose->count()/ENHANCECELLNUM + ((m_pArrayCanChoose->count()%ENHANCECELLNUM) == 0? 0:1);
}
