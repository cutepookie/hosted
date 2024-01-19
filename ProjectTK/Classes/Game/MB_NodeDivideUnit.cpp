
#include "MB_NodeDivideUnit.h"
#include "MB_LayerListEquip.h"

MB_NodeDivideUnit::MB_NodeDivideUnit(){
}
MB_NodeDivideUnit::~MB_NodeDivideUnit(){

}
bool MB_NodeDivideUnit::init(CCLayer * layer){

    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/obj_sale_unit.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    m_pLayerParent = layer;
    return true;
}
MB_NodeDivideUnit * MB_NodeDivideUnit::create(CCLayer * layer){

    MB_NodeDivideUnit *ptr = new MB_NodeDivideUnit();
    if(ptr && ptr->init(layer)){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeDivideUnit::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDivideClick", MB_NodeDivideUnit::onDivideClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeDivideUnit::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    return NULL;
}
bool MB_NodeDivideUnit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){

    return false;
}
void  MB_NodeDivideUnit::onDivideClick(CCObject *){

    if(dynamic_cast<MB_NodePetList *>(m_pLayerParent) != NULL){
        
        ((MB_NodePetList *)m_pLayerParent)->onSoldClick(NULL);
    
    }else     if(dynamic_cast<MB_LayerListEquip  *>(m_pLayerParent) != NULL){
    
        ((MB_LayerListEquip *)m_pLayerParent)->onSaleClicked(NULL);
    }
    
}