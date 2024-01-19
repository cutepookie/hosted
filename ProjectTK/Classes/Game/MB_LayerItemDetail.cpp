//
//  MB_LayerItemDetail.cpp
//  ProjectPM
//
//  Create by WenYong on 4/5/2014.
//
//
#include "MB_LayerItemDetail.h"
#include "MB_ItemData.h"
#include "MB_LayerListEquip.h"
#include "MB_LayerListEquipChange.h"
#include "MB_LayerItemEnhance.h"
#include "MB_LayerBackpack.h"
#include "MB_LayerSuitDetail.h"
#include "MB_LayerItemUpdate.h"
#include "MB_LayerItemList.h"
MB_LayerItemDetail::MB_LayerItemDetail()
{
    m_pMoveDown = NULL;
    m_pLabelBeEquip = NULL;
    m_pLastTimes = NULL;
    m_pBtnOpenMore = NULL;
    m_pNodeOpenOne= NULL;
    m_pNodeUse= NULL;
    m_pNodeOpenMore= NULL;
    m_pZBBtn = NULL;
    m_pNodeEquipProperty = NULL;
    m_pItemName	 = NULL;
    m_pProperty[0]	 = NULL;
    m_pProperty[1]	 = NULL;
    m_pProperty[2]	 = NULL;
    m_pProperty[3]	 = NULL;
    m_pDescribe	 = NULL;
    m_nItemTID = 0;
    m_nItemUID = 0;
    m_pNodeIcon = NULL;
    m_pNodeDescProperty = NULL;
    isSet = false;
    m_pBgEquip = NULL;
    m_pBgItem = NULL;
    m_pSuiPian = NULL;
    m_pBaoWu = NULL;
    m_pHCBtn = NULL;
    m_pMoveNode = NULL;
    m_pNum1 = NULL;
    m_pNum2 = NULL;
    m_pJLBtn = NULL;
    m_pQHBtn = NULL;
    m_bShowRoleInfoPanel = true;
    MB_LayerRoleInfoHeader::setMenuEnable(false,"MB_LayerItemDetail");
    
    
    for (int i = 0;i<4; i++) {
        m_pPropertyTitle[i] = NULL;
    }
}
MB_LayerItemDetail::~MB_LayerItemDetail()
{
    global_layerItemDetail = NULL;
    
    CC_SAFE_RELEASE_NULL(m_pMoveDown);
    CC_SAFE_RELEASE_NULL(m_pLabelBeEquip);
    CC_SAFE_RELEASE_NULL(m_pLastTimes);
    CC_SAFE_RELEASE_NULL(m_pBtnOpenMore);
    CC_SAFE_RELEASE_NULL(m_pNodeOpenOne);
    CC_SAFE_RELEASE_NULL(m_pNodeUse);
    CC_SAFE_RELEASE_NULL(m_pNodeOpenMore);
    CC_SAFE_RELEASE_NULL(m_pZBBtn);
    CC_SAFE_RELEASE_NULL(m_pNodeDescProperty);
    CC_SAFE_RELEASE_NULL(m_pNodeEquipProperty);
    
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pProperty[0]);
    CC_SAFE_RELEASE_NULL(m_pProperty[1]);
    CC_SAFE_RELEASE_NULL(m_pProperty[2]);
    CC_SAFE_RELEASE_NULL(m_pProperty[3]);
    
    CC_SAFE_RELEASE_NULL(m_pNodeIcon);
    CC_SAFE_RELEASE_NULL(m_pDescribe);
    
    CC_SAFE_RELEASE_NULL(m_pBgEquip);
    CC_SAFE_RELEASE_NULL(m_pBgItem);
    CC_SAFE_RELEASE_NULL(m_pSuiPian);
    CC_SAFE_RELEASE_NULL(m_pBaoWu);
    CC_SAFE_RELEASE_NULL(m_pHCBtn);
    CC_SAFE_RELEASE_NULL(m_pMoveNode);
    CC_SAFE_RELEASE_NULL(m_pNum1);
    CC_SAFE_RELEASE_NULL(m_pNum2);
    CC_SAFE_RELEASE_NULL(m_pJLBtn);
    CC_SAFE_RELEASE_NULL(m_pQHBtn);
    MB_LayerRoleInfoHeader::setMenuEnable(true,"MB_LayerItemDetail");
    
    for (int i = 0;i<4; i++) {
        CC_SAFE_RELEASE_NULL(m_pPropertyTitle[i]);
    }
    if (global_layerBackpack!=NULL&&global_layerBackpack->isResetWnd) {
        global_layerBackpack->isAnimation = false;
        global_layerBackpack->onResetWnd();
    }
}
bool MB_LayerItemDetail::init()
{
    global_layerItemDetail = this;
    CCNode* pNode = loadResource("res/item_layer_detailinfo.ccbi");
    if(pNode)
	{
        addChild(NSGameHelper::createDisableTouchLayer());
		addChild(pNode);
        
        if (m_eNowWindow == kDAOJU) {
            m_pZBBtn->setVisible(false);
        }else if (m_eNowWindow == KRENWUXIANGQING)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zhuangbei.plist");
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tmzz_btn_change_equ.png");
            m_pZBBtn->setBackgroundSpriteFrameForState(frame,CCControlStateNormal);
            m_pZBBtn->setBackgroundSpriteFrameForState(frame,CCControlStateHighlighted);
            m_pZBBtn->setBackgroundSpriteFrameForState(frame,CCControlStateSelected);
            m_pZBBtn->setBackgroundSpriteFrameForState(frame,CCControlStateDisabled);
        }
		return true;
	}
	return false;
}

void MB_LayerItemDetail::setItemUID(uint64_t uid)
{
    m_nItemUID = uid;
    m_nItemTID = 0;
    onReSet();
}
void MB_LayerItemDetail::setItemTID(uint16_t tid)
{
    m_nItemTID = tid;
    m_nItemUID = 0;
    onReSet();
}
void MB_LayerItemDetail::onReSet(bool isReSet)
{
    if (isReSet) {
        isSet = false;
    }
    if (m_nItemUID!=0)
    {
        MB_ItemData* pMB_ItemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
        if (pMB_ItemData)
        {
            m_nItemTID = pMB_ItemData->getItemID();
            uint8_t type = pMB_ItemData->getItemType();
            resetByTID(pMB_ItemData->getItemID(),pMB_ItemData);
        }else
        {
            runAction(CCSequence::create(CCDelayTime::create(.1f),CCRemoveSelf::create(),NULL));
        }
    }
    else if(m_nItemTID!=0)
    {
        resetByTID(m_nItemTID);
    }
}

void MB_LayerItemDetail::resetByTID(uint16_t nTypeID,MB_ItemData* pMB_ItemData)
{
    MB_ItemTemplate* pTemplate = MB_ItemMgr::getInstance()->getItemTemplateByID(nTypeID);
    if (pTemplate)
    {
        bool isEquip = pTemplate->getIsEquip();
        if (!isSet) {
            isSet = true;
            if (isEquip) {
                m_pBgEquip->setVisible(true);
                m_pBgItem->setVisible(false);
                
                if (m_nItemUID == 0) {
                    m_pItemName->setString(pTemplate->getItemName());
                    m_pQHBtn->setVisible(false);
                    m_pJLBtn->setVisible(false);
                }else
                {
                    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
                    if (itemData->getItemPetID() != 0)
                    {
                        m_pLabelBeEquip->setVisible(true);
                        char temp[128] = {0};
                        char* name = new char[64];
                        MB_PetMgr::getInstance()->getPetRealName(name, itemData->getItemPetID());
                        sprintf(temp, "已被\"%s\"装备", name);
                        CC_SAFE_DELETE_ARRAY(name);
                        m_pLabelBeEquip->setString(temp);
                        m_pDescribe->setVisible(true);
                        m_pDescribe->setPositionY(m_pDescribe->getPositionY()-10);
                    }else
                    {
                        m_pLabelBeEquip->setVisible(false);
                    }
                    
                    char* str = new char[32];
                    MB_ItemMgr::getInstance()->realName(str, m_nItemUID);
                    m_pItemName->setString(str);
                }
            }
            else
            {
                m_pItemName->setString(pTemplate->getItemName());
                m_pBgEquip->setVisible(false);
                m_pBgItem->setVisible(true);
                m_pMoveNode->setPositionY(-60);
                if (pTemplate->getIsDebris()) {
                    m_pSuiPian->setVisible(true);
                    m_pBaoWu->setVisible(false);
                    if (pMB_ItemData!=NULL) {
                        char str[20];
                        sprintf(str,"%d",pMB_ItemData->getItemNumber());
                        m_pNum1->setString(str);
                        sprintf(str,"/ %d",pTemplate->getComposeNum());
                        m_pNum2->setString(str);
                    }
                }else
                {
                    m_pSuiPian->setVisible(false);
                    m_pBaoWu->setVisible(true);
                    setItem(pTemplate);
                }
                
                if (m_nItemUID == 0) {
                    m_pSuiPian->setVisible(false);
                    m_pBaoWu->setVisible(false);
                }
            }
        }
        m_pNodeEquipProperty->setVisible(isEquip);

        m_pNodeIcon->removeAllChildren();
        MB_NodeItem* pIcon;
        if (m_nItemUID!=0) {
            pIcon = MB_NodeItem::create(m_nItemUID,kNINWNONE);
        }else
        {
            pIcon = MB_NodeItem::create(nTypeID,kNINWNONE);
        }

        pIcon->showNameCount(false);
        m_pNodeIcon->addChild(pIcon);
        
        m_pDescribe->setString(pTemplate->getItemDesc());
        
        pTemplate->getItemType();
        
        float  attack = 0.0f;
        float  hp = 0.0f;
        //属性
        if (pMB_ItemData)
        {
            attack = pTemplate->getAtrribute(eItem_Attribute_Type_Attack ,pMB_ItemData);
            hp = pTemplate->getAtrribute(eItem_Attribute_Type_HP , pMB_ItemData);
        }
        else
        {
            attack = pTemplate->getAtrribute(eItem_Attribute_Type_Attack ,1,0);
            hp = pTemplate->getAtrribute(eItem_Attribute_Type_HP , 1,0);
        }
        
        int nIndex = 0;
        char buff[64] = {};
        
        if(attack > 0)
        {
            m_pPropertyTitle[nIndex]->setString("攻击");
            sprintf(buff, "%.0f",attack);
            m_pProperty[nIndex++]->setString(buff);
        }
        if(hp > 0)
        {
            m_pPropertyTitle[nIndex]->setString("生命");
            sprintf(buff, "%.0f", hp);
            m_pProperty[nIndex++]->setString(buff);
        }
        
        int index = 0;
        attributeMap& attributes = pTemplate->getAtrributeMap();
        for ( attributeMap_It it = attributes.begin(); it !=  attributes.end(); it++)
        {
            if(it->first != eItem_Attribute_Type_Attack && it->first != eItem_Attribute_Type_HP)
            {
                sDesCommon* pItemCommon = MB_ItemMgr::getInstance()->getItemAttributeCommon((*it).first);
                if(pItemCommon)
                {
                    sprintf(buff, "%s",pItemCommon->queryValue("Name").toString().c_str());
                    m_pPropertyTitle[nIndex]->setString(buff);
                    if(it->first == eItem_Attribute_Type_Absorb || it->first == eItem_Attribute_Type_DamageBack)
                    {
                        sprintf(buff, "%.2f%%",(*it).second /100.0f);
                    }
                    else
                    {
                        sprintf(buff, "%d",(*it).second);
                    }
                    if (index > 1)
                    {
                        break;
                    }

                    m_pProperty[nIndex++]->setString(buff);
                    index++;
                }
            }
        }
        
        for (int i = nIndex; i<4; ++i)
        {
            m_pPropertyTitle[i]->setString("");
            m_pProperty[i]->setString("");
        }
        
        //套装
        if (pTemplate->getSuitID()!=0)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zhuangbei.plist");
            m_pBgEquip->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_item_taozhuang.png"));
            m_pMoveDown->setPositionY(-3);
            m_pNodeEquipProperty->setPositionY(650);
            m_pMoveNode->setPositionY(208);
            MB_LayerSuitDetail* pLayer = NULL;
            if (m_nItemUID)
            {
                pLayer = MB_LayerSuitDetail::create(m_nItemUID);
            }
            else if (m_nItemTID)
            {
                pLayer = MB_LayerSuitDetail::createByTid(m_nItemTID);
            }
            addChild(pLayer);
            pLayer->setPosition(ccp(0,0));
        }
    }
}

void MB_LayerItemDetail::setItem(MB_ItemTemplate* pTemplate)
{
    if (m_nItemUID == 0) {
        return;
    }
    if (pTemplate->getItemType() == kOTHER_BOX)//宝箱则显示打开按钮
    {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
        if(itemData->getItemNumber() > 1)
        {
            m_pNodeOpenMore->setVisible(true);
            m_pNodeOpenOne->setVisible(false);
            char str[32] = {};
            sprintf(str,"%d",itemData->getItemNumber()>10? 10:itemData->getItemNumber());
            NSGameHelper::setControlButtonTitleBMFontAllState(m_pBtnOpenMore, "fonts/font_1.fnt");
            NSGameHelper::setControlButtonTitleAllState(m_pBtnOpenMore, str);
            NSGameHelper::setControlButtonTitleBMFontScale(m_pBtnOpenMore,.44f,.34f);
        }
        else
        {
            m_pNodeOpenMore->setVisible(false);
            m_pNodeOpenOne->setVisible(true);
        }
    }
    else if(pTemplate->getItemType() == ENERGY_RECOVERY)//体力道具
    {
        int lastTimes = MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(pTemplate->getItemID());
        char str[20];
        if (lastTimes >= 0) {
            sprintf(str, "剩余次数:%d",lastTimes);
        }
        m_pLastTimes->setString(str);
        m_pNodeUse->setVisible(true);
    }
}
bool MB_LayerItemDetail::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    TutorialAssignLayerWindow
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMoveDown",CCNode*,m_pMoveDown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeEquipProperty",CCNode*,m_pNodeEquipProperty);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeDescProperty",CCNode*,m_pNodeDescProperty);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemName",CCLabelTTF*,m_pItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProperty1",CCLabelBMFont*,m_pProperty[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProperty2",CCLabelBMFont*,m_pProperty[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProperty3",CCLabelBMFont*,m_pProperty[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pProperty4",CCLabelBMFont*,m_pProperty[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPropertyTitle1",CCLabelTTF*,m_pPropertyTitle[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPropertyTitle2",CCLabelTTF*,m_pPropertyTitle[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPropertyTitle3",CCLabelTTF*,m_pPropertyTitle[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pPropertyTitle4",CCLabelTTF*,m_pPropertyTitle[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeIcon",CCNode*,m_pNodeIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pDescribe",CCLabelTTF*,m_pDescribe);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pZBBtn",CCControlButton*,m_pZBBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBtnOpenMore",CCControlButton*,m_pBtnOpenMore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBgEquip",CCSprite*,m_pBgEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBgItem",CCNode*,m_pBgItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pSuiPian",CCNode*,m_pSuiPian);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pBaoWu",CCNode*,m_pBaoWu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pHCBtn",CCNode*,m_pHCBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pMoveNode",CCNode*,m_pMoveNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNum1",CCLabelBMFont*,m_pNum1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNum2",CCLabelBMFont*,m_pNum2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelBeEquip",CCLabelTTF*,m_pLabelBeEquip);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LastTimes", CCLabelTTF *, m_pLastTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pJLBtn",CCNode*,m_pJLBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pQHBtn",CCNode*,m_pQHBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "openone", CCNode*, m_pNodeOpenOne);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "use", CCNode*, m_pNodeUse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "openmore", CCNode*, m_pNodeOpenMore);
    return false;
}
SEL_MenuHandler MB_LayerItemDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_LayerItemDetail::onCloseClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOpenClicked", MB_LayerItemDetail::onOpenClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUseClicked", MB_LayerItemDetail::onUseClicked);
    return NULL;
}
SEL_CCControlHandler MB_LayerItemDetail::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onClickQH",MB_LayerItemDetail::onClickQH);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onClickJL",MB_LayerItemDetail::onClickJL);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onClickZB",MB_LayerItemDetail::onClickZB);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onClickHC",MB_LayerItemDetail::onClickHC);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOpenMoreClicked", MB_LayerItemDetail::onOpenMoreClicked);
    
    return NULL;
}
void MB_LayerItemDetail::onCloseClicked(CCObject* pSender)
{
    TutorialTriggerComplete
    removeFromParent();
}
bool MB_LayerItemDetail::showItemDetailByTID(uint16_t nTid)
{
    MB_LayerItemDetail* pWnd = MB_LayerItemDetail::createByType(nTid);
    if (pWnd)
    {
        MB_SceneMain* pScene = (MB_SceneMain*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(LAYER_SCENE_MAIN);
        if (pScene)
        {
            pScene->addChild(pWnd,Z_ORDER_Detail);
        }else{
            CCDirector::sharedDirector()->getRunningScene()->addChild(pWnd, Z_ORDER_OUTSHOW);
        }
        return true;
    }
    
    return false;
}

bool MB_LayerItemDetail::showItemDetailByUID(uint64_t nUid)
{
    MB_ItemData* pItem = MB_ItemMgr::getInstance()->getItemDataByUID(nUid);
    if (pItem)
    {
        return showItemDetailByTID(pItem->getItemID());
    }
    
    return false;
}

MB_LayerItemDetail* MB_LayerItemDetail::create(uint64_t nUid,NODEITEMNOWWINDOW nowWindow)
{
    MB_LayerItemDetail* pInstance = new MB_LayerItemDetail;
    pInstance->m_eNowWindow = nowWindow;
    if (pInstance && pInstance->init())
    {
        pInstance->setItemUID(nUid);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

MB_LayerItemDetail* MB_LayerItemDetail::createByType(uint16_t nTid,NODEITEMNOWWINDOW nowWindow)
{
    MB_LayerItemDetail* pInstance = new MB_LayerItemDetail;
    pInstance->m_eNowWindow = nowWindow;
    if (pInstance && pInstance->init())
    {
        pInstance->setItemTID(nTid);
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}


void MB_LayerItemDetail::onClickQH(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_LayerItemUpdate* layer = MB_LayerItemUpdate::create(m_nItemUID);
    getParent()->addChild(layer);
    setVisible(false);
}
void MB_LayerItemDetail::onClickJL(CCObject* pSender)
{
    MB_LayerItemEnhance* layer = MB_LayerItemEnhance::create(m_nItemUID);
    getParent()->addChild(layer);
    setVisible(false);
}
void MB_LayerItemDetail::onClickZB(CCObject* pSender)
{
    if (m_eNowWindow == KRENWUXIANGQING) {
        MB_ResWindow* layer = MB_LayerListEquipChange::create(detail_type, detail_itemPos, m_nItemUID, detail_petID);
        popWindow();
        global_layerPetDetail->pushWindow(layer,true);
    }else
    {
        MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
        MB_ItemMgr::getInstance()->senditem_up_equip(global_layerPetDetail->m_pData->getPetID(), global_layerPetDetail->m_nZBItemPos, m_nItemUID, itemData->getItemPetID());
        MB_Message::sharedMB_Message()->showMessage("", 15);
    }
}

void MB_LayerItemDetail::onClickHC(CCObject* pSender)
{
    TutorialTriggerComplete
    MB_Message::sharedMB_Message()->showMessage("",30);
    MB_ItemMgr::getInstance()->senditem_compound(m_nItemTID);
}
void MB_LayerItemDetail::onUseClicked(CCObject* pSender){
    MB_LOG("onUseClicked");
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
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
    MB_ItemMgr::getInstance()->senditem_use(m_nItemUID,1);
}
void MB_LayerItemDetail::onOpenClicked(cocos2d::CCObject *pSender)
{
    MB_LOG("onOpenClicked");
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
    MB_ShopMgr::getInstance()->sendbox_item(itemData->getItemID());
}

void MB_LayerItemDetail::onOpenMoreClicked(cocos2d::CCObject *pSender)
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
    MB_ShopMgr::getInstance()->sendbox_item(itemData->getItemID(),(itemData->getItemNumber()>10)? 10:itemData->getItemNumber());
}
