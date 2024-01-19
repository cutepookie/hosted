

#include "MB_LayerInviteUnite.h"
MB_LayerInviteUnite::MB_LayerInviteUnite(){

    m_pRoleName = NULL;
    m_pLevel = NULL;
    m_pNotFirstTime = NULL;
    m_pHasFirstTime = NULL;
    m_pNodeIcon = NULL;
    m_pNodeSize = NULL;
    
}
MB_LayerInviteUnite::~MB_LayerInviteUnite(){

    CC_SAFE_RELEASE(m_pRoleName);
    CC_SAFE_RELEASE(m_pLevel);
    CC_SAFE_RELEASE(m_pNotFirstTime);
    CC_SAFE_RELEASE(m_pHasFirstTime);
    CC_SAFE_RELEASE(m_pNodeIcon);
    CC_SAFE_RELEASE(m_pNodeSize) ;
}
bool MB_LayerInviteUnite::init(){

    if(MB_ResWindow::init() == false){
    
        return false;
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/obj_invent_unit.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    return true;
}

MB_LayerInviteUnite* MB_LayerInviteUnite::create(){

    MB_LayerInviteUnite * ptr = new MB_LayerInviteUnite();
    if(ptr && ptr->init()){
    
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}
void MB_LayerInviteUnite::setViteData(inviteData *data){

    char databuf[50];
    sprintf(databuf, "Lv.%d",data->getlevel());
    m_pLevel->setString(databuf);
    MB_TitleTemplete *title = MB_TitleMgr::getInstance()->getTitleByID(data->getTitle());
    m_pRoleName->setString(data->getRoleName());

    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(data->getisMale() == 1 ? title->getMFaceFrame():title->getFFaceFrame());
    if (frame != NULL) {
        //头像
        m_pNodeIcon->setDisplayFrame(frame);
    }
    if(data->getIspay()){
    
        m_pHasFirstTime->setVisible(true);
        m_pNotFirstTime->setVisible(false);
    
    }else {
        
        m_pHasFirstTime->setVisible(false);
        m_pNotFirstTime->setVisible(true);
    
    }
    
}
CCSize MB_LayerInviteUnite::getUnitSize(){

    return m_pNodeSize->getContentSize();
}
cocos2d::SEL_MenuHandler MB_LayerInviteUnite::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMailClick", MB_LayerInviteUnite::onMailClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_LayerInviteUnite::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

     return NULL;
}
bool MB_LayerInviteUnite::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"size", CCNode*, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pRoleName",CCLabelTTF *,m_pRoleName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLevel",CCLabelTTF *,m_pLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNotFirstTime",CCLabelTTF *,m_pNotFirstTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pHasFirstTime",CCLabelTTF*,m_pHasFirstTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "roleIcon", CCSprite *, m_pNodeIcon);
    if(strcmp(pMemberVariableName, "menu") == 0 && pTarget == this){
        
        ((CCMenu *)pNode)->setSwallowsTouches(false);
        return  true;
    }
    return false;
}
void MB_LayerInviteUnite::onMailClick(CCObject *){
    
//    MB_TARGET_PARENT(MB_LayerInvite, ptr);
//    if(ptr){
//    
//        MB_MailEdit* layer = MB_MailEdit::create(m_pRoleName->getString());
//        ptr->pushWindow(layer, true);
//        layer->_setZOrder(Z_ORDER_OUTSHOW);
//    }    
}
