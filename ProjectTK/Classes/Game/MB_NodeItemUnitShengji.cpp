

#include "MB_NodeItemUnitShengji.h"
#include "MB_NodeItem.h"
#include "MB_LayerPetUpdate.h"
MB_NodeItemUnitShengji::MB_NodeItemUnitShengji()
{
    m_pLpu = NULL;
    m_pNodeIcon = NULL;
    m_pSelectSpr = NULL;
}

MB_NodeItemUnitShengji::~MB_NodeItemUnitShengji()
{
    m_pLpu = NULL;
    CC_SAFE_RELEASE_NULL(m_pNodeIcon);
    CC_SAFE_RELEASE_NULL(m_pSelectSpr);
}

MB_NodeItemUnitShengji* MB_NodeItemUnitShengji::create(MB_LayerPetUpdate* lie, uint64_t itemUID)
{
    MB_NodeItemUnitShengji* layer = new MB_NodeItemUnitShengji();
    if (layer != NULL && layer->init(lie,itemUID)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

CCSize MB_NodeItemUnitShengji::m_cellSizeItem = CCSizeZero;

CCSize MB_NodeItemUnitShengji::getUnitSize()
{
    if(m_cellSizeItem.width == 0 || m_cellSizeItem.height == 0)MB_NodeItemUnitShengji::create();
    
    return m_cellSizeItem;
}

bool MB_NodeItemUnitShengji::init(MB_LayerPetUpdate* lie,uint64_t itemUID)
{
    if ( !CCLayer::init() )return false;
    m_pLpu = lie;
    m_uItemUID = itemUID;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //读取界面
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_unitJingLian.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    MB_NodeItem* nodeIcon = MB_NodeItem::create(m_uItemUID);
    nodeIcon->setOnClickEnable(false);
    nodeIcon->showNameCount(false);
    m_pNodeIcon->addChild(nodeIcon);
    
    return true;
}

void MB_NodeItemUnitShengji::onResetWnd()
{
}


bool MB_NodeItemUnitShengji::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSelectSpr", CCNode*, m_pSelectSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeIcon", CCNode*, m_pNodeIcon);
    
    if (strcmp(pMemberVariableName, "m_cellSizeItem") == 0 && pTarget == this) {
        m_cellSizeItem = pNode->getContentSize();
        return true;
    }
    
    if (pTarget == this && strcmp(pMemberVariableName, "scrollmenu") == 0)
    {
        CCMenu* menu = dynamic_cast<CCMenu*>(pNode);
        if (menu != NULL) {
            menu->setSwallowsTouches(false);
            menu->setTouchEnabled(false);
            menu->setTouchEnabled(true);
        }
        return true;
    }
    return true;
}




SEL_MenuHandler MB_NodeItemUnitShengji::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseClicked", MB_NodeItemUnitShengji::onChooseClicked);
    
    return NULL;
}
SEL_CCControlHandler MB_NodeItemUnitShengji::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodeItemUnitShengji::onChooseClicked(cocos2d::CCObject *pSender)
{
    CCArray* array = m_pLpu->m_pSoldList;
    MB_ItemData* data = MB_ItemMgr::getInstance()->getItemDataByUID(m_uItemUID);
    if (data == NULL)
    {
        return;
    }
    if (m_pSelectSpr->isVisible())
    {
        m_pSelectSpr->setVisible(false);
        array->removeObject(data);
    }
    else
    {
        if (array->count() >=6 ) {
            
            MB_Message::sharedMB_Message()->showMessage("只能选择6个材料");
            return;
        }
        m_pSelectSpr->setVisible(true);
        array->addObject(data);
    }
    m_pLpu->reloadData();
}
