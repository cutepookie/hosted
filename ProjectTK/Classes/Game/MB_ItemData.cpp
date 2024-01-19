//
//  MB_MB_ItemData.cpp
//  ProjectTK
//
//
//  Description: 道具的模板和數据

#include "MB_ItemData.h"
#include "Game.h"
#include <math.h>
#include <algorithm>
#include "MB_LayerItemDetail.h"
#define value_ratio 1.0f

//Item模板 实现

MB_ItemTemplate::MB_ItemTemplate()
{
    m_iItemID        = 0;
    m_iItemType      = 0;
    m_bItemStack     = false;
    m_iItemCost      = 0;
    m_iItemStar      = 0;
    m_iItemRankMax   = 0;
    m_iComposeItemID = 0;
    m_iComposeNum    = 0;
    m_nComposeCommonMaxNum = 0;
    m_nSuitID = 0;
}

MB_ItemTemplate::~MB_ItemTemplate()
{
}

//kWEAPON = 1,                                    //兵器
//kARMOR = 2,										//戰甲
//kHORSE = 3,										//坐骑
//kTREASURE_PHYSICAL_DAMAGE_ADDTION = 4,			//破甲寶物
//kTREASURE_PHYSICAL_DAMAGE_REDUCTION = 5,        //護甲寶物
//kTREASURE_MAGIC_DAMAGE_ADDTION = 6,             //法穿寶物
//kTREASURE_MAGIC_DAMAGE_REDUCTION = 7,			//法抗寶物
//kTREASURE_CRITIC = 8,							//暴擊寶物
//kTREASURE_CRITIC_REDUCE = 9,					//韧性寶物
//kTREASURE_DOOM = 10,							//命中寶物
//
//kDEBRIS_WEAPON = 11,							//武器碎片
//kDEBRIS_HEADWEAR= 12,							//头盔碎片
//kDEBRIS_ARMOR= 13,                              //護甲碎片
//kDEBRIS_WINGS = 14,                             //幸运物碎片
//kDEBRIS_TOTEM = 15,                             //项链碎片
//kDEBRIS_RUNESTONE = 16,							//戒指碎片
//
//kTREASURE_REEL_REDUCE = 17,						//抗擊晕寶物
//kMATERRIAL = 18,								//材料
//kOTHER = 19,                                    //其他
//KMATERRIAL_PATCH_GENERAL = 20,                  //將魂（精靈碎片）
//KMATERRIAL_PATCH_WEAPON = 21,                   //武器碎片
//KMATERRIAL_PATCH_ARMOR  = 22,                   //防具碎片
//KMATERRIAL_PATCH_HORSE  = 23,                   //坐骑碎片
//kOTHER_BOX = 24,                                //寶箱
//kTREASURE_TIANQIAN = 25,                        //天谴
//kTREASURE_DIKUN = 26,                           //地锟
//kTREASURE_LEIZHEN = 27,                         //雷震
//kTREASURE_FENGXUN = 28,                         //风讯
//kTREASURE_SHUIKAN = 29,                         //水堪
//kTREASURE_HUOLI = 30,                           //huoli
//kTREASURE_SHANGENG = 31,                        //shangeng
//kTREASURE_ZEDUI = 32,                           //zedui
//kITEM_WING = 33,                                //翅膀
//kITEM_HEADWEAR = 34,                            //头饰
//kITEM_TOTEM = 35,                               //图腾
//kITEM_RUNESTONE = 36,                           //符石
//kITEM_FORMULA = 37,                              //配方
//ENERGY_RECOVERY = 38,                            //体力恢複道具

bool MB_ItemTemplate::getIsEquip()
{
    return m_iItemType == kWEAPON || m_iItemType == kARMOR || m_iItemType == kHORSE ||
    m_iItemType == kITEM_RUNESTONE ||
    //    m_iItemType == kDEBRIS_WEAPON || m_iItemType == kDEBRIS_HEADWEAR || m_iItemType == kDEBRIS_ARMOR ||
    //    m_iItemType == kDEBRIS_WINGS || m_iItemType == kDEBRIS_TOTEM || m_iItemType == kDEBRIS_RUNESTONE ||
    m_iItemType == kITEM_WING || m_iItemType == kITEM_HEADWEAR || m_iItemType == kITEM_TOTEM;
}

bool MB_ItemTemplate::getIsDebris()
{
    return m_iItemType == kDEBRIS_WEAPON || m_iItemType == kDEBRIS_HEADWEAR || m_iItemType == kDEBRIS_ARMOR ||
    m_iItemType == kDEBRIS_WINGS || m_iItemType == kDEBRIS_TOTEM || m_iItemType == kDEBRIS_RUNESTONE;
}

attributeMap& MB_ItemTemplate::getAtrributeMap()
{
    return m_attributeMap;
}

void MB_ItemTemplate::setAttribute(eItem_Attribute_Type type,int32_t value)
{
    if(containsAtrribute(type))
    {m_attributeMap[type] = value;}
    else{m_attributeMap.insert(std::make_pair(type,value));}
}


float MB_ItemTemplate::getAtrribute(eItem_Attribute_Type type,MB_ItemData* entity/*= NULL*/)
{
    float ret;
    ret = containsAtrribute(type)?m_attributeMap[type]:0.0f;
    ret = calculateAttribute(type, entity, ret);
    return ret;
}

float MB_ItemTemplate::getAtrribute(eItem_Attribute_Type type, uint8_t itemLevel, uint8_t itemRank)
{
    float ret;
    ret = containsAtrribute(type)?m_attributeMap[type]:0.0f;
    ret = calculateAttribute(type, itemLevel, itemRank, ret);
    return ret;
}

float MB_ItemTemplate::calculateAttribute(eItem_Attribute_Type type,MB_ItemData* entity ,float templateValue)
{
    switch (type)
    {
        case eItem_Attribute_Type_PDAdd:
        case eItem_Attribute_Type_PDRed:
        case eItem_Attribute_Type_MDAdd:
        case eItem_Attribute_Type_MDRed:
        case eItem_Attribute_Type_Critic:
        case eItem_Attribute_Type_CriticRed:
        case eItem_Attribute_Type_Doom:
        case eItem_Attribute_Type_Miss:
        case eItem_Attribute_Type_SPInit:
        case eItem_Attribute_Type_SPLeft:
        case eItem_Attribute_Type_Reel:
        case eItem_Attribute_Type_ReelRed:
            break;
        case eItem_Attribute_Type_Attack:
        case eItem_Attribute_Type_HP:
            if(entity)
            {
                templateValue = \
                templateValue * \
                (1+(entity->getItemLevel()-1) * 0.1)* \
                ( pow(4,( entity->getItemRank()*0.1 )));
            }
            break;
        case eItem_Attribute_Type_Absorb:
        case eItem_Attribute_Type_DamageBack:
            templateValue /= value_ratio;
            break;
        default:
            break;
    }
    return templateValue;
}

float MB_ItemTemplate::calculateAttribute(eItem_Attribute_Type type,uint8_t itemLevel, uint8_t itemRank,float templateValue)
{
    switch (type)
    {
        case eItem_Attribute_Type_PDAdd:
        case eItem_Attribute_Type_PDRed:
        case eItem_Attribute_Type_MDAdd:
        case eItem_Attribute_Type_MDRed:
        case eItem_Attribute_Type_Critic:
        case eItem_Attribute_Type_CriticRed:
        case eItem_Attribute_Type_Doom:
        case eItem_Attribute_Type_Miss:
        case eItem_Attribute_Type_SPInit:
        case eItem_Attribute_Type_SPLeft:
        case eItem_Attribute_Type_Reel:
        case eItem_Attribute_Type_ReelRed:
            break;
        case eItem_Attribute_Type_Attack:
        case eItem_Attribute_Type_HP:
            templateValue = templateValue * (1+(itemLevel-1) * 0.1)* ( pow(4,( itemRank*0.1 )));
            break;
        case eItem_Attribute_Type_Absorb:
        case eItem_Attribute_Type_DamageBack:
            templateValue /= value_ratio;
            break;
        default:
            break;
    }
    return templateValue;
}

bool MB_ItemTemplate::containsAtrribute(eItem_Attribute_Type type)
{
    attributeMap_It finder = m_attributeMap.find(type);
    return finder != m_attributeMap.end();
}

//MB_ItemData類 实现

MB_ItemData::MB_ItemData()
:m_uItemPetID(0)
,m_uItemPos(0)
,m_bReadyForSell(false)
,m_uItemType(0)
,m_uExp(0)
,m_uItemUID(0)
{
    
}

MB_ItemData::~MB_ItemData()
{
    
}

bool MB_ItemData::getUsed()
{
    return m_uItemPos != 0 || m_uItemPetID != 0;
}

int MB_ItemData::getTemplateStar()
{
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(getItemID());
    if (pTemplate)
    {
        return pTemplate->getItemStar();
    }
    return 0;
}
bool MB_ItemData::isSuitPart(int nSuitId)
{
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(getItemID());
    if (pTemplate==NULL)
    {
        return false;
    }

    return pTemplate->getSuitID() == nSuitId;
}

//登录獎勵
DailyReward::DailyReward()
{
    m_pValueArray = CCArray::create();
    m_pValueArray->retain();
}

DailyReward::~DailyReward()
{
    CC_SAFE_RELEASE(m_pValueArray);
}

MB_ItemQualityCostTemplete::MB_ItemQualityCostTemplete()
{
    m_nStar = 0;
    m_nQuality = 0;
    m_nCoin = 0;
}

MB_UseItemRule::MB_UseItemRule()
{
    m_utID = 0;
    m_uLastTime = 0;
    m_uType = 0;
}

MB_UseItemRule* MB_UseItemRule::create(uint16_t id,uint8_t times,uint8_t type)
{
    MB_UseItemRule* pInstance = new MB_UseItemRule(id,times,type);
    if (pInstance)
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return NULL;
}
MB_UseItemRule::MB_UseItemRule(uint16_t id,uint8_t times,uint8_t type)
{
    m_utID = id;
    m_uLastTime = times;
    m_uType = type;
}
RewardTemplete::RewardTemplete()
{
    m_pValueArray = new CCArray();
}

RewardTemplete::~RewardTemplete()
{
    CC_SAFE_RELEASE_NULL(m_pValueArray);
}

//Item管理類 实现

static MB_ItemMgr* s_pMB_ItemMgr = NULL;

MB_ItemMgr::MB_ItemMgr()
{
    m_enhanceItemUID = 0;
    m_sellTotalPrice = 0;
    m_vLoginRecord.clear();
    
    m_pItemDataArray = new CCArray();
    m_pEquipArray = new CCArray();
    m_pWeaponArray = new CCArray();
    m_pDefenceArray = new CCArray();
    m_pHorseArray = new CCArray();
    m_pTreasureArray = new CCArray();
    m_pMaterialArray = new CCArray();
    m_pBoxArray = new CCArray();
    m_pOtherArray = new CCArray();
    m_pEquipUnionArray = new CCArray();
    m_pPetUnionArray = new CCArray();
    m_pCanEquipTreaArray = new CCArray();
    m_pEatArray = new CCArray();
    m_pWingArray = new CCArray();
    m_pHeadwareArray = new CCArray();
    m_pRuneStoreArray = new CCArray();
    m_pTotermArray = new CCArray();
    m_pItemFormulaArray = new CCArray();
    m_pUseItemRuleArray = new CCArray();
    m_pItemDebrisArray = new CCArray();
    m_pExpCardArray = new CCArray();
    m_vecItemForSell       = new std::vector<uint64_t>;

    m_pItemQualityUpCost = new CCArray();
    m_pExpCardDataArray = new CCArray();
    if (!initItemTemplate())
    {
        MB_LOG("init MB_ItemTemplate failed.");
    }
    
    if (!initQualityCost()) {
        MB_LOG("init item qualityCost failed.");
    }
    
    
    
    initUseItemLastTimes();
    initExpCardData();
    
    m_pDailyRewardArray = new CCArray();
    m_pDailyRewardTemplete = new CCArray();
    m_pTitleRewardTemplete = new CCArray();
    if (!initDailyRewardTemplete()) {
        MB_LOG("initDailyRewardTemplete failed.");
    }
    
    
    if (!initTitleRewardTemplete()) {
        MB_LOG("initTitleRewardTemplete failed.");
    }
    SOCKET_MSG_REGIST(SC_ITEM_BAG,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_EQUIP,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_NEW,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_UPDATE,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_UP_EQUIP,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_DOWN_EQUIP,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_SELL,MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_USE, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_DAILY_GET_LIST, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_DAILY_DRAW, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_DELETE_NOTIFY, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_REINFORCE, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_MAX_REINFORCE, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_UPDATE_RANK, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_UP_RANK, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_COMPOUND, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_EAT, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ROLE_LOGIN_REWARD, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_USE_INFO, MB_ItemMgr);
    SOCKET_MSG_REGIST(SC_ITEM_MORE, MB_ItemMgr);
}

MB_ItemMgr::~MB_ItemMgr()
{
    CC_SAFE_RELEASE_NULL(m_pItemDataArray);
    CC_SAFE_RELEASE_NULL(m_pEquipArray);
    CC_SAFE_RELEASE_NULL(m_pWeaponArray);
    CC_SAFE_RELEASE_NULL(m_pDefenceArray);
    CC_SAFE_RELEASE_NULL(m_pHorseArray);
    CC_SAFE_RELEASE_NULL(m_pTreasureArray);
    CC_SAFE_RELEASE_NULL(m_pMaterialArray);
    CC_SAFE_RELEASE_NULL(m_pBoxArray);
    CC_SAFE_RELEASE_NULL(m_pOtherArray);
    CC_SAFE_RELEASE_NULL(m_pEquipUnionArray);
    CC_SAFE_RELEASE_NULL(m_pPetUnionArray);
    CC_SAFE_RELEASE_NULL(m_pCanEquipTreaArray);
    CC_SAFE_RELEASE_NULL(m_pEatArray);
    CC_SAFE_RELEASE_NULL(m_pWingArray);
    CC_SAFE_RELEASE_NULL(m_pHeadwareArray);
    CC_SAFE_RELEASE_NULL(m_pRuneStoreArray);
    CC_SAFE_RELEASE_NULL(m_pTotermArray);
    CC_SAFE_RELEASE_NULL(m_pItemFormulaArray);
    CC_SAFE_RELEASE_NULL(m_pExpCardArray);
    CC_SAFE_DELETE(m_vecItemForSell);
    CC_SAFE_RELEASE_NULL(m_pDailyRewardArray);
    CC_SAFE_RELEASE_NULL(m_pItemQualityUpCost);
    CC_SAFE_RELEASE(m_pDailyRewardTemplete);
//    CC_SAFE_RELEASE(m_pLevelRewardTemplete);
    CC_SAFE_RELEASE(m_pTitleRewardTemplete);
    CC_SAFE_RELEASE(m_pUseItemRuleArray);
    CC_SAFE_RELEASE_NULL(m_pItemDebrisArray);
    CC_SAFE_RELEASE_NULL(m_pExpCardDataArray);
    SOCKET_MSG_UNREGIST(SC_ITEM_BAG);
    SOCKET_MSG_UNREGIST(SC_ITEM_EQUIP);
    SOCKET_MSG_UNREGIST(SC_ITEM_NEW);
    SOCKET_MSG_UNREGIST(SC_ITEM_UPDATE);
    SOCKET_MSG_UNREGIST(SC_ITEM_UP_EQUIP);
    SOCKET_MSG_UNREGIST(SC_ITEM_DOWN_EQUIP);
    SOCKET_MSG_UNREGIST(SC_ITEM_SELL);
    SOCKET_MSG_UNREGIST(SC_ITEM_USE);
    SOCKET_MSG_UNREGIST(SC_DAILY_GET_LIST);
    SOCKET_MSG_UNREGIST(SC_DAILY_DRAW);
    SOCKET_MSG_UNREGIST(SC_ITEM_DELETE_NOTIFY);
    SOCKET_MSG_UNREGIST(SC_ITEM_REINFORCE);
    SOCKET_MSG_UNREGIST(SC_ITEM_MAX_REINFORCE);
    SOCKET_MSG_UNREGIST(SC_ITEM_UPDATE_RANK);
    SOCKET_MSG_UNREGIST(SC_ITEM_UP_RANK);
    SOCKET_MSG_UNREGIST(SC_ITEM_COMPOUND);
    SOCKET_MSG_UNREGIST(SC_ITEM_EAT);    
    SOCKET_MSG_UNREGIST(SC_ROLE_LOGIN_REWARD);
    SOCKET_MSG_UNREGIST(SC_ITEM_USE_INFO);
    SOCKET_MSG_UNREGIST(SC_ITEM_MORE);
    
    MB_ItemTemplateMap::iterator itr = m_mapItemTemplate.begin();
    MB_ItemTemplateMap::iterator end  = m_mapItemTemplate.end();
    while (itr != end) {
        
        CC_SAFE_RELEASE(itr->second);
        itr++;
    }
       m_vLoginRecord.clear();
}

MB_ItemMgr* MB_ItemMgr::getInstance()
{
    if (s_pMB_ItemMgr == NULL) {
        s_pMB_ItemMgr = new MB_ItemMgr();
    }
    
    return s_pMB_ItemMgr;
}

void MB_ItemMgr::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pMB_ItemMgr);
    s_pMB_ItemMgr = NULL;
}

sDesCommon* MB_ItemMgr::getItemAttributeCommon(uint16_t/*eItem_Attribute_Type*/ type)
{
    return MB_DescriptionCommonTable::getInstance().getDesCommon("item_property.xml",type);
}

sDesCommon* MB_ItemMgr::getItemTypeCommon(uint16_t/*ItemType*/ type)
{
    return MB_DescriptionCommonTable::getInstance().getDesCommon("itemtype.xml",type);
}

uint32_t MB_ItemMgr::getEnhanceItemCostByUID(uint64_t uid)
{
    unsigned int ret = 0;
    float   ratioA,ratioB,ratioC;
    MB_ItemData*               pItemEntity;
    MB_ItemTemplate*           pItemTemplate = NULL;
    
    pItemEntity = getItemDataByUID(uid);
    
    if(pItemEntity)
        pItemTemplate = getItemTemplateByID(pItemEntity->getItemID());
    
    if(pItemEntity&&pItemTemplate)
    {
        sDesCommon* pdc;
        
        pdc = MB_DescriptionCommonTable::getInstance(). \
              getDesCommon("strengthen_cost.xml",pItemEntity->getItemLevel());
        
        ratioA = pdc?pdc->queryValue("exp").toInt():0;
        
        pdc = MB_DescriptionCommonTable::getInstance(). \
              getDesCommon("itemtype.xml",pItemTemplate->getItemType());
        
        ratioB = pdc?pdc->queryValue("EnhanceCostRatio").toInt()/100.0f:0;
        
        pdc = MB_DescriptionCommonTable::getInstance(). \
              getDesCommon("item_strengthen_rate.xml",pItemTemplate->getItemStar());
        ratioC = pdc?pdc->queryValue("EnhanceCostRatio").toInt()/100.0f:0;
        
        ret = ratioC*ratioA*ratioB;
    }
    
    return ret;
}

uint32_t MB_ItemMgr::getItemCostByUID(uint64_t uid)
{
    unsigned int ret = 0;
    MB_ItemData*               pItemEntity;
    MB_ItemTemplate*           pItemTemplate = NULL;
    
    pItemEntity         = getItemDataByUID(uid);
    
    if(pItemEntity)
        pItemTemplate   = getItemTemplateByID(pItemEntity->getItemID());
    
    ret = pItemEntity&&pItemTemplate? \
    pItemTemplate->getItemCost() * (1 + (pItemEntity->getItemLevel() * 0.1f)) * (1 + (pItemEntity->getItemRank()*0.1f)) : 0;
    return ret;
}

float MB_ItemMgr::getAtrributeByUID (uint64_t uid,eItem_Attribute_Type type)
{
    float ret = 0;
    MB_ItemData*   pItemEntity;
    MB_ItemTemplate*   pItemTemplate = NULL;
    pItemEntity = getItemDataByUID(uid);
    if(pItemEntity)
        pItemTemplate   = getItemTemplateByID(pItemEntity->getItemID());
    if (pItemTemplate&&pItemEntity)
    {
       ret = pItemTemplate->getAtrribute(type,pItemEntity);
    }
    return ret;
}

void MB_ItemMgr::setItemLevel(uint64_t uid, uint16_t level)
{
    MB_ItemData* itemData;
    itemData = getItemDataByUID(uid);
    if(itemData)
        itemData->setItemLevel(level);
}

void MB_ItemMgr::plusItemLevel(uint64_t uid, uint16_t plusNum)
{
    MB_ItemData* itemData;
    itemData = getItemDataByUID(uid);
    if(itemData)
        itemData->setItemLevel(itemData->getItemLevel() + plusNum);
}

std::string MB_ItemMgr::getItemNameByUid(uint64_t uid)
{
    MB_ItemData* itemData;
    itemData = getItemDataByUID(uid);
    return getItemNameByTid(itemData?itemData->getItemID():0);
}

std::string MB_ItemMgr::getItemNameByTid(uint32_t tid)
{
    MB_ItemTemplate* pit;
    pit = getItemTemplateByID(tid);
    return pit?pit->getItemName():"";
}

bool MB_ItemMgr::canBeEnhancedByItemTid(uint32_t tid)
{
    bool ret = false;
    MB_ItemTemplate*   pItemTemplate = NULL;
    sDesCommon* pDc;

    pItemTemplate = getItemTemplateByID(tid);
    if(pItemTemplate)
    {
        pDc = MB_DescriptionCommonTable::getInstance(). \
              getDesCommon("itemtype.xml",
                           pItemTemplate->getItemType());
        ret = pDc->queryValue("Enhance").toBoolean();
    }
    return ret;
}

bool MB_ItemMgr::canBeEnhancedByItemUid(uint64_t uid)
{
    bool ret = false;
    MB_ItemData* itemData;
    itemData = getItemDataByUID(uid);
    if(itemData)
        ret = canBeEnhancedByItemTid(itemData->getItemID());
    return ret;
}

uint64_t MB_ItemMgr::getItemEntityUID(uint32_t itemID, uint32_t itemNum)
{
    uint64_t retUID = 0;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pItemDataArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemID() == itemID && \
             itemData->getItemNumber() >= itemNum)
            retUID = itemData->getItemUID();
    }
    return retUID;
}

unsigned int MB_ItemMgr::getItemEntityCount(uint32_t itemid)
{
    unsigned int ret = 0;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pItemDataArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemID() == itemid)
            ret+=itemData->getItemNumber();
    }
    return ret;
}
int  MB_ItemMgr::getCanComposPetNum(){

    int count = 0;
    CCObject *obj;
    CCArray *ptr = MB_ItemMgr::getInstance()->getPetUnionArray();
    CCARRAY_FOREACH(ptr, obj){
        
        MB_ItemData *data = (MB_ItemData *) obj;
        count += getCanComposPetNumByType(data);
      
    }
    return count;
}
int  MB_ItemMgr::getCanComposItemNum(){
    
    int count = 0;
    CCObject *obj;
    CCArray *ptr = MB_ItemMgr::getInstance()->getEquipUnionArray();
    CCARRAY_FOREACH(ptr, obj){
        
        MB_ItemData *data = (MB_ItemData *) obj;
        count += getCanComposItemNumByType(data);
    }
    return count;
}
int MB_ItemMgr::getCanComposPetNumByType(MB_ItemData *data){
    
    int count = 0;
    MB_ItemTemplate * item  =  MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    count += (data->getItemNumber()/item->getComposeNum());
    int left = data->getItemNumber() % item->getComposeNum();

    if(left >= (item->getComposeNum() - item->getComposeCommonMaxNum())){
        
        MB_PetTemplate * itemTo = MB_PetMgr::getInstance()->getPetTemplateByID(item->getComposeItemID());
        int compos = 0;
        switch (itemTo->getPetStar()) {
            case 3:
                compos = getItemEntityCount(COMPOS_GER3_ID);
                break;
            case 4:
                compos = getItemEntityCount(COMPOS_GER4_ID);
                break;
            case 5:
                compos = getItemEntityCount(COMPOS_GER5_ID);
                break;
            default:
                break;
        }
        if((left + compos) >= item->getComposeNum()){
      
            count += 1;
        }
    }
    return count;
}
int MB_ItemMgr::getCanComposItemNumByType(MB_ItemData *data){
    
    int count = 0;
    MB_ItemTemplate * item  =  MB_ItemMgr::getInstance()->getItemTemplateByID(data->getItemID());
    count += (data->getItemNumber()/item->getComposeNum());
    int left = data->getItemNumber() % item->getComposeNum();
    if(left >= (item->getComposeNum() - item->getComposeCommonMaxNum())){
        
         MB_ItemTemplate * itemTo  =  MB_ItemMgr::getInstance()->getItemTemplateByID(item->getComposeItemID());
        int compos = 0;
        switch (itemTo->getItemStar()) {
            case 3:
                compos = getItemEntityCount(COMPOS_ITEM3_ID);
                break;
            case 4:
                compos = getItemEntityCount(COMPOS_ITEM4_ID);
                break;
            case 5:
                compos = getItemEntityCount(COMPOS_ITEM5_ID);
                break;
            default:
                break;
        }
        if((left + compos) >= item->getComposeNum()){
            
            count += 1;
        }

    }

    return count;
}

const char * MB_ItemMgr::realName(char *buf, uint64_t UID){

    MB_ItemData * data = getItemDataByUID(UID);
    //容错处理
    if (data == NULL) {
        memset(buf, 0, sizeof(buf));
        return buf;
    }
    
    MB_ItemTemplate *tem = getItemTemplateByID(data->getItemID());
    //容错处理
    if (tem == NULL) {
        memset(buf, 0, sizeof(buf));
        return buf;
    }
    
    std::string addName = "";

    sprintf(buf, "%s%s",addName.c_str(),tem->getItemName());
    
    int qual =  data->getItemRank();
    
    if(qual!=0){
        
        if(qual == 10)
        {
            sprintf(buf, "[完美]%s",tem->getItemName());
        }
        else
        {
            sprintf(buf, "%s +%d",buf,qual);
        }
    }
        
    return buf;
}

const char* MB_ItemMgr::realNameByTypeID(char *buf, uint16_t typeID)
{
    MB_ItemTemplate *tem = getItemTemplateByID(typeID);
    //容错处理
    if (tem == NULL) {
        memset(buf, 0, sizeof(buf));
        return buf;
    }
    
    sprintf(buf, "%s",tem->getItemName());
    return buf;
}

bool MB_ItemMgr::isAttrValueDecimal(eItem_Attribute_Type type)
{
    bool ret = false;
    switch (type)
    {
        case eItem_Attribute_Type_PDAdd:
        case eItem_Attribute_Type_PDRed:
        case eItem_Attribute_Type_MDAdd:
        case eItem_Attribute_Type_MDRed:
        case eItem_Attribute_Type_Critic:
        case eItem_Attribute_Type_CriticRed:
        case eItem_Attribute_Type_Doom:
        case eItem_Attribute_Type_Miss:
        case eItem_Attribute_Type_SPInit:
        case eItem_Attribute_Type_SPLeft:
        case eItem_Attribute_Type_Reel:
        case eItem_Attribute_Type_ReelRed:
            break;
        case eItem_Attribute_Type_Attack:
            break;
        case eItem_Attribute_Type_HP:
            break;
        case eItem_Attribute_Type_Absorb:
        case eItem_Attribute_Type_DamageBack:
            ret = true;
            break;
        default:
            break;
    }
    return ret;
}

std::string MB_ItemMgr::attrConvertToDes(eItem_Attribute_Type type,float value)
{
    std::string         ret;
    char                temp[32];
    bool                positiveNum;
    float               fTempValue;
    bool                isdecimal;
    sDesCommon*         pIc;
    
    isdecimal       = isAttrValueDecimal(type);
    positiveNum     = value>=0.0f;
    fTempValue      = value;
    fTempValue      = positiveNum?fTempValue:-fTempValue;
    fTempValue     /= isdecimal?100.0f:1.0f;
    
    pIc = getItemAttributeCommon(type);
    
    sprintf(temp,
            "%s：%s%.0f%s",
            pIc?pIc->queryValue("Name").toString().c_str():"error",
            positiveNum?" ":"-",
            fTempValue,isdecimal?"%":" ");
    ret = temp;
    return ret;
}
std::string MB_ItemMgr::attrConvertToTitle(eItem_Attribute_Type type)
{
    std::string         ret;
    char                temp[32];
    sDesCommon*         pIc;
    pIc = getItemAttributeCommon(type);
    sprintf(temp,
            "%s",
            pIc?pIc->queryValue("Name").toString().c_str():"error");
    ret = temp;
    return ret;
}
std::string MB_ItemMgr::attrConvertToDesValue(eItem_Attribute_Type type,float value)
{
    std::string         ret;
    char                temp[32];
    bool                positiveNum;
    float               fTempValue;
    bool                isdecimal;
    sDesCommon*         pIc;
    
    isdecimal       = isAttrValueDecimal(type);
    positiveNum     = value>=0.0f;
    fTempValue      = value;
    fTempValue      = positiveNum?fTempValue:-fTempValue;
    fTempValue     /= isdecimal?100.0f:1.0f;
    
    pIc = getItemAttributeCommon(type);
    
    sprintf(temp,
            "%s%.0f%s",
            positiveNum?"":"-",
            fTempValue,isdecimal?"%":"");
    ret = temp;
    return ret;
}

int MB_ItemMgr::getItemQualityByUid(uint64_t uid)
{
    MB_ItemData*       pItemEntity;
    MB_ItemTemplate*   pItemTemplate;
    
    pItemEntity     = getItemDataByUID(uid);
    pItemTemplate   = getItemTemplateByID(pItemEntity?pItemEntity->getItemID():0);
    
    int quality;
    quality = pItemTemplate?pItemTemplate->getItemStar():0 + \
    pItemEntity?pItemEntity->getItemRank()/10:0;
    
    return quality;
}

int MB_ItemMgr::getItemQualityByTid(uint32_t tid)
{
    MB_ItemTemplate*   pItemTemplate;
    pItemTemplate   = getItemTemplateByID(tid);
    return pItemTemplate?pItemTemplate->getItemStar():0;
}


MB_ItemTemplateMap* MB_ItemMgr::getItemTemplateMap()
{
    return &m_mapItemTemplate;
}

MB_ItemTemplate* MB_ItemMgr::getItemTemplateByID(uint16_t itemID)
{
    MB_ItemTemplateMap::iterator itemTempleteIterator = m_mapItemTemplate.find(itemID);
    if ( itemTempleteIterator != m_mapItemTemplate.end()) {
        return itemTempleteIterator->second;
    }
    else
    {
//        MB_LOG("ID:%d item not exist.", itemID);
        return  NULL;
    }
}

MB_ItemData* MB_ItemMgr::getItemDataByUID(uint64_t itemUID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pItemDataArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemUID() == itemUID)
        {
            return itemData;
        }
    }
    MB_LOG("UID:%ld item instance not exist.", itemUID);
    return NULL;
    
}

MB_ItemData* MB_ItemMgr::getEquipByUID(uint64_t uID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pEquipArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemUID() == uID)
        {
            return itemData;
        }
    }
    MB_LOG("UID:%d equip instance not exist.", uID);
    return NULL;
    
}

MB_ItemData* MB_ItemMgr::getTreasureByUID(uint64_t uID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pTreasureArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemUID() == uID)
        {
            return itemData;
        }
    }
    MB_LOG("UID:%llu treasure instance not exist.", uID);
    return NULL;
    
}

MB_ItemData* MB_ItemMgr::getMaterialByUID(uint64_t uID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pItemDataArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemUID() == uID)
        {
            return itemData;
        }
    }
    MB_LOG("UID:%d Material instance not exist.", uID);
    return NULL;
}

void MB_ItemMgr::setSpriteFrame(cocos2d::CCSprite *icon, std::string frameName)
{
    if (icon && frameName != "")
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("global.plist");
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pic_main.plist");
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        if (frame != NULL )
            icon->setDisplayFrame(frame);
    }
}

MB_ItemData* MB_ItemMgr::getBoxByUID(uint64_t uID)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pBoxArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        if ( itemData->getItemUID() == uID)
        {
            return itemData;
        }
    }
    MB_LOG("UID:%d item instance not exist.", uID);
    return NULL;
    
}

unsigned int MB_ItemMgr::getItemCountInPacket()
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pItemDataArray, pObj)
    {
        MB_ItemData* itemData = (MB_ItemData*)pObj;
        MB_LOG("ITEM ID  :%d",itemData->getItemID());
    }
    return m_pItemDataArray->count();
}

void MB_ItemMgr::sortMB_ItemDataArray()
{
    int i,j;
    MB_ItemData *itemData1, *itemData2;
    MB_ItemTemplate *itemTemplete1, *itemTemplete2;
    for (i = 0; i < m_pItemDataArray->count(); i++)
    {
        for (j = i + 1; j < m_pItemDataArray->count(); j++)
        {
            itemData1 = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
            itemData2 = (MB_ItemData*)m_pItemDataArray->objectAtIndex(j);
            
            //穿上的道具排前面
            if (itemData1->getItemPetID() != 0
                && itemData2->getItemPetID() == 0)
            {
                continue;
            }
            else if (itemData1->getItemPetID() == 0
                     && itemData2->getItemPetID() != 0)
            {
                m_pItemDataArray->exchangeObjectAtIndex(i, j);
            }
            else
            {
                itemTemplete1 = m_mapItemTemplate.find(itemData1->getItemID())->second;
                itemTemplete2 =m_mapItemTemplate.find(itemData2->getItemID())->second;
                
                //星級高的排前面
                if (itemData1->getItemRank() + itemTemplete1->getItemStar()*100
                    > itemData2->getItemRank() + itemTemplete2->getItemStar()*100)
                {
                    continue;
                }
                else if (itemData1->getItemRank() + itemTemplete1->getItemStar()*100
                    < itemData2->getItemRank() + itemTemplete2->getItemStar()*100)
                {
                    m_pItemDataArray->exchangeObjectAtIndex(i, j);
                }
                else    //相等
                {
                    if (itemData1->getItemLevel() > itemData2->getItemLevel())
                    {
                        continue;
                    }
                    else if (itemData1->getItemLevel() < itemData2->getItemLevel())
                    {
                        m_pItemDataArray->exchangeObjectAtIndex(i, j);
                    }
                    else //相等
                    {
                        if (itemData1->getItemID() > itemData2->getItemID())
                        {
                            m_pItemDataArray->exchangeObjectAtIndex(i, j);
                        }
                    }
                }
            }
        }
    }
    
    //更新各个分支隊列
    updateSubArray();
}

int MB_ItemMgr::getItemPrice(MB_ItemData* itemData, MB_ItemTemplate* itemTemplete)
{
    if (itemData == NULL || itemTemplete == NULL) {
        return 0;
    }
    
    return (itemTemplete->getItemCost() * (1+itemData->getItemLevel()) * (1+itemData->getItemRank()));
}

bool MB_ItemMgr::getItemInPackage(uint16_t tid)
{
    MB_ItemData* pData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pItemDataArray, MB_ItemData*, pData)
    {
        if (pData->getItemID() == tid)
        {
            return true;
        }
    }
    return  false;
}

int MB_ItemMgr::getItemNumForExchangeByType(uint16_t type){

    int count = 0;
    CCObject *obj;
    CCARRAY_FOREACH(m_pItemDataArray, obj){
    
        MB_ItemData *data = (MB_ItemData *) obj;
        if(data->getItemID() == type){
            
            if(data->getItemLevel() < 10 && data->getItemRank() < 1){
            
                if (data->getItemPetID() == 0) {
                    
                    count +=  (data->getItemNumber() > 1 ? data->getItemNumber() : 1);
                }
            }
        }
        
    }
    return count;
}
void MB_ItemMgr::updateSubArray()
{
    m_pEquipArray->removeAllObjects();
    m_pWeaponArray->removeAllObjects();
    m_pDefenceArray->removeAllObjects();
    m_pHorseArray->removeAllObjects();
    m_pTreasureArray->removeAllObjects();
    m_pMaterialArray->removeAllObjects();
    m_pBoxArray->removeAllObjects();
    m_pOtherArray->removeAllObjects();
    m_pEquipUnionArray->removeAllObjects();
    m_pPetUnionArray->removeAllObjects();
    m_pWingArray->removeAllObjects();
    m_pHeadwareArray->removeAllObjects();
    m_pRuneStoreArray->removeAllObjects();
    m_pTotermArray->removeAllObjects();
    m_pItemFormulaArray->removeAllObjects();
    m_pItemDebrisArray->removeAllObjects();
    m_pExpCardArray->removeAllObjects();
    int totalNum = m_pItemDataArray->count();
    MB_ItemData* itemData = NULL;
    MB_ItemTemplate* itemTemplete = NULL;
    uint8_t itemType = kNONE;
    for (int i = 0; i < totalNum; i++)
    {
        itemData = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
        
        //初始化itemdata中的itemtype
        if (itemData->getItemType() == 0)
        {
            itemTemplete = getItemTemplateByID(itemData->getItemID());
            CCAssert(itemTemplete != NULL, "");
            itemType = itemTemplete->getItemType();
            itemData->setItemType(itemType);
            
        }
        else
        {
            itemType = itemData->getItemType();
        }
        
        //归類
        if (itemType == kWEAPON) {
            m_pEquipArray->addObject(itemData);
            m_pWeaponArray->addObject(itemData);
        }
        else if(itemType == kITEM_WING)
        {
            m_pEquipArray->addObject(itemData);
            m_pWingArray->addObject(itemData);
        }
        else if(itemType == kITEM_HEADWEAR)
        {
            m_pEquipArray->addObject(itemData);
            m_pHeadwareArray->addObject(itemData);
        }
        else if(itemType == kITEM_TOTEM)
        {
            m_pEquipArray->addObject(itemData);
            m_pTotermArray->addObject(itemData);
        }
        else if(itemType == kITEM_RUNESTONE)
        {
            m_pEquipArray->addObject(itemData);
            m_pRuneStoreArray->addObject(itemData);
        }
        else if (itemType == kARMOR)
        {
            m_pEquipArray->addObject(itemData);
            m_pDefenceArray->addObject(itemData);
        }
        else if (itemType == kHORSE)
        {
            m_pEquipArray->addObject(itemData);
            m_pHorseArray->addObject(itemData);
        }
        else if(itemType == kITEM_FORMULA)
        {
            m_pItemFormulaArray->addObject(itemData);
//            m_pOtherArray->addObject(itemData);
        }
//        else if ((itemType >= kTREASURE_PHYSICAL_DAMAGE_ADDTION && itemType <= kTREASURE_REEL_REDUCE)
//                 || (itemType >= kTREASURE_TIANQIAN && itemType <= kTREASURE_ZEDUI))
//        {
//            m_pTreasureArray->addObject(itemData);
//        }
        else if (itemType == kMATERRIAL)
        {
            m_pMaterialArray->addObject(itemData);
        }
        else if (itemType == kOTHER)
        {
            if(itemData->getItemID() != COMPOS_GER3_ID && itemData->getItemID() != COMPOS_GER4_ID  && itemData->getItemID() != COMPOS_GER5_ID &&
               itemData->getItemID() != COMPOS_ITEM3_ID && itemData->getItemID() != COMPOS_ITEM4_ID  && itemData->getItemID() != COMPOS_ITEM5_ID
               ){
                
                m_pOtherArray->addObject(itemData);
            }
        }
        else if (itemType == kOTHER_BOX)
        {
            m_pOtherArray->insertObject(itemData, 0);
        }
        else if (itemType >= KMATERRIAL_PATCH_WEAPON
                 && itemType <= KMATERRIAL_PATCH_HORSE)
        {
            m_pEquipUnionArray->addObject(itemData);
        }
        else if (itemType == KMATERRIAL_PATCH_GENERAL)
        {
            m_pPetUnionArray->addObject(itemData);
        }
        else if(itemType == ENERGY_RECOVERY) //体力恢複道具
        {
            m_pOtherArray->insertObject(itemData, 0);
        }
        else if(CheckIsDebris(itemType)) //碎片
        {
            m_pItemDebrisArray->addObject(itemData);
        }
        else if(itemType == kEXPCARD) //經驗卡牌
        {
            m_pExpCardArray->addObject(itemData);
            m_pOtherArray->addObject(itemData);
            
        }
        else
        {
            MB_LOG("error:unkown item type id:%d", itemType);
        }
    }
}

void MB_ItemMgr::sortOtherArray()
{
    m_pOtherArray->sortArray(MB_ItemMgr::sortOther);
}



//類型 kOTHER_BOX 寶箱 >ENERGY_RECOVERY 体力> kOTHER 其他>kEXPCARD 經驗卡牌
bool MB_ItemMgr::sortOther(CCObject* p1,CCObject* p2)
{
    if (p1 == NULL || p2 == NULL) {
        return false;
    }
    MB_ItemData* data1 = dynamic_cast<MB_ItemData*>(p1);
    MB_ItemData* data2 = dynamic_cast<MB_ItemData*>(p2);

    if (data1 == NULL || data2 == NULL) {
        return true;
    }
    
    if (data1->getItemType() == kEXPCARD && data2->getItemType() != kEXPCARD)
    {
        return false;
    }
    
    if (data1->getItemType() == kOTHER && (data2->getItemType() == ENERGY_RECOVERY || data2->getItemType() == kOTHER_BOX))
    {
        return false;
    }
    
    if (data1->getItemType() == ENERGY_RECOVERY && data2->getItemType() == kOTHER_BOX)
    {
        return false;
    }
    
    if (data1->getItemType() == kOTHER_BOX && data2->getItemType() != kOTHER_BOX)
    {
        return true;
    }
    
    if(data1->getItemType() == data2->getItemType())
    {
        if (data1->getTemplateStar() < data2->getTemplateStar())
        {
            return false;
        }
        else if (data1->getTemplateStar() > data2->getTemplateStar())
        {
            return true;
        }
        
        if (data1->getItemID() < data2->getItemID())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
   
    
    
}
CCArray* MB_ItemMgr::getCanEquipTreaArray(uint64_t petUID, uint8_t itemPos)
{
    m_pCanEquipTreaArray->removeAllObjects();
    uint8_t petPos = MB_TeamData::getInstance()->getPetPosByPetID(petUID);
    TeamDataStruct* teamData = MB_TeamData::getInstance()->getTeamMemberByIndex(petPos);
    MB_ItemData* itemData = NULL;
    uint8_t* ignoreTypeArray = new uint8_t[10];
    memset(ignoreTypeArray, 0, sizeof(uint8_t)*10);
    int index = 0;
    MB_ItemTemplate* treaTemplete = NULL;
    bool isHave = false;
    if (itemPos == kItemPosTreasure1)
    {
        if (teamData->m_pTreasure2 != NULL)
        {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure2->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }

        if (teamData->m_pTreasure3 != NULL)
        {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure3->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }
    }
    else if (itemPos == kItemPosTreasure2)
    {
        if (teamData->m_pTreasure1 != NULL) {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure1->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }
        if (teamData->m_pTreasure3 != NULL) {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure3->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }
    }
    else
    {
        if (teamData->m_pTreasure1 != NULL) {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure1->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }
        if (teamData->m_pTreasure2 != NULL) {
            treaTemplete = getItemTemplateByID(teamData->m_pTreasure2->getItemID());
            attributeMap& attributes = treaTemplete->getAtrributeMap();
            for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
            {
                isHave = false;
                for (int i = 0; i <= index; i++) {
                    if (ignoreTypeArray[i] == (uint8_t)it->first) {
                        isHave = true;
                        break;
                    }
                }
                if (!isHave)
                {
                    ignoreTypeArray[index++] = (uint8_t)it->first;
                }
            }
        }
    }
    
    for (int i = 0; i < m_pTreasureArray->count(); i++)
    {
        itemData = (MB_ItemData*)m_pTreasureArray->objectAtIndex(i);
        if (itemData->getItemPetID() == petUID)
        {
            continue;
        }
        
        //判断是否道具有相同属性
        isHave = false;
        treaTemplete = getItemTemplateByID(itemData->getItemID());
        attributeMap& attributes = treaTemplete->getAtrributeMap();
        for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
        {
            for (int i = 0; i < index; i++) {
                if (ignoreTypeArray[i] == (uint8_t)it->first) {
                    isHave = true;
                    break;
                }
            }
        }
        if (isHave) {
            continue;
        }
        
        m_pCanEquipTreaArray->addObject(itemData);
    }
    return m_pCanEquipTreaArray;
}

bool MB_ItemMgr::initItemTemplate()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/item.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "Item")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_ItemTemplate* itemTempleteNode = new MB_ItemTemplate();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Type"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemType(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Name"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemName(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Desc"))
            { 
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemDesc(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Icon"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemIcon(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Card"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemCard(value);
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Star"))
            { 
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemStar(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "RankMax"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemRankMax(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }

            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Cost"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemCost(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Stack"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setItemStack(std::strcmp(value, "false"));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "ComposeItemID"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setComposeItemID(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "ComposeNeedNum"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setComposeNum(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            if (attr && !xmlStrcmp(attr->name, BAD_CAST "ComposeCommonMaxNum")) {
                
                value = (char*)xmlNodeGetContent(attr->children);
                itemTempleteNode->setComposeCommonMaxNum(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            xmlNodePtr curNodeChild = curNode->xmlChildrenNode;
            char* atrributeValue;
            struct _xmlAttr * attr1 = NULL;
            while(NULL != curNodeChild)
            {
                if (xmlStrcmp(curNodeChild->name,BAD_CAST "Attribute"))
                {
                    if (xmlStrcmp(curNodeChild->name,BAD_CAST "Suit")==0)
                    {
                        attr1 = curNodeChild->properties;
                        if (0 == xmlStrcmp(attr1->name, BAD_CAST "id"))
                        {
                            atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                            itemTempleteNode->setSuitID(atoi(atrributeValue));
                            CC_SAFE_FREE(atrributeValue);
                            attr1 = attr1->next;
                        }
                    }
                    curNodeChild = curNodeChild->next;
                    continue;
                }
                
                attr1 = curNodeChild->properties;
                
                if (attr1 != NULL)
                {
                    uint16_t atype  = 0;
                    uint16_t avalue = 0;
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "Type"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        atype = atoi(atrributeValue);
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if (0 == xmlStrcmp(attr1->name,BAD_CAST "Value"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        avalue = atoi(atrributeValue);
                        CC_SAFE_FREE(atrributeValue);
                    }
                    itemTempleteNode->setAttribute((eItem_Attribute_Type)atype, avalue);
//                    MB_LOG("atype: %d  avalue: %d",atype,avalue);
                }
                curNodeChild = curNodeChild->next;
            }
            //加入到模板map中
            m_mapItemTemplate.insert(MB_ItemTemplateMapEntry(itemTempleteNode->getItemID(), itemTempleteNode));
            
        }
        else
        {
            MB_LOG("Error:empty item in templete.");
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}
void MB_ItemMgr::setSellTotalPrice(uint32_t price)
{
    m_sellTotalPrice = price;
}

bool MB_ItemMgr::addItemForSell(uint64_t itemUID, ItemType itemType)
{
    int i;
    MB_ItemData* itemData;
    //判断是否已裝備
    if (itemType == kWEAPON)
    {
        for (i = 0; i < MEMBER_NUM; i++) {
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pEquip1;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
        }
    }
    else if (itemType == kARMOR)
    {
        for (i = 0; i < MEMBER_NUM; i++) {
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pEquip2;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
        }
    }
    else if (itemType == kHORSE)
    {
        for (i = 0; i < MEMBER_NUM; i++) {
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pEquip3;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
        }
    }
    else if ((itemType >= kTREASURE_PHYSICAL_DAMAGE_ADDTION && itemType <= kTREASURE_REEL_REDUCE)
             || (itemType >= kTREASURE_TIANQIAN && itemType <= kTREASURE_ZEDUI))
    {
        for (i = 0; i < MEMBER_NUM; i++) {
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure1;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure2;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure3;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure4;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure5;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure6;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure7;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
            itemData =MB_TeamData::getInstance()->getTeamMemberByIndex(i)->m_pTreasure8;
            if (itemData != NULL && itemData->getItemUID() == itemUID) {
               
                MB_LOG("need to move out of equip itemUID:%ld itemType:%d", itemUID, itemType);
                return false;
            }
        }
    }
    
    //判断是否已經存在待售列表
    for (i = m_vecItemForSell->size() - 1; i >=0; --i) {
        if (m_vecItemForSell->at(i) == itemUID)
        {
            MB_LOG("already added for sell petID:%ld", itemUID);
            return false;
        }
    }
    m_vecItemForSell->push_back(itemUID);
    return true;
}

bool MB_ItemMgr::removeItemForSell(uint64_t itemUID)
{
    MB_ItemData* itemData = NULL;
    for (int j = 0; j < m_pItemDataArray->count(); j++) {
        itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getItemUID() == itemUID) {
            itemData->setReadyForSell(false);
            return true;
        }
    }
    MB_LOG("remove pet for sell failed, can't find id:%ld",itemUID);
    return false;
}

void MB_ItemMgr::clearItemForSell()
{
    int j;
    MB_ItemData* itemData = NULL;
    for (j = 0; j < m_pItemDataArray->count(); j++) {
        itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getReadyForSell()) {
            itemData->setReadyForSell(false);
        }
    }
}

std::vector<uint16_t>&  MB_ItemMgr::getEnhanceLevelList(void)
{
    return m_enhanceItemList;
}

uint64_t MB_ItemMgr::getEnhanceItemUid()
{
    return m_enhanceItemUID;
}
void  MB_ItemMgr::removeItemByUID  (uint64_t itemuid){

    //销毁总列表中的道具实例
    for (int j = 0; j < m_pItemDataArray->count(); j++)
    {
        MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getItemUID() == itemuid)
        {
         
            m_pItemDataArray->removeObjectAtIndex(j);
            
            break;
        }
    }
    updateSubArray();

}
void MB_ItemMgr::removeItem(uint64_t itemuid, uint8_t removenum)
{
    //销毁总列表中的道具实例
    for (int j = 0; j < m_pItemDataArray->count(); j++)
    {
        MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getItemUID() == itemuid)
        {
            if (itemData->getItemNumber() > removenum) {
                itemData->setItemNumber(itemData->getItemNumber() - removenum);
            }
            else
            {
                m_pItemDataArray->removeObjectAtIndex(j);
            }
            break;
        }
    }
    updateSubArray();
}

void MB_ItemMgr::removeItemByTypeID(uint16_t itemTypeID, uint8_t num)
{
    //销毁总列表中的道具实例
    for (int j = 0; j < m_pItemDataArray->count(); j++)
    {
        MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getItemID() == itemTypeID)
        {
            if (itemData->getItemNumber() > num)
            {
                itemData->setItemNumber(itemData->getItemNumber() - num);
            }
            else
            {
                m_pItemDataArray->removeObjectAtIndex(j);
            }
            break;
        }
    }
    updateSubArray();
}

void MB_ItemMgr::removeItemAfterSell()
{
    int j;
    //uint8_t itemType;
    //销毁总列表中的道具实例
    for (j = 0; j < m_pItemDataArray->count(); j++) {
        MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
        if ( itemData->getReadyForSell()) {
            m_pItemDataArray->removeObjectAtIndex(j);
            j--;
        }
    }
    updateSubArray();
}

bool MB_ItemMgr::senditem_bag()
{
    SOCKET_REQUEST_START(CS_ITEM_BAG);
    SOCKET_REQUEST_END(SC_ITEM_BAG, MB_ItemMgr::onMsgRecv);
    
    return true;
}

bool MB_ItemMgr::recvitem_bag(MB_MsgBuffer *recvPacket)
{
    m_pItemDataArray->removeAllObjects();
    return recvitem_new(recvPacket);
}

bool MB_ItemMgr::senditem_use(uint64_t itemuid,uint8_t itemnum)
{
    SOCKET_REQUEST_START(CS_ITEM_USE);
    packet->WriteUINT64(itemuid);
    packet->writeU8(itemnum);
    SOCKET_REQUEST_END(SC_ITEM_USE, MB_ItemMgr::onMsgRecv);
    return true;
}

bool MB_ItemMgr::recvitem_use(MB_MsgBuffer* recvPacket)
{
    uint8_t data8;
    uint64_t data64;

    recvPacket->readU8(&data8);
    if (1 == data8) {
        recvPacket->readU64(&data64);
        recvPacket->readU8(&data8);
        MB_Message::sharedMB_Message()->showMessage("使用成功");
        
    }
    else if(2 == data8)
    {
        MB_Message::sharedMB_Message()->showMessage("使用失败-数量不足");
    }
    else if(3 == data8)
    {
        MB_Message::sharedMB_Message()->showMessage("使用失败-原因未知");
    }
    else if(4 == data8)
    {
        MB_Message::sharedMB_Message()->showMessage("今日使用次数已达上限, 请明日再使用");
    }
    else if(5 == data8)
    {
        MB_Message::sharedMB_Message()->showMessage("体力值已满, 使用失败");
    }
    else
    {
        SHOW_WND_TIP("useitem_message.xml", data8);
    }
    sortMB_ItemDataArray();
    return true;
}


//剩余次數
bool MB_ItemMgr::senditem_use_info()
{
    SOCKET_REQUEST_START(CS_ITEM_USE_INFO);
    SOCKET_REQUEST_END(SC_ITEM_USE_INFO, MB_ItemMgr::onMsgRecv);
    return true;
}
bool MB_ItemMgr::recvitem_use_info(MB_MsgBuffer* recvPacket)
{
    uint16_t len = 0;
    uint16_t data16;
    uint8_t  data8;
    recvPacket->readU16(&len);
    for(int i=0;i<len;i++)
    {
        recvPacket->readU16(&data16);
        recvPacket->readU8(&data8);
        MB_UseItemRule*  rule = new MB_UseItemRule(data16,data8);
        setUseItemLastTimes(rule);
        rule->release();
    }
    return true;
}

bool MB_ItemMgr::senditem_equip()
{
    SOCKET_REQUEST_START(CS_ITEM_EQUIP);
    SOCKET_REQUEST_END(SC_ITEM_EQUIP, MB_ItemMgr::onMsgRecv);
    
    return true;
}

bool MB_ItemMgr::recvitem_equip(MB_MsgBuffer *recvPacket)
{
    uint16_t len;
    uint8_t data8;
    uint16_t data16;
    uint64_t data64;
    uint32_t data32;
    //m_pItemDataArray已經在recvitem_bag中清理過了
    
    recvPacket->readU16(&len);
    for (int i = 0; i < len; i++)
    {
        MB_ItemData* itemData = new MB_ItemData();
        itemData->setItemNumber(0);
        if (recvPacket->readU64(&data64))
        {
            itemData->setItemUID(data64);
        }
        if (recvPacket->readU16(&data16)) {
            itemData->setItemID(data16);
        }
        if (recvPacket->readU8(&data8)) {
            itemData->setItemLevel(data8);
        }
        if (recvPacket->readU8(&data8)) {
            itemData->setItemRank(data8);
        }
        if (recvPacket->readU64(&data64)) {
            itemData->setItemPetID(data64);
        }
        if (recvPacket->readU8(&data8)) {
            itemData->setItemPos(data8);
        }
        if (recvPacket->readU32(&data32)) {
            itemData->setItemRankOverTim(data32);
        }
        if (recvPacket->readU16(&data16)) {

            itemData->setExp(data16);
        }


        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pItemDataArray, pObj)
        {
            //不应該有重複的实体被添加
            CC_ASSERT(((MB_ItemData*)pObj)->getItemUID() != itemData->getItemUID());
        }
        m_pItemDataArray->addObject(itemData);
        itemData->release();
    }
    sortMB_ItemDataArray();
    return true;
}
bool  MB_ItemMgr::senditem_compound(uint16_t typeID){

    SOCKET_REQUEST_START(CS_ITEM_COMPOUND);
    packet->writeU16(typeID);
    SOCKET_REQUEST_END(SC_ITEM_COMPOUND, MB_ItemMgr::onMsgRecv);
    return true;
}
bool  MB_ItemMgr::recvitem_compound(MB_MsgBuffer* recvPacket){
    MB_Message::sharedMB_Message()->removeALLMessage();
    uint8_t data8;
    recvPacket->readU8(&data8);
    if(data8 == 1){
        uint16_t data16;
        recvPacket->readU16(&data16);
        
        if (global_layerItemDetail!=NULL) {
            global_layerItemDetail->onReSet(true);
        }
    }else {
    
        MB_Message::sharedMB_Message()->showMessage("材料不足");
    }
    
    return true;
}
bool MB_ItemMgr::senditem_sell()
{
    uint16_t size = 0;
    MB_ItemData* itemData = NULL;
    for (uint16_t i = 0; i < m_pItemDataArray->count(); i++)
    {
        itemData = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
        if (itemData->getReadyForSell())
        {
            size++;
        }
    }
    
    if (size == 0) {
        MB_Message::sharedMB_Message()->removeALLMessage();
        MB_Message::sharedMB_Message()->showMessage("未选择出售道具.");
        return true;
    }
    
    SOCKET_REQUEST_START(CS_ITEM_SELL);
    packet->writeU16(size);
    for (int i = 0; i < m_pItemDataArray->count(); i++)
    {
        itemData = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
        if (itemData->getReadyForSell())
        {
            packet->WriteUINT64(itemData->getItemUID());
        }
    }
    SOCKET_REQUEST_END(SC_ITEM_SELL, MB_ItemMgr::onMsgRecv);
    
    return true;
}


bool MB_ItemMgr::recvitem_sell(MB_MsgBuffer *recvPacket)
{
    MB_Message::sharedMB_Message()->removeALLMessage();
    
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1) {
        
//        removeItemAfterSell();
        sortMB_ItemDataArray();
    }
    else
    {
        clearItemForSell();
        SHOW_WND_TIP("item_sell_result.xml", result);
        return false;
    }
    
    return true;
}

bool MB_ItemMgr::senditem_down_equip(uint64_t petUID, uint8_t itemPos)
{
    SOCKET_REQUEST_START(CS_ITEM_DOWN_EQUIP);
    packet->WriteUINT64(petUID);
    packet->writeU8(itemPos);
    SOCKET_REQUEST_END(SC_ITEM_DOWN_EQUIP, MB_ItemMgr::onMsgRecv);
    return true;
}

bool MB_ItemMgr::recvitem_down_equip(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    recvPacket->readU8(&result);
    if (result == 1) {
        MB_LOG("卸载装备成功");
        uint32_t petUID;
        uint8_t itemPos;
        recvPacket->readU64(&petUID);
        recvPacket->readU8(&itemPos);
        for (int i = 0; i < m_pItemDataArray->count(); i++) {
            MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(i));
            if ( itemData->getItemPetID() == petUID && itemData->getItemPos() == itemPos)
            {
                itemData->setItemPetID(0);
                itemData->setItemPos(0);
                break;
            }
        }
    }
    else if (result == 2)
    {
        MB_LOG("卸载装备不存在");
    }
    else
    {
        MB_LOG("卸载装备未知错误");
    }
    sortMB_ItemDataArray();
    return true;
}

bool MB_ItemMgr::senditem_up_equip(uint64_t petUID, uint8_t itemPos, uint64_t itemUID, uint64_t oldPetUID)
{
    SOCKET_REQUEST_START(CS_ITEM_UP_EQUIP);
    packet->WriteUINT64(petUID);
    packet->writeU8(itemPos);
    packet->WriteUINT64(itemUID);
    packet->WriteUINT64(oldPetUID);
    SOCKET_REQUEST_END(SC_ITEM_UP_EQUIP, MB_ItemMgr::onMsgRecv);
    MB_Message::sharedMB_Message()->showMessage("",15, NULL);
    return true;
}

bool MB_ItemMgr::recvitem_new(MB_MsgBuffer *recvPacket)
{
    uint16_t len;
    uint8_t data8;
    uint16_t data16;
    uint64_t data64;
    uint32_t data32;
    recvPacket->readU16(&len);
    for (int i = 0; i < len; i++)
    {
        MB_ItemData* itemData = new MB_ItemData();
        
        if (recvPacket->readU64(&data64))
        {
            itemData->setItemUID(data64);
        }
        if (recvPacket->readU16(&data16)) {
            itemData->setItemID(data16);
        }
        if (recvPacket->readU8(&data8)) {
            itemData->setItemLevel(data8);
        }
        if (recvPacket->readU8(&data8)) {
            itemData->setItemRank(data8);
        }
        if (recvPacket->readU16(&data16)) {
            itemData->setItemNumber(data16);
        }
        if (recvPacket->readU32(&data32)) {
            itemData->setItemRankOverTim(data32);
        }
        if(recvPacket->readU16(&data16)){
        
            itemData->setExp(data16);
        }
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pItemDataArray, pObj)
        {
            //不应該有重複的实体被添加
            CC_ASSERT(((MB_ItemData*)pObj)->getItemUID() != itemData->getItemUID());
            
            if (((MB_ItemData*)pObj)->getItemUID() == itemData->getItemUID())
            {
                ((MB_ItemData*)pObj)->setItemNumber(((MB_ItemData*)pObj)->getItemNumber() + itemData->getItemNumber());
            }
        }
        m_pItemDataArray->addObject(itemData);
        itemData->release();
    }
    sortMB_ItemDataArray();
    return true;
}

bool MB_ItemMgr::recvitem_update(MB_MsgBuffer *recvPacket)
{
    uint16_t len;
    uint64_t itemUID;
    uint16_t itemNum;
    MB_ItemData* itemData;
    recvPacket->readU16(&len);
    for (int i = 0; i < len; i++) {
        recvPacket->readU64(&itemUID);
        recvPacket->readU16(&itemNum);
        for (int j = 0; j < m_pItemDataArray->count(); j++) {
            itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(j));
            if (itemData->getItemUID() == itemUID) {
                itemData->setItemNumber(itemNum);
                break;
            }
        }
    }
    sortMB_ItemDataArray();
    
    if (global_layerItemDetail!=NULL) {
        global_layerItemDetail->onReSet(true);
    }
    return true;
}

/*
 required	int64		petID			=2;//要穿上裝備的武將ID
 required	int8		itemPos			=3;//裝備位置
 required	int64		itemUID			=4;//穿上的裝備的UID
 */
bool MB_ItemMgr::recvitem_up_equip(MB_MsgBuffer *recvPacket)
{
    uint8_t result;
    MB_Message::sharedMB_Message()->removeALLMessage();
    recvPacket->readU8(&result);
    if (result == 1) {
        MB_LOG("穿装成功");
        uint64_t petUID, itemUID;
        uint8_t itemPos;
        recvPacket->readU64(&petUID);
        recvPacket->readU8(&itemPos);
        recvPacket->readU64(&itemUID);

        int i;
        bool bDown = false, bUp = false;
        //卸下裝備
        int countItem =  m_pItemDataArray->count();
        for (i = 0; i < countItem ; i++) {
            
            MB_ItemData* itemData = dynamic_cast<MB_ItemData*>(m_pItemDataArray->objectAtIndex(i));
            if(itemData != NULL){
                
                // 卸下裝備
                if (itemData->getItemPetID() == petUID && itemData->getItemPos() == itemPos)
                {
                    itemData->setItemPetID(0);
                    itemData->setItemPos(0);
                    bDown = true;
                }
                if (itemData->getItemUID() == itemUID) {
                    
                    if (itemData->getItemPetID() != 0) {
                        
                        bool isFind = false;
                        TeamDataStruct* teamData = NULL;
                        for (int j = 0; j < CARD_IN_GAME; j++) {
                            
                            teamData = MB_TeamData::getInstance()->getTeamMemberByIndex(j);
                            if (teamData->m_pPet != NULL && teamData->m_pPet->getPetID() == itemData->getItemPetID())
                            {
                                MB_TeamData::getInstance()->equipDownByItemUID((uint8_t)j, itemUID);
                                isFind = true;
                                break;
                            }
                        }
                    }
                    itemData->setItemPetID(petUID);
                    itemData->setItemPos(itemPos);
                    bUp = true;
                }
                if (bDown && bUp) {
                    
                    MB_LOG("换装成功");
                    break;
                }
            }
        }
        //更新TeamData
        uint8_t petPos = MB_TeamData::getInstance()->getPetPosByPetID(petUID);
        if(petPos < MEMBER_NUM)
        {
            MB_TeamData::getInstance()->equipUpByItemUID(petPos, itemUID);
        }
        
        global_layerPetDetail->isUpdateUI = true;
        global_layerPetDetail->onResetWnd();
    }
    else{
        MB_LOG("recvitem_up_equip failed. errcode:%d", result);
    }
    if (global_layerItemDetail!=NULL) {
        global_layerItemDetail->removeFromParent();
    }
    sortMB_ItemDataArray();
    return true;
}

bool MB_ItemMgr::senddaily_get_list()
{
    SOCKET_REQUEST_START(CS_DAILY_GET_LIST);
    SOCKET_REQUEST_END(SC_DAILY_GET_LIST, MB_ItemMgr::onMsgRecv);
    return true;
}

bool MB_ItemMgr::recvdaily_get_list(MB_MsgBuffer *recvPacket)
{
    uint8_t data8;
    uint16_t num;
    
    m_pDailyRewardArray->removeAllObjects();
    
    if (recvPacket->readU16(&num))
    {
//        if (num == 0) {
//            MB_LOG("無登入領取");
//            return true;
//        }
        
        DailyRewardValue* pObj = NULL;
        for (int i = 0; i < num; ++i)
        {
            pObj = new DailyRewardValue();
            if (recvPacket->readU8(&data8)) {
                pObj->setType(data8);
            }
            if (recvPacket->readU8(&data8)) {
                pObj->setValue(data8);
            }
            if (recvPacket->readU8(&data8)) {
                pObj->setIsGet(data8);
            }
            m_pDailyRewardArray->addObject(pObj);
            pObj->release();
        }
    }
    else
    {
        MB_LOG("parse recvdaily_get_list failed.");
        return false;
    }
    
    m_vLoginRecord.clear();
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    uint8_t day=0;
    for (uint16_t i=0; i<count; ++i)
    {
        recvPacket->readU8(&day);
        m_vLoginRecord.push_back(day);
    }
    
    return true;
}

bool MB_ItemMgr::senddaily_draw(uint8_t type)
{
    SOCKET_REQUEST_START(CS_DAILY_DRAW);
    packet->writeU8(type);
    SOCKET_REQUEST_END(SC_DAILY_DRAW, MB_ItemMgr::onMsgRecv);
    return true;
}

bool MB_ItemMgr::recvdaily_draw(MB_MsgBuffer *recvPacket)
{
    uint8_t data8;
    
    if (recvPacket->readU8(&data8)) {
        if (data8 == 1) {
            
            DailyRewardValue* dailyRewardValue = new DailyRewardValue();
            if (recvPacket->readU8(&data8)) {
                dailyRewardValue->setType(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dailyRewardValue->setValue(data8);
            }
            if (recvPacket->readU8(&data8)) {
                dailyRewardValue->setIsGet(data8);
            }
            bool bAdd = true;
            for (int i = 0; i < m_pDailyRewardArray->count(); i++)
            {
                DailyRewardValue* oldValue = (DailyRewardValue*)m_pDailyRewardArray->objectAtIndex(i);
                if (oldValue->getType() == dailyRewardValue->getType()) {
                    m_pDailyRewardArray->removeObjectAtIndex(i);
                    m_pDailyRewardArray->addObject(dailyRewardValue);
                    dailyRewardValue->release();
                    bAdd = false;
                    break;
                }
            }
            //找不到同類型的则加入
            if(bAdd)
            {
                m_pDailyRewardArray->addObject(dailyRewardValue);
                dailyRewardValue->release();
            }
        }
        else
        {
            MB_LOG("Daily reward failed. errcode:%d", data8);
            return false;
        }
    }
    m_vLoginRecord.clear();
    
    uint16_t count = 0;
    recvPacket->readU16(&count);
    uint8_t day=0;
    for (uint16_t i=0; i<count; ++i)
    {
        recvPacket->readU8(&day);
        m_vLoginRecord.push_back(day);
    }
    if (global_layerItemDetail!=NULL) {
        global_layerItemDetail->onReSet(true);
    }
    return false;
}

const std::vector<int>& MB_ItemMgr::getLoginRecordList()const
{
    return m_vLoginRecord;
}

void MB_ItemMgr::recvitem_delete_notify(MB_MsgBuffer* recvPacket)
{
    uint64_t data64;
    uint16_t num;
    if (recvPacket->readU16(&num))
    {
        for (int i = 0; i < num; ++i)
        {
            recvPacket->readU64(&data64);
            removeItemByUID (data64);
        }
    }
    sortMB_ItemDataArray();
    if (global_layerItemDetail!=NULL) {
        global_layerItemDetail->onReSet(true);
    }
}

void MB_ItemMgr::senditem_reinforce(uint64_t itemUid,uint64_t petID)
{
    SOCKET_REQUEST_START(CS_ITEM_REINFORCE);
    packet->WriteUINT64(itemUid);
    packet->WriteUINT64(petID);
    SOCKET_REQUEST_END(SC_ITEM_REINFORCE, MB_ItemMgr::onMsgRecv);
}
void MB_ItemMgr::recvitem_reinforce(MB_MsgBuffer* recvPacket)
{
    uint16_t data16;
    uint8_t result;
    m_enhanceItemList.clear();
    recvPacket->readU8(&result);
    // 1=> 強化成功
	// 2=> 強化失敗-银两不足
	// 3=> 強化失敗-裝備等級大於等於訓練師等級
	// 4=> 強化失敗-該裝備不存在
	// 5=> 強化失敗-未知錯誤
	// 6=> 強化失敗-該裝備不能強化
    if (1 == result)
    {
        recvPacket->readU64(&m_enhanceItemUID);
        recvPacket->readU16(&data16);
        m_enhanceItemList.push_back(data16);
        
        MB_ItemData* itemData = getItemDataByUID(m_enhanceItemUID);
        m_enhanceItemList[0] -= itemData?itemData->getItemLevel():0;
        itemData->setItemLevel(data16);
        sortMB_ItemDataArray();
    }
    else{
        if (result == 2) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "金币不足","确定");
        }
        else if (result == 3) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "装备等级大于等于玩家等级","确定");
        }
        else if (result == 4) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "该装备不存在","确定");
        }
        else if (result == 5) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "未知错误","确定");
        }
        else if (result == 6) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "该装备不能强化","确定");
        }
    }
}
void MB_ItemMgr::senditem_max_reinforce(uint64_t itemUid,uint64_t petID)
{
    SOCKET_REQUEST_START(CS_ITEM_MAX_REINFORCE);
    packet->WriteUINT64(itemUid);
    packet->WriteUINT64(petID);
    SOCKET_REQUEST_END(SC_ITEM_MAX_REINFORCE, MB_ItemMgr::onMsgRecv);
}

void MB_ItemMgr::recvitem_max_reinforce(MB_MsgBuffer* recvPacket)
{
    uint16_t data16;
    uint16_t num;
    uint8_t result;
    m_enhanceItemList.clear();
    recvPacket->readU8(&result);
    if (1 == result)
    {
        recvPacket->readU64(&m_enhanceItemUID);
        if (recvPacket->readU16(&num))
        {
            for (int i = 0; i < num; ++i)
            {
                recvPacket->readU16(&data16);
                m_enhanceItemList.push_back(data16);
            }
            
            for (int i = num - 1; i>=0; i--)
            {
                if(i>0)
                {
                    m_enhanceItemList[i] -= m_enhanceItemList[i-1];
                }
                else
                {
                    MB_ItemData* itemData = getItemDataByUID(m_enhanceItemUID);
                    m_enhanceItemList[i] -= itemData?itemData->getItemLevel():0;
                    itemData->setItemLevel(data16);
                }
            }
        }
        sortMB_ItemDataArray();
    }
    else
    {
        if (result == 2) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "金币不足","确定");
        }
        else if (result == 3) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "装备等级大于等于玩家等级","确定");
        }
        else if (result == 4) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "该装备不存在","确定");
        }
        else if (result == 5) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "未知错误","确定");
        }
        else if (result == 6) {
            MB_Message::sharedMB_Message()->showMessage("强化失败", "该装备不能强化","确定");
        }
    }
}

bool MB_ItemMgr::recvitem_update_rank(MB_MsgBuffer *recvPacket)
{
    uint64_t itemUID = 0;
    uint8_t newItemRank = 0;
    uint32_t newOverTime = 0;
    if (recvPacket->readU64(&itemUID) && \
        recvPacket->readU8(&newItemRank)&& \
        recvPacket->readU32(&newOverTime))
    {
        for (int i = 0; i < m_pItemDataArray->count(); ++i)
        {
            MB_ItemData* itemData = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
            if (itemData->getItemUID() == itemUID)
            {
                itemData->setItemRank(newItemRank);
                itemData->setItemRankOverTim(newOverTime);
                return true;
            }
        }
    }
    sortMB_ItemDataArray();
    return false;
}

bool MB_ItemMgr::senditem_up_rank(uint64_t srcUID, uint64_t foodUID, uint64_t srcPetID, uint64_t foodPetID)
{
    SOCKET_REQUEST_START(CS_ITEM_UP_RANK);
    packet->WriteUINT64(srcUID);
    packet->WriteUINT64(foodUID);
    packet->WriteUINT64(srcPetID);
    packet->WriteUINT64(foodPetID);
    SOCKET_REQUEST_END(SC_ITEM_UP_RANK, MB_ItemMgr);
    return true;
}

bool MB_ItemMgr::recvitem_up_rank(MB_MsgBuffer *recvPacket)
{
    uint8_t result = 0;
    recvPacket->readU8(&result);
    if (result == 1) {
        MB_LOG("道具升品成功");
        uint64_t srcItemUID = 0, foodItemUID = 0;
        if (recvPacket->readU64(&srcItemUID) && recvPacket->readU64(&foodItemUID) )
        {
            MB_ItemData* itemData = NULL;
            bool bOK1 = false, bOK2 = false;
            for (int i = 0; i < m_pItemDataArray->count(); ++i)
            {
                itemData = (MB_ItemData*)m_pItemDataArray->objectAtIndex(i);
                
                if (itemData->getItemUID() == srcItemUID) {
                    uint8_t level = 0, rank = 0;
                    if (recvPacket->readU8(&level) && recvPacket->readU8(&rank)) {
                        itemData->setItemLevel(level);
                        itemData->setItemRank(rank);
                    }
                    bOK1 = true;
                }
                if (itemData->getItemUID() == foodItemUID) {
                    if (itemData->getItemPetID() != 0) {
                        uint8_t petPos = MB_TeamData::getInstance()->getPetPosByPetID(itemData->getItemPetID());
                        MB_TeamData::getInstance()->equipDownByItemUID(petPos, foodItemUID);
                    }
                    m_pItemDataArray->removeObjectAtIndex(i);
                    i--;
                    bOK2 = true;
                }
                if (bOK1 && bOK2) {
                    break;
                }
            }
        }
        sortMB_ItemDataArray();
    }
    else{
        MB_LOG("recvitem_up_rank errcode:%d", result);
        if (result == 2) {
            MB_Message::sharedMB_Message()->showMessage("","升品失败,装备已达到最高品阶.", "确定");
        }
        else if (result == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,主道具不存在.", "确定");
        }
        else if (result == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,材料道具不存在.", "确定");
        }
        else if (result == 5)
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,不同道具不能吞噬.", "确定");
        }
        else if (result == 6)
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,金币不足.", "确定");
        }
        else if (result == 7)
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,非装备不能升品.", "确定");
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("", "升品失败,未知错误.", "确定");
        }
    }

    return false;
}
bool MB_ItemMgr::senditem_eat(uint64_t itemid,CCArray *itemList){

    SOCKET_REQUEST_START(CS_ITEM_EAT);
    packet->WriteUINT64(itemid);
    MB_ItemData *item  = getTreasureByUID(itemid);
    packet->WriteUINT64(item->getItemPetID());
    packet->writeU16(itemList->count());
    CCObject *obj;
    m_pEatArray->removeAllObjects();
    CCARRAY_FOREACH(itemList, obj){
    
        packet->WriteUINT64(((MB_ItemData *)obj)->getItemUID());
        m_pEatArray->addObject(obj);
    }
    SOCKET_REQUEST_END(SC_ITEM_EAT, MB_ItemMgr::onMsgRecv);
    return true;
}
bool MB_ItemMgr::recvitem_eat(MB_MsgBuffer* recvPacket){

    uint8_t result = 0;
    recvPacket->readU8(&result);
    if (result == 1) {
    
        uint64_t itemid;
        recvPacket->readU64(&itemid);
        MB_ItemData *data = getTreasureByUID(itemid);
        uint8_t data8;
        recvPacket->readU8(&data8);
        data->setItemRank(data8);
        uint16_t data16;
        recvPacket->readU16(&data16);
        data->setExp(data16);
        CCObject *obj;
        CCARRAY_FOREACH(m_pEatArray, obj){
            
            m_pItemDataArray->removeObject(obj);
        }
        sortMB_ItemDataArray();
    }
    else{
        
        MB_LOG("recvitem_up_rank errcode:%d", result);
        if (result == 2) {
            MB_Message::sharedMB_Message()->showMessage("精炼失败","被精炼宝物中有已装备宝物", "确定");
        }
        else if (result == 3)
        {
            MB_Message::sharedMB_Message()->showMessage("精炼失败","被精炼宝物中有已装备宝物", "确定");
        }
        else if (result == 4)
        {
            MB_Message::sharedMB_Message()->showMessage("精炼失败","该宝物已满阶", "确定");
        }
        else if (result == 5)
        {
            MB_Message::sharedMB_Message()->showMessage("精炼失败","数据不存在", "确定");
        }
        else
        {
            MB_Message::sharedMB_Message()->showMessage("精炼失败","被精炼宝物中有已装备宝物", "确定");
        }
      
    }

    return true;
}
void MB_ItemMgr::onMsgRecv(CCNode* node, SocketResponse* response)
{
    assert(response != NULL);
    
    //將socket數据读取到序列化結构
    MB_MsgBuffer* recvPacket = response->getResponseData();
    
    //协议號
    uint16_t Msg = 0;
    recvPacket->Reset();
    recvPacket->skipU16();
    recvPacket->skipU8();
    recvPacket->readU16(&Msg);
    
    switch (Msg) {
            
        case SC_ITEM_BAG:
            recvitem_bag(recvPacket);
            break;
        case SC_ITEM_EQUIP:
            recvitem_equip(recvPacket);
            break;
        case SC_ITEM_NEW:
            recvitem_new(recvPacket);
            break;
        case SC_ITEM_MORE:
            sc_item_more(recvPacket);
            break;
        case SC_ITEM_UPDATE:
            recvitem_update(recvPacket);
            break;
        case SC_ITEM_UP_EQUIP:
            recvitem_up_equip(recvPacket);
            break;
        case SC_ITEM_DOWN_EQUIP:
            recvitem_down_equip(recvPacket);
            break;
        case SC_ITEM_SELL:
            recvitem_sell(recvPacket);
            break;
        case SC_ITEM_USE:
            recvitem_use(recvPacket);
            break;
        case SC_DAILY_GET_LIST://TODODO 每日奖励
            recvdaily_get_list(recvPacket);
            break;
        case SC_DAILY_DRAW:
            recvdaily_draw(recvPacket);
            break;
            
        case SC_ITEM_DELETE_NOTIFY:
            recvitem_delete_notify(recvPacket);
            break;
        case SC_ITEM_REINFORCE:
            recvitem_reinforce(recvPacket);
            break;
        case SC_ITEM_MAX_REINFORCE:
            recvitem_max_reinforce(recvPacket);
            break;
        case SC_ITEM_UPDATE_RANK:
            recvitem_update_rank(recvPacket);
            break;
        case SC_ITEM_UP_RANK:
            recvitem_up_rank(recvPacket);
            break;
        case SC_ITEM_COMPOUND:
            recvitem_compound(recvPacket);
            break;
        case SC_ITEM_EAT:
            recvitem_eat(recvPacket);
            break;
        case SC_ITEM_USE_INFO:
            recvitem_use_info(recvPacket);
            break;
        case SC_ROLE_LOGIN_REWARD:
            recv_role_login_reward(recvPacket);
            break;
        default:
            break;
    }
}


bool MB_ItemMgr::initQualityCost()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/item_rank.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "rank")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            MB_ItemQualityCostTemplete* itemQCT = new MB_ItemQualityCostTemplete();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "star"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemQCT->setStar(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "quality"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemQCT->setQuality(atoi(value));
                CC_SAFE_FREE(value);
                attr = attr->next;
            }
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "coin"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                itemQCT->setCoin(atoll(value));
                CC_SAFE_FREE(value);
            }
            
            //加入到模板中
            m_pItemQualityUpCost->addObject(itemQCT);
            itemQCT->release();
            
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

/*
 message cs_role_login_reward[id=10139]{
 }
 
 message sc_role_login_reward[id=10140]{
 repeated    p_mail_reward               list    =1;
 }
 */

#include "MB_GiftsProtocol.h"
void MB_ItemMgr::send_role_login_reward()
{
    SOCKET_REQUEST_START(CS_ROLE_LOGIN_REWARD);
    SOCKET_REQUEST_END(SC_ROLE_LOGIN_REWARD, NULL);
}

void MB_ItemMgr::recv_role_login_reward(MB_MsgBuffer* pRecv)
{
    MB_MailReward reward;
    
    uint16_t count = 0;
    pRecv->readU16(&count);
    
    RewardTemplete *t = NULL;
    m_pDailyRewardTemplete->removeAllObjects();
    uint8_t uid = 1;
    for (uint16_t i=0; i<count; ++i)
    {
        t = new RewardTemplete;
        t->setID(uid);
        reward.read(pRecv);
        t->getValueArray()->addObjectsFromArray(reward.converIDNUM2RewardTempleteValue());
        m_pDailyRewardTemplete->addObject(t);
        t->release();
        ++uid;
    }
}

int MB_ItemMgr::getRenameCardCount()
{
    MB_ItemData* pData = NULL;
    CCARRAY_FOREACH_4TYPE(m_pItemDataArray, MB_ItemData*, pData)
    {
        if (pData->getItemID() == 50017)
        {
            return pData->getItemNumber();
        }
    }
    return 0;
}

bool MB_ItemMgr::initDailyRewardTemplete()
{
    return true;  // 改成从伺服器發送
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/daily_reward.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "reward")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            RewardTemplete* rewardTemplete = new RewardTemplete();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                rewardTemplete->setID(atoi(value));
                CC_SAFE_FREE(value);
            }
            
            xmlNodePtr curNodeChild = curNode->xmlChildrenNode;
            char* atrributeValue;
            while(NULL != curNodeChild)
            {
                if (xmlStrcmp(curNodeChild->name,BAD_CAST "values"))
                {
                    curNodeChild = curNodeChild->next;
                    continue;
                }
                
                struct _xmlAttr * attr1 = curNodeChild->properties;
                
                if (attr1 != NULL)
                {
                    RewardTempleteValue* rewardTempleteValue = new RewardTempleteValue();
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "type"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setType(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "value"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setValueID(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if (0 == xmlStrcmp(attr1->name,BAD_CAST "number"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setNumber(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                    }
                    //加入模板
                    rewardTemplete->getValueArray()->addObject(rewardTempleteValue);
                    rewardTempleteValue->release();
                }
                curNodeChild = curNodeChild->next;
            }
            //加入到模板
            m_pDailyRewardTemplete->addObject(rewardTemplete);
            rewardTemplete->release();
            
        }
        else
        {
            MB_LOG("Error:empty reward in daily templete.");
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}


bool MB_ItemMgr::initTitleRewardTemplete()
{
    xmlDocPtr g_sharedDoc = MB_XmlReader::readXml("config/item/arena_level_reward.xml");
    
    if (!g_sharedDoc)
    {
        return false;
    }
    
    xmlNodePtr root;
    
    root=xmlDocGetRootElement(g_sharedDoc);
    xmlNodePtr curNode = root->xmlChildrenNode;
    char* value;
    while(curNode != NULL) {
        
        if (xmlStrcmp(curNode->name,BAD_CAST "reward")) {
            curNode = curNode->next;
            continue;
        }
        
        struct _xmlAttr * attr = curNode->properties;
        
        if (attr != NULL) {
            
            RewardTemplete* rewardTemplete = new RewardTemplete();
            
            if (attr&&!xmlStrcmp(attr->name,BAD_CAST "Id"))
            {
                value = (char*)xmlNodeGetContent(attr->children);
                rewardTemplete->setID(atoi(value));
                CC_SAFE_FREE(value);
            }
            
            xmlNodePtr curNodeChild = curNode->xmlChildrenNode;
            char* atrributeValue;
            while(NULL != curNodeChild)
            {
                if (xmlStrcmp(curNodeChild->name,BAD_CAST "values"))
                {
                    curNodeChild = curNodeChild->next;
                    continue;
                }
                
                struct _xmlAttr * attr1 = curNodeChild->properties;
                
                if (attr1 != NULL)
                {
                    RewardTempleteValue* rewardTempleteValue = new RewardTempleteValue();
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "type"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setType(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if ( 0 == xmlStrcmp(attr1->name,BAD_CAST "value"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setValueID(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                        attr1 = attr1->next;
                    }
                    
                    if (0 == xmlStrcmp(attr1->name,BAD_CAST "number"))
                    {
                        atrributeValue = (char*)xmlNodeGetContent(attr1->children);
                        rewardTempleteValue->setNumber(atoi(atrributeValue));
                        CC_SAFE_FREE(atrributeValue);
                    }
                    //加入模板
                    rewardTemplete->getValueArray()->addObject(rewardTempleteValue);
                    rewardTempleteValue->release();
                }
                curNodeChild = curNodeChild->next;
            }
            //加入到模板
            m_pTitleRewardTemplete->addObject(rewardTemplete);
            rewardTemplete->release();
            
        }
        else
        {
            MB_LOG("Error:empty reward in title templete.");
        }
        
        curNode = curNode->next;
    }
    
    xmlFreeDoc(g_sharedDoc);
    
    return true;
}

//獲取剩余次數（体力道具）
int MB_ItemMgr::getUseItemLastTimesByTID(uint16_t tID)
{
    if (!m_pUseItemRuleArray) {
        return -1;
    }
    for (int i = 0; i < m_pUseItemRuleArray->count(); i++) {
        MB_UseItemRule* rule = (MB_UseItemRule*)(m_pUseItemRuleArray->objectAtIndex(i));
        if (rule->getItemTID() == tID) {
            return rule->getLastTime();
        }
    }
    return -1;
}
//更新剩余使用次數
bool MB_ItemMgr::setUseItemLastTimes(MB_UseItemRule* data)
{
    if (data == NULL)
    {
        return false;
    }
    int count = m_pUseItemRuleArray->count();
    for (int i = 0; i < count; i++) {
         MB_UseItemRule* rule = (MB_UseItemRule*)(m_pUseItemRuleArray->objectAtIndex(i));
        if (rule->getItemTID() == data->getItemTID())
        {
            rule->setLastTime(data->getLastTime());
            if (data->getType() != 0)
            {
                rule->setType(data->getType());
            }
            return true;
        }
    }
    m_pUseItemRuleArray->addObject(data);
    return true;
}

void MB_ItemMgr::getUseItemTidByType(int type,std::vector<uint16_t>& vContainer)
{
    MB_UseItemRule* pTemp = NULL;
    CCARRAY_FOREACH_4TYPE(m_pUseItemRuleArray, MB_UseItemRule*, pTemp)
    {
        if (pTemp->getType() == type)
        {
            vContainer.push_back(pTemp->getItemTID());
        }
    }
}
uint8_t MB_ItemMgr::getUseItemType(uint16_t tID)
{
    if (!m_pUseItemRuleArray) {
        return 0;
    }
    for (int i = 0; i < m_pUseItemRuleArray->count(); i++) {
        MB_UseItemRule* rule = (MB_UseItemRule*)(m_pUseItemRuleArray->objectAtIndex(i));
        if (rule->getItemTID() == tID) {
            return rule->getType();
        }
    }
    return 0;
}

void  MB_ItemMgr::initUseItemLastTimes()
{
    MB_XmlFile* pXml = MB_XmlFile::create("config/item/item_point.xml");
    if (pXml == NULL)
    {
        return;
    }
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("data", pArray))
    {
        return;
    }
    
    m_pExpCardDataArray->removeAllObjects();
    
    MB_XmlNode* pRoot = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
    pArray->removeAllObjects();
    
    MB_XmlNode* pTemp = NULL;
    if(pRoot->queryNodesByName("time|times", pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            
            MB_UseItemRule* item = new MB_UseItemRule();
            item->setItemTID(pTemp->queryAttributeByName("id")->intValue());
            item->setLastTime(pTemp->queryAttributeByName("times")->intValue());
            item->setType(pTemp->queryAttributeByName("type")->intValue());
            setUseItemLastTimes(item);
            item->release();
        }
    }
    pArray->removeAllObjects();
    
 }
void MB_ItemMgr::initExpCardData()
{
    MB_XmlFile* pXml = MB_XmlFile::create("config/item/item_point.xml");
    if (pXml == NULL)
    {
        return;
    }
    
    CCArray* pArray = CCArray::create();
    if(!pXml->queryNodesByName("data", pArray))
    {
        return;
    }
    
    m_pExpCardDataArray->removeAllObjects();
    
    MB_XmlNode* pRoot = dynamic_cast<MB_XmlNode*>(pArray->objectAtIndex(0));
    pArray->removeAllObjects();
    
    MB_XmlNode* pTemp = NULL;
    MB_ExpCardData *pdata = NULL;
    if(pRoot->queryNodesByName("exps|exp", pArray))
    {
        CCARRAY_FOREACH_4TYPE(pArray, MB_XmlNode*, pTemp)
        {
            pdata = new MB_ExpCardData;
            if (pdata->init(pTemp))
            {
                m_pExpCardDataArray->addObject(pdata);
            }
            CC_SAFE_RELEASE_NULL(pdata);
        }
    }
    pArray->removeAllObjects();
    
}


bool MB_ItemMgr::CheckIsDebris(uint16_t type)//检查是否碎片
{
    if (type >= kDEBRIS_WEAPON && type <= kDEBRIS_RUNESTONE)
    {
        return true;
    }
    return false;
}

bool MB_ItemMgr::sortDebris(CCObject* p1,CCObject* p2)
{
    MB_ItemData* data1 = dynamic_cast<MB_ItemData*>(p1);
    MB_ItemData* data2 = dynamic_cast<MB_ItemData*>(p2);
    if (data1 == NULL || data2 == NULL)
    {
        return true;
    }
    MB_ItemTemplate* templete1 = MB_ItemMgr::getInstance()->getItemTemplateByID(data1->getItemID());
    MB_ItemTemplate* templete2 = MB_ItemMgr::getInstance()->getItemTemplateByID(data2->getItemID());
    
    if (data1->getItemNumber() >= templete1->getComposeNum() && data2->getItemNumber() < templete2->getComposeNum())
    {
        return true;
    }
    else if(data1->getItemNumber() < templete1->getComposeNum() && data2->getItemNumber() >= templete2->getComposeNum())
    {
        return false;
    }

    
    //星級排序，星級越高优先級越高
    if (templete1->getItemStar() > templete2->getItemStar())
    {
        return true;
    }
    else if(templete1->getItemStar() < templete2->getItemStar())
    {
        return false;
    }
    
    //拥有數量
    if (data1->getItemNumber() > data2->getItemNumber())
    {
        return true;
    }
    else if(data1->getItemNumber() < data2->getItemNumber())
    {
        return false;
    }
    
    //itemid升序
    if (templete1->getItemID() < templete2->getItemID())
    {
        return true;
    }
    else if(templete1->getItemStar() > templete2->getItemStar())
    {
        return false;
    }
    return true;
}
void MB_ItemMgr::sortDebrisArray()
{
    m_pItemDebrisArray->sortArray(MB_ItemMgr::sortDebris);
}


CCArray* MB_ItemMgr::getExpCardArray()
{
    m_pExpCardArray->sortArray(MB_ItemMgr::sortExpCard);
    return m_pExpCardArray;
}

bool MB_ItemMgr::sortExpCard(CCObject* p1,CCObject* p2)
{
    static int s = 0;
    s++;
//    CCLOG("count = %d",s);
    if (p1 == NULL || p2 == NULL) {
        return false;
    }
    MB_ItemData* data1 = dynamic_cast<MB_ItemData*>(p1);
    MB_ItemData* data2 = dynamic_cast<MB_ItemData*>(p2);
    
    if (data1 == NULL || data2 == NULL) {
        return true;
    }
    
    if (data1->getTemplateStar() > data2->getTemplateStar())
    {
        return true;
    }
    else if(data1->getTemplateStar() < data2->getTemplateStar())
    {
        return false;
    }
    
    if (data1->getItemID() <= data2->getItemID())
    {
        return true;
    }
    else
    {
        return false;
    }
    
}


bool MB_ExpCardData::init(MB_XmlNode* pNode)
{
    m_nTid = pNode->queryAttributeByName("id")->intValue();
    m_nExp = pNode->queryAttributeByName("exp_add")->intValue();
    return true;
}

uint32_t MB_ItemMgr::getExpByTid(uint16_t tid)
{
    MB_ExpCardData* data;
    CCARRAY_FOREACH_4TYPE(m_pExpCardDataArray, MB_ExpCardData*, data)
    {
        if (tid == data->getTid())
        {
            return data->getExp();
        }
    }
    return 0;
}

void MB_ItemMgr::sc_item_more(MB_MsgBuffer* recvPacket)
{
    uint16_t len;
    uint8_t data8;
    uint16_t data16;
    uint64_t data64;
    uint32_t data32;
    recvPacket->readU16(&len);
    for (int i = 0; i < len; i++)
    {
        MB_ItemData* itemData = new MB_ItemData();
        if (recvPacket->readU64(&data64))
        {
            itemData->setItemUID(data64);
        }
        if (recvPacket->readU16(&data16))
        {
            itemData->setItemID(data16);
        }
        if (recvPacket->readU8(&data8))
        {
            itemData->setItemLevel(data8);
        }
        if (recvPacket->readU8(&data8))
        {
            itemData->setItemRank(data8);
        }
        if (recvPacket->readU16(&data16))
        {
            itemData->setItemNumber(data16);
        }
        if (recvPacket->readU32(&data32))
        {
            itemData->setItemRankOverTim(data32);
        }
        if(recvPacket->readU16(&data16))
        {
            itemData->setExp(data16);
        }
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pItemDataArray, pObj)
        {
            //不应該有重複的实体被添加
            CC_ASSERT(((MB_ItemData*)pObj)->getItemUID() != itemData->getItemUID());
            
            if (((MB_ItemData*)pObj)->getItemUID() == itemData->getItemUID())
            {
                ((MB_ItemData*)pObj)->setItemNumber(((MB_ItemData*)pObj)->getItemNumber() + itemData->getItemNumber());
            }
        }
        m_pItemDataArray->addObject(itemData);
        itemData->release();
    }
    if(len == 0)sortMB_ItemDataArray();         //數量為0排序
}
