//
//  MB_LayerSelectMaterial.cpp
//  ProjectPM
//
//  Created by crimoon00007 on 14-3-19.
//
//

#include "MB_LayerSelectMaterial.h"
#include "Game.h"

MB_LayerSelectMaterial::MB_LayerSelectMaterial()
{
    m_pItemList = NULL;
    m_nCount = 0;
    m_nCurrentUid = 0;
    m_pSelectNode = NULL;
    m_nType = 0;
    m_pNodeList = NULL;
    m_pTitle = NULL;
    m_pDelegate = NULL;
    m_szGuiName = "res/item_layer_list5.ccbi";
    m_bShowRoleInfoPanel = true;
}

MB_LayerSelectMaterial::~MB_LayerSelectMaterial()
{
    CC_SAFE_DELETE_ARRAY(m_pItemList);
    CC_SAFE_RELEASE_NULL(m_pSelectNode);
    CC_SAFE_RELEASE_NULL(m_pNodeList);
    CC_SAFE_RELEASE_NULL(m_pTitle);
    m_nCurrentUid = 0;
    m_nCount = 0;
    m_nType = 0;
    m_pDelegate = NULL;
}

MB_LayerSelectMaterial* MB_LayerSelectMaterial::create(uint64_t* uids,uint32_t count,uint64_t nCurrentUid,uint16_t nType)
{
    MB_LayerSelectMaterial* pInstance = new MB_LayerSelectMaterial;
    if (pInstance && pInstance->init(uids, count, nCurrentUid, nType))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;
}

MB_LayerSelectMaterial* MB_LayerSelectMaterial::create(std::vector<uint64_t>& uids,uint64_t nCurrentUid, uint16_t nType)
{
    MB_LayerSelectMaterial* pInstance = new MB_LayerSelectMaterial;
    if (pInstance && pInstance->initWithContainer(uids, nCurrentUid, nType))
    {
        pInstance->autorelease();
        return pInstance;
    }

    CC_SAFE_RELEASE_NULL(pInstance);
    return pInstance;

}

bool MB_LayerSelectMaterial::initWithContainer(std::vector<uint64_t>& uids,uint64_t nCurrentUid, uint16_t nType)
{
    if (uids.empty())
    {
        return init(NULL, 0, nCurrentUid, nType);
    }

    size_t sz = uids.size();

    uint64_t* pUid = new uint64_t[uids.size()];

    for (int i=0; i<sz; ++i)
    {
        pUid[i] = uids[i];
    }

    bool ret = init(pUid, uids.size(), nCurrentUid, nType);

    CC_SAFE_DELETE_ARRAY(pUid);

    return ret;
}

bool MB_LayerSelectMaterial::init(uint64_t* uids,uint32_t count,uint64_t nCurrentUid,uint16_t nType)
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
    m_nCount = count;
    if (m_nCount == 0)
    {
        m_nCurrentUid = nCurrentUid;
        m_nType = nType;
        onResetWnd();
        return true;
    }
    
    MB_NodeSelect* pTemp = MB_NodeSelect::create(nType, uids[0]);
    m_Size = pTemp->getNodeSize();

    CC_SAFE_DELETE_ARRAY(m_pItemList);

    
    m_pItemList = new uint64_t[m_nCount];
    memcpy(m_pItemList, uids, sizeof(uint64_t)*m_nCount);
    m_nCurrentUid = nCurrentUid;
    m_nType = nType;

    m_pNodeList->removeAllChildren();
    NSGameHelper::adjustScrollNode(m_pNodeList);
    
    check2UpList();
    
    m_pTableView = CCTableView::create(this, m_pNodeList->getContentSize());
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setDirection( kCCScrollViewDirectionVertical);
    m_pNodeList->addChild(m_pTableView);

    onResetWnd();

    return true;
}

void MB_LayerSelectMaterial::check2UpList()
{
    if (m_nCurrentUid==0)
    {
        m_pSelectNode->setVisible(false);
        CCSize sz = m_pNodeList->getContentSize();
        m_pNodeList->setPositionY(m_pNodeList->getPositionY()+m_pSelectNode->getContentSize().height);
        sz.height = sz.height + m_pSelectNode->getContentSize().height;
        m_pNodeList->setContentSize(sz);
    }
}
void MB_LayerSelectMaterial::onResetWnd()
{
    m_pSelectNode->removeAllChildren();
    if (m_nCurrentUid)
    {
        MB_NodeSelect* pNode = MB_NodeSelect::create(m_nType, m_nCurrentUid);
        if (pNode)
        {
            pNode->m_pBtn1->setHighlighted(true);
            pNode->m_pBtn1->setEnabled(false);
            m_pSelectNode->addChild(pNode);
            pNode->setPosition(ccp(m_pSelectNode->getContentSize().width/2.0f,m_pSelectNode->getContentSize().height/2.0f));
        }
    }
    if (m_nCount)
    {
        m_pTableView->reloadData();
    }
}

void MB_LayerSelectMaterial::setTitle(const char* pTitle)
{
    m_pTitle->setString(pTitle);
}

bool MB_LayerSelectMaterial::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "chapterText", CCLabelBMFont*, m_pTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_list", CCNode*, m_pNodeList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "node_selected", CCNode*, m_pSelectNode);
    return false;
}

SEL_MenuHandler MB_LayerSelectMaterial::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_LayerSelectMaterial::onBackClicked);
    return NULL;
}

SEL_CCControlHandler MB_LayerSelectMaterial::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

CCSize MB_LayerSelectMaterial::cellSizeForTable(CCTableView *table)
{
    return m_Size;
}

CCTableViewCell* MB_LayerSelectMaterial::tableCellAtIndex(CCTableView *table, unsigned int idx)
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

unsigned int MB_LayerSelectMaterial::numberOfCellsInTableView(CCTableView *table)
{
    return m_nCount;
}

void MB_LayerSelectMaterial::onBackClicked(CCObject* pObject)
{
    popWindow();
}

void MB_LayerSelectMaterial::onNodeSelected(uint64_t nUid,uint16_t nType)
{
    if (m_pDelegate)
    {
        m_pDelegate->onNodeSelected(nUid, nType);
        onBackClicked(NULL);
    }
}
