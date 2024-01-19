//
//  MB_NodeItemBuchong.cpp
//  ProjectPM
//
//  Create by WenYong on 9/5/2014.
//
//
#include "MB_NodeItemBuchong.h"
#include "MB_MailData.h"
#include "MB_SystemMailData.h"
#include "MB_LayerSystemMailDetail.h"
#include "MB_LayerMailView.h"
#include "MB_LayerItemList.h"
MB_NodeItemBuchong::MB_NodeItemBuchong()
{
    m_nItemUID = 0;
    m_pItemIcon	 = NULL;
    m_pItemName	 = NULL;
    m_pNodeSize = NULL;
    m_pItemDescription= NULL;
    m_pItemCanUseTimes= NULL;
}
MB_NodeItemBuchong::~MB_NodeItemBuchong()
{
    CC_SAFE_RELEASE_NULL(m_pItemIcon);
    CC_SAFE_RELEASE_NULL(m_pItemName);
    CC_SAFE_RELEASE_NULL(m_pNodeSize);
    CC_SAFE_RELEASE_NULL(m_pItemDescription);
    CC_SAFE_RELEASE_NULL(m_pItemCanUseTimes);
}

bool MB_NodeItemBuchong::init(uint64_t nItemUid)
{
    CCNode* pNode = loadResource("res/item_node_buchong.ccbi");
    if(pNode)
	{
		addChild(pNode);
        m_nItemUID = nItemUid;
        onResetWnd();
		return true;
	}
	return false;
}

void MB_NodeItemBuchong::onResetWnd()
{
    MB_ItemData* itemData = MB_ItemMgr::getInstance()->getItemDataByUID(m_nItemUID);
    MB_ItemTemplate* itemTemplete = MB_ItemMgr::getInstance()->getItemTemplateByID(itemData->getItemID());
    m_pItemName->setString(itemTemplete->getItemName());
    m_pItemDescription->setString(itemTemplete->getItemDesc());
    MB_NodeItem* nodeIcon = MB_NodeItem::create(m_nItemUID,kNINWNONE);
    nodeIcon->showNameCount(false);
    m_pItemIcon->addChild(nodeIcon);
    int lastTimes = MB_ItemMgr::getInstance()->getUseItemLastTimesByTID(itemData->getItemID());
    char str[20];
    if (lastTimes >= 0) {
        sprintf(str, "剩余次数 %d",lastTimes);
    }
    m_pItemCanUseTimes->setString(str);
}
bool MB_NodeItemBuchong::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemIcon",CCNode*,m_pItemIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemName",CCLabelTTF*,m_pItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeSize", CCNode*, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemDescription",CCLabelTTF*,m_pItemDescription);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pItemCanUseTimes",CCLabelTTF*,m_pItemCanUseTimes);
	return false;
}
SEL_MenuHandler MB_NodeItemBuchong::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
SEL_CCControlHandler MB_NodeItemBuchong::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"onUseItemClicked",MB_NodeItemBuchong::onUseItemClicked);
	return NULL;
}
void MB_NodeItemBuchong::onUseItemClicked(CCObject* pSender)
{
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

MB_NodeItemBuchong* MB_NodeItemBuchong::create(uint64_t nItemUid)
{
    MB_NodeItemBuchong* pInstance = new MB_NodeItemBuchong;
    if (pInstance && pInstance->init(nItemUid))
    {
        pInstance->autorelease();
        return pInstance;
    }
    
    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

CCSize MB_NodeItemBuchong::getNodeSize()
{
    MB_NodeItemBuchong* pTemp = new MB_NodeItemBuchong;
    if (pTemp)
    {
        CCBReader* pCCBReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
        CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_buchong.ccbi",pTemp);
        CC_SAFE_RELEASE_NULL(pCCBReader);
        if (pNode)
        {
            CCSize sz = pTemp->m_pNodeSize->getContentSize();
            CC_SAFE_RELEASE_NULL(pTemp);
            return sz;
        }
    }
    CC_SAFE_RELEASE_NULL(pTemp);
    return CCSize(0,0);
}
