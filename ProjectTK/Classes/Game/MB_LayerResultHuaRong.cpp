

#include "MB_LayerResultHuaRong.h"

MB_LayerResultHuaRong::MB_LayerResultHuaRong(){
    
    m_pMorale = NULL;
    m_bIsPopScene = false;
    for (int i = 0 ; i < 5; i++) {
      
        m_pItem[i] = NULL;
        m_pItemName[i] = NULL;
    }

}
MB_LayerResultHuaRong::~MB_LayerResultHuaRong(){
    
    CC_SAFE_RELEASE(m_pMorale);
    for (int i = 0 ; i < 5; i++) {
        
       CC_SAFE_RELEASE( m_pItem[i]);
       CC_SAFE_RELEASE(m_pItemName[i]);
    }

}
MB_LayerResultHuaRong  * MB_LayerResultHuaRong::create(recvfight *fight,p_reward *result){
    
    MB_LayerResultHuaRong * ptr = new MB_LayerResultHuaRong();
    if(ptr && ptr->init(fight,result)){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
bool   MB_LayerResultHuaRong::init(recvfight *fight,p_reward *result){
    
    CCLayer::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode * node = ccbReader->readNodeGraphFromFile("res/gui_result_huarong.ccbi",this);
    this->addChild(node);
    CCBAnimationManager *m_pAnimationMgr = ccbReader->getAnimationManager();
    if(fight->issuccess == 1){
       
        char databuf[50];
        sprintf(databuf, "+%d",result->coin);
        m_pMorale ->setString(databuf);
        m_pAnimationMgr->runAnimationsForSequenceNamed("win");
        
    }else {
        
        m_pMorale ->setString("0");
        m_pAnimationMgr->runAnimationsForSequenceNamed("lose");
    }
    
    ccbReader->release();
    
    p_item_view *item = result->item;
    int i = 0;
    while ( item!=NULL && i< 5 ) {
        
        if(item->itemNum>0)
        {
            
            MB_NodeItem * node =MB_NodeItem::create((uint16_t)item->itemTypeId);
            node->setNum(item->itemNum);
            m_pItem[i] ->addChild( node );
            MB_ItemTemplate *itdata = MB_ItemMgr::getInstance()->getItemTemplateByID((uint16_t)item->itemTypeId);
            m_pItemName[i]->setString(itdata->getItemName());

        }
        else
        {
            
            MB_NodePet * node = MB_NodePet::create(item->itemTypeId,item->itemLevel,item->itemRank);
            m_pItem[i] ->addChild( node );
            MB_PetTemplate *petTemplete = MB_PetMgr::getInstance()->getPetTemplateByID(item->itemTypeId);
            const char *name = MB_PetMgr::getInstance()->getPetRealName((uint16_t)item->itemTypeId, (uint16_t)item->itemRank);
            m_pItemName[i]->setString(name);
             CC_SAFE_DELETE_ARRAY(name);
        }
        i++;
        item = item->next;        
    }
    
    return true;
}
cocos2d::SEL_MenuHandler MB_LayerResultHuaRong::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
 
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCallPetClick", MB_LayerResultHuaRong::onCallPetClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerResultHuaRong::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}
bool MB_LayerResultHuaRong::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMorale", CCLabelTTF *,m_pMorale);
    char item[] = "item1";
    char itemName[] = "itemname1";
    for (int i = 0 ; i < 5; i++) {
        
           item[4] = i + '1';
           CCB_MEMBERVARIABLEASSIGNER_GLUE(this, item, CCNode *,m_pItem[i]);
            itemName[8] = i + '1';
            CCB_MEMBERVARIABLEASSIGNER_GLUE(this, itemName ,CCLabelTTF *, m_pItemName[i]);

    }
    return false;
}
void MB_LayerResultHuaRong::onCallPetClick(CCObject *){
    
    if (m_bIsPopScene == false)
    {
        m_bIsPopScene = true;
        PlayBackGround(kmBackGround_Normal);
        CCDirector::sharedDirector()->popScene();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}
