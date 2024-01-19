
#include "MB_LayerPetCommand.h"
#include "MB_LayerPetEquipment.h"
MB_LayerPetCommand::MB_LayerPetCommand ()
{
    m_kLayerPetType = kSubLayerTypeTeam;
    m_bShowRoleInfoPanel = true;
    m_bShowHomeButton = true;
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerPetCommand",true);
}
MB_LayerPetCommand::~MB_LayerPetCommand ()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("LayerPetCommand",false);
}

MB_LayerPetCommand* MB_LayerPetCommand::create(int type)
{
    MB_LayerPetCommand* layer = new MB_LayerPetCommand();
    if (layer != NULL && layer->init(type)) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return NULL;
}

bool MB_LayerPetCommand::init(int type){

    if( CCLayer::init() == false ){
        
        return  false;
    }

    m_kLayerPetType = type;
    MB_TeamData::getInstance()->setNowPet(0);
    //init CCBReader
    onResetWnd();
    return  true;
}

void MB_LayerPetCommand::onResetWnd()
{
    if (m_kLayerPetType == kSubLayerTypeTeam) {
        
        enterTeamPage();
    }
    else if (m_kLayerPetType == kSubLayerTypePet)
    {
        enterPetEquip();
    }
    else
    {
        MB_LOG("init unkown sublayer type:%d", m_kLayerPetType);
    }
}

cocos2d::SEL_MenuHandler MB_LayerPetCommand::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTeamClicked",MB_LayerPetCommand ::onTeamClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPetEquipClicked",MB_LayerPetCommand ::onPetEquipClicked);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler MB_LayerPetCommand ::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

bool MB_LayerPetCommand::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    if (MB_ResWindow::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode)) {
        return true;
    }
 
    
    return  false;
}

void MB_LayerPetCommand::onTeamClicked(CCObject * sender)
{

    
    if (m_kLayerPetType == kSubLayerTypeTeam) {
        return;
    }
    enterTeamPage();
    MB_LOG("onChangeTeamClick");
}

void MB_LayerPetCommand::onPetEquipClicked(CCObject * sender)
{

    if (m_kLayerPetType == kSubLayerTypePet) {
        return;
    }
    enterPetEquip();
    MB_LOG("onPetEquipClicked");
}

void MB_LayerPetCommand::enterTeamPage()
{

    
    m_kLayerPetType = kSubLayerTypeTeam;
    
    MB_LayerPetTeam* layer = MB_LayerPetTeam::create(kPetTeamTypeMove);
    if (m_pSubLayer == NULL)
    {
        pushWindow(layer);
    }
    else
    {
        m_pSubLayer->replaceLayer(layer);
    }
}

void MB_LayerPetCommand::enterPetEquip()
{
   
    
    m_kLayerPetType = kSubLayerTypePet;
    
    MB_LayerPetEquipment* layer = MB_LayerPetEquipment::create();
    if (m_pSubLayer == NULL) {
        pushWindow(layer);
    }
    else
    {
        m_pSubLayer->replaceLayer(layer);
    }
}

