

#include "MB_NodeItemUnitJingLian.h"
#include "MB_NodeItem.h"
#include "MB_LayerItemEnhance.h"
MB_NodeItemUnitJingLian::MB_NodeItemUnitJingLian()
{
    m_pLie = NULL;
    m_pNodeIcon = NULL;
    m_pSelectSpr = NULL;
}

MB_NodeItemUnitJingLian::~MB_NodeItemUnitJingLian()
{
    if (m_pLie!=NULL&&m_pSelectSpr->isVisible()) {
        m_pLie->m_pIujl = NULL;
    }

    CC_SAFE_RELEASE_NULL(m_pNodeIcon);
    CC_SAFE_RELEASE_NULL(m_pSelectSpr);
    
    
}

MB_NodeItemUnitJingLian* MB_NodeItemUnitJingLian::create(MB_LayerItemEnhance* lie, uint64_t itemUID)
{
    MB_NodeItemUnitJingLian* layer = new MB_NodeItemUnitJingLian();
    if (layer != NULL && layer->init(lie,itemUID)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

CCSize MB_NodeItemUnitJingLian::m_cellSizeItem = CCSizeZero;

CCSize MB_NodeItemUnitJingLian::getUnitSize()
{
    if(m_cellSizeItem.width == 0 || m_cellSizeItem.height == 0)MB_NodeItemUnitJingLian::create();
    
    return m_cellSizeItem;
}

bool MB_NodeItemUnitJingLian::init(MB_LayerItemEnhance* lie,uint64_t itemUID)
{
    if ( !CCLayer::init() )return false;
    m_pLie = lie;
    m_uItemUID = itemUID;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //读取界面
    CCBReader* pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("res/item_node_unitJingLian.ccbi", this);
    this->addChild(pNode);
    CC_SAFE_RELEASE_NULL(pCCBReader);
    
    MB_NodeItem* nodeIcon = MB_NodeItem::create(m_uItemUID,kNINWNONE);
    nodeIcon->showNameCount(false);
    m_pNodeIcon->addChild(nodeIcon);
    
    return true;
}

void MB_NodeItemUnitJingLian::onResetWnd()
{
}


bool MB_NodeItemUnitJingLian::onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode)
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
        }
        return true;
    }
    return true;
}




SEL_MenuHandler MB_NodeItemUnitJingLian::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseClicked", MB_NodeItemUnitJingLian::onChooseClicked);
    
    return NULL;
}
SEL_CCControlHandler MB_NodeItemUnitJingLian::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

void MB_NodeItemUnitJingLian::onChooseClicked(cocos2d::CCObject *pSender)
{
    if (!m_pSelectSpr->isVisible()) {
        m_pSelectSpr->setVisible(true);
        m_pLie->resetCostItemUID(this,m_uItemUID);
    }
}
