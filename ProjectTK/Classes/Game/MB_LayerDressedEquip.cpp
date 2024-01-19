//
//  MB_LayerDressedEquip.cpp
//  ProjectMB
//
//  Create by ChenHongkun on 23/9/2014.
//
//
#include "MB_LayerDressedEquip.h"
#include "../Common/GameLib/GameHelper/CCGameHelper.h"

MB_LayerDressedEquip* MB_LayerDressedEquip::create(TeamDataStruct* tdata)
{
    MB_LayerDressedEquip * node = new MB_LayerDressedEquip();
    node->m_pDataStruct = tdata;
    if( node && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return  NULL;
}

MB_LayerDressedEquip::MB_LayerDressedEquip()
{
    m_pTableContainer	 = NULL;
    m_pArrayShows = new CCArray;
    m_pTableView = NULL;
    m_pChapterText = NULL;
    m_bShowRoleInfoPanel = true;
}
MB_LayerDressedEquip::~MB_LayerDressedEquip()
{
    CC_SAFE_RELEASE_NULL(m_pTableContainer);
    CC_SAFE_RELEASE_NULL(m_pArrayShows);
    CC_SAFE_RELEASE_NULL(m_pChapterText);
}
bool MB_LayerDressedEquip::init()
{
    if ( !CCLayer::init() )return false;
    
    CCNode* pNode = loadResource("res/card_layer_switchequipment.ccbi");
    if(pNode)
	{
        this->addChild(NSGameHelper::createDisableTouchLayer12());
		addChild(pNode);
        
        
        m_pChapterText->setString("装备提升");
        NSGameHelper::adjustScrollNode(m_pTableContainer);
        m_pTableView = CCTableView::create(this, m_pTableContainer->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pTableContainer->addChild(m_pTableView);
        onResetWnd();
		return true;
	}
	return false;
}
void MB_LayerDressedEquip::onResetWnd()
{
    m_pArrayShows->removeAllObjects();
    if(m_pDataStruct)
    {
        if(m_pDataStruct->m_pEquip1)m_pArrayShows->addObject(m_pDataStruct->m_pEquip1);
        if(m_pDataStruct->m_pEquip2)m_pArrayShows->addObject(m_pDataStruct->m_pEquip2);
        if(m_pDataStruct->m_pEquip3)m_pArrayShows->addObject(m_pDataStruct->m_pEquip3);
        if(m_pDataStruct->m_pTreasure1)m_pArrayShows->addObject(m_pDataStruct->m_pTreasure1);
        if(m_pDataStruct->m_pTreasure2)m_pArrayShows->addObject(m_pDataStruct->m_pTreasure2);
        if(m_pDataStruct->m_pTreasure3)m_pArrayShows->addObject(m_pDataStruct->m_pTreasure3);
        
        if(m_pTableView)m_pTableView->reloadData();
    }
}
bool MB_LayerDressedEquip::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"SubItemPositionSign2",CCNode*,m_pTableContainer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "chapterText", CCLabelBMFont*, m_pChapterText);
	return false;
}
SEL_MenuHandler MB_LayerDressedEquip::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClicked",MB_LayerDressedEquip::onCloseClicked);
	return NULL;
}
SEL_CCControlHandler MB_LayerDressedEquip::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}
void MB_LayerDressedEquip::onCloseClicked(CCObject* pSender)
{
    popWindow(true);
}



CCSize MB_LayerDressedEquip::cellSizeForTable(CCTableView *table)
{
    return MB_NodeItemUnit::getUnitSize();
}

CCTableViewCell* MB_LayerDressedEquip::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
    
    MB_ItemData* itemData = (MB_ItemData*)m_pArrayShows->objectAtIndex(idx);
    if (itemData != NULL)
    {
        CCNode* pNode = MB_NodeItemUnit::create(kListItemTypeEquip, itemData->getItemUID(),false);
        pNode->setPosition( CCPointMake(MB_NodeItemUnit::getUnitSize().width/2, MB_NodeItemUnit::getUnitSize().height/2));
        cell->addChild(pNode);
    }

    return cell;
}

unsigned int MB_LayerDressedEquip::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrayShows->count();
}

