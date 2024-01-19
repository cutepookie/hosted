

#include "MB_NodeUpdatePetList.h"
#include "MB_LayerPetUpdate.h"
MB_NodeUpdatePetList::MB_NodeUpdatePetList(){
    
    m_pCheckList = new  CCArray();
    m_pListSize = NULL;
    m_pTableView = NULL;
    m_bShowRoleInfoPanel = true;
}
MB_NodeUpdatePetList::~MB_NodeUpdatePetList(){

    CC_SAFE_RELEASE_NULL(m_pCheckList);
    CC_SAFE_RELEASE_NULL(m_pListSize);
}
MB_NodeUpdatePetList* MB_NodeUpdatePetList::create(CCArray *list,uint64_t petID){

    MB_NodeUpdatePetList *ptr = new MB_NodeUpdatePetList();
   
    if(ptr && ptr->init(list,petID)){
        
        ptr->autorelease();
       
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool MB_NodeUpdatePetList::init(CCArray *list,uint64_t petID){

    m_nListSize = 0;
    m_nPetId = petID;
    m_pSize = MB_NodePetUnit::create(-1, 0)->getCellSize();
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node = pCCBReader->readNodeGraphFromFile("res/card_layer_expcardlist.ccbi", this);
    this->addChild(NSGameHelper::createDisableTouchLayer12());
    this->addChild(node);
    pCCBReader->release();
    
    CC_SAFE_RELEASE_NULL(m_pCheckList);
    m_pCheckList = MB_ItemMgr::getInstance()->getExpCardArray();
    CC_SAFE_RETAIN(m_pCheckList);
    
    
//    CCArray *petlist = MB_PetMgr::getInstance()->getPetDataArray(); 
//    CCObject *petData;
//  //  CCArray *tempList  =CCArray::create();
//    CCARRAY_FOREACH_REVERSE(petlist, petData){
//        
//        // 屏蔽守护神
//        if (((MB_PetData *)petData)->getIsHomelandPet())
//        {
//            continue;
//        }
//        if (MB_TeamData::getInstance()->checkInTeam((MB_PetData *)petData) == false &&((MB_PetData *)petData)->getPetID() != m_nPetId && ((MB_PetData *)petData)->getPetTypeID()< 10) {
//            
//                m_pCheckList->addObject(petData);
//        }
//    }
//    int length =tempList->count();
//    for (int i=0 ; i< length; i++) {
//      
//        MB_PetData *data = (MB_PetData *)tempList->objectAtIndex(0);
//        CCObject *petData;
//        CCARRAY_FOREACH(tempList, petData){
//        
//            MB_PetTemplate * templete1 = MB_PetMgr::getInstance()->getPetTemplateByID(data->getPetTypeID());
//            MB_PetTemplate * templete2 = MB_PetMgr::getInstance()->getPetTemplateByID(((MB_PetData *)petData)->getPetTypeID());
//            if (templete2->getPetStar() < templete1->getPetStar()) {
//                
//                data = (MB_PetData *)petData;
//            }
//        }
//        
//        m_pCheckList->addObject(data);
//        tempList->removeObject(data);
//    }
    
    
    m_pSoldList = list;
    m_nListSize = m_pCheckList->count();
    m_bIsEnd = false;
    //OCandCppHelper::convertScollerViewSuitable(m_pListSize);
    NSGameHelper::adjustScrollNode(m_pListSize);
    m_pTableView = CCTableView::create(this, m_pListSize->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setDelegate(this);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pListSize->addChild( m_pTableView,1);
    m_pTableView->reloadData();
    
    this->runAction(CCSequence::create(CCDelayTime::create(0.5f),CCCallFunc::create(this, callfunc_selector(MB_NodeUpdatePetList::whenActionOver)),NULL));
    return true;
}
cocos2d::SEL_MenuHandler MB_NodeUpdatePetList::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCloseClick", MB_NodeUpdatePetList::onListCloseClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUpdatePetList::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSoldClick", MB_NodeUpdatePetList::onSoldClick);
    
    return NULL;
}
bool MB_NodeUpdatePetList::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pListSize", CCNode *, m_pListSize);
    
    return false;
}
void MB_NodeUpdatePetList::onListCloseClick(CCObject *){
 
//    popWindow();
    onSoldClick(NULL);
}
void MB_NodeUpdatePetList::onSoldClick(CCObject *)
{
    MB_TARGET_PARENT(MB_LayerPetUpdate, ptr)
    {
        ptr->reloadData();
    }
//    MB_LayerPetUpdate *layer = (MB_LayerPetUpdate *)m_pLayerParent;
//    layer->reloadData();
    popWindow();
}
CCArray * MB_NodeUpdatePetList::getSoldList(){

    return   m_pSoldList;
}
void MB_NodeUpdatePetList::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){

}
cocos2d::CCSize MB_NodeUpdatePetList::cellSizeForTable(cocos2d::extension::CCTableView *table){

     return   m_pSize;
}
cocos2d::extension::CCTableViewCell* MB_NodeUpdatePetList::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
    
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

    MB_ItemData* data = (MB_ItemData*)m_pCheckList->objectAtIndex(idx);
    MB_NodeItemUnit* node = MB_NodeItemUnit::create(kListItemTypeLevelUp,data->getItemUID());
    node->setPosition(ccp( m_pListSize->getContentSize().width/2.0f, m_pSize.height/2.0f));
    cell->addChild(node);
    node->setTag(1);
    node->setShowSelect(m_pSoldList->containsObject(data));
    return cell ;
}
unsigned int MB_NodeUpdatePetList::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){

    return m_nListSize;
}
void MB_NodeUpdatePetList::scrollViewDidScroll(cocos2d::extension::CCScrollView* view){

}
void MB_NodeUpdatePetList::scrollViewDidZoom(cocos2d::extension::CCScrollView* view){
}
void MB_NodeUpdatePetList::onTouchHead(CCObject *){
}
void MB_NodeUpdatePetList::whenActionOver(){
    
       m_bIsEnd = true;
}
void MB_NodeUpdatePetList::setShowNode(uint64_t uid)
{
    int index = -1;
    for (int i = 0;i < m_pCheckList->count(); i++)
    {
        if(dynamic_cast<MB_ItemData*>(m_pCheckList->objectAtIndex(i))->getItemUID() == uid)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        if(index*m_pSize.height > m_pListSize->getContentSize().height)
        {
            m_pTableView->setContentOffset(ccp(0, -m_pSize.height*(m_pCheckList->count()-index-1)));

        }
    }
    
}
