
#include "MB_ShopBase.h"
#include "Game.h"
#include "MB_ShopData.h"
//#include "MB_NodeReword.h"
#include "MB_LayerListItemEnhance.h"

//////////////////////////////////////////////////
MB_ShopPageBase::MB_ShopPageBase():m_pPageNode(NULL)
{
    m_pArray = new CCArray();
    m_pPanel = NULL;
    m_pTableView = NULL;
    m_uShopID     = 0;
    m_nListLength = 0;
    m_bShowRoleInfoPanel = true;
}

MB_ShopPageBase::~MB_ShopPageBase()
{
    m_pArray->removeAllObjects();
    CC_SAFE_DELETE(m_pArray);
    CC_SAFE_RELEASE(m_pPanel);
    CC_SAFE_RELEASE(m_pPageNode);
}

bool MB_ShopPageBase::init()
{
    MB_ResWindow::init();
    
    m_cellSize =  MB_ShopSubItem::create()->getUnitSize();

    return true;
}

void MB_ShopPageBase::onResetWnd()
{
    m_pShopInfo = MB_ShopMgr::getInstance()->getShopInfoByID(m_uShopID);
    
    CCAssert(m_pPanel, "");
    if (m_pTableView == NULL)
    {
//        NSGameHelper::adjustScrollNode(m_pPanel);
        m_pTableView = CCTableView::create(this, m_pPanel->getContentSize());
        m_pTableView->setDirection(kCCScrollViewDirectionVertical);
        m_pTableView->setDelegate(this);
        m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        m_pPanel->addChild(m_pTableView);
    }
}

bool MB_ShopPageBase::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return false;
}


SEL_MenuHandler MB_ShopPageBase::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler MB_ShopPageBase::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}


CCSize MB_ShopPageBase::cellSizeForTable(CCTableView *table)
{
    return m_cellSize;
}

CCTableViewCell* MB_ShopPageBase::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    return NULL;
}

unsigned int MB_ShopPageBase::numberOfCellsInTableView(CCTableView *table)
{
    return 0;
}

void MB_ShopPageBase::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    
}

void MB_ShopPageBase::scrollViewDidScroll(CCScrollView* view)
{
    
}

void MB_ShopPageBase::scrollViewDidZoom(CCScrollView* view)
{
}

void MB_ShopPageBase::ShowPageNode(bool b)
{
    if(m_pPageNode)
    {
        if(b)
        {
            m_pPageNode->setPosition(m_Pos);
        }
        else
        {
            m_pPageNode->setPosition(ccpAdd(m_Pos,ccp(50000,0)));
        }
        m_pPageNode->setVisible(b);
    }
}
                                                                 
