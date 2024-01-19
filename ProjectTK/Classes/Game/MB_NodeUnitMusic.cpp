

#include "MB_NodeUnitMusic.h"
MB_NodeUnitMusic::MB_NodeUnitMusic(){

    m_pMusicOpen = NULL;
    m_pMusicClose = NULL;
    m_pSoundOpen = NULL;
    m_pSoundClose = NULL;
    m_pNodeSize = NULL;
}
MB_NodeUnitMusic::~MB_NodeUnitMusic(){

    CC_SAFE_RELEASE(m_pMusicOpen);
    CC_SAFE_RELEASE(m_pMusicClose);
    CC_SAFE_RELEASE(m_pSoundOpen);
    CC_SAFE_RELEASE(m_pSoundClose);
    CC_SAFE_RELEASE(m_pNodeSize);
}
CCSize MB_NodeUnitMusic::getUnitSize()
{
    static CCSize size = MB_NodeUnitMusic::create()->getSize();
    
    return size;
}
bool MB_NodeUnitMusic::init(){

    MB_ResWindow::init();
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/setting_node_BGM.ccbi", this);
    pCCBReader->release();
    this->addChild(node);
    if(MB_Audio::getInstance()->getBackGroundOpen()){
        
        m_pMusicOpen->setVisible(false);
        
    }else {
        
        m_pMusicClose->setVisible(false);
        
    }
    if(MB_Audio::getInstance()->getEffectsoundOpen()){
        
        m_pSoundOpen->setVisible(false);
        
    }else {
        
        m_pSoundClose->setVisible(false);
    }

    return true;
}
MB_NodeUnitMusic* MB_NodeUnitMusic::create(){

    MB_NodeUnitMusic * ptr = new MB_NodeUnitMusic();
    if (ptr && ptr->init()) {
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
cocos2d::SEL_MenuHandler MB_NodeUnitMusic::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

     return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeUnitMusic::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSoundOnClick",  MB_NodeUnitMusic::onSoundOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSoundOffClick",  MB_NodeUnitMusic::onSoundOffClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMusicOnClick",  MB_NodeUnitMusic::onMusicOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMusicOffClick",  MB_NodeUnitMusic::onMusicOffClick);

     return NULL;
}
bool MB_NodeUnitMusic::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "size", CCNode *, m_pNodeSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "musicOpen", CCControlButton*,m_pMusicOpen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "musicClose", CCControlButton*,m_pMusicClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "soundOpen", CCControlButton*,m_pSoundOpen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "soundClose", CCControlButton*,m_pSoundClose);

    return false;
}

void MB_NodeUnitMusic::onSoundOnClick(CCObject *){
    
    SETBYKEY("soundOff", false);
    m_pSoundOpen->setVisible(false);
    m_pSoundClose->setVisible(true);
    MB_Audio::getInstance()->setEffectsoundOpen(true);
    
}
void MB_NodeUnitMusic::onSoundOffClick(CCObject *){
    
    SETBYKEY("soundOff", true);
    m_pSoundOpen->setVisible(true);
    m_pSoundClose->setVisible(false);
    MB_Audio::getInstance()->setEffectsoundOpen(false);
    
}
void MB_NodeUnitMusic::onMusicOnClick(CCObject *){
    
    SETBYKEY("musicOff",false);
    m_pMusicOpen->setVisible(false);
    m_pMusicClose->setVisible(true);
    MB_Audio::getInstance()->setBackGrondOpen(true);
    
}
void MB_NodeUnitMusic::onMusicOffClick(CCObject*){
    
    SETBYKEY("musicOff",true);
    m_pMusicOpen->setVisible(true);
    m_pMusicClose->setVisible(false);
    MB_Audio::getInstance()->setBackGrondOpen(false);
    
}
