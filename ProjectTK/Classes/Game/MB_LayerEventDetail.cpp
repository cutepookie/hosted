#include "MB_LayerEventDetail.h"
#include "MB_LayerEventUnit.h"
#include "MB_LayerEventDiscription.h"
MB_LayerEventDetail::MB_LayerEventDetail()
{
    m_pNodeScroller = NULL;
    m_pNodeDes = NULL;
}

MB_LayerEventDetail::~MB_LayerEventDetail()
{
    CC_SAFE_RELEASE(m_pNodeScroller);
    CC_SAFE_RELEASE(m_pNodeDes);
}

bool MB_LayerEventDetail::init(int eventID)
{
    if(MB_ResWindow::init() == false)
    {
        return false;
    }
    
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/activity_layer_background.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    
    NSGameHelper::adjustScrollNode(m_pNodeScroller);
    
    m_pData = MB_MoneyEevntMgr::getInstance()->getEventDataByActivityID(eventID);
    if(m_pData == NULL)
    {
        return false;
    }
    m_nlength =  m_pData->getUnitList()->count();
    m_UnitSize = MB_LayerEventUnit::create(2)->getUnitSize();
    m_nEventID = eventID;
    
    
    m_pTabelView = new CCTableView();
    m_pTabelView->setSwaller(false);
//    m_pTabelView->setTouchPriority(100);
    m_pTabelView ->initWithViewSize(m_pNodeScroller->getContentSize());
    m_pTabelView->setDirection(kCCScrollViewDirectionVertical);
    m_pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTabelView ->setDataSource(this);
    m_pTabelView->setDelegate(this);
    m_pTabelView->_updateCellPositions();
    m_pTabelView->_updateContentSize();
    m_pNodeScroller->addChild(m_pTabelView);
    m_pTabelView->release();
//    m_pTabelView->setTouchEnabled(false);
    
    
    MB_LayerEventDiscription* pNodeLayer =  MB_LayerEventDiscription::create();
    pNodeLayer ->setPosition(ccp(m_pNodeDes->getContentSize().width/2.0f,m_pNodeDes->getContentSize().height/2.0f));
    pNodeLayer->setClostTime(m_pData->getStopTime());
    pNodeLayer->setDiscription(m_pData->getDescription());
    pNodeLayer->setActivyID(m_pData->getActivityID());
    pNodeLayer->setNomCount(m_pData->getType(),m_pData->getTypeValue());
    m_pNodeDes->addChild(pNodeLayer);
    return true;
}
MB_LayerEventDetail * MB_LayerEventDetail::create(int eventID){
    
    MB_LayerEventDetail *ptr = new MB_LayerEventDetail();
    if(ptr && ptr->init(eventID)){
        
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_LayerEventDetail::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{

    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerEventDetail::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

bool MB_LayerEventDetail::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScroller", CCNode *, m_pNodeScroller);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeDes",CCNode*,m_pNodeDes);
    return false;
}





CCSize MB_LayerEventDetail::cellSizeForTable(CCTableView *table)
{
    return m_UnitSize;
}

unsigned int MB_LayerEventDetail::numberOfCellsInTableView(CCTableView *table)
{
    return m_nlength;
}

CCTableViewCell* MB_LayerEventDetail::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if(cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildrenWithCleanup(true);
    }

//    if(idx == 0)
//    {
//    }
//    else
//    {
    MB_MoneyEevntUnit * unit = (MB_MoneyEevntUnit *)m_pData->getUnitList()->objectAtIndex(idx);
    MB_LayerEventUnit * nodeLayer =  MB_LayerEventUnit::create(m_pData->getType());
    cell->addChild(nodeLayer);
    nodeLayer->setActivityAndUnit(m_pData->getActivityID(),unit->getDrawID());
    nodeLayer ->setPosition(ccp( m_UnitSize.width/2.0f, m_UnitSize.height/2.0f));
//    }
    
    //过期活动 不显示单元
    if(m_pData->getStopTime() > 0 && m_pData->getStopTime() < MB_ClientSocket::getInstance()->getServerTime())
    {
        cell->setVisible(false);
    }
    
    return cell;
}

void MB_LayerEventDetail::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{    
}
