
#include "MB_LayerInvite.h"

MB_LayerInvite::MB_LayerInvite(){

    m_pNode = NULL;
    m_pArray = NULL;
    m_pTableView = NULL;
    m_nLength = 0;
}
MB_LayerInvite::~MB_LayerInvite(){
    m_pArray->removeAllObjects();
    CC_SAFE_DELETE(m_pArray);
    CC_SAFE_RELEASE(m_pNode);
}

bool MB_LayerInvite::init(CCArray *array){

    if(MB_ResWindow::init() == false){
        
        return false;
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/gui_invent_list.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    
    
    m_nLength = array->count();
    m_pSize = MB_LayerInviteUnite::create()->getUnitSize();
    m_pArray = array;
    OCandCppHelper::convertScollerViewSuitable(m_pNode);
    m_pTableView = CCTableView::create(this, m_pNode->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pNode->addChild(m_pTableView,0);
    m_pTableView->reloadData();

    return true;
}
MB_LayerInvite* MB_LayerInvite::create(CCArray *array){
    
    MB_LayerInvite *ptr = new MB_LayerInvite();
    if(ptr && ptr->init(array)){
    
        ptr->autorelease();
        return  ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;

}
cocos2d::SEL_MenuHandler MB_LayerInvite::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClicked", MB_LayerInvite::onCloseClicked);
    return NULL;
}
void MB_LayerInvite::onCloseClicked(CCObject *){
    
    this->popWindow();
}
cocos2d::extension::SEL_CCControlHandler MB_LayerInvite::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    
    return NULL;
}
bool MB_LayerInvite::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode", CCNode *, m_pNode);
    return false;
}
void MB_LayerInvite::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){
}
cocos2d::CCSize MB_LayerInvite::cellSizeForTable(cocos2d::extension::CCTableView *table){
    
    return  m_pSize;
}
cocos2d::extension::CCTableViewCell* MB_LayerInvite::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    
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
    inviteData * data =(inviteData *) m_pArray->objectAtIndex(idx);
    MB_LayerInviteUnite *layer = MB_LayerInviteUnite::create();
    layer->setViteData(data);
    layer->setPosition(ccp(m_pSize.width/2.0f,m_pSize.height/2.0f));
    cell->addChild(layer);
    
    return cell;
}
unsigned int MB_LayerInvite::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){

    return m_nLength;
}
 void MB_LayerInvite::scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {
}
void MB_LayerInvite::scrollViewDidZoom(cocos2d::extension::CCScrollView* view){
}
