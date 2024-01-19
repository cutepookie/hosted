
#include "MB_NodeRocketTeamReport.h"
MB_NodeRocketTeamReport::MB_NodeRocketTeamReport(){
    

    for (int i = 0 ; i < 10; i++){
        
        m_pAttack[i] = NULL;
        m_pUserName[i] = NULL;
        m_pSprite[i] = NULL;
    }
}
MB_NodeRocketTeamReport::~MB_NodeRocketTeamReport(){
    
  
    for (int i = 0 ; i < 10 ; i++){
    
        CC_SAFE_RELEASE(m_pAttack[i]);
        CC_SAFE_RELEASE(m_pUserName[i]);
        CC_SAFE_RELEASE(m_pSprite[i]);
    }
    SOCKET_MSG_UNREGIST(SC_HULA_OPEN);
    SOCKET_MSG_UNREGIST(SC_HULA_INIT_STATE);
    SOCKET_MSG_UNREGIST(SC_NANM_OPEN);
    SOCKET_MSG_UNREGIST(SC_NANM_INIT_STATE);
    
}
bool MB_NodeRocketTeamReport::init(){
    
    if(CCLayer::init() == false){
        
        return false;
        
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode*  node= pCCBReader->readNodeGraphFromFile("res/gui_hulao_rank.ccbi", this);
    this->addChild(node);
    pCCBReader->release();
    m_propertyDirty = false;
    m_nType = 0;
    onResetWnd();
    return true;
}
MB_NodeRocketTeamReport* MB_NodeRocketTeamReport::create(int type){

    MB_NodeRocketTeamReport * ptr = new MB_NodeRocketTeamReport();
    if( ptr && ptr->init(type) ){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
    
}
bool MB_NodeRocketTeamReport::init(int type){
    
    if(CCLayer::init() == false){
        
        return false;
        
    }
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    CCBReader *pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    std::string filename = "";
    filename = "res/station_layer_rocketdamage.ccbi";
    addChild(NSGameHelper::createDisableTouchLayer());
    CCNode*  node= pCCBReader->readNodeGraphFromFile(filename.c_str(), this);
    this->addChild(node);
    pCCBReader->release();
    m_propertyDirty = false;
    m_nType = type;
    onResetWnd();
    return true;
}
MB_NodeRocketTeamReport* MB_NodeRocketTeamReport::create(){
    
    MB_NodeRocketTeamReport * ptr = new MB_NodeRocketTeamReport();
    if( ptr && ptr->init() ){
        
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}
void MB_NodeRocketTeamReport::onResetWnd(){
    
    MB_EventData *m_pData = (MB_EventData *)MB_EventMgr::getInstence()->getEvenlist()->objectAtIndex(m_nType);

    int index = 0;
    CCObject *obj;
    char databuf[60];
  
    CCARRAY_FOREACH(m_pData->getHarmList(), obj){
        
        MB_EventHarm * m_pHarm = (MB_EventHarm * )obj;
        m_pUserName[index]->setString(m_pHarm->getName());
        sprintf(databuf, "总伤害:%lld (%.2lf%%)",m_pHarm->getHarm(),m_pHarm->getHarm()*100.0f/m_pData->getMaxHp());
        m_pAttack[index]->setString(databuf);
        if(strcmp(m_pHarm->getName(), MB_RoleData::getInstance()->getName()) == 0){
        
            if(m_pSprite[index])m_pSprite[index]->setColor(ccc3(0, 255, 0));
        }
        index++;
        if (index >=10) {
            
            break;
        }
    }
    for(int i= index ;i <10 ;i++){
    
        m_pUserName[i]->setString(" ");
        m_pAttack[i]->setString(" ");
    }
    
    
}
cocos2d::SEL_MenuHandler MB_NodeRocketTeamReport::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onCloseClick",MB_NodeRocketTeamReport::onCloseClick);
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler MB_NodeRocketTeamReport::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}
void MB_NodeRocketTeamReport::onCloseClick(CCObject*)
{
    popWindow();
}
bool MB_NodeRocketTeamReport::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode){
    
    char attack[]="m_pAttack0";
    char username[]="m_pUserName0";
    char sprite[] = "m_pSprite0";
    for (int i = 0 ; i < 10 ; i++){
     
        attack[9] = '0' +i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  attack, CCLabelTTF*, m_pAttack[i]);
        username[11]= '0'+i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,  username, CCLabelTTF*, m_pUserName[i]);
        sprite[9] = '0' +i;
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this,   sprite, CCScale9Sprite *, m_pSprite[i]);
    }
    return false;
}
